// Implementation of CPhoneCollection methods
// Copyright © 2009 The University of Chicago
#include "PhoneCollection.h"

#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "MonteCarlo.h"
#include "Stem.h"
#include "BiphoneCollection.h"
#include "WordCollection.h"
#include "log2.h"

CPhoneCollection::CPhoneCollection( CWordCollection* WC)
{
	m_MyWords			= WC;
	m_MyBiphones		= new CBiphoneCollection(WC);
	m_expMI				= NULL;
	m_expMIFromBoundary = NULL;
	m_expMIToBoundary	= NULL;

}	
CPhoneCollection::~CPhoneCollection()
{
	delete m_MyBiphones;
	
}	
double	CPhoneCollection:: GetSumOfMyMIs()  { return m_MyBiphones->GetSumOfMyMIs(); }	

void CPhoneCollection::CountPhonesAndBiphonesInWord( CStem* pStem, eTier WhichTier)
{
	int i;
	CPhone*			pPhone, *prevPhone; 
	prevPhone = NULL;
	CParse*			pThisString;
	QString			Biphone;
 
	if (WhichTier == TIER_1) 
	{
		pThisString = pStem->GetPhonology_Tier1();
	}
	else if (WhichTier == TIER_1_SKELETON)
	{
		pThisString = pStem->GetPhonology_Tier1_Skeleton();
	}
	else
	{
		pThisString = pStem->GetPhonology_Tier2();
	}


	QString temp2; temp2 = pThisString->Display();
	QString temp3; temp3 = pStem->Display();
	Q_ASSERT (pThisString->Size());
	if (pThisString->Size()==0) return;
	QString temp = pThisString->Display();


  
	for (i=1; i <=  pThisString->Size(); i++)
	{
		QString temp2 = pThisString->GetPiece(i).Display();
		
		if ( i						 == pThisString->Size() &&		// these conditions define a # at the end of a string like #dog#
			 pThisString->GetPiece(1).Display() == QString("#")					&& 
			 pThisString->GetPiece(i).Display() == QString("#") 
			)
			{ 
				pPhone = *this ^= pThisString->GetPiece(i);  
			}
			else
			{
				pPhone = *this << pThisString->GetPiece(i);  
			}		
			if (i>1)
			{
				m_MyBiphones->Insert (prevPhone, pPhone);
			}
			prevPhone = pPhone;
	}





 
}

void CPhoneCollection::Normalize()
{
	int i;
	CPhone*			pPhone;
	CBiphone*		pBiphone;
	double			MI, Freq;

	for (i = 0; i < GetCount(); i++)
	{
		pPhone = GetAt(i);
		pPhone->m_Frequency = pPhone->GetCorpusCount() / (double) m_CorpusCount;
		pPhone->m_LogFreq = -1 * base2log( pPhone->m_Frequency );
	}
	

 	Q3DictIterator<CBiphone> it (*m_MyBiphones);
	for ( ; it.current(); ++it)
	{	
 		pBiphone = it.current();
		Freq = (double) pBiphone->GetCorpusCount() / m_MyBiphones->GetTotalCount(); 
		pBiphone->m_Freq = Freq;
 		pBiphone->m_LogFreq =  -1 * base2log ( Freq );
		pBiphone->m_CondProb = Freq / (double) pBiphone->m_MyFirst->m_Frequency;
		pBiphone->m_LogCondProb = -1 * base2log ( pBiphone->m_CondProb );
		
		MI = base2log ( Freq / ( pBiphone->m_MyFirst->m_Frequency * pBiphone->m_MySecond->m_Frequency ) );
		
		pBiphone->m_MI = MI;
		pBiphone->m_WMI = MI * pBiphone->GetCorpusCount();
		pBiphone->m_NormalizedMI = pBiphone->m_MI - m_MyBiphones->m_Z_biphones;		
	}
	m_MyBiphones->ComputeZ_MI(); 
 	
	for (it.toFirst() ; it.current(); ++it)
	{	
 		pBiphone = it.current();
 		pBiphone->m_NormalizedMI = (m_MyBiphones->m_Z_biphones)- (pBiphone->m_MI) ;	
	}
}

void CPhoneCollection::ListDisplay( Q3ListView* pView )
{
   CPhone* pPhone;

   pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);
  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  //    Add Column headers
  pView->addColumn( "Phone" );
  pView->addColumn( "Count" );
  pView->addColumn( "+LogProb" ); 
  pView->addColumn( "Prob" ); 

  if (m_SortValidFlag == FALSE)
  {
    Sort(KEY);
  }
 
  m_MyWords->GetLexicon()->GetDocument()->setStatusBar1( "Creating phone list for display" );
  m_MyWords->GetLexicon()->GetDocument()->BeginCountDown();
	
 	  // Display all items
  for (int i = 0; i < (int) GetCount(); i++)
  {
     pPhone = GetAtSort(i);
     pPhone->PhoneListDisplay( pView );
     m_MyWords->GetLexicon()->GetDocument()->CountDownOnStatusBar(i, GetCount());
  }


  m_MyWords->GetLexicon()->GetDocument()->setStatusBar1( "" );
  m_MyWords->GetLexicon()->GetDocument()->EndCountDown();   
}





 
void CPhoneCollection::PopulateMonteCarlo( MonteCarlo* pMyMonteCarlo)
{	
	QString				FirstPhone;
	MonteCarlo*			qMonteCarlo;
	int					Size;
	int					NumberOfBigramsFound = 0;
	CPhone*				pPhone, *qPhone;
	CBiphone*			pBiphone;
	int					j;
	// first, Unigram frequencies:		
	for (int i = 0; i < GetSize(); i++)
	{
		pPhone = GetAt(i);
		pMyMonteCarlo->StockDictionary( pPhone->Display(), pPhone->m_Frequency, i );	
	}

	static const QString FileName = "c:\\LxaDeleteMe.txt";
	QFile file( FileName );
	Q3TextStream outf( &file );
	outf.setEncoding( Q3TextStream::Unicode );

	// Now Bigram frequencies:
	if (pMyMonteCarlo->m_ModelType == BIGRAM)
	{		
		for (int i = 0; i < GetSize(); i++) // iterate throught the phonemes...
		{
			pPhone			= GetAt(i);
			FirstPhone		= pPhone->Display();
			Size			= GetSize();
			qMonteCarlo		= new MonteCarlo ( Size, FirstPhone );
			pMyMonteCarlo	->GetMyBigrams()->insert ( FirstPhone, qMonteCarlo ); // this is a QDict within the MonteCarlo, for subMonteCarlos for each phone
			NumberOfBigramsFound = 0;
			
			outf << endl << FirstPhone << endl;

			for (j = 0; j < Size; j++)  // iterate through the phonemes, for the second phoneme of this bigram
			{				 
				qPhone		= GetAt(j);
				pBiphone	= m_MyBiphones->GetBiphone ( pPhone, qPhone );
				if (pBiphone)
				{
					qMonteCarlo->StockDictionary( qPhone->Display(), pBiphone->m_CondProb, j);
					NumberOfBigramsFound++;
				}			 
			}
			qMonteCarlo->SetSize ( NumberOfBigramsFound );
			qMonteCarlo->Normalize();				
			//qMonteCarlo->Dump( &outf );
			 
			


			

		}
	}

	pMyMonteCarlo->Normalize();



	


	file.close();


}

void ComputeStringAgreementAndDisagreement(
	CLParse* string1, CLParse* string2,
	double& agreement_unigram, double& agreement_bigram,
	double& disagreement_unigram, double& disagreement_bigram)
{
	struct not_implemented { };
	throw not_implemented();

	static_cast<void>(string1);
	static_cast<void>(string2);
	static_cast<void>(agreement_unigram);
	static_cast<void>(agreement_bigram);
	static_cast<void>(disagreement_unigram);
	static_cast<void>(disagreement_bigram);

//	QString string1_alpha = string1->GetAlphabetizedForm();
//	QString string2_alpha = string2->GetAlphabetizedForm();
//	int i,j;
//	j = 1;
//	// first calculate unigram overlap and non-overlap costs.
//	for (i=1; i <= string1->Size(); i++)
//	{
//		if (string1_alpha[i] == string2_alpha[j] )
//		{
//			agreement_unigram += ;
//		}
//		else if (string1_alpha[i] < string2_alpha[j])
//		{
//			disagreement_unigram += ;
//			if (i==string1->Size()){
//				break;
//			}
//			i++;
//		}
//		else
//		{
//			disagreement_unigram += ;
//			if (j==string1->Size()){
//				break;
//			}
//			j++;
//		}
//	}
//	if (i < string1->Size()){
//		for (; i <= string1->Size(); i++){
//			disagreement_unigram +=  ;
//		}
//	}
//	if (j < string1->Size()){
//		for (; j <= string1->Size(); j++){
//			disagreement_unigram +=  ;
//		}
//	} // end of calculation of unigram figures.
}
