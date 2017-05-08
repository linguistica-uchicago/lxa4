// Implementation of LxPoSCollection methods
// Copyright © 2009 The University of Chicago
#include "POSCollection.h"

namespace {
        typedef Q3PtrList<LxPoS> base;
}

LxPoSCollection::LxPoSCollection() : base()
{ base::setAutoDelete(true); }

LxPoSCollection::~LxPoSCollection() { }

void LxPoSCollection::ListDisplay(Q3ListView* pView)
{
	pView->setRootIsDecorated(false);
	pView->setSorting(1);

	// Remove all previous columns
	while (pView->columns() != 0)
		pView->removeColumn(0);

	// Add Column headers
	pView->addColumn("POS Signatures");
	pView->addColumn("Robustness");
	pView->hideColumn(1);  // Not needed in this view
	// XXX. more columns:
//	pView->addColumn("Exemplar");
//	pView->addColumn("Descr. Length");
//	pView->addColumn("Corpus Count");
//	pView->addColumn("Stem Count");
//	pView->addColumn("Remarks");
//	pView->addColumn("Sort Alphabetically");

	// Display each item
	foreach (LxPoS* pPoS, *this) {
		pPoS->SortByValue();
		pPoS->ListDisplay(pView, pPoS->Display('.'));
	}
}
