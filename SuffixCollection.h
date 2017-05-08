// Suffix list for suffix/signature-based morphology discovery and display
// Copyright © 2009 The University of Chicago
#ifndef SUFFIXCOLLECTION_H
#define SUFFIXCOLLECTION_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.
// See also the very similar CPrefixCollection class.

#include "CollectionTemplate.h"
#include <q3listview.h>

class CSuffix;
class CSignatureCollection;

typedef QMap<uint,eLxaClass>	PtrToClass;
typedef QMap<uint,uint>			PtrToPtr;

class CSuffixCollection : public TCollection<CSuffix>
{
//	eMDL_STYLE_1	m_MDLStyle;						//corpus count or grammar count
	double			m_DLofPointersToMyMembers;
	

public:
	CSuffixCollection(CMiniLexicon*);
	CSuffixCollection();
	~CSuffixCollection();


	void			ListDisplay(Q3ListView*, 
								StringToString* = NULL, 
								bool b = true );

	void			OutputSuffixes		( QString );
	void			SortByIndex			( );
	void			ReadSuffixFile		( QString );

        int                     GetTotalUseCount ();
        void                    CalculateTotalUseCount();

	CSuffix*		operator<<			( CStringSurrogate& );
	CSuffix*		operator<<			( CParse* );
   	CSuffix*		operator<<			( CParse& );
	CSuffix*		operator<<			( QString );
	void			AddPointer			( CSuffix* );
	CSuffix*		AddToCollection		( CParse& );
	CSuffix*		AddToCollection		( CStringSurrogate& );
	
	void			Empty				( );
	void			RemoveAll			( );
	bool			Remove				( CSuffix* ); // doesn't delete CSuffix*
	bool			RemoveMember		( CSuffix* ); // deletes CSuffix*
	bool			RemoveMember		( CStringSurrogate& ); // deletes CSuffix*
	bool			RemoveMember		( CStringSurrogate&, bool ); // FSA
	void			DeleteMarkedMembers	( );

	/* Look for suffix combinations		*/

	void			FindCombinations	( CSignatureCollection* Signatures, CMiniLexicon* );
	void			FindFactorableSuffixes();
	
	/*	Description length				*/
	double			GetDL_PhonologicalContent();
	double			CalculatePointersToMySuffixes(eMDL_STYLE);
	
//	double			ComputeLengthOfPointersToEachOfMyMembers ();//computes and returns m_DLofPointersToMyMembers;
};

#endif // SUFFIXCOLLECTION_H
