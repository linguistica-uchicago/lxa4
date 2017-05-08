// Implementation of Help->About dialog
// Copyright © 2009 The University of Chicago
#include "helpaboutdialog.h"

#include <QWidget>
#include <Qt>
#include <QString>
#include "Version.h"

HelpAboutDialog::HelpAboutDialog( QWidget* parent, Qt::WindowFlags fl )
	: QDialog( parent, 0, false, fl ), Ui::HelpAboutDialogBase()
{
	setupUi( this );

	m_versionTextLabel->setText( "<h1><font face=\"Arial\">Linguistica " + QString(LXA_VERSION) + "</font></h1>" ); 
	setCaption( "About Linguistica " + QString(LXA_VERSION) );
}

