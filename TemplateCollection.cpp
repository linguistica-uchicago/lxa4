// Implementation of CTemplateCollection methods
// Copyright © 2009 The University of Chicago
#include "TemplateCollection.h"

#include <memory>
#include <Q3TextStream>
#include <QMessageBox>
#include <Q3ListView>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "Alignment.h"
#include "Template.h"
#include "WordCollection.h"
#include "HTML.h"
#include "log2.h"

CTemplateCollection::CTemplateCollection(CLexicon* lexicon)
{
	m_lexicon = lexicon; 
	m_AllWordsAndParses = NULL;

}
 
CTemplateCollection::~CTemplateCollection(void)
{
}


void CTemplateCollection::ListDisplay(Q3ListView* pView)
{
		
  //QMessageBox::information( NULL, "Debug","Begin to Lisplay","OK" );		

  int              Counter =1;

	pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);


  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  //    Add Column headers
  pView->addColumn( "TemplateNumber" );
  pView->addColumn( "NumberOfColumns" );
  pView->addColumn( "Complexity" );
  pView->addColumn( "Layer1" );
  pView->addColumn( "Layer2" );
  pView->addColumn( "Layer3" );
  pView->addColumn( "Layer4" );
  
  // Column three or four gets really wide, limit
  // the width to 180
  pView->setColumnWidthMode( 2, Q3ListView::Manual );
  pView->setColumnWidth( 2, 180 );

  pView->setColumnWidthMode( 3, Q3ListView::Manual );
  pView->setColumnWidth( 3, 180 );

  pView->setColumnWidthMode( 4, Q3ListView::Manual );
  pView->setColumnWidth( 4, 180 );

  pView->setColumnWidthMode( 5, Q3ListView::Manual );
  pView->setColumnWidth( 5, 180 );


  m_lexicon->GetDocument()->setStatusBar1( "Displaying Templates" );
  m_lexicon->GetDocument()->BeginCountDown();


  const int TotalNumber = GetCount();
  for (int i = 0; i < TotalNumber; ++i) {
      CTemplate* pTemplate = GetAt(i);
      pTemplate->ListDisplay(pView);
      m_lexicon->GetDocument()->CountDownOnStatusBar(Counter++, (TotalNumber/20)*20, TotalNumber/20);
  }

  m_lexicon->GetDocument()->setStatusBar1( "" );
  m_lexicon->GetDocument()->EndCountDown();



	/*
	CTemplate*  pTemplate;
	int			MaxNumberOfColumns = 0,
				SuffixColumn;
	int			col = 0,
				n;

	for (int j = 0; j < GetCount(); j++)
	{
		n = GetAt(j)->GetNumberOfColumns();
		if (n > MaxNumberOfColumns ) 
		{ MaxNumberOfColumns = n;}

	}

	CListCtrl& List = pView->GetListCtrl();

	//			Clean it out first		
	for (int i = 0; i < (int) pView->GetNumberOfColumns(); i++)
	{
		List.DeleteColumn(0);
	}
	List.DeleteAllItems();


	//		Add Column headers			
	pView->GetListCtrl().InsertColumn(col++, "Savings", LVCFMT_LEFT, 120);	
	pView->IncrementNumberOfColumns();
	
	List.InsertColumn(col++, "1", LVCFMT_RIGHT, 80);	
	pView->IncrementNumberOfColumns();

	List.InsertColumn(col++, "2", LVCFMT_RIGHT, 80);	
	pView->IncrementNumberOfColumns();

	List.InsertColumn(col++, "3", LVCFMT_RIGHT, 90);	
	pView->IncrementNumberOfColumns();

	List.InsertColumn(col++, "4", LVCFMT_RIGHT, 80);	
	pView->IncrementNumberOfColumns();

	List.InsertColumn(col++, "5", LVCFMT_RIGHT, 50	);	
	pView->IncrementNumberOfColumns();
	
	List.InsertColumn(col++, "6", LVCFMT_RIGHT, 100);	
	pView->IncrementNumberOfColumns();

	for (; col <= 4 + MaxNumberOfColumns; col++)
	{
		List.InsertColumn(col, "7", LVCFMT_RIGHT, 75 );	
		pView->IncrementNumberOfColumns();
	}
		
	SuffixColumn = col;
	List.InsertColumn(col++, "Suffix", LVCFMT_RIGHT, 70);	
	pView->IncrementNumberOfColumns();

	if (!m_SortValidFlag) {	Sort (TEMPLATE_SORT); }

	m_HashHasChangedFlag = TRUE;

	int linenumber  = 0;
	for (i = 0; i < GetCount(); i++)
	{
		pTemplate = GetAtSort(i);
		pTemplate->Display( List, linenumber);
		linenumber++;
	}



	*/

}

CTemplate* CTemplateCollection::AddTemplate( CTemplate* pTemplate)
{

	CTemplate*			qTemplate; 
	CNode*				pTerminal;
	int					Result;

	QString				SpelledOutTemplate = pTemplate->Display(); // yuhuask Problematic ?

	pTerminal = Insert (CStringSurrogate(SpelledOutTemplate), &Result);
	if ( Result == 1)
	{
		qTemplate = new CTemplate( * pTemplate);
		pTerminal->SetPointer (qTemplate);
	}
	else
	{
		qTemplate =(CTemplate*) pTerminal->Get_T_Pointer();
	}

	IncrementCorpusCount(1);	
	qTemplate->IncrementCorpusCount(1);	 
	 
	m_SortValidFlag			= FALSE;
	m_HashHasChangedFlag	= TRUE;
	
	return qTemplate;


}


CTemplate* CTemplateCollection::AddToCollection(CAlignment* pAlign)
{
	int Result;
	CNode* pTerminal = Insert(
			CStringSurrogate(pAlign->SpellOut()),
			&Result);

	std::auto_ptr<CTemplate> pTemplate;
	if (Result == 1) {
		pTemplate = std::auto_ptr<CTemplate>(new CTemplate(pAlign));
		pTemplate->SetIndex(GetCount() - 1);
		pTerminal->SetPointer(pTemplate.get());
	} else {
		pTemplate = std::auto_ptr<CTemplate>(
			static_cast<CTemplate*>(pTerminal->Get_T_Pointer()));
	}

	IncrementCorpusCount(1);
	pTemplate->IncrementCorpusCount(1);	 

	m_SortValidFlag = false;
	m_HashHasChangedFlag = true;

	return pTemplate.release();
}

void CTemplateCollection::CheckForConflations 
					( CTemplateCollection* InputCollection )
{
	int						Column;
	bool					BreakFlag;
	CTemplateCollection		TemporaryHoldings (m_lexicon);

	QString			debugstring1, debugstring2; 
//	const char*     CCDebugString1, *CCDebugString2;
//	int				debugint; 

	int i;
	for (i = 0; i < InputCollection->GetCount(); i++)
	{
		CTemplate* pTemplate = InputCollection->GetAt(i);
		BreakFlag = FALSE;

		int j;
		for ( j = 0; j < GetCount(); j++)
		{
			CTemplate* qTemplate = GetAt(j);
			if ( pTemplate->ShouldConflate(qTemplate, Column) )
			{				
				//debugstring1 = pTemplate ->Display(); 
				//CCDebugString1 = debugstring1.ascii();
				//debugstring2 = qTemplate->Display(); 
				//CCDebugString2 = debugstring2.ascii();
				//debugint = 1; 
				
				qTemplate->ConflateWith( pTemplate, Column ) ;		
				BreakFlag = TRUE;
				
			}
			
		}
		if (BreakFlag) { continue; }	

		for (j = i+1; j < InputCollection->GetCount(); j++)
		{	

			CTemplate* qTemplate = InputCollection->GetAt(j);
			if ( pTemplate->ShouldConflate(qTemplate, Column) )
			{
				
				
				//debugstring1 = pTemplate ->Display(); 
				//CCDebugString1 = debugstring1.ascii();
				//debugstring2 = qTemplate->Display(); 
				//CCDebugString2 = debugstring2.ascii();
				//debugint = 1; 
				
				
				pTemplate->ConflateWith( qTemplate, Column );
				this->AddTemplate ( pTemplate  );
				break; 
			}
			
		}
	}

	// Keep in mind, for each column, the morpheme can be repeated
	// e.g. b#g#_ettingbradybrady_; 


	
	//################################################
	// Debug and test, should be no useful for release


	/*
	for (i = 0; i < GetCount(); i++)
	{
		debugstring1 = GetAt(i)->Display(); 
		CCDebugString1 = debugstring1.ascii();
		debugint = 1; 

	}
	*/

	//################################################
	// ReAdjust - Pre-edit-1


	 
	do {
		
		TemporaryHoldings.Empty();
		for (i = 0; i < GetCount(); i++)
		{
			GetAt(i)->Readjust( &TemporaryHoldings );
		}
		for (i = 0; i < TemporaryHoldings.GetCount(); i++)
		{
			this->AddTemplate( TemporaryHoldings[i] );
		}
	}
	while (TemporaryHoldings.GetCount() > 0 );


	//*******************************************
	/* Get PolyMorpheme
	CWordCollection Words, NewWords, TempWords;
	CPolyMorpheme* pWord;

	for (i = 0; i < GetCount(); i++)
	{
		CTemplate* pTemplate = GetAt(i);
		Words.Empty();


		for (int j = 1; j <= pTemplate->GetColumn(0)->Size(); j++)
		{ Words << pTemplate->GetColumn(0)->GetAt_SS(j) ; }
	
		for (int col = 1; col < pTemplate->GetNumberOfColumns(); col++)
		{
			NewWords.Empty();

			for (int row = 1; row <= (int) pTemplate->GetColumn(col)->Size(); row++)
			{
				TempWords = Words;

				CSS ss = pTemplate->GetColumn(col)->GetAt_SS(row);
				if (ss == CSS("NULL") )
				{
					
				} else
				{
					TempWords.SuffixToAllWords ( pTemplate->GetColumn(col)->GetAt_SS(row) );
				}
				NewWords.AddWordCollection( TempWords );
			}
			Words = NewWords;			
		}

		for (int k = 0; k < (int) Words.GetCount(); k++)
		{
			pWord = *Lexicon->GetPolyWords() << Words.GetAt(k);
			pWord->CopyParse ( *(CParse*)Words.GetAt(k) );
		}

	}
	*/



}


void  CTemplateCollection::OutputTemplatesForGoldStand()
{
	StringToParse					OneWordsAndParses; 
	StringToParse::Iterator			StringToParseIt; 
	QString							TheWord; 
	CParse*							TheParse;
	CParse*							OneParse; 
	QString							SSDisplay;

	
	if ( m_AllWordsAndParses != NULL) delete m_AllWordsAndParses; 

	m_AllWordsAndParses = new StringToParse();  

	//QMessageBox::information( NULL, "Debug", "Run Here -1", "OK" );

	for (int i = 0; i < GetCount(); i++) 
	{	 		
		CTemplate* pTemplate = GetAt(i);
		
		OneWordsAndParses.clear();
		pTemplate ->GetWordsAndParses(OneWordsAndParses); 
		
	
		for ( StringToParseIt = OneWordsAndParses.begin(); StringToParseIt != OneWordsAndParses.end(); StringToParseIt++)
		{
			TheWord = StringToParseIt.key();
			TheParse = StringToParseIt.data(); 
			

			if ( m_AllWordsAndParses ->contains(TheWord))
			{
				OneParse = (*m_AllWordsAndParses)[TheWord];
				OneParse ->yuhuMergeParse(TheParse); 
			}
			else
			{
				m_AllWordsAndParses ->insert(TheWord, TheParse); 
			}

		}
		
	}

	
 }






 /*
void CTemplateCollection::OutputTemplates ( LPCTSTR FileName)
{
	ofstream		outf(FileName); 		  
	outf			<< setiosflags (ios::left); 
	outf			<< GetCount() ;

	Sort (TEMPLATE_SORT);
	for (int i = 0; i < GetCount(); i++) 
	{	 		
		CTemplate* pTemplate = GetAtSort(i);
		pTemplate->OutputForFile ( outf );
		outf << endl;
			 
	
		outf << "Number of columns: "<< pTemplate->GetNumberOfColumns() << endl;
		outf << "Complexity: "		 << pTemplate->GetComplexity()		<< endl;
		outf << "Words complexity: " << pTemplate->GetWordsTotalComplexity() << endl;	
		outf << "Sorting quantity: " << pTemplate->GetSortingQuantity()	<< endl<< endl;
	
	}
	outf.close();
}

void CTemplateCollection::ReadTemplateFile( LPCTSTR FileName)
{
	const int bufferSize = 256;
	char buffer[bufferSize];

	CTemplate*	pTemplate;
	CParse*		pParse= new CParse();
	ifstream	inf(FileName); 
	int			size			= 0,
				Count			= 0,
				NumberOfColumns = 0;
				inf.getline(buffer, bufferSize, '\n');		
				size = atoi (buffer);

	while (inf && Count < size) 
	{	
		
		inf.getline(buffer, bufferSize, '\n');		
		pParse->Collapse(buffer);
		if ( pParse->Size() <= 0) { continue; }

		NumberOfColumns = pParse->Size();
		pTemplate = new CTemplate (NumberOfColumns);
		for (int i = 1; i<= (int) pParse->Size(); i++)
		{
			pTemplate->AddToColumn( pParse->GetAt_SS(i), i-1);
		}
		while (inf)
		{
			inf.getline (buffer, bufferSize, '\n');
			pParse->Collapse(buffer);
			if ( pParse->Length() == 0 ) 
			{ 
				break; 
			}
		
			for (int i = 1; i<= (int) pParse->Size(); i++)
			{
				if ( pParse->GetAt_SS(i).FirstChar() == '-' ) { continue;}
				pTemplate->AddToColumn( pParse->GetAt_SS(i), i-1);
			}
		}			 
		AddTemplate ( pTemplate );
		// there are 10 lines with stuff we don't read.
		for (i = 0; i < 10; i++) { inf.getline(buffer, bufferSize, '\n'); }


		Count++;
	}
}

int CompareTemplateColumn1 (const void *pA, const void *pB)
{
	CTemplate* pS1=*(CTemplate**) pA;
	CTemplate* pS2=*(CTemplate**) pB;	 
	
	int Value1 = pS1->GetColumn(0)->SpellOut().Compare(pS2->GetColumn(0)->SpellOut() );
	if ( Value1 != 0 ) return Value1;

	int Value2 = pS1->GetColumn(1)->SpellOut().Compare(pS2->GetColumn(1)->SpellOut() );
	 return Value2;

//	int Value3 = pS1->GetColumn(3)->SpellOut().Compare(pS2->GetColumn(3)->SpellOut() );
//	if ( Value2 != 0 ) return Value2;
 
}
int CompareTemplateColumn2 (const void *pA, const void *pB)
{
	CTemplate* pS1=*(CTemplate**) pA;
	CTemplate* pS2=*(CTemplate**) pB;	 
	
	if ( pS1->GetColumn(1) == NULL )
	{
		if ( pS2->GetColumn(1) == NULL )
		{
			return 0;
		}
		return -1;
	}
	if ( pS2->GetColumn(1) == NULL )
	{		
		return -1;
	}


	int Value1 = pS1->GetColumn(1)->SpellOut().Compare(pS2->GetColumn(1)->SpellOut() );
	if ( Value1 != 0 ) return Value1;

	int Value2 = pS1->GetColumn(0)->SpellOut().Compare(pS2->GetColumn(0)->SpellOut() );
	
	return Value2;

//	int Value3 = pS1->GetColumn(3)->SpellOut().Compare(pS2->GetColumn(3)->SpellOut() );
//	if ( Value2 != 0 ) return Value2;
 
}


void CTemplateCollection::SortTemplates (eSortStyle SortStyle, int ColumnNumber )
{
	if (SortStyle != TEMPLATE_SORT_COLUMN) { return; }

	int Size = GetCount();

	if (SortArray) { delete [] SortArray; }

	SortArray  = new CTemplate*[ Size ];

	double* ValueArray = new double    [ Size ];


	for (int i = 0; i < Size; i++)
	{
		SortArray[i] = GetAt( i );		
	}

	// Fix this -- make it general, not case by case
	switch ( ColumnNumber ) 
	{
	case 1:
		{
			qsort((void*) SortArray, Size, sizeof(CTemplate*), CompareTemplateColumn1);
			break;
		}
	case 2:
		{
			qsort((void*) SortArray, Size, sizeof(CTemplate*), CompareTemplateColumn2);
			break;
		}
	case 3:
		{
//			qsort((void*) SortArray, Size, sizeof(CTemplate*), CompareTemplateColumn3);
			break;
		}	
	}

	m_SortValidFlag = true;	 

	m_SortStyle = SortStyle;	



}
*/


/*		This function looks for templates with 3 columns in which most of the letters --
		that is, the lexical heads -- are in the 3rd column.
*/

/*
void CTemplateCollection::FindPrefixingTemplates( CTemplateCollection* PrefixingTemplates )
{
	CTemplate*	pTemplate;
	double		Threshold = 0.2,
				NumberOfLetters,
				FirstColumnNL = 0,
				SecondColumnNL = 0;

	for (int i = 0; i < (int) GetCount(); i++)
	{
		pTemplate = GetAt(i);
		if ( pTemplate->GetNumberOfColumns() < 3 ) { continue; }
		NumberOfLetters = pTemplate->GetNumberOfLetters();
		if ( (double) pTemplate->GetColumn(0)->GetLength() / NumberOfLetters  < Threshold  &&
			 (double) pTemplate->GetColumn(1)->GetLength() / NumberOfLetters  < Threshold 
		   )
		{
			PrefixingTemplates->AddTemplate( pTemplate );
		}
	}







}


eAffixationType	CTemplateCollection::FindAffixationSide()
{
	int		HowManyTemplates = 10;
	double	nPrefix = 0,
			nSuffix = 0,
			nUnknown = 0;
	double	Threshold = 0.6;

	Sort (TEMPLATE_SORT );
	for (int i = 0; i < HowManyTemplates && i < GetCount(); i++)
	{
		switch (GetAtSort(i)->DetermineAffixationSide() )
		{
		case (TYPE_Suffix):
			{	
				nSuffix++;
				break;
			}
		case (TYPE_Prefix):
			{
				nPrefix++;
				break;
			}
		case (TYPE_Unknown):
			{
				nUnknown++;
				break;
			}
		}
	}


	int Total = int( nPrefix + nSuffix + nUnknown );
	if (nPrefix / Total > Threshold )
		return TYPE_Prefix;
	if (nSuffix / Total > Threshold )
		return TYPE_Suffix;
	return TYPE_Unknown;





}

void CTemplateCollection::AddToCollections( CStemCollection* SuffixStems,
										  CStemCollection* PrefixStems,
										  CSuffixCollection* Suffixes,
										  CPrefixCollection* Prefixes,
										  CSignatureCollection* PrefixSignatures,
										  CSignatureCollection* SuffixSignatures )

{
	eAffixationType Type;
	if ( Lexicon->GetLogFile() ) { *Lexicon->GetLogFile() << endl << endl << "Adding templates to collections" << endl  ; }
	for (int i = 0; i < GetCount(); i++)
	{

		Type = GetAt(i)->DetermineAffixationSide();
		if ( Lexicon->GetLogFile() ) { *Lexicon->GetLogFile() << endl << GetAt(i)->SpellOut(); }
		if ( Type == TYPE_Suffix )
		{
			GetAt(i)->AddToCollections ( Type,   SuffixStems, (CAffixCollection*) Suffixes, SuffixSignatures );
			if ( Lexicon->GetLogFile() ) { *Lexicon->GetLogFile() << "\t Suffix"; }
		}

		if ( Type == TYPE_Prefix )
		{
			GetAt(i)->AddToCollections ( Type, PrefixStems, (CAffixCollection*)  Prefixes, PrefixSignatures );
			if ( Lexicon->GetLogFile() ) { *Lexicon->GetLogFile() << "\t Prefix"; }
		}
	}
}



*/


void	CTemplateCollection::UpdateGlobalStickNess2()
{
	
	int									i, column; 
	int									piecei, piecej;
	QString								Morphemei, Morphemej; 
	QString								HostMorpheme, SlaveMorpheme; 
	QString								PreviousMorpheme, CurrentMorpheme; 
	QString								oneMorpheme; 
	CParse*								oneColumn; 
	float								myComplexity; 
	StringToFloat*						oneCollection;
	StringToFloat::Iterator				StringToFloatIt;
	StringToStringToFloat::Iterator		StringToStringToFloatIt; 
	StringToInt							AllMorphemes; 
	StringToInt							MorphemesInThisTemplate; 
	StringToInt::Iterator				StringToIntIt;
	float								oneFloat; 
	int									NumberOfWordsInThisTemplate; 
	int									TotalWords; 
	QString								dummystring; 


	QFile file( "paragmatic.txt" );
    
	if ( !file.open( QIODevice::WriteOnly ) ) 
	{
		return;    
	}

	Q3TextStream logf( &file );
	
	Sort (TEMPLATE_SORT);


	// Clear m_GlobalStickNess2; 
	for (StringToStringToFloatIt = m_GlobalStickNess2.begin(); StringToStringToFloatIt != m_GlobalStickNess2.end();  StringToStringToFloatIt++)
	{
		oneCollection = StringToStringToFloatIt.data(); 
		delete oneCollection;
	}


	// Clear m_GlobalStickNess2 and m_GlobalNodeStickNess2
	m_GlobalStickNess2.clear(); 
	m_GlobalNodeStickNess2.clear(); 

	
	
	AllMorphemes.clear(); 
	m_TotalGlobalStickNess2 = 0.0;

	TotalWords = 0; 

	for (i = 0; i < GetCount(); i++) {
		CTemplate* pTemplate = GetAtSort(i);

		if ( pTemplate ->m_IsDeleted) continue; 


		//myComplexity = pTemplate ->GetSortingQuantity(); in this function, we take number of words as robustness

		MorphemesInThisTemplate.clear(); 

		NumberOfWordsInThisTemplate = 1; 
		for ( column =0; column < pTemplate ->m_NumberOfColumns; column++)
		{
			oneColumn = pTemplate -> m_Columns[column];
			NumberOfWordsInThisTemplate = NumberOfWordsInThisTemplate * oneColumn ->Size(); 
		}

		TotalWords += NumberOfWordsInThisTemplate;
		myComplexity = (float) NumberOfWordsInThisTemplate;
		

		for ( column =0; column < pTemplate ->m_NumberOfColumns; column++)
		{
			oneColumn = pTemplate -> m_Columns[column];
			
			if ( oneColumn ->Size() <= 1) 
			{
				Morphemei = oneColumn ->GetPiece(1).Display(); 
				
				if ( column ==0)
				{
					Morphemei = Morphemei.right(Morphemei.length() -1); 
					
					if ( Morphemei.length() ==0)
					{
						Morphemei = TheStringNULL; 
					}
					
				}
				
				AllMorphemes.insert(Morphemei, 1);
				MorphemesInThisTemplate.insert(Morphemei, 1);
				continue;
			}

			for ( piecei = 1; piecei <= oneColumn ->Size() -1; piecei++)
			{
				Morphemei = oneColumn ->GetPiece(piecei).Display(); 
				
				if ( column ==0)
				{
					Morphemei = Morphemei.right(Morphemei.length() -1); 
					
					if ( Morphemei.length() ==0)
					{
						Morphemei = TheStringNULL; 
					}
					
				}
				AllMorphemes.insert(Morphemei, 1); 
				MorphemesInThisTemplate.insert(Morphemei, 1);

				for ( piecej = piecei + 1; piecej <= oneColumn ->Size(); piecej++)
				{
					Morphemej = oneColumn ->GetPiece(piecej).Display(); 
				
					if ( column ==0)
					{
						Morphemej = Morphemej.right(Morphemej.length() -1); 
						
						if ( Morphemej.length() ==0)
						{
							Morphemej = TheStringNULL; 
						}
						
					}

					AllMorphemes.insert(Morphemej, 1); 
					MorphemesInThisTemplate.insert(Morphemej, 1);


					if ( Morphemei > Morphemej)
					{
						HostMorpheme = Morphemei; 
						SlaveMorpheme = Morphemej; 
					}
					else
					{
						HostMorpheme = Morphemej; 
						SlaveMorpheme = Morphemei; 						
					}

					if ( m_GlobalStickNess2.contains(HostMorpheme))
					{
						oneCollection = m_GlobalStickNess2[HostMorpheme];

						if ( oneCollection ->contains(SlaveMorpheme))
						{
							(*oneCollection)[SlaveMorpheme] += myComplexity; 
							m_TotalGlobalStickNess2 += myComplexity; 

						}
						else
						{
							oneCollection ->insert(SlaveMorpheme, (float)(myComplexity));							
							m_TotalGlobalStickNess2 += myComplexity; 
						}
					
					}
					else
					{
						oneCollection = new StringToFloat();
						m_GlobalStickNess2.insert(HostMorpheme, oneCollection); 

						oneCollection ->insert(SlaveMorpheme, (float)(myComplexity));							
						m_TotalGlobalStickNess2 += myComplexity;
					
					}


				}
			
			
			
			
			}
			




		}


		// Get the Vertex stickness for this template

		for ( StringToIntIt = MorphemesInThisTemplate.begin(); StringToIntIt != MorphemesInThisTemplate.end();  StringToIntIt++)
		{
			oneMorpheme = StringToIntIt.key(); 
				
			if ( m_GlobalNodeStickNess2.contains(oneMorpheme))
			{
				m_GlobalNodeStickNess2[oneMorpheme] += myComplexity;
			}
			else
			{
				m_GlobalNodeStickNess2.insert(oneMorpheme,(float)(myComplexity));
			}

		}


	}


	// Finally, Calculate the -log(prob) of edge stickness and vertex stickness
	float				LogValue; 

	logf << "********The Paragmatic Edge StickNess******"<<endl<<endl; 
	
	for ( StringToStringToFloatIt = m_GlobalStickNess2.begin(); StringToStringToFloatIt != m_GlobalStickNess2.end(); StringToStringToFloatIt++)
	{
		HostMorpheme = StringToStringToFloatIt.key(); 
		oneCollection = StringToStringToFloatIt.data(); 

		
		for ( StringToFloatIt = oneCollection ->begin(); StringToFloatIt != oneCollection ->end(); StringToFloatIt++)
		{
			SlaveMorpheme = StringToFloatIt.key(); 
			oneFloat = StringToFloatIt.data();
			
			LogValue = -base2log((oneFloat)/m_TotalGlobalStickNess2); 
			(*oneCollection)[SlaveMorpheme] = LogValue;
			
			// Log Info
			logf << HostMorpheme << "-" << SlaveMorpheme << " : "<<LogValue << endl; 
		
		}
	
	}



	logf <<endl<<endl<<endl; 


	logf << "********The Paragmatic Node StickNess******"<<endl<<endl; 


	for ( StringToFloatIt = m_GlobalNodeStickNess2.begin(); StringToFloatIt != m_GlobalNodeStickNess2.end(); StringToFloatIt++)
	{
		oneMorpheme = StringToFloatIt.key();
		oneFloat = StringToFloatIt.data(); 

		LogValue = -base2log((oneFloat)/(float)TotalWords); 
		m_GlobalNodeStickNess2[oneMorpheme] = LogValue;

		// Log Info
		logf << oneMorpheme << " : " << LogValue << endl; 
	}

	m_TotalWord2 = (float)TotalWords; 

	logf <<endl; 

	
	 file.close(); 

}



void  CTemplateCollection::AdjustTemplatesByMovingCommonTailOrHead2(int Loopi)
{
	// Parameter
	const int						MaximumSizeOfEachColumn = 3; 
	const int						MaximumNumberOfMovingLetters = 3; 
	bool							PrintChangedTemplates = true; 
	
	Sort (TEMPLATE_SORT);


	// Check Through each Template Once
	for (int i = 0; i < GetCount(); i++) {
		CTemplate* pTemplate = GetAtSort(i);
		
		if (pTemplate ->m_IsDeleted) continue; 

		/*
		if ( i == GetCount() -1)
		{
			QMessageBox::information (NULL, "Debug", QString("Run Template %1").arg(i), "OK");
		}
		*/

		pTemplate ->AdjustMeByMovingCommonTailOrHead2(m_GlobalNodeStickNess2,MaximumSizeOfEachColumn, \
			MaximumNumberOfMovingLetters,PrintChangedTemplates, Loopi, true, m_GlobalStickNess2, m_TotalGlobalStickNess2, m_TotalWord2);  
	}
	
	
}

bool	CTemplateCollection::CollapseAlgorithm1(int  loopnumber)
{
	
	
	
	// Parameters
	int					MinimumSizeOfStemColumn = 5;
	int					OnlyConsiderTemplatesWithSlotNumber =3; 
	int					MaximumSymmetricError = 2;
	int					MinimumCommonStem =2; 
	int					MaximumOutputMorphemesInOneColumn=10000; 
	bool				PrintCollapsedTemplates = true; 
	bool				PrintCreatedWords = true; 
	bool				DisplayOldDeletedTemplates = false;

	int					i,j;
	CTemplate* qTemplate;
	int					column; 
	CParse*				pLeftColumn, *pRightColumn, *pStemColumn;
	CParse*				qLeftColumn, *qRightColumn, *qStemColumn;
	int					pIndexOfFirstOfNonStemColumns,pIndexOfStemColumn; 
	int					qIndexOfFirstOfNonStemColumns,qIndexOfStemColumn; 
	bool				pShouldConsiderMe;
	bool				qShouldConsiderMe;
	bool				CollapsedAnyOne; 
	bool				AnyChanged ;

	AnyChanged = false; 


	CollapsedAnyOne = true;

	// Loop until no more templates are collpased
	while ( CollapsedAnyOne)
	{
	
		// Check Through each Template for possible collapsing
		for (i = 0; i < GetCount()-1; i++) {
			CTemplate* pTemplate = GetAtSort(i);
			pShouldConsiderMe = false;
			CollapsedAnyOne = false;

			if (pTemplate ->m_IsDeleted)
			{
				continue;
			}


			if (pTemplate ->m_NumberOfColumns != OnlyConsiderTemplatesWithSlotNumber)
			{
				continue;
			}


			for ( column =0; column < pTemplate ->m_NumberOfColumns -1; column++)
			{
				pLeftColumn = pTemplate ->m_Columns[column];
				pRightColumn = pTemplate ->m_Columns[column+1];
				pIndexOfFirstOfNonStemColumns = column; 
				
				if ( column ==0)
				{
					pStemColumn = pTemplate ->m_Columns[column+2];
					pIndexOfStemColumn = column + 2; 
				}
				else
				{
					pStemColumn = pTemplate ->m_Columns[0];
					pIndexOfStemColumn =0; 
				}

				if (( pLeftColumn ->Size() < MinimumSizeOfStemColumn) \
						&& ( pRightColumn ->Size() < MinimumSizeOfStemColumn)\
						&& ( pStemColumn ->Size() >= MinimumSizeOfStemColumn))
				{
					pShouldConsiderMe = true;
					break;
				}
			}
			
			if ( !pShouldConsiderMe)
			{
				continue; 
			}

			
			for (j = i+1; j < GetCount(); j++) 
			{
				qTemplate = GetAtSort(j);
				qShouldConsiderMe = false;

				if (qTemplate ->m_IsDeleted)
				{
					continue;
				}

				if (qTemplate ->m_NumberOfColumns != OnlyConsiderTemplatesWithSlotNumber)
				{
					continue;
				}
				

				for ( column =0; column < qTemplate ->m_NumberOfColumns -1; column++)
				{
				
					if ( column != pIndexOfFirstOfNonStemColumns)
					{
						continue;
					}
					
					qLeftColumn = qTemplate ->m_Columns[column];
					qRightColumn = qTemplate ->m_Columns[column+1];
					qIndexOfFirstOfNonStemColumns = column; 
					
					if ( column ==0)
					{
						qStemColumn = qTemplate ->m_Columns[column+2];
						qIndexOfStemColumn = column + 2; 
					}
					else
					{
						qStemColumn = qTemplate ->m_Columns[0];
						qIndexOfStemColumn =0; 
					}

					if (( qLeftColumn ->Size() < MinimumSizeOfStemColumn) \
							&& ( qRightColumn ->Size() < MinimumSizeOfStemColumn)\
							&& ( qStemColumn ->Size() >= MinimumSizeOfStemColumn))
					{
						qShouldConsiderMe = true;
						break;
					}
				}
				
				if ( !qShouldConsiderMe)
				{
					continue; 
				}

				//*******************************************************
				// Now the pTemplate and qTemplate are ready to compare 
				// Creteria:
				// 1. One of the two non-stem columns is indentical
				// 2. Another non-stem column's symmetric error less than MaximumSymmetricError
				// 3. The # of common stems is bigger than MinimumCommonStem
				//********************************************************

				bool				PassNonStemColumnTest;
				bool				PassStemColumnTest;
				int					NumberOfSymmetricError; 
				int					NumberOfCommonStems; 
				int					piecei; 
				int					outputi, outputj; 
				QString				TheMorpheme;
				int					EqualNonStemColumn;
				int					MergeNonStemColumn;
				CParse*				pOneColumn, *qOneColumn; 
				CStringSurrogate	TempCSS; 
				//ofstream			outf; 
				



				pLeftColumn ->Alphabetize();
				pRightColumn ->Alphabetize();

				qLeftColumn ->Alphabetize();
				qRightColumn ->Alphabetize();

				PassNonStemColumnTest = false;
				PassStemColumnTest = false;

				// Check whether LeftColumn is equal
				
				if ( 	(*pLeftColumn) == qLeftColumn	)
				{
					NumberOfSymmetricError =0;
					
					for (piecei =1; piecei<= pRightColumn ->Size(); piecei++)
					{
						TheMorpheme = pRightColumn->GetPiece(piecei).Display();

						TempCSS = CStringSurrogate(TheMorpheme);
						if ( !qRightColumn ->Contains(TempCSS))
						{
							NumberOfSymmetricError++;
						}
					}

					for (piecei =1; piecei<= qRightColumn ->Size(); piecei++)
					{
						TheMorpheme = qRightColumn->GetPiece(piecei).Display();

						TempCSS = CStringSurrogate(TheMorpheme);
						if ( !pRightColumn ->Contains(TempCSS))
						{
							NumberOfSymmetricError++;
						}
					}
				
				
					if (NumberOfSymmetricError <=  MaximumSymmetricError)
					{
						PassNonStemColumnTest = true;
						EqualNonStemColumn = pIndexOfFirstOfNonStemColumns;
						MergeNonStemColumn = pIndexOfFirstOfNonStemColumns + 1; 
					}
					else
					{
						PassNonStemColumnTest = false;
					}
				
				}else if ((*pRightColumn) == qRightColumn)
				{
					NumberOfSymmetricError =0;
					
					for (piecei =1; piecei<= pLeftColumn ->Size(); piecei++)
					{
						TheMorpheme = pLeftColumn->GetPiece(piecei).Display();

						TempCSS = CStringSurrogate(TheMorpheme);
						if ( !qLeftColumn ->Contains(TempCSS) )
						{
							NumberOfSymmetricError++;
						}
					}

					for (piecei =1; piecei<= qLeftColumn ->Size(); piecei++)
					{
						TheMorpheme = qLeftColumn->GetPiece(piecei).Display();

						TempCSS = CStringSurrogate(TheMorpheme);
						if ( !pLeftColumn ->Contains(TempCSS))
						{
							NumberOfSymmetricError++;
						}
					}
				
				
					if (NumberOfSymmetricError <=  MaximumSymmetricError)
					{
						PassNonStemColumnTest = true;
						EqualNonStemColumn = pIndexOfFirstOfNonStemColumns +1;
						MergeNonStemColumn = pIndexOfFirstOfNonStemColumns; 
					}
					else
					{
						PassNonStemColumnTest = false;
					}
				
				}

				if ( !PassNonStemColumnTest)
				{
					continue;
				}

					
				NumberOfCommonStems =0; 

				for (piecei =1; piecei<= pStemColumn ->Size(); piecei++)
				{
					TheMorpheme = pStemColumn->GetPiece(piecei).Display();

					TempCSS = CStringSurrogate(TheMorpheme);
					if ( qStemColumn ->Contains(TempCSS) )
					{
						NumberOfCommonStems++;
					}
				}

				if ( NumberOfCommonStems >= MinimumCommonStem)
				{
					PassStemColumnTest = true;	
				}
				else
				{
					PassStemColumnTest = false;
					continue;
				}

			
				// Now, we collapse these two template together
				CollapsedAnyOne = true;
				AnyChanged = true; 
				if (!DisplayOldDeletedTemplates)
				{
					m_NumberOfDeletedTemplates++;
				}

				qTemplate ->m_IsDeleted = true; 
				// Print the attempted templates
				if ( PrintCollapsedTemplates)
				{
					QString			DisplayOfOneColumn;						
					int				RealTrimSize; 

					QFile file( "CollapseWithAlgorithm1.txt" );
    
					if ( !file.open( QIODevice::WriteOnly | QIODevice::Append) ) 
					{
						QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
						return false;    
					}

					Q3TextStream outf( &file );



                    //outf.open ("CollapseWithAlgorithm1.txt", ofstream::out | ofstream::app);			

					outf << "***************"<<loopnumber<<"********************" <<endl;
					outf << "	Original P-Template:" << endl; 
					outf << "		";

					for ( outputi = 0; outputi < pTemplate ->m_NumberOfColumns; outputi++)
					{
						pOneColumn = pTemplate ->m_Columns[outputi];
						
						DisplayOfOneColumn = QString("{ ");
							
						RealTrimSize = MaximumOutputMorphemesInOneColumn;
						if ( pOneColumn ->Size() < RealTrimSize)
						{
							RealTrimSize = 	pOneColumn ->Size();
						}

						for (outputj =  1; outputj <= RealTrimSize;outputj++)
						{
							DisplayOfOneColumn += pOneColumn ->GetPiece(outputj).Display();
							if ( outputj != RealTrimSize )
							{
								DisplayOfOneColumn += QString(" , ");
							}
						}

						DisplayOfOneColumn += QString(" }");
						outf << DisplayOfOneColumn;
						if ( outputi != pTemplate ->m_NumberOfColumns -1)
						{
							outf << " --> "; 
						}
					}

					outf << endl << endl;
					
					outf << "	Original q-Template:" << endl; 
					outf << "		";

					for ( outputi = 0; outputi < qTemplate ->m_NumberOfColumns; outputi++)
					{
						qOneColumn = qTemplate ->m_Columns[outputi];
						
						DisplayOfOneColumn = QString("{ ");
							
						RealTrimSize = MaximumOutputMorphemesInOneColumn;
						if ( qOneColumn ->Size() < RealTrimSize)
						{
							RealTrimSize = 	qOneColumn ->Size();
						}

						for (outputj =  1; outputj <= RealTrimSize;outputj++)
						{
							DisplayOfOneColumn += qOneColumn ->GetPiece(outputj).Display();
							if ( outputj != RealTrimSize )
							{
								DisplayOfOneColumn += QString(" , ");
							}
						}

						DisplayOfOneColumn += QString(" }");
						outf << DisplayOfOneColumn;
						if ( outputi != qTemplate ->m_NumberOfColumns -1)
						{
							outf << " --> "; 
						}
					}

					outf << endl << endl;

					file.close(); 
				}


				// To Print out the new created words, Keep old words
				StringToParse							OneWordsAndParses; 
				StringToParse							OldAllWordsAndParses;
				StringToParse							NewAllWordsAndParses;
				StringToParse::iterator					StringToParseIt;
				QString									TheWord; 
				CParse*									DumpParse; 
				
			
				// Populate the old word list
				if ( PrintCreatedWords)
				{
					OneWordsAndParses.clear();
					pTemplate ->GetWordsAndParses(OneWordsAndParses); 
			
					for ( StringToParseIt = OneWordsAndParses.begin(); StringToParseIt != OneWordsAndParses.end(); StringToParseIt++)
					{
						TheWord = StringToParseIt.key();
						DumpParse = StringToParseIt.data();
					
						delete DumpParse; 
						
						if ( !OldAllWordsAndParses.contains(TheWord)) 
						{
							OldAllWordsAndParses.insert(TheWord, NULL); 
						}
			
					}


					OneWordsAndParses.clear();
					qTemplate ->GetWordsAndParses(OneWordsAndParses); 
			
					
					for ( StringToParseIt = OneWordsAndParses.begin(); StringToParseIt != OneWordsAndParses.end(); StringToParseIt++)
					{
						
						TheWord = StringToParseIt.key();
						DumpParse = StringToParseIt.data();
						delete DumpParse; 
						
						if ( !OldAllWordsAndParses.contains(TheWord)) 
						{
							OldAllWordsAndParses.insert(TheWord, NULL); 
						}
			
					}

				}
				
				// First, merge not-equal non-stem column from qTemplate into pTemplate
				pOneColumn = pTemplate ->m_Columns[MergeNonStemColumn];
				qOneColumn = qTemplate ->m_Columns[MergeNonStemColumn];

				for (piecei =1; piecei<= qOneColumn ->Size(); piecei++)
				{
					TheMorpheme = qOneColumn->GetPiece(piecei).Display();

					TempCSS = CStringSurrogate(TheMorpheme);
					if ( !pOneColumn ->Contains(TempCSS) )
					{
//						pOneColumn ->AppendInAlphabeticalOrder(TempCSS); 
   						pOneColumn ->Append (TempCSS); 
					}
				}

								


				// Second, merge the stem column from qTemplate into pTemplate
				pOneColumn = pTemplate ->m_Columns[pIndexOfStemColumn];
				qOneColumn = qTemplate ->m_Columns[qIndexOfStemColumn];

				for (piecei =1; piecei<= qOneColumn ->Size(); piecei++)
				{
					TheMorpheme = qOneColumn->GetPiece(piecei).Display();

					TempCSS = CStringSurrogate(TheMorpheme);
					if ( !pOneColumn ->Contains(TempCSS) )
					{
//						pOneColumn ->AppendInAlphabeticalOrder(TempCSS); 
   						pOneColumn ->Append (TempCSS); 
					}
				}

				// Change the flag m_IsNewAfterCollapse1 and m_StemColumnInCollapse1
				pTemplate ->m_IsNewAfterCollapse1 = true; 
				pTemplate ->m_StemColumnInCollapse1 = pIndexOfStemColumn;


				// Print the attempted templates
				if ( PrintCollapsedTemplates)
				{
					QString			DisplayOfOneColumn;						
					int				RealTrimSize; 
					
					QFile file( "CollapseWithAlgorithm1.txt" );
    
					if ( !file.open( QIODevice::WriteOnly | QIODevice::Append) ) 
					{
						QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
						return false;    
					}

					Q3TextStream outf( &file );



					//outf.open ("CollapseWithAlgorithm1.txt", ofstream::out | ofstream::app);			
					outf << "	Collapsed -Template:" << endl; 
					outf << "		";

					for ( outputi = 0; outputi < pTemplate ->m_NumberOfColumns; outputi++)
					{
						pOneColumn = pTemplate ->m_Columns[outputi];
						
						DisplayOfOneColumn = QString("{ ");
							
						RealTrimSize = MaximumOutputMorphemesInOneColumn;
						if ( pOneColumn ->Size() < RealTrimSize)
						{
							RealTrimSize = 	pOneColumn ->Size();
						}

						for (outputj =  1; outputj <= RealTrimSize;outputj++)
						{
							DisplayOfOneColumn += pOneColumn ->GetPiece(outputj).Display();
							if ( outputj != RealTrimSize )
							{
								DisplayOfOneColumn += QString(" , ");
							}
						}

						DisplayOfOneColumn += QString(" }");
						outf << DisplayOfOneColumn;
						if ( outputi != pTemplate ->m_NumberOfColumns -1)
						{
							outf << " --> "; 
						}
					}

					outf << endl << endl;
					file.close(); 
				}

				// Populate the new word list
				if ( PrintCreatedWords)
				{
					OneWordsAndParses.clear();
					pTemplate ->GetWordsAndParses(OneWordsAndParses); 
			
					
					for ( StringToParseIt = OneWordsAndParses.begin(); StringToParseIt != OneWordsAndParses.end(); StringToParseIt++)
					{
						TheWord = StringToParseIt.key();
						DumpParse = StringToParseIt.data(); 
						delete DumpParse; 
						
						if ( !NewAllWordsAndParses.contains(TheWord)) 
						{
							NewAllWordsAndParses.insert(TheWord, NULL); 
						}
			
					}
					
				}


				// Print out the new created words
				if ( PrintCreatedWords)
				{
					QFile file( "CollapseWithAlgorithm1.txt" );
    
					if ( !file.open( QIODevice::WriteOnly | QIODevice::Append) ) 
					{
						QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
						return false;    
					}

					Q3TextStream outf( &file );

					//outf.open ("CollapseWithAlgorithm1.txt", ofstream::out | ofstream::app);			
					outf << "	New-Created Words:" << endl; 
					outf << "		" << "{";

					for ( StringToParseIt = NewAllWordsAndParses.begin(); StringToParseIt != NewAllWordsAndParses.end(); StringToParseIt++)
					{
				
						TheWord = StringToParseIt.key();

						if ( !OldAllWordsAndParses.contains(TheWord)) 
						{
							outf << " "<< TheWord <<" ,"; 
						}

					}

					outf << "}" << endl << endl <<endl; 

					file.close();
				}


				break; 
			}
			

			if ( CollapsedAnyOne)
			{
				break; 
			}
		}

	}
	
	return AnyChanged; 

}


void CTemplateCollection::SetSwitchOfSortingValue(bool value)
{
	for (int i = 0; i < GetCount(); ++i) {
		CTemplate* pTemplate = GetAtSort(i);
		pTemplate ->SetSwitchOfSortingValue(value); 
	}
} 



void	CTemplateCollection::AbsorbWords1(int Loopi)
{

	
	bool								Conservative = false; 
	int									MiniMumPrefixOrSuffixNeedToBeAbsorbed = 2;
	int									UnTouchedTopTemplate = 5; 
	int									i, j; 
	int									TemplateIndex; 
	CTemplate* qTemplate;
	StringToParse						pWordsAndParses;
	StringToParse						qWordsAndParses;
	StringToParse::iterator				StringToParseIt;
	StringToInt							CommonWords; 
	QString								oneWord;
	CParse*								pParse, *qParse; 
	bool								Contained; 


	TemplateIndex =0; 
	for (i = 1; i < GetCount()-1; i++) {
		CTemplate* pTemplate = GetAtSort(i);
		
		if (pTemplate ->m_IsDeleted)
		{
			continue;
		}

		TemplateIndex++; 
		if ( TemplateIndex <= UnTouchedTopTemplate)
		{
			continue; 
		}

		pWordsAndParses.clear(); 
		pTemplate ->GetWordsAndParses(pWordsAndParses); 

		CommonWords.clear(); 

		for ( j=0; j< i; j++)
		{
			qTemplate = GetAtSort(j);
		
			if (qTemplate ->m_IsDeleted)
			{
				continue;
			}

			// Check the common word between pTemplate and qTemplate
			qWordsAndParses.clear(); 
			qTemplate ->GetWordsAndParses(qWordsAndParses);
			
			
			for ( StringToParseIt= qWordsAndParses.begin(); StringToParseIt != qWordsAndParses.end(); StringToParseIt++)
			{
				oneWord = StringToParseIt.key();
				qParse = StringToParseIt.data(); 
				
				if ( pWordsAndParses.contains(oneWord)) 
				{
					pParse = pWordsAndParses[oneWord];
					Contained = OneParseContainAnother(qParse, pParse); 	
					
					if (!Contained) continue; 

					// We found this word in pParse can be absorbed to higher ranking template
					CommonWords.insert(oneWord, 1);
				
				}
				else
				{
					continue; 
				}
			
			
			}

			// Clean the  qWordsAndParse
			
			for ( StringToParseIt= qWordsAndParses.begin(); StringToParseIt != qWordsAndParses.end(); StringToParseIt++)
			{
				qParse = StringToParseIt.data();
				delete qParse;
			}

		}

		// Now, for the template p, we have got the Common Words between pTemplate and all qTemplates

		if ( CommonWords.count() == 0)
		{
			// Clean the  pWordsAndParses
			for ( StringToParseIt= pWordsAndParses.begin(); StringToParseIt != pWordsAndParses.end(); StringToParseIt++)
			{
				pParse = StringToParseIt.data(); 
				delete pParse;
			}

			continue; 
		}


		// Next, we deal with these common words for pTemplate

		pTemplate ->AdjustMeAfterAbsorb1(CommonWords,Conservative, MiniMumPrefixOrSuffixNeedToBeAbsorbed, Loopi ); 
		
		// Clean the  pWordsAndParses
		for ( StringToParseIt= pWordsAndParses.begin(); StringToParseIt != pWordsAndParses.end(); StringToParseIt++)
		{
			pParse = StringToParseIt.data(); 
			delete pParse;
		}


	}




}

// Whether qParse contains/Covers pParse
bool	CTemplateCollection::OneParseContainAnother(CParse* qParse, CParse* pParse)
{
	bool			Success, FoundOneCut; 
	int				oneCutLoc, PossibleLoc; 	

	Success = true;
	for (int i = 1; i<= pParse ->Size(); i++) 
	{
		oneCutLoc = pParse ->GetPieceLoc(i);
		
		FoundOneCut = false; 
		for ( int j=1; j<= qParse ->Size(); j++)
		{
			PossibleLoc = 	qParse ->GetPieceLoc(j);

			if ( oneCutLoc == PossibleLoc) 
			{
				FoundOneCut = true; 
				break;
			}

		}

		if ( !FoundOneCut)
		{
			Success = false;
			break; 
		}

	}

	return Success; 

} 


void	CTemplateCollection::FindMorphemePrefixOrSuffixWithParadigmaticGraph(int Loopi)
{
	int							MaximumSizeOfStemColumn = 5; 

	for (int i = 0; i < GetCount(); i++) {
		CTemplate* pTemplate = GetAtSort(i);

		if ( pTemplate ->m_IsDeleted) continue; 

		pTemplate ->FindMorphemePrefixOrSuffixWithParadigmaticGraph(Loopi, MaximumSizeOfStemColumn, m_GlobalNodeStickNess2,  m_GlobalStickNess2, m_TotalGlobalStickNess2, m_TotalWord2);  
	
	}


} 

void	CTemplateCollection::CutMtCorpusWithMorphologyAnalyses(QString inFileName, QString outFileName, StringToPtrCStem&	MorphologyCuts, int Strategy)
{

	if ( Strategy == 1) // Just take the morphemes, don't care its layers or location
	{
		QFile inFile( inFileName );
		if ( inFile.open( QIODevice::ReadOnly ) )
		{
        
		}
		else
		{
			return; 
		}
		

		QFile oFile( outFileName );
		if ( oFile.open( QIODevice::WriteOnly  ) )
		{

		}
		else
		{
			return; 
		}
		
		
		Q3TextStream				instream( &inFile );
		Q3TextStream				ostream( &oFile );
		QString					oneLine;

		// Unicode or ASCII encoding?
		instream.setEncoding ( Q3TextStream::Unicode);
		ostream.setEncoding ( Q3TextStream::Unicode);

		
		// Read these sentences in...
		while( !instream.atEnd() )
		{
			oneLine = instream.readLine(); 
			oneLine = oneLine.lower(); 

			QString				oneWord;
			QString				outWord; 
			bool				endOfLine; 
			int					Pos; 
			CStem*				theCStem; 				
		
			// Strip the start and end white space
		
			oneLine = oneLine.simplifyWhiteSpace (); 

			if ( oneLine.length() ==0)
			{
				ostream <<" " <<endl; 
				continue; 
			}

			endOfLine = false;
			while ( !endOfLine)
			{
				Pos = oneLine.find(QString(" ")); 
			
				if ( Pos != -1)
				{
					oneWord = oneLine.left(Pos);
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						outWord = theCStem ->Display(QChar(' ')); 

					}
					else
					{
						outWord = oneWord; 
					}
			
					ostream << outWord <<" "; 

					oneLine = oneLine.right(oneLine.length() - Pos-1);
				}
				else
				{
					oneWord = oneLine; 
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						outWord = theCStem ->Display(QChar(' ')); 	
					}
					else
					{
						outWord = oneWord; 
					}
					
					ostream << outWord; 
					endOfLine = true; 
					break; 
				}

			}


			ostream <<endl; 
		}


		inFile.close();
		oFile.close(); 

		return; 	
	}

	if ( Strategy == 2) // Take the morphemes, make difference for begin and end
	{
		QFile inFile( inFileName );
		if ( inFile.open( QIODevice::ReadOnly ) )
		{
        
		}
		else
		{
			return; 
		}
		

		QFile oFile( outFileName );
		if ( oFile.open( QIODevice::WriteOnly  ) )
		{

		}
		else
		{
			return; 
		}
		
		
		Q3TextStream				instream( &inFile );
		Q3TextStream				ostream( &oFile );
		QString					oneLine;

		// Unicode or ASCII encoding?
		instream.setEncoding ( Q3TextStream::Unicode);
		ostream.setEncoding ( Q3TextStream::Unicode);

		
		// Read these sentences in...
		while( !instream.atEnd() )
		{
			oneLine = instream.readLine(); 
			oneLine = oneLine.lower(); 

			QString				oneWord;
			QString				outWord; 
			QString				onePiece; 
			bool				endOfLine; 
			int					Pos; 
			CStem*				theCStem; 				
			int					i; 
			int					StemLayer; 
			int					StemSize; 
		

			// Strip the start and end white space
		
			oneLine = oneLine.simplifyWhiteSpace (); 

			if ( oneLine.length() ==0)
			{
				ostream <<" " <<endl; 
				continue; 
			}

			endOfLine = false;
			while ( !endOfLine)
			{
				Pos = oneLine.find(QString(" ")); 
			
				if ( Pos != -1)
				{
					oneWord = oneLine.left(Pos);
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						
						if ( theCStem ->Size() == 1)
						{
							outWord = oneWord; 
						}
						else
						{
						
							// For Stem, we keep it being
							StemLayer =1;
							StemSize =0; 

							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display();
								if ( static_cast <int> (onePiece.length()) >= StemSize ) //%%% complaining signed-unsigned; type cast to fix warning
								{
									StemLayer =i;
									StemSize =onePiece.length(); 
								}
							
							}
							
							
							outWord = QString("");
							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display(); 
								
								if ( (i== 1) && (i== theCStem ->Size()))
								{
									QMessageBox::information ( NULL, "Debug", "Impossible Here!", "OK" );	
									return; 
								}

								if (( i == 1) && (i != StemLayer))
								{
									onePiece = onePiece + "_"; 
									outWord = outWord + onePiece+ " ";
								} 
								else if ( (i == theCStem ->Size()) && (i != StemLayer))
								{
									onePiece = "_" + onePiece; 
									outWord = outWord + onePiece;
								}
								else if ( (i == theCStem ->Size()) && (i == StemLayer))
								{
									outWord = outWord + onePiece;
								}
								else
								{
									outWord = outWord + onePiece + " ";
								}

								
							
							}
						}
						
					}
					else
					{
						outWord = oneWord; 
					}
			
					ostream << outWord <<" "; 

					oneLine = oneLine.right(oneLine.length() - Pos-1);
				}
				else
				{
					oneWord = oneLine; 
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						
						if ( theCStem ->Size() == 1)
						{
							outWord = oneWord; 
						}
						else
						{
						
							// For Stem, we keep it being
							StemLayer =1;
							StemSize =0; 

							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display();
								if ( static_cast <int> (onePiece.length()) >= StemSize ) //%%% length(); gives unsigned
								{
									StemLayer =i;
									StemSize =onePiece.length(); 
								}
							
							}
							
							
							outWord = QString("");
							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display(); 
								
								if ( (i== 1) && (i== theCStem ->Size()))
								{
									QMessageBox::information ( NULL, "Debug", "Impossible Here!", "OK" );	
									return; 
								}

								if (( i == 1) && (i != StemLayer))
								{
									onePiece = onePiece + "_"; 
									outWord = outWord + onePiece+ " ";
								} 
								else if ( (i == theCStem ->Size()) && (i != StemLayer))
								{
									onePiece = "_" + onePiece; 
									outWord = outWord + onePiece;
								}
								else if ( (i == theCStem ->Size()) && (i == StemLayer))
								{
									outWord = outWord + onePiece;
								}
								else
								{
									outWord = outWord + onePiece + " ";
								}				
							
							}
						}
						
					}
					else
					{
						outWord = oneWord; 
					}
					
					ostream << outWord; 
					endOfLine = true; 
					break; 
				}

			}


			ostream <<endl; 
		}


		inFile.close();
		oFile.close(); 

		return; 	
	}

	if ( Strategy == 3) // Take the morphemes, make difference for its location
	{
		QFile inFile( inFileName );
		if ( inFile.open( QIODevice::ReadOnly ) )
		{
        
		}
		else
		{
			return; 
		}
		

		QFile oFile( outFileName );
		if ( oFile.open( QIODevice::WriteOnly  ) )
		{

		}
		else
		{
			return; 
		}
		
		
		Q3TextStream				instream( &inFile );
		Q3TextStream				ostream( &oFile );
		QString					oneLine;

		// Unicode or ASCII encoding?
		instream.setEncoding ( Q3TextStream::Unicode);
		ostream.setEncoding ( Q3TextStream::Unicode);

		
		// Read these sentences in...
		while( !instream.atEnd() )
		{
			oneLine = instream.readLine(); 
			oneLine = oneLine.lower(); 

			QString				oneWord;
			QString				outWord; 
			QString				onePiece; 
			bool				endOfLine; 
			int					Pos; 
			CStem*				theCStem; 				
			int					i; 
			int					StemLayer; 
			int					StemSize; 
		

			// Strip the start and end white space
		
			oneLine = oneLine.simplifyWhiteSpace (); 

			if ( oneLine.length() ==0)
			{
				ostream <<" " <<endl; 
				continue; 
			}

			endOfLine = false;
			while ( !endOfLine)
			{
				Pos = oneLine.find(QString(" ")); 
			
				if ( Pos != -1)
				{
					oneWord = oneLine.left(Pos);
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						
						if ( theCStem ->Size() == 1)
						{
							outWord = oneWord; 
						}
						else
						{
						
							// For Stem, we keep it being
							StemLayer =1;
							StemSize =0; 

							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display();
								if ( static_cast <int> (onePiece.length()) >= StemSize ) //%%% length(); gives unsigned
								{
									StemLayer =i;
									StemSize =onePiece.length(); 
								}
							
							}
							
							
							outWord = QString("");
							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display(); 
								
								if ( (i== 1) && (i== theCStem ->Size()))
								{
									QMessageBox::information ( NULL, "Debug", "Impossible Here!", "OK" );	
									return; 
								}

								if (( i == 1) && (i != StemLayer))
								{
									onePiece = onePiece + "_" + QString("%1").arg(i); 
									outWord = outWord + onePiece+ " ";
								} 
								else if ( (i == theCStem ->Size()) && (i != StemLayer))
								{
									onePiece = onePiece + "_" + QString("%1").arg(i); 
									outWord = outWord + onePiece;
								}
								else if ( (i == theCStem ->Size()) && (i == StemLayer))
								{
									outWord = outWord + onePiece;
								}
								else
								{
									if ( i == StemLayer)
									{
										outWord = outWord + onePiece + " ";
									}
									else
									{
										onePiece = onePiece + "_" + QString("%1").arg(i); 
										outWord = outWord + onePiece + " ";
									}
								}	

								
							
							}
						}
						
					}
					else
					{
						outWord = oneWord; 
					}
			
					ostream << outWord <<" "; 

					oneLine = oneLine.right(oneLine.length() - Pos-1);
				}
				else
				{
					oneWord = oneLine; 
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						
						if ( theCStem ->Size() == 1)
						{
							outWord = oneWord; 
						}
						else
						{
						
							// For Stem, we keep it being
							StemLayer =1;
							StemSize =0; 

							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display();
								if ( static_cast <int> (onePiece.length()) >= StemSize ) //%%% length(); gives unsigned
								{
									StemLayer =i;
									StemSize =onePiece.length(); 
								}
							
							}
							
							
							outWord = QString("");
							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display(); 
								
								if ( (i== 1) && (i== theCStem ->Size()))
								{
									QMessageBox::information ( NULL, "Debug", "Impossible Here!", "OK" );	
									return; 
								}

								if (( i == 1) && (i != StemLayer))
								{
									onePiece = onePiece + "_" + QString("%1").arg(i); 
									outWord = outWord + onePiece+ " ";
								} 
								else if ( (i == theCStem ->Size()) && (i != StemLayer))
								{
									onePiece = onePiece + "_" + QString("%1").arg(i); 
									outWord = outWord + onePiece;
								}
								else if ( (i == theCStem ->Size()) && (i == StemLayer))
								{
									outWord = outWord + onePiece;
								}
								else
								{
									if ( i == StemLayer)
									{
										outWord = outWord + onePiece + " ";
									}
									else
									{
										onePiece = onePiece + "_" + QString("%1").arg(i); 
										outWord = outWord + onePiece + " ";
									}
								}	

								
							
							}
						}
						
					}
					else
					{
						outWord = oneWord; 
					}
					
					ostream << outWord; 
					endOfLine = true; 
					break; 
				}

			}


			ostream <<endl; 
		}


		inFile.close();
		oFile.close(); 

		return; 	
	}

	if ( Strategy == 4) // Take the morphemes, make difference for its relative location to Stemlayer
	{
		QFile inFile( inFileName );
		if ( inFile.open( QIODevice::ReadOnly ) )
		{
        
		}
		else
		{
			return; 
		}
		

		QFile oFile( outFileName );
		if ( oFile.open( QIODevice::WriteOnly  ) )
		{

		}
		else
		{
			return; 
		}
		
		
		Q3TextStream				instream( &inFile );
		Q3TextStream				ostream( &oFile );
		QString					oneLine;

		// Unicode or ASCII encoding?
		instream.setEncoding ( Q3TextStream::Unicode);
		ostream.setEncoding ( Q3TextStream::Unicode);

		
		// Read these sentences in...
		while( !instream.atEnd() )
		{
			oneLine = instream.readLine(); 
			oneLine = oneLine.lower(); 

			QString				oneWord;
			QString				outWord; 
			QString				onePiece; 
			bool				endOfLine; 
			int					Pos; 
			CStem*				theCStem; 				
			int					i; 
			int					StemLayer; 
			int					StemSize; 
		

			// Strip the start and end white space
		
			oneLine = oneLine.simplifyWhiteSpace (); 

			if ( oneLine.length() ==0)
			{
				ostream <<" " <<endl; 
				continue; 
			}

			endOfLine = false;
			while ( !endOfLine)
			{
				Pos = oneLine.find(QString(" ")); 
			
				if ( Pos != -1)
				{
					oneWord = oneLine.left(Pos);
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						
						if ( theCStem ->Size() == 1)
						{
							outWord = oneWord; 
						}
						else
						{
						
							// For Stem, we keep it being
							StemLayer =1;
							StemSize =0; 

							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display();
								if ( static_cast <int> (onePiece.length()) >= StemSize ) //%%% length(); gives unsigned
								{
									StemLayer =i;
									StemSize =onePiece.length(); 
								}
							
							}
							
							
							outWord = QString("");
							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display(); 
								
								if ( (i== 1) && (i== theCStem ->Size()))
								{
									QMessageBox::information ( NULL, "Debug", "Impossible Here!", "OK" );	
									return; 
								}

								if (( i == 1) && (i != StemLayer))
								{
									onePiece = onePiece + "_-" + QString("%1").arg(StemLayer -i); 
									outWord = outWord + onePiece+ " ";
								} 
								else if ( (i == theCStem ->Size()) && (i != StemLayer))
								{
									onePiece = onePiece + "_+" + QString("%1").arg(i-StemLayer); 
									outWord = outWord + onePiece;
								}
								else if ( (i == theCStem ->Size()) && (i == StemLayer))
								{
									outWord = outWord + onePiece;
								}
								else
								{
									if ( i == StemLayer)
									{
										outWord = outWord + onePiece + " ";
									}
									else
									{
										if ( i > StemLayer )
										{
											onePiece = onePiece + "_+" + QString("%1").arg(i- StemLayer); 
											outWord = outWord + onePiece + " ";					
										}
										else
										{
											onePiece = onePiece + "_-" + QString("%1").arg(StemLayer -i); 
											outWord = outWord + onePiece + " ";
										}
									}
								}	

								
							
							}
						}
						
					}
					else
					{
						outWord = oneWord; 
					}
			
					ostream << outWord <<" "; 

					oneLine = oneLine.right(oneLine.length() - Pos-1);
				}
				else
				{
					oneWord = oneLine; 
					
					if ( MorphologyCuts.contains(oneWord))
					{
						theCStem = 	MorphologyCuts[oneWord];
						
						if ( theCStem ->Size() == 1)
						{
							outWord = oneWord; 
						}
						else
						{
						
							// For Stem, we keep it being
							StemLayer =1;
							StemSize =0; 

							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display();
								if ( static_cast <int> (onePiece.length()) >= StemSize ) //%%% length(); gives unsigned
								{
									StemLayer =i;
									StemSize =onePiece.length(); 
								}
							
							}
							
							
							outWord = QString("");
							for ( i=1; i<= theCStem ->Size(); i++)
							{
								onePiece = 	theCStem ->GetPiece(i).Display(); 
								
								if ( (i== 1) && (i== theCStem ->Size()))
								{
									QMessageBox::information ( NULL, "Debug", "Impossible Here!", "OK" );	
									return; 
								}

								if (( i == 1) && (i != StemLayer))
								{
									onePiece = onePiece + "_-" + QString("%1").arg(StemLayer -i); 
									outWord = outWord + onePiece+ " ";
								} 
								else if ( (i == theCStem ->Size()) && (i != StemLayer))
								{
									onePiece = onePiece + "_+" + QString("%1").arg(i-StemLayer); 
									outWord = outWord + onePiece;
								}
								else if ( (i == theCStem ->Size()) && (i == StemLayer))
								{
									outWord = outWord + onePiece;
								}
								else
								{
									if ( i == StemLayer)
									{
										outWord = outWord + onePiece + " ";
									}
									else
									{
										if ( i > StemLayer )
										{
											onePiece = onePiece + "_+" + QString("%1").arg(i- StemLayer); 
											outWord = outWord + onePiece + " ";					
										}
										else
										{
											onePiece = onePiece + "_-" + QString("%1").arg(StemLayer -i); 
											outWord = outWord + onePiece + " ";
										}
									}
								}	

								
							
							}
						}
						
					}
					else
					{
						outWord = oneWord; 
					}
					
					ostream << outWord; 
					endOfLine = true; 
					break; 
				}

			}


			ostream <<endl; 
		}


		inFile.close();
		oFile.close(); 

		return; 	
	}

}


/////////////////////////////////////////////////////////////////
//// FindStringEditDistance
void CTemplateCollection::FindAllEditDistances(CLexicon* MyLexicon, CWordCollection* MyWords )
{ 


    int						NumberOfWords; 
 	int						MinimumSize			= 5;	
	int						ScoreThreshold		= 8; // was 6
	int						MaximumNumberOfLetterDifferences = 9;
	int						MinimumNumberOfCommonLetters = 5;
	CStem*					pWord, 
							*qWord;
 
	CParse					Substitution; 
	CParse					Context;
	double					Score;
	QStringToTemplate	    Templates;
	int						Counter				= 1; 
	int						TotalNumber; 
	int						DebugPair			= 0; 

 	NumberOfWords			= MyWords ->GetCount(); // Fix a bug -yu hu 02/10/2006

	MyLexicon->GetDocument()->setStatusBar1(QString("StringEdit:FindAllEditDistances"));

    TotalNumber				= NumberOfWords - 1;

	if ( MyLexicon->LogFileOn() && MyLexicon->GetLogFileStream() ) 
	{ 
 		*MyLexicon->GetLogFileStream()  <<		endl << 
				"<h3 class=blue>"												<<
					"String comparisons"				<< 
				"</h3>"															<< endl << 
					StartTable<< 
					StartTableRow << 
					MakeTableHeader("String 1") << 
					MakeTableHeader("String 2") <<
					MakeTableHeader("something else") << 
					EndTableRow;			

    }
	
 
	//	loop through all members of the collection... 
	for (int i = 0; i < NumberOfWords - 1; i++)
	{
		pWord = MyWords ->GetAt(i);
		
		if (pWord->GetKeyLength() < MinimumSize ) continue;

		
		for (int j = i+1; j < NumberOfWords; j++)
		{
			qWord		= MyWords ->GetAt(j);
			
			if (qWord->GetKeyLength() < MinimumSize ) continue;

			// -------  Our tests to see if these two words, pWord and qWord, are similar enough ----- //
			// -------  to be worth testing with string edit distance                           ------ //
			int Overlap = OverlapOfTwoAlphabetizedLists ( pWord->GetAlphabetizedForm(), qWord->GetAlphabetizedForm() );
			if (Overlap < MinimumNumberOfCommonLetters ) continue;
	
			int Diff = DifferencesOfTwoAlphabetizedLists ( pWord->GetAlphabetizedForm(), qWord->GetAlphabetizedForm() );
			if ( Diff > MaximumNumberOfLetterDifferences ) continue;
			//	--------  end of tests  -----------------------------------------------------------   //

			std::auto_ptr<CAlignment> pAlignment(
					new CAlignment(pWord, qWord));

			Score		= pAlignment->FindStringEditDistance();

						
			if (  Score < ScoreThreshold &&  pAlignment->m_Slips == 1 	)
			{				
				Substitution = pAlignment->FindSubstitution();
 				Context      = pAlignment->FindContext();
//				Substitution = pAlignment->FindSubstitution( );

  			    if ( MyLexicon->LogFileOn() ) 
                { 
				    *MyLexicon->GetLogFileStream()  << endl << 
				    StartTableRow <<
				    TableData (Substitution.GetPiece(1).Display()) <<
				    TableData (Context) <<
 				    EndTableRow <<

				    StartTableRow <<
				    TableData ( Substitution.GetPiece(2).Display() ) <<
  				    EndTableRow;                 
                }		


				QMap<QString, CTemplate*>::iterator iter =
					Templates.find(Context.GetKey().Display());
				if (iter != Templates.end()) {
					CTemplate* pTemplate = *iter;

					pTemplate->AddToColumn ( Substitution, pTemplate->GetVerticalColumn() );
					pTemplate->IncrementCorpusCount(1);
					pTemplate->AddAlignment(pAlignment.get());
					//if ( Lexicon->LogFileOn() ) {*Lexicon->GetLogFile() << endl <<"Already present  " << Context.GetKey(); }
				} else {
					std::auto_ptr<CTemplate> new_template(
						new CTemplate(pAlignment.get()));
					CTemplate* pTemplate = new_template.get();

					Templates.insert(Context.GetKey().Display(),
						new_template.release());
					pTemplate->SetCorpusCount(1);
					pTemplate->AddAlignment(pAlignment.get());
				}
			}
		}

		MyLexicon->GetDocument()->CountDownOnStatusBar(Counter++, TotalNumber/20*20, TotalNumber/20);

	}

	
	// Now go through the templates, and add them to the real collection // 
	QStringToTemplate::Iterator				QStringToTemplateIt; 
	
	for (QMap<QString, CTemplate*>::const_iterator iter =
				Templates.constBegin();
			iter != Templates.constEnd();
			++iter) {
		QString Key = iter.key();
		CTemplate* pTemplate = iter.value();

		++DebugPair;
		CTemplate* qTemplate = AddTemplate(pTemplate);
		qTemplate->SetCorpusCount(pTemplate->GetCorpusCount());
		delete pTemplate;
	}

	MyLexicon->GetDocument()->setStatusBar1(QString(""));
	MyLexicon->GetDocument()->EndCountDown();
	if ( MyLexicon->LogFileOn() ) 
		{ 
			* MyLexicon->GetLogFileStream()  <<	endl << EndTable;
		}


}


