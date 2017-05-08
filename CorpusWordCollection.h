// Type of master corpus word list
// Copyright © 2009 The University of Chicago
#ifndef CORPUSWORDCOLLECTION_H
#define CORPUSWORDCOLLECTION_H

#include "CollectionTemplate.h"

class CCorpusWord;

class CCorpusWordCollection : public TCollection<CCorpusWord>
{

public:
	CCorpusWordCollection();
	CCorpusWordCollection(CLexicon*);

	virtual ~CCorpusWordCollection();

	void SetUpdateFlags( bool );
};

#endif // CORPUSWORDCOLLECTION_H
