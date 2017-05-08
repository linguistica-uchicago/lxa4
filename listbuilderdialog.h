// Generic two-paned included/excluded list dialog
// Copyright © 2009 The University of Chicago
#ifndef LISTBUILDERDIALOG_H
#define LISTBUILDERDIALOG_H

#include <QDialog>
#include "ui_listbuilderdialogbase.h"

#include <Q3ListView>
#include <QStringList>
#include <QString>
#include <Qt>

class QListBox;

class ListBuilderDialog : public QDialog, private Ui::ListBuilderDialogBase
{
    Q_OBJECT

public:
	ListBuilderDialog( QString caption,
			QStringList& notIncluded, QStringList& included,
			QWidget* parent = 0, Qt::WindowFlags fl = 0 );

	Q3ListBox* GetNotIncluded() { return m_NotIncluded; }
	Q3ListBox* GetIncluded()    { return m_Included; }

public slots:
	void addListItemSlot( Q3ListViewItem* );
	void addListItemSlot();
	void removeListItemSlot( Q3ListViewItem* );
	void removeListItemSlot();
};

#endif // LISTBUILDERDIALOG_H
