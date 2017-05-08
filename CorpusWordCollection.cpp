// Implementation of CCorpusWordCollection methods
// Copyright © 2009 The University of Chicago
#include "CorpusWordCollection.h"

#include "CorpusWord.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCorpusWordCollection::CCorpusWordCollection(CLexicon* Lex)
{
	m_pMiniLex = NULL;
	m_pLexicon = Lex;
}


CCorpusWordCollection::CCorpusWordCollection( )
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL;
}


CCorpusWordCollection::~CCorpusWordCollection()
{

}


void CCorpusWordCollection::SetUpdateFlags( bool b )
{
	for( int i = 0; i < GetCount(); i++ )
	{
		GetAt(i)->SetUpdated( b );
	}
}
