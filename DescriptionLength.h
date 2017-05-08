// Corpus and lexicon description length bookkeeping type
// Copyright © 2009 The University of Chicago
#ifndef DESCRIPTIONLENGTH_H
#define DESCRIPTIONLENGTH_H

#include <Q3ListViewItem>

#include "generaldefinitions.h"

class QString;

///////////////////////////////////////////////////////////////////////
//
//					Description Length
//.
///////////////////////////////////////////////////////////////////////



class CDescriptionLength 
{

protected: 
	class CMiniLexicon* m_MyMiniLexicon;
	class CLexicon* m_MyLexicon;
	eMDL_STYLE		m_MDLStyle;
	double			m_TotalDL;
 
	// Stems
	double 			m_NumberOfStems;
	double			m_StemsTotalPhonologicalInformationContent;
	double			m_SumOfPointersToMyStems_CorpusCount;
	double			m_SumOfPointersToMyStems_GrammarCount;

	// Unanalyzed words
	int 			m_NumberOfUnanalyzedWords;
	double			m_UnanalyzedWordsTotalPhonologicalInformationContent;
	double			m_SumOfPointersToMyUnanalyzedWords_CorpusCount;
	double			m_SumOfPointersToMyUnanalyzedWords_GrammarCount;

	// Analyzed words
	int				m_NumberOfAnalyzedWords;

	// Suffixes
	double			m_SuffixesTotalPhonologicalInformationContent;

	double			m_SumOfPointersToMySuffixes_CorpusCount;
	double			m_SumOfPointersToMySuffixes_GrammarCount;

	
	// Suffix signatures
	double			m_SumOfInformationContentOfPointersInMySuffixSignatures;
 	double			m_SumOfPointersToMySuffixSignatures_CorpusCount;
	double			m_SumOfPointersToMySuffixSignatures_GrammarCount;

	// Corpus
	double			m_CompressedLengthOfCorpus;
	double			m_CompressedLengthOfUnanalyzedWords;

public:
	CDescriptionLength( CMiniLexicon* );
	CDescriptionLength( CLexicon* );
	~CDescriptionLength();

 


	double		TotalDL											( );

	//			Stems
	double		GetStemsTotalPhonologicalInformationContent			(  );
	double		GetAffixesTotalPhonologicalInformationContent		(  );
 	double		GetSumOfPointersToMyStems						(  eMDL_STYLE Flag = CorpusCount);
	
//	double		GetUnanalyzedWordsTotalPhonologicalContent		(  eMDL_STYLE = CorpusCount);
//  'eMDL_STYLE' unused parameter
	double		GetUnanalyzedWordsTotalPhonologicalInformationContent		(  );

	double		GetSumOfPointersToMyUnanalyzedWords				(  eMDL_STYLE Flag = CorpusCount);
 
	//			Suffixes
	double		GetSuffixesTotalPhonologicalInformationContent	( );
 	double		GetSumOfPointersToMySuffixes					(eMDL_STYLE Flag = CorpusCount);

	//			Suffix signatures
	double		GetSumOfInformationContentOfPointersInMySuffixSignatures	();
 	double		GetSumOfPointersToMySuffixSignatures					(	eMDL_STYLE Flag = CorpusCount);

	//			Corpus
	double		GetCompressedLengthOfCorpus						();

	void		SetStemsTotalPhonologicalInformationContent				( double c ) { m_StemsTotalPhonologicalInformationContent = c; }
 	double		CalculateCompressedLengthOfCorpus				();


	// display

	void DescriptionLengthListDisplay(class Q3ListView* list);
};


///////////////////////////////////////////////////////////////////////
//
//					Description Length
//.
///////////////////////////////////////////////////////////////////////


class CDescriptionLengthListViewItem : public Q3ListViewItem
{
public:
	CDescriptionLengthListViewItem ( class Q3ListView* parent = NULL );
	CDescriptionLengthListViewItem ( class Q3ListView *parent,
							eDocumentType,
						    QString = QString::null,
						    CDescriptionLength * = NULL,
							int index = 0 );
	CDescriptionLengthListViewItem ( Q3ListViewItem *parent, 
							eDocumentType,
						    QString = QString::null,
						    CDescriptionLength * = NULL,
							int index = 0 );

	virtual QString				text ( int ) const;
	virtual QString key(int column, bool ascending) const;
	QString	 					GetSubstance					() const;
	eDocumentType				GetSpellOutType					() const	{ return m_SpellOutType;}
	QString						SpellOutType					() const; 
	QString						GetLengthOfPointersToMe			()  const;
	CDescriptionLength*			GetDL							()	const	{return m_DL; }
	QString						GetLengthOfInternalPointers		()	const;

protected:
	eDocumentType				m_SpellOutType; 
	CDescriptionLength*			m_DL;
	int							m_index;
};

#endif // DESCRIPTIONLENGTH_H
