// Analysis and number of occurences for a word in the corpus
// Copyright © 2009 The University of Chicago
#ifndef CORPUSWORD_H
#define CORPUSWORD_H

#include <q3ptrvector.h>

#include "LParse.h"

class CCompound;

// All corpus counts in a Linguistica session should be based on the counts
// of these and be retrievable from *CLexicon::m_pCorpusWords.
// The cuts in these words should be updated by the mini-lexica.
class CCorpusWord  : public CLParse
{

protected:

	//--------------------------------------------------
	// Protected member variables
	//--------------------------------------------------

	Q3PtrVector<CLParse>		m_morphemes;
	bool					m_updated;


public:

	//--------------------------------------------------
	// Constructors/Destructor
	//--------------------------------------------------

	CCorpusWord( CMiniLexicon* mini = NULL );
	CCorpusWord( const CStringSurrogate&, CMiniLexicon* mini = NULL );
	CCorpusWord( CCorpusWord& );
	CCorpusWord( const CLParse& );
	CCorpusWord( const CParse&, CMiniLexicon* mini = NULL );
	~CCorpusWord();


	//--------------------------------------------------
	// Overloaded operators
	//--------------------------------------------------

	void		operator= ( const CCorpusWord& );

	void		Copy( CCorpusWord& );


	//--------------------------------------------------
	// Public accessor methods
	//--------------------------------------------------

	virtual eLxaClass	GetType() const { return CORPUS_WORD_CLASS; }
	CLParse*			GetMorpheme(int) const;
	eLxaClass			GetMorphemeType(int) const;
	bool				IsUpdated() const { return m_updated; }


	//--------------------------------------------------
	// Public mutator methods
	//--------------------------------------------------
	
	void	CopyParseStructure( CCompound* );
	void	CutRightBeforeHere(int);
	void	InsertMorpheme( int, CLParse* );
	void	MergePieces(int);
	void	SetMorpheme( int, CLParse* );
	void	SetUpdated( bool b = TRUE ) { m_updated = b; }
	void	SimplifyParseStructure();

protected:
	virtual void SetLengthOfPieceVector(int i);
};

#endif // CORPUSWORD_H
