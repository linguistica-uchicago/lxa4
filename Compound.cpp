// Implementation of CCompound, CCompoundListViewItem methods
// Copyright © 2009 The University of Chicago
#include "Compound.h"

#include <QList>
#include "Lexicon.h"
#include "Linker.h"
#include "Edge.h"
#include "Stem.h"
#include "CompoundCollection.h"
#include "LinkerCollection.h"
#include "StringFunc.h"
#include "Typedefs.h"

CCompoundListViewItem::CCompoundListViewItem( Q3ListView *parent,
											  QString compound,
											  CCompound* pCompound,
											  int parse,
											  double score,
											  QString mostFreqPiece,
											  double MFPCount,
											  QString pieceCounts,
											  double prefixness,
											  double suffixness,
											  int parseCount,
											  StringToString* filter )
: Q3ListViewItem( parent, compound )
{
	m_compound = pCompound;
	m_parse = parse;
	m_score = score;
	m_mostFreqPiece = mostFreqPiece;
	m_MFPCount = MFPCount;
	m_pieceCounts = pieceCounts;
	m_prefixness = prefixness;
	m_suffixness = suffixness;
	m_parseCount = parseCount;
	m_filter = filter;
}


CCompoundListViewItem::CCompoundListViewItem( Q3ListViewItem *parent,
											  QString compound,
											  CCompound* pCompound,
											  int parse,
											  double score,
											  QString mostFreqPiece,
											  double MFPCount,
											  QString pieceCounts,
											  double prefixness,
											  double suffixness,
											  int parseCount,
											  StringToString* filter )
: Q3ListViewItem( parent, compound )
{
	m_compound = pCompound;
	m_parse = parse;
	m_score = score;
	m_mostFreqPiece = mostFreqPiece;
	m_MFPCount = MFPCount;
	m_pieceCounts = pieceCounts;
	m_prefixness = prefixness;
	m_suffixness = suffixness;
	m_parseCount = parseCount;
	m_filter = filter;
}


QString CCompoundListViewItem::key(int col, bool asc) const
{
	switch (col) {
	case 1:
		return QString("%1").arg(m_parseCount, 10);
	case 2:
		return QString("%1").arg(static_cast<int>(
			1000 * m_MFPCount), 10);
	case 3:
		return QString("%1").arg(static_cast<int>(
			1000 * m_prefixness), 10);
	case 4:
		return QString("%1").arg(static_cast<int>(
			1000 * m_suffixness), 10);
	default:
		return Q3ListViewItem::key(col, asc);
	}
}

QString CCompoundListViewItem::text(int col) const
{
	switch (col) {
	case 1:
		return QString::number(m_parseCount);
	case 2:
		if (m_parse < 0)
			return QString();
		return Filter(m_filter, m_mostFreqPiece);
	case 3:
		if (m_parse < 0)
			return QString();
		return QString::number(m_prefixness, 'f', 4);
	case 4:
		if (m_parse < 0)
			return QString();
		return QString::number(m_suffixness, 'f', 4);
	default:
		return Q3ListViewItem::text(col);
	}
}

CCompound::CCompound( CMiniLexicon* mini ) : CLParse( mini )
{
	m_MyComponents = new Components();
	m_MyLinkers    = new Linkers();
	m_Parses     = NULL;
	m_BestParse  = -1;
	m_pLexicon   = NULL;
}



CCompound::CCompound ( const CStringSurrogate& SS, CMiniLexicon* mini ) : CLParse (SS, mini)
{
	m_MyComponents = new Components();
	m_MyLinkers    = new Linkers();
	m_Parses     = NULL;
	m_BestParse  = -1;
	m_pLexicon   = NULL;
}


CCompound::~CCompound()
{
	if( m_MyComponents ) delete m_MyComponents;
	if( m_MyLinkers ) delete m_MyLinkers;
	if( m_Parses ) delete m_Parses;
}



void CCompound::CompoundListDisplay( Q3ListView* List, StringToString* filter, QChar separator )
{
	int i;
	
double usage, score, 
		   MFPCount = 0.0,
		   mostMFPCount = 0.0,
		   bestScore = 0.0,
		   prefixness = 0.0,
		   suffixness = 0.0,
		   highest_prefixness = 0.0,
		   highest_suffixness = 0.0;
	
	usage = 0.0;
	score = 0.0;
	
	QStringList pieceCounts;
	QString mostFreqStem;

	CStem* pStem;
	CLinker* pLinker;
	CParse parse;

	StemSet* pStemSet;

	int MINIMUM_STEM_LENGTH = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );

	CCompoundListViewItem* parent, * item;

	if( m_Parses )
	{
		CEdge* pEdge;
		int index = 0;

		if( m_Parses->count() > 1 )
		{
			parent = new CCompoundListViewItem( List, Display( filter ), this, -1, 0.0, QString::null, 0.0, QString::null, 0.0, 0.0, m_Parses->count(), filter );
			parent->setOpen( TRUE );

			int parseNumber = 0;
                        for( pEdge = m_Parses->first(); pEdge; pEdge = m_Parses->next() )
                        //for (int z = 0; z < m_Parses->size(); z++)
                        {     //  pEdge = m_Parses->at(z);
				pEdge->GetParse( &parse );

				mostMFPCount = 0.0;
				bestScore = 0.0;

				pieceCounts.clear();

				score = 1.0;
				for( i = 1; i <= parse.Size(); i++ )
				{
					pLinker = NULL;
					pStemSet = NULL;

					if( parse.GetPiece(i).Display().length() >= MINIMUM_STEM_LENGTH )
					{
						pStemSet = m_pLexicon->GetAllStems()->find( parse.GetPiece(i).Display() );
						if( !pStemSet ) pStemSet = m_pLexicon->GetAllWords()->find( parse.GetPiece(i).Display() );
					}

					if( !pStemSet ) pLinker = *m_pLexicon->GetLinkers() ^= parse.GetPiece(i);

					if( pStemSet || pLinker )
					{
						if( pLinker ) 
						{
							usage = 2.0; // This gives us the identity (when 1 is subtracted) for linking elements, we don't want to count them
							pieceCounts.append( QString("%1").arg( pLinker->GetCompoundCount(), 0, 'f', 1 ) );
						}
						else 
						{
                                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                                        for (int z= 0; z < pStemSet->size(); z++)
                                                        {       pStem = pStemSet->at(z);
								usage = pStem->GetCompoundCount();
								pieceCounts.append( QString("%1").arg( usage, 0, 'f', 1 ) );

								if( usage == 0.0 ) continue;

								if( usage > MFPCount )
								{
									mostFreqStem = pStem->Display();
									MFPCount = usage;
								}

								break;
							}
						}
					}
					else 
					{
						score = -1.0;
						break;
					}

					score *= usage - 1.0;

					if( pStemSet && i == 1 ) prefixness = pStemSet->at(0)->GetAffixness();
					if( pStemSet && i == parse.Size() ) suffixness = pStemSet->at(0)->GetAffixness();
				}

				if( MFPCount > mostMFPCount ) parent->SetMFSCount( MFPCount );
				if( score > bestScore ) parent->SetScore( score );
				if( prefixness > highest_prefixness ) parent->SetPrefixness( prefixness );
				if( suffixness > highest_suffixness ) parent->SetSuffixness( suffixness );

				if( parseNumber == GetBestParse() )
				{
					item = new CCompoundListViewItem( parent, "*" + parse.Display( separator, filter ), 
													  this, index++, score, mostFreqStem, MFPCount, 
													  pieceCounts.join(", "),
													  prefixness, suffixness, 1, filter );
				}
				else
				{
					item = new CCompoundListViewItem( parent, parse.Display( separator, filter ), 
													  this, index++, score, mostFreqStem, MFPCount, 
													  pieceCounts.join(", "),
													  prefixness, suffixness, 1, filter );
				}
				parseNumber++;
			}
		}
		else 
		{
			m_Parses->first()->GetParse( &parse );

			score = 1.0;
			for( i = 1; i <= parse.Size(); i++ )
			{
				pLinker = NULL;

				pStemSet = NULL;

				if( parse.GetPiece(i).Display().length() >= MINIMUM_STEM_LENGTH )
				{
					pStemSet = m_pLexicon->GetAllStems()->find( parse.GetPiece(i).Display() );
					if( !pStemSet ) pStemSet = m_pLexicon->GetAllWords()->find( parse.GetPiece(i).Display() );
				}
				
				if( !pStemSet ) pLinker = *m_pLexicon->GetLinkers() ^= parse.GetPiece(i);

				if( pStemSet || pLinker )
				{
					if( pLinker ) 
					{
						usage = 2.0; // This gives us the identity (when 1 is subtracted) for linking elements, we don't want to count them
						pieceCounts.append( QString("%1").arg( pLinker->GetCompoundCount(), 0, 'f', 1 ) );
					}
					else 
					{
                                                //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                                for (int z = 0; z < pStemSet->size(); z++)
                                                {       pStem = pStemSet->at(z);
							usage = pStem->GetCompoundCount();
							pieceCounts.append( QString("%1").arg( usage, 0, 'f', 1 ) );

							if( usage == 0.0 ) continue;

							if( usage > MFPCount )
							{
								mostFreqStem = pStem->Display();
								MFPCount = usage;
							}

							break;
						}
					}
				}
				else 
				{
					score = -1.0;
					break;
				}

				score *= usage - 1.0;

				if( pStemSet && i == 1 ) prefixness = pStemSet->at(0)->GetAffixness();
				if( pStemSet && i == parse.Size() ) suffixness = pStemSet->at(0)->GetAffixness();
			}

			m_Parses->first()->GetParse( &parse );
			item = new CCompoundListViewItem( List, parse.Display( separator, filter ), 
											  this, index++, score, mostFreqStem, MFPCount,
											  pieceCounts.join(", "),
											  prefixness, suffixness, m_Parses->count(), filter );
		}
	}	
	else
	{
		item = new CCompoundListViewItem( List, Display( separator, filter ), this );
	}
}


void CCompound::DetachAllPieces()
{
	CLinker* pLinker;

	// Not necessary unless we have some tracking of compounds going on in 
	// the stems, which we don't ... yet. (TODO : this + corpus count?)
	m_MyComponents->clear();

	Linkers::Iterator it;
	for( it = m_MyLinkers->begin(); it != m_MyLinkers->end(); ++it )
	{
		pLinker = it.data();

		pLinker->IncrementCorpusCount( -1 * GetCorpusCount() );

		// The linker is not deleted because it may be part of another
		// parse of the same compound
	}
	m_MyLinkers->clear();
}


void CCompound::SetBestParse(int i)
{
        if (i >= 0 && static_cast<int>(i) >= m_Parses->count())
		return;
	if (i < 0) {
		m_BestParse = i;
		return;
	}

	const int MINIMUM_STEM_LENGTH = m_pLexicon->GetIntParameter(
		"Main\\MinimumStemLength", 3);

	CEdge* pEdge = m_Parses->at(i);
	CParse oneParse;
	pEdge->GetParse(&oneParse);
	this->Collapse(CStringSurrogate(oneParse.Display('.')), '.');

	// Detach components from stems and linkers
	DetachAllPieces();

	// Attach components to stems and linkers
	for (int j = 1; j <= Size(); ++j) {
		CStringSurrogate piece_surrogate = GetPiece(j);
		QString piece = piece_surrogate.Display();

                QList<CStem*>* pStemSet = 0;

		if (oneParse.GetPiece(j).Display().size() >=
				MINIMUM_STEM_LENGTH) {
			pStemSet = m_pLexicon->GetAllStems()->find(piece);
			if (pStemSet == 0)
				pStemSet = m_pLexicon->GetAllWords()->find(
					piece);
		}

		if (pStemSet != 0) {
			m_MyComponents->insert(j, pStemSet);
			// XXX. corpus count?
		} else {
			// it is a linker element
			if (CLinker* pLinker = *m_pLexicon->GetLinkers() ^=
				piece_surrogate) {
					m_MyLinkers->insert(j, pLinker);
					pLinker->IncrementCorpusCount(
						GetCorpusCount());
			}
		}
	}
	m_BestParse = i;
}

void CCompound::SetParses( Q3PtrList<CEdge>* parses, double* pComponentCount, double* pLinkerCount )
{ 
	CStem* pStem;
	CEdge* pEdge;
	CParse oneParse;
	QString compound;
	CSS ssCompound;
	CLinker* pLinker;
	StemSet* pStemSet;
	
// unused variable 'componentCoun'
//	double componentCount = 0.0;

	ComponentMap* allComponents = m_pLexicon->GetCompounds()->GetComponentMap();
	
	int MINIMUM_STEM_LENGTH = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );

	// Detach components, stems, and linkers
	if( m_Parses )
	{
                for( pEdge = m_Parses->first(); pEdge; pEdge = m_Parses->next() )
                //for (int z = 0; z < m_Parses->size(); z++)
                {    //   pEdge = m_Parses->at(z);
			pEdge->GetParse( &oneParse );
			compound = oneParse.Display('.');
			ssCompound = compound;
			oneParse.Collapse( ssCompound, '.' );	

			for( int j = 1; j <= oneParse.Size(); j++ )
			{		
				pStemSet = NULL;
				if( allComponents->find( oneParse.GetPiece(j).Display() ) != allComponents->end() )
				{
					pStemSet = allComponents->find( oneParse.GetPiece(j).Display() ).data();
				}

				if( pStemSet )
				{
					// TODO: remove stem to compound links (these don't exist yet)
                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                        for (int z= 0; z < pStemSet->size(); z++)
                                        {       pStem = pStemSet->at(z);
						pStem->IncrementCompoundCount(
							-double(GetCorpusCount()) /
							m_Parses->count());
						if( pStem->GetCompoundCount() <= 0.0 )
						{
							allComponents->remove( oneParse.GetPiece(j).Display() );
							pStem->SetCompoundCount( 0.0 );
							pStem = NULL;
						}
					}
				}
				else
				{
					// It is a linker element
					pLinker = *m_pLexicon->GetLinkers() ^= oneParse.GetPiece(j);

					if( pLinker ) 
					{
						pLinker->RemoveCompound( this );
						pLinker->IncrementCompoundCount(
							-double(1.0) /
							m_Parses->count());
						pLinker->IncrementCorpusCount(
							// XXX. why integer?
							static_cast<int>(
								double(-1) *
								GetCorpusCount() /
								m_Parses->count()));

						if( pLinker->GetCompoundCount() <= 0.0 ) 
						{
							m_pLexicon->GetLinkers()->RemoveMember( pLinker );
							pLinker = NULL;
						}
					}
				}
			}
		}
	}

	if( m_Parses ) delete m_Parses; 
        m_Parses = parses;

        for( pEdge = m_Parses->first(); pEdge; pEdge = m_Parses->next() )
        //for (int z = 0; z < m_Parses->size(); z++)
        {       //pEdge = m_Parses->at(z);
		pEdge->GetParse( &oneParse );

		compound = oneParse.Display('.');
		ssCompound = compound;
		oneParse.Collapse( ssCompound, '.' );	

		// Attach components, stems, and linkers
		for( int j = 1; j <= oneParse.Size(); j++ )
		{		
			pStemSet = NULL;

			if( allComponents->find( oneParse.GetPiece(j).Display() ) != allComponents->end() )
			{
				pStemSet = allComponents->find( oneParse.GetPiece(j).Display() ).data();
			}
			else if( oneParse.GetPiece(j).Display().length() >= MINIMUM_STEM_LENGTH )
			{		
				pStemSet = m_pLexicon->GetAllStems()->find( oneParse.GetPiece(j).Display() );

				if( !pStemSet ) pStemSet = m_pLexicon->GetAllWords()->find( oneParse.GetPiece(j).Display() );

				if( pStemSet ) allComponents->insert( oneParse.GetPiece(j).Display(), pStemSet );
			}

			if( pStemSet ) 
			{
				m_MyComponents->insert( j, pStemSet );
                                //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                for (int z = 0; z < pStemSet->size(); z++)
                                {
                                        pStem= pStemSet->at(z);
					pStem->IncrementCompoundCount(
						double(GetCorpusCount()) /
						m_Parses->count());
				}

				*pComponentCount +=
					double(1.0) / m_Parses->count();
			}
			else
			{
				// It is a linker element
				pLinker = *m_pLexicon->GetLinkers() << oneParse.GetPiece(j);

				if( pLinker ) 
				{
					m_MyLinkers->insert( j, pLinker );
					pLinker->AddCompound( this );
					pLinker->IncrementCompoundCount(
						double(1.0) /
						m_Parses->count());
					pLinker->IncrementCorpusCount(
						// XXX. why integer?
						static_cast<int>(
							double(GetCorpusCount()) /
							m_Parses->count()));
					*pLinkerCount += double(1.0) /
						m_Parses->count();
				}
			}
		}
	}
}


void CCompound::AddParse( CEdge* pEdge )
{
	CStem* pStem;
	CEdge* qEdge;
	CParse oneParse;
	QString compound;
	CSS ssCompound;
	CLinker* pLinker;
	StemSet* pStemSet;

	if( !pEdge ) return;
	
	int MINIMUM_STEM_LENGTH = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );

	m_Parses->append( pEdge );

        for( qEdge = m_Parses->first(); qEdge; qEdge = m_Parses->next() )
        //for (int z =0; z < m_Parses->size(); z++)
        {       //qEdge = m_Parses->at(z);
		qEdge->GetParse( &oneParse );
		compound = oneParse.Display('.');
		ssCompound = compound;
		oneParse.Collapse( ssCompound, '.' );	

		// Attach components, stems, and linkers
		// Recalculate counts
		for( int j = 1; j <= oneParse.Size(); j++ )
		{
			pStemSet = NULL;

			if( oneParse.GetPiece(j).Display().length() >= MINIMUM_STEM_LENGTH )
			{
				pStemSet = m_pLexicon->GetAllStems()->find( oneParse.GetPiece(j).Display() );

				if( !pStemSet ) pStemSet = m_pLexicon->GetAllWords()->find( oneParse.GetPiece(j).Display() );
			}
			
			if( pStemSet ) 
			{
				if( qEdge == pEdge )
				{
					m_MyComponents->insert( j, pStemSet );
					// TODO: add stem to compound links
				}
				else
				{
                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                         for (int z = 0; z < pStemSet->size(); z++)
                                         {      pStem = pStemSet->at(z);
                                                pStem->IncrementCompoundCount(
							-double(GetCorpusCount()) /
							(double(m_Parses->count()) -
								1.0));
                                            }
				}

                                //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                for (int z = 0; z < pStemSet->size(); z++)
                                {   pStem  = pStemSet->at(z);
                                    pStem->IncrementCompoundCount(
						double(GetCorpusCount()) /
						m_Parses->count());
                                }
			}
			else
			{
				// It is a linker element
				pLinker = *m_pLexicon->GetLinkers() << oneParse.GetPiece(j);

				if( pLinker ) 
				{
					if( qEdge == pEdge )
					{
						m_MyLinkers->insert( j, pLinker );
						pLinker->AddCompound( this );
					}
					else
					{
						pLinker->IncrementCompoundCount(
							-double(1.0) /
							(double(m_Parses->count()) -
								1.0));
						pLinker->IncrementCorpusCount(
							// XXX. why integer?
							static_cast<int>(
							-double(GetCorpusCount()) /
							(double(m_Parses->count()) -
								1.0)));
					}
					
					pLinker->IncrementCompoundCount(
						// XXX. why integer?
						static_cast<int>(
							double(1.0) /
							m_Parses->count()));
					pLinker->IncrementCorpusCount(
						// XXX. why integer?
						static_cast<int>(
							double(GetCorpusCount()) /
							m_Parses->count()));
				}
			}
		}
	}
}


bool CCompound::RemoveParse( CEdge* pEdge )
{
        CStem*      pStem;
        CEdge*      qEdge;
        CParse      oneParse;
        QString     compound;
        CSS         ssCompound;
        CLinker*    pLinker;
        StemSet*    pStemSet;

	if( !pEdge ) return FALSE;

	int MINIMUM_STEM_LENGTH = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );

        int pos = m_Parses->find( pEdge );
	if( pos < 0 ) return FALSE;

        for( qEdge = m_Parses->first(); qEdge; qEdge = m_Parses->next() )
        //for (int z = 0; z < m_Parses->size(); z++)
        {
           //   qEdge = m_Parses->at(z);
		qEdge->GetParse( &oneParse );
		compound = oneParse.Display('.');
		ssCompound = compound;
		oneParse.Collapse( ssCompound, '.' );	

		// Attach components, stems, and linkers
		// Recalculate counts
		for( int j = 1; j <= oneParse.Size(); j++ )
		{
			pStemSet = NULL;

			if( oneParse.GetPiece(j).Display().length() >= MINIMUM_STEM_LENGTH )
			{
				pStemSet = m_pLexicon->GetAllStems()->find( oneParse.GetPiece(j).Display() );

				if( !pStemSet ) pStemSet = m_pLexicon->GetAllWords()->find( oneParse.GetPiece(j).Display() );
			}

			if( pStemSet ) 
			{
				if( qEdge == pEdge )
				{
					// TODO: remove stem to compound links
				}
				else
				{
                                        //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                        for (int y = 0; y < pStemSet->size(); y++)
                                        {       pStem  = pStemSet->at(y);
						pStem->IncrementCompoundCount(
							double(GetCorpusCount()) /
							(double(m_Parses->count()) -
								1.0));
                                        }
				}

                                //for( pStem = pStemSet->first(); pStem; pStem = pStemSet->next() )
                                for (int w = 0; w < pStemSet->size(); w++)
                                {   pStem= pStemSet->at(w);
                                    pStem->IncrementCompoundCount(
						-double(GetCorpusCount()) /
						m_Parses->count());
                                }
			}
			else
			{
				// It is a linker element
				pLinker = *m_pLexicon->GetLinkers() << oneParse.GetPiece(j);

				if( pLinker ) 
				{
					if( qEdge == pEdge )
					{
						pLinker->RemoveCompound( this );
					}
					else
					{						
						pLinker->IncrementCompoundCount(
							double(1.0) /
							(double(m_Parses->count()) -
								1.0));
						pLinker->IncrementCorpusCount(
							static_cast<int>(
							double(GetCorpusCount()) /
							(double(m_Parses->count()) -
								1.0)));
					}

					pLinker->IncrementCompoundCount(
						-double(1.0) / m_Parses->count());
					pLinker->IncrementCorpusCount(
						// XXX. why integer?
						static_cast<int>(
						-double(GetCorpusCount()) /
						m_Parses->count()));

					if( pLinker->GetCompoundCount() <= 0.0 ) 
					{
						m_pLexicon->GetLinkers()->RemoveMember( pLinker );
					}
				}
			}
		}
	}

        m_Parses->remove( qEdge ) ; //@@@@ check that this is right -- JG

	if( pos == m_BestParse ) SetBestParse(-1); 

	return TRUE;
}


StemSet* CCompound::GetComponent( int i ) const
{ 
	if( m_MyComponents->find(i) == m_MyComponents->end() ) return NULL; 
	return m_MyComponents->find(i).data();
}


CLinker* CCompound::GetLinker( int i ) const
{
	if( m_MyLinkers->find(i) == m_MyLinkers->end() ) return NULL;
	return m_MyLinkers->find(i).data();
}


double CCompound::GetPrefixness()
{
	StemSet* compound = GetComponent(0);
	if( compound ) return compound->first()->GetAffixness();
	else return 0.0;
}


double CCompound::GetSuffixness()
{
	StemSet* compound = GetComponent( m_MyComponents->count() - 1 );
	if( compound ) return compound->first()->GetAffixness();
	else return 0.0;
}


QString CCompound::DisplayParse( int i, StringToString* filter )
{
	CEdge* pEdge = m_Parses->at(i);	
	if( !pEdge ) return "";
	
	return pEdge->DisplayParse( filter );
}
	



