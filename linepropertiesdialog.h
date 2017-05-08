// “Line properties” dialog from old FSA code
// Copyright © 2009 The University of Chicago
#ifndef LINEPROPERTIESDIALOG_H
#define LINEPROPERTIESDIALOG_H

#include <QDialog>
#include "ui_linepropertiesdialogbase.h"

#include <Qt>

class LinePropertiesDialog : public QDialog, private Ui::LinePropertiesDialogBase
{
    Q_OBJECT
public:
	LinePropertiesDialog( QWidget* parent = 0, Qt::WindowFlags fl = 0 );

public slots:
	void exec( Q3CanvasItem* item );
};

#endif // LINEPROPERTIESDIALOG_H
