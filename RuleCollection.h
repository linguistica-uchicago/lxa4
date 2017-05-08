// CRuleCollection class
// Copyright © 2009 The University of Chicago
#ifndef RULECOLLECTION_H
#define RULECOLLECTION_H
 
class CRuleCollection;

#include "CollectionTemplate.h"
#include "Rule.h"

class CRuleCollection  : public TCollection < CRule >
{
public:
	CRuleCollection();
	CRuleCollection(class CLexicon*);
	virtual ~CRuleCollection();

	CRule*	operator<< ( CRule& );
//	CRule*	operator^= ( CString rule );
//	void	ReadRuleFile ( LPCTSTR );
//	void	Display(CMyCollectionView*);
};

#endif // RULECOLLECTION_H
