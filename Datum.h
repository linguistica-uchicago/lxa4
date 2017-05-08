// CDatum, CDatumListViewItem classes
// Copyright © 2009 The University of Chicago
#ifndef DATUM_H
#define DATUM_H

#include <qstring.h>
#include <q3textstream.h> 
#include <qdatetime.h>

#include <math.h> //log

#include "Parse.h"

#include <q3listview.h>

class CStringSurrogate;
class CMiniLexicon;
class CVeryLong;

class CDatum;

class CDatumListViewItem : public Q3ListViewItem
{
public:
	CDatumListViewItem( Q3ListView* parent = NULL );
	CDatumListViewItem( Q3ListView *parent, 
						 QString = QString::null,
						 CDatum* = NULL );
	CDatumListViewItem( Q3ListViewItem *parent, 
						 QString = QString::null,
						 CDatum* = NULL );

	virtual QString text ( int ) const;
	virtual QString key ( int, bool ) const;
	CDatum* GetDatum() { return m_datum; }
	void SetDatum( CDatum* pDatum ) { m_datum = pDatum; }
protected:
	CDatum* m_datum;
};


class CDatum : public CParse 
{

public:
	
	//CVeryLong	m_Count; //this should never get to zero.
	//CVeryLong	m_Frequency;//between 0 and 1; = this->Count / Lexicon->TotalCount
	double		m_Count; //this should never get to zero.
	double		m_Frequency;
	int			m_Index;

	
			CDatum();
			CDatum( CParse& );
			CDatum( QChar );
			CDatum( CStringSurrogate& );

	void	SetCount( double i );
	double	GetCount();
//	double	GetInformationContent( CMiniLexicon* Lexicon ); todo: put this back
	
	void	SetFrequency( float f );
	void	IncrementCount( CVeryLong& );
	void	IncrementCount();

};

#endif // DATUM_H
