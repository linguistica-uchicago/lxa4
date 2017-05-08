// Record of compound interfixes in a corpus
// Copyright © 2009 The University of Chicago
#ifndef LINKERCOLLECTION_H
#define LINKERCOLLECTION_H

// See the CLexicon class in Lexicon.h for an overview of compound discovery.

#include "CollectionTemplate.h"
#include <q3listview.h>

class CLinker;

class CLinkerCollection : public TCollection<CLinker> {
public:
	CLinkerCollection();
	CLinkerCollection(CLexicon*);
	CLinkerCollection(CMiniLexicon*);
	virtual ~CLinkerCollection();

	void ListDisplay(Q3ListView* parent,
		QMap<QString, QString>* filter = 0);

	void SortByIndex();
	int GetTotalUseCount();
};

#endif // LINKERCOLLECTION_H
