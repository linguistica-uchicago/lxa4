// Intermediate state for string alignment algorithm
// Copyright © 2009 The University of Chicago
#ifndef STRINGEDITGRID_H
#define STRINGEDITGRID_H

struct StringEditGridEntry;
class StringEditGrid;

#include "generaldefinitions.h"

// basically, just the entry in the grid: an arrow
// with a direction, and
struct StringEditGridEntry {
	enum eAlignmentOperation m_Movement;
	int m_Slips;
};

class CStringEditGrid  {
	// horizontal string
	int m_Length1;
	class QChar* m_String1;

	// vertical string
	int m_Length2;
	class QChar* m_String2;

	// parameters
	float m_DeletionCost;
	float m_SubstitutionCost;

	// per-entry data
	// XXX. valarray would make layout more obvious
	// XXX. consider moving scores to grid entries
	float* m_Scores;
	StringEditGridEntry** m_GridEntries;
public:
	// construction/destruction.

	CStringEditGrid(class QString, class QString);
	CStringEditGrid(class CAlignment*);
	virtual ~CStringEditGrid();
private:
	// copying not implemented.
	CStringEditGrid(const CStringEditGrid& x);
	CStringEditGrid& operator=(const CStringEditGrid& x);
public:

	// Levenshtein algorithm.

	float FindBestAlignment(class CAlignment& Output);
	// pass in reference for answer
	class CAlignment& GetAlignment(class CAlignment&);

	// per-entry data.

	float GetScore(int, int);
	void SetScore(int, int, float);
	StringEditGridEntry* GetStringEditGridEntry(int, int);
	void SetStringEditGridEntry(int, int, StringEditGridEntry*);

	/// cost of character alignment
	float GetCost(class QChar, class QChar);
};

#endif // STRINGEDITGRID_H
