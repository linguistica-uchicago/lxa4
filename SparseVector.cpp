// Implementation of CSparseVector methods
// Copyright © 2009 The University of Chicago
#include "SparseVector.h"

struct BiData 
{
	int		Integer;
	float	m_Values;
	
};
int CompareBiData (const void*  , const void*  );

CSparseVector::CSparseVector() 
{
	m_Length		= 0; 	
	m_NumberOfSlots	= 10; 
	m_Values		= new float [m_NumberOfSlots];
	m_Dimension		= new int   [m_NumberOfSlots];

	for (int i = 0; i < m_NumberOfSlots; i++) 
	{
		m_Values[i]		= 0;
		m_Dimension[i]	= 0;
	}
	m_NormalizedFlag	= 0;
	 

};
CSparseVector::CSparseVector ( int n)
{
	int MinimumNumberOfSlots = 10;
	if (n > MinimumNumberOfSlots) 
	{
		m_NumberOfSlots = n ;
	} else 
	{
		m_NumberOfSlots = MinimumNumberOfSlots;
	}
	
	m_Length		= n;
	m_Values		= new float [m_NumberOfSlots];
	m_Dimension		= new int   [m_NumberOfSlots];
	
	for (int i = 0; i < m_NumberOfSlots; i++) 
	{
		m_Values[i]		= 0;
		m_Dimension[i]	= 0;
	}
	m_NormalizedFlag	= 0;
	 
};
CSparseVector::	CSparseVector (CSparseVector& rhs)
{

	m_NumberOfSlots = rhs.GetNumberOfSlots();
	m_Length		= rhs.GetLength();

	int pos = 0;	
	while ( GetNextDimension ( m_Dimension[pos], m_Values[pos], pos ) )
	{
		// blank intentionally
	}

	m_NormalizedFlag = rhs.GetNormalizedFlag();
}

CSparseVector::	~CSparseVector()
{
	if (m_Values)	 {delete [] m_Values;   }
	if (m_Dimension) {delete [] m_Dimension;}
}
/* -colin-
void CSparseVector::Clear() 
{
	if (m_Length > 0) 
	{
		for (int i = 0; i < m_NumberOfSlots; i++) 
		{
			m_Values[i] = 0;
			m_Dimension[i] = 0;
		}	
	}
	m_NormalizedFlag = 0;
}
*/ /*
void CSparseVector::SetLength (int n) 
{ 
	m_Length			= n;
	m_NumberOfSlots		= n;
	if (m_Values) 
	{ 
		delete m_Values; 
	}	
	m_Values = new float [n];

}
*/
int CSparseVector:: GetLength() {return m_Length;}

/* -colin-
float CSparseVector::operator[] (int n)  // uses internal index, not external -- 
{
	if (n < 0 || n >= m_Length ) {return -1;}
	else { return m_Values[n]; };
}

 -colin- */
int CSparseVector::GetNumberOfSlots() {return m_NumberOfSlots;}

int	CSparseVector::GetNextDimension (int& DimOut, float& Value, int& Position)
{
	if ( Position < 0         )	{ return 0; }
	if ( Position >= m_Length )	{ return 0; }
	DimOut = m_Dimension[ Position ];
	Value  = m_Values   [ Position ];
	Position++;
	return 1;

}
/* -colin-
float CSparseVector::GetAt (int dim)  // dim is the value to the outside world
{	
	int n = ContainsDim(dim);

	//if (n == -1 )	{	return -1;	}

	if ( n== -1)	{ return 0; }
	else			{ return  m_Values[n]; };	
}

void CSparseVector::operator= (CSparseVector& rhs)
{

		m_Length		= rhs.GetLength();

		if ( rhs.GetLength() > m_NumberOfSlots ) 
		{
			if (m_Dimension)	delete m_Dimension;
			if (m_Values)		delete m_Values;
			m_NumberOfSlots = rhs.GetLength();
			m_Dimension		= new int   [ m_NumberOfSlots ];
			m_Values		= new float [ m_NumberOfSlots ];
		}
		for (int i = 0; i<m_Length; i++) 
		{ 
			m_Dimension[i] = rhs.m_Dimension[i];
			m_Values[i] = rhs.m_Values[i];
		}

};

int		CSparseVector::operator== (CSparseVector& L2)
{
	if (m_Length != L2.GetLength() ) {return 0;}
	for (int i = 0; i < m_Length; i++) 
	{ 
		if (m_Dimension[i] != L2.m_Dimension[i]) { return 0; }
		if (m_Values[i]    != L2[i] )			 { return 0; }
	}
	return 1;
};

int CSparseVector::Delete (int Dim)
{	
	int InternalDim = -1;
	if (m_Length == 0) 
	{		
		return -1;
	}
	for (int i = 0; i < m_Length; i++) 
	{
		if  ( m_Dimension[i] == Dim) 
		{
			InternalDim = i;
			break;
		}
	}
	if (InternalDim < 0) 
	{
		return -1;
	}
	for ( i = InternalDim; i< m_Length -1; i++) 
	{
		m_Dimension[i] = m_Dimension[i+1];
		m_Values[i] = m_Values[i+1];		
	}
	m_Length--;
	return 0;
}

int	CSparseVector::GetTopDimension()
{	
	return m_Dimension[m_Length -1];
}

void	CSparseVector::SetAt (int dimen, float value) // insert New at the
													  // right spot.
{	int		index,
			RightSpot;

	if ( dimen < 0 )			
	{
		return;
	}
	// Find out if the dimension is already represented in this vector...
	
	//--------------------------------------------------
	index = ContainsDim (dimen); 
	if (index >= 0 )		// if it is already represented, fine...
	{							
		m_Values[index] = value;
		return;
	}
	
	//--------------------------------------------------
	// Otherwise, we must add a slot to represent it.
	
	m_Length++;

	if (m_Length <= m_NumberOfSlots) 
	{ 
		for (int i = 0; i < m_Length-1 && dimen > m_Dimension[i]; i++ ) 
		{
			// nothing here on purpose
		}
		RightSpot = i;
		for (i = m_Length - 1; i > RightSpot; i--) 
		{
			m_Dimension[i] = m_Dimension[i-1];
			m_Values[i]    = m_Values [i-1];
		}
		m_Values    [RightSpot] = value;
		m_Dimension [RightSpot] = dimen;
	}
	
	else 
	{
	 
		m_NumberOfSlots *= 2;
		float * Newm_Values    = new float[ m_NumberOfSlots ];
		int   * Newm_Dimension = new int  [ m_NumberOfSlots ];

		for (int i = 0; i< m_Length - 1 && dimen > m_Dimension[i] ; i++) 	
		{
			Newm_Dimension[i] = m_Dimension[i];
			Newm_Values[i]    = m_Values[i]; 
		};
		
		Newm_Values[i]    = value;
		Newm_Dimension[i] = dimen;

		for (i++; i< m_Length; i++) 	
		{
			Newm_Dimension[i] = m_Dimension[i-1];
			Newm_Values[i]    = m_Values   [i-1]; 
		};
		 
		if (m_Values) 
		{
			delete[] m_Dimension;			
			delete [] m_Values;			
		}
		m_Values = Newm_Values;
		m_Dimension = Newm_Dimension;
	}

	m_NormalizedFlag = 0;
}

void CSparseVector::operator() (int n, float val)
{	
	SetAt (n,val);
	m_NormalizedFlag =0;
}

void CSparseVector::IncrementAt(int n, float val )
{
	int dim = ContainsDim (n);
	if ( dim >= 0   ) 
	{
		m_Values[dim]  += val;
		return;
	} else			// we assume that a value that was not present is taken to be zero.
	{
		SetAt (n, val);
	}
	m_NormalizedFlag =0;
}


int Overlap (CSparseVector& List1, CSparseVector& List2)
{	
	int		overlap = 0;
	int		i = 0,
			j = 0;
	float	Val1=0,
			Val2=0;

	while ( i < List1.GetLength() && j < List2.GetLength() ) 
	{
		Val1 = List1[i];
		Val2 = List2[j];
		if (Val1 == Val2) 
		{
			overlap++;	i++; j++;
		} 
		else 
		{
			if (Val1 < Val2 ) 
			{
				i++;
			} 
			else 
			{
				j++;
			}
		}
	}
	return overlap;
}
void CSparseVector::ClearOut()
{	
	for (int i = 0; i < m_NumberOfSlots; i++) 
	{
		m_Values[i] = 0;
		m_Dimension[i] = 0;
	}
	
	m_NormalizedFlag = 0;
	m_Length = 0;
}

int CSparseVector::ContainsDim (int n)
{	// take advantage of log Size: do this smarter. Do
	// this in log n time, not n/2!
	
	if (m_Length == 0) {return -1;}

	for (int i = 0; i < m_Length; i++) 
	{
		if  ( m_Dimension[i] == n) 
		{
			return i;
		}
	}
	return -1;
}


 

ostream& CSparseVector::OutputToStream (CWordCollection& rWords, ostream& stream,int threshold)
{	
 
	BiData*		SortArray  = new BiData[ m_Length ];
 
	for (int i = 0; i<m_Length; i++) {
		 
		SortArray[i].Integer   = m_Dimension[i];
		SortArray[i].m_Values  = m_Values[i];
	}

 	qsort ( (void*) SortArray, m_Length, sizeof (BiData ), CompareBiData );

	for ( i = 0; i<m_Length ; i++) 
	{
		if ( SortArray[i].m_Values < threshold ) {continue;}
		if (SortArray[i].Integer > (int) rWords.GetCount() ||
			SortArray[i].Integer < 0 ) 
		{continue;}
		stream 
			<< setw(6)   << SortArray[i].Integer 
			<< setw(16)  << rWords[ SortArray[i].Integer ]-> GetKey() 
			<< setw (7)  << SortArray[i].m_Values 
			<< endl;

	}
	 
	delete SortArray;
	return stream;


}

int CompareBiData (const void* BiData1, const void* BiData2)
{
 
	float S1 = (float) int(	 ((BiData*) BiData1)->m_Values			);
	float S2 = (float) int(	 ((BiData*) BiData2)->m_Values			);
	if (S2 > S1) {return 1;}
	if (S2 < S1) {return -1;}
	return 0;
	 
}; 	

void CSparseVector::MakeLogFreq (CWordCollection* Words)
{	int		WordNumber;
	
	for (int i = 0; i < m_Length; i++ ) 
	{
		WordNumber = m_Dimension[i];
		Q_ASSERT ( Words->GetAt (WordNumber) ->GetCorpusCount() > 0 );
		m_Values[i] = float 
					( log ( m_Values[i] ) - 
					  log ( Words->GetAt (WordNumber)->GetCorpusCount() ) );
	}
	m_NormalizedFlag = 0;
}

void CSparseVector::Normalize()
{	float Total = 0;
	for (int i = 0; i < m_Length; i++) 
	{
		Total += m_Values[i];
	}
	for (i=0; i < m_Length; i++) 
	{
		m_Values[i] /=   Total;
	}
	m_NormalizedFlag = 1;
}
 -colin- */
int CSparseVector::GetNormalizedFlag() {return m_NormalizedFlag;}
/* -colin-
float CSparseVector::InnerProduct ( CSparseVector* Vector2)
{
	float	Total = 0,
			ThatValue= 0;
	int		ThisDim=0;

	for (int i = 0; i < m_Length; i++) 
	{
		ThisDim = m_Dimension[i];
		ThatValue = Vector2->GetAt(ThisDim);
		if (ThatValue >= 0) 
		{
			Total += m_Values[i] * ThatValue;
		}
	}
	return Total;
}
 -colin- */
 

