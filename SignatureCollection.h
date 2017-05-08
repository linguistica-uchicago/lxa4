// Affixes and signatures in signature/suffix-based model of morphology
// Copyright © 2009 The University of Chicago
#ifndef SIGNATURECOLLECTION_H
#define SIGNATURECOLLECTION_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.

#include "CollectionTemplate.h"
#include "generaldefinitions.h"
#include "AffixLocation.h"

template<class K, class V> class QMap;
class QString;

class CSignatureCollection: public TCollection<class CSignature> {
	class CSuffixCollection* MySuffixes;
	class CPrefixCollection* MyPrefixes;
	/// prefix or suffix
	enum eAffixLocation m_SignatureType;
	double m_DLofPointersToMyMembers;
	double m_SumOfDLofPointersInternalToEachMember;
public:
	// construction/destruction.

	CSignatureCollection();
	CSignatureCollection(enum eAffixLocation prefix_or_suffix);
	CSignatureCollection(CMiniLexicon* mini, CSuffixCollection* suffixes,
		enum eAffixLocation prefix_or_suffix);
	CSignatureCollection(CMiniLexicon* mini, CPrefixCollection* prefixes,
		enum eAffixLocation prefix_or_suffix);
	/// deprecated
	CSignatureCollection(CMiniLexicon* mini);
	~CSignatureCollection();

	// disable copy
private:
	CSignatureCollection(const CSignatureCollection& x);
	CSignatureCollection& operator=(const CSignatureCollection& x);
public:
	// assign.

	void Empty();
	void RemoveAll();

	// insert.

	CSignature* operator<<(CSignature* sig);
	CSignature* operator<<(CParse* affixes);
	void AddPointer(CSignature* sig);
	CSignature* AddToCollection(CParse& affixes);
	CSignature* AddToCollection(CStringSurrogate& dot_delimited);

	// find.

	CSignature* operator^=(CParse& affixes);
	CSignature* operator^=(CParse* affixes);
	/// str should be a .-delimited list of affixes
	/// result is 0 if no such signature exists
	CSignature* operator^=(CStringSurrogate& str);
	/// *this ^= CStringSurrogate(str)
	CSignature* operator^=(QString str);

	// remove.

	/// doesn't delete sig
	bool Remove(CSignature* sig);
	/// deletes sig
	bool RemoveMember(CSignature* sig);
	/// deletes *this ^= dot_delimited
	bool RemoveMember(CStringSurrogate& dot_delimited);
	bool RemoveMember(CStringSurrogate& dot_delimited, bool delete_it);
	/// remove each item from m_DeletionArray
	void DeleteMarkedMembers();

	// union of contained signatures.

	void SetMyPrefixes(CPrefixCollection* prefixes);
	CPrefixCollection* GetMyPrefixes() { return MyPrefixes; }
	void SetMySuffixes(CSuffixCollection* suffixes);
	CSuffixCollection* GetMySuffixes() { return MySuffixes; }

	// affix location (prefix or suffix).

	eAffixLocation GetSignatureType() { return m_SignatureType; }

	// allomorphy.

	void FindAllomorphy();
	void PutAffixesOfRegularSignaturesIntoNewSuffixes(
		CSuffixCollection* NewSuffixes,
		int MinimumNumberOfStems);
	void PutAffixesOfRegularSignaturesIntoNewPrefixes(
		CPrefixCollection* NewPrefixes);

	// output to GUI.

	void BorrowedSigsDisplay(class Q3ListView* widget,
		QMap<QString, QString>* filter);
	void ListDisplay(class Q3ListView* widget,
		QMap<QString, QString>* filter = 0);

	// serialization and deserialization (file I/O).

	void OutputSignatures(QString filename);
	void ReadSignatureFile(QString filename,
		enum eAffixLocation prefix_or_suffix);
	void ReadSignatureFileBis(QString filename);

	/// scan all sigs, and if the stems of pSig do not begin
	/// with DiffLetter, then Diff
	void TryToRemove(const QString Suffix, const QString DiffLetter);
	double GetMDL();
	void CalculateFrequencies();
	/// For each signature, determines if a signature
	/// with more robustness is contained in it; if so, takes the
	/// larger robustness as its own. This measures our certain of
	/// the STEMS as such for the signature.
	void CheckRobustness();
	void FindDisplayOrdering();
	void CleanUp();
	/// sum for each signature the number of stems * number of affixes
	int GetTotalNumberOfWords();
	int TheseTwoSuffixesShareHowManyStems(
		class CSuffix* suf1, class CSuffix* suf2);
	double ComputeDLofInternalPointersOfEachMember(enum eMDL_STYLE style);
	double ComputeLengthOfPointersToEachOfMyMembers(enum eMDL_STYLE style);
	void GetIndividualCountsForEachStem();
};

#endif // SIGNATURECOLLECTION_H
