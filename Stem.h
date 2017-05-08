// Common type for stems to which to attach affixes and words to analyze
// Copyright © 2009 The University of Chicago
#ifndef STEM_H
#define STEM_H

class CStem;
// Q3ListViewItem pointers to CStem in its two roles
class CWordListViewItem;
class CStemListViewItem;

// to define CStem:
#include "LParse.h"
#include <QString>
#include <QMap>
#include "SparseVector.h"
#include "Parse.h"
#include "generaldefinitions.h"
template<class V> class QList;

// to define CWordListViewItem, CStemListViewItem:
#include <Q3ListViewItem>
#include <QString>
#include "generaldefinitions.h"
class Q3ListView;
template<class K, class V> class QMap;
class CSignature;

/// CStem objects are the key to signature discovery.
///
/// A CStem represents a morpheme to which an affix might be attached
/// on the left or right.  The CStem itself may be further analyzed,
/// so that in the representation as stem + affix each word has an
/// implied parse tree.
///
/// A single instance represents all uses of a stem, and its main
/// purpose is to remember the list of affixes it appears with so
/// they can be considered as a potential signature.  In the
/// prefix/suffix-based morphology code, first the affix and stem
/// collections are built together and then the signature collection is
/// built using data stored with the stems.
///
/// Once a signature is built, CStem instances maintain the information
/// a signature needs to remember about each stem it appears with.  In
/// particular, the corpus count of a stem is kept here.
///
/// Compound discovery code uses CStem instances in a similar way:
/// the various parses of a word, the likelihood that a parse is of the
/// form stem + affix rather than stem + stem, and other relevant data
/// are maintained in CStem instances before compound objects are built,
/// and afterwards the compound objects defer to the underlying CStem
/// for some relevant counts.
///
/// Lastly, phonological information in Linguistica is stored per-word,
/// in the hope that it can help improve the discovery of
/// affix boundaries and compounds.  In particular, the representation
/// length (information content) of a stem or word disregarding
/// morphology can be used in calculating its description length
/// for building more complex models.
///
/// Sometimes a CStem is used in ways that emphasize its role as
/// something to be analyzed (i.e., something to be split: an entire
/// word or a stem from a MiniLexicon’s word collection), while at
/// other times, a CStem is primarily a constituent for other stems or
/// compounds.  We say in the former case that the CStem is “playing
/// the role of a word”, and in the latter, “it plays the role of a
/// stem”, even though in both cases the representation is the same.
/// This distinction comes up when displaying a word collection or
/// stem collection through the UI: only the properties relevant to
/// the role considered are displayed.
class CStem : public CLParse
{
protected:
	int		m_WordCount;
	CParse*		m_BrokenForm;
	CParse		m_SuffixList; //sister affixes, not daughter
	class CSignature* m_pSuffixSignature;
	class CSignature* m_pPrefixSignature;
	CParse		m_PrefixList; //sister affixes, not daughter
	int		m_Regular;
	bool		m_SimpleFlag; //if TRUE, then it's not further decomposable.
	enum eStemType	m_StemType;
	int		m_StemLoc;
	int		m_Stem2Loc;
	int		m_NumberOfStems;
	int		m_PrefixLoc;
	int		m_SuffixLoc;
	QString		m_Confidence;
	CStem*		m_pStem;
        CParse          m_strStem;
        CParse          m_strSuffix;
        CParse          m_strPrefix;
	class CSuffix*	m_pSuffix;
	class CPrefix*	m_pPrefix;
	mutable double	m_LengthOfPointerToMe; ///< Based on corpus counts, and the Stem collection set.
	double		m_LengthOfPointerToMe_2;

        QList<CStem*>* m_WordPtrList;
	static class CLexicon* m_Lexicon;
	CSparseVector	m_LeftNeighbors;
	CSparseVector	m_RightNeighbors;

	//----------------------------------------
	// Compounding...
        class           CEarleyParser* m_MyEarleyParser;
	double		m_CompoundCount;
	double		m_Affixness;

	//----------------------------------------
	// Phonology
	CParse		m_Phonology_Tier1;
	CParse		m_Phonology_Tier2;
	CParse		m_Phonology_Tier1_Skeleton;

	double		m_UnigramLogProb;
	double		m_BigramLogProb;

	double		m_BigramComplexity; // average log prob
	double		m_UnigramComplexity; // average log prob
	mutable double	m_PhonologicalContent; // value depends on what we have computed so far.
	double		m_HMM_LogProbability;

	// First Boltzmann model: only MI between tier 2 neighbors:
	double		m_Tier2_LocalMI_Score; //Only the MI on tier 2
	double		m_LocalMI_TotalBoltzmannScore; // Total score, including tier 1 bigram score
	double		m_LocalMI_Plog;

	// Second Boltzmann model: MI between more distant tier 2 elements
	double		m_Tier2_DistantMI_Score;
	double		m_DistantMI_TotalBoltzmannScore;
	double		m_DistantMI_Plog;

public:
	// Some Tier one Phonology Info for Graphica display
	QMap<int, QString> m_phonologies;
	QMap<int, double> m_unigrams;
	QMap<int, double> m_mis;
	int		m_countofunigrams;
	int		m_countofmis;
	double		m_maxpositive;
	double		m_maxnegative;
	bool		m_donephonology;

public:
	// construction/destruction.

	CStem(class CMiniLexicon* mini = 0);
	CStem(const class CStringSurrogate&, class CMiniLexicon* mini = 0);
	CStem(CStem&);
	CStem(const CLParse&);
	CStem(const CParse&, class CMiniLexicon* mini = 0);
	virtual ~CStem();

	// copy assignment.

	void	operator=(const CStem &);
	void	Copy(CStem&);



        bool                    IsAnalyzed();
        virtual                 enum eLxaClass GetType() const { return STEM_CLASS; }
        float                   CalculateDL() const;
        bool                    ContainsPrefix(class CPrefix*) const;
        bool                    ContainsPrefix(const class CStringSurrogate&) const;
        bool                    ContainsSuffix(class CSuffix*) const;

	CParse	DisplayBrokenForm();	// for MT, etc.
	QString	DisplayStemType() const;
//	TODO: get CRule  int FindRule (CStem*, CRule&) const;

        // accessors

        double                  GetAffixness()      const   { return m_Affixness; }
        double                  GetCompoundCount()  const   { return m_CompoundCount; }
        QString                 GetConfidence()     const   { return m_Confidence; }
        int                     GetCorpusCount()    const   { return linguistica::corpus_count::GetCorpusCount(); }
        class  CEarleyParser*   GetMyEarleyParser() const   { return m_MyEarleyParser;}
        int                     GetNumberOfPrefixes() const { return m_PrefixList.Size(); }
        int                     GetNumberOfStems() const;
        int                     GetNumberOfSuffixes() const { return m_SuffixList.Size(); }
        void                    GetPrefix(CParse&) const;
        class CStringSurrogate  GetPrefix()         const;
        CParse*                 GetPrefixList()             { return &m_PrefixList; }
        int                     GetPrefixLoc()      const   { return m_PrefixLoc; }
        class   CPrefix*        GetPrefixPtr()      const   { return m_pPrefix; }
        class   CSignature*     GetPrefixSignature() const  { return m_pPrefixSignature; }
        int                     GetRegular()        const   { return m_Regular; }
        bool                    GetSimpleFlag()     const   { return m_SimpleFlag; }
        float                   GetSortingQuantity() const; // TODO
        QString                 GetSortingString();
        void                    GetStem(CParse&)    const;
        class CStringSurrogate  GetStem();
        int                     GetStem2Loc()       const { return m_Stem2Loc; }
        int                     GetStemLoc()        const { return m_StemLoc; }
        CStem*                  GetStemPtr()        const { return m_pStem; }
        enum eStemType          GetStemType()       const { return m_StemType; }
        void                    GetSuffix(CParse&)  const;
        class CStringSurrogate  GetSuffix()         const;
        CParse*                 GetSuffixList()             { return &m_SuffixList; }
        int*                    GetSuffixCounts(int*);	//returns corpus counts of each suffix with this stem.
        int                     GetSuffixLoc()      const { return m_SuffixLoc; }
        class CSuffix*          GetSuffixPtr()      const { return m_pSuffix; }
        class CSignature*       GetSuffixSignature() const  { return m_pSuffixSignature; }
        int                     GetWordCount() const { return m_WordCount; }


        //Phonology
        double                  GetUnigramLogProb()         { return m_UnigramLogProb; }
        double                  GetBigramLogProb()          { return m_BigramLogProb; }
        CParse*                 GetTier1()                  { return &m_Phonology_Tier1; }
        const CParse*           GetTier1()          const   { return &m_Phonology_Tier1; }
        CParse*                 GetTier2()                  { return &m_Phonology_Tier2; }
        const CParse*           GetTier2()          const   { return &m_Phonology_Tier2; }
        CParse*                 GetTier1_Skeleton()         { return &m_Phonology_Tier1_Skeleton; }
        const   CParse*         GetTier1_Skeleton() const   { return &m_Phonology_Tier1_Skeleton; }

        double                  GetUnigramComplexity() { return m_UnigramComplexity; }
        double                  GetBigramComplexity() { return m_BigramComplexity; }
        CParse*                 GetPhonology_Tier1();
        CParse*                 GetPhonology_Tier2();
        CParse*                 GetPhonology_Tier1_Skeleton()                   { return &m_Phonology_Tier1_Skeleton; }
        void                    SplitPhonologyToTiers(enum ePhonologySplitType, CParse& PhonesToMove);
        double                  GetTier2_LocalMI_Score()                        { return m_Tier2_LocalMI_Score; }
        double                  GetLocalMI_TotalBoltzmannScore()                { return m_LocalMI_TotalBoltzmannScore; }
        double                  GetLocalMI_Plog()                               { return m_LocalMI_Plog; }
        double                  GetTier2_DistantMI_Score()                      { return m_Tier2_DistantMI_Score; }
        double                  GetDistantMI_TotalBoltzmannScore()              { return m_DistantMI_TotalBoltzmannScore; }
        double                  GetDistantMI_Plog()                             { return m_DistantMI_Plog; }
        double                  GetHMM_LogProbability()                         { return m_HMM_LogProbability; }
        double                  CalculatePhonologicalInformationContent(class CLexicon*) const;
        double                  GetPhonologicalInformationContent(class CLexicon* = 0) const;

        QList<CStem*>*          GetWordPtrList()                                { return m_WordPtrList; }
        enum eStemType          GetWordType()                           const   { return m_StemType; }
        double                  GetLengthOfPointerToMe()                const;
        double                  GetLengthOfPointerToMe_2();
        void                    SetLengthOfPointerToMe(double L)                { m_LengthOfPointerToMe = L; }

        bool                    HasAPrefix() const;
        bool                    HasASuffix() const;

        bool                    IsValid() const;
        int                     SF(int) const; // SuccessorFrequency;
        void                    StemListDisplay(class Q3ListView* dest,  QMap<QString, QString>* filter = 0, int char_count = 27);
        void                    WordListDisplay(class Q3ListView* dest,  QMap<QString, QString>* filter = 0, enum eWordDisplayMode = MiniLexicon_MorphologyStuffFirst,
			int char_count = 27);

        QString                 GetProbabilityInformation();
        void                    CreateCVTemplate(CParse* Vowels);
        void                    OutputStem(class Q3TextStream& outf, int index);
        void                    OutputWord(class Q3TextStream& outf, int index);


	void	ComputeBoltzmannProbabilities(double Z, double ZStar);

	// mutators.

        void                    AddNULLPrefix();
        void                    AddNULLSuffix();
        void                    AddPrefix(class CPrefix*);
        void                    AddPrefix(const class CStringSurrogate&);
        void                    AddSuffix(class CSuffix*);
        void                    AddSuffix(const class CStringSurrogate&);
        bool                    AddWord(CStem*);
        void                    AppendToConfidence(const QString string)        { m_Confidence += string; }
        void                    AttachPrefixSignature(class CSignature*);
        void                    AttachSuffixSignature(class CSignature*);
        void                    AttachWordAndSuffixalStem(CStem*);
        void                    AttachWordAndPrefixalStem(CStem*);
        void                    AttachWordStemAndPrefix(CStem*, class CPrefix*);
        void                    AttachWordStemAndSuffix(CStem*, class CSuffix*);

        class CSignature*       ChangeSuffixSignature(class CSignature* pNewSig);
        void                    ClearPointers(); // to Stem, Suffix, Signature;
        void                    ClearPrefixStemSplit();
        void                    ClearRootSuffixSplit();
        void                    CopyStemInformation(CStem*);
        void                    CopySuffixList(CParse*);

        void                    DeleteFactorization();
        void                    DeletePrefix();	 // Arabic morphology
        void                    DetachPrefix(class CPrefix*);
        void                    DetachSuffix(class CSuffix*);

        void                    IncrementSuffixLocs();
        void                    IncrementCompoundCount(double d = 1.0)            { m_CompoundCount += d; }
        void                    IncrementWordCount(int n = 1);

        void                    RepairSuffixList(const class CMiniLexicon*);
        void                    RemoveWordFromWordPtrList(CStem*);

        void                    SetAffixness(double d)                          { m_Affixness = d; }
        void                    SetCompoundCount(double d)                      { m_CompoundCount = d; }
        void                    SetConfidence(const QString conf)               { m_Confidence = conf; }
        static void             SetLexicon(CLexicon* Lex)                       { m_Lexicon = Lex; }
        void                    SetNumberOfStems(int n)                         { m_NumberOfStems = n; }
        void                    SetPrefixLoc(int n)                             { m_PrefixLoc = n; }
        void                    SetPrefixPtr(class CPrefix* pPre)               { m_pPrefix = pPre; }
        void                    SetPrefixSignature(class CSignature* pSig)      { m_pPrefixSignature = pSig; }
        void                    SetStem2Loc(int n)                              { m_Stem2Loc = n; }
        void                    SetStemLoc(int n)                               { m_StemLoc = n; }
        void                    SetStemPtr(CStem* pStm)                         { m_pStem = pStm; }
        void                    SetStemType(enum eStemType e)                   { m_StemType = e; }
        void                    SetSuffixList(CParse* pParse)                   { m_SuffixList = pParse; }
        void                    SetSuffixLoc(int n)                             { m_SuffixLoc = n; }
        void                    SetSuffixPtr(class CSuffix* pSuf)               { m_pSuffix = pSuf; }
        void                    SetSuffixSignature(class CSignature* pSig)	{ m_pSuffixSignature = pSig; }
        void                    SetWordCount(int n)                             { m_WordCount = n; }
        void                    SetWordType(enum eStemType WT)                  { m_StemType = WT; }
        void                    SetMyEarleyParser(class CEarleyParser* parser)	{ m_MyEarleyParser = parser; }
        void                    SetPhonology_Tier1(CParse*);
        void                    ShiftStemSuffixBoundary(int);
        void                    ShiftPrefixStemBoundary(int);
        void                    SetHMM_LogProbability(double logprob)           { m_HMM_LogProbability = logprob;}

        void                    CreatePhonologyFromOrthography(enum eAddBoundarySymbols = BOUNDARIES);
        void                    ComputeProbabilities(class CWordCollection*);
        double                  ComputeBoltzmannScore(class CWordCollection*);

        void                    GetPhonogyTier1InfoForGraph(class CWordCollection*);
        double                  ComputeMyDL();
};

/// A list view item for words.
/**
	Contains all the necessary variables needed when displaying a 
	word and its data in a list view.
 */

class CWordListViewItem : public Q3ListViewItem {
	CStem* m_pWord;
	int m_mini;
	QMap<QString, QString>* m_filter;
	enum eWordDisplayMode m_DisplayMode;
	int m_char_count;
	double m_DL;
	QString m_prefix;
	QString m_stem;
	QString m_suffix;
	QString m_signature;
	QString m_tier1;
	QString m_tier1_skeleton;
	QString m_tier2;
	CSignature* m_pSig;
public:
	// construction/destruction.

	explicit CWordListViewItem(Q3ListView* parent = 0);

        CWordListViewItem(Q3ListView* parent, QString word_text,
            int mini_index = -1, CStem* word = 0,
            QMap<QString, QString>* filter = 0,
            enum eWordDisplayMode format = MiniLexicon_MorphologyStuffFirst,
            int char_count = 27);

	CWordListViewItem(Q3ListViewItem* parent, QString word_text,
            int mini_index = -1, CStem* word = 0,
            QMap<QString, QString>* filter = 0,
            enum eWordDisplayMode format = MiniLexicon_MorphologyStuffFirst,
            int char_count = 27);

	// copy.

	CWordListViewItem(const CWordListViewItem& x)
		: Q3ListViewItem(x),
		m_pWord(x.m_pWord),
		m_mini(x.m_mini),
		m_filter(x.m_filter),
		m_DisplayMode(x.m_DisplayMode),
		m_char_count(x.m_char_count),
		m_DL(x.m_DL),
		m_prefix(x.m_prefix),
		m_stem(x.m_stem),
		m_suffix(x.m_suffix),
		m_signature(x.m_signature),
		m_tier1(x.m_tier1),
		m_tier1_skeleton(x.m_tier1_skeleton),
		m_tier2(x.m_tier2),
		m_pSig(x.m_pSig) { }
	CWordListViewItem& operator=(const CWordListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_pWord = x.m_pWord;
		m_mini = x.m_mini;
		m_filter = x.m_filter;
		m_DisplayMode = x.m_DisplayMode;
		m_char_count = x.m_char_count;
		m_DL = x.m_DL;
		m_prefix = x.m_prefix;
		m_stem = x.m_stem;
		m_suffix = x.m_suffix;
		m_signature = x.m_signature;
		m_tier1 = x.m_tier1;
		m_tier1_skeleton = x.m_tier1_skeleton;
		m_tier2 = x.m_tier2;
		m_pSig = x.m_pSig;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	int compare(Q3ListViewItem* other, int column, bool ascending) const;
	virtual QString key(int column, bool ascending) const;

	// underlying stem object.

	CStem* GetWord() { return m_pWord; }
	void SetWord(CStem* pWord) { m_pWord = pWord; }

	/// index of mini-lexicon containing this word (or -1 for none)
	int GetMini() { return m_mini; }

	/// description length
	double GetDL() { return m_DL; }

	bool isFullLex() { return false; }
};

/// A list view item for stems.
/**
	Contains all the necessary variables needed when displaying a 
	stem and its data in a list view.
 */


class CStemListViewItem : public Q3ListViewItem {
	CStem* m_Stem;
	QMap<QString, QString>* m_filter;
	int m_char_count;
	int m_mini;
public:
	// construction/destruction.

	explicit CStemListViewItem(Q3ListView* parent = 0);
	CStemListViewItem(Q3ListView* parent, QString stem_text,
		int mini_index = -1, CStem* stem = 0,
		QMap<QString, QString>* filter = 0,
		int char_count = 27);
	CStemListViewItem(Q3ListViewItem* parent, QString stem_text,
		int mini_index = -1, CStem* stem = 0,
		QMap<QString, QString>* filter = 0,
		int char_count = 27);

	// copy.

	CStemListViewItem(const CStemListViewItem& x)
		: Q3ListViewItem(x),
		m_Stem(x.m_Stem),
		m_filter(x.m_filter),
		m_char_count(x.m_char_count),
		m_mini(x.m_mini) { }
	CStemListViewItem& operator=(const CStemListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_Stem = x.m_Stem;
		m_filter = x.m_filter;
		m_char_count = x.m_char_count;
		m_mini = x.m_mini;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	int compare(Q3ListViewItem* other, int column, bool ascending) const;
	virtual QString key(int column, bool ascending) const;

	// underlying stem object.

	CStem* GetStem() { return m_Stem; }
	void SetStem(CStem* pStem) { m_Stem = pStem; }
};

#endif // STEM_H
