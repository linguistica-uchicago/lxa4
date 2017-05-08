// Implementation of CAlignment methods
// Copyright © 2009 The University of Chicago
#include "Alignment.h"
#include "StringEditGrid.h"
#include "StringSurrogate.h"
#include "Parse.h"

// construction/destruction.

CAlignment::CAlignment(const QString String1, const QString String2)
	: m_Str1(new CParse(CStringSurrogate(QString('#') + String1))),
	m_Str2(new CParse(CStringSurrogate(QString('#') + String2))),
	m_Length1(String1.size() + 1),
	m_Length2(String2.size() + 1),
	m_Match1(new int[m_Length1]),	// filled below
	m_Match2(new int[m_Length2]),	// filled below
	m_Score(0.0),
	m_Slips(0),
	m_Spans(1),
	m_Identities(0)
{
	std::fill(&m_Match1[0], &m_Match1[m_Length1], -5);
	std::fill(&m_Match2[0], &m_Match2[m_Length2], -5);
}

CAlignment::CAlignment(CParse* Parse1, CParse* Parse2)
	: m_Str1(),	// initialized below
	m_Str2(),	// initialized below
	m_Length1(Parse1->GetKeyLength() + 1),
	m_Length2(Parse2->GetKeyLength() + 1),
	m_Match1(new int[m_Length1]),	// filled below
	m_Match2(new int[m_Length2]),	// filled below
	m_Score(0.0),
	m_Slips(0),
	m_Spans(1),
	m_Identities(0)
{
	{
		m_Str1 = new CParse(QChar('#'));
		m_Str1->Append(*Parse1);
		m_Str1->SimplifyParseStructure();
	}
	{
		m_Str2 = new CParse(QChar('#'));
		m_Str2->Append(*Parse2);
		m_Str2->SimplifyParseStructure();
	}
	std::fill(&m_Match1[0], &m_Match1[m_Length1], -5);
	std::fill(&m_Match2[0], &m_Match2[m_Length2], -5);
}

CAlignment::CAlignment(const CAlignment* other)
	: m_Str1(new CParse(*other->m_Str1)),
	m_Str2(new CParse(*other->m_Str2)),
	m_Length1(other->m_Length1),
	m_Length2(other->m_Length2),
	m_Match1(new int[m_Length1]),	// filled below
	m_Match2(new int[m_Length2]),	// filled below
	m_Score(other->m_Score),
	m_Slips(other->m_Slips),
	m_Spans(other->m_Spans),
	m_Identities(other->m_Identities)
{
	std::copy(&other->m_Match1[0], &other->m_Match1[m_Length1],
		&m_Match1[0]);
	std::copy(&other->m_Match2[0], &other->m_Match2[m_Length2],
		&m_Match2[0]);
}

CAlignment::CAlignment(const CAlignment& other)
	: m_Str1(new CParse(*other.m_Str1)),
	m_Str2(new CParse(*other.m_Str2)),
	m_Length1(other.m_Length1),
	m_Length2(other.m_Length2),
	m_Match1(new int[m_Length1]),	// filled below
	m_Match2(new int[m_Length2]),	// filled below
	m_Score(other.m_Score),
	m_Slips(other.m_Slips),
	m_Spans(other.m_Spans),
	m_Identities(other.m_Identities)
{
	std::copy(&other.m_Match1[0], &other.m_Match1[m_Length1],
		&m_Match1[0]);
	std::copy(&other.m_Match2[0], &other.m_Match2[m_Length2],
		&m_Match2[0]);
}

CAlignment::~CAlignment()
{
	delete[] m_Match2;
	delete[] m_Match1;
	delete m_Str2;
	delete m_Str1;
}

CAlignment& CAlignment::operator=(const CAlignment& other)
{
	*m_Str1 = *other.m_Str1;
	*m_Str2 = *other.m_Str2;
	m_Length1 = other.m_Length1;
	m_Length2 = other.m_Length2;
	std::copy(&other.m_Match1[0], &other.m_Match1[m_Length1],
		&m_Match1[0]);
	std::copy(&other.m_Match2[0], &other.m_Match2[m_Length2],
		&m_Match2[0]);
	m_Score = other.m_Score;
	m_Slips = other.m_Slips;
	m_Spans = other.m_Spans;
	m_Identities = other.m_Identities;
	return *this;
}

bool CAlignment::String1CharMatches(int n)// true if the char is aligned and identical to matchee
{
	
	if ( m_Match1[n] == -1 ) return FALSE;
	if ( m_Str1->GetChar(n) == m_Str2->GetChar( m_Match1[ n ] ) )
	{
		return TRUE;
	}
	
	return FALSE;

}

bool CAlignment::String2CharMatches(int n)// true if the char is aligned and identical to matchee
{
	
	if ( m_Match2[n] == -1 ) return FALSE;
	if ( m_Str2->GetChar(n) == m_Str1->GetChar( m_Match2[ n ] ) )
	{
		return TRUE;
	}
	
	return FALSE;

}
bool CAlignment::PerfectMatch (int n, int m )// true of these two chars are identical and aligned
{
	
	if ( m_Match1[n] == m  &&
		 m_Match2[m] == n  &&
		 m_Str1->GetChar(n) == m_Str2->GetChar(m)
		 )
	{
		 return TRUE;
	}
	
	else
	return FALSE;

}

CParse CAlignment::CalculateDisplay()
{
	
	CParse Return;
	/*
	UINT index = 0; // on the page
	int locTop = 1, locBottom = 1; // because 0's are for the word boundary symbols #
	int State= 0; 
	char Top [50], Bottom[50], Middle[50];
	CParse Return;
	CParse TopPiece, BottomPiece;
	 
		0	Both match
		1	Just top
		2	Just bottom
		3	both no match
	
	
	

	while ( locTop < m_Length1 || locBottom < m_Length2 )
	{
		switch (State)
		{
		case 0: // Both match
			{
				while ( PerfectMatch (locTop, locBottom) && 
								locTop < m_Length1 
				       )
				{
					Top    [ index ] = m_Str1->GetChar( locTop++ );
					Bottom [ index ] = m_Str2->GetChar( locBottom++ );
					Middle [ index ] = '|';
					index++;

					Top    [ index ]  = ' ';
					Bottom [ index ]  = ' ';
					Middle [ index ]  = ' ';
					index++;

				}
				if ( locTop == m_Length1 
					 && locBottom == m_Length2   )
					break;
				//----------------------------------------------//
				
				
				if ( locTop == m_Length1  )
				{
					State = 2;
					break;
				}
				if ( locBottom == m_Length2  )
				{
					State = 1;
					break;
				}

				if (m_Match1 [ locTop ] == locBottom
					&&
					m_Match2 [ locBottom ] == locTop	
				    )
				{
					State = 3;					
				}
				else if ( m_Match1 [ locTop ] == -1 )
				{
					State = 1;
				}
				else
				{
					State = 2;
				}
				break;
			}		
			
			 
		case 1:
			{
				while ( m_Match1 [ locTop ] == -1 )
				{
					TopPiece.Append( m_Str1->GetChar( locTop ) );

					Top		[ index ] = m_Str1->GetChar( locTop++ );
					Bottom  [ index ] = ' ';
					Middle  [ index ] = ' ';
					index++;

					Top    [ index]	 = ' ';
					Bottom [ index ] = ' ';
					Middle [ index]  = ' ';
					index++;
					
				}
				TopPiece.Append (' ');
			//-----------------------------------------------//	
				if ( PerfectMatch (locTop, locBottom) )								    
				{
					State = 0;										
				}
				else if (m_Match1 [ locTop ] == locBottom
						&&
						m_Match2 [ locBottom ] == locTop	
						)
				{
					State = 3;
				}				
				else
				{
					State = 2;
				}
				break;
			}		
		case 2:
			{
				while ( m_Match2 [ locBottom ] == -1 )
				{
					Top		[ index ] = ' ';
					Bottom  [ index ] = m_Str2->GetChar( locBottom++ );
					Middle  [ index ] = ' ';
					index++;

					Top    [ index]	 = ' ';
					Bottom [ index ] = ' ';
					Middle [ index]  = ' ';
					index++;
				}
			//-----------------------------------------------//	
				if ( PerfectMatch (locTop, locBottom) )				    
				{
					State = 0;
					
				}
				else if (m_Match1 [ locTop ] == locBottom
						&&
						m_Match2 [ locBottom ] == locTop	
						)
				{
					State = 3;
				}								
				break;
			}
		
		case 3: // Linked but not a match
			{
				while ( m_Match1 [ locTop ] == locBottom
					&&
					m_Match2 [ locBottom ] == locTop	
					&&
					m_Str1->GetChar(locTop ) != m_Str2->GetChar(  locBottom )
				   )
				{
					Top    [ index]		= m_Str1->GetChar( locTop++ );
					Bottom [ index ] = m_Str2->GetChar( locBottom++ );
					Middle [ index] = '#';
					index++;


					Top    [ index]	 = ' ';
					Bottom [ index ] = ' ';
					Middle [ index]  = ' ';
					index++;

				}
				//----------------------------------------------//
				if (m_Match1 [ locTop ] == locBottom
					&&
					m_Match2 [ locBottom ] == locTop	
				    )
				{
					State = 0;										
				}
				else if ( m_Match1 [ locTop ] == -1 )
				{
					State = 1;
				}
				else
				{
					State = 2;
				}
				break;
			} // end of case 		

	}










	}

	
	Top		[ index ] = '\0';
	Middle	[ index ] = '\0';
	Bottom	[index  ] = '\0';

	Return.Append('\n');
	Return.Append(Top);
	Return.Append('\n');
	Return.Append(Middle);
	Return.Append('\n');
	Return.Append(Bottom);
	Return.Append('\n');
	Return.Append ("Slips: " );
	Return.Append( m_Slips);
	Return.Append ("Spans: " );
	Return.Append( m_Spans);
	return Return;
	
	  */
	return Return;
}


CParse CAlignment::FindSubstitution()
// this assumes that there is only one part of the alignment
// where the two words disagree; and it returns the two 
// pieces that disagree with each other. 
{	
	CParse		Return;
 	int			Str1Match = 0, Str2Match = 0;
 
	if ( m_Slips != 1 ) { return Return; }  

	int piece;
	for (piece = 1; piece <= m_Str1->Size(); piece++)
	{
		Str2Match = Str2MatchForStr1Piece (piece);
		if ( Str2Match <= 0    ||  m_Str1->GetPiece(piece) != m_Str2->GetPiece(Str2Match)  )
		{
			Return.Append( m_Str1->GetPiece( piece ) ) ;
		}
	}

	if ( Return.Size() == 0) 
	{
		Return = CParse(CStringSurrogate(QString("NULL").unicode(), 0, 4)); 
	}
	//---------------------------------------------------------------//
	for (piece = 1; piece <= m_Str2->Size(); piece++)
	{
		Str1Match = Str1MatchForStr2Piece (piece);
		if ( Str1Match <= 0  || m_Str2->GetPiece(piece) != m_Str1->GetPiece(Str1Match)  )
		{
			Return.Append( m_Str2->GetPiece( piece ) ) ;			
		}
	}

	if ( Return.Size() == 1) 
	{
		Return.Append( CStringSurrogate(QString("NULL").unicode(), 0, 4)); 
	}

	return Return;
 
}

CParse CAlignment::SpellOut()
{

	CParse Return ( *m_Str1 );
	Return.Append ( *m_Str2);
	
	return Return;
}



CParse CAlignment::FindContext()
{	
	/* This returns a parse consisting of 2 or 3 pieces; each piece is either something shared by 
		both strings of the alignment, or else it's an underscore, representing the difference(s)
		between the string. */
	

	CParse		Return;

	int			loc1=1, loc2=1;  
	int			StartLoc1 = 0, StartLoc2 = 0;
	int			State; // 1=matching, 2= not matching

	if (m_Spans > 3 ) { return Return; }


	if ( PerfectMatch (1,1) )
	{
		State = 1; // matching
	}
	else
	{
		State = 2; // not matching
	}

	while ( loc1 < m_Length1 || loc2 < m_Length2 )
	{
		if (State == 1)
		{
			while ( loc1 < m_Length1    &&    loc2 < m_Length2    &&   PerfectMatch (loc1, loc2)  )
			{
				loc1++;
				loc2++;
			}

			CStringSurrogate Piece1 ( m_Str1->GetKeyPointer(), StartLoc1, loc1 - StartLoc1 );
			CStringSurrogate Piece2 ( m_Str2->GetKeyPointer(), StartLoc2, loc2 - StartLoc2 );

			if ( Piece1.GetLength ()  == 0 )	{ Return.Append (CStringSurrogate (QString("NULL").unicode(), 0, 4 ) ); 	}
			else								{ Return.Append ( Piece1 ); 			}
			// yuhuask Could be ?					

			StartLoc1 = loc1  ;
			StartLoc2 = loc2  ;
			State = 2;
		}
		else 
		{
			while ( loc1 < m_Length1    &&   ! String1CharMatches (loc1) )
				  
			{
				loc1++;				
			}
			while ( loc2 < m_Length2    &&   !String2CharMatches (loc2) )				  
			{
				loc2++;				
			}

			// yuhuask Here, loc2 == match1[Loc1] or Loc2=m_Length2&&Loc1=m_Lenght1

			Return.Append(QChar('_'));
			
			StartLoc1 = loc1  ;
			StartLoc2 = loc2  ;
			State = 1;
		}

	}
	
	
	return Return;



}

double CAlignment::FindStringEditDistance()
{
	CStringEditGrid Grid (this);	
	return Grid.FindBestAlignment ( *this );


}

/// piece number of the piece that corresponds to piece n, or 0 if none
int CAlignment::Str2MatchForStr1Piece(int n)
{
	if (n < 1 || n > m_Str1->Size())
		return 0;

	int Str1Spot = m_Str1->GetPositionOfFirstCharOfThisPiece( n );
	int Str2Spot = m_Match1 [ Str1Spot ];

	if ( Str2Spot < 0 ) { return 0; }

	int Str2Piece = -1;
	for (int i = 1; i <= m_Str2->Size(); i++)
	{
		if ( m_Str2->GetPositionOfFirstCharOfThisPiece (i) == Str2Spot ) 
		{
			Str2Piece = i;
			break;
		}
	}
	if ( Str2Piece < 0 ) { return -1;}

	 

	return Str2Piece;
	
}

/// piece number of the piece that corresponds to piece n, or 0 if none
int CAlignment::Str1MatchForStr2Piece(int n)
{
	if (n < 1 || n > m_Str2->Size())
		return 0;

	int Str2Spot = m_Str2->GetPositionOfFirstCharOfThisPiece( n );
	int Str1Spot = m_Match2 [ Str2Spot ];

	if ( Str1Spot < 0 ) { return 0; }

	int Str1Piece = -1;
	for (int i = 1; i <= m_Str1->Size(); i++)
	{
		if ( m_Str1->GetPositionOfFirstCharOfThisPiece (i) == Str1Spot ) 
		{
			Str1Piece = i;
			break;
		}
	}
	if ( Str1Piece < 0 ) { return -1;}

	 
	return Str1Piece;
	


}
