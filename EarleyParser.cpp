// Implementation of CEarleyParser methods
// Copyright © 2009 The University of Chicago
#include "EarleyParser.h"

#include "Config.h"
#include <QTextStream>
#include <Q3PtrList>
#include "GrammarRule.h"
#include "Edge.h"
#include "TerminalRuleCollection.h"
#include "Typedefs.h"


bool operator<< ( StateMap& stateMap, CEdge* edge ) // a StateMap is a map from strings to ptrs to Edges -- actually, from the "display" of the edge to a ptr to the Edge. Note used here,actually. We should get rid of it.
{
	if( stateMap.find( edge->Display() ) == stateMap.end() )
	{
		stateMap.insert( edge->Display(), edge );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*void operator<< ( State& state, CEdge* edge ) // a State is a list of ptrs to Edges.
{
	state.append( edge );
}
*/

bool operator<< (State& state, CEdge* edge) // a State is a QList of ptrs to Edges.
{
     CEdge* pEdge;
     //for (int z = 0; z < state.size(); z++)
     Q3PtrListIterator<CEdge> it(state);
     while ( ( pEdge = it.current() ) != 0 )
     {  ++it;
         if (pEdge->Display() == edge->Display() )
         { return FALSE;}
     }

     state.append (edge);
     return TRUE;
	
}
bool AddIfNecessary (State& state, CEdge* edge) // a State is a QPtrList of ptrs to Edges.
{
     CEdge* pEdge;
    for (pEdge = state.first(); pEdge; pEdge = state.next())
     {
         if (pEdge->Display() == edge->Display() )
         { return FALSE;}
     }

     state.append (edge);
     return TRUE;

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEarleyParser::CEarleyParser( CParse* word, RuleCollection* grammar, TerminalCollection* lexicon, QTextStream* logFile, int maximumParseDepth )
{
	m_word = word;
	m_grammar = grammar;
	m_logFile = logFile;
	m_lexicon = lexicon;
	m_maximumParseDepth = maximumParseDepth;

	m_validGrammarFlag = TRUE;

//	m_autoDeleteRoots = TRUE;

        CEdge* pEdge = new CEdge( (*m_grammar)[ "Start" ].at(0), m_word, 1 );

	m_CurrentLocation = 1;
	m_NumberOfStates = m_word->GetKeyLength() + 2;

        m_Roots = new Q3PtrList<CEdge>();

	uint i;
	
	for( i = 1; i < m_NumberOfStates; i++ )
	{
		State empty;
		m_states.insert( i, empty );
                //m_states[i].setAutoDelete( TRUE );
	}

        //m_states[1].append( pEdge );
        m_states[1] << pEdge;



	// Find the minimum length of substring required to add
	// each grammar node. This also gives us the opportunity
        // to check the grammar for determinicity.
	RuleCollection::Iterator it;
	TerminalCollection::Iterator it2;
	CGrammarRule* pRule;
	int shortest;

	// Initialize all min lengths of grammar to 0
	for( it = m_grammar->begin(); it != m_grammar->end(); ++it )
	{
//qDebug( it.key() );
		m_minimumLengths.insert( it.key(), 0 );
	}
	for( it2 = m_lexicon->begin(); it2 != m_lexicon->end(); ++it2 )
	{
//qDebug( it2.key() );
		shortest = it2.data()->GetShortest();
		if( shortest < 1 ) shortest = 1;
		m_minimumLengths.insert( it2.key(), shortest );
	}

	// We will go through this loop until we make no new
	// updates.
	bool done = FALSE;
	while( !done )
	{
		done = TRUE;

		for( it = m_grammar->begin(); it != m_grammar->end(); ++it )
		{
//qDebug( it.key() );
			if( m_minimumLengths.find( it.key() ) == m_minimumLengths.end() )
			{
				m_validGrammarFlag = FALSE;
				return;
			}

			int minimumLength = 0;

                        for( pRule = it.data().first(); pRule; pRule = it.data().next() )
                        //for (int z = 0; z < it.data().size(); z++)
                        {      // pRule = it.data().at(z);
				int thisLength = 0;
                                //qDebug( pRule->Display() );
				CParse parse = pRule->GetRHS();
				for( int j = 1; j <= parse.Size(); j++ )
				{
					if( parse.GetPiece(j) == pRule->GetLHS() ) 
					{
						thisLength = 0;
						break;
					}
					if( m_minimumLengths.find( parse.GetPiece(j).Display() ) == m_minimumLengths.end() )
					{
						if( parse.GetPiece(j).Display() != GRAMMAR_RULE_WILD_CARD )
						{
							m_validGrammarFlag = FALSE;
							return;
						}
					}
					
					if( parse.GetPiece(j).Display() == GRAMMAR_RULE_WILD_CARD )
					{
						thisLength += 1;
					}
					else if( m_minimumLengths[ parse.GetPiece(j).Display() ] > 0 )
					{
						thisLength += m_minimumLengths[ parse.GetPiece(j).Display() ];
					}
					else
					{
						thisLength = 0;
						break;
					}
				}
				
				if( thisLength > 0 )
				{
					if( minimumLength == 0 || minimumLength > thisLength )
					{
						minimumLength = thisLength;
					}
				}
			}

			if( minimumLength > 0 )
			{
				if( m_minimumLengths[ it.key() ] == 0 || minimumLength < m_minimumLengths[ it.key() ] )
				{
					m_minimumLengths[ it.key() ] = minimumLength;
					done = FALSE; // Made a change, so we're not done
				}
			}
		}
	}

	// If not all the minimums are set, the grammar is bad
	QMap<QString,int>::Iterator it3;
	for( it3 = m_minimumLengths.begin(); it3 != m_minimumLengths.end(); ++it3 )
	{
//qDebug( it3.key() + QString( " : %1" ).arg( it3.data() ) );
		if( it3.data() == 0 )
		{
			m_validGrammarFlag = FALSE;
			return;
		}
	}

	pEdge->setMinimumLength( m_minimumLengths[ "Start" ] );
}


CEarleyParser::~CEarleyParser()
{
    // Problem: JG 12/2008 if we delete these Edges when we delete
    // m_Roots, we must make sure the destructure for This does not
    // try to delete them when it destroys m_states of This. Otherwise
    // it tosses an exception. 
    //delete m_Roots;
   
}


bool CEarleyParser::Prediction( CEdge* pEdge )
{
	CStringSurrogate NextNode = pEdge->GetNextNode();
	CParse           RHSofRule;
	CEdge*           qEdge;
	CGrammarRule*    pRule;
    CSS              ssPiece;
	int              i, minimumLength;

	Q_ASSERT( pEdge->NextNodeIsNonterminal() ); 

    RuleList& matches = (*m_grammar)[ NextNode.Display() ];
    for( pRule = matches.first(); pRule; pRule = matches.next() )
    //for (int z= 0; z < matches.size(); z++)
        {
        //  Create an edge...  
		qEdge = new CEdge( pRule, m_word, m_CurrentLocation ); //dot location is I too;
		qEdge->setDepth( pEdge->getDepth() + 1 );

		// If the minimum length of this edge won't be longer than
		// the length of the word, add this new edge to the current state
		// minLength = min(RHS) + min(Parent) - min(LHS) - min(Parent's past children)
		minimumLength = 0;
		
		// min(RHS)
		for( i = 2; i <= qEdge->Size(); i++ )
		{
			minimumLength += m_minimumLengths[ qEdge->GetPiece(i).Display() ];
		}

		// min(Parent)
		minimumLength += pEdge->getMinimumLength();

		// min(LHS)
		minimumLength -= m_minimumLengths[ qEdge->GetPiece(1).Display() ];

		// min(Parent's past children)
		for( i = 2; i <= pEdge->GetDotLocation()-1; i++ )
		{
			minimumLength -= m_minimumLengths[ pEdge->GetPiece(i).Display() ];
		}

		if( minimumLength <= m_word->GetKeyLength() - m_CurrentLocation + 1 )
		{
                        m_states[ m_CurrentLocation ] << qEdge;
                        qEdge->m_Parent = pEdge;
                        qEdge->setMinimumLength( minimumLength );
                         //  Log this action.
                            if( m_logFile )
                            {
                                    QString log_line = "Prediction 1:";
                                    for( int i = 1; i <= m_CurrentLocation; i++ )
                                    {
                                            log_line += "\t";
                                    }
                                    log_line += qEdge->Display();

                                *m_logFile << log_line << endl;
                            }
                }
		else
		{
			delete qEdge;
			continue;
		}
	}


        CSS string = m_word->GetKey().Mid( m_CurrentLocation - 1 );

	if( m_lexicon->find( NextNode.Display() ) != m_lexicon->end() )
	{
		CTerminalRuleCollection* termMatches = (*m_lexicon)[ NextNode.Display() ];

                Q3PtrList<CTerminalRule> substrings;
		termMatches->FindSubstrings( string, substrings );

                for( pRule = substrings.first(); pRule; pRule = substrings.next() )
                //for (int y = 0; y < substrings.size(); y++)
                {       //pRule =  substrings.at(y);
                        if (m_CurrentLocation==1 && pRule->GetRHS().GetKeyLength() == string.GetLength() ) // this "rule" returns the whole word as its hypothesis, which is not useful.
                        { continue; }

			//  Create an edge...  
			qEdge = new CEdge( pRule, m_word, m_CurrentLocation ); //dot location is I too;
			qEdge->setDepth( pEdge->getDepth() + 1 );

                        if ( AddIfNecessary ( m_states[ m_CurrentLocation ],  qEdge ) )//if the edge was already there, this should return FALSE
                        {
			     qEdge->m_Parent = pEdge;
			
			     //  Log this action.
			     if( m_logFile )
			     {
				     QString log_line = "Prediction 2:";
				     for( int i = 1; i <= m_CurrentLocation; i++ )
				     {
					     log_line += "\t";
				     }
				     log_line += qEdge->Display();

			     	     *m_logFile << log_line << endl;
			     }
            }
		}
	}

	return TRUE;
}

bool CEarleyParser::Scanning( CEdge* pEdge )
{
	CParse		NextNode, LHSofRule;
	CEdge*		qEdge;

	NextNode = pEdge->GetNextNode(); //to the right of dot
	QChar ThisLetter = m_word->GetKey().Display()[ m_CurrentLocation-1 ];

	if ( QString(ThisLetter) == NextNode.Display() ||
			NextNode.Display() == GRAMMAR_RULE_WILD_CARD ) {
		qEdge = new CEdge( *pEdge );
		qEdge->SetDotLocation( qEdge->GetDotLocation() + 1 );

                m_states[ m_CurrentLocation + 1 ] << qEdge;

		//  Log this action.
		if ( m_logFile ) {
			QString log_line = "Scanned:";
			for( int i = 1; i <= m_CurrentLocation+1; i++ )
			{
				log_line += "\t";
			}
			log_line += qEdge->Display();

			*m_logFile << log_line << endl;
		}
	}
	return TRUE;
}


bool CEarleyParser::Completion( CEdge* pEdge )
{
	QString		Key;
	CEdge*		qEdge, *rEdge;
//	int			pEdgeStartLoc = pEdge->GetStart(); unused variable 'pEdgeStartLoc'
	CSS			NextNode;
 
	
 
  qEdge = pEdge->m_Parent;
        if( qEdge )					// pEdge != Start
        {
                NextNode = qEdge->GetNextNode();

                Q_ASSERT( NextNode == pEdge->GetLHS() );

                rEdge = new CEdge( *qEdge );
                rEdge->SetStart( qEdge->GetStart() );
                rEdge->SetEnd( m_CurrentLocation - 1 );//****
                rEdge->MoveDotToTheRight();

                m_states[ m_CurrentLocation ] << rEdge;

                pEdge->m_Parent = rEdge;
                rEdge->m_Daughters.append( pEdge );

                if ( m_CurrentLocation-1 == m_word->GetKeyLength() && rEdge->GetLHS().Display() == QString( "Start" ) )
                {
                        m_Roots->append( rEdge );
                }

                //  Log this action
//qDebug( "\tCompletion : " + rEdge->Display() );
                if( m_logFile )
                {
                        QString log_line = "Completion:";
                        for( int i = 1; i <= m_CurrentLocation; i++ )
                        {
                                log_line += "\t";
                        }
                        log_line += rEdge->Display();

                        *m_logFile << log_line << endl;
                }
        }
	
	return TRUE;
}


Q3PtrList<CEdge>* CEarleyParser::Parse()
{
	CEdge*		        pEdge;
	QString		        Key;
        Q3PtrList<CEdge>*       pCurrentEdgeStack;
        int                     i;

	if( m_logFile )
	{
		*m_logFile << "======================================================" << endl;
		*m_logFile << "Attempting to parse \'" << m_word->Display() << "\'..." << endl << endl;
	}

        //qDebug( m_word->Display() );
        for( m_CurrentLocation = 1; (int) m_CurrentLocation <= m_word->GetKeyLength() + 1 ; m_CurrentLocation++ )
        {
                if( m_states[ m_CurrentLocation ].count() == 0 )
                {
                        break;
                }
//%%%%% Signed/Unsigned????
                for( i = 0; i < static_cast <int> ( m_states[ m_CurrentLocation ].count()); ++i )
                {
                        pEdge = m_states[ m_CurrentLocation ].at(i);
                        if( !pEdge ) continue;
//qDebug( pEdge->Display() + " :" );
//qDebug( "---------------------" );
                        if( pEdge->Incomplete() && pEdge->NextNodeIsNonterminal() && pEdge->getDepth() <= m_maximumParseDepth )
                        {
                                Prediction( pEdge );
                        }
                        else if( pEdge->Incomplete() && pEdge->NextNodeIsTerminal() )
                        {
                                Scanning( pEdge );
                        }
                        else
                        {
                                Completion( pEdge );
                        }
//qDebug( " " );
                }
        }

	if( m_logFile )
	{
		*m_logFile    << "\n\n";
                *m_logFile    << "Found " << m_Roots->count();
		if( m_Roots->count() == 1 ) *m_logFile << " parse";
		else *m_logFile << " parses";
		*m_logFile    << " for \'" 
                      << m_word->Display() 
                      << "\'.\n\n";
	}
 

    return m_Roots;
}
