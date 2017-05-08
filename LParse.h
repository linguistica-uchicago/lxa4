// Morpheme type
// Copyright © 2009 The University of Chicago
#ifndef LPARSE_H
#define LPARSE_H

#include "Parse.h"
#include "CorpusCount.h"

typedef QMap<uint,eLxaClass> PtrToClass;
typedef QMap<uint,uint> PtrToPtr;

class CMiniLexicon;

/// A subclass of CParse adapted for use in Linguistica.
/**
	A subclass of CParse with some additional, Linguistica specific members and methods. 
 */

class CLParse : public CParse, public linguistica::corpus_count {
protected:

	//--------------------------------------------------
	// Protected member variables
	//--------------------------------------------------

	bool			m_DoNotParse;		///< true if this CLParse should not be further parsed
	bool			m_DoomFlag;			///< true if this CLParse is to be destroyed
	int				m_Index;			///< this CLParse's position in parent collection
	int				m_SortIndex;		///< this CLParse's sorted position in parent collection
	CParse*			m_Trigrams;			///< list of trigrams in this CLParse
	QString			m_AlphabetizedForm; ///< string with all characters of this CLParse alphabetized
	CMiniLexicon*	m_pMyMini;			///< this CLParse's grandparent mini-lexicon



public:

	//--------------------------------------------------
	// Constructors/Destructor
	//--------------------------------------------------

	CLParse( CMiniLexicon* );
	CLParse( const QChar&, CMiniLexicon* );
	CLParse( const CParse*, CMiniLexicon* );
	CLParse( const CStringSurrogate&, CMiniLexicon*	);
	CLParse( CLParse& );
	CLParse( const CParse&, CMiniLexicon* );
	virtual ~CLParse();
	
	
	CLParse& operator=(const CLParse& other);


	//--------------------------------------------------
	// Public accessor methods
	//--------------------------------------------------


	virtual eLxaClass	GetType() const { return LPARSE_CLASS; }
	int					CompareTrigrams(CLParse&);
	QString				GetAlphabetizedForm() const { return m_AlphabetizedForm; }
	int					GetIndex() const		{ return m_Index; }
	CMiniLexicon*		GetMyMini() const		{ return m_pMyMini; }
	int					GetSortIndex() const	{ return m_SortIndex; }	
	virtual float		GetSortingQuantity() const	{ return 0.0; }	// TODO: Ask John
	virtual QString		GetSortingString()		{ return ""; }	// TODO: Ask John
	bool				IsDoomed() const		{ return m_DoomFlag; }	
	bool				MayBeParsed() const		{ return !m_DoNotParse; }


	//--------------------------------------------------
	// Public mutator methods
	//--------------------------------------------------

	void			CalculateTrigrams();
	void			DoNotParse(bool b = true)			{ m_DoNotParse = b; }
	void			Doomed(bool b = true)				{ m_DoomFlag = b; }
	CParse*			GetTrigrams();
	void			PrepareWordForInput(bool, QString);
	void			SetAlphabetizedForm(QString s)		{ m_AlphabetizedForm = s; }
	void			SetIndex (int n)					{ m_Index = n; }
	void			SetMyMini( CMiniLexicon* mini )		{ m_pMyMini = mini; }
	void			SetSortIndex(int n)					{ m_SortIndex = n; }
	void			SetTriGramsToNULL()					{ m_Trigrams = NULL; }

protected:
	virtual void SetLengthOfPieceVector( int i ) { m_LengthOfPieceVector = i; };
};

#endif // LPARSE_H
