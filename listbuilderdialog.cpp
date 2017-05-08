// Generic two-paned included/excluded list dialog
// Copyright © 2009 The University of Chicago
#include "listbuilderdialog.h"

ListBuilderDialog::ListBuilderDialog( QString caption,
				QStringList& notIncluded, QStringList& included,
				QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, 0, false, fl ), Ui::ListBuilderDialogBase()
{
	setupUi( this );

	setCaption( caption );
	m_NotIncluded->insertStringList( notIncluded );
	m_Included->insertStringList( included );
}


void ListBuilderDialog::addListItemSlot( Q3ListViewItem* )
{
}


void ListBuilderDialog::addListItemSlot()
{
  m_Included->insertItem( m_NotIncluded->currentText() );
  m_NotIncluded->removeItem( m_NotIncluded->currentItem() );
}


void ListBuilderDialog::removeListItemSlot( Q3ListViewItem* )
{
}


void ListBuilderDialog::removeListItemSlot()
{
  m_NotIncluded->insertItem( m_Included->currentText() );
  m_Included->removeItem( m_Included->currentItem() );
}
