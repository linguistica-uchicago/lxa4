// Implementation of LxPoS, GUIPOSListViewItem methods
// Copyright © 2009 The University of Chicago
#include "POS.h"
#include "CompareFunc.h"

// Construction/Destruction

LxPoS::LxPoS(CSignature* pSig, CMiniLexicon* mini)
	: CLParse(pSig, mini),
	m_Signature(pSig),
	m_SatelliteAffixes(),
	m_Robustness(0) { }

LxPoS::~LxPoS() { }

void LxPoS::ListDisplay(Q3ListView* pView, QString strPoS)
{ static_cast<void>(new GUIPOSListViewItem(pView, strPoS, this)); }

void LxPoS::ListDisplay(Q3ListViewItem* pViewItem, QString strPoS)
{ static_cast<void>(new GUIPOSListViewItem(pViewItem, strPoS, this)); }

GUIPOSListViewItem::GUIPOSListViewItem(Q3ListView* pView, QString string, LxPoS* lxPoS): Q3ListViewItem (pView, string)
{
    m_PoS = lxPoS;

}
GUIPOSListViewItem::GUIPOSListViewItem(Q3ListViewItem* pItem, QString string, LxPoS* lxPoS): Q3ListViewItem (pItem, string)
{

        m_PoS = lxPoS;

}

QString GUIPOSListViewItem::key(int /* column */, bool /* ascending */) const
{ return QString("%1").arg(m_PoS->GetRobustness(), 9); }

QString GUIPOSListViewItem::text( int column  ) const
{
    switch (column)
    {
    case (0):
        {
          return m_PoS->Display('-');
        }

    case (1):
        {
          return QString("%1").arg(m_PoS->GetRobustness());
        }

    default:
        return "TEST";
    }

}

int GUIPOSListViewItem::compare(Q3ListViewItem *item,
	int column, bool ascending) const
{
	if (column == 2)
		return MakeComparable(GetPoS()->GetRobustness(),
			static_cast<GUIPOSListViewItem*>(item)->GetPoS()
			->GetRobustness());
	else
		return Q3ListViewItem::compare(item, column, ascending);
}
