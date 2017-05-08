// Updating the main window’s morpheme collection view
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include "MiniLexicon.h"
#include "Lexicon.h"
#include "TreeViewItem.h"
#include "GUIclasses.h"
#include "DescriptionLength.h"
#include "DLHistory.h"
#include "SignatureCollection.h"
#include "TemplateCollection.h"
#include "BiphoneCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "PhoneCollection.h"
#include "StemCollection.h"
#include "WordCollection.h"
#include "POSCollection.h"

class LxPoSCollection;
class GUIWordCollection;

void LinguisticaMainWindow::updateCollectionViewSlot()
{
	if (m_docType == TOKENS_REQUESTED) {
		emit tokensRequestedSignal();
	} else if (CMiniLexicon* mini = m_lexicon->GetMiniLexicon(
				m_lexicon->GetActiveMiniIndex())) {
		switch (m_docType) {
		case WORDS:
			mini->GetGUIWords()
				->ListDisplay(m_collectionView,
					m_lexicon->GetOutFilter(),
					false);
			break;
		case ANALYZED_WORDS:
			mini->GetGUIWords()
				->ListDisplay(m_collectionView,
					m_lexicon->GetOutFilter(),
					true);
			break;
		case STEMS:
			mini->GetStems()->ListDisplay(m_collectionView,
					m_lexicon->GetOutFilter());
			break;
		case PREFIXES:
			if (CPrefixCollection* prefixes = mini->GetPrefixes())
				prefixes->ListDisplay(m_collectionView,
						m_lexicon->GetOutFilter());
			break;
		case SUFFIXES:
			if (CSuffixCollection* suffixes = mini->GetSuffixes())
				suffixes->ListDisplay(m_collectionView,
						m_lexicon->GetOutFilter(),
						false);
			break;
		case PHONES:
			if (CPhoneCollection* phones = mini->GetWords()->GetPhones())
				phones->ListDisplay(m_collectionView);
			break;
		case BIPHONES:
			if (CBiphoneCollection* biphones =
					mini->GetWords()->GetPhones()
					->GetMyBiphones())
				biphones->ListDisplay(m_collectionView);
			break;
		case PHONES_Tier2:
			if (CPhoneCollection* phones =
					mini->GetWords()->GetPhones_Tier2())
				phones->ListDisplay(m_collectionView);
			break;
		case BIPHONES_Tier2:
			if (CBiphoneCollection* biphones =
					mini->GetWords()->GetPhones_Tier2()
					->GetMyBiphones())
				biphones->ListDisplay(m_collectionView);
			break;
		case PHONES_Tier1_Skeleton:
			if (CPhoneCollection* phones =
					mini->GetWords()
					->GetPhones_Tier1_Skeleton())
				phones->ListDisplay(m_collectionView);
			break;
		case BIPHONES_Tier1_Skeleton:
			if (CBiphoneCollection* biphones =
					mini->GetWords()
					->GetPhones_Tier1_Skeleton()
					->GetMyBiphones())
				biphones->ListDisplay(m_collectionView);
			break;
		case SIGNATURES:
			mini->GetSignatures()
				->ListDisplay(m_collectionView,
					m_lexicon->GetOutFilter());
			break;
		case POS:
			// Parts of speech
			mini->GetPOS()->ListDisplay(m_collectionView);
			break;
		case FSA_DOC:
			mini->GetFSA()->FSAListDisplay(m_collectionView,
					m_lexicon->GetOutFilter(),
					false);
			break;
		case REVERSE_TRIE:
			mini->GetWords()->GetReverseTrie()
				->ListDisplay(m_collectionView,
					this,
					m_lexicon->GetOutFilter(),
					true);
			break;
		case TRIE:
			mini->GetWords()->GetTrie()
				->ListDisplay(m_collectionView,
					this,
					m_lexicon->GetOutFilter());
			break;
		case TOKENS_REQUESTED:
			// not reached
			emit tokensRequestedSignal();
			break;
		case DESCRIPTION_LENGTH:
			if (mini->GetDescriptionLength() == 0)
				mini->CalculateDescriptionLength();
			if (CDescriptionLength* dl =
					mini->GetDescriptionLength())
				dl->DescriptionLengthListDisplay(m_collectionView);
			// XXX. add a section for CLexicon
			break;
		default:
			break;
		}
	}
 
	if (m_lexicon != 0) {
		switch (m_docType) {
		case CORPUS_WORDS:
			m_lexicon->CorpusWordListDisplay(
					m_collectionView,
					m_lexicon->GetOutFilter(),
					false);
			break;
		case ANALYZED_CORPUS_WORDS:
			m_lexicon->CorpusWordListDisplay(
					m_collectionView,
					m_lexicon->GetOutFilter(),
					true);
			break;
		case ALL_WORDS:
			m_lexicon->WordListDisplay(
					m_collectionView,
					false);
			break;
		case ALL_ANALYZED_WORDS:
			m_lexicon->WordListDisplay(
					m_collectionView,
					true);
			break;
		case ALL_STEMS:
			m_lexicon->StemListDisplay(m_collectionView);
			break;
		case ALL_PREFIXES:
			m_lexicon->PrefixListDisplay(m_collectionView);
			break;
		case ALL_PREFIX_SIGNATURES:
			m_lexicon->SignatureListDisplay(
					m_collectionView,
					PREFIX_SIGNATURES);
			break;
		case ALL_SUFFIXES:
			m_lexicon->SuffixListDisplay(m_collectionView);
			break;
		case ALL_SUFFIX_SIGNATURES:
			m_lexicon->SignatureListDisplay(
					m_collectionView,
					SUFFIX_SIGNATURES);
			break;
		case COMPOUNDS:
			m_lexicon->CompoundListDisplay(
					m_collectionView,
					m_lexicon->GetOutFilter(),
					QChar());
			break;
		case LINKERS:
			m_lexicon->LinkerListDisplay(
					m_collectionView,
					m_lexicon->GetOutFilter());
			break;
		case COMPOUND_COMPONENTS:
			m_lexicon->CompoundComponentListDisplay(
					m_collectionView);
			break;
		case TOKENS_REQUESTED:
			emit tokensRequestedSignal();
			break;
		case INITIALSTRINGEDITTEMPLATES:
			m_Words_InitialTemplates->ListDisplay(
					m_collectionView);
			break;
		case WORKINGSTRINGEDITTEMPLATES:
			m_Words_Templates->ListDisplay(
					m_collectionView);
			break;
		case DESCRIPTION_LENGTH_HISTORY:
			m_lexicon->GetDLHistory()
				->DLHistoryListDisplay(m_collectionView);
			break;
		default:
			break;
		}
	}

	m_collectionView->setFont(m_eastFont);
}

void LinguisticaMainWindow::updateCollectionViewSlot(Q3ListViewItem* item)
{
	if (item == 0)
		return;

	CTreeViewItem& it = *static_cast<CTreeViewItem*>(item);
	enum eDocumentType newDocType = it.GetState();
	int newIndex = it.GetIndex();

	if (newDocType == MINI_LEXICON) {
		m_lexicon->SetActiveMiniIndex(newIndex);
		updateTreeViewSlot();
		return;
	}

	if (newDocType == m_docType &&
			newIndex == m_lexicon->GetActiveMiniIndex())
		// nothing to do.
		return;

	m_commandMini = newIndex;
	m_docType = newDocType;
	if (newIndex >= 0)
		m_lexicon->SetActiveMiniIndex(newIndex);
	updateCollectionViewSlot();
}
