// Implementation of most LinguisticaMainWindow methods
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include "Config.h"
#include "Version.h"
#include <memory>
#include <limits>
#include <cstdio>
#include <QDesktopWidget>
#include <QMessageBox>
#include <Q3PopupMenu>
#include <Q3ListView>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QMoveEvent>
#include <QLabel>
#include <Q3TextStream>
#include <Q3ValueList>
#include "listbuilderdialog.h"
#include "helpaboutdialog.h"
#include "verifydialog.h"
#include "LPreferences.h"
#include "GUIclasses.h"
#include "Sequencer.h"
#include "DLHistory.h"
#include "Stats.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "SignatureCollection.h"
#include "TemplateCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "StemCollection.h"
#include "WordCollection.h"
#include "CommandLine.h"
#include "Slice.h"
//#include <QTime>

namespace {
	// command-line argument parsing helper
	struct command_line_args {
		QString corpus, logFile, goldStdFile, outputDir, error;
		bool mini;
		bool prefix;
		bool suffix;
		bool verbose;
		int count;

		command_line_args() : mini(false),
			prefix(false), suffix(false),
			verbose(false), count(0) { }
		/// result is false for --help and errors
		bool process(int argc, char** argv)
		{
			return processCommandLineArgs(argc, argv,
					corpus, count, logFile, goldStdFile,
					outputDir, mini, prefix, suffix,
					verbose, error) >= 0;
		}
	};
}

LinguisticaMainWindow::LinguisticaMainWindow( const int argc, char** argv,
			QApplication* app, QWidget* parent, Qt::WindowFlags f )
	: QMainWindow(parent, f), Ui::LinguisticaMainWindowBase(),
	// Application
	m_app(app),
	m_commandLineFlag(argc > 1),
	// Preferences
	// XXX. set organization string "UChicago", application "Linguistica"
	m_Settings(),
	m_preferences(&m_Settings),
	// Lexicon
	m_lexicon(new CLexicon(this)),
	// GUI
	m_docType(NO_DOC),
	m_commandParse(),
	m_commandMini(-1),
	m_pSig1(), m_pSig2(),
	m_GUIWords(),
	// Token count
	m_numberOfTokens(0),
	// Log file.
	m_logging(false),
	m_logFileName(m_Settings.value(
		"/linguistica.uchicago.edu/Linguistica/MainWindow/LogFile/FileName",
		QString("C:\\.txt")).value<QString>()),
	m_logFile(),
	m_logFileStream(),
	// Status/Progress bar
	m_statusBar1(new QLabel(this)),	// width set, put in status bar below
	m_statusBar2(new QLabel(this)),	// width set, put in status bar below
	m_progressBar(new Q3ProgressBar()),	// width set, put in status bar below
	m_progressDialog(),
	m_progressText1(), m_progressText2(),
	// Counter
	m_counterDisplayFlag(false),
	m_counter(0),
	// Project settings
	m_projectIndex(0),
	m_projectDirectory(m_Settings.value(
		"/linguistica.uchicago.edu/Linguistica/Project/Directory",
		QString()).value<QString>()),
	m_projectName(),
	m_projectDirty(false),	// No changes yet
	// Filenames
	m_corpusFileName(m_Settings.value(
		"/linguistica.uchicago.edu/Linguistica/MainWindow/FileMenu/Open",
		QString()).value<QString>()),
	m_goldStdFileName(m_Settings.value(
		"/linguistica.uchicago.edu/Linguistica/MainWindow/DiagnosticsMenu/NewGoldStdFile",
		QString()).value<QString>()),
	m_goldStdOutputFile(),
	// Encoding
	m_EncodingType(m_Settings.value(
		"/linguistica.uchicago.edu/Linguistica/MainWindow/Encoding/EncodingType",
		QString()).value<QString>()),
	// Fonts
	m_eastFont(m_preferences.GetFontPreference("Main")),
	// FSA
	m_CommonState(),
	// String edit distance
	m_CommonTemplate(),
	m_Words_InitialTemplates(), m_Words_Templates(),
	m_Sequencer(new CSequencer(this)),
    m_Stats(new CStats(this))
{
	using std::auto_ptr;
	using std::printf;

	command_line_args args;
	if (m_commandLineFlag && !args.process(argc, argv)) {
		printf("%s", args.error.ascii());
		DisplayHelp();
		return;
	}

	setupUi(this);
	setCaption("Linguistica " + QString(LXA_VERSION));

	// Set up the status bars
	m_statusBar1->setMaximumWidth(250);
	m_progressBar->setMaximumWidth(250);
	m_statusBar2->setMaximumWidth(250);
	statusBar()->addPermanentWidget(m_statusBar1, 33);
	statusBar()->addPermanentWidget(m_progressBar, 33);
	statusBar()->addPermanentWidget(m_statusBar2, 33);

	m_commandLine->setWordWrap( Q3TextEdit::NoWrap );

	// Toolbars and Status Bar visible
	viewToolbarsAction->setOn(true);
	viewStatusBarAction->setOn(true);

	// Set up Help menu
	auto_ptr<Q3PopupMenu> help(new Q3PopupMenu(this));
	// Web links in windows version only
	auto_ptr<Q3PopupMenu> links(new Q3PopupMenu(this));
	links->insertItem( "&John Goldsmith", this, SLOT(jgWebLinksActionSlot()) );
	links->insertItem( "&Linguistica", this, SLOT(lxaWebLinksActionSlot()) );
	help->insertItem( "&Web Links", links.release() );
	help->insertSeparator();
	help->insertItem( "&About", this, SLOT( helpAboutSlot() ) );
	menuBar()->insertItem( "&Help", help.release() );

	// Graphic view.

	// memory owned by m_SmallGraphicDisplayTab

	// added ... 
	this->pImgLabel = new QLabel;
	this->pImgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->pImgLabel->setAlignment(Qt::AlignCenter);
	this->pImgLabel->setMinimumSize(240, 160);
	

	// Get all user settings and preferences
	{
		m_Settings.beginGroup("/linguistica.uchicago.edu/Linguistica");

		setMinimumSize(800, 600);
		{
			m_Settings.beginGroup("Geometry");
			if (m_Settings.contains("Width") &&
					m_Settings.contains("Height") &&
					m_Settings.contains("X_Pos") &&
					m_Settings.contains("Y_Pos")) {
				QSize sz(m_Settings.value("Width").value<int>(),
					m_Settings.value("Height").value<int>());
				QPoint loc(m_Settings.value("X_Pos").value<int>(),
					m_Settings.value("Y_Pos").value<int>());

				resize(sz);
				move(loc);
			} else {
				resize(sizeHint());
			}
			m_Settings.endGroup();
		}

		// Hack: ensure that if the window closed maximized, the next
		// time it opens it will be maximized again and when
		// un-maximized it will return to the last remembered
		// un-maximized size and position.

		// If the remembered position was large, the window
		// probably closed maximized.
		const bool maximized = QApplication::desktop()->width() < width()+10 ||
			QApplication::desktop()->height() < height()+30;
		if (maximized) {
			{
				m_Settings.beginGroup("Geometry");
				if (m_Settings.contains("Width_Old") &&
							m_Settings.contains("Height_Old") &&
							m_Settings.contains("X_Pos_Old") &&
							m_Settings.contains("Y_Pos_Old")) {
					QSize sz(m_Settings.value("Width_Old").value<int>(),
						m_Settings.value("Height_Old").value<int>());
					QPoint loc(m_Settings.value("X_Pos_Old").value<int>(),
						m_Settings.value("Y_Pos_Old").value<int>());

					resize(sz);
					move(loc);
				}
				m_Settings.endGroup();
			}
			showMaximized();
		}

		// Number of tokens
		m_numberOfTokens = m_Settings.value(
					"Lexicon/NumberOfTokens", 10000)
					.value<int>();

		// Set the triscreen dimensions
		{
			m_Settings.beginGroup("Triscreen");

			if (m_Settings.contains("West") &&
					m_Settings.contains("East") &&
					m_Settings.contains("North") &&
					m_Settings.contains("South")) {
				QList<int> eastWest, northSouth;

				// default: 300
				eastWest.append(m_Settings.value("West").value<int>());
				// default: 500
				eastWest.append(m_Settings.value("East").value<int>());

				// default: 400
				northSouth.append(m_Settings.value("North").value<int>());
				// default: 200
				northSouth.append(m_Settings.value("South").value<int>());

				m_eastWestSplitter->setSizes(eastWest);
				m_northSouthSplitter->setSizes(northSouth);
			}

			m_Settings.endGroup();
		}
		m_Settings.endGroup();
	}

	{
		// Connect signals and slots
		connect(this, SIGNAL(updateAllViewsSignal()),
			this, SLOT(updateTreeViewSlot()));
		connect(this, SIGNAL(updateAllViewsSignal()),
			this, SLOT(updateCollectionViewSlot()));
		connect(this, SIGNAL(updateAllViewsSignal()),
			this, SLOT(updateCommandLineSlot()));
		connect(this, SIGNAL(updateCommandLineSignal()),
			this, SLOT(updateCommandLineSlot()));
		connect(this, SIGNAL(updateTreeViewSignal()),
			this, SLOT(updateTreeViewSlot()));
		connect(this, SIGNAL(tokensRequestedSignal()),
			this, SLOT(tokensRequestedDialogSlot()));
	}

	// Draw tree view
	m_treeView->setSortColumn(-1);
	emit updateAllViewsSignal();

	// Prepare collection view
	m_collectionView->setShowSortIndicator(true);

	// Command line execution
	if (!args.corpus.isEmpty()) {
		m_corpusFileName = args.corpus;

		if (!args.logFile.isEmpty()) {
			m_logging = true;
			m_logFileName = args.logFile;
		}

		if (!args.goldStdFile.isEmpty())
			m_goldStdFileName = args.goldStdFile;

		if (!args.outputDir.isEmpty())
			m_projectDirectory = args.outputDir;

		executeCommandLineArgs(args.count, args.mini,
					args.prefix, args.suffix);
		return;
	}
}

LinguisticaMainWindow::~LinguisticaMainWindow()
{
	delete m_lexicon;
	delete m_pSig1;		// never used
	delete m_pSig2;		// never used
	delete m_GUIWords;	// never used
	// close log file (flushes buffers)
	delete m_logFile;
	delete m_logFileStream;
	delete m_progressDialog;
	delete m_Words_InitialTemplates;
	delete m_Words_Templates;
	delete m_Sequencer;
	delete m_Stats;
}

void LinguisticaMainWindow::enableLoggingActionSlot(bool b)
{
  m_logging = b;
  emit updateAllViewsSignal();
}


void LinguisticaMainWindow::clearLogFileActionSlot()
{
	if( m_logFileStream )
	{
		// Log file open, can't clear now.
		// TODO: message to screen.
		return;
	}

	// Delete the file and create a new, empty one with
	// the same name.
	Q_ASSERT(!GetLogFileName().isEmpty());
	m_logFile = new QFile( GetLogFileName() );
	m_logFile->remove();
	m_logFile = NULL;

	OpenLogFile();
	*m_logFileStream << "";
	CloseLogFile();

	emit updateAllViewsSignal();
}


void LinguisticaMainWindow::CloseLogFile()
{
	if ( !m_logFileStream )
	{
        *GetLogFileStream() << "</body></html>";
		Q_ASSERT ( !m_logging );
		//  AfxMessageBox ("Log file is not open.");  // TODO: Qt
		return;
	}

	Q_ASSERT ( m_logging );

	m_logFile->close();
	m_logFile = NULL;
	m_logFileStream = NULL;
	m_logging = FALSE;
}


void LinguisticaMainWindow::OpenLogFile()
{
	if( m_logFileStream )
	{
		Q_ASSERT ( m_logging );
		//  AfxMessageBox ("Log file is already open.");  // TODO: Qt
		return;
	}

	if( GetLogFileName().lower() == "c:\\.txt" || GetLogFileName().lower() == "none" )
	{
		AskUserForLogFileName();
	}

	m_logFile = new QFile( GetLogFileName() );

	if ( m_logFile->open( QIODevice::WriteOnly ) )
	{
                m_logFileStream = new QTextStream( m_logFile );
                m_logFileStream->setEncoding( QTextStream::Unicode );
		m_logging = TRUE;
        *m_logFileStream << "<html><head> <meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\"/> <link rel=\"stylesheet\" type=\"text/css\" href=\"template_files/lxa.css\"/> <script charset=\"utf-8\" id=\"injection_graph_func\" src=\"template_files/injection_graph_func.js\"></script>";
        *m_logFileStream << " <style type=\"text/css\">" ;
        *m_logFileStream << " h1 { font-size: 250%; color: white; background-color: #1A4969; text-align: center;; font-family: Georgia, \"Times New Roman\", Times, serif }";
        *m_logFileStream << " h2 { text-align: center; color: #0000FF; background-color:  #E3DDAF ; font-size: 150%; margin-left:25%; margin-right:25%;	}";
        *m_logFileStream << " h3 { text-align: center; font-size: 120%; font-weight: bold; color: black; background-color: #21AD94 	; %border-top: thin solid #000000; border-bottom: thin solid #000000; margin-left: 0%; margin-right: 40%;       padding: 0.3em;   border-right: 1em solid black }" ;
        *m_logFileStream << " h4 { text-align: center; font-size: 120%; color: #000000; background-color: #21AD94  ; padding: 5px; height: auto; border-left: 1em solid black; %border: thin solid #FF0000; %margin-top: 5px; %margin-bottom: 5px; margin-left: 40%; }" ;
        *m_logFileStream << " h5 { color: #FF0000; background-color: #EEEEEE; font-size: 80%; text-align: center; }" ;
        *m_logFileStream << " table  { 	border-width: 4px 4px 4px 4px; 	border-spacing: 2px; 	border-style: outset outset outset outset; 	border-color: #1A4969 #1A4969 #1A4969 #1A4969; 	border-collapse: separate; 	background-color: rgb(255, 255, 255); margin-left: auto; margin-right: auto; margin-top: 2em; }";
        *m_logFileStream << "table  th { border-width: 1px 1px 1px 1px; 	padding: 2px 2px 2px 2px; 	border-style: solid solid solid solid; 	border-color: gray gray gray gray; 	background-color: white; 	-moz-border-radius: 3px 3px 3px 3px; }" ;
        *m_logFileStream << " h4 { table  td { 	border-width: 1px 1px 1px 1px; 	padding: 2px 2px 2px 2px; 	border-style: solid solid solid solid; 	border-color: gray gray gray gray; 	background-color: white; 	-moz-border-radius: 3px 3px 3px 3px; }" ;
        *m_logFileStream << "</style></head><body>";
	    
    
    
    }

	return;
}


void LinguisticaMainWindow::newLogFileActionSlot()
{
  AskUserForLogFileName();
  emit updateAllViewsSignal();
}


void LinguisticaMainWindow::runAllSuffixActionSlot()
{
  if( m_lexicon->GetMiniCount() )
  {
    // Run all suffix functions, log if desired
    if( m_logging ) OpenLogFile();
    m_lexicon->FindSuffixes();
    if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

  
    // Enable allomorphy
  //  findAllomorphyAction->setEnabled(true);

    // Unsaved work
    m_projectDirty = true;

    // Update tree view
    emit updateAllViewsSignal();
  }
}


void LinguisticaMainWindow::runAllPrefixActionSlot()
{
  if( m_lexicon->GetMiniCount() )
  {
    // Run all prefix functions, log if desired
    if( m_logging ) OpenLogFile();
    m_lexicon->FindPrefixes();
    if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

    // Unsaved work
    m_projectDirty = true;

    // Update tree view
    emit updateAllViewsSignal();
  }
}


void LinguisticaMainWindow::AskUserForLogFileName()
{
  bool ok;

  QString lastfile = m_Settings.readEntry( "/linguistica.uchicago.edu/Linguistica/MainWindow/LogFile/FileName", QString::null, &ok );
  m_logFileName = Q3FileDialog::getSaveFileName( lastfile,
                                                "Text Files( *.txt );;Rich Text Files( *.rtf );;All Files( *.* )",
                                                this,
                                                "Open Log File" );
  if( !m_logFileName.isEmpty() && lastfile != m_logFileName )
    m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/MainWindow/LogFile/FileName", m_logFileName );
}


// Change font in collection view and command line only
void LinguisticaMainWindow::changeFontSlot()
{
  bool ok;
  QFont font = QFontDialog::getFont( &ok, m_eastFont, this );
  if ( ok )
  {
        // Apply this font to the collection view and
    // command line frames
    m_eastFont = font;
    font = GetFontPreference( "Affix" );
    font.setFamily( m_eastFont.family() );
    font.setPointSize( m_eastFont.pointSize() );
    SetFontPreference( "Affix", font );

    font = GetFontPreference( "Signature" );
    font.setFamily( m_eastFont.family() );
    font.setPointSize( m_eastFont.pointSize() );
    SetFontPreference( "Signature", font );

    font = GetFontPreference( "Stem" );
    font.setFamily( m_eastFont.family() );
    font.setPointSize( m_eastFont.pointSize() );
    SetFontPreference( "Stem", font );

    font = GetFontPreference( "Word" );
    font.setFamily( m_eastFont.family() );
    font.setPointSize( m_eastFont.pointSize() );
    SetFontPreference( "Word", font );

    emit updateAllViewsSignal();
  }
  else
  {
    // the user canceled the dialog; font is set
    // to the application's default font
  }
}

// Called before closing the main window
void LinguisticaMainWindow::closeEvent(QCloseEvent* close)
{
	if (m_commandLineFlag) {
		close->accept();
		return;
	}

	bool verify;

	// Record triscreen position before closing
	Q3ValueList<int> eastWest = m_eastWestSplitter->sizes(),
		northSouth = m_northSouthSplitter->sizes();

	m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Triscreen/West", eastWest.first() );
	m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Triscreen/East", eastWest.last() );
	m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Triscreen/North", northSouth.first() );
	m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Triscreen/South", northSouth.last() );

	// Verify information saved
	QString notifications = GetPreference( "Notifications" );
	if( notifications.length() ) verify = GetPreference( "Notifications" ).toInt();
	else verify = false;

	if ( verify && m_projectDirty ) {
		QString message = "Would you like to save your changes before closing?";
		VerifyDialog *saveCheckDlg = new VerifyDialog(message);
		saveCheckDlg->setCaption( saveCheckDlg->caption() + "Save Project?" );

		switch( saveCheckDlg->exec() )
		{
		case RESULT_YES:
			// User clicked 'Yes', save changes and close
			saveFileActionSlot();
			if ( m_projectDirty ) close->ignore();
			else close->accept();
			return;
		case RESULT_NO:
			// User clicked 'No', close without saving
			close->accept();
			return;
		case RESULT_CANCEL:
		default:
			// User clicked 'Cancel', do not close
			close->ignore();
			return;
		}
	}

	// allow the window to close
	close->accept();
}


// Called whenever the window is resized, includes maximizing,
// normalizing, opening and closing the window
void LinguisticaMainWindow::resizeEvent( QResizeEvent *resize )
{
  m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/Width", resize->size().width() );
  m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/Height", resize->size().height() );

  // If old size and new size are different, update old size
  if( resize->size().width() != resize->oldSize().width() )
    m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/Width_Old", resize->oldSize().width() );
  if( resize->size().width() != resize->oldSize().width() )
    m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/Height_Old", resize->oldSize().height() );
}


// Called whenever the window is moved, includes maximizing,
// normalizing, opening and closing the window
void LinguisticaMainWindow::moveEvent( QMoveEvent *move )
{
  int x, y;
  int x_max = QApplication::desktop()->width() - ( width() + 10 );
  int y_max = QApplication::desktop()->height() - ( height() + 30 );
  x = move->pos().x();
  if( x < 10 ) x = 10;
  if( x > x_max ) x = x_max;
  y = move->pos().y();
  if( y < 30 ) y = 30;
  if( y > y_max ) y = y_max;

  m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/X_Pos", x );
  m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/Y_Pos", y );

  // If old position and new position are different, update old position.
  if( move->pos().x() != move->oldPos().x() || move->pos().y() != move->oldPos().y() )
  {
    x = move->oldPos().x();
    if( x < 10 ) x = 10;
    if( x > x_max ) x = x_max;
    y = move->oldPos().y();
    if( y < 30 ) y = 30;
    if( y > y_max ) y = y_max;

    m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/X_Pos_Old", x );
    m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Geometry/Y_Pos_Old", y );
  }
}

void LinguisticaMainWindow::tokensRequestedDialogSlot()
{
	bool ok;
	int amount = QInputDialog::getInteger(this, "Linguistica",
		"Number of tokens requested:", m_numberOfTokens,
		0, std::numeric_limits<int>::max(), 1, &ok);

	if (!ok || amount == 0)
		// user cancelled
		return;

	// user entered something and pressed OK
	m_numberOfTokens = amount;
	m_Settings.writeEntry("/linguistica.uchicago.edu/Linguistica/"
		"Lexicon/NumberOfTokens", amount);

	m_collectionView->clear();
	m_docType = NO_DOC;
	emit updateTreeViewSignal();
}

void LinguisticaMainWindow::setStatusBar1(QString string)
{
	if( m_progressText1 == string ) return;
		
	m_progressText1 = string;

	/*if( m_app )
	{
		if( m_progressDialog ) m_progressDialog->setLabelText( m_progressText1 + "\n" + m_progressText2 );
		
		m_app->processEvents();
	}
	else
	{*/
		m_statusBar1->setText(string);
		m_statusBar1->repaint();
//	}
}


void LinguisticaMainWindow::setStatusBar2(QString string)
{
	if( m_progressText2 == string ) return;
		
	m_progressText2 = string;

/*	if( m_app )
	{
		if( m_progressDialog ) m_progressDialog->setLabelText( m_progressText1 + "\n" + m_progressText2 );
		
		m_app->processEvents();
	}
	else
	{*/
		m_statusBar2->setText(string);
		m_statusBar2->repaint();
//	}
}


void LinguisticaMainWindow::BeginCountDown()
{
/*	QString text = m_progressText1 + "\n" + m_progressText2;

	if( m_app )
	{
		if( m_progressDialog ) EndCountDown();
			
		m_progressDialog = new QProgressDialog( text, QString::null, 0, this, "progressDialog", TRUE );
		m_progressDialog->setMinimumDuration( 1000 );
		m_app->processEvents();
	}
	else*/ m_progressBar->reset();
}


void LinguisticaMainWindow::EndCountDown()
{
/*	if( m_app )
	{
		m_app->processEvents();

		if( m_progressDialog )
		{
			m_progressDialog->close();
			delete m_progressDialog;
			m_progressDialog = NULL;
		}
	}
	else*/ m_progressBar->reset();

	m_progressText1 = "";
	m_progressText2 = "";
}


void LinguisticaMainWindow::CountDownOnStatusBar( int i, int total, int stepsize )
{
	if( !stepsize ) stepsize = total/100;
	if( stepsize < 1 ) stepsize = 1;

/*	if( m_app )
	{
		if( !m_progressDialog ) BeginCountDown();

		if( i < 0  || i > total ) EndCountDown();
		else
		{
			// Update on multiples of stepsize
			if( i % stepsize == 0 )
			{
				m_progressDialog->setProgress( i, total );
				m_app->processEvents();
			}
		}
	}
	else
	{*/
		if( i < 0  || i > total )    // Reset if less than 0 or greater than total
		{
			m_progressBar->reset();
		}
		else
		{
			// Update on multiples of stepsize
			if( i % stepsize == 0 )
			{
				m_progressBar->setProgress( i, total );
			}
		}
//	}
}


void LinguisticaMainWindow::newFileActionSlot()
{
  bool ok;
  int result;

  // Verify information saved before overwrite
  bool notifications = GetPreference( "Notifications" ).toInt();
  if( notifications && m_projectDirty )
  {
    QString message = "This action will overwrite your data.  Would you like to\nsave your changes first?";
    VerifyDialog *saveCheckDlg = new VerifyDialog(message);
    saveCheckDlg->setCaption( saveCheckDlg->caption() + "Save Project?" );

    switch( saveCheckDlg->exec() )
    {
    case RESULT_YES:
      // User clicked 'Yes', save changes and continue
      saveFileActionSlot();
      if( m_projectDirty ) return;
      break;
    case RESULT_NO:
      // User clicked 'No', continue
      break;
    case RESULT_CANCEL:
    default:
      // User clicked 'Cancel', just return
      return;
    }
  }


  // Dialog for lexicon file
  QString lastfile = m_Settings.readEntry( "/linguistica.uchicago.edu/Linguistica/MainWindow/FileMenu/Open", QString::null, &ok );
  QString filename = Q3FileDialog::getOpenFileName( lastfile, "Text Files( *.txt );;Rich Text Files( *.rtf );;All Files( *.* )" );
  if( !filename.isEmpty() ){
    if( lastfile != filename ) m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/MainWindow/FileMenu/Open", filename );

    m_corpusFileName = filename;

    // Read the lexicon and activate other functions
    // if successful.  Log if desired.
    m_lexicon->ClearAll();
    if( m_logging ) OpenLogFile();
    result = m_lexicon->ReadCorpus( filename, GetNumberOfTokens() );
    if( m_logging ) CloseLogFile();
    if( result != -1 )
    {
//      runAllAction->setEnabled(true);
      rereadCorpusAction->setEnabled( true );
    }
    else
    {
//      if( runAllAction->isEnabled() ) runAllAction->setEnabled(false);
      if( rereadCorpusAction->isEnabled() ) rereadCorpusAction->setEnabled(false);
    }

	// Update corpus words
	m_lexicon->DoWordUpdates();

    // Project unsaved
    m_projectDirty = true;
  }

  // Set the filter for graphic display and anything else if necessary

  // Clear the collection view
  m_collectionView->clear();
  m_docType = NO_DOC;

  // Update tree view
  emit updateAllViewsSignal();
}


void LinguisticaMainWindow::SetUpNewLexicon()
{
//  int count = m_lexicon->GetNumberOfWords();
  delete m_lexicon;
  m_lexicon = new CLexicon(this);
//  m_lexicon->SetNumberOfWords( count );

  QStringList items;
  GetStringListPreference( "Character_Combinations", &items );
  m_lexicon->SetFilters( &items );
}


void LinguisticaMainWindow::openFileActionSlot()
{
	QString	Directory,
			ProjectName,
			ProjectFileName,
			FileName,
			CorpusFileName;
	int		SlashLoc, DotLoc, i, j;

	CMiniLexicon* mini;

	SetUpNewLexicon();

	CorpusFileName = Q3FileDialog::getOpenFileName( m_projectDirectory,
												   "Project files (*.prj);;All files (*.*)",
												   this,
												   "open file dialog",
												   "Choose a project to open" );

	if( CorpusFileName != QString::null )
	{	
		SlashLoc = CorpusFileName.findRev ('\\');
		if( SlashLoc < 0 ) SlashLoc = CorpusFileName.findRev('/');
		Directory = CorpusFileName.left( SlashLoc + 1 );

		setProjectDirectory( Directory );

		FileName = CorpusFileName.mid (SlashLoc+1);
		DotLoc = FileName.findRev ('.');
		if( DotLoc < 0 ) return;

		ProjectName = FileName.left(DotLoc);
		ProjectFileName = Directory + ProjectName + ".prj";

		int miniCount = m_lexicon->ReadProjectFile( ProjectFileName );

		for( i=0; i < miniCount; i++ )
		{
			j = m_lexicon->NewMiniLexicon();
			Q_ASSERT( j == i );
			mini = m_lexicon->GetMiniLexicon(i);

			QString Prefix					= Directory + ProjectName + "_";
			QString SuffixFileName			= Prefix + QString("Mini%1_").arg(i+1) + "Suffixes.txt";
			QString PrefixFileName			= Prefix + QString("Mini%1_").arg(i+1) + "Prefixes.txt";
			QString SignatureFileName		= Prefix + QString("Mini%1_").arg(i+1) + "Signatures.txt";
			QString StemFileName			= Prefix + QString("Mini%1_").arg(i+1) + "Stems.txt";
			QString WordFileName			= Prefix + QString("Mini%1_").arg(i+1) + "Words.txt";

			setStatusBar1( "Reading suffixes..." );
			mini->GetSuffixes()->ReadSuffixFile( SuffixFileName );// must precede signatures Oct 20 1999 jg
			
			if( mini && mini->GetSuffixes()->GetCount() == 0 )
			{
				mini->SetAffixLocation( STEM_INITIAL );
				setStatusBar1( "Reading prefixes..." );
				mini->GetPrefixes()->ReadPrefixFile( PrefixFileName );// must precede signatures Oct 20 1999 jg
			}
			
			setStatusBar1( "Reading signatures..." );
			mini->GetSignatures()->ReadSignatureFile( SignatureFileName, mini->GetAffixLocation() );  // must follow suffixes
			
			setStatusBar1( "Reading stems..." );
			mini->GetStems()->ReadStemFile( StemFileName, mini->GetAffixLocation() ); //stems must follow signatures Oct 24 1999 jg, but also must precede signatures for signatures to get their stem lists...too bad.
			
			setStatusBar1 ( "Reading signatures (verbose)..." );
			mini->GetSignatures()->ReadSignatureFileBis(SignatureFileName);

			setStatusBar1 ( "Reading words..." );
			mini->GetWords()->ReadWordFile( WordFileName );
		}

		// TODO: read corpus words

		setStatusBar1 ( "" );
				
		emit updateAllViewsSignal();
	}
}


void LinguisticaMainWindow::saveAsFileActionSlot()
{

  int    SlashLoc;
  int    NameLoc;

  // Notify about large number of files
  bool notify;
  QString notifications = GetPreference( "Notifications" );
  if( notifications.length() ) notify = GetPreference( "Notifications" ).toInt();
  else notify = true;

  if( notify )
  {
    QString message = "Linguistica saves your project in a large number of 'readable' text\nfiles.  We suggest you create a new folder in which to save them.";
    QMessageBox::information ( this, "Linguistica : Save File", message );
  }

  QString FileName = Q3FileDialog::getSaveFileName( m_projectDirectory + m_projectName,
                           "Linguistica Projects (*.prj)",
                           this,
                           "save file dialog"
                           "Choose a folder to save under" );

  if (FileName.length() == 0 ) return;

  SlashLoc = FileName.findRev ('\\');
  if( SlashLoc < 0 ) SlashLoc = FileName.findRev('/');
  m_projectIndex = 1;

  m_projectDirectory = FileName.left( SlashLoc + 1 );
  m_Settings.writeEntry( "/linguistica.uchicago.edu/Linguistica/Project/Directory", m_projectDirectory );

  m_projectName = FileName.mid ( SlashLoc + 1 );
  NameLoc = m_projectName.findRev(".prj");
  SlashLoc = m_projectName.findRev("_");
  if( NameLoc >= 0 )
  {
  	if( SlashLoc >= 0 && SlashLoc < NameLoc )
	{
    	FileName = m_projectName.mid( SlashLoc + 1, NameLoc - SlashLoc - 1 );
    	m_projectIndex = FileName.toInt();
    	m_projectName = m_projectName.left( SlashLoc );
	}
	else
	{
		m_projectName = m_projectName.left( NameLoc );
	}
  }

  saveFileActionSlot();

}


void LinguisticaMainWindow::saveFileActionSlot()
{
	if ( m_projectDirectory.length() == 0  || m_projectName.length() == 0 )
	{
		saveAsFileActionSlot();
		return;
	}

	QString Prefix = m_projectDirectory + m_projectName + "_" + QString("%1").arg( m_projectIndex );
	m_projectIndex ++;
	QString ProjectFileName = Prefix + ".prj";

	for( int i=0; i < m_lexicon->GetMiniSize(); i++ )
	{
		CMiniLexicon* mini = m_lexicon->GetMiniLexicon(i);
		if( !mini ) continue;

		QString WordsFileName				= Prefix + QString("_Mini%1").arg(i+1) + "_Words.txt";

		QString SuffixFileName				= Prefix + QString("_Mini%1").arg(i+1) + "_Suffixes.txt";
		QString PrefixFileName				= Prefix + QString("_Mini%1").arg(i+1) + "_Prefixes.txt";

		QString SignatureFileName			= Prefix + QString("_Mini%1").arg(i+1) + "_Signatures.txt";
		QString StemFileName				= Prefix + QString("_Mini%1").arg(i+1) + "_Stems.txt";

		mini->GetWords()->OutputWords( WordsFileName );

		if( mini->GetAffixLocation() == WORD_FINAL || 
			mini->GetAffixLocation() == STEM_FINAL  )
		{
			mini->GetSuffixes()->OutputSuffixes( SuffixFileName );
		}

		if( mini->GetAffixLocation() == WORD_INITIAL || 
			mini->GetAffixLocation() == STEM_INITIAL  )
		{
			mini->GetPrefixes()->OutputPrefixes( PrefixFileName );
		}

		if( mini->GetSignatures() )
		{
			mini->GetSignatures()->OutputSignatures( SignatureFileName );
			mini->GetStems()->OutputStems( StemFileName );
		}
	}

	m_lexicon->OutputStats( ProjectFileName );

	// TODO: output corpus words

	// Project saved
	m_projectDirty = false;

	emit updateTreeViewSignal();
}


namespace {
	// "c:\\Program Files\\Internet Explorer\\iexplore.exe" on Windows?
	const QString default_browser = "netscape";
}

void  LinguisticaMainWindow::jgWebLinksActionSlot()
{
	// code taken from a Qt message board -jeremy
	QString url = "http://humanities.uchicago.edu/faculty/goldsmith";
	Q3Process *browser = new Q3Process( this );
	browser->clearArguments();
	browser->addArgument(default_browser);

	if(url.stripWhiteSpace().length() > 0)
	{
		browser->addArgument(url);
	}
	if( !browser->start() )
	{
		QMessageBox::critical(this, "Critical!",
			"Browser reports error!");
	}
}


void  LinguisticaMainWindow::lxaWebLinksActionSlot()
{
	// code taken from a Qt message board -jeremy
	QString url = "http://linguistica.uchicago.edu/linguistica.html";
	Q3Process *browser = new Q3Process( this );
	browser->clearArguments();
	browser->addArgument(default_browser);

	if(url.stripWhiteSpace().length() > 0)
	{
		browser->addArgument(url);
	}
	if( !browser->start() )
	{
		QMessageBox::critical(this, "Critical!",
			"Browser reports error!");
	}
}



void  LinguisticaMainWindow::findAllomorphySlot()
{
  if( m_lexicon->GetMiniCount() )
  {

  if( m_logging ) OpenLogFile();
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  current_mini->RelateStems();



//  m_lexicon->FindAllomorphy();
//  m_lexicon->FindAllomorphy2();
  if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

  // Disable this functionality
//  if( findAllomorphyAction->isEnabled() ) findAllomorphyAction->setEnabled(false);

  // Unsaved work
  m_projectDirty = true;

  // Update tree view
  emit updateAllViewsSignal();

  }
}


void  LinguisticaMainWindow::showDeleteesSlot( bool b )
{
  m_showDeleteesAction->setOn( b );
  emit updateAllViewsSignal();
}


void  LinguisticaMainWindow::rereadCorpusSlot()
{
  int result;

  if (m_corpusFileName.isEmpty()) {
	// XXX. no corpus file chosen! let user know.
	return;
  }

  // Verify information saved before overwrite
  bool notifications = GetPreference( "Notifications" ).toInt();
  if( notifications && m_projectDirty )
  {
    QString message = "This action will overwrite your data.  Would you like to\nsave your changes first?";
    VerifyDialog *saveCheckDlg = new VerifyDialog(message);
    saveCheckDlg->setCaption( saveCheckDlg->caption() + "Save Project?" );

    switch( saveCheckDlg->exec() )
    {
    case RESULT_YES:
      // User clicked 'Yes', save changes and continue
      saveFileActionSlot();
      if( m_projectDirty ) return;
      break;
    case RESULT_NO:
      // User clicked 'No', continue
      break;
    case RESULT_CANCEL:
    default:
      // User clicked 'Cancel', just return
      return;
    }
  }

  // Clear collection view
  m_collectionView->clear();
  m_docType = NO_DOC;

  // Read the lexicon and activate other functions
  // if successful.  Log if desired.
  if( m_logging ) OpenLogFile();
  Q_ASSERT(!m_corpusFileName.isEmpty());
  result = m_lexicon->RereadCorpus( m_corpusFileName, GetNumberOfTokens() );
  if( m_logging ) CloseLogFile();
//  if( result != -1 ) runAllAction->setEnabled(true);
//  else if( runAllAction->isEnabled() ) runAllAction->setEnabled(false);


	// Update corpus words
	m_lexicon->DoWordUpdates();

  // Project unsaved
  m_projectDirty = true;

  emit updateAllViewsSignal();
}


void  LinguisticaMainWindow::clearLexiconSlot()
{
  // Verify information saved before overwrite
  bool notifications = GetPreference( "Notifications" ).toInt();
  if( notifications && m_projectDirty )
  {
    QString message = "This action will overwrite your data.  Would you like to\nsave your changes first?";
    VerifyDialog *saveCheckDlg = new VerifyDialog(message);
    saveCheckDlg->setCaption( saveCheckDlg->caption() + "Save Project?" );

    switch( saveCheckDlg->exec() )
    {
    case RESULT_YES:
      // User clicked 'Yes', save changes and continue
      saveFileActionSlot();
      if( m_projectDirty ) return;
      break;
    case RESULT_NO:
      // User clicked 'No', continue
      break;
    case RESULT_CANCEL:
    default:
      // User clicked 'Cancel', just return
      return;
    }
  }

  m_collectionView->clear();
  m_docType = NO_DOC;
  m_lexicon->ClearAll();
  m_projectDirty = false;
  emit updateAllViewsSignal();
}


void  LinguisticaMainWindow::successorFreqSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->GetWords()->SuccessorFreq1 ( current_mini->GetStems(),
      	                 												 current_mini->GetSuffixes(),
        	               												 current_mini->GetSignatures(), SF1,
          	             												 NUMBER | UNKNOWN  );
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			successorFreqSlot();
		}
	}
}


void  LinguisticaMainWindow::predecessorFreqSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_INITIAL ) )
		{

    	// Run predecessor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->GetWords()->CreateReverseTrie();
			current_mini->GetWords()->PredecessorFreq1 ( current_mini->GetStems(),
      	      				           									      current_mini->GetPrefixes(),
        	            				   									 			current_mini->GetSignatures(), SF1,
          	             													 			NUMBER | UNKNOWN  );
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_INITIAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			predecessorFreqSlot();
		}
	}
}


void  LinguisticaMainWindow::checkPfxSignaturesSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_INITIAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->CheckSignatures();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_INITIAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			checkPfxSignaturesSlot();
		}
	}
}

void  LinguisticaMainWindow::checkSignaturesSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex())->CheckSignatures();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
//		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			checkSignaturesSlot();
		}
	}
}

void  LinguisticaMainWindow::knownStemsPrefixesSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_INITIAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->ExtendKnownStemsToKnownAffixes();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_INITIAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			knownStemsPrefixesSlot();
		}
	}
}


void  LinguisticaMainWindow::knownStemsSuffixesSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->ExtendKnownStemsToKnownAffixes();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			knownStemsSuffixesSlot();
		}
	}
}

void  LinguisticaMainWindow::fromPfxSigsFindStemsSlot()
{	
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_INITIAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->TakeSignaturesFindStems();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_INITIAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			fromPfxSigsFindStemsSlot();
		}
	}
}


void  LinguisticaMainWindow::fromSigsFindStemsSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->TakeSignaturesFindStems();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			fromSigsFindStemsSlot();
		}
	}
}


void  LinguisticaMainWindow::fromStemsFindAffixesSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->FromStemsFindAffixes();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			fromStemsFindAffixesSlot();
		}
	}
}


void  LinguisticaMainWindow::findPfxSingletonSigsSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_INITIAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->FindSingletonSignatures();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_INITIAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			findPfxSingletonSigsSlot();
		}
	}
}


void  LinguisticaMainWindow::findSingletonSigsSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->FindSingletonSignatures();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			findSingletonSigsSlot();
		}
	}
}


void  LinguisticaMainWindow::pfxLooseFitSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_INITIAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->LooseFit();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_INITIAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			pfxLooseFitSlot();
		}
	}
}


void  LinguisticaMainWindow::looseFitSlot()
{
  CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

  if( m_lexicon->GetMiniCount() )
  {
		if( isCorrectAffix( STEM_FINAL ) )
		{

    	// Run successor freq function, log if desired
    	if( m_logging ) OpenLogFile();
    	current_mini->LooseFit();
		
    	if( m_logging ) CloseLogFile();

		// Update corpus words
		m_lexicon->DoWordUpdates();

    	// Unsaved work
    	m_projectDirty = true;

    	// Update tree view
    	emit updateAllViewsSignal();
  	}
		else
		{
			CMiniLexicon* new_mini = m_lexicon->GetMiniLexicon( m_lexicon->NewMiniLexicon() );
			new_mini->SetAffixLocation( STEM_FINAL );
			new_mini->AddToWordCollection( current_mini->GetWords(), WW_All );
			m_lexicon->SetActiveMiniIndex( new_mini->GetIndex() );
			looseFitSlot();
		}
	}
}

void  LinguisticaMainWindow::showToolbarsSlot(bool b)
{
	if (b) m_Toolbar->show();
	else m_Toolbar->hide();
}


void  LinguisticaMainWindow::showStatusBarSlot(bool b)
{
  if( b ) statusBar()->show();
  else statusBar()->hide();
}


void  LinguisticaMainWindow::saveBrokenCorpusSlot()
{  
	QString BrokenCorpusFileName = m_corpusFileName.left( m_corpusFileName.find('.') ) + "_Broken.txt";
	BrokenCorpusFileName = Q3FileDialog::getSaveFileName( BrokenCorpusFileName,
														 "Text Documents (*.txt)",
														 this,
														 "save file dialog"
														 "Choose a folder to save under" );

	if( BrokenCorpusFileName.length() == 0 ) return;

	m_lexicon->MakeBrokenCorpus( BrokenCorpusFileName );
}


void  LinguisticaMainWindow::helpAboutSlot()
{
  HelpAboutDialog *helpDlg = new HelpAboutDialog( this );
  if( helpDlg->exec() == QDialog::Accepted )
  {
    // Do nothing
  }
  else
  {
    // Do nothing
  }
  delete helpDlg;
}


void LinguisticaMainWindow::newMiniLexiconActionSlot()
{
  int index;
  
  for( index = m_lexicon->GetMiniSize()-1; index >= 0; index-- )
  {
  	if( m_lexicon->GetMiniLexicon(index) )
	{
		index++;
		break;
	}
  }
  
  if( index == 0 )
  {
    newFileActionSlot();
    return;
  }

  // Create the new mini
  index = m_lexicon->NewMiniLexicon();
  m_lexicon->SetActiveMiniIndex( index );

  // Populate its words
  populateWordsActionSlot();
  

  QString mini_name( "Mini-Lexicon %1" );
  mini_name = mini_name.arg( index + 1 );
  QString remark = "Before analysis; words only";
  m_lexicon->GetDLHistory()->append( mini_name, remark, m_lexicon->GetMiniLexicon( index ) );
}


void LinguisticaMainWindow::deleteMiniLexiconActionSlot()
{
	if( m_lexicon->GetMiniCount() == 1 )
	{
		clearLexiconSlot();
	}
	else
	{
		int active = m_lexicon->GetActiveMiniIndex();
		m_lexicon->DeleteMiniLexicon( active );
	}
	
	SetDocType( NO_DOC );	
	emit updateAllViewsSignal();
}


void LinguisticaMainWindow::autoLayeringActionSlot()
{
  if( m_lexicon->GetMiniCount() )
  {
    // Run all suffix functions, log if desired
    if( m_logging ) OpenLogFile();
    m_lexicon->FindSuffixes( true );
	
    if( m_logging ) CloseLogFile();

	// Update corpus words
	m_lexicon->DoWordUpdates();

    // Unsaved work
    m_projectDirty = true;

    // Update tree view
    emit updateAllViewsSignal();
  }
}


void LinguisticaMainWindow::populateWordsActionSlot()
{
  int index = m_lexicon->GetActiveMiniIndex();
  CMiniLexicon* active, * other;

  QStringList notIncluded, included;

  if( m_lexicon->GetMiniLexicon( index-1 ) )
  {
    included << "Mini-Lexicon " + QString("%1").arg( index ) + " : Unanalyzed Words";
    included << "Mini-Lexicon " + QString("%1").arg( index ) + " : Stems";
    notIncluded << "Mini-Lexicon " + QString("%1").arg( index ) + " : Analyzed Words";
  }
  for( int i=0; i < m_lexicon->GetMiniSize(); i++ )
  {
    if( i != index && i != index-1 && m_lexicon->GetMiniLexicon(i) )
    {
      notIncluded << "Mini-Lexicon " + QString("%1").arg( i+1 ) + " : Analyzed Words";
      notIncluded << "Mini-Lexicon " + QString("%1").arg( i+1 ) + " : Unanalyzed Words";
      notIncluded << "Mini-Lexicon " + QString("%1").arg( i+1 ) + " : Stems";
    }
  }

  ListBuilderDialog *dlg = new ListBuilderDialog( "Linguistica : Populate Mini-Lexicon",
                                                notIncluded, included, this );
  if( dlg->exec() == QDialog::Accepted )
  {
  Q3ListBoxItem* included = dlg->GetIncluded()->item(0);
  QString item;

    // Populate the word collection of a new mini
    active = m_lexicon->GetMiniLexicon( index );
	

  while( active && included )
  {
    item = included->text();
    index = item.find( " :" ) - 1;
    index = item.mid( index, 1 ).toInt() - 1;

    other = m_lexicon->GetMiniLexicon( index );
	if( !other ) continue;

    if( item.find( "Unanalyzed" ) >= 0 )
    {
      active->AddToWordCollection( other->GetWords(), WW_UnanalyzedOnly );
    }
    else if( item.find( "Analyzed" ) >= 0 )
    {
      active->AddToWordCollection( other->GetWords(), WW_AnalyzedOnly );
    }
    else if( item.find( "Stems" ) >= 0 )
    {
      active->AddToWordCollection( other->GetStems() );
    }

    included = included->next();
  }
  }
  else
  {
    // Do nothing
  }
  delete dlg;

  emit updateTreeViewSignal();
}


void LinguisticaMainWindow::addToBorrowedSigsSlot()
{
  int index = m_lexicon->GetActiveMiniIndex();
  CMiniLexicon* active, * other;

  QStringList notIncluded, included;

  if( m_lexicon->GetMiniLexicon( index-1 ) )
  {
    included << "Mini-Lexicon " + QString("%1").arg( index ) + " : Signatures";
  }
  for( int i=0; i < m_lexicon->GetMiniSize(); i++ )
  {
    if( i != index-1 && m_lexicon->GetMiniLexicon(i) )
    {
      notIncluded << "Mini-Lexicon " + QString("%1").arg( i+1 ) + " : Signatures";
    }
  }

  ListBuilderDialog *dlg = new ListBuilderDialog( "Linguistica : Populate Mini-Lexicon",
                                                notIncluded, included, this );
  if( dlg->exec() == QDialog::Accepted )
  {
  Q3ListBoxItem* included = dlg->GetIncluded()->item(0);
  QString item;

    // Populate the word collection of a new mini
    active = m_lexicon->GetMiniLexicon( index );

  while( active && included )
  {
    item = included->text();
    index = item.find( " :" ) - 1;
    index = item.mid( index, 1 ).toInt() - 1;

    other = m_lexicon->GetMiniLexicon( index );
	if( !other ) continue;

    included = included->next();
  }
  }
  else
  {
    // Do nothing
  }
  delete dlg;

  emit updateTreeViewSignal();
}

 


void LinguisticaMainWindow::RunSedSlot()
{
	QMessageBox::information( this, "Debug","Finding word neighbors","OK" );	
	if ( m_lexicon)
	{
		if ( m_Words_InitialTemplates != NULL)
		{
			QMessageBox::information( this, "Attention","You have run the SED !","OK" );	
			return; 
		}
//		bool			ShouldBeFurther = true; 	
		
		
		
		// StringEdit Distance Init
		m_Words_InitialTemplates		= new CTemplateCollection (m_lexicon);
		m_Words_Templates				= new CTemplateCollection (m_lexicon);
		   	
        
        if( m_logging ) OpenLogFile();
     	
//  Put the following back in ------------------//

        //		FindAllEditDistances(m_Words_InitialTemplates);

        FindAllWordNeighbors(m_lexicon);


if (false) // John Goldsmith Dec 28 2008 testing what follows:
{
        CheckForConflations(m_Words_Templates, m_Words_InitialTemplates);
		
		// Update the Stickness
		m_Words_Templates ->UpdateGlobalStickNess2();
		
		// Move Common Head/Tail
		m_Words_Templates ->AdjustTemplatesByMovingCommonTailOrHead2(0); 
		
		// Collapse algorithm 1
//		ShouldBeFurther = m_Words_Templates ->CollapseAlgorithm1(1);
		m_Words_Templates ->CollapseAlgorithm1(1);

		// Then sort these templates again.
		m_Words_Templates ->SetSwitchOfSortingValue(true); 
		m_Words_Templates ->SetSortValidFlag(false); 
		m_Words_Templates ->Sort(TEMPLATE_SORT); 

		
		// Next, I tried the absorption algorithm
		m_Words_Templates ->AbsorbWords1(1); 
		m_Words_Templates ->SetSwitchOfSortingValue(true); 
		m_Words_Templates ->SetSortValidFlag(false);  
		m_Words_Templates ->Sort(TEMPLATE_SORT);  


		// Next, I tried the Paradigmatic graph function
		m_Words_Templates ->UpdateGlobalStickNess2(); 
		m_Words_Templates ->FindMorphemePrefixOrSuffixWithParadigmaticGraph(1); 

		// Then sort these templates again.
		m_Words_Templates ->SetSwitchOfSortingValue(true); 
		m_Words_Templates ->SetSortValidFlag(false); 
		m_Words_Templates ->Sort(TEMPLATE_SORT); 



		
		m_Words_Templates ->OutputTemplatesForGoldStand(); 
} // end of if (FALSE);
        emit updateTreeViewSignal(); 
	}
	else
	{
		QMessageBox::information( this, "Attention","Lexicon is NULL","OK" );	
	}
    if( m_logging ) CloseLogFile();
} 


void LinguisticaMainWindow::FindSlicesSlot()
{
  if( m_lexicon  && m_lexicon->GetMiniCount())
  {
    //QTime t; t.start();

    if (m_logging) OpenLogFile();

    CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());
    CWordCollection* Words = current_mini->GetWords();

    SliceCollection MySlices;
    StringInventory MyStringInventory;
    setStatusBar1("Finding slices...");
    MyStringInventory.addwordcollection(Words, MySlices, this);

    if (m_logging) { MySlices.writetolog(*GetLogFileStream()); }

    MySlices.FindWordPairs(this, m_lexicon);

    if (m_logging) CloseLogFile();

    //std::cout << "FindSlices:: Time elapsed: " << t.elapsed() << "ms." << std::endl;
  }
} 


/////////////////////////////////////////////////////////////////
void LinguisticaMainWindow::FindAllWordNeighbors(CLexicon* MyLexicon )
{ 

    MyLexicon->GetSEDWords()->FindAllWordNeighbors(MyLexicon);
    return;
 
}



/////////////////////////////////////////////////////////////////
//// FindStringEditDistance
void LinguisticaMainWindow::FindAllEditDistances(CTemplateCollection* pContainer)
{
	pContainer->FindAllEditDistances ( m_lexicon, m_lexicon->GetSEDWords()) ;
	return;
}


void LinguisticaMainWindow::CheckForConflations(CTemplateCollection* Target, CTemplateCollection* Source)
{
	Target ->CheckForConflations(Source); 		
}






//void LinguisticaMainWindow::runSyntax()
//{
	
//	if ( m_lexicon ->m_pFSA)
//	{
		//m_lexicon ->m_pFSA ->FindAllEditDistances(m_lexicon ->m_pFSA ->m_Words_InitialTemplates);
		//m_lexicon ->m_pFSA ->CheckForConflations(m_lexicon ->m_pFSA ->m_Words_Templates, m_lexicon ->m_pFSA ->m_Words_InitialTemplates);
//		emit updateTreeViewSignal(); 
//	}
//	else
//	{
//		QMessageBox::information( this, "Attention","FSA is NULL","OK" );	
//	}

//}


bool LinguisticaMainWindow::isCorrectAffix( eAffixLocation affixLoc )
{
	CMiniLexicon* mini = m_lexicon->GetMiniLexicon( m_lexicon->GetActiveMiniIndex() );
	eAffixLocation current = mini->GetAffixLocation();
	
	if( current == affixLoc ) return TRUE;
	
	if( ( mini->GetSuffixes() && !mini->GetSuffixes()->GetCount() ) ||
	    ( mini->GetPrefixes() && !mini->GetPrefixes()->GetCount() ) )
	{
		mini->SetAffixLocation( affixLoc );
		return TRUE;
	}
	
	switch( affixLoc )
	{
		case STEM_INITIAL:
		case WORD_INITIAL:
			if( current == STEM_INITIAL || current == WORD_INITIAL ) return TRUE;
			else return FALSE;
			
		case STEM_FINAL:
		case WORD_FINAL:
		default:
			if( current == STEM_FINAL || current == WORD_FINAL ) return TRUE;
			else return FALSE;
	}
}

void LinguisticaMainWindow::commandLineCloseSlot()
{ close(); }

void LinguisticaMainWindow::executeCommandLineArgs(int count,
	bool mini, bool prefix, bool suffix)
{
	if (m_corpusFileName.isEmpty()) {
		// XXX. no corpus file chosen! let user know.
		return;
	}

	if( count != 0 ) SetNumberOfTokens( count );

	m_lexicon->ClearAll();
    
	// Log if desired.
	if( m_logging ) OpenLogFile();
    
	// Read words into lexicon from the corpus
	Q_ASSERT(!m_corpusFileName.isEmpty());
	m_lexicon->ReadCorpus(m_corpusFileName, GetNumberOfTokens());

	if( mini )
	{
		if( suffix ) m_lexicon->FindSuffixes( TRUE );
		if( prefix ) m_lexicon->FindPrefixes( TRUE );
		
	}
	else
	{
		if( suffix ) m_lexicon->FindSuffixes();
 		if( prefix ) m_lexicon->FindPrefixes();
		
	}

	if( m_logging ) CloseLogFile();

  	// Clear the collection view
  	m_collectionView->clear();
  	m_docType = NO_DOC;
	
	int SlashLoc = m_corpusFileName.findRev('\\');
  	if( SlashLoc < 0 ) SlashLoc = m_corpusFileName.findRev('/');

  	if( m_projectDirectory.length() == 0 ) m_projectDirectory = m_corpusFileName.left( SlashLoc + 1 );
	else if( m_projectDirectory.at( m_projectDirectory.length()-1 ) != '/' ) m_projectDirectory = m_projectDirectory + "/";
	if( m_projectDirectory.length() == 0 ) m_projectDirectory = "./";
	
	m_projectName = m_corpusFileName.mid ( SlashLoc + 1 );
	int NameLoc = m_projectName.findRev(".");
	m_projectName = m_projectName.left( NameLoc );
	m_projectIndex = 0;
	
	if( m_goldStdFileName.length() > 0 )
	{
		m_goldStdOutputFile = m_projectDirectory + m_projectName + "_GoldStandardComparison.txt"; 
		compareGoldStdSlot();
	}
	
	saveFileActionSlot();

  	// Update tree view
  	emit updateAllViewsSignal();
}


// YuHu Add for output morphological cut corpus for MT 
// TODO: Need change after 2005/11/30 Fix after Lexicon is done
void LinguisticaMainWindow::editCorpusForMT()
{
/*
	QString								line;
	QString								FirstPiece, RemainingPiece; 
	QString								theWord;
	CStem*								theCStem; 
	CParse*								theParse; 
	StringToParse*						TempSedCuts; 
	StringToParse::Iterator				StringToParseIt; 
	StringToPtrCStem					SFCuts; 
	StringToPtrCStem					SedCuts; 
	StringToCStem::Iterator				SFIt; 
	StringToCStem*						TempSFCut; 
	int									Strategy; // we discussed the strategy 1, 2, 3, 4

	
	// Get the Lingustica analyses result SF or PF
	if ( !m_lexicon) return; 
	TempSFCut = m_lexicon ->GetWords();

	for ( SFIt = TempSFCut ->begin(); SFIt != TempSFCut ->end(); SFIt++)
	{
		theWord = SFIt.key();
		theCStem = &SFIt.data();
		SFCuts.insert(theWord, theCStem);
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

	// 3. Read MT Corpus File 

	QString			MTFileName;
	QString			FileNameStrippedDot; 
	QString			outputMTFileName_SF;
	QString			outputMTFileName_SED;


	MTFileName = QFileDialog::getOpenFileName( m_projectDirectory,
												 "Files (*.*)",
												 this,
												 "open file dialog",
												 "Choose a file to open" );
												 
	if( !MTFileName.isEmpty() )
	{ 
		
	}
	else
	{
		return; 
	}

	FileNameStrippedDot = MTFileName.left(MTFileName.find(QString("."))); 
		

	for ( Strategy =1; Strategy <=4; Strategy++)
	{
		outputMTFileName_SF = FileNameStrippedDot + "_Output_SF_" + QString("%1").arg(Strategy) + ".txt";
		m_lexicon ->CutMtCorpusWithMorphologyAnalyses(MTFileName, outputMTFileName_SF,SFCuts,Strategy);   
	}

	if ( m_Words_Templates != NULL)
	{
		for ( Strategy =1; Strategy <=4; Strategy++)
		{
			outputMTFileName_SED = FileNameStrippedDot + "_Output_SED_" + QString("%1").arg(Strategy) + ".txt";
			m_Words_Templates ->CutMtCorpusWithMorphologyAnalyses(MTFileName, outputMTFileName_SED,SedCuts,Strategy);   
		}
	
	
	}
*/
}


// Start of John's Phonology stuff ///////////////////////////////////
// moved to phonology.cpp
/*
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

 
void LinguisticaMainWindow::DropTierLeaveSlot()
{
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());

	if ( current_mini )
	{
		current_mini->GetWords()->SplitPhonologyToTiers( Split_LeaveSlot);
		current_mini->GetWords()->ComputeZ();
//		current_mini->GetWords()->ComputeZStar();
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
//		current_mini->GetWords()->ComputeZStar();
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
 */
 /////////// End of John's Phonology
 /*
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
*/
/*
void LinguisticaMainWindow::sequencerTestAFileSlot()
{
	if ( m_Sequencer == NULL)
	{
		return;
	}

	m_Sequencer ->sequencerTestAFile(); 

}
*/
 /*
void LinguisticaMainWindow::statsReadCorpusSlot()
{
	if ( m_Stats == NULL)
	{
		return;
	}

	m_Stats->readCorpus();

}
 */
/*
void LinguisticaMainWindow::fromStemsFindCompoundsSlot()
{
	if( m_logging ) OpenLogFile();
	m_lexicon->FromStemsFindCompounds();
	//the following is put here temporarily; it would normally be
	// triggered by a separate user behavior: JG
	m_lexicon->CalculateCoefficientsOfAffixness();
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
*/


// MT part
/*
void LinguisticaMainWindow::mTModel1Slot()
{

	int					model1Iterations = 10; 
	int					model2Iterations = 10; 
	bool				inheritTFromModel1 = true; 

	if ( m_MT != NULL)
	{
		delete m_MT; 	
	}

	m_MT = new cMT(this, m_projectDirectory); 
	
	m_MT ->readTrainingCorpus(); 

	m_MT ->trainModel1(model1Iterations); 
	
	m_MT ->trainModel2Norm(model2Iterations, inheritTFromModel1); 

}
*/
// HMM part
/*
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

	//delete oneStateHMM;

	// Update tree view
	emit updateAllViewsSignal();



}
*/
//////////////////////////////////////////////////////////////////////////////
//		Test
//////////////////////////////////////////////////////////////////////////////

void LinguisticaMainWindow::testMultiDimensionDisplaySlot()
{
	int				NumberOfSymbols;
	int				NumberOfStates;
	double**		ptrData;
	IntToString		listOfSymbols; 	
	int				i,j; 
	int				NumberOfIterations =100; 

	NumberOfSymbols = 4; 
	NumberOfStates = 4; 

	// Update the GraphicView to Display the HMM multidimension data
	ptrData = new double*[NumberOfSymbols];
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
	for (i=0; i<NumberOfIterations; i++)
	{

		// Display on Graphic View
//		updateSmallGraphicDisplaySlotForMultiDimensionData(NumberOfStates,
//	/													NumberOfSymbols,
//														ptrData,
//														listOfSymbols);


		//Alter the ptrData
		for(j=0; j<NumberOfSymbols;j++)
		{
			ptrData[j][j % NumberOfStates] += 0.1 / NumberOfStates; 
			
		}
		
		// Sleep for a short time : Is there any Qt sleep function ?
		int			dummy=0; 
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

void LinguisticaMainWindow::goldwaterMethodSlot()
{
	QMessageBox::information ( this, "GoldwaterMethod", "Begin Goldwater Thesis Morphology Learning Algorithm!" );
}
/*
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
*/
/*
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
*/
/*
void LinguisticaMainWindow::viewCorpusSlot()
{
	CorpusViewDialog *corpusViewDlg = new CorpusViewDialog( m_lexicon, this, "corpusView", FALSE, Qt::WStyle_Customize | Qt::WStyle_NormalBorder | Qt::WStyle_Title | Qt::WStyle_SysMenu );
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
}
*/
void LinguisticaMainWindow::suffixesCollapse_two_signaturesAction_activated()
{
	int i;
	i =2;
	CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());
	CSignatureCollection		TheseSignatures (current_mini);
 	 

	int NumberOfSignaturesSelected = 0;
//unused variable:
//	QListViewItem* selectedItem = NULL;

	m_collectionView->setSelectionMode (Q3ListView::Extended);
    
	Q3ListViewItemIterator it( m_collectionView );

    while ( it.current() ) 
	{
            if (it.current()->isSelected() ) 
			{
				NumberOfSignaturesSelected++;
				CSignatureListViewItem *item = (CSignatureListViewItem*) it.current();
 				TheseSignatures << item->GetSignature();
			}
            ++it;
    }

	if (NumberOfSignaturesSelected != 2) 
	{
		QMessageBox::warning(	m_lexicon->GetDocument(),
										"Linguistica",
										"Select exactly two signatures, and press command again",
										QMessageBox::Ok,
										QMessageBox::NoButton,
										QMessageBox::NoButton );

		return;
	}
 
	



	
	m_collectionView->setSelectionMode (Q3ListView::Single);
}
void	LinguisticaMainWindow::toggleMultipleSelectionSlot()
{
	if (m_collectionView->selectionMode() == Q3ListView::Single )
	{
		m_collectionView->setSelectionMode(Q3ListView::Extended);
	}	else
	{
		m_collectionView->setSelectionMode (Q3ListView::Single);

	}
}


void  LinguisticaMainWindow::addContentToCommandLine(QString content)
{
	m_commandLine->insert(content);
}

/** \page page1 The GUI: An overview
  
  \section sec The main screen
  This page contains the subsections \ref subsection1 and \ref subsection2.
  For more info see page \ref page2. Hello??
  \subsection subsection1 The first subsection
  Text. Lxa
  \subsection subsection2 The second subsection
  More text.

! \page page2 How strings are represented: The CParse class
  Even more info.
! \page page3 Collection classes
! \page page4 The Lexicon class
! \page page5 A MiniLexicon: Signatures, Stems, Affixes
*/



void  LinguisticaMainWindow::fsaTestFuncAction()
{
  if( m_lexicon  && m_lexicon->GetMiniCount())
  {
    CMiniLexicon* current_mini = m_lexicon->GetMiniLexicon(m_lexicon->GetActiveMiniIndex());
    if(current_mini->GetFSA())
    {
      current_mini->GetFSA()->ResetDisplay();
      current_mini->GetFSA()->FSATestFunc();
      current_mini->GetFSA()->FSAListDisplay(m_collectionView,m_lexicon->GetOutFilter(),false);
    }
  } 
}

