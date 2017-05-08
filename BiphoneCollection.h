// Description length bookkeeping, search, and display of encountered biphones
// Copyright © 2009 The University of Chicago
#ifndef BIPHONECOLLECTION_H
#define BIPHONECOLLECTION_H

class CBiphoneCollection;

#include <Q3Dict>
#include "Biphone.h"

#include <Q3SortedList>
#include <QString>
#include "Parse.h"
#include "generaldefinitions.h"

class CBiphoneCollection : public Q3Dict<CBiphone> {
public:
	Q3SortedList<CBiphone> m_PtrArray;
	Q3SortedList<CBiphone> m_CountSortArray;
	Q3SortedList<CBiphone> m_MISortArray;
	Q3SortedList<CBiphone> m_WMISortArray;
	enum eBiphoneSortStyle m_SortStyle;
	class CPhoneCollection* m_Phones;
	class CWordCollection* m_MyWords;
	int* m_Count;
	double* m_LogFreqs;
	double* m_Freqs;
	int m_Length; ///< size of alphabet
	double* m_MI;
	double m_SumOfMyMIs;
	int m_TotalCount;
	double m_Z_biphones;
public:
	// construction/destruction.

	CBiphoneCollection(class CWordCollection*);
	CBiphoneCollection(class CPhoneCollection*);
	virtual ~CBiphoneCollection();	

	// disable default-construction, copy
private:
	CBiphoneCollection();
	CBiphoneCollection(const CBiphoneCollection& x);
	CBiphoneCollection& operator=(const CBiphoneCollection& x);
public:
	// assign.

	void Empty();

	// find.

	CBiphone* operator^=(CParse& str);
	CBiphone* operator^=(QString str);
	CBiphone* GetBiphone(class CPhone* lhs, class CPhone* rhs);

	// insert.

	CBiphone* Insert(class CPhone* lhs, class CPhone* rhs);

	// sort.

	void Sort();

	// size.

	void SetSize(int i);

	// counts.

	void SetAtLogFreq(int FirstPhoneIndex, int SecondPhoneIndex,
			double val);
	double GetLogFreq(int FirstPhoneIndex, int SecondPhoneIndex);
	void IncrementAtCount (int FirstPhoneIndex, int SecondPhoneIndex,
			int incr = 1);
	void SetAtCount(int FirstPhoneIndex, int SecondPhoneIndex, int n);
	int GetCount(int FirstPhoneIndex, int SecondPhoneIndex);
	int GetTotalCount() { return m_TotalCount; }

	// mutual information.

	void SetAtMI(int FirstPhoneIndex, int SecondPhoneIndex, double val);
	double GetMI(CBiphone* bigram);
	double GetSumOfMyMIs();
	double ComputeZ_MI();

	/// output to GUI
	void ListDisplay(Q3ListView* widget);
};

#endif // BIPHONECOLLECTION_H
