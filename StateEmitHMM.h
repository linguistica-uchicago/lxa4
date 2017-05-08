// Hidden Markov model
// Copyright © 2009 The University of Chicago
#ifndef STATEEMITHMM_H
#define STATEEMITHMM_H

#include <QString>
#include <QMap>
#include "generaldefinitions.h"
#include "Typedefs.h"

class LinguisticaMainWindow; 
class CParse; 
class hmmForSortingItem;
class CPhoneCollection;
class CWordCollection; 
class VideoFrame;

template<class V> class Q3SortedList;

typedef Q3SortedList<hmmForSortingItem> hmmSortedList;
typedef QMap<int, hmmSortedList*> IntTohmmSortedList; 
typedef QMap<int, CParse*> IntToParse;
typedef QMap<int, void*> IntToVoid;
typedef QMap<int, int*> IntToIntArray;
typedef QMap<int, int> IntToInt;
typedef QMap<QString, int> QStringToInt;
 
class Video; 
 
class StateEmitHMM  
{

public:
	class LinguisticaMainWindow*			m_parent; 
	class CLexicon*						m_Lexicon;

	// Construction Parameters
	int								m_countOfStates;
	int								m_countOfSymbols;
	int								m_lengthOfObservation;
	int								m_maxLengthOfObservation;
	int								m_NumberOfIterations; 
	int								m_countOfDataItems; 
	QString							m_HMMLog; 
	QString							m_HMMLogDirectory;
	eHmmDataType					m_dataType; 

	Video*							m_Video;


	// Vocabulary List
	IntToString						m_symbolList;
	StringToInt						m_symbolIndex; 


	// Train Data
	IntToParse						m_trainingData; 
	IntToIntArray					m_encodedTrainingData; 
	IntToVoid						m_trainingDataSource;  
	QStringToInt					m_trainingDataIndices;
	IntToInt						m_trainingDataFrequency;
	IntToInt						m_trainingDataSizes;
	int*							m_trainingDatum; 
	void*							m_trainingDatumSource; // a pointer to the Object that provided the data

	// prob parameters
	double*							m_PI;
	double**						m_A;
	double**						m_B;
	double**						m_Alpha;
	double**						m_Beta; 
	double***						m_P; 

	// soft counts
	double*							m_PI_SoftCounts; // state i softcounts
	double**						m_A_SoftCounts; // state i --> state j softcounts
	double**						m_B_SoftCounts; // state i --> symbol j softcounts
	double*							m_Entropy;		// Entropy of each state's emissions

	// probability of data
	double*							m_WordProbabilities; // could be total Forward probl, or Viterbi; one for each data item

	// For next use, output
	IntTohmmSortedList				m_symbolStateList; 

	// Results	
	double							m_LogProbabilityOfData;

public:
	StateEmitHMM(LinguisticaMainWindow*);
	StateEmitHMM(CLexicon*);

	virtual ~StateEmitHMM();

	// init function
	bool	preprocessData(eHmmDataType, void*); // type =1 : take PhoneTier1; type =2 take PhoneTier2, type=3 take CParse
	void	init(int, int loops = 1000 ); 
	void	initPiAndAB(); 

	// forward procedure
	void	forward(int, double&);
	
	// backward procedure
	void	backward(int, double&); 

	// Expectation procedure
	void	Expectation(int); 

	// Total Maximization procedure
	void	Maximization(); 

	// Train procedure
	double	trainParameters(); 

	// clear function
	void	clear(); 

	// compute a symbol's state list
	void	getStateListForASymbol(); 

	// Log function
	void	logInfo(double totalLogProbability); 
	void	OutputTransitions(int IterationNumber, QString FileName);
	void	OutputTransitionsToLogFile(int IterationNumber, QString FileName);
	void	OutputEmissions(int IterationNumber, QString LogFileName);
	void	OutputInitials(int IterationNumber, QString LogFileName );

	// Totals
	double	GetLogProbability() { return m_LogProbabilityOfData; }

	// Output to VideoFrame
	void	InsertValues ( VideoFrame* );
	void	Display( );
};


class hmmForSortingItem
{
public:
	int						m_stateNumber; 
	double					m_probRatio;
	
public:
	hmmForSortingItem(){};
	~hmmForSortingItem(){};

	hmmForSortingItem(int	stateNumber, double probRatio)
	{
		m_stateNumber = stateNumber;
		m_probRatio = probRatio;
	};



	bool	operator<(const hmmForSortingItem& another) 
	{	
		return (m_probRatio > another.m_probRatio); 
	};
	
		
	bool	operator==(const hmmForSortingItem& another) 
	{
		return (m_probRatio == another.m_probRatio);
	};

};


#endif // STATEEMITHMM_H
