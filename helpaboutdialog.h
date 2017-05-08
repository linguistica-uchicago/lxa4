// Help->About dialog
// Copyright © 2009 The University of Chicago
#ifndef HELPABOUTDIALOG_H
#define HELPABOUTDIALOG_H

#include <QDialog>
#include "ui_helpaboutdialogbase.h"

#include <Qt>

class HelpAboutDialog : public QDialog, private Ui::HelpAboutDialogBase
{
    Q_OBJECT

public:
	HelpAboutDialog( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
};

#endif // HELPABOUTDIALOG_H
