// Implementation of core CMiniLexicon methods
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include <iostream>
#include <Q3TextStream>
#include <QTime>
#include "Lexicon.h"
#include "GUIclasses.h" 
#include "DescriptionLength.h"
#include "Datum.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "PrefixCollection.h"
#include "SuffixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "POSCollection.h"
#include "AffixLocation.h"
#include "log2.h"

CMiniLexicon::CMiniLexicon(CLexicon* lexicon, int index,
			enum eAffixLocation affixLocation)
	: m_pLexicon(lexicon),
	m_Index(index),
	m_AffixLocation(affixLocation),
	m_pWords(new CWordCollection(this)),
	m_pSuffixes(is_initial(affixLocation) ?
			0 :
			new CSuffixCollection(this)),
	m_pPrefixes(is_initial(affixLocation) ?
			new CPrefixCollection(this) :
			0),
	m_pStems(new CStemCollection(this)),
	m_pSignatures(is_initial(affixLocation) ?
		new CSignatureCollection(this, m_pPrefixes, affixLocation) :
		new CSignatureCollection(this, m_pSuffixes, affixLocation)),
	m_pPOS(),
	m_DescriptionLength(),
	m_CorpusCountOfUnanalyzedWords(0.0),
	m_PhonologicalInformationOfUnanalyzedWords(0.0),
	m_GUIWords(new GUIWordCollection(this, m_pWords)),
	m_DataMap(),
   m_pFSA(0) { }

CMiniLexicon::~CMiniLexicon()
{
	// Update corpus words when deleting mini-lexicon
	for (int i = 0; i < m_pWords->GetCount(); ++i) {
		CStem* word = m_pWords->GetAt(i);

		word->SimplifyParseStructure();
		m_pLexicon->UpdateWord(word);
	}
	m_pLexicon->DoWordUpdates();

	delete m_pWords;
	delete m_pSuffixes;
	delete m_pPrefixes;
	delete m_pStems;
	delete m_pSignatures;
	delete m_pPOS;
	delete m_DescriptionLength;
	delete m_GUIWords;
	delete m_pFSA;
}

void CMiniLexicon::AddToScreen( QString msg )
{
  m_pLexicon->AddToScreen( msg );
}

GUIWordCollection* CMiniLexicon::GetGUIWords()
{
    return m_GUIWords;
}

int CMiniLexicon::GetCorpusCount()
{
	return m_pLexicon->GetCorpusCount();
}

 
int CMiniLexicon::GetNumberOfCharacterTypes()
{
	return m_pLexicon->GetNumberOfCharacterTypes();
}


CDLHistory* CMiniLexicon::GetDLHistory()
{
	return m_pLexicon->GetDLHistory();
}


void CMiniLexicon::AddToWordCollection( CWordCollection* pWords, eWhichWords which_words )
{
	CStem* pWord, * qWord;
	int w;
	CStringSurrogate css;
	
	for( w = 0; w < (int) pWords->GetCount(); w++ )
	{
		pWord = pWords->GetAt(w);
		
		switch ( which_words )
		{
		case WW_All:
			qWord = (*m_pWords) << pWord;
			qWord->SetWordType( pWord->GetWordType() );
			break;
		case WW_AnalyzedOnly:
			if( pWord->Size() > 1 )
			{
				qWord = (*m_pWords) << pWord;
				qWord->SetWordType( pWord->GetWordType() );
			}
			break;
		case WW_UnanalyzedOnly:
		default:
			if( pWord->Size() <= 1 )
			{
				qWord = (*m_pWords) << pWord;
				qWord->SetWordType( pWord->GetWordType() );
			}
			break;
		}
	}
}


void CMiniLexicon::AddToWordCollection( CStemCollection* pWords )
{
	CStem* pWord, * qWord;
	int w;
	CStringSurrogate css;
	
	for( w = 0; w < (int) pWords->GetCount(); w++ )
	{
		pWord = pWords->GetAt(w);
		qWord = (*m_pWords) << pWord;
		if( pWord->GetStemType() == BIWORD_COMPOUND ||
			pWord->GetStemType() == MULTIPLE_COMPOUND )
		{
			qWord->SetWordType( STEM_COMPOUND );
		}
		else 
		{
			qWord->SetWordType( STEM_NORMAL );
		}
	}
}


void CMiniLexicon::ClearAll()
{
  if( m_pStems ) m_pStems->Empty();
  if( m_pWords ) m_pWords->Empty();
  
  if( m_pSuffixes ) m_pSuffixes->Empty();
  if( m_pPrefixes ) m_pPrefixes->Empty();
  
  if( m_pSignatures ) m_pSignatures->Empty();
}


CCorpusWord*  CMiniLexicon::FindAWord(CStem* pStem, CSuffix* pSuffix)
{
  return m_pLexicon->FindAWord(pStem, pSuffix);
}


CSuffixCollection* CMiniLexicon::FindSuffixes() //Suffixes/Run all
{
	QTime t;
	t.start();

	QString mini_name( "Mini-Lexicon %1" );
	mini_name = mini_name.arg( m_Index );

	QString remark;

	if( m_AffixLocation == STEM_FINAL || m_AffixLocation == WORD_FINAL )
	{
		m_pWords->SuccessorFreq1( GetStems(), GetSuffixes(), GetSignatures(), SF1, NUMBER | UNKNOWN );
 //      FindAllomorphy();
		CheckSignatures();
		ExtendKnownStemsToKnownAffixes();
		TakeSignaturesFindStems();
        TakeSignaturesFindStems();
		ExtendKnownStemsToKnownAffixes();
		FromStemsFindAffixes(); // problem here @@@ oct 2008 jg
//      ExtendKnownStemsToKnownAffixes();
		LooseFit();
		CheckSignatures();
		FindSingletonSignatures();
		CheckSignatures();
        FindMajorSignatures();
		m_pWords->m_DisplayMode = MiniLexicon_MorphologyStuffFirst;
		CalculateDescriptionLength();
		FindAllomorphy();
		m_pFSA = new FSA(this); 
	}

	std::cout << "Find Suffixes: Time elapsed: " <<
	t.elapsed() << "ms." << std::endl;

	return m_pSuffixes;
}


CPrefixCollection* CMiniLexicon::FindPrefixes()
{
	if( m_AffixLocation == STEM_INITIAL || m_AffixLocation == WORD_INITIAL )
	{
		m_pWords->CreateReverseTrie();

		m_pWords->PredecessorFreq1( GetStems(), GetPrefixes(), GetSignatures(), SF1, NUMBER | UNKNOWN );

		CheckSignatures();

		ExtendKnownStemsToKnownAffixes();

		TakeSignaturesFindStems();

		ExtendKnownStemsToKnownAffixes(); 

		FromStemsFindAffixes();

		ExtendKnownStemsToKnownAffixes();

		LooseFit();

		CheckSignatures();

		FindSingletonSignatures();

		return m_pPrefixes;
	}
	else return NULL;
}


LinguisticaMainWindow*  CMiniLexicon::GetDocument()
{
  return m_pLexicon->GetDocument();
}

int CMiniLexicon::GetIntParameter( QString strParam, int iDefault )
{
  return m_pLexicon->GetIntParameter( strParam, iDefault );
}


QTextStream* CMiniLexicon::GetLogFile()
{
  return m_pLexicon->GetLogFileStream();
}


int CMiniLexicon::GetMiniCount()
{
  return m_pLexicon->GetMiniCount();
}


int CMiniLexicon::GetMiniSize()
{
  return m_pLexicon->GetMiniSize();
}


CMiniLexicon* CMiniLexicon::GetMiniLexicon( int index )
{
  return m_pLexicon->GetMiniLexicon( index );
}


StringToString* CMiniLexicon::GetOutFilter()
{
  return m_pLexicon->GetOutFilter();
}


bool CMiniLexicon::LogFileOn()
{
	return (CLexicon*)m_pLexicon->LogFileOn();
}


bool CMiniLexicon::SetAffixLocation(enum eAffixLocation affixLoc)
{
	if (m_AffixLocation == affixLoc)
		// done, without lifting a finger!
		return true;

	if (is_initial(m_AffixLocation) == is_initial(affixLoc)) {
		m_AffixLocation = affixLoc;
		return true;
	}

	// Affix types differ: throw away discoveries.

	if (m_pStems->GetCount() != 0)
		// someone else could be using our discovered stems
		return false;

	if (is_initial(affixLoc)) {
		Q_ASSERT(m_pPrefixes == 0);
		m_pPrefixes = new CPrefixCollection(this);

		delete m_pSuffixes;
		m_pSuffixes = 0;
	} else {
		delete m_pPrefixes;
		m_pPrefixes = 0;

		Q_ASSERT(m_pSuffixes == 0);
		m_pSuffixes = new CSuffixCollection(this);
	}

	m_AffixLocation = affixLoc;

	delete m_pSignatures;
	m_pSignatures = is_initial(affixLoc) ?
		new CSignatureCollection(this, m_pPrefixes, affixLoc) :
		new CSignatureCollection(this, m_pSuffixes, affixLoc);
	return true;
}

int	CMiniLexicon::GetCorpusCountOfUnanalyzedWords		( )
{
	int i = 0;

	 
	m_CorpusCountOfUnanalyzedWords = 0;

		if ( GetAffixLocation() == WORD_FINAL || GetAffixLocation() == STEM_FINAL )
		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetSuffixSignature() ) 
				{
					m_CorpusCountOfUnanalyzedWords += m_pWords->GetAt(i)->GetCorpusCount();
				}
			}
		}
		else if (  GetAffixLocation() == WORD_INITIAL || GetAffixLocation() == STEM_INITIAL )

		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetPrefixSignature() ) 
				{
					m_CorpusCountOfUnanalyzedWords += m_pWords->GetAt(i)->GetCorpusCount();
				}
			}
		}
	
	return (int) m_CorpusCountOfUnanalyzedWords;
}
double CMiniLexicon::CalculateSumOfPointersToMyUnanalyzedWords ( eMDL_STYLE MDLflag)
{
 	int 	i = 0; 
	double 	total = 0;
	double	denominator = 0;
 
	switch (MDLflag)
	{
	case CorpusCount:

		
		denominator = GetCorpusCountOfUnanalyzedWords ( ) +
					  m_pStems->GetCorpusCount();
		
 
		if ( GetAffixLocation() == WORD_FINAL || GetAffixLocation() == STEM_FINAL )
		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetSuffixLoc() ) 
				{
					total += base2log ( denominator / (double)	 m_pWords->GetAt(i)->GetCorpusCount() ) ;
				}
			}
		}
		else if (  GetAffixLocation() == WORD_INITIAL || GetAffixLocation() == STEM_INITIAL )

		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetPrefixLoc() ) 
				{
					total += base2log ( denominator / m_pWords->GetAt(i)->GetCorpusCount() ) ;
				}
			}
		}
		break;

	case GrammarCount:
	int NumberOfUnanalyzedWords;
	GetNumberOfAnalyzedWords(NumberOfUnanalyzedWords);
	
 		denominator = NumberOfUnanalyzedWords +
					  m_pStems->GetTotalUseCount    ( );

		if ( GetAffixLocation() == WORD_FINAL || GetAffixLocation() == STEM_FINAL )
		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetSuffixLoc() ) 
				{
					total += base2log ( denominator ) ;
				}
			}
		}
		else if (  GetAffixLocation() == WORD_INITIAL || GetAffixLocation() == STEM_INITIAL )

		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetPrefixLoc() ) 
				{
					total += base2log ( denominator ) ;

				}
			}
		}

		break;

	}
	return total;
}

double CMiniLexicon::CalculateUnanalyzedWordsTotalPhonologicalInformationContent( )
{
	CLexicon* MotherLexicon = GetLexicon();
	int i; 
	if (   m_PhonologicalInformationOfUnanalyzedWords == 0)
	{
		if ( GetAffixLocation() == WORD_FINAL || GetAffixLocation() == STEM_FINAL )
		{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetSuffixLoc() ) 
				{
					m_PhonologicalInformationOfUnanalyzedWords += m_pWords->GetAt(i)->CalculatePhonologicalInformationContent( MotherLexicon );
				}
			}
		}
		else if (  GetAffixLocation() == WORD_INITIAL || GetAffixLocation() == STEM_INITIAL )
			{
			for (i = 0; i < m_pWords->GetCount(); i++)
			{
				if ( 0 == m_pWords->GetAt(i)->GetPrefixLoc() ) 
				{
					m_PhonologicalInformationOfUnanalyzedWords += m_pWords->GetAt(i)->CalculatePhonologicalInformationContent( MotherLexicon ); 
				}
			}
		}		
	}
		
		
	return	m_PhonologicalInformationOfUnanalyzedWords;

}

 
double CMiniLexicon::CalculateCompressedLengthOfUnanalyzedWords(  )
{	 
	double CompressedLengthOfUnanalyzedWords = 0;
	CLexicon* MotherLexicon = GetLexicon();
	int i;
	 
		if ( GetAffixLocation() == WORD_FINAL || GetAffixLocation() == STEM_FINAL )
		{
			for (i = 0; i < GetWords()->GetCount(); i++)
			{
				if ( NULL == GetWords()->GetAt(i)->GetSuffixSignature() ) 
				{
					CompressedLengthOfUnanalyzedWords	+= 
						GetWords()->GetAt(i)->CalculatePhonologicalInformationContent( MotherLexicon ) 
						*  GetWords()->GetAt(i)->GetCorpusCount();
				}
			}
		}
		else if ( GetAffixLocation() == WORD_INITIAL ||  GetAffixLocation() == STEM_INITIAL )
			{
			for (i = 0; i <  m_pWords->GetCount(); i++)
			{
				if ( 0 ==  m_pWords->GetAt(i)->GetPrefixSignature() ) 
				{
					CompressedLengthOfUnanalyzedWords  += 
						m_pWords->GetAt(i)->CalculatePhonologicalInformationContent( MotherLexicon )
						* m_pWords->GetAt(i)->GetCorpusCount(); 
				}
			}
		}		
			

	
	return CompressedLengthOfUnanalyzedWords;
}

int	CMiniLexicon::GetNumberOfAnalyzedWords (int& NumberOfUnanalyzedWords)
{
	CStem* pWord;
	int 	NumberOfAnalyzedWords = 0;
			NumberOfUnanalyzedWords = 0;
	for (int i = 0;i < m_pWords->GetCount(); i++)
	{
		pWord = m_pWords->GetAt(i);	
		if (pWord->IsAnalyzed() )
		{
			NumberOfAnalyzedWords++;
		}	else
		{
			NumberOfUnanalyzedWords++;
		}	
	}
	return NumberOfAnalyzedWords;
}




