// Menu for forming a word in string alignment-based model of morphology
// Copyright © 2009 The University of Chicago
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>

#include "Stem.h"
#include "Typedefs.h"

class CAlignment;
enum eAffixationType;

template<class K, class V> class QMap;
typedef QMap<QString, class CParse*> StringToParse;
typedef QMap<QString, float> StringToFloat;
typedef QMap<QString, StringToFloat*> StringToStringToFloat;

/// this is a class for schemas -- a sequence of slots. Each column is a CParse.
class CTemplate : public CStem
{
friend class CTemplateListViewItem; 
friend class LinguisticaMainWindow;
friend class CTemplateCollection;
	int										m_NumberOfColumns;
	CParse**								m_Columns;
	mutable float m_WordsTotalComplexity; // total complexity of words without any analysis
	mutable float m_Complexity;
	//int										m_SortingComplexity; 
	int										m_TemplateNumber; 
	
	// Delete flag
	bool									m_IsDeleted; 

	mutable float m_CurrentSortComplexity;
	mutable float m_NewSortComplexity;
	int										m_ModifiedColumn; 	
	bool									m_IsNewAfterCollapse1; 
	int										m_StemColumnInCollapse1; 
	//WordsAndInt								m_AbsordedWords; 
	//TemplateAndWordsAndInt					m_AbsordedWordsFromEachTemplate;
	bool									m_SwitchOfSortingValue;




public:
	CTemplate (int NumberOfColumns);
	CTemplate ( CAlignment* );
	CTemplate ( CTemplate&);
	~CTemplate(void);

	int			GetNumberOfColumns () { return m_NumberOfColumns; }
	float ComputeWordsTotalComplexity() const;
	float		GetWordsTotalComplexity(); 
	float		GetComplexity() ;
	float ComputeComplexity() const;
	int			GetMaximumColumnHeight();
	void		operator= (CAlignment* );

	//void		Display ( CListCtrl& , int& LineNumber);
	QString		Display();
	QString		DisplayFirstLine();
	int			GetVerticalColumn();
	void		AddToColumn(CParse&, int n);
	void		AddToColumn ( CStringSurrogate&, int n);

	float GetSortingQuantity() const;
	double		GetTemplateSortingQuantity();
	CParse*		GetColumn(int n);
	void		GetWordsAndParses(StringToParse& OneWordAndParse);
	QString		GetEntry (int row, int column);
	void		AddAlignment( CAlignment*);
	int			GetNumberOfLetters();

	bool		ShouldConflate ( CTemplate*, int& conflatecolumn );
	void		ConflateWith ( CTemplate* pOther, int Column );
	bool		Readjust(class CTemplateCollection* , int MinCount = 2); // checks to see if letters should be moved from one column to the other
	void		ListDisplay(Q3ListView* list);

	void		AdjustMeByMovingCommonTailOrHead2(StringToFloat& , int , int , bool PrintChangedTemplates,\
													int , bool , StringToStringToFloat& , \
													float , float );


	void		SetSwitchOfSortingValue(bool value){m_SwitchOfSortingValue = value;};
	void		AdjustMeAfterAbsorb1(StringToInt& , bool , int , int);
	void		GetWordsFromTwoColums(StringToInt& , int );
	void		FindMorphemePrefixOrSuffixWithParadigmaticGraph(int, int , StringToFloat& , StringToStringToFloat& , float , float );
	float		GetRobustNessWithParadigmaticGraph(CParse& , StringToFloat& , StringToStringToFloat& , float , float );


	//void				OutputForFile (ofstream& );
	//eAffixationType		DetermineAffixationSide ();
	//void				AddToCollections (  eAffixationType ThisType, 
		//									CStemCollection* Stems, 
		//									CAffixCollection* Affixes, 
		//									CSignatureCollection* Signatures
		//								  );
	
};


class CTemplateListViewItem : public Q3ListViewItem {
protected:
	CTemplate* m_Template;
	int m_MaxMumShownMorphemes;
public:
	CTemplateListViewItem(Q3ListView* parent = 0,
		CTemplate* templ = 0, QString label = QString());
	CTemplateListViewItem(Q3ListViewItem* parent,
		CTemplate* templ, QString label);

	virtual QString text(int) const;
	virtual QString key(int, bool) const;

	CTemplate* GetTemplate() { return m_Template; }
};

#endif // TEMPLATE_H
