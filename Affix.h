// Data, algorithms, and interface shared by CPrefix and CSuffix
// Copyright © 2009 The University of Chicago
#ifndef AFFIX_H
#define AFFIX_H

class CAffix;
namespace linguistica {
	/// #include "affix_list_view_item.tcc" for definition
	/// requires:
	///
	/// struct Prefix_or_suffix {
	///	double ComputeDL(int char_count);
	///	double GetLengthOfPointerToMe() const;
	///	int GetCorpusCount() const;
	///	int GetUseCount() const;
	///	CParse* GetStemString();
	/// };
	template<class Prefix_or_suffix> class affix_list_view_item;
}

#include <Q3ListViewItem>
#include <QString>
#include "LParse.h"
#include "Parse.h"
#include "generaldefinitions.h"
template<class K, class V> class QMap;

/// Affix bookkeeping type for suffix/signature-based morphology code.
/// Most words can be parsed as stem + suffix or prefix + stem, where
/// the suffix or prefix is possibly empty.  Instances of this class
/// hold information on all instances of a particular prefix or
/// suffix.  A single string (e.g., “es” in Spanish) might be
/// represented by multiple different affixes, but a single string
/// in the context of a single signature (e.g., “es” of “∅.es” in
/// Spanish) will have a single associated affix opject.
///
/// Affixes are stored in the m_pSuffixes and m_pPrefixes members of
/// each mini-lexicon.  They are created whenever a particular affix
/// is being investigated as possibly useful and stored if it
/// proves so.
class CAffix : public CLParse {
protected:
	int m_UseCount;
	CParse m_StemString;
        QList<class CStem*>* m_StemPtrList;
	double m_CompressedLength;
	CParse m_Deletees;
	CParse m_Morphees;
	double m_LengthOfPointerToMe;
	double m_PhonologicalInformationContent;
	double m_UnigramLogProb;
	double m_BigramLogProb;
public:
	// construction/destruction.
	CAffix(class CMiniLexicon* owner);
	CAffix(const class CStringSurrogate& text, class CMiniLexicon* owner);
	virtual ~CAffix() = 0;
private:
	// copying forbidden for now.
	CAffix(const CAffix& x);
	CAffix& operator=(const CAffix& x);
public:
	// XXX. poor man’s run-time type information
	virtual enum eLxaClass GetType() const { return AFFIX_CLASS; }

	// description length.
	double GetCompressedLength() const { return m_CompressedLength; }
	int GetUseCount() const { return m_UseCount; }
	double GetLengthOfPointerToMe();
	double GetPhonologicalInformationContent();
	void CalculatePhonologicalInformationContent(class CLexicon* lexicon);
	void IncrementUseCount(int num_stems = 1);
	void SetCompressedLength(double m) { m_CompressedLength = m; }
	void SetUseCount(int n) { m_UseCount = n; }

	// allomorphy.
	CParse* GetDeletees() { return &m_Deletees; }
	void AddDeletee(class CStringSurrogate deletee);
	void AddMorphee(class CStringSurrogate pattern,
		class CStringSurrogate subst);

	// associated stems.
	int GetNumberOfStems() const { return m_StemString.Size(); }
	CParse* GetStemString() { return &m_StemString; }
        QList<CStem*>* GetStems() { return m_StemPtrList; }
	CStem* GetAtStem(int i) { return m_StemPtrList->at(i); }
	void AddStem(CStem* stem);
	void AppendToStemString(const class CStringSurrogate& stem_text);
	void RemoveFromStemPtrList(CStem* stem);
	void ClearStemPtrList() { m_StemPtrList->clear(); }
	void RemoveStemString(const class CStringSurrogate& stem_text);

	// display.
	QString ExpressAffix(bool ExpressDeletees = true);
};

template<class Affix>
class linguistica::affix_list_view_item : public Q3ListViewItem {
	Affix* m_affix;
	QMap<QString, QString>* m_filter;
	int m_char_count;
public:
	// construction/destruction.

	explicit affix_list_view_item(class Q3ListView* parent = 0,
		QString affix_text = QString(), Affix* affix = 0,
		QMap<QString, QString>* filter = 0,
		int char_count = 27);
	explicit affix_list_view_item(Q3ListViewItem* parent,
		QString affix_text = QString(), Affix* affix = 0,
		QMap<QString, QString>* filter = 0,
		int char_count = 27);

	// copy.

	affix_list_view_item(const affix_list_view_item& x)
		: Q3ListViewItem(x),
		m_affix(x.m_affix),
		m_filter(x.m_filter),
		m_char_count(x.m_char_count) { }
	affix_list_view_item& operator=(const affix_list_view_item& x)
	{
		Q3ListViewItem::operator=(x);
		m_affix = x.m_affix;
		m_filter = x.m_filter;
		m_char_count = x.m_char_count;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	int compare(Q3ListViewItem* other, int column, bool ascending) const;
	virtual QString key(int column, bool ascending) const;

	// underlying affix object.

	Affix* GetAffix() const { return m_affix; }
	void SetAffix(Affix* affix) { m_affix = affix; }
};

#endif // AFFIX_H
