// Description length bookkeeping and display for a single phoneme
// Copyright © 2009 The University of Chicago
#ifndef PHONE_H
#define PHONE_H

class CPhoneListViewItem;
class CPhone; 
 
#include <Q3ListViewItem>
#include "LParse.h"

#include <QString>
#include "StringSurrogate.h"
#include "generaldefinitions.h"
#include "CompareFunc.h"

class CPhoneListViewItem : public Q3ListViewItem {
	CPhone* m_MyPhone;
public:
	// construction/destruction.

	CPhoneListViewItem(Q3ListView* parent = 0,
		QString phoneme_text = QString(), CPhone* phoneme = 0);
	CPhoneListViewItem(Q3ListViewItem* parent,
		QString phoneme_text = QString(), CPhone* phoneme = 0);
	// implicitly defined destructor

	// copy.

	CPhoneListViewItem(const CPhoneListViewItem& x)
		: Q3ListViewItem(x), m_MyPhone(x.m_MyPhone) { }
	CPhoneListViewItem& operator=(const CPhoneListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_MyPhone = x.m_MyPhone;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	int compare(Q3ListViewItem* other, int column, bool ascending) const;
	virtual QString key(int column, bool ascending) const;

	// underlying unigram object.

	CPhone* GetPhone() const { return m_MyPhone; }
	void SetPhone(CPhone* pPhone) { m_MyPhone = pPhone; }
};
 
class CPhone  : public CLParse
{
public:
	CPhone(CMiniLexicon* mini = NULL);
	CPhone(QString&, CMiniLexicon* mini = NULL);
	CPhone(CStringSurrogate, CMiniLexicon* mini = NULL);
	virtual ~CPhone();
	bool		operator==(CPhone& );
	bool		operator<( CPhone& );

 	double		m_LogFreq;
	double		m_Frequency;
	void		SetLogFreq (double);
	void		PhoneListDisplay( Q3ListView*);
	static		ePhoneSortStyle		m_SortStyle;

	
};
 
#endif // PHONE_H
