// Implementation of CTreeViewItem methods
// Copyright © 2009 The University of Chicago
#include "TreeViewItem.h"


CTreeViewItem::CTreeViewItem( Q3ListView *parent )
: Q3ListViewItem( parent )
{}


CTreeViewItem::CTreeViewItem( Q3ListView *parent, 
                QString label1,
                eDocumentType docType,
                int index )
: Q3ListViewItem( parent, label1 )
{
  m_docType = docType;
  m_Index = index;
}

CTreeViewItem::CTreeViewItem( Q3ListView *parent,
                Q3ListViewItem *after,
                QString label1,
                eDocumentType docType,
                int index )
: Q3ListViewItem( parent, after, label1 )
{
  m_docType = docType;
  m_Index = index;
}

CTreeViewItem::CTreeViewItem( Q3ListViewItem *parent,
                QString label1,
                eDocumentType docType,
                int index )
: Q3ListViewItem( parent, label1 )
{
  m_docType = docType;
  m_Index = index;
}

CTreeViewItem::CTreeViewItem( Q3ListViewItem *parent,
                Q3ListViewItem *after,
                QString label1,
                eDocumentType docType,
                int index )
: Q3ListViewItem( parent, after, label1 )
{
  m_docType = docType;
  m_Index = index;
}

eDocumentType CTreeViewItem::GetState()
{
  return m_docType;
}

void CTreeViewItem::SetState( eDocumentType docType )
{
  m_docType = docType;
}

int CTreeViewItem::GetIndex()
{
  return m_Index;
}

void CTreeViewItem::SetIndex( int index )
{
  m_Index = index;
}
