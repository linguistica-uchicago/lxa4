// Implementation of CTemplate methods
// Copyright © 2009 The University of Chicago
#include "Template.h"

#include <QMessageBox>
#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "Lexicon.h"
#include "Alignment.h"
#include "TemplateCollection.h"
#include "WordCollection.h"
#include "generaldefinitions.h"
#include "Parse.h"
#include "log2.h"

extern double g_Lambda ;

CTemplate::CTemplate(int NumberOfColumns)
{
	m_NumberOfColumns = NumberOfColumns;
	m_Columns = new CParse*[ m_NumberOfColumns ];

	for (int i = 0; i < NumberOfColumns; i++)
	{
		m_Columns[i] = new CParse();
	}
	m_Complexity = 0;
	m_WordsTotalComplexity = 0;
	m_TemplateNumber = 0; 
	
	m_IsDeleted = false; 
	m_ModifiedColumn = -1; 
	m_IsNewAfterCollapse1 = false;
	m_StemColumnInCollapse1 =-1;
	m_SwitchOfSortingValue = false;


}
CTemplate::CTemplate(CTemplate& Template) : CStem ( Template.Display() )
{
	
	m_NumberOfColumns = Template.m_NumberOfColumns;
	m_Columns = new CParse* [ m_NumberOfColumns ];
	for (int i = 0; i < m_NumberOfColumns; i++)
	{

		m_Columns[i] = new CParse ( *Template.m_Columns[i]);
		Q_ASSERT ( m_Columns[i]->Size() > 0 );
	}

	m_WordsTotalComplexity = Template.GetWordsTotalComplexity();
	m_Complexity =  Template.GetComplexity();
	m_TemplateNumber = Template.m_TemplateNumber; 

	m_IsDeleted = Template.m_IsDeleted; 
	m_ModifiedColumn = Template.m_ModifiedColumn;
	m_IsNewAfterCollapse1 = Template.m_IsNewAfterCollapse1;
	m_StemColumnInCollapse1 = Template.m_StemColumnInCollapse1;
	m_SwitchOfSortingValue = Template.m_SwitchOfSortingValue;

 }

CTemplate::CTemplate(CAlignment* pAlign) : CStem ( pAlign->SpellOut() )
{
	
	int			loc1=0, loc2=0;  
	int			StartLoc1, StartLoc2;
	int			col = 0;

	if ( pAlign->m_Slips != 1 ) { return;  }
	
	QString			debugstring1, debugstring2; 
	const char*     CCDebugString1, *CCDebugString2;

	debugstring1 = pAlign ->m_Str1 ->GetKey().Display(); 
	CCDebugString1 = debugstring1.ascii();
	debugstring2 = pAlign ->m_Str2 ->GetKey().Display();
	CCDebugString2 = debugstring2.ascii();


	m_NumberOfColumns = pAlign->m_Spans;
	m_Columns = new CParse*[ m_NumberOfColumns ];

	for (int c = 0; c < m_NumberOfColumns; c++)
	{
		m_Columns[c] = new CParse();
	}
	
	
	// it always does this loop at least once, because of initial "#" which is shared
	while ( pAlign->PerfectMatch (loc1, loc2) )
	{
		loc1++;
		loc2++;
	}
 
	if ( loc1 > 1 )
	{		// there is an initial shared span...
		m_Columns[col]->Append( CStringSurrogate (pAlign->m_Str1->GetKeyPointer(),0 , loc1 ) );
		col++;
		StartLoc1 = loc1;
		StartLoc2 = loc2;
	}
	else // there is no initial shared span, and we'll back up to put the # in each piece
	{
		StartLoc1 = loc1 - 1;
		StartLoc2 = loc2 - 1;
	}
	 	
	
	
	while ( loc1 < pAlign->m_Length1    &&
			pAlign->m_Str2->GetChar( pAlign->m_Match1[loc1] ) != pAlign->m_Str1->GetChar( loc1 ) 			
		  )
	{
		loc1++;
	}

	while ( loc2 < pAlign->m_Length2 && 		 
		      pAlign->m_Str1->GetChar( pAlign->m_Match2[loc2] ) != pAlign->m_Str2->GetChar(loc2) )
	{
		loc2++;
	}

	
	CStringSurrogate Piece1 ( pAlign->m_Str1->GetKeyPointer(), StartLoc1 , loc1 - StartLoc1 );
	CStringSurrogate Piece2 ( pAlign->m_Str2->GetKeyPointer(), StartLoc2 , loc2 - StartLoc2 );
	
	
	if ( Piece1.GetLength ()  == 0 )
	{ 
//		m_Columns[col]->AppendInAlphabeticalOrder( CStringSurrogate(QString("NULL").unicode(), 0, 4));
        m_Columns[col]->Append(CStringSurrogate(QString("NULL").unicode(), 0, 4));
    }
	else 
	{	
		m_Columns[col]->Append(Piece1);
//		m_Columns[col]->AppendInAlphabeticalOrder( Piece1, true);
	}


	if ( Piece2.GetLength ()  == 0 )
	{ 	
//		m_Columns[col]->AppendInAlphabeticalOrder( CStringSurrogate(QString("NULL").unicode(), 0, 4), true );
		m_Columns[col]->Append(
			CStringSurrogate(QString("NULL").unicode(), 0, 4));
	}
	else 
	{
//		m_Columns[col]->AppendInAlphabeticalOrder( Piece2, true);		 
		m_Columns[col]->Append(Piece2);
	}

	// yuhuask when slip == 1 Only have three cases: yn or yny
	if ( col + 1 < m_NumberOfColumns )
	{
		col++;
//		m_Columns[col]->AppendInAlphabeticalOrder( CStringSurrogate (pAlign->m_Str1->GetKeyPointer(), loc1,pAlign->m_Str1->GetKeyLength() - loc1  ), true );
		m_Columns[col]->Append(CStringSurrogate (pAlign->m_Str1->GetKeyPointer(), loc1,pAlign->m_Str1->GetKeyLength() - loc1));
	}
	
	for (int i = 1; i < m_NumberOfColumns; i++)
	{
		Q_ASSERT(m_Columns[i]->Size() > 0 );
	}


	Q_ASSERT (m_Columns[0]->GetChar(0) == '#');
	m_TemplateNumber = 0; 

	
	m_ModifiedColumn = -1; 
	m_IsDeleted = false;
	m_IsNewAfterCollapse1 = false; 
	m_StemColumnInCollapse1 =-1;
	m_SwitchOfSortingValue = false;
	return ;

}


void CTemplate::operator= (CAlignment* pAlign)
{
	
	int			loc1= 0, loc2=0;  
	int			StartLoc1, StartLoc2;
	int			col = 0;

	if ( m_NumberOfColumns ) 
	{
		for (int i = 0; i < m_NumberOfColumns; i++)
		{
			if ( m_Columns[i] )  delete m_Columns[i];
		}
	}

	if ( pAlign->m_Slips != 1 ) { return;  }
	
	m_NumberOfColumns = pAlign->m_Spans;
		
	m_Columns = new CParse*[ m_NumberOfColumns  ];

	for (int c = 0; c < m_NumberOfColumns; c++)
	{
		m_Columns[c] = new CParse();
	}


	while ( pAlign->m_Str2->GetChar( loc2 ) == pAlign->m_Str1->GetChar( loc1 )    )
	{
		loc1++;
		loc2++;
	}
 
	if ( loc1 > 1 ) // they agree at the beginning, up to loc1 - 1;
	{
		m_Columns[col]->Append( CStringSurrogate (pAlign->m_Str1->GetKeyPointer(), 0, loc1) ); // yuhuask should be loc1 not loc1 -1
	}
 
 



	col++;
	StartLoc1 = loc1;
	StartLoc2 = loc2;

	while ( loc1 < pAlign->m_Length1 && 
			pAlign->m_Str2->GetChar( pAlign->m_Match1[loc1] ) != pAlign->m_Str1->GetChar( loc1 ) 
		  )
	{
		loc1++;
	}

	while ( loc2 < pAlign->m_Length2 &&
		    pAlign->m_Str1->GetChar( pAlign->m_Match2[loc2] ) != pAlign->m_Str2->GetChar( loc2 ) )
	{
		loc2++;
	}

	
	CStringSurrogate Piece1 ( pAlign->m_Str1->GetKeyPointer(), StartLoc1, loc1 - StartLoc1  ); // yuhuask same problem StartLoc1 - 1 ?
	CStringSurrogate Piece2 ( pAlign->m_Str2->GetKeyPointer(), StartLoc2, loc2 - StartLoc2  );
	


	if ( Piece1.GetLength ()  == 0 )
	{ 
		m_Columns[col]->Append( CStringSurrogate(QString("NULL").unicode(), 0, 4) );
	}
	else 
	{	
		m_Columns[col]->Append( Piece1);
	}


	if ( Piece2.GetLength ()  == 0 )
	{ 	
		m_Columns[col]->Append( CStringSurrogate(QString("NULL").unicode(), 0, 4) );
	}
	else 
	{
		m_Columns[col]->Append( Piece2);
	}

	col++;

	m_Columns[col]->Append( CStringSurrogate (pAlign->m_Str1->GetKeyPointer(), loc1, pAlign->m_Str1->GetKeyLength() - loc1 ) );

	m_TemplateNumber = 0; 

	return ;
	
}



CTemplate::~CTemplate(void)
{
	
	for (int i = 0; i < m_NumberOfColumns; i++)
	{
		delete m_Columns[i];
	}
	delete m_Columns;

}

//------------------------------------------------------

CParse* CTemplate::GetColumn(int n )
{

	Q_ASSERT ( n >= 0 );

	
	if ( n < m_NumberOfColumns  && n >= 0 )
	{
		return m_Columns[n];
	}
	return NULL;
	
 }

//------------------------------------------------------






QString CTemplate::Display()
{
	QString Return;
	
	for (int i = 0; i < m_NumberOfColumns; i++)
	{
		Return += m_Columns[i]->Display() + "_";
	}
	
	return Return;
}

/* From JG's original: 

void CTemplate::Display(CListCtrl& List, int& LineNumber)
{
	int  NumberOfRows = 0;
	for (int col = 0; col < m_NumberOfColumns; col++)
	{
		if (m_Columns[col]->Size() > NumberOfRows ) { NumberOfRows = m_Columns[col]->Size(); }
	}
	
	for (int row = 0; row < NumberOfRows+1; row++)
	{
		List.InsertItem (LineNumber + row, CString ("") );
	}
	
	List.SetItemText ( LineNumber, 0, IntToString( (int) GetSortingQuantity() ) );


 	

	for ( row = 0; row < NumberOfRows; row++)
	{	
		for (int col = 0; col < m_NumberOfColumns; col++)
		{
			if ( m_Columns[col]->Size() > row )
			{
				List.SetItemText(LineNumber+row, col + 1, m_Columns[col]->GetAtCString(row+1) );
			}
		}
	}

	LineNumber += row;


}

*/
/*
QString CTemplate::DisplayFirstLine()
{
	QString Return;
	
	for (int i = 0; i < m_NumberOfColumns; i++)
	{
		Return += m_Columns[i]->GetPiece(1).Display() + "_";
	}
	
	return Return;
}
*/
/*
void CTemplate::Display(CListCtrl& List, int& LineNumber)
{
	
	int  NumberOfRows = 0;
	for (int col = 0; col < m_NumberOfColumns; col++)
	{
		if (m_Columns[col]->Size() > NumberOfRows ) { NumberOfRows = m_Columns[col]->Size(); }
	}
	
	for (int row = 0; row < NumberOfRows+1; row++)
	{
		List.InsertItem (LineNumber + row, CString ("") );
	}

//	if ( GetSortingQuantity() > 15000 || GetSortingQuantity() < 0 ) 
//	{
//		ofstream out ("c:\\4_tests\\IntToString.txt", ios::app );
//		out << endl << endl; OutputForFile (out);
//		out << endl << GetSortingQuantity();
//		out << "  " << IntToString ( (int) GetSortingQuantity () );
//	}
	List.SetItemText ( LineNumber, 0, IntToString( (int) GetSortingQuantity() ) );

	for ( row = 0; row < NumberOfRows; row++)
	{	
		for (int col = 0; col < m_NumberOfColumns; col++)
		{
			if ( m_Columns[col]->Size() > row )
			{
				List.SetItemText(LineNumber+row, col + 1, m_Columns[col]->GetAtCString(row+1) );
			}
		}
	}

	LineNumber += row;


}
	*/

void CTemplate::ListDisplay(Q3ListView* List)
{
	GetSortingQuantity(); 
	static_cast<void>(new CTemplateListViewItem(List, this));
}

int	CTemplate::GetVerticalColumn()
{
	
	for (int i = 0; i < m_NumberOfColumns; i++)
	{
		if ( m_Columns[i]->Size() > 1 )  return i;
	}
	
	return -1;
}
void CTemplate::AddToColumn(CParse& Morphemes, int n)
{
	
	for (int i = 1; i <= Morphemes.Size(); i++)
	{
//		m_Columns[n]->AppendInAlphabeticalOrder ( Morphemes.GetPiece(i), true );
		m_Columns[n]->Append(Morphemes.GetPiece(i));
	}
	
}
void CTemplate::AddToColumn(CStringSurrogate& SS, int n)
{
//	m_Columns[n]->AppendInAlphabeticalOrder ( SS, true );		
	m_Columns[n]->Append(SS);
	
}




float CTemplate::GetSortingQuantity() const
{
	
	
	{ ComputeComplexity(); }
	
	{ ComputeWordsTotalComplexity(); }
	

	Q_ASSERT ( m_WordsTotalComplexity - m_Complexity < 55000);
	

	m_CurrentSortComplexity = m_WordsTotalComplexity - m_Complexity;
	
	// I set up a switch flag to indicate that we switch the sorting value
	if ( m_SwitchOfSortingValue )
	{
		int					NumberOfStems =0;
		int					i; 
		CParse*				OneColumn; 



		// Roughly get the number of stems
		for ( i = 0; i < m_NumberOfColumns; i++)
		{
			OneColumn = m_Columns[i];
			if ( OneColumn ->Size() > NumberOfStems)
			{
				NumberOfStems = OneColumn ->Size();
			}
		}


		m_NewSortComplexity = (m_WordsTotalComplexity - m_Complexity)/(float)NumberOfStems;
	}
	else
	{
		m_NewSortComplexity = m_WordsTotalComplexity - m_Complexity;
	}

	

	return float ( m_NewSortComplexity);
	//return float ( m_WordsTotalComplexity - m_Complexity );



}


/*
float CTemplate::GetSortingQuantity()
{
	
//	if ( m_Complexity <= 0 ) 
	{ ComputeComplexity(); }
	
//	if ( m_WordsTotalComplexity <= 0 ) 
	{ ComputeWordsTotalComplexity(); }
	
//	ofstream out ("c:\\4_tests\\TemplateDisplay.txt", ios::app );

	Q_ASSERT ( m_WordsTotalComplexity - m_Complexity < 55000);
	

//	if ( m_WordsTotalComplexity < 0 || m_WordsTotalComplexity > 15000)
//	{
//		OutputForFile(out);
//	}
//	if ( m_Complexity < 0 || m_Complexity > 15000)
//	{
//		OutputForFile(out);
//	}

	m_SortingComplexity = m_WordsTotalComplexity - m_Complexity;

	return float ( m_WordsTotalComplexity - m_Complexity );


}
*/

void CTemplate::AddAlignment(CAlignment* pAlignment)
{
	struct not_implemented { };
	throw not_implemented();
	static_cast<void>(pAlignment);

	//	m_Alignments.AddTail( pAlignment);
	// yuhuask ?
}

bool CTemplate::ShouldConflate ( CTemplate* pAlignment, int& ConflateColumn )
{

	/*	Works only with templates of 2 or 3 columns.
		If two alignments share a column, they are collapsed. */

	
	if ( m_NumberOfColumns  != pAlignment->m_NumberOfColumns ) { return FALSE; }
	if ( m_NumberOfColumns == 2 )
	{
		if (// m_Columns[0]->Size() > 1 && 
			*m_Columns[0] == pAlignment->m_Columns[0] )
		{			
			ConflateColumn = 1;
			return TRUE;
		}
		else if (//	m_Columns[1]->Size() > 1 &&
					*m_Columns[1] == pAlignment->m_Columns[1] )
		{			
			ConflateColumn = 0;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	} // end of Size = 2;
	else if ( m_NumberOfColumns == 3 )
	{
		if ( //m_Columns[0]->Size() > 1 && 
			*m_Columns[0] == pAlignment->m_Columns[0] &&
			//m_Columns[2]->Size() > 1 && 
			*m_Columns[2] == pAlignment->m_Columns[2] 
			)
		{			
			ConflateColumn = 1;
			return TRUE;
		}
		else if (//	m_Columns[1]->Size() > 1 &&
					*m_Columns[1] == pAlignment->m_Columns[1]  &&
				//	m_Columns[2]->Size() > 1 &&
					*m_Columns[2] == pAlignment->m_Columns[2] )
		{			
			ConflateColumn = 0;
			return TRUE;
		}
		else if (//	m_Columns[0]->Size() > 1 &&
					*m_Columns[0] == pAlignment->m_Columns[0]  &&
				//	m_Columns[1]->Size() > 1 &&
					*m_Columns[1] == pAlignment->m_Columns[1] )
		{			
			ConflateColumn = 2;
			return TRUE;
		}
		else
		{
			return FALSE;
		}

	} // end of Size = 3;
	
	return FALSE;


}

void CTemplate::ConflateWith ( CTemplate* pOther, int Column )
{
	CParse& their_column = *pOther->m_Columns[Column];
	CParse& my_column = *m_Columns[Column];

	for (int i = 1; i <= their_column.Size(); ++i)
		my_column.Append(their_column.GetPiece(i));
}

bool CTemplate::Readjust(CTemplateCollection* TempTemplates, int MinCount )
{
//	bool				AllSame = TRUE;
	bool				Return = FALSE;
	CWordCollection		Words;


	
	ComputeWordsTotalComplexity();

	int i;
	for (i = 1; i < m_NumberOfColumns; i++)
	{
		if ( (int) m_Columns[i]->Size() < MinCount ) 
		{ 
			continue; 
		}
			
		Words.RemoveAll();
		for (int w = 1; w <= (int) m_Columns[i]->Size(); w++)
		{
			Words << m_Columns[i]->GetPiece(w).Display();
		}
		CStringSurrogate ssPrefix = Words.FindMaximalMajorityPrefix();
		if ( ssPrefix.GetLength() == 0 ) { continue; }

		//------------------------------------------
		//		if we have some material that might potentially be
		//		moved leftward, let's calculate the complexity in that
		//		new situation.
		//
		//------------------------------------------


		CParse RightColumn				 = *m_Columns[ i ];
		CParse RightColumnOtherMorphemes = RightColumn;
		CParse LeftColumn				 = *m_Columns[i-1];

		RightColumn	 .RemovePiecesThatDoNotBegin ( ssPrefix );
		RightColumn  .RemovePrefixFromAllPieces  ( ssPrefix );
		RightColumnOtherMorphemes 
					 .RemovePiecesThatBegin( ssPrefix );
		
		LeftColumn	 .SuffixToAllPieces2          ( ssPrefix );
		
		double OldComplexity = m_Columns[i]->ComputeComplexity() +
							   m_Columns[i-1]->ComputeComplexity();
		double NewComplexity = RightColumn.ComputeComplexity() +
							   LeftColumn.ComputeComplexity();

		if (RightColumnOtherMorphemes.Size() > 0 )
		{
			NewComplexity += RightColumnOtherMorphemes.ComputeComplexity() +
							    m_Columns[i-1]->ComputeComplexity();
		}
		
		
		
		if ( NewComplexity < OldComplexity )
		{
			if ( RightColumnOtherMorphemes.Size() > 0 ) 
			{
				CTemplate TempTemplate ( *this );			
				*TempTemplate.GetColumn( i-1 ) = *m_Columns[ i-1 ];
				*TempTemplate.GetColumn( i   ) = RightColumnOtherMorphemes;
			
				TempTemplates->AddTemplate ( &TempTemplate);
			}
			
			*m_Columns[i]   = RightColumn;
			*m_Columns[i-1] = LeftColumn;
		}
	}
	

	
	CStringSurrogate		TempSS; 

	
	for ( i = 1; i < m_NumberOfColumns  ; i++) 
	{

		if ( (int) m_Columns[i]->Size() < MinCount ) 
		{ 
			continue; 
		}
			
		Words.RemoveAll();
		for (int w = 1; w <= (int) m_Columns[i-1]->Size(); w++)
		{
			TempSS = m_Columns[i-1]->GetPiece(w);
			TempSS.SetBackwards(); 
			Words << TempSS; 
		}
		TempSS =  Words.FindMaximalMajorityPrefix();
		TempSS.SetBackwards(); 
		CStringSurrogate ssSuffix ( TempSS  );

		if ( ssSuffix.GetLength() == 0 ) { continue; }

//------------------------------------------
//
//		if we have some material that might potentially be
//		moved rightward, let's calculate the complexity in that
//		new situation.
//
//------------------------------------------


		CParse RightColumn				 = *m_Columns[ i ];		
		CParse LeftColumn				 = *m_Columns[i-1];
		CParse LeftColumnOtherMorphemes  = LeftColumn;

		LeftColumn	 .RemovePiecesThatDoNotEnd  ( ssSuffix );
		LeftColumn   .RemoveSuffixFromAllPieces ( ssSuffix );
		LeftColumnOtherMorphemes 
					 .RemovePiecesThatEnd ( ssSuffix );
		
		RightColumn	 .PrefixToAllPieces2          ( ssSuffix );
		
		double OldComplexity = m_Columns[i]  ->ComputeComplexity() +
							   m_Columns[i-1]->ComputeComplexity();

		double NewComplexity = RightColumn.ComputeComplexity() +
							   LeftColumn.ComputeComplexity();

		if (LeftColumnOtherMorphemes.Size() > 0 )
		{
			NewComplexity += LeftColumnOtherMorphemes.ComputeComplexity() +
							    m_Columns[i]->ComputeComplexity();
		}
		

		
		if ( NewComplexity < OldComplexity )
		{
			if ( LeftColumnOtherMorphemes.Size() > 0 )
			{
				CTemplate TempTemplate ( *this );			
				*TempTemplate.GetColumn( i-1 ) = LeftColumnOtherMorphemes;			
				*TempTemplate.GetColumn( i ) = *m_Columns[ i ];

				TempTemplates->AddTemplate ( &TempTemplate);
			}
			
			*m_Columns[i]   = RightColumn;
			*m_Columns[i-1] = LeftColumn;
			
		}

		continue;
		
	
	}


	return Return;

}

/*
void CTemplate::OutputForFile(ofstream& out )
{
	int MaxSize = (int) m_Columns[0]->Size();
	CString Space = " ";
	for ( int i = 1; i < m_NumberOfColumns; i++)
	{
		if ( (int) m_Columns[i]->Size() > MaxSize )
		{
			MaxSize = m_Columns[i]->Size();	
		}
	}
	for (int row = 0; row < MaxSize; row++)
	{
		out << endl;
		for (int col = 0; col < m_NumberOfColumns; col++)
		{
			out << setw(20);
			if ( row < (int) m_Columns[col]->Size() ) 
			{
				out << m_Columns[col]->GetAt(row+1) << ' ';
			}
			else 
			{
				out << '-';
			}
		}
	}
	out << endl <<	endl <<  "Complexity: "<< endl;
	out << "From length: "<< base2log (m_NumberOfColumns) << endl;
	for (  i = 0; i < m_NumberOfColumns; i++)
	{
		out << i << " " <<  m_Columns[i]->ComputeComplexity() << endl;
	}
}

*/

int CTemplate::GetNumberOfLetters()
{

	int Total = 0;
	
	for (int i = 0; i < m_NumberOfColumns; i++)
	{
		Total += m_Columns[i]->GetKeyLength();
	}
	
	return Total;
}

float CTemplate::ComputeComplexity() const
{
	m_Complexity = 0;
	m_Complexity += float ( base2log (m_NumberOfColumns) + 
					g_Lambda * m_NumberOfColumns * (m_NumberOfColumns - 1 ) / 2 );
	Q_ASSERT (m_Complexity < 20 );
	for (int i = 0; i < m_NumberOfColumns; i++)
	{
		m_Complexity += (float) m_Columns[ i ]->ComputeComplexity();
		Q_ASSERT ( m_Complexity < 55000 );
	}
	Q_ASSERT ( m_Complexity > 0 );
	Q_ASSERT ( m_Complexity < 55000 );
	
 

	return m_Complexity;
}

float CTemplate::ComputeWordsTotalComplexity() const
{
	
	CParse		TempWords,
				NewWords;
	// first figure out the words:
	if (m_NumberOfColumns < 1) 
	{
		m_WordsTotalComplexity= 0;
		//out << " No columns." ;
		return m_WordsTotalComplexity;
	}

	CParse Words = *m_Columns[0];
	for (int col = 1; col < m_NumberOfColumns; col++)
	{
		NewWords.ClearParse();
		for (int row = 1; row <= (int) m_Columns[col]->Size(); row++)
		{
			TempWords = Words;
			CStringSurrogate ss = m_Columns[col]->GetPiece(row);
			if (ss == CStringSurrogate(QString("NULL").unicode(), 0, 4) )
			{
			//	TempWords = Words;
			} else
			{
				TempWords.SuffixToAllPieces2 ( m_Columns[col]->GetPiece(row) );
			}
			NewWords.Append (&TempWords);
		}
		Words = NewWords;
		
	}

	m_WordsTotalComplexity = (float) Words.ComputeComplexity();
 
	Q_ASSERT (m_WordsTotalComplexity < 50000 );

	return m_WordsTotalComplexity;

}



float CTemplate:: GetComplexity()
{ 
	if (m_Complexity <= 0)
	{
		ComputeComplexity();
	}
	return m_Complexity;
}
float CTemplate:: GetWordsTotalComplexity()
{ 
	if (m_WordsTotalComplexity <= 0)
	{
		ComputeWordsTotalComplexity();
	}
	return m_WordsTotalComplexity;
}



void		CTemplate::GetWordsAndParses(StringToParse& OneWordAndParse)
{
	int								CurrentSize ;
	int								Column;
	int								row; 
	StringToParse					TempWordsAndParses; 
	StringToParse					SwapWordsAndParses;
	StringToParse::Iterator			StringToParseIt; 
	QString							TheWord, OneWord, NewWord, DumpWord;
	CParse*							TheParse; 
	CParse*							NewParse;
	bool							IsPreNull;
	

	CurrentSize = (int) m_Columns[0]->Size();
	for ( row= 0; row<CurrentSize; row++)
	{
		TheWord = m_Columns[0]->GetPiece(row+1).Display();
		//Delete the "#"
		TheWord = TheWord.right((TheWord.length()-1));
		if ( TheWord.length() == 0)
		{
			TheWord = QString("NULL");
		}

		TheParse = new CParse(CStringSurrogate(TheWord)); 
		TempWordsAndParses.insert(TheWord,TheParse);  
	}
	
	
	for ( int i = 1; i < m_NumberOfColumns; i++)
	{
		Column = i; 
		
		CurrentSize = (int) m_Columns[Column]->Size();

		for ( StringToParseIt = TempWordsAndParses.begin();StringToParseIt != TempWordsAndParses.end(); StringToParseIt++)
		{
			TheWord = StringToParseIt.key();
			TheParse = StringToParseIt.data();

			// It only works for first col; 
			if (TheWord == QString("NULL"))
			{
				IsPreNull = true; 
			}
			else
			{
				IsPreNull = false; 
			}

			for ( row= 0; row<CurrentSize; row++)
			{
				OneWord = m_Columns[Column]->GetPiece(row+1).Display();
				

				if ( OneWord == QString("NULL"))
				{
					// Impossible We get "NULL" + "NULL"
					NewWord = TheWord;
					NewParse = new CParse(*TheParse);
				}
				else
				{
					if (! IsPreNull)
					{
						NewWord = TheWord + OneWord; 
						NewParse = new CParse(*TheParse);
						NewParse->Append(CStringSurrogate(OneWord));
					}
					else
					{
						NewWord = OneWord; 
						NewParse = new CParse();
						NewParse->Append(CStringSurrogate(OneWord));
					}
					
				}

				if (! SwapWordsAndParses.contains(NewWord))
				{
					SwapWordsAndParses.insert(NewWord,NewParse);  
				}
				else
				{
					QMessageBox::information( NULL, "debug","Impossible Here. Please Let Yu Hu Debug it!", "OK") ; 
				}
			}

			delete TheParse; 
			
		}

		TempWordsAndParses.clear(); 
		
		for ( StringToParseIt = SwapWordsAndParses.begin();StringToParseIt != SwapWordsAndParses.end(); StringToParseIt++)
		{
			TheWord = StringToParseIt.key();
			TheParse = StringToParseIt.data(); 

			TempWordsAndParses.insert(TheWord, TheParse); 
		}
		
		SwapWordsAndParses.clear(); 

	}

	
	
	for ( StringToParseIt = TempWordsAndParses.begin();StringToParseIt != TempWordsAndParses.end(); StringToParseIt++)
	{
		TheWord = StringToParseIt.key();
		TheParse =  StringToParseIt.data(); 
		OneWordAndParse.insert(TheWord, TheParse); 
	}
	

}




//////////////////

void	CTemplate::AdjustMeByMovingCommonTailOrHead2(StringToFloat& MorphemeAndItsComplexity, int MaximumSizeOfEachColumn, int MaximumNumberOfMovingLetters, bool PrintChangedTemplates,\
													int Loopi, bool ShouldUseStickNess, StringToStringToFloat& GlobalStickNess, \
													float TotalGlobalStickNess, float TotalWords)
{



	int					i, row;
	int					backletteri, headletteri; 
	QString				TheMorpheme;
	bool				PassColumnSizeTest = false;
	CParse*				LeftColumn, *RightColumn, *OneColumn; 
	bool				changed = false; 
	bool				NoFurther; 
	int					MoveWhichColumn;
	int					MoveL2RorR2L; // 0 --> left to right; 1 --> right to left
	int					MoveHowmanyLetters = 0; 
	float				OneMorphemeComplexity, AlternativeMorphemeComplexity;
	QString				CommonTail, CommonHead, MyTail, MyHead; 
	QString				Newmorpheme; 
	float				NewmorphemeComplexity, Diff, BestDiff, BestStickNessDiff; 
	float				StickNessDiff; 
	float				LeftColumnOldStickness, LeftColumnNewStickness;
	float				RightColumnOldStickness, RightColumnNewStickness;
	int					Tempi, Tempj;
	QString				TempMorphemei, TempMorphemej; 
	StringToFloat*		oneCollection; 
	float				oneFloat; 
	CParse				PossibleNewColumn; 
		

	
	//Through each column
	for ( i = 0; i < m_NumberOfColumns -1; i++)
	{
		
		if ( i == m_ModifiedColumn) 
		{
			continue;
		}

		LeftColumn = m_Columns[i];
		RightColumn = m_Columns[i+1];

		if (( LeftColumn ->Size() <= MaximumSizeOfEachColumn) && (RightColumn ->Size() <= MaximumSizeOfEachColumn))
		{
			PassColumnSizeTest = true; 
		}
		else
		{
			PassColumnSizeTest = false; 
			continue; 
		}
		

		LeftColumnOldStickness = 0; 
		LeftColumnNewStickness = 0; 
		RightColumnOldStickness = 0; 
		RightColumnNewStickness = 0; 

		if ( ShouldUseStickNess )
		{
	
			if ( LeftColumn ->Size() != 1)
			{
				
				for ( Tempi = 1; Tempi < LeftColumn ->Size(); Tempi++)
				{
					TempMorphemei = LeftColumn ->GetPiece(Tempi).Display();

					if ( i == 0)
					{
						TempMorphemei = TempMorphemei.right(TempMorphemei.length() -1);
						if  ( TempMorphemei.length() ==0)
						{
							TempMorphemei = QString("NULL"); 
						}
					
					}


					for ( Tempj = Tempi + 1; Tempj <= LeftColumn ->Size(); Tempj++)
					{
						TempMorphemej = LeftColumn ->GetPiece(Tempj).Display(); 
						
						if ( i == 0)
						{
							TempMorphemej = TempMorphemej.right(TempMorphemej.length() -1);
							if  ( TempMorphemej.length() ==0)
							{
								TempMorphemej = QString("NULL"); 
							}
						
						}

						
						if ( TempMorphemei > TempMorphemej )
						{
							oneCollection = GlobalStickNess[TempMorphemei];
							oneFloat = (*oneCollection)[TempMorphemej];
							LeftColumnOldStickness += oneFloat;
						}
						else
						{
							oneCollection = GlobalStickNess[TempMorphemej];
							oneFloat = (*oneCollection)[TempMorphemei];
							LeftColumnOldStickness += oneFloat;
						
						}

					}
				
				
				}
		
			}		
		

			if ( RightColumn ->Size() != 1)
			{
				
				for ( Tempi = 1; Tempi < RightColumn ->Size(); Tempi++)
				{
					TempMorphemei = RightColumn ->GetPiece(Tempi).Display(); 


					for ( Tempj = Tempi +1; Tempj <= RightColumn ->Size(); Tempj++)
					{
						TempMorphemej = RightColumn ->GetPiece(Tempj).Display(); 
						
						
						if ( TempMorphemei > TempMorphemej )
						{
							oneCollection = GlobalStickNess[TempMorphemei];
							oneFloat = (*oneCollection)[TempMorphemej];
							RightColumnOldStickness += oneFloat;
						}
						else
						{
							oneCollection = GlobalStickNess[TempMorphemej];
							oneFloat = (*oneCollection)[TempMorphemei];
							RightColumnOldStickness += oneFloat;
						
						}

					}
				
				
				}
		
			}	
		
		} // ShouldUseStickNess, then get the LeftColumnOldStickness, RightColumnOldStickness



		// Check LeftColumn
		
		backletteri = 1; 
		NoFurther = false; 

		while ( (backletteri <= MaximumNumberOfMovingLetters))
		{
					
			LeftColumnNewStickness = 0; 
			RightColumnNewStickness = 0; 

			// Need experiment on how to deal with "NULL" since "NULL" is too common
			if ( (static_cast <int> ( (LeftColumn ->Size() )) == 1) && (LeftColumn->GetPiece(1).Display().length()<=backletteri ))
			{
				NoFurther = true; 
				break; 
			}

			
			PossibleNewColumn.ClearParse(); 

			// Check whether all words have backletteri tailletter in common 
			for ( row =1; row <= LeftColumn ->Size(); row++)
			{
				TheMorpheme = LeftColumn->GetPiece(row).Display();


				if ( i == 0)
				{
					TheMorpheme = TheMorpheme.right(TheMorpheme.length() -1); 
					
					if ( TheMorpheme.length() ==0)
					{
						TheMorpheme = QString("NULL"); 
					}
				
				}
				
				if ( TheMorpheme == QString("NULL"))
				{
					NoFurther = true; 
					break; 
				}
				
				if ( static_cast <int> ( TheMorpheme.length() ) < backletteri)
				{
					NoFurther = true; 
					break; 
				}

				MyTail = TheMorpheme.right(backletteri);

				if ( row == 1)
				{
					CommonTail = MyTail;
					continue; 
				}

				if ( MyTail != CommonTail)
				{
					NoFurther = true; 
					break;
				}
			}

			if ( NoFurther)
			{
				break; 
			}

			// Now Calculate the Alternative Complexity
			Diff = 0.0; 

			for ( row =1; row <= LeftColumn ->Size(); row++)
			{
				TheMorpheme = LeftColumn->GetPiece(row).Display();
				
				if ( i == 0)
				{
					TheMorpheme = TheMorpheme.right(TheMorpheme.length() -1); 
					
					if ( TheMorpheme.length() ==0)
					{
						TheMorpheme = QString("NULL"); 
					}
				
				}

				if (!MorphemeAndItsComplexity.contains(TheMorpheme)) //, OneMorphemeComplexity))
				{
					QMessageBox::information(NULL, "Debug",  "Can't find this Morpheme", "OK");
					return; 
				}

				OneMorphemeComplexity = MorphemeAndItsComplexity[TheMorpheme];
				
				Newmorpheme = TheMorpheme.left(TheMorpheme.length() - backletteri); 

				if ( Newmorpheme.length() ==0)
				{
					Newmorpheme = QString("NULL"); 
				}
				
				// Populate the possible Column
				PossibleNewColumn.Append(Newmorpheme); 

				if (!MorphemeAndItsComplexity.contains(Newmorpheme))//, AlternativeMorphemeComplexity))
				{
					NewmorphemeComplexity = -base2log(1.0/TotalWords);  // Big Penalty		
				}
				else
				{
					AlternativeMorphemeComplexity = MorphemeAndItsComplexity[Newmorpheme];
					NewmorphemeComplexity = AlternativeMorphemeComplexity; 
				}

				Diff += NewmorphemeComplexity - OneMorphemeComplexity;
		
			}



			// Compute the possible Column Stickness
			if ( ShouldUseStickNess )
			{
				if ( PossibleNewColumn.Size() > 1)
				{
					
					for ( Tempi = 1; Tempi < PossibleNewColumn.Size(); Tempi++)
					{
						TempMorphemei = PossibleNewColumn.GetPiece(Tempi).Display(); 

						for ( Tempj = Tempi + 1; Tempj <= PossibleNewColumn.Size(); Tempj++)
						{
							TempMorphemej = PossibleNewColumn.GetPiece(Tempj).Display(); 
							
							if ( TempMorphemei > TempMorphemej )
							{
								if ( GlobalStickNess.contains(TempMorphemei))
								{
									oneCollection = GlobalStickNess[TempMorphemei];

									if ( oneCollection ->contains(TempMorphemej)) 
									{
										oneFloat = (*oneCollection)[TempMorphemej];
										LeftColumnNewStickness += oneFloat;
									}
									else
									{
										LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}
							}
							else
							{
								if ( GlobalStickNess.contains(TempMorphemej)) 
								{
									oneCollection = GlobalStickNess[TempMorphemej];
									if ( oneCollection ->contains(TempMorphemei))
									{
										oneFloat = (*oneCollection)[TempMorphemei];
										LeftColumnNewStickness += oneFloat;
									}
									else
									{
										LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}							
							}

						}
					
					
					}
			
				}
				else
				{
					LeftColumnNewStickness = 0.0;
				}
			}


			PossibleNewColumn.ClearParse(); 
			for ( row =1; row <= RightColumn ->Size(); row++)
			{
				TheMorpheme = RightColumn->GetPiece(row).Display();
				
				if (!MorphemeAndItsComplexity.contains(TheMorpheme))
				{
					QMessageBox::information (NULL, "Debug",  "Can't find this Morpheme", "OK");
					return; 
				}

				OneMorphemeComplexity = MorphemeAndItsComplexity[TheMorpheme];

				if ( TheMorpheme == QString("NULL"))
				{
					Newmorpheme = CommonTail;
				}
				else
				{
					Newmorpheme = CommonTail + TheMorpheme;
				}

				PossibleNewColumn.Append(Newmorpheme); 

				if (!MorphemeAndItsComplexity.contains(Newmorpheme)) //, ))
				{
					NewmorphemeComplexity = -base2log(1.0/TotalWords);  // Big Penalty		
				}
				else
				{
					AlternativeMorphemeComplexity = MorphemeAndItsComplexity[Newmorpheme];
					NewmorphemeComplexity = AlternativeMorphemeComplexity; 
				}

				Diff += NewmorphemeComplexity - OneMorphemeComplexity;
		
			}

			
			// Compute the possible Column Stickness
			if ( ShouldUseStickNess )
			{
				if ( PossibleNewColumn.Size() > 1)
				{
					
					for ( Tempi = 1; Tempi < PossibleNewColumn.Size(); Tempi++)
					{
						TempMorphemei = PossibleNewColumn.GetPiece(Tempi).Display(); 

						for ( Tempj = Tempi + 1; Tempj <= PossibleNewColumn.Size(); Tempj++)
						{
							TempMorphemej = PossibleNewColumn.GetPiece(Tempj).Display(); 
							
							if ( TempMorphemei > TempMorphemej )
							{
								if ( GlobalStickNess.contains(TempMorphemei)) 
								{
									oneCollection = GlobalStickNess[TempMorphemei];
									if ( oneCollection ->contains(TempMorphemej)) 
									{
										oneFloat = (*oneCollection)[TempMorphemej];
										RightColumnNewStickness += oneFloat;
									}
									else
									{
										RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}
							}
							else
							{
								if ( GlobalStickNess.contains(TempMorphemej)) 
								{
									oneCollection = GlobalStickNess[TempMorphemej];
									if ( oneCollection ->contains(TempMorphemei)) 
									{
										oneFloat = (*oneCollection)[TempMorphemei];
										RightColumnNewStickness += oneFloat;
									}
									else
									{
										RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}							
							}

						}
					
					
					}
			
				}
				else
				{
					RightColumnNewStickness = 0.0;
				}
			}
		



			// Check whether Diff > 0, if so records these changes

			if ( ShouldUseStickNess )
			{
				
				StickNessDiff = ( RightColumnNewStickness + LeftColumnNewStickness) - (RightColumnOldStickness + LeftColumnOldStickness)  ;

				Diff +=  StickNessDiff;

			}
			
			
			if (Diff < 0)
			{
				if (changed)
				{
					if ( Diff < BestDiff)
					{
						BestDiff = Diff;
						BestStickNessDiff = StickNessDiff;
						MoveWhichColumn = i;
						MoveL2RorR2L = 0;
						MoveHowmanyLetters = backletteri;
						// Always remember the left one column
						m_ModifiedColumn = i; 
					}
					
				}
				else
				{
					changed = true; 
					BestDiff = Diff; 
					MoveWhichColumn = i;
					MoveL2RorR2L = 0;
					MoveHowmanyLetters = backletteri;
					// Always remember the left one column
					m_ModifiedColumn = i; 
				}
			
			}
			
			backletteri++;
		}

	
		
		// Check RightColumn
		
		headletteri = 1; 
		NoFurther = false; 

		while ( (headletteri <= MaximumNumberOfMovingLetters))
		{
					
			LeftColumnNewStickness = 0; 
			RightColumnNewStickness = 0; 

			PossibleNewColumn.ClearParse(); 

			// Need experiment on how to deal with "NULL" since "NULL" is too common
			if ( (static_cast <int> ((RightColumn ->Size())) == 1) && (RightColumn->GetPiece(1).Display().length()<=headletteri ))
			{
				NoFurther = true; 
				break; 
			}

			// Check whether all words have headletteri headletter in common 
			for ( row =1; row <= RightColumn ->Size(); row++)
			{
				TheMorpheme = RightColumn->GetPiece(row).Display();
				
				if ( TheMorpheme == QString("NULL"))
				{
					NoFurther = true; 
					break; 
				}
				
				if ( static_cast <int> ( TheMorpheme.length() ) < headletteri)
				{
					NoFurther = true; 
					break; 
				}

				MyHead = TheMorpheme.left(headletteri);

				if ( row == 1)
				{
					CommonHead = MyHead;
					continue; 
				}

				if ( MyHead != CommonHead)
				{
					NoFurther = true; 
					break;
				}
			}

			if ( NoFurther)
			{
				break; 
			}

			// Now Calculate the Alternative Complexity
			Diff = 0.0; 

			for ( row =1; row <= RightColumn ->Size(); row++)
			{
				TheMorpheme = RightColumn->GetPiece(row).Display();
				
				if (!MorphemeAndItsComplexity.contains(TheMorpheme)) 
				{
					QMessageBox::information (NULL, "Debug",  "Can't find this Morpheme", "OK");
					return; 
				}


				OneMorphemeComplexity = MorphemeAndItsComplexity[TheMorpheme];
				Newmorpheme = TheMorpheme.right(TheMorpheme.length() - headletteri); 

				if ( Newmorpheme.length() ==0)
				{
					Newmorpheme = QString("NULL"); 
				}

				PossibleNewColumn.Append(Newmorpheme); 

				if (!MorphemeAndItsComplexity.contains(Newmorpheme)) 
				{
					NewmorphemeComplexity = -base2log(1.0/TotalWords);  // Big Penalty		
				}
				else
				{
					AlternativeMorphemeComplexity = MorphemeAndItsComplexity[Newmorpheme];
					NewmorphemeComplexity = AlternativeMorphemeComplexity; 
				}

				Diff += NewmorphemeComplexity - OneMorphemeComplexity;
		
			}

			// Compute the possible Column Stickness
			if ( ShouldUseStickNess )
			{
				if ( PossibleNewColumn.Size() > 1)
				{
					
					for ( Tempi = 1; Tempi < PossibleNewColumn.Size(); Tempi++)
					{
						TempMorphemei = PossibleNewColumn.GetPiece(Tempi).Display(); 

						for ( Tempj = Tempi + 1; Tempj <= PossibleNewColumn.Size(); Tempj++)
						{
							TempMorphemej = PossibleNewColumn.GetPiece(Tempj).Display(); 
							
							if ( TempMorphemei > TempMorphemej )
							{
								if ( GlobalStickNess.contains(TempMorphemei)) 
								{
									oneCollection = GlobalStickNess[TempMorphemei];
									if ( oneCollection ->contains(TempMorphemej)) 
									{
										oneFloat = (*oneCollection)[TempMorphemej];
										RightColumnNewStickness += oneFloat;
									}
									else
									{
										RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}
							}
							else
							{
								if ( GlobalStickNess.contains(TempMorphemej)) 
								{
									oneCollection = GlobalStickNess[TempMorphemej];
									if ( oneCollection ->contains(TempMorphemei)) 
									{
										oneFloat = (*oneCollection)[TempMorphemei];
										RightColumnNewStickness += oneFloat;
									}
									else
									{
										RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									RightColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}							
							}

						}
					
					
					}
			
				}
				else
				{
					RightColumnNewStickness = 0.0;
				}
			}

			PossibleNewColumn.ClearParse(); 	
			for ( row =1; row <= LeftColumn ->Size(); row++)
			{
				TheMorpheme = LeftColumn->GetPiece(row).Display();

				if ( i == 0)
				{
					TheMorpheme = TheMorpheme.right(TheMorpheme.length() -1);
					if ( TheMorpheme.length() ==0)
					{
						TheMorpheme = QString("NULL"); 	
					}
				
				}
				
				if (!MorphemeAndItsComplexity.contains(TheMorpheme)) 
				{
					QMessageBox::information (NULL, "Debug",  "Can't find this Morpheme", "OK");
					return; 
				}


				OneMorphemeComplexity = MorphemeAndItsComplexity[TheMorpheme];

				if ( TheMorpheme == QString("NULL"))
				{
					Newmorpheme = CommonHead;
				}
				else
				{
					Newmorpheme = TheMorpheme + CommonHead;
				}
				
				PossibleNewColumn.Append(Newmorpheme); 

				if (!MorphemeAndItsComplexity.contains(Newmorpheme)) 
				{
					NewmorphemeComplexity = -base2log(1.0/TotalWords);  // Big Penalty	
				}
				else
				{
					AlternativeMorphemeComplexity = MorphemeAndItsComplexity[Newmorpheme];
					NewmorphemeComplexity = AlternativeMorphemeComplexity; 
				}

				Diff += NewmorphemeComplexity - OneMorphemeComplexity;
		
			}
		
			// Compute the possible Column Stickness
			if ( ShouldUseStickNess )
			{
				if ( PossibleNewColumn.Size() > 1)
				{
					
					for ( Tempi = 1; Tempi < PossibleNewColumn.Size(); Tempi++)
					{
						TempMorphemei = PossibleNewColumn.GetPiece(Tempi).Display(); 

						for ( Tempj = Tempi + 1; Tempj <= PossibleNewColumn.Size(); Tempj++)
						{
							TempMorphemej = PossibleNewColumn.GetPiece(Tempj).Display(); 
							
							if ( TempMorphemei > TempMorphemej )
							{
								if ( GlobalStickNess.contains(TempMorphemei)) 
								{
									oneCollection = GlobalStickNess[TempMorphemei];
									if ( oneCollection ->contains(TempMorphemej)) 
									{
										oneFloat = (*oneCollection)[TempMorphemej];
										LeftColumnNewStickness += oneFloat;
									}
									else
									{
										LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}
							}
							else
							{
								if ( GlobalStickNess.contains(TempMorphemej))
								{
									oneCollection = GlobalStickNess[TempMorphemej];
									if ( oneCollection ->contains(TempMorphemei)) 
									{
										oneFloat = (*oneCollection)[TempMorphemei];
										LeftColumnNewStickness += oneFloat;
									}
									else
									{
										LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

									}
									
								}
								else
								{
									LeftColumnNewStickness += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
								}							
							}

						}
					
					
					}
			
				}
				else
				{
					LeftColumnNewStickness = 0.0;
				}
			}


			// Check whether Diff > 0, if so records these changes

			if ( ShouldUseStickNess )
			{

				StickNessDiff = ( RightColumnNewStickness + LeftColumnNewStickness) -  (RightColumnOldStickness + LeftColumnOldStickness)  ;

				Diff +=  StickNessDiff;

			}

			if (Diff  < 0)
			{
				if (changed)
				{
					if ( Diff < BestDiff)
					{
						BestDiff = Diff;
						BestStickNessDiff = StickNessDiff;
						MoveWhichColumn = i+1;
						MoveL2RorR2L = 1;
						MoveHowmanyLetters = headletteri;
						
						// Always remember the left one column
						m_ModifiedColumn = i; 
					}
					
				}
				else
				{
					changed = true; 
					BestDiff = Diff; 
					MoveWhichColumn = i+1;
					MoveL2RorR2L = 1;
					MoveHowmanyLetters = headletteri;
					
					// Always remember the left one column
					m_ModifiedColumn = i; 
				}
			
			}
			
			headletteri++;
		}
	}


	
	// Now, we can know whether we adjust this template
		
	
//	int					MaximumOutputMorphemeInOneColumn = 8; 
	QString				DisplayOfOneColumn; 


	if ( changed )
	{
		// Print Original Templates
		if (PrintChangedTemplates)
		{

			QFile file( "AdjustedTemplates.txt" );
    
			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );

			//outf.open ("AdjustedTemplates.txt", ofstream::out | ofstream::app);
				
			outf << "***********"<<Loopi<<"************" <<endl;
			outf << "	Original Template:" << endl; 
			outf << "		";

			for ( i = 0; i < m_NumberOfColumns; i++)
			{
				OneColumn = m_Columns[i];
				
				DisplayOfOneColumn = QString("{ "); 
				for (int j =  1; j <= OneColumn ->Size();j++)
				{
					DisplayOfOneColumn += OneColumn ->GetPiece(j).Display();
					if ( j != OneColumn ->Size())
					{
						DisplayOfOneColumn += QString(" , ");
					}
				}

				DisplayOfOneColumn += QString(" }");
				outf << DisplayOfOneColumn;
				if ( i != m_NumberOfColumns -1)
				{
					outf << " --> "; 
				}
			}

			outf << endl; 

			file.close();
			//outf.close();  
		}


		// Modify this tempalte based on former bestdiff record
		CParse					TempParse; 
		QString					MovedSubString; 
		CStringSurrogate		TempCSS; 
		
		if ( MoveL2RorR2L == 0)
		{
			// when letters are moved from left to right
			LeftColumn = m_Columns[MoveWhichColumn];
			RightColumn = m_Columns[MoveWhichColumn+1]; 
			MovedSubString = LeftColumn ->GetPiece(1).Display().right(MoveHowmanyLetters);
			
			// Modify left column
			TempParse.ClearParse(); 
			for ( row =1; row <= LeftColumn ->Size(); row++)
			{
				TheMorpheme = LeftColumn->GetPiece(row).Display();
				
				
				if ( MoveWhichColumn ==0)
				{
					TheMorpheme = TheMorpheme.right(TheMorpheme.length() -1);
					
					if ( TheMorpheme.length() ==0)
					{
						QMessageBox::information (NULL, "Debug", "Impossible Here!", "OK");
						TheMorpheme = QString("NULL"); 
					}
				
				}
				
  
				Newmorpheme = TheMorpheme.left(TheMorpheme.length() - MoveHowmanyLetters); 
				
				if ( Newmorpheme.length() ==0)
				{
					Newmorpheme = QString("NULL"); 
				}				
		

				TempCSS = CStringSurrogate(Newmorpheme);
				if ( !TempParse.Contains(TempCSS))
				{
					TempParse.Append(Newmorpheme); 
				}

			}

			if ( TempParse.Size() ==0)
			{
				QMessageBox::information(NULL, "Debug",  "TempParse Size should not be 0", "OK"); 
				return; 
			}

			// If this is the first column, we put "#" back
			if ( MoveWhichColumn ==0)
			{
				CParse					SwapParse;
				int						Swapi; 
				QString					Swappiece; 

				for ( Swapi  = 1; Swapi <= TempParse.Size(); Swapi++)
				{
					Swappiece = TempParse.GetPiece(Swapi).Display(); 
					
					if ( Swappiece == QString("NULL"))
					{
						Swappiece = QString("#"); 
					}
					else
					{
						Swappiece = QString("#") + Swappiece; 
					}

					SwapParse.Append(Swappiece); 
				}

				TempParse = SwapParse ;
			}

			(*LeftColumn) = TempParse;

	
			// Modify right column
			TempParse.ClearParse(); 
			for ( row =1; row <= RightColumn ->Size(); row++)
			{
				TheMorpheme = RightColumn->GetPiece(row).Display();
				
				if ( TheMorpheme == QString("NULL"))
				{
					Newmorpheme = MovedSubString; 
				}
				else
				{
					Newmorpheme = MovedSubString + TheMorpheme; 
				}

				TempCSS = CStringSurrogate(Newmorpheme);
				if ( !TempParse.Contains(TempCSS))
				{
					TempParse.Append(Newmorpheme); 
				}


			}

			if ( TempParse.Size() ==0)
			{
				QMessageBox::information(NULL, "Debug",  "TempParse Size should not be 0", "OK"); 
				return; 
			}

			(*RightColumn) = TempParse;

		}
		else
		{	
			// when letters are moved from right to left
			LeftColumn = m_Columns[MoveWhichColumn-1];
			RightColumn = m_Columns[MoveWhichColumn]; 
			MovedSubString = RightColumn ->GetPiece(1).Display().left(MoveHowmanyLetters);
			
			// Modify right column
			TempParse.ClearParse(); 
			for ( row =1; row <= RightColumn ->Size(); row++)
			{
				TheMorpheme = RightColumn->GetPiece(row).Display();
				Newmorpheme = TheMorpheme.right(TheMorpheme.length() - MoveHowmanyLetters); 
				if ( Newmorpheme.length() ==0)
				{
					Newmorpheme = QString("NULL"); 
				}				

				TempCSS = CStringSurrogate(Newmorpheme);
				if ( !TempParse.Contains(TempCSS))
				{
					TempParse.Append(Newmorpheme); 
				}
				
			}

			if ( TempParse.Size() ==0)
			{
				QMessageBox::information(NULL, "Debug",  "TempParse Size should not be 0", "OK"); 
				return; 
			}

			(*RightColumn) = TempParse;

	
			// Modify left column
			TempParse.ClearParse(); 
			for ( row =1; row <= LeftColumn ->Size(); row++)
			{
				TheMorpheme = LeftColumn->GetPiece(row).Display();
				
				if ( MoveWhichColumn == 1)
				{
					TheMorpheme = TheMorpheme.right(TheMorpheme.length() -1);
					if ( TheMorpheme.length() ==0)
					{
						TheMorpheme = QString("NULL"); 
					}
				
				}

				if ( TheMorpheme == QString("NULL"))
				{
					Newmorpheme = MovedSubString; 
				}
				else
				{
					Newmorpheme = TheMorpheme + MovedSubString; 
				}

				TempCSS = CStringSurrogate(Newmorpheme);
				if ( !TempParse.Contains(TempCSS))
				{
					TempParse.Append(Newmorpheme); 
				}

			}

			if ( TempParse.Size() ==0)
			{
				QMessageBox::information(NULL, "Debug",  "TempParse Size should not be 0", "OK"); 
				return; 
			}

			// If this is the first column, we put "#" back
			if ( MoveWhichColumn == 1)
			{
				CParse					SwapParse;
				int						Swapi; 
				QString					Swappiece; 

				for ( Swapi  = 1; Swapi <= TempParse.Size(); Swapi++)
				{
					Swappiece = TempParse.GetPiece(Swapi).Display(); 
					
					if ( Swappiece == QString("NULL"))
					{
						Swappiece = QString("#"); 
					}
					else
					{
						Swappiece = QString("#") + Swappiece; 
					}

					SwapParse.Append(Swappiece); 
				}

				TempParse = SwapParse ;
			}

			(*LeftColumn) = TempParse;

		}


		// Check through this template, delete those column, which only has "NULL" or "#"
		int				Newi; 
		bool			DeleteFirstColumn; 


		DeleteFirstColumn = false; 
		Newi = 0; 
		for ( i = 0; i < m_NumberOfColumns; i++)
		{
			OneColumn = m_Columns[i];

			if (( OneColumn ->Size() ==1 )&&(OneColumn ->GetPiece(1).Display() == QString("#")))
			{
				DeleteFirstColumn = true; 
				continue; 
			}

			if ( ( OneColumn ->Size() ==1 )&&(OneColumn ->GetPiece(1).Display() == QString("NULL")))
			{
				continue; 
			}

			if ( DeleteFirstColumn && (Newi == 0))
			{
				CParse					SwapParse;
				int						Swapi; 
				QString					Swappiece; 

				for ( Swapi  = 1; Swapi <= OneColumn ->Size(); Swapi++)
				{
					Swappiece = OneColumn ->GetPiece(Swapi).Display(); 
					
					if ( Swappiece == QString("NULL"))
					{
						Swappiece = QString("#"); 
					}
					else
					{
						Swappiece = QString("#") + Swappiece; 
					}

					SwapParse.Append(Swappiece); 
				}

				(*OneColumn) = SwapParse ;
			}


			m_Columns[Newi] = OneColumn;
			Newi++; 
		}

		m_NumberOfColumns = Newi; 


		// Print Result Templates
		if (PrintChangedTemplates)
		{
			QFile file( "AdjustedTemplates.txt" );
    
			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );

			//outf.open ("AdjustedTemplates.txt", ofstream::out | ofstream::app);

			outf << "	Adjusted Template:" << endl; 
			outf << "		";

			for ( i = 0; i < m_NumberOfColumns; i++)
			{
				OneColumn = m_Columns[i];
				
				DisplayOfOneColumn = QString("{ "); 
				for (int j =  1; j <= OneColumn ->Size(); j++)
				{
					DisplayOfOneColumn += OneColumn ->GetPiece(j).Display();
					if ( j != OneColumn ->Size())
					{
						DisplayOfOneColumn += QString(" , ");
					}
				}

				DisplayOfOneColumn += QString(" }");
				outf << DisplayOfOneColumn;
				if ( i != m_NumberOfColumns -1)
				{
					outf << " --> "; 
				}
			}

			outf << endl; 
			
			outf << "The Diff in Pointer is " << BestDiff << ", The StickNess Diff is " << BestStickNessDiff <<"."; 
			
			outf << endl; 
			outf << endl; 
			outf << endl; 

			file.close(); 
		
		}

		
	}
	else
	{
		QFile file( "AdjustedTemplates.txt" );
    
		if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
		{
			QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
			return;    
		}

		Q3TextStream outf( &file );

		outf<< "No Change for this template !" <<endl; 

		file.close();

	
	}

}

namespace {
	QString omit_first_letter(const QString& morpheme)
	{
		Q_ASSERT(morpheme != TheStringNULL);
		Q_ASSERT(morpheme.size() >= 1);

		if (morpheme.size() == 1)
			return TheStringNULL;
		else
			return morpheme.mid(1);
	}
}

void CTemplate::AdjustMeAfterAbsorb1(QMap<QString, int>& AbsorbedWords,
	bool Conservative, int MiniMumPrefixOrSuffixNeedToBeAbsorbed, int Loopi)
{
	const bool OpenPrint = true;

	int StemSize = 0;
	int StemColumn = -1;
	for (int i = 0; i < m_NumberOfColumns; ++i) {
		CParse& column = *m_Columns[i];

		if (column.Size() > StemSize) {
			StemSize = column.Size();
			StemColumn = i; 
		}
	}

	Q_ASSERT(StemSize >= 0);
	Q_ASSERT(StemColumn >= 0 && StemColumn < m_NumberOfColumns);
	Q_ASSERT(m_NumberOfColumns == 2 || m_NumberOfColumns == 3);

	// We don't consider the case where Stem is in middle
	if (m_NumberOfColumns == 3 && StemColumn == 1)
		return;

	Q_ASSERT(StemColumn == 0 || StemColumn == 1 || StemColumn == 2);

	if (StemColumn == 1)
		// Already returned if number of columns == 3.
		Q_ASSERT(m_NumberOfColumns == 2);

	if (StemColumn == 2)
		// it only can be 3-column
		Q_ASSERT(m_NumberOfColumns == 3);

	// values are all 1.  XXX. use std::set.
	QMap<QString, int> affix_set;

	if (m_NumberOfColumns == 3) {
		Q_ASSERT(StemColumn == 0);
		GetWordsFromTwoColums(affix_set, 1);
	} else {
		Q_ASSERT(m_NumberOfColumns == 2);

		CParse& column = *m_Columns[1 - StemColumn];
		for (int row = 1; row <= column.Size(); ++row) {
			QString affix = column.GetPiece(row).Display();
			if (StemColumn == 1)
				affix = omit_first_letter(affix);

			affix_set[affix] = 1;
		}
	}

	// With these affixes, check the stem column
	CParse& column = *m_Columns[StemColumn];
	CParse TempParse;
	QMap<QString, int> AbsorbedStems;
	int AbsorbedStemSize = 0;
	for (int row = 1; row <= column.Size(); ++row) {
		QString stem = column.GetPiece(row).Display();
		if (StemColumn == 0)
			stem = omit_first_letter(stem);

		int FitHowManyPrefixOrSuffix = 0;
		for (QMap<QString, int>::const_iterator iter =
					affix_set.constBegin();
				iter != affix_set.constEnd();
				++iter) {
			QString affix = iter.key();
			Q_ASSERT(iter.value() == 1);

			QString MakeUpWord;
			if (stem != TheStringNULL)
				MakeUpWord.append(stem);

			if (affix != TheStringNULL) {
				if (StemColumn == 0) {
					MakeUpWord.append(affix);
				} else {
					Q_ASSERT(StemColumn ==
							m_NumberOfColumns - 1);
					MakeUpWord.prepend(affix);
				}
			}

			if (AbsorbedWords.contains(MakeUpWord))
				++FitHowManyPrefixOrSuffix;
		}

		int CheckLimit = affix_set.size();
		if (Conservative == 0)
			CheckLimit = std::min(CheckLimit,
				MiniMumPrefixOrSuffixNeedToBeAbsorbed);

		if (FitHowManyPrefixOrSuffix < CheckLimit) {
			TempParse.Append(CStringSurrogate(stem));
		} else {
			++AbsorbedStemSize;
			AbsorbedStems[stem] = 1;
		}
	}

	if (AbsorbedStemSize == StemSize)
		m_IsDeleted = true;
	else if (AbsorbedStemSize > 0)
		std::swap(*(m_Columns[StemColumn]), TempParse);
	else
		return;

	if (!OpenPrint)
		return;

	QFile file("Absorb1.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QMessageBox::information(0, "Error",
			"Can't Open the file!", "OK");
		return;
	}
	QTextStream outf(&file);

	outf << "*************" << Loopi << "**************" << endl;
	if (AbsorbedStemSize == StemSize) {
		outf << "\tDelete This Template:" << endl;
	} else {
		Q_ASSERT(AbsorbedStemSize > 0);
		// Took some stems away from one template
		outf << "\tAbsorb Some Stems From This Template:" <<
				endl;
	}
	outf << "\t\t";

	for (int i = 0; i < m_NumberOfColumns; ++i) {
		CParse& column = i != StemColumn
			? *m_Columns[i]
			: TempParse;	// old *m_Columns[i]
		
		outf << "{ ";
		for (int j = 1; j <= column.Size(); ++j) {
			outf << column.GetPiece(j).Display();
			if (j == column.Size())
				break;
			outf << " , ";
		}
		outf << " }";

		if (i == m_NumberOfColumns - 1)
			break;
		outf << " --> ";
	}
	outf << endl;

	if (AbsorbedStemSize != StemSize) {
		Q_ASSERT(AbsorbedStemSize > 0);
		outf << "Absorbed Stems: ";

		outf << "{ ";
		if (!AbsorbedStems.isEmpty()) {
			QMap<QString, int>::const_iterator iter =
				AbsorbedStems.constBegin();

			outf << iter.key();	// first stem
			Q_ASSERT(iter.value() == 1);

			for (++iter; iter != AbsorbedStems.constEnd();
					++iter) {
				outf << " , " << iter.key();
				Q_ASSERT(iter.value() == 1);
			}
		}
		outf << " }" << endl;
	}
	outf << endl;
}

void		CTemplate::GetWordsFromTwoColums(StringToInt& AllPrefixes, int StartColumn)
{
	
	int									CurrentSize ;
	int									Column;
	int									row; 
	QString								TheWord, OneWord, NewWord, DumpWord;
	StringToInt::iterator				StringToIntIt;
	bool								IsPreNull;
	StringToInt							TempWords; 


	if ( GetNumberOfColumns() < StartColumn +2)
	{
		QMessageBox::information(NULL, "Error",  "Impossible Here So far. Please Let Yu Hu Debug it!", "OK") ; 
		return; 
	}


	AllPrefixes.clear(); 
	
	CurrentSize = (int) m_Columns[StartColumn]->Size();
	for ( row= 0; row<CurrentSize; row++)
	{
		TheWord = m_Columns[StartColumn]->GetPiece(row+1).Display();
		
		if ( StartColumn == 0)
		{
			TheWord = TheWord.right((TheWord.length()-1));
			if ( TheWord.length() ==0)
			{
				TheWord = QString("NULL");
			}
		}

		TempWords.insert(TheWord,1);  
	}
	
	
	Column = StartColumn + 1; 
		
	CurrentSize = (int) m_Columns[Column]->Size();

	for ( StringToIntIt = TempWords.begin(); StringToIntIt != TempWords.end(); StringToIntIt++)
	{
		TheWord = StringToIntIt.key();
		
		// It only works for first col; 
		if (TheWord == QString("NULL"))
		{
			IsPreNull = true; 
		}
		else
		{
			IsPreNull = false; 
		}

		for ( row= 0; row<CurrentSize; row++)
		{
			OneWord = m_Columns[Column]->GetPiece(row+1).Display();	

			if ( OneWord == QString("NULL"))
			{
				// possible We get "NULL" + "NULL"
				NewWord = TheWord;
			}
			else
			{
				if (! IsPreNull)
				{
					NewWord = TheWord + OneWord; 
				}
				else
				{
					NewWord = OneWord; 
				}
				
			}

			if (! AllPrefixes.contains(NewWord)) 
			{
				AllPrefixes.insert(NewWord,1);  
			}
			else
			{
				QMessageBox::information(NULL, "Error" ,"Impossible Here. Please Let Yu Hu Debug it!", "OK") ; 
			}
		}

	}


}





void	CTemplate::FindMorphemePrefixOrSuffixWithParadigmaticGraph(int Loopi, int MaximumSizeOfStemColumn, StringToFloat& GlobalNodeStickNess2, StringToStringToFloat& TotalGlobalStickNess2, float GlobalStickNess2, float TotalWord2)
{
	
	CParse*					oneColumn; 
	int						i, itemi, itemj;  
	QString					Morphemei, Morphemej; 
	bool					IsMePrefixOfOthers, IsMeSuffixOfOthers; 
	QString					ThePrefixOrSuffix;
	bool					FoundAndModified;
	bool					HasEverChanged; 
	CTemplate*				BackUpTemplate; 	
	CStringSurrogate		TempCSS, TempCSS1;
	CStringSurrogate		NULLCSS;


	NULLCSS = CStringSurrogate(QString("NULL"));
	

	
	BackUpTemplate = new CTemplate(*this);

	
	HasEverChanged = false; 
	FoundAndModified = true;
	
	while( FoundAndModified )
	{

		FoundAndModified = false; 
		for ( i = 0; i < m_NumberOfColumns; i++)
		{
			oneColumn = m_Columns[i];
			
			if ( oneColumn ->Size() > MaximumSizeOfStemColumn)
			{
				continue; 
			}

			if ( oneColumn ->Size() == 1)
			{
				continue; 
			}


			for ( itemi = 1; itemi <= oneColumn ->Size(); itemi++)
			{
			
				Morphemei = oneColumn ->GetPiece(itemi).Display();
				
				if ( i ==0)
				{
					Morphemei = Morphemei.right(Morphemei.length() -1);
					if ( Morphemei.length() ==0)
					{
						Morphemei = QString("NULL"); 
						continue; 
						// NULL could not be any prefix or suffix of other morphemes
					}

				}

				if ( Morphemei == QString("NULL"))
				{
					continue; 
					// NULL could not be any prefix or suffix of other morphemes				
				}
				
				if ( Morphemei.length() <= 1)
				{
					continue;
					// too short morpheme is suspicious for prefix and suffix of others
				}

				ThePrefixOrSuffix = Morphemei; // Morphemei could be others' prefix or suffix
		
				// Check through the other morpheme to see whether this morphemei could be prefix
				IsMePrefixOfOthers = false; 
				for ( itemj= 1; itemj <= oneColumn ->Size(); itemj++)
				{
					Morphemej = oneColumn ->GetPiece(itemj).Display(); 

					if ( i ==0)
					{
						Morphemej = Morphemej.right(Morphemej.length() -1);
						if ( Morphemej.length() ==0)
						{
							Morphemej = QString("NULL"); 
						}

						continue; 
					}

					
					if ( Morphemej.length() <= Morphemei.length())
					{
						continue; 
					}

					if ( Morphemej.left(Morphemei.length()) != Morphemei)
					{
						continue; 
					}

					IsMePrefixOfOthers = true; 
					break; 
				}

				// If found morphemei is prefix of at least one other morpheme
				if ( IsMePrefixOfOthers)
				{
					CParse				OriginalColumn, NewColumnOne, NewColumnTwo;
					CParse*				ReplaceFirstColumn;
					int					Originali; 
					QString				oneOriginalMoprheme, oneNewMorpheme; 
					float				OlderRobustNess, NewRobustNess; 
					float				RobustNessDiff; 
					int					Replacei; 
					CParse**			TempColumns; 
					CParse*				ReplaceOneColumn; 
					QString				Swappiece;
					CParse				SwapParse; 
					
					// Try to get the NewColumnOne and NewColumnTwo
					for ( Originali = 1; Originali<= oneColumn ->Size(); Originali++)
					{
						oneOriginalMoprheme = oneColumn ->GetPiece(Originali).Display();
						
						if ( i ==0)
						{
							oneOriginalMoprheme = oneOriginalMoprheme.right(oneOriginalMoprheme.length() -1);

							if ( oneOriginalMoprheme.length() ==0)
							{
								oneOriginalMoprheme = QString("NULL"); 	
							}
						}


						TempCSS = CStringSurrogate(oneOriginalMoprheme);
						OriginalColumn.Append(TempCSS); 

						if ( oneOriginalMoprheme == QString("NULL"))
						{

							NewColumnOne.Append(TempCSS); 
							continue; 
						}

						if ( oneOriginalMoprheme.length() <= ThePrefixOrSuffix.length())
						{
							NewColumnOne.Append(TempCSS); 
							continue;
						}

						if ( oneOriginalMoprheme.left(ThePrefixOrSuffix.length()) != ThePrefixOrSuffix)
						{
							NewColumnOne.Append(TempCSS); 
							continue;
						}

						if (oneOriginalMoprheme.left(ThePrefixOrSuffix.length()) == ThePrefixOrSuffix)
						{
							oneNewMorpheme = oneOriginalMoprheme.right(oneOriginalMoprheme.length() - ThePrefixOrSuffix.length());
							
							TempCSS1 = CStringSurrogate(oneNewMorpheme);

							NewColumnTwo.Append(TempCSS1); 
						}
					}


					NewColumnTwo.Append(NULLCSS); 

					// Get Original Robustness     
					OlderRobustNess = GetRobustNessWithParadigmaticGraph(OriginalColumn, GlobalNodeStickNess2, TotalGlobalStickNess2, GlobalStickNess2, TotalWord2); 

					// Calculate the alternative robustness  to do 
					NewRobustNess = GetRobustNessWithParadigmaticGraph(NewColumnOne, GlobalNodeStickNess2, TotalGlobalStickNess2, GlobalStickNess2, TotalWord2); 			
					NewRobustNess += GetRobustNessWithParadigmaticGraph(NewColumnTwo, GlobalNodeStickNess2, TotalGlobalStickNess2, GlobalStickNess2, TotalWord2); 			

					// If Diff satisfy the condition, we make the modification, then break; 
					RobustNessDiff = NewRobustNess - OlderRobustNess;
					
					if (1) // RobustNessDiff < 0)  
					{
					
						// Change the template by replacing the two columns for the original one
						TempColumns = new CParse*[ m_NumberOfColumns + 1];

						for ( Replacei = m_NumberOfColumns -1; Replacei >=0; Replacei--)
						{
							ReplaceOneColumn = m_Columns[Replacei];

							if ( Replacei > i)
							{
								TempColumns[Replacei+1] = ReplaceOneColumn;
							}

							if ( Replacei == i)
							{
								TempColumns[Replacei+1] = new CParse(NewColumnTwo); 
								TempColumns[Replacei] = new CParse(NewColumnOne);
								delete m_Columns[Replacei];
							}

							if ( Replacei < i)
							{
								TempColumns[Replacei] = ReplaceOneColumn;
							}

						}

						delete m_Columns;
						m_Columns = TempColumns;
						m_NumberOfColumns++; 

						
						
						// If necessary, Put back the "#" back for the first column
						if ( i ==0)
						{
						
							ReplaceFirstColumn = m_Columns[0];
							for ( Replacei = 1; Replacei <= ReplaceFirstColumn ->Size(); Replacei++)
							{
								Swappiece = ReplaceFirstColumn ->GetPiece(Replacei).Display(); 
								
								if ( Swappiece == QString("NULL"))
								{
									Swappiece = QString("#"); 
								}
								else
								{
									Swappiece = QString("#") + Swappiece; 
								}

								TempCSS = CStringSurrogate(Swappiece);
								SwapParse.Append(TempCSS); 
							}

							(*ReplaceFirstColumn)= SwapParse ;
						}

						FoundAndModified  = true; 
						HasEverChanged = true;
						break; 
					}

				}


				// Check through the other morpheme to see whether this morphemei could be suffix
				IsMeSuffixOfOthers = false; 
				for ( itemj= 1; itemj <= oneColumn ->Size(); itemj++)
				{
					Morphemej = oneColumn ->GetPiece(itemj).Display(); 

					if ( i ==0)
					{
						Morphemej = Morphemej.right(Morphemej.length() -1);
						if ( Morphemej.length() ==0)
						{
							Morphemej = QString("NULL"); 
						}

						continue; 
					}

					
					if ( Morphemej.length() <= Morphemei.length())
					{
						continue; 
					}

					if ( Morphemej.right(Morphemei.length()) != Morphemei)
					{
						continue; 
					}

					IsMeSuffixOfOthers = true; 
					break; 
				}

				// If found morphemei is prefix of at least one other morpheme
				if ( IsMeSuffixOfOthers)
				{
					CParse				OriginalColumn, NewColumnOne, NewColumnTwo;
					CParse*				ReplaceFirstColumn;
					int					Originali; 
					QString				oneOriginalMoprheme, oneNewMorpheme; 
					float				OlderRobustNess, NewRobustNess; 
					float				RobustNessDiff; 
					int					Replacei; 
					CParse**			TempColumns; 
					CParse*				ReplaceOneColumn; 
					QString				Swappiece;
					CParse				SwapParse; 
					
					// Try to get the NewColumnOne and NewColumnTwo
					for ( Originali = 1; Originali<= oneColumn ->Size(); Originali++)
					{
						oneOriginalMoprheme = oneColumn ->GetPiece(Originali).Display();
						
						if ( i ==0)
						{
							oneOriginalMoprheme = oneOriginalMoprheme.right(oneOriginalMoprheme.length() -1);

							if ( oneOriginalMoprheme.length() ==0)
							{
								oneOriginalMoprheme = QString("NULL"); 	
							}
						}

						TempCSS = CStringSurrogate(oneOriginalMoprheme);
						OriginalColumn.Append(TempCSS); 

						if ( oneOriginalMoprheme == QString("NULL"))
						{
							NewColumnTwo.Append(TempCSS); 
							continue; 
						}

						if ( oneOriginalMoprheme.length() <= ThePrefixOrSuffix.length())
						{
							NewColumnTwo.Append(TempCSS); 
							continue;
						}

						if ( oneOriginalMoprheme.right(ThePrefixOrSuffix.length()) != ThePrefixOrSuffix)
						{
							NewColumnTwo.Append(TempCSS); 
							continue;
						}

						if (oneOriginalMoprheme.right(ThePrefixOrSuffix.length()) == ThePrefixOrSuffix)
						{
							oneNewMorpheme = oneOriginalMoprheme.left(oneOriginalMoprheme.length() - ThePrefixOrSuffix.length());
							
							TempCSS1 = CStringSurrogate(oneNewMorpheme);
							NewColumnOne.Append(TempCSS1); 
						}
					}

					NewColumnOne.Append(NULLCSS); 

					// Get Original Robustness
					OlderRobustNess = GetRobustNessWithParadigmaticGraph(OriginalColumn, GlobalNodeStickNess2, TotalGlobalStickNess2, GlobalStickNess2, TotalWord2); 

					// Calculate the alternative robustness
					NewRobustNess = GetRobustNessWithParadigmaticGraph(NewColumnOne, GlobalNodeStickNess2, TotalGlobalStickNess2, GlobalStickNess2, TotalWord2); 			
					NewRobustNess += GetRobustNessWithParadigmaticGraph(NewColumnTwo, GlobalNodeStickNess2, TotalGlobalStickNess2, GlobalStickNess2, TotalWord2); 			

					// If Diff satisfy the condition, we make the modification, then break; 
					RobustNessDiff = NewRobustNess - OlderRobustNess;
					
					if (1)	//RobustNessDiff < 0) 
					{
					
						// Change the template by replacing the two columns for the original one
						TempColumns = new CParse*[ m_NumberOfColumns + 1];

						for ( Replacei = m_NumberOfColumns -1; Replacei >=0; Replacei--)
						{
							ReplaceOneColumn = m_Columns[Replacei];

							if ( Replacei > i)
							{
								TempColumns[Replacei+1] = ReplaceOneColumn;
							}

							if ( Replacei == i)
							{
								TempColumns[Replacei+1] = new CParse(NewColumnTwo); 
								TempColumns[Replacei] = new CParse(NewColumnOne);
								delete m_Columns[Replacei];
							}

							if ( Replacei < i)
							{
								TempColumns[Replacei] = ReplaceOneColumn;
							}

						}

						delete m_Columns;
						m_Columns = TempColumns;
						m_NumberOfColumns++; 

						
						
						// if necessary,  Put back the "#" back for the first column
						
						if ( i == 0)
						{

							ReplaceFirstColumn = m_Columns[0];
							for ( Replacei = 1; Replacei <= ReplaceFirstColumn ->Size(); Replacei++)
							{
								Swappiece = ReplaceFirstColumn ->GetPiece(Replacei).Display(); 
								
								if ( Swappiece == QString("NULL"))
								{
									Swappiece = QString("#"); 
								}
								else
								{
									Swappiece = QString("#") + Swappiece; 
								}

								TempCSS = CStringSurrogate(Swappiece);
								SwapParse.Append(TempCSS); 
							}

							(*ReplaceFirstColumn)= SwapParse ;
						}

						FoundAndModified  = true;
						HasEverChanged = true; 
						break; 
					}
				}

			
			}

			
			if ( FoundAndModified) break;

		}


	}// According to FoundAndModified, while loop; 


	// If this template is modified, output to logf
	if ( HasEverChanged)
	{
		StringToParse					OriginalWords, NewWords;
		StringToParse::iterator			StringToParseIt;
		StringToInt						NewCreatedWords; 
		StringToInt::iterator			StringToIntIt;
		QString							TempWordString; 
		CParse*							dummyParse; 
		QString							DisplayOfOneColumn; 

		
		QFile file( "PrefixOrSuffixMorphemeAdjust.txt" );
    
		if ( !file.open( QIODevice::WriteOnly | QIODevice::Append) ) 
		{
			QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
			return;    
		}

		Q3TextStream outf( &file );

		


		BackUpTemplate ->GetWordsAndParses(OriginalWords); 

		
		for ( StringToParseIt = OriginalWords.begin(); StringToParseIt != OriginalWords.end(); StringToParseIt++)
		{ 
			dummyParse = StringToParseIt.data(); 
			delete dummyParse; 
		}

		this ->GetWordsAndParses(NewWords); 

		for ( StringToParseIt = NewWords.begin(); StringToParseIt != NewWords.end(); StringToParseIt++)
		{
			dummyParse = StringToParseIt.data(); 
			TempWordString = StringToParseIt.key();

			delete dummyParse;
			
			if ( !OriginalWords.contains(TempWordString)) 
			{
				NewCreatedWords.insert(TempWordString, NULL); 
			}

		}


				
		outf << "***********"<<Loopi<<"************" <<endl;
		outf << "	Original Template:" << endl; 
		outf << "		";

		
		for ( i = 0; i < BackUpTemplate ->m_NumberOfColumns; i++)
		{
			oneColumn = BackUpTemplate ->m_Columns[i];
			
			DisplayOfOneColumn = QString("{ "); 
			for (int j =  1; j <= oneColumn ->Size();j++)
			{
				DisplayOfOneColumn += oneColumn ->GetPiece(j).Display();
				if ( j != oneColumn ->Size())
				{
					DisplayOfOneColumn += QString(" , ");
				}
			}

			DisplayOfOneColumn += QString(" }");
			outf << DisplayOfOneColumn;
			if ( i != m_NumberOfColumns -1)
			{
				outf << " --> "; 
			}
		}
		

		outf << endl; 
		outf << endl; 

		outf << "	New Template:" << endl; 
		outf << "		";

		for ( i = 0; i < m_NumberOfColumns; i++)
		{
			oneColumn = m_Columns[i];
			
			DisplayOfOneColumn = QString("{ "); 
			for (int j =  1; j <= oneColumn ->Size();j++)
			{
				DisplayOfOneColumn += oneColumn ->GetPiece(j).Display();
				if ( j != oneColumn ->Size())
				{
					DisplayOfOneColumn += QString(" , ");
				}
			}

			DisplayOfOneColumn += QString(" }");
			outf << DisplayOfOneColumn;
			if ( i != m_NumberOfColumns -1)
			{
				outf << " --> "; 
			}
		}

		outf << endl; 
		outf << endl; 

		outf << "	New Created Words:" << endl; 
		outf << "		{ ";

		for ( StringToIntIt = NewCreatedWords.begin(); StringToIntIt != NewCreatedWords.end(); StringToIntIt++)
		{
			TempWordString = 	StringToIntIt.key(); 
			outf << TempWordString << " , "; 
		}

		outf << " }"<< endl; 
		outf << endl; 
		outf << endl; 
		outf << endl; 

		file.close();  
		
	}

	  
	delete BackUpTemplate;
	
}



float	CTemplate::GetRobustNessWithParadigmaticGraph(CParse& oneColumn,  StringToFloat& MorphemeAndItsComplexity, StringToStringToFloat& GlobalStickNess, float TotalGlobalStickNess, float TotalWords)
{

	
	int						i, j; 
	QString					oneMorpheme, anotherMorpheme; 
	QString					HostMorpheme, SlaveMorpheme; 
	float					NodeRobustNess;
	float					EdgeRobustNess; 
	float					oneFloat; 
	StringToFloat*			oneCollection; 


	NodeRobustNess =0.0;
	EdgeRobustNess = 0.0;


	for ( i=1; i<= oneColumn.Size(); i++)
	{
		oneMorpheme = oneColumn.GetPiece(i).Display(); 

		if (MorphemeAndItsComplexity.contains(oneMorpheme)) 
		{
			oneFloat = MorphemeAndItsComplexity[oneMorpheme];
			NodeRobustNess += oneFloat; 
		}
		else
		{
			NodeRobustNess += (-base2log(1.0/TotalWords));  // Big Penalty		
				
		}

		for ( j =i+1; j<= oneColumn.Size(); j++)
		{
			anotherMorpheme = oneColumn.GetPiece(j).Display(); 

			if ( oneMorpheme > anotherMorpheme )
			{
				if ( GlobalStickNess.contains(oneMorpheme)) 
				{
					oneCollection = GlobalStickNess[oneMorpheme];

					if ( oneCollection ->contains(anotherMorpheme)) 
					{
						oneFloat = (*oneCollection)[anotherMorpheme];
						EdgeRobustNess += oneFloat;
					}
					else
					{
						EdgeRobustNess += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

					}
					
				}
				else
				{
					EdgeRobustNess += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
				}
			}
			else
			{
				if ( GlobalStickNess.contains(anotherMorpheme))
				{
					oneCollection = GlobalStickNess[anotherMorpheme];

					if ( oneCollection ->contains(oneMorpheme)) 
					{
						oneFloat = (*oneCollection)[oneMorpheme];
						EdgeRobustNess += oneFloat;
					}
					else
					{
						EdgeRobustNess += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	

					}
					
				}
				else
				{
					EdgeRobustNess += -base2log(1.0/TotalGlobalStickNess);  // Big Penalty	
				}							
			}
						
		}
	
	
	}

	return (NodeRobustNess + EdgeRobustNess); 
 } 








/*
// Answer the Q: does this template describe prefixes, or suffixes?
eAffixationType	  CTemplate::DetermineAffixationSide()
{
	float	threshold = 2;
	int		MinimumNumberOfStems = 3; 
	int		ColumnNumber = 0;
	int		MinimumStemLength = 4;

	if ( m_NumberOfColumns != 2 ) return TYPE_Unknown;

	//#############################################################/
	// initial templates have only 1 column with more than 1 entry; deal with them first 
	int NumberOfColumnsWithMoreThan1Entry = 0;
	for (int i = 0; i < m_NumberOfColumns; i++)
	{	if ( m_Columns[i]->Size() > 1 ) 
			NumberOfColumnsWithMoreThan1Entry ++;
			ColumnNumber = i;
	}
	//###########################################################//
	if ( NumberOfColumnsWithMoreThan1Entry == 1 )
	{
		int OtherColumn = 2 - ColumnNumber;
	}
	//###########################################################//
	else 
	{


		// We consider regular templates, with more than one column containing more than 1 entry 
		float N1 = (float) m_Columns[0]->GetLength();
		float N2 = (float) m_Columns[1]->GetLength();


		if ( N1/N2 > threshold && m_Columns[0]->Size() >= MinimumNumberOfStems ) 
		{		
			return TYPE_Suffix;
		}
		if ( N2/N1 > threshold && m_Columns[1]->Size() >= MinimumNumberOfStems) 
		{		
			return TYPE_Prefix;
		}
		return TYPE_Unknown;

	}
	//#########################################################//

	return TYPE_Unknown;
}

void CTemplate::AddToCollections ( eAffixationType ThisType, CStemCollection* Stems, CAffixCollection* Affixes, CSignatureCollection* Signatures)
{
	
	CStem*			pStem;
	CSignature*		pSig,
					*qSig;
	CParse			Sig1, Sig2;
	CStringSurrogate				ssPiece;
	CString			WordBoundary("#"),
					Null ("NULL");
	//  Right now, there is a spurious '#' at the beginning of words, so we have to 
	//	remove this from each prefix and prefix signature. The # should be removed, 
	//	and this code simplified, so that prefixes are just like suffixes.
	//
	if (ThisType == TYPE_Prefix)
	{
		for (int i = 1; i <= m_Columns[0]->Size(); i++)
		{
			Sig1 = m_Columns[0]->GetAt_SS(i);
			for (int i=1; i <= Sig1.Size(); i++)
			{
				ssPiece = Sig1.GetAt_SS(i);
				if ( ssPiece == WordBoundary ) 
				{	
					Sig2.AppendInAlphabeticalOrder (Null );
					ssPiece = Null;					
				}
				else if ( ssPiece[0] == '#' ) 
				{
					ssPiece = ssPiece.Mid(1);
					Sig2.AppendInAlphabeticalOrder ( ssPiece );
				}
				*Affixes << ssPiece;
			}
			qSig = *Signatures <<	&Sig2;
			qSig->SetAffixLocation ( WORD_INITIAL ); //this is probably no longer necessary; todo
		}
		for (i = 1; i <= m_Columns[1]->Size(); i++)
		{
			pStem = *Stems <<	m_Columns[1]->GetAt_SS(i);		
			qSig->GetStemPtrList()->AddTail(pStem);
			pStem->SetSuffixSignature (qSig);
		}
		
		return;
	}
	else if ( ThisType == TYPE_Suffix)
	{
		pSig = 	*Signatures << m_Columns[1];

		for (int i = 1; i <= m_Columns[1]->Size(); i++)
		{
			*Affixes <<	m_Columns[1]->GetAt_SS(i);
		}
		for (i = 1; i <= m_Columns[0]->Size(); i++)
		{
			pStem = *Stems <<	m_Columns[0]->GetAt_SS(i);
			pSig->GetStemPtrList()->AddTail(pStem);
			pStem->SetSuffixSignature (pSig);
		}			


		return;
	}
	return;




}

  */


//////////////////////////////////////////////////////////////////
//////  CStateListViewItem Implementation Section

CTemplateListViewItem::CTemplateListViewItem(Q3ListView *parent,
	CTemplate* templ, QString label)
	: Q3ListViewItem(parent, label),
	m_Template(templ),
	m_MaxMumShownMorphemes(4) { }

CTemplateListViewItem::CTemplateListViewItem(Q3ListViewItem* parent,
	CTemplate* templ, QString label)
	: Q3ListViewItem(parent, label),
	m_Template(templ),
	m_MaxMumShownMorphemes(4) { }

QString CTemplateListViewItem::key( int column, bool ascending ) const
{
  if(m_Template)
  {
    QString            QSstring = "";
    int				   NumberOfMorphemes;
    

    switch( column )
    {
    case 0:
      return QString("%1").arg(m_Template ->m_TemplateNumber,10);
    case 1:
      return QString("%1").arg(m_Template ->m_NumberOfColumns,10);
	case 2:
	  return QString("%1").arg(m_Template ->m_NewSortComplexity, 10);
    case 3:

	  if (m_Template-> m_Columns[0] )
	  {
		NumberOfMorphemes = m_Template->m_Columns[0]->Size() ;
	  }
	  else
	  {
		NumberOfMorphemes = 0; 
	  }
      return QString("%1").arg(NumberOfMorphemes,10);

    case 4:

	  if (m_Template-> m_Columns[1] )
	  {
		NumberOfMorphemes = m_Template->m_Columns[1]->Size() ;
	  }
	  else
	  {
		NumberOfMorphemes = 0; 
	  }
      return QString("%1").arg(NumberOfMorphemes,10);

    case 5:

	  if (m_Template->m_NumberOfColumns >= 3 )
	  {
		NumberOfMorphemes = m_Template->m_Columns[2]->Size() ;
	  }
	  else
	  {
		NumberOfMorphemes = 0; 
	  }
      return QString("%1").arg(NumberOfMorphemes,10);

    case 6:

	  if (m_Template->m_NumberOfColumns >= 4 )
	  {
		NumberOfMorphemes = m_Template->m_Columns[3]->Size() ;
	  }
	  else
	  {
		NumberOfMorphemes = 0; 
	  }
      return QString("%1").arg(NumberOfMorphemes,10);

    default:
      return Q3ListViewItem::text( column );
    }
  }
  else return Q3ListViewItem::key( column, ascending );


}

QString CTemplateListViewItem::text( int column ) const
{

  if(m_Template)
  {
    QString          QSstring = "";
    int              i;
    int              NumberOfMorphemes;
    int              NumberOfDisplayedMorphemes;
    bool             ShowPlus;
//    int					 PrintedMorphemes=0;
	QString				 QSOneMorpheme, QSReversedOneMorpheme; 
	CStringSurrogate	 SSOneMorpheme; 
//	const char*			 CCDebugString1, *CCDebugString2;


    switch( column )
    {
    case 0:
      return QString("%1").arg( m_Template->m_TemplateNumber);
    case 1:
      return QString("%1").arg( m_Template ->m_NumberOfColumns);
    case 2:
      return QString("%1").arg( m_Template ->m_NewSortComplexity);
	case 3:


	  if ( m_Template->m_NumberOfColumns < 1)
	  {
		  return QString("");
	  }

      NumberOfMorphemes = m_Template->m_Columns[0] ->Size() ;

      NumberOfDisplayedMorphemes = m_MaxMumShownMorphemes;
      ShowPlus  = true;
      if(NumberOfMorphemes <= m_MaxMumShownMorphemes)
      {
        NumberOfDisplayedMorphemes = NumberOfMorphemes;
        ShowPlus = false;
      }

      for( i = 1; i <= NumberOfDisplayedMorphemes ; i++ )
      {
		QSstring.append( m_Template->m_Columns[0] ->GetPiece(i).Display() + ", "); 
	  }
      QSstring = QSstring.left( QSstring.length() - 2 );

      if(ShowPlus)
      {
        QSstring += " +";
      }
      return QSstring;

    case 4:

	  if ( m_Template->m_NumberOfColumns < 2)
	  {
		  return QString("");
	  }
    
	  NumberOfMorphemes = m_Template->m_Columns[1] ->Size() ;

      NumberOfDisplayedMorphemes = m_MaxMumShownMorphemes;
      ShowPlus  = true;
      if(NumberOfMorphemes <= m_MaxMumShownMorphemes)
      {
        NumberOfDisplayedMorphemes = NumberOfMorphemes;
        ShowPlus = false;
      }

      for( i = 1; i <= NumberOfDisplayedMorphemes ; i++ )
      {
		QSstring.append( m_Template->m_Columns[1] ->GetPiece(i).Display() + ", "); 
	  }
      QSstring = QSstring.left( QSstring.length() - 2 );

      if(ShowPlus)
      {
        QSstring += " +";
      }
      return QSstring;

	case 5:

	  if ( m_Template->m_NumberOfColumns < 3)
	  {
		  return QString("");
	  }
    
	  NumberOfMorphemes = m_Template->m_Columns[2] ->Size() ;

      NumberOfDisplayedMorphemes = m_MaxMumShownMorphemes;
      ShowPlus  = true;
      if(NumberOfMorphemes <= m_MaxMumShownMorphemes)
      {
        NumberOfDisplayedMorphemes = NumberOfMorphemes;
        ShowPlus = false;
      }

      for( i = 1; i <= NumberOfDisplayedMorphemes ; i++ )
      {
		QSstring.append( m_Template->m_Columns[2] ->GetPiece(i).Display() + ", "); 
	  }
      QSstring = QSstring.left( QSstring.length() - 2 );

      if(ShowPlus)
      {
        QSstring += " +";
      }
      return QSstring;
	
	case 6:

	  if ( m_Template->m_NumberOfColumns < 4)
	  {
		  return QString("");
	  }
    
	  NumberOfMorphemes = m_Template->m_Columns[3] ->Size() ;

      NumberOfDisplayedMorphemes = m_MaxMumShownMorphemes;
      ShowPlus  = true;
      if(NumberOfMorphemes <= m_MaxMumShownMorphemes)
      {
        NumberOfDisplayedMorphemes = NumberOfMorphemes;
        ShowPlus = false;
      }

      for( i = 1; i <= NumberOfDisplayedMorphemes ; i++ )
      {
		QSstring.append( m_Template->m_Columns[3] ->GetPiece(i).Display() + ", "); 
	  }
      QSstring = QSstring.left( QSstring.length() - 2 );

      if(ShowPlus)
      {
        QSstring += " +";
      }
      return QSstring;


    default:
      return Q3ListViewItem::text( column );
    }
  }
  else return Q3ListViewItem::text( column );

}


