// UI actions for discovering phonology
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include <QMessageBox>
#include "corpusviewdialog.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "StateEmitHMM.h"
#include "Sequencer.h"
#include "Stats.h"
#include "WordCollection.h"
 
void LinguisticaMainWindow::GenericPhonologySlot()
{
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

	if ( current_mini )
	{
		current_mini->GetWords()->DoPhonology();
	}
	// Update tree view
  emit updateAllViewsSignal();
}
void LinguisticaMainWindow::CreateSkeletonSlot() // Creates CV template
{
	 
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());
	if ( current_mini )
	{
		current_mini->GetWords()->CreateCVTemplate();
	}


	// Update tree view
  emit updateAllViewsSignal();
}

void LinguisticaMainWindow::PhonologyCalculateInformation()
{


}

void LinguisticaMainWindow::DropTierLeaveSlot()
{
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

	if ( current_mini )
	{
		current_mini->GetWords()->SplitPhonologyToTiers( Split_LeaveSlot);
		current_mini->GetWords()->ComputeZ();
		current_mini->GetWords()->ComputeZStar();
		current_mini->GetWords()->ComputeBoltzmannProbabilities();

	}
	

	// Update tree view
	emit updateAllViewsSignal();

}
void LinguisticaMainWindow::DropTierLeaveCopy()
{
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());
	if ( current_mini)
	{
		current_mini->GetWords()->SplitPhonologyToTiers( Split_LeaveCopy);
		current_mini->GetWords()->ComputeZ();
		current_mini->GetWords()->ComputeZStar();
		current_mini->GetWords()->ComputeBoltzmannProbabilities();
	}
	

	// Update tree view
	emit updateAllViewsSignal();

}
void LinguisticaMainWindow::PhonologyComputeGibbsFunction() // currently not used.
{
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());
	if ( current_mini)
	{
		//current_mini->GetWords()->ComputeZ();
	}
	// Update tree view
	emit updateAllViewsSignal();
}
 
 /////////// End of John's Phonology
 
void LinguisticaMainWindow::sequencerReadCorpusSlot()
{
	if ( m_Sequencer == NULL)
	{
		return;
	}

	m_Sequencer ->readCorpus(); 


}
 
void LinguisticaMainWindow::sequenceASentenceSlot()
{
	if ( m_Sequencer == NULL)
	{
		return;
	}

	int			birank; 
	int			trirank;


	//m_Sequencer ->sequenceASentence(birank,trirank); 
	m_Sequencer ->sequenceASentence2(birank,trirank); 


}

void LinguisticaMainWindow::sequencerTestAFileSlot()
{
	if ( m_Sequencer == NULL)
	{
		return;
	}

	m_Sequencer ->sequencerTestAFile(); 

}
 
void LinguisticaMainWindow::statsReadCorpusSlot()
{
	if ( m_Stats == NULL)
	{
		return;
	}

	m_Stats->readCorpus();

}

void LinguisticaMainWindow::DCNstressSlot()
{
//	combinedWindow *window = new combinedWindow(0, "DCN");
//	window->show();
}

void LinguisticaMainWindow::DCNsylSlot()
{
//	windowsyl* window = new windowsyl(0, "DCN Main Window");
//	window->show();
}

void LinguisticaMainWindow::fromStemsFindCompoundsSlot()
{
	if( m_logging ) OpenLogFile();
	m_lexicon->FromStemsFindCompounds();
	if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

	// Unsaved work
	m_projectDirty = true;

	// Update tree view
	emit updateAllViewsSignal();
}

void LinguisticaMainWindow::fromStemsFindFlatCompoundsSlot()
{
	if( m_logging ) OpenLogFile();
	m_lexicon->FromStemsFindFlatCompounds();
	if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

	// Unsaved work
	m_projectDirty = true;

	// Update tree view
	emit updateAllViewsSignal();
}


// HMM part
void LinguisticaMainWindow::testSEMHMMSlot()
{
	
	CWordCollection*			dataCorpus;
	StateEmitHMM*				pHMM; 
	bool						dataIsRight; 
	int							NumberOfIterations(70);
	int							NumberOfStates; 


	NumberOfIterations = m_lexicon ->GetIntParameter ("HMM\\NumberOfIterations", 25);
	NumberOfStates =	 m_lexicon ->GetIntParameter ("HMM\\NumberOfStates", 2);

	if ( !m_lexicon) 
	{
		QMessageBox::information ( this, "Linguistica : Error", "Lexicon is NULL when running HMM!" );
		return; 
	}

	CMiniLexicon* pMini;
	
	pMini = (*(m_lexicon ->m_pMiniLexica))[0];
	
	dataCorpus = pMini ->GetWords(); 

	pHMM = m_lexicon->CreateNewHMM();
	
	
	dataIsRight = pHMM->preprocessData(PHONE_TIER1, (void*)(dataCorpus));  
	
	if ( !dataIsRight)
	{
		delete pHMM;
		QMessageBox::information ( this, "Linguistica : Error", "Data is not right for HMM!" );
		return;
	}

	pHMM->init(NumberOfStates,NumberOfIterations); 
	pHMM->initPiAndAB();
	


	pHMM->trainParameters(); 
	pHMM->logInfo(-1); 

//	delete oneStateHMM;

	// Update tree view
	emit updateAllViewsSignal();

}

void LinguisticaMainWindow::calculateAffixnessSlot()
{
	if( m_logging ) OpenLogFile();
	m_lexicon->CalculateCoefficientsOfAffixness();
	if( m_logging ) CloseLogFile();

	// Unsaved work
	m_projectDirty = true;

	// Update tree view
	emit updateAllViewsSignal();
}


void LinguisticaMainWindow::fromAffixnessUpdateSigsAndCompoundsSlot()
{
	if( m_logging ) OpenLogFile();
	m_lexicon->FromAffixnessUpdateSigsAndCompounds();
	if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

	// Unsaved work
	m_projectDirty = true;

	// Update tree view
	emit updateAllViewsSignal();
}


void LinguisticaMainWindow::viewCorpusSlot()
{
	CorpusViewDialog *corpusViewDlg = new CorpusViewDialog( m_lexicon, this,
							Qt::WStyle_Customize |
							Qt::WStyle_NormalBorder |
							Qt::WStyle_Title |
							Qt::WStyle_SysMenu );
	if( corpusViewDlg->exec() == QDialog::Accepted )
	{
		// Do nothing
	}
	else
	{
		// Do nothing
	}
	delete corpusViewDlg;	
}


void LinguisticaMainWindow::exportProjectSlot()
{
#ifdef _EXPORTWIZARD_ //@@@
	ExportWizard *exportWiz = new ExportWizard( m_lexicon, this, "exportWizard", FALSE );
	if( exportWiz->exec() == QDialog::Accepted )
	{
		// Export

			exportWiz->exportAll();
	}
	else
	{
		// Do nothing
	}
	delete exportWiz;
#endif		
}
