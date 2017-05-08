// Implementation of CBiphone, CBiphoneListViewItem methods
// Copyright © 2009 The University of Chicago
#include "Biphone.h"
#include "CompareFunc.h"
#include <cmath>
#include "implicit_cast.h"

CBiphoneListViewItem::CBiphoneListViewItem(Q3ListView* parent,
	QString bigram_text, CBiphone* bigram)
	: Q3ListViewItem(parent, bigram_text), m_MyBiphone(bigram) { }

CBiphoneListViewItem::CBiphoneListViewItem(Q3ListViewItem* parent,
	QString bigram_text, CBiphone* bigram)
	: Q3ListViewItem(parent, bigram_text), m_MyBiphone(bigram) { }

QString CBiphoneListViewItem::text( int column ) const
{

	switch(	column )
	{
	case 1: //counts
		return QString("%1").arg( m_MyBiphone->GetCorpusCount() );
	case 2:
		return QString("%1").arg( m_MyBiphone->m_Freq); 
	case 3:
		return QString("%1").arg( -1 * m_MyBiphone->m_LogCondProb); 
	case 4:
		return QString("%1").arg( m_MyBiphone->m_LogCondProb); 
	case 5:
		return QString("%1").arg( m_MyBiphone->m_MI); 
	case 6:
		return QString("%1").arg( m_MyBiphone->m_WMI); 
	case 7:
		 return QString("%1").arg( m_MyBiphone->m_CondProb ); 
	case 8:
		 return QString("%1").arg( m_MyBiphone->m_NormalizedMI ); 
	default:
		return Q3ListViewItem::text( column );
	}
}

int CBiphoneListViewItem::compare(Q3ListViewItem* item, int col, bool asc) const
{
	const CBiphoneListViewItem& other =
		*static_cast<CBiphoneListViewItem*>(item);
	const CBiphone& this_biphone = *GetBiphone();
	const CBiphone& other_biphone = *other.GetBiphone();

	switch (col) {
	case 1:
		return MakeComparable(other_biphone.GetCorpusCount(),
			this_biphone.GetCorpusCount());
	case 2:
		return MakeComparable(this_biphone.m_Freq, other_biphone.m_Freq);
	case 3:
	case 4:
		return MakeComparable(this_biphone.m_LogCondProb,
			other_biphone.m_LogCondProb);
	case 5:
		return MakeComparable(this_biphone.m_MI,
			other_biphone.m_MI);
	case 6:
		return MakeComparable(this_biphone.m_WMI,
			other_biphone.m_WMI);
	case 8:
		return MakeComparable(this_biphone.m_NormalizedMI,
			other_biphone.m_NormalizedMI);
	default:
		return Q3ListViewItem::compare(item, col, asc);
	}
}

enum eBiphoneSortStyle			CBiphone::m_SortStyle;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace {
	using linguistica::implicit_cast;
}

CBiphone::CBiphone()
	: CLParse(implicit_cast<CMiniLexicon*, CMiniLexicon*>(0)),
	m_Key(),
	m_Freq(0.0),
	m_LogFreq(0.0),
	m_MI(0.0),
	m_WMI(0.0),
	m_LogCondProb(0.0),
	m_CondProb(0.0),
	m_NormalizedMI(0.0),
	m_MyFirst(), m_MySecond() { }

CBiphone::CBiphone(QString String)
	: CLParse(implicit_cast<CMiniLexicon*, CMiniLexicon*>(0)),
	m_Key(String),
	m_Freq(0.0),
	m_LogFreq(0.0),
	m_MI(0.0),
	m_WMI(0.0),
	m_LogCondProb(0.0),
	m_CondProb(0.0),
	m_NormalizedMI(0.0),
	m_MyFirst(), m_MySecond() { }

CBiphone::~CBiphone() { }

CBiphone::CBiphone(const CBiphone& x)
	: CLParse(implicit_cast<CMiniLexicon*, CMiniLexicon*>(0)),
	m_Key(x.m_Key),
	m_Freq(x.m_Freq),
	m_LogFreq(x.m_LogFreq),
	m_MI(x.m_MI),
	m_WMI(x.m_WMI),
	m_LogCondProb(x.m_LogCondProb),
	m_CondProb(x.m_CondProb),
	m_NormalizedMI(x.m_NormalizedMI),
	m_MyFirst(x.m_MyFirst), m_MySecond(x.m_MySecond) { }

CBiphone& CBiphone::operator=(const CBiphone& x)
{
	CLParse::operator=(x);
	m_Key = x.m_Key;
	m_Freq = x.m_Freq;
	m_LogFreq = x.m_LogFreq;
	m_MI = x.m_MI;
	m_WMI = x.m_WMI;
	m_LogCondProb = x.m_LogCondProb;
	m_CondProb = x.m_CondProb;
	m_NormalizedMI = x.m_NormalizedMI;
	m_MyFirst = x.m_MyFirst;
	m_MySecond = x.m_MySecond;
	return *this;
}

void CBiphone::SetMI (double mi ) { m_MI = mi ; }

bool CBiphone::operator==(const CBiphone& rhs)
{
	switch (m_SortStyle)
	{
	case WMI:{
				if (m_WMI == rhs.m_WMI)
					return TRUE;
					break;

			 }
	case MI:{
				if (m_MI == rhs.m_MI)
					return TRUE;
					break;

			 }

	default:{
				return FALSE;
			}

	}
	return FALSE;
}
bool CBiphone::operator<(const CBiphone& rhs)
{
	switch (m_SortStyle)
	{
	case WMI:{
				if (m_WMI < rhs.m_WMI)
					return TRUE;
					break;

			 }
	case MI:{
				if (m_MI < rhs.m_MI)
					return TRUE;
					break;

			 }

	default:{
				return FALSE;
			}

	}
	return FALSE;
}

void CBiphone::BiphoneListDisplay(Q3ListView* List)
{ static_cast<void>(new CBiphoneListViewItem(List, m_Key, this)); }
