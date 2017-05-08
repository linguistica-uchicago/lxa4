// Vector of integers with mostly zero entries
// Copyright © 2009 The University of Chicago
#ifndef SPARSEINTVECTOR_H
#define SPARSEINTVECTOR_H

// See also CSparseVector.

#include <qstring.h>

class CParse;


class CSparseIntVector
{	friend int Overlap (CSparseIntVector& List1, CSparseIntVector& List2); 
	friend int Overlap (CSparseIntVector* List1, CSparseIntVector* List2, CSparseIntVector&); 

//	friend CLexicon; 
//	friend CMorphemeMatrix;
//	friend CWordMatrix;

	protected:
	
	int		Length;
	int*	Dimension;
	int*	Values;	
	int		NumberOfSlots;

	int		ContainsDim (int n);
	void	SetLength(int n);
	int		operator[] (int n); //n is the local value 
	int		NormalizedFlag;
	

public:
	CSparseIntVector();
	CSparseIntVector ( int n);
	CSparseIntVector (CSparseIntVector&);
	~CSparseIntVector();


	int		operator< (CSparseIntVector&);
	int		operator> (CSparseIntVector&);
	void	operator() (int n, int val);  // n is the value of Dimension
	int		operator() (int n);				// n is the value of Dimension
	void	operator= (CSparseIntVector&);
	int		operator== (CSparseIntVector&);	 

	// for iteration: (uses MFC-style syntax):
	int		GetNextDimension (int& DimOut, int& Position);
	int		GetLength();
	int		GetFirstDimension();
	int		GetTopDimension();
	int		GetNumberOfSlots ();

	void	Clear();
	void	ClearOut();	
	int		GetNormalizedFlag();
	
	CParse	Display();	
	QString DisplayAsString();
	QString DisplayAsStringNoColons();


	int		Union (CSparseIntVector& );//returns length of result
	bool	Contains (CSparseIntVector* );// just checks dimensions that are present, not the values	

	int		GetAt( int dim ); //uses outside world value of dimension
	void	SetAt ( int, int);
	int		Delete (int dim); //uses outside world value of dim
	void	IncrementAt(int, int = 1);	
	
	void	SetNumberOfSlots(int);
//	TODO:	ostream& OutputToStream (CWordCollection&, ostream& stream, int threshold=2);
//	TODO: WordCollection	void	MakeLogFreq (CWordCollection*);

	void	Normalize();
	int		InnerProduct (CSparseIntVector*);
	void	Ingest(CSparseIntVector*);
	
};


#endif // SPARSEINTVECTOR_H
