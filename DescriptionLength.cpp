// Description length calculations, CDescriptionLength methods
// Copyright © 2009 The University of Chicago
#include "DescriptionLength.h"
#include "MiniLexicon.h"

#include "Lexicon.h"
#include "Signature.h"
#include "Suffix.h"
#include "Compound.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "SuffixCollection.h"
#include "StemCollection.h"
#include "StringFunc.h"
#include "log2.h"

// The CDLHistory class is the main user for these functions.

//-----------------------------------------------------------------
//           Mini Lexicon function
//-----------------------------------------------------------------


double CMiniLexicon::CalculateDescriptionLength()
{
	if (m_DescriptionLength) delete m_DescriptionLength;
	m_DescriptionLength = new CDescriptionLength (this);
	m_DescriptionLength->GetStemsTotalPhonologicalInformationContent    ( );
	m_DescriptionLength->GetSuffixesTotalPhonologicalInformationContent ( ); // Should be affixes, deal with prefixes case

	return 0;
}

 
//-----------------------------------------------------------------
// Constructors/Destructor
//-----------------------------------------------------------------

CDescriptionLength::CDescriptionLength( CMiniLexicon* mini)
{
	m_MyMiniLexicon        = mini;
	m_MyLexicon            = mini->GetLexicon();
	m_TotalDL              = 0;
	m_MDLStyle             = CorpusCount;
	
	// Stems
	m_NumberOfStems 										= mini->GetStems()->GetCount();
	m_StemsTotalPhonologicalInformationContent             = 0;
	m_SumOfPointersToMyStems_CorpusCount                   = 0;
	m_SumOfPointersToMyStems_GrammarCount                  = 0;

	m_NumberOfAnalyzedWords									= mini->GetNumberOfAnalyzedWords(m_NumberOfUnanalyzedWords);

	// Unanalyzed words
 	m_UnanalyzedWordsTotalPhonologicalInformationContent   = 0;
	m_SumOfPointersToMyUnanalyzedWords_CorpusCount         = 0;
	m_SumOfPointersToMyUnanalyzedWords_GrammarCount        = 0;

	
	// Suffixes
	m_SuffixesTotalPhonologicalInformationContent          = 0;
	m_SumOfPointersToMySuffixes_CorpusCount                = 0;
	m_SumOfPointersToMySuffixes_GrammarCount               = 0;

	// Suffix signatures
	m_SumOfInformationContentOfPointersInMySuffixSignatures	= 0;
 	m_SumOfPointersToMySuffixSignatures_CorpusCount		= 0;
	m_SumOfPointersToMySuffixSignatures_GrammarCount	= 0;

	// Corpus
	m_CompressedLengthOfCorpus                              = 0;

	 
}

CDescriptionLength::CDescriptionLength( CLexicon* lex)
{
	m_MyMiniLexicon = NULL;
	m_MyLexicon                                             = lex;
	m_TotalDL                                               = 0;
	m_MDLStyle                                              = CorpusCount;
	
	// Stems
	m_NumberOfStems											= lex->GetAllStems()->count();
	m_StemsTotalPhonologicalInformationContent				= 0;
	m_SumOfPointersToMyStems_CorpusCount					= 0;
	m_SumOfPointersToMyStems_GrammarCount					= 0;

	// Unanalyzed words
	m_NumberOfUnanalyzedWords 								= 0;
	m_UnanalyzedWordsTotalPhonologicalInformationContent	= 0;
	m_SumOfPointersToMyUnanalyzedWords_CorpusCount			= 0;
	m_SumOfPointersToMyUnanalyzedWords_GrammarCount			= 0;

	m_NumberOfAnalyzedWords									= 0;

	// Suffixes
	m_SuffixesTotalPhonologicalInformationContent			= 0;
	m_SumOfPointersToMySuffixes_CorpusCount				= 0;
	m_SumOfPointersToMySuffixes_GrammarCount			= 0;

	// Suffix signatures
	m_SumOfInformationContentOfPointersInMySuffixSignatures	= 0;
 	m_SumOfPointersToMySuffixSignatures_CorpusCount		= 0;
	m_SumOfPointersToMySuffixSignatures_GrammarCount	= 0;

	// Corpus
	m_CompressedLengthOfCorpus							= 0;

	 
} 

CDescriptionLength::~CDescriptionLength()
{

}
//-----------------------------------------------------------------
//           DescriptionLength ListViewItem
//-----------------------------------------------------------------


CDescriptionLengthListViewItem::CDescriptionLengthListViewItem( Q3ListView *parent )
: Q3ListViewItem( parent )
{}

//   DL f2
CDescriptionLengthListViewItem::CDescriptionLengthListViewItem( Q3ListView *parent, 
												eDocumentType type,
												QString label,
												CDescriptionLength* pDL,
												int index )
: Q3ListViewItem( parent, label )
{
	m_DL = pDL;
	m_index = index;
	m_SpellOutType = type;
//	m_label = label;
}

 
//   DL f3
CDescriptionLengthListViewItem::CDescriptionLengthListViewItem( Q3ListViewItem *parent, 
												eDocumentType  type,									
												QString mini_name,
												CDescriptionLength* pDL,
												int index )
: Q3ListViewItem( parent, mini_name )
{
	m_DL	= pDL;
	m_index = index;
	m_SpellOutType = type;

}
//   DL f5
QString CDescriptionLengthListViewItem::SpellOutType() const
{
	switch (m_SpellOutType)
	{
	case STEMS:
		return QString ("Stems"); break;
	case SUFFIXES:
		return QString ("Suffixes"); break;
	case SUFFIX_SIGNATURES:
		return QString ("Suffix signatures"); break;
	case CORPUS_DOC: 
		return QString ("Corpus"); break;
	case UNANALYZED_WORDS: 
		return QString ("Unanalyzed words"); break;
	default:
		return QString (""); 
	}
}
//   DL f6
QString    CDescriptionLengthListViewItem::GetSubstance() const
{
	switch (m_SpellOutType)
	{
		case STEMS:
			return DblToStringWithCommas( m_DL->GetStemsTotalPhonologicalInformationContent( ) );
			break;
		case UNANALYZED_WORDS:
			return DblToStringWithCommas( m_DL->GetUnanalyzedWordsTotalPhonologicalInformationContent( ) );
			break;
		case SUFFIXES:
			return DblToStringWithCommas( m_DL->GetSuffixesTotalPhonologicalInformationContent( ) );
			break;
		case SUFFIX_SIGNATURES:
			return QString ("0.0"); break;
		default:
			return QString (""); 
	}
	
}
//   DL f7
QString    CDescriptionLengthListViewItem::GetLengthOfInternalPointers() const
{
	switch (m_SpellOutType)
	{
		case STEMS:
  		case SUFFIXES:
		case UNANALYZED_WORDS:
			return DblToStringWithCommas( 0.0 );
			break;
		case SUFFIX_SIGNATURES:
			return DblToStringWithCommas( m_DL->GetSumOfInformationContentOfPointersInMySuffixSignatures()  );; break;
		case CORPUS_DOC:
			return DblToStringWithCommas(m_DL-> CalculateCompressedLengthOfCorpus() );

		default:
			return QString (""); 
	}
	
}
//   DL f8
QString	CDescriptionLengthListViewItem::GetLengthOfPointersToMe ()  const
{
	switch (m_SpellOutType)
	{
		case STEMS:
			return DblToStringWithCommas(m_DL->GetSumOfPointersToMyStems  ( ) );
			break;
		case UNANALYZED_WORDS:
			return DblToStringWithCommas(m_DL->GetSumOfPointersToMyUnanalyzedWords ( ) );
			break;
		case SUFFIXES:
			return DblToStringWithCommas(m_DL-> GetSumOfPointersToMySuffixes ( ) );
			break;
		case SUFFIX_SIGNATURES:
			return  DblToStringWithCommas(m_DL-> GetSumOfPointersToMySuffixSignatures ( ) ); break;
		default:
			return QString (""); 
	}




}
//   DL f4.1
QString CDescriptionLengthListViewItem::key(int column, bool) const
{	switch(	column )
	{
	case 0:
		return SpellOutType();
	case 1:
		return GetSubstance(); 
//	case 2:
//		return m_dlhistory->getRemark( m_index );
//	case 3:
//		total_dl += m_dlhistory->getStemDL(m_index);
//		total_dl += m_dlhistory->getAffixDL(m_index);
//		total_dl += m_dlhistory->getSigDL(m_index);
//
//		return QString("%1").arg( (int)(1000 * total_dl), 10 );
//	case 4:
//		return QString("%1").arg( (int)(1000 * m_dlhistory->getUnanalyzedStemDL(m_index)), 10 );
//	case 5:
//		return QString("%1").arg( (int)(1000 * m_dlhistory->getAnalyzedStemDL(m_index)), 10 );
//	case 6:
//		return QString("%1").arg( (int)(1000 * m_dlhistory->getStemDL(m_index)), 10 );
//	case 7:
//		return QString("%1").arg( (int)(1000 * m_dlhistory->getAffixDL(m_index)), 10 );
//	case 8:
//		return QString("%1").arg( (int)(1000 * m_dlhistory->getSigDL(m_index)), 10 );
	default:
		return QString ("x");
//		return QListViewItem::key( column, ascending );
	}
}
//   DL f4.2
QString CDescriptionLengthListViewItem::text( int column ) const
{
//	double total_dl = 0.0;  LK 7.18.08: unused varible

	switch(	column )
	{
	case 0:
		return SpellOutType();
	case 1:
		return  GetSubstance()  ; 
	case 2:
		return GetLengthOfInternalPointers();
//	case 3:
  	case 4:
		return   GetLengthOfPointersToMe()  ;
//	case 5:
//		return DblToStringWithCommas( m_dlhistory->getAnalyzedStemDL(m_index) );
//	case 6:
//		return DblToStringWithCommas( m_dlhistory->getStemDL(m_index) );
//	case 7:
//		return DblToStringWithCommas( m_dlhistory->getAffixDL(m_index) );
//	case 8:
//		return DblToStringWithCommas( m_dlhistory->getSigDL(m_index) );
	default:
		return QString (" ");		
//		return QListViewItem::text( column );
	}
}



 

//-----------------------------------------------------------------
//           DescriptionLength ListDisplay
//-----------------------------------------------------------------

//   DL f1
void CDescriptionLength::DescriptionLengthListDisplay( Q3ListView* list )
{
	// Remove all previous columns
	while( list->columns() ) list->removeColumn( 0 );

	// Add Column headers
	list->addColumn( "Component" );
	list->addColumn( "Phonological content" );
	list->addColumn( "Internal pointers" );
	list->addColumn( "External pointers" );
	list->addColumn( "Pointers to me" );
	list->addColumn( "Unanalyzed words");
	list->addColumn( "Stems");
	
	list->setColumnAlignment( 3, Qt::AlignRight );
//	list->addColumn( "Unanalyzed stems DL" );
	list->setColumnAlignment( 4, Qt::AlignRight );
//	list->addColumn( "Analyzed stems DL" );
	list->setColumnAlignment( 5, Qt::AlignRight );
//	list->addColumn( "All stems DL" );
	list->setColumnAlignment( 6, Qt::AlignRight );
//	list->addColumn( "Affixes DL" );
	list->setColumnAlignment( 7, Qt::AlignRight );
//	list->addColumn( "Signatures DL" );
	list->setColumnAlignment( 8, Qt::AlignRight );

//	list->setSorting (-1); //don't sort

//	if( m_MyLexicon )
//	{
//		m_MyLexicon->GetDocument()->setStatusBar1( "Creating description length list for display" );
//		m_MyLexicon->GetDocument()->BeginCountDown();
//	}

	 

//	if( m_MyLexicon )
//	{
//		m_MyLexicon->GetDocument()->setStatusBar1( "" );
//		m_MyLexicon->GetDocument()->EndCountDown();
//	}
///	CDescriptionLengthListViewItem* item = new CDescriptionLengthListViewItem( list, 
///																   " A ", "B", "C"),
///																   this, 0);


 


	 int LineNumber = 0;
	(void) new CDescriptionLengthListViewItem ( list, CORPUS_DOC, QString ("Corpus"), this, ++LineNumber );
	(void) new CDescriptionLengthListViewItem ( list, SUFFIX_SIGNATURES, QString ("Suffix signatures"), this, ++LineNumber );
 	(void) new CDescriptionLengthListViewItem ( list, SUFFIXES, QString ("Suffixes"), this, ++LineNumber );
	(void) new CDescriptionLengthListViewItem ( list, STEMS, QString ("Stems"), this, ++LineNumber );
	(void) new CDescriptionLengthListViewItem ( list, UNANALYZED_WORDS, QString ("UnanalyzedWords"), this, ++LineNumber );



//	list->setSorting (1); //go back to sorting


//	CDescriptionLengthListViewItem* item = new CDescriptionLengthListViewItem( list, 
//																   QString("Stems"),
//																   this, 0);
	

}
//-----------------------------------------------------------------
//           Phonological content
//-----------------------------------------------------------------

double CDescriptionLength::GetStemsTotalPhonologicalInformationContent	(   )
{

 	if (  m_StemsTotalPhonologicalInformationContent > 0)
	{
		return m_StemsTotalPhonologicalInformationContent;
	}

	if (m_MyMiniLexicon)
	{
		m_StemsTotalPhonologicalInformationContent = m_MyMiniLexicon->GetStems()->CalculateTotalPhonologicalInformationContent(m_MyLexicon);
	}
	else if (m_MyLexicon)
	{
		m_StemsTotalPhonologicalInformationContent = m_MyLexicon->CalculateTotalPhonologicalInformationContentOfStems();
	}

	return m_StemsTotalPhonologicalInformationContent; 

}

double CLexicon::CalculateTotalPhonologicalInformationContentOfStems()
{
	double total = 0.0;
	for (Q3DictIterator<StemSet> iter(m_AllStems);
			iter.current() != 0; ++iter) {
		StemSet& stems = *iter.current();

		foreach (CStem* pStem, stems)
			total += pStem->GetPhonologicalInformationContent(this);
	}
	return total;
}


double CDescriptionLength::GetUnanalyzedWordsTotalPhonologicalInformationContent	(   )
//double CDescriptionLength::GetUnanalyzedWordsTotalPhonologicalContent	(   eMDL_STYLE  CorpusCount) LK 7.18.08: unused parameter 'CorpusCount'
{
  	if (  m_UnanalyzedWordsTotalPhonologicalInformationContent > 0)
	{
		return m_UnanalyzedWordsTotalPhonologicalInformationContent;
	}

	if (m_MyMiniLexicon)
	{
		m_UnanalyzedWordsTotalPhonologicalInformationContent = m_MyMiniLexicon-> CalculateUnanalyzedWordsTotalPhonologicalInformationContent();
	}
	else if (m_MyLexicon)
	{
		m_StemsTotalPhonologicalInformationContent = m_MyLexicon->CalculateUnanalyzedWordsTotalPhonologicalInformationContent();
	}
	return m_UnanalyzedWordsTotalPhonologicalInformationContent; 

}

double	CLexicon::CalculateUnanalyzedWordsTotalPhonologicalInformationContent()
{
	double total = 0;
	CStem*			pWord;

	Q3DictIterator<StemSet> it( m_AllWords );
    for( ; it.current(); ++it )
	{
                //for( pWord = it.current()->first(); pWord; pWord = it.current()->next() )
                for (int z = 0; z < it.current()->size(); z++)
                {       pWord = it.current()->at(z);
			total += pWord->CalculatePhonologicalInformationContent( this);
		}
	}
	return total;
}

double CDescriptionLength::GetSuffixesTotalPhonologicalInformationContent	(   )
{
	int i;
	CSuffix*	pSuffix;
	if ( m_SuffixesTotalPhonologicalInformationContent > 0)
	{
		return m_SuffixesTotalPhonologicalInformationContent;
	}

	if (m_MyMiniLexicon)
	{
		m_SuffixesTotalPhonologicalInformationContent = 0; 
		CSuffixCollection& suffixes = *m_MyMiniLexicon->GetSuffixes();
		for (i = 0; i < suffixes.GetCount(); ++i) {
			pSuffix = suffixes.GetAt(i);

			m_SuffixesTotalPhonologicalInformationContent +=
				pSuffix->GetPhonologicalInformationContent();
		}
	}
	else if (m_MyLexicon)
	{
		m_SuffixesTotalPhonologicalInformationContent = 0;
		m_SuffixesTotalPhonologicalInformationContent = m_MyLexicon->GetPhonologicalInformationContentOfSuffixes(  );
	}

	return m_SuffixesTotalPhonologicalInformationContent; 

}

double CLexicon::GetPhonologicalInformationContentOfSuffixes( ) //double check this. This is not used for MiniLexicons -- only for full CLexicon.
{
	double total = 0.0;
	for (Q3DictIterator<SuffixSet> iter(m_AllSuffixes);
				iter.current() != 0; ++iter) {
		SuffixSet& suffixes = *iter.current();

		foreach (CSuffix* pSuffix, suffixes)
			total += pSuffix->GetPhonologicalInformationContent();
	}
	return total;
}

//-----------------------------------------------------------------
//						Pointer information:	Stems
//-----------------------------------------------------------------

double CDescriptionLength::GetSumOfPointersToMyStems( eMDL_STYLE MDLStyle )
{
	double	result;

	switch ( MDLStyle )
	{
	case CorpusCount:
		if ( m_SumOfPointersToMyStems_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->GetStems()->CalculateSumOfPointersToMyStems (CorpusCount);		
			m_SumOfPointersToMyStems_CorpusCount = result;
		}
		else
		{
			return m_SumOfPointersToMyStems_CorpusCount;
		}
		break;
	case GrammarCount:
		if ( m_SumOfPointersToMyStems_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->GetStems()->CalculateSumOfPointersToMyStems (GrammarCount);		
			m_SumOfPointersToMyStems_GrammarCount = result;
		}
		else
		{
			return m_SumOfPointersToMyStems_GrammarCount;
		}
		break;
	default:
		return 0;

	}
	return 0;
}

double CDescriptionLength::GetSumOfPointersToMyUnanalyzedWords( eMDL_STYLE MDLStyle )
{
	double	result;

	switch ( MDLStyle )
	{
	case CorpusCount:
		if ( m_SumOfPointersToMyUnanalyzedWords_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->CalculateSumOfPointersToMyUnanalyzedWords (CorpusCount);		
			m_SumOfPointersToMyUnanalyzedWords_CorpusCount = result;
		}
		else
		{
			return m_SumOfPointersToMyUnanalyzedWords_CorpusCount;
		}
		break;
	case GrammarCount:
		if ( m_SumOfPointersToMyUnanalyzedWords_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->CalculateSumOfPointersToMyUnanalyzedWords(GrammarCount);		
			m_SumOfPointersToMyUnanalyzedWords_GrammarCount = result;
		}
		else
		{
			return m_SumOfPointersToMyUnanalyzedWords_GrammarCount;
		}
		break;
	default:
		return 0;

	}
	return 0;
}
 

//-----------------------------------------------------------------
//					Pointer information:	Suffixes
//-----------------------------------------------------------------

double CDescriptionLength::GetSumOfPointersToMySuffixes( eMDL_STYLE MDLStyle )
{
	double	result;

	switch ( MDLStyle )
	{
	case CorpusCount:
		if ( m_SumOfPointersToMySuffixes_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->GetSuffixes()->CalculatePointersToMySuffixes (CorpusCount);		
			m_SumOfPointersToMySuffixes_CorpusCount = result;
		}		 
		return m_SumOfPointersToMySuffixes_CorpusCount;
		break;
	case GrammarCount:
		if ( m_SumOfPointersToMySuffixes_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->GetSuffixes()->CalculatePointersToMySuffixes (GrammarCount);		
			m_SumOfPointersToMySuffixes_GrammarCount = result;
		}
		else
		{
			return m_SumOfPointersToMySuffixes_GrammarCount;
		}
		break;
	default:
		return 0;

	}
	return 0;
}

 
//-----------------------------------------------------------------
//					Pointer information:	Suffix Signatures
//-----------------------------------------------------------------
//double CDescriptionLength::GetSumOfInformationContentOfPointersInMySuffixSignatures	( ) unused parameter 'RecomputeFlag
double CDescriptionLength::GetSumOfInformationContentOfPointersInMySuffixSignatures	( )

{	
	m_SumOfInformationContentOfPointersInMySuffixSignatures = 
		m_MyMiniLexicon->GetSignatures()->ComputeDLofInternalPointersOfEachMember( GrammarCount );

	return m_SumOfInformationContentOfPointersInMySuffixSignatures;
}

double CDescriptionLength::GetSumOfPointersToMySuffixSignatures( eMDL_STYLE MDLStyle )
{
	double	result = 0;

	switch ( MDLStyle )
	{
	case CorpusCount:
		if ( m_SumOfPointersToMySuffixSignatures_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->GetSignatures()->ComputeLengthOfPointersToEachOfMyMembers (CorpusCount);		
			m_SumOfPointersToMySuffixSignatures_CorpusCount = result;
		}
		 
		return m_SumOfPointersToMySuffixSignatures_CorpusCount;
		
		break;
	case GrammarCount:
		if ( m_SumOfPointersToMySuffixSignatures_CorpusCount == 0  )
		{
			result = m_MyMiniLexicon->GetSignatures()->ComputeLengthOfPointersToEachOfMyMembers(GrammarCount);		
			m_SumOfPointersToMySuffixSignatures_GrammarCount = result;
		}
		else
		{
			return m_SumOfPointersToMySuffixSignatures_GrammarCount;
		}
		break;
	default:
		return 0;

	}
	return 0;
}




 
//-----------------------------------------------------------------
//					Corpus 
//-----------------------------------------------------------------
double	CDescriptionLength::CalculateCompressedLengthOfCorpus()
{
	int i;
	CSignature	*		pSig;
	m_CompressedLengthOfCorpus = 0;

	for (i= 0; i < m_MyMiniLexicon->GetSignatures()->GetCount(); i++)
	{
		pSig = m_MyMiniLexicon->GetSignatures()->GetAt(i);
		m_CompressedLengthOfCorpus += pSig->ComputeDLofMyCorpus();
	}

	m_CompressedLengthOfCorpus += m_MyMiniLexicon->CalculateCompressedLengthOfUnanalyzedWords(  );

	return m_CompressedLengthOfCorpus ;

};


 	double	CalculateTotalPhonologicalContentOfStems();
	double	CalculateUnanalyzedWordsTotalPhonologicalContent();
	double	GetPhonologicalInformationContentOfSuffixes( );


//////////////////////////////////////////////////////////////////////////////
///
///								Description Length of Stem Collection
///
//////////////////////////////////////////////////////////////////////////////
 
double CStemCollection::CalculateTotalPhonologicalInformationContent(CLexicon* MotherLexicon)
{
 	double StemsTotalPhonologicalContent = 0; 
	CStem*	pStem;
	
	for (int i = 0; i < m_pMiniLex->GetStems()->GetCount(); ++i) {
		pStem = m_pMiniLex->GetStems()->GetAt(i);
		StemsTotalPhonologicalContent += pStem->CalculatePhonologicalInformationContent( MotherLexicon );
	}
	return StemsTotalPhonologicalContent;
}
double	CStemCollection::CalculateSumOfPointersToMyStems ( eMDL_STYLE style)
{
	int i;
	double	TotalLength = 0,
			length = 0,
			denominator = 0;
	switch (style)
	{
	case CorpusCount:
		for (i = 0; i < GetCount();i++)
		{
			denominator += GetAt(i)->GetCorpusCount();
		}
		//////////////
		denominator += GetMiniLexicon()->GetCorpusCountOfUnanalyzedWords();
		/////////////
		for (i = 0; i < GetCount();i++)
		{
			length = base2log ( denominator / GetAt(i)->GetCorpusCount() ) ;
			GetAt(i)->SetLengthOfPointerToMe ( length );
			TotalLength += length;
		}
		break;


	case GrammarCount:
		for (i = 0; i < GetCount();i++)
		{
			denominator += GetAt(i)->GetNumberOfSuffixes();
		}
		int NumberOfUnanalyzedWords;
		GetMiniLexicon()->GetNumberOfAnalyzedWords ( NumberOfUnanalyzedWords);
		//////////////
		denominator += NumberOfUnanalyzedWords;
		/////////////
		
		for (i = 0; i < GetCount();i++)
		{
			length = base2log ( denominator / GetAt(i)->GetNumberOfSuffixes() );
			GetAt(i)->SetLengthOfPointerToMe ( length );
			TotalLength += length;
		}
		break;
	}



	return TotalLength;

}

