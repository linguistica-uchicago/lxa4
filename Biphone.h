// Description length bookkeeping and display for a phoneme pair
// Copyright © 2009 The University of Chicago
#ifndef BIPHONE_H
#define BIPHONE_H

class CBiphone;
class CBiphoneListViewItem;

#include <Q3ListViewItem>
#include "LParse.h"

#include <QString>
#include "generaldefinitions.h"

class CBiphoneListViewItem : public Q3ListViewItem {
	CBiphone* m_MyBiphone;
public:
	explicit CBiphoneListViewItem(Q3ListView* parent = 0,
		QString bigram_text = QString(), CBiphone* bigram = 0);
	explicit CBiphoneListViewItem(Q3ListViewItem* parent,
		QString bigram_text = QString(), CBiphone* bigram = 0);

	// copy.

	CBiphoneListViewItem(const CBiphoneListViewItem& x)
		: Q3ListViewItem(x), m_MyBiphone(x.m_MyBiphone) { }
	CBiphoneListViewItem& operator=(const CBiphoneListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_MyBiphone = x.m_MyBiphone;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	int compare(Q3ListViewItem* other, int column, bool ascending) const;

	// underlying biphone object.

	CBiphone* GetBiphone() const { return m_MyBiphone; }
	void SetBiphone(CBiphone* pBiphone) { m_MyBiphone = pBiphone; }
};

class CBiphone : public CLParse {
public:
	static enum eBiphoneSortStyle m_SortStyle;
public:
	QString m_Key;
	double m_Freq;
	double m_LogFreq;
	double m_MI;
	double m_WMI;
	double m_LogCondProb;
	double m_CondProb;
	double m_NormalizedMI;
	class CPhone* m_MyFirst;
	class CPhone* m_MySecond;
public:
	// construction/destruction.

	CBiphone();
	CBiphone(QString unigrams);
	virtual ~CBiphone();

	// copy.

	CBiphone(const CBiphone& x);
	CBiphone& operator=(const CBiphone&);

	// compare.

	bool operator==(const CBiphone& x);
	bool operator<(const CBiphone& x);

	// counts.

	void SetMI (double value);
	double GetMI() { return m_MI; }
	void SetLogFreq(double d) { m_LogFreq = d; }

	/// output to GUI
	void BiphoneListDisplay(Q3ListView* widget);
};

#endif // BIPHONE_H
