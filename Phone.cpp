// Implementation of CPhone, CPhoneListViewItem methods
// Copyright © 2009 The University of Chicago
#include "Phone.h"

#include "Typedefs.h"

CPhoneListViewItem::CPhoneListViewItem( Q3ListView *parent,
										  QString Phone,										  
										  CPhone* pPhone
										   )
: Q3ListViewItem( parent, Phone  )
{
	m_MyPhone = pPhone;
 
}


CPhoneListViewItem::CPhoneListViewItem( Q3ListViewItem *parent,
										  QString Phone, 										 
										  CPhone* pPhone
										   )
: Q3ListViewItem( parent, Phone )
{
	m_MyPhone = pPhone;
 
}


QString CPhoneListViewItem::key( int column, bool ascending ) const
{
 
	switch(	column )
	{
	case 1: //counts
		return QString("%1").arg( m_MyPhone->GetCorpusCount(), 10 );
	case 2:
		return QString("%1").arg( (int)(m_MyPhone->m_LogFreq*1000), 10 ); 
//	case 3:
//		return QString("%1").arg( m_MyPhone->m_MI, 10 ); 
//	case 4:
//		 return QString("%1").arg( m_MyPhone->m_WMI, 10 ); 

	default:
		return Q3ListViewItem::key( column, ascending );
	}
}

QString CPhoneListViewItem::text( int column ) const
{

	switch(	column )
	{
	case 1: //counts
		return QString("%1").arg( m_MyPhone->GetCorpusCount() );
	case 2:
		return QString("%1").arg( m_MyPhone->m_LogFreq); 
//	case 3:
//		return QString("%1").arg( m_MyPhone->m_MI); 
//	case 4:
//		 return QString("%1").arg( m_MyPhone->m_WMI ); 
	default:
		return Q3ListViewItem::text( column );
	}
}
int  CPhoneListViewItem::compare(Q3ListViewItem *item, int col, bool asc) const
{
     if (col== 1)
     {
	    return MakeComparable(static_cast<CPhoneListViewItem*>(item)->GetPhone()->GetCorpusCount(),
	                                                            GetPhone()->GetCorpusCount()) ;
     }
      if (col== 2)
     {
	    return   MakeComparable(GetPhone()->m_LogFreq , ((CPhoneListViewItem*)item)->GetPhone()->m_LogFreq) ;
     }
 
     else
     {
        return Q3ListViewItem::compare(item, col, asc);
     }
}

enum ePhoneSortStyle			CPhone::m_SortStyle;

CPhone::CPhone(CSS Phone, CMiniLexicon* mini): CLParse (Phone,mini)
{


}
CPhone::~CPhone()
{

}
bool CPhone::operator==(CPhone& rhs)
{
	switch (m_SortStyle)
	{
	case PHONE_FREQ:
		{
			if (m_Frequency == rhs.m_Frequency )
				return TRUE;
			break;
		} 
	default:{
				return FALSE;
			}

	}
	return FALSE;
}
bool CPhone::operator<(CPhone& rhs)
{
	switch (m_SortStyle)
	{
	case PHONE_FREQ:
		{
			if (m_Frequency < rhs.m_Frequency )
				return TRUE;
			break;
		}
	
	 
	default:{
				return FALSE;
			}

	}
	return FALSE;
}
void CPhone::PhoneListDisplay(Q3ListView* List)
{
	static_cast<void>(new CPhoneListViewItem(
		List, Display(), this));
}


