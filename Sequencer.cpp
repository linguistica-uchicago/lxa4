// Implementation of CSequencer methods
// Copyright © 2009 The University of Chicago
#include "Sequencer.h"

#include <QMessageBox>
#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "log2.h"


CSequencer::CSequencer()
{
	m_bigrams.clear();
	m_bigramsbase.clear();
	m_trigrams.clear();
	m_totalbigrams =0;
	m_totaltrigrams =0;

	separator = QString("?_?");
	m_K		= 3;

}

CSequencer::CSequencer(LinguisticaMainWindow* parent)
{
	m_parent = parent; 
	m_bigrams.clear();
	m_bigramsbase.clear();
	m_trigrams.clear();
	m_totalbigrams =0;
	m_totaltrigrams =0;

	separator = QString("?_?");
	m_K		= 10;
	m_resultK = 10;
	m_maxlineintrain = 2000;
	m_maxlineintest = 10;
}


CSequencer::~CSequencer()
{


}


void CSequencer::readCorpus()
{
	
	QString							sequenceTrainFileName; 
	QString							oneLine; 
	QString							firstWord, secondWord, thirdWord;  
	QString							leftWord, rightWord; 
	QString							oneBigram, oneTrigram;
	QString							oneTrigrambase; 
	int								numberOfLines;
	int								loc; 
	int								indexOfWord; 
	int								oneNumber; 
	StringToInt::Iterator			StringToIntIt;
	StringToDouble::Iterator		StringToDoubleIt;
	



	sequenceTrainFileName = Q3FileDialog::getOpenFileName( sequenceTrainFileName,
												 "TXT Files (*.txt)",
												 NULL,
												 "open file dialog",
												 "Choose a train file to open" );


	if ( sequenceTrainFileName.isEmpty() )
	{
		return; 
	}

	m_bigrams.clear();
	m_bigramsbase.clear();
	m_bigramprob.clear(); 
	m_trigrams.clear();
	m_trigramsbase.clear();
	m_trigramprob.clear();
	m_totalbigrams =0;
	m_totaltrigrams =0;
	m_totalbigramsbase =0; 
	m_totaltrigramsbase =0;


	Q_ASSERT(!sequenceTrainFileName.isEmpty());
	QFile trainFile(sequenceTrainFileName);

	if ( trainFile.open( QIODevice::ReadOnly ) ) 
	{
		Q3TextStream trainStream( &trainFile );
		//trainStream.setEncoding( QTextStream::Unicode );

		numberOfLines = 0; 
		while(!trainStream.atEnd())
		{
			oneLine = trainStream.readLine(); // This is one sentence. 
			

			if ( oneLine.length() == 0)
			{
				continue;
			}


			oneLine = oneLine.lower(); 
			oneLine = oneLine.stripWhiteSpace(); 
			oneLine = oneLine.simplifyWhiteSpace(); 
			
			firstWord = "#";
			secondWord = "";
			thirdWord = "";
			indexOfWord = -1; 

			loc = oneLine.find(" "); 
			while(loc != -1)
			{
				leftWord = oneLine.left(loc);
				rightWord = oneLine.right(oneLine.length() - loc - 1);
				
				indexOfWord++; 

				if ( indexOfWord == 0)
				{
					secondWord = leftWord; 
					oneBigram = firstWord + separator  + secondWord;
					if ( m_bigrams.contains(oneBigram))
					{
						m_bigrams[oneBigram]++;
					}
					else
					{
						m_bigrams.insert(oneBigram, 1); 
					}

					if ( m_bigramsbase.contains(firstWord))
					{
						m_bigramsbase[firstWord]++;

					}
					else
					{
						m_bigramsbase.insert(firstWord, 1); 
					}

					m_totalbigrams++;
					m_totalbigramsbase++; 

				}
				else
				{
					thirdWord = leftWord;
					
					oneBigram = secondWord + separator + thirdWord;
					oneTrigram = firstWord + separator + secondWord + separator + thirdWord;
					oneTrigrambase = firstWord + separator + secondWord; 


					// add into bigram
					if ( m_bigrams.contains(oneBigram))
					{
						m_bigrams[oneBigram]++;
					}
					else
					{
						m_bigrams.insert(oneBigram, 1); 
					}

					if ( m_bigramsbase.contains(secondWord))
					{
						m_bigramsbase[secondWord]++;

					}
					else
					{
						m_bigramsbase.insert(secondWord, 1); 
					}

					m_totalbigrams++;
					m_totalbigramsbase++; 

					// add into trigram
					if ( m_trigrams.contains(oneTrigram))
					{
						m_trigrams[oneTrigram]++;
					}
					else
					{
						m_trigrams.insert(oneTrigram, 1); 
					}

					if ( m_trigramsbase.contains(oneTrigrambase))
					{
						m_trigramsbase[oneTrigrambase]++;

					}
					else
					{
						m_trigramsbase.insert(oneTrigrambase, 1); 
					}
				
					m_totaltrigrams++;
					m_totaltrigramsbase++; 

					// Move the first,second words
					firstWord = secondWord;
					secondWord = thirdWord; 

				}



				oneLine = rightWord; 
				loc = oneLine.find(" "); 
			}


			leftWord = oneLine;
			
			indexOfWord++; 

			if ( leftWord == QString("."))
			{

				Q_ASSERT(indexOfWord > 0); // make sure we don't get a line like "."	
			
				thirdWord = leftWord;
				
				oneBigram = secondWord + separator + thirdWord;
				oneTrigram = firstWord + separator + secondWord + separator + thirdWord;
				oneTrigrambase = firstWord + separator + secondWord; 


				// add into bigram
				if ( m_bigrams.contains(oneBigram))
				{
					m_bigrams[oneBigram]++;
				}
				else
				{
					m_bigrams.insert(oneBigram, 1); 
				}

				if ( m_bigramsbase.contains(secondWord))
				{
					m_bigramsbase[secondWord]++;

				}
				else
				{
					m_bigramsbase.insert(secondWord, 1); 
				}

				m_totalbigrams++;
				m_totalbigramsbase++; 

				// add into trigram
				if ( m_trigrams.contains(oneTrigram))
				{
					m_trigrams[oneTrigram]++;
				}
				else
				{
					m_trigrams.insert(oneTrigram, 1); 
				}

				if ( m_trigramsbase.contains(oneTrigrambase))
				{
					m_trigramsbase[oneTrigrambase]++;

				}
				else
				{
					m_trigramsbase.insert(oneTrigrambase, 1); 
				}
			
				m_totaltrigrams++;
				m_totaltrigramsbase++;

			}
			else
			{
				if ( leftWord.right(1) == QString("."))
				{
					if ( indexOfWord == 0)
					{
						secondWord = leftWord.left(leftWord.length() -1);
						
						oneBigram = firstWord + separator  + secondWord;
						if ( m_bigrams.contains(oneBigram))
						{
							m_bigrams[oneBigram]++;
						}
						else
						{
							m_bigrams.insert(oneBigram, 1); 
						}

						if ( m_bigramsbase.contains(firstWord))
						{
							m_bigramsbase[firstWord]++;

						}
						else
						{
							m_bigramsbase.insert(firstWord, 1); 
						}

						m_totalbigrams++;
						m_totalbigramsbase++; 

					}
					else
					{
						thirdWord = leftWord.left(leftWord.length() -1);
						
						oneBigram = secondWord + separator + thirdWord;
						oneTrigram = firstWord + separator + secondWord + separator + thirdWord;
						oneTrigrambase = firstWord + separator + secondWord; 


						// add into bigram
						if ( m_bigrams.contains(oneBigram))
						{
							m_bigrams[oneBigram]++;
						}
						else
						{
							m_bigrams.insert(oneBigram, 1); 
						}

						if ( m_bigramsbase.contains(secondWord))
						{
							m_bigramsbase[secondWord]++;

						}
						else
						{
							m_bigramsbase.insert(secondWord, 1); 
						}
						
						m_totalbigrams++;
						m_totalbigramsbase++; 

						// add into trigram
						if ( m_trigrams.contains(oneTrigram))
						{
							m_trigrams[oneTrigram]++;
						}
						else
						{
							m_trigrams.insert(oneTrigram, 1); 
						}

						if ( m_trigramsbase.contains(oneTrigrambase))
						{
							m_trigramsbase[oneTrigrambase]++;

						}
						else
						{
							m_trigramsbase.insert(oneTrigrambase, 1); 
						}
					
						m_totaltrigrams++;
						m_totaltrigramsbase++;

						// Move the first,second words
						firstWord = secondWord;
						secondWord = thirdWord; 

					}
							
				}
				else
				{
				
					if ( indexOfWord == 0)
					{
						secondWord = leftWord;
						
						oneBigram = firstWord + separator  + secondWord;
						if ( m_bigrams.contains(oneBigram))
						{
							m_bigrams[oneBigram]++;
						}
						else
						{
							m_bigrams.insert(oneBigram, 1); 
						}

						if ( m_bigramsbase.contains(firstWord))
						{
							m_bigramsbase[firstWord]++;

						}
						else
						{
							m_bigramsbase.insert(firstWord, 1); 
						}

						m_totalbigrams++;
						m_totalbigramsbase++; 

					}
					else
					{
						thirdWord = leftWord;
						
						oneBigram = secondWord + separator + thirdWord;
						oneTrigram = firstWord + separator + secondWord + separator + thirdWord;
						oneTrigrambase = firstWord + separator + secondWord; 


						// add into bigram
						if ( m_bigrams.contains(oneBigram))
						{
							m_bigrams[oneBigram]++;
						}
						else
						{
							m_bigrams.insert(oneBigram, 1); 
						}

						if ( m_bigramsbase.contains(secondWord))
						{
							m_bigramsbase[secondWord]++;

						}
						else
						{
							m_bigramsbase.insert(secondWord, 1); 
						}
						
						m_totalbigrams++;
						m_totalbigramsbase++; 

						// add into trigram
						if ( m_trigrams.contains(oneTrigram))
						{
							m_trigrams[oneTrigram]++;
						}
						else
						{
							m_trigrams.insert(oneTrigram, 1); 
						}

						if ( m_trigramsbase.contains(oneTrigrambase))
						{
							m_trigramsbase[oneTrigrambase]++;

						}
						else
						{
							m_trigramsbase.insert(oneTrigrambase, 1); 
						}
					
						m_totaltrigrams++;
						m_totaltrigramsbase++; 

						// Move the first,second words
						firstWord = secondWord;
						secondWord = thirdWord; 

					}
				
				}

				
				// add the last "."
				Q_ASSERT(indexOfWord > 0); 
			
				thirdWord = QString(".");
				
				oneBigram = secondWord + separator + thirdWord;
				oneTrigram = firstWord + separator + secondWord + separator + thirdWord;
				oneTrigrambase = firstWord + separator + secondWord; 


				// add into bigram
				if ( m_bigrams.contains(oneBigram))
				{
					m_bigrams[oneBigram]++;
				}
				else
				{
					m_bigrams.insert(oneBigram, 1); 
				}

				if ( m_bigramsbase.contains(secondWord))
				{
					m_bigramsbase[secondWord]++;

				}
				else
				{
					m_bigramsbase.insert(secondWord, 1); 
				}

				m_totalbigrams++;
				m_totalbigramsbase++; 

				// add into trigram
				if ( m_trigrams.contains(oneTrigram))
				{
					m_trigrams[oneTrigram]++;
				}
				else
				{
					m_trigrams.insert(oneTrigram, 1); 
				}

				if ( m_trigramsbase.contains(oneTrigrambase))
				{
					m_trigramsbase[oneTrigrambase]++;

				}
				else
				{
					m_trigramsbase.insert(oneTrigrambase, 1); 
				}
			
				m_totaltrigrams++;
				m_totaltrigramsbase++; 


			}
			
			
			//oneLine = trainStream.readLine(); // This is the "return"

			numberOfLines++;
			m_parent ->setStatusBar1(QString("read line %1...").arg(numberOfLines));
			
			if ( numberOfLines > m_maxlineintrain )
			{
				break;
			}



		}
		//QMessageBox::information ( NULL, "Debug", QString("%1").arg(numberOfLines), "OK" );	

		trainFile.close(); 


		// Compute the bigram prob and trigram prob
		double			oneBigramProb; 
		double			oneTrigramProb;
		double			oneBaseProb; 
		QString			oneBase; 
		int				numberOfProcessed; 

		numberOfProcessed = 0; 
		for ( StringToIntIt = m_bigrams.begin(); StringToIntIt != m_bigrams.end();  StringToIntIt++)
		{
			oneBigram = StringToIntIt.key(); 
			oneNumber = StringToIntIt.data(); 
			
			oneBigramProb = (double)oneNumber / (double)m_totalbigrams;

			loc = oneBigram.find(separator);
			oneBase = oneBigram.left(loc);

			oneBaseProb = (double)(m_bigramsbase[oneBase]) / (double)(m_totalbigramsbase); 
			
			oneBigramProb = -base2log(oneBigramProb / oneBaseProb); 

			m_bigramprob.insert(oneBigram, oneBigramProb);
		
			numberOfProcessed++;
			m_parent ->setStatusBar1(QString("processing bigram %1...").arg(numberOfProcessed));

		}


		numberOfProcessed =0; 
		for ( StringToIntIt = m_trigrams.begin(); StringToIntIt != m_trigrams.end();  StringToIntIt++)
		{
			oneTrigram = StringToIntIt.key(); 
			oneNumber = StringToIntIt.data(); 
			
			oneTrigramProb = (double)oneNumber / (double)m_totaltrigrams;

			loc = oneTrigram.findRev(separator);
			oneBase = oneTrigram.left(loc);

			oneBaseProb = (double)m_trigramsbase[oneBase]/ (double)m_totaltrigramsbase; 
			
			oneTrigramProb = -base2log(oneTrigramProb / oneBaseProb); 

			m_trigramprob.insert(oneTrigram, oneTrigramProb);
		
			numberOfProcessed++;
			m_parent ->setStatusBar1(QString("processing trigram %1...").arg(numberOfProcessed));

		}

		m_parent ->setStatusBar1(QString(""));



		
		// Debug output bigrams and trigrams
		QString							bigramFileName = "bigrams.txt";
		QString							trigramFileName = "trigrams.txt";
		QString							oneKey;
		double							oneValue; 
		


		
		QFile bigramFile(bigramFileName);
		QFile trigramFile(trigramFileName);


		if ( bigramFile.open( QIODevice::WriteOnly ) ) 
		{
			Q3TextStream bigramStream( &bigramFile );


			for ( StringToDoubleIt = m_bigramprob.begin(); StringToDoubleIt != m_bigramprob.end(); StringToDoubleIt++)
			{
				oneKey = StringToDoubleIt.key();
				oneValue =StringToDoubleIt.data();
				oneKey = oneKey.replace(separator, " ");

				bigramStream << oneKey << "		" << oneValue << endl; 
			}
			
			bigramFile.close(); 

		
		}
		else
		{
		
		}


		if ( trigramFile.open( QIODevice::WriteOnly ) ) 
		{
			Q3TextStream trigramStream( &trigramFile );


			for ( StringToDoubleIt = m_trigramprob.begin(); StringToDoubleIt != m_trigramprob.end(); StringToDoubleIt++)
			{
				oneKey = StringToDoubleIt.key();
				oneValue =StringToDoubleIt.data();
				oneKey = oneKey.replace(separator, " ");

				trigramStream << oneKey << "		" << oneValue << endl; 
			}
			
			trigramFile.close(); 

		
		}
		else
		{
		
		}
	
	  
	}
	else
	{
		return; 
	}
	

}

void  CSequencer::sequencerTestAFile()
{
	
	if ( m_totalbigrams == 0)
	{
		QMessageBox::information ( NULL, "Warning","Please Read Training Corpus Firstly!", "OK" );
		return;
	}



	QString						sequenceTestFileName;
	

	sequenceTestFileName = Q3FileDialog::getOpenFileName( sequenceTestFileName,
												 "TXT Files (*.txt)",
												 NULL,
												 "open file dialog",
												 "Choose a train file to open" );


	if ( sequenceTestFileName.isEmpty() )
	{
		return; 
	}

	QFile							testFile(sequenceTestFileName);
	int								numberOfLines;
	QString							oneLine;
	int								oneBiScore, oneTriScore;
	int								totalHitInBigramList =0;
	int								totalHitInTrigramList=0;
	int								totalSentences =0;
	int								totalHitInBigramListSumRanks =0;
	int								totalHitInTrigramListSumRanks =0;
	double							averageBiRanking, averageTriRanking;


	if ( testFile.open( QIODevice::ReadOnly ) ) 
	{
		Q3TextStream testStream( &testFile );
		//testStream.setEncoding( QTextStream::Unicode );

		numberOfLines = 0; 
		while(!testStream.atEnd())
		{
			oneLine = testStream.readLine(); // This is one sentence. 
			
			if ( oneLine.length() == 0)
			{
				continue;
			}

			oneLine = oneLine.lower(); 
			oneLine = oneLine.stripWhiteSpace(); 
			oneLine = oneLine.simplifyWhiteSpace(); 

			if ( oneLine.length() ==0)
			{
				continue;
			}

			sequenceASentence(oneBiScore, oneTriScore, oneLine);
			totalSentences++;

			if ( oneBiScore != 0)
			{
				totalHitInBigramListSumRanks += oneBiScore;
				totalHitInBigramList++;
			}

			if ( oneTriScore != 0)
			{
				totalHitInTrigramListSumRanks += oneTriScore;
				totalHitInTrigramList++;
			}

			numberOfLines++;
			m_parent ->setStatusBar1(QString("testing sentence %1...").arg(numberOfLines));

			if ( numberOfLines > m_maxlineintest)
			{
				break;	
			}

		}

		m_parent ->setStatusBar1(QString(""));

		// Result Statics
		averageBiRanking = (double)totalHitInBigramListSumRanks /  totalHitInBigramList;
		averageTriRanking = (double)totalHitInTrigramListSumRanks /  totalHitInTrigramList;

		QMessageBox::information ( NULL, "Debug",QString("Total %1, Bi-Hit %2, Tri-Hit %3, RankingInBiHit %4, RankingInTriHit %5").\
								arg(totalSentences).arg(totalHitInBigramList).arg(totalHitInTrigramList).\
								arg(averageBiRanking).arg(averageTriRanking), "OK" );
		

		

	}
	else
	{
		return;
	}


} 



void CSequencer::sequenceASentence(int& biRank, int& triRank, QString inputSentence)
{
	QString							aSentence;
	bool							ok; 
	int								loc; 
	int								numberOfWords; 
	StringToInt						bagOfWords; 
	StringToInt						currentBagOfWords;
	StringToInt::Iterator			StringToIntIt1, StringToIntIt2 ;
	QString							rightSentence;
	QString							oneWord, twoWord; 
	QString							oneBigram, bestBigram; 
	bool							reasonablePair; 
	int								count; 
	double							bigramcount, bestbigramcount;
	SortedSentences					finalRankedSentences;
	SortedSentences					biResultRankedSentences;
	SortedSentences					triResultRankedSentences;
	sentenceItem*					oneSentenceItem;
	QString							resultSentence;
	int								resultRanki; 
	bool							getInputFromUI;



	finalRankedSentences.setAutoDelete(FALSE);
	biResultRankedSentences.setAutoDelete(TRUE);
	triResultRankedSentences.setAutoDelete(TRUE);

	if ( m_totalbigrams == 0)
	{
		QMessageBox::information ( NULL, "Warning","Please Read Training Corpus Firstly!", "OK" );
		return;
	}

	bagOfWords.clear(); 


	if ( inputSentence.length() ==0)
	{
		aSentence = QInputDialog::getText(
            "Sequencer_ASentence", "Enter a Sentence", QLineEdit::Normal,
            QString::null, &ok, NULL );
		
		getInputFromUI = true;
	}
	else
	{
		aSentence = inputSentence;
		ok = true;
		getInputFromUI = false;
	}

	if ( ok && !aSentence.isEmpty() ) 
	{
		// Parse this sentence into words
		QString				leftWord, rightWord; 
		


		aSentence = aSentence.lower(); 
		aSentence = aSentence.stripWhiteSpace(); 
		aSentence = aSentence.simplifyWhiteSpace();

		rightSentence = QString("#");

		numberOfWords = 0; 
		loc = aSentence.find(" "); 
		while(loc != -1)
		{
			leftWord = aSentence.left(loc);
			rightWord = aSentence.right(aSentence.length() - loc - 1);
						
			if (( leftWord != QString("#")) && (leftWord != QString(".")))
			{
			
				if ( bagOfWords.contains(leftWord))
				{
					bagOfWords[leftWord]++;
				}
				else
				{
					bagOfWords.insert(leftWord, 1); 
				}

				rightSentence = rightSentence + " " + leftWord;
				numberOfWords++; 
			}

			aSentence = rightWord; 
			loc = aSentence.find(" "); 
		}

		leftWord = aSentence; 

		if ( leftWord != QString("."))
		{
			if (leftWord.right(1) == QString("."))
			{
				leftWord = leftWord.left(leftWord.length() -1); 
			}

			if (( leftWord != QString("#")) && (leftWord != QString(".")))
			{

				if ( bagOfWords.contains(leftWord))
				{
					bagOfWords[leftWord]++;
				}
				else
				{
					bagOfWords.insert(leftWord, 1); 
				}

				rightSentence = rightSentence + " " + leftWord;
				numberOfWords++; 

			}
		}


		rightSentence = rightSentence + " ." ;

		if ( numberOfWords == 1)
		{
			resultSentence = QString("# ") + (bagOfWords.begin()).key() + QString(" .") ;
			//QMessageBox::information ( NULL, "All-Debug",resultSentence, "OK" );	
			biRank = 1;
			triRank = 1;
			return; 
		}


		//QMessageBox::information ( NULL, "Debug",QString("bag of word has %1 words.").arg(numberOfWords), "OK" );
		
		bestbigramcount =0.0; 
		for ( StringToIntIt1 = bagOfWords.begin(); StringToIntIt1 != bagOfWords.end(); StringToIntIt1++)
		{
			oneWord = StringToIntIt1.key(); 
			count = StringToIntIt1.data(); 

			if ( count > 1)
			{
				reasonablePair = true;
			}
			else
			{
				reasonablePair = false;
			}

			for ( StringToIntIt2 = bagOfWords.begin(); StringToIntIt2 != bagOfWords.end(); StringToIntIt2++)
			{
				twoWord = StringToIntIt2.key(); 

				if (( !reasonablePair) && (oneWord != twoWord))
				{
					reasonablePair = true;
				}
				
				if ( !reasonablePair)
				{
					continue; 
				}

				oneBigram = oneWord + separator + twoWord; 

				if ( m_bigramprob.contains(oneBigram))
				{

					bigramcount = m_bigramprob[oneBigram];
									
					currentBagOfWords = bagOfWords;

					if (currentBagOfWords[oneWord] <= 1)
					{
						currentBagOfWords.remove(oneWord);
					}
					else
					{
						currentBagOfWords[oneWord]--;
					}

					if (currentBagOfWords[twoWord] <= 1)
					{
						currentBagOfWords.remove(twoWord);
					}
					else
					{
						currentBagOfWords[twoWord]--;
					}

					currentBagOfWords.insert(QString("#"), 1);
					currentBagOfWords.insert(QString("."), 1);

					
					// Test bigram sequencer
					
					sequenizeFromABigram(oneBigram, bigramcount, currentBagOfWords, numberOfWords, m_K, finalRankedSentences, 1);
					
					for ( oneSentenceItem=finalRankedSentences.first(); oneSentenceItem != 0; oneSentenceItem=finalRankedSentences.next())
					{
						biResultRankedSentences.append(oneSentenceItem);
					}


					finalRankedSentences.setAutoDelete(FALSE);
					finalRankedSentences.clear();
					

					// Test trigram sequencer
					
					sequenizeFromABigram(oneBigram, bigramcount, currentBagOfWords, numberOfWords, m_K, finalRankedSentences, 2);
					
					for ( oneSentenceItem=finalRankedSentences.first(); oneSentenceItem != 0; oneSentenceItem=finalRankedSentences.next())
					{
						triResultRankedSentences.append(oneSentenceItem);
					}
					
					finalRankedSentences.setAutoDelete(FALSE);
					finalRankedSentences.clear();
					

				}
				

			}

		
		}

	
		if ( biResultRankedSentences.count() != 0)
		{

			QFile file( "SequencerLog.txt" );
    
			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );

			outf << "******Bigram Results******" << endl <<endl; 



			QString				biResultKey;


			biResultRankedSentences.sort();

			resultRanki = 0; 
			biRank = resultRanki;
			for ( oneSentenceItem=biResultRankedSentences.first(); oneSentenceItem != 0; oneSentenceItem=biResultRankedSentences.next())
			{
				resultRanki++; 

				biResultKey = oneSentenceItem ->m_key;
				biResultKey.replace(separator, " ");
				
				if ( biResultKey == rightSentence)
				{
					biRank = resultRanki;
				}
				

				if ( resultRanki > m_resultK)
				{
					break;
				}


				// log history of this result sentence 
				outf << "Result Sentence Rank " << resultRanki << " : " << biResultKey << endl; 
				for ( int stepi = 1; stepi <= oneSentenceItem ->m_stepnumber; stepi++)
				{
					QString					oneHistoryString; 
					double					oneHistoryScore;

					oneHistoryString = oneSentenceItem ->m_historystrings[stepi];
					oneHistoryString = oneHistoryString.replace(separator, " ");
					oneHistoryScore = oneSentenceItem ->m_historyscores[stepi];

					outf << "	" << stepi << " : " << oneHistoryString << " : " <<  oneHistoryScore << endl; 
				
				}

				outf << endl; 

			}
			

			if ( getInputFromUI )
			{
			

				oneSentenceItem=biResultRankedSentences.first();

				biResultKey = oneSentenceItem ->m_key;
				biResultKey.replace(separator, " ");

				QMessageBox::information ( NULL, "Top Bigram Sequencer Output",biResultKey, "OK" );	
			
			}
			
			
		
			biResultRankedSentences.clear();
			
			file.close();
		}
		

		if ( triResultRankedSentences.count() != 0)
		{

			QFile file( "SequencerLog.txt" );
    
			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );

			outf << "******Trigram Results******" << endl <<endl; 


			QString				triResultKey;

			triResultRankedSentences.sort();

			resultRanki = 0; 
			triRank = resultRanki;
			for ( oneSentenceItem=triResultRankedSentences.first(); oneSentenceItem != 0; oneSentenceItem=triResultRankedSentences.next())
			{
				resultRanki++; 

				triResultKey = oneSentenceItem ->m_key;
				triResultKey.replace(separator, " ");
				
				if ( triResultKey == rightSentence)
				{
					triRank = resultRanki;
				}
				

				if ( resultRanki > m_resultK)
				{
					break;
				}

				// log history of this result sentence 
				outf << "Result Sentence Rank " << resultRanki << " : " << triResultKey << endl; 
				for ( int stepi = 1; stepi <= oneSentenceItem ->m_stepnumber; stepi++)
				{
					QString					oneHistoryString; 
					double					oneHistoryScore;

					oneHistoryString = oneSentenceItem ->m_historystrings[stepi];
					oneHistoryString = oneHistoryString.replace(separator, " ");
					oneHistoryScore = oneSentenceItem ->m_historyscores[stepi];

					outf << "	" << stepi << " : " << oneHistoryString << " : " <<  oneHistoryScore << endl; 
				
				}

				outf << endl; 


			}
			
			
			if ( getInputFromUI )
			{
				QString				triResultKey;

				oneSentenceItem=triResultRankedSentences.first();

				triResultKey = oneSentenceItem ->m_key;
				triResultKey.replace(separator, " ");

				QMessageBox::information ( NULL, "Top Trigram Sequencer Output",triResultKey, "OK" );	
			
			}
		
		
			triResultRankedSentences.clear();

			file.close(); 
		}
		


	} 
	else 
	{
		return;     
    }


}

void CSequencer::sequenceASentence2(int& biRank, int& triRank, QString inputSentence)
{
	QString							aSentence;
	bool							ok; 
	int								loc; 
	int								numberOfWords; 
	StringToDouble					allBigrams;
	StringToInt						bagOfWords; 
	StringToInt						currentBagOfWords;
	StringToInt::Iterator			StringToIntIt1, StringToIntIt2 ;
	QString							rightSentence;
	QString							oneWord, twoWord; 
	QString							oneBigram, bestBigram; 
	bool							reasonablePair; 
	int								count; 
	double							bigramcount, bestbigramcount;
	SortedSentences					finalRankedSentences;
	SortedSentences					biResultRankedSentences;
	SortedSentences					triResultRankedSentences;
	sentenceItem*					oneSentenceItem, *twoSentenceItem;
	QString							resultSentence;
	int								resultRanki; 
	bool							getInputFromUI;
	IntToString						currentHistoryString;
	IntToDouble						currentHistoryScore;
	



	finalRankedSentences.setAutoDelete(FALSE);
	biResultRankedSentences.setAutoDelete(TRUE);
	triResultRankedSentences.setAutoDelete(TRUE);

	if ( m_totalbigrams == 0)
	{
		QMessageBox::information ( NULL, "Warning","Please Read Training Corpus Firstly!", "OK" );
		return;
	}

	bagOfWords.clear(); 


	if ( inputSentence.length() ==0)
	{
		aSentence = QInputDialog::getText(
            "Sequencer_ASentence", "Enter a Sentence", QLineEdit::Normal,
            QString::null, &ok, NULL );
		
		getInputFromUI = true;
	}
	else
	{
		aSentence = inputSentence;
		ok = true;
		getInputFromUI = false;
	}

	if ( ok && !aSentence.isEmpty() ) 
	{
		// Parse this sentence into words
		QString				leftWord, rightWord; 
		


		aSentence = aSentence.lower(); 
		aSentence = aSentence.stripWhiteSpace(); 
		aSentence = aSentence.simplifyWhiteSpace();

		rightSentence = QString("#");

		numberOfWords = 0; 
		loc = aSentence.find(" "); 
		while(loc != -1)
		{
			leftWord = aSentence.left(loc);
			rightWord = aSentence.right(aSentence.length() - loc - 1);
						
			if (( leftWord != QString("#")) && (leftWord != QString(".")))
			{
			
				if ( bagOfWords.contains(leftWord))
				{
					bagOfWords[leftWord]++;
				}
				else
				{
					bagOfWords.insert(leftWord, 1); 
				}

				rightSentence = rightSentence + " " + leftWord;
				numberOfWords++; 
			}

			aSentence = rightWord; 
			loc = aSentence.find(" "); 
		}

		leftWord = aSentence; 

		if ( leftWord != QString("."))
		{
			if (leftWord.right(1) == QString("."))
			{
				leftWord = leftWord.left(leftWord.length() -1); 
			}

			if (( leftWord != QString("#")) && (leftWord != QString(".")))
			{

				if ( bagOfWords.contains(leftWord))
				{
					bagOfWords[leftWord]++;
				}
				else
				{
					bagOfWords.insert(leftWord, 1); 
				}

				rightSentence = rightSentence + " " + leftWord;
				numberOfWords++; 

			}
		}


		rightSentence = rightSentence + " ." ;

		if ( numberOfWords == 1)
		{
			resultSentence = QString("# ") + (bagOfWords.begin()).key() + QString(" .") ;
			//QMessageBox::information ( NULL, "All-Debug",resultSentence, "OK" );	
			biRank = 1;
			triRank = 1;
			return; 
		}


		//QMessageBox::information ( NULL, "Debug",QString("bag of word has %1 words.").arg(numberOfWords), "OK" );
		
		bestbigramcount =0.0; 
		for ( StringToIntIt1 = bagOfWords.begin(); StringToIntIt1 != bagOfWords.end(); StringToIntIt1++)
		{
			oneWord = StringToIntIt1.key(); 
			count = StringToIntIt1.data(); 

			if ( count > 1)
			{
				reasonablePair = true;
			}
			else
			{
				reasonablePair = false;
			}

			for ( StringToIntIt2 = bagOfWords.begin(); StringToIntIt2 != bagOfWords.end(); StringToIntIt2++)
			{
				twoWord = StringToIntIt2.key(); 

				if (( !reasonablePair) && (oneWord != twoWord))
				{
					reasonablePair = true;
				}
				
				if ( !reasonablePair)
				{
					continue; 
				}

				oneBigram = oneWord + separator + twoWord; 

				if ( m_bigramprob.contains(oneBigram))
				{

					// bigram score
					bigramcount = m_bigramprob[oneBigram];

					// bigram bag of words
					currentBagOfWords.clear();
					currentBagOfWords = bagOfWords;

					if (currentBagOfWords[oneWord] <= 1)
					{
						currentBagOfWords.remove(oneWord);
					}
					else
					{
						currentBagOfWords[oneWord]--;
					}

					if (currentBagOfWords[twoWord] <= 1)
					{
						currentBagOfWords.remove(twoWord);
					}
					else
					{
						currentBagOfWords[twoWord]--;
					}

					currentBagOfWords.insert(QString("#"), 1);
					currentBagOfWords.insert(QString("."), 1);

					currentHistoryString.clear();
					currentHistoryScore.clear();

					oneSentenceItem = new sentenceItem(bigramcount, oneBigram, currentBagOfWords, 1, currentHistoryString, currentHistoryScore ); 
					oneSentenceItem ->m_numberofwordsinsentence = 2; 
					oneSentenceItem ->m_value = oneSentenceItem ->m_value / (double)oneSentenceItem ->m_numberofwordsinsentence; 
					
					twoSentenceItem = new sentenceItem(0, oneBigram, currentBagOfWords, 1, currentHistoryString, currentHistoryScore ); 
					twoSentenceItem ->m_numberofwordsinsentence = 2; 
					twoSentenceItem ->m_value = twoSentenceItem ->m_value / (double)twoSentenceItem ->m_numberofwordsinsentence; 

					biResultRankedSentences.append(oneSentenceItem);
					triResultRankedSentences.append(twoSentenceItem); 

					
				}
				

			}

		
		}


		// Test Bigram Sequencerizer2
		sequenize2(bagOfWords, numberOfWords, m_K, biResultRankedSentences, 1);

		// Test Trigram Sequencerizer2
		sequenize2(bagOfWords, numberOfWords, m_K, triResultRankedSentences, 2);

	
		if ( biResultRankedSentences.count() != 0)
		{

			QFile file( "SequencerLog2.txt" );
    
			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );

			outf << "******Bigram Results******" << endl <<endl; 



			QString				biResultKey;


			biResultRankedSentences.sort();

			resultRanki = 0; 
			biRank = resultRanki;
			for ( oneSentenceItem=biResultRankedSentences.first(); oneSentenceItem != 0; oneSentenceItem=biResultRankedSentences.next())
			{
				resultRanki++; 

				biResultKey = oneSentenceItem ->m_key;
				biResultKey.replace(separator, " ");
				
				if ( biResultKey == rightSentence)
				{
					biRank = resultRanki;
				}
				

				if ( resultRanki > m_resultK)
				{
					break;
				}


				// log history of this result sentence 
				outf << "Result Sentence Rank " << resultRanki << " : " << biResultKey << endl; 
				for ( int stepi = 1; stepi <= oneSentenceItem ->m_stepnumber; stepi++)
				{
					QString					oneHistoryString; 
					double					oneHistoryScore;

					oneHistoryString = oneSentenceItem ->m_historystrings[stepi];
					oneHistoryString = oneHistoryString.replace(separator, " ");
					oneHistoryScore = oneSentenceItem ->m_historyscores[stepi];

					outf << "	" << stepi << " : " << oneHistoryString << " : " <<  oneHistoryScore << endl; 
				
				}

				outf << endl; 

			}
			

			if ( getInputFromUI )
			{
			

				oneSentenceItem=biResultRankedSentences.first();

				biResultKey = oneSentenceItem ->m_key;
				biResultKey.replace(separator, " ");

				QMessageBox::information ( NULL, "Top Bigram Sequencer Output",biResultKey, "OK" );	
			
			}
			
			biResultRankedSentences.setAutoDelete(TRUE);
			biResultRankedSentences.clear();
			
			file.close();
		}
		

		if ( triResultRankedSentences.count() != 0)
		{

			QFile file( "SequencerLog2.txt" );
    
			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );

			outf << "******Trigram Results******" << endl <<endl; 


			QString				triResultKey;

			triResultRankedSentences.sort();

			resultRanki = 0; 
			triRank = resultRanki;
			for ( oneSentenceItem=triResultRankedSentences.first(); oneSentenceItem != 0; oneSentenceItem=triResultRankedSentences.next())
			{
				resultRanki++; 

				triResultKey = oneSentenceItem ->m_key;
				triResultKey.replace(separator, " ");
				
				if ( triResultKey == rightSentence)
				{
					triRank = resultRanki;
				}
				

				if ( resultRanki > m_resultK)
				{
					break;
				}

				// log history of this result sentence 
				outf << "Result Sentence Rank " << resultRanki << " : " << triResultKey << endl; 
				for ( int stepi = 1; stepi <= oneSentenceItem ->m_stepnumber; stepi++)
				{
					QString					oneHistoryString; 
					double					oneHistoryScore;

					oneHistoryString = oneSentenceItem ->m_historystrings[stepi];
					oneHistoryString = oneHistoryString.replace(separator, " ");
					oneHistoryScore = oneSentenceItem ->m_historyscores[stepi];

					outf << "	" << stepi << " : " << oneHistoryString << " : " <<  oneHistoryScore << endl; 
				
				}

				outf << endl; 


			}
			
			
			if ( getInputFromUI )
			{
				QString				triResultKey;

				oneSentenceItem=triResultRankedSentences.first();

				triResultKey = oneSentenceItem ->m_key;
				triResultKey.replace(separator, " ");

				QMessageBox::information ( NULL, "Top Trigram Sequencer Output",triResultKey, "OK" );	
			
			}
		
			triResultRankedSentences.setAutoDelete(TRUE);
			triResultRankedSentences.clear();

			file.close(); 
		}
		


	} 
	else 
	{
		return;     
    }


}

void		CSequencer::sequenizeFromABigram(QString oneBigram, double bigramValue, StringToInt& bagOfWords, int lenOfSentence, int K, SortedSentences& resultKSentences, int computeType)
{
	// computeType: 1 --> bigram; 2 --> trigram
	
	StringToInt::Iterator				StringToIntIt;
	double								currentValue;
	QString								currentString;
	QString								currentleftBigrambase, currentrightBigrambase;
	QString								currentleftTrigrambase, currentrightTrigrambase;
	StringToInt*						currentBagOfWords;
	QString								tempString;
	int									leftFirstLoc, rightFirstLoc;
	int									leftSecondLoc, rightSecondLoc;
	int									lenOfSeparator = separator.length();
	StringToInt							oneTryBagOfWords;
	SortedSentences						tempResultKSentence;
	SortedSentences						swapResultKSentence;
	sentenceItem*						oneSentenceItem;
	sentenceItem*						oneCurrentItem;
	int									i,j; 
	bool								canExpandLeft, canExpandRight;
	bool								lastWord;
	IntToString							currentHistoryString;
	IntToDouble							currentHistoryScore;
	int									currentStepNumber;


	resultKSentences.setAutoDelete( TRUE ); 
	tempResultKSentence.setAutoDelete( FALSE ); 
	resultKSentences.clear();


	// First, put this bigram in resultKSentences;
	currentHistoryString.clear();
	currentHistoryScore.clear();
	oneSentenceItem = new sentenceItem(bigramValue, oneBigram, bagOfWords, 1, currentHistoryString, currentHistoryScore ); 
	resultKSentences.append(oneSentenceItem);


	// Loop for lenOfSentence( abc doesn't count the beginning "#" and ending ".")
	// Each loop refers to expand one word either from left or right
	lastWord = false;
	for ( i=0; i <lenOfSentence; i++)
	{
		// for each expansion. Total : N loops

		if ( i == lenOfSentence -1)
		{
			lastWord = true;	
		}
		else
		{
			lastWord = false;	
		}


		tempResultKSentence.clear();
		for ( oneCurrentItem=resultKSentences.first(); oneCurrentItem != 0; oneCurrentItem=resultKSentences.next())
        {
			// for each current string. Total: K loops
		
			currentString = oneCurrentItem ->m_key;
			currentValue = oneCurrentItem ->m_value;
			currentBagOfWords = &(oneCurrentItem ->m_bagofwords); 
			currentHistoryString.clear();
			currentHistoryString = oneCurrentItem ->m_historystrings;
			currentHistoryScore.clear();
			currentHistoryScore = oneCurrentItem ->m_historyscores; 
			currentStepNumber = oneCurrentItem ->m_stepnumber;
			
			leftFirstLoc = currentString.find(separator);
			currentleftBigrambase = currentString.left(leftFirstLoc);
			tempString = currentString.right(currentString.length() - leftFirstLoc - lenOfSeparator);
			leftSecondLoc = tempString.find(separator);

			if ( leftSecondLoc == -1)
			{
				currentleftTrigrambase = currentString;
			}
			else
			{
				currentleftTrigrambase = currentString.left(leftFirstLoc + lenOfSeparator + leftSecondLoc);
			}
			

			rightFirstLoc = currentString.findRev(separator);
			currentrightBigrambase = currentString.right(currentString.length() - rightFirstLoc - lenOfSeparator);
			tempString = currentString.left(rightFirstLoc );
			rightSecondLoc = tempString.findRev(separator);

			if ( rightSecondLoc == -1)
			{
				currentrightTrigrambase = currentString;
			}
			else
			{
				currentrightTrigrambase = currentString.right(currentString.length() - rightSecondLoc - lenOfSeparator);
			}
			

			if (currentleftBigrambase == QString("#"))
			{
				canExpandLeft = false;
			}
			else
			{
				canExpandLeft = true;
			}


			if (currentrightBigrambase == QString("."))
			{
				canExpandRight = false;
			}
			else
			{
				canExpandRight = true;
			}


			if ( (!canExpandLeft) && (!canExpandRight))
			{
				continue;
			}
			
			for ( StringToIntIt = currentBagOfWords ->begin(); StringToIntIt != currentBagOfWords ->end();  StringToIntIt++)
			{
				// For each possible word. Total : (N - M) loops
				
				QString				onePossibleExpansion; 
				QString				leftExpansion;
				QString				rightExpansion;
				double				leftValue;
				double				rightValue;

				onePossibleExpansion = StringToIntIt.key();


				// Try Left Expansion
				if (( onePossibleExpansion != QString(".")) && (canExpandLeft))
				{
					if ((onePossibleExpansion == QString("#")) && (!canExpandRight) && (!lastWord))
					{
						continue;
					}


					leftExpansion = onePossibleExpansion + separator + currentString;
					
					if ( computeType == 1)
					{
						QString				oneTryBigram;
						double				oneValue; 

						oneTryBigram = onePossibleExpansion + separator + currentleftBigrambase;
						
						if (! m_bigramprob.contains(oneTryBigram))
						{
							if (m_bigramsbase.contains(onePossibleExpansion))
							{
								oneValue = 10.0; // big punishment 
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_bigramprob[oneTryBigram];
						}

						leftValue = currentValue + oneValue; 

					}
					else if ( computeType == 2)
					{

						QString				oneTryTrigram;
						QString				oneTryTrigrambase;
						double				oneValue; 

						oneTryTrigrambase = onePossibleExpansion + separator + currentleftBigrambase;
						oneTryTrigram = onePossibleExpansion + separator + currentleftTrigrambase;
						


						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								oneValue = 10.0;  // big punishment 
							}
							else
							{
								oneValue = 5.0;  // mild punishment
							}

						}
						else
						{
							oneValue = m_trigramprob[oneTryTrigram];
						}

						leftValue = currentValue + oneValue; 
					
					}
					else
					{
						return;
					}
					
					
					// create a sentenceItem
					oneTryBagOfWords = (*currentBagOfWords);
					if ( oneTryBagOfWords[onePossibleExpansion] > 1)
					{
						oneTryBagOfWords[onePossibleExpansion]--;
					}
					else
					{
						oneTryBagOfWords.remove(onePossibleExpansion);
					}

					oneSentenceItem = new sentenceItem(leftValue, leftExpansion, oneTryBagOfWords, currentStepNumber+1, currentHistoryString, currentHistoryScore); 
				
					tempResultKSentence.append(oneSentenceItem);

				}


				// Try Right Expansion
				if ( (onePossibleExpansion != QString("#")) && (canExpandRight))
				{
					if ((onePossibleExpansion == QString(".")) && (!canExpandLeft) && (!lastWord))
					{
						continue;
					}

					rightExpansion = currentString + separator + onePossibleExpansion;
					
					if ( computeType == 1)
					{
						QString				oneTryBigram;
						double				oneValue; 

						oneTryBigram =  currentrightBigrambase + separator + onePossibleExpansion;
						
						if (! m_bigramprob.contains(oneTryBigram))
						{
							if (m_bigramsbase.contains(currentrightBigrambase))
							{
								oneValue = 10.0; // big punishment
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_bigramprob[oneTryBigram];
						}

						rightValue = currentValue + oneValue; 

					}
					else if ( computeType == 2)
					{

						QString				oneTryTrigram;
						QString				oneTryTrigrambase;
						double				oneValue; 

						oneTryTrigram =  currentrightTrigrambase + separator + onePossibleExpansion;
						oneTryTrigrambase = currentrightTrigrambase;


						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								oneValue = 10.0; // big punishment 
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_trigramprob[oneTryTrigram];
						}

						rightValue = currentValue + oneValue; 
					
					}
					else
					{
						return;
					}
					
					
					// create a sentenceItem
					oneTryBagOfWords = (*currentBagOfWords);;
					if ( oneTryBagOfWords[onePossibleExpansion] > 1)
					{
						oneTryBagOfWords[onePossibleExpansion]--;
					}
					else
					{
						oneTryBagOfWords.remove(onePossibleExpansion);
					}

					oneSentenceItem = new sentenceItem(rightValue, rightExpansion, oneTryBagOfWords, currentStepNumber+1, currentHistoryString, currentHistoryScore); 
				
					tempResultKSentence.append(oneSentenceItem);

				}

			
			}
		}

		tempResultKSentence.sort(); 


		// Delete the duplicate Items
		QString			preString;
		QString			postString; 

		preString = QString("");
		swapResultKSentence.clear(); 
		for ( oneCurrentItem=tempResultKSentence.first(); oneCurrentItem != 0; oneCurrentItem=tempResultKSentence.next())
        {
			postString = oneCurrentItem ->m_key;

			if (! (postString == preString) )
			{
				swapResultKSentence.append(oneCurrentItem);	
				preString =  postString ;  
			}
			else
			{
				delete oneCurrentItem; 
			}

			
		}

		tempResultKSentence = swapResultKSentence;


		// Keep the top K item in this sentence list
		if ( static_cast <int> ( tempResultKSentence.count() ) > K)
		{
			int				diff;

			diff = tempResultKSentence.count() - K ;

			tempResultKSentence.setAutoDelete( TRUE ); 
			for ( j = 0; j< diff; j++)
			{
				tempResultKSentence.removeLast();
			}
			tempResultKSentence.setAutoDelete( FALSE ); 
		}

		// copy to ResultKSentence
		resultKSentences.clear();
		resultKSentences = tempResultKSentence;
		
	}	




} 


void		CSequencer::sequenize2(StringToInt allBagOfWords, int lenOfSentence, int K, SortedSentences& resultKSentences, int computeType)
{
	// computeType: 1 --> bigram; 2 --> trigram
	
	StringToInt							testBagOfWords; 
	StringToInt							testBagOfWords2; 
	StringToInt::Iterator				StringToIntIt;
	double								currentValue, tryValue;
	QString								currentString, tryString;
	QString								currentleftBigrambase, currentrightBigrambase;
	QString								currentleftTrigrambase, currentrightTrigrambase;
	QString								tryleftBigrambase, tryrightBigrambase;
	QString								tryleftTrigrambase, tryrightTrigrambase;
	StringToInt*						currentBagOfWords;
	StringToInt*						tryBagOfWords;
	QString								tempString;
	int									leftFirstLoc, rightFirstLoc;
	int									leftSecondLoc, rightSecondLoc;
	int									lenOfSeparator = separator.length();
	StringToInt							oneTryBagOfWords;
	SortedSentences						tempResultKSentence;
	SortedSentences						swapResultKSentence;
	SortedSentences						copyResultKSentence;
	sentenceItem*						oneSentenceItem;
	sentenceItem*						oneCurrentItem;
	sentenceItem*						twoCurrentItem;
	int									i,j; 
	bool								canExpandLeft, canExpandRight;
	bool								canExpandLeft2, canExpandRight2;
	bool								lastWord;
	bool								myLastWord;
	IntToString							currentHistoryString, tryHistoryString;
	IntToDouble							currentHistoryScore, tryHistoryScore;
	int									currentStepNumber;
	int									currentNumberOfWordsInSentence, tryNumberOfWordsInSentence;
	bool								shouldFurther; 
	bool								debug = false;
	bool								deleteduplicatesentence = false; 


	resultKSentences.setAutoDelete( TRUE ); 
	tempResultKSentence.setAutoDelete( FALSE ); 
	copyResultKSentence.setAutoDelete( FALSE );
	swapResultKSentence.setAutoDelete( FALSE );
			

	if ( debug)
	{
		QFile file( "SequencerLog2Debug.txt" );
    
		if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
		{
			QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
			return;    
		}

		Q3TextStream outf( &file );
		QString				displayTempString; 


		outf << "******One Sentence******" << endl <<endl; 

		file.close();

	}

	// At most Loop for lenOfSentence( abc doesn't count the beginning "#" and ending ".")
	// Each loop refers to expand one step
	lastWord = false;
	for ( i=0; i <lenOfSentence; i++)
	{

		shouldFurther = false; 
		
		// for each expansion. Total : N loops

		if ( i == lenOfSentence -1)
		{
			lastWord = true;	
		}
		else
		{
			lastWord = false;	
		}


		if ( debug)
		{
			QFile file( "SequencerLog2Debug.txt" );

			if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
			{
				QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
				return;    
			}

			Q3TextStream outf( &file );
			QString				displayTempString; 



			outf << endl << "******" << i <<"******" << endl; 
			
			file.close(); 

		}

		tempResultKSentence.clear();

		copyResultKSentence = resultKSentences;

		for ( oneCurrentItem=resultKSentences.first(); oneCurrentItem != 0; oneCurrentItem=resultKSentences.next())
        {
			// for each current string. Total: K loops

			currentString = oneCurrentItem ->m_key;
			currentValue = oneCurrentItem ->m_value; // Now, this is an average value;
			currentBagOfWords = &(oneCurrentItem ->m_bagofwords); 
			currentHistoryString.clear();
			currentHistoryString = oneCurrentItem ->m_historystrings;
			currentHistoryScore.clear();
			currentHistoryScore = oneCurrentItem ->m_historyscores; 
			currentStepNumber = oneCurrentItem ->m_stepnumber;
			currentNumberOfWordsInSentence = oneCurrentItem ->m_numberofwordsinsentence; 


			
			if ( debug)
			{
			
				QFile file( "SequencerLog2Debug.txt" );
    
				if ( !file.open( QIODevice::WriteOnly | QIODevice::Append ) ) 
				{
					QMessageBox::information(NULL, "Error", "Can't Open the file!", "OK"); 
					return;    
				}

				Q3TextStream outf( &file );
				QString				displayTempString; 

				
				displayTempString = currentString;
				displayTempString = displayTempString.replace(separator, " ");
				outf << displayTempString << "	"	<< currentValue <<endl;

				file.close(); 
			}
				

			// Get the words of currentString
			testBagOfWords.clear(); 
			testBagOfWords = allBagOfWords;
			for ( StringToIntIt = currentBagOfWords ->begin(); StringToIntIt != currentBagOfWords ->end(); StringToIntIt++)
			{
				QString					oneInCurrentWords; 

				oneInCurrentWords = StringToIntIt.key(); 
				
				if ( testBagOfWords[oneInCurrentWords] == 1)
				{
					testBagOfWords.remove(oneInCurrentWords);	
				}
				else
				{
					testBagOfWords[oneInCurrentWords]--;
				}
			
			}


			// this sentence already done
			if ( currentNumberOfWordsInSentence == (lenOfSentence +2))
			{
				oneSentenceItem = new sentenceItem(oneCurrentItem); 
				
				tempResultKSentence.append(oneSentenceItem);
				
				continue; 
			}

			myLastWord = lastWord;
			if ( currentNumberOfWordsInSentence == (lenOfSentence +1))
			{
				myLastWord = true; 
			}



			// Figure out the bigrambase and trigrambase of the current string;
			leftFirstLoc = currentString.find(separator);
			currentleftBigrambase = currentString.left(leftFirstLoc);
			tempString = currentString.right(currentString.length() - leftFirstLoc - lenOfSeparator);
			leftSecondLoc = tempString.find(separator);

			if ( leftSecondLoc == -1)
			{
				currentleftTrigrambase = currentString;
			}
			else
			{
				currentleftTrigrambase = currentString.left(leftFirstLoc + lenOfSeparator + leftSecondLoc);
			}
			

			rightFirstLoc = currentString.findRev(separator);
			currentrightBigrambase = currentString.right(currentString.length() - rightFirstLoc - lenOfSeparator);
			tempString = currentString.left(rightFirstLoc );
			rightSecondLoc = tempString.findRev(separator);

			if ( rightSecondLoc == -1)
			{
				currentrightTrigrambase = currentString;
			}
			else
			{
				currentrightTrigrambase = currentString.right(currentString.length() - rightSecondLoc - lenOfSeparator);
			}
			

			if (currentleftBigrambase == QString("#"))
			{
				canExpandLeft = false;
			}
			else
			{
				canExpandLeft = true;
			}


			if (currentrightBigrambase == QString("."))
			{
				canExpandRight = false;
			}
			else
			{
				canExpandRight = true;
			}


			if ( (!canExpandLeft) && (!canExpandRight))
			{
				continue;
			}
			


			// Consider the single word in currentbagsofWords
			for ( StringToIntIt = currentBagOfWords ->begin(); StringToIntIt != currentBagOfWords ->end();  StringToIntIt++)
			{
				// For each possible word. Total : (N - M) loops
				
				QString				onePossibleExpansion; 
				QString				leftExpansion;
				QString				rightExpansion;
				double				leftValue;
				double				rightValue;

				onePossibleExpansion = StringToIntIt.key();


				// Try Left Expansion
				if (( onePossibleExpansion != QString(".")) && (canExpandLeft))
				{
					if ((onePossibleExpansion == QString("#")) && (!canExpandRight) && (!myLastWord))
					{
						continue;
					}


					leftExpansion = onePossibleExpansion + separator + currentString;
					
					if ( computeType == 1)
					{
						QString				oneTryBigram;
						double				oneValue; 

						oneTryBigram = onePossibleExpansion + separator + currentleftBigrambase;
						
						if (! m_bigramprob.contains(oneTryBigram))
						{
							if (m_bigramsbase.contains(onePossibleExpansion))
							{
								oneValue = 10.0; // big punishment 
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_bigramprob[oneTryBigram];
						}

						leftValue = currentValue*currentNumberOfWordsInSentence + oneValue; 

					}
					else if ( computeType == 2)
					{

						QString				oneTryTrigram;
						QString				oneTryTrigrambase;
						double				oneValue; 

						oneTryTrigrambase = onePossibleExpansion + separator + currentleftBigrambase;
						oneTryTrigram = onePossibleExpansion + separator + currentleftTrigrambase;
						


						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								oneValue = 10.0;  // big punishment 
							}
							else
							{
								oneValue = 5.0;  // mild punishment
							}

						}
						else
						{
							oneValue = m_trigramprob[oneTryTrigram];
						}

						leftValue = currentValue*currentNumberOfWordsInSentence + oneValue; 
					
					}
					else
					{
						return;
					}
					
					
					// create a sentenceItem
					oneTryBagOfWords = (*currentBagOfWords);
					if ( oneTryBagOfWords[onePossibleExpansion] > 1)
					{
						oneTryBagOfWords[onePossibleExpansion]--;
					}
					else
					{
						oneTryBagOfWords.remove(onePossibleExpansion);
					}

					oneSentenceItem = new sentenceItem(leftValue, leftExpansion, oneTryBagOfWords, currentStepNumber+1, currentHistoryString, currentHistoryScore); 
					oneSentenceItem ->m_numberofwordsinsentence = currentNumberOfWordsInSentence + 1; 
					oneSentenceItem ->m_value = oneSentenceItem ->m_value / (double)oneSentenceItem ->m_numberofwordsinsentence; 

					tempResultKSentence.append(oneSentenceItem);
					shouldFurther = true; 

				}


				// Try Right Expansion
				if ( (onePossibleExpansion != QString("#")) && (canExpandRight))
				{
					if ((onePossibleExpansion == QString(".")) && (!canExpandLeft) && (!myLastWord))
					{
						continue;
					}

					rightExpansion = currentString + separator + onePossibleExpansion;
					
					if ( computeType == 1)
					{
						QString				oneTryBigram;
						double				oneValue; 

						oneTryBigram =  currentrightBigrambase + separator + onePossibleExpansion;
						
						if (! m_bigramprob.contains(oneTryBigram))
						{
							if (m_bigramsbase.contains(currentrightBigrambase))
							{
								oneValue = 10.0; // big punishment
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_bigramprob[oneTryBigram];
						}

						rightValue = currentValue*currentNumberOfWordsInSentence  + oneValue; 

					}
					else if ( computeType == 2)
					{

						QString				oneTryTrigram;
						QString				oneTryTrigrambase;
						double				oneValue; 

						oneTryTrigram =  currentrightTrigrambase + separator + onePossibleExpansion;
						oneTryTrigrambase = currentrightTrigrambase;


						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								oneValue = 10.0; // big punishment 
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_trigramprob[oneTryTrigram];
						}

						rightValue = currentValue*currentNumberOfWordsInSentence  + oneValue; 
					
					}
					else
					{
						return;
					}
					
					
					// create a sentenceItem
					oneTryBagOfWords = (*currentBagOfWords);;
					if ( oneTryBagOfWords[onePossibleExpansion] > 1)
					{
						oneTryBagOfWords[onePossibleExpansion]--;
					}
					else
					{
						oneTryBagOfWords.remove(onePossibleExpansion);
					}

					oneSentenceItem = new sentenceItem(rightValue, rightExpansion, oneTryBagOfWords, currentStepNumber+1, currentHistoryString, currentHistoryScore); 
					oneSentenceItem ->m_numberofwordsinsentence = currentNumberOfWordsInSentence + 1; 
					oneSentenceItem ->m_value = oneSentenceItem ->m_value / (double)oneSentenceItem ->m_numberofwordsinsentence; 

					tempResultKSentence.append(oneSentenceItem);
					shouldFurther = true; 

				}

			
			}


			// If this sentence Item only need one more word, not necessary to consider other chunks;
			//myLastWord = true; 
			
			if ( myLastWord)
			{
				continue; 
			}

			// Consider the possible chunk concatenance; 

			for ( twoCurrentItem=copyResultKSentence.first(); twoCurrentItem != 0; twoCurrentItem=copyResultKSentence.next())
			{
				QString				leftExpansion;
				QString				rightExpansion;
				double				leftValue;
				double				rightValue;
				bool				overlapped; 


				tryString = twoCurrentItem ->m_key;
				tryValue = twoCurrentItem ->m_value; // Now, this is an average value;
				tryBagOfWords = &(twoCurrentItem ->m_bagofwords); 
				tryHistoryString.clear();
				tryHistoryString = twoCurrentItem ->m_historystrings;
				tryHistoryScore.clear();
				tryHistoryScore = twoCurrentItem ->m_historyscores; 
				tryNumberOfWordsInSentence = twoCurrentItem ->m_numberofwordsinsentence; 		
				

				// Too long
				if ( (currentNumberOfWordsInSentence + tryNumberOfWordsInSentence -2) > lenOfSentence)
				{
					continue;
				}


				// Figure out the bigrambase and trigrambase of the try string;
				leftFirstLoc = tryString.find(separator);
				tryleftBigrambase = tryString.left(leftFirstLoc);
				tempString = tryString.right(tryString.length() - leftFirstLoc - lenOfSeparator);
				leftSecondLoc = tempString.find(separator);

				if ( leftSecondLoc == -1)
				{
					tryleftTrigrambase = tryString;
				}
				else
				{
					tryleftTrigrambase = tryString.left(leftFirstLoc + lenOfSeparator + leftSecondLoc);
				}
				

				rightFirstLoc = tryString.findRev(separator);
				tryrightBigrambase = tryString.right(tryString.length() - rightFirstLoc - lenOfSeparator);
				tempString = tryString.left(rightFirstLoc );
				rightSecondLoc = tempString.findRev(separator);

				if ( rightSecondLoc == -1)
				{
					tryrightTrigrambase = tryString;
				}
				else
				{
					tryrightTrigrambase = tryString.right(tryString.length() - rightSecondLoc - lenOfSeparator);
				}
			
				
				// Do quick check in order to save time

				if (tryleftBigrambase == QString("#"))
				{
					canExpandLeft2 = false;
				}
				else
				{
					canExpandLeft2 = true;
				}


				if (tryrightBigrambase == QString("."))
				{
					canExpandRight2 = false;
				}
				else
				{
					canExpandRight2 = true;
				}

				
				
				if ( !canExpandLeft && !canExpandRight)
				{
					continue; 
				}

				if ( !canExpandLeft2 && !canExpandRight2)
				{
					continue; 
				}

				if ( (canExpandLeft && !canExpandRight) && (!canExpandRight2 && canExpandLeft2))
				{
					continue; 
				}

				if ( (!canExpandLeft && canExpandRight) && (canExpandRight2 && !canExpandLeft2))
				{
					continue; 
				}

				if ( (canExpandLeft && canExpandRight) && (canExpandRight2 && canExpandLeft2))
				{
					if (( currentNumberOfWordsInSentence + tryNumberOfWordsInSentence) > lenOfSentence)
					{
						continue;
					}
				}
				

				if ( (canExpandLeft && !canExpandRight) && (canExpandRight2 && !canExpandLeft2))
				{
					if ( (currentNumberOfWordsInSentence + tryNumberOfWordsInSentence -2) < lenOfSentence)
					{
						continue; 
					}
				}

				if ( (canExpandLeft2 && !canExpandRight2) && (canExpandRight && !canExpandLeft))
				{
					if ( (currentNumberOfWordsInSentence + tryNumberOfWordsInSentence -2) < lenOfSentence)
					{
						continue; 
					}
				}


				// Check wether the two strings overlap some common words. 
				testBagOfWords2.clear(); 
				testBagOfWords2 = (*tryBagOfWords); 

				overlapped = false; 
				for ( StringToIntIt = testBagOfWords.begin(); StringToIntIt != testBagOfWords.end(); StringToIntIt++)
				{
					QString					oneInTestWords; 
					int						oneInTestWordCount; 

	
					oneInTestWords = StringToIntIt.key(); 			
					oneInTestWordCount = StringToIntIt.data(); 			

					if (! testBagOfWords2.contains(oneInTestWords))
					{
						overlapped = true; 
						break; 
					}

					if ( testBagOfWords2[oneInTestWords] < oneInTestWordCount)
					{
						overlapped = true; 
						break; 
					}
					else if ( testBagOfWords2[oneInTestWords] == oneInTestWordCount)
					{
						testBagOfWords2.remove(oneInTestWords); 
					}
					else
					{
						testBagOfWords2[oneInTestWords] -= oneInTestWordCount; 
					}

				}

				if ( overlapped) continue; 


				// Now, these two chunks are ready to merge
				oneTryBagOfWords.clear();
				oneTryBagOfWords = 	testBagOfWords2; 


				// Try Left Merge

				if ( canExpandLeft && canExpandRight2)
				{
			
					leftExpansion = tryString + separator + currentString;
					
					if ( computeType == 1)
					{
						QString				oneTryBigram;
						double				oneValue; 

						oneTryBigram = tryrightBigrambase + separator + currentleftBigrambase;
						
						if (! m_bigramprob.contains(oneTryBigram))
						{
							if (m_bigramsbase.contains(tryrightBigrambase))
							{
								oneValue = 10.0; // big punishment 
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_bigramprob[oneTryBigram];
						}

						leftValue = currentValue*currentNumberOfWordsInSentence + oneValue + tryValue*tryNumberOfWordsInSentence;  

					}
					else if ( computeType == 2)
					{

						QString				oneTryTrigram;
						QString				oneTryTrigrambase;
						double				oneValue, twoValue; 
				

						oneTryTrigrambase = tryrightBigrambase + separator + currentleftBigrambase;
						oneTryTrigram = tryrightBigrambase + separator + currentleftTrigrambase;
						


						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								oneValue = 10.0;  // big punishment 
							}
							else
							{
								oneValue = 5.0;  // mild punishment
							}

						}
						else
						{
							oneValue = m_trigramprob[oneTryTrigram];
						}


						// Special here, one more trigram are taken in. 
						oneTryTrigrambase = tryrightTrigrambase;
						oneTryTrigram = tryrightTrigrambase + separator + currentleftBigrambase;
						

						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								twoValue = 10.0;  // big punishment 
							}
							else
							{
								twoValue = 5.0;  // mild punishment
							}

						}
						else
						{
							twoValue = m_trigramprob[oneTryTrigram];
						}


						leftValue = currentValue*currentNumberOfWordsInSentence + oneValue + twoValue + tryValue*tryNumberOfWordsInSentence;  
						
					}
					else
					{
						return;
					}
			
					// create a sentenceItem
					
					// Debug
					for ( StringToIntIt = oneTryBagOfWords.begin(); StringToIntIt != oneTryBagOfWords.end(); StringToIntIt++)
					{
						QString					oneInTestWords; 
						int						oneInTestWordCount; 

						oneInTestWords = StringToIntIt.key(); 
						oneInTestWordCount = 1; 
	


					}


					oneSentenceItem = new sentenceItem(leftValue, leftExpansion, oneTryBagOfWords, currentStepNumber+1, currentHistoryString, currentHistoryScore); 
					oneSentenceItem ->m_numberofwordsinsentence = currentNumberOfWordsInSentence + tryNumberOfWordsInSentence; 
					oneSentenceItem ->m_value = oneSentenceItem ->m_value / (double)oneSentenceItem ->m_numberofwordsinsentence; 

					tempResultKSentence.append(oneSentenceItem);
					shouldFurther = true; 

				}


				// Try Right Merge

				if ( canExpandRight && canExpandLeft2)
				{
			
					rightExpansion = currentString + separator + tryString;
					
					if ( computeType == 1)
					{
						QString				oneTryBigram;
						double				oneValue; 

						oneTryBigram = currentrightBigrambase + separator + tryleftBigrambase;
						
						if (! m_bigramprob.contains(oneTryBigram))
						{
							if (m_bigramsbase.contains(tryrightBigrambase))
							{
								oneValue = 10.0; // big punishment 
							}
							else
							{
								oneValue = 5.0; // mild punishment
							}

						}
						else
						{
							oneValue = m_bigramprob[oneTryBigram];
						}

						rightValue = currentValue*currentNumberOfWordsInSentence + oneValue + tryValue*tryNumberOfWordsInSentence;  

					}
					else if ( computeType == 2)
					{

						QString				oneTryTrigram;
						QString				oneTryTrigrambase;
						double				oneValue, twoValue; 
				

						oneTryTrigrambase = currentrightBigrambase + separator + tryleftBigrambase;
						oneTryTrigram = currentrightBigrambase + separator + tryleftTrigrambase;
						

						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								oneValue = 10.0;  // big punishment 
							}
							else
							{
								oneValue = 5.0;  // mild punishment
							}

						}
						else
						{
							oneValue = m_trigramprob[oneTryTrigram];
						}


						// Special here, one more trigram are taken in. 
						oneTryTrigrambase = currentrightTrigrambase;
						oneTryTrigram = currentrightTrigrambase + separator + tryleftBigrambase;
						

						if (! m_trigramprob.contains(oneTryTrigram))
						{
							if (m_trigramsbase.contains(oneTryTrigrambase))
							{
								twoValue = 10.0;  // big punishment 
							}
							else
							{
								twoValue = 5.0;  // mild punishment
							}

						}
						else
						{
							twoValue = m_trigramprob[oneTryTrigram];
						}


						rightValue = currentValue*currentNumberOfWordsInSentence + oneValue + twoValue + tryValue*tryNumberOfWordsInSentence;  
					
					}
					else
					{
						return;
					}
			
					// create a sentenceItem
					oneSentenceItem = new sentenceItem(rightValue, rightExpansion, oneTryBagOfWords, currentStepNumber+1, currentHistoryString, currentHistoryScore); 
					oneSentenceItem ->m_numberofwordsinsentence = currentNumberOfWordsInSentence + tryNumberOfWordsInSentence; 
					oneSentenceItem ->m_value = oneSentenceItem ->m_value / (double)oneSentenceItem ->m_numberofwordsinsentence; 

					tempResultKSentence.append(oneSentenceItem);
					shouldFurther = true; 

				}

				
			}

		}				
		
		

		tempResultKSentence.sort(); 

		// Delete the duplicate Items

		if ( deleteduplicatesentence )
		{
			QString			preString;
			QString			postString; 

			preString = QString("");
			swapResultKSentence.clear(); 
			for ( oneCurrentItem=tempResultKSentence.first(); oneCurrentItem != 0; oneCurrentItem=tempResultKSentence.next())
			{
				postString = oneCurrentItem ->m_key;

				if (! (postString == preString) )
				{
					swapResultKSentence.append(oneCurrentItem);	
					preString =  postString ;  
				}
				else
				{
					delete oneCurrentItem; 
				}

				
			}

			tempResultKSentence = swapResultKSentence;
		}
	

		// Keep the top K item in this sentence list
		if ( static_cast <int> ( tempResultKSentence.count() ) > K)
		{
			int				diff;

			diff = tempResultKSentence.count() - K ;

			tempResultKSentence.setAutoDelete( TRUE ); 
			for ( j = 0; j< diff; j++)
			{
				tempResultKSentence.removeLast();
			}
			tempResultKSentence.setAutoDelete( FALSE ); 
		}

		// copy to ResultKSentence
		resultKSentences.clear();
		resultKSentences = tempResultKSentence;
	
		if ( !shouldFurther)
		{
			break; 
		}

	}

}
