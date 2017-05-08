// Implementation of StateEmitHMM methods
// Copyright © 2009 The University of Chicago
#include "StateEmitHMM.h"

#include <cstdlib>
#include <ctime>
#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include <Q3SortedList>
#include <QMessageBox>
#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "Stem.h"
#include "WordCollection.h"
#include "StringSurrogate.h"
#include "Parse.h"
#include "CompareFunc.h"
#include "log2.h"

class CLexicon;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StateEmitHMM::StateEmitHMM(LinguisticaMainWindow* parent)
{
	m_parent				= parent; 
	m_PI					= NULL;
	m_A						= NULL;
	m_B						= NULL;
	m_Alpha					= NULL;
	m_Beta					= NULL; 
	m_P						= NULL; 
	m_PI_SoftCounts			= NULL;
	m_A_SoftCounts			= NULL;
	m_B_SoftCounts			= NULL;
	m_trainingDatum			= NULL;
	m_trainingDatumSource	= NULL;
	m_symbolStateList.clear(); 
	m_Entropy				= NULL;
	m_countOfStates			= 0; 
	m_countOfSymbols		= 0; 
	m_lengthOfObservation	= 0;
	m_NumberOfIterations	= 0; 
	m_countOfDataItems		= 0; 
	m_maxLengthOfObservation =0; 
	m_HMMLog				= parent->GetLogFileName();	
	m_HMMLogDirectory		= parent->GetLogFileName(); 

//	m_HMMLog = QString("Linguistica_HMM_Log.txt"); 

	m_WordProbabilities		= NULL;
	m_dataType				= HMMNONE; 

	m_encodedTrainingData.clear(); 
	
}

StateEmitHMM::StateEmitHMM(CLexicon * pLexicon )
{
	m_parent				= NULL; 
	m_PI					= NULL;
	m_A						= NULL;
	m_B						= NULL;
	m_Alpha					= NULL;
	m_Beta					= NULL; 
	m_P						= NULL; 
	m_PI_SoftCounts			= NULL;
	m_A_SoftCounts			= NULL;
	m_B_SoftCounts			= NULL;
	m_trainingDatum			= NULL;
	m_trainingDatumSource	= NULL;
	m_symbolStateList		.clear(); 
	m_Entropy				= NULL;
	m_countOfStates			= 0; 
	m_countOfSymbols		= 0; 
	m_lengthOfObservation	= 0;
	m_NumberOfIterations	= 0; 
	m_countOfDataItems		= 0; 
	m_maxLengthOfObservation =0; 
	m_WordProbabilities		= NULL;	 
	m_HMMLog				= QString("Linguistica_HMM_Log.txt"); 
	m_Lexicon				= pLexicon;
	m_dataType				= HMMNONE; 

	m_encodedTrainingData.clear(); 

}
StateEmitHMM::~StateEmitHMM()
{
	clear(); 

}
/// Figure out what kind of phonological segments are being used as the symbols of this HMM
///
/// Parameters:
///		- type - can be PHONE_TIER1, PHONE_TIER2, or PARSE (which is essentially the spelling)
///

bool	StateEmitHMM::preprocessData(eHmmDataType type, void* dataCollection)
{
	// clear the HMM
	clear(); 

	// depending on the type, process the data
	if ( type == PHONE_TIER1) // take the wordCollection, and get PhoneTier 1
	{
		CWordCollection*					PhoneData;
		int									i;
		CStem*								pWord; 
		CParse*								pDataItem; 
		int									pCount;
		int									Index; 
		CStringSurrogate*					poundCSS; 
		QString								poundStr = QString("#"); 
		void*								pOriginData; 


		poundCSS = new CStringSurrogate(poundStr); 

		// The data is phoneCollection
		PhoneData = (CWordCollection*)dataCollection; 

		

		Index = 0; 
		for (i = 0; i < PhoneData ->GetCount(); i++)
		{
			pWord			= PhoneData ->GetAt(i);
			pOriginData		= (void*)pWord; 
			pCount			= pWord->GetCorpusCount(); 
			pDataItem		= pWord ->GetPhonology_Tier1();
			
			if ( pDataItem ->Size() ==0)
			{
				return false; 
			}



			pDataItem ->RemovePiecesThatBegin((*poundCSS));
			
			if ( pDataItem ->Size() ==0)
			{
				continue; 
			}

			m_trainingDataSource.	insert(Index, pOriginData); 
			m_trainingData.			insert(Index, pDataItem);
			m_trainingDataFrequency.insert(Index, pCount);	
			m_trainingDataSizes.	insert(Index, pDataItem ->Size()); 
			Index++; 

			if ( pDataItem ->Size() > m_maxLengthOfObservation)
			{
				m_maxLengthOfObservation = pDataItem ->Size() ; 
			}
		}

		m_countOfDataItems	= Index; 
		delete				poundCSS;
		m_dataType			= type;
		return true;
	}

	if ( type == PHONE_TIER2) // take the wordCollection, and get PhoneTier 2
	{
		CWordCollection*					PhoneData;
		int									i;
		CStem*								pWord; 
		CParse*								pDataItem; 
		int									pCount;
		int									Index; 
		void*								pOriginData; 

		// The data is phoneCollection
		PhoneData = (CWordCollection*)dataCollection; 

		Index = 0; 
		for (i = 0; i < PhoneData ->GetCount(); i++)
		{
			pWord		= PhoneData ->GetAt(i);
			pOriginData = (void*)pWord; 
			pCount		= pWord->GetCorpusCount(); 
			pDataItem	= pWord ->GetPhonology_Tier2(); 
			if ( pDataItem ->Size() ==0)
			{
				return false; 
			}
			m_trainingDataSource.	insert(Index, pOriginData); 
			m_trainingData.			insert(Index, pDataItem);
			m_trainingDataFrequency.insert(Index, pCount);
			m_trainingDataSizes.	insert(Index, pDataItem ->Size()); 
			Index++; 

			if ( pDataItem ->Size() > m_maxLengthOfObservation)
			{
				m_maxLengthOfObservation = pDataItem ->Size() ; 
			}

		}
		m_countOfDataItems	= Index; 
		m_dataType			= type;
		return true;
	}


	if ( type == PARSE) // take the wordCollection, and get CParse
	{
		CWordCollection*					WordData;
		int									i;
		CStem*								pWord; 
		CParse*								pDataItem; 
		int									pCount;
		int									Index; 
		void*								pOriginData; 

		// The data is WordCollection
		WordData = (CWordCollection*)dataCollection; 

		Index = 0; 
		for (i = 0; i < WordData ->GetCount(); i++)
		{
			pWord		= WordData ->GetAt(i);
			pOriginData = (void*)pWord; 
			pCount		= pWord->GetCorpusCount(); 
			pDataItem	= (CParse*)pWord; 

			m_trainingDataSource.	insert(Index, pOriginData); 
			m_trainingData.			insert(Index, pDataItem);
			m_trainingDataFrequency.insert(Index, pCount);
			m_trainingDataSizes.	insert(Index, pDataItem ->Size()); 
			Index++; 

			if ( pDataItem ->Size() > m_maxLengthOfObservation)
			{
				m_maxLengthOfObservation = pDataItem ->Size() ; 
			}

		}

		m_countOfDataItems	= Index; 
		m_dataType			= type;
		return true;
	}

	return false; 
} 

void	StateEmitHMM::init(int countOfStates, int loops)
{
	StringToInt::iterator					StringToIntIt; 
	StringToInt								tempSymbolList; 
	int										i,j; 
	QString									oneSymbol; 
	int										symbolIndex; 
	CParse*									oneDataItem; 
	int										itemSize; 
	int*									oneIntArray; 
	int										encodeId; 


	// count of states
	if ( countOfStates < 2 ) 
	{
		QMessageBox::information(NULL, "error", "The number of states of one HMM should > 1", "OK"); 
		return; 
	}

	m_countOfStates = countOfStates; 

	// training data
	if ( m_countOfDataItems  == 0)
	{
		QMessageBox::information(NULL, "error", "The training data is empty", "OK"); 
		clear(); 
		return;
	}
	
//	m_Video = new Video ( countOfStates, m_countOfDataItems );
	// symbols
	for ( i=0; i<  m_countOfDataItems; i++)
	{
		oneDataItem = m_trainingData[i];
		for ( j=1; j<= oneDataItem ->Size(); j++)
		{
			oneSymbol = (oneDataItem ->GetPiece(j)).Display(); 
			tempSymbolList.insert(oneSymbol, 1);
		}
	}
	

	symbolIndex = 0; 
	for ( StringToIntIt = tempSymbolList.begin(); StringToIntIt != tempSymbolList.end(); StringToIntIt++)
	{
		oneSymbol		= StringToIntIt.key(); 
		m_symbolList.	insert(symbolIndex, oneSymbol); 
		m_symbolIndex.	insert(oneSymbol, symbolIndex); 
		symbolIndex++;
	}

	m_countOfSymbols = symbolIndex; 

	// After we've got symbols, we encode training data 
	for ( i=0; i<  m_countOfDataItems; i++)
	{
		oneDataItem		= m_trainingData[i];
		itemSize		= m_trainingDataSizes[i];
		oneIntArray		= new int[1+itemSize]; // init an int array, whose size is (1+itemSize). The zero location is not used. we use from 1 to itemSize in this array
		m_encodedTrainingData.insert(i, oneIntArray); 
		for ( j=1; j<= itemSize; j++)
		{
			oneSymbol		= (oneDataItem ->GetPiece(j)).Display(); 
			encodeId		= m_symbolIndex[oneSymbol];
			oneIntArray[j]	= encodeId; 
		}
	}
///////////////////////////////////////////////////////////////////////////////
	// Output alphabet members to file //
///////////////////////////////////////////////////////////////////////////////
	QFile	file( m_HMMLogDirectory + "segments.txt");	
	if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
	{
		QMessageBox::information(NULL, "Error", "Can't Open the segments file!", "OK"); 
		return;    
	}

	Q3TextStream outf( &file );
	for ( i=0; i<  m_countOfSymbols; i++)
	{	
		outf << m_symbolList[i] << endl;
	}
 
	file.close();
///////////////////////////////////////////////////////////////////////////////


	// allocate memory for prob parameters
	// PI
	m_PI = new double[m_countOfStates];

	// A
	m_A = new double*[m_countOfStates];
	for ( i=0; i< m_countOfStates; i++)
	{
		m_A[i] = new double [m_countOfStates];
	}

	// B
	m_B = new double*[m_countOfStates];
	for ( i=0; i< m_countOfStates; i++)
	{
		m_B[i] = new double [m_countOfSymbols];
	}

	// m_PI_SoftCounts
	m_PI_SoftCounts = new double[m_countOfStates];

	// m_A_SoftCounts
	m_A_SoftCounts = new double*[m_countOfStates];
	for ( i=0; i< m_countOfStates; i++)
	{
		m_A_SoftCounts[i] = new double [m_countOfStates];
	}

	// m_B_SoftCounts
	m_B_SoftCounts = new double*[m_countOfStates];
	for ( i=0; i< m_countOfStates; i++)
	{
		m_B_SoftCounts[i] = new double [m_countOfSymbols];
	}

	// Alpha from 0 to T
	m_Alpha = new double*[m_maxLengthOfObservation + 1]; 
	for ( i=0; i< m_maxLengthOfObservation + 1; i++)
	{
		m_Alpha[i] = new double [m_countOfStates];
	}

	// Beta from 0 to T
	m_Beta = new double*[m_maxLengthOfObservation + 1]; 
	for ( i=0; i< m_maxLengthOfObservation + 1; i++)
	{
		m_Beta[i] = new double [m_countOfStates];
	}


	// m_P from 0 to T - 1 
	m_P = new double**[m_maxLengthOfObservation];
	for ( i=0; i< m_maxLengthOfObservation; i++)
	{
		m_P[i] = new double* [m_countOfStates];

		for ( j=0; j< m_countOfStates; j++)
		{
			m_P[i][j] = new double[m_countOfStates];
		}
	}
	
	// Word probabilities:
	m_WordProbabilities = new double [m_countOfDataItems];


	// The Loop times
	m_NumberOfIterations = loops; 

////////////////////////////////////////////////////////////////////////////////////////////////		
////////////////////////////////////////////////////////////////////////////////////////////////		
	QFile file2( m_HMMLogDirectory + "config.txt");	
	if ( !file2.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
	{
		QMessageBox::information(NULL, "Error", "Can't Open the HMM Log config file!", "OK"); 
		return;    
	}

	Q3TextStream outf2( &file2 );

	outf2 << m_countOfStates << " = Number of states " << endl;
	outf2 << m_countOfSymbols << " = Number of symbols" << endl;	
	outf2 << m_NumberOfIterations  << " = Number of iterations";	

	file2.close();
////////////////////////////////////////////////////////////////////////////////////////////////		
////////////////////////////////////////////////////////////////////////////////////////////////		


}

void	StateEmitHMM::initPiAndAB()
{
	using std::srand;
	using std::time;
	using std::rand;

	double						oneUniformProb;
	int							i,j; 
	double						total = 0;
	double						random_weight = 0.25; //was 0.25


	// srand the seed
	srand ( time(NULL) );

	// init Pi
	oneUniformProb = 1.0 / m_countOfStates; 
	for ( i=0; i< m_countOfStates; i++)
	{
		m_PI[i] = oneUniformProb; 
	}

	// init A
	//------------------------------------------------//
	/*	initialize transition probabilities */
	for (i = 0; i < m_countOfStates; i++)
	{
		total = 0;
		for ( j=0; j< m_countOfStates; j++)
		{
			m_A[i][j] = 	(1 / (double) m_countOfStates) * (1-random_weight) + (random_weight) * rand()/(double)RAND_MAX;
			total += m_A[i][j];
		}
		
		for ( j=0; j< m_countOfStates; j++)
		{
			m_A[i][j] = m_A[i][j] / total;	
		}
	}	

	/*	initialize emission probabilities		*/
	total = 0;
	for (i = 0; i < m_countOfStates; i++)
	{
		total = 0;
		for ( j=0; j< m_countOfSymbols; j++)
		{
			m_B[i][j] = 	(1 / (double) m_countOfSymbols) * (1-random_weight-0.1) + (random_weight+0.1) * rand()/(double)RAND_MAX;
			total += m_B[i][j];
		}
		
		for ( j=0; j< m_countOfSymbols; j++)
		{
			m_B[i][j] = m_B[i][j] / total;	
		}
	}	



	/*	initialize m_PI_SoftCounts as zero	*/
	for ( i=0; i< m_countOfStates; i++)
	{
		m_PI_SoftCounts[i] = 0.0; 
	}

	/*	initialize m_A_SoftCounts as zero	*/
	for (i = 0; i < m_countOfStates; i++)
	{
		for ( j=0; j< m_countOfStates; j++)
		{
			m_A_SoftCounts[i][j] = 	0.0;
		}
	}


	/*	initialize m_B_SoftCounts as zero	*/
	for (i = 0; i < m_countOfStates; i++)
	{	
		for ( j=0; j< m_countOfSymbols; j++)
		{
			m_B_SoftCounts[i][j] = 0.0;	
		}
	}



}


void	StateEmitHMM::forward(int dataIndex, double&  result)
{
	int						i,j,k; 
	double					sum; 
	int						symbolIndex; 
	double					normSum; 
	CStem*					pWord;



	// Get the current dataItem as CParse
	m_trainingDatum			= m_encodedTrainingData[ dataIndex ];
	m_trainingDatumSource	= m_trainingDataSource [ dataIndex ];
	m_lengthOfObservation	= m_trainingDataSizes  [ dataIndex ]; 

	// init the alpha as PI; 
	for (i=0; i< m_countOfStates; i++)
	{
		m_Alpha[0][i]= m_PI[i]; 
	}

	// Induction step
	for ( i=1; i <= m_lengthOfObservation; i++)
	{
		normSum = 0.0;
		
		// figure out which symbol is emitted for this 
		symbolIndex = m_trainingDatum[i];	

		for ( j=0; j< m_countOfStates; j++)
		{
			sum = 0.0; 
			for (k=0; k< m_countOfStates; k++)
			{
				sum += m_Alpha[i-1][k] * m_A[k][j] * m_B[k][symbolIndex]; 
			}
			
			m_Alpha[i][j] = sum; 
		//	normSum += sum; // add them up for normalization 
		}

		// Norm the m_Alpha to avoid too small values
		/*
		for ( j=0; j< m_countOfStates; j++)
		{
			m_Alpha[i][j] = m_Alpha[i][j] / normSum; 
		}
		*/	
	}
	
	double		probOfTheData; 	

	probOfTheData = 0.0;
	for ( i=0; i<m_countOfStates; i++)
	{
		probOfTheData += m_Alpha[m_lengthOfObservation][i]; 
	}

	result = probOfTheData; 
	Q_ASSERT (result);
	
	// Find pointer to original word or whatever
	if ( m_dataType == PHONE_TIER1) {
		pWord = static_cast<CStem*>(m_trainingDatumSource);
		pWord->SetHMM_LogProbability(-1 * base2log(result));
	}
}


void	StateEmitHMM::backward(int dataIndex,  double&  result)
{
	int						i,j,k; 
	double					sum; 
	int						symbolIndex; 
	double					normSum; 

	// Get the current dataItem as CParse
	m_trainingDatum			= m_encodedTrainingData[dataIndex];
	m_trainingDatumSource	= m_trainingDataSource [dataIndex];
	m_lengthOfObservation	= m_trainingDataSizes  [dataIndex]; 


	// init the beta as 1; 
	for (i=0; i< m_countOfStates; i++)
	{
		m_Beta[m_lengthOfObservation][i]= 1; 
	}

	// Induction step
	for ( i=m_lengthOfObservation -1; i>=0; i--)
	{
		normSum = 0.0; 
		for ( j=0; j< m_countOfStates; j++)
		{
			// figure out which symbol is emitted for this 
			symbolIndex = m_trainingDatum[i+1];	

			sum = 0.0; 
			for (k=0; k< m_countOfStates; k++)
			{
				sum += m_Beta[i+1][k] * m_A[j][k] * m_B[j][symbolIndex]; 
			}
			
			m_Beta[i][j] = sum; 
		//	normSum += sum; 
		}

		// Norm the m_Beta to avoid too small values
		/*
		for ( j=0; j< m_countOfStates; j++)
		{
			m_Beta[i][j] = m_Beta[i][j] / normSum; 
		}
		*/
	}
	

	double		probOfTheData; 	

	probOfTheData = 0.0;
	for ( i=0; i<m_countOfStates; i++)
	{
		probOfTheData += m_PI[i]*m_Beta[0][i]; 
	}
	
	result = probOfTheData; 

	//QMessageBox::information(NULL, "Debug", QString("The String Prob Computed by forward as %1").arg(probOfTheData), "OK");  
	
}

void	StateEmitHMM::Expectation(int dataIndex)
{

	/* Old version, with John's efforts 
	int						i, j, k;
	int						symbolIndex; 
	double					denominator;
	double					numerator;
	double					oneGamma; 
	int						pCount; 
	double					oneValue; 

	// Get the current dataItem as CParse
 
	m_trainingDatum				= m_encodedTrainingData  [dataIndex];
	m_trainingDatumSource		= m_trainingDataSource   [dataIndex];
	m_lengthOfObservation		= m_trainingDataSizes    [dataIndex]; 
 
	pCount						= m_trainingDataFrequency[dataIndex];

	Q_ASSERT(pCount > 0);

	


	QFile					file( m_HMMLogDirectory + "expectation.txt");	
	if ( !file.open( IO_WriteOnly | IO_Append ) ) 
	{
		QMessageBox::information(NULL, "Error", "Can't Open the HMM Log file!", "OK"); 
		return;    
	}
	QTextStream outf( &file );

	if (dataIndex == 0)
	{
		outf << endl <<"----------------------------------------------------------------------" << endl;
	}
	else
	{
		outf << endl << endl;
	}
	outf << dataIndex << "\tProbs:\nL\tFrom\tTo";



	// compute the m_P: // (Position in string, from-state, to-state);
	for ( i=0; i< m_lengthOfObservation; i++)
	{
		// figure out which symbol is emitted for this 
		symbolIndex = m_trainingDatum[i+1];	
		
		// compute the denominator
		denominator = 0.0; 
		for ( j=0; j< m_countOfStates; j++)
		{
			for (k=0; k< m_countOfStates; k++)
			{
				denominator += m_Alpha[i][j] * m_A[j][k] * m_B[j][symbolIndex]* m_Beta[i+1][k];
			}
		}
		
		Q_ASSERT (denominator);
		// compute numerator
		for ( j=0; j< m_countOfStates; j++)
		{
			for (k=0; k< m_countOfStates; k++)
			{
				numerator = m_Alpha[i][j] * m_A[j][k] * m_B[j][symbolIndex]* m_Beta[i+1][k];
				m_P[i][j][k] = numerator / denominator; 
				outf << endl << i << m_symbolList[symbolIndex] << "\t" << j << "\t" << k << "\t" << m_P[i][j][k]; 
			}
		}
	}


	// Next, compute softcount and add them to softcount data
	
	// Estimate Pi

	outf << "\n\n" << "Soft counts for Pi:" << "\t";
	for ( i=0; i< m_countOfStates; i++)
	{
		oneGamma =0.0; 
		outf << "\nFrom:\t" << i; 
		for (j=0; j< m_countOfStates; j++)
		{
			oneGamma += m_P[0][i][j];
			outf << "\tTo:\t"<< j <<" \t" << oneGamma << "\t"; 
		}

		oneValue = oneGamma; 
		m_PI_SoftCounts[i] += oneValue * pCount;  
		outf << "\tTotal soft counts (Pi) initially to state :"<< i << "\t"<<m_PI_SoftCounts[i];
	}

	// Estimate m_A
	for ( i=0; i< m_countOfStates; i++)
	{
		denominator = 0.0; 
		for ( k=0; k< m_lengthOfObservation; k++)
		{
			oneGamma =0.0; 
			for ( j=0; j< m_countOfStates; j++)
			{
				oneGamma += m_P[k][i][j];
			}

			denominator += oneGamma; 
		}
		Q_ASSERT (denominator);

		// compute m_A[i][j]	 
		for ( j=0; j< m_countOfStates; j++)
		{
			numerator =0.0;	
			for ( k=0; k< m_lengthOfObservation; k++)
			{
				numerator += m_P[k][i][j];
			}		
			
			oneValue = numerator / denominator;
			m_A_SoftCounts[i][j] += oneValue * pCount;  
			outf << "\nTotal soft counts from state: "<<i<< " to state " << j << "\t"<<m_A_SoftCounts[i][j];
		}
	}
 

	outf << "\n\nSoft counts of symbol emissions "<< endl; 
	for (k = 0; k < m_lengthOfObservation; k++)
	{
		// figure out which symbol is emitted for this 
		symbolIndex = m_trainingDatum[k+1];	
		
		outf << endl <<"Dealing with symbol: " << m_symbolList[symbolIndex];

		// Compute denominator
		denominator =0.0;	

		for (i = 0; i < m_countOfStates; i++)
		{
			for (j = 0; j < m_countOfStates; j++)
			{
				denominator += m_P[k][i][j]; 
			}
		}
		Q_ASSERT (denominator);

		// Compute numerator and m_B
		for (i = 0; i < m_countOfStates; i++)
		{	
			outf << "\n\tState: " << i << " ";
			for (j = 0; j < m_countOfStates; j++)
			{
				outf << " to state " <<  j << " "; 
				m_B_SoftCounts[i][symbolIndex] += ( m_P[k][i][j] / denominator) * pCount;  
				outf << m_P[k][i][j] / denominator;
			}
		}
	}

	for (i = 0; i < m_countOfStates; i++)
	{
		outf << endl << "\nIn State: "<< i;
		for (j= 0; j < m_countOfSymbols; j++)
		{
			outf << "\tEmit symbol: "<< j<< " "<< m_symbolList[j] << " "<<m_B_SoftCounts[i][j];
		}
	}



	file.close();

  */  //end of OLD VERSION
 
	int						i, j, k;
	int						symbolIndex; 
	double					denominator;
	double					numerator;
	double					oneGamma; 
	int						pCount; 
	double					oneValue; 

	// Get the current dataItem as CParse
	m_trainingDatum				= m_encodedTrainingData[dataIndex];
	m_trainingDatumSource		= m_trainingDataSource[dataIndex];
	m_lengthOfObservation		= m_trainingDataSizes[dataIndex]; 
	pCount						= m_trainingDataFrequency[dataIndex];

	Q_ASSERT(pCount > 0);


	denominator = 0.0; 
	for ( j=0; j< m_countOfStates; j++)
	{
		/*
		for (k=0; k< m_countOfStates; k++)
		{
			denominator += m_Alpha[i][j] * m_A[j][k] * m_B[j][symbolIndex]* m_Beta[i+1][k];
		}
		*/
		denominator += m_Alpha[m_lengthOfObservation][j];
	}


	// compute the m_P
	for ( i=0; i< m_lengthOfObservation; i++)
	{
		// figure out which symbol is emitted for this 
		symbolIndex = m_trainingDatum[i+1];	
		
		// compute the denominator
		
		
		Q_ASSERT (denominator);
		// compute numerator
		for ( j=0; j< m_countOfStates; j++)
		{
			for (k=0; k< m_countOfStates; k++)
			{
				numerator = m_Alpha[i][j] * m_A[j][k] * m_B[j][symbolIndex]* m_Beta[i+1][k];
				m_P[i][j][k] = numerator / denominator; 
			}
		}
	}


	// Next, compute softcount and add them to softcount data

	// Estimate Pi
	for ( i=0; i< m_countOfStates; i++)
	{
		oneGamma =0.0; 
		
		for (j=0; j< m_countOfStates; j++)
		{
			oneGamma += m_P[0][i][j];
		}

		oneValue = oneGamma; 
		m_PI_SoftCounts[i] += oneValue * pCount;  
	}

	// Estimate m_A
	for ( i=0; i< m_countOfStates; i++)
	{
		for ( j=0; j< m_countOfStates; j++)
		{
			denominator = 0.0; 
			for ( k=0; k< m_lengthOfObservation; k++)
			{
				denominator += m_P[k][i][j];
			}

			Q_ASSERT (denominator);
			m_A_SoftCounts[i][j] += denominator * pCount; 
		}

	}

	// Estimate m_B

	for (i=0; i< m_countOfStates; i++)
	{
		
		// Compute numerator and m_B
		for (k=0; k< m_lengthOfObservation; k++)
		{
			// figure out which symbol is emitted for this 
			symbolIndex = m_trainingDatum[k+1];	
			
			numerator =0.0; 
			for ( j=0; j< m_countOfStates; j++)
			{
				numerator += m_P[k][i][j];  
			}			
			oneValue = numerator ;
			m_B_SoftCounts[i][symbolIndex] += oneValue * pCount;  
		}
	}
		
} 
		
 

/// Calculate the new probability parameters, based on soft counts, and emission entropy
///
/// Parameters:
///		none
///
void	StateEmitHMM::Maximization()
{
	int						i, j;
	double					total; 

	QFile					file( m_HMMLogDirectory + "maximization.txt");	
	if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
	{
		QMessageBox::information(NULL, "Error", "Can't Open the maximization file!", "OK"); 
		return;    
	}
	Q3TextStream outf( &file );
 
	outf << endl <<"----------------------------------------------------------------------" << endl;

	outf << "\nPi softcounts:\t";
	// Re-Estimate the m_PI
	total =0.0;
	for ( i=0; i< m_countOfStates; i++)
	{	
		total += m_PI_SoftCounts[i];
		outf << "State: "<<i<<"\t" << m_PI_SoftCounts[i] << "\t";
	}
	Q_ASSERT (total);

	outf << "\n";
	for ( i=0; i< m_countOfStates; i++)
	{	
		m_PI[i]				= m_PI_SoftCounts[i] / total;
		m_PI_SoftCounts[i]	= 0.0; 

		outf << endl << "Pi for State: "<<"\t" << m_PI[i];
	}


	outf << "\n\nMatrix A";
	// Re-Estimate the m_A
	for ( i=0; i< m_countOfStates; i++)
	{
		outf << "\n\nFrom State: "<< i << "\t";
		total = 0.0; 
		for (j=0; j< m_countOfStates; j++)
		{
			total += m_A_SoftCounts[i][j];
			outf << " To State: "<< j << "\t" << m_A_SoftCounts[i][j];
		}
		outf 	<< " -- Total: "<< total;
		Q_ASSERT (total);

		outf << "\nTransition probabilities: ";
		for (j=0; j< m_countOfStates; j++)
		{
			m_A[i][j]			 = m_A_SoftCounts[i][j] /total;
			m_A_SoftCounts[i][j] = 0.0; 
			outf << "\tto: "<< j << "\t"<< m_A[i][j];
		}
	}

	outf << "\n\nMatrix B";
	// Re-Estimate the m_B
	for ( i=0; i< m_countOfStates; i++)
	{
		outf << "\nFrom State: " << i << endl; 
		total =0.0; 
		for (j=0; j< m_countOfSymbols; j++)
		{
			total += m_B_SoftCounts[i][j];
			outf << "\tCount of symbol "<< j << " "<<m_B_SoftCounts[i][j]; 
		}
		outf << endl; 
	 
//		if (total == 0) 
//		{
//			int aaa = 0;
//		}
		// ************** bug found JG Nov 30 2006 **********
		if (total == 0)
		{
			for (j=0; j< m_countOfSymbols; j++)
			{
				m_B[i][j]			 = 0;;
				m_B_SoftCounts[i][j] = 0.0; 
				outf << "\tSymb: "<< j << "\t" << m_B[i][j];
			}
		}
		else
		{
			for (j=0; j< m_countOfSymbols; j++)
			{
				m_B[i][j]			 = m_B_SoftCounts[i][j] /total;
				m_B_SoftCounts[i][j] = 0.0; 
				outf << "Symbol: "<< j << "\t" << m_B[i][j];
			}
		}
	}

	// calculate each state's emission entropy:
	if (m_Entropy) delete m_Entropy;
	m_Entropy = new double [m_countOfStates];
	
	for ( i=0; i< m_countOfStates; i++)
	{	
		total =0.0; 
		for (j=0; j< m_countOfSymbols; j++)
		{
			Q_ASSERT (m_B[i][j] );
			if (base2log (m_B[i][j]) > -1* 1000000)  // i.e., if m_B[i][j] ins't too small...
			{
				total += -1 * m_B[i][j] * base2log ( m_B[i][j] );
			}			
		}		
		m_Entropy[i] = total;
	}

}
// The highest level iteration in this function
// 
//
// Parameters:
//		none
double	StateEmitHMM::trainParameters()
{
	int					i; 
	int					dataIndex; 
	double				stringProbWithForward ;
	double				stringProbWithBackward;
	int					HowFrequentlyToOutputStatistics;
	int					dummy(0);
	
	HowFrequentlyToOutputStatistics = 1;


	m_Lexicon->GetDocument()->setStatusBar1( "Training HMM" );
	m_Lexicon->GetDocument()->BeginCountDown();

	for ( i=0; i<m_NumberOfIterations; i++)
	{
		m_LogProbabilityOfData = 0;

		m_Lexicon->GetDocument()->CountDownOnStatusBar (i, m_NumberOfIterations, 1);

		//OutputTransitions(i, m_HMMLog);
		for ( dataIndex =0; dataIndex < m_countOfDataItems; dataIndex++)
		{
			
			forward (dataIndex, stringProbWithForward); 
			backward(dataIndex, stringProbWithBackward);

			Q_ASSERT (stringProbWithForward == stringProbWithBackward); 
			Q_ASSERT (stringProbWithForward);

			Expectation(dataIndex); 
			
			m_LogProbabilityOfData += -1 * base2log (stringProbWithForward);			
			
		}

		Maximization(); 
		OutputTransitionsToLogFile(i, m_HMMLog);
		
//		pVideoFrame = new VideoFrame(m_countOfStates );
//		InsertValues (pVideoFrame);
//		m_Video->insert (i, pVideoFrame);

		dummy++;
		if (dummy == HowFrequentlyToOutputStatistics )
		{
			dummy			 = 0;
			OutputEmissions  (i, m_HMMLog);
			OutputTransitions(i, m_HMMLog);
		 	OutputInitials   (i, m_HMMLog);


		}		
		
	}
		
	getStateListForASymbol();	//JG: put this back in, took out for debugging;

	return (m_LogProbabilityOfData);
}


void	StateEmitHMM::clear()
{
	double*								oneArray; 
	double**							oneTwoDimensionArray; 
	int									i,j; 
	IntToIntArray::iterator				IntToIntArrayIt; 
	int*								oneIntArray; 

	// Clear data
	m_trainingData.clear(); 
	m_trainingDataFrequency.clear();
	m_trainingDataSizes.clear(); 

	// Clear Origin data
	m_trainingDataSource.clear(); 


	// Clear m_encodedTrainingData
	for ( IntToIntArrayIt = m_encodedTrainingData.begin(); IntToIntArrayIt != m_encodedTrainingData.end(); IntToIntArrayIt++)
	{
		oneIntArray = IntToIntArrayIt.data(); 
		if ( oneIntArray != NULL)
		{
			delete [] oneIntArray; 
		}
	}
	m_encodedTrainingData.clear(); 


	// Clear m_WordProbabilities
	if (m_WordProbabilities) delete m_WordProbabilities;

	// clear PI
	if ( m_PI != NULL)
	{
		delete [] m_PI;
		m_PI = NULL; 
	}
	// clear A
	if ( m_A != NULL)
	{
		for ( i=0; i< m_countOfStates; i++)
		{
			oneArray = m_A[i];
			delete oneArray;
		}
		delete [] m_A; 
		m_A = NULL; 
	}
	// clear B
	if ( m_B != NULL)
	{
		for ( i=0; i< m_countOfStates; i++)
		{
			oneArray = m_B[i];
			delete oneArray;
		}
		delete [] m_B; 
		m_B = NULL; 
	}

	// clear m_PI_SoftCounts
	if ( m_PI_SoftCounts != NULL)
	{
		delete [] m_PI_SoftCounts;
		m_PI_SoftCounts = NULL; 
	}

	// clear m_A_SoftCounts
	if ( m_A_SoftCounts != NULL)
	{
		for ( i=0; i< m_countOfStates; i++)
		{
			oneArray = m_A_SoftCounts[i];
			delete oneArray;
		}
		delete [] m_A_SoftCounts; 
		m_A_SoftCounts = NULL; 
	}
	// clear m_B_SoftCounts
	if ( m_B_SoftCounts != NULL)
	{
		for ( i=0; i< m_countOfStates; i++)
		{
			oneArray = m_B_SoftCounts[i];
			delete oneArray;
		}
		delete [] m_B_SoftCounts; 
		m_B_SoftCounts = NULL; 
	}

	// clear Alpha
	if ( m_Alpha != NULL)
	{
		for ( i=0; i< m_maxLengthOfObservation + 1; i++)
		{
			oneArray = m_Alpha[i];
			delete oneArray;
		}
		delete [] m_Alpha; 
		m_Alpha = NULL; 
	}
	// clear Beta
	if ( m_Beta != NULL)
	{
		for ( i=0; i< m_maxLengthOfObservation + 1; i++)
		{
			oneArray = m_Beta[i];
			delete oneArray;
		}
		delete [] m_Beta; 
		m_Beta = NULL; 
	}
	
	// clear m_P
	if ( m_P != NULL)
	{
		for ( i=0; i< m_maxLengthOfObservation; i++)
		{
			oneTwoDimensionArray = m_P[i];

			for ( j=0; j< m_countOfStates; j++)
			{
				oneArray = oneTwoDimensionArray[j]; 
				delete oneArray; 
			}

			delete oneTwoDimensionArray; 
		}

		delete [] m_P; 
		m_P = NULL; 
	}

	// clear m_symbolStateList
	IntTohmmSortedList::iterator			IntTohmmSortedListIt;
	hmmSortedList*							oneStateList; 
	
	for(IntTohmmSortedListIt = m_symbolStateList.begin();  IntTohmmSortedListIt != m_symbolStateList.end(); IntTohmmSortedListIt++)
	{
		oneStateList	= IntTohmmSortedListIt.data();
		oneStateList	->setAutoDelete(true); 
		delete oneStateList; 
	}
	m_symbolStateList.clear(); 	

	// set construction parameters back to zeros
	m_countOfStates				= 0; 
	m_countOfSymbols			= 0; 
	m_maxLengthOfObservation	= 0;
	m_NumberOfIterations		= 0;  
	m_countOfDataItems			= 0; 
	m_dataType					= HMMNONE; 

	// clear Volca
	m_symbolList				.clear(); 
	m_symbolIndex				.clear();

	// clear entropy
	if ( m_Entropy )
	{
		delete m_Entropy;
	}

}

void	StateEmitHMM::getStateListForASymbol()
{	
	int						i, j; 
	double					total; 
	double					oneValue, 
							restValue; 		
	hmmSortedList*			oneList; 
	hmmForSortingItem*		oneItem; 
	const double			MaxLogRatio = 10;
	const double			MinLogRatio = -100;
	double					LogRatio;

	for ( i=0; i< m_countOfSymbols; i++)
	{
		oneList = new hmmSortedList(); 
		m_symbolStateList.insert(i, oneList); 

		total = 0.0; 
		for (j=0; j< m_countOfStates; j++)
		{
			total += m_B[j][i]; 
		}

		for (j=0; j< m_countOfStates; j++)
		{
			oneValue = m_B[j][i];
			restValue = total - oneValue; 

			if ( restValue == 0.0)
			{
				LogRatio = MaxLogRatio;
			}
			else
			{
				if (oneValue == 0.0) {
					LogRatio = MinLogRatio;
				} else {
					Q_ASSERT(restValue != 0);
					LogRatio = base2log(oneValue / restValue);
				}

				if ( LogRatio > MaxLogRatio)
				{
					LogRatio = MaxLogRatio;
				}
				
				if ( LogRatio < MinLogRatio)
				{
					LogRatio = MinLogRatio;
				}

			}

			oneItem = new hmmForSortingItem(j, LogRatio ); 
			oneList ->append(oneItem); 
		}
		
		oneList ->sort(); 
	}

}

void StateEmitHMM::OutputTransitionsToLogFile(int IterationNumber,
		QString LogFileName)
{
	QFile file(LogFileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QMessageBox::information(0, "Error",
			"Can't Open the HMM Log file!", "OK");
		return;
	}
	QTextStream outf(&file);
	
	outf << endl << IterationNumber << '\t';
	for (int i = 0; i < m_countOfStates; ++i)
		for (int j = 0; j < m_countOfStates; ++j)
			outf << m_A[i][j] << '\t';
	for (int i = 0; i < m_countOfStates; ++i)
		outf << m_Entropy[i] << '\t';
}

void StateEmitHMM::OutputTransitions(int /* iteration number, unused */,
		QString /* log file name. XXX. unused */)
{
	QFile file2(QString("%1transitions.txt").arg(m_HMMLogDirectory));
	if (!file2.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QMessageBox::information(0, "Error",
			"Can't Open the HMM transitions file!", "OK");
		return;    
	}

	QTextStream outf2(&file2);
	for (int i = 0; i < m_countOfStates; ++i)
		for (int j = 0; j < m_countOfStates; ++j)
			outf2 << m_A[i][j] << '\t';
	outf2 << endl;
}

void StateEmitHMM::OutputEmissions(int /* iteration number, unused */,
		QString /* log file name. XXX. unused */)
{
	QFile file(QString("%1emissions.txt").arg(m_HMMLogDirectory));
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QMessageBox::information(0, "Error",
			"Can't Open the HMM emissions file!", "OK");
		return;
	}

	QTextStream outf(&file);
	for (int i = 0; i < m_countOfStates; ++i)
		for (int j = 0; j < m_countOfSymbols; ++j)
			outf << m_B[i][j] << '\t';
	outf << endl;
}

void StateEmitHMM::OutputInitials(int /* iteration number, unused */,
		QString /* log file name. XXX. unused */)
{
	QFile file(QString("%1initials.txt").arg(m_HMMLogDirectory));
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QMessageBox::information(0, "Error",
			"Can't Open the HMM initials file!", "OK");
		return;
	}

	QTextStream outf(&file);
	for (int j = 0; j < m_countOfStates; ++j)
		outf << m_PI[j] << '\t';
	outf << endl;
}

void	StateEmitHMM::logInfo(double totalLogProbability)
{
	QFile					file( m_HMMLog );
    int						i, j; 			
	QString					oneOutString; 

	if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
	{
		QMessageBox::information(NULL, "Error", "Can't Open the HMM Log file!", "OK"); 
		return;    
	}

	Q3TextStream outf( &file );

	outf << "\n*** One SnapShot ***" << endl <<endl; 

	outf << "Total log probability: "<<totalLogProbability << endl << endl;

	// Output PI
	outf << "** PI Values **" << endl; 
	for (i=0; i<m_countOfStates; i++)
	{
		oneOutString = QString("State %1:\t %2\t").arg(i).arg(m_PI[i]);
		outf <<"	"<< oneOutString << endl; 
	}

	// Output A
	outf << "** A Values **" << endl; 
	for (i=0; i<m_countOfStates; i++)
	{
		for ( j =0; j< m_countOfStates; j++)
		{
			oneOutString = QString("State %1 -> %2 :\t%3").arg(i).arg(j).arg(m_A[i][j]);
			outf <<"	"<< oneOutString << endl; 
		}
	}
	
	// Output B
	outf << "** B Values **" << endl; 
	for (i=0; i<m_countOfStates; i++)
	{
		for ( j =0; j< m_countOfSymbols; j++)
		{
			oneOutString = QString("State %1\tEmit\t%2 :\t%3").arg(i).arg(m_symbolList[j]).arg(m_B[i][j]);
			outf <<"	"<< oneOutString << endl; 
		}
	}

	// Output the m_symbolStateList
	QString					thisSymbol; 
	hmmSortedList*			oneList; 
	hmmForSortingItem*		oneItem; 
	int						stateNumber, thisStateNumber;
	double					ratioValue; 

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// The special, but usual, case where we care about a 2-state HMM:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	if (m_countOfStates == 2)
	{		
		outf << "** Two State system: Log ratio probability, State 0 to State 1 **" << endl; 
		for ( i=0; i< m_countOfSymbols; i++)
		{
			thisSymbol	= m_symbolList[i]; 
//			oneList		= m_symbolStateList[i];
			outf <<endl << thisSymbol<< "\t" << 
				m_B[0][i] <<"\t" <<
				m_B[1][i] <<"\t" <<
				base2log ( m_B[0][i] / m_B[1][i] );		 			
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////


	outf << endl << endl <<  "** Symbol StateList: Log ratio probability, this state to all others, individually sorted by best state **" << endl; 
	for ( i=0; i< m_countOfSymbols; i++)
	{
		thisSymbol	= m_symbolList[i]; 
		oneList		= m_symbolStateList[i];

		outf <<endl << thisSymbol<< "\t"; 

		for ( oneItem=oneList ->first(); oneItem != 0; oneItem=oneList ->next())
		{
		//	stateNumber		= oneItem ->m_stateNumber;
		//	ratioValue		= oneItem ->m_probRatio; 			
		//	oneOutString	= QString("%1\t%2\t").arg(stateNumber).arg(ratioValue  ); 	
		//	outf << oneOutString  ;
		}
	
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Symbol StateList: Log ratio probability, this state to all others, states in normal order 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	outf << endl << endl << "\n\n** Symbol StateList: Log ratio probability, this state to all others, states in normal order **" << endl; 
	for ( i=0; i< m_countOfSymbols; i++)
	{
		thisSymbol	= m_symbolList[i]; 		
		oneList		= m_symbolStateList[i];

		outf <<endl << thisSymbol<< " "; 

		for (stateNumber= 0; stateNumber < m_countOfStates; stateNumber++  )
		{	
			for ( oneItem=oneList ->first(); oneItem != 0; oneItem=oneList ->next()) // this "unsorts"  the list
			{
				thisStateNumber = oneItem ->m_stateNumber;
				if ( thisStateNumber == stateNumber )
				{
					ratioValue = oneItem ->m_probRatio; 					
					oneOutString = QString("%1\t%2\t").arg(stateNumber).arg(ratioValue  ); 	
					outf << oneOutString  ;
				}
			}
		}
	
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// JG: Output ordered list of symbols for each state.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	double*	SymbolEmissions; SymbolEmissions = NULL;
	int*	SortedOutput; SortedOutput = NULL;

	outf << "\n\n** Each state: ordered emissions **"; 
	for (i = 0; i < m_countOfStates; i++)
	{
		outf << endl << "\nState " << i;
		if ( SymbolEmissions)	{ delete SymbolEmissions; }
		if ( SortedOutput	)	{ delete SortedOutput;    }
		SymbolEmissions = new double[ m_countOfSymbols];
		SortedOutput	= new int   [m_countOfSymbols];
		
		for (j = 0; j < m_countOfSymbols; j++)
		{
			SymbolEmissions[j] = m_B[i][j];
		}
		SortVector (SortedOutput, SymbolEmissions, m_countOfSymbols);
		
		for (j = 0; j < m_countOfSymbols; j++)
		{
			outf << endl <<   
			m_symbolList[SortedOutput[j]] << "\t"<<   
			m_B[i][SortedOutput[j]];
		}

	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	outf <<endl <<endl<<endl; 
	file.close(); 

}


// --------------------------------- For graphical display --------------------------//
 
/*
void StateEmitHMM::Display ()
{
//	m_Video;

	int				NumberOfSymbols;
	int				NumberOfStates;
	double**		ptrData;
	IntToString		listOfSymbols; 
	int				i,j; 
	int				NumberOfIterations =100; 

	NumberOfSymbols = m_Video->GetNumberOfDataPoints(); 
	NumberOfStates  = m_Video->GetDimensionality(); 

	// Update the GraphicView to Display the HMM multidimension data
	ptrData = new double*[ NumberOfSymbols ];
	for ( i=0; i<NumberOfSymbols; i++)
	{
		ptrData[i] = new double[NumberOfStates] ;
	}

	// assign initial ptrData
	for(i=0; i<NumberOfSymbols;i++)
	{
		listOfSymbols.insert(i, QString("s%1").arg(i)); 
		for(j=0; j<NumberOfStates; j++)
		{
			ptrData[i][j] = 1.0 / NumberOfStates; 
		}
	}

	// Iterations...
	
	for ( pFrame = m_Video->first(); pFrame; pFrame = m_Video->next() )
	{

		// Display on Graphic View
		updateSmallGraphicDisplaySlotForMultiDimensionData(NumberOfStates, 
														NumberOfSymbols,
														ptrData, 
														listOfSymbols); 


 		
		// Sleep for a short time : Is there any Qt sleep function ?
		int			dummy; 
		for(j=0; j<500000; j++)
		{
			dummy++;
			dummy--; 
		}

	}
	//clean ptrData
	for(i=0; i<NumberOfSymbols; i++)
	{
		delete [] ptrData[i];	
	}

	delete []ptrData; 

}
*/

