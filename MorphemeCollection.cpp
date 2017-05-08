// Implementation of CMorphemeCollection methods
// Copyright © 2009 The University of Chicago
#include "MorphemeCollection.h"

#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "MiniLexicon.h"
#include "Morpheme.h"

CMorphemeCollection::CMorphemeCollection()
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL;
	m_TotalDLSavings = 0;
}

CMorphemeCollection::CMorphemeCollection( CMiniLexicon* Lex )
{
	m_pMiniLex = Lex; 
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
	m_TotalDLSavings = 0;
}
  
CMorphemeCollection::~CMorphemeCollection()
{


}
CMorpheme* CMorphemeCollection::operator << (CStringSurrogate ssMorpheme)
{
  CMorpheme* pMorpheme = TCollection<CMorpheme>::AddToCollection (ssMorpheme);
  return pMorpheme;
}

/* -colin-
CMorpheme* CMorphemeCollection::operator << (char* szWord)
{
  CMorpheme* pMorpheme = TCollection<CMorpheme>::operator<< (szWord);
  return pMorpheme;

}
CMorpheme* CMorphemeCollection::operator << (CMorpheme& Morpheme)
{


  CMorpheme*      pMorpheme;
  CNode*        pNode;
  int          Result;

  pNode        = Insert (Morpheme.GetKeyPointer(), &Result);

  if ( Result == 1)
  {
    pMorpheme = new CMorpheme(Morpheme);
    pNode->SetPointer (pMorpheme);
    pMorpheme->SetIndex ( GetCount() - 1 );
    pMorpheme->SetDLSavings( Morpheme.GetDLSavings() );
    pMorpheme->SetDLImprovementFromSuffixes ( Morpheme.GetDLImprovementFromSuffixes() );
    pMorpheme->SetCorpusCount ( Morpheme.GetCorpusCount() );

  }
  else
  {
    pMorpheme =(CMorpheme*) pNode->Get_T_Pointer();
    pMorpheme->SetDLSavings( pMorpheme->GetDLSavings() + Morpheme.GetDLSavings()   );
    pMorpheme->SetDLImprovementFromSuffixes (  pMorpheme->GetDLImprovementFromSuffixes() +
                          Morpheme.GetDLImprovementFromSuffixes()    );
    pMorpheme->SetCorpusCount ( pMorpheme->GetCorpusCount() + Morpheme.GetCorpusCount() );

  }

  IncrementCorpusCount(1);


  m_SortValidFlag      = FALSE;
  m_HashHasChangedFlag  = TRUE;

  m_TotalDLSavings += Morpheme.GetDLSavings() + Morpheme.GetDLImprovementFromSuffixes();
  pMorpheme->CopySuffixList ( Morpheme );

  return pMorpheme;


}

void CMorphemeCollection::operator<< (CMorphemeCollection& CMC)
{
  CMorpheme* pMorpheme;
  for (int i = 0; i < CMC.GetCount(); i++)
  {
    pMorpheme = *this << *CMC.GetAt(i);

  }

}



void CMorphemeCollection::Display(CMyCollectionView* pView)
{
  CMorpheme* pMorpheme;
  int  col = 1;
  CListCtrl& List = pView->GetListCtrl();
  //        Clean it out first
  for (int i = 0; i < pView->GetNumberOfColumns(); i++)
  {
    List.DeleteColumn(0);
  }
  List.DeleteAllItems();

  m_MemberName = "Morpheme";

  //    Add Column headers
  pView->GetListCtrl().InsertColumn(0, m_MemberName, LVCFMT_LEFT, 100);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "Inverse log freq", LVCFMT_RIGHT, 100);
  pView->IncrementNumberOfColumns();


  List.InsertColumn(col++, "Morpheme count", LVCFMT_RIGHT, 100);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "Corpus count", LVCFMT_RIGHT, 100);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "PF", LVCFMT_RIGHT, 50);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "SF", LVCFMT_RIGHT, 50);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "Goodness", LVCFMT_RIGHT, 70);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "Description Length savings", LVCFMT_RIGHT, 150);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "Frequency", LVCFMT_RIGHT, 100);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(col++, "Followed by:", LVCFMT_RIGHT, 180);
  pView->IncrementNumberOfColumns();
-colin- */
/*
  List.InsertColumn(3, "Other word letters", LVCFMT_RIGHT, 110);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(4, "Suffix letters", LVCFMT_RIGHT, 120);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(5, "Signatures", LVCFMT_RIGHT, 80);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(6, "Corpus:", LVCFMT_RIGHT, 90);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(7, "Unanalyzed words", LVCFMT_RIGHT, 120);
  pView->IncrementNumberOfColumns();

  List.InsertColumn(8, "Analyzed words", LVCFMT_RIGHT, 120);
  pView->IncrementNumberOfColumns();

*/
/* -colin-
  if (m_SortValidFlag == FALSE)
  {
    Sort(DL_SAVINGS);
  }



  for (i = 0; i < (int) GetCount(); i++)
  {
    pMorpheme = GetAtSort(i);
    pMorpheme->Display( &List, i );

  }

}

void operator<< (ofstream& out, CMorphemeCollection& MC)
{
  for (int i = 0; i < MC.GetCount(); i++)
  out << MC.GetAt(i)->SpellOut() << " " << MC.GetAt(i)->GetDLSavings() << " ";

}

void CMorphemeCollection::Empty()
{

  m_TotalDLSavings = 0;
  TCollection<CMorpheme>::Empty();
}

void CMorphemeCollection::ClearAllMorphemeCounts()
{
  for (int  i = 0; i < GetCount(); i++)
  {
    GetAt(i)->SetMorphemeCount (0);
  }
}

  -colin- */
void CMorphemeCollection::OutputMorphemes (QString& FileName)
{
	Q_ASSERT(!FileName.isEmpty());

  CMorpheme*      pMorpheme;
  QFile        file( FileName );

  if( file.open( QIODevice::WriteOnly ) )
  {
    Q3TextStream outf( &file );
    outf.setEncoding ( Q3TextStream::Unicode );

    outf.setf(2);
    outf << GetCount();

    Sort( KEY );
    for (int i = 0; i< (int)GetCount(); i++)
    {
      pMorpheme = GetAtSort(i);

      outf << endl;
      outf.width(20);
      outf.width(20);
      outf.width(20);
      outf.width(20);
      outf << pMorpheme->Display( 0, m_pMiniLex->GetOutFilter() );
      outf << pMorpheme->GetMorphemeCount();
      outf << pMorpheme->GetFrequency();
      outf << pMorpheme->GetSuffixList()->Display( 0, m_pMiniLex->GetOutFilter() );
    }

    file.close();
  }
}
