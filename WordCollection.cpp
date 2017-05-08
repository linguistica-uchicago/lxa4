// Implementation for CWordCollection methods
// Copyright © 2009 The University of Chicago
#include "WordCollection.h"

#include <Q3TextStream>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "MonteCarlo.h"
#include "Alignment.h"
#include "Prefix.h"
#include "Suffix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "PrefixCollection.h"
#include "SuffixCollection.h"
#include "BiphoneCollection.h"
#include "PhoneCollection.h"
#include "StemCollection.h"
#include "StringSurrogate.h"
#include "Typedefs.h"
#include "HTML.h"
#include "log2.h"
#include "DLHistory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CWordCollection::CWordCollection(CMiniLexicon* Lex)
	: TCollection<CStem>(Lex, "Words"),
	m_AffixLocation(WORD_FINAL),
	m_DisplayMode(MiniLexicon_MorphologyStuffFirst),
	m_Phones_Tier1(new CPhoneCollection(this)),
	m_Phones_Tier2(new CPhoneCollection(this)),
	m_Phones_Tier1_Skeleton(new CPhoneCollection(this)),
	m_PhonologicalContent_Unigram(0.0),
	m_PhonologicalContent_Bigram(0.0),
	m_Tier2_LocalMI_Score(0.0),
	m_Tier2_DistantMI_Score(0.0),
	m_LocalMI_TotalBoltzmannScore(0.0),
	m_LocalMI_Plog(0.0),
	m_DistantMI_TotalBoltzmannScore(0.0),
	m_DistantMI_Plog(0.0),
	m_MyZ_Local(0.0),
	m_MyZ_Distant(0.0),
	m_Vowels(new CParse()) { }

CWordCollection::~CWordCollection()
{
	delete m_Phones_Tier1;
	delete m_Phones_Tier2;
	delete m_Phones_Tier1_Skeleton;
	delete m_Vowels;

	if (m_pLexicon != 0) {
		CLexicon& lex = *m_pLexicon;

		for (int i = 0; i < GetCount(); ++i)
			lex.RemoveWord(GetAt(i));
	}
}

CStem* CWordCollection::operator<< ( CStem* Word )
{
  CStem*	pWord;

  pWord =	AddToCollection (*Word);

  QChar*	pAlpha;

  pAlpha	= LxAlphabetizeString ( Word->GetKeyPointer(), Word->GetKeyLength() );
  pWord		->SetAlphabetizedForm ( QString( pAlpha, Word->GetKeyLength() ) );

  return pWord;
}

CStem* CWordCollection::operator<< ( CStem& Word )
{
  CStem*	pWord;

  pWord =	AddToCollection (Word);

  QChar*	pAlpha;

  pAlpha	= LxAlphabetizeString ( Word.GetKeyPointer(), Word.GetKeyLength() );
  pWord		->SetAlphabetizedForm ( QString( pAlpha, Word.GetKeyLength() ) );

  return pWord;
}
CStem* CWordCollection::operator<< ( CStringSurrogate& Word )
{
  CStem*  pWord;

  pWord = AddToCollection( Word );

  QChar*	pAlpha;
  pAlpha	= LxAlphabetizeString ( Word.GetKey(), Word.GetLength() );
  pWord		->SetAlphabetizedForm ( QString( pAlpha, Word.GetLength() ) );

  return pWord;
}


CStem* CWordCollection::operator<< ( CParse* Word )
{
  CStem*  pWord;

  pWord = AddToCollection (*Word);

  QChar* pAlpha;
  pAlpha = LxAlphabetizeString ( Word->GetKeyPointer(), Word->GetKeyLength() );
  pWord->SetAlphabetizedForm ( QString( pAlpha, Word->GetKeyLength() ) );

  return pWord;
}


CStem* CWordCollection::operator<< ( QString Word )
{
  CStem*  pWord;

  CStringSurrogate cssWord( Word );
  pWord = AddToCollection( cssWord );

  QChar* pAlpha;
  pAlpha = LxAlphabetizeString ( Word.unicode(), Word.length() );
  pWord->SetAlphabetizedForm ( QString( pAlpha, Word.length() ) );

  return pWord;
}


void CWordCollection::AddPointer( CStem* pWord )
{
	TCollection<CStem>::AddPointer( pWord );

	if( m_pLexicon ) m_pLexicon->InsertWord( pWord );
}


CStem* CWordCollection::AddToCollection( CParse& Word )
{
	CStem* pWord = TCollection<CStem>::AddToCollection( Word );

	if( m_pLexicon ) m_pLexicon->InsertWord( pWord );

	return pWord;
}


CStem* CWordCollection::AddToCollection( CStringSurrogate& Word )
{
	CStem* pWord = TCollection<CStem>::AddToCollection( Word );

	if( m_pLexicon ) m_pLexicon->InsertWord( pWord );

	return pWord;
}


void CWordCollection::Empty()
{
	if( m_pLexicon )
	{
		CStem* pWord;

		for( int i = 0; i < GetCount(); i++ )
		{
			pWord = GetAt(i);

			m_pLexicon->RemoveWord( pWord );
		}
	}

	TCollection<CStem>::Empty();
}


void CWordCollection::RemoveAll()
{
	if( m_pLexicon )
	{
		CStem* pWord;

		for( int i = 0; i < GetCount(); i++ )
		{
			pWord = GetAt(i);

			m_pLexicon->RemoveWord( pWord );
		}
	}

	TCollection<CStem>::RemoveAll();
}


bool CWordCollection::Remove( CStem* pWord )
{
	if( m_pLexicon ) m_pLexicon->RemoveWord( pWord );

	return TCollection<CStem>::Remove( pWord );
}


bool CWordCollection::RemoveMember( CStem* pWord )
{
	if( m_pLexicon ) m_pLexicon->RemoveWord( pWord );

	return TCollection<CStem>::RemoveMember( pWord );
}


bool CWordCollection::RemoveMember( CStringSurrogate& Word )
{
	CStem* pWord = *this ^= Word;

	if( m_pLexicon ) m_pLexicon->RemoveWord( pWord );

	return TCollection<CStem>::RemoveMember( Word );
}


bool CWordCollection::RemoveMember( CStringSurrogate& Word, bool b )
{
	CStem* pWord = *this ^= Word;

	if( m_pLexicon ) m_pLexicon->RemoveWord( pWord );

	return TCollection<CStem>::RemoveMember( Word, b );
}


void CWordCollection::DeleteMarkedMembers()
{
	if ( m_DeletionArray == NULL ) { return; }

	int count = GetCount();
	for (int i = 0; i < count; i++)
	{
		if ( m_DeletionArray[i] == 1 )
		{
			if( m_pLexicon ) m_pLexicon->RemoveWord( m_PointerArray[i] );
		}
	}

	TCollection<CStem>::DeleteMarkedMembers();
}


CPhoneCollection* CWordCollection::GetPhones()
{
	return m_Phones_Tier1;
}
CPhoneCollection* CWordCollection::GetPhones_Tier1_Skeleton()
{
	return m_Phones_Tier1_Skeleton;
}
CPhoneCollection* CWordCollection::GetPhones_Tier2()
{
	return m_Phones_Tier2;
}
 
void CWordCollection::AssignSignatureFromStemsAffixPointer( eAffixLocation AffixLoc )
{
  CStem*  pWord;
  CStem*  pStem;

  m_pLexicon->GetDocument()->setStatusBar2( "Assign signature to word" );
  m_pLexicon->GetDocument()->BeginCountDown();

  for (int i = 0; i < (int)GetCount(); i++)  // 3-21-2000 JG
  {
    m_pLexicon->GetDocument()->CountDownOnStatusBar(i, GetCount());
    pWord = GetAt(i);
    pStem = pWord->GetStemPtr();
    if (pStem)
    {
      if ( AffixLoc == WORD_FINAL)
      {
        pWord->SetSuffixSignature ( pWord->GetStemPtr()->GetSuffixSignature() );
      }
      else
      {
        pWord->SetPrefixSignature ( pWord->GetStemPtr()->GetPrefixSignature() );
      }
    }
  }
}

// TODO: this gets very slow when the total
// requested amount is large (>300,000) we
// should keep a running total during
// analysis.  For now, I am adding count down
// capabilities so the user doesn't think the
// program is stalled
int CWordCollection::HowManyAreAnalyzed( int& HowManyNotAnalyzed, LinguisticaMainWindow* doc  )
{
  int count = 0;
  CStem* pWord;
	HowManyNotAnalyzed = 0;	
  if( doc )
  {
    doc->BeginCountDown();
    doc->setStatusBar1( "Counting analyzed words." );
  }
  for (int i = 0; i < (int)GetCount(); i++)
  {
    if( doc ) doc->CountDownOnStatusBar( i, GetCount(), 0 );    
    pWord = GetAt(i);
    if (pWord->GetSuffixSignature() )
    {       count++;			}
    	 else
    {	HowManyNotAnalyzed++; 	}
  }

  if( doc )
  {
    doc->setStatusBar1( "" );
    doc->EndCountDown();
  }  
  return count;
}


void CWordCollection::PredecessorFreq1( CStemCollection* Stems,
                                             CPrefixCollection* Prefixes,
                                             CSignatureCollection* Signatures,
                                             eSuccessorFrequencyMode PFM,
                                             int ToBeRemoved )
{
  CStem*               pWord;
  CPrefixCollection    TempPrefixes;
  CStemCollection      TempStems;
  CSignatureCollection TempSigs ( m_pMiniLex, Prefixes, WORD_INITIAL ); // final 2 args added Dec 2008
  CSignatureCollection BadSigs ( m_pMiniLex );
  CPrefix*             pPrefix;
  CStem*               pStem;
  QString              ThisConf = "PF1";
  CStringSurrogate     ssPrefix,
                       ssStem;
  CParse               Word;
  QString              msg, Null = "NULL";
  CSignature*          pSig, *qSig;
  CParse               Prefix;
  int                  Length, i;


 
  const int  MinimumNumberOfAppearancesOfPrefix = m_pLexicon->GetIntParameter( "PredecessorFrequency\\MinimumNumberOfAppearancesOfPrefix", 2 );
  const int  MinimumNumberOfStemsInSignature    = m_pLexicon->GetIntParameter( "PredecessorFrequency\\MinimumNumberOfStemsInSignature", 2 );
  const int  MinimumLengthOfSignature           = m_pLexicon->GetIntParameter( "PredecessorFrequency\\MinimumLengthOfSignature", 2 );
  const int  MaxNeighborPredecessorCount        = m_pLexicon->GetIntParameter( "PredecessorFrequency\\MaxNeighborPredecessorCount", 1 );
  const int  LengthOfAStrongSignature           = m_pLexicon->GetIntParameter( "PredecessorFrequency\\LengthOfAStrongSignature", 5 );
  const int  MaximumPrefixLength                = m_pLexicon->GetIntParameter( "Main\\MaximumPrefixLength", 5 );
  const int  MinimumStemLength                  = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );
  const int  LargeNumberOfStems                 = m_pLexicon->GetIntParameter( "PredecessorFreq1\\LargeNumberOfStems", 25 );

  m_AffixLocation = WORD_INITIAL;

  if ( GetCount() == 0) { return; }

  if (PFM == SF1)
  {
    msg = "Predecessor Freq 1";
    m_pLexicon->GetDocument()->setStatusBar1 ( msg );
    Sort(KEY);
    T_PredecessorFrequency ( SF1, NULL, NULL,
                             MaxNeighborPredecessorCount,
                             MaximumPrefixLength,
                             MinimumStemLength );
  }
  else
  {
    msg = "Predecessor Freq 2";
    m_pLexicon->GetDocument()->setStatusBar1 ( msg );
    T_PredecessorFrequency( SF2, m_pMiniLex->GetStems(),
                            m_pMiniLex->GetPrefixes(),
                            MaxNeighborPredecessorCount,
                            MaximumPrefixLength,
                            MinimumStemLength );
  }
    
  //-------------  Use the breaks discovered by PredecessorFrequency --------------//
  m_pLexicon->GetDocument()->BeginCountDown();
  for ( i = 0; i < (int)GetCount(); i++)
  {
    pWord= GetAt(i);
    m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
    if ( ! pWord->MayBeParsed() ) continue; // if it's a compound

    // Do not analyze unwanted types
    if( ToBeRemoved >= POLYWORD_PIECE )
    {
      if( pWord->GetWordType() == POLYWORD_PIECE ) continue;
      ToBeRemoved -= POLYWORD_PIECE;
    }
    if( ToBeRemoved >= ENDS_IN_HYPHEN )
    {
      if( pWord->GetWordType() == ENDS_IN_HYPHEN ) continue;
      ToBeRemoved -= ENDS_IN_HYPHEN;
    }
    if( ToBeRemoved >= UNKNOWN )
    {
      if( pWord->GetWordType() == UNKNOWN ) continue;
      ToBeRemoved -= UNKNOWN;
    }
    if( ToBeRemoved >= NUMBER )
    {
      if( pWord->GetWordType() == NUMBER ) continue;
      ToBeRemoved -= NUMBER;
    }
    if( ToBeRemoved >= POSSIBLE_COMPOUND )
    {
      if( pWord->GetWordType() == POSSIBLE_COMPOUND ) continue;
      ToBeRemoved -= POSSIBLE_COMPOUND;
    }
    if( ToBeRemoved >= MULTIPLE_COMPOUND )
    {
      if( pWord->GetWordType() == MULTIPLE_COMPOUND ) continue;
      ToBeRemoved -= MULTIPLE_COMPOUND;
    }
    if( ToBeRemoved >= BIWORD_COMPOUND )
    {
      if( pWord->GetWordType() == BIWORD_COMPOUND ) continue;
      ToBeRemoved -= BIWORD_COMPOUND;
    }
    if( ToBeRemoved >= STEM_COMPOUND )
    {
      if( pWord->GetWordType() == STEM_COMPOUND ) continue;
      ToBeRemoved -= STEM_COMPOUND;
    }
    if( ToBeRemoved >= STEM_NORMAL )
    {
      if( pWord->GetWordType() == STEM_NORMAL ) continue;
      ToBeRemoved -= STEM_NORMAL;
    }
    if( ToBeRemoved >= STEM_PLUS_SUFFIX )
    {
      if( pWord->GetWordType() == STEM_PLUS_SUFFIX ) continue;
      ToBeRemoved -= STEM_PLUS_SUFFIX;
    }
    if( ToBeRemoved >= NORMAL )
    {
      if( pWord->GetWordType() == NORMAL ) continue;
      ToBeRemoved -= NORMAL;
    }

    if (pWord->Size() > 1 )
    {
      pPrefix = TempPrefixes << pWord->GetPiece(1);

      pPrefix->AppendToStemString( pWord->GetPiece(2) ); // TODO: What about the stem pointer list?
      pWord->SetStemLoc(2);
      pWord->SetPrefixLoc(1);
	  m_pLexicon->UpdateWord( pWord );
    }
  }
  
	//-------------  If a prefix appears only rarely, get rid of it --------------//
	for( i = 0; i < (int)TempPrefixes.GetCount(); i++ )
	{
		pPrefix = TempPrefixes.GetAt(i);

		if( pPrefix->GetCorpusCount() < MinimumNumberOfAppearancesOfPrefix )
		{
			pPrefix->MergeMeWithMyStems( m_pMiniLex );
		}
	}
	
	m_pLexicon->GetDocument()->BeginCountDown();

	//-------------  Make temporary signatures  --------------//
	for ( i = 0; i < (int)GetCount(); i++)
	{
		pWord = GetAt(i);
		m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
		if( !pWord->MayBeParsed() ) continue; // if it's a compound

		if(pWord->Size() > 1 )
		{
			pStem = TempStems << pWord->GetPiece(2);
			pStem->AddPrefix( pWord->GetPiece(1) );
		}
	}

	for( i = 0; i < (int)TempStems.GetCount(); i++)
	{
		pStem = TempStems.GetAt(i);
		if( *this ^= pStem->GetKey() )
		{
			pStem->AddPrefix( Null );
		}
		pSig = TempSigs << pStem->GetPrefixList();
		pSig->AttachToPrefixSig( pStem );
	}

	for( i = 0; i < (int)TempSigs.GetCount(); i++ )
	{
		pSig = TempSigs.GetAt(i);
		Length = 0;
		bool GoodFlag = TRUE;

		for( int m = 1; m <= pSig->Size(); m++ )
		{
			if( pSig->GetPiece(m).Display() == "NULL" )
			{
				Length += 1;
			}
			else
			{
				Length += pSig->GetPiece(m).GetLength() - 1;
			}
			// so NULL.b and b.p are both bad, but NULL.br and br.pr are both good
		}
		
		if( Length < MinimumLengthOfSignature && 
			pSig->GetNumberOfStems() < LargeNumberOfStems )
		{
			BadSigs << pSig;
			GoodFlag = FALSE;
		}

		// the idea in what follows is that if a signature is strong enough,
		// even one example suffices:
		if( Length < LengthOfAStrongSignature &&
			pSig->GetNumberOfStems() < MinimumNumberOfStemsInSignature )
		{
			BadSigs << pSig;
			GoodFlag = FALSE;
		}

		if( GoodFlag == TRUE )
		{
			for (int k = 1; k < pSig->Size(); k++)
			{
				TempPrefixes << pSig->GetPiece(k);
			}
		}
	}
	
	//-------------  Undo the bad signatures  --------------//
	for( i = 0; i < (int)BadSigs.GetCount(); i++ )
	{
		pSig = BadSigs.GetAt(i);
		qSig = TempSigs ^= pSig;
		
                for (int z = 0; z < qSig->GetStemPtrList()->size(); z++)
		{
                        pStem = qSig->GetStemPtrList()->at(z);
			ssStem = pStem->GetKey();
			
			for( int j = 1; j <= qSig->Size(); j++ )
			{
				ssPrefix = qSig->GetPiece(j);
				if( ssPrefix.IsNULL() ) continue;
				
				Word = ssPrefix + ssStem;
				pWord = *this ^= Word;
				
				if( pWord ) pWord->ClearPrefixStemSplit();
				m_pLexicon->UpdateWord( pWord );
			}
		}
		// redo these words in good
		// signatures IF POSSIBLE
		TempSigs.Remove( qSig );
	}
	
	// Now we have good word splits------------------------------------------
	
	m_pLexicon->GetDocument()->BeginCountDown();
	for( i = 0; i < (int)GetCount(); i++ )
	{
		pWord = GetAt(i);

		pWord->ClearPointers();

		m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
		if ( !pWord->MayBeParsed() ) continue; // if it's a compound
		if ( pWord->Size() < 2 ) continue; // Unanalyzed
		
		pStem = *Stems << pWord->GetPiece(2);
		pPrefix = *Prefixes << pWord->GetPiece(1);

		pWord->AttachWordStemAndPrefix( pStem, pPrefix ); //March 14 2003 inside AttachWordAndStem		

		pStem->IncrementCorpusCount( pWord->GetCorpusCount() - 1 );
		pPrefix->IncrementCorpusCount( pWord->GetCorpusCount() - 1 );
		
		pStem->IncrementWordCount();
		pStem->SetConfidence( "PF 1" );
		
		pWord->SetStemLoc(2);
		pWord->SetPrefixLoc(1);

		m_pLexicon->UpdateWord( pWord );
		
		pWord->DoNotParse();
	}
	
	
	for( i = 0; i < (int)Stems->GetCount(); i++ )
	{
		pStem = Stems->GetAt(i);
		if ( *this ^= pStem->GetKey() )
		{
			pStem->AddPrefix( Null );
			pPrefix = *m_pMiniLex->GetPrefixes() << CStringSurrogate(Null);
			pPrefix->IncrementUseCount();
			pPrefix->AddStem( pStem );
		}
		pSig = *Signatures << pStem->GetPrefixList();
		
		pSig->AttachToPrefixSig( pStem );
		pSig->IncrementCorpusCount( pStem->GetCorpusCount() );
		
		
                for (int z = 0; z < pStem->GetWordPtrList()->size(); z++)
                {
                        pWord = pStem->GetWordPtrList()->at(z);
			pWord->SetPrefixSignature ( pSig );
		}

		if( PFM == SF1 )
		{
			msg = "PF1";
			pSig->SetRemark( msg );
		}
		else if( PFM == SF2 )
		{
			msg = "PF2";
			pSig->SetRemark( msg );
		}
	}

	if( PFM == SF1 )
	{
		m_pLexicon->GetDocument()->setStatusBar1( "End of Predecessor Freq 1" );
	}
	else if( PFM == SF2 )
	{
		m_pLexicon->GetDocument()->setStatusBar1( "End of Predecessor Freq 2" );
	}
	
	m_pLexicon->GetDocument()->EndCountDown();
}

// Suffixes/Successor frequencies      bootstrap heuristic
void CWordCollection::SuccessorFreq1( CStemCollection* Stems,
                                      CSuffixCollection* Suffixes,
                                      CSignatureCollection* Signatures,
                                      eSuccessorFrequencyMode SFM,
                                      int ToBeRemoved )
{
  CSuffixCollection    TempSuffixes;
  CStemCollection      TempStems;
  CSignatureCollection TempSigs ( m_pMiniLex, Suffixes, WORD_FINAL ); //2nd and 3rd args added Dec 2008
  CSignatureCollection BadSigs ( m_pMiniLex );
  CSuffix*             pSuffix;
  CStem*               pStem;
  QString              ThisConf = "SF1";
  CStringSurrogate     ssSuffix,
                       ssStem;
  CParse               Word;
  QString              msg, Null = "NULL";
  CSignature*          pSig, *qSig;
  CParse               Suffix;
  int                  Length, i;

  const int MinimumNumberOfAppearancesOfSuffix = m_pLexicon->GetIntParameter( "SuccessorFreq1\\MinimumNumberOfAppearancesOfSuffix", 3 ); // 3;
  const int MinimumNumberOfStemsInSignature    = m_pLexicon->GetIntParameter( "SuccessorFreq1\\MinimumNumberOfStemsInSignature", 2 ); // 2;
  const int MinimumLengthOfSignature           = m_pLexicon->GetIntParameter( "SuccessorFreq1\\MinimumLengthOfSignature", 2 ); // 2;
  const int LengthOfAStrongSignature           = m_pLexicon->GetIntParameter( "SuccessorFreq1\\LengthOfAStrongSignature", 4 ); // 4;
  const int LargeNumberOfStems                 = m_pLexicon->GetIntParameter( "SuccessorFreq1\\LargeNumberOfStems", 25 ); // 25;
  const int MaxNeighborSuccessorCount          = m_pLexicon->GetIntParameter( "SuccessorFreq1\\MaxNeighborSuccessorCount", 1 );
  const int MaximumSuffixLength                = m_pLexicon->GetIntParameter( "Main\\MaximumSuffixLength", 5 );
  const int MinimumStemLength                  = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );

  m_AffixLocation = WORD_FINAL;

  if ( GetCount() == 0) { return; }

  if (SFM == SF1)
  {
    msg = "Successor Freq 1";
    m_pLexicon->GetDocument()->setStatusBar1 ( msg );
    Sort(KEY);
    T_SuccessorFrequency( SF1, NULL, NULL,
                           MaxNeighborSuccessorCount,
                           MaximumSuffixLength,
                           MinimumStemLength );
  }
  else
  {
    msg = "Successor Freq 2";
    m_pLexicon->GetDocument()->setStatusBar1 ( msg );
    T_SuccessorFrequency( SF2, m_pMiniLex->GetStems(),
                          m_pMiniLex->GetSuffixes(),
                          MaxNeighborSuccessorCount,
                          MaximumSuffixLength,
                          MinimumStemLength );
  }         
  
  //-------------  Use the breaks discovered by SuccessorFrequency --------------//
  m_pLexicon->GetDocument()->BeginCountDown();
  for ( i = 0; i < (int)GetCount(); i++)
  {
    CStem* pWord= GetAt(i);
    m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
    if ( ! pWord->MayBeParsed() ) { continue; } // if it's a compound

    // Do not analyze unwanted types
    if( ToBeRemoved >= POLYWORD_PIECE )
    {    
      if( pWord->GetWordType() == POLYWORD_PIECE ) continue;
      ToBeRemoved -= POLYWORD_PIECE;
    }

    if( ToBeRemoved >= ENDS_IN_HYPHEN )
    {
      if( pWord->GetWordType() == ENDS_IN_HYPHEN ) continue;
      ToBeRemoved -= ENDS_IN_HYPHEN;
    }
        if( ToBeRemoved >= UNKNOWN )
    {
      if( pWord->GetWordType() == UNKNOWN ) continue;
      ToBeRemoved -= UNKNOWN;
    }
        if( ToBeRemoved >= NUMBER )
    {
      if( pWord->GetWordType() == NUMBER ) continue;
      ToBeRemoved -= NUMBER;
    }
        if( ToBeRemoved >= POSSIBLE_COMPOUND )
    {
      if( pWord->GetWordType() == POSSIBLE_COMPOUND ) continue;
      ToBeRemoved -= POSSIBLE_COMPOUND;
    }
        if( ToBeRemoved >= MULTIPLE_COMPOUND )
    {
      if( pWord->GetWordType() == MULTIPLE_COMPOUND ) continue;
      ToBeRemoved -= MULTIPLE_COMPOUND;
    }
        if( ToBeRemoved >= BIWORD_COMPOUND )
    {
      if( pWord->GetWordType() == BIWORD_COMPOUND ) continue;
      ToBeRemoved -= BIWORD_COMPOUND;
    }
        if( ToBeRemoved >= STEM_COMPOUND )
    {
      if( pWord->GetWordType() == STEM_COMPOUND ) continue;
      ToBeRemoved -= STEM_COMPOUND;
    }
        if( ToBeRemoved >= STEM_NORMAL )
    {
      if( pWord->GetWordType() == STEM_NORMAL ) continue;
      ToBeRemoved -= STEM_NORMAL;
    }
        if( ToBeRemoved >= STEM_PLUS_SUFFIX )
    {
      if( pWord->GetWordType() == STEM_PLUS_SUFFIX ) continue;
      ToBeRemoved -= STEM_PLUS_SUFFIX;
    }
        if( ToBeRemoved >= NORMAL )
    {
      if( pWord->GetWordType() == NORMAL ) continue;
      ToBeRemoved -= NORMAL;
    }

		
    if( pWord->Size() > 1 )
    {
      pSuffix = TempSuffixes << pWord->GetPiece(2).Display();

      pSuffix->AppendToStemString( pWord->GetPiece(1) ); // TODO: What about the stem pointer list?
      pWord->SetStemLoc(1);
      pWord->SetSuffixLoc(2);
	  m_pLexicon->UpdateWord( pWord );
    }
  }
  //-------------  If a suffix appears only rarely, get rid of it --------------//
  for ( i = 0; i < (int)TempSuffixes.GetCount(); i++)
  {
    pSuffix = TempSuffixes.GetAt(i);

    if ( pSuffix->GetCorpusCount() < MinimumNumberOfAppearancesOfSuffix )
    {
      pSuffix->MergeMeWithMyStems( m_pMiniLex );
    }
  }

  m_pLexicon->GetDocument()->BeginCountDown();

  //-------------  Make temporary signatures  --------------//

  for ( i = 0; i < (int)GetCount(); i++)
  {
    CStem* pWord= GetAt(i);
    m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
    if ( ! pWord->MayBeParsed() ) { continue; } // if it's a compound

    if (pWord->Size() > 1 )
    {
      pStem = TempStems << pWord->GetPiece(1);

      pStem->AddSuffix( pWord->GetPiece(2) );
    }
  }         

  for ( i = 0; i < (int)TempStems.GetCount(); i++)
  {
    pStem = TempStems.GetAt(i);
    if ( *this ^= pStem->GetKey() )
    {
      pStem->AddSuffix( Null );
    }
    pSig = TempSigs << pStem->GetSuffixList();
    pSig->AttachToSuffixSig(pStem);
  }


  for ( i = 0; i < (int)TempSigs.GetCount(); i++)
  {
    pSig = TempSigs.GetAt(i);
    Length = 0;
    bool GoodFlag = TRUE;
            
    for (int m = 1; m <= pSig->Size(); m++)
    {
      if (pSig->GetPiece(m).Display() == "NULL")
      {
        Length += 1;
      }
      else
      {
        Length += pSig->GetPiece(m).GetLength() - 1;
      }
      // so NULL.b and b.p are both bad, but NULL.br and br.pr are both good
    }
    if ( Length < MinimumLengthOfSignature &&
       pSig->GetNumberOfStems() < LargeNumberOfStems )
    {
      BadSigs << pSig;
      GoodFlag = FALSE;
    }

    // the idea in what follows is that if a signature is strong enough,
    // even one example suffixes:
    if ( Length < LengthOfAStrongSignature &&
         pSig->GetNumberOfStems() < MinimumNumberOfStemsInSignature
       )
    {
      BadSigs << pSig;
      GoodFlag = FALSE;
    }


    if (GoodFlag == TRUE)
    {
      for (int k = 1; k < pSig->Size(); k++)
      {
        TempSuffixes << pSig->GetPiece(k).Display();
      }
    }
  }
            
  //-------------  Undo the bad signatures  --------------//
  for ( i = 0; i < (int)BadSigs.GetCount(); i++)
  {
    pSig = BadSigs.GetAt(i);
    qSig = TempSigs ^= pSig;

    for (int z = 0; z < qSig->GetStemPtrList()->size();z++)
    {
        pStem = qSig->GetStemPtrList()->at(z);
        ssStem = pStem->GetKey();

        for (int j = 1; j <= qSig->Size(); j++)
        {
            ssSuffix = qSig->GetPiece(j);
            if ( ssSuffix.IsNULL() ) continue;

            Word = ssStem + ssSuffix;
            CStem* pWord = *this ^= Word;
            if( pWord )  pWord->ClearRootSuffixSplit();
            m_pLexicon->UpdateWord( pWord );
      }
    }
    // redo these words in good
    // signatures IF POSSIBLE
    TempSigs.Remove (qSig);
  }
            
//   m_pMiniLex->TakeSplitWords_ProduceStemsAndSigs(CSS("Initial heuristic"));


if (TRUE) // this should be removed; it's replaced by the preceding line's function call.Oct 2008. But that didn't work right, actually --
{


  // Now we have good word splits------------------------------------------//

  m_pLexicon->GetDocument()->BeginCountDown();
  for ( i = 0; i < (int)GetCount(); i++)
  {
    CStem* pWord = GetAt(i);

    pWord->ClearPointers();

    m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
    if ( !pWord->MayBeParsed() ) { continue; } // if it's a compound
    if ( pWord->Size() < 2) { continue;} // Unanalyzed

    pStem  = *Stems  << pWord->GetPiece(1);
    pSuffix= *Suffixes  << pWord->GetPiece(2).Display();

    pWord  -> AttachWordStemAndSuffix (pStem, pSuffix); //March 14 2003 inside AttachWordAndStem
    m_pLexicon->UpdateWord( pWord );

 // Moved stem and suffix increments inside AttachWordStemAndSuffix : -cs- 2005/06/13

    pStem  -> SetConfidence ( "SF 1" );
    pWord  -> SetStemLoc(1);
    pWord  -> SetSuffixLoc(2);
    pWord  -> DoNotParse();
  }

  for ( i = 0; i < (int)Stems->GetCount(); i++)
  {
    pStem = Stems->GetAt(i);
    // Looking for Null suffixation
    if (CStem* pWord = *this ^= pStem->GetKey()) {
      pStem   -> IncrementCorpusCount ( pWord->GetCorpusCount() );// June 2005
      pStem   -> AddSuffix( Null );
      pSuffix =  *m_pMiniLex->GetSuffixes() << TheStringNULL;
      pSuffix -> IncrementUseCount();
      pSuffix -> IncrementCorpusCount( pWord->GetCorpusCount() - 1);
      pSuffix -> AddStem(pStem);
    }
    pSig  =  *Signatures << pStem->GetSuffixList();

    pSig->AttachToSuffixSig(pStem);
//    pSig  ->  IncrementCorpusCount( pStem->GetCorpusCount() );


    foreach (CStem* pWord, *pStem->GetWordPtrList()) {
      pWord->SetSuffixSignature ( pSig );
      m_pLexicon->UpdateWord( pWord );
    }

    if (SFM == SF1)
    {
      msg = "SF1";
      pSig->SetRemark( msg );
    }
    else if (SFM == SF2)
    {
      msg = "SF2";
      pSig->SetRemark( msg );
    }
  }

  if (SFM == SF1)
  {
    m_pLexicon->GetDocument()->setStatusBar1 ( "End of Successor Freq 1" );
  }
  else if (SFM == SF2)
  {
    m_pLexicon->GetDocument()->setStatusBar1 ( "End of Successor Freq 2" );
  }
}// end of second half

	GetMiniLexicon()->CalculateDescriptionLength(); // @@-DL-1
	QString mini_name( "Mini-Lexicon %1" );
	mini_name = mini_name.arg( m_pMiniLex->GetIndex() + 1 );
	QString remark = "SuccessorFreq ";
      m_pLexicon->GetDLHistory()->append( mini_name, remark, m_pMiniLex );
      m_pLexicon->GetDocument()->EndCountDown();
}


void CWordCollection::OutputWords( QString FileName )
{
	QFile file( FileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream outf( &file );
		outf.setEncoding( Q3TextStream::Unicode );

		outf << "# Word Count" << endl;
		outf << "# ----------" << endl;
		outf << "  " << GetCount() << endl << endl;

		outf << "# Index | Size | Pieces                                   | Corpus Count | Prefix Loc | Stem Loc | Suffix Loc | Signature " << endl;
		outf << "# ----------------------------------------------------------------------------------------------------------------------- " << endl;
		
		Sort( CORPUSCOUNT );
		for (int i = 0; i < (int)GetCount(); i++)
		{
			GetAtSort(i)->OutputWord( outf, i );
		}

		file.close();
	}
}


void CWordCollection::OutputWordsForTesting (QString FileName)
{
  CStem* pWord;
  QFile  file( FileName );

  if( file.open(QIODevice::WriteOnly) )
  {
    Q3TextStream  outf( &file );
    outf.setEncoding ( Q3TextStream::Unicode );

    outf.setf(2);
    outf << GetCount() << endl;

    Sort (KEY);
    for (int i = 0; i< (int)GetCount(); i++)
    {

      pWord = GetAtSort(i);

      outf.width(20);
      outf <<  pWord->GetKey().Display( m_pLexicon->GetOutFilter() ) << " ";
      outf.width(2);
      outf << pWord->Size() << " ";

      if ( pWord->GetStemPtr() )
      {
        outf.width(20);
        outf << pWord->GetStemPtr()->GetKey().Display( m_pLexicon->GetOutFilter() ) << " ";
      }
      if ( pWord->GetSuffixPtr() )
      {
        outf.width(8);
        outf << pWord->GetSuffixPtr()->GetKey().Display( m_pLexicon->GetOutFilter() ) << " ";
      }
      outf << endl;
    }
    file.close();
  }
}


void CWordCollection::ReadWordFile( QString FileName )
{
	CStem*		pWord;
	CSignature*	pSig;
	QFile		file(FileName);
	QString		buffer, 
				QstrSignature, 
				source;
				
	int			index,
				size,
				corpusCount,
				prefixLoc,
				stemLoc,
				suffixLoc,
				numberOfPieces,
				lineCount = 0;

	if( file.exists() && file.open( QIODevice::ReadOnly ) )
	{
		Q3TextStream inf(&file);
		inf.setEncoding ( Q3TextStream::Locale );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> size;

		buffer = inf.readLine(); // end of size line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine(); // blank line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );
		
		m_pLexicon->GetDocument()->BeginCountDown();

		while( !inf.atEnd() && lineCount < size )
		{
			m_pLexicon->GetDocument()->CountDownOnStatusBar( lineCount, size );

			lineCount++;
			
			pWord = new CStem( m_pMiniLex );

			inf >> index >> numberOfPieces;
			
			if( numberOfPieces == 0 ) numberOfPieces = 1;
			
			for( int i = 1; i <= numberOfPieces; i++ )
			{
				inf >> buffer;
				
				// Filter all sequences that should be
				// analyzed as one character
				buffer = Filter( m_pLexicon->GetInFilter(), buffer );
				
				pWord->Append( buffer );
			}
			
			inf >> corpusCount
				>> prefixLoc
				>> stemLoc
				>> suffixLoc
				>> QstrSignature;
				
			pWord->SetCorpusCount( corpusCount );
			m_CorpusCount += corpusCount;
			pWord->SetPrefixLoc( prefixLoc );
			pWord->SetStemLoc( stemLoc );
			pWord->SetSuffixLoc( suffixLoc );
			pWord->SetIndex( index );
			
			if( QstrSignature != "NONE" )
			{
				// Filter all sequences that should be
				// analyzed as one character
				QstrSignature = Filter( m_pLexicon->GetInFilter(), QstrSignature );
				
				pSig = *m_pMiniLex->GetSignatures() ^= QstrSignature ;

				if( suffixLoc != 0 )
				{
					pWord->SetSuffixSignature( pSig );
					pWord->SetPrefixSignature( NULL );
				}
				else if( prefixLoc != 0 )
				{
					pWord->SetPrefixSignature( pSig );
					pWord->SetSuffixSignature( NULL );
				}
			}
			
			// Insert the word into the trie
			CNode* pTerminal;
			pTerminal = Insert( pWord->GetKey() );
			pTerminal->SetPointer( pWord );
		}

		file.close();
	}  
}


 

//=====================================================================
void CWordCollection::CreatePhonologyFromOrthography()
{
	int i;
	for (i = 0; i<GetSize(); i++)
	{
		GetAt(i)->CreatePhonologyFromOrthography();
	}
}
//=====================================================================

void CWordCollection::CountPhonesAndBiphones(enum eTier WhichTier)
{
	int i;

	m_pLexicon->GetDocument()->BeginCountDown();
	m_pLexicon->GetDocument()->setStatusBar1( "Counting phones and biphones:" );

	
	switch (WhichTier)
	{
	case (TIER_1):
		{
			
			m_Phones_Tier1->Empty();
			m_Phones_Tier1->GetMyBiphones()->Empty();//clear();
			for (i=0; i < (int)  GetCount(); i++)
			{
				m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetSize(), 0 );				
				m_Phones_Tier1->CountPhonesAndBiphonesInWord(  GetAt(i), TIER_1 );
			}
			break;
		}
	case (TIER_2):
		{	m_Phones_Tier2->Empty();
			m_Phones_Tier2->GetMyBiphones()->clear();
		
			for (i=0; i < (int)  GetCount(); i++)
			{
				m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetSize(), 0 );
				m_Phones_Tier2->CountPhonesAndBiphonesInWord(  GetAt(i), TIER_2 );
			}
			break;
		}
	case (TIER_1_SKELETON):
		{
			m_Phones_Tier1_Skeleton->Empty();
			m_Phones_Tier1_Skeleton->GetMyBiphones()->clear();
		
			for (i=0; i < (int)  GetCount(); i++)
			{
				m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetSize(), 0 );
				m_Phones_Tier1_Skeleton->CountPhonesAndBiphonesInWord(  GetAt(i), TIER_1_SKELETON );
			}
			break;
		}

	
	}
}
//===================================================================== 
void CWordCollection::DoPhonology()
{	 
//	m_Vowels->ClearParse();
//	m_Vowels->Collapse( CStringSurrogate (m_pLexicon->GetStringParameter( "Symbols\\Vowels" ) ) ); 	   

	const QChar vowels[] = {
		'a', 'e', 'i', 'o', 'u', 'y',
		'A', 'E', 'I', 'O', 'U', // XXX. but not Y in Yttrium?
		228, 246, '@' // ä, ö, @
	};
	const std::size_t num_vowels = sizeof(vowels)/sizeof(QChar);

	for (const QChar* vowel = &vowels[0];
			vowel != &vowels[num_vowels];
			++vowel)
		*m_Vowels << CSS(vowel, 0, 1);

	static bool AlreadyDone(false);

	if ( AlreadyDone == false && GetCount () > 0 )
	{
		CreatePhonologyFromOrthography();
 		 
		CountPhonesAndBiphones(TIER_1);
		// XXX. this should be made conditional on Tier2
		// having been already created
//		CountPhonesAndBiphones(TIER_2);

		GetPhones()->Normalize();
		GetPhones_Tier2()->Normalize();
		
		ComputeProbabilitiesOfWords();
		GetPhonologyTierInfoForGraphOfWords(); 
	}

	AlreadyDone = true;


	m_DisplayMode = MiniLexicon_PhonologyStuffFirst;


}

//====================================================================
void CWordCollection::CreateCVTemplate()
{
	
	int i;
	static bool AlreadyDone(false);

	if (AlreadyDone == true ) return;

	for (i = 0; i<GetSize(); i++)
	{
		GetAt(i)->CreateCVTemplate( m_Vowels);
	}
	CountPhonesAndBiphones(TIER_1_SKELETON);
	m_Phones_Tier1_Skeleton->Normalize();

	AlreadyDone =  true;

}

//=====================================================================


void	CWordCollection::SplitPhonologyToTiers (ePhonologySplitType SplitType )
{
	int i;
	static bool AlreadyDone = false;

	if ( AlreadyDone == true) return;

	for (i = 0; i<GetSize(); i++)
	{
		GetAt(i)->SplitPhonologyToTiers (SplitType, *m_Vowels);
	}
	CountPhonesAndBiphones(TIER_1);
	CountPhonesAndBiphones(TIER_2);

	GetPhones()->Normalize();
	GetPhones_Tier2()->Normalize();
	
	ComputeProbabilitiesOfWords();
	
	AlreadyDone = true;

}
 
//=====================================================================
void CWordCollection::ComputeProbabilitiesOfWords( )
{
	int i;
	m_PhonologicalContent_Unigram = 0;
	m_PhonologicalContent_Bigram = 0;
	m_Tier2_LocalMI_Score = 0;
	m_Tier2_DistantMI_Score = 0;
	m_MyZ_Local = 0;
	m_MyZ_Distant = 0;

	m_pLexicon->GetDocument()->BeginCountDown();
	m_pLexicon->GetDocument()->setStatusBar1( "Computing word probabilities:" );



	for (i = 0; i<GetSize(); i++)
	{

		m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetSize(), 0 );

		GetAt(i)->ComputeProbabilities(this);
		m_PhonologicalContent_Unigram += GetAt(i)->GetUnigramLogProb();
		m_PhonologicalContent_Bigram  += GetAt(i)->GetBigramLogProb();
		m_Tier2_LocalMI_Score		  += GetAt(i)->GetTier2_LocalMI_Score();
		m_Tier2_DistantMI_Score		  += GetAt(i)->GetTier2_DistantMI_Score();
		m_LocalMI_Plog				  += GetAt(i)->GetLocalMI_Plog();
		m_DistantMI_Plog			  += GetAt(i)->GetDistantMI_Plog();

		

	}

	m_pLexicon->AddToScreen( QString ("Unigram content: %1  Bigram content: %2"). 
		arg( (int) m_PhonologicalContent_Unigram, 10 ).
	    arg( (int) m_PhonologicalContent_Bigram , 10 )   );
 
}

void CWordCollection::ComputeBoltzmannProbabilities()
{
	int i;
	m_Tier2_LocalMI_Score			=0;
	m_Tier2_DistantMI_Score			=0;
	m_LocalMI_TotalBoltzmannScore	=0; 
	m_LocalMI_Plog					=0;
	m_DistantMI_TotalBoltzmannScore	=0; 
	m_DistantMI_Plog				=0;

	

	for (i = 0; i<GetSize(); i++)
	{
		GetAt(i)->ComputeBoltzmannProbabilities(m_MyZ_Local, 
												m_MyZ_Distant);	
		m_Tier2_LocalMI_Score			+= GetAt(i)->GetTier2_LocalMI_Score();
		m_Tier2_DistantMI_Score			+= GetAt(i)->GetTier2_DistantMI_Score();
		m_LocalMI_TotalBoltzmannScore	+= GetAt(i)->GetLocalMI_TotalBoltzmannScore();
		m_LocalMI_Plog					+= GetAt(i)->GetLocalMI_Plog();
		m_DistantMI_TotalBoltzmannScore	+= GetAt(i)->GetDistantMI_TotalBoltzmannScore();
		m_DistantMI_Plog				+= GetAt(i)->GetDistantMI_Plog();

	}

}
 
double CWordCollection::ComputeZ()
{

	int			NumberOfIterations = m_pLexicon->GetIntParameter( "Boltzmann\\NumberOfSamples", 100 ); 	
	int			NumberOfPhones ( m_Phones_Tier1->GetSize() );
	int			MinimumWordLength = 2;
	double		TotalWeightedExponentiatedScore = 0;
	double		TotalWeightOfSpaceSampled = 0;
	CWordCollection TestWords;

	MonteCarlo		Dealer (NumberOfPhones);
	CStem			Word;
	CParse			prsWord;
	double			prob, score, 
					expoScore;
	
	m_pLexicon->GetDocument()->BeginCountDown();
	m_pLexicon->GetDocument()->setStatusBar1( "Computing Z:" );


	Dealer.m_ModelType		= BIGRAM;
	m_Phones_Tier1			->PopulateMonteCarlo ( &Dealer);	
	
	
	QFile outfile( "c:\\deleteMeLxa.txt" );
		outfile.open( QIODevice::WriteOnly );
		Q3TextStream outf( &outfile );	

	if (TRUE) {
		
		outf.setEncoding( Q3TextStream::Unicode );
		outf << "Word \t GibbsScore \t ExpoScore \t BigramProb \t UnigramLogProb \t T1 MI \t T2 MI";
	}

	for (int i = 1; i < NumberOfIterations; i++)
	{		
		m_pLexicon			->GetDocument()->CountDownOnStatusBar( i, NumberOfIterations, 0 );
		Dealer.				ReturnString(prsWord);
		if (prsWord.Size() <=  MinimumWordLength ) { continue; }

		QString temp		= prsWord.Display();		

		if (TestWords ^= temp  ) 
		{	
			i--;
			continue;
		}
		TestWords << temp ;

		Word				= prsWord;
		Word.				CreatePhonologyFromOrthography(NO_BOUNDARIES);
		Word.				SplitPhonologyToTiers( Split_LeaveCopy, *m_Vowels);
		Word.				ComputeProbabilities(this);
		score				= ( Word.GetBigramLogProb() - Word.GetTier2_LocalMI_Score() ); 		
		prob				= exp2 ( -1.0 * Word.GetBigramLogProb() ) ;
		//score2			= score * score/prob;
		expoScore			= exp2 ( -1.0 * score );

		QString temp3		= Word.Display();
		

		double Tier1MI = Word.GetUnigramLogProb() - Word.GetBigramLogProb();

		if (TRUE) {
			outf << endl << temp << "\t" <<
					score << "\t" << 
					expoScore << "\t" <<
					prob  << "\t" <<
					Word.GetUnigramLogProb() << "\t" <<
					Tier1MI << "\t" <<
					Word.GetTier2_LocalMI_Score () ;
		}

		TotalWeightedExponentiatedScore += expoScore;
		TotalWeightOfSpaceSampled		+= prob;

	

	}

	m_MyZ_Local = TotalWeightedExponentiatedScore/TotalWeightOfSpaceSampled; 

	if (TRUE) {
		outfile.close(); }


	return m_MyZ_Local;
	

	
}
double CWordCollection::ComputeZStar() // For "field" method on Tier 2
{

	int			NumberOfIterations = m_pLexicon->GetIntParameter( "Boltzmann\\NumberOfIterations", 10000 ); 	
	int			NumberOfPhones ( m_Phones_Tier1->GetSize() );
	int			MinimumWordLength = 2;
	double		TotalWeightedExponentiatedScore = 0;
	double		TotalWeightOfSpaceSampled = 0;


	MonteCarlo		Dealer (NumberOfPhones);
	CStem			Word;
	CParse			prsWord;
	double			prob,
					expoScore;
	
	m_pLexicon->GetDocument()->BeginCountDown();
	m_pLexicon->GetDocument()->setStatusBar1( "Computing Z*:" );



	Dealer.m_ModelType = BIGRAM;
	m_Phones_Tier1->PopulateMonteCarlo ( &Dealer);	

	for (int i = 1; i < NumberOfIterations; i++)
	{		
		m_pLexicon->GetDocument()->CountDownOnStatusBar( i, NumberOfIterations, 0 );
		Dealer.ReturnString(prsWord);
		if (prsWord.Size() <=  MinimumWordLength ) { continue; }

		Word = prsWord;
		Word.CreatePhonologyFromOrthography(NO_BOUNDARIES);
		Word.SplitPhonologyToTiers( Split_LeaveCopy, *m_Vowels);
		Word.ComputeProbabilities(this);
		prob		= exp2 ( -1 * Word.GetBigramLogProb() ) ;
		expoScore	= exp2 ( -1 * (Word.GetBigramLogProb() - Word.GetTier2_DistantMI_Score())  );

		TotalWeightedExponentiatedScore += expoScore;
		TotalWeightOfSpaceSampled		+= prob;
	}

	m_MyZ_Distant = TotalWeightedExponentiatedScore/TotalWeightOfSpaceSampled; 
	return m_MyZ_Distant;

	
}

//=====================================================================
void CWordCollection::GetPhonologyTierInfoForGraphOfWords( )
{
	int i;

	m_pMiniLex->GetLexicon()->GetDocument()->BeginCountDown();
	m_pMiniLex->GetLexicon()->GetDocument()->setStatusBar1( "Get Tier1 Info For Graphic Display...:" );

	for (i = 0; i<GetSize(); i++)
	{

		m_pMiniLex->GetLexicon()->GetDocument()->CountDownOnStatusBar( i, GetSize(), 0 );

		GetAt(i)->GetPhonogyTier1InfoForGraph(this);

	}
 
}
 



/////////////////////////////////////////////////////////////////
void CWordCollection::FindAllWordNeighbors( CLexicon* MyLexicon)
{ 

    int						NumberOfWords; 
 	int						MinimumSize			= 5;	
    double			        ScoreThreshold = MyLexicon->GetIntParameter( "Neighbors\\DifferenceThreshold", 2.5 ); 	
 
    int						MaximumNumberOfLetterDifferences = 9;
	int						MinimumNumberOfCommonLetters = 5;
    CParse                  Substitution;
    CStem*					pWord, 
							*qWord;
	CAlignment				*pAlignment; 
 	double					Score;
	QStringToTemplate	    Templates;
	int						Counter				= 1; 
	int						TotalNumber; 
  	NumberOfWords			= GetCount();  
	MyLexicon->GetDocument()->setStatusBar1(QString("StringEdit:FindAllEditDistances"));
    TotalNumber				= NumberOfWords - 1;
    bool                    MatchAlreadyFound;

	if ( MyLexicon->LogFileOn() && MyLexicon->GetLogFileStream() ) 
	{ 
 		*MyLexicon->GetLogFileStream()  <<		endl << 
				"<h3 class=blue>"												<<
					"Word neighbors"				<< 
				"</h3>"															<< endl << 
					StartTable<< 
					StartTableRow << 
					MakeTableHeader("String 1") << 
					MakeTableHeader("String 2") <<
					MakeTableHeader("Distance") << 
					EndTableRow;			

    }
    

 	for (int i = 0; i < NumberOfWords - 1; i++)
	{
		pWord =  GetAtSort(i);
		
		if (pWord->GetKeyLength() < MinimumSize ) continue;
        MatchAlreadyFound = FALSE;
		
		for (int j = i+1; j < NumberOfWords; j++)
		{
			qWord		= GetAtSort(j);
			
			if (qWord->GetKeyLength() < MinimumSize ) continue;

			// -------  Our tests to see if these two words, pWord and qWord, are similar enough ----- //
			// -------  to be worth testing with string edit distance                           ------ //
			int Overlap = OverlapOfTwoAlphabetizedLists ( pWord->GetAlphabetizedForm(), qWord->GetAlphabetizedForm() );
			if (Overlap < MinimumNumberOfCommonLetters ) continue;
	
			int Diff = DifferencesOfTwoAlphabetizedLists ( pWord->GetAlphabetizedForm(), qWord->GetAlphabetizedForm() );
			if ( Diff > MaximumNumberOfLetterDifferences ) continue;
			//	--------  end of tests  -----------------------------------------------------------   //

			pAlignment	= new CAlignment ( pWord, qWord );		 
			Score		= pAlignment->FindStringEditDistance();						
			if (  Score < ScoreThreshold  )
			{			 
  			    if ( MyLexicon->LogFileOn() ) 
                { 
                    if (MatchAlreadyFound == FALSE) 
                    {
				        *MyLexicon->GetLogFileStream()  << endl << 
				        StartTableRow <<
				        TableData (pWord )<<
				        TableData (qWord ) <<
 				        TableData(   Score );
                        if ( pAlignment->m_Slips == 1 )
                        {
                            Substitution = pAlignment->FindSubstitution();
                            *MyLexicon->GetLogFileStream() << 
                                TableData (Substitution.GetPiece(1)) <<
                                TableData (Substitution.GetPiece(2));
                        }
                        MatchAlreadyFound = TRUE;
                        *MyLexicon->GetLogFileStream() << EndTableRow;
                    }
                    else
                    {
				        *MyLexicon->GetLogFileStream()  << endl << 
				        StartTableRow <<
				        TableData ("" )<<
				        TableData (qWord );
                         *MyLexicon->GetLogFileStream() << TableData( Score );
                        if ( pAlignment->m_Slips == 1 )
                        {
                            Substitution = pAlignment->FindSubstitution();
                            *MyLexicon->GetLogFileStream() << 
                                TableData (Substitution.GetPiece(1)) <<
                                TableData (Substitution.GetPiece(2));
                        }
                        *MyLexicon->GetLogFileStream() << EndTableRow;
                    }
                }		
            }			
			delete pAlignment;
		}
		MyLexicon->GetDocument()->CountDownOnStatusBar(Counter++, TotalNumber/20*20, TotalNumber/20);
	}
}
