// Compound type for compound discovery and display
// Copyright © 2009 The University of Chicago
#ifndef COMPOUND_H
#define COMPOUND_H

class CCompound;
class CCompoundListViewItem;

#include "LParse.h"
#include <q3listview.h>
#include <q3ptrvector.h>
#include <Q3PtrList>
#include <QList>

class CStem;
class CLinker;
class CEdge;
class CCompoundCollection;
class CLexicon;

typedef QList<CStem*> StemSet;
typedef QMap<int,StemSet*> Components;
typedef QMap<int,CLinker*> Linkers;

class CCompoundListViewItem : public Q3ListViewItem {
	CCompound* m_compound;
	int m_parse;
	double m_score;
	QString m_mostFreqPiece;
	double m_MFPCount;
	QString m_pieceCounts;
	double m_prefixness;
	double m_suffixness;
	int m_parseCount;
	QMap<QString, QString>* m_filter;
public:
	// construction/destruction.

	explicit CCompoundListViewItem(Q3ListView* parent = 0,
		QString compound_text = QString(), CCompound* compound = 0,
		int = -1, double = -1.0, QString = QString(),
		double = 0.0, QString = QString(),
		double = 0.0, double = 0.0, int = 1,
		QMap<QString, QString>* filter = 0);
	explicit CCompoundListViewItem(Q3ListViewItem *parent,
		QString compound_text = QString(), CCompound* compound = 0,
		int = -1, double = -1.0, QString = QString(),
		double = 0.0, QString = QString(),
		double = 0.0, double = 0.0, int = 1,
		QMap<QString, QString>* filter = 0);
	// destructor implicitly defined

	// copy.

	CCompoundListViewItem(const CCompoundListViewItem& x)
		: Q3ListViewItem(x),
		m_compound(x.m_compound),
		m_parse(x.m_parse),
		m_score(x.m_score),
		m_mostFreqPiece(x.m_mostFreqPiece),
		m_MFPCount(x.m_MFPCount),
		m_pieceCounts(x.m_pieceCounts),
		m_prefixness(x.m_prefixness),
		m_suffixness(x.m_suffixness),
		m_parseCount(x.m_parseCount),
		m_filter(x.m_filter) { }
	CCompoundListViewItem& operator=(const CCompoundListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_compound = x.m_compound;
		m_parse = x.m_parse;
		m_score = x.m_score;
		m_mostFreqPiece = x.m_mostFreqPiece;
		m_MFPCount = x.m_MFPCount;
		m_pieceCounts = x.m_pieceCounts;
		m_prefixness = x.m_prefixness;
		m_suffixness = x.m_suffixness;
		m_parseCount = x.m_parseCount;
		m_filter = x.m_filter;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	virtual QString key(int column, bool ascending) const;

	// underlying compound object.

	CCompound* GetCompound() const { return m_compound; }
	void SetCompound(CCompound* pCompound) { m_compound = pCompound; }

	// compound properties.

	void SetMFSCount(double d) { m_MFPCount = d; }
	void SetScore(double d) { m_score = d; }
	void SetPrefixness(double d) { m_prefixness = d; }
	void SetSuffixness(double d) { m_suffixness = d; }
	int GetParse() { return m_parse; }
};

class CCompound : public CLParse {
	// The word components and linkers of the compound, but 
	// only those reflected in the best parse (see m_BestParse)
	// and the CParse structure of the compound
        QMap<int, QList<CStem*>*>* m_MyComponents;
	QMap<int, CLinker*>* m_MyLinkers;

	/// All "possible" parses of the compound as found
	/// by the Earley Parser and not deleted thereafter
        Q3PtrList<CEdge>* m_Parses;

	/// This is the "best" parse chosen from the list above. This
	/// parse is reflected in the CParse structure of the compound.
	int m_BestParse;

	/// The lexicon
	CLexicon* m_pLexicon;
public:
	// construction/destruction.

	explicit CCompound(CMiniLexicon* mini = 0);
	explicit CCompound(const CStringSurrogate& str, CMiniLexicon* mini = 0);
	virtual ~CCompound();

	// disable copy.
private:
	CCompound(const CCompound& x);
	CCompound& operator=(const CCompound& x);
public:

	QString DisplayBestParse(QMap<QString, QString>* filter = 0)
		{ return DisplayParse(m_BestParse, filter); }
	QString DisplayParse(int, QMap<QString, QString>* filter = 0);
	int GetNumberComponents() { return m_MyComponents->count(); }
	void CompoundListDisplay(Q3ListView* widget,
		QMap<QString, QString>* filter = 0, QChar separator = QChar());
	int GetBestParse() { return m_BestParse; }
        QList<CStem*    >* GetComponent(int) const;
	Components* GetComponents() { return m_MyComponents; }
	CLinker* GetLinker(int) const;
	Linkers* GetLinkers() { return m_MyLinkers; }
	CEdge* GetParse(int i) { return m_Parses->at(i); }
        Q3PtrList<CEdge>* GetParses() { return m_Parses; }
	double GetPrefixness();
	double GetSuffixness();

	void AddParse(CEdge*);
        void AttachComponentToWord(unsigned int piece, QList<CStem*>* word)
		{ m_MyComponents->insert(piece, word); }
	void DetachAllPieces();
	bool RemoveParse(CEdge*);
	bool RemoveParse(int i) { return RemoveParse(GetParse(i)); }
	void SetBestParse(int);
	void SetLexicon(CLexicon* lex) { m_pLexicon = lex; }
        void SetParses(Q3PtrList<CEdge>*, double*, double*);

	/// deprecated: poor man’s RTTI
	virtual enum eLxaClass GetType() const { return COMPOUND_CLASS; }
};

#endif // COMPOUND_H
