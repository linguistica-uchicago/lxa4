// alignment result from string-edit distance algorithm
// Copyright © 2009 The University of Chicago
#ifndef ALIGNMENT_H
#define ALIGNMENT_H

class CParse;

/// an alignment of two strings, Str1 and Str2.
/// There's an array for each string, Match1 and Match2, and they
/// explain how that letter lines up with its counterpart on the opposite
/// string. "-1" means there is no match. A non-negative number is the
/// index of the character to which it's aligned or matched on the
/// other string.
class CAlignment {
public: 
	// These are parses, so that we can cut them into
	// pieces, based on where the alignments change qualitatively
	// (where the slips begin or end).
	CParse* m_Str1;
	CParse* m_Str2;
	int m_Length1;
	int m_Length2;
	int* m_Match1; // "-1" means no match
	int* m_Match2;
	float m_Score;
	// number of times the alignment departs from
	// 1-to-1 alignment. Two or more non-alignments counts as 1 slip.
	int m_Slips;
	// How many continuous regions of good or bad associations there are.
	int m_Spans;
	int m_Identities;
public:
	// construction/destruction.

	CAlignment(class QString String1, class QString String2);
	CAlignment(CParse*, CParse*);
	/// deprecated
	CAlignment(const CAlignment*);
	virtual ~CAlignment();

	// copy.

	CAlignment(const CAlignment& other);
	CAlignment& operator=(const CAlignment& other);

	double FindStringEditDistance();
	CParse CalculateDisplay();
	CParse SpellOut();
	CParse FindSubstitution();
	CParse FindContext();

	void SetScore(float s) { m_Score = s; }

	// true if the char is aligned and identical to its matchee
	bool String1CharMatches(int);
	bool String2CharMatches(int);
	// true if these two chars are identical and aligned
	bool PerfectMatch(int n, int m);

	// which piece corresponds to piece n, if any (otherwise, 0)
	// corresponding pieces need not be identical stringwise
	int Str2MatchForStr1Piece(int n);
	// which piece corresponds to piece n, if any (else 0);
	// corresponding pieces need not be identical stringwise
	int Str1MatchForStr2Piece(int n);
};

#endif // ALIGNMENT_H
