// Template list for string alignment-based morphology discovery and display
// Copyright © 2009 The University of Chicago
#ifndef TEMPLATECOLLECTION_H
#define TEMPLATECOLLECTION_H

#include "CollectionTemplate.h"
#include "Template.h"

#include <QString>
#include <QMap>

typedef QMap<QString, class CParse*> StringToParse;
typedef QMap<QString, int> StringToInt;
typedef QMap<QString, float> StringToFloat;
typedef QMap<QString, StringToFloat*> StringToStringToFloat;

class CTemplateCollection :
	public TCollection<CTemplate>
{
private:
	class CLexicon* m_lexicon;

	// Parsed Result
	StringToParse* m_AllWordsAndParses;

	float m_TotalGlobalStickNess;
	
	// Paragmatic Graph
	StringToStringToFloat					m_GlobalStickNess2; 
	StringToFloat							m_GlobalNodeStickNess2; 
	float									m_TotalGlobalStickNess2; 
	float									m_TotalWord2; 

	int										m_NumberOfDeletedTemplates;


public:
	
	CTemplateCollection(CLexicon* );
	~CTemplateCollection(void);
	
	CTemplate*			AddToCollection (CAlignment*);
	
	CTemplate*			AddTemplate( CTemplate*);
	CTemplate*			operator<< (CAlignment*);
	void				ListDisplay(Q3ListView* parent);
	void				CheckForConflations (CTemplateCollection* InputCollection);
	void				OutputTemplatesForGoldStand();
	StringToParse*		GetParsedResult() {return m_AllWordsAndParses;};
	//void				OutputTemplates ( LPCTSTR Filename);
	//void				ReadTemplateFile (LPCTSTR Filename);
	//void				SortTemplates (eSortStyle, int ColumnNumber );
	//void				FindPrefixingTemplates(CTemplateCollection* PrefixingTemplates);
	//eAffixationType		FindAffixationSide();
	//void				AddToCollections( CStemCollection* SuffixStems,
	//									  CStemCollection* PrefixStems,
	//									  CSuffixCollection* Suffixes,
	//									  CPrefixCollection* Prefixes,
	//									  CSignatureCollection* PrefixSignatures,
	//									  CSignatureCollection* SuffixSignatures );

    void                FindAllEditDistances(CLexicon*, CWordCollection* Words );
    
	// Transfer in Summer 2005
	void				UpdateGlobalStickNess2();
	void				AdjustTemplatesByMovingCommonTailOrHead2(int);
	bool				CollapseAlgorithm1(int );
	void				SetSwitchOfSortingValue(bool value);
	void				AbsorbWords1(int Loopi);
	bool OneParseContainAnother(class CParse*, class CParse*);
	void				FindMorphemePrefixOrSuffixWithParadigmaticGraph(int);

	// interface to MT 
	void CutMtCorpusWithMorphologyAnalyses(QString, QString,
				QMap<QString, class CStem*>&, int);
};

#endif // TEMPLATECOLLECTION_H
