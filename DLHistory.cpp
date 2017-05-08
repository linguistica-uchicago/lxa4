// Implementation of description length history display
// Copyright © 2009 The University of Chicago
#include "DLHistory.h"

#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Prefix.h"
#include "Signature.h"
#include "Suffix.h"
#include "Affix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "PrefixCollection.h"
#include "SuffixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "StringFunc.h"

CDLHistoryListViewItem::CDLHistoryListViewItem( Q3ListView *parent )
: Q3ListViewItem( parent )
{}


CDLHistoryListViewItem::CDLHistoryListViewItem( Q3ListView *parent, 
												QString mini_name,
												CDLHistory* pDLHistory,
												int index )
: Q3ListViewItem( parent, mini_name )
{
	m_dlhistory = pDLHistory;
	m_index = index;
}


CDLHistoryListViewItem::CDLHistoryListViewItem( Q3ListViewItem *parent, 
												QString mini_name,
												CDLHistory* pDLHistory,
												int index )
: Q3ListViewItem( parent, mini_name )
{
	m_dlhistory = pDLHistory;
	m_index = index;
}


QString CDLHistoryListViewItem::key(int column, bool ascending) const
{
	switch (column) {
	case 0:
		return QString("%1").arg(m_index, 10);
	case 1:
		return m_dlhistory->getMini(m_index);
	case 2:
		return m_dlhistory->getRemark(m_index);
	case 3:
	{
		double total_dl = 0.0;
		total_dl += m_dlhistory->getStemDL(m_index);
		total_dl += m_dlhistory->getAffixDL(m_index);
		total_dl += m_dlhistory->getSigDL(m_index);
		return QString("%1").arg(static_cast<int>(
			double(1000) * total_dl), 10);
	}
	case 4:
		return QString("%1").arg(static_cast<int>(
			double(1000) * m_dlhistory->getUnanalyzedWordDL(m_index)),
			10);
	case 6:
		return QString("%1").arg(static_cast<int>(
			double(1000) * m_dlhistory->getStemDL(m_index)), 10);
	case 7:
		return QString("%1").arg(static_cast<int>(
			double(1000) * m_dlhistory->getAffixDL(m_index)), 10);
	case 8:
		return QString("%1").arg(static_cast<int>(
			double(1000) * m_dlhistory->getSigDL(m_index)), 10 );
	case 9:
		return QString("%1").arg(static_cast<int>(
			m_dlhistory->getNumberOfStems(m_index)), 10);
	case 10:
		return QString("%1").arg(static_cast<int>(
			m_dlhistory->getNumberOfAnalyzedWords(m_index)), 10);
	case 11:
		return QString("%1").arg(static_cast<int>(
			m_dlhistory->getNumberOfUnanalyzedWords(m_index)), 10);
	default:
		return Q3ListViewItem::key(column, ascending);
	}
}

QString CDLHistoryListViewItem::text(int column) const
{
	switch (column) {
	case 0:
		return QString("%1").arg(m_index);
	case 1:
		return m_dlhistory->getMini( m_index );
	case 2:
		return m_dlhistory->getRemark( m_index );
	case 3:
	{
		double total_dl = 0.0;
		total_dl += m_dlhistory->getStemDL(m_index);
		total_dl += m_dlhistory->getAffixDL(m_index);
		total_dl += m_dlhistory->getSigDL(m_index);
		total_dl += m_dlhistory->getUnanalyzedWordDL(m_index);

		return DblToStringWithCommas(total_dl);
	}
	case 4:
		return DblToStringWithCommas(m_dlhistory->getUnanalyzedWordDL(
			m_index));
	case 6:
		return DblToStringWithCommas(m_dlhistory->getStemDL(m_index));
	case 7:
		return DblToStringWithCommas(m_dlhistory->getAffixDL(m_index));
	case 8:
		return DblToStringWithCommas(m_dlhistory->getSigDL(m_index));
	case 9: 
		return IntToStringWithCommas(m_dlhistory->getNumberOfStems(
			m_index));
	case 10: 
		return IntToStringWithCommas(
			m_dlhistory->getNumberOfAnalyzedWords(m_index));
	case 11: 
		return IntToStringWithCommas(
			m_dlhistory->getNumberOfUnanalyzedWords(m_index));
	default:
		return Q3ListViewItem::text(column);
	}
}

int CDLHistoryListViewItem::compare(
	Q3ListViewItem* item, int col, bool asc) const
{
	CDLHistoryListViewItem& rhs = *static_cast<CDLHistoryListViewItem*>(item);
	switch (col) {
	case 0:
		return m_index - rhs.m_index;
	default:
		return Q3ListViewItem::compare(item, col, asc);
	}
}

// construction/destruction.

CDLHistory::CDLHistory(CLexicon* lexicon)
	: log(), m_Lexicon(lexicon) { }

CDLHistory::~CDLHistory() { }

void CDLHistory::DLHistoryListDisplay( Q3ListView* list )
{
	// Remove all previous columns
	while( list->columns() ) list->removeColumn( 0 );

	// Add Column headers
	list->addColumn( "Order",60 );
	list->addColumn( "Mini-Lexicon",100 );
	list->addColumn( "Remark",175 );
	list->addColumn( "Total DL",160 );
	list->setColumnAlignment( 3, Qt::AlignRight );
	list->addColumn( "Unanalyzed words DL",130 );
	list->setColumnAlignment( 4, Qt::AlignRight );
	list->addColumn( "--" );
	list->setColumnAlignment( 5, Qt::AlignRight );
	list->addColumn( "Stems DL",75 );
	list->setColumnAlignment( 6, Qt::AlignRight );
	list->addColumn( "Affixes DL",75 );
	list->setColumnAlignment( 7, Qt::AlignRight );
	list->addColumn( "Signatures DL",90 );
	list->setColumnAlignment( 8, Qt::AlignRight );
	list->addColumn( "Stem count",75 );
	list->setColumnAlignment( 9, Qt::AlignRight );
	list->addColumn( "Analyzed words",100 );
	list->setColumnAlignment( 10, Qt::AlignRight );
	list->addColumn( "Unanalyzed words",120 );
	list->setColumnAlignment( 11, Qt::AlignRight );
	

	if( m_Lexicon )
	{
		m_Lexicon->GetDocument()->setStatusBar1( "Creating description length list for display" );
		m_Lexicon->GetDocument()->BeginCountDown();
	}

	for (int i = 0; i < count(); ++i) {
		static_cast<void>(new CDLHistoryListViewItem(
			list, getMini(i), this, i));

		if (m_Lexicon)
			m_Lexicon->GetDocument()->CountDownOnStatusBar(i, count());
	}

	if( m_Lexicon )
	{
		m_Lexicon->GetDocument()->setStatusBar1( "" );
		m_Lexicon->GetDocument()->EndCountDown();
	}
}

	/// calculate current description length and add it to the stack.
	/// if count() == std::numeric_limits<int>::max(),
	/// clear the history first.
void CDLHistory::append(QString mini_name, QString remark,
		CMiniLexicon* mini_ptr)
{
	if (log.size() >= log.max_size() ||
			log.size() >= static_cast<std::size_t>(
				std::numeric_limits<int>::max()))
		// too many entries
		log.clear();

	if (mini_ptr == 0)
		return;
	CMiniLexicon& mini = *mini_ptr;

	const int num_distinct_phonemes =
		m_Lexicon->GetNumberOfCharacterTypes();

	double stems_len = 0.0;
	int num_stems = 0;
	if (CStemCollection* stems = mini.GetStems()) {
		num_stems = stems->GetCount();
		for (int i = 0; i < num_stems; ++i) {
			CStem& stem = *stems->GetAt(i);
			stems_len += stem.ComputeDL(num_distinct_phonemes);
		}
	}
  
	double unanalyzed_words_len = 0.0;
	if (CWordCollection* words = mini.GetWords())
		for (int i = 0; i < words->GetCount(); ++i) {
			CStem& word = *words->GetAt(i);
			if (word.IsAnalyzed()) 
				continue;
			unanalyzed_words_len += word.ComputeDL(
					num_distinct_phonemes);
		}

	double affixes_len = 0.0;
	if (CSuffixCollection* suffixes = mini.GetSuffixes()) {
		affixes_len += suffixes->GetDL_PhonologicalContent();
	} else {
		CPrefixCollection* prefixes = mini.GetPrefixes();
		Q_ASSERT(prefixes != 0);
		// XXX. define prefixes->GetDL_PhonologicalContent()

		for (int i = 0; i < prefixes->GetCount(); ++i) {
			CAffix& affix = *prefixes->GetAt(i);
			affixes_len += affix.ComputeDL(num_distinct_phonemes);
		}
	}

	double signatures_len = 0.0;
	if (CSignatureCollection* signatures = mini.GetSignatures())
		for (int i = 0; i < signatures->GetCount(); ++i) {
			CSignature& sig = *signatures->GetAt(i);
			signatures_len += sig.ComputeDLofModel(
					num_distinct_phonemes);
		}

	int num_unanalyzed_words = -1;
	const int num_analyzed_words =
		mini.GetNumberOfAnalyzedWords(num_unanalyzed_words);

	this->log.push_back(entry());
	entry& new_entry = log.back();
	{
		new_entry.stems_len = stems_len;
		new_entry.unanalyzed_words_len = unanalyzed_words_len;
		new_entry.affixes_len = affixes_len;
		new_entry.signatures_len = signatures_len;

		new_entry.num_stems = num_stems;
		new_entry.num_unanalyzed_words = num_unanalyzed_words;
		new_entry.num_analyzed_words = num_analyzed_words;

		new_entry.remark = remark;
		new_entry.mini_name = mini_name;
	}
}
