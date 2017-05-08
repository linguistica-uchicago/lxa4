// Implementation of CSparseIntVector methods
// Copyright © 2009 The University of Chicago
#include "SparseIntVector.h"

#include "StringSurrogate.h"
#include "Parse.h"

class CSparseIntVector;

struct BiData {
	int		Integer;
	int		Values;
	
};

int CompareBiData (const void*  , const void*  );

CSparseIntVector::CSparseIntVector() {
	Length = 0; 
	Dimension = 0; 
	Values = 0; 

	NumberOfSlots = 10;
 
	Values = new int[NumberOfSlots];
	Dimension = new int [NumberOfSlots];
	for (int i = 0; i < NumberOfSlots; i++) {
		Values[i] = 0;
		Dimension[i] = 0;
	}
	NormalizedFlag = 0;
	 

};
CSparseIntVector::CSparseIntVector ( int n)
{	
	int MinimumNumberOfSlots = 10;
	if (n > MinimumNumberOfSlots) {
		NumberOfSlots = n ;
	} else {
		NumberOfSlots = MinimumNumberOfSlots;
	}
	
	Length = n;
	Values = new int [NumberOfSlots];
	Dimension = new int [NumberOfSlots];
	for (int i = 0; i < NumberOfSlots; i++) {
		Values[i] = 0;
		Dimension[i] = 0;
	}
	NormalizedFlag = 0;
	 
};
CSparseIntVector::	CSparseIntVector (CSparseIntVector& rhs){
	 
	NumberOfSlots = rhs.GetNumberOfSlots();
	Length = rhs.GetLength();
	int i;
	for ( i = 0; i<Length; i++) { Values[i] = rhs[i];};
	
	for ( i = Length; i < NumberOfSlots; i++) 
	{
		Values[i] = rhs[i];
	}

//	NormalizedFlag = rhs.GetNormalizedFlag();
}

CSparseIntVector::	~CSparseIntVector()
{	if (Values) {
		delete Values;
	}
	if (Dimension) {
		delete Dimension;
	}
}


int	CSparseIntVector::operator< (CSparseIntVector& RHS)
{
	if ( Length  < RHS.Length ) {
		return 1;
	}
	if ( Length  > RHS.Length ) {
		return -1;
	}

	for (int i = 0; i < Length; i++) {
		if ( Dimension[i] < RHS.Dimension[i] ) {
			return 1;
		} 
		if ( Dimension[i] > RHS.Dimension[i] ) {
			return -1;
		} 		
	}
	return 0;
}

int	CSparseIntVector::operator> (CSparseIntVector& RHS)
{
	if ( Length  > RHS.Length ) {
		return 1;
	}
	if ( Length  < RHS.Length ) {
		return -1;
	}

	for (int i = 0; i < Length; i++) {
		if ( Dimension[i] > RHS.Dimension[i] ) {
			return 1;
		} 
		if ( Dimension[i] < RHS.Dimension[i] ) {
			return -1;
		} 		
	}
	return 0;
}





void CSparseIntVector::Clear() {
	if (Length > 0) {
		for (int i = 0; i < NumberOfSlots; i++) {
			Values[i] = 0;
		}	
	}
	NormalizedFlag = 0;
}

void CSparseIntVector::SetLength (int n) { 
	Length = n;
	NumberOfSlots = n;
	Values = new int [n];
}
int CSparseIntVector:: GetLength() {return Length;}

int CSparseIntVector::operator[] (int n) {
	if (n < 0 || n >= Length ) {return -1;}
	else { return Values[n]; };
}

int CSparseIntVector::GetNumberOfSlots() {return NumberOfSlots;}

int	CSparseIntVector::GetNextDimension (int& DimOut, int& Position)
{
	if (Position < 0) {return 0;}
	if (Position >=   Length) {return 0;} 
	DimOut = Dimension[Position];
	Position++;
	return 1;

}
int CSparseIntVector::GetAt (int dim)  // dim is the value to the outside world
{	int n = ContainsDim(dim);
	if (n == -1 )	{	return -1;	}
	else			{	return  Values[n]; };	
}

void CSparseIntVector::operator= (CSparseIntVector& rhs)
{	// March 17 2000 JG
		Length = rhs.GetLength();
		if ( rhs.GetLength() > NumberOfSlots ) 
		{
			if (Dimension)	delete Dimension;
			if (Values)		delete Values;
			NumberOfSlots = rhs.GetLength();
			Dimension = new int [NumberOfSlots];
			Values = new int [NumberOfSlots];
		}
		for (int i = 0; i<Length; i++) 
		{ 
			Dimension[i] = rhs.Dimension[i];
			Values[i] = rhs.Values[i];
		}
}
int		CSparseIntVector::operator== (CSparseIntVector& L2)
{
	if (Length != L2.GetLength() ) {return 0;}
	for (int i = 0; i < Length; i++) { 
		if (Dimension[i] != L2.Dimension[i]) {return 0;}
		if (Values[i] != L2[i] ) {return 0;}
	}
	return 1;
};

int CSparseIntVector::Delete (int Dim)
{	int InternalDim = -1,
		i;
	if (Length == 0) {return -1;}
	for ( i = 0; i < Length; i++) 
	{
		if  ( Dimension[i] == Dim) 
		{
			InternalDim = i;
			break;
		}
	}
	if (InternalDim < 0) {
		return -1;
	}
	for ( i = InternalDim; i< Length-1; i++) {
		Dimension[i] = Dimension[i+1];
		Values[i] = Values[i+1];
		Length--;
	}
	return 0;
}

int	CSparseIntVector::GetTopDimension()
{	return Dimension[Length-1];}

void	CSparseIntVector::SetAt (int dimen, int value) // insert New at the
											// right spot.
{	int		index,
			RightSpot = -1,
			i;

	if (dimen < 0 ) {return;}
	index = ContainsDim (dimen); 
	if (index >= 0 ) {
		Values[index] = value;
		return;
	}

	Length++;

	if (Length <= NumberOfSlots) 
	{ 
		//Feb 28 1999
		// special case if we happen to be appending at the end:
		if ( dimen > Dimension[Length-2] ) 
		{
			Dimension[ Length - 1 ] = dimen;
			Values   [ Length - 1 ] = value;
			return; // march 15 1999
		}

		for ( i = 0; i < Length-1 && dimen > Dimension[i]; i++ ) 
		{
           RightSpot = i+1;
		}
		for ( i = Length-1; i > RightSpot; i--) 
		{
			Dimension[i] = Dimension[i-1];
			Values[i] = Values [i-1];
		}
		Values[RightSpot] = value;
		Dimension [RightSpot] = dimen;
	}	
	else 	
	{
	 
		NumberOfSlots *= 2;
		int * NewValues		= new int [NumberOfSlots];
		int * NewDimension	= new int [NumberOfSlots];

    int pos;
	pos=0;
		for ( i = 0; i<Length-1 && dimen > Dimension[i] ; i++) 	
		{
			NewDimension[i] = Dimension[i];
			NewValues[i] = Values[i];
      pos = i+1;
		}
		NewValues[pos] = value;
		NewDimension[pos] = dimen;
		for ( i = pos + 1; i<Length; i++) 	
		{
			NewDimension[i] = Dimension[i-1];
			NewValues[i] = Values[i-1]; 
		}
		 
		if (Values) 
		{
			delete[] Dimension;
			Dimension = 0;
			delete [] Values;
			Values = 0;
		}
		Values = NewValues;
		Dimension = NewDimension;
	}

	NormalizedFlag = 0;
}

void CSparseIntVector::operator() (int n, int val)
{	SetAt (n,val);
	NormalizedFlag =0;
}

int CSparseIntVector::operator () (int n) {
	int loc = ContainsDim (n);
	return GetAt(loc);

}
void CSparseIntVector::IncrementAt(int n, int val ){
	int dim = ContainsDim (n);
	if ( dim >= 0   ) {
		Values[dim]  += val;
		return;
	} else {
		SetAt (n, val);
	}
	NormalizedFlag =0;
}


int Overlap (CSparseIntVector& List1, CSparseIntVector& List2)
{	int overlap = 0;
	int	i = 0,
		j = 0;
	int	Val1=0,
			Val2=0;
	while (i < List1.GetLength() && j < List2.GetLength() ) {
		Val1 = List1[i];
		Val2 = List2[j];
		if (Val1 == Val2) {
			overlap++;	i++; j++;
		} else {
			if (Val1 < Val2 ) {
				i++;
			} else {
				j++;
			}
		}
	}
	return overlap;
}
void CSparseIntVector::ClearOut()
{	for (int i = 0; i < NumberOfSlots; i++) {
		Values[i] = 0;
		Dimension[i] = 0;
	}
	Length = 0;
	NormalizedFlag = 0;
}

int CSparseIntVector::ContainsDim (int n)
{	// take advantage of log Size: do this smarter.!
	
	if (Length == 0) {return -1;}



	for (int i = 0; i < Length; i++) {
		if  ( Dimension[i] == n) {
			return i;
		}
	}
	return -1;
}


 
/* TODO: find alternative if used
ostream& CSparseIntVector::OutputToStream (CWordCollection& rWords, ostream& stream,int threshold)
{	
 
	BiData*		SortArray  = new BiData[Length];
 
	for (int i = 0; i < (int) Length; i++) {
		 
		SortArray[i].Integer = Dimension[i];
		SortArray[i].Values	 = Values[i];
	}

 // put this back in:
//	qsort ( (void*) SortArray, Length, sizeof (BiData ), CompareBiData );

	for ( i = 0; i < (int) Length; i++) {
		if ( SortArray[i].Values < threshold ) {continue;}
		if ( SortArray[i].Integer > (int) rWords.GetCount() ||
			SortArray[i].Integer < 0 ) 
		{continue;}
	
		stream << setw(6) << SortArray[i].Integer << setw(16)  << 
			rWords[ SortArray[i].Integer ]-> GetKey() << setw (7)   << 
										SortArray[i].Values << endl;



	}
	
	
	
	 
	delete SortArray;
	return stream;




}
*/
/* TODO: need CWordCollection

void CSparseIntVector::MakeLogFreq (CWordCollection* Words)
{	int		WordNumber;
	for (int i = 0; i < Length; i++ ) {
		WordNumber = Dimension[i];
		Values[i] = int 
					( log ( Values[i] ) - 
					  log ( Words->GetAt (WordNumber)->GetCorpusCount() ) );
	}
	NormalizedFlag = 0;
}
*/

void CSparseIntVector::Normalize()
{	
	int Total = 0,
		i;
	for ( i = 0; i < Length ; i++) {
		Total += Values[i];
	}
	for ( i=0; i < Length ; i++) {
		Values[i] /=   Total;
	}
	NormalizedFlag = 1;
}
int CSparseIntVector::GetNormalizedFlag() {return NormalizedFlag;}

int CSparseIntVector::InnerProduct ( CSparseIntVector* Vector2)
{
	int		Total = 0,
			ThatValue= 0;
	int		ThisDim=0;

	for (int i = 0; i < Length ; i++) {
		ThisDim = Dimension[i];
		ThatValue = Vector2->GetAt(ThisDim);
		if (ThatValue >= 0) {
			Total += Values[i] * ThatValue;
		}
	}
	return Total;
}

int CSparseIntVector::GetFirstDimension()
{	if (Dimension) { return Dimension[0] ;}
	else { return 0;}

}

void CSparseIntVector::Ingest(CSparseIntVector* pVector)
{
	int Position = 0,
		DimOut= 0;
	while ( pVector->GetNextDimension (DimOut, Position) ) {
		SetAt (DimOut, 1);
	}
}

bool CSparseIntVector::Contains (CSparseIntVector* pVec)
{	
	int ThisDim,
	
		ThatDim,
		DimPos = 0;

		ThatDim=0;
	// Oct 30 1999:
	if (pVec->GetLength() > GetLength() ) {
		return 0;
	}
	
	pVec->GetNextDimension( ThatDim, DimPos );

	for (int i = 0; i < Length; i ++) {
		ThisDim = Dimension[i];

		
		/* we step through the values present in This,
		looking to see if That has such a dimension;
		if we slip past That without finding its dimension,
		it means This doesn't contain that. Note the use
		of MFC-style iterator for the That vector */
		
		if ( ThisDim == ThatDim ){
			if (! pVec->GetNextDimension( ThatDim, DimPos ) ) {
				return TRUE;//we've gone through pVec entirely
			}
			continue;
		}
		if ( ThisDim < ThatDim ) {
			continue;
		}
		if ( ThisDim > ThatDim ) {
			return FALSE;
		}	
	}

	return FALSE; //October 30 1999	
	 
}

// Oct 31 1999 JG
int CSparseIntVector::Union (CSparseIntVector& Vector)
{
		 NumberOfSlots  += Vector.GetLength();		
	int* NewDimension	= new int [NumberOfSlots];
	int* NewValues		= new int [NumberOfSlots];
	
	int				This = 0, 
					That = 0,
					ThisDim = -1,
					ThatDim = -1,
					NewDim = 0;

	while ( ( This >= 0 && This < Length)
					|| 
			(That >= 0 && That < Vector.Length ) 
		  )
	{
		
		if (This >= 0 && This < Length ) {  //This is in the legal zone
			ThisDim = Dimension[This];			
		}	else {
			ThisDim = -1;
		}
		if (That >= 0 && That < Vector.Length ) {	//That is in the legal zone
			ThatDim = Vector.Dimension[That];			
		} else {
			ThatDim = -1;
		}

		if  ( ThatDim < 0 ||					   // That is exhausted
			 ( ThisDim >= 0 && ThisDim < ThatDim ) // This is real, so is That, This is smaller
			)
		{		
			NewDimension[NewDim] = ThisDim;
			//NewValues[NewDim] = 1;	change March 5 2000 JG			
			NewValues[NewDim] = Values[This];	// March 5 2000
			This ++;		
		} 
		if (ThisDim < 0 ||							//This is exhausted
			 ( ThatDim >= 0 && ThatDim < ThisDim )	// This is real, so is That, That is smaller
			)
		{
			NewDimension[NewDim] = ThatDim;
			//NewValues[NewDim] =1;			change March 5 2000 JG
			NewValues[NewDim] = Vector.Values[That];	// March 5 2000
			That++;
		}
	
		if (ThisDim >= 0 && ThisDim == ThatDim) {
			NewDimension[NewDim] = ThatDim;
			//NewValues[NewDim] =1;		//  change March 5 2000 JG						
			NewValues[NewDim] = Values[This] + Vector.Values[That];	// March 5 2000
			That++;
			This++;
		}


				
		 
		NewDim ++;
		
		if (This >= Length ) {
			This = -1;
		}
		if (That >= Vector.Length ) {
			That = -1;
		}
	}

	Length = NewDim ;

	delete Dimension;
	delete Values;

	Dimension = NewDimension;
	Values = NewValues;
	
	return Length;
}



// Oct 31 1999
int Overlap (CSparseIntVector* List1, CSparseIntVector* List2, CSparseIntVector& Intersection)
{		
	if ( List1->Length < List2->Length) {
		Intersection.NumberOfSlots = List1->Length;
	} else {
		Intersection.NumberOfSlots = List2->Length;
	}

	
	if (Intersection.Dimension) {
		delete Intersection.Dimension;
	}
	if (Intersection.Values) {
		delete Intersection.Values;
	}
	
	Intersection.Dimension = new int [Intersection.NumberOfSlots];
	Intersection.Values = new int [Intersection.NumberOfSlots];

	int				This = 0, 
					That = 0,
					ThisDim = 0,
					ThatDim = 0,
					NewDim = 0;

	while (This >= 0 && That >= 0) {

		if (This >= 0) {
			ThisDim = List1->Dimension[This];
		}
		if (That >= 0) {
			ThatDim = List2->Dimension[That];
		}

		if (This >= 0 && ThisDim == ThatDim) {
			Intersection.Dimension[NewDim] = ThisDim;
			Intersection.Values[NewDim] = 1;		
			This ++;
			That ++;		
			NewDim ++;
		}
		if (ThisDim >= 0   &&  ThisDim < ThatDim) {		
			This ++;		
		}
		if (ThatDim >= 0   &&   ThisDim > ThatDim) {			
			That ++;
		}
		
		if (This >= List1->Length ) {
			This = -1;
		}
		if (That >= List2->Length ) {
			That = -1;
		}
	}

	Intersection.Length = NewDim  ;
	


	return Intersection.GetLength();
}

CParse CSparseIntVector::Display()
{
	CParse Return;
	for (int i = 0 ; i < Length; i++)
	{
		QString colon = ":", space = " ";
		Return.Append (Dimension[i]);
		Return.Append( CStringSurrogate( colon.unicode(), 0, colon.length()) );
		Return.Append ( Values[i] );
		Return.Append ( CStringSurrogate( space.unicode(), 0, space.length()) );
	}
	return Return;
}
QString CSparseIntVector::DisplayAsString()
{
	QString Return,
			Temp;
	for (int i = 0; i < Length; i++)
	{
		Temp.arg( Dimension[i] );
		Temp += ":";
		Temp.arg( Values[i] ) ;
		Return += Temp;
	}

	return Return;
}
