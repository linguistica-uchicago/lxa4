// User interface for Dynamic Computational Network computations
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include <QMessageBox>
#include <QString>
#include "DCNlearningsyl.h"
#include "DCNcorpussyl.h"
#include "DCNlearning.h"
#include "DCNsnetwork.h"
#include "DCNgrammar.h"
#include "Lexicon.h"

/* 
	This file contains all the GUI slots for the DCN tabs, namely
	DCN Stress and DCN Syllabification
*/

//	DCN STRESS FUNCTIONS:

// sets up a grammar, snetwork, and then computes the dcn from the 
// data given by the user (alpha through max)
void LinguisticaMainWindow::DCNstressComputeSlot()
{
	float alpha = alphaLine->text().toFloat();
	float beta  = betaLine->text().toFloat();
	float I		= initialLine->text().toFloat();
	float F		= finalLine->text().toFloat();
	int		min	= 2;	//minLine->text().toInt();
	int		max = 15;	//maxLine->text().toInt();

	grammar *theGrammar = new grammar();
	theGrammar->setValues(alpha, beta, I, F, 0, 0);
	snetwork *theSnetwork = new snetwork(min, max);
	theSnetwork->setGrammar(theGrammar);
	theSnetwork->equilibrium();
	theSnetwork->print(corpusTextEdit);
	delete theGrammar;
	delete theSnetwork;
}

// sets up a learning system, reads in the corpus, and runs the learning
// algorithm.
void LinguisticaMainWindow::DCNstressLearnSlot()
{
	learning DCNlearn;
	
	DCNlearn.TfromUser			= TLine->text().toFloat();
	DCNlearn.increaseWhenWrong	= iwwLine->text().toFloat();
	DCNlearn.decreaseWhenRight	= dwrLine->text().toFloat();
	DCNlearn.numberOfTries		= trialsLine->text().toInt();
	DCNlearn.cutoffFromUser		= cutoffLine->text().toInt();

	DCNlearn.startingAlpha		= sAlphaLine->text().toFloat();
	DCNlearn.startingBeta		= sBetaLine->text().toFloat();
	DCNlearn.startingI			= sInitialLine->text().toFloat();
	DCNlearn.startingF			= sFinalLine->text().toFloat();

	int maxCorpusIndex = corpusTextEdit->lines() - 1;

	QString  theWindow = corpusTextEdit->text();
	QString* corpus = new QString[maxCorpusIndex];
	
	for (int i = 0; i < maxCorpusIndex; i++)
	{
		QString word = corpusTextEdit->text(i);
		int length = word.length();
		length--;
		word.truncate(length);
		corpus[i] = word;
	}
	
	DCNlearn.setCorpus(corpus, maxCorpusIndex);

	DCNlearn.run(this);
	
	
	grammar* theGrammar = DCNlearn.returnGrammar();
	snetwork theSnetwork(2, 15);
	theSnetwork.setGrammar(theGrammar);
	theSnetwork.equilibrium();

	float alpha = theGrammar->getAlpha();
	float beta  = theGrammar->getBeta();
	float I		= theGrammar->getI();
	float F		= theGrammar->getF();

	if (DCNlearn.isSuccessful())
	{
		QMessageBox::information( this, "DCN Stress Learning Algorithm",
			"The learning algorithm was successful!" );

		QString string;
		string.setNum(alpha);			alphaLine->setText(string);
		string.setNum(beta);			betaLine->setText(string);
		string.setNum(I);				initialLine->setText(string);
		string.setNum(F);				finalLine->setText(string);

	}
	else
	{
		QMessageBox::warning( this, "dcn syl",
    		"Sorry, the learning algorithm was unsuccessful." );
	}
	
	delete[] corpus;

}


//	DCN SYLLABIFICATION FUNCTIONS:

// opens the training corpus
void LinguisticaMainWindow::DCNsylFindTrainSlot()
{
	QString					trainFileName;

	trainFileName = Q3FileDialog::getOpenFileName( trainFileName,
												 "TXT Files (*.txt)",
												 NULL,
												 "open file dialog",
												 "Choose a training file to open" );
	if ( trainFileName.isEmpty() )
		return;

	QFile trainFile(trainFileName);

	m_lexicon->DCNsylTrainCorpus = new corpussyl;
	m_lexicon->DCNsylTrainCorpus->readInput(trainFile);
	m_lexicon->isDCNtrainRead = true;
	
}

// opens the testing corpus
void LinguisticaMainWindow::DCNsylFindTestSlot()
{
	QString					testFileName;

	testFileName = Q3FileDialog::getOpenFileName( testFileName,
												 "TXT Files (*.txt)",
												 NULL,
												 "open file dialog",
												 "Choose a test file to open" );
	if ( testFileName.isEmpty() )
		return; 

	QFile testFile(testFileName);

	m_lexicon->DCNsylTestCorpus = new corpussyl;
	m_lexicon->DCNsylTestCorpus->readInput(testFile); // testFile
	m_lexicon->isDCNtestRead = true;
}

// trains the network.
void LinguisticaMainWindow::DCNsylTrainSlot()
{
	if (!(m_lexicon->isDCNtrainRead && m_lexicon->isDCNtestRead))
	{
		QMessageBox::information( this, "Linguistica DCN Syllabification",
    	"Unable to access the Training and Test corpera.\n"
		"Please select the corresponding corpera with the \"Find Training Corpus\" and "
		"\"Find Testing Corpus\" buttons." );
	}
    	
	learningsyl DCNlearn;
	DCNlearn.setCorpus(*m_lexicon->DCNsylTrainCorpus);

	
	DCNlearn.TfromUser			= TLineS->text().toFloat();
	DCNlearn.increaseWhenWrong	= iwwLineS->text().toFloat();
	DCNlearn.decreaseWhenRight	= dwrLineS->text().toFloat();
	DCNlearn.numberOfTries		= trialsLineS->text().toInt();
	DCNlearn.cutoffFromUser		= cutoffLineS->text().toInt();

	DCNlearn.startingAlpha		= sAlphaLineS->text().toFloat();
	DCNlearn.startingBeta		= sBetaLineS->text().toFloat();

	DCNlearn.run(this);

	//do some output
	if (!DCNlearn.isSuccessful())
	{
		QMessageBox::warning( this, "Linguistica DCN Syllabification",
    	"Sorry, the training algorithm was unsuccessful." );
	}
	else
	{
		QMessageBox::information( this, "Linguistica DCN Syllabification",
    	"The training algorithm was successful!" );
	}
		grammarsyl* gram = DCNlearn.returnGrammar();
		grammarOutputS->setText(gram->print());
		corpusOutputS ->setText(m_lexicon->DCNsylTestCorpus->printCorpus(gram));
}
