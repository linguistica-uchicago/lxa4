// Vector of floating-point values with mostly zero entries
// Copyright © 2009 The University of Chicago
#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

// See also CSparseIntVector.

#include <q3textstream.h>

class CLexicon;
class CWordCollection;
class CMorphemeCollection;

// this is a class which keeps track of values
// associated with an integer (the "dimension"),
// useful when such a vector is "sparse," that is,
// the values for most of the "dimensions" is zero
// (and hence you don't want to have to remember each zero).
// It keeps track of the dimensions that we care about,
// with their corresponding "values"; any dimension not
// explicitly listed is taken to have a zero value.
class CSparseVector
{	
	friend int Overlap (CSparseVector& List1, CSparseVector& List2); 
	friend class CLexicon; 
//	friend class CSparseVector;   // Implicitly friends with itself

	protected:
	
	int		m_Length; // the number of slots currently in use.
//	int		m_MaximalIndex; // highest index available to outside world
	int*	m_Dimension;
	float*  m_Values;
	int		m_NormalizedFlag;
	int		m_NumberOfSlots;

	int		ContainsDim (int n);
	int		GetLength();
//	void	SetLength(int n);
	float	operator[] (int n); //n is the local value 
	
public:

	CSparseVector();
	CSparseVector ( int n);
	CSparseVector (CSparseVector&);
	~CSparseVector();

	void	operator() (int n, float val);  // n is the value of Dimension
	float	operator() (int n);				// n is the value of Dimension
	void	operator= (CSparseVector&);
	int		operator== (CSparseVector&);	 


	// for iteration: (uses MFC-style syntax):
	int		GetNextDimension (int& DimOut, float& Value, int& Position);
	
	void	Clear();
	void	ClearOut();	
	int		GetNormalizedFlag();
	int		GetTopDimension();	
	float	GetAt( int dim ); //uses outside world value of dimension
	void	SetAt ( int, float);
	int		Delete (int dim); //uses outside world value of dim
	void	IncrementAt(int, float = 1);	
	int		GetNumberOfSlots ();
	void	SetNumberOfSlots(int);
//	int		GetNumberOfNonZeroMembers();
	Q3TextStream& OutputToStream (CWordCollection&, Q3TextStream& stream, int threshold=2);
	void	MakeLogFreq (CWordCollection*);
	void	Normalize();
	float	InnerProduct (CSparseVector*);
	
};

#endif // SPARSEVECTOR_H
