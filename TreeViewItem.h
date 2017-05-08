// CTreeViewItem class
// Copyright © 2009 The University of Chicago
#ifndef TREEVIEWITEM_H
#define TREEVIEWITEM_H

#include <Q3ListViewItem>

#include <QString>
#include "generaldefinitions.h"

class CTreeViewItem : public Q3ListViewItem
{
public:
	CTreeViewItem( Q3ListView* parent = NULL );
	CTreeViewItem( Q3ListView *parent, 
				   QString = QString::null, 
				   eDocumentType = NO_DOC, 
				   int = -1 );

	CTreeViewItem( Q3ListView *parent,
				   Q3ListViewItem *after = 0,
				   QString = QString::null,
				   eDocumentType = NO_DOC, 
				   int = -1 );
	
	CTreeViewItem( Q3ListViewItem *parent, 
				   QString = QString::null, 
				   eDocumentType = NO_DOC, 
				   int = -1 );

	CTreeViewItem( Q3ListViewItem *parent,
				   Q3ListViewItem *after = 0,
				   QString = QString::null, 
				   eDocumentType = NO_DOC, 
				   int = -1 );

	eDocumentType GetState();
	void SetState(eDocumentType);

	int GetIndex();
	void SetIndex( int );

protected:
	eDocumentType m_docType;
	int m_Index;
};

#endif // TREEVIEWITEM_H
