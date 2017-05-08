// Compound discovery and analysis within the Lexicon class
// Copyright © 2009 The University of Chicago
#include "Lexicon.h"

#include <QTextStream>
#include <QList>
#include "linguisticamainwindow.h"
#include "EarleyParser.h"
#include "MiniLexicon.h"
#include "GrammarRule.h"
#include "Compound.h"
#include "Linker.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Stem.h"
#include "Edge.h"
#include "TerminalRuleCollection.h"
#include "CompoundCollection.h"
#include "LinkerCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "Typedefs.h"

/**
 * Displays all compounds in the collection view <i>pView</i>. All joined characters are
 * re-filtered on output to separate characters with <i>filter</i>. The <i>separator</i> will be
 * placed between components of a compound in the first column.
 */
void CLexicon::CompoundListDisplay( Q3ListView* pView, StringToString* filter, QChar separator )
{
	CCompound*    pCompound;
	int	MostParses = 0;
	int   n, i;

	pView->setRootIsDecorated( FALSE );
	
	for( i = 0; i < (int)m_pCompounds->GetCount(); i++ )
	{
		if( !m_pCompounds->GetAt(i)->GetParses() ) continue;

		n = m_pCompounds->GetAt(i)->GetParses()->count();
		if( n > MostParses ) MostParses = n; 
	}
	
	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );
	
	// Add Column headers
	pView->addColumn( "Compound" );
	pView->addColumn( "# Parses" );
	pView->addColumn( "Most Frequent Stem" );	
	pView->addColumn( "Prefixness" );
	pView->addColumn( "Suffixness" );
	m_pCompounds->Sort(KEY);
	m_pDoc->setStatusBar1( "Creating compound list for display" );
	m_pDoc->BeginCountDown();
	for ( i = 0; i < (int)m_pCompounds->GetCount(); i++)
	{
		pCompound = m_pCompounds->GetAtSort(i);

		pCompound->CompoundListDisplay( pView, filter, separator );

		m_pDoc->CountDownOnStatusBar( i, m_pCompounds->GetCount() );
	}

	m_pDoc->setStatusBar1( "" );
	m_pDoc->EndCountDown();   
}


/**
 * Displays all linkers in the collection view <i>pView</i>. All joined characters are
 * re-filtered on output to separate characters with <i>filter</i>.
 */
void CLexicon::LinkerListDisplay( Q3ListView* pView, StringToString* filter )
{
	CLinker* pLinker;
	int i;

	pView->setRootIsDecorated( FALSE );
	
	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );
	
	// Add Column headers
	pView->addColumn( "Linker" );
	pView->addColumn( "Corpus Count" );
	pView->addColumn( "Compound Count" );
	pView->addColumn( "Compounds" );
	m_pLinkers->Sort(KEY);
	m_pDoc->setStatusBar1( "Creating linker list for display" );
	m_pDoc->BeginCountDown();

	for ( i = 0; i < (int)m_pLinkers->GetCount(); i++)
	{
		pLinker = m_pLinkers->GetAtSort(i);
		pLinker->ListDisplay( pView, filter );
		m_pDoc->CountDownOnStatusBar( i, m_pLinkers->GetCount() );
	}

	m_pDoc->setStatusBar1( "" );
	m_pDoc->EndCountDown();   
}
/**
 * Displays all compound components in the collection view <i>pView</i>.
 * All joined characters are re-filtered on output to separate characters
 * with the lexicon’s filter.
 */
void CLexicon::CompoundComponentListDisplay(Q3ListView* pView)
{
    CStem* pStem;
    pView->setRootIsDecorated( FALSE );
	
	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );
	
	// Add Column headers
	pView->addColumn( "Compound component" );
	pView->addColumn( "Corpus Count" );
	pView->addColumn( "Compound Count" );

 
//    m_pCompounds->GetComponents()->Sort(KEY);

 	m_pDoc->BeginCountDown();

	for ( int i = 0; i < (int)m_pCompounds->GetComponents()->GetCount(); i++)
	{
		pStem = m_pCompounds->GetComponents()->GetAtSort(i);
        new Q3ListViewItem(pView, pStem->GetKey().Display(),IntToStringWithCommas( pStem->GetCorpusCount())     );
//		pStem ->ListDisplay( pView, filter );
		m_pDoc->CountDownOnStatusBar( i, m_pCompounds->GetComponents()->GetCount() );
	}
 
    
    
    m_pDoc->setStatusBar1( "" );
	m_pDoc->EndCountDown();   
}
void CLexicon::FromStemsFindFlatCompounds( QList<CStem*>* compounds, QList<CStem*>* components, QString linker, int maxNumberOfRoots )
{
	CMiniLexicon* pMini;
	int stemCount = 0;
	int i, j;
	
	int MaximumParseDepth = GetIntParameter ("EarleyParser\\MaximumParseDepth", 6 );

	// We need to have analyzed some stems.
	if( !compounds )
	{
		for( i = 0; i < static_cast <int> ( m_pMiniLexica->size() ) ; i++ )
		{
			pMini = (*m_pMiniLexica)[i];
			if( pMini ) stemCount += pMini->GetStems()->GetCount();
		}
		if( stemCount == 0 ) return;
	}

	CStem* pStem;
	CGrammarRule* pRule;
	CTerminalRule* tRule;
	CWildCardRule* wRule;
	QString rule, compound;
        Q3PtrList<CEdge>* allParses = NULL;
	CCompound* pCompound;
	CParse oneParse;
	CEdge* pEdge;
	CSS ssCompound;
	CMiniLexicon* mini;

        QTextStream* logFile = NULL;

	int longestCompound = 0;
	int shortestComponent = 0;

	m_pCompounds->SetComponentCount( 0.0 );
	m_pCompounds->SetLinkerCount( 0.0 );

	int MINIMUM_STEM_LENGTH = GetIntParameter( "Main\\MinimumStemLength", 3 );
	int MAXIMUM_LINKER_LENGTH = GetIntParameter( "Compounds\\MaximumLinkerLength", 1 );

	// We will attempt to parse all stems and unanalyzed 
	// words (assumed to be stems), so we should collect
	// them all into one place.
	CStemCollection Stems;
	Stems.CreateReverseTrie();

	if( !compounds )
	{
		for( i = GetMiniSize()-1; i >= 0; i-- )
		{
			mini = GetMiniLexicon(i);
			if( !mini ) continue;

			for( j = 0; j < mini->GetStems()->GetCount(); j++ )
			{
				Stems << mini->GetStems()->GetAt(j);
			}

			for( j = 0; j < mini->GetWords()->GetCount(); j++ )
			{
				// We don't want to parse analyzed words
				if( mini->GetWords()->GetAt(j)->Size() > 1 ) continue;

				// We don't want words that are too short
				if( mini->GetWords()->GetAt(j)->GetKeyLength() < MINIMUM_STEM_LENGTH ) continue;

				Stems << mini->GetWords()->GetAt(j);
			}
		}
	}
	else
	{
                //for( pStem = compounds->first(); pStem; pStem = compounds->next() )
                for (int z = 0; z < compounds->size(); z++)
                {       pStem = compounds->at(z);
			Stems << pStem;
			if( pStem->GetKeyLength() > longestCompound ) 
			{
				longestCompound = pStem->GetKeyLength();
			}
		}

                //for( pStem = components->first(); pStem; pStem = components->next() )
                for (int y = 0; y < components->size(); y++)
                {       pStem = components->at(y);
			Stems << pStem;
			if( shortestComponent == 0 || pStem->GetKeyLength() < shortestComponent )
			{
				shortestComponent = pStem->GetKeyLength();
			}
		}
	}


	// We need a grammar to parse from
	RuleCollection grammar;

	// Start
	grammar.insert( "Start", RuleList() );
        //grammar[ "Start" ].setAutoDelete( TRUE );

	pRule = new CGrammarRule();
	rule = "Start Word";							// Start --> Word
	pRule->Collapse( rule );
	grammar[ "Start" ].append( pRule );

	// Word
	grammar.insert( "Word", RuleList() );
        //grammar[ "Word" ].setAutoDelete( TRUE );

	pRule = new CGrammarRule();
	rule = "Word Compound";							// Word --> Compound
	pRule->Collapse( rule );
	grammar[ "Word" ].append( pRule );

	// Compound
	grammar.insert( "Compound", RuleList() );
        //grammar[ "Compound" ].setAutoDelete( TRUE );

	for( i = 2; i <= maxNumberOfRoots; i++ )		// Compound --> Root Root+
	{
		pRule = new CGrammarRule();

		rule = "Compound";
		for( j = 0; j < i; j++ ) rule += " Root";

		pRule->Collapse( rule );
		grammar[ "Compound" ].append( pRule );
	}


	// Linker
	CTerminalRuleCollection linkers;

	if( linker == QString::null )
	{
		if( MAXIMUM_LINKER_LENGTH > 0 )
		{
			grammar.insert( "Linker", RuleList() );
                        //grammar[ "Linker" ].setAutoDelete( TRUE );

			for( i = 1; i <= MAXIMUM_LINKER_LENGTH; i++ )
			{
				rule = "Linker";
				wRule = new CWildCardRule( rule, i );
				grammar[ "Linker" ].append( wRule );
			}
		}
	}
	else
	{
		rule = "Linker";
		tRule = new CTerminalRule( rule );
		tRule->SetKey( CStringSurrogate( linker ) );
		Q_ASSERT( tRule == ( linkers << tRule ) );
	}
	

	if( grammar.find( "Linker" ) != grammar.end() || 
		linker != QString::null )
	{

		for( i = 2; i <= maxNumberOfRoots; i++ )	// Compound --> Root (Linker Root)+
		{
			pRule = new CGrammarRule();

			rule = "Compound";
			for( j = 0; j < i - 1; j++ ) rule += " Root Linker";
			rule += " Root";

			pRule->Collapse( rule );
			grammar[ "Compound" ].append( pRule );
		}
	}

	// Add all the stems as terminal root rules
	CTerminalRuleCollection stems;

	if( !components )
	{
		Stems.Sort(KEY);
		for( i = 0; i < Stems.GetCount(); i++ )
		{
			pStem = Stems.GetAtSort(i);

			rule = "Root";
			tRule = new CTerminalRule( rule );
			tRule->Append( pStem );
			Q_ASSERT( tRule == ( stems << tRule ) );
		}
	}
	else
	{
                //for( pStem = components->first(); pStem; pStem = components->next() )
                for (int z= 0; z < components->size(); z++)
                {       pStem = components->at(z);
			rule = "Root";
			tRule = new CTerminalRule( rule );
			tRule->Append( pStem );
			Q_ASSERT( tRule == ( stems << tRule ) );
		}
	}
	
	TerminalCollection lexicon;
	lexicon.insert( "Root", &stems );
	if( linker != QString::null ) lexicon.insert( "Linker", &linkers );

	// Parse all stems
	Stems.Sort(KEY);
	GetDocument()->setStatusBar1( "Parsing possible compounds" );
	GetDocument()->BeginCountDown();

	CEarleyParser* parser = NULL;

	for( i = 0; i < Stems.GetCount(); i++ )
	{
		GetDocument()->CountDownOnStatusBar( i, Stems.GetCount(), Stems.GetCount()/100 );
		pStem = Stems.GetAtSort(i);

		// We don't want to analyze anything that can't contain two stems
		// Words that are not at least the length of two stems
		if( pStem->GetKeyLength() < 2 * MINIMUM_STEM_LENGTH ) continue; 

		// This includes anything that has less than two valid stems that start
		// at the first character of this word
		CSS key = pStem->GetKey();
		if( Stems.CountValidSubstrings( key ) < 2 ) continue;

		// And also includes anything that has less than two valid stems that
		// end at the last character of this word
		key.SetBackwards();
		if( Stems.GetReverseTrie()->CountValidSubstrings( key ) < 2 ) continue;

		// Log if desired
		if( LogFileOn() )
		{
			logFile = GetLogFileStream(); 
        } else { logFile = NULL; }

		// Parse the word
        parser = new CEarleyParser( pStem, &grammar, &lexicon, logFile, MaximumParseDepth );
        pStem->SetMyEarleyParser (parser);  
 
		if( parser->isValidGrammar() ) 
		{
			allParses = parser->Parse();
		}

		if( allParses && !allParses->isEmpty() )
		{
			// We found some parses, now we can create a compound
			// we'll use the first parse until we can get component
			// probability information
			
			pEdge = allParses->first();
			pEdge->GetParse( &oneParse );

			pCompound = *m_pCompounds << oneParse.Display();
			pCompound->IncrementCorpusCount( pStem->GetCorpusCount() - 1 );

			double componentCount = 0.0,
				   linkerCount = 0.0;
			pCompound->SetLexicon( this );
			pCompound->SetParses( allParses, &componentCount, &linkerCount );
			m_pCompounds->SetComponentCount( m_pCompounds->GetComponentCount() + componentCount );
			m_pCompounds->SetLinkerCount( m_pCompounds->GetLinkerCount() + linkerCount );
			pCompound->SetBestParse(0);

			UpdateCompound( pCompound->Display() );
		}

		 
	}

	GetDocument()->EndCountDown();
}


void CLexicon::FromStemsFindCompounds( QList<CStem*>* compounds, QList<CStem*>* components, QString linker )
{
	CMiniLexicon* pMini;
	int stemCount = 0;
	int i, j;
	
	int MaximumParseDepth = GetIntParameter ("EarleyParser\\MaximumParseDepth", 5 );

	// We need to have analyzed some stems.
	if( !compounds )
	{
		for( i = 0; i < static_cast <int> ( m_pMiniLexica->size() ) ; i++ )
		{
			pMini = (*m_pMiniLexica)[i];
			if( pMini ) stemCount += pMini->GetStems()->GetCount();
		}
		if( stemCount == 0 ) return;
	}

	CStem*           pStem;
	CGrammarRule*    pRule;
	CTerminalRule*   tRule;
	CWildCardRule*   wRule;
	QString          rule, compound;
        Q3PtrList<CEdge>*   allParses = NULL;
	CCompound*       pCompound;
	CParse           oneParse;
	CEdge*           pEdge;
	CSS              ssCompound;
	CMiniLexicon*    mini;
        QTextStream*     logFile = NULL;

	int longestCompound   = 0;
	int shortestComponent = 0;

	m_pCompounds->SetComponentCount( 0.0 );
	m_pCompounds->SetLinkerCount( 0.0 );

	int MINIMUM_STEM_LENGTH = GetIntParameter( "Main\\MinimumStemLength", 3 );
	int MAXIMUM_LINKER_LENGTH = GetIntParameter( "Compounds\\MaximumLinkerLength", 1 );

	// We will attempt to parse all stems and unanalyzed 
	// words (assumed to be stems), so we should collect
	// them all into one place.
	CStemCollection Stems;
	Stems.CreateReverseTrie();

	if( !compounds )
	{
		for( i = GetMiniSize()-1; i >= 0; i-- )
		{
			mini = GetMiniLexicon(i);
			if( !mini ) continue;

			for( j = 0; j < mini->GetStems()->GetCount(); j++ )
			{
				Stems << mini->GetStems()->GetAt(j);
			}

			for( j = 0; j < mini->GetWords()->GetCount(); j++ )
			{
				// We don't want to parse analyzed words
				if( mini->GetWords()->GetAt(j)->Size() > 1 ) continue;

				// We don't want words that are too short
				if( mini->GetWords()->GetAt(j)->GetKeyLength() < MINIMUM_STEM_LENGTH ) continue;

				Stems << mini->GetWords()->GetAt(j);
			}
		}
	}
	else
	{
                //for( pStem = compounds->first(); pStem; pStem = compounds->next() )
                for (int z= 0; z < compounds->size(); z++)
                {       pStem = compounds->at(z);
			Stems << pStem;
			if( pStem->GetKeyLength() > longestCompound ) 
			{
				longestCompound = pStem->GetKeyLength();
			}
		}

                //for( pStem = components->first(); pStem; pStem = components->next() )
                for (int y  = 0; y < components->size(); y++)
                {       pStem = components->at(y);
			Stems << pStem;
			if( shortestComponent == 0 || pStem->GetKeyLength() < shortestComponent )
			{
				shortestComponent = pStem->GetKeyLength();
			}
		}
	}


	// We need a grammar to parse from
	RuleCollection grammar;

	// Start
	grammar.insert( "Start", RuleList() );
        //grammar[ "Start" ].setAutoDelete( TRUE );

	pRule = new CGrammarRule();
	rule = "Start Word";							// Start --> Word
	pRule->Collapse( rule );
	grammar[ "Start" ].append( pRule );

	// Word
	grammar.insert( "Word", RuleList() );
        //grammar[ "Word" ].setAutoDelete( TRUE );

	pRule = new CGrammarRule();
	rule = "Word Compound";							// Word --> Compound
	pRule->Collapse( rule );
	grammar[ "Word" ].append( pRule );

	// Compound
	grammar.insert( "Compound", RuleList() );
        //grammar[ "Compound" ].setAutoDelete( TRUE );

	pRule = new CGrammarRule();
	rule = "Compound Compound Compound";			// Compound --> Compound Compound
	pRule->Collapse( rule );
	grammar[ "Compound" ].append( pRule );

	pRule = new CGrammarRule();
	rule = "Compound Compound Root";				// Compound --> Compound Root
	pRule->Collapse( rule );
	grammar[ "Compound" ].append( pRule );

	pRule = new CGrammarRule();
	rule = "Compound Root Compound";				// Compound --> Root Compound
	pRule->Collapse( rule );
	grammar[ "Compound" ].append( pRule );

	pRule = new CGrammarRule();
	rule = "Compound Root Root";					// Compound --> Root Root
	pRule->Collapse( rule );
	grammar[ "Compound" ].append( pRule );

	// Linker
	CTerminalRuleCollection linkers;

	if( linker == QString::null )
	{
		if( MAXIMUM_LINKER_LENGTH > 0 )
		{
			grammar.insert( "Linker", RuleList() );
                        //grammar[ "Linker" ].setAutoDelete( TRUE );

			for( i = 1; i <= MAXIMUM_LINKER_LENGTH; i++ )
			{
				rule = "Linker";
				wRule = new CWildCardRule( rule, i );
				grammar[ "Linker" ].append( wRule );
			}
		}
	}
	else
	{
		rule = "Linker";
		tRule = new CTerminalRule( rule );
		tRule->SetKey( CStringSurrogate( linker ) );
		Q_ASSERT( tRule == ( linkers << tRule ) );
	}
	

	if( grammar.find( "Linker" ) != grammar.end() || 
		linker != QString::null )
	{
		pRule = new CGrammarRule();
		rule = "Compound Compound Linker Compound";		// Compound --> Compound Linker Compound
		pRule->Collapse( rule );
		grammar[ "Compound" ].append( pRule );

		pRule = new CGrammarRule();
		rule = "Compound Compound Linker Root";			// Compound --> Compound Linker Root
		pRule->Collapse( rule );
		grammar[ "Compound" ].append( pRule );

		pRule = new CGrammarRule();
		rule = "Compound Root Linker Compound";			// Compound --> Root Linker Compound
		pRule->Collapse( rule );
		grammar[ "Compound" ].append( pRule );

		pRule = new CGrammarRule();
		rule = "Compound Root Linker Root";				// Compound --> Root Linker Root
		pRule->Collapse( rule );
		grammar[ "Compound" ].append( pRule );
	}

	// Add all the stems as terminal root rules
	CTerminalRuleCollection stems;

	if( !components )
	{
		Stems.Sort(KEY);
		for( i = 0; i < Stems.GetCount(); i++ )
		{
			pStem = Stems.GetAtSort(i);

			rule = "Root";
			tRule = new CTerminalRule( rule );
			tRule->Append( pStem );
			Q_ASSERT( tRule == ( stems << tRule ) );
		}
	}
	else
	{
                //for( pStem = components->first(); pStem; pStem = components->next() )
                for (int z = 0; z < components->size(); z++)
                {       pStem = components->at(z);
			rule = "Root";
			tRule = new CTerminalRule( rule );
			tRule->Append( pStem );
			Q_ASSERT( tRule == ( stems << tRule ) );
		}
	}
	
	TerminalCollection lexicon;
	lexicon.insert( "Root", &stems );
	if( linker != QString::null ) lexicon.insert( "Linker", &linkers );

	// Parse all stems
	Stems.Sort(KEY);
	GetDocument()->setStatusBar1( "Parsing possible compounds" );
	GetDocument()->BeginCountDown();

	CEarleyParser* parser = NULL;

 	for( i = 0; i < Stems.GetCount(); i++ )
	{
		GetDocument()->CountDownOnStatusBar( i, Stems.GetCount(), Stems.GetCount()/100 );
		pStem = Stems.GetAtSort(i);

		// We don't want to analyze anything that can't contain two stems
		// Words that are not at least the length of two stems
		if( pStem->GetKeyLength() < 2 * MINIMUM_STEM_LENGTH ) continue; 

		// This includes anything that has less than two valid stems that start
		// at the first character of this word
		CSS key = pStem->GetKey();
		if( Stems.CountValidSubstrings( key ) < 2 ) continue;

		// And also includes anything that has less than two valid stems that
		// end at the last character of this word
		key.SetBackwards();
		if( Stems.GetReverseTrie()->CountValidSubstrings( key ) < 2 ) continue;

		// Log if desired
		if( LogFileOn() )
		{
			logFile = GetLogFileStream(); 
		} else { logFile = NULL; }

		// Parse the word
		parser = new CEarleyParser( pStem, &grammar, &lexicon, logFile, MaximumParseDepth );
        pStem->SetMyEarleyParser( parser);

		if( parser->isValidGrammar() ) 
		{
			allParses = parser->Parse();
		}

		if( allParses && !allParses->isEmpty() )
		{
			// We found some parses, now we can create a compound
			// we'll use the first parse until we can get component
			// probability information
			
			pEdge = allParses->first();
			pEdge->GetParse( &oneParse );

			pCompound = *m_pCompounds << oneParse.Display();
			pCompound->IncrementCorpusCount( pStem->GetCorpusCount() - 1 );

            //-----------------------------------------------//
            for (int m = 1; m <= oneParse.Size(); m++)
            {  
                *m_pCompounds->GetComponents() << oneParse.GetPiece(m).Display(); 
            } 

            //-----------------------------------------------//

			double componentCount = 0.0,
				   linkerCount = 0.0;
			pCompound->SetLexicon( this );
			pCompound->SetParses( allParses, &componentCount, &linkerCount );
			m_pCompounds->SetComponentCount( m_pCompounds->GetComponentCount() + componentCount );
			m_pCompounds->SetLinkerCount( m_pCompounds->GetLinkerCount() + linkerCount );
			pCompound->SetBestParse(0);

			UpdateCompound( pCompound->Display() );
		}

    }

// DEBUG	QMessageBox::information( m_pDoc, "Linguistica", "End search through stems." );

	GetDocument()->EndCountDown();
}


void CLexicon::CalculateCoefficientsOfAffixness()
{
	int          i, j, count = 0;
	SuffixSet*   pSuffixSet;
	PrefixSet*   pPrefixSet;
	CSuffix*     pSuffix;
	CPrefix*     pPrefix;
	CStem*       pStem, * pWord;
	StemSet*     pStemSet;
	pStemSet     = NULL;
	CLinker*     pLinker;
	pLinker      = NULL;
	CCompound*   pCompound;
	CEdge*       pEdge;
	CParse       parse;

        QList<CStem*>* pWords, *pStems;

	m_pDoc->setStatusBar1( "Calculating affixness..." );
	m_pDoc->BeginCountDown();

	ComponentMap::Iterator it;
	for( it = m_pCompounds->GetComponentMap()->begin(); it != m_pCompounds->GetComponentMap()->end(); ++it )
	{
		m_pDoc->CountDownOnStatusBar( ++count, m_pCompounds->GetComponentMap()->count(), 
                                               m_pCompounds->GetComponentMap()->count()/100 );

		double affix_prob     = 0.0,
			   component_prob = 0.0;

		double sig_count, stem_count, affix_count;

		pSuffixSet = m_AllSuffixes[ it.key() ];
	
		if( pSuffixSet )
		{
			for( j = 0; j < static_cast <int> ( pSuffixSet->count() ); j++ )
			{
				pSuffix = pSuffixSet->at(j);
				
				pStems = pSuffix->GetStems();
				
				if( !pStems ) continue;

                                //for( pStem = pStems->first(); pStem; pStem = pStems->next() )
                                for (int z = 0; z < pStems->size(); z++)
                                {       pStem = pStems->at(z);
					stem_count = pStem->GetCorpusCount();
					sig_count = pStem->GetSuffixSignature()->GetCorpusCount();

					pWords = pStem->GetSuffixSignature()->GetWordPtrList();

					if( !pWords ) continue;

					affix_count = 0;

                                        //for( pWord = pWords->first(); pWord; pWord = pWords->next() )
                                        for (int z = 0; z < pWords->size(); z++)
                                        {       pWord = pWords->at(z);
						if( pWord->GetSuffix() != pSuffix->GetKey() ) continue;

						affix_count += pWord->GetCorpusCount();
					}
					
					affix_prob += ( (double) sig_count / (double) GetCorpusCount() ) *
								  ( (double) stem_count / (double) sig_count ) *
								  ( (double) affix_count / (double) sig_count );
				}
			}
		}



		pPrefixSet = m_AllPrefixes[ it.key() ];
	
		if( pPrefixSet )
		{
			for( j = 0; j < static_cast <int> ( pPrefixSet->count() ); j++ )
			{
				pPrefix = pPrefixSet->at(j);
				
				pStems = pPrefix->GetStems();
				
				if( !pStems ) continue;

                                //for( pStem = pStems->first(); pStem; pStem = pStems->next() )
                                for (int z = 0; z < pStems->size(); z++)
                                {       pStem = pStems->at(z);
					stem_count = pStem->GetCorpusCount();
					sig_count = pStem->GetPrefixSignature()->GetCorpusCount();

					pWords = pStem->GetPrefixSignature()->GetWordPtrList();

					if( !pWords ) continue;

					affix_count = 0;

                                        //for( pWord = pWords->first(); pWord; pWord = pWords->next() )
                                        for (int y = 0; y < pWords->size(); y++)
                                        {       pWord = pWords->at(z);
						if( pWord->GetPrefix() != pPrefix->GetKey() ) continue;

						affix_count += pWord->GetCorpusCount();
					}
					
					affix_prob += ( (double) sig_count / (double) GetCorpusCount() ) *
								  ( (double) stem_count / (double) sig_count ) *
								  ( (double) affix_count / (double) sig_count );
				}
			}
		}



		double word_is_compound_prob = (double) m_pCompounds->GetCorpusCount() / (double) GetCorpusCount();

		for( i = 0; i < m_pCompounds->GetCount(); i++ )
		{
			pCompound = m_pCompounds->GetAt(i);

			double this_parse_prob,
				   piece_prob;
                        for( pEdge = pCompound->GetParses()->first(); pEdge; pEdge = pCompound->GetParses()->next() )
                        //for (int z= 0; z < pCompound->GetParses()->size(); z++)
                        { //      pEdge = pCompound->GetParses()->at(z);
				pEdge->GetParse( &parse );

				if( parse.Find( it.key() ) == 0 ) continue;

				this_parse_prob = 1.0;

				for( j = 1; j < parse.Size(); j++ )
				{
					if( m_pCompounds->GetComponentMap()->find( parse.GetPiece(j).Display() ) != m_pCompounds->GetComponentMap()->end() )
					{
						pStemSet = m_pCompounds->GetComponentMap()->find( parse.GetPiece(j).Display() ).data();
					}
					else pLinker = *GetLinkers() ^= parse.GetPiece(j);

					if( pStemSet )
					{
						piece_prob = pStemSet->at(0)->GetCompoundCount() / m_pCompounds->GetComponentCount();
					}
					else if( pLinker ) piece_prob = pLinker->GetCompoundCount() / m_pCompounds->GetLinkerCount();
					else continue;

					this_parse_prob *= piece_prob;
				}

				component_prob += word_is_compound_prob * this_parse_prob;
			}
		}


		pStemSet = it.data();
                //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                for (int y = 0; y < pStemSet->size(); y++)
                {       pStem = pStemSet->at(y);
			if( affix_prob == 0.0 ) pStem->SetAffixness( 0.0 );
			else if( component_prob == 0.0 ) pStem->SetAffixness( 1.0 );
			else pStem->SetAffixness( affix_prob / ( affix_prob + component_prob ) );
		}
	}

	m_pDoc->setStatusBar1( "" );
	m_pDoc->EndCountDown();
}


void CLexicon::FromAffixnessUpdateSigsAndCompounds()
{
	bool ok;
	double UPPER_THRESHOLD = 0.70;
	UPPER_THRESHOLD = QInputDialog::getDouble( "Linguistica", 
											   "Enter the upper affixness threshold:", 
											   UPPER_THRESHOLD, 0.0, 1.0, 2, &ok, m_pDoc );
	if ( !ok ) UPPER_THRESHOLD = 0.70;

	double LOWER_THRESHOLD = 0.30;
	LOWER_THRESHOLD = QInputDialog::getDouble( "Linguistica", 
											   "Enter the lower affixness threshold:", 
											   LOWER_THRESHOLD, 0.0, 1.0, 2, &ok, m_pDoc );
	if ( !ok ) LOWER_THRESHOLD = 0.30;

	if( UPPER_THRESHOLD < LOWER_THRESHOLD ) UPPER_THRESHOLD = LOWER_THRESHOLD;

	double affixness;

	ComponentMap* pComponents = m_pCompounds->GetComponentMap();
	CCompound*    pCompound;
	CEdge*        pEdge;
	CParse        parse;
	QString       component, word;
	StemSet*      pStemSet;
	SuffixSet*    pSuffixSet;
	PrefixSet*    pPrefixSet;
	CStem*        pStem, *pWord;
	CSuffix*      pSuffix;
	CPrefix*      pPrefix;
	CMiniLexicon* pMini;

        QList<CCompound*> cmpdDeletions;
        QList<CMiniLexicon*> affectedMinis;

	for( int i = 0; i < m_pCompounds->GetCount(); i++ )
	{
		pCompound = m_pCompounds->GetAt(i);

                QList<CEdge*> edgeDeletions;

                for( pEdge = pCompound->GetParses()->first(); pEdge; pEdge = pCompound->GetParses()->next() )
                //for (int z= 0; z < pCompound->GetParses()->size(); z++)
                {//       pEdge = pCompound->GetParses()->at(z);
			pEdge->GetParse( &parse );

			for( int j = 1; j <= parse.Size(); j++ )
			{
				component = parse.GetPiece(j).Display();
				if( pComponents->find( component ) == pComponents->end() ) continue;

				pStemSet = pComponents->find( component ).data();

				affixness = pStemSet->at(0)->GetAffixness();

				// Remove compounds which have a component whose affixness
				// exceeds the upper affixness threshold
				if( affixness >= UPPER_THRESHOLD )
				{
                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                        for (int y = 0; y < pStemSet->size(); y++)
                                        {   pStem = pStemSet->at(y);
                                            pStem->SetCompoundCount( 0.0 );
                                            edgeDeletions.append( pEdge );
					}
				}


				// Remove suffixes whose corresponding component's affixness
				// is below the lower affixness threshold
				if( affixness <= LOWER_THRESHOLD && affixness > 0 )
				{
					// Must exist as suffix or prefix also
					pSuffixSet = m_AllSuffixes[ component ];
					bool isSuffix = TRUE;
					if( !pSuffixSet ) 
					{
						pPrefixSet = m_AllPrefixes[ component ];
						isSuffix = FALSE;
						if( !pPrefixSet ) continue;
					}

					if( isSuffix )
					{
                                                //for( pSuffix = pSuffixSet->first(); pSuffix; pSuffix = pSuffixSet->next() )
                                                for (int z = 0; z < pSuffixSet->size(); z++)
                                                {       pSuffix = pSuffixSet->at(z);
							pMini = pSuffix->GetMyMini();
							pStemSet = pSuffix->GetStems();

                                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                                        for (int y = 0; y < pStemSet->size(); y++)
                                                        {       pStem = pStemSet->at(y);
								word = pStem->Display() + pSuffix->Display();

								pWord = (*pMini->GetWords()) ^= CSS( word );

								pWord->ClearParseStructure();

                                                                if( affectedMinis.indexOf( pMini ) < 0 ) affectedMinis.append( pMini );
							}
						}							
					}
					else
					{
                                                //for( pPrefix = pPrefixSet->first(); pPrefix; pPrefix = pPrefixSet->next() )
                                                for (int z= 0; z < pPrefixSet->size(); z++)
                                                {       pPrefix = pPrefixSet->at(z);
							pMini = pPrefix->GetMyMini();
							pStemSet = pPrefix->GetStems();

                                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                                        for (int z = 0; z < pStemSet->size(); z++)
                                                        {       pStem = pStemSet->at(z);
								word = pPrefix->Display() + pStem->Display();
								pWord = (*pMini->GetWords()) ^= CSS( word );
								pWord->ClearParseStructure();
                                                                if( affectedMinis.indexOf( pMini ) < 0 ) affectedMinis.append( pMini );
							}
						}
					}
				}
			}
		}

		// Remove all edges marked for deletion
                //for( pEdge = edgeDeletions.first(); pEdge; pEdge = edgeDeletions.next() )
                for (int z=0; z < edgeDeletions.size(); z++)
                {   pEdge = edgeDeletions.at(z);
                    pCompound->RemoveParse( pEdge );
		}
		
		if( pCompound->GetParses()->count() == 0 )
		{
			cmpdDeletions.append( pCompound );
		}
		else if( pCompound->GetBestParse() < 0 ) pCompound->SetBestParse( 0 );
	}

	// Remove all compounds marked for deletion
        //for( pCompound = cmpdDeletions.first(); pCompound; pCompound = cmpdDeletions.next() )
        for (int z= 0; z < cmpdDeletions.size(); z++)
        {   pCompound = cmpdDeletions.at(z);
		m_pCompounds->RemoveMember( pCompound );
	}

	// Update all affected minis
	QString strAffixness = "Affixness";
	CStringSurrogate cssAffixness( strAffixness );
        //for( pMini = affectedMinis.first(); pMini; pMini = affectedMinis.next() )
        for (int z = 0; z < affectedMinis.size(); z++)
        {   pMini = affectedMinis.at(z);
            pMini->TakeSplitWords_ProduceStemsAndSigs( cssAffixness );
	}

	// Check validity of compounds
	m_pCompounds->CheckAndRecount();
}

