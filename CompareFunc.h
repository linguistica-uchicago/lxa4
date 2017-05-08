// Comparison and sorting functions
// Copyright © 2009 The University of Chicago
#ifndef COMPAREFUNC_H
#define COMPAREFUNC_H

class QStringList;

// Compare CLParse** objects
extern int CompareAlphabetically(const void* a, const void* b);
extern int CompareReverseAlphabetically(const void* a, const void* b);
extern int CompareSortingQuantity(const void* a, const void* b);
extern int CompareSortingString(const void* a, const void* b);

// Compare CSignature** objects
extern int CompareNumberOfStems(const void* a, const void* b);
extern int CompareSigRemark(const void* a, const void* b);

// Compare CStem** objects
extern int CompareStemSource(const void* a, const void* b);

// Compare CLParse** objects
extern int CompareCorpusCount(const void* a, const void* b);
extern int CompareSize(const void* a, const void* b);
extern int CompareLength(const void* a, const void* b);

// Compare CMorpheme** objects
extern int CompareDLSavings(const void* a, const void* b);
extern int CompareFrequency(const void* a, const void* b);
extern int CompareMorphemeCount(const void* a, const void* b);

// Compare CAffix** objects
extern int CompareUseCount(const void* a, const void* b);

// Compare Pair* objects
extern int GreaterThan(const void* a, const void* b);
extern int FollowsAlphabetically(const void* a, const void* b);
extern int ReversedFollowsAlphabetically(const void* a, const void* b);
extern int Precedes(const void* a, const void* b);

// Sort indices according to values
extern void SortVector(int* out, const double* values, int len);
extern void SortStrings(int* out, const QStringList& values, int len);
extern void SortReversedStrings(int* out, const QStringList& values, int len);
extern void SortLetters(int* out, const class QChar* values, int len);

extern void SortQStringListFromRight(QStringList& l);

// compare() for basic types
extern int MakeComparable(int a, int b);
extern int MakeComparable(double a, double b);

#endif // COMPAREFUNC_H
