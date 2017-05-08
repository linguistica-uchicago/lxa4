// Implementation of CPrefixListViewItem, CSuffixListViewItem methods
// Copyright © 2009 The University of Chicago
#ifndef AFFIX_LIST_VIEW_ITEM_TCC
#define AFFIX_LIST_VIEW_ITEM_TCC

#include "Affix.h"
#include <Q3ListViewItem>
#include <QString>
#include "StringSurrogate.h"
#include "Parse.h"
#include "CompareFunc.h"

namespace linguistica {

template<class Affix> affix_list_view_item<Affix>::affix_list_view_item(
		Q3ListView* parent, QString text, Affix* affix,
		QMap<QString, QString>* filter, int char_count)
	: Q3ListViewItem(parent, text),
	m_affix(affix),
	m_filter(filter),
	m_char_count(char_count) { }

template<class Affix> affix_list_view_item<Affix>::affix_list_view_item(
		Q3ListViewItem* parent, QString text, Affix* affix,
		QMap<QString, QString>* filter, int char_count)
	: Q3ListViewItem(parent, text),
	m_affix(affix),
	m_filter(filter),
	m_char_count(char_count) { }

template<class Affix> QString affix_list_view_item<Affix>::text(int col) const
{
	switch (col) {
	case 1:
		if (m_affix == 0)
			return QString();
		return QString::number(m_affix->ComputeDL(m_char_count));
	case 2:
		if (m_affix == 0)
			return QString();
		return QString::number(m_affix->GetLengthOfPointerToMe());
	case 3:
	{
		if (m_affix != 0)
			return QString::number(m_affix->GetCorpusCount());
		int count = 0;
		for (affix_list_view_item* child =
					static_cast<affix_list_view_item*>(
					firstChild());
				child != 0;
				child = static_cast<affix_list_view_item*>(
					child->nextSibling()))
			if (Affix* affix = child->m_affix)
				count += affix->GetCorpusCount();
		return QString::number(count);
	}
	case 4:
	{
		if (m_affix != 0)
			return QString::number(m_affix->GetUseCount());
		int count = 0;
		for (affix_list_view_item* child =
					static_cast<affix_list_view_item*>(
					firstChild());
				child != 0;
				child = static_cast<affix_list_view_item*>(
					child->nextSibling()))
			if (Affix* affix = child->m_affix)
				count += affix->GetUseCount();
		return QString::number(count);
	}
	case 5:
	{
		if (m_affix == 0)
			return QString();
		CParse& stem_str = *m_affix->GetStemString();

		if (stem_str.Size() == 0)
			return QString();
		QString stem_string = stem_str.GetPiece(1).Display(m_filter);
		for (int i = 2; i <= stem_str.Size(); ++i) {
			stem_string += ", ";
			stem_string += stem_str.GetPiece(i).Display(m_filter);
		}
		return stem_string;
	}
	default:
		return Q3ListViewItem::text(col);
	}
}

template<class Affix> int affix_list_view_item<Affix>::compare(
	Q3ListViewItem* other, int col, bool asc) const
{
	Affix& this_affix = *m_affix;
	Affix& other_affix = *static_cast<affix_list_view_item*>(
			other)->m_affix;

	switch (col) {
	case 1:
		return MakeComparable(this_affix.ComputeDL(),
			other_affix.ComputeDL());
	case 2:
		return MakeComparable(this_affix.GetLengthOfPointerToMe(),
			other_affix.GetLengthOfPointerToMe());
	case 3:
		return MakeComparable(this_affix.GetCorpusCount(),
			other_affix.GetCorpusCount());
	case 4:
		return MakeComparable(this_affix.GetUseCount(),
			other_affix.GetUseCount());
	default:
		return Q3ListViewItem::compare(other, col, asc);
	}
}

template<class Affix> QString affix_list_view_item<Affix>::key(
	int col, bool asc) const
{
	switch (col) {
	case 1:
		if (m_affix == 0)
			return QString();
		return QString("%1").arg(static_cast<int>(
			1000 * m_affix->ComputeDL(m_char_count)), 15);
	case 2:
		if (m_affix == 0)
			return QString();
		return QString("%1").arg(static_cast<int>(
			1000 * m_affix->GetLengthOfPointerToMe()), 15);
	case 3:
	{
		if (m_affix != 0)
			return QString("%1").arg(m_affix->GetCorpusCount(), 15);
		int count = 0;
		for (affix_list_view_item* child =
					static_cast<affix_list_view_item*>(
					firstChild());
				child != 0;
				child = static_cast<affix_list_view_item*>(
					child->nextSibling()))
			if (Affix* affix = child->m_affix)
				count += affix->GetCorpusCount();
		return QString("%1").arg(count, 15);
	}
	case 4:
	{
		if (m_affix != 0)
			return QString("%1").arg(m_affix->GetUseCount(), 15);
		int count = 0;
		for (affix_list_view_item* child =
					static_cast<affix_list_view_item*>(
					firstChild());
				child != 0;
				child = static_cast<affix_list_view_item*>(
					child->nextSibling()))
			if (Affix* affix = child->m_affix)
				count += affix->GetUseCount();
		return QString("%1").arg(count, 15);
	}
	case 5:
	{
		if (m_affix == 0)
			return QString();
		CParse& stem_str = *m_affix->GetStemString();

		if (stem_str.Size() == 0)
			return QString();
		QString stem_string = stem_str.GetPiece(1).Display(m_filter);
		for (int i = 2; i <= stem_str.Size(); ++i) {
			stem_string += ", ";
			stem_string += stem_str.GetPiece(i).Display(m_filter);
		}
		return stem_string;
	}
	default:
		return Q3ListViewItem::key(col, asc);
	}
}

} // namespace linguistica

#endif // AFFIX_LIST_VIEW_ITEM_TCC
