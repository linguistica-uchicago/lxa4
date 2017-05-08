// User interface and driver
// Copyright © 2009 The University of Chicago
#ifndef LINGUISTICAMAINWINDOW_H
#define LINGUISTICAMAINWINDOW_H

// Doxygen comments defining the index page
/**	\mainpage Linguistica
 
	\section intro_sec What is Linguistica?

	Linguistica is a program designed to explore the unsupervised learning of natural language, with primary focus on morphology (word-structure). It runs under Windows, Mac OS X and Linux, and is written in C++ within the Qt development framework. Its demands on memory depend on the size of the corpus analyzed.

	Unsupervised learning refers to the computational task of making inferences (and therefore acquiring knowledge) about the structure that lies behind some set of data, without any direct access to that structure. In the case of unsupervised learning of morphology, Linguistica explores the possibilities of morpheme-combinations for a set of words, based on no internal knowledge of the language from which the words are drawn.

	Segmentation is the first task of this process; the program figures out where the morpheme boundaries are in the words, and then decides what the stems are, what the suffixes are, and so forth. Most of Linguistica's functionality, at this point, goes into making these decisions.

	\section creator Creator
	- John Goldsmith

	\section engineers Engineers

	- Jon Cihlar
	- Yu Hu
	- Jeremy O'Brien
	- Colin Sprague

	\section contributors Contributors

	- Carl Dolnick
	- James Kirby
	- Irina Matveeva
	- Aris Xanthos
 
 */

#include <QMainWindow>
#include "ui_linguisticamainwindowbase.h"

#include <Q3ProgressDialog>
#include <Q3FileDialog>
#include <QInputDialog>
#include <QFontDialog>
#include <Q3ProgressBar>
#include <Q3PopupMenu>
#include <QStatusBar>
#include <Q3TextEdit>
#include <QSplitter>
#include <Q3ToolBar>
#include <QMenuBar>
#include <Q3Canvas>
#include <Q3VBox>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QMoveEvent>
#include <QApplication>
#include <QSettings>
#include <Q3Process>
#include <QLayout>
#include <QAction>
#include <QLabel>
#include <Q3TextStream>
#include <Q3PtrList>
#include <QString>
#include <Qt>
#include "LPreferences.h"
#include "generaldefinitions.h"
#include "AffixLocation.h"

#include <QLabel>

class CStem;
class CLexicon;
class CParse;
class CLPreferences;
class CTreeViewItem;
class CState; 
class CTemplate; 
class CTemplateCollection;
class CTemplateListViewItem;
class CSequencer; 
class CStats;
class CCorpusWord;
class CSignature;
class GUIWordCollection;

enum eDocumentType;

//typedef QMap<QString,QString>			StringToString;
typedef QMap<QString,CTemplate*>		QStringToTemplate;
typedef Q3PtrList<CStem>				CStemList;
typedef QMap<QString,CStemList>			StringToCStemList;
typedef QMap<QString,CStem*>			StringToPtrCStem;
typedef QMap<QString,CStem>			StringToCStem;
typedef QMap<QString,CParse*>			StringToParse;
typedef QMap<QString,CCorpusWord*>		StringToPtrCCorpusWord;
typedef QMap<int,QString>			IntToString;

class LinguisticaMainWindow : public QMainWindow,
					public Ui::LinguisticaMainWindowBase
{
	Q_OBJECT
protected:
	// Application
	QApplication*          m_app;	///< memory belongs to caller
	/// true if running in batch mode
	bool                   m_commandLineFlag;

	// Preferences
	QSettings              m_Settings;
	CLPreferences          m_preferences;

	// Lexicon
	CLexicon*              m_lexicon;

	// GUI
	eDocumentType          m_docType;
	CParse*                m_commandParse;
	int                    m_commandMini;
	CSignature*            m_pSig1;
	CSignature*            m_pSig2;
	GUIWordCollection*     m_GUIWords;

	// Token count
	int                    m_numberOfTokens;

	// Logging variables
	bool                   m_logging;
	QString                m_logFileName;
	QFile*                 m_logFile;
        QTextStream*           m_logFileStream;

	// Status/Progress Bar
	QLabel*               m_statusBar1;	///< deleted by status bar
	QLabel*               m_statusBar2;	///< deleted by status bar
	Q3ProgressBar*        m_progressBar;	///< deleted by status bar
	Q3ProgressDialog*     m_progressDialog;
	QString               m_progressText1,
		    	      m_progressText2;

	// Counter
	bool                  m_counterDisplayFlag;
	int                   m_counter;

	// Project information
	int                  m_projectIndex;
	QString              m_projectDirectory;
	QString              m_projectName;
	bool                 m_projectDirty;

	// File names
	QString              m_corpusFileName;
	QString              m_goldStdFileName;
	QString              m_goldStdOutputFile;

	// Encoding
	QString m_EncodingType;

	// Fonts
	// Collection view and command line can have different
	// font, they are on the east side of the screen
	QFont                m_eastFont;  // Collection view and command line font, east side of screen


	//========== FSA
	CState*              m_CommonState;

	//========= SED
	CTemplate*           m_CommonTemplate;
	CTemplateCollection* m_Words_InitialTemplates;
	CTemplateCollection* m_Words_Templates;

	//========= Sequencer
	CSequencer*          m_Sequencer; 

	//========= Statistics
	CStats*              m_Stats;


public:
  LinguisticaMainWindow( const int argc, char** argv, QApplication* app = 0,
                  QWidget* parent = 0, Qt::WindowFlags f = Qt::WType_TopLevel );
  ~LinguisticaMainWindow();

	// disable copy
private:
	LinguisticaMainWindow(const LinguisticaMainWindow& x);
	LinguisticaMainWindow& operator=(const LinguisticaMainWindow& x);
public:

  void                       SetNumberOfTokens( int i ) { m_numberOfTokens = i; }
  int                        GetNumberOfTokens() { return m_numberOfTokens; }

  void                       SetUpNewLexicon	();

  void                       setProjectDirectory( QString dir ) { m_projectDirectory = dir; }
  bool					getProjectDirty	() { return m_projectDirty; }

  QString				getStatusBar1	() { return m_statusBar1->text(); }
  QString				getStatusBar2	() { return m_statusBar2->text(); }

  Q3ProgressBar*                         getProgressBar	() { return m_progressBar; }

  void					setStatusBar1	(QString);
  void					setStatusBar2	(QString);

  void					BeginCountDown	();
  void					EndCountDown	();
  void					CountDownOnStatusBar(int i, int total, int step = 100);

  QString				GetLogFileName	() { return m_logFileName; }
  void					AskUserForLogFileName();

  void					SetEastFont		( QFont font ) { m_eastFont = font; }
  CLPreferences*                        GetPreferences	() { return &m_preferences; }
  QSettings*                            GetSettings		() { return &m_Settings; }

  void					SetDocType		( eDocumentType dt ) { m_docType = dt; }
  eDocumentType                         GetDocType		() { return m_docType; }

  bool                                  autoLayering	() { return m_autoLayeringAction->isOn(); }
	
  bool					isCorrectAffix	( eAffixLocation );

	void executeCommandLineArgs(int words_count, bool auto_layer,
		bool prefix, bool suffix);
	/// true if running in batch mode
	bool commandLineMode() { return m_commandLineFlag; }

  QFont					GetEastFont		() { return m_eastFont; }

	// Logging
  void					CloseLogFile	();
  void					OpenLogFile		();
  bool					LogFileOn		() { return m_logging; }
  QTextStream*                          GetLogFileStream() { return m_logFileStream; }
  

  	QLabel * pImgLabel;

	CLexicon*	GetLexicon(void) { return m_lexicon; }
private:
   
  
  Q3ListViewItem*        GetMiniLexiconSubTree( Q3ListViewItem*, int );
  void					GetMorphPrecisionRecallByWord( StringToCStemList&,
													   StringToParse&,
													   double&,
													   double&,
													   double&,
													   double& );

  void					GetCutPrecisionRecall( StringToCStemList&,
											   StringToParse&,
											   double&,
											   double&,
											   double&,
											   double& );

  void					GetMorphPrecisionRecall( StringToCStemList&,
												 StringToParse&,
												 double&,
												 double&,
												 double&,
												 double& );
private:
	QFont GetFontPreference(QString key) const
	{ return m_preferences.GetFontPreference(key); }
	void SetFontPreference(QString key, QFont font)
	{ m_preferences.SetFontPreference(key, font); }
	QString GetPreference(QString key) const
	{ return m_preferences.GetPreference(key); }
	void GetStringListPreference(QString key, QStringList* out) const
	{ m_preferences.GetStringListPreference(key, out); }

signals:
  void corpusOKSignal(bool);
  void updateAllViewsSignal();
  void updateTreeViewSignal();
  void updateCommandLineSignal();
  void tokensRequestedSignal();  // for changing the number of words requested
  void commandLineClose();

public slots:

  // Slots derived from LinguisticaMainWindowBase
  void openFileActionSlot();
  void runAllSuffixActionSlot();
  void enableLoggingActionSlot( bool );
  void clearLogFileActionSlot();
  void newLogFileActionSlot();
  /// Refresh collection view, for example for a switch in m_docType.
  void updateCollectionViewSlot();
  void updateCollectionViewSlot( Q3ListViewItem* );
  void updateCommandLineSlot( Q3ListViewItem* );
  void changeFontSlot();
  void preferencesEditSlot();
  void saveFileActionSlot();
  void newFileActionSlot();
  void saveAsFileActionSlot();
  void findAllomorphySlot();
  void showDeleteesSlot( bool );
  void rereadCorpusSlot();
  void clearLexiconSlot();
  void predecessorFreqSlot();
  void successorFreqSlot();
  void checkPfxSignaturesSlot();
  void checkSignaturesSlot();
  void knownStemsPrefixesSlot();
  void knownStemsSuffixesSlot();
  void fromPfxSigsFindStemsSlot();
  void fromSigsFindStemsSlot();
  void findPfxSingletonSigsSlot();
  void findSingletonSigsSlot();
  void pfxLooseFitSlot();
  void looseFitSlot();
  void showToolbarsSlot( bool );
  void showStatusBarSlot( bool );
  void saveBrokenCorpusSlot();
  void helpAboutSlot();
  void newMiniLexiconActionSlot();
  void deleteMiniLexiconActionSlot();
  void autoLayeringActionSlot();
  void populateWordsActionSlot();
  void addToBorrowedSigsSlot();
  void compareGoldStdSlot();
  void changeGoldStdFileSlot();
  void runAllPrefixActionSlot();
  void commandLineCloseSlot();
  void viewCorpusSlot();
  void exportProjectSlot();
  void addContentToCommandLine(QString); 
  void setCommandLineTabStopWidth(int length){m_commandLine->setTabStopWidth(length);};  
  int  getCommandLinePointSize(){ return m_commandLine ->pointSize();};
  void setCommandLineStyle( QString );

  // Compounds
  void fromStemsFindCompoundsSlot();
  void fromStemsFindFlatCompoundsSlot();
  void calculateAffixnessSlot();
  void fromAffixnessUpdateSigsAndCompoundsSlot();
  void compareCompoundsSlot();

  // Phonology
  virtual void GenericPhonologySlot();
  virtual void CreateSkeletonSlot();
  virtual void fromStemsFindAffixesSlot();
  virtual void DropTierLeaveSlot();
  virtual void DropTierLeaveCopy();
  virtual void PhonologyCalculateInformation();
  virtual void PhonologyComputeGibbsFunction();

  void updateSmallGraphicDisplaySlot(); //needed for compound displays
// --- new fsa code
  void fsaTestFuncAction(); 

  // Phonogy graphic display
  void updateSmallGraphicDisplaySlotForPhonogy(CStem*); 


  // Sequencer
  void sequencerReadCorpusSlot();
  void sequenceASentenceSlot();
  void sequencerTestAFileSlot();

  //========  MT 
  void mTModel1Slot();

   // ========= HMM
  void testSEMHMMSlot();
  void DisplayVideoHMM();
  
  // ========= Graphic display of Multidimension data
  void testMultiDimensionDisplaySlot();
  void updateSmallGraphicDisplaySlotForMultiDimensionData(int, int, double**, IntToString); 

	// ======  Goldwater Method
  void goldwaterMethodSlot();

  void testSignatureDisplaySlot(); //jg july 2006

  // Statistics
  void statsReadCorpusSlot();

  // DCN
  void DCNstressSlot();
  void DCNsylSlot();

  void DCNstressComputeSlot();
  void DCNstressLearnSlot();

  void DCNsylFindTrainSlot();
  void DCNsylFindTestSlot();
  void DCNsylTrainSlot();

  // StringEditDistance
  void RunSedSlot(); 
  void FindSlicesSlot(); 
  void FindAllEditDistances(CTemplateCollection*);
  void CheckForConflations(CTemplateCollection* , CTemplateCollection* );
  void FindAllWordNeighbors(CLexicon*);

  // Goldstandard
//  void GetPrecisionRecall(StringToPtrCStem&, StringToParse&, double& , double& , double& , double& );

  // Machine Translation
  void editCorpusForMT();

  // Other slots
  void jgWebLinksActionSlot();
  void lxaWebLinksActionSlot();
  void updateTreeViewSlot();
  void updateCommandLineSlot();
  void tokensRequestedDialogSlot();
  void setProjectDirtySlot( bool b ) { m_projectDirty = b; }

  void suffixesCollapse_two_signaturesAction_activated();
  void updateSignatureGraphicDisplaySlot();


  //	User interface items
  void	toggleMultipleSelectionSlot();


protected:
  virtual void closeEvent( QCloseEvent * );
  virtual void resizeEvent( QResizeEvent * );
  virtual void moveEvent( QMoveEvent * );

public:
	bool	getLogging(){ return m_logging; }
};

#endif // LINGUISTICAMAINWINDOW_H
