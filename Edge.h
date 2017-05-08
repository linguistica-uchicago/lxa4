// CEdge class
// Copyright © 2009 The University of Chicago
#ifndef EDGE_H
#define EDGE_H

#include <q3canvas.h>
#include <qrect.h>
#include <Q3PtrList>

#include "Parse.h"

class CGrammarRule;

class CEdge : public CParse
{
        int		m_Start;
        int		m_End;
        int		m_DotLocation;// the number of the Parse piece to the right of the dot.
        double		m_X, m_Y; // coordinates for display;
        bool		m_InFinalParse;
        int		m_MinimumLength;
        int		m_Depth;
        Q3PtrList<Q3CanvasItem>     m_CanvasItems;

public: 

        CEdge*		m_Parent;
        Q3PtrList<CEdge> m_Daughters;

public:

	CEdge();
	CEdge( CEdge& );
	CEdge( CGrammarRule*, CParse*, int DotLocation );
	CEdge( CParse& Cat, QString Word, int i, int End ); // for Scanner


        int		GetDotLocation();
        void		SetDotLocation(int n);
        void		SetEnd (int n ) { m_End = n; }
	virtual ~CEdge();

	
        QString             LHS();
        CStringSurrogate    GetLHS();
        void                SetLHS( QString );
        QString             RHS();
	
        int                 GetStart();
        int                 GetEnd();
        CStringSurrogate    GetNextNode(); // the one to the right of the dot, which is m_DotLocation + 1;
        void                SetStart(int n );
        void                GetParse( CParse*, bool clearParse = TRUE );
        int                 getDepth() const { return m_Depth; }
        void                setDepth( int d ) { m_Depth = d; }
        bool                Complete();
        bool                Incomplete();
        void                MoveDotToTheRight();
        bool                NextNodeIsNonterminal();
        bool                NextNodeIsTerminal();

        QString             Display();
        QString             DisplayParse( StringToString* filter = NULL );
        QRect               drawTree( Q3Canvas*, int, int, StringToString* filter = NULL );
        void                shiftTree( Q3Canvas*, int, int );
        int                 getMinimumLength() { return m_MinimumLength; }
        void                setMinimumLength( int, QMap<QString,int>* = NULL );
};

#endif // EDGE_H
