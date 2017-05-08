// Implementation of CLinkerCollection methods
// Copyright © 2009 The University of Chicago
#include "LinkerCollection.h"

#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Linker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinkerCollection::CLinkerCollection(CMiniLexicon* Lex)
{
	// do the creation of TCollection with ptr to Lexicon and name of class
	m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon(); 
}

CLinkerCollection::CLinkerCollection(CLexicon* Lex)
{
	// do the creation of TCollection with ptr to Lexicon and name of class
	m_pMiniLex = NULL;
	m_pLexicon = Lex; 
}


CLinkerCollection::CLinkerCollection()
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL; 
}


CLinkerCollection::~CLinkerCollection()
{}


void CLinkerCollection::ListDisplay(Q3ListView* pView, StringToString* filter)
{
	CLinker*      pLinker;
	pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);
  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  //    Add Column headers
  pView->addColumn( "Linkers" );
  pView->addColumn( "Corpus Count" );
  pView->addColumn( "Use Count" );
  pView->addColumn( "Compounds" );

  if( m_pLexicon ) m_pLexicon->GetDocument()->setStatusBar1( "Creating linker list for display" );
  if( m_pLexicon ) m_pLexicon->GetDocument()->BeginCountDown();


  if (m_SortValidFlag == FALSE)
  {
    Sort(COUNT);
  }

  for (int i = 0; i < (int)GetCount(); i++)
  {
    pLinker = GetAtSort(i);
    pLinker->ListDisplay( pView, filter );

    if( m_pLexicon ) m_pLexicon->GetDocument()->CountDownOnStatusBar(i, GetCount());
  }

  if( m_pLexicon ) m_pLexicon->GetDocument()->setStatusBar1( "" );
  if( m_pLexicon ) m_pLexicon->GetDocument()->EndCountDown();
}


