// Compound interfix type for compound discovery and display
// Copyright © 2009 The University of Chicago
#ifndef LINKER_H
#define LINKER_H

// See the CLexicon class in Lexicon.h for an overview of compound discovery.

#include "Affix.h"
#include <q3listview.h>
#include <QList>

class CLParse;
class CMiniLexicon;
class CLinker;
class CCompound;

class CLinkerListViewItem : public Q3ListViewItem {
	CLinker* m_linker;
	QMap<QString, QString>* m_filter;
public:
	// construction/destruction.

	explicit CLinkerListViewItem(Q3ListView* parent = 0,
		QString linker_text = QString(), CLinker* linker = 0,
		QMap<QString, QString>* filter = 0);
	explicit CLinkerListViewItem(Q3ListViewItem* parent,
		QString linker_text = QString(), CLinker* linker = 0,
		QMap<QString, QString>* filter = 0);

	// copy.

	CLinkerListViewItem(const CLinkerListViewItem& x)
		: Q3ListViewItem(x),
		m_linker(x.m_linker),
		m_filter(x.m_filter) { }
	CLinkerListViewItem& operator=(const CLinkerListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_linker = x.m_linker;
		m_filter = x.m_filter;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	virtual QString key(int column, bool ascending) const;

	// underlying linker object.

	CLinker* GetLinker() const { return m_linker; }
	void SetLinker(CLinker* pLinker) { m_linker = pLinker; }
};

class CLinker : public CAffix {
	double m_CompoundCount;
        QList<CCompound*>* m_CompoundPtrList;
public:
	// construction/destruction.

	explicit CLinker(CMiniLexicon* mini);
	CLinker(const CStringSurrogate& text, CMiniLexicon* mini);
	virtual ~CLinker();

	// disable default-construction, copy
private:
	CLinker();
	CLinker(const CLinker& x);
	CLinker& operator=(const CLinker& x);
public:
	/// output to GUI
	void ListDisplay(Q3ListView* parent,
		QMap<QString, QString>* filter = 0);

	// compound list.

	CCompound* GetAtCompound(int i) { return m_CompoundPtrList->at(i); }
	int GetNumberOfCompounds() { return m_CompoundPtrList->count(); }
	void ClearCompoundPtrList();
	void AddCompound(CCompound* compound);
	void RemoveCompound(CCompound* compound);

	// compound count.

	double GetCompoundCount() { return m_CompoundCount; }
	void IncrementCompoundCount(double d = 1.0) { m_CompoundCount += d; }

	// description length.

	virtual double GetLengthOfPointerToMe();

	/// deprecated: poor man’s RTTI
	virtual enum eLxaClass GetType() const { return LINKER_CLASS; }
};

#endif // LINKER_H
