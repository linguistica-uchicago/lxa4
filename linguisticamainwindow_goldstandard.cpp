// Handling requests to compare the analyzed corpus to a gold standard
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>
#include <Q3ValueList>
#include "Lexicon.h"
#include "CorpusWord.h"
#include "Stem.h"
#include "CorpusWordCollection.h"
#include "TemplateCollection.h"
#include "Typedefs.h"

typedef QMap<CParse*,int> ParseToInt;
typedef QMap<QString,CParse*> StringToParse;
typedef QMap<QString,ParseToInt*> StringToParseToInt;
typedef QMap<QString,StringToInt*> StringToStringToInt;

void LinguisticaMainWindow::changeGoldStdFileSlot()
{
  m_goldStdFileName = Q3FileDialog::getOpenFileName( m_goldStdFileName,
                                                    "XML files (*.xml)",
                                                    this,
                                                    "Linguistica :: New Gold Standard File",
                                                    "Choose a new gold standard file" );
  if( !m_goldStdFileName.isEmpty() )
  m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/MainWindow/DiagnosticsMenu/NewGoldStdFile", m_goldStdFileName );
}



void LinguisticaMainWindow::compareCompoundsSlot()
{
/*
	QString				word;
	CStem*				pStem; 
	StringToPtrCStem	goldStdCompounds, goldStd; 

	QString				goldStdFileName;

	goldStdFileName = QFileDialog::getOpenFileName( m_projectDirectory,
													"XML Files (*.xml)",
													this,
													"open file dialog",
													"Choose a gold standard:" );

	if( !goldStdFileName.isEmpty() )
	{ 
		QFile goldStdFile( goldStdFileName );
		if( goldStdFile.open( IO_ReadOnly ) )
		{
			QDomDocument doc( "Goldstandard" );

			if( !doc.setContent( &goldStdFile ) )
			{
				goldStdFile.close();
				return;
			}

			QDomElement root = doc.documentElement();

			QString tagName = root.tagName();

			if( root.tagName() != "GDS")
			{
				QMessageBox::information( NULL, "Error", "There was an error reading the Gold Standard. The following XML tag cannot be read: " + tagName, "OK" );
				goldStdFile.close();
				return; 
			}

			// Read the header
			QDomNode header = root.firstChild();

			QDomElement direction = header.nextSibling().toElement();

			// Read all content
			QDomNode contentnode = direction.nextSibling();
			QDomElement content = contentnode.toElement();

			tagName = content.tagName();
			if( tagName != "content" )
			{
				QMessageBox::information( NULL, "Error", "There was an error reading the Gold Standard. The following XML tag cannot be read: " + tagName, "OK" );
				goldStdFile.close();
				return;
			}

			QString				value; 
			int					supposedTotalNumberOfWords; 
			QString				key;
			QString				wordComment; 
			int					numberOfPieces;  
			int					start; 
			int					type;
			int					color; 
			int					score;
			int					rootCount;
			QString				comment, allomorph; 

			value = content.attribute( "number", "100" ); 
			supposedTotalNumberOfWords = value.toInt(); 

			QDomNode onewordnode = content.firstChild();

			while (!onewordnode.isNull())
			{
				QDomElement oneword = onewordnode.toElement();
				if( !oneword.isNull() )
				{
					if( oneword.tagName() == "word" )
					{
						key = oneword.attribute( "key", "" );
						if (key == "")
						{
							onewordnode = onewordnode.nextSibling();
							continue; 
						}

						word = key;
						pStem = new CStem( key );
						goldStd.insert( word, pStem ); 

						value = oneword.attribute("morphemes", "0"); 
						numberOfPieces = value.toInt();

						// Looking for goldStdCompounds, must be length 2
						if( numberOfPieces < 2 )
						{
							onewordnode = onewordnode.nextSibling();
							continue;
						}

						wordComment = oneword.attribute( "comment", "" );						

						QDomNode onepiecenode = oneword.firstChild();		

						rootCount = 0; // Need at least two roots to be a compound

						while( !onepiecenode.isNull() )
						{
							QDomElement onepiece = onepiecenode.toElement();
							if( !onepiece.isNull() )
							{
								if( onepiece.tagName() == "morpheme" )
								{
									value = onepiece.attribute("start", "-1");
									start = value.toInt();
									value = onepiece.attribute("type", "-1"); 
									type = value.toInt();


									if( type == 0 || word[start] == '-' )
									{
										goldStd.remove( word );
										goldStdCompounds.remove( word ); 
										if( pStem ) delete pStem;
										pStem = NULL;
										break; 
									}

									if( type == 1 ) rootCount++;
									if( rootCount >= 2 ) goldStdCompounds.insert( word, pStem ); 

									value = onepiece.attribute("color", "-2");
									color = value.toInt();
									value = onepiece.attribute("score", "0");
									score = value.toInt();
									allomorph = onepiece.attribute("allomorph", "");
									comment = onepiece.attribute("comment", "");

									if( score != 1 )
									{
										goldStd.remove( word );
										goldStdCompounds.remove( word ); 
										if( pStem ) delete pStem;
										pStem = NULL;
										break;
									}

									if( (start == -1) || (type == -1) || (color == -2) ) 
									{
										onepiecenode = onepiecenode.nextSibling();
										continue; 
									}

									pStem->CutRightBeforeHere( start ); 
								}
							}	

							onepiecenode = onepiecenode.nextSibling();
						}	
						
						if( rootCount < 2 )
						{
							goldStdCompounds.remove( word );
						}
					}
				}

				onewordnode = onewordnode.nextSibling();
			}

			goldStdFile.close();
		}
		else
		{
			QMessageBox::information( NULL, "Attention", "Unable to open " + goldStdFileName + " .", "OK" );
			return; 
		}
	}
	else return;

	CMiniLexicon* mini = m_lexicon->GetMiniLexicon( m_lexicon->GetActiveMiniIndex() );
	CWordCollection* pWords = mini->GetWords();
	CCompoundCollection* pCompounds = mini->GetCompounds();
	CStem* pWord, * qWord;
	CCompound* pCompound;
	CSuffixCollection* pSuffixes = NULL;
	CPrefixCollection* pPrefixes = NULL;
	CSuffix* pSuffix;
	CPrefix* pPrefix;
	int truePos = 0, trueNeg = 0, falsePos = 0, falseNeg = 0;

	QString outputFileName;

	outputFileName = QFileDialog::getOpenFileName( m_projectDirectory,
												   "Text Files (*.txt)",
												   this,
												   "open file dialog",
												   "Choose an output file:" );

	if( !outputFileName.isEmpty() )
	{ 
		QFile outputFile( outputFileName );
		if( outputFile.open( IO_WriteOnly ) )
		{
			QTextStream out( &outputFile );
			out.setEncoding( QTextStream::Unicode );

			pWords->Sort(KEY);

			out.setf(2);

			out.width(20);
			out << "WORD";

			out.width(2);
			out << "  ";

			out.width(20);
			out << "GOLD STD";

			out.width(2);
			out << "  ";

			out.width(20);
			out << "COMPOUND";

			out.width(2);
			out << "  ";

			out.width(1);
			out << "P";

			out.width(2);
			out << "  ";

			out.width(1);
			out << "S" << endl;

			for( int i = 0; i < pWords->GetCount(); i++ )
			{
				bool notInGS = FALSE;

				pWord = pWords->GetAtSort(i);

				pCompound = *pCompounds ^= pWord->GetKey();

				if( !pCompound ) 
				{
					pStem = pWord->GetStemPtr();
					if( pStem ) pCompound = *pCompounds ^= pStem->GetKey();
				}
				
				if( goldStdCompounds.find( pWord->Display() ) != goldStdCompounds.end() )
				{
					qWord = goldStdCompounds[ pWord->Display() ];
				}
				else qWord = NULL;

				if( goldStd.find( pWord->Display() ) == goldStd.end() )
				{
					notInGS = TRUE;
				}
				else
				{
					if( qWord && pCompound ) truePos++;
					if( qWord && !pCompound ) falseNeg++;
					if( !qWord && pCompound ) falsePos++;

					if( !qWord && !pCompound )
					{
						trueNeg++;
					}
				}

				if( !qWord && !pCompound )
				{
					continue;
				}
					
				if( notInGS )
				{
					out.width(3);
					out << "*  ";
				}

				out.width(20);
				out << pWord->Display();

				out.width(2);
				out << "  ";

				out.width(20);
				if( qWord ) out << qWord->Display('+');
				else out << " ";

				out.width(2);
				out << "  ";

				out.width(20);
				if( pCompound ) out << pCompound->Display('+');
				else out << " ";

				out.width(2);
				out << "  ";

				out.width(1);
				CMiniLexicon* mini2;
				int j;
				for( j = 0; j < m_lexicon->GetMiniSize(); j++ )
				{
					mini2 = m_lexicon->GetMiniLexicon(j);
					if( mini2 )
					{
						pPrefixes = mini2->GetPrefixes();

						if( pCompound && pPrefixes ) 
						{
							pPrefix = (*pPrefixes) ^= pCompound->GetPiece( 1 );
						
							if( pPrefix )
							{
								out << "*";
								break;
							}
						}
					}
				}

				out.width(2);
				out << "  ";

				out.width(1);
				for( j = 0; j < m_lexicon->GetMiniSize(); j++ )
				{
					mini2 = m_lexicon->GetMiniLexicon(j);
					if( mini2 )
					{
						pSuffixes = mini2->GetSuffixes();

						if( pCompound && pSuffixes ) 
						{
							pSuffix = (*pSuffixes) ^= pCompound->GetPiece( 1 );
						
							if( pSuffix )
							{
								out << "*";
								break;
							}
						}
					}
				}

				out << endl;
			}

			double precision = (double) truePos / (double)( truePos + falsePos );
			double recall = (double) truePos / (double)( truePos + falseNeg );

			out << endl << QString( "True Positive Count = %1" ).arg( truePos ) << endl; 
			out << QString( "True Negative Count = %1" ).arg( trueNeg ) << endl; 
			out << QString( "False Positive Count = %1" ).arg( falsePos ) << endl;
			out << QString( "False Negative Count = %1" ).arg( falseNeg ) << endl;
			out << endl << QString( "Precision = %1" ).arg( precision ) << endl; 
			out << QString( "Recall = %1" ).arg( recall ) << endl;
			out << QString( "F-Score = %1" ).arg( ( 2.0 * precision * recall ) / ( precision + recall ) ) << endl;

			outputFile.close();
		}
	}
*/
}


void LinguisticaMainWindow::compareGoldStdSlot()
{
	StringToCStemList			goldStdWords;
	StringToCStemList::Iterator	goldStdWordsIt;
	CStemList					stemList;

	QString	goldStdFileName = Q3FileDialog::getOpenFileName( m_projectDirectory,
															"XML Files (*.xml)",
															this,
															"open file dialog",
															"Choose a gold standard file to open" );
	if( !goldStdFileName.isEmpty() )
	{ 
		
		QFile goldStdFile( goldStdFileName );
		if( goldStdFile.open( QIODevice::ReadOnly ) )
		{

			QDomDocument doc( "Alchemist" ), author_data, document_data;

			QString errorMsg;
			int errorLine, errorColumn;
			if( !doc.setContent( &goldStdFile, &errorMsg, &errorLine, &errorColumn ) ) 
			{
//Maybe we should put this back in.
//				QMessageBox::warning( this, "Gold Standard : XML Error", 
//				  QString( errorMsg + "\nLine: %1" + "Col: %2" ).arg( errorLine ).arg( errorColumn ), QMessageBox::Ok, NULL, NULL );

				return;
			}

			QString feature_name;

			QDomElement alchemist_doc, element, word, string, gloss,
						morph, piece, notes, morpheme, allomorph,
						lmnt, feature, name, feature_id, instance_id;
			QDomNodeList nodes;
			QDomNode node1, node2, node3, node4;
			QDomText text;

			CStem* pStem;

			QString strStem;

			bool skipWord = FALSE;
			int pieceCount, lastEnd, start, length;

			alchemist_doc = doc.documentElement();

			if( alchemist_doc.tagName() != "alchemist-doc" )
			{
				errorMsg = "The XML document \"" + alchemist_doc.tagName() + "\" is not an alchemist document.";
				QMessageBox::information( NULL, "Gold Standard : XML Error", errorMsg, "OK" );
				return; 
			}


			// Author data (optional)
			node1 = alchemist_doc.firstChild();
			if( !node1.isNull() && node1.isElement() && node1.nodeName() == "author-data" )
			{
				// Skip...
				node1 = node1.nextSibling();
			}


			// Document data (optional)
			if( !node1.isNull() && node1.isElement() && node1.nodeName() == "document-data" )
			{
				// Skip...		
				node1 = node1.nextSibling();
			}


			// Feature list first of morphology description
			if( node1.isNull() || !node1.isElement() || node1.nodeName() != "feature-list" )
			{
				// TODO: add to error string
			}
			else
			{
				// Skip...
				node1 = node1.nextSibling();
			}


			// Morpheme list second
			if( node1.isNull() || !node1.isElement() || node1.nodeName() != "morpheme-list" )
			{
				// TODO: add to error string
			}
			else
			{
				// Skip...
				node1 = node1.nextSibling();
			}


			// Word list last.. this is what we need!
			if( node1.isNull() || !node1.isElement() || node1.nodeName() != "word-list" )
			{
				// TODO: add to error string
			}
			else
			{
				node2 = node1.firstChild();

				while( !node2.isNull() &&
					   node2.isElement() &&
					   node2.nodeName() == "word" )
				{
					word = node2.toElement();
					node2 = node2.nextSibling();

					// score attribute
					if( !word.hasAttribute( "score" ) )
					{
						// TODO: add to error string
						continue;
					}
					else
					{
						if( word.attribute( "score" ) == "Not Scored" ) continue;
						else if( word.attribute( "score" ) == "Certain" ); // we want to look at these words
						else if( word.attribute( "score" ) == "Somewhat Certain" ) continue;
						else if( word.attribute( "score" ) == "Uncertain" ) continue;
					}

					// string element
					node3 = word.firstChild();
					if( !node3.isElement() || node3.nodeName() != "string" )
					{
						// TODO: add to error message
						continue;
					}					
					string = node3.toElement();

					// Make new gold standard word
					strStem = string.text();
					pStem = new CStem( strStem );

					// gloss element
					node3 = string.nextSibling();
					if( node3.isElement() && node3.nodeName() == "gloss" )
					{
						// Skip...
						node3 = node3.nextSibling();
					}

					// affix, root, and piece elements
					skipWord = FALSE;
					while( !node3.isNull() && 
						   node3.isElement() &&
						   ( node3.nodeName() == "piece" ||
							 node3.nodeName() == "affix" ||
							 node3.nodeName() == "root" ) &&
						   !skipWord )
					{
						if( node3.nodeName() == "affix" || node3.nodeName() == "root" )
						{
							morph = node3.toElement();	

							// string element
							node4 = morph.firstChild();
							if( node4.isElement() && node4.nodeName() == "string" ) 
							{
								string = node4.toElement();

								// no need to do anything with this string
								node4 = string.nextSibling();
							}
							else
							{
								// TODO: add to error string
							}

							// piece elements
							pieceCount = 0;
							lastEnd = -1;
							while( !node4.isNull() && node4.isElement() && node4.nodeName() == "piece" )
							{
								piece = node4.toElement();
								pieceCount++;

								// Not handling multi-piece morphemes yet
								if( pieceCount > 1 )
								{
									skipWord = TRUE;
									delete pStem; pStem = NULL;
									break;
								}

								if( !piece.hasAttribute( "start" ) ||
									!piece.hasAttribute( "length" ) )
								{
									// TODO: add to error string
									skipWord = TRUE;
									delete pStem; pStem = NULL;
									break;
								}

								// Maybe we'll want to handle these differently in the future
								// so I am leaving the distinction
								if( morph.tagName() == "affix" || morph.tagName() == "root" ) 
								{	
									start = piece.attribute( "start" ).toInt();
									length = piece.attribute( "length" ).toInt();
									
									// Not handling overlapping morphemes yet
									if( start <= lastEnd ) 
									{
										skipWord = TRUE;
										delete pStem; pStem = NULL;
										break;
									}
									lastEnd = start + length - 1;

									pStem->CutRightBeforeHere( start );
								}

								node4 = node4.nextSibling();
							}
						}
						else
						{
							// Word has unassigned pieces, skip...
							skipWord = TRUE;
							delete pStem; pStem = NULL;
						}

						node3 = node3.nextSibling();
					}

					if( skipWord ) continue;

					
					// Add word to gold standard words
					goldStdWordsIt = goldStdWords.find( strStem );
					if( goldStdWordsIt == goldStdWords.end() )
					{
						// New word...
						goldStdWordsIt = goldStdWords.insert( strStem, stemList );
                                                //goldStdWordsIt.data().setAutoDelete( TRUE );    @@@ fix this, make sure there are no memory leaks created here.
					}
					goldStdWordsIt.data().append( pStem );


					// notes element
					if( !node3.isNull() && node3.isElement() && node3.nodeName() == "notes" )
					{
						// Skip...
						node3 = node3.nextSibling();
					}

					if( !node3.isNull() )
					{
						// TODO: add to error string
					}
				}
			}
		}
		else
		{
			QMessageBox::information( NULL, "Attention", "Unable to open " + goldStdFileName + " .", "OK" );
			return; 
		}
    	
		goldStdFile.close();
	}
	else
	{
		return; 
	}
	
 
// Yu Hu's code
//----------------------------------------------------------------------
	QString								theWord;
	CStem*								theCStem; 
	CParse*								theParse; 
	StringToParse*						TempSedCuts; 
	StringToParse::Iterator				StringToParseIt;  
	StringToParse						SedCuts; 
	CCorpusWordCollection*				TempSFCut; 
	StringToParse						SFCuts; 
	CCorpusWord*						theCorpusWord;

	// Get the Lingustica analyses result SF or PF
	if ( !m_lexicon) return; 
	TempSFCut = m_lexicon->GetWords();

	TempSFCut->Sort( KEY );

	for( int i = 0; i < TempSFCut->GetCount(); i++ )
	{
		theCorpusWord = TempSFCut->GetAt(i);
		theWord = theCorpusWord->Display();
		
		SFCuts.insert(theWord, theCorpusWord);
	
	}

	// Get SED analyses
	if ( m_Words_Templates != NULL)
	{
		TempSedCuts = m_Words_Templates ->GetParsedResult();
		for ( StringToParseIt = TempSedCuts ->begin(); StringToParseIt != TempSedCuts ->end(); 	StringToParseIt++)
		{
			theWord = StringToParseIt.key();
			theParse = StringToParseIt.data(); 
			theCStem = new CStem(*theParse); 
		
			SedCuts.insert(theWord, theCStem); 
		}
		

	}

	// Goldstandard comparison output
	double TotalPrecision;
	double TotalRecall;
	double AveragePrecision;
	double AverageRecall;

	double Ftot=0.0;
	double Fav=0.0;
	QString					outs; 
	
	////////////// compute precision recall		SF	

	GetMorphPrecisionRecallByWord( goldStdWords, SFCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
	Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);	
	// print out precision recall
	outs = QString("Total precision MiniLexicon = %1, total recall= %2 Ftot=%3 ").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

	QMessageBox::information ( NULL, "SF Morpheme Precision/Recall By Word", outs );

	GetMorphPrecisionRecall( goldStdWords, SFCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
	Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);	
	// print out precision recall
	outs = QString("Total precision MiniLexicon = %1, total recall= %2 Ftot=%3 ").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

	QMessageBox::information ( NULL, "SF Morpheme Precision/Recall", outs );

	GetCutPrecisionRecall( goldStdWords, SFCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
	Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);	
	// print out precision recall
	outs = QString("Total precision MiniLexicon = %1, total recall= %2 Ftot=%3 ").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

	QMessageBox::information ( NULL, "SF Cut Precision/Recall", outs );

	

	
		
	///////////////////////////////// SED
	if ( m_Words_Templates != NULL)
	{
	
		GetMorphPrecisionRecallByWord( goldStdWords, SedCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	
		Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
		Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);

		outs = QString("Total precision SED= %1, total recall= %2 Ftot=%3").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

		QMessageBox::information ( NULL, "SED Morpheme Precision/Recall By Word", outs );
	
		GetMorphPrecisionRecall( goldStdWords, SedCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	
		Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
		Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);

		outs = QString("Total precision SED= %1, total recall= %2 Ftot=%3").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

		QMessageBox::information ( NULL, "SED Morpheme Precision/Recall By Word", outs );

	
		GetCutPrecisionRecall( goldStdWords, SedCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	
		Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
		Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);

		outs = QString("Total precision SED= %1, total recall= %2 Ftot=%3").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

		QMessageBox::information ( NULL, "SED Cut Precision/Recall", outs );
	}
}



void LinguisticaMainWindow::GetMorphPrecisionRecallByWord( StringToCStemList& goldStdWords, 
														   StringToParse& lxaWords, 
														   double& totalPrecision, 
														   double& totalRecall,
														   double& averagePrecision, 
														   double& averageRecall )
{
	CParse*	pGoldStdStem;
	int*	goldStdStemCuts;
        int	goldStdStemCutsPos;

	CParse*	pLxaStem;
	int*	lxaStemCuts;
        int	lxaStemCutsPos;

        int     totalNumLxaWordsCompared = 0;
        int     totalNumGSWordsCompared = 0;

        int     totalNumLxaMorphemes = 0;
        int     totalNumGSMorphemes = 0;
        int     totalNumCorrectMorphemes = 0;
        int     totalNumFoundMorphemes = 0;		// For precision, see generalization notes below in function

                averagePrecision = 0.0;
                averageRecall = 0.0;

	QString strWord;

	StringToCStemList::Iterator goldStdIt;
	for( goldStdIt = goldStdWords.begin(); goldStdIt != goldStdWords.end(); goldStdIt++ )
	{
		strWord = goldStdIt.key();

		// We only look through words that exist in both spaces
		if( lxaWords.find( strWord ) == lxaWords.end() ) continue;
		pLxaStem = lxaWords.find( strWord ).data();

		lxaStemCuts = pLxaStem->GetPieces();

		int numLxaMorphemes,
			numGSMorphemes,
			numCorrectMorphemes;

		totalNumLxaWordsCompared++;

		// There may be duplicates in gold standard, we should consider all
		for( pGoldStdStem = goldStdIt.data().first(); pGoldStdStem; pGoldStdStem = goldStdIt.data().next() )
		{
			numLxaMorphemes = 0;
			numGSMorphemes = 0;
			numCorrectMorphemes = 0;

			totalNumGSWordsCompared++;

			goldStdStemCuts = pGoldStdStem->GetPieces();

			// The word strings should match now...
			Q_ASSERT( pLxaStem->Display() == pGoldStdStem->Display() );

			// Therefore we can look at the cuts to compare the morphemes
			lxaStemCutsPos = goldStdStemCutsPos = 0;
			while( lxaStemCutsPos < pLxaStem->Size() && goldStdStemCutsPos < pGoldStdStem->Size() )
			{
				if( lxaStemCuts[ lxaStemCutsPos ] == goldStdStemCuts[ goldStdStemCutsPos ] &&
					lxaStemCuts[ lxaStemCutsPos + 1 ] == goldStdStemCuts[ goldStdStemCutsPos + 1 ] )
				{
					// Morphemes match, increment everything
					numLxaMorphemes++;
					numGSMorphemes++;
					numCorrectMorphemes++;

					// Move both positions
					lxaStemCutsPos++;
					goldStdStemCutsPos++;
				}
				else if( lxaStemCuts[ lxaStemCutsPos ] == goldStdStemCuts[ goldStdStemCutsPos ] )
				{
					if( lxaStemCuts[ lxaStemCutsPos + 1 ] < goldStdStemCuts[ goldStdStemCutsPos + 1 ] )
					{
						numLxaMorphemes++;
						lxaStemCutsPos++;
					}
					else
					{
						numGSMorphemes++;
						goldStdStemCutsPos++;
					}
				}
				else
				{
					if( lxaStemCuts[ lxaStemCutsPos ] < goldStdStemCuts[ goldStdStemCutsPos ] )
					{
						numLxaMorphemes++;
						lxaStemCutsPos++;
					}
					else
					{
						numGSMorphemes++;
						goldStdStemCutsPos++;
					}
				}
			}
			
			// Handle remaining morphemes in either group
			while( lxaStemCutsPos < pLxaStem->Size() )
			{
				numLxaMorphemes++;
				lxaStemCutsPos++;
			}
			while( goldStdStemCutsPos < pGoldStdStem->Size() )
			{
				numGSMorphemes++;
				goldStdStemCutsPos++;
			}

			averageRecall += ( (double) numCorrectMorphemes / (double) numGSMorphemes );
			
			totalNumGSMorphemes += numGSMorphemes;
			totalNumCorrectMorphemes += numCorrectMorphemes;
		}


		// Precision generalization: if Lxa finds a morpheme M in a word W, it
		// gets credit for it if M appears in any of the analyses spelled W.
		// From John's e-mail to Colin, July 27, 2006

		numLxaMorphemes = 0;
		int numFoundMorphemes = 0;
		int piece = 1;
		while( piece <= pLxaStem->Size() )
		{
			numLxaMorphemes++;

			for( pGoldStdStem = goldStdIt.data().first(); pGoldStdStem; pGoldStdStem = goldStdIt.data().next() )
			{
				if( pGoldStdStem->Contains( pLxaStem->GetPiece( piece ) ) )
				{
					numFoundMorphemes++;
					break;
				}
			}

			piece++;
		}

		totalNumLxaMorphemes += numLxaMorphemes;
		totalNumFoundMorphemes += numFoundMorphemes;

		averagePrecision += ( (double) numFoundMorphemes / (double) numLxaMorphemes );
	}

	averagePrecision /= (double) totalNumLxaWordsCompared;
	averageRecall /= (double) totalNumGSWordsCompared;

	totalPrecision = (double) totalNumFoundMorphemes / (double) totalNumLxaMorphemes;
	totalRecall = (double) totalNumCorrectMorphemes / (double) totalNumGSMorphemes;
}


void LinguisticaMainWindow::GetCutPrecisionRecall( StringToCStemList& goldStdWords,
												   StringToParse& lxaWords,
												   double& totalPrecision,
												   double& totalRecall,
												   double& averagePrecision,
												   double& averageRecall )
{
	CParse*	pGoldStdStem;
	int*	goldStdStemCuts;
	int		goldStdStemCutsPos;

	CParse*	pLxaStem;
	int*	lxaStemCuts;
	int		lxaStemCutsPos;

	int totalNumLxaWordsCompared = 0;	
	int totalNumGSWordsCompared = 0;

	int totalNumLxaCuts = 0;
	int totalNumGSCuts = 0;
	int totalNumCorrectCuts = 0;
	int totalNumFoundCuts = 0;		// Need different number for precision (using totalNumCorrectCuts for recall)
	int totalNumOnePieceWords = 0;	// One piece Lxa words are undefined for precision, we need to subtract when
									// totalling

	averagePrecision = 0.0;
	averageRecall = 0.0;

	QString strWord;

	StringToCStemList::Iterator goldStdIt;
	for( goldStdIt = goldStdWords.begin(); goldStdIt != goldStdWords.end(); goldStdIt++ )
	{
		strWord = goldStdIt.key();

		// We only look through words that exist in both spaces
		if( lxaWords.find( strWord ) == lxaWords.end() ) continue;
		pLxaStem = lxaWords.find( strWord ).data();

		lxaStemCuts = pLxaStem->GetPieces();

		int numLxaCuts = 0,
			numGSCuts = 0,
			numCorrectCuts = 0,
			numFoundCuts = 0;

		totalNumLxaWordsCompared++;

		Q3ValueList<int> unionOfGSCuts;

		// There may be duplicates in gold standard, we need the union of all their cuts
		for( pGoldStdStem = goldStdIt.data().first(); pGoldStdStem; pGoldStdStem = goldStdIt.data().next() )
		{
			totalNumGSWordsCompared++;

			goldStdStemCuts = pGoldStdStem->GetPieces();

			// The word strings should match here.
			Q_ASSERT( pLxaStem->Display() == pGoldStdStem->Display() );

			goldStdStemCutsPos = 0;
			while( goldStdStemCutsPos < pGoldStdStem->Size() )
			{
				if( unionOfGSCuts.find( goldStdStemCuts[ goldStdStemCutsPos ] ) == unionOfGSCuts.end() )
				{
					unionOfGSCuts.append( goldStdStemCuts[ goldStdStemCutsPos ] );
				}
				goldStdStemCutsPos++;
			}
		}
			
		lxaStemCutsPos = 0;
		while( lxaStemCutsPos < pLxaStem->Size() )
		{
			numLxaCuts++;

			if( unionOfGSCuts.find( lxaStemCuts[ lxaStemCutsPos ] ) != unionOfGSCuts.end() )
			{
				numCorrectCuts++;
				numFoundCuts++;
			}
			lxaStemCutsPos++;
		}

		numGSCuts = unionOfGSCuts.count();

		averageRecall += ( (double) numCorrectCuts / (double) numGSCuts );
		
		totalNumGSCuts += numGSCuts;
		totalNumCorrectCuts += numCorrectCuts;

		if( pLxaStem->Size() < 2 ) 
		{
			totalNumOnePieceWords++;

			Q_ASSERT( numFoundCuts == 1 && numLxaCuts == 1 );
			numFoundCuts--;
			numLxaCuts--;
			
			if( numFoundCuts < 0 ) numFoundCuts = 0;
			if( numLxaCuts < 0 ) numLxaCuts = 0;
		}
			
		totalNumLxaCuts += numLxaCuts;
		totalNumFoundCuts += numFoundCuts;

		if( numLxaCuts > 0 ) averagePrecision += ( (double) numCorrectCuts / (double) numLxaCuts );
	}

	averagePrecision /= (double) ( totalNumLxaWordsCompared - totalNumOnePieceWords );
	averageRecall /= (double) totalNumGSWordsCompared;

	totalPrecision = (double) totalNumFoundCuts / (double) totalNumLxaCuts;
	totalRecall = (double) totalNumCorrectCuts / (double) totalNumGSCuts;
}


void LinguisticaMainWindow::GetMorphPrecisionRecall( StringToCStemList& goldStdWords,
													 StringToParse& lxaWords,
													 double& totalPrecision,
													 double& totalRecall,
													 double& averagePrecision,
													 double& averageRecall )
{
	QStringList unionOfGoldStdMorphs,
				unionOfLxaMorphs;

	QString strWord, strPiece;

	CParse* pLxaStem, * pGoldStdStem;

	int i,
		totalNumLxaWordsCompared = 0,
		totalNumGSWordsCompared = 0,
		totalNumLxaMorphemes = 0,
		totalNumGSMorphemes = 0,
		totalNumCorrectMorphemes = 0;

	StringToCStemList::Iterator goldStdIt;
	for( goldStdIt = goldStdWords.begin(); goldStdIt != goldStdWords.end(); goldStdIt++ )
	{
		strWord = goldStdIt.key();

		// We only look through words that exist in both spaces
		if( lxaWords.find( strWord ) == lxaWords.end() ) continue;
		pLxaStem = lxaWords.find( strWord ).data();

		totalNumLxaWordsCompared++;

		for( i = 1; i <= pLxaStem->Size(); i++ )
		{
			strPiece = pLxaStem->GetPiece(i).Display();
			if( unionOfLxaMorphs.findIndex( strPiece ) == -1 )
			{
				unionOfLxaMorphs.append( strPiece );
			}
		}

		// There may be duplicates in gold standard, we need the union of all their morphemes
		for( pGoldStdStem = goldStdIt.data().first(); pGoldStdStem; pGoldStdStem = goldStdIt.data().next() )
		{
			totalNumGSWordsCompared++;

			for( i = 1; i <= pGoldStdStem->Size(); i++ )
			{
				strPiece = pGoldStdStem->GetPiece(i).Display();
				if( unionOfGoldStdMorphs.findIndex( strPiece ) == -1 )
				{
					unionOfGoldStdMorphs.append( strPiece );
				}
			}
		}
	}

	unionOfLxaMorphs.sort();
	unionOfGoldStdMorphs.sort();

	QStringList::Iterator lxaMorphsIt = unionOfLxaMorphs.begin(),
						  goldStdMorphsIt = unionOfGoldStdMorphs.begin();

	while( lxaMorphsIt != unionOfLxaMorphs.end() &&
		   goldStdMorphsIt != unionOfGoldStdMorphs.end() )
	{
		if( *goldStdMorphsIt == *lxaMorphsIt )
		{
			totalNumCorrectMorphemes++;
			totalNumLxaMorphemes++;
			totalNumGSMorphemes++;

			++goldStdMorphsIt;
			++lxaMorphsIt;
		}
		else if( *goldStdMorphsIt > *lxaMorphsIt )
		{
			totalNumLxaMorphemes++;

			++lxaMorphsIt;
		}
		else // *goldStdMorphsIt < *lxaMorphsIt
		{
			totalNumGSMorphemes++;

			++goldStdMorphsIt;
		}
	}

	totalPrecision = (double) totalNumCorrectMorphemes / (double) totalNumLxaMorphemes;
	totalRecall = (double) totalNumCorrectMorphemes / (double) totalNumGSMorphemes;

	averagePrecision = totalPrecision;
	averageRecall = totalRecall;
}



/*  This is the old version that Yu Hu wrote before Alchemist 3.0
	I am keeping it here for reference. The last part of compareGoldStdSlot()
	was transferred	to the new version.

void LinguisticaMainWindow::compareGoldStdSlot()
{
	QString								line;
	//int									FoundLoc;
	QString								FirstPiece, RemainingPiece; 
	QString								theWord;
	CStem*								theCStem; 
	CParse*								theParse; 
	StringToParse*						TempSedCuts; 
	StringToParse::Iterator				StringToParseIt; 
	StringToPtrCStem					GoldCuts; 
	StringToParse						SedCuts; 
	StringToPtrCStem::Iterator			GoldStIt; 
	StringToCStem::Iterator				SFIt; 
	CCorpusWordCollection*				TempSFCut; 
	StringToParse						SFCuts; 
	CCorpusWord*						theCorpusWord;

	// 1. Read GoldStand File

	QString goldFileName;
	
	goldFileName = QFileDialog::getOpenFileName( m_projectDirectory,
												 "XML Files (*.xml)",
												 this,
												 "open file dialog",
												 "Choose a file to open" );
												 
	if( !goldFileName.isEmpty() )
	{ 
	
		QFile goldFile( goldFileName );
		if ( goldFile.open( IO_ReadOnly ) )
		{
			QDomDocument doc( "Goldstandard" );
				
			 if( !doc.setContent(&goldFile) )
			 {
  				goldFile.close();
  				return;
			 }
			
			QDomElement root = doc.documentElement();
  		
			QString	rootTagName = root.tagName();
			
			if( root.tagName() != "GDS")
			{
				QMessageBox::information( NULL, "Error", "There was an error reading the Gold Standard. The following XML tag cannot be read: " + rootTagName, "OK" );
				goldFile.close();
				return; 
			}
			
			// Read the header
			 QDomNode header = root.firstChild();

			 QDomElement direction = header.nextSibling().toElement();
			 
			// Filling into the docinfo
			 // Read the content
			 QDomNode contentnode = direction.nextSibling();
			 QDomElement content = contentnode.toElement();

			 if( content.tagName() != "content" )
    		 {
			 	QMessageBox::information( NULL, "Error", "Sorry, the xml file format is not supported", "OK" );
				goldFile.close();
				return;
			 }

			 
			 
			 QString				value; 
			 int					supposedtotalnumberofwords; 
			 QString				key;
			 QString				wordcomment; 
			 int					numberofpieces;  
			 int					start; 
			 int					type;
			 int					color; 
			 int					score;
			 QString				allomorph, comment; 
//			 int					Index; 
			 
			 
			 value = content.attribute("number", "100"); 
			 supposedtotalnumberofwords = value.toInt(); 
			 
			 QDomNode onewordnode = content.firstChild();
			 
			 while (!onewordnode.isNull())
			 {
			 	QDomElement oneword = onewordnode.toElement();
			 	if( !oneword.isNull() )
  				{
					if( oneword.tagName() == "word" )
    				{
						key = oneword.attribute( "key", "" );
						if (key == "")
						{
							onewordnode = onewordnode.nextSibling();
							continue; 
						}
						
						theWord = key;
						theCStem = new CStem(key);
						GoldCuts.insert(theWord, theCStem); 

						value = oneword.attribute("morphemes", "0"); 
						numberofpieces = value.toInt();
						
						if (numberofpieces == 0)
						{
							onewordnode = onewordnode.nextSibling();
							continue;
						}
						
						wordcomment = oneword.attribute("comment", "");
						

						QDomNode onepiecenode = oneword.firstChild();		
						
						while (!onepiecenode.isNull())
			 			{
							QDomElement onepiece = onepiecenode.toElement();
			 				if( !onepiece.isNull() )
  							{
								if( onepiece.tagName() == "morpheme" )
    							{
									value = onepiece.attribute("start", "-1");
									start = value.toInt();
									value =onepiece.attribute("type", "-1"); 
									type = value.toInt();
										
									
									if ( type == 0)
									{
										GoldCuts.remove(theWord); 
										delete theCStem;
										break; 
									}
									

									value = onepiece.attribute("color", "-2");
									color = value.toInt();
									value = onepiece.attribute("score", "0");
									score = value.toInt();
									allomorph = onepiece.attribute("allomorph", "");
									comment = onepiece.attribute("comment", "");
									
									if ( ( start == -1) || (type == -1) || (color == -2)) 
 									{
										onepiecenode = onepiecenode.nextSibling();
										continue; 
									}
									
									theCStem ->CutRightBeforeHere(start); 
									

									//m_WordCollection ->ParseOneWord(key, start, type, color, true, score, allomorph, comment, Index, wordcomment);
									 
									
								}
							}	
						
							onepiecenode = onepiecenode.nextSibling();
						}			
						
						
					}
				}
					
				onewordnode = onewordnode.nextSibling();
			 }

		}
		else
		{
			QMessageBox::information( NULL, "Attention", "Unable to open " + goldFileName + " .", "OK" );
			return; 
		}
    	
		goldFile.close();

	}
	else
	{
		return; 
	}

	// Get the Lingustica analyses result SF or PF

	if ( !m_lexicon) return; 
	TempSFCut = m_lexicon->GetWords();

	TempSFCut->Sort( KEY );

	for( int i = 0; i < TempSFCut->GetCount(); i++ )
	{
		theCorpusWord = TempSFCut->GetAt(i);
		theWord = theCorpusWord->Display();
		
		SFCuts.insert(theWord, theCorpusWord);
	
	}

	// Get SED analyses
	if ( m_Words_Templates != NULL)
	{
		TempSedCuts = m_Words_Templates ->GetParsedResult();
		for ( StringToParseIt = TempSedCuts ->begin(); StringToParseIt != TempSedCuts ->end(); 	StringToParseIt++)
		{
			theWord = StringToParseIt.key();
			theParse = StringToParseIt.data(); 
			theCStem = new CStem(*theParse); 
		
			SedCuts.insert(theWord, theCStem); 
		}
		

	}

	// Goldstandard comparison output
	double TotalPrecision;
	double TotalRecall;
	double AveragePrecision;
	double AverageRecall;

	double Ftot=0.0;
	double Fav=0.0;
	QString					outs; 
	
	////////////// compute precision recall		SF	

	GetPrecisionRecall(GoldCuts,SFCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
	Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);	
	// print out precision recall
	outs = QString("Total precision MiniLexicon = %1, total recall= %2 Ftot=%3 ").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

	QMessageBox::information ( NULL, "Irinaoutput", outs );

	
		
	///////////////////////////////// SED
	if ( m_Words_Templates != NULL)
	{
	
		GetPrecisionRecall(GoldCuts,SedCuts, TotalPrecision, TotalRecall,AveragePrecision,AverageRecall);
	
		Ftot=2*TotalPrecision*TotalRecall/(TotalPrecision+TotalRecall);
		Fav=2*AveragePrecision*AverageRecall/(AveragePrecision+AverageRecall);

		outs = QString("Total precision SED= %1, total recall= %2 Ftot=%3").arg(TotalPrecision).arg(TotalRecall).arg(Ftot);

		QMessageBox::information ( NULL, "Irinaoutput", outs );
	}

	// TODO: delete all QMap data that are pointers
}


void LinguisticaMainWindow::GetPrecisionRecall(StringToCStemList& GoldStM, StringToParse&  ResultM, double &TotalPrecision, double &TotalRecall, double &AveragePrecision, double &AverageRecall )
{

	// iterate through the gold standard QMap GoldStM
	// look up each word in the results QMap ResultM
	// get the CParses for each word from GoldStM and ResultM and compare them


	// precision and recall are computed for all cuts	
	// average precision and recall: precision and recall are computed for each word and then averaged

	StringToCStemList::Iterator		GoldStIt;	
	CParse*							ReferenceStem;
	CParse*							ResultStem;
//	CParse*							ReferenceParse;
//	CParse*							ResultParse;
	int*							ReferenceCuts;
	int*							ResultCuts;
	QString							Word;

    // simultaneously collect the results for individual morphemes	

	int TotalNumReferenceCuts=0;
	int TotalNumResultCuts=0;
	int TotalNumRightCuts=0;// use for precision
	int TotalNumMissedReferenceCuts=0; // use for recall

	AveragePrecision=0;
	AverageRecall=0;
	TotalPrecision=0;
	TotalRecall=0;

	int NumWords=0;

	for( GoldStIt = GoldStM.begin(); GoldStIt != GoldStM.end();GoldStIt++)
	{

		
	// do for each word	
	// get the reference and the result cuts

		Word = GoldStIt.key();
		for( ReferenceStem = GoldStIt.data().first(); ReferenceStem; ReferenceStem = GoldStIt.data().next() )
		{ 
			// For now, we are only handling one version of each word
			// string. We need to escape after the first.
			if( ReferenceStem != GoldStIt.data().first() )
			{
				break;
			}

			//ReferenceParse=ReferenceStem->GetStemPtr();
			ReferenceCuts=ReferenceStem->GetPieces();



			if(ResultM.contains(Word))
			{
				NumWords++;

				ResultStem=ResultM[Word];
			//	ResultParse=ResultStem->GetStemPtr();
				ResultCuts=ResultStem->GetPieces();


				// compare these two analyses	
				int RefSz=ReferenceStem->Size();
				int ResSz=ResultStem->Size();

	
				int RefCount=1;// the first index is always 0
				int ResCount=1;// the first index is always 0

				int NumRightCuts=0;
				int NumMissedCuts=0;

				// compare the cuts
				// if there is only one morpheme=word in both analyses:
				if(RefSz==1&& ResSz==1)
					{

						AveragePrecision+=1;
						AverageRecall+=1;
						TotalNumRightCuts++;
						TotalNumReferenceCuts+=(RefSz);
						TotalNumResultCuts+=(ResSz);
	
						continue;
					}
					else if(RefSz==1) // all cuts are wrong
					{

						TotalNumResultCuts+=(ResSz-1);	
						continue;
					}
					else if(ResSz==1)
					{
						TotalNumReferenceCuts+=(RefSz-1);
						continue;
					}

				TotalNumReferenceCuts+=(RefSz-1);
				TotalNumResultCuts+=(ResSz-1);

				int begin=0;
				int end=0;

				while(RefCount<(RefSz) && ResCount<(ResSz))
				{
				  int NextRefIndex=ReferenceCuts[RefCount];
				  int NextResIndex=ResultCuts[ResCount];

					if(NextRefIndex == NextResIndex)// the right cut
					{
							

							NumRightCuts++;
							TotalNumRightCuts++;

							RefCount++;
							ResCount++;

					}
					else if(NextRefIndex < NextResIndex)//missed cut
					{	
	
							//NumMissedCuts++;
							//TotalNumMissedReferenceCuts++;

							RefCount++;
					}
					else if (NextRefIndex > NextResIndex)//wrong cut
					{
							ResCount++;
					}
				}

				double WordPrecision=(double)NumRightCuts/(double)(ResSz-1);
				double WordRecall=(double)NumRightCuts/(double)(RefSz-1);
				AveragePrecision+=WordPrecision;
				AverageRecall+=WordRecall;
				
			}
		}
	}


	AveragePrecision/=(double)NumWords;
	AverageRecall/=(double)NumWords;

	TotalPrecision=(double)TotalNumRightCuts/(double)TotalNumResultCuts;
	TotalRecall=(double)TotalNumRightCuts/(double)TotalNumReferenceCuts;

}

*/

