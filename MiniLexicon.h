// Sub-stem morphology model and driver
// Copyright © 2009 The University of Chicago
#ifndef MINILEXICON_H
#define MINILEXICON_H

#include <qstring.h>
#include <qmap.h>
#include <QList>
#include <QTextStream>
#include <q3ptrstack.h>
#include <q3listview.h>

#include "Signature.h" // July 29 2008
#include "generaldefinitions.h"
#include "AffixLocation.h"
#include "FSA.h"

class FSA;
class CSuffixCollection;
class CPrefixCollection;
class CStemCollection;
class CSignatureCollection;
class CWordCollection;
class CTemplateCollection;
class CSuffix;
class CStem;
class CCorpusWord;
class CStringSurrogate;
class CDatum;
class CVeryLong;
class CParse;
class LinguisticaMainWindow;
class CPhoneCollection;
class CDLHistory;
class CDescriptionLength;
class CLexicon;
class LxPoSCollection; 
class GUIWordCollection;
class CRuleCollection;

typedef QMap<QString,QString>	StringToString;
typedef QMap<QString,QString>	StringToString;
typedef QMap<QString,CDatum>	StringToDatum;
typedef QMap<uint,eLxaClass>	PtrToClass;
typedef QMap<uint,uint> 	PtrToPtr; 
typedef QList<CSignature*>    SignatureList;

const int MAXIMUM_LENGTH_OF_INPUT_LINE = 1000;

/// All analyses at the sub-stem level (non-compound) are done in the
/// lexicon’s mini-lexica.
class CMiniLexicon {
	/// The parent of this mini-lexicon
	CLexicon* m_pLexicon;

	/// The index of this mini in its parent's mini-lexicon list.
	int m_Index;

	/// A flag designating the affix type (prefix|suffix). This is also
	/// noted by the signatures and their collection.
	enum eAffixLocation m_AffixLocation;

	/// This mini-lexicon's local copy of words will be the basis for all
	/// analyses within the mini-lexicon. The suffixes, prefixes, stems and
	/// signatures are all discovered locally in this mini-lexicon. The
	/// mini-lexicon has the responsibility to update the global collection.
	CWordCollection* m_pWords;
	CSuffixCollection* m_pSuffixes;
	CPrefixCollection* m_pPrefixes;
	CStemCollection* m_pStems;
	CSignatureCollection* m_pSignatures;
	LxPoSCollection* m_pPOS;
	CDescriptionLength* m_DescriptionLength;
	double m_CorpusCountOfUnanalyzedWords;
	double m_PhonologicalInformationOfUnanalyzedWords;

	GUIWordCollection* m_GUIWords;

	QMap<QString, CDatum> m_DataMap; // for deMarcken JG

	FSA* m_pFSA;
public:
	// construction/destruction.

	CMiniLexicon(CLexicon* parent = 0, int index = -1,
		enum eAffixLocation affixLocation = STEM_FINAL);
	~CMiniLexicon();

	// disable copy.
private:
	CMiniLexicon(const CMiniLexicon& x);
	CMiniLexicon& operator=(const CMiniLexicon& x);
public:

	// assign.

	void ClearAll();

	// location in parent lexicon.

	int GetIndex() { return m_Index; }
	CLexicon* GetLexicon() { return m_pLexicon; }
	CCorpusWord* FindAWord(CStem* stem, CSuffix* suffix);
	/// total number of (not necessarily unique) words in corpus
	int GetCorpusCount();
	int GetNumberOfCharacterTypes();
	int GetMiniCount();
	int GetMiniSize();
	CMiniLexicon* GetMiniLexicon(int index);

	// parameters.

	enum eAffixLocation GetAffixLocation() { return m_AffixLocation; }
	/// Set affix type.
	/// If affix type has changed from initial to final or vice-versa,
	/// this entails forgetting any previously discovered affixes.
	/// If this further entails forgetting some discovered stems,
	/// do nothing; result is false.
	/// Result is true on success.
	bool SetAffixLocation(enum eAffixLocation prefix_or_suffix);
	int GetIntParameter(QString key, int default_value);

	// analyzed and unanalyzed words.

	CWordCollection* GetWords() { return m_pWords; }
	void AddToWordCollection(CStemCollection* words);
	void AddToWordCollection(CWordCollection* words,
		enum eWhichWords which_words = WW_UnanalyzedOnly);
	int GetNumberOfUnanalyzedWords();
	int GetCorpusCountOfUnanalyzedWords();
	int GetNumberOfAnalyzedWords(int& unanalyzed_count);

	// stem/signature/suffix model of morphology.

	CPrefixCollection* GetPrefixes() { return m_pPrefixes; }
	CSignatureCollection* GetSignatures() { return m_pSignatures; }
	CStemCollection* GetStems() { return m_pStems; }
	CSuffixCollection* GetSuffixes() { return m_pSuffixes; }
	int GetNumberOfStems();
	int GetNumberOfSuffixes();

	// linguistic analysis (stem/signature/suffix discovery).

	CPrefixCollection* FindPrefixes();
	/// If affix type is not suffix, do nothing.
	/// Otherwise, apply various heuristics to fill this mini-lexicon’s
	/// suffix collection.  Result points to the suffix collection.
	CSuffixCollection* FindSuffixes();
	void FindSingletonSignatures();
	/// Analyze unanalyzed words using known stems and known affixes.
	/// XXX. If a word can be analyzed in two ways as stem + suffix,
	/// this function does not assess their relative merits.
	/// Instead, it just picks the version with the longer suffix.
	/// The situation is even worse for prefixes: the version with
	/// the stem earliest in alphabetical order is used.
	void ExtendKnownStemsToKnownAffixes();
	/// Rebuild signature list through knowledge of stems and their
	/// associated affixes.
	void FindAllSignatures();
	void FromStemsFindAffixes();
	/// Find new signatures using unanalyzed words and known affixes.
	/// More precisely:
	///
	/// For each word, if it ends with a known suffix (resp starts with
	/// a known prefix), consider the corresponding stem text.
	///
	/// If adding that new stem (and the corresponding signature from
	/// analyzing other words with it) decreases description length,
	/// record the new stem, signature, and analyzed words.
	void LooseFit();
	void RebuildAffixesStemsAndSignaturesFromWordSplits(
		CStringSurrogate& remark);
	void TakeSplitWords_ProduceStemsAndSigs(CStringSurrogate& Remark,
		CWordCollection* words = 0, CStemCollection* stems = 0,
		CPrefixCollection* prefixes = 0,
		CSuffixCollection* suffixes = 0);
	/// successor-frequency algorithm (bootstrapping step)
	void TakeSignaturesFindStems(CSignatureCollection* Sigs = 0);
	void CheckSignatures();

	// description length.

	CDescriptionLength* GetDescriptionLength()
		{ return m_DescriptionLength; }
	double CalculateDescriptionLength();
	double CalculateSumOfPointersToMyUnanalyzedWords(enum eMDL_STYLE style);
	double CalculateUnanalyzedWordsTotalPhonologicalInformationContent();
	CDLHistory* GetDLHistory();
	double CalculateCompressedLengthOfUnanalyzedWords();

	// part-of-speech discovery (does not affect description length).

	LxPoSCollection* GetPOS() { return m_pPOS; }
	/// Build or update m_pPOS to reflect top discovered signatures
	void FindMajorSignatures();

	// output.

	FSA* GetFSA() { return m_pFSA; }
	bool LogFileOn();
        QTextStream* GetLogFile();
	QMap<QString, QString>* GetOutFilter();

	// output to GUI.

	/// set text for “command line” pane
	void AddToScreen(QString info);
	/// handle for UI operations
	LinguisticaMainWindow* GetDocument();
	GUIWordCollection* GetGUIWords();

	/// deprecated: poor man’s RTTI
	enum eLxaClass GetType() { return MINI_LEXICON_CLASS; }

	// CDatum* LookUp(CStringSurrogate&);

	// allomorphy.

	void FindAllomorphy();
	void RelateStems();
	void ShiftFinalLetterToStem(CStem* pStem, QString& FinalLetter );
	void HowManyStemsWithThisSuffixEndInThisLetter(CStringSurrogate& Suffix,
		CStringSurrogate& Letter, int& TotalStemsWithSuffix,
		int& HowManyEndWithThisLetter);
	int StemsWithBothSuffixes(CStringSurrogate& suf1, CStringSurrogate& suf2);
	int StemsWithBothSuffixes(QString suf1, CStringSurrogate& suf2);
	void MoveWordsStemSuffixBoundaryToRight(CSignature* pSigToChange,
		CStringSurrogate& Letters, CParse* pSuffixCandidates);
	void MoveWordsStemSuffixBoundaryToRight(CSignature* pSigToChange,
		QString	Letters, CParse* pSuffixCandidates);
	CParse CreateADeletingSignature(CSignature* pSig,
		CStringSurrogate Deletee, CParse& ReplacingSuffixes,
		int* bStatus, CParse& WhatSigWillBecome,
		QMap<QString, QString>& Remapper);
	CParse CreateADeletingSignature(CSignature* pSig,
		CStringSurrogate Deletee, CParse& ReplacingSuffixes,
		int* bStatus, CParse& WhatSigWillBecome,
		CParse* pSuffixCandidates);
};

#endif // MINILEXICON_H
