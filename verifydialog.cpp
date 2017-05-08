// Implementation for simple yes/no dialog
// Copyright © 2009 The University of Chicago
#include "verifydialog.h"

#include "generaldefinitions.h"

VerifyDialog::VerifyDialog( QString msg, QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, 0, false, fl ), Ui::VerifyDialogBase()
{
	setupUi( this );
	m_textLabel->setText( msg );
}

void VerifyDialog::yesSlot()
{
	done( RESULT_YES );
}

void VerifyDialog::noSlot()
{
	done( RESULT_NO );
	
}

void VerifyDialog::cancelSlot()
{
	done( RESULT_CANCEL );	
}
