// Implementation of word list and stem list displays
// Copyright © 2009 The University of Chicago
#include "GUIclasses.h"
#include "Stem.h"

#include <Q3ListView>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Signature.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "CompareFunc.h"

//------------------------------------------------------------------//
//
//     Word collections
//
//------------------------------------------------------------------//

GUIWordCollection::GUIWordCollection (CMiniLexicon* pLexicon, CWordCollection* pWords)
{
    m_MiniLexicon = pLexicon;
    m_Words       = pWords;
    m_DisplayMode = MiniLexicon_MorphologyStuffFirst; 
}

void GUIWordCollection::ListDisplay (Q3ListView* pView, StringToString* filter,
					bool bAnalyzedWordsOnly)
{
  CStem*    pWord;
  int       MaxNumberOfStems = 0;
  int       n;

  pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);
  for (int i = 0; i < m_Words->GetCount(); ++i) {
    n = m_Words->GetAt(i)->GetNumberOfStems();
    if (n > MaxNumberOfStems )
    { MaxNumberOfStems = n; }
  }

  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  //    Add Column headers
  if (   m_DisplayMode == MiniLexicon_MorphologyStuffFirst )
  {

	  pView->addColumn( "Word");
	  pView->addColumn( "Mini" );
	  pView->hideColumn(1);  // Not needed in this view
	  pView->addColumn( "Descr. Length" );
	  pView->addColumn( "Corpus Count" );
	  pView->addColumn( "Type" );
	  pView->addColumn( "Signature" );
	  pView->addColumn( "Source" );
	  pView->addColumn( "Prefix" );
	  pView->addColumn( "Stem" );
	  pView->addColumn( "Suffix" );
	  pView->addColumn( "Log prob" );
	  pView->addColumn( "Av log prob");
	  pView->addColumn( "Log prob (cond.)");
	  pView->addColumn( "Av log prob (cond.)");
	  pView->addColumn( "Tier 1");
	  pView->addColumn( "Tier 1 template");
	  pView->addColumn( "Tier 2");
  }
  else 
  {
	  pView->addColumn( "Word" );
	  pView->addColumn( "Log prob (unigram)" );
	  pView->addColumn( "Av log prob (uni)");
	  pView->addColumn( "Log prob (bigram)");
	  pView->addColumn( "Av log prob (bi)");
	  pView->addColumn( "HMM log prob" );
	  pView->addColumn( "Tier 1");
	  pView->addColumn( "Tier 1 template");
	  pView->addColumn( "Tier 2");
	  pView->addColumn( "Mini" );
	  pView->hideColumn(8);  // Not needed in this view
	  pView->addColumn( "Descr. Length" );
	  pView->addColumn( "Corpus Count" );
	  pView->addColumn( "Type" );
	  pView->addColumn( "Signature" );
	  pView->addColumn( "Source" );
	  pView->addColumn( "Prefix" );
	  pView->addColumn( "Stem" );
	  pView->addColumn( "Suffix" );
  }

  if (m_Words->GetSortValidFlag() == FALSE)
  {
    m_Words->Sort(KEY);
  }

  m_MiniLexicon->GetLexicon()->GetDocument()->setStatusBar1( "Creating word list for display" );
  m_MiniLexicon->GetLexicon()->GetDocument()->BeginCountDown();

  for (int i = 0; i < m_Words->GetCount(); ++i) {
    pWord = m_Words->GetAtSort(i);

    if ( !bAnalyzedWordsOnly )
    {
      pWord->WordListDisplay( pView, filter, m_DisplayMode, m_MiniLexicon->GetLexicon()->GetNumberOfCharacterTypes() );
    }
    else
    if( bAnalyzedWordsOnly && pWord->Size() > 1 )
    {
      pWord->WordListDisplay( pView, filter, m_DisplayMode, m_MiniLexicon->GetLexicon()->GetNumberOfCharacterTypes() );
    }
    m_MiniLexicon->GetLexicon()->GetDocument()->CountDownOnStatusBar( i, m_Words->GetCount() );
  }
  m_MiniLexicon->GetLexicon()->GetDocument()->setStatusBar1( "" );
  m_MiniLexicon->GetLexicon()->GetDocument()->EndCountDown();   


};


//------------------------------------------------------------------//
//
//     Word items
//
//------------------------------------------------------------------//


//--------------------------------------------------
// Public accessor methods
//--------------------------------------------------

// TODO: integrate this with the Qt interface list items
// Display this word in a list of words in the triscreen
// interface
//
// Parameters:
//    List - the listitem to be displayed
//    position - the position in the list
//    SuffixColumn - TODO

void CStem::WordListDisplay(Q3ListView* List,
	QMap<QString, QString>* filter,
	enum eWordDisplayMode DisplayMode,
	int char_count)
{
	static_cast<void>(new CWordListViewItem(
		List, Display(QChar(), filter),
		this->GetMyMini()->GetIndex(), this,
		filter, DisplayMode, char_count));
}


CWordListViewItem::CWordListViewItem (Q3ListView *parent,
			QString word,
			int mini,
			CStem* pWord,
			StringToString* filter,
			eWordDisplayMode DisplayMode,
			int char_count)
: Q3ListViewItem( parent, word )
{
	m_pWord = pWord;
	m_filter = filter;
	m_DisplayMode = DisplayMode;
	m_char_count = char_count;
	m_mini = mini;

	if ( m_pWord )
	{
		m_DL = m_pWord->ComputeDL( m_char_count );
		m_prefix = m_pWord->GetPiece( m_pWord->GetPrefixLoc() )
						.Display( m_filter );
		m_stem = m_pWord->GetStem().Display( m_filter );
		m_suffix = m_pWord->GetPiece( m_pWord->GetSuffixLoc() )
						.Display( m_filter );
		m_pSig = m_pWord->GetSuffixSignature();

		if ( m_pSig == NULL )
			m_pSig = m_pWord->GetPrefixSignature();

		if ( m_pSig != NULL )
			m_signature = m_pSig->Display( '.', m_filter );
		else
			m_signature = "";

		m_tier1 = m_pWord->GetTier1()->Display( ' ' );
		m_tier1_skeleton = m_pWord->GetTier1_Skeleton()->Display();
		m_tier2 = m_pWord->GetTier2()->Display();
	}
	else
	{
		m_DL = 0.0;
		m_prefix = "";
		m_stem = "";
		m_suffix = "";
		m_pSig = NULL;
		m_signature = "";
		m_tier1 = "";
		m_tier1_skeleton = "";
		m_tier2 = "";
	}
}



CWordListViewItem::CWordListViewItem( Q3ListViewItem *parent,
                    QString word,
                    int mini,
                    CStem* pWord,
                    StringToString* filter ,
					eWordDisplayMode DisplayMode,
					int char_count)
: Q3ListViewItem( parent, word )
{
	m_pWord = pWord;
	m_filter = filter;
	m_DisplayMode = DisplayMode;
	m_char_count = char_count;
	m_mini = mini;
	if( m_pWord )
	{
		m_DL = m_pWord->ComputeDL( m_char_count );
		m_prefix = m_pWord->GetPiece( m_pWord->GetPrefixLoc() ).Display( m_filter );
		m_stem = m_pWord->GetStem().Display(m_filter);
		m_suffix = m_pWord->GetPiece( m_pWord->GetSuffixLoc() ).Display( m_filter );
		m_pSig = m_pWord->GetSuffixSignature();
		if( m_pSig == NULL ) m_pSig = m_pWord->GetPrefixSignature();
		if( m_pSig != NULL ) m_signature = m_pSig->Display( '.', m_filter );
		else m_signature = "";
		m_tier1 = m_pWord->GetTier1()->Display();
		m_tier1_skeleton = m_pWord->GetTier1_Skeleton()->Display();
		m_tier2 = m_pWord->GetTier2()->Display();
	}
	else
	{
		m_DL = 0.0;
		m_prefix = "";
		m_stem = "";
		m_suffix = "";
		m_pSig = NULL;
		m_signature = "";
		m_tier1 = "";
		m_tier1_skeleton = "";
		m_tier2 = "";
	}
}

int CWordListViewItem::compare(Q3ListViewItem* pOther, int col, bool asc) const
{
	if (m_pWord == 0)
		return Q3ListViewItem::compare(pOther, col, asc);
	CWordListViewItem& other = *static_cast<CWordListViewItem*>(pOther);
	CStem* other_word = other.m_pWord;

	if (m_DisplayMode == MiniLexicon_MorphologyStuffFirst) {
		switch (col) {
		case 2:
			return MakeComparable(m_DL, other.m_DL);
		case 3:
			return MakeComparable(m_pWord->GetCorpusCount(),
				other_word->GetCorpusCount());
		case 10:
			return MakeComparable(m_pWord->GetUnigramLogProb(),
				other_word->GetUnigramLogProb());
		case 11:
			return MakeComparable(m_pWord->GetUnigramComplexity(),
				other_word->GetUnigramComplexity());
		case 12:
			return MakeComparable(m_pWord->GetBigramLogProb(),
				other_word->GetBigramLogProb());
		case 13:
			return MakeComparable(m_pWord->GetBigramComplexity(),
				other_word->GetBigramComplexity());
		default:
			return Q3ListViewItem::compare(pOther, col, asc);
		}
	}

	// Phonology Stuff First
	switch (col) {
	case 1:
		return MakeComparable(m_pWord->GetUnigramLogProb(),
			other_word->GetUnigramLogProb());
	case 2:
		return MakeComparable(m_pWord->GetUnigramComplexity(),
			other_word->GetUnigramComplexity());
	case 3:
		return MakeComparable(m_pWord->GetBigramLogProb(),
			other_word->GetBigramLogProb());
	case 4:
		return MakeComparable(m_pWord->GetBigramComplexity(),
			other_word->GetBigramComplexity());
	case 5:
		return MakeComparable(m_pWord->GetHMM_LogProbability(),
			other_word->GetHMM_LogProbability());
	case 9:
		 return MakeComparable(m_mini, other.m_mini);
	case 10:
		 return MakeComparable(m_DL, other.m_DL);
	case 11:
		 return MakeComparable(m_pWord->GetCorpusCount(),
			other_word->GetCorpusCount());
	default:
		return Q3ListViewItem::compare(pOther, col, asc);
	}
}

QString CWordListViewItem::key( int column, bool ascending ) const
{
  if( m_pWord )
  {
	if ( m_DisplayMode == MiniLexicon_MorphologyStuffFirst )
	{
		switch( column )
		{
		case 1:
			return QString( "%1" ).arg( 100 * m_mini, 10 );
   
		case 4:
		  return m_pWord->DisplayStemType();
		case 5:
		  return m_signature;
		case 6:
		  if( m_pSig && m_pWord->GetConfidence() == "" )
		  {
			return m_pSig->GetRemark();
		  }
		  else
		  {
			return m_pWord->GetConfidence();
		  }
		case 7:
		  return m_suffix;
		case 8:
		  return m_stem;
		case 9:
		  return m_prefix;
 
		default:
		  return Q3ListViewItem::key( column, ascending );
		}
	}// end of switch for MorphologyStuffFirst --
	else // Phonology Stuff First
	{
		switch (column) {
		case 1:
			return QString("%1").arg(static_cast<int>(
				double(10000) * m_pWord->GetUnigramLogProb()),
				10);
		case 2:
			return QString("%1").arg(static_cast<int>(
				double(10000) * m_pWord->GetUnigramComplexity()),
				10);
		case 3:
			return QString("%1").arg(static_cast<int>(
				double(10000) * m_pWord->GetBigramLogProb()),
				10);
		case 4:
			return QString("%1").arg(static_cast<int>(
				double(10000) * m_pWord->GetBigramComplexity()),
				10);
		case 5:
			return QString("%1").arg(static_cast<int>(
				double(10000) * m_pWord->GetHMM_LogProbability()),
				10);
		case 6:	
 			return m_tier1;
		case 7:
			return m_tier1_skeleton;
		case 8:
			return m_tier2;
		case 9:
			return QString("%1").arg( 100 * m_mini, 10 );
		case 10:
			if (m_pWord == 0)
				return QString();
			return QString("%1").arg(static_cast<int>(
				double(1000) * m_DL), 10);
		case 11:
			return QString("%1").arg(m_pWord->GetCorpusCount(), 10);
		case 12:
		  return m_pWord->DisplayStemType();
		case 13:
		  return m_signature;
		case 14:
		  if( m_pSig && m_pWord->GetConfidence() == "")
		  {
			return m_pSig->GetRemark();
		  }
		  else
		  {
			return m_pWord->GetConfidence();
		  }
		case 15:
		  return m_prefix;
		case 16:
		  return m_stem;
		case 17:
		  return m_suffix;
	

		default:
		  return Q3ListViewItem::key( column, ascending );
		}
	}

  }
  else return Q3ListViewItem::key( column, ascending );
}

QString CWordListViewItem::text( int column ) const
{
  if(! m_pWord) return QString("");
  
   switch (m_DisplayMode)
   {
       case MiniLexicon_MorphologyStuffFirst:
       case Lexicon_Word:
          {
		    switch( column )
		    {
			    case 1:
			      return QString( "%1" ).arg( m_mini );
			    case 2:
			      return QString("%1").arg( m_DL );
			    case 3:
			      return QString("%1").arg( m_pWord->GetCorpusCount() );
			    case 4:
			      return m_pWord->DisplayStemType();
			    case 5:
			      return m_signature;
			    case 6:
			      if( m_pSig && m_pWord->GetConfidence() == "")
			      {
				    return m_pSig->GetRemark();
			      }
			      else
			      {
				    return m_pWord->GetConfidence();
			      }
			    case 7:
			      return m_prefix;
			    case 8:
			      return m_stem;
			    case 9:
			      return m_suffix;
			    case 10: 
				     return QString("%1").arg( m_pWord->GetUnigramLogProb() );
			    case 11:
 				    return QString("%1").arg( m_pWord->GetUnigramComplexity() );
			    case 12: 
				     return QString("%1").arg( m_pWord->GetBigramLogProb() );

			    case 13:
 				    return QString("%1").arg( m_pWord->GetBigramComplexity() );

			    case 14:	
 				    return m_tier1;
			    case 15:
				    return m_tier1_skeleton;
			    case 16:
				    return m_tier2;


			    default:
			      return Q3ListViewItem::text( column );
		    }
	        break;
        };
        case MiniLexicon_PhonologyStuffFirst:
	    {
		  switch( column )
			    {
			    case 1: 
				     return QString("%1").arg( m_pWord->GetUnigramLogProb() );
			    case 2:
 				    return QString("%1").arg( m_pWord->GetUnigramComplexity() );
			    case 3: 
				     return QString("%1").arg( m_pWord->GetBigramLogProb() );
			    case 4:
 				    return QString("%1").arg( m_pWord->GetBigramComplexity() );
			    case 5:	
 				    return QString("%1").arg( m_pWord->GetHMM_LogProbability() );
			    case 6:
				    return m_tier1;
			    case 7:
				    return m_tier1_skeleton;
			    case 8:
				    return m_tier2;
			    case 9:
				    return QString( "%1" ).arg( m_mini );
			    case 10:
			      if( m_pWord ) return QString("%1").arg( m_DL );
			      else return "";
			    case 11:
			      return QString("%1").arg( m_pWord->GetCorpusCount() );
			    case 12:
			      return m_pWord->DisplayStemType();
			    case 13:
			      return m_signature;
			    case 14:
			      if( m_pSig && m_pWord->GetConfidence() == "")
			      {
				    return m_pSig->GetRemark();
			      }
			      else
			      {
				    return m_pWord->GetConfidence();
			      }
			    case 15:
			      return m_prefix;
			    case 16:
			      return m_stem;
			    case 17:
			      return m_suffix;
			     
			    default:
			      return Q3ListViewItem::text( column );

		    }// end of switch on column...
	    }// end of MiniLexicon_Phonology stuff first
      } //end of DisplayMode switch
   
      return Q3ListViewItem::text( column );
}


//------------------------------------------------------------------//
//
//     Stem collection
//
//------------------------------------------------------------------//


void CStemCollection::ListDisplay(Q3ListView* pView, StringToString* filter)
{
  CStem*      pStem;

	pView->setRootIsDecorated( FALSE );

  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );
  pView->setSorting(1);
  //  Add Column headers
  pView->addColumn( "Stem" );
//  pView->addColumn( "Source" );
//  pView->hideColumn(1);  // Not necessary with this view
  pView->addColumn( "Phonological content");
  pView->addColumn( "Length ptr to me"	);
  pView->addColumn( "Corpus count"		);
  pView->addColumn( "Suffix sig"		);
  pView->addColumn( "Prefix sig"		);
  pView->addColumn( "Origin"			);
  pView->addColumn( "Type"				);
 
  if (m_SortValidFlag == FALSE)
  {
    Sort(KEY);
  }

  m_pLexicon->GetDocument()->setStatusBar1( "Creating stem list for display" );
  m_pLexicon->GetDocument()->BeginCountDown();

  // Display all items
  for (int i = 0; i < GetCount(); ++i) {
		pStem = GetAtSort(i);
		pStem->StemListDisplay( pView, filter, m_pLexicon->GetNumberOfCharacterTypes() );
		m_pLexicon->GetDocument()->CountDownOnStatusBar(i, GetCount());
  }

  m_pLexicon->GetDocument()->setStatusBar1( "" );
  m_pLexicon->GetDocument()->EndCountDown();
}

// Display this stem in a list on Triscreen
//
// Parameters:
//    List - the list it will be added to
//    position - the position in the list

void CStem::StemListDisplay(Q3ListView* List,
	QMap<QString, QString>* filter, int char_count)
{
	static_cast<void>(new CStemListViewItem(
		List, Display(QChar(), filter),
		this->GetMyMini()->GetIndex(),
		this, filter, char_count));
}

CStemListViewItem::CStemListViewItem( Q3ListView *parent, 
                    QString stem,
                    int mini,
                    CStem* pStem,
                    StringToString* filter,
					int char_count )
: Q3ListViewItem( parent, stem )
{
  m_Stem = pStem;
  m_filter = filter;
  m_char_count = char_count;
  m_mini = mini;
}


CStemListViewItem::CStemListViewItem( Q3ListViewItem *parent,
                    QString stem,
                    int mini,
                    CStem* pStem,
                    StringToString* filter,
					int char_count )
: Q3ListViewItem( parent, stem )
{
  m_Stem = pStem;
  m_filter = filter;
  m_char_count = char_count;
  m_mini = mini;
}
int CStemListViewItem::compare(Q3ListViewItem* pOther, int col, bool asc) const
{
	CStemListViewItem* other = static_cast<CStemListViewItem*>(pOther);
 
		switch( col )
		{
		case 1:
                  if( m_Stem ) return MakeComparable (m_Stem->GetPhonologicalInformationContent(), other->m_Stem->GetPhonologicalInformationContent());
		case 2:
                  if( m_Stem ) return MakeComparable (m_Stem->GetLengthOfPointerToMe(), other->GetStem()->GetLengthOfPointerToMe());
		case 3:
                  if( m_Stem ) return MakeComparable (m_Stem->GetCorpusCount(), other->GetStem()->GetCorpusCount());
		case 8:
                  if( m_Stem ) return MakeComparable (m_Stem->GetUnigramLogProb(), other->GetStem()->GetUnigramLogProb());
 		default:
		  return Q3ListViewItem::compare(pOther, col, asc);
		}		 
 
}
QString CStemListViewItem::key( int column, bool ascending ) const
{
  CSignature* sigs;
  int count;

  switch( column )
  {
 
  case 3:
    if( m_Stem )
    {
      return QString("%1").arg( m_Stem->GetCorpusCount(), 10 );
    }
    else
    {
      count = 0;

		for (CStemListViewItem* child =
					static_cast<CStemListViewItem*>(
					firstChild());
				child != 0;
				child = static_cast<CStemListViewItem*>(
					child->nextSibling()))
			if (CStem* stem = child->GetStem())
				count += stem->GetCorpusCount();

      return QString("%1").arg( count, 10 );
    }

  case 4:
    if( m_Stem )
    {
       sigs = m_Stem->GetSuffixSignature();
      if( sigs ) 
	  {
		  return sigs->Display('.', m_filter);
	  }
      else return "";
    }
    else return "";
  case 5:
    if( m_Stem )
    {
      sigs = m_Stem->GetPrefixSignature();
      if( sigs ) return sigs->Display('.', m_filter);
      else return "";
    }
    else return "";
  case 6:
    if( m_Stem ) return m_Stem->GetConfidence();
    else return "";
  case 7:
    if( m_Stem ) return m_Stem->DisplayStemType();
    else return "";
   case 9:	
	return m_Stem->GetTier1()->Display();
  case 10:
	return m_Stem->GetTier1_Skeleton()->Display();
  case 11:
	return m_Stem->GetTier2()->Display();

 
  default:	  
    return Q3ListViewItem::key( column, ascending );
  }
}

QString CStemListViewItem::text( int column ) const
{
//  CParse*    pfxs;
  CSignature* sigs;

  int count;

  switch( column )
  {
//  case 1:
//	  return QString( "%1" ).arg( m_mini );
  case 1:
    if( m_Stem ) return QString("%1").arg( m_Stem->ComputeDL( m_char_count ) );
    else return "";
  case 2:
    if( m_Stem ) return QString("%1").arg( m_Stem->GetLengthOfPointerToMe( ) );
    else return "";
  
  
  case 3:
    if( m_Stem )
    {
      return QString("%1").arg( m_Stem->GetCorpusCount() );
    }
    else
    {
      count = 0;

		for (CStemListViewItem* child =
					static_cast<CStemListViewItem*>(
					firstChild());
				child != 0;
				child = static_cast<CStemListViewItem*>(
					child->nextSibling()))
			if (CStem* stem = child->GetStem())
				count += stem->GetCorpusCount();

      return QString("%1").arg( count );
    }
/*
  case 3:
    if( m_Stem )
    {
      pfxs = m_Stem->GetPrefixList();
      if( pfxs->GetKeyLength() )
        return pfxs->Display('-', m_filter);
      else return "";
    }
 
    else return "";
*/
   

  case 4:
 
    if( m_Stem )
    {
//		qDebug( m_Stem->Display() );
      sigs = m_Stem->GetSuffixSignature();
      if( sigs ) 
	  {
//		qDebug( ((CParse*)sigs)->Display('.') );
		  return sigs->Display('.', m_filter);
	  }
      else return "";
    }
    else return "";
  case 5:
    if( m_Stem )
    {
      sigs = m_Stem->GetPrefixSignature();
      if( sigs ) return sigs->Display('.', m_filter);
      else return "";
    }
    else return "";
  case 6:
    if( m_Stem ) return m_Stem->GetConfidence();
    else return "";
  case 7:
    if( m_Stem ) return m_Stem->DisplayStemType();
    else return "";
  case 8:
	return QString("%1").arg ( m_Stem->GetUnigramLogProb() );
  case 9:	
	return m_Stem->GetTier1()->Display();
  case 10:
	return m_Stem->GetTier1_Skeleton()->Display();
  case 11:
	return m_Stem->GetTier2()->Display();
  case 12:
    return QString("just placeholdin'");
	  //return m_Stem->GetPhonologicalInformationContent();
 default:
    return Q3ListViewItem::text( column );
  }
}
