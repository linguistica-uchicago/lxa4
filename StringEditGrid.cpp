// implementation of CStringEditGrid methods
// Copyright © 2009 The University of Chicago
#include "StringEditGrid.h"
#include <algorithm>
#include "Alignment.h" 
#include "Parse.h"
#include "StringFunc.h"

// construction/destruction.

namespace {
	void copy_cstr(const QChar* src, const std::size_t len, QChar* dest)
	{
		std::copy(&src[0], &src[len], &dest[0]);
		dest[len] = QChar();
	}
	QChar* new_cstr(const QChar* src, const std::size_t len)
	{
		QChar* dest = new QChar[len + 1];
		copy_cstr(src, len, dest);
		return dest;
	}
}
CStringEditGrid::CStringEditGrid(CAlignment* pAlign)
	: m_Length1(pAlign->m_Length1),
	m_String1(new_cstr(pAlign->m_Str1->GetKeyPointer(), m_Length1)),
	m_Length2(pAlign->m_Length2),
	m_String2(new_cstr(pAlign->m_Str2->GetKeyPointer(), m_Length2)),
	m_DeletionCost(1.0),
	m_SubstitutionCost(1.5),
	m_Scores(new float[m_Length1 * m_Length2]),	// left uninitialized
	// left uninitialized
	m_GridEntries(new StringEditGridEntry*[m_Length1 * m_Length2]) { }

CStringEditGrid::CStringEditGrid(const QString String1, const QString String2)
	: m_Length1(String1.size()),
	m_String1(new_cstr(String1.data(), m_Length1)),
	m_Length2(String2.size()),
	m_String2(new_cstr(String2.data(), m_Length2)),
	m_DeletionCost(1.0),
	m_SubstitutionCost(1.5),
	m_Scores(new float[m_Length1 * m_Length2]),	// left uninitialized
	// left uninitialized
	m_GridEntries(new StringEditGridEntry*[m_Length1 * m_Length2])
{ Q_ASSERT(!String1.isEmpty() && !String2.isEmpty()); }

CStringEditGrid::~CStringEditGrid()
{
	for (int i = 0; i < m_Length1 * m_Length2; ++i)
		delete m_GridEntries[i];
	delete[] m_GridEntries;
	delete[] m_Scores;

	delete[] m_String2;
	delete[] m_String1;
}

float CStringEditGrid::GetScore(int row, int col)
{
	if (row >= m_Length2 || col >= m_Length1 ) { return -1; }

	return ( m_Scores [ row * m_Length1 + col ] );


}
void CStringEditGrid::SetScore(int row, int col, float value)
{
	if (row >= m_Length2 || col >= m_Length1 ) { return ; }
	
	m_Scores [ row * m_Length1 + col ] = value;
	

}


CAlignment& CStringEditGrid::GetAlignment(CAlignment& Alignment)
{	 
		Alignment.m_Identities = 0;

		if ( Alignment.m_Match1 ) { delete Alignment.m_Match1; }
		if ( Alignment.m_Match2 ) { delete Alignment.m_Match2; }
		
		Alignment.m_Match1 = new int [ m_Length1 ];
		Alignment.m_Match2 = new int [ m_Length2 ];
		Alignment.m_Slips = 0;
		Alignment.m_Spans = 1;

		StringEditGridEntry*		pEntry;
		int							row				= m_Length2 - 1;
		int							col				= m_Length1 - 1;
		eAlignmentOperation			PreviousMatch	= End;

		// we're going to move backwards, down the grid from the upper right-hand corner
		// to the lower left-hand corner.
		// You have to understand string-edit grids to follow what's going on here!


		pEntry = GetStringEditGridEntry (row, col);

		while ( pEntry->m_Movement != Start )
		{
			switch (pEntry->m_Movement)
			{
			case FromBelow:
				{
					// we added an element from String2 not linked to String1
					if ( PreviousMatch == IdenticalMatch ||
						 PreviousMatch == End 
					   )
					{
						Alignment.m_Slips++;
					}
					if ( PreviousMatch == IdenticalMatch )
					{
						Alignment.m_Spans++;
						Alignment.m_Str1->CutRightBeforeHere(col+1);
						Alignment.m_Str2->CutRightBeforeHere(row+1);
						
					}

					Alignment.m_Match2[row] = -1;					
					row--;
					PreviousMatch = FromBelow;
					pEntry = GetStringEditGridEntry(row, col);
					break;
				}
			case FromLeft:
				{
					// we added an element from String1 not linked to String2
					if ( PreviousMatch == IdenticalMatch  || 
						 PreviousMatch == End 
					   )
					{
						Alignment.m_Slips++;
					}
					if ( PreviousMatch == IdenticalMatch )
					{
						Alignment.m_Spans++;
						Alignment.m_Str1->CutRightBeforeHere (col+1); 
						Alignment.m_Str2->CutRightBeforeHere (row+1); 
					}

					Alignment.m_Match1[col] = -1;					
					col--;
					PreviousMatch = FromLeft;
					pEntry = GetStringEditGridEntry (row, col);
					break;
				}
			case FromBelowAndLeft:
				{	// we made a matching alignment

					Alignment.m_Match1[col] = row;
					Alignment.m_Match2[row] = col;
				
					if (m_String1[col] == m_String2[row] )
					{
						if ( PreviousMatch != IdenticalMatch &&
							 PreviousMatch != End   )
						{
							Alignment.m_Spans++;
							Alignment.m_Str1->CutRightBeforeHere(col+1); 
							Alignment.m_Str2->CutRightBeforeHere(row+1); 
						}
						PreviousMatch = IdenticalMatch;
						Alignment.m_Identities++;
					}
					else // non-identity match
					{
						if ( PreviousMatch == IdenticalMatch ||  // april 2003
							 PreviousMatch == End
						   )
						{
							Alignment.m_Slips++;
						}	
						if ( PreviousMatch == IdenticalMatch ) // april 2003							
						{
							Alignment.m_Spans++;
							Alignment.m_Str1->CutRightBeforeHere(col+1); 
							Alignment.m_Str2->CutRightBeforeHere(row+1); 
						}
						PreviousMatch = NonIdenticalMatch;
					}
					col--;
					row--;
					pEntry = GetStringEditGridEntry (row, col);
					break;
					// yuhuask ? Not very clear about the diff between slips and spans

				}
			default: break;
			}			
		}
	
	Q_ASSERT (row == 0);
	Q_ASSERT (col == 0);
	Q_ASSERT (Alignment.m_Str1->GetChar(0) == '#');
	Alignment.m_Match1[0] = 0;
	Alignment.m_Match2[0] = 0;

	return Alignment;
}

StringEditGridEntry* CStringEditGrid::GetStringEditGridEntry(int row, int col)
{
	if (row >= m_Length2 || col >= m_Length1 )
	{
		return NULL;
	}
	return m_GridEntries [ row * m_Length1 + col ] ;


}

void CStringEditGrid::SetStringEditGridEntry (int row, int col, StringEditGridEntry* pAlign)
{
	if (row >= m_Length2 || col >= m_Length1 )
	{
		return ;
	}
	m_GridEntries [ row * m_Length1 + col ] = pAlign;
	

}

float CStringEditGrid::FindBestAlignment(CAlignment& Alignment)
{


	
	float						ScoreFromBelow, 
								ScoreDiagonal, 
								ScoreFromLeft;
	int							Winner = 0;
	float						BestScore = 0.0;
	StringEditGridEntry* pEntry;
	float						Cost ;

	for (int col = 0; col < m_Length1; col++)  
	{
		for (int row = 0; row < m_Length2; row++) // row number
		{
	
			if (col == 0 && row == 0)
			{				
				pEntry = new StringEditGridEntry;				
				pEntry->m_Movement = Start;
				pEntry->m_Slips = 0;
				SetStringEditGridEntry (0,0, pEntry);
				SetScore(0,0, 0 );
				continue;
			}

			if ( col == 0) { ScoreFromLeft = -1; } 
			else
			{
				ScoreFromLeft = GetScore( row, col-1) + m_DeletionCost;					
			};
			
			if (row == 0) { ScoreFromBelow = -1; }
			else
			{
				ScoreFromBelow = GetScore( row - 1, col ) + m_DeletionCost;				
			}
			
			if (row == 0 || col == 0) { ScoreDiagonal = -1; }
			else
			{
				Cost = GetCost( m_String1[col], m_String2[row] );				
				ScoreDiagonal = GetScore (row-1, col-1 ) + 	Cost;
			}
			//-------------------------------------------------
			// Now find the lowest score that isn't negative
			//--------------------------------------------------
			if (ScoreFromLeft >= 0) 
			{
				Winner = 0;				
				BestScore = ScoreFromLeft;
			}
			else if (ScoreFromBelow >= 0 )
			{
				Winner = 1;
				BestScore = ScoreFromBelow;
			}
			else if (ScoreDiagonal >= 0 )
			{
				Winner = 2;
				BestScore = ScoreDiagonal;
			}
			else { Q_ASSERT (FALSE); }

			if (Winner == 0)
			{
				if ( ScoreFromBelow >= 0 && ScoreFromBelow < ScoreFromLeft )
				{
					Winner = 1;					
					BestScore = ScoreFromBelow;
				}
			}
			if (Winner == 0 || Winner == 1)
			{
				if ( ScoreDiagonal >= 0 && ScoreDiagonal < BestScore )
				{
					Winner = 2;					
					BestScore = ScoreDiagonal;
				}
			}
			//--------------------------------------------------
			//	Use the conclusions...
			//--------------------------------------------------

			if (Winner == 0)  // arrow from left
			{

				pEntry = new StringEditGridEntry;				
				SetStringEditGridEntry (row, col, pEntry);
				pEntry->m_Movement = FromLeft;
//				qEntry = GetStringEditGridEntry (row, col-1);  

			}
			if (Winner == 1)  // arrow from below
			{

				pEntry = new StringEditGridEntry;		
				SetStringEditGridEntry (row, col, pEntry);
				pEntry->m_Movement = FromBelow;
//				qEntry = GetStringEditGridEntry (row-1, col);


			}
			if (Winner == 2) // up the diagonal
			{

				pEntry = new StringEditGridEntry;		
				SetStringEditGridEntry (row, col, pEntry);
				pEntry->m_Movement = FromBelowAndLeft;
//				qEntry = GetStringEditGridEntry (row-1, col-1);

			}
			SetScore (row, col, BestScore);
		}
	}
	
	
	
	GetAlignment (Alignment );
	Alignment.m_Score = BestScore;
	
    return BestScore;
//    return GetScore (m_Length2 - 1, m_Length1 - 1); //why was this here? JG
	



}

float CStringEditGrid::GetCost(QChar c1, QChar c2)
{

	if ( c1 == c2 ) { return 0; }
	else { return m_SubstitutionCost; }

}

