// Prefix list for suffix/signature-based morphology discovery and display
// Copyright © 2009 The University of Chicago
#ifndef PREFIXCOLLECTION_H
#define PREFIXCOLLECTION_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.

#include "CollectionTemplate.h"

class LinguisticaMainWindow;

class CPrefix;

typedef QMap<uint,eLxaClass> PtrToClass;
typedef QMap<uint,uint>			PtrToPtr;

class CPrefixCollection: public TCollection<CPrefix>
{


public:
  CPrefixCollection (CMiniLexicon* Lex);
  CPrefixCollection();
  ~CPrefixCollection();
  
  void      ListDisplay( Q3ListView*, StringToString* = NULL );

  void      OutputPrefixes(QString);

  CPrefix*  operator<< ( CParse*  );
  CPrefix*  operator<< ( CStringSurrogate  );

	CPrefix*		operator<< ( QString );
	void			AddPointer( CPrefix* );
	CPrefix*		AddToCollection( CParse& );
	CPrefix*		AddToCollection( CStringSurrogate& );
	
	void			Empty();
	void			RemoveAll();
	bool			Remove( CPrefix* ); // doesn't delete CPrefix*
	bool			RemoveMember( CPrefix* ); // deletes CPrefix*
	bool			RemoveMember( CStringSurrogate& ); // deletes CPrefix*
	bool			RemoveMember( CStringSurrogate&, bool ); // FSA
	void			DeleteMarkedMembers();

  void      ReadPrefixFile (QString FileName);

  	/*	Description length				*/
	double			GetDL_PhonologicalContent();

};

#endif // PREFIXCOLLECTION_H
