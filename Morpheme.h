// CMorpheme, CMorphemeListViewItem classes
// Copyright © 2009 The University of Chicago
#ifndef MORPHEME_H
#define MORPHEME_H

#include "LParse.h"
#include "SparseVector.h"
#include <q3listview.h>

class CMorpheme;

class MorphemeCount
{
	CMorpheme* Morpheme;
	double	   Frequency;

};

class CMorphemeListViewItem : public Q3ListViewItem {
	CMorpheme* m_morpheme;
public:
	explicit CMorphemeListViewItem(Q3ListView* parent = 0,
		QString text = QString(), CMorpheme* morphene = 0);

	// copy.

	CMorphemeListViewItem(const CMorphemeListViewItem& x)
		: Q3ListViewItem(x), m_morpheme(x.m_morpheme) { }
	CMorphemeListViewItem& operator=(const CMorphemeListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_morpheme = x.m_morpheme;
		return *this;
	}

	// Qt3 list view item interface.

	virtual QString text(int column_index) const;
	virtual QString key(int column, bool ascending) const;
};

class CMorpheme : public CLParse
{

	CParse		m_SuffixList;
	CParse		m_PrefixList;
	double		m_ILogProb;
	double		m_DLSavings;
	double		m_DLImprovementFromSuffixes; // this keeps track of how much improvement in Description Length
	double		m_Frequency;
	double		m_MorphemeCount;

public:	// fix that
	int			m_SF;
	int			m_PF;


public:
	CSparseVector m_PrecedingMorphemes;
	CSparseVector m_FollowingMorphemes;
	



	// arises from the suffixes that this morpheme makes possible.
	public:
	CMorpheme( CMiniLexicon* mini = NULL );
	CMorpheme(CMorpheme* );
	CMorpheme (CStringSurrogate, CMiniLexicon* mini = NULL );
	~CMorpheme();
	void 				AddSuffix				( CStringSurrogate );
	void				AddSuffixes				( CMorphemeCollection* );
	void				CopySuffixList			( CMorpheme* );
	CParse*				GetSuffixList			( );

	void 				AddPrefix				( CStringSurrogate );
	CParse*				GetPrefixList			(      );


	
	void				ListDisplay					( Q3ListView* );
	void				SetDLSavings			( double);
	double				GetDLSavings			(	);
	
	double			GetILogProb				( );
	void			SetILogProb				(double);

	void			SetDLImprovementFromSuffixes ( double );
	double			GetDLImprovementFromSuffixes ( );
	
	double			GetFrequency			( );
	void			SetFrequency			( double );

	void			SetMorphemeCount		( double ) ;
	double			GetMorphemeCount		( );
	void			IncrementMorphemeCount	( double );

	float GetSortingQuantity() const;
	int				GetPF		() const { return m_PF; }
	int				GetSF		() const { return m_SF; }

};

#endif // MORPHEME_H
