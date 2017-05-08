// Implementation of CLinker methods
// Copyright © 2009 The University of Chicago
#include "Linker.h"

#include <QList>
#include "Compound.h"

CLinkerListViewItem::CLinkerListViewItem( Q3ListView *parent,
										  QString linker,
										  CLinker* pLinker,
										  StringToString* filter )
: Q3ListViewItem( parent, linker )
{
	m_linker = pLinker;
	m_filter = filter;
}


CLinkerListViewItem::CLinkerListViewItem( Q3ListViewItem *parent,
										  QString linker,
										  CLinker* pLinker,
										  StringToString* filter )
: Q3ListViewItem( parent, linker )
{
	m_linker = pLinker;
	m_filter = filter;
}


QString CLinkerListViewItem::key( int column, bool ascending ) const
{
	QString compoundstring = "";
	int i;

	switch( column )
	{
	case 1:
		if( m_linker ) return QString("%1").arg( m_linker->GetCorpusCount(), 10 );
		else return "";
	case 2:
		if( m_linker ) return QString("%1").arg( (int)( 1000.0 * m_linker->GetCompoundCount() ), 10 );
		else return "";
	case 3:
		if( m_linker )
		{
			for( i = 0; i < m_linker->GetNumberOfCompounds(); i++ )
			{
				compoundstring.append( m_linker->GetAtCompound(i)->Display( QChar(0), m_filter ) + ", " );
			}
			compoundstring = compoundstring.left( compoundstring.length() - 2 );	
			return compoundstring;
		}
		else return "";
	default:
		return Q3ListViewItem::key( column, ascending );
	}
}


QString CLinkerListViewItem::text( int column ) const
{
	QString compoundstring = "";
	int i;

	switch( column )
	{
	case 1:
		if( m_linker ) return QString("%1").arg( m_linker->GetCorpusCount() );
		else return "";
	case 2:
		if( m_linker ) return QString("%1").arg( m_linker->GetCompoundCount() );
		else return "";
	case 3:
		if( m_linker )
		{
			for( i = 0; i < m_linker->GetNumberOfCompounds(); i++ )
			{
				compoundstring.append( m_linker->GetAtCompound(i)->Display( QChar(0), m_filter ) + ", " );
			}
			compoundstring = compoundstring.left( compoundstring.length() - 2 );	
			return compoundstring;
		}
		else return "";
	default:
		return Q3ListViewItem::text( column );
	}
}


//-----------------------------------------------------------------
// Constructors/Destructor
//-----------------------------------------------------------------

CLinker::CLinker( CMiniLexicon* mini ) : CAffix( mini )
{
	m_CompoundCount = 0.0;
        m_CompoundPtrList = new QList<CCompound*>();
}

/*
CLinker::CLinker(const QString Key, CMiniLexicon* mini ): CLParse(Key, mini)
{}
*/

CLinker::CLinker( const CStringSurrogate& Key, CMiniLexicon* mini ) : CAffix(Key, mini) 
{
	m_CompoundCount = 0.0;
        m_CompoundPtrList = new QList<CCompound*>();
}

CLinker::~CLinker()
{
	if( m_CompoundPtrList ) delete m_CompoundPtrList;
}



//-----------------------------------------------------------------
// Public accessor methods
//-----------------------------------------------------------------


// Create the list item to be displayed in
// the triscreen
//
// Parameters:
//		List - the list item to be built
//		Line - what line it will be displayed
//		on

void CLinker::ListDisplay(Q3ListView* List, QMap<QString, QString>* filter)
{
	static_cast<void>(new CLinkerListViewItem(List,
			Display(filter),
			this, filter));
}

//-----------------------------------------------------------------
// Public mutator methods
//-----------------------------------------------------------------

void CLinker::AddCompound( CCompound* compound )
{
        if( m_CompoundPtrList->indexOf( compound ) < 0 )
	{
		m_CompoundPtrList->append( compound );
	}
}


void CLinker::ClearCompoundPtrList()
{
	m_CompoundPtrList->clear();
}


void CLinker::RemoveCompound( CCompound* compound )
{
	m_CompoundPtrList->remove( compound );
}

double CLinker::GetLengthOfPointerToMe()
{ 
	return m_LengthOfPointerToMe;
}
