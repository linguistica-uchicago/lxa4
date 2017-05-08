// Implementation of CTerminalRuleCollection methods
// Copyright © 2009 The University of Chicago
#include "TerminalRuleCollection.h"

#include <QList>
#include <QString>
#include "StringSurrogate.h"
#include "GrammarRule.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTerminalRuleCollection::CTerminalRuleCollection()
{}


CTerminalRuleCollection::~CTerminalRuleCollection()
{
	// TODO : This should delete it's own rules if flag set
}


CTerminalRule*	CTerminalRuleCollection::operator<< ( CTerminalRule* pRule )
{
	CNode*            pTerminal;
	int               Result;
	QString           Key;
	CStringSurrogate  cssKey;

	cssKey = pRule->GetKey();
	pTerminal = Insert( cssKey, &Result );
	if( Result == 1 )
	{
		pTerminal->SetPointer( pRule );
	}
	else
	{
		Q_ASSERT( FALSE && "Rule should not already exist, ignoring it." );
	}

	m_SortValidFlag      = FALSE;
	m_HashHasChangedFlag  = TRUE;

	return pRule;
}


void CTerminalRuleCollection::FindSubstrings( CStringSurrogate& string, Q3PtrList<CTerminalRule>& substrings )
{
	CTerminalRule* substring;
	CStringSurrogate ss = string;
	int step;

	CNode* pNode = m_Root,
		 * qNode = pNode->FindLetter( ss[0] );

	while( qNode )
	{
		substring = (CTerminalRule*) qNode->Get_T_Pointer();
		if( substring ) substrings.append( substring );

		step = qNode->m_BreakPoint - pNode->m_BreakPoint;
		ss = ss.Mid( step );

		pNode = qNode;
		qNode = pNode->FindLetter( ss[0] );
	}
}


int  CTerminalRuleCollection::GetShortest()
{
	Sort( LENGTH );
	CTerminalRule* pTR = GetAtSort( GetCount() - 1 );
	return pTR->GetKeyLength();


/*
	// Breadth first search in trie

	int shortest = -1, depth;
	int* pInt;

	QPtrQueue<CNode>	nodeQ;
	QPtrQueue<int>		depthQ;

	CNode* pNode;

	nodeQ.enqueue( m_Root );
	depthQ.enqueue( new int( 0 ) );
	pNode = nodeQ.dequeue();
	pInt = depthQ.dequeue();
	depth = *pInt;
	delete pInt;
	
	while( pNode )
	{
		if( pNode->m_ExistenceFlag )
		{
			if( shortest < 0 || shortest > ( (CTerminalRule*)pNode->Get_T_Pointer() )->GetKeyLength() )
			{
				shortest = ( (CTerminalRule*)pNode->Get_T_Pointer() )->GetKeyLength();
			}
			if( depth >= shortest ) 
			{
				depthQ.setAutoDelete( TRUE );
				return shortest;
			}
		}

		int numberOfBranches = pNode->GetNumberOfBranches();
		for( int i = 0; i < numberOfBranches; i++ )
		{
			nodeQ.enqueue( pNode->GetBranch(i) );
			depthQ.enqueue( new int( depth+1 ) );
		}

		pNode = nodeQ.dequeue();
		pInt = depthQ.dequeue();
		if( pInt ) depth = *pInt;
		else depth = -1;
		delete pInt;
	}

	depthQ.setAutoDelete( TRUE );
	return -1;
*/
}
