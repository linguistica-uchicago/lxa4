// Suffix type with corpus count for suffix/signature-based morphology discovery
// Copyright © 2009 The University of Chicago
#ifndef SUFFIX_H
#define SUFFIX_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.
// See also the very similar CPrefix class.

class CSuffix;

#include "Affix.h"

// XXX. we should avoid implicit instantiation of
// affix_list_view_item<CSuffix>, but swig can’t handle the
// appropriate declaration.  (See Prefix.h for details.)

/// A list view item for suffixes.
/**
	Contains all the necessary variables needed when displaying a 
	prefix and its data in a list view.
 */
typedef linguistica::affix_list_view_item<CSuffix> CSuffixListViewItem;

/// A string represention of suffixes.
/**
	This class is a string representation of prefixes.
 */

class CSuffix : public CAffix  
{
  

protected:
	//--------------------------------------------------
	// Protected member variables
	//--------------------------------------------------

	ePOS		m_POS;

public:

	//--------------------------------------------------
	// Constructors/Destructor
	//--------------------------------------------------

	CSuffix ( class CMiniLexicon* mini = NULL );
	CSuffix (const CStringSurrogate&, class CMiniLexicon* mini = NULL );
	virtual ~CSuffix();

	//--------------------------------------------------
	// Public accessor methods
	//--------------------------------------------------

	virtual eLxaClass	        GetType				(	) const { return SUFFIX_CLASS; }
	void				ListDisplay			( class Q3ListView*, StringToString* = NULL, bool b = true, int char_count = 27 );
	ePOS				GetPOS				(	) const { return m_POS; }
	void				MergeMeWithMyStems	( class CMiniLexicon* );
	CParse&				Express				( CParse&, bool bDisplayDeletees = TRUE ); // march 2004 jg
	void				OutputSuffix		( class Q3TextStream& );
    QString             DisplaySuffix       ( bool ExpressDeletees = TRUE );

	//--------------------------------------------------
	// Public mutator methods
	//--------------------------------------------------

	// TODO: need some sort of set deletees method
	void				SetPOS (ePOS e)				{ m_POS = e; }



};

#endif // SUFFIX_H
