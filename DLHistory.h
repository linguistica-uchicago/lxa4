// Description length log for display
// Copyright © 2009 The University of Chicago
#ifndef DLHISTORY_H
#define DLHISTORY_H

class CDLHistoryListViewItem;
class CDLHistory;

#include <Q3ListViewItem>

class CDLHistoryListViewItem : public Q3ListViewItem {
protected:
	CDLHistory* m_dlhistory;
	int m_index;
public:
	CDLHistoryListViewItem(class Q3ListView* widget = 0);
	CDLHistoryListViewItem(class Q3ListView* widget,
		QString = QString(), CDLHistory* = 0, int index = 0);
	CDLHistoryListViewItem(class Q3ListViewItem* widget,
		QString = QString(), CDLHistory* = 0, int index = 0);

	// list view item interface.

	virtual QString text(int column) const;
	virtual QString key(int column, bool ascending) const;
	virtual int compare(class Q3ListViewItem* i, int col,
		bool ascending) const; 

	int GetIndex() { return m_index;}
};

#include <cstddef>
#include <vector>
#include <limits>
#include <QString>

class CDLHistory {
protected:
	struct entry {
		double stems_len;
		double unanalyzed_words_len;
		double affixes_len;
		double signatures_len;

		int num_stems;
		int num_unanalyzed_words;
		int num_analyzed_words;

		QString remark;
		QString mini_name;
	};

	std::vector<entry> log;

	/// lexicon and driver, for total counts and user interaction
	class CLexicon* m_Lexicon;
public:
	// construction/destruction.

	CDLHistory(class CLexicon* lexicon = 0);
	~CDLHistory();

	// output to GUI.

	void DLHistoryListDisplay(class Q3ListView* widget);

	// add to history.

	/// calculate current description length and add it to the stack.
	/// if the stack is too large, clear it first.
	void append(QString mini_name, QString remark,
		class CMiniLexicon* mini_lexicon);

	/// number of entries
	int count()
	{
		Q_ASSERT(log.size() <= static_cast<std::size_t>(
				std::numeric_limits<int>::max()));
		return static_cast<int>(log.size());
	}

	// read entries.

	QString getMini(int i) { return log[i].mini_name; }
	QString getRemark(int i) { return log[i].remark; }
	double getStemDL(int i) { return log[i].stems_len; }
	double getUnanalyzedWordDL(int i)
		{ return log[i].unanalyzed_words_len; }
	double getAffixDL(int i) { return log[i].affixes_len; }
	double getSigDL(int i) { return log[i].signatures_len; }

	int getNumberOfStems(int i) { return log[i].num_stems; }
	int getNumberOfAnalyzedWords(int i)
		{ return log[i].num_analyzed_words; }
	int getNumberOfUnanalyzedWords(int i)
		{ return log[i].num_unanalyzed_words; }
protected:
	// set lexicon.

	void setLexicon(CLexicon* lex) { m_Lexicon = lex; }
};

#endif // DLHISTORY_H
