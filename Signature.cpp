// Implementation of CSignature, CSignatureListViewItem methods
// Copyright © 2009 The University of Chicago
#include "Signature.h"

#include <QTextStream>
#include <QList>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "LPreferences.h"
#include "CorpusWord.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "SparseIntVector.h"
#include "CompareFunc.h"
#include "HTML.h"
#include "log2.h"
#include "Typedefs.h"
#include "implicit_cast.h"

CSignatureListViewItem::CSignatureListViewItem( Q3ListView *parent, 
                    QString signature,
                    int mini,
                    CSignature* pSig,
                    StringToString* filter )
: Q3ListViewItem
( parent, signature )
{
  m_signature    = pSig;
  m_filter    = filter;
  m_label      = signature;
  m_parentlist  = parent;
  m_mini = mini;
}


CSignatureListViewItem::CSignatureListViewItem( Q3ListViewItem *parent,
                    QString signature,
                    int mini,
                    CSignature* pSig,
                    StringToString* filter )
: Q3ListViewItem( parent, signature )
{
  m_signature    = pSig;
  m_filter    = filter;
  m_label      = signature;
  m_parentlist  = parent->listView();
  m_mini = mini;
}
 
int  CSignatureListViewItem::compare(Q3ListViewItem *item, int col, bool asc) const
{
//     if (col== 0)
// /    {
//	    return MakeComparable (	m_signature->GetSortIndex() , ((CSignatureListViewItem*) item)->GetSignature()->GetSortIndex() );
//     }
     if (col== 2)
     {
	    return MakeComparable (	m_signature->ComputeDLofModel() , ((CSignatureListViewItem*) item)->GetSignature()->ComputeDLofModel() );
     }
     if (col== 3)
     {
		return MakeComparable (	m_signature->GetCorpusCount() , ((CSignatureListViewItem*) item)->GetSignature()->GetCorpusCount() );
     }
    if (col== 4)
     {
		return MakeComparable (	m_signature->GetNumberOfStems() , ((CSignatureListViewItem*) item)->GetSignature()->GetNumberOfStems() );
     }
     if (col== 6)
     {
//		return MakeComparable (	((CSignatureListViewItem*) item)->GetSignature()->GetRobustness(), m_signature->GetRobustness()   );
     }
     else
     {
        return Q3ListViewItem::compare(item, col, asc);
     }
}
 

QString CSignatureListViewItem::text( int column ) const
{
  QList<CStem*>* stems = NULL;

  CSignatureListViewItem* child = NULL;

  int count;

  if( m_signature ) stems = m_signature->GetStemPtrList();

  switch( column )
  {
  case 0:
    if( m_signature && m_parentlist->sortColumn() == 0 && m_signature->GetMentor() )
    {
      return "  : " + m_label;
    }
    else return m_label;
  case 1:
    if( stems && stems->count() )
    {
      return stems->first()->Display( QChar(0), m_filter );
    }
    else return "";
  case 2:
	if( m_signature ) return QString("%1").arg( m_signature->ComputeDLofModel() );
	else return "";
   case 3:
    if( m_signature ) return QString("%1").arg( m_signature->GetCorpusCount() );
    else
    {
      count = 0;
      child = (CSignatureListViewItem*) firstChild();
      while( child )
      {
        if( child->GetSignature() )
        {
          count += child->GetSignature()->GetCorpusCount();
        }
        child = (CSignatureListViewItem*) child->nextSibling();
      }
      return QString("%1").arg( count );
    }
  case 4:
    if( m_signature && stems ) return QString("%1").arg( stems->count() );
    else
    {
      count = 0;
      child = (CSignatureListViewItem*) firstChild();
      while( child )
      {
        if( child->GetSignature() &&
          child->GetSignature()->GetStemPtrList() )
        {
          count += child->GetSignature()->GetStemPtrList()->count();
        }
        child = (CSignatureListViewItem*) child->nextSibling();
      }
      return QString("%1").arg( count );
    }
  case 5:
    if( m_signature ) return m_signature->GetRemark();
    else return "";
 
  case 6:
    if( m_signature ) return QString("%1").arg( (int) m_signature->GetRobustness(),8,10 );
 
    else
    {
      count = 0;
      child = (CSignatureListViewItem*) firstChild();
      while( child )
      {
        if( child->GetSignature() &&
          child->GetSignature()->GetStemPtrList() )
        {
          count += child->GetSignature()->GetStemPtrList()->count();
        }
        child = (CSignatureListViewItem*) child->nextSibling();
      }
      return QString("%1").arg( count );
    }
  case 7:
    return "";
  default:
    return Q3ListViewItem::text( column );
  }
}



CSignature::CSignature( CMiniLexicon* Lexicon ) : CLParse( Lexicon )
{
	m_pMyMini		= Lexicon;
	m_MyGeneralizer         = NULL;	
	m_Vector		= NULL;
	m_Remark		= "";
	m_Frequencies		= NULL;
	m_Robustness		= 0;
	m_Mentor		= NULL;
        m_StemPtrList		= new QList<CStem*>();
        m_WordPtrList		= new QList<CStem*>();
        m_MentorList		= new QList<CSignature*>();
        m_SuffixPtrList		= new QList<CSuffix*>();
        m_PrefixPtrList		= new QList<CPrefix*>();
    m_SortStyle         = eAlphabetized;	
       // Description Length
       m_DLofMyCorpus         = 0;
       m_DLofMyStemPointers   = 0;
       m_DLofMyAffixPointers  = 0;
       m_LengthOfPointerToMe  = 0;
  if( Lexicon ) m_AffixLocation = Lexicon->GetAffixLocation();
}


CSignature::CSignature( eAffixLocation AffixLocation, CMiniLexicon* Lexicon ) : CLParse( Lexicon )
{
	m_pMyMini		= Lexicon;
	m_MyGeneralizer         = NULL;	
	m_AffixLocation	        = AffixLocation;
	m_Vector		= NULL;
	m_Remark		= "";
	m_Frequencies	        = NULL;
	m_Robustness	        = 0;
	m_Mentor		= NULL;
        m_StemPtrList		= new QList<CStem*>();
        m_WordPtrList		= new QList<CStem*>();
        m_MentorList		= new QList<CSignature*>();
        m_SuffixPtrList		= new QList<CSuffix*>();
        m_PrefixPtrList		= new QList<CPrefix*>();
       m_DLofMyCorpus           = 0;
       m_DLofMyStemPointers     = 0;
       m_DLofMyAffixPointers    = 0;
       m_LengthOfPointerToMe    = 0;
       m_SortStyle         = eAlphabetized;	
}


CSignature::CSignature (const CParse& ParseSig, CMiniLexicon* Lexicon) : CLParse ( ParseSig, Lexicon )
{
  m_pMyMini        = Lexicon;
  m_MyGeneralizer  = NULL;	
  m_Vector         = NULL;
  m_Remark         = "";
  m_Frequencies    = new float [ ParseSig.Size() + 1 ];
  for (int i = 1; i <= Size(); ++i)
  {
    m_Frequencies[i] = 0;
  }
  m_Robustness    = 0;
  m_Mentor      = NULL;
   
        m_StemPtrList		= new QList<CStem*>();
        m_WordPtrList		= new QList<CStem*>();
        m_MentorList		= new QList<CSignature*>();
	m_AffixLocation		= Lexicon->GetAffixLocation();
       m_DLofMyCorpus         = 0;
       m_DLofMyStemPointers   = 0;
       m_DLofMyAffixPointers  = 0;
       m_LengthOfPointerToMe  = 0;

      m_SortStyle         = eAlphabetized;	
}


CSignature::CSignature (const CParse* pParseSig, CMiniLexicon* Lexicon) : CLParse ( *pParseSig, Lexicon )
{
  m_pMyMini      = Lexicon;
  m_AffixLocation		= Lexicon->GetAffixLocation();
  m_Vector      = NULL;
  m_Remark      = "";
  m_Frequencies    = new float [ Size() + 1 ];
  for (int i = 1; i <= Size(); ++i)
  {
    m_Frequencies[i] = 0;
  }
  m_Robustness    = 0;
  m_Mentor      = NULL;
 
  m_StemPtrList		= new QList<CStem*>();
  m_WordPtrList		= new QList<CStem*>();
  m_MentorList		= new QList<CSignature*>();
  m_SuffixPtrList           = new QList<CSuffix*>();
  m_PrefixPtrList		= new QList<CPrefix*>();
  m_DLofMyCorpus         = 0;
  m_DLofMyStemPointers   = 0;
  m_DLofMyAffixPointers  = 0;
  m_LengthOfPointerToMe  = 0;
  m_MyGeneralizer         = NULL;
  m_SortStyle         = eAlphabetized;
}


CSignature::CSignature(const CSignature& Sig) : CLParse (Sig, Sig.GetLexicon())
{
	m_pMyMini = Sig.GetLexicon();	
        QList<CStem*>*		pStemList = Sig.GetStemPtrList();

	m_AffixLocation = Sig.GetAffixLocation();
	m_Remark = Sig.GetRemark();
	
       m_StemPtrList = new QList<CStem*>();
       for (int z = 0; z < pStemList->size(); z++)
        {
            m_StemPtrList->append( pStemList->at(z) );
	}
	m_Frequencies = new float [ Size() +1 ];
	for( int i = 0; i < Size(); ++i) {
		if ( Sig.m_Frequencies )
		{
			m_Frequencies[i] = Sig.GetNthFrequency(i);
		}
		else
		{
			m_Frequencies[i] = 0;
		}
	}
	m_Robustness = Sig.GetRobustness();
	m_Mentor = NULL;
	m_MyGeneralizer         = NULL;	 
    m_SortStyle         = eAlphabetized;	
 // @@@ Copy these from the argument: Oct 2008
        m_WordPtrList = new QList<CStem*>();

        m_MentorList = new QList<CSignature*>();
        m_SuffixPtrList = new QList<CSuffix*>();

        m_PrefixPtrList = new QList<CPrefix*>();
}


CSignature::CSignature(const CStringSurrogate& ssSig, CMiniLexicon* Lexicon) : CLParse(ssSig, Lexicon)
{
  m_pMyMini      = Lexicon;

	m_AffixLocation		= Lexicon->GetAffixLocation();
  m_Vector      = NULL;
  m_Frequencies    = NULL;
  m_Robustness    = 0;
  m_Mentor      = NULL;
  m_StemPtrList		= new QList<CStem*>();
  m_WordPtrList		= new QList<CStem*>();
  m_MentorList		= new QList<CSignature*>();
  m_SuffixPtrList     = new QList<CSuffix*>();
  m_PrefixPtrList     = new QList<CPrefix*>();
       m_DLofMyCorpus         = 0;
       m_DLofMyStemPointers   = 0;
       m_DLofMyAffixPointers  = 0;
       m_LengthOfPointerToMe  = 0;
  Collapse( ssSig, '.');
      m_SortStyle         = eAlphabetized;	
}


CSignature::~CSignature()
{
  if( m_Frequencies   ) delete [] m_Frequencies;
  if( m_StemPtrList   ) delete m_StemPtrList;
  if( m_WordPtrList   ) delete m_WordPtrList;
  if( m_MentorList    ) delete m_MentorList;
  if( m_SuffixPtrList ) delete m_SuffixPtrList;
  if( m_PrefixPtrList ) delete m_PrefixPtrList ;
}

QString CSignature::Display(QChar sep, QMap<QString, QString>* filter) const
{
	QString sd = sep;
	if (sd == ".") {
		sd = m_pMyMini->GetDocument()->GetPreferences()
			->GetPreference("Sig_Delimiter");
		if (sd.size() != 1)
			sd = ".";
	}
	return CParse::Display(sd.at(0), filter);
}

QString CSignature::Display(QMap<QString, QString>* filter) const
{ return CParse::Display(filter); }

QString CSignature::Display() const
{ return CParse::Display('.'); }

void CSignature::ConsumeParse( CParse* pParse )
{
	ClearParse();
	SetKey( pParse );
	CopyParseStructure( *pParse );	
}


void CSignature::Suicide()
{
  //TODO: fill this in;
}
void CSignature::SetMyGeneralizer (CSignature* pSig)
{
	m_MyGeneralizer = pSig;
}

void CSignature::operator=(const CSignature* pSig)
{
  int                   z;
  QList<CStem*>*    pStemList = pSig->GetStemPtrList();
  QList<CStem*>*    pWordList = pSig->GetWordPtrList();
// The following two were added by JG August 2006
  QList<CSuffix*>*  pSuffixPtrList = pSig->GetSuffixPtrList();
  QList<CPrefix*>*  pPrefixPtrList = pSig->GetPrefixPtrList();


  CLParse::operator=(*pSig);
  m_AffixLocation = pSig->GetAffixLocation();
  m_Remark = pSig->GetRemark();

  /*  Copy Stem Pointer list      */
  for (z = 0; z < pStemList->size(); z++)
  {
      m_StemPtrList->append ( pStemList->at(z) );
  }


  /*  Copy Word Pointer list      */
  for (z = 0; z < pWordList->size(); z++)
  {
      m_WordPtrList->append ( pWordList->at(z) );
  }


	  /*  Copy Suffix Pointer list      */

  for (z = 0; z < pSuffixPtrList->size(); z++)
  {
        m_SuffixPtrList->append ( pSuffixPtrList->at(z) );
  }

	  /*  Copy Prefix Pointer list      */
  for (z = 0; z < pPrefixPtrList->size(); z++)
  {
       m_PrefixPtrList->append( pPrefixPtrList->at(z) );
  }

  m_Frequencies = new float [ Size() +1 ];
  for (int i = 0; i < Size(); ++i) {
    if ( pSig->m_Frequencies )
    {
      m_Frequencies[i] = pSig->GetNthFrequency(i);
    }
    else
    {
      m_Frequencies[i] = 0;
    }
  }
  m_Robustness = pSig->GetRobustness();
  m_Mentor      = NULL;
}


QTextStream& operator<< (QTextStream& stream, CSignature* pSig)
{
  CStem*      pStem;

  stream << endl << pSig->Display();
  stream.width(6);
  stream << pSig -> GetNumberOfStems() << "  " <<  pSig->GetCorpusCount();

  for (int z = 0; z < pSig->GetStemPtrList()->size(); z++)
  {
    pStem = pSig->GetStemPtrList()->at(z);
    if ( pStem->GetKey() != CStringSurrogate() )
    {
      stream << endl;
      stream.width(20);
      stream << pStem->GetKey().Display();
    } else
    {
      stream << endl;
      stream.width(20);
      stream << "???";
    }
  }

  return stream;

}



int CSignature::GetNumber( CSuffix* pSuffix )
{
  CStringSurrogate ssSuffix = pSuffix->GetKey();
  for (int i = 1; i <= Size(); ++i) {
    if ( GetPiece(i) == ssSuffix )
    {
      return i;
    }

  }
  return 0;
}


CSignature*    CSignature::GetMentor  ( )            { return m_Mentor; }

void      CSignature::SetMentor  ( CSignature* pSig )
{
  m_Mentor = pSig;
  if( pSig && pSig->GetMentorList() && pSig->GetMentorList()->indexOf (this) < 0)
  { 
    pSig->GetMentorList()->append( this );
  }
}

QList<CSignature*>*    CSignature::GetMentorList( ) { return m_MentorList; }



void CSignature::SetRemark ( QString remark)
{ m_Remark = remark; }

QList<CStem*>* CSignature::GetWordPtrList() const
{ return m_WordPtrList; }

QList<CSuffix*>* CSignature::GetSuffixPtrList() const
{ return m_SuffixPtrList; }

QList<CPrefix*>* CSignature::GetPrefixPtrList() const
{ return m_PrefixPtrList; }

QString CSignature::GetRemark() const { return m_Remark; }

void CSignature::CalculateFrequencies(CMiniLexicon* Lexicon)
{
  CStringSurrogate  Suffix;
  CSuffix*          pSuffix;
  CStem*            pStem;
  CCorpusWord*      pCorpusWord;
  Q_ASSERT( GetCorpusCount() > 0);
  int               TotalCorpusCount = 0, i;
  int*              SuffixCount = new int [ Size()+ 1 ];
  for (int k = 1; k <= Size(); ++k)
  { SuffixCount[k] = 0; }

  for ( i = 1; i <= Size(); i++)
  {
        Suffix      = GetPiece(i);
        pSuffix      = new CSuffix(Suffix);

        for (int z= 0; z < m_StemPtrList->size(); z++)
        {
            pStem = m_StemPtrList->at(z);         
            pCorpusWord        = Lexicon->FindAWord (pStem, pSuffix);
            if( pCorpusWord )                // might not exist if we have collapsed signatures.
            {
                TotalCorpusCount  += pCorpusWord->GetCorpusCount();
                SuffixCount[i]    += pCorpusWord->GetCorpusCount();
            }
        }
  }
  for ( i = 1; i <= Size(); i++)
  {
    m_Frequencies[i] = float( SuffixCount[i] ) / TotalCorpusCount;
  }
  delete [] SuffixCount;
}

void CSignature::BorrowedSigsDisplay(Q3ListView* List,
		QMap<QString, QString>* filter)
{
	QString source = "Unknown";
	for (int i = 0; i < m_pMyMini->GetMiniSize(); ++i) {
		CMiniLexicon* mini = m_pMyMini->GetMiniLexicon(i);
		if (mini == 0)
			continue;

		CSignatureCollection& sigs = *mini->GetSignatures();
		if (sigs ^= this) {
			// found!
			source = QString("Mini-Lexicon %1").arg(i + 1);
			break;
		}
	}

	static_cast<void>(new Q3ListViewItem(
		List, Display('.', filter), source));
}

void CSignature::ListDisplay(Q3ListView* List,
	QMap<QString, QString>* filter, bool ExpressDeletees)
{
	CSignature sig(m_pMyMini);
	Express(sig, ExpressDeletees);
	QString text = sig.Display('.', filter);

	static_cast<void>(new CSignatureListViewItem(
		List, text, m_pMyMini->GetIndex(), this, filter));
}

float CSignature::GetNthFrequency (int n) const
{ return m_Frequencies[n]; }

CSparseIntVector*  CSignature::GetVector () { return m_Vector; }

void    CSignature::FindCorpusCount( )
{  // rewritten March 10 2000 JG
  // This should be redone again Oct 2001
// CStem*    pWord;
  int      Count = 0;


  for (int z =0; z < m_WordPtrList->size(); z++)
  {
     Count += (int) m_WordPtrList->at(z)->GetCorpusCount();
  }

  // what do we do with Count, now? JG @@@
}

void  CSignature::operator<< (CStem* pStem) //add to tail of list.
{

  CStem* pWord;

  if ( m_StemPtrList->indexOf ( pStem ) < 0 )
  {
    Q_ASSERT (pStem->GetKeyLength() > 0);
    m_StemPtrList->append(pStem);
  }

  Q_ASSERT ( m_PieceCount  <= m_LengthOfPieceVector  )  ;

  for (int z = 0; z < pStem->GetWordPtrList()->size(); z++)
  {
    //++it;
    pWord = pStem->GetWordPtrList()->at(z);
    Q_ASSERT (pWord->GetKeyLength() > 0);
    m_WordPtrList->append (pWord);
  }
  pStem->SetSuffixSignature (this);

  m_Robustness = 0;
  m_Robustness = GetRobustness();
}

void  CSignature::AttachToSuffixSig(CStem* pStem, bool bLookAtPreviousSig) //add to tail of list.
{

	CStem*        pWord;
	CSignature*   pOldSig = pStem->GetSuffixSignature();
	
	/*  First, remove pStem from any other SuffixSignature it might be linked to.*/
	if ( pOldSig && pOldSig != this )
	{
		pOldSig->DetachStem( pStem, eDo_Not_Call_Words );
	}
    
        if( m_StemPtrList->indexOf ( pStem ) < 0 )
	{
		m_StemPtrList->append( pStem );
	}


	// move the Words from the old signature to this, the new one. 
        for (int z = 0; z < pStem->GetWordPtrList()->size(); z++)
	{
            pWord = pStem->GetWordPtrList()->at(z);
            m_WordPtrList->append (pWord);
            pWord->SetSuffixSignature (this);
            if ( bLookAtPreviousSig && pOldSig && pOldSig != this  && pOldSig->GetWordPtrList()->count() > 0 )
            {
                pOldSig->GetWordPtrList()->remove( pWord );
            }
	}

	pStem->SetSuffixSignature( this );
	IncrementCorpusCount( pStem->GetCorpusCount()-1 );// first time CC is incremented
	
	
	m_Robustness = 0;
	m_Robustness = GetRobustness();
}

void  CSignature::AttachToPrefixSig( CStem* pStem, bool bLookAtPreviousSig ) //add to tail of list.
{

	CStem*        pWord;
	CSignature*   pOldSig = pStem->GetPrefixSignature();
	
	/*  First, remove pStem from any other PrefixSignature it might be linked to.*/
	if ( pOldSig && pOldSig != this )
	{
		pOldSig->DetachStem( pStem, eDo_Not_Call_Words );
	}
    
        if( m_StemPtrList->indexOf ( pStem ) < 0 )
	{
		m_StemPtrList->append( pStem );
	}


	// move the Words from the old signature to this, the new one.

        for (int z = 0; z < pStem->GetWordPtrList()->size(); z++)
	{
                //++it;
             pWord = pStem->GetWordPtrList()->at(z);
		m_WordPtrList->append (pWord);
		pWord->SetPrefixSignature (this);
	
	
		if ( bLookAtPreviousSig && pOldSig && pOldSig != this  && pOldSig->GetWordPtrList()->count() > 0 )
		{
			pOldSig->GetWordPtrList()->remove( pWord );
		}
	}

	pStem->SetPrefixSignature( this );
	IncrementCorpusCount( pStem->GetCorpusCount()-1 );
	
	
	m_Robustness = 0;
	m_Robustness = GetRobustness();
}


double CSignature::GetRobustness() const
{
  int    SuffixLetters = 0,
      StemLetters = 0;

  if (m_Robustness == 0)
  {
    SuffixLetters = GetKeyLength();
    QString Null = "NULL";
    if ( Contains( CStringSurrogate(Null.unicode(),0,Null.length()) ) ) { SuffixLetters -= 4; }

    CStem* pStem;

    for (int z = 0; z < m_StemPtrList->size(); z++)
    {
      pStem = m_StemPtrList->at(z);
      StemLetters += pStem->GetKeyLength();
    }

    m_Robustness = ( Size() - 1 ) * StemLetters  + (GetNumberOfStems() - 1) * SuffixLetters;

  }
  return m_Robustness;
}

void CSignature::SetRobustness ( double R ) { m_Robustness = R; }


int CSignature::GetNumberOfStems() const
{ return m_StemPtrList->count(); }

int CSignature::GetNumberOfAffixes() {return m_PieceCount; }


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// TODO: make sure COST function is consistent with older versions and working right
    double CSignature::FindCost(CMiniLexicon* Lexicon)

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*
Cost of a sig =

  Sum over all of its stems :

      log ( CorpusSize / Stem-count )      ( cost    )
      length ( stem ) * cost of a letter    ( savings )

  Sum over all of its suffixes:

      log ( CorpusSize / suffix-count )      ( cost    )
      length ( suffix ) * cost of a letter    ( savings )
*/
{
  CStem*      pStem;
  double      Cost          = 0,
              AffixCost     = 0,
              AffixSavings  = 0,
              SignatureCost = 0,
              StemCost      = 0,
              StemSavings   = 0,
              CostOfALetter = base2log (26),
              ThisAffixCost = 0,
              NumberOfWords = Lexicon->GetWords()->GetCount();
  CAffix*     pAffix;


  for (int  f = 1; f <= Size(); f++)
  {
    if( m_AffixLocation == WORD_FINAL || m_AffixLocation == STEM_FINAL ) 
		{
			pAffix = *Lexicon->GetSuffixes() ^= GetPiece(f);
		}
		else
		{
 		  pAffix = *Lexicon->GetPrefixes() ^= GetPiece(f);
		}

    if ( pAffix ) // it already exists
    {
      ThisAffixCost  =  base2log ( NumberOfWords / pAffix->GetUseCount() );
    }
    else
    {
      ThisAffixCost = base2log ( NumberOfWords/GetNumberOfStems() );
      ThisAffixCost += GetPiece(f).GetLength() * CostOfALetter;
    }
    AffixCost += ThisAffixCost;

    AffixSavings +=  GetPiece(f).GetLength() * CostOfALetter;

    SignatureCost += ThisAffixCost;
  }


  for (int z = 0; z < m_StemPtrList->size(); z++)
    {
       pStem = m_StemPtrList->at(z);;
        StemCost += base2log ( NumberOfWords / Size() ); // Size is the number of words that use stem, of course.
        StemCost += pStem->GetKeyLength() * CostOfALetter;
        StemSavings += pStem->GetKeyLength() * CostOfALetter * Size(); // save for each time stem appears, with each suffix
        SignatureCost += StemCost;
  }

  Cost = AffixCost + StemCost - AffixSavings - StemSavings + SignatureCost;

  return Cost;
}


/* 10-31-99 *******************************************************
 *
 *    Using vector representation of signature
 *
 */

void CSignature::ComputeSignatureVector(CMiniLexicon* Lexicon)
{
  CSuffixCollection*  Suffixes = Lexicon->GetSuffixes();
  CPrefixCollection*  Prefixes = Lexicon->GetPrefixes();
  CStringSurrogate			Suffix, Prefix;
  CSuffix*      			pSuffix;
  CPrefix*      			pPrefix;
	
  m_Vector = new CSparseIntVector;

  for (int i = 1; i <= Size(); i++) 
	{
    switch( m_AffixLocation )
		{
			case WORD_INITIAL:
			case STEM_INITIAL:
				Prefix = GetPiece(i);
				pPrefix = *Prefixes ^= Prefix;
				if( pPrefix )
				{
					m_Vector->SetAt( pPrefix->GetIndex(), 1 );
				}
				break;
				
			case WORD_FINAL:
			case STEM_FINAL:
			default:
				Suffix = GetPiece(i);
				pSuffix = *Suffixes ^= Suffix;
				if( pSuffix ) 
				{
					m_Vector->SetAt( pSuffix->GetIndex(), 1 );
				}
				break;
		}
	}
}


float CSignature::GetSortingQuantity() const
{
  return (float) GetRobustness();
}

CParse  CSignature::GetStems()
{
  CParse  List;
//  CStem*  pStem;

  List.Alphabetize();

  if ( m_StemPtrList->count() == 0 ) { return List; } // **********  This is clearly a mistake. Fix it.
  for (int z = 0; z < m_StemPtrList->size(); z++)
  {
    List.Append( m_StemPtrList->at(z)->GetKey() );
  }

  return List;
}

CParse  CSignature::GetWords()
{
  CParse  List;
  if (m_WordPtrList->count() == 0 ) { return List; }  // clearly an error == Fix it.

  for (int z = 0; z < m_WordPtrList->size(); z++)
  {
      List.Append( m_WordPtrList->at(z)->GetKey() );
   }

  List.Alphabetize();
  return List;
}


QList<CStem*>*  CSignature::GetStemPtrList() const
{
  return m_StemPtrList;
}

eAffixLocation CSignature::GetAffixLocation() const
{ return m_AffixLocation; }

void  CSignature::OutputSignature( QTextStream& outf )
{
	QString				strOutput;
	CStem*				pStem;
	CStringSurrogate	Suffix,
						Prefix;
	CParse				StemList;
	QString				string;
	
	outf << endl;

	outf << "  ";
	outf << Display( '.', m_pMyMini->GetOutFilter() );
	outf << "   ";

	outf << QString("%1").arg( (int) GetNumberOfStems() );
	outf << "   ";

	outf << QString("%1").arg( GetCorpusCount() );
	outf << " ";	
	outf << endl;
	
	outf << "  ";
	outf << GetRemark().replace( QChar(' '), "_" );
	outf << " ";
	outf << endl;	
	
	QStringList stems;
       for (int z = 0; z < m_StemPtrList->size(); z++)
	{
                //++it;
            pStem = m_StemPtrList->at(z);
            if ( pStem->GetKey() != CStringSurrogate() )
            {
                stems.append( pStem->Display( 0, m_pMyMini->GetOutFilter() ) );
            }
	}
	
	stems.sort();
	int m = 1;
	outf << "  ";
	for( QStringList::Iterator strIt = stems.begin(); strIt != stems.end(); ++strIt )
	{
		outf << *strIt << " ";
		if( m % 10 == 0 )
		{
			outf << endl;
			outf << "  ";
		}
		m++;
	}

	outf << endl;
}


/*    This purpose of this function is to take a signature of the form A.SUFFIX
    and make it NULL.SUFFIX (the pAlternateSig), and move that letter A back onto its stems.
*/


void CSignature::RemoveLetter (CStringSurrogate& ssLetter, CMiniLexicon* Lexicon, CSignature* pAlternateSig)
{

  CStem*        pStem,
                *qStem = NULL;
  CSuffix*      pSuffix,
                *pNewSuffix = NULL;
  QString        Stem,
                Suffix,
                Null = "NULL";
  QString        OldKey = Display();
  CStringSurrogate  ssSuffix,
                ssStem;
  CStem*        pWord;
  CSignature    NewSig ( WORD_FINAL, Lexicon );
  int           LetterLength = ssLetter.GetLength();

  CSignature   *qSig = NULL,
                *pOlderSig = NULL;
  CParse        PSuffix,
                PWord,
                PNewStem;

  QMap<QString,CSuffix*>  SuffixPtrTranslation;

  /*    Create the NewSig    */
  for (int n = 1; n <= Size(); n++)
  {
    ssSuffix = GetPiece(n);
    if(!NewSig.GetSortStyle()== eAlphabetized) NewSig.Alphabetize();
    if ( ssSuffix == ssLetter )
    {
      if(!NewSig.GetSortStyle()==eAlphabetized) NewSig.Alphabetize();
      NewSig.Append ( CStringSurrogate(Null.unicode(),0,Null.length()) );
    }
    else
    {
      QString lt_brak = "<", rt_brak = ">";

      PSuffix = CStringSurrogate(lt_brak.unicode(),0,1);
      PSuffix += ssLetter;
      PSuffix += CStringSurrogate(rt_brak.unicode(),0,1);
      PSuffix += ssSuffix;

      pSuffix = *Lexicon->GetSuffixes() << PSuffix;

      Suffix  = "<" + ssLetter.Display() + ">" + ssSuffix.Display();
      SuffixPtrTranslation[ ssSuffix.Display() ] = pSuffix; // based on old suffix
//      SuffixStringTranslation[ ssSuffix.Display() ] = Suffix;

      NewSig.Append ( PSuffix.GetKey() );
    }
  }

  /*    Change the KEY of this signature    */

  SetKey ( NewSig );
  QString remark = GetRemark() + " +allomorphy";
  SetRemark ( remark );

  //------------------------------------------------------------//
  // Change the signature, the stems, the words -- and the suffixes.
    //-----------------------------------//
  /*  Deal with the stems         */
  //-----------------------------------//


  for (int z = 0; z < m_StemPtrList->size(); z++)
  {
    pStem = m_StemPtrList->at(z);
    ssStem   = pStem->GetKey();
    PNewStem = ssStem + ssLetter;
    qStem    = *Lexicon->GetStems() ^= PNewStem;

    if (qStem)    // -- if the larger one already existed
    {
      pOlderSig = *Lexicon->GetSignatures() ^= qStem->GetSuffixList();

      // this removes both stem and word from signature:
      pOlderSig ->  DetachStem ( qStem, eCall_Words ); // we might want to eliminate this sig if it has no more stems

      qStem    ->  GetSuffixList()->MergeAndAlphabetizeParse( CParse(NewSig) );

      qSig    =    *Lexicon->GetSignatures() << qStem->GetSuffixList();

      // attaches both stems and words to qSig
      qSig    ->  AttachToSuffixSig(qStem, false);

    }
    else // make the old stem into this new one
    {
      pStem   -> RepairSuffixList ( Lexicon );
      Lexicon   ->  GetStems()-> SetKey( pStem, PNewStem );
      pStem   ->  SetKey( PNewStem );

    }
    }


  //---------------------------------------------//
  /*  Deal with the WORDs of this signature     */
  //---------------------------------------------//

  for (int y = 0; y < m_WordPtrList->size(); y++)
  {
    pWord = m_WordPtrList->at(y);
    pNewSuffix = SuffixPtrTranslation[ pWord->GetSuffix().Display() ];
    pWord -> ShiftStemSuffixBoundary ( LetterLength );

    pWord -> SetSuffixPtr ( pNewSuffix );
    pWord -> AttachWordAndSuffixalStem   ( pStem );
    pWord -> SetSuffixSignature ( this );
    }


  //------------------------------------------------------------//
  //    Alternate Sig
  //------------------------------------------------------------//
  /*  Shift stems from AlternateSig to the NewSig, but NOT
    if the stem ends with Letter; if it does, we'll
    keep the old signature with that stem.


      This will replace some or all of pAlternateSig --
    "some" when there are any stems that don't allow removal of the Letter.
    For example, NULL.ing will not disappear when <e>ing.NULL is created,
    because the stem "be"  still requires NULL.ing --
   */

  // Deal with stems in AlternateSig....

  for (int w = 0; w < pAlternateSig->GetStemPtrList()->size(); w++)
  {
    pStem = pAlternateSig->GetStemPtrList()->at(w);
    ssStem    = pStem->GetKey();
    if ( ssStem.Right(LetterLength) == ssLetter )
    { continue; }

    pAlternateSig->DetachStem( pStem, eCall_Words );
    AttachToSuffixSig( pStem, false );
  }
  // Deal with Words in Alternate signature

  for (int w = 0; w < pAlternateSig->GetStemPtrList()->size(); w++)
  {
    pWord = pAlternateSig->GetStemPtrList()->at(w);
    pNewSuffix = SuffixPtrTranslation[ pWord->GetSuffix().Display() ];

    pWord -> SetSuffixPtr ( pNewSuffix );
    pWord -> AttachWordAndSuffixalStem   ( pStem );
    pWord ->SetSuffixSignature ( this );
  }

  //------------------------------------------------------------//

  /*    Get rid of the Alternate Sig ("NULL.ing" )  */

  if  ( pAlternateSig->GetStemPtrList()->count() == 0 )
  {
    Lexicon->GetSignatures()->Remove( pAlternateSig );
  }


}

bool CSignature::EachSuffixCanHaveThisLetterPrefixedToIt ( const QString& Letter)
{
  QString    Suffix;
  for (int i = 1; i <= Size(); ++i) {
    Suffix = GetPiece(i).Display();
    if (Suffix == "NULL" ) { Suffix = ""; }
    Suffix = Letter + Suffix;
    if(0)// TODO:    if ( ! (*Lexicon->GetSuffixes() ^= Suffix )   )
    {
      return FALSE;
    }
  }

  return TRUE;
}

void CSignature::ShiftStemSuffixCutToTheLeft(int Distance,
	const QString& Piece)
{
	struct not_implemented { };
	throw not_implemented();

	// XXX. suppresses “unused parameter” warnings
	static_cast<void>(Distance);
	static_cast<void>(Piece);

	foreach (CStem* word, *m_WordPtrList) {
		word->ShiftStemSuffixBoundary(-1);
		Q_ASSERT(word->GetStemLoc() != 0);
	}

	foreach (CStem* stem, *m_StemPtrList) {
		CStringSurrogate stem_text = stem->GetKey();
		stem->ClearParse();
		stem->SetKey(stem_text.Left(stem_text.GetLength() - 1));

		// XXX. Check to see if the new stem already exists.
//		Lexicon->GetStems()->GetHash()->RemoveKey ( Stem );
//		Lexicon->GetStems()->GetHash()->SetAt( NewStem, pStem );
//		Lexicon->GetStems()->SetKey( pStem, NewStem  );
	}

	// XXX. fix the signature
//	AddLetter ( 1, Piece );

//	Lexicon->AddToScreen ( Display() );
}

// Variant in which the shifted string varies from stem to stem.
void CSignature::ShiftStemSuffixCutToTheLeft(int Distance)
{
	// XXX. suppresses “unused parameter” warning
	static_cast<void>(Distance);
	struct not_implemented { };
	throw not_implemented();

	// first, fix the words;
	foreach (CStem* word, *m_WordPtrList) {
		word->ShiftStemSuffixBoundary(-1);
		Q_ASSERT(word->GetStemLoc() != 0);
	}

	// XXX. fix the signature
//	AddLetter ( 1, Piece );

//	Lexicon->AddToScreen ( Display() );
}

void CSignature::AddLetter(const QString& Letter )
{
  PrefixToAllPieces ( CStringSurrogate(Letter.unicode(),0,Letter.length() ) );

}

/// Looks at the final ngrams of the stems, and calculates its entropy
double CSignature::ComputeFinalNgramEntropyOfStems(int n)
{
	TCollection<CLParse> Ngrams;
	foreach (CStem* pStem, *m_StemPtrList) {
		if (pStem->GetKeyLength() <= n)
			// too short
			return -1;

		CStringSurrogate ssPiece = pStem->GetKey();
		ssPiece = is_initial(GetAffixLocation()) ?
			ssPiece.Left(n) : ssPiece.Right(n);
		Ngrams << ssPiece;
	}

	double Entropy = 0.0;
	const double StemCount = m_StemPtrList->count();
	const int ngram_count = Ngrams.GetCount();
	for (int i = 0; i < ngram_count; ++i) {
		const double fraction = StemCount / Ngrams[i]->GetCorpusCount();
		Entropy += log2(fraction) / fraction;
	}

	return Entropy;
}

/// Test to see whether the break with its stems is a good one.
int CSignature::CheckOut(CMiniLexicon* Lexicon)
{
	using linguistica::implicit_cast;
	// Throughout, “DL” stands for “description length”.

	if (Lexicon->LogFileOn()) {
		// dump stem list to log file.

                QTextStream& log = *Lexicon->GetLogFile();

		log << LargeTitle(this->Display()) <<
			StartTable <<
			StartTableRow;

		const int num_columns = 5;

		// For each stem:
		CParse Stems = GetStems();
		for (int i = 1; i <= GetNumberOfStems(); ++i) {
			if (i % num_columns == 0)
				log << EndTableRow << StartTableRow;

			log << TableData(Stems[i]);
		}
		log << EndTableRow <<
			EndTable;
	}

	if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
		// Header for stem resolution table
		StartTable <<
		StartTableRow <<
			MakeTableHeader("Number of letters") <<
			MakeTableHeader("Entropy") <<
			MakeTableHeader("Resolution?") <<
		EndTableRow;

	bool LowEntropyFlag = false;
	int LargestSizeChunkToPullOffStem = 0;
	// Use entropy to see how many letters to consider shifting
	// XXX. Make this user-changeable.
	const double EntropyThreshold = 1.5;
	const int LengthToConsiderShifting = 4;
	for (int n = 1; n <= LengthToConsiderShifting; ++n) {
		const double Entropy = ComputeFinalNgramEntropyOfStems(n);

		if (Entropy < 0) {
			// Negative entropy:
			// stem too short to consider shortening.

			if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
				StartTableRow <<
					TableData() <<
					TableData() <<
					TableData("No reanalysis") <<
				EndTableRow;
			continue;
		}

		if (Entropy >= EntropyThreshold) {
			if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
				StartTableRow <<
					TableData(n) <<
					TableData(Entropy) <<
					TableData("Entropy too large") <<
				EndTableRow;
			break;
		}

		// set of n-suffixes of stems has low entropy:
		// maybe stems have a common suffix that should be
		// incorporated into the signature.
		LowEntropyFlag = true;
		LargestSizeChunkToPullOffStem = n;

		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			StartTableRow <<
				TableData(n) <<
				TableData(Entropy) <<
				TableData("Entropy sufficiently small") <<
			EndTableRow;
	}
	if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
		EndTable;

	if (!LowEntropyFlag)
		// Not enough stems share common endings to restructure,
		// so leave this signature alone.
		return 0;

	const bool analyzingSuffixes = !is_initial(GetAffixLocation());

	const double TotalNumberOfAnalyzedWords =
		Lexicon->GetSignatures()->GetTotalNumberOfWords();
	const double LogTotalNumberOfAnalyzedWords =
		base2log(TotalNumberOfAnalyzedWords);
	const double LengthOfPointerToThisSig =
		LogTotalNumberOfAnalyzedWords -
		base2log(Size() * GetNumberOfStems());

	// Description length of the original analysis
	double CurrentDL;
	{
		// DL of this signature:
		//
		// a. Length of pointers to its suffixes;								var: LengthOfPointersToAllAffixesOfSig
		// b. Prorated responsibility for phonological content of suffixes
		//	var: TotalResponsibilityForAffixListings
		// c. List of pointers from each stem to this signature
		//	var: StemPointersToThisSig;
		// d. List of pointers from each word to its suffix

		// Compute DL of 'original' analysis.

		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			SmallerTitle("Description length of current signature") <<
			StartTable <<
			StartTableRow <<
				MakeTableHeader("Affix") <<
				MakeTableHeader("Use count") <<
				MakeTableHeader("Pointer to this affix") <<
			EndTableRow;

		double LengthOfPointersToAllAffixesOfSig = 0.0;
		double TotalResponsibilityForAffixListings = 0.0;
		// for each suffix (resp. prefix) in this signature:
		for (int k = 1; k <= Size(); ++k) {
			QString Affix = GetPiece(k).Display();
			CAffix* pAffix = analyzingSuffixes
				? implicit_cast<CAffix*>(
					*Lexicon->GetSuffixes() ^= Affix)
				: implicit_cast<CAffix*>(
					*Lexicon->GetPrefixes() ^= Affix);
		
			// Length of pointers to affixes
			//  part a
			const double LengthOfPointerToThisAffix =
				LogTotalNumberOfAnalyzedWords -
				base2log(pAffix->GetUseCount());
			LengthOfPointersToAllAffixesOfSig +=
				LengthOfPointerToThisAffix;
			
			if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
				StartTableRow <<
					TableData(Affix) <<
					TableData(pAffix->GetUseCount()) <<
					TableData(LengthOfPointerToThisAffix) <<
				EndTableRow;

			// use count of affix; length of pointer to this affix.

			// Assign partial responsibility for this signature's
			// suffixes' entries.
			//  part b.
			const double LocalProportion =
				double(GetNumberOfStems()) / pAffix->GetUseCount();
			const double ResponsibilityForThisAffixListing =
				LocalProportion * Affix.length() * base2log(26);
			TotalResponsibilityForAffixListings +=
				ResponsibilityForThisAffixListing; // in *bits*
		}
		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile()
			<< EndTable;

		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			StartTable;
		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			StartTableRow <<
				TableData("Part 1: Length of pointer to affixes") <<
				TableData(LengthOfPointersToAllAffixesOfSig) <<
			EndTableRow <<
			StartTableRow <<
				TableData("Part 2: Prorated responsibility for phonology of affixes:") <<
				TableData(TotalResponsibilityForAffixListings) <<
			EndTableRow;

		// part c.
		const double StemPointersToThisSig =
			GetNumberOfStems() * LengthOfPointerToThisSig;

		// In sum:
		const double total_dl =
			LengthOfPointersToAllAffixesOfSig +
			TotalResponsibilityForAffixListings +
			StemPointersToThisSig;

		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			StartTableRow <<
				TableData("Part 3: Stem pointers to this sig:")	<<
				TableData(StemPointersToThisSig) <<
			EndTableRow <<
			StartTableRow <<
				TableData("Length of 1 pointer to this sig:") <<
				TableData(LengthOfPointerToThisSig) <<
			EndTableRow <<
			StartTableRow <<
				TableData("Total") <<
				TableData(total_dl) <<
			EndTableRow;
		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			EndTable;
		CurrentDL = total_dl;
	}
	double WinningDL = CurrentDL;
	int WinningLengthOfStemToShift = 0;

	// We might shift only those stems for which the EndPiece
	// occurs in more than 45% of the stems of this sig (that
	// leaves open the case of two closely related letters
	// comprising almost all of the cases).
	// But for now, we're not doing that.

	// The outer loop here is for the case where the entropy test
	// tells us that 2 or more letters can be shifted
	// (e.g., sig on.ve can be shifted either to ion.ive or
	// tion.tive), and we want to evaluate both.

	// Major loop through alternatives to the current signature
	CParse WinningSig;
	// loop through different lengths to shift:
	for (int NumberOfLettersShifted = LargestSizeChunkToPullOffStem;
			NumberOfLettersShifted > 0;
			--NumberOfLettersShifted) {

		TCollection<CLParse> EndPieces;
		foreach (CStem* pStem, *m_StemPtrList) {
			if (pStem->GetKeyLength() <= NumberOfLettersShifted)
				continue;

			CStringSurrogate stem_text = pStem->GetKey();
			CStringSurrogate ssPiece = analyzingSuffixes
				? stem_text.Right(NumberOfLettersShifted)
				: stem_text.Left(NumberOfLettersShifted);
			EndPieces << ssPiece;
		}

		// XXX. The function is supple enough to move material
		// from the stem to the affix in some cases but not in others.

		double AllNewSigsAnalysisDL = 0.0;
		double TotalDecreaseInDLDueToShorterStems = 0.0;
		// each of these is a distinct piece being, perhaps,
		// transferred from stem(s) to affixes
		// for each string of this length that would have to be shifted:
		CParse Sig;
		for (int k = 0; k < EndPieces.GetCount(); ++k) {
			CLParse* pPiece = EndPieces.GetAt(k);

			// make a copy to play with.
			Sig = *this;

			if (analyzingSuffixes)
				Sig.PrefixToAllPieces2(pPiece->GetKey());
			else
				Sig.SuffixToAllPieces2(pPiece->GetKey());

			// DL of this signature:
			//
			// a. Length of pointers to its suffixes;
			//	var: LengthOfPointersToAllAffixesOfSig
			// b. Prorated responsibility for phonological
			//    content of suffixes
			//	var: TotalResponsibilityForAffixListings
			// c. List of pointers from each stem to this
			//    signature
			//	var: PointersToThisSig;
			// d. Savings because stems already existed
			//	var: SavingsBecauseStemAlreadyExisted
			// e. Savings because stems are shorter
			//	var: TotalDecreaseInDLDueToShorterStems :
			//	once for each *length* being shifted from
			//	stem to suffix
			// f. List of pointers from each word to its
			//    suffix
			//	XXX. not implemented.

			double LengthOfPointersToAllAffixesOfSig = 0.0;
			double TotalResponsibilityForAffixListings = 0.0;
			if (*Lexicon->GetSignatures() ^= Sig) {
				// new signature already exists
				if (Lexicon->LogFileOn())
					*Lexicon->GetLogFile() <<
					SmallerTitle(QString(
					"Alternative analysis (already existed): %1")
					.arg(Sig.Display('.')));

				// XXX. address this case!
			} else {
				// new signature
				if (Lexicon->LogFileOn())
					*Lexicon->GetLogFile() <<
					SmallerTitle(QString(
					"Conjectured signature: %1")
					.arg(Sig.Display('.')));

				//  iterate through suffixes of the signature
				if (Lexicon->LogFileOn())
					*Lexicon->GetLogFile() <<
					StartTable <<
					StartTableRow <<
						MakeTableHeader("Suffix") <<
						MakeTableHeader("Previous count") <<
						MakeTableHeader("New count") <<
						MakeTableHeader("Pointer length to this affix") <<
						MakeTableHeader("Responsibility for this affix (phonology) in bits:") <<
						MakeTableHeader("New DL for this affix") <<
					EndTableRow;
				double ThisNewSigDL = 0.0;
				// for each suffix (resp prefix) in the new sig:
				for (int n = 1; n <= Size(); ++n) {
					CStringSurrogate ssAffix =
						Sig.GetPiece(n);

					CAffix* pAffix = analyzingSuffixes
						? implicit_cast<CAffix*>(
							*Lexicon->GetSuffixes() ^= ssAffix)
						: implicit_cast<CAffix*>(
							*Lexicon->GetPrefixes() ^= ssAffix);
					double sum;
					if (pAffix != 0) {
						const double ResponsibilityForThisAffixListing =
							double(ssAffix.GetLength()) * base2log(26) *
							GetNumberOfStems() /
							(double(GetNumberOfStems()) +
								pAffix->GetUseCount());
						const double LengthOfPointerToThisAffix =
							LogTotalNumberOfAnalyzedWords -
							base2log(pAffix->GetUseCount() +
								GetNumberOfStems());

						TotalResponsibilityForAffixListings +=
							ResponsibilityForThisAffixListing;
						LengthOfPointersToAllAffixesOfSig +=
							LengthOfPointerToThisAffix;

						sum = ResponsibilityForThisAffixListing +
							LengthOfPointerToThisAffix;

						if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
							StartTableRow <<
								TableData(ssAffix) <<
								TableData(pAffix->GetUseCount()) <<
								TableData(GetNumberOfStems() +
									pAffix->GetUseCount()) <<
								TableData(LengthOfPointerToThisAffix) <<
								TableData(ResponsibilityForThisAffixListing) <<
								TableData(sum) <<
							EndTableRow;
					} else {
						// new affix
						const double ResponsibilityForThisAffixListing =
							double(ssAffix.GetLength()) * base2log(26);
						const double LengthOfPointerToThisAffix =
							LogTotalNumberOfAnalyzedWords -
							base2log(GetNumberOfStems());

						LengthOfPointersToAllAffixesOfSig +=
							LengthOfPointerToThisAffix;
						TotalResponsibilityForAffixListings +=
							ResponsibilityForThisAffixListing;
						sum = ResponsibilityForThisAffixListing +
							LengthOfPointerToThisAffix;

						if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
							StartTableRow <<
								TableData(ssAffix) <<
								// use count = 0
								TableData("0") <<
								TableData(GetNumberOfStems()) <<
								TableData(LengthOfPointerToThisAffix) <<
								TableData(ResponsibilityForThisAffixListing) <<
								TableData(sum) <<
							EndTableRow;
					}
					ThisNewSigDL += sum;
				}
				if (Lexicon->LogFileOn())
					*Lexicon->GetLogFile() <<
					StartTableRow <<
						TableData("Total") <<
						TableData() <<
						TableData() <<
						TableData(LengthOfPointersToAllAffixesOfSig) <<
						TableData(TotalResponsibilityForAffixListings) <<
						TableData(ThisNewSigDL) <<
					EndTableRow;
			}

			// Length of the pointers to the sig from its stems:
			double SavingsBecauseStemAlreadyExisted = 0.0;
			double StemPointersToThisSig;
			IterateThroughStems(NumberOfLettersShifted,
				Lexicon,
				pPiece,
				TotalDecreaseInDLDueToShorterStems,
				LogTotalNumberOfAnalyzedWords,
				StemPointersToThisSig,
				SavingsBecauseStemAlreadyExisted,
				analyzingSuffixes);
			const double ThisNewSigDL =
				LengthOfPointersToAllAffixesOfSig +
				TotalResponsibilityForAffixListings +
				StemPointersToThisSig +
				-SavingsBecauseStemAlreadyExisted +
				-TotalDecreaseInDLDueToShorterStems;
			AllNewSigsAnalysisDL += ThisNewSigDL;

			if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
				StartTable <<
				StartTableRow <<
					TableData("Part 1:  Length of pointer to affixes:") <<
					TableData(LengthOfPointersToAllAffixesOfSig) <<
				EndTableRow <<
				StartTableRow <<
					TableData("Part 2: Prorated responsibility for phonology of affixes: ") <<
					TableData(TotalResponsibilityForAffixListings) <<
				EndTableRow <<
				StartTableRow <<
					TableData("Part 3: Stem pointers to this sig:") <<
					TableData(StemPointersToThisSig) <<
				EndTableRow <<
				StartTableRow <<
					TableData("Length of 1 pointer to this sig: ") <<
					TableData(LengthOfPointerToThisSig) <<
				EndTableRow <<
				StartTableRow <<
					TableData("Part 4: Total savings from stems that had already existed:") <<
					TableData(SavingsBecauseStemAlreadyExisted) <<
				EndTableRow <<
				StartTableRow <<
					TableData("Part 5: Total decrease in DL due to shorter stems:") <<
					TableData(TotalDecreaseInDLDueToShorterStems) <<
				EndTableRow <<
				StartTableRow <<
					TableData("Total DL: ") <<
					TableData(ThisNewSigDL) <<
				EndTableRow <<
				EndTable;
		}
		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			"<br /><br />" <<
			QString("If we add %1 letters, total TD is %2")
			.arg(NumberOfLettersShifted).arg(AllNewSigsAnalysisDL) <<
			endl << "******" << endl <<
			"<br />";

		if (AllNewSigsAnalysisDL < WinningDL) {
			WinningDL = AllNewSigsAnalysisDL;
			WinningLengthOfStemToShift = NumberOfLettersShifted;
			WinningSig = Sig;
		}
	}

	if (WinningDL != CurrentDL) {
		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			SmallTitle(QString(
			"Change signature from \"%1\" to \"%2\"")
			.arg(Display(), WinningSig.Display('.'))) <<
			"<hr />";
		Lexicon->AddToScreen(
			QString("%1 >> %2")
			.arg(Display('.'), WinningSig.Display('.')));
		return WinningLengthOfStemToShift;
	} else {
		if (Lexicon->LogFileOn()) *Lexicon->GetLogFile() <<
			SmallTitle(QString(
			"%1: Conclusion: Keep original signature.")
			.arg(Display())) <<
			"<hr />";
		return 0;
	}
}

void CSignature::IterateThroughStems(   int           NumberOfLettersShifted, 
									    CMiniLexicon* Lexicon, 
										CLParse*      pPiece,
										double&       TotalDecreaseInDLDueToShorterStems,
										double        LogTotalNumberOfAnalyzedWords,
										double&       StemPointersToThisSig,
										double& 	  SavingsBecauseStemAlreadyExisted,
										bool          analyzingSuffixes)
{



CStem*					pStem;
int					HowManyStemsForThisSig				 = 0; //check that
int					NumberOfShortenedStemsThatPreExisted = 0;
double					ThisSavingBecauseStemAlreadyExisted  = 0;
double					DecreaseInDLDueToShorterStems		 = 0;
double					LengthOfPointerToThisSig 			 = 0;
CSS					ssNewStem;

                                        TotalDecreaseInDLDueToShorterStems	 = 0;
                                        SavingsBecauseStemAlreadyExisted 	 = 0;
	if ( Lexicon->LogFileOn() )					 			
	{
		 *Lexicon->GetLogFile() << 
			"<br> We now shift the piece " <<pPiece->Display() << "<br>" <<
			StartTable <<
				StartTableRow <<
					MakeTableHeader("Current stem" ) <<
					MakeTableHeader(" Proposed stem" ) <<
					MakeTableHeader(" Savings from preexisting stem" )<<
				EndTableRow; 
	}
			

        for (int z = 0; z < m_StemPtrList->size(); z++)
        {
            pStem = m_StemPtrList->at(z);
            ThisSavingBecauseStemAlreadyExisted =0;
            int StemLength = pStem->GetKeyLength();
            ssNewStem = pStem->GetKey().Left(
            StemLength - NumberOfLettersShifted);
		
            if ( analyzingSuffixes ) // Suffixes
            {
                if ( pStem->GetKey().Right(NumberOfLettersShifted).Display() == pPiece->Display() )
                    {
				HowManyStemsForThisSig++;
				if (Lexicon->LogFileOn())
				{ *Lexicon->GetLogFile() << 
					StartTableRow <<
						TableData(pStem) <<
						TableData (ssNewStem);
				}
                    }
			else
			{
				continue;
				{ *Lexicon->GetLogFile() <<  
					StartTableRow <<
						TableData (pStem) <<
						TableData (ssNewStem) <<
					EndTableRow;
 				}
			}
			ssNewStem = pStem->GetKey().Left( pStem->GetKeyLength() - NumberOfLettersShifted );
			}
		else // Prefixes
		{
			if ( pStem->GetKey().Left(NumberOfLettersShifted).Display() == pPiece->Display() )
			{
				HowManyStemsForThisSig++;
			}
			else
			{
				continue;
			}
			ssNewStem = pStem->GetKey().Right( pStem->GetKeyLength() - NumberOfLettersShifted );
		}

 				
					
		if ( Lexicon->GetStems()->Contains( ssNewStem )  ||  // ** Was: "GetStems_Suffixed
			 Lexicon->GetWords()->Contains( ssNewStem )      )
		{
			NumberOfShortenedStemsThatPreExisted ++;
			ThisSavingBecauseStemAlreadyExisted = ssNewStem.GetLength() * base2log (26);
			SavingsBecauseStemAlreadyExisted += ThisSavingBecauseStemAlreadyExisted;	
					
				// ** Add the cost of having a pointer to the stem ******

		}
						
		if ( Lexicon->LogFileOn()  && 
			   ( pStem->GetKey().Right(NumberOfLettersShifted).Display() == pPiece->Display() ) )
		{	
			 
 						if ( ThisSavingBecauseStemAlreadyExisted > 0)
						{
							*Lexicon->GetLogFile() <<
								"<td>" << ThisSavingBecauseStemAlreadyExisted << 
								 "</td></tr>";
						} else
						{
							*Lexicon->GetLogFile() <<
								"<td>" << "none (did not exist)" << 
								 "</td></tr>";
						}
				}

			}

			DecreaseInDLDueToShorterStems = ( HowManyStemsForThisSig - NumberOfShortenedStemsThatPreExisted ) * 
											NumberOfLettersShifted * base2log (26);
			TotalDecreaseInDLDueToShorterStems += DecreaseInDLDueToShorterStems ;

		
			LengthOfPointerToThisSig = LogTotalNumberOfAnalyzedWords - base2log ( Size() * HowManyStemsForThisSig ) ;			
			StemPointersToThisSig	  =  HowManyStemsForThisSig * ( LengthOfPointerToThisSig ) ;
			if ( Lexicon->LogFileOn() )					 			
			{
				 *Lexicon->GetLogFile() << // FILL THIS IN -- 
 					
					 StartTable							<<
						 StartTableRow							<<
							MakeTableHeader("Current stem")		<<
							MakeTableHeader("Proposed stem")		<<
							MakeTableHeader("Savings from preexisting stem")			<<
						EndTableRow;
			}


}

bool CSignature::IsValid()
//  tests that pieces of the signature are all non-null
{
  for (int i = 1; i <= m_PieceCount; i++) {
    if ( GetPiece(i).GetLength() < 1 ) {
      return FALSE;
    }
  }

  return TRUE;
}







void CSignature::DetachStem( CStem* pStem, eDetachment_Parameter Parameter )
{
	if( !m_StemPtrList->isEmpty() &&
                m_StemPtrList->indexOf( pStem ) >= 0 &&
		m_StemPtrList->remove( pStem ) )
	{
		IncrementCorpusCount( -1 * pStem->GetCorpusCount() );

		if( Parameter != eDo_Not_Call_Words )
		{
                    CStem *pWord;
                    for (int z = 0; z < pStem->GetWordPtrList()->size(); z++)
                    {       pWord = pStem->GetWordPtrList()->at(z);
                            m_WordPtrList->removeOne( pWord );
                    }
		}
	}
}


void CSignature::DetachWord( CStem* pWord, eDetachment_Parameter Parameter )
{
        if( !m_WordPtrList->empty() && m_WordPtrList->indexOf( pWord ) >= 0 )
                m_WordPtrList->removeOne(pWord); //
	
	if ( Parameter == eDo_Not_Call_Words )
	{
	// TODO: ?? -cs-
	}
	else
	{
	// TODO: ?? -cs-
	}
}

void CSignature::TakeAllStems(CSignature* source)
{
        QList<CStem*>& source_stems = *source->GetStemPtrList();

	foreach (CStem* stem, source_stems) {
		stem->SetSuffixList(this);
		m_StemPtrList->append(stem);
		IncrementCorpusCount(stem->GetCorpusCount());
	}

	// Remove items from source.
        //Q_ASSERT(!source_stems.autoDelete());
	source_stems.clear();

	// XXX. Decrement source corpus count in turn?
	// Hard to tell, since there are no call sites.
}

void CSignature::AddWord (CStem* pWord)
{

  m_WordPtrList->append (pWord);
  IncrementCorpusCount (pWord->GetCorpusCount() );




}


CParse CSignature::CreateADeletingSignature( CParse& Deletee, CMiniLexicon* Lexicon )
{
  CStringSurrogate  ssSuffix;


  CParse        PSuffix,
            NewSig,
            Suffix;
  CSuffix*      pSuffix;
  QString        Null = "NULL", lt_brak = "<", rt_brak = "<";


  Q_ASSERT (Deletee.Size() == 1);

  for (int n = 1; n <= Size(); n++)
  {
    ssSuffix = GetPiece(n);
    if(NewSig.GetSortStyle() != eAlphabetized ) NewSig.Alphabetize();
    if ( ssSuffix == Deletee )
    {
      NewSig.Append ( CStringSurrogate(Null.unicode(),0,Null.length() ) );
    }
    else
    {
      PSuffix = CStringSurrogate(lt_brak.unicode(),0,1);
      PSuffix += Deletee;
      PSuffix += CStringSurrogate(rt_brak.unicode(),0,1);
      PSuffix.ClearParseStructure();
      PSuffix += ssSuffix;
      NewSig.Append ( PSuffix.GetKey() );

      pSuffix = *Lexicon->GetSuffixes() << PSuffix;

      QString line = "<" + Deletee.Display() + ">" + ssSuffix.Display();
      Suffix  = CStringSurrogate( line.unicode(),0,line.length());

      NewSig.Append (Suffix.GetKey());
//      Lexicon->SetSuffixTranslation(this, ssSuffix, Suffix);

    }
  }
  return NewSig;
}


bool CSignature::RemoveStem(CStem * pStem )
{
  return m_StemPtrList->remove( pStem );
}



bool CSignature::RemoveWord(CStem* pWord)
{
  return m_WordPtrList->remove( pWord );
}

// copy out affixes, with null affix replaced with "NULL",
// possibly with deletees marked with angle brackets
CSignature& CSignature::Express(CSignature& Output, bool bDisplayDeletees)
{
	CSuffixCollection* Suffixes = 0;
	CPrefixCollection* Prefixes = 0;
	if (!is_initial(GetAffixLocation()))
		Suffixes = GetSignatureCollection()->GetMySuffixes();
	else
		Prefixes = GetSignatureCollection()->GetMyPrefixes();

	Output.ClearParse();

	for (int i = 1; i <= Size(); ++i) {
		CStringSurrogate affix_text = GetPiece(i);

		if (affix_text.IsNULL()) {
			Output.Append(TheStringNULL);
			continue;
		}
		if (!is_initial(m_AffixLocation)) {
			CSuffix* suffix = *Suffixes ^= affix_text;
			Q_ASSERT(suffix != 0);

			CParse Temp;
			Output.Append(
				suffix->Express(Temp, bDisplayDeletees));
		} else {
			CPrefix* prefix = *Prefixes ^= affix_text;
			Q_ASSERT(prefix != 0);

			CParse Temp;
			Output.Append(
				prefix->Express(Temp, bDisplayDeletees));
		}
	}
	return Output;
}

/// concatenate affixes, separated by -.
QString CSignature::Express(bool bDisplayDeletees)
{
	CSuffixCollection* Suffixes = 0;
	CPrefixCollection* Prefixes = 0;
	if (!is_initial(GetAffixLocation()))
		Suffixes = GetSignatureCollection()->GetMySuffixes();
	else
		Prefixes = GetSignatureCollection()->GetMyPrefixes();

	QString Outstring;
	for (int i = 1; i <= Size(); ++i) {
		CStringSurrogate affix_text = GetPiece(i);

		if (affix_text.IsNULL()) {
			if (!Outstring.isEmpty())
				Outstring.append('-');
			Outstring.append(TheStringNULL);
			continue;
		}

		if (is_initial(m_AffixLocation)) {
			CPrefix* prefix = *Prefixes ^= affix_text;
			Q_ASSERT(prefix != 0);
			if (!Outstring.isEmpty())
				Outstring.append('-');

			CParse Temp;
			Outstring.append(prefix->Express(Temp,
				bDisplayDeletees).Display());
		} else {
			CSuffix* suffix = *Suffixes ^= affix_text;
			Q_ASSERT(suffix != 0);
			if (!Outstring.isEmpty())
				Outstring.append('-');

			CParse Temp;
			Outstring.append(suffix->Express(Temp,
				bDisplayDeletees).Display());
		}
	}

	return Outstring;
}

// this should probably be replaced by ComputeDLofModel
/*
double CSignature::ComputeDL( int char_count )
{
	CStem* pStem;
	CAffix* pAffix;

	CStringSurrogate Affix;

	bool CORPUS_BASED_AFFIX_COUNT = m_pMyMini->GetIntParameter( "SignatureDL\\CorpusBasedAffixCount", 0 );
	bool CORPUS_BASED_STEM_COUNT = m_pMyMini->GetIntParameter( "SignatureDL\\CorpusBasedStemCount", 1 );

	double stems_dl = 0.0,
		   affixes_dl = 0.0;

	uint stem_total = 0,
		 affix_total = 0;

	if( CORPUS_BASED_STEM_COUNT )
	{
		for( pStem = m_StemPtrList->first(); pStem; pStem = m_StemPtrList->next() )
		{
			stems_dl += ( (double) -1 ) * base2log( (double) pStem->GetCorpusCount() / (double) m_pMyMini->GetCorpusCount() );
		}
	}
	else
	{
		for( pStem = m_StemPtrList->first(); pStem; pStem = m_StemPtrList->next() )
		{
			stems_dl = ( (double) -1 ) * base2log( (double) pStem->GetWordPtrList()->count() / (double) m_pMyMini->GetWords()->GetCount() );
		} 
	}

	bool analyzedSuffixes = TRUE;
	if( GetAffixLocation() == STEM_INITIAL || GetAffixLocation() == WORD_INITIAL ) analyzedSuffixes = FALSE;

	int i;
	if( !CORPUS_BASED_AFFIX_COUNT )
	{
		for( i = 1; i <= m_PieceCount; i++ )
		{
			Affix = GetPiece(i);

			if( analyzedSuffixes )
			{
				pAffix = *m_pMyMini->GetSuffixes() ^= Affix;
			}
			else
			{
				pAffix = *m_pMyMini->GetPrefixes() ^= Affix;
			}

			if( pAffix ) affix_total += pAffix->GetCorpusCount();
		}
	}

	for( i = 1; i <= m_PieceCount; i++ )
	{
		Affix = GetPiece(i);

		if( analyzedSuffixes )
		{
			pAffix = *m_pMyMini->GetSuffixes() ^= Affix;
		}
		else
		{
			pAffix = *m_pMyMini->GetPrefixes() ^= Affix;
		}

		if( pAffix ) 
		{
			if( CORPUS_BASED_AFFIX_COUNT ) affixes_dl += ( (double) -1 ) * base2log( (double) pAffix->GetCorpusCount() / (double) m_pMyMini->GetCorpusCount() );
			else affixes_dl += ( (double) -1 ) * base2log( (double) pAffix->GetCorpusCount() / (double) affix_total );
		}
	}

	return stems_dl + affixes_dl;
}
*/

//====================================================================//
//				Description Length								      //
//====================================================================//
  double  CSignature::GetDLofMyAffixPointers(	) 
{
	if (m_DLofMyAffixPointers == 0)
        {
           bool analyzedSuffixes = TRUE;
           CSuffix * pSuffix;
           CPrefix* pPrefix;
	   if( GetAffixLocation() == STEM_INITIAL || GetAffixLocation() == WORD_INITIAL ) analyzedSuffixes = FALSE;
	   if (analyzedSuffixes)
           {
               for (int z = 0; z < GetSuffixPtrList()->size(); z++)
               {     pSuffix= GetSuffixPtrList()->at(z);
			m_DLofMyAffixPointers += pSuffix->GetLengthOfPointerToMe ();
                }
	   }
           else
           {
                for (int z  = 0; z < GetPrefixPtrList()->size(); z++)
                {
                    pPrefix= GetPrefixPtrList()->at(z);
                    m_DLofMyAffixPointers += pPrefix->GetLengthOfPointerToMe ();
                }
           }
         }
     return m_DLofMyAffixPointers;
}
double  CSignature::GetDLofMyStemPointers()
{
       if (m_DLofMyStemPointers == 0)
        {
           CStem * pStem;
           for (int z  = 0; z < GetStemPtrList()->size(); z++)
           {
                pStem = GetStemPtrList()->at(z);
                m_DLofMyStemPointers += pStem->GetLengthOfPointerToMe ();
	   }
         }
     return m_DLofMyStemPointers;
}  

double CSignature::ComputeDLofModel(int /* char_count, not used */)
{
	// XXX. take SignatureDL\CorpusBased{Stem,Affix}Count parameters
	// into account

	m_DLofMyStemPointers = GetDLofMyStemPointers();
	m_DLofMyAffixPointers = GetDLofMyAffixPointers();
	return m_DLofMyStemPointers + m_DLofMyAffixPointers;
}

double CSignature::ComputeDLofMyCorpus()
{
	using linguistica::implicit_cast;

	if (m_pMyMini == 0)
		return 0.0;

	m_DLofMyCorpus = 0.0;
	foreach (CStem* pWord, *m_WordPtrList) {
		CStringSurrogate stem_text = pWord->GetStem();
		CStem* stem = *m_pMyMini->GetStems() ^= stem_text;

		CStringSurrogate affix_text = is_initial(m_AffixLocation)
			? pWord->GetPrefix()
			: pWord->GetSuffix();
		if (affix_text.GetLength() == 0)
			affix_text = TheStringNULL;

		CAffix* affix = is_initial(m_AffixLocation)
			? implicit_cast<CAffix*>(
				*m_pMyMini->GetPrefixes() ^= affix_text)
			: implicit_cast<CAffix*>(
				*m_pMyMini->GetSuffixes() ^= affix_text);

		CStem* word = *m_pMyMini->GetWords() ^= pWord;
		const double ThisWordDL =
			stem->GetLengthOfPointerToMe() +
			affix->GetLengthOfPointerToMe();
		m_DLofMyCorpus += word->GetCorpusCount() * ThisWordDL;
	}
	return m_DLofMyCorpus;
}

//the output is a vector of integers, whose length is 
// the number of stems times the number of suffixes. Pass it
// an int pointer that points to NULL; it will delete the memory
// that this function creates.
int* CSignature::GetIndividualCountsForEachStem (int* output )
{
	int i, StemNumber (0);
	int*	temp = NULL; 
	CStem*	pStem;

       if (output) delete output; //if this occurs, it's an error.
	output = new int [GetNumberOfStems() * GetNumberOfAffixes() ];

       for (int z = 0; z < m_StemPtrList->size(); z++)
	{
              pStem = m_StemPtrList->at(z);
		temp = pStem-> GetSuffixCounts( temp );
		for (i = 0; i < GetNumberOfAffixes(); i++)
		{
			output[StemNumber* GetNumberOfAffixes() + i] = temp[i];
		}
		StemNumber++;
		delete temp;
		temp = NULL;
	}
	return output;
}
 

double CSignature::GetSumOfDLofInternalPointers( eMDL_STYLE, eRecomputeStyle  )
{
	int i = 0;
	double		StemTotal = 0, SuffixTotal = 0;
	CStem*		pStem;
	CSuffix*	pSuffix;
        CSS		ssSuffix;
	CSuffixCollection& Suffixes = *m_pMyMini->GetSuffixes();
       for (int z = 0; z < m_StemPtrList->size(); z++)
	{
            pStem = m_StemPtrList->at(z);
            StemTotal += pStem->GetLengthOfPointerToMe_2 ();
	}
	
	for (i = 1; i <= GetNumberOfAffixes(); i++)
	{
		ssSuffix = GetPiece(i);
		pSuffix = Suffixes ^= ssSuffix;
		SuffixTotal += pSuffix->GetLengthOfPointerToMe();
	}
	return StemTotal + SuffixTotal;
}


void CSignature::SetLengthOfPointerToMe(double L)  
{ 
	m_LengthOfPointerToMe = L;
	return;
}


//----------------------------------------------------------//
void CSignature::AppendSatelliteAffix(CParse& suffix)
{

    m_SatelliteAffixes.Append(suffix);
}

// for allomorphy
bool CSignature::Generalizes(CSignature* pSig)
{
	struct not_implemented { };
	throw not_implemented();

	// 1. Check they have the same length; find which one is longer.
	// 2. Go from longest to shortest pieces of the longer signature:
	//    look for unambiguous correspondents in the other signature, and
	//    put those pairs of corresponding affixes in some structure.
	// 3. After unambiguous cases, deal with ambiguous cases, if any exist.
	// 4. Find alignment
	//
	// ed |NULL | NULL | ed  |
	// ing|NULL | NULL | ing |
	// es |e    | NULL |  s  |
	// e  |e    | NULL | NULL|
	//
	//
	// ed |e    | <e>  | ed  |
	// ing|e    | <e>  | ing |
	// es |e    | NULL |  s  |
	// e  |e    | NULL | NULL|
	//
	//
	// ien     |ien  | NULL | NULL  |
	// ienne   |ienn | NULL | e     |
	// iens    |ien  | NULL |  s    |
	// iennes  |ienn | NULL | es    |
	//
	// ien     |ien  | NULL | NULL  |
	// ienne   |ien  | n    | e     |
	// iens    |ien  | NULL |  s    |
	// iennes  |ien  | n    | es    |

	CSignature* LongerSig, *ShorterSig;

	struct Row {
	    QString LongAffix;
	    QString Extension;
	    QString Operation;
	    QString ShortAffix;
	};

	if (Size() != pSig->Size())
		return false;

	const int dif = GetKeyLength() - pSig->GetKeyLength();
	if (dif > 0) {
		LongerSig = this; ShorterSig = pSig;
	} else if (dif == 0) {
		return false;
	} else {
		LongerSig = pSig; ShorterSig = this;
	}

	const int MAXAFFIXSIZE = 10;

	QStringList ShorterSigPieces;
	{

		// Copy the affixes of ShorterSig,
		// from shortest to longest
		// onto the list ShorterSigPieces.
		if (ShorterSig->ContainsNULL())
			ShorterSigPieces.append(TheStringNULL);
		for (int m = 1; m < MAXAFFIXSIZE &&
				ShorterSigPieces.count() < ShorterSig->Size();
				++m) {
			// XXX. this test makes no sense
			if (ShorterSig->ThisPieceLength(m) == m)
				ShorterSigPieces.prepend(
					ShorterSig->GetPiece(m).Display());
		}
		Q_ASSERT(ShorterSigPieces.count() == ShorterSig->Size());
	}

	QStringList LongerSigPieces;
	{
		// Copy the affixes of LongerSig,
		// from shortest to longest
		// onto the list LongerSigPieces.
		if (LongerSig->ContainsNULL())
			LongerSigPieces.append(TheStringNULL);
		for (int m = 1; m < MAXAFFIXSIZE &&
				LongerSigPieces.count() < LongerSig->Size();
				++m)
			if (LongerSig->ThisPieceLength(m) == m)
				LongerSigPieces.prepend(
					LongerSig->GetPiece(m).Display());
		Q_ASSERT(LongerSigPieces.count() == LongerSig->Size());
	}

        CStringSurrogate ssIng, ssTing;
	foreach (QString shortersig_piece, ShorterSigPieces) {
		// example: "ing"
		CStringSurrogate short_affix(shortersig_piece);
		bool match = false;
		foreach (QString longersig_piece, LongerSigPieces) {
			// example "ting"
			CStringSurrogate long_affix(longersig_piece);
			if (long_affix.IsNULL())
				continue;
			if (short_affix != long_affix.Right(
					short_affix.GetLength()))
				continue;
			bool unambiguous_match = !match;
			if (!match)
				match = true;

			if (!unambiguous_match)
				continue;

			Row ThisRow;
			ThisRow.LongAffix =
				long_affix.Display();
			ThisRow.ShortAffix =
				short_affix.Display();
			ThisRow.Extension = long_affix.Left(
				long_affix.GetLength() -
				short_affix.GetLength())
				.Display();
			// XXX. use ThisRow...
			static_cast<void>(ThisRow);
		}
	}
	return false;
}
