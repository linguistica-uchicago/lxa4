// Compound and component lists for compound discovery
// Copyright © 2009 The University of Chicago
#ifndef COMPOUNDCOLLECTION_H
#define COMPOUNDCOLLECTION_H

#include "CollectionTemplate.h"
#include "Compound.h"
#include <QList>
class CCompound;
class CGrammarRule;

typedef QList<CStem*>			StemSet;
typedef QMap<uint,uint>			PtrToPtr;
typedef Q3PtrList<CGrammarRule>         RuleList;
typedef QMap<QString,RuleList>          RuleCollection;
typedef QMap<QString,StemSet*>          ComponentMap;
typedef TCollection<CStem>              ComponentCollection;

class CCompoundCollection : public TCollection<CCompound>
{

protected:

	double					m_ComponentCount;
	double					m_LinkerCount;
	ComponentMap            m_ComponentMap;
    ComponentCollection     m_Components;
	
public:
	CCompoundCollection( CLexicon* lexicon );
	CCompoundCollection( CMiniLexicon* lexicon = NULL );
	virtual	~CCompoundCollection();

	ComponentMap*           GetComponentMap()              { return &m_ComponentMap; }
    ComponentCollection*    GetComponents()                { return &m_Components;}
//	void	                ChooseParseByProbability();
	void	                FindMostProbableParse();
//	void	                OutputCompounds ( QString );


	void	                SetComponentCount( double d )  { m_ComponentCount = d; }
	void	                SetLinkerCount( double d )     { m_LinkerCount = d; }
	double	                GetComponentCount()            { return m_ComponentCount; }
	double	                GetLinkerCount()               { return m_LinkerCount; }
	void	                CheckAndRecount();
};

#endif // COMPOUNDCOLLECTION_H
