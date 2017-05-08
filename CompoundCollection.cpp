// Implementation of CCompoundCollection methods
// Copyright © 2009 The University of Chicago
#include "CompoundCollection.h"

#include <QList>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Linker.h"
#include "Edge.h"
#include "Stem.h"
#include "LinkerCollection.h"
#include "WordCollection.h"
#include "log2.h"

class CPhoneCollection;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompoundCollection::CCompoundCollection( CMiniLexicon* Lex )
{
	m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
	m_ComponentCount = 0.0;
	m_LinkerCount = 0.0;
}

CCompoundCollection::CCompoundCollection( CLexicon* Lex )
{
	m_pMiniLex = NULL;
	m_pLexicon = Lex;
	m_ComponentCount = 0.0;
	m_LinkerCount = 0.0;
}

CCompoundCollection::~CCompoundCollection()
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL;
	m_ComponentCount = 0.0;
	m_LinkerCount = 0.0;
}

/* TODO:
void CCompoundCollection::OutputCompounds (QString FileName)
{
  CStem* pCompound;        
  QFile  file( FileName );

  if( file.open( IO_WriteOnly ) )
  {
    QTextStream  outf( &file );
    outf.setEncoding ( QTextStream::Unicode );

    outf.setf(2);
	outf << "# Compound Count:" << endl;
    outf << GetCount();
	
	outf << endl << endl << "# Index Size Pieces CorpusCount PrefixLoc StemLoc SuffixLoc PrefixSig SuffixSig" << endl;

    Sort (KEY);
    for (int i = 0; i< (int)GetCount(); i++)
    {
      pCompound = GetAtSort(i);

      outf.width(6);
      outf << i << pCompound->Size() << " ";

      for ( int j = 1; j <= pCompound->Size(); j++ )
      {
        outf  << pCompound->GetPiece(j).Display( m_pLexicon->GetOutFilter() ) << " ";
      }
	  
      outf << pCompound->GetCorpusCount() << " "
           << pCompound->GetPrefixLoc() << " "
           << pCompound->GetStemLoc()  << " "
           << pCompound->GetSuffixLoc() << " ";
		   
      if ( pCompound->GetPrefixSignature() )
      {
        outf << pCompound->GetPrefixSignature()->Display( '.', m_pLexicon->GetOutFilter() ) << " ";
      }
      else outf << "NONE ";

      if ( pCompound->GetSuffixSignature() )
      {
        outf << pCompound->GetSuffixSignature()->Display( '.', m_pLexicon->GetOutFilter() ) << " ";
      }
      else outf << "NONE ";
	  
      outf << endl;
    }
    file.close();
  }
}
*/





void CCompoundCollection::FindMostProbableParse()
{
        QList<CStem*>*	stemSet;
	CMiniLexicon*		mini; 
	mini = NULL;
	
	CCompound*			pCompound;
	CLinker*			pLinker;
	CStem*				pStem;
	CEdge*				pEdge;
	CParse				oneParse;

	int				i, j;

	m_pLexicon->GetDocument()->setStatusBar1( "Counting Components" );

	Sort( KEY );

	for( i = 0; i < GetCount(); i++ )
	{
		m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
		pCompound = GetAtSort(i);

		double component_count,
			   parse_log_prob,
			   smallest_plog = 0.0;

		uint most_probable_parse = 0;

                for( pEdge = pCompound->GetParses()->first(); pEdge; pEdge = pCompound->GetParses()->next() )
                //for (int z = 0; z < pCompound->GetParses()->size(); z++)
                { //      pEdge = pCompound->GetParses()->at(z);
			pEdge->GetParse( &oneParse );
			parse_log_prob = 0.0;
			for( j = 1; j <= oneParse.Size(); j++ )
			{
				stemSet = m_pLexicon->GetStemSet( oneParse.GetPiece(j) );				
				if( stemSet )
				{
					// TODO: we might be adding the same stem more than once, check and fix
					component_count = 0.0;
                                        //for( pStem = stemSet->first(); pStem; pStem = stemSet->next() )
                                        for (int y = 0; y < stemSet->size(); y++)
                                        {       pStem = stemSet->at(y);
						component_count += pStem->GetCompoundCount();
					}

					parse_log_prob -= base2log( pStem->GetCompoundCount() / m_ComponentCount + m_LinkerCount );
				}
				else
				{
					// Since this is not in the list of stems, it could be an
					// unanalyzed word. We should only look at the last mini-
					// lexicon
					for( i = m_pLexicon->GetMiniSize(); i >= 0; i++ )
					{
						mini = m_pLexicon->GetMiniLexicon(i);
						if( mini )
						{
							pStem = *mini->GetWords() ^= oneParse.GetPiece(j);
							if( pStem )
							{
								parse_log_prob -= base2log( pStem->GetCompoundCount() / m_ComponentCount + m_LinkerCount );
							}
							break;
						}
					}

					// Otherwise must be a linker
					if( !mini )
					{
						pLinker = *m_pLexicon->GetLinkers() ^= oneParse.GetPiece(j);
						Q_ASSERT( pLinker );
						if( pLinker )
						{
							parse_log_prob -= base2log( pLinker->GetCompoundCount() / m_ComponentCount + m_LinkerCount );
						}
					}
				}
			}

			if( parse_log_prob < smallest_plog || smallest_plog == 0.0 ) 
			{
				smallest_plog = parse_log_prob;
                                most_probable_parse = pCompound->GetParses()->find( pEdge );
			}
		}
		pCompound->SetBestParse( most_probable_parse );

		m_pLexicon->UpdateCompound( pCompound->Display() );
	}

	m_pLexicon->GetDocument()->setStatusBar1( "" );
	m_pLexicon->GetDocument()->EndCountDown();
}


/*void CCompoundCollection::ChooseParseByProbability()
{
	uint i, j;
	CCompound* pCompound;
	CEdge* pEdge;

	m_pLexicon->GetDocument()->setStatusBar1( "Choosing best parses by stem size" );
	m_pLexicon->GetDocument()->ResetCountDown();

	Sort(KEY);
	for( i = 0; i < GetCount(); i++ )
	{
		m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
		pCompound = GetAtSort(i);

		if( !pCompound->GetParses() ) continue;

		int n = 1, bestScore = 0;
		for( pEdge = pCompound->GetParses()->first(); pEdge; pEdge = pCompound->GetParses()->next() )
		{
			int length, score = 0;;

			CParse parse = pEdge->GetParse();
			for( j = 1; j <= parse.Size(); j++ )
			{
				length = parse.GetPiece(j).GetLength();
				score += length*length;
			}

			if( bestScore < score ) 
			{
				bestScore = score;
				pCompound->SetBestParse( n );
				m_pLexicon->UpdateCompound( pCompound->Display() );
			}
			n++;
		}

		// Redo cuts
		pEdge = pCompound->GetParses()->at( pCompound->GetBestParse()-1 );
		CParse oneParse = pEdge->GetParse();
		QString compound = oneParse.Display('.');
		CSS ssCompound = compound;
		pCompound->Collapse( ssCompound, '.' );

		// Attach components to stems and linkers
		pCompound->DetachAllPieces();
		m_pLexicon->UpdateCompound( pCompound->Display() );

		Components* components = pCompound->GetComponents();
		Linkers* linkers = pCompound->GetLinkers();
		for( j = 1; j <= (int)pCompound->Size(); j++ )
		{
			CStem* qStem = *m_pLexicon->GetStems() ^= pCompound->GetPiece(j);

			if( !qStem ) qStem = *m_pLexicon->GetWords() ^= pCompound->GetPiece(j);

			if( qStem ) components->insert( j, qStem );
			else
			{
				// It is a linker element
				CLinker* pLinker = *m_pLexicon->GetLinkers() << pCompound->GetPiece(j);

				if( pLinker ) 
				{
					linkers->insert( j, pLinker );

					qStem = *m_pLexicon->GetStems() ^= pCompound->GetKey();

					if( !qStem ) qStem = *m_pLexicon->GetWords() ^= pCompound->GetKey();

					if( qStem ) pLinker->AddStem( qStem );
				}
			}
		}
	}
	
	m_pLexicon->GetDocument()->setStatusBar1( "" );
	m_pLexicon->GetDocument()->ResetCountDown();
}*/


void CCompoundCollection::CheckAndRecount()
{
	CCompound* pCompound;
	CEdge* pParse;

	CParse parse;

	StemSet* pStemSet;
	CStem* pStem;

        QList<CCompound*> invalidCmpds;

	// Reset all stem's compound counts to 0.0
	Q3DictIterator<StemSet> it( *m_pLexicon->GetAllStems() );
	for( ; it.current(); ++it )
	{
                //for( pStem = it.current()->first(); pStem; pStem = it.current()->next() )
                for (int z= 0; z < it.current()->size(); z++)
		{
                        pStem = it.current()->at(z);
			pStem->SetCompoundCount( 0.0 );
		}
	}

	it = Q3DictIterator<StemSet>( *m_pLexicon->GetAllWords() );
	for( ; it.current(); ++it )
	{
                //for( pStem = it.current()->first(); pStem; pStem = it.current()->next() )
                for (int z = 0; z < it.current()->size(); z++)
                {       pStem = it.current()->at(z);
			pStem->SetCompoundCount( 0.0 );
		}
	}

	// Count components and remove compounds with missing components
	for (int i = 0; i < GetCount(); ++i) {
		pCompound = GetAt(i);
		
                QList<CEdge*> invalidParses;

                for( pParse = pCompound->GetParses()->first(); pParse; pParse = pCompound->GetParses()->next() )
                //for (int z = 0; z < pCompound->GetParses()->size(); z++)
                {   //    pParse = pCompound->GetParses()->at(z);
			pParse->GetParse( &parse );

			for( int j = 1; j <= parse.Size(); j++ )
			{
				pStemSet = (*m_pLexicon->GetAllStems())[ parse.GetPiece(j).Display() ];
				if( !pStemSet ) pStemSet = (*m_pLexicon->GetAllWords())[ parse.GetPiece(j).Display() ];
				if( !pStemSet )
				{
					invalidParses.append( pParse );
					break;
				}	
				
                                //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                for (int y = 0; y < pStemSet->size(); y++)
                                {       pStem = pStemSet->at(y);
					pStem->IncrementCompoundCount(
						double(pCompound->GetCorpusCount()) /
						pCompound->GetParses()->count());
				}
			}
		}

		// Delete invalid parses
                //for( pParse = invalidParses.first(); pParse; pParse = invalidParses.next() )
                for (int x=0; x < invalidParses.size(); x++)
                {       pParse=invalidParses.at(x);
			pCompound->RemoveParse( pParse );
			m_pLexicon->UpdateCompound( pCompound->Display() );
		}

		if( pCompound->GetParses()->count() == 0 ) invalidCmpds.append( pCompound );
	}

	// Delete invalid compounds
        //for( pCompound = invalidCmpds.first(); pCompound; pCompound = invalidCmpds.next() )
        for (int w = 0; w < invalidCmpds.size(); w++)
        {       pCompound = invalidCmpds.at(w);
		m_pLexicon->UpdateCompound( pCompound->Display() );
		RemoveMember( pCompound );
	}
}




