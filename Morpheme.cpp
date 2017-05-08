// Implementation of CMorpheme, CMorphemeListViewItem methods
// Copyright © 2009 The University of Chicago
#include "Morpheme.h"

#include <cmath>
#include <QString>
#include "MorphemeCollection.h"
#include "log2.h"

CMorphemeListViewItem::CMorphemeListViewItem( Q3ListView *parent, 
									  QString label1, 
									  CMorpheme* morpheme )
: Q3ListViewItem( parent, label1 )
{
	m_morpheme = morpheme; 
}

QString CMorphemeListViewItem::key( int column, bool ascending ) const
{
	if( m_morpheme )
	{
		QString string = "";
		switch( column )
		{
		case 1:
			string = QString("%1").arg( m_morpheme->GetILogProb(), 10 );
			return string;
		case 2:
			string = QString("%1").arg( m_morpheme->GetMorphemeCount(), 10 );
			return string;
		case 3:
			string = QString("%1").arg( m_morpheme->GetCorpusCount(), 10 );
			return string;
		case 4:
			string = QString("%1").arg( m_morpheme->GetPF(), 10 );
			return string;
		case 5:
			string = QString("%1").arg( m_morpheme->GetSF(), 10 );
			return string;
		case 6:
			string = QString("%1").arg( m_morpheme->GetSortingQuantity(), 10 );
			return string;
		case 7:
			string = QString("%1").arg( m_morpheme->GetDLSavings(), 10 );
			return string;
		case 8:
			string = QString("%1").arg( m_morpheme->GetFrequency(), 10 );
			return string;
		case 9:
			string = m_morpheme->GetSuffixList()->Display('.');
			return string;
		default:
			return Q3ListViewItem::key( column, ascending );
		}
	}
	else return Q3ListViewItem::key( column, ascending );
}

QString CMorphemeListViewItem::text( int column ) const
{
	if( m_morpheme )
	{
		QString string = "";
		switch( column )
		{
		case 1:
			string = QString("%1").arg( m_morpheme->GetILogProb() );
			return string;
		case 2:
			string = QString("%1").arg( m_morpheme->GetMorphemeCount() );
			return string;
		case 3:
			string = QString("%1").arg( m_morpheme->GetCorpusCount() );
			return string;
		case 4:
			string = QString("%1").arg( m_morpheme->GetPF() );
			return string;
		case 5:
			string = QString("%1").arg( m_morpheme->GetSF() );
			return string;
		case 6:
			string = QString("%1").arg( m_morpheme->GetSortingQuantity() );
			return string;
		case 7:
			string = QString("%1").arg( m_morpheme->GetDLSavings() );
			return string;
		case 8:
			string = QString("%1").arg( m_morpheme->GetFrequency() );
			return string;
		case 9:
			string = m_morpheme->GetSuffixList()->Display('.');
			return string;
		default:
			return Q3ListViewItem::text( column );
		}
	}
	else return Q3ListViewItem::text( column );
}



CMorpheme::CMorpheme(CMiniLexicon* lex): CLParse(lex) 
{


}
CMorpheme::CMorpheme(CMorpheme* RHS): CLParse(*RHS,RHS->GetMyMini()) 
{
	m_DLSavings = 0;
	m_DLImprovementFromSuffixes = 0;
	m_Frequency = 0;
	m_MorphemeCount = 0;
	m_ILogProb = 0;
	m_SF = 0;
	m_PF = 0;
}

CMorpheme::~CMorpheme()
{
	
	
}


CMorpheme::CMorpheme (CStringSurrogate SS, CMiniLexicon* mini): CLParse (SS,mini)
{
	m_DLSavings = 0;
	m_DLImprovementFromSuffixes = 0;
	m_SF = 0;
	m_PF = 0;
}

void CMorpheme::AddSuffix(CStringSurrogate SS)
{
//	if( m_SuffixList.GetSortStyle()  ) m_SuffixList.Alphabetize();
	m_SuffixList.Append( SS );
}

CParse* CMorpheme::GetSuffixList()
{
	return &m_SuffixList;
}

CParse* CMorpheme::GetPrefixList()
{
	return &m_PrefixList;
}

void	CMorpheme::AddPrefix(CStringSurrogate SS)
{
//	if( !m_PrefixList.Alphabetical() ) m_PrefixList.Alphabetize();
	m_PrefixList.Append( SS );
}


double	CMorpheme::GetILogProb() { return m_ILogProb; }

void	CMorpheme::SetILogProb( double d ) { m_ILogProb = d; }

void	CMorpheme::ListDisplay(Q3ListView* List)
{
	static_cast<void>(new CMorphemeListViewItem(
		List, Display(), this));
}

double CMorpheme::GetFrequency () { return m_Frequency; }

void	CMorpheme::SetFrequency( double f ) 
{ 
	m_Frequency = f; 
	m_ILogProb = -1 * base2log ( f );
}

void CMorpheme::SetDLSavings( double d) { m_DLSavings = d; }

double CMorpheme::GetDLSavings() { return m_DLSavings; }

void CMorpheme::AddSuffixes ( CMorphemeCollection* CMC )
{
	for (int i = 0; i < (int)CMC->GetCount(); i++)
		AddSuffix ( CMC->GetAt_SS(i) );
}
void CMorpheme::CopySuffixList (CMorpheme* Morpheme)
{
	m_SuffixList = Morpheme->GetSuffixList();
}



void		CMorpheme::SetDLImprovementFromSuffixes ( double d ) { m_DLImprovementFromSuffixes = d; }
double		CMorpheme::GetDLImprovementFromSuffixes () { return m_DLImprovementFromSuffixes ; }

void CMorpheme::IncrementMorphemeCount (double d) { m_MorphemeCount += d; } 
void CMorpheme::SetMorphemeCount( double d ) { m_MorphemeCount = d; }
double CMorpheme::GetMorphemeCount () { return m_MorphemeCount; }

float CMorpheme::GetSortingQuantity() const
{
	using std::log;
	return log(m_PF) * log(m_SF);
}
