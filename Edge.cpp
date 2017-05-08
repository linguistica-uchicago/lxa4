// Implementation of CEdge methods
// Copyright © 2009 The University of Chicago
#include "Edge.h"

#include "Config.h"
#include <Q3ValueList>
#include "GrammarRule.h"
#include "StringFunc.h"
#include "Typedefs.h"

namespace {
	bool IsTerminalCategory(CStringSurrogate ssPiece)
	{
		return !(ssPiece.GetLength() > 1 ||
				ssPiece.GetLength() <= 0);
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdge::CEdge()
{
	m_InFinalParse = FALSE;
	m_Parent = NULL;
	m_MinimumLength = 20000; // Just needs to be a large number
	m_Depth = 0;
}

CEdge::~CEdge()
{
	/*CEdge* pEdge;
	for( pEdge = m_Daughters.first(); pEdge; pEdge = m_Daughters.next() )
	{
		if( pEdge ) 
		{	
			delete pEdge;
		}
	}*/
}


CEdge::CEdge( CGrammarRule* rule, CParse* word, int i )
{
	Append( rule->GetLHS() );
	if( rule->GetRHS().GetKey()[0] == GRAMMAR_RULE_WILD_CARD )
	{
		QString rightSide;
		for( int j = 0; j < rule->GetRHS().GetKeyLength(); j++ )
		{
			if( rule->GetRHS().GetKey()[j] == GRAMMAR_RULE_WILD_CARD )
			{
				rightSide = word->GetKey()[ j + i - 1 ];
				CSS ssRHS( rightSide );
				Append( ssRHS );
			}
		}
	}
	else Append( rule->GetRHS() );

	m_Start				= i;
	m_End				= i;
	m_DotLocation	= 2; // that's where a rule always starts
	m_InFinalParse = FALSE;
	m_Parent = NULL;
	m_MinimumLength = 20000; // Just needs to be a large number
	m_Depth = 0;
}


CEdge::CEdge( CEdge& Edge ) : CParse( Edge )
{
	m_Start         = Edge.GetStart();
	m_DotLocation   = Edge.GetDotLocation();
	m_InFinalParse  = FALSE;
	m_Parent        = Edge.m_Parent;
	m_MinimumLength = Edge.m_MinimumLength;
	m_Depth         = Edge.getDepth();

	CEdge *pEdge;
    for( pEdge      = Edge.m_Daughters.first(); pEdge; pEdge = Edge.m_Daughters.next() )
	{
        m_Daughters.append( pEdge );
	}
}


CEdge::CEdge( CParse& Cat, QString Key, int i, int End ) // Used in Scanning
{
	Append( Cat );
	Append( Key );
	m_Start = i ;
	m_End = End;
	m_DotLocation = 3;
	m_InFinalParse = FALSE;
	m_Parent = NULL;
	m_MinimumLength = 20000; // Just needs to be a large number
	m_Depth = 0;
}


CSS CEdge::GetNextNode()
{
	return GetPiece( m_DotLocation );
}


int CEdge::GetStart() { return m_Start; }


void CEdge::SetDotLocation (int n) { m_DotLocation = n; }


int  CEdge::GetDotLocation() { return m_DotLocation; }


void CEdge::SetStart( int n ) { m_Start = n; }


QString CEdge::LHS()
{
	return GetPiece(1).Display();
}


QString CEdge::RHS()
{
	return ThisPieceAndWhatFollows(2).Display();
}


CStringSurrogate CEdge::GetLHS()
{ 
	return GetPiece(1);
} 


bool CEdge::Complete ()
{
	if( m_DotLocation > Size() ) { return TRUE; }
	return FALSE;
}	


void CEdge::MoveDotToTheRight()
{
	Q_ASSERT( m_DotLocation <= m_PieceCount + 1 ) ;// check that
	m_DotLocation++;
}


bool CEdge::NextNodeIsNonterminal()
{
	CSS ssPiece = GetPiece( m_DotLocation );
	return !IsTerminalCategory( ssPiece );
}


bool CEdge::NextNodeIsTerminal() 
{
	return IsTerminalCategory( GetPiece( m_DotLocation ) );
}


bool CEdge::Incomplete()
{
	if( m_DotLocation == Size() + 1 ) { return FALSE; }
	else { return TRUE; }
}


QString CEdge::Display()
{
	QString String = GetPiece(1).Display() + " ->";	
	int i;
	for( i = 2; i <= m_PieceCount; i++ )
	{		
		if( i == m_DotLocation ) 
			String += "*";
		else
			String += " ";
		String += GetPiece(i).Display();			
	}
	if( m_DotLocation == i ) 
		String += "*";

	return String;	
}


void CEdge::GetParse( CParse* parse, bool clearParse )
{
	if( clearParse ) parse->ClearParse();

	QString rhs = RHS();
	CStringSurrogate rightSide( rhs );

	if( m_Daughters.isEmpty() )
	{
		parse->Append(rightSide);
	}
	else
	{
		CEdge* daughter;
		for( daughter = m_Daughters.first(); daughter; daughter = m_Daughters.next() )
		{
			daughter->GetParse( parse, FALSE );
		}
	}
}


QRect CEdge::drawTree( Q3Canvas* canvas, int left, int depth, StringToString* filter )
{
	int X_PADDING = 10;
	int Y_SPACING = 30;

//	int X_MARGIN = 10; unused variable 'X_Margin'
	int Y_MARGIN = 10;

	//================================================

	Q3CanvasItem* edge = new Q3CanvasText( LHS(), canvas ),
			   * leaf = NULL;
	Q3CanvasLine* line;

	m_CanvasItems.clear();
	m_CanvasItems.append( edge );

	int myLeft = left,
		myTop = ( depth * Y_SPACING ) + Y_MARGIN,
		myCenterX,
		myBottom,
		childCenterX,
		childLeft,
		childTop,
		shiftAmount;

	Q3ValueList<QRect> daughterBoundingRectangles;
	Q3ValueList<QRect>::iterator it;

	QRect myBoundingRect, rectangle;
	myBoundingRect.setTop( myTop );
	myBoundingRect.setLeft( myLeft );
	myBoundingRect.setBottom( myTop + edge->boundingRect().height() - 1 );
	myBoundingRect.setRight( myLeft + edge->boundingRect().width() - 1 );
	
	int count = 0;
//	bool first = TRUE; unused variable 'first'

	CEdge* daughter;
	for( daughter = m_Daughters.first(); daughter; daughter = m_Daughters.next() )
	{
		daughterBoundingRectangles.append( rectangle );

		daughterBoundingRectangles[count] = daughter->drawTree( canvas, left, depth + 1, filter );

		// Adjust left position based on bounding rectangle of last daughter
		left = daughterBoundingRectangles[count].right() + X_PADDING;

		count++;
	}

	if( m_Daughters.isEmpty() )
	{
		// Create leaf node
		childLeft = myLeft;
		childTop = ( ( depth + 1 ) * Y_SPACING ) + Y_MARGIN;

		leaf = new Q3CanvasText( Filter( filter, RHS() ), canvas );
		m_CanvasItems.append( leaf );

		leaf->move( childLeft, childTop );
		leaf->show();

		// Adjust my bounding rect
		if( leaf->boundingRect().right() > myBoundingRect.right() ) myBoundingRect.setRight( leaf->boundingRect().right() );
		myBoundingRect.setBottom( leaf->boundingRect().bottom() );
	}
	else
	{
		for( it = daughterBoundingRectangles.begin(); it != daughterBoundingRectangles.end(); ++it )
		{
			// Adjust my bounding rect
			if( (*it).right() > myBoundingRect.right() ) myBoundingRect.setRight( (*it).right() );
			if( (*it).bottom() > myBoundingRect.bottom() ) myBoundingRect.setBottom( (*it).bottom() );
		}
	}
	
	if( myBoundingRect.width() == edge->boundingRect().width() ) 
	{
		// Shift all children to the right
		if( m_Daughters.isEmpty() )
		{
			shiftAmount = int (( myBoundingRect.width() - leaf->boundingRect().width() ) / 2.0);

			leaf->move( leaf->boundingRect().left() + shiftAmount, leaf->boundingRect().top() );
			leaf->show();
		}
		else
		{
			shiftAmount = int (( myBoundingRect.width() - ( daughterBoundingRectangles.last().right() - daughterBoundingRectangles.first().left() ) ) / 2.0);
			
			for( daughter = m_Daughters.first(); daughter; daughter = m_Daughters.next() )
			{
				daughter->shiftTree( canvas, shiftAmount, 0 );
			}

			for( it = daughterBoundingRectangles.begin(); it != daughterBoundingRectangles.end(); ++it )
			{
				// Adjust the bounding rect position
				(*it).setLeft( (*it).left() + shiftAmount );
				(*it).setRight( (*it).right() + shiftAmount );
			}
		}
	}
	else myLeft = ( myBoundingRect.right() - ( myBoundingRect.width() / 2 ) ) - ( edge->boundingRect().width() / 2 );


	if( myLeft < myBoundingRect.left() ) myLeft = myBoundingRect.left();
	edge->move( myLeft, myTop );

	// Draw lines to daughter nodes
	if( m_Daughters.isEmpty() )
	{
		myCenterX = edge->boundingRect().center().x();
		myBottom = edge->boundingRect().bottom();

		childCenterX = leaf->boundingRect().center().x();
		childTop = leaf->boundingRect().top();

		if( myCenterX - childCenterX == 1 || myCenterX - childCenterX == -1 ) myCenterX = childCenterX;

		line = new Q3CanvasLine( canvas );
		line->setPoints( myCenterX, myBottom, childCenterX, childTop );
		line->show();

		m_CanvasItems.append( line );
	}
	else
	{
		Q3ValueList<QRect>::iterator it;
		for( it = daughterBoundingRectangles.begin(); it != daughterBoundingRectangles.end(); ++it )
		{
			myCenterX = edge->boundingRect().center().x();
			myBottom = edge->boundingRect().bottom();

			childCenterX = (*it).center().x();
			childTop = (*it).top();

			if( myCenterX - childCenterX == 1 || myCenterX - childCenterX == -1 ) myCenterX = childCenterX;

			line = new Q3CanvasLine( canvas );
			line->setPoints( myCenterX, myBottom, childCenterX, childTop );
			line->show();

			m_CanvasItems.append( line );
		}
	}

	edge->show();
	canvas->update();

	return myBoundingRect;
}


void CEdge::shiftTree( Q3Canvas* canvas, int right, int down )
{
	CEdge* daughter;
	for( daughter = m_Daughters.first(); daughter; daughter = m_Daughters.next() )
	{
		daughter->shiftTree( canvas, right, down );
	}

	Q3CanvasItem* item;
	for( item = m_CanvasItems.first(); item; item = m_CanvasItems.next() )
	{
		item->moveBy( right, down );
		item->show();
	}
}


void CEdge::setMinimumLength( int length, QMap<QString,int>* mins )
{
	if( m_Parent && mins && mins->find( LHS() ) != mins->end() )
	{
		int parentLength = m_Parent->getMinimumLength();
		parentLength -= (*mins)[ LHS() ];
		parentLength += length;

		m_Parent->setMinimumLength( parentLength, mins );
	}

	m_MinimumLength = length;
}


QString CEdge::DisplayParse( StringToString* filter )
{
	QString parse = LHS() + "( ";

	if( m_Daughters.count() )
	{
		CEdge* daughter;
		for( daughter = m_Daughters.first(); daughter; daughter = m_Daughters.next() )
		{
			parse += daughter->DisplayParse( filter );
			parse += " ";
		}
	}
	else
	{
		if( filter ) parse += Filter( filter, RHS() );
		else parse += RHS();

		parse += " ";
	}

	return parse + ")";
}
