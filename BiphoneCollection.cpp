// Implementation of CBiphoneCollection methods
// Copyright © 2009 The University of Chicago
#include <math.h>
#include "BiphoneCollection.h"
#include "Biphone.h"
#include "Phone.h"
#include "WordCollection.h"
#include "log2.h"

int CompareWMI (const void *pM1,   const void *pM2);
int CompareMI (const void *pM1,   const void *pM2);
int ComparePhonemeCount (const void *pM1,   const void *pM2);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBiphoneCollection::CBiphoneCollection(CWordCollection* words)
	: Q3Dict<CBiphone>(571),
	m_PtrArray(),
	m_CountSortArray(),
	m_MISortArray(),
	m_WMISortArray(),
	m_SortStyle(WMI),
	m_Phones(),
	m_MyWords(words),
	m_Count(),
	m_LogFreqs(),
	m_Freqs(),
	m_Length(0),
	m_MI(),
	m_SumOfMyMIs(0.0),
	m_TotalCount(0),
	m_Z_biphones(0.0)
{
	// XXX. set auto-delete?
}

CBiphoneCollection::CBiphoneCollection(CPhoneCollection* phones)
	: Q3Dict<CBiphone>(571),
	m_PtrArray(),
	m_CountSortArray(),
	m_MISortArray(),
	m_WMISortArray(),
	m_SortStyle(MI),
	m_Phones(phones),
	m_MyWords(),
	m_Count(),
	m_LogFreqs(),
	m_Freqs(),
	m_Length(0),
	m_MI(),
	m_SumOfMyMIs(0.0),
	m_TotalCount(0),
	m_Z_biphones(0.0)
{
	// XXX. set auto-delete?
}

CBiphoneCollection::~CBiphoneCollection()
{
	delete[] m_MI;
	delete[] m_Freqs;
	delete[] m_LogFreqs;
	delete[] m_Count;
}

void CBiphoneCollection::Empty()
{
	clear();
	m_TotalCount = 0;
	m_Z_biphones = 0;
}
 
CBiphone* CBiphoneCollection::Insert (CPhone* P1, CPhone* P2)
{

	CBiphone*		pBiphone;
	QString			biphone;
	biphone = P1->Display() + "." + P2->Display();
 
	m_TotalCount++;

	pBiphone = find (biphone);

	if ( ! pBiphone )
	{
		pBiphone = new CBiphone(biphone);
		pBiphone->m_MyFirst = P1;
		pBiphone->m_MySecond = P2;
		pBiphone->IncrementCorpusCount(1);
 		insert(biphone, pBiphone); 
	}
	else 
	{ 
 		pBiphone->IncrementCorpusCount(1);
	}
	return pBiphone;

}
CBiphone* CBiphoneCollection::operator ^= (QString biphone)
{
	return find (biphone);
}

CBiphone* CBiphoneCollection::GetBiphone (CPhone* P1, CPhone* P2)
{

	 
	QString			biphone;
	biphone = P1->Display() + "." + P2->Display();
 
	return find (biphone);	

}
/*
CBiphone* CBiphoneCollection::operator^= (CParse& Biphone)
{

	StringToBiphone::Iterator it = m_Hash.find(Biphone.Display());

	if ( it == m_Hash.end() )
	{
		return NULL;
	}
	else return &it.data();

 
  }

CBiphone*	CBiphoneCollection::GetBiphone (CPhone* Ph1, CPhone* Ph2)
{
 	CBiphone* pBiphone;
  	QString Biphone = Ph1->Display() + "." + Ph2->Display();
 
	StringToBiphone::Iterator it = m_Hash.find( Biphone );

	if ( it == m_Hash.end() )
	{
		return NULL;
	}
	else return pBiphone;


}
*/
void CBiphoneCollection::SetSize(int n)
{
	delete[] m_Count;
	delete[] m_MI;
	delete[] m_Freqs;
	delete[] m_LogFreqs;
	m_LogFreqs = new double [n*n];
	m_Freqs = new double [n*n];
	m_MI = new double [n*n];
	m_Count = new int [n*n];

	for (int i = 0; i < n*n; ++i) {
		m_LogFreqs[i] = 0;
		m_Freqs[i] = 0;
		m_MI[i] = 0;
		m_Count[i] = 0;
	}
	m_Length = n;
}

void CBiphoneCollection::SetAtLogFreq(int FirstIndex, int SecondIndex, double ThisLogFreq)
{
	m_LogFreqs[ FirstIndex * m_Length + SecondIndex ] = ThisLogFreq;
}
double CBiphoneCollection::GetLogFreq(int FirstIndex, int SecondIndex)
{
	return m_LogFreqs[ FirstIndex * m_Length + SecondIndex ];
}
void CBiphoneCollection::SetAtCount(int FirstIndex, int SecondIndex, int ThisCount)
{
	m_Count[ FirstIndex * m_Length + SecondIndex ] = ThisCount;
}
int CBiphoneCollection::GetCount(int FirstIndex, int SecondIndex)
{
	return m_Count[ FirstIndex * m_Length + SecondIndex ];
}

void CBiphoneCollection::SetAtMI(int FirstIndex, int SecondIndex, double ThisMI)
{
	m_MI[ FirstIndex * m_Length + SecondIndex ] = ThisMI;
}


void CBiphoneCollection::IncrementAtCount (int FirstPhoneIndex, int SecondPhoneIndex, int n)
{
	m_Count[ FirstPhoneIndex * m_Length + SecondPhoneIndex ] += n;
}

 
 

 
 
//void	CBiphoneCollection::SortByLogProb()
//{/
//	
//};
void CBiphoneCollection::ListDisplay( Q3ListView* pView )
{
	int count = 0;

   pView->setRootIsDecorated( FALSE );
   pView->setSorting(1);
   // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  //    Add Column headers
  pView->addColumn( "Bigram" );
  pView->addColumn( "Count" );
  pView->addColumn( "Frequency" );
  pView->addColumn ( "Log Cond Prob" );
  pView->addColumn( "+LogProb" );
  pView->addColumn( "MutualInf" );
  pView->addColumn( "WMI" );
  pView->addColumn( "Cond Prob" );
  pView->addColumn( "MI markedness" );
 
  m_MyWords->GetLexicon()->GetDocument()->setStatusBar1( "Creating biphone list for display" );
  m_MyWords->GetLexicon()->GetDocument()->BeginCountDown();

  Q3Dict<CBiphone>& DictRef = *this;
  Q3DictIterator<CBiphone> it (DictRef);

	for ( ; it.current(); ++it)
	{	
		  it.current()->BiphoneListDisplay( pView ); 
		  m_MyWords->GetLexicon()->GetDocument()->CountDownOnStatusBar( count++, DictRef.count() );
	}

  m_MyWords->GetLexicon()->GetDocument()->setStatusBar1( "" );
  m_MyWords->GetLexicon()->GetDocument()->EndCountDown();   
}

double CBiphoneCollection::GetSumOfMyMIs()
{
	Q3DictIterator<CBiphone> it (*this);
	CBiphone* pBiphone;
	if ( m_SumOfMyMIs == 0 ) 
	{
		for ( ; it.current(); ++it)
		{	
 			pBiphone = it.current();
			m_SumOfMyMIs += pBiphone->m_MI;
		}
	}
	return m_SumOfMyMIs;
}
double CBiphoneCollection::ComputeZ_MI()
{
	// 	Currently this is not correctly computing this Z: 
	//  To compute it correctly, we need to assign an MI value to the unseen bigrams
	//  and take those into consideration. By leaving them out, we're assuming 
	//  an infinite negative MI for those bigrams.
	m_Z_biphones = 0; 
	Q3DictIterator<CBiphone> it (*this);
	CBiphone* pBiphone;
	double 	sum =  0;
	if ( m_Z_biphones == 0 ) 
	{
		for ( ; it.current(); ++it)
		{	
 			pBiphone = it.current();
			sum += pow(2, -1 * pBiphone->m_MI);
		}
	}
	m_Z_biphones = base2log (sum);
	return m_Z_biphones;
}
