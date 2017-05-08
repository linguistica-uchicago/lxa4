// driver and model for linguistica analyses
// Copyright © 2009 The University of Chicago
#ifndef LEXICON_H
#define LEXICON_H

class CLexicon;

#include <QStringList>
#include <Q3PtrVector>
#include <QList>
#include <Q3Dict>
#include <QMap>
#include "generaldefinitions.h"
 
class QString;
class CStringSurrogate;
class CSignatureCollection;

// compatibility typedefs.

typedef QMap<QString, class CStem> StringToStem;
typedef QMap<QString, int> StringToInt;
typedef QMap<QString, QString> StringToString;
typedef QList<class CPrefix*> PrefixSet;
typedef QList<class CSignature*> SignatureSet;
typedef QList<class CSuffix*> SuffixSet;
typedef QMap<QString, class CStem*> StringToPtrCStem;
typedef QList<class CStem*> StemSet;

/// The lexicon contains all the morphological collections.
/// These include words, stems, affixes, signatures, and other structures
/// used by different Linguistica functions.
class CLexicon {
protected:
	/// parent driver object (and UI)
	class LinguisticaMainWindow* m_pDoc;
	/// defaults for user-specified parameters (see CLPreferences class)
	QMap<QString, QString> m_ParamDefaults;

	/// master corpus line list.  (raw lines from the input file,
	/// except hyphenated lines are joined if the user so requests.)
	QStringList m_Corpus;
	/// master corpus word list (see class CCorpusWord).
	class CCorpusWordCollection* m_pCorpusWords;
	/// maps strings in QStringList::split(' ', m_Corpus[i])
	/// to corpus words in the master corpus word list
	Q3Dict<class CCorpusWord> m_CorpusMap;

	/// sub-stem morphology model (see class CMiniLexicon).
	Q3PtrVector<class CMiniLexicon>* m_pMiniLexica;
	/// mini-lexicon selected by and displayed to the user,
	/// the only mini-lexicon that changes.
	/// -1 indicates no mini-lexicon is active; otherwise,
	/// 0 <= m_ActiveMini < m_pMiniLexica->size()
	int m_ActiveMini;
	/// mini-lexicon “words” with changes to propagate to the lexicon
	/// see UpdateWord(), DoWordUpdates()
        QList<class CStem*> m_WordUpdates;
	// stems, suffixes, prefixes, and signatures owned by mini-lexica.
        Q3Dict< QList<class CPrefix*> > 	m_AllPrefixes;
        Q3Dict< QList<class CSignature*> > 	m_AllPrefixSigs;
        Q3Dict< QList<class CStem*> > 		m_AllStems;
        Q3Dict< QList<class CSuffix*> > 	m_AllSuffixes;
        Q3Dict< QList<class CSignature*> > 	m_AllSuffixSigs;
        Q3Dict< QList<class CStem*> > 		m_AllWords;

	CSignatureCollection*			m_SuffixalBiSignatures;
	CSignatureCollection*			m_PrefixalBiSignatures;
  
	// compound discovery happens globally (not inside the mini-lexica),
	// using information from all mini-lexica.
	class CCompoundCollection* m_pCompounds;	///< discovered compounds
	class CLinkerCollection* m_pLinkers;	///< compound interfixes
	/// compounds with changes to propagate to other lexicon members
	/// see UpdateCompound(), DoWordUpdates()
	QStringList m_CompoundUpdates;

	// scrubbing filters.
	/// map grapheme sequences to phoneme sequences
	QMap<QString, QString>* m_pInFilter;
	/// map phone sequences to grapheme sequences
	QMap<QString, QString>* m_pOutFilter;

	// description length.
	/// number of distinct phonemes encountered
	int m_NumberOfCharacterTypes;
	/// number of distinct words encountered
	int m_tokenCount;
	/// log of description length changes and their reasons.
	class CDLHistory* m_pDLHistory;
	/// “all-purpose” (i.e., unused) description length accounting object
	class CDescriptionLength* m_DescriptionLength;

	// string edit distance-based analyses.
	/// working copy of word list for string edit distance-based analysis
	class CWordCollection* m_pSEDWords;
public:
	// syllabification.
protected:
	// hidden Markov model.
	/// “all-purpose” (i.e., unused) HMM
	class StateEmitHMM* m_HMM;
public:
	// XXX. poor man’s run-time type information
	enum eLxaClass GetType() { return LEXICON_CLASS; }

	// construction/destruction.
private:
	// disable default-construction.
	CLexicon();
public:
	CLexicon(LinguisticaMainWindow*);
	~CLexicon();
private:
	// disable copies and copy-assignment.
	CLexicon(const CLexicon& x);
	CLexicon& operator=(const CLexicon& x);
public:

	// clear.
	void ClearAll();

	// input from file.

	/// requires: filename is a valid filename (in particular, nonempty)
	int ReadCorpus(const QString filename, int NumberOfWords = 5000);
	int ReadProjectFile(QString filename);
	int ReadDX1File (const QString filename, int NumberOfWords = -1);
	/// requires: filename is a valid filename (in particular, nonempty)
	int RereadCorpus(const QString filename, int NumberOfWords = 5000);

	// input from stream.
	/// write number of occurences of each word in lines to out
	int Tokenize(QStringList& lines, QMap<QString, int>& out);

	// output to file.
	void MakeBrokenCorpus(QString filename);
	void OutputStats(QString filename);

	// compound discovery and stem-level morphology discovery.
	void UpdateCompound(QString);
	void UpdateWord(CStem*);
	void DoWordUpdates();
	void FindPrefixes(bool AutoLayer = false);
	void FindSuffixes(bool AutoLayer = false);

	// compound discovery. (Lexicon_Compounds.cpp)
        void FromStemsFindCompounds(QList<CStem*>* compounds = 0,
                QList<CStem*>* components = 0,
		QString linker = QString());
	void CalculateCoefficientsOfAffixness();
	void FromAffixnessUpdateSigsAndCompounds();
        void FromStemsFindFlatCompounds(QList<CStem*>* compounds = 0,
                QList<CStem*>* components = 0,
		QString linker = QString(),
		int maxNumberOfRoots = 5);

	/// driver and UI.
	LinguisticaMainWindow* GetDocument() { return m_pDoc; }
	int GetIntParameter(QString key, int default_value);
	void AddToScreen(QString text);
	void ClearScreen();
        class QTextStream* GetLogFileStream();
	bool LogFileOn();
	QString GetStringParameter(QString key);
	/// defaults for user settings.
	QMap<QString, QString>* GetDefaultParams() { return &m_ParamDefaults; }

	// basic accessors.
	QStringList* GetCorpus() { return &m_Corpus; }
	CCorpusWordCollection* GetWords() { return m_pCorpusWords; }
	Q3Dict<CCorpusWord>* GetCorpusMap() { return &m_CorpusMap; }
	CCorpusWord* GetCorpusWord(const CStringSurrogate& word_text);

	// convenience accessors.
	CCorpusWord* FindAWord(CStem*, CSuffix*);

	//FSA approach
	void FindSuffixalBiSignatures();
	void FindPrefixalBiSignatures();
	
	// mini-lexica.
	int GetActiveMiniIndex() { return m_ActiveMini; }
	int GetMiniCount() { return m_pMiniLexica->count(); }
	int GetMiniSize() { return m_pMiniLexica->size(); }
	/// points to the mini-lexicon with index n
	/// result is a null pointer if n == -1, for convenience
	/// in expressions such as GetMiniLexicon(GetActiveMiniIndex())
	/// Requires: n == -1 or n is a valid mini-lexicon index
	CMiniLexicon* GetMiniLexicon(int n);
	void ClearMiniLexicon(int n);
	void DeleteMiniLexicon(int n);
	int NewMiniLexicon();
	void SetActiveMiniIndex(int);

	// mini-lexicon contents.
        QList<CPrefix*>* GetPrefixSet(const CStringSurrogate& text);
        QList<CSignature*>* GetPrefixSigSet(const CStringSurrogate& text);
        QList<CStem*>* GetStemSet(const CStringSurrogate& text);
        QList<CSuffix*>* GetSuffixSet(const CStringSurrogate& text);
        QList<CSignature*>* GetSuffixSigSet(const CStringSurrogate& text);
        QList<CStem*>* GetWordSet(const CStringSurrogate& text);

        Q3Dict<QList<CPrefix*> >* GetAllPrefixes() { return &m_AllPrefixes; }
        Q3Dict<QList<CSignature*> >* GetAllPrefixSigs()
	{ return &m_AllPrefixSigs; }
        Q3Dict<QList<CStem*> >* GetAllStems() { return &m_AllStems; }
        Q3Dict<QList<CSuffix*> >* GetAllSuffixes() { return &m_AllSuffixes; }
        Q3Dict<QList<CSignature*> >* GetAllSuffixSigs()
	{ return &m_AllSuffixSigs; }
        Q3Dict<QList<CStem*> >* GetAllWords() { return &m_AllWords; }

	bool InsertPrefix(CPrefix*);
	bool InsertPrefixSig(CSignature*);
	bool InsertStem(CStem*);
	bool InsertSuffix(CSuffix*);
	bool InsertSuffixSig(CSignature*);
	bool InsertWord(CStem*);

	bool RemovePrefix(CPrefix*);
	bool RemovePrefixSig(CSignature*);
	bool RemoveStem(CStem*);
	bool RemoveSuffix(CSuffix*);
	bool RemoveSuffixSig(CSignature*);
	bool RemoveWord(CStem*);

	// scrubbing rules.
	QMap<QString, QString>* GetInFilter() { return m_pInFilter; }
	QMap<QString, QString>* GetOutFilter() { return m_pOutFilter; }

	// discovered compounds.
	CCompoundCollection* GetCompounds() { return m_pCompounds; }
	CLinkerCollection* GetLinkers() { return m_pLinkers; }

	// string edit distance-based analysis.
	CWordCollection* GetSEDWords() { return m_pSEDWords; }

	// description length. (Lexicon.cpp, DescriptionLength.cpp)
	int GetNumberOfCharacterTypes()	{ return m_NumberOfCharacterTypes; }
	int GetTokenCount() { return m_tokenCount; }
	CDLHistory* GetDLHistory() { return m_pDLHistory; }
	CDescriptionLength* GetDescriptionLength() { return m_DescriptionLength; }
	int GetCorpusCount();
	double CalculateTotalPhonologicalInformationContentOfStems();
	double CalculateUnanalyzedWordsTotalPhonologicalInformationContent();
	double GetPhonologicalInformationContentOfSuffixes();

	// output to GUI.
	void CompoundListDisplay(class Q3ListView* widget,
		QMap<QString, QString>* filter = 0, QChar separator = QChar());
	void CompoundComponentListDisplay(class Q3ListView* widget);
	void CorpusWordListDisplay(class Q3ListView* widget,
		QMap<QString, QString>* filter,
		bool analyzed_words_only = true);
	void LinkerListDisplay(class Q3ListView* widget,
		QMap<QString, QString>* filter = 0);
	void PrefixListDisplay(class Q3ListView* widget);
	void SignatureListDisplay(class Q3ListView* widget,
		enum eDocumentType affix_loc);
	void StemListDisplay(class Q3ListView* widget);
	void SuffixListDisplay(class Q3ListView* widget);
	void WordListDisplay(class Q3ListView* widget, bool analyzed_only);

	// scrubbing filters.
	void SetFilters(QStringList* phonemes);

	// “all-purpose” hidden Markov model.
	StateEmitHMM* GetHMM();
	StateEmitHMM* CreateNewHMM();

	friend class LinguisticaMainWindow;
};

#endif // LEXICON_H
