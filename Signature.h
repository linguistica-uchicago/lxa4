// Signature type for suffix/signature-based morphology discovery
// Copyright © 2009 The University of Chicago
#ifndef SIGNATURE_H
#define SIGNATURE_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.

#include "LParse.h"

#include <q3listview.h>
#include <qstring.h>
#include <QTextStream>
#include <qmap.h>
#include <q3dict.h>
#include <QList>
#include "AffixLocation.h"

class CStem;
class CPrefix;
class CSuffix;
class CMiniLexicon;
class CSparseIntVector;
class CSignatureCollection;
class CSuffixCollection;
class CPrefixCollection;
class CSignature;


enum eDetachment_Parameter;
enum eAffixLocation;

typedef QMap<uint,eLxaClass> PtrToClass;
typedef QMap<uint,uint> PtrToPtr;

/// A list view item for signatures.
/**
	Contains all the necessary variables needed when displaying a
	signature and its data in a list view.
 */

class CSignatureListViewItem : public Q3ListViewItem {
	CSignature* m_signature;
	QMap<QString, QString>* m_filter;
	QString m_label;
	Q3ListView* m_parentlist;
	int m_mini;
public:
	// construction/destruction.

	explicit CSignatureListViewItem(Q3ListView* parent = 0,
		QString sig_text = QString(), int mini_index = -1,
		CSignature* sig = 0, QMap<QString, QString>* filter = 0);
	CSignatureListViewItem(Q3ListViewItem* parent,
		QString sig_text = QString(), int mini_index = -1,
		CSignature* sig = 0, QMap<QString, QString>* filter = 0);

	// copy.

	CSignatureListViewItem(const CSignatureListViewItem& x)
		: Q3ListViewItem(x),
		m_signature(x.m_signature),
		m_filter(x.m_filter),
		m_label(x.m_label),
		m_parentlist(x.m_parentlist),
		m_mini(x.m_mini) { }
	CSignatureListViewItem& operator=(const CSignatureListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_signature = x.m_signature;
		m_filter = x.m_filter;
		m_label = x.m_label;
		m_parentlist = x.m_parentlist;
		m_mini = x.m_mini;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	int compare(Q3ListViewItem* other, int column, bool ascending) const;

	// underlying signature object.

	CSignature* GetSignature() { return m_signature; }
	void SetSignature(CSignature* pSig) { m_signature = pSig; }

	/// enclosing widget
	Q3ListView* GetParent() { return m_parentlist; }
};

/// A string implementation of signatures.
/**
	Signatures are simple statements of morphological patterns, which aid both
	in quantifying the Minimum Description Length (MDL) account and in constructively
	building a satisfactory morphological grammar (for MDL offers no guidance in the
	task of seeking the optimal analysis).
 */

class CSignature: public CLParse {
protected:
	enum eAffixLocation m_AffixLocation;
        QList<CStem*>* m_StemPtrList;
        QList<CStem*>* m_WordPtrList;
        QList<CSuffix*>* m_SuffixPtrList;
        QList<CPrefix*>* m_PrefixPtrList;

	// XXX. we may want to do this with a bit-base
	// vector someday to speed it up.
	/// points to the indexes of the affixes
	CSparseIntVector* m_Vector;

	QString m_Remark;
	/// must total to 1.0; frequencies of affixes within the signature
	float* m_Frequencies;
	/// the number of letters saved by having this signature
	/// = ( Number of stems - 1 ) * ( Number of suffixes - 1);
	/// Or, if there is a more robust signature which is
	/// contained in this one.
	/// It really measures how good our knowledge of these stems is, qua stems.
	mutable double m_Robustness;
	CSignature* m_Mentor;
        QList<CSignature*>* m_MentorList;
	CSignature* m_MyGeneralizer;
	/// without the <e> stuff prefixed
	CParse m_SimplifiedForm;
	CSignatureCollection* m_SignatureCollection;

	/// These affixes are "close" to this signature, in the sense that
	/// stems associated with this signature may also be marked to take
	/// that affix.
	CParse m_SatelliteAffixes;

	// description length.

	double m_DLofMyCorpus;
	double m_DLofMyStemPointers;
	double m_DLofMyAffixPointers;
	double m_LengthOfPointerToMe;
public:
	// construction/destruction.

	CSignature(CMiniLexicon* mini);
	CSignature(enum eAffixLocation prefix_or_suffix,
		CMiniLexicon* mini);
	CSignature(const CParse& affixes, CMiniLexicon* mini);
	/// single-affix signature
	CSignature(const CStringSurrogate& affix, CMiniLexicon* mini);
	/// deprecated
	CSignature(const CParse* affixes_ptr, CMiniLexicon* mini);
	~CSignature();

	// copy/assignment.

	CSignature(const CSignature& x);
	CSignature& operator=(const CSignature& x)
		{ *this = &x; return *this; }
	/// deprecated
	void operator=(const CSignature* x);
	/// clear
	void Suicide();
	void ConsumeParse(CParse* sigs);

	/// deprecated: poor man’s RTTI
	virtual enum eLxaClass GetType() const { return SIGNATURE_CLASS; }

	// convert to string.

	/// includes deletees in affixes
	QString Express(bool bDisplayDeletees = true);
	// includes deletees in affixes
	CSignature& Express(CSignature& Express, bool bDisplayDeletees = true);
	QString Display(QChar sep, QMap<QString, QString>* filter = 0) const;
	QString Display(QMap<QString, QString>* filter) const;
	QString Display() const;

	// counts.

	/// number of occurences in corpus (corpus count).
	/// output is a vector of integers whose length is the number of stems
	/// times the number of suffixes.
	int* GetIndividualCountsForEachStem(int* output);
	int GetNumberOfAffixes();
	int GetNumberOfStems() const;
	float GetNthFrequency(int n) const;
	void CalculateFrequencies(CMiniLexicon* mini);

	// context (enclosing mini-lexicon).

	/// affix location (prefix or suffix)
	enum eAffixLocation GetAffixLocation() const;
	void SetAffixLocation(enum eAffixLocation prefix_or_suffix)
		{ m_AffixLocation = prefix_or_suffix; }
	CSignatureCollection* GetSignatureCollection()
		{ return m_SignatureCollection; }
	void SetSignatureCollection(CSignatureCollection* list)
		{ m_SignatureCollection = list; }
	CMiniLexicon* GetLexicon() const { return m_pMyMini; }
	void SetLexicon(CMiniLexicon* lex) { m_pMyMini = lex; }
	/// human-readable string describing this signature’s discovery.
	QString GetRemark() const;
	void SetRemark(QString origin);

	// contained affixes.

	/// indices of affixes in the affix collection that holds them.
	CSparseIntVector* GetVector();
	void ComputeSignatureVector(CMiniLexicon* mini);
        QList<CSuffix*>* GetSuffixPtrList() const;
        QList<CPrefix*>* GetPrefixPtrList() const;

	// stems appearing with this sig.

	CParse GetStems();
        QList<CStem*>* GetStemPtrList() const;

	// words using this sig.

        QList<CStem*>* GetWordPtrList() const;
	CParse GetWords();

	// description length.

	double GetDLofMyStemPointers();
	double GetDLofMyAffixPointers();
	virtual double ComputeDLofModel(int char_count = 26);
	double FindCost(CMiniLexicon* mini);
	double ComputeDLofMyCorpus();
	double GetLengthOfPointerToMe();
	void SetLengthOfPointerToMe(double);
	double GetSumOfDLofInternalPointers(enum eMDL_STYLE unused,
		enum eRecomputeStyle unused2);

	// part-of-speech discovery.

	CSignature* GetMentor();
	void SetMentor(CSignature* sig);
        QList<CSignature*>* GetMentorList();

	/// deprecated: index of a known suffix in the suffix list.
	int GetNumber(CSuffix* suffix);

	/// (#affixes - 1)(total length of stems) +
	/// (#stems - 1)(total length of affixes)
	double GetRobustness() const;
	void SetRobustness(double value);
	/// deprecated: synonym for GetRobustness
	float GetSortingQuantity() const;

	// insert.

	/// register a stem appearing with this signature.
	void operator<<(class CStem* stem);
	/// Attach to Suffix Sig.
	/**
	 * This is the function to use to take a stem from one
	 * signature to a new one, and deal with all of the bookkeeping
	 * that goes with that. First it detaches the Stem from its
	 * old signature by using DetachStem() (see below);
	 * then it adds this stem to the New Signature;
	 * then it shifts all of the stem's words from the old signature
	 * to the new signature.
	 */
	void AttachToSuffixSig(CStem* stem, bool bLookAtPreviousSig = true);
	void AttachToPrefixSig(CStem* stem, bool bLookAtPreviousSig = true);
	void AttachStemFromDifferentPrefixSignature(CStem* s)
		{ AttachToPrefixSig(s); }
	void AttachStemFromDifferentSuffixSignature(CStem* s)
		{ AttachToSuffixSig(s); }
	void AddWord(CStem* word);
	/// add a satellite affix
	/// (i.e. remember one which often occurs on stems that take
	/// this signature)
	void AppendSatelliteAffix(CParse& Affix);
	void TakeAllStems(CSignature* other);

	// remove.

	void DetachWord(CStem* word, enum eDetachment_Parameter unused);
	/// remove a stem from a signature's Stem Ptr List, and if the
	/// Detachment Parameter is true, also remove all of the stem's
	/// WORDS from the signature's Word Ptr List.
	/// This is called by AttachToSuffixSig().
	void DetachStem(CStem* stem, enum eDetachment_Parameter words_too);
	bool RemoveStem(CStem* stem);
	bool RemoveWord(CStem* word);

	// output to GUI.

	void BorrowedSigsDisplay(Q3ListView* widget,
		QMap<QString, QString>* filter = 0);
	void ListDisplay(Q3ListView* widget,
		QMap<QString, QString>* filter = 0,
		bool express_deletees = true);

	/// output to file
        void OutputSignature(QTextStream& out);

	/// no empty affixes (but "NULL" as an affix is fine)
	bool IsValid();

	/// XXX. no-op
	void FindCorpusCount();

	/// XXX. unused
	void SetMyGeneralizer(CSignature* sig);

	// allomorphy and cut shifting helpers.

	/// delete Letter from the beginning of each suffix, and
	/// add it to each stem.
	/// add a <Letter> to suffixes
	/// Much like shifting boundary of stem/suffix split to the right.
	void RemoveLetter(CStringSurrogate& Letter, CMiniLexicon* mini,
		CSignature* out);
	/// add Letter to the beginning of each suffix
	void AddLetter(const QString& Letter);
	/// whether adding a letter at the start of each suffix still yield
	/// known suffixes
	bool EachSuffixCanHaveThisLetterPrefixedToIt(const QString& Letter);
	void ShiftStemSuffixCutToTheLeft(int distance, const QString& Piece);
	void ShiftStemSuffixCutToTheLeft(int distance);
	bool Generalizes(CSignature* other);

	CParse CreateADeletingSignature(CParse& Deleter, CMiniLexicon* mini);

	/// entropy of final ngrams of stems
	double ComputeFinalNgramEntropyOfStems(int n);

	// real workers.

	int CheckOut(CMiniLexicon* mini);
	void IterateThroughStems(int NumberOfLettersShifted,
		CMiniLexicon* Lexicon, CLParse*	pPiece,
		double& TotalDecreaseInDLDueToShorterStems,
		double LogTotalNumberOfAnalyzedWords,
		double& StemPointersToThisSig,
		double& SavingsBecauseStemAlreadyExisted,
		bool analyzingSuffixex);

        friend QTextStream& operator<<(QTextStream& out, CSignature* sigp);
};

#endif // SIGNATURE_H
