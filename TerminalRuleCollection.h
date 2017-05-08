// CTerminalRuleCollection class
// Copyright © 2009 The University of Chicago
#ifndef TERMINALRULECOLLECTION_H
#define TERMINALRULECOLLECTION_H

#include "CollectionTemplate.h"
#include <QList>

class CTerminalRule;

class CTerminalRuleCollection : public TCollection<CTerminalRule>
{

public:

					CTerminalRuleCollection();
	virtual			~CTerminalRuleCollection();

	CTerminalRule*	operator<< ( CTerminalRule* );

        //void			FindSubstrings( CStringSurrogate&, QList<CTerminalRule*>& );
        void            FindSubstrings (CStringSurrogate&, Q3PtrList<CTerminalRule>& );
	int  GetShortest();

};

#endif // TERMINALRULECOLLECTION_H
