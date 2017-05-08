// Implementation of mTVolca methods
// Copyright © 2009 The University of Chicago
#include "mTVolca.h"

#include <Q3FileDialog>
#include <QMessageBox>
#include <Q3TextStream>
#include <QFile>
#include <QString>
#include "Typedefs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

mTVolca::mTVolca(cMT* myMT, QString projectDirectory)
{
	m_myMT = myMT;
	m_projectDirectory = projectDirectory; 

	m_language1TotalWords =0; 
	m_language2TotalWords =0; 
	
	m_language1FileName = "";
	m_language2FileName = "";

	m_countOfSentences = 0; 
}


mTVolca::~mTVolca()
{
	// To do clean

}

void	mTVolca::initVolList()
{

	m_language1Words.clear();
	m_language2Words.clear();
	m_language1WordIndex.clear();
	m_language2WordIndex.clear();


	QString					language1FileName;
	QString					language2FileName;
	QFile*					language1File;
	QFile*					language2File;
	QString					oneWord; 
	int						wordIndex; 
	StringToInt::iterator	StringToIntIt; 
	

	language1FileName = Q3FileDialog::getOpenFileName( m_projectDirectory,
												   "Text File (*.txt);;All files (*.*);;Corpus File (*.corpus)",
												   NULL,
												   "open file dialog",
												   "Choose Language1 corpus" );

	language2FileName = Q3FileDialog::getOpenFileName( m_projectDirectory,
												   "Text File (*.txt);;All files (*.*);;Corpus File (*.corpus)",
												   NULL,
												   "open file dialog",
												   "Choose Language2 corpus" );


	m_language1FileName = language1FileName;
	m_language2FileName = language2FileName;

	language1File = new QFile( language1FileName );
    if ( language1File->open( QIODevice::ReadOnly ) )
	{
		Q3TextStream stream( language1File );
		stream.setEncoding( Q3TextStream::Locale );
		
		while( !stream.atEnd() )
		{
			stream >> oneWord; 

			// a little filtering
			if (oneWord.length() >0 && oneWord != QString(".") && oneWord != QString(","))
			{
				m_language1Words.insert(oneWord, 0);
			}
		}

		
		m_language1TotalWords = m_language1Words.size(); 
		
		wordIndex =0; 
		for ( StringToIntIt = m_language1Words.begin(); StringToIntIt != m_language1Words.end(); StringToIntIt++ )
		{
			oneWord = StringToIntIt.key(); 
			m_language1Words[oneWord] = wordIndex;
			m_language1WordIndex.insert(wordIndex, oneWord); 
			wordIndex++;
		}

		StringToIntIt--;
		wordIndex = StringToIntIt.data(); 

		//QMessageBox::information ( NULL, "Linguistica : MT Model1", QString("The total is %1 and last index is %2.").arg(m_language1TotalWords).arg(wordIndex), "OK" );

		language1File ->close(); 
	}
	else
	{
		QMessageBox::information ( NULL, "Linguistica : MT Model1", "Can't Open Language 1 Corpus !", "OK" );
		return; 
	}

	language2File = new QFile( language2FileName );
    if ( language2File->open( QIODevice::ReadOnly ) )
	{
		Q3TextStream stream( language2File );
		stream.setEncoding( Q3TextStream::Locale );
		
		while( !stream.atEnd() )
		{
			stream >> oneWord; 

			// a little filtering
			if (oneWord.length() >0 && oneWord != QString(".") && oneWord != QString(","))
			{
				m_language2Words.insert(oneWord, 0);
			}
		}

		m_language2TotalWords = m_language2Words.size(); 
		
		wordIndex =0; 
		for ( StringToIntIt = m_language2Words.begin(); StringToIntIt != m_language2Words.end(); StringToIntIt++ )
		{
			oneWord = StringToIntIt.key(); 
			m_language2Words[oneWord] = wordIndex;
			m_language2WordIndex.insert(wordIndex, oneWord); 
			wordIndex++;
		}

		StringToIntIt--;
		wordIndex = StringToIntIt.data(); 

		//QMessageBox::information ( NULL, "Linguistica : MT Model1", QString("The total is %1 and last index is %2.").arg(m_language2TotalWords).arg(wordIndex), "OK" );

		language2File ->close(); 

	}
	else
	{
		QMessageBox::information ( NULL, "Linguistica : MT Model1", "Can't Open Language 2 Corpus !", "OK" );
		return; 
	}


}


void	mTVolca::readSentences()
{
	
	int							countOfLanguage1Sentence,countOfLanguage2Sentence;
	QFile*						language1File;
	QFile*						language2File;
	QString						oneLine; 
	QString						oneWord; 
	int							indexInsideSentence; 
	int							idOfTheWord; 
	IntToInt*					oneSentence; 


	
	countOfLanguage1Sentence =0; 
	language1File = new QFile( m_language1FileName );
    if ( language1File->open( QIODevice::ReadOnly ) )
	{
		Q3TextStream stream( language1File );
		stream.setEncoding( Q3TextStream::Locale );
		
		while( !stream.atEnd() )
		{
			oneLine = stream.readLine(); 		
			

			Q3TextStream lineStream( &oneLine, QIODevice::ReadOnly );

			indexInsideSentence = 0; 
			oneSentence = new IntToInt(); 
			while ( ! lineStream.atEnd())
			{
				lineStream >> oneWord; 	

				if (oneWord.length() >0 && oneWord != QString(".") && oneWord != QString(","))
				{
					idOfTheWord = m_language1Words[oneWord];
					oneSentence ->insert(indexInsideSentence, idOfTheWord);	
					indexInsideSentence++; 
				}
			}
			
			if ( indexInsideSentence >= 1)
			{
				m_language1Sentences.insert(countOfLanguage1Sentence,oneSentence);  
				countOfLanguage1Sentence++;
			}
			else
			{
				delete oneSentence;
			}
		}

	}
	else
	{
		QMessageBox::information ( NULL, "Linguistica : MT Model1", "Can't Open Language 1 Corpus !", "OK" );
		return;
	}


	countOfLanguage2Sentence =0; 
	language2File = new QFile( m_language2FileName );
    if ( language2File->open( QIODevice::ReadOnly ) )
	{
		Q3TextStream stream( language2File );
		stream.setEncoding( Q3TextStream::Locale );
		
		while( !stream.atEnd() )
		{
			oneLine = stream.readLine(); 		
			

			Q3TextStream lineStream( &oneLine, QIODevice::ReadOnly );

			indexInsideSentence = 0; 
			oneSentence = new IntToInt(); 
			while ( ! lineStream.atEnd())
			{
				lineStream >> oneWord; 	

				if (oneWord.length() >0 && oneWord != QString(".") && oneWord != QString(","))
				{
					idOfTheWord = m_language2Words[oneWord];
					oneSentence ->insert(indexInsideSentence, idOfTheWord);	
					indexInsideSentence++; 
				}
			}
			
			if ( indexInsideSentence >= 1)
			{
				m_language2Sentences.insert(countOfLanguage2Sentence,oneSentence);  
				countOfLanguage2Sentence++;
			}
			else
			{
				QMessageBox::information ( NULL, "Linguistica : MT Model1 Error", QString("At Sentence %1").arg(countOfLanguage2Sentence), "OK" );
				delete oneSentence;
			}
		}

	}
	else
	{
		QMessageBox::information ( NULL, "Linguistica : MT Model1", "Can't Open Language 2 Corpus !", "OK" );
		return;
	}


	if ( countOfLanguage1Sentence != countOfLanguage2Sentence )
	{
		QMessageBox::information ( NULL, "Linguistica : MT Model1", "Language1 Sentence# != Language2 Sentence#!", "OK" );
		// To do  Clean sentences 
		return;
	}

	m_countOfSentences = countOfLanguage1Sentence;


	//QMessageBox::information ( NULL, "Linguistica : MT Model1", QString("Read In %1 sentences !").arg(m_countOfSentences), "OK" );
 

	// Debug
	/*
	QString								oneSentenceStr; 
	QString								oneVolcaWord; 
	QString								twoVolcaWord; 
	int									oneWordId; 
	int									count; 
	int									i; 

		
	oneSentence = m_language1Sentences[1];
	count = oneSentence ->size(); 
	

	oneSentenceStr = "";
	for ( i=0; i < count; i++)
	{
		oneWordId = (*oneSentence)[i];
		oneSentenceStr += QString("%1-").arg(oneWordId);
	}

	
	QMessageBox::information ( NULL, "Linguistica : MT Model1", "Lan1 Sentence 1 is: " +  oneSentenceStr, "OK" );

	oneSentence = m_language2Sentences[1];
	count = oneSentence ->size(); 
	

	oneSentenceStr = "";
	for ( i=0; i < count; i++)
	{
		oneWordId = (*oneSentence)[i];
		oneSentenceStr += QString("%1-").arg(oneWordId);
	}

	QMessageBox::information ( NULL, "Linguistica : MT Model1", "Lan2 Sentence 1 is: " +  oneSentenceStr, "OK" );
	*/

}

void	mTVolca::setFastSearchPairsForT()
{
	QString								fastSearchPairs; 
	int									i, l, m;
	int									idOfOneLanguage1Word;
	int									idOfOneLanguage2Word;
	IntToInt*							oneLan1Sentence;
	IntToInt*							oneLan2Sentence;
	IntToDouble*						lan2WordsForOneLan1Word; 
	IntToDouble*						softCountLan2WordsForOneLan1Word; 



	for ( i=0; i < m_countOfSentences; i++)
	{
		oneLan1Sentence = m_language1Sentences[i];
		oneLan2Sentence = m_language2Sentences[i];
			
		for ( l=0; l< static_cast <int> (oneLan1Sentence ->size() ); l++)
		{
			idOfOneLanguage1Word = (*oneLan1Sentence)[l];

			if ( m_fastWordsPairs.contains(idOfOneLanguage1Word))
			{
				lan2WordsForOneLan1Word = m_fastWordsPairs[idOfOneLanguage1Word];
			}
			else
			{
				lan2WordsForOneLan1Word = new IntToDouble();
				m_fastWordsPairs.insert(idOfOneLanguage1Word, lan2WordsForOneLan1Word); 
			}

			if ( m_fastWordsSoftCounts.contains(idOfOneLanguage1Word))
			{
				softCountLan2WordsForOneLan1Word = m_fastWordsSoftCounts[idOfOneLanguage1Word];
			}
			else
			{
				softCountLan2WordsForOneLan1Word = new IntToDouble();
				m_fastWordsSoftCounts.insert(idOfOneLanguage1Word, softCountLan2WordsForOneLan1Word); 
			}

			for ( m=0; m < static_cast <int> ( oneLan2Sentence ->size() ); m++)
			{
				idOfOneLanguage2Word = (*oneLan2Sentence)[m];

				lan2WordsForOneLan1Word ->insert(idOfOneLanguage2Word, 0.0); 
				softCountLan2WordsForOneLan1Word ->insert(idOfOneLanguage2Word, 0.0); 
			}
		}
	
	}

	QMessageBox::information ( NULL, "Linguistica : MT Model1", "Finished Indexing the Word Pairs", "OK" );

} 


void	mTVolca::clearSentenceViterbiAlignment()
{
	IntToIntToInt::iterator			IntToIntToIntIt;
	IntToInt*						oneAlignment; 			

	for ( IntToIntToIntIt = m_sentenceAlignments.begin(); IntToIntToIntIt != m_sentenceAlignments.end(); IntToIntToIntIt++)
	{
		oneAlignment = IntToIntToIntIt.data();
		delete oneAlignment;
	}

	m_sentenceAlignments.clear(); 
}

