// Prefix type with corpus count for suffix/signature-based morphology discovery
// Copyright © 2009 The University of Chicago
#ifndef PREFIX_H
#define PREFIX_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.

class CPrefix;

#include "Affix.h"

// XXX. affix_list_view_item<CPrefix> is explicitly instantiated
// in Prefix.cpp, so we should avoid instantiating it automatically
// in other translation units:

//extern template class linguistica::affix_list_view_item<CPrefix>;

// but swig cannot handle the "extern template" declaration, so we
// skip it.  Luckily for us, affix_list_view_item<CPrefix> is not
// used in Suffix.cpp, the only other translation unit that
// includes affix_list_view_item.tcc, so even without the "extern
// template" declaration the methods happen to be instantiated only
// once.

/// A list view item for prefixes.
/**
	Contains all the necessary variables needed when displaying a 
	prefix and its data in a list view.
 */
typedef linguistica::affix_list_view_item<CPrefix> CPrefixListViewItem;

/// A string represention of prefixes.
/**
	This class is a string representation of prefixes.
 */

class CPrefix : public CAffix
{
  
public:

  //--------------------------------------------------
  // Constructors/Destructor
  //--------------------------------------------------

  CPrefix ( class CMiniLexicon* mini = NULL );
//  CPrefix (const QString);
  CPrefix (const CStringSurrogate&, class CMiniLexicon* mini = NULL );
  virtual ~CPrefix();


  //--------------------------------------------------
  // Public accessor methods
  //--------------------------------------------------

  virtual eLxaClass		GetType() const { return PREFIX_CLASS; }
  void        ListDisplay(class Q3ListView*, StringToString* = NULL, int char_count = 27 );
  CParse&     Express( CParse& Output, bool DisplayDeletees = true );
	void		OutputPrefix( class Q3TextStream& );
  QString     ExpressPrefix ();

	//--------------------------------------------------
	// Public mutator methods
	//--------------------------------------------------

	void        MergeMeWithMyStems ( class CMiniLexicon* );
	virtual double GetLengthOfPointerToMe();
};

#endif // PREFIX_H
