// Implementation of preferences dialog
// Copyright © 2009 The University of Chicago
#include "preferencesdialog.h"

#include "Config.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QCheckBox>
#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include <Q3PtrList>
#include <QString>
#include "linguisticamainwindow.h"
#include "LPreferences.h"
#include "ScrubRules.h"

const int MAX_REPLACEMENTS = 100;

namespace {
	void LoadDictIntoListView(QMap<QString, QString>* dict, Q3ListView* view )
	{
		Q3ListViewItem * item, * parent;
		QString dKey, dVal;
		int slash;

		view->clear();

		StringToString::Iterator it;
		for( it = dict->begin(); it != dict->end(); ++it )
		{
			dKey = it.key();
			dVal = it.data();

			slash = dKey.find( '\\' );
			if( slash >= 0 )
			{
				parent = view->findItem( dKey.left( slash ), 0, Q3ListView::ExactMatch );
				if( !parent )
				{
					parent = new Q3ListViewItem( view, dKey.left( slash ) );
					parent->setOpen( true );
				}
				item = new Q3ListViewItem( parent, dKey.mid( slash + 1 ), dVal.replace( '_', ' ' ) );
			}
			else
			{
				item = new Q3ListViewItem( view, dKey, dVal.replace( '_', ' ' ) );
			}
		}
	}
}

QColor	GetColorPreference( CLPreferences* prefs, QString title )
{
	QString clrname = prefs->GetPreference( title + "_Color" );
	if( clrname.length() < 1 ) clrname = "#000000";
	return QColor( clrname );
}


void SaveScrubRulesToPreferences( PreferencesDialog* dialog, CLPreferences* prefs, bool initialized )
{
	Q3ListBoxItem* item = dialog->m_scrubListBox->item(0);
	QStringList scrubRules;

	while( item )
    {				
      	scrubRules << item->text();

		if( item->text() == SCR_REMOVE_PRECEDING_PUNCT ) scrubRules << dialog->m_precedingPunctLineEdit->text();
		else if( item->text() == SCR_REMOVE_INTERNAL_PUNCT ) scrubRules << dialog->m_internalPunctLineEdit->text();
		else if( item->text() == SCR_REMOVE_FOLLOWING_PUNCT ) scrubRules << dialog->m_followingPunctLineEdit->text();

		item = item->next();
	}

	if (initialized)
		prefs->SetStringListPreference("Scrub_Replacements",
						scrubRules);
}


PreferencesDialog::PreferencesDialog( CLPreferences* prefs,
			StringToString* params,
			QWidget* parent, Qt::WindowFlags fl )
	: QDialog( parent, 0, false, fl ), Ui::PreferencesDialogBase()
{
	setupUi( this );

	m_Prefs = prefs;
	m_DefaultParams = params;
	m_replacements = new StringToString();

	m_initialized = FALSE;
	init();
	m_initialized = TRUE;
}

PreferencesDialog::~PreferencesDialog()
{
	if( m_replacements ) delete m_replacements;
}


void PreferencesDialog::init()
{
	QString preference = "";

	QFont font = m_Prefs->GetFontPreference( "Affix" );
	QColor color = GetColorPreference( m_Prefs, "Affix" );

	// Morphology Highlighting
	m_MH_ListBox->setCurrentItem(0);
	m_MH_PreviewLineEdit->setFont( font );
	m_MH_PreviewLineEdit->setPointSize( 10 );
	if( color.isValid() ) m_MH_PreviewLineEdit->setColor( color );

	m_MH_BoldCheckBox->setChecked( font.bold() );
	m_MH_ItalicCheckBox->setChecked( font.italic() );
	m_MH_UnderlineCheckBox->setChecked( font.underline() );

	// Main font
	font = m_Prefs->GetFontPreference( "Main" );
	color = GetColorPreference( m_Prefs, "Main" );
	m_DSF_PreviewLineEdit->setFont( font );
	if( color.isValid() ) m_DSF_PreviewLineEdit->setColor( color );

	// Character Combinations
	m_CC_ListBox->clear();
	QStringList combos;
	m_Prefs->GetStringListPreference( "Character_Combinations", &combos );
	for( QStringList::Iterator strIt = combos.begin(); strIt != combos.end(); ++strIt )
	{
		m_CC_ListBox->insertItem( *strIt );
	}

	// Signature Delimiter
	preference = m_Prefs->GetPreference( "Sig_Delimiter" );
	if( preference.length() ) m_SigDelimiterLineEdit->setText( preference );
	else m_SigDelimiterLineEdit->setText( "." );

	// Save notifications
	preference = m_Prefs->GetPreference( "Notifications" );
	if( preference.length() ) m_NotificationsCheckBox->setChecked( preference.toInt() );
	else m_NotificationsCheckBox->setChecked( TRUE );

	// Scrubbing
	m_scrubListBox->clear();
	m_makeLowerCaseCheckBox->setChecked( FALSE );
	m_removeNumbersCheckBox->setChecked( FALSE );
	m_removePrecedingPunctCheckBox->setChecked( FALSE );
	m_removeInternalPunctCheckBox->setChecked( FALSE );
	m_removeFollowingPunctCheckBox->setChecked( FALSE );

	QStringList scrubRules;
	m_Prefs->GetStringListPreference( "Scrub_Replacements", &scrubRules );

	for( QStringList::Iterator it = scrubRules.begin(); it != scrubRules.end(); ++it )
	{
        if( (*it) == SCR_MAKE_LOWER_CASE ) m_makeLowerCaseCheckBox->toggle();
		else if( (*it) == SCR_REMOVE_NUMBERS ) m_removeNumbersCheckBox->toggle();
		else if( (*it) == SCR_REMOVE_PRECEDING_PUNCT ) 
		{
			m_removePrecedingPunctCheckBox->toggle();
			++it;
			m_precedingPunctLineEdit->setText( *it );
		}
		else if( (*it) == SCR_REMOVE_INTERNAL_PUNCT ) 
		{
			m_removeInternalPunctCheckBox->toggle();
			++it;
			m_internalPunctLineEdit->setText( *it );
		}
		else if( (*it) == SCR_REMOVE_FOLLOWING_PUNCT ) 
		{
			m_removeFollowingPunctCheckBox->toggle();
			++it;
			m_followingPunctLineEdit->setText( *it );
		}
        else 
		{
			int arrow = (*it).findRev( " --> " );
			if( arrow >= 0 )
			{
				QString replace = (*it).left( arrow );
				QString with = (*it).right( (*it).length() - arrow - 5 );
				m_replacements->replace( replace, with );

				m_scrubListBox->insertItem( *it );
			}
		}
    }

	// Dash at end of line -- defaults to "Join_Without_Dash"
	preference = m_Prefs->GetPreference( "Line_Final_Dash" );
	if( preference == "Join_With_Dash" ) m_joinWithDashRadioButton->setChecked( TRUE );
	else if( preference == "Do_Not_Join" ) m_doNotJoinRadioButton->setChecked( TRUE );

	// Dash inside word -- defaults to "Do_Not_Remove" and "Include_Full_Word_Only"
	preference = m_Prefs->GetPreference( "Word_Internal_Dash" );
	if( preference == "Remove" ) m_removeHyphenCheckBox->setChecked( TRUE );
	else m_removeHyphenCheckBox->setChecked( FALSE );

	preference = m_Prefs->GetPreference( "Word_With_Dash" );
	if( preference == "Include_Full_Word_Only" )
	{
		m_includeFullHyphenatedWordOnlyRadioButton->setChecked( TRUE );
	}
	else if( preference == "Include_Substrings_Only" )
	{
		m_includeSubstringsOfHyphenatedWordOnlyRadioButton->setChecked( TRUE );
	}
	else if( preference == "Include_Full_Word_And_Substrings" )
	{
		m_includeFullHyphenatedWordAndSubstringsRadioButton->setChecked( TRUE );
	}

	initParams();

	RedrawPreviews();
}


void PreferencesDialog::initParams()
{
	// Build Parameters list
	StringToString dict;
	m_Prefs->GetDictionaryPreference( "Lxa_Parameters", &dict );
	m_paramListView->setRootIsDecorated( true );
	LoadDictIntoListView( &dict, m_paramListView );

	// Make values renamable
	m_paramListView->setDefaultRenameAction( Q3ListView::Accept );
	m_paramListView->setSelectionMode( Q3ListView::Single );
	m_paramListView->setResizeMode( Q3ListView::LastColumn );
	Q3ListViewItemIterator listIt( m_paramListView );
    while ( listIt.current() ) 
	{
        if( listIt.current()->text(1).length() > 0 )
			listIt.current()->setRenameEnabled( 1, true );
        ++listIt;
    }
}


void PreferencesDialog::RedrawPreviews()
{
	// Morphology Highlighting
	m_MH_PreviewLineEdit->clear();
	m_MH_PreviewLineEdit->setPointSize( 10 );
	m_MH_PreviewLineEdit->insert( "Preview text" );

	// Default Screen Font
	QString text = m_DSF_PreviewLineEdit->text();
	m_DSF_PreviewLineEdit->clear();
	m_DSF_PreviewLineEdit->insert( text );
}



// SLOTS //////////////////////////////////////////////

void PreferencesDialog::mhListBoxHighlightedSlot()
{
	QFont font;
	QColor color;
	QString itemTxt;
	Q3ListBoxItem* item = m_MH_ListBox->selectedItem();

	if( item ) itemTxt = item->text();
	else itemTxt = "Affix";

	font = m_Prefs->GetFontPreference( itemTxt );
	color = GetColorPreference( m_Prefs, itemTxt );

	m_MH_BoldCheckBox->setChecked( font.bold() );
	m_MH_ItalicCheckBox->setChecked( font.italic() );
	m_MH_UnderlineCheckBox->setChecked( font.underline() );
	m_MH_PreviewLineEdit->setFont( font );
	m_MH_PreviewLineEdit->setColor( color );
	RedrawPreviews();
}


void PreferencesDialog::mhBoldCheckBoxClickedSlot()
{
	Q3ListBoxItem* item = m_MH_ListBox->selectedItem();
	if( !item ) return;

	QFont font = m_Prefs->GetFontPreference( item->text() );
	
	font.setBold( m_MH_BoldCheckBox->isChecked() );
	m_Prefs->SetFontPreference( item->text(), font );
	m_MH_PreviewLineEdit->setFont( font );
	RedrawPreviews();
}


void PreferencesDialog::mhItalicCheckBoxClickedSlot()
{
	Q3ListBoxItem* item = m_MH_ListBox->selectedItem();
	if( !item ) return;

	QFont font = m_Prefs->GetFontPreference( item->text() );
	
	font.setItalic( m_MH_ItalicCheckBox->isChecked() );
	m_Prefs->SetFontPreference( item->text(), font );
	m_MH_PreviewLineEdit->setFont( font );
	RedrawPreviews();
}


void PreferencesDialog::mhUnderlineCheckBoxClickedSlot()
{
	Q3ListBoxItem* item = m_MH_ListBox->selectedItem();
	if( !item ) return;

	QFont font = m_Prefs->GetFontPreference( item->text() );
	
	font.setUnderline( m_MH_UnderlineCheckBox->isChecked() );
	m_Prefs->SetFontPreference( item->text(), font );
	m_MH_PreviewLineEdit->setFont( font );
	RedrawPreviews();
}

void PreferencesDialog::mhColorButtonClickedSlot()
{
	Q3ListBoxItem* item = m_MH_ListBox->selectedItem();
	if( !item ) return;

	QColor color = GetColorPreference( m_Prefs, item->text() );

	color = QColorDialog::getColor(color);
	if( color.isValid() )
	{
		m_MH_PreviewLineEdit->setColor( color );
		m_Prefs->SetPreference( item->text() + "_Color", color.name() );
		RedrawPreviews();
	}
}


void PreferencesDialog::dsfFontButtonClickedSlot()
{    
	bool ok;
    QFont font = QFontDialog::getFont( &ok, m_Prefs->GetFontPreference( "Main" ) ),
		  temp;
    if ( ok ) {
        // font is set to the font the user selected
		m_Prefs->SetFontPreference( "Main", font );
		
		temp = m_Prefs->GetFontPreference( "Affix" );
		temp.setFamily( font.family() );
		temp.setPointSize( font.pointSize() );
		m_Prefs->SetFontPreference( "Affix", temp );

		temp = m_Prefs->GetFontPreference( "Signature" );
		temp.setFamily( font.family() );
		temp.setPointSize( font.pointSize() );
		m_Prefs->SetFontPreference( "Signature", temp );
		
		temp = m_Prefs->GetFontPreference( "Stem" );
		temp.setFamily( font.family() );
		temp.setPointSize( font.pointSize() );
		m_Prefs->SetFontPreference( "Stem", temp );

		temp = m_Prefs->GetFontPreference( "Word" );
		temp.setFamily( font.family() );
		temp.setPointSize( font.pointSize() );
		m_Prefs->SetFontPreference( "Word", temp );

		temp = m_Prefs->GetFontPreference( "Error" );
		temp.setFamily( font.family() );
		temp.setPointSize( font.pointSize() );
		m_Prefs->SetFontPreference( "Error", temp );
		
		((LinguisticaMainWindow*)parent())->SetEastFont( font );
		m_DSF_PreviewLineEdit->setFont( font );
		RedrawPreviews();
	}
	else
	{
        // the user canceled the dialog; font is set to the initial
    }
}


void PreferencesDialog::loadPrefsButtonClickedSlot()
{
	QSettings& settings =
		*static_cast<LinguisticaMainWindow*>(parent())
		->GetSettings();

	const QString lastfile =
		settings.readEntry(
			"/linguistica.uchicago.edu/Linguistica/PreferencesFileName",
			QString());
	// Dialog for preferences file
	const QString filename =
		QFileDialog::getOpenFileName(lastfile,
			"Text Files( *.txt );;"
			"Rich Text Files( *.rtf );;"
			"All Files( *.* )");
	if (filename.isEmpty())
		return;
	if (filename != lastfile)
		settings.writeEntry(
			"/linguistica.uchicago.edu/Linguistica/PreferencesFileName",
			filename);

	m_Prefs->load_prefs_from_file(filename);
	init();
}

// XXX. refactor to share code with loadPrefsButtonClickedSlot()
void PreferencesDialog::savePrefsButtonClickedSlot()
{
	QSettings& settings =
		*static_cast<LinguisticaMainWindow*>(parent())
		->GetSettings();
	const QString lastfile =
		settings.readEntry(
			"/linguistica.uchicago.edu/Linguistica/PreferencesFileName",
			QString());
	const QString filename =
		QFileDialog::getSaveFileName(lastfile,
			"Text Files( *.txt );;"
			"Rich Text Files( *.rtf );;"
			"All Files( *.* )",
			this,
			"Choose a file name to save under");
	if (filename.isEmpty())
		return;
	if (filename != lastfile)
		settings.writeEntry(
			"/linguistica.uchicago.edu/Linguistica/PreferencesFileName",
			filename);
	m_Prefs->store_prefs_to_file(filename);
}

void PreferencesDialog::notificationsCheckBoxClickedSlot()
{
	m_Prefs->SetPreference( "Notifications", QString("%1").arg( m_NotificationsCheckBox->isChecked() ) );}


void PreferencesDialog::sigDelimiterChangedSlot( const QString& delimiter )
{
	m_Prefs->SetPreference( "Sig_Delimiter", delimiter.stripWhiteSpace() );
}


void PreferencesDialog::resetValuePushButtonClickedSlot()
{
	Q3ListViewItem* item	= m_paramListView->selectedItem();
	if( item )
	{
		Q3ListViewItem* parent	= item->parent();

		QString key = item->text(0), 
				value;
		if( parent ) key = parent->text(0) + "\\" + key;

		StringToString::Iterator it = m_DefaultParams->find(key);
		if( it != m_DefaultParams->end() )
		{
			value = it.data();
			item->setText( 1, value );
			paramListItemRenamedSlot(item, 1, value);
		}
	}
}


void PreferencesDialog::resetAllValsPushButtonClickedSlot()
{
	m_Prefs->SetDictionaryPreference("Lxa_Parameters", *m_DefaultParams);
	initParams();
}

void PreferencesDialog::paramListItemRenamedSlot(Q3ListViewItem* item,
		int /* column */, const QString& value)
{
	QMap<QString, QString> dict;
	m_Prefs->GetDictionaryPreference("Lxa_Parameters", &dict);

	Q3ListViewItem* parent = item->parent();

	QString key;
	if (parent) {
		key.append(parent->text(0));
		key.append('\\');
	}
	key.append(item->text(0));
	dict.replace(key, value);

	m_Prefs->SetDictionaryPreference("Lxa_Parameters", dict);
}

void PreferencesDialog::help()
{
	Q3WhatsThis::enterWhatsThisMode();
}


void PreferencesDialog::makeLowerCaseCheckBoxToggled(bool b)
{
	if( b )
	{		
		m_scrubListBox->insertItem( SCR_MAKE_LOWER_CASE );
	}
	else
	{
		m_scrubListBox->removeItem( m_scrubListBox->index( m_scrubListBox->findItem( SCR_MAKE_LOWER_CASE ) ) );
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::removeNumbersCheckBoxToggled(bool b)
{
	if( b )
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_NUMBERS ) ) < 0 );
		
		m_scrubListBox->insertItem( SCR_REMOVE_NUMBERS );
	}
	else
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_NUMBERS ) ) >= 0 );

		m_scrubListBox->removeItem( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_NUMBERS ) ) );
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::removePrecedingPunctCheckBoxToggled(bool b)
{
	m_precedingPunctLineEdit->setEnabled(b); 
		
	if( b )
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_PRECEDING_PUNCT ) ) < 0 );
		
		m_scrubListBox->insertItem( SCR_REMOVE_PRECEDING_PUNCT );
	}
	else
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_PRECEDING_PUNCT ) ) >= 0 );

		m_scrubListBox->removeItem( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_PRECEDING_PUNCT ) ) );
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::removeInternalPunctCheckBoxToggled(bool b)
{
	m_internalPunctLineEdit->setEnabled(b);
		
	if( b )
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_INTERNAL_PUNCT ) ) < 0 );
		
		m_scrubListBox->insertItem( SCR_REMOVE_INTERNAL_PUNCT );
	}
	else
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_INTERNAL_PUNCT ) ) >= 0 );

		m_scrubListBox->removeItem( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_INTERNAL_PUNCT ) ) );
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::removeFollowingPunctCheckBoxToggled(bool b)
{
	m_followingPunctLineEdit->setEnabled(b);
		
	if( b )
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_FOLLOWING_PUNCT ) ) < 0 );
		
		m_scrubListBox->insertItem( SCR_REMOVE_FOLLOWING_PUNCT );
	}
	else
	{
		Q_ASSERT( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_FOLLOWING_PUNCT ) ) >= 0 );

		m_scrubListBox->removeItem( m_scrubListBox->index( m_scrubListBox->findItem( SCR_REMOVE_FOLLOWING_PUNCT ) ) );
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::addNewReplacementButtonPressed()
{
	QString replace = m_replaceLineEdit->text();
	QString with = m_withLineEdit->text();
	QString replacement = replace + " --> " + with;

	if( !replace.isEmpty() )
	{
		if( !(*m_replacements)[ replace ].isEmpty() )
		{
			QMessageBox::information( this, 
									  "Alchemist",
									  "This replacement will not be added. Each regular expression \n"
									  "may only be replaced by one string. The regular expression \n"
									  "already exists." );
			return;
		}
		if( static_cast <int> ( m_replacements->count() ) > MAX_REPLACEMENTS )
		{
			QString message = "This replacement will not be added. The maximum number of\nadvanced replacements allowed is %1.";
			QMessageBox::information( this, 
									  "Alchemist",
									  message.arg( MAX_REPLACEMENTS ) );
			return;
		}

		m_scrubListBox->insertItem( replacement );
		m_replacements->replace( replace, with );
	}

	m_replaceLineEdit->setText("");
	m_withLineEdit->setText("");

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::moveUpButtonPressed()
{
	Q3ListBoxItem* item = m_scrubListBox->item(0),
				* next;

	while( item )
	{
		next = item->next();

		if( item->isSelected() ) 
		{
			if( item->prev() && !item->prev()->isSelected() )
			{
				int index = m_scrubListBox->index( item );

				m_scrubListBox->insertItem( item->text(), index - 1 );
				m_scrubListBox->removeItem( index + 1 );
				m_scrubListBox->setSelected( index - 1, TRUE );
			}
		}

		item = next;
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );	
}


void PreferencesDialog::moveDownButtonPressed()
{
	Q3ListBoxItem* item = m_scrubListBox->item( m_scrubListBox->count()-1 ),
				* prev;

	while( item )
	{
		prev = item->prev();

		if( item->isSelected() ) 
		{
			if( item->next() && !item->next()->isSelected() )
			{
				int index = m_scrubListBox->index( item );

				m_scrubListBox->insertItem( item->text(), index + 2 );
				m_scrubListBox->removeItem( index );
				m_scrubListBox->setSelected( index + 1, TRUE );
			}
		}

		item = prev;
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::removeReplacementButtonPressed()
{
	Q3PtrList<Q3ListBoxItem> selected;

	Q3ListBoxItem* item = m_scrubListBox->item(0);

	while( item )
	{
		if( item->isSelected() ) selected.append( item );
		item = item->next();
	}

    for ( item = selected.first(); item; item = selected.next() )
	{
		if( item->text() == SCR_MAKE_LOWER_CASE ) m_makeLowerCaseCheckBox->toggle();
		else if( item->text() == SCR_REMOVE_NUMBERS ) m_removeNumbersCheckBox->toggle();
		else if( item->text() == SCR_REMOVE_PRECEDING_PUNCT ) m_removePrecedingPunctCheckBox->toggle();
		else if( item->text() == SCR_REMOVE_INTERNAL_PUNCT ) m_removeInternalPunctCheckBox->toggle();
		else if( item->text() == SCR_REMOVE_FOLLOWING_PUNCT ) m_removeFollowingPunctCheckBox->toggle();
        else 
		{
			int arrow = item->text().findRev( " --> " );
			if( arrow >= 0 ) m_replacements->remove( item->text().left( arrow ) );

			m_scrubListBox->removeItem( m_scrubListBox->index( item ) );
		}
	}

	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::replaceStringsChanged()
{
	if( m_replaceLineEdit->text().isEmpty() ) 
	{
		m_addButton->setEnabled( FALSE );
	}
	else 
	{
		m_addButton->setEnabled( TRUE );
	}
}


void PreferencesDialog::scrubListBoxSelectionChanged()
{
	Q3PtrList<Q3ListBoxItem> selected;

	Q3ListBoxItem* item = m_scrubListBox->item(0);

	while( item )
	{
		if( item->isSelected() ) selected.append( item );
		item = item->next();
	}

	if( selected.count() )
	{
		m_moveUpButton->setEnabled( TRUE );
		m_moveDownButton->setEnabled( TRUE );
		m_removeButton->setEnabled( TRUE );
	}
	else
	{
		m_moveUpButton->setEnabled( FALSE );
		m_moveDownButton->setEnabled( FALSE );
		m_removeButton->setEnabled( FALSE );
	}
}


void PreferencesDialog::precedingPunctLineEditTextChanged(const QString& s)
{

	QString temp = s; //just to avoid warning. fix.
	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
}


void PreferencesDialog::internalPunctLineEditTextChanged(const QString& s)
{
	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
	QString temp = s; //just to avoid warning. fix.
}


void PreferencesDialog::followingPunctLineEditTextChanged(const QString& s)
{
	SaveScrubRulesToPreferences( this, m_Prefs, m_initialized );
	QString temp = s; //just to avoid warning. fix.
}


void PreferencesDialog::importRulesButtonClickedSlot()
{
	// Get the last file name used
	QSettings* settings = ((LinguisticaMainWindow*)parent())->GetSettings();
	QString loadFileName = settings->readEntry( "/linguistica.uchicago.edu/Linguistica/Scrubbing/File", QString::null );
	
	loadFileName = Q3FileDialog::getOpenFileName( loadFileName,
												 "Text Files (*.txt);;Rich Text Files (*.rtf);;All Files (*)",
												 this,
												 "load scrub file dialog",
												 "Choose a scrub file to load" );
												 
	if( !loadFileName.isEmpty() )
	{ 	
		QFile file( loadFileName );
		QString scrubExp; // Scrub expression

		if ( file.open( QIODevice::ReadOnly ) )
		{
			settings->writeEntry( "/linguistica.uchicago.edu/Linguistica/Scrubbing/File", loadFileName );

        	Q3TextStream stream( &file );
		 	stream.setEncoding( Q3TextStream::Locale );


			m_scrubListBox->clear();
			m_replacements->clear();

			while( !stream.atEnd() )
    		{				
      			scrubExp = stream.readLine();

				if( scrubExp == SCR_MAKE_LOWER_CASE ) m_makeLowerCaseCheckBox->setChecked( TRUE );
				else if( scrubExp == SCR_REMOVE_NUMBERS ) m_removeNumbersCheckBox->setChecked( TRUE );
				else if( scrubExp == SCR_REMOVE_PRECEDING_PUNCT ) 
				{
					m_removePrecedingPunctCheckBox->setChecked( TRUE );
					m_precedingPunctLineEdit->setText( stream.readLine() );
				}
				else if( scrubExp == SCR_REMOVE_INTERNAL_PUNCT ) 
				{
					m_removeInternalPunctCheckBox->setChecked( TRUE );
					m_internalPunctLineEdit->setText( stream.readLine() );
				}
				else if( scrubExp == SCR_REMOVE_FOLLOWING_PUNCT )
				{
					m_removeFollowingPunctCheckBox->setChecked( TRUE );
					m_followingPunctLineEdit->setText( stream.readLine() );
				}
				else
				{
					int arrow = scrubExp.findRev( " --> " );
					if( arrow >= 0 )
					{
						QString replace = scrubExp.left( arrow );
						QString with = scrubExp.right( scrubExp.length() - arrow - 5 );
						m_replacements->replace( replace, with );
					}
				}

				

				if( !m_scrubListBox->findItem( scrubExp ) ) m_scrubListBox->insertItem( scrubExp );
			}			

			file.close();			 
		}
	}

	m_Prefs->SetDictionaryPreference("Scrub_Replacements", *m_replacements);
}


void PreferencesDialog::exportRulesButtonClickedSlot()
{
	// Get the save file name
	QSettings* settings = ((LinguisticaMainWindow*)parent())->GetSettings();
	QString saveFileName = settings->readEntry( "/linguistica.uchicago.edu/Linguistica/Scrubbing/File", QString::null );

	saveFileName = Q3FileDialog::getSaveFileName( saveFileName,
												 "Text Files (*.txt);;Rich Text Files (*.rtf);;All Files (*)",
												 this,
												 "save scrub file dialog",
												 "Choose a filename to save the scrub file under" );
  
	if( !saveFileName.isEmpty() ) 
	{
		QFile file( saveFileName );

		if ( file.open( QIODevice::WriteOnly ) )
		{
			settings->writeEntry( "/linguistica.uchicago.edu/Linguistica/Scrubbing/File", saveFileName );

        	Q3TextStream stream( &file );
		 	stream.setEncoding( Q3TextStream::Unicode );

			Q3ListBoxItem* item = m_scrubListBox->item(0);

			while( item )
    		{				
      			stream << item->text();

				if( item->text() == SCR_REMOVE_PRECEDING_PUNCT ) stream << "\n" << m_precedingPunctLineEdit->text();
				else if( item->text() == SCR_REMOVE_INTERNAL_PUNCT ) stream << "\n" << m_internalPunctLineEdit->text();
				else if( item->text() == SCR_REMOVE_FOLLOWING_PUNCT ) stream << "\n" << m_followingPunctLineEdit->text();

				stream << "\n";

				item = item->next();
			}			

			file.close();			 
		}
	}
}


void PreferencesDialog::removeComboButtonClickedSlot()
{
	Q3PtrList<Q3ListBoxItem> selected;
	QStringList not_removed;

	Q3ListBoxItem* item = m_CC_ListBox->item(0);

	while( item )
	{
		if( item->isSelected() ) selected.append( item );
		else
		{
			not_removed << item->text();
		}
		item = item->next();
	}

    for ( item = selected.first(); item; item = selected.next() )
	{
		m_CC_ListBox->removeItem( m_CC_ListBox->index( item ) );
	}

	m_Prefs->SetStringListPreference("Character_Combinations",
				not_removed);
}


void PreferencesDialog::newComboButtonClickedSlot()
{
	bool ok;
	QString label =	"Enter a character combination with length greater than one and no white space.\n";
	label +=		"A single character will be substituted for the combination during analysis and\n";
	label +=		"the combination will be replaced during output.\n";
    QString text = QInputDialog::getText( "Linguistica", 
										  label, 
										  QLineEdit::Normal,
										  QString::null, &ok, this );
    if ( ok && !text.isEmpty() )
	{
		QRegExp whitespace( "\\s" );
        if( text.find( whitespace ) >= 0 ) 
		{
			QMessageBox::information( this, 
									  "Linguistica",
									  "The character combination cannot include whitespace.\n" );
			return;
		}
		if( m_CC_ListBox->findItem( text ) )
		{
			QMessageBox::information( this, 
									  "Linguistica",
									  "This character combination already exists in the list.\n" );
			return;
		}
		
		m_CC_ListBox->insertItem( text );
		
		QStringList allCombos;

		Q3ListBoxItem* item = m_CC_ListBox->item(0);

		while( item )
		{
			allCombos << item->text();
			item = item->next();
		}

		m_Prefs->SetStringListPreference("Character_Combinations",
				allCombos);
    }
}


void PreferencesDialog::comboListBoxSelectionChangedSlot()
{
	Q3PtrList<Q3ListBoxItem> selected;

	Q3ListBoxItem* item = m_CC_ListBox->item(0);

	while( item )
	{
		if( item->isSelected() ) selected.append( item );
		item = item->next();
	}

	if( selected.count() )
	{
		m_CC_RemoveButton->setEnabled( TRUE );
	}
	else
	{
		m_CC_RemoveButton->setEnabled( FALSE );
	}
}


void PreferencesDialog::joinWithoutDashRadioButtonClickedSlot()
{
	m_Prefs->SetPreference( "Line_Final_Dash", "Join_Without_Dash" );
}


void PreferencesDialog::joinWithDashRadioButtonClickedSlot()
{
	m_Prefs->SetPreference( "Line_Final_Dash", "Join_With_Dash" );
}


void PreferencesDialog::doNotJoinRadioButtonClickedSlot()
{
	m_Prefs->SetPreference( "Line_Final_Dash", "Do_Not_Join" );
}


void PreferencesDialog::removeHyphenCheckBoxClickedSlot()
{
	switch( m_removeHyphenCheckBox->checkState() )
	{
	case Qt::Checked:
		m_Prefs->SetPreference( "Word_Internal_Dash", "Remove" );
		break;
	case Qt::Unchecked:
		m_Prefs->SetPreference( "Word_Internal_Dash", "Do_Not_Remove" );
		break;
	case Qt::PartiallyChecked:
	default:
		break;
	}
}


void PreferencesDialog::includeFullHyphenatedWordOnlyRadioButtonClickedSlot()
{
	m_Prefs->SetPreference( "Word_With_Dash", "Include_Full_Word_Only" );
}


void PreferencesDialog::includeSubstringsOfHyphenatedWordOnlyRadioButtonClickedSlot()
{
	m_Prefs->SetPreference( "Word_With_Dash", "Include_Substrings_Only" );
}


void PreferencesDialog::includeFullHyphenatedWordAndSubstringsRadioButtonClickedSlot()
{
	m_Prefs->SetPreference( "Word_With_Dash", "Include_Full_Word_And_Substrings" );
}

