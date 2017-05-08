// Implementation of comparison and sorting functions
// Copyright © 2009 The University of Chicago
#include "CompareFunc.h"

#include <algorithm>
#include <iterator>
#include <utility>
#include <QStringList>
#include <QString>
#include <QChar>
#include "MiniLexicon.h"
#include "Signature.h"
#include "Morpheme.h"
#include "LParse.h"
#include "Affix.h"
#include "Stem.h"
#include "StringFunc.h"

int CompareAlphabetically(const void *pA, const void *pB)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pA);
	CLParse* pS2 = *static_cast<CLParse* const*>(pB);

	Q_ASSERT(pS1);
	Q_ASSERT(pS2);

	if ( pS1->GetMyMini() && pS2->GetMyMini() )
	{
		QString str1 = pS1->Display( QChar(0),
					pS1->GetMyMini()->GetOutFilter() ),
			str2 = pS2->Display( QChar(0),
					pS2->GetMyMini()->GetOutFilter() );

		return LxStrCmp( str1, str2, str1.length(), str2.length(),
					0, 0 );
	}
	else
		return LxStrCmp( pS1->GetKeyPointer(),
					pS2->GetKeyPointer(),
					pS1->GetKeyLength(),
					pS2->GetKeyLength() );
}

int CompareReverseAlphabetically(const void *pA, const void *pB)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pA);
	CLParse* pS2 = *static_cast<CLParse* const*>(pB);

  Q_ASSERT(pS1);
  Q_ASSERT(pS2);


  QChar* S1 = new QChar[pS1->GetKeyLength()];
  QChar* S2 = new QChar[pS2->GetKeyLength()];
  LxStrCpy_R( pS1->GetKeyPointer(), S1, pS1->GetKeyLength() );
  LxStrCpy_R( pS2->GetKeyPointer(), S2, pS2->GetKeyLength() );
  int comp = LxStrCmp( S1, S2, pS1->GetKeyLength(), pS2->GetKeyLength() );

  delete [] S1;
  delete [] S2;

  return comp;
}

int CompareSortingQuantity (const void *pA, const void *pB)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pA);
	CLParse* pS2 = *static_cast<CLParse* const*>(pB);

  float  dif =   pS2->GetSortingQuantity() -  pS1->GetSortingQuantity();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareSortingString (const void *pA, const void *pB)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pA);
	CLParse* pS2 = *static_cast<CLParse* const*>(pB);

  return LxStrCmp( pS1->GetSortingString(), pS2->GetSortingString(), pS1->GetSortingString().length(), pS2->GetSortingString().length() );

}

int CompareNumberOfStems (const void *pA, const void *pB)
{
	CSignature* pS1 = *static_cast<CSignature* const*>(pA);
	CSignature* pS2 = *static_cast<CSignature* const*>(pB);

	int dif = pS2->GetNumberOfStems() -  pS1->GetNumberOfStems();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}

}

int CompareSigRemark (const void *pA, const void *pB)
{
	CSignature* pS1 = *static_cast<CSignature* const*>(pA);
	CSignature* pS2 = *static_cast<CSignature* const*>(pB);
  return QString::compare( pS1->GetRemark(), pS2->GetRemark() );
}

int CompareStemSource (const void *pA, const void *pB)
{
	CStem* pS1 = *static_cast<CStem* const*>(pA);
	CStem* pS2 = *static_cast<CStem* const*>(pB);
  return QString::compare( pS1->GetConfidence(), pS2->GetConfidence() );
}

int CompareCorpusCount (const void *pM1,   const void *pM2)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pM1);
	CLParse* pS2 = *static_cast<CLParse* const*>(pM2);

	int dif = pS2->GetCorpusCount() -  pS1->GetCorpusCount();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareSize (const void *pM1,   const void *pM2)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pM1);
	CLParse* pS2 = *static_cast<CLParse* const*>(pM2);

  int  dif =   pS2->Size() -  pS1->Size();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareLength (const void *pM1,   const void *pM2)
{
	CLParse* pS1 = *static_cast<CLParse* const*>(pM1);
	CLParse* pS2 = *static_cast<CLParse* const*>(pM2);

  int  dif =   pS2->GetKeyLength() -  pS1->GetKeyLength();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareDLSavings (const void *pM1,   const void *pM2)
{
	CMorpheme* pS1 = *static_cast<CMorpheme* const*>(pM1);
	CMorpheme* pS2 = *static_cast<CMorpheme* const*>(pM2);

  double  dif =   pS2->GetDLSavings() -  pS1->GetDLSavings();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareFrequency (const void *pM1,   const void *pM2)
{
	CMorpheme* pS1 = *static_cast<CMorpheme* const*>(pM1);
	CMorpheme* pS2 = *static_cast<CMorpheme* const*>(pM2);

  double  dif =   pS2->GetFrequency() -  pS1->GetFrequency();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareMorphemeCount (const void *pM1,   const void *pM2)
{
	CMorpheme* pS1 = *static_cast<CMorpheme* const*>(pM1);
	CMorpheme* pS2 = *static_cast<CMorpheme* const*>(pM2);

  double  dif =   pS2->GetMorphemeCount() -  pS1->GetMorphemeCount();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareUseCount (const void *pM1,   const void *pM2)
{
	CAffix* pS1 = *static_cast<CAffix* const*>(pM1);
	CAffix* pS2 = *static_cast<CAffix* const*>(pM2);

  double  dif =   pS2->GetUseCount() -  pS1->GetUseCount();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int GreaterThan (const void *pA, const void *pB)
{
  struct Pair
  {
    int    Index;
    double  Value;
  };

	Pair F1 = *static_cast<const Pair*>(pA);
	Pair F2 = *static_cast<const Pair*>(pB);

  if ( F1.Value == F2.Value ) { return 0; }
  if ( F1.Value >  F2.Value )  { return -1; }
  return 1;

};
int FollowsAlphabetically(const void *pA, const void *pB)
{
  struct Pair
  {
    int      Index;
    QString  Value;
  };

	Pair F1 = *static_cast<const Pair*>(pA);
	Pair F2 = *static_cast<const Pair*>(pB);

  if ( F1.Value == F2.Value ) { return 0; }
  if ( F1.Value >  F2.Value )  { return -1; }
  return 1;

};

namespace {
	int compare_int(int a, int b)
	{
		// cannot just return a - b because overflow is possible
		return a > b ? 1 : a < b ? -1 : 0;
	}

	int compare_qchar(QChar a, QChar b)
	{ return compare_int(a.unicode(), b.unicode()); }

	int compare_reversed_string(const QString& a, const QString& b)
	{
		if (a.size() > b.size())
			return -compare_reversed_string(b, a);

		typedef std::reverse_iterator<QString::const_iterator>
			riterator;
		const riterator rbegin_a = riterator(a.constEnd());
		const riterator rend_a = riterator(a.constBegin());
		const riterator rbegin_b = riterator(b.constEnd());

		const std::pair<riterator, riterator> x = std::mismatch(
			rbegin_a, rend_a, rbegin_b);
		if (x.first == rend_a)
			// tails match
			return compare_int(a.size(), b.size());
		return compare_qchar(*x.first, *x.second);
	}
}

/// sort strings from their right ends, rather than their left ends.
int ReversedFollowsAlphabetically(const void *pA, const void *pB)
{
	typedef std::pair<int, QString> item;
	return compare_reversed_string(
		static_cast<const item*>(pA)->second,
		static_cast<const item*>(pB)->second);
}

// Sort indices according to values.

//----------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------//
// Output is an ordered list of the row numbers of Input, sorted by value;
//----------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------//
void SortVector(int* Output, const double* Input, int Length)
{
  int i;
  struct Pair
  {
    int    Index;
    double  Value;
  };
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].Index = i;
    Pairs[i].Value = Input[i];
  }
  qsort( Pairs, Length, sizeof( Pair ), GreaterThan );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].Index;
  }

  delete [] Pairs;
  return;
}
//----------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------//

void SortStrings (int* Output, const QStringList& Input, int Length)
{
  int i;
  struct Pair
  {
    int      Index;
    QString  Value;
  };
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].Index = i;
    Pairs[i].Value = Input[i];
  }
  qsort ( Pairs, Length, sizeof( Pair ), FollowsAlphabetically );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].Index;
  }

  delete [] Pairs;
  return;
}
//----------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------//
void SortReversedStrings (int* Output, const QStringList& Input, int Length)
{
  int i;
  typedef std::pair<int, QString> Pair;
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].first = i;
    Pairs[i].second = Input[i];
  }
  qsort ( Pairs, Length, sizeof( Pair ), ReversedFollowsAlphabetically );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].first;
  }

  delete [] Pairs;
  return;
}
//----------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------//
void SortQStringListFromRight(QStringList& ThisStringList)
{
    int             Length      = ThisStringList.count();
    QStringList     CopyOfMe    = ThisStringList;
    int*            IndexList   = new int[ Length ];
    
    SortReversedStrings (IndexList, ThisStringList, Length);
    ThisStringList.clear();
    for (int i = 0; i < Length; i++)
    {
       ThisStringList.append(CopyOfMe[ IndexList[i] ]);
    }
}
//----------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------//



int Precedes(const void *pA, const void *pB)
{
  struct Pair
  {
    int    Index;
    char  Value;
  };

	Pair F1 = *static_cast<const Pair*>(pA);
	Pair F2 = *static_cast<const Pair*>(pB);

  if ( F1.Value == F2.Value ) { return 0; }
  if ( F1.Value <  F2.Value )  { return -1; }
  return 1;

};
// Output is an ordered list of the row numbers of Input, sorted alphabetically;
void SortLetters (int* Output, const QChar* Input, int Length)
{
  int i;
  struct Pair
  {
    int    Index;
    QChar  Value;
  };
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].Index = i;
    Pairs[i].Value = Input[i];
  }
  qsort ( Pairs, Length, sizeof( Pair ), Precedes );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].Index;
  }

  delete [] Pairs;
  return;
}

// compare() for basic types
int MakeComparable(int a, int b)
{
	const int difference = a - b;

	if (difference < 0) return -1;
	else if (difference == 0) return 0;
	else return 1;
}

int MakeComparable(double a, double b)
{
	const double difference = a - b;

	if (difference < 0) return -1;
	else if (difference == 0) return 0;
	else return 1;
}
