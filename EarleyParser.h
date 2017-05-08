// Earley parser
// Copyright © 2009 The University of Chicagof
#ifndef EARLEYPARSER_H
#define EARLEYPARSER_H

#include <qmap.h>
#include <Q3PtrList>
#include <q3ptrqueue.h>
#include <QTextStream>

class CParse;
class CEdge;
class CGrammarRule;
class CTerminalRuleCollection;

typedef QMap<QString,CEdge*>                    StateMap;
typedef Q3PtrList<CEdge>                           State;
typedef QMap<uint,State>                        StateCollection;
typedef Q3PtrList<CGrammarRule>                 RuleList;
typedef QMap<QString,RuleList>                  RuleCollection;
typedef QMap<QString,CTerminalRuleCollection*>  TerminalCollection;


class CEarleyParser  
{
public:
        CEarleyParser( CParse*, RuleCollection*, TerminalCollection*, QTextStream* logFile = NULL, int maximumParseDepth = 5 );
	virtual ~CEarleyParser();
	
        Q3PtrList<CEdge>*                          Parse();  // the main event
        bool					Prediction( CEdge* );
        bool					Scanning( CEdge* );
        bool					Completion( CEdge* );
        bool					isValidGrammar() { return m_validGrammarFlag; }
        void					setMaximumParseDepth( int d ) { m_maximumParseDepth = d; }
        int					getMaximumParseDepth() const { return m_maximumParseDepth; }

//------------------------------------------------------------------------------------
protected:
	StateCollection				m_states;
	RuleCollection*				m_grammar;
        CParse*					m_word;
	TerminalCollection*			m_lexicon;
        int					m_shortest; // Length of shortest non-wild-card terminal

        Q3PtrList<CEdge>*                          m_Roots;
        int					m_CurrentLocation;
        uint					m_NumberOfStates;

        QTextStream*				m_logFile;

	QMap<QString,int>			m_minimumLengths;
        bool					m_validGrammarFlag;
        int					m_maximumParseDepth;

	/*	The entry is the Key; the Value is a parse, each of whose entries is the name of one of 
		the Key's categories (e.g., "can"  ... N.V );		*/

//	bool						TestWordForCategory( QString Word, CParse& Category );
};

#endif // EARLEYPARSER_H
