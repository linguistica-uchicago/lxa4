// Mini-lexicon’s collection of stems
// Copyright © 2009 The University of Chicago
#ifndef STEMCOLLECTION_H
#define STEMCOLLECTION_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.

class CStemCollection;

#include "CollectionTemplate.h"
#include "AffixLocation.h"
#include "generaldefinitions.h"
template<class K, class V> class QMap;

/// List of stems for a stem/signature model of morphology
///
/// Maintains a list of stems used in analyzing a particular collection
/// of words (that is, all stems associated to a particular mini-lexicon).
/// Semantically, a stem collection is a set (like std::set) of pointers
/// to CStem objects which it owns.  The contained stems are generally
/// deleted upon removal.
///
/// When a stem is inserted, it is added to the associated lexicon, and
/// when a stem is removed, it is removed from the associated lexicon.
///
/// This collection type also maintains a total use count for the stems it
/// manages, for use in description length calculations.
///
/// To support the successor-frequency algorithm, a stem collection
/// should support incremental lookup of stems (find all stems starting
/// with a given phoneme sequence, add a phoneme to that sequence to
/// narrow the search, etc).
class CStemCollection : public TCollection<class CStem> {
protected:
	enum eAffixLocation m_AffixLocation;
	double m_TotalUseCount;
public:
	// construction/destruction.

	CStemCollection();
	CStemCollection(class CMiniLexicon* mini);
	~CStemCollection();
	// copy construction, copy-assignment implicitly defined.

	// Qt3-style collection view.

	void ListDisplay(class Q3ListView* parent,
		QMap<class QString, class QString>* filter = 0);

	// input/output to file.

	void OutputStems(class QString filename);
	void ReadStemFile(class QString filename,
			enum eAffixLocation affix_loc);

	// insert.

	CStem* operator<<(const CStem* stem);
	CStem* operator<<(class CStringSurrogate stem_text);
	CStem* operator<<(const class CParse* stem_text);
	CStem* operator<<(class QString stem_text);
	void AddPointer(CStem* pointee);
	CStem* AddToCollection(const class CParse& stem_text);
	CStem* AddToCollection(const class CStringSurrogate& stem_text);

	// clear.

	void Empty();
	void RemoveAll();

	// remove.

	bool Remove(CStem* stem); // doesn't delete CStem*
	bool RemoveMember(CStem* stem); // deletes CStem*
	bool RemoveMember(const class CStringSurrogate& stem_text); // deletes CStem*
	bool RemoveMember(const class CStringSurrogate& stem_text,
				bool delete_stem); // FSA
	void DeleteMarkedMembers();

	// accessors.

	double GetTotalUseCount();

	// description length.

	double CalculateSumOfPointersToMyStems(enum eMDL_STYLE style);
	double CalculateTotalPhonologicalInformationContent(
		class CLexicon* MotherLexicon);
};

#endif // STEMCOLLECTION_H
