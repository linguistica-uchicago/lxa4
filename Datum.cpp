// Implemenation of CDatum, CDatumListViewItem methods
// Copyright © 2009 The University of Chicago
#include "Datum.h"

#include "VeryLong.h"
#include "Typedefs.h"

CDatumListViewItem::CDatumListViewItem( Q3ListView *parent )
: Q3ListViewItem( parent )
{}


CDatumListViewItem::CDatumListViewItem( Q3ListView *parent,
										QString affix, 
										CDatum* pDatum )
: Q3ListViewItem( parent, affix )
{
	m_datum = pDatum;
}


CDatumListViewItem::CDatumListViewItem( Q3ListViewItem *parent,
										QString affix,
										CDatum* pDatum )
: Q3ListViewItem( parent, affix )
{
	m_datum = pDatum;
}


QString CDatumListViewItem::key( int column, bool ascending ) const
{
	switch( column )
	{
	case 1:
		return QString("%1").arg( m_datum->m_Count, 10 );
	case 2:
		return QString("%1").arg( m_datum->m_Frequency, 10 );
	default:
		return Q3ListViewItem::key( column, ascending );
	}
}


QString CDatumListViewItem::text( int column ) const
{
	switch(	column )
	{
	case 1:
		return QString("%1").arg( m_datum->m_Count );
	case 2:
		return QString("%1").arg( m_datum->m_Frequency );
	default:
		return Q3ListViewItem::text( column );
	}
}

CDatum::CDatum() : CParse() 
{
	m_Count = 0;
	m_Frequency = 0;
}
 

CDatum::CDatum( CParse& parse ) : CParse( parse ) 
{
	m_Count = 1;
	m_Frequency = 0;
 }
 
  
CDatum::CDatum ( QChar c ) : CParse ( c ) 
{
	m_Count = 1;
	m_Frequency = 0;
}

CDatum::CDatum( CSS& ssString ) : CParse( ssString )
{
	m_Count = 1;
	m_Frequency = 0;
}


void CDatum::SetFrequency( float f ) { m_Frequency=f; }


double CDatum::GetCount() { return m_Count; }


//CString CDatum::GetKey() { return Key; }


void CDatum::SetCount( double f ) { m_Count = f; }


void CDatum::IncrementCount( CVeryLong& VL )
{
	m_Count = m_Count + VL.ToDouble();
}

void CDatum::IncrementCount()
{
	m_Count++;
}
 

// this is normally found in MiniLexicon_deMarcken, which is temporarily not included.
/*
CDatum*	CMiniLexicon::LookUp ( QString s )
{
	if( m_DataMap.contains( s ) )
	{
		StringToDatum::Iterator it = m_DataMap.find( s );
		return &it.data();
	}

	return NULL;
}
*/


/*   todo: put this back
double CDatum::GetInformationContent( CMiniLexicon* lexicon )
{
	double	info = -1 * log( m_Frequency ) / log( 2 ),
			letterInfo;
	QChar	letter;
	CDatum* pLetter;
	
	CSS key = GetKey();

	for( int i = 0; i < key.GetLength(); i++ )
	{
		letter = key[i];
		pLetter = lexicon->LookUp( letter );
		letterInfo = -1 * log( pLetter->m_Frequency ) / log(2);

		info -= letterInfo;
	}

	return info * m_Count;
}
*/
