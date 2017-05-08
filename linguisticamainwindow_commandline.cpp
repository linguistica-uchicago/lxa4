// Updating the main window’s additional-info area
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include <algorithm>
#include <Q3TextStream>
#include <QString>
#include <QFont>
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "LPreferences.h"
#include "Compound.h"
#include "Suffix.h"
#include "Prefix.h"
#include "POS.h"
#include "SignatureCollection.h"
#include "TemplateCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"

void LinguisticaMainWindow::setCommandLineStyle( QString style )
{
  QFont font = m_eastFont;
  QString color = GetPreference( style + "_Color" );
  if( color.length() == 0 ) color = "black";

  m_commandLine->setColor( QColor( color ) );

  m_commandLine->setFamily( font.family() );
  m_commandLine->setPointSize( font.pointSize() );

  font = GetFontPreference( style );
  m_commandLine->setBold( font.bold() );
  m_commandLine->setItalic( font.italic() );
  m_commandLine->setUnderline( font.underline() );
}


void LinguisticaMainWindow::updateCommandLineSlot()
{
	updateCommandLineSlot( NULL );
}

void LinguisticaMainWindow::updateCommandLineSlot(Q3ListViewItem* item)
{
	if (item != 0) {
		// set m_commandParse and m_commandMini for the selected
		// collection view item.

		switch (m_docType) {
		case WORDS:
		case ANALYZED_WORDS:
		case ALL_ANALYZED_WORDS:
			if (m_lexicon->GetActiveMiniIndex() != -1) {
				CWordListViewItem* word =
					static_cast<CWordListViewItem*>(item);

				if (!word->isFullLex()) {
					m_commandParse = word->GetWord();
					item = 0;
				} else {
					m_commandParse = 0;
				}
				m_commandMini = -1;
			}
			break;
		case SUFFIXES:
		{
			CSuffixListViewItem* suffix_item =
				static_cast<CSuffixListViewItem*>(item);
			if (CSuffix* suffix = suffix_item->GetAffix()) {
				m_commandParse = suffix;
				m_commandMini = suffix->GetMyMini()->GetIndex();
			}
			break;
		}
		case PREFIXES:
		{
			CPrefixListViewItem* prefix_item =
				static_cast<CPrefixListViewItem*>(item);
			if (CPrefix* prefix = prefix_item->GetAffix()) {
				m_commandParse = prefix;
				m_commandMini = prefix->GetMyMini()->GetIndex();
			}
			break;
		}
		case TRIE:
			break;
		case STEMS_SUFFIXED:
		{
			CStemListViewItem* stem_item =
				static_cast<CStemListViewItem*>(item);
			if (CStem* stem = stem_item->GetStem()) {
				m_commandParse = stem;
				m_commandMini = stem->GetMyMini()->GetIndex();
			}
			break;
		}
		case SIGNATURES:
		case PREFIX_SIGNATURES:
		case SUFFIX_SIGNATURES:
		{
			CSignatureListViewItem* sig_item =
				static_cast<CSignatureListViewItem*>(item);
			if (CSignature* sig = sig_item->GetSignature()) {
				m_commandParse = sig;
				m_commandMini = sig->GetMyMini()->GetIndex();
			}
			break;
		}
		case COMPOUNDS:
			m_commandParse = static_cast<CCompoundListViewItem*>(item)
				->GetCompound();
			break;
		case INITIALSTRINGEDITTEMPLATES:
			m_CommonTemplate =
				static_cast<CTemplateListViewItem*>(item)
				->GetTemplate();
			break;
		case WORKINGSTRINGEDITTEMPLATES:
			m_CommonTemplate =
				static_cast<CTemplateListViewItem*>(item)
				->GetTemplate();
			break;
		case POS:
		{
			GUIPOSListViewItem* pos_item =
				static_cast<GUIPOSListViewItem*>(item);
			if (LxPoS* pos = pos_item->GetPoS())
				m_commandParse = pos;
			break;
		}
		case FSA_DOC:
		case NO_DOC:
		default:
			m_commandMini = -1;
			break;
		}
	}

	// Clear the command line
	m_commandLine->clear();
	m_commandLine->setFont(m_eastFont);

	if (m_commandParse == 0 && m_CommonState == 0 && item == 0)
		return;

	QString text;
	QTextStream ts(&text, QIODevice::WriteOnly);

	CMiniLexicon* mini = m_lexicon->GetMiniLexicon(m_commandMini);
	QMap<QString, QString>* const filter = m_lexicon->GetOutFilter();

	switch (m_docType) {
	case WORDS:
	case ANALYZED_WORDS:
	case ALL_ANALYZED_WORDS:
		if (item != 0) {
			// selected item in collection view
			CWordListViewItem* word_item =
				static_cast<CWordListViewItem*>(item);
			CStem* word = word_item->GetWord();

			setCommandLineStyle("Stem");
			m_commandLine->insert(item->text(1));

			setCommandLineStyle("Affix");
			const int nColumns = m_lexicon->GetMiniCount() + 2;
			for (int i = 2; i < nColumns; ++i)
				if (!item->text(i).isEmpty()) {
					m_commandLine->insert(QString(" %1")
						.arg(item->text(i)));
				}

			m_commandLine->insert(QString("\n%1").arg(
				word->GetProbabilityInformation()));

			// Graphic Display
			//updateSmallGraphicDisplaySlotForPhonogy(word);
		} else {
			// just updating the “command line” text
			// XXX. Reconcile with other case.

			CStem* word = static_cast<CStem*>(m_commandParse);

			if (CPrefix* pPrefix = word->GetPrefixPtr()) {
				setCommandLineStyle("Affix");
				m_commandLine->insert(QString("%1 ")
					.arg(pPrefix->Display(filter)));
			}

			if (CStem* pStem = word->GetStemPtr()) {
				setCommandLineStyle("Stem");
				m_commandLine->insert(QString("%1 ")
					.arg(pStem->Display(filter)));
			} else {
				m_commandLine->insert(word->Display(filter));
			}

			if (CSuffix* pSuffix = word->GetSuffixPtr()) {
				setCommandLineStyle("Affix");
				m_commandLine->insert(pSuffix->Display(filter));
			}

			m_commandLine->insert(QString("\n%1")
				.arg(word->GetProbabilityInformation()));

			// Graphic display
			//updateSmallGraphicDisplaySlotForPhonogy(word);
		}
		break;
	case SUFFIXES:
	{
		if (m_commandParse == 0)
			break;

		CSuffix* suffix = static_cast<CSuffix*>(m_commandParse);
		QString selected = suffix->Display(filter);
		if (selected.isEmpty()) {
			setCommandLineStyle("Error");
			m_commandLine->insert(QString("Not found."));
			return;
		}

		// Suffix name
		setCommandLineStyle("Affix");
		m_commandLine->insert(selected);

		// XXX. deletees?

		// Corresponding signatures
		setCommandLineStyle("Main");
		m_commandLine->insert("\n\nSignatures:\n");

		Q_ASSERT(mini != 0);
		CSignatureCollection* Signatures = mini->GetSignatures();
		setCommandLineStyle("Signature");
		for (int i = 0; i < Signatures->GetCount(); ++i) {
			const CSignature& sig = *Signatures->GetAt(i);

			if (sig.Contains(selected))
				m_commandLine->insert(QString("\t%1\n")
					.arg(sig.Display('.', filter)));
		}

		// Corresponding stems
		setCommandLineStyle("Main");
		m_commandLine->insert("\n\nStems:\n\t");
		setCommandLineStyle("Stem");
		int nColumns = 3;
		int tablength = 0;
		if (CSuffix* pSuffix = *mini->GetSuffixes() ^= selected) {
			CParse* pParse = pSuffix->GetStemString();

			for (int i = 1; i <= pParse->Size(); ) {
				for(int j = 1; j <= nColumns; ++j) {
					QString text = pParse->GetPiece(i)
							.Display(filter);
					++i;

					m_commandLine->insert(QString("%1\t")
							.arg(text));

					// Make tab length depend on the longest
					// word and font size
					tablength = std::max(tablength,
						text.size() *
						m_commandLine->pointSize());
					m_commandLine->insert("\n\t");
				}
				m_commandLine->setTabStopWidth(tablength);
			}
		}
		break;
	}
	case PREFIXES:
	{
		if (m_commandParse == 0)
			break;

		CPrefix* prefix = static_cast<CPrefix*>(m_commandParse);
		QString selected = prefix->Display(filter);
		if (selected.isEmpty()) {
			setCommandLineStyle("Error");
			m_commandLine->insert(QString("Not found."));
			return;
		}

		// Prefix name
		setCommandLineStyle("Affix");
		m_commandLine->insert(selected);

		// XXX. deletees?

		// Corresponding signatures
		setCommandLineStyle("Main");
		m_commandLine->insert("\n\nSignatures:\n");

		Q_ASSERT(mini != 0);
		CSignatureCollection* Signatures = mini->GetSignatures();
		setCommandLineStyle("Signature");
		for (int i = 0; i < Signatures->GetCount(); ++i) {
			const CSignature& sig = *Signatures->GetAt(i);

			if (sig.Contains(selected))
				m_commandLine->insert(QString("\t%1\n")
					.arg(sig.Display('.', filter)));
		}

		// Corresponding stems
		setCommandLineStyle("Main");
		m_commandLine->insert("\n\nStems:\n\t");
		setCommandLineStyle("Stem");
		int nColumns = 3;
		int tablength = 0;
		if (CPrefix* pPrefix = *mini->GetPrefixes() ^= selected) {
			CParse* pParse = pPrefix->GetStemString();

			for (int i = 1; i <= pParse->Size(); ) {
				for(int j = 1; j <= nColumns; ++j) {
					QString text = pParse->GetPiece(i)
							.Display(filter);
					++i;

					m_commandLine->insert(QString("%1\t")
							.arg(text));

					// Make tab length depend on the longest
					// word and font size
					tablength = std::max(tablength,
						text.size() *
						m_commandLine->pointSize());
					m_commandLine->insert("\n\t");
				}
				m_commandLine->setTabStopWidth(tablength);
			}
		}
		break;
	}
	case TRIE:
		break;
	case STEMS_SUFFIXED:
		break;
	case SIGNATURE_SUBSET:
	case SIGNATURES:
	case PREFIX_SIGNATURES:
	case SUFFIX_SIGNATURES:
	{
		const QString sigPrefix = " : ";

		if (m_commandParse == 0)
			break;

		// XXX. avoid work if “command line” is not visible

		CSignature* sig = static_cast<CSignature*>(m_commandParse);
		QString selected = sig->Display('.', filter);
		if (selected.left(3) == sigPrefix)
			selected = selected.mid(3);

		if (selected.isEmpty()) {
			setCommandLineStyle("Error");
			m_commandLine->insert(QString("Not found."));
			return;
		}

		setCommandLineStyle("Signature");
		m_commandLine->insert(selected);

		setCommandLineStyle("Normal");
		m_commandLine->insert("\n\nStems:\n");
		setCommandLineStyle("Stem");

		CSignature* pSig = *mini->GetSignatures() ^= selected ;
		Q_ASSERT(pSig != 0);

		// alphabetize stems from the right end.
		CParse StemList = pSig->GetStems();
		StemList.Display();
		StemList.ReverseAlphabetize(); // from the end of the stem.

		m_commandLine->insert("\n\n");
		int nColumns = 5;
		int tablength = 0;
		for (int i = 1; i <= pSig->GetNumberOfStems(); ) {
			for (int j = 1; j <= nColumns; ++j) {
				QString text = StemList[i].Display(filter)
						.trimmed();
				++i;

				m_commandLine->insert(QString("%1\t")
						.arg(text));

				// Make tab length depend on the longest
				// word and font size
				tablength = std::max(tablength,
					text.length() *
					m_commandLine->pointSize());
			}

			m_commandLine->insert("\n");
		}
		m_commandLine->setTabStopWidth(tablength);

		m_commandLine->insert("\nDL of my corpus: ");
		m_commandLine->insert(QString::number(
				pSig->ComputeDLofMyCorpus()));

		m_commandLine->insert("\nDL of my stem pointers: ");
		m_commandLine->insert(QString::number(
				pSig->GetDLofMyStemPointers()));

		m_commandLine->insert("\nDL of my suffix pointers: ");
		m_commandLine->insert(QString::number(
				pSig->GetDLofMyAffixPointers()));

		m_commandLine->insert("\nNumber of stem pointers: ");
		m_commandLine->insert(QString::number(
				pSig->GetStemPtrList()->count()));

		// XXX. Display signature's stems graphically
//		updateSmallGraphicDisplaySlotForMultiDimensionData(...)
		break;
	}
	case POS:
	{
		if (m_commandParse == 0)
			break;
		CSignature* sig = static_cast<CSignature*>(m_commandParse);
		QString selected = sig->Display('.', filter);

		if (selected.isEmpty()) {
			setCommandLineStyle("Error");
			m_commandLine->insert(QString("Not found."));
			return;
		}

		setCommandLineStyle("Signature");
		m_commandLine->insert(selected);

		setCommandLineStyle("Normal");
		m_commandLine->insert("\n\nSatellite affixes:\n");
		break;
	}
	case COMPOUNDS:
		setStatusBar1("");
		//updateSmallGraphicDisplaySlot();
		break;
	case FSA_DOC:
	{
		FSAListViewItem* pFSAListViewItem =
			static_cast<FSAListViewItem*>(item);
		pFSAListViewItem->DisplayEdgePath(m_commandLine);
		this->pImgLabel->setPixmap(pFSAListViewItem
			->GetQPixmap()->scaled(
				pImgLabel->size(),
				Qt::KeepAspectRatio,
				Qt::SmoothTransformation));
		//updateSmallGraphicDisplaySlot();
		break;
	}
	case NO_DOC:
	default:
		break;
	}

	// further additions use plain text
	setCommandLineStyle("Main");
	m_commandLine->setCursorPosition(0, 0);
}
