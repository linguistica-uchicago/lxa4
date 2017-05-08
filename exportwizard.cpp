// User interface for writing morpheme data to files
// Copyright © 2009 The University of Chicago
#include "exportwizard.h"

#include <QColorDialog>
#include <Q3FileDialog>
#include <QMessageBox>
#include <QDir>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "CorpusWord.h"
#include "Signature.h"
#include "Compound.h"
#include "Linker.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Edge.h"
#include "Stem.h"
#include "CorpusWordCollection.h"
#include "SignatureCollection.h"
#include "CompoundCollection.h"
#include "LinkerCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"

ExportWizard::ExportWizard( CLexicon* pLexicon, QWidget* parent,
							Qt::WindowFlags fl )
	: Q3Wizard(parent, 0, false, fl), ExportWizardBase()
{
	setupUi( this );

	m_pLexicon = pLexicon;
	m_pSettings = m_pLexicon->GetDocument()->GetSettings();

	// Disable the next and finish buttons until 
	// proper settings are made
	setNextEnabled( page(PROJECT_INFO_PAGE), FALSE );
	setFinishEnabled( page(CONFIRMATION), FALSE );

	// Set all pages as inappropriate, these will change 
	// as the user makes selections on the first page
	setAppropriate( page( STYLE_SHEET_PAGE ), FALSE );
	setAppropriate( page( CORPUS_WORDS_FILE_PAGE ), FALSE );
	setAppropriate( page( COMPOUNDS_FILE_PAGE ), FALSE );
	setAppropriate( page( ALL_WORDS_FILE_PAGE ), FALSE );
	setAppropriate( page( ALL_SUFFIX_SIGNATURES_FILE_PAGE ), FALSE );
	setAppropriate( page( ALL_PREFIX_SIGNATURES_FILE_PAGE ), FALSE );
	setAppropriate( page( ALL_STEMS_FILE_PAGE ), FALSE );
	setAppropriate( page( ALL_SUFFIXES_FILE_PAGE ), FALSE );
	setAppropriate( page( ALL_PREFIXES_FILE_PAGE ), FALSE );
	setAppropriate( page( MINI_WORDS_FILE_PAGE ), FALSE );
	setAppropriate( page( MINI_SIGNATURES_FILE_PAGE ), FALSE );
	setAppropriate( page( MINI_STEMS_FILE_PAGE ), FALSE );
	setAppropriate( page( MINI_SUFFIXES_FILE_PAGE ), FALSE );
	setAppropriate( page( MINI_PREFIXES_FILE_PAGE ), FALSE );

	// Update all examples
	updateCorpusWordsExampleSlot();

	// Load from settings
	load();
}


void ExportWizard::load()
{
	// Project Information
	m_projectName->setText( m_pSettings->readEntry( SETTINGS + "projectName", "" ) );
	m_language->setText( m_pSettings->readEntry( SETTINGS + "language", "" ) );
	m_researchers->setText( m_pSettings->readEntry( SETTINGS + "researchers", "" ) );
	m_brokenCorpusFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "brokenCorpusFlag" ) );
	m_corpusWordsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsFlag" ) );
	m_compoundsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundsFlag" ) );
	m_allWordsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allWordsFlag" ) );
	m_allSuffixSigsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixSigsFlag" ) );
	m_allPrefixSigsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixSigsFlag" ) );
	m_allStemsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allStemsFlag" ) );
	m_allSuffixesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixesFlag" ) );
	m_allPrefixesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixesFlag" ) );
	m_miniWordsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "wordsFlag" ) );
	m_miniSignaturesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "signaturesFlag" ) );
	m_miniStemsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "stemsFlag" ) );
	m_miniSuffixesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "suffixesFlag" ) );
	m_miniPrefixesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "prefixesFlag" ) );
	m_simpleTextFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "simpleTextFlag" ) );
	m_markUpFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "markUpFlag" ) );
	m_bothFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "bothFlag" ) );
	m_outputDirectory->setText( m_pSettings->readEntry( SETTINGS + "outputDirectory", "" ) );

	// Style Sheet
	m_wordStyle->setPaletteForegroundColor( QColor( m_pSettings->readEntry( SETTINGS + "wordStyleColor", "#000000" ) ) );
	m_wordBoldFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "wordBoldFlag" ) );
	m_wordItalicFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "wordItalicFlag" ) );	
	m_signatureStyle->setPaletteForegroundColor( QColor( m_pSettings->readEntry( SETTINGS + "signatureStyleColor", "#000000" ) ) );
	m_signatureBoldFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "signatureBoldFlag" ) );
	m_signatureItalicFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "signatureItalicFlag" ) );	
	m_stemStyle->setPaletteForegroundColor( QColor( m_pSettings->readEntry( SETTINGS + "stemStyleColor", "#000000" ) ) );
	m_stemBoldFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "stemBoldFlag" ) );
	m_stemItalicFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "stemItalicFlag" ) );	
	m_suffixStyle->setPaletteForegroundColor( QColor( m_pSettings->readEntry( SETTINGS + "suffixStyleColor", "#000000" ) ) );
	m_suffixBoldFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "suffixBoldFlag" ) );
	m_suffixItalicFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "suffixItalicFlag" ) );	
	m_prefixStyle->setPaletteForegroundColor( QColor( m_pSettings->readEntry( SETTINGS + "prefixStyleColor", "#000000" ) ) );
	m_prefixBoldFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "prefixBoldFlag" ) );
	m_prefixItalicFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "prefixItalicFlag" ) );	
	m_compoundStyle->setPaletteForegroundColor( QColor( m_pSettings->readEntry( SETTINGS + "compoundStyleColor", "#000000" ) ) );
	m_compoundBoldFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundBoldFlag" ) );
	m_compoundItalicFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundItalicFlag" ) );

	// Corpus Words	
	m_corpusWordsAnalyzedOnlyFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsAnalyzedOnlyFlag" ) );
	m_corpusWordsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsColumnTitlesFlag" ) );
	m_corpusWordsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsUniformFieldWidthsFlag" ) );
	m_corpusWordsAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsAlphabeticalSortFlag" ) );
	m_corpusWordsCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsCorpusCountSortFlag" ) );
	m_corpusWordsMorphemeCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "corpusWordsMorphemeCountSortFlag" ) );
	m_corpusWordsLine->setText( m_pSettings->readEntry( SETTINGS + "corpusWordsLine", INDEX_FIELD + ". " + WORD_FIELD + " " + CORPUS_COUNT_FIELD + " " + MORPHS_COUNT_FIELD + " " + MORPHS_FIELD ) );
	m_corpusWordsMorphemeFieldDelimiter->setText( m_pSettings->readEntry( SETTINGS + "corpusWordsMorphemeFieldDelimiter", "." ) );
	
	// Linkers
	m_linkersColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "linkersColumnTitlesFlag" ) );
	m_linkersUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "linkersUniformFieldWidthsFlag" ) );
	m_linkersIncludeCompoundListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "linkersIncludeCompoundListFlag" ) );
	m_linkersAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "linkersAlphabeticalSortFlag" ) );
	m_linkersCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "linkersCorpusCountSortFlag" ) );
	m_linkersLine->setText( m_pSettings->readEntry( SETTINGS + "linkersLine", INDEX_FIELD + ". " + LINKER_FIELD + " " + CORPUS_COUNT_FIELD + " " + COMPOUND_COUNT_FIELD ) );
	
	// Compounds	
	m_compoundsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundsColumnTitlesFlag" ) );
	m_compoundsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundsUniformFieldWidthsFlag" ) );
	m_compoundsAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundsAlphabeticalSortFlag" ) );
	m_compoundsCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundsCorpusCountSortFlag" ) );
	m_compoundsMorphemeCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "compoundsMorphemeCountSortFlag" ) );
	m_compoundsLine->setText( m_pSettings->readEntry( SETTINGS + "compoundsLine", INDEX_FIELD + ". " + COMPOUND_FIELD + " " + CORPUS_COUNT_FIELD + " " + MORPHS_COUNT_FIELD + " " + MORPHS_FIELD + " " + SUFFIXNESS_FIELD ) );
	m_compoundsMorphemeFieldDelimiter->setText( m_pSettings->readEntry( SETTINGS + "compoundsMorphemeFieldDelimiter", "." ) );
	
	// All Words
	m_allWordsAnalyzedOnlyFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allWordsAnalyzedOnlyFlag" ) );
	m_allWordsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allWordsColumnTitlesFlag" ) );
	m_allWordsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allWordsUniformFieldWidthsFlag" ) );
	m_allWordsLine->setText( m_pSettings->readEntry( SETTINGS + "allWordsLine", INDEX_FIELD + ". " + WORD_FIELD + " " + MINI_LEX_FIELD + " " + CORPUS_COUNT_FIELD + " " + SIGNATURE_FIELD + " " + PREFIX_FIELD + " " + STEM_FIELD + " " + SUFFIX_FIELD ) );

	// All Suffixes
	m_allSuffixesColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixesColumnTitlesFlag" ) );
	m_allSuffixesUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixesUniformFieldWidthsFlag" ) );
	m_allSuffixesIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixesIncludeStemListFlag" ) );
	m_allSuffixesLine->setText( m_pSettings->readEntry( SETTINGS + "allSuffixesLine", INDEX_FIELD + ". " + SUFFIX_FIELD + " " + MINI_LEX_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );

	// All Suffix Sigs
	m_allSuffixSigsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixSigsColumnTitlesFlag" ) );
	m_allSuffixSigsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixSigsUniformFieldWidthsFlag" ) );
	m_allSuffixSigsIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allSuffixSigsIncludeStemListFlag" ) );
	m_allSuffixSigsLine->setText( m_pSettings->readEntry( SETTINGS + "allSuffixSigsLine", INDEX_FIELD + ". " + SIGNATURE_FIELD + " " + MINI_LEX_FIELD + " " + ROBUSTNESS_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );

	// All Prefixes
	m_allPrefixesColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixesColumnTitlesFlag" ) );
	m_allPrefixesUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixesUniformFieldWidthsFlag" ) );
	m_allPrefixesIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixesIncludeStemListFlag" ) );
	m_allPrefixesLine->setText( m_pSettings->readEntry( SETTINGS + "allPrefixesLine", INDEX_FIELD + ". " + PREFIX_FIELD + " " + MINI_LEX_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );

	// All Prefix Sigs
	m_allPrefixSigsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixSigsColumnTitlesFlag" ) );
	m_allPrefixSigsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixSigsUniformFieldWidthsFlag" ) );
	m_allPrefixSigsIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allPrefixSigsIncludeStemListFlag" ) );
	m_allPrefixSigsLine->setText( m_pSettings->readEntry( SETTINGS + "allPrefixSigsLine", INDEX_FIELD + ". " + SIGNATURE_FIELD + " " + MINI_LEX_FIELD + " " + ROBUSTNESS_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );

	// All Stems
	m_allStemsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allStemsColumnTitlesFlag" ) );
	m_allStemsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "allStemsUniformFieldWidthsFlag" ) );
	m_allStemsLine->setText( m_pSettings->readEntry( SETTINGS + "allStemsLine", INDEX_FIELD + ". " + STEM_FIELD + " " + MINI_LEX_FIELD + " " + CORPUS_COUNT_FIELD + " " + SIGNATURE_FIELD ) );

	// Mini Words	
	m_miniWordsAnalyzedOnlyFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniWordsAnalyzedOnlyFlag" ) );
	m_miniWordsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniWordsColumnTitlesFlag" ) );
	m_miniWordsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniWordsUniformFieldWidthsFlag" ) );
	m_miniWordsAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniWordsAlphabeticalSortFlag" ) );
	m_miniWordsCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniWordsCorpusCountSortFlag" ) );
	m_miniWordsMorphemeCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniWordsMorphemeCountSortFlag" ) );
	m_miniWordsLine->setText( m_pSettings->readEntry( SETTINGS + "miniWordsLine", INDEX_FIELD + ". " + WORD_FIELD + " " + CORPUS_COUNT_FIELD + " " + SIGNATURE_FIELD + " " + PREFIX_FIELD + " " + STEM_FIELD + " " + SUFFIX_FIELD ) );

	// Mini Signatures
	m_miniSignaturesColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSignaturesColumnTitlesFlag" ) );
	m_miniSignaturesUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSignaturesUniformFieldWidthsFlag" ) );
	m_miniSignaturesIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSignaturesIncludeStemListFlag" ) );
	m_miniSignaturesAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSignaturesAlphabeticalSortFlag" ) );
	m_miniSignaturesCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSignaturesCorpusCountSortFlag" ) );
	m_miniSignaturesStemCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSignaturesStemCountSortFlag" ) );
	m_miniSignaturesLine->setText( m_pSettings->readEntry( SETTINGS + "miniSignaturesLine", INDEX_FIELD + ". " + SIGNATURE_FIELD + " " + ROBUSTNESS_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );

	// Mini Stems	
	m_miniStemsColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniStemsColumnTitlesFlag" ) );
	m_miniStemsUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniStemsUniformFieldWidthsFlag" ) );
	m_miniStemsAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniStemsAlphabeticalSortFlag" ) );
	m_miniStemsCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniStemsCorpusCountSortFlag" ) );
	m_miniStemsLine->setText( m_pSettings->readEntry( SETTINGS + "miniStemsLine", INDEX_FIELD + ". " + STEM_FIELD + " " + CORPUS_COUNT_FIELD + " " + SIGNATURE_FIELD ) );

	// Mini Suffixes
	m_miniSuffixesColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSuffixesColumnTitlesFlag" ) );
	m_miniSuffixesUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSuffixesUniformFieldWidthsFlag" ) );
	m_miniSuffixesIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSuffixesIncludeStemListFlag" ) );
	m_miniSuffixesAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSuffixesAlphabeticalSortFlag" ) );
	m_miniSuffixesCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSuffixesCorpusCountSortFlag" ) );
	m_miniSuffixesStemCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniSuffixesStemCountSortFlag" ) );
	m_miniSuffixesLine->setText( m_pSettings->readEntry( SETTINGS + "miniSuffixesLine", INDEX_FIELD + ". " + SUFFIX_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );
	
	// Mini Prefixes
	m_miniPrefixesColumnTitlesFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniPrefixesColumnTitlesFlag" ) );
	m_miniPrefixesUniformFieldWidthsFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniPrefixesUniformFieldWidthsFlag" ) );
	m_miniPrefixesIncludeStemListFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniPrefixesIncludeStemListFlag" ) );
	m_miniPrefixesAlphabeticalSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniPrefixesAlphabeticalSortFlag" ) );
	m_miniPrefixesCorpusCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniPrefixesCorpusCountSortFlag" ) );
	m_miniPrefixesStemCountSortFlag->setChecked( m_pSettings->readBoolEntry( SETTINGS + "miniPrefixesStemCountSortFlag" ) );
	m_miniPrefixesLine->setText( m_pSettings->readEntry( SETTINGS + "miniPrefixesLine", INDEX_FIELD + ". " + SUFFIX_FIELD + " " + CORPUS_COUNT_FIELD + " " + STEM_COUNT_FIELD ) );
	
	// Do updates
	validateProjectInformationSlot();
	updateStylesSlot();
}


void ExportWizard::save()
{
	// Project Information
	m_pSettings->writeEntry( SETTINGS + "projectName", m_projectName->text() );
	m_pSettings->writeEntry( SETTINGS + "language", m_language->text() );
	m_pSettings->writeEntry( SETTINGS + "researchers", m_researchers->text() );
	m_pSettings->writeEntry( SETTINGS + "brokenCorpusFlag", m_brokenCorpusFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsFlag", m_corpusWordsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundsFlag", m_compoundsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allWordsFlag", m_allWordsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixSigsFlag", m_allSuffixSigsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixSigsFlag", m_allPrefixSigsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allStemsFlag", m_allStemsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixesFlag", m_allSuffixesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixesFlag", m_allPrefixesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "wordsFlag", m_miniWordsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "signaturesFlag", m_miniSignaturesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "stemsFlag", m_miniStemsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "suffixesFlag", m_miniSuffixesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "prefixesFlag", m_miniPrefixesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "simpleTextFlag", m_simpleTextFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "markUpFlag", m_markUpFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "bothFlag", m_bothFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "outputDirectory", m_outputDirectory->text() );

	// Style Sheet
	m_pSettings->writeEntry( SETTINGS + "wordStyleColor", m_wordStyle->paletteForegroundColor().name() );
	m_pSettings->writeEntry( SETTINGS + "wordBoldFlag", m_wordBoldFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "wordItalicFlag", m_wordItalicFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "stemStyleColor", m_stemStyle->paletteForegroundColor().name() );
	m_pSettings->writeEntry( SETTINGS + "stemBoldFlag", m_stemBoldFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "stemItalicFlag", m_stemItalicFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "signatureStyleColor", m_signatureStyle->paletteForegroundColor().name() );
	m_pSettings->writeEntry( SETTINGS + "signatureBoldFlag", m_signatureBoldFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "signatureItalicFlag", m_signatureItalicFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "suffixStyleColor", m_suffixStyle->paletteForegroundColor().name() );
	m_pSettings->writeEntry( SETTINGS + "suffixBoldFlag", m_suffixBoldFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "suffixItalicFlag", m_suffixItalicFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "prefixStyleColor", m_prefixStyle->paletteForegroundColor().name() );
	m_pSettings->writeEntry( SETTINGS + "prefixBoldFlag", m_prefixBoldFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "prefixItalicFlag", m_prefixItalicFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundStyleColor", m_compoundStyle->paletteForegroundColor().name() );
	m_pSettings->writeEntry( SETTINGS + "compoundBoldFlag", m_compoundBoldFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundItalicFlag", m_compoundItalicFlag->isChecked() );

	// Corpus Words	
	m_pSettings->writeEntry( SETTINGS + "corpusWordsAnalyzedOnlyFlag", m_corpusWordsAnalyzedOnlyFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsColumnTitlesFlag", m_corpusWordsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsUniformFieldWidthsFlag", m_corpusWordsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsAlphabeticalSortFlag", m_corpusWordsAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsCorpusCountSortFlag", m_corpusWordsCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsMorphemeCountSortFlag", m_corpusWordsMorphemeCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsLine", m_corpusWordsLine->text() );
	m_pSettings->writeEntry( SETTINGS + "corpusWordsMorphemeFieldDelimiter", m_corpusWordsMorphemeFieldDelimiter->text() );
	
	// Compounds	
	m_pSettings->writeEntry( SETTINGS + "compoundsColumnTitlesFlag", m_compoundsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundsUniformFieldWidthsFlag", m_compoundsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundsAlphabeticalSortFlag", m_compoundsAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundsCorpusCountSortFlag", m_compoundsCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundsMorphemeCountSortFlag", m_compoundsMorphemeCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "compoundsLine", m_compoundsLine->text() );
	m_pSettings->writeEntry( SETTINGS + "compoundsMorphemeFieldDelimiter", m_compoundsMorphemeFieldDelimiter->text() );

	// Linkers
	m_pSettings->writeEntry( SETTINGS + "linkersColumnTitlesFlag", m_linkersColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "linkersUniformFieldWidthsFlag", m_linkersUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "linkersIncludeCompoundListFlag", m_linkersIncludeCompoundListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "linkersAlphabeticalSortFlag", m_linkersAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "linkersCorpusCountSortFlag", m_linkersCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "linkersLine", m_linkersLine->text() );

	// All Words
	m_pSettings->writeEntry( SETTINGS + "allWordsAnalyzedOnlyFlag", m_allWordsAnalyzedOnlyFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allWordsColumnTitlesFlag", m_allWordsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allWordsUniformFieldWidthsFlag", m_allWordsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allWordsLine", m_allWordsLine->text() );

	// All Suffixes
	m_pSettings->writeEntry( SETTINGS + "allSuffixesColumnTitlesFlag", m_allSuffixesColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixesUniformFieldWidthsFlag", m_allSuffixesUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixesIncludeStemListFlag", m_allSuffixesIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixesLine", m_allSuffixesLine->text() );

	// All Suffix Sigs
	m_pSettings->writeEntry( SETTINGS + "allSuffixSigsColumnTitlesFlag", m_allSuffixSigsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixSigsUniformFieldWidthsFlag", m_allSuffixSigsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixSigsIncludeStemListFlag", m_allSuffixSigsIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allSuffixSigsLine", m_allSuffixSigsLine->text() );

	// All Prefixes
	m_pSettings->writeEntry( SETTINGS + "allPrefixesColumnTitlesFlag", m_allPrefixesColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixesUniformFieldWidthsFlag", m_allPrefixesUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixesIncludeStemListFlag", m_allPrefixesIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixesLine", m_allPrefixesLine->text() );

	// All Prefix Sigs
	m_pSettings->writeEntry( SETTINGS + "allPrefixSigsColumnTitlesFlag", m_allPrefixSigsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixSigsUniformFieldWidthsFlag", m_allPrefixSigsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixSigsIncludeStemListFlag", m_allPrefixSigsIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allPrefixSigsLine", m_allPrefixSigsLine->text() );

	// All Stems
	m_pSettings->writeEntry( SETTINGS + "allStemsColumnTitlesFlag", m_allStemsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allStemsUniformFieldWidthsFlag", m_allStemsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "allStemsLine", m_allStemsLine->text() );
	
	// Mini Words	
	m_pSettings->writeEntry( SETTINGS + "miniWordsAnalyzedOnlyFlag", m_miniWordsAnalyzedOnlyFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniWordsColumnTitlesFlag", m_miniWordsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniWordsUniformFieldWidthsFlag", m_miniWordsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniWordsAlphabeticalSortFlag", m_miniWordsAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniWordsCorpusCountSortFlag", m_miniWordsCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniWordsMorphemeCountSortFlag", m_miniWordsMorphemeCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniWordsLine", m_miniWordsLine->text() );	

	// Mini Sigs
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesColumnTitlesFlag", m_miniSignaturesColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesUniformFieldWidthsFlag", m_miniSignaturesUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesIncludeStemListFlag", m_miniSignaturesIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesAlphabeticalSortFlag", m_miniSignaturesAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesCorpusCountSortFlag", m_miniSignaturesCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesStemCountSortFlag", m_miniSignaturesStemCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSignaturesLine", m_miniSignaturesLine->text() );
	
	// Mini Stems	
	m_pSettings->writeEntry( SETTINGS + "miniStemsColumnTitlesFlag", m_miniStemsColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniStemsUniformFieldWidthsFlag", m_miniStemsUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniStemsAlphabeticalSortFlag", m_miniStemsAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniStemsCorpusCountSortFlag", m_miniStemsCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniStemsLine", m_miniStemsLine->text() );	

	// Mini Suffixes
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesColumnTitlesFlag", m_miniSuffixesColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesUniformFieldWidthsFlag", m_miniSuffixesUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesIncludeStemListFlag", m_miniSuffixesIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesAlphabeticalSortFlag", m_miniSuffixesAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesCorpusCountSortFlag", m_miniSuffixesCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesStemCountSortFlag", m_miniSuffixesStemCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniSuffixesLine", m_miniSuffixesLine->text() );

	// Mini Prefixes
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesColumnTitlesFlag", m_miniPrefixesColumnTitlesFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesUniformFieldWidthsFlag", m_miniPrefixesUniformFieldWidthsFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesIncludeStemListFlag", m_miniPrefixesIncludeStemListFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesAlphabeticalSortFlag", m_miniPrefixesAlphabeticalSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesCorpusCountSortFlag", m_miniPrefixesCorpusCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesStemCountSortFlag", m_miniPrefixesStemCountSortFlag->isChecked() );
	m_pSettings->writeEntry( SETTINGS + "miniPrefixesLine", m_miniPrefixesLine->text() );
}


void ExportWizard::browseOutputDirSlot()
{
	QString outputDirectory = Q3FileDialog::getExistingDirectory( m_outputDirectory->text(),
																 this,
																 "get existing directory",
																 "Choose an existing directory",
																 TRUE );

	if( outputDirectory.length() > 0 ) m_outputDirectory->setText( outputDirectory );
}


void ExportWizard::corpusWordsCheckedSlot( bool b )
{
	setAppropriate( page( CORPUS_WORDS_FILE_PAGE ), b );
}


void ExportWizard::compoundsCheckedSlot( bool b )
{
	setAppropriate( page( COMPOUNDS_FILE_PAGE ), b );
}


void ExportWizard::allWordsCheckedSlot( bool b )
{
	setAppropriate( page( ALL_WORDS_FILE_PAGE ), b );
}


void ExportWizard::allSuffixSignaturesCheckedSlot( bool b )
{
	setAppropriate( page( ALL_SUFFIX_SIGNATURES_FILE_PAGE ), b );
}


void ExportWizard::allPrefixSignaturesCheckedSlot( bool b )
{
	setAppropriate( page( ALL_PREFIX_SIGNATURES_FILE_PAGE ), b );
}


void ExportWizard::allStemsCheckedSlot( bool b )
{
	setAppropriate( page( ALL_STEMS_FILE_PAGE ), b );
}


void ExportWizard::allSuffixesCheckedSlot( bool b )
{
	setAppropriate( page( ALL_SUFFIXES_FILE_PAGE ), b );
}


void ExportWizard::allPrefixesCheckedSlot( bool b )
{
	setAppropriate( page( ALL_PREFIXES_FILE_PAGE ), b );
}


void ExportWizard::wordsCheckedSlot( bool b )
{
	setAppropriate( page( MINI_WORDS_FILE_PAGE ), b );
}


void ExportWizard::signaturesCheckedSlot( bool b )
{
	setAppropriate( page( MINI_SIGNATURES_FILE_PAGE ), b );
}


void ExportWizard::stemsCheckedSlot( bool b )
{
	setAppropriate( page( MINI_STEMS_FILE_PAGE ), b );
}


void ExportWizard::suffixesCheckedSlot( bool b )
{
	setAppropriate( page( MINI_SUFFIXES_FILE_PAGE ), b );
}


void ExportWizard::prefixesCheckedSlot( bool b )
{
	setAppropriate( page( MINI_PREFIXES_FILE_PAGE ), b );
}
	
//unused parameter (bool b)
//void ExportWizard::simpleTextToggledSlot( bool b )  
void ExportWizard::simpleTextToggledSlot( )
{
	setAppropriate( page( STYLE_SHEET_PAGE ), FALSE );
}

//unused paramater (bool b) 
//void ExportWizard::markUpToggledSlot( bool b ) 
void ExportWizard::markUpToggledSlot(  ) 

{
	setAppropriate( page( STYLE_SHEET_PAGE ), TRUE );
}

//unused parameter (bool b)
//void ExportWizard::bothToggledSlot( bool b ) 
void ExportWizard::bothToggledSlot( )
{
	setAppropriate( page( STYLE_SHEET_PAGE ), TRUE );
}


void ExportWizard::validateProjectInformationSlot()
{
	// If no output directory has been chosen, disable
	if( m_outputDirectory->text().length() == 0 )
	{
		setNextEnabled( page(PROJECT_INFO_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
		
	// If no project name has been set, disable
	if( m_projectName->text().length() == 0 )
	{
		setNextEnabled( page(PROJECT_INFO_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}


	// Disable if the user chosen output directory 
	// doesn't exist
	QDir directory( m_outputDirectory->text() );
	if( !directory.exists() )
	{
		setNextEnabled( page(PROJECT_INFO_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	

	// If the project name is not already the 
	// final directory in the path
	QString projectName = m_projectName->text().simplifyWhiteSpace();
	int pos = m_outputDirectory->text().find( projectName );

	if( pos < 0 || static_cast <int> (m_outputDirectory->text().length() - projectName.length()) != pos ) //%%%% unsigned/signed int???
	{
		// Disable if the project directory can't be created
		if( !directory.exists( projectName ) )
		{
			if( projectName.length() > 0 )
			{
				if( directory.mkdir( projectName ) )
				{
					Q_ASSERT( directory.rmdir( projectName ) );
				}
				else
				{
					QMessageBox::warning( this, "Linguistica : Export Wizard",
										  "Not able to make a new directory in the\n"
										  "given output directory. Please check its\n"
										  "permission settings.\n\n",
										  QMessageBox::Ok, 0, 0 );

					setNextEnabled( page(PROJECT_INFO_PAGE), FALSE );
					setFinishEnabled( page(CONFIRMATION), FALSE );
					return;
				}
			}
		}
	}


	// Disable if user hasn't chosen at least
	// one output
	if( !m_brokenCorpusFlag->isChecked() &&
		!m_corpusWordsFlag->isChecked() &&
		!m_miniSignaturesFlag->isChecked() &&
		!m_compoundsFlag->isChecked() &&
		!m_allWordsFlag->isChecked() &&
		!m_allSuffixSigsFlag->isChecked() &&
		!m_allPrefixSigsFlag->isChecked() &&
		!m_allStemsFlag->isChecked() &&
		!m_allSuffixesFlag->isChecked() &&
		!m_allPrefixesFlag->isChecked() &&
		!m_miniSuffixesFlag->isChecked() &&
		!m_miniPrefixesFlag->isChecked() &&
		!m_miniWordsFlag->isChecked() &&
		!m_miniStemsFlag->isChecked() )
	{
		setNextEnabled( page(PROJECT_INFO_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}


	// Otherwise, enable next button and update
	// file names
	setNextEnabled( page(PROJECT_INFO_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	// Update the confirmation page
	QString confirmation = "", fileName, miniName;

	fileName = m_projectName->text();
	fileName.replace( " ", "_" );

	confirmation += "\t" + m_outputDirectory->text() + "/" + fileName + "/\n\n";

	if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
	{
		if( m_brokenCorpusFlag->isChecked() &&
			m_pLexicon->GetCorpus()->count() )
		{
			fileName =  m_projectName->text() + "_" + BROKEN_CORPUS_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_corpusWordsFlag->isChecked() &&
			m_pLexicon->GetWords() &&
			m_pLexicon->GetWords()->GetCount() )
		{
			fileName = m_projectName->text() + "_" + CORPUS_WORDS_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allWordsFlag->isChecked() &&
			m_pLexicon->GetAllWords() &&
			m_pLexicon->GetAllWords()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_WORDS_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allSuffixesFlag->isChecked() &&
			m_pLexicon->GetAllSuffixes() &&
			m_pLexicon->GetAllSuffixes()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_SUFFIXES_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allSuffixSigsFlag->isChecked() &&
			m_pLexicon->GetAllSuffixSigs() &&
			m_pLexicon->GetAllSuffixSigs()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_SUFFIX_SIGNATURES_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allStemsFlag->isChecked() &&
			m_pLexicon->GetAllStems() &&
			m_pLexicon->GetAllStems()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_STEMS_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allPrefixesFlag->isChecked() &&
			m_pLexicon->GetAllPrefixes() &&
			m_pLexicon->GetAllPrefixes()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_PREFIXES_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allPrefixSigsFlag->isChecked() &&
			m_pLexicon->GetAllPrefixSigs() &&
			m_pLexicon->GetAllPrefixSigs()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_PREFIX_SIGNATURES_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_compoundsFlag->isChecked() &&
			m_pLexicon->GetCompounds() &&
			m_pLexicon->GetCompounds()->GetCount() )
		{
			fileName = m_projectName->text() + "_" + COMPOUNDS_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";

			fileName = m_projectName->text() + "_" + LINKERS_FILE_TITLE + ".txt";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
 
		
		CMiniLexicon* pMini;
		for( int mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
		{	
			pMini = m_pLexicon->GetMiniLexicon(mini);
			if( !pMini || !pMini->GetWords() ) continue;
			
			miniName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 );

			if( m_miniWordsFlag->isChecked() &&
				pMini->GetWords() &&
				pMini->GetWords()->GetCount() )
			{
				fileName = miniName + MINI_WORDS_FILE_TITLE + ".txt";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniSuffixesFlag->isChecked() &&
				pMini->GetSuffixes() &&
				pMini->GetSuffixes()->GetCount() )
			{
				fileName = miniName + MINI_SUFFIXES_FILE_TITLE + ".txt";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniPrefixesFlag->isChecked() &&
				pMini->GetPrefixes() &&
				pMini->GetPrefixes()->GetCount() )
			{
				fileName = miniName + MINI_PREFIXES_FILE_TITLE + ".txt";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniSignaturesFlag->isChecked() &&
				pMini->GetSignatures() &&
				pMini->GetSignatures()->GetCount() )
			{
				fileName = miniName + MINI_SIGNATURES_FILE_TITLE + ".txt";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniStemsFlag->isChecked() &&
				pMini->GetStems() &&
				pMini->GetStems()->GetCount() )
			{
				fileName = miniName + MINI_STEMS_FILE_TITLE + ".txt";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
		}
	}
	
	if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
	{
		confirmation += "\t\tindex.html\n";

		fileName = m_projectName->text() + ".css";
		fileName.replace( " ", "_" );
		confirmation += "\t\t" + fileName + "\n";

		if( m_brokenCorpusFlag->isChecked() &&
			m_pLexicon->GetCorpus()->count() )
		{
			fileName =  m_projectName->text() + "_" + BROKEN_CORPUS_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_corpusWordsFlag->isChecked() &&
			m_pLexicon->GetWords() &&
			m_pLexicon->GetWords()->GetCount() )
		{
			fileName = m_projectName->text() + "_" + CORPUS_WORDS_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allWordsFlag->isChecked() &&
			m_pLexicon->GetAllWords() &&
			m_pLexicon->GetAllWords()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_WORDS_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allSuffixesFlag->isChecked() &&
			m_pLexicon->GetAllSuffixes() &&
			m_pLexicon->GetAllSuffixes()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_SUFFIXES_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allSuffixSigsFlag->isChecked() &&
			m_pLexicon->GetAllSuffixSigs() &&
			m_pLexicon->GetAllSuffixSigs()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_SUFFIX_SIGNATURES_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allStemsFlag->isChecked() &&
			m_pLexicon->GetAllStems() &&
			m_pLexicon->GetAllStems()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_STEMS_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allPrefixesFlag->isChecked() &&
			m_pLexicon->GetAllPrefixes() &&
			m_pLexicon->GetAllPrefixes()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_PREFIXES_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_allPrefixSigsFlag->isChecked() &&
			m_pLexicon->GetAllPrefixSigs() &&
			m_pLexicon->GetAllPrefixSigs()->count() )
		{
			fileName = m_projectName->text() + "_" + ALL_PREFIX_SIGNATURES_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
		if( m_compoundsFlag->isChecked() &&
			m_pLexicon->GetCompounds() &&
			m_pLexicon->GetCompounds()->GetCount() )
		{
			fileName = m_projectName->text() + "_" + COMPOUNDS_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";

			fileName = m_projectName->text() + "_" + LINKERS_FILE_TITLE + ".html";
			fileName.replace( " ", "_" );

			confirmation += "\t\t" + fileName + "\n";
		}
 
		
		CMiniLexicon* pMini;
		for( int mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
		{	
			pMini = m_pLexicon->GetMiniLexicon(mini);
			if( !pMini || !pMini->GetWords() ) continue;
			
			miniName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 );

			if( m_miniWordsFlag->isChecked() &&
				pMini->GetWords() &&
				pMini->GetWords()->GetCount() )
			{
				fileName = miniName + MINI_WORDS_FILE_TITLE + ".html";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniSuffixesFlag->isChecked() &&
				pMini->GetSuffixes() &&
				pMini->GetSuffixes()->GetCount() )
			{
				fileName = miniName + MINI_SUFFIXES_FILE_TITLE + ".html";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniPrefixesFlag->isChecked() &&
				pMini->GetPrefixes() &&
				pMini->GetPrefixes()->GetCount() )
			{
				fileName = miniName + MINI_PREFIXES_FILE_TITLE + ".html";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniSignaturesFlag->isChecked() &&
				pMini->GetSignatures() &&
				pMini->GetSignatures()->GetCount() )
			{
				fileName = miniName + MINI_SIGNATURES_FILE_TITLE + ".html";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
			if( m_miniStemsFlag->isChecked() &&
				pMini->GetStems() &&
				pMini->GetStems()->GetCount() )
			{
				fileName = miniName + MINI_STEMS_FILE_TITLE + ".html";
				fileName.replace( " ", "_" );

				confirmation += "\t\t" + fileName + "\n";
			}
		}
	}

	m_confirmation->setText( confirmation );
}


void ExportWizard::corpusWordsAddIndexButtonClickedSlot()
{
	QString line = m_corpusWordsLine->text();
	int cursor = m_corpusWordsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_corpusWordsLine->setText( line );
	m_corpusWordsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::corpusWordsAddWordButtonClickedSlot()
{
	QString line = m_corpusWordsLine->text();
	int cursor = m_corpusWordsLine->cursorPosition();

	line = line.insert( cursor, WORD_FIELD );

	m_corpusWordsLine->setText( line );
	m_corpusWordsLine->setCursorPosition( cursor + WORD_FIELD.length() );
}


void ExportWizard::corpusWordsAddCorpusCountButtonClickedSlot()
{
	QString line = m_corpusWordsLine->text();
	int cursor = m_corpusWordsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_corpusWordsLine->setText( line );
	m_corpusWordsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::corpusWordsAddMorphCountButtonClickedSlot()
{
	QString line = m_corpusWordsLine->text();
	int cursor = m_corpusWordsLine->cursorPosition();

	line = line.insert( cursor, MORPHS_COUNT_FIELD );

	m_corpusWordsLine->setText( line );
	m_corpusWordsLine->setCursorPosition( cursor + MORPHS_COUNT_FIELD.length() );
}


void ExportWizard::corpusWordsAddMorphsButtonClickedSlot()
{
	QString line = m_corpusWordsLine->text();
	int cursor = m_corpusWordsLine->cursorPosition();

	line = line.insert( cursor, MORPHS_FIELD );

	m_corpusWordsLine->setText( line );
	m_corpusWordsLine->setCursorPosition( cursor + MORPHS_FIELD.length() );
}


void ExportWizard::compoundsAddIndexButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::compoundsAddCompoundButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, COMPOUND_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + COMPOUND_FIELD.length() );
}


void ExportWizard::compoundsAddCorpusCountButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::compoundsAddMorphCountButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, MORPHS_COUNT_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + MORPHS_COUNT_FIELD.length() );
}


void ExportWizard::compoundsAddMorphsButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, MORPHS_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + MORPHS_FIELD.length() );
}


void ExportWizard::compoundsAddSuffixnessButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, SUFFIXNESS_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + SUFFIXNESS_FIELD.length() );
}


void ExportWizard::compoundsAddPrefixnessButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, PREFIXNESS_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + PREFIXNESS_FIELD.length() );
}


void ExportWizard::compoundsAddParseButtonClickedSlot()
{
	QString line = m_compoundsLine->text();
	int cursor = m_compoundsLine->cursorPosition();

	line = line.insert( cursor, PARSE_FIELD );

	m_compoundsLine->setText( line );
	m_compoundsLine->setCursorPosition( cursor + PARSE_FIELD.length() );
}


void ExportWizard::linkersAddIndexButtonClickedSlot()
{
	QString line = m_linkersLine->text();
	int cursor = m_linkersLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_linkersLine->setText( line );
	m_linkersLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::linkersAddLinkerButtonClickedSlot()
{
	QString line = m_linkersLine->text();
	int cursor = m_linkersLine->cursorPosition();

	line = line.insert( cursor, LINKER_FIELD );

	m_linkersLine->setText( line );
	m_linkersLine->setCursorPosition( cursor + LINKER_FIELD.length() );
}


void ExportWizard::linkersAddCorpusCountButtonClickedSlot()
{
	QString line = m_linkersLine->text();
	int cursor = m_linkersLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_linkersLine->setText( line );
	m_linkersLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::linkersAddCompoundCountButtonClickedSlot()
{
	QString line = m_linkersLine->text();
	int cursor = m_linkersLine->cursorPosition();

	line = line.insert( cursor, COMPOUND_COUNT_FIELD );

	m_linkersLine->setText( line );
	m_linkersLine->setCursorPosition( cursor + COMPOUND_COUNT_FIELD.length() );
}


void ExportWizard::allWordsAddIndexButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::allWordsAddWordButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, WORD_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + WORD_FIELD.length() );
}


void ExportWizard::allWordsAddMiniLexButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, MINI_LEX_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + MINI_LEX_FIELD.length() );
}


void ExportWizard::allWordsAddDescLengthButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::allWordsAddCorpusCountButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::allWordsAddTypeButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, TYPE_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + TYPE_FIELD.length() );
}


void ExportWizard::allWordsAddSignatureButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::allWordsAddSourceButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, SOURCE_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + SOURCE_FIELD.length() );
}


void ExportWizard::allWordsAddPrefixButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, PREFIX_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + PREFIX_FIELD.length() );
}


void ExportWizard::allWordsAddStemButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, STEM_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + STEM_FIELD.length() );
}


void ExportWizard::allWordsAddSuffixButtonClickedSlot()
{
	QString line = m_allWordsLine->text();
	int cursor = m_allWordsLine->cursorPosition();

	line = line.insert( cursor, SUFFIX_FIELD );

	m_allWordsLine->setText( line );
	m_allWordsLine->setCursorPosition( cursor + SUFFIX_FIELD.length() );
}


void ExportWizard::allStemsAddIndexButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::allStemsAddStemButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, STEM_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + STEM_FIELD.length() );
}


void ExportWizard::allStemsAddMiniLexButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, MINI_LEX_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + MINI_LEX_FIELD.length() );
}


void ExportWizard::allStemsAddDescLengthButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::allStemsAddCorpusCountButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::allStemsAddTypeButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, TYPE_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + TYPE_FIELD.length() );
}


void ExportWizard::allStemsAddSignatureButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::allStemsAddOriginButtonClickedSlot()
{
	QString line = m_allStemsLine->text();
	int cursor = m_allStemsLine->cursorPosition();

	line = line.insert( cursor, ORIGIN_FIELD );

	m_allStemsLine->setText( line );
	m_allStemsLine->setCursorPosition( cursor + ORIGIN_FIELD.length() );
}


void ExportWizard::allSuffixesAddIndexButtonClickedSlot()
{
	QString line = m_allSuffixesLine->text();
	int cursor = m_allSuffixesLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_allSuffixesLine->setText( line );
	m_allSuffixesLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::allSuffixesAddSuffixButtonClickedSlot()
{
	QString line = m_allSuffixesLine->text();
	int cursor = m_allSuffixesLine->cursorPosition();

	line = line.insert( cursor, SUFFIX_FIELD );

	m_allSuffixesLine->setText( line );
	m_allSuffixesLine->setCursorPosition( cursor + SUFFIX_FIELD.length() );
}


void ExportWizard::allSuffixesAddMiniLexButtonClickedSlot()
{
	QString line = m_allSuffixesLine->text();
	int cursor = m_allSuffixesLine->cursorPosition();

	line = line.insert( cursor, MINI_LEX_FIELD );

	m_allSuffixesLine->setText( line );
	m_allSuffixesLine->setCursorPosition( cursor + MINI_LEX_FIELD.length() );
}


void ExportWizard::allSuffixesAddDescLengthButtonClickedSlot()
{
	QString line = m_allSuffixesLine->text();
	int cursor = m_allSuffixesLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_allSuffixesLine->setText( line );
	m_allSuffixesLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::allSuffixesAddCorpusCountButtonClickedSlot()
{
	QString line = m_allSuffixesLine->text();
	int cursor = m_allSuffixesLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_allSuffixesLine->setText( line );
	m_allSuffixesLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::allSuffixesAddStemCountButtonClickedSlot()
{
	QString line = m_allSuffixesLine->text();
	int cursor = m_allSuffixesLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_allSuffixesLine->setText( line );
	m_allSuffixesLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddIndexButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddSignatureButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddMiniLexButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, MINI_LEX_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + MINI_LEX_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddDescLengthButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddCorpusCountButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddStemCountButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddExemplarButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, EXEMPLAR_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + EXEMPLAR_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddRemarksButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, REMARKS_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + REMARKS_FIELD.length() );
}


void ExportWizard::allSuffixSigsAddRobustnessButtonClickedSlot()
{
	QString line = m_allSuffixSigsLine->text();
	int cursor = m_allSuffixSigsLine->cursorPosition();

	line = line.insert( cursor, ROBUSTNESS_FIELD );

	m_allSuffixSigsLine->setText( line );
	m_allSuffixSigsLine->setCursorPosition( cursor + ROBUSTNESS_FIELD.length() );
}


void ExportWizard::allPrefixesAddIndexButtonClickedSlot()
{
	QString line = m_allPrefixesLine->text();
	int cursor = m_allPrefixesLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_allPrefixesLine->setText( line );
	m_allPrefixesLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::allPrefixesAddPrefixButtonClickedSlot()
{
	QString line = m_allPrefixesLine->text();
	int cursor = m_allPrefixesLine->cursorPosition();

	line = line.insert( cursor, PREFIX_FIELD );

	m_allPrefixesLine->setText( line );
	m_allPrefixesLine->setCursorPosition( cursor + PREFIX_FIELD.length() );
}


void ExportWizard::allPrefixesAddMiniLexButtonClickedSlot()
{
	QString line = m_allPrefixesLine->text();
	int cursor = m_allPrefixesLine->cursorPosition();

	line = line.insert( cursor, MINI_LEX_FIELD );

	m_allPrefixesLine->setText( line );
	m_allPrefixesLine->setCursorPosition( cursor + MINI_LEX_FIELD.length() );
}


void ExportWizard::allPrefixesAddDescLengthButtonClickedSlot()
{
	QString line = m_allPrefixesLine->text();
	int cursor = m_allPrefixesLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_allPrefixesLine->setText( line );
	m_allPrefixesLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::allPrefixesAddCorpusCountButtonClickedSlot()
{
	QString line = m_allPrefixesLine->text();
	int cursor = m_allPrefixesLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_allPrefixesLine->setText( line );
	m_allPrefixesLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::allPrefixesAddStemCountButtonClickedSlot()
{
	QString line = m_allPrefixesLine->text();
	int cursor = m_allPrefixesLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_allPrefixesLine->setText( line );
	m_allPrefixesLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddIndexButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddSignatureButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddMiniLexButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, MINI_LEX_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + MINI_LEX_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddDescLengthButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddCorpusCountButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddStemCountButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddExemplarButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, EXEMPLAR_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + EXEMPLAR_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddRemarksButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, REMARKS_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + REMARKS_FIELD.length() );
}


void ExportWizard::allPrefixSigsAddRobustnessButtonClickedSlot()
{
	QString line = m_allPrefixSigsLine->text();
	int cursor = m_allPrefixSigsLine->cursorPosition();

	line = line.insert( cursor, ROBUSTNESS_FIELD );

	m_allPrefixSigsLine->setText( line );
	m_allPrefixSigsLine->setCursorPosition( cursor + ROBUSTNESS_FIELD.length() );
}


void ExportWizard::miniWordsAddIndexButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::miniWordsAddWordButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, WORD_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + WORD_FIELD.length() );
}


void ExportWizard::miniWordsAddDescLengthButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::miniWordsAddCorpusCountButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::miniWordsAddTypeButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, TYPE_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + TYPE_FIELD.length() );
}


void ExportWizard::miniWordsAddSignatureButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::miniWordsAddSourceButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, SOURCE_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + SOURCE_FIELD.length() );
}


void ExportWizard::miniWordsAddPrefixButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, PREFIX_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + PREFIX_FIELD.length() );
}


void ExportWizard::miniWordsAddStemButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, STEM_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + STEM_FIELD.length() );
}


void ExportWizard::miniWordsAddSuffixButtonClickedSlot()
{
	QString line = m_miniWordsLine->text();
	int cursor = m_miniWordsLine->cursorPosition();

	line = line.insert( cursor, SUFFIX_FIELD );

	m_miniWordsLine->setText( line );
	m_miniWordsLine->setCursorPosition( cursor + SUFFIX_FIELD.length() );
}


void ExportWizard::miniSignaturesAddIndexButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::miniSignaturesAddSignatureButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::miniSignaturesAddDescLengthButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::miniSignaturesAddCorpusCountButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::miniSignaturesAddStemCountButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}


void ExportWizard::miniSignaturesAddExemplarButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, EXEMPLAR_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + EXEMPLAR_FIELD.length() );
}


void ExportWizard::miniSignaturesAddRemarksButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, REMARKS_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + REMARKS_FIELD.length() );
}


void ExportWizard::miniSignaturesAddRobustnessButtonClickedSlot()
{
	QString line = m_miniSignaturesLine->text();
	int cursor = m_miniSignaturesLine->cursorPosition();

	line = line.insert( cursor, ROBUSTNESS_FIELD );

	m_miniSignaturesLine->setText( line );
	m_miniSignaturesLine->setCursorPosition( cursor + ROBUSTNESS_FIELD.length() );
}


void ExportWizard::miniStemsAddIndexButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::miniStemsAddStemButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, STEM_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + STEM_FIELD.length() );
}


void ExportWizard::miniStemsAddDescLengthButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::miniStemsAddCorpusCountButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::miniStemsAddTypeButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, TYPE_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + TYPE_FIELD.length() );
}


void ExportWizard::miniStemsAddSignatureButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, SIGNATURE_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + SIGNATURE_FIELD.length() );
}


void ExportWizard::miniStemsAddOriginButtonClickedSlot()
{
	QString line = m_miniStemsLine->text();
	int cursor = m_miniStemsLine->cursorPosition();

	line = line.insert( cursor, ORIGIN_FIELD );

	m_miniStemsLine->setText( line );
	m_miniStemsLine->setCursorPosition( cursor + ORIGIN_FIELD.length() );
}


void ExportWizard::miniSuffixesAddIndexButtonClickedSlot()
{
	QString line = m_miniSuffixesLine->text();
	int cursor = m_miniSuffixesLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_miniSuffixesLine->setText( line );
	m_miniSuffixesLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::miniSuffixesAddSuffixButtonClickedSlot()
{
	QString line = m_miniSuffixesLine->text();
	int cursor = m_miniSuffixesLine->cursorPosition();

	line = line.insert( cursor, SUFFIX_FIELD );

	m_miniSuffixesLine->setText( line );
	m_miniSuffixesLine->setCursorPosition( cursor + SUFFIX_FIELD.length() );
}


void ExportWizard::miniSuffixesAddDescLengthButtonClickedSlot()
{
	QString line = m_miniSuffixesLine->text();
	int cursor = m_miniSuffixesLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_miniSuffixesLine->setText( line );
	m_miniSuffixesLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::miniSuffixesAddCorpusCountButtonClickedSlot()
{
	QString line = m_miniSuffixesLine->text();
	int cursor = m_miniSuffixesLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_miniSuffixesLine->setText( line );
	m_miniSuffixesLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::miniSuffixesAddStemCountButtonClickedSlot()
{
	QString line = m_miniSuffixesLine->text();
	int cursor = m_miniSuffixesLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_miniSuffixesLine->setText( line );
	m_miniSuffixesLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}


void ExportWizard::miniPrefixesAddIndexButtonClickedSlot()
{
	QString line = m_miniPrefixesLine->text();
	int cursor = m_miniPrefixesLine->cursorPosition();

	line = line.insert( cursor, INDEX_FIELD );

	m_miniPrefixesLine->setText( line );
	m_miniPrefixesLine->setCursorPosition( cursor + INDEX_FIELD.length() );
}


void ExportWizard::miniPrefixesAddPrefixButtonClickedSlot()
{
	QString line = m_miniPrefixesLine->text();
	int cursor = m_miniPrefixesLine->cursorPosition();

	line = line.insert( cursor, PREFIX_FIELD );

	m_miniPrefixesLine->setText( line );
	m_miniPrefixesLine->setCursorPosition( cursor + PREFIX_FIELD.length() );
}


void ExportWizard::miniPrefixesAddDescLengthButtonClickedSlot()
{
	QString line = m_miniPrefixesLine->text();
	int cursor = m_miniPrefixesLine->cursorPosition();

	line = line.insert( cursor, DESC_LENGTH_FIELD );

	m_miniPrefixesLine->setText( line );
	m_miniPrefixesLine->setCursorPosition( cursor + DESC_LENGTH_FIELD.length() );
}


void ExportWizard::miniPrefixesAddCorpusCountButtonClickedSlot()
{
	QString line = m_miniPrefixesLine->text();
	int cursor = m_miniPrefixesLine->cursorPosition();

	line = line.insert( cursor, CORPUS_COUNT_FIELD );

	m_miniPrefixesLine->setText( line );
	m_miniPrefixesLine->setCursorPosition( cursor + CORPUS_COUNT_FIELD.length() );
}


void ExportWizard::miniPrefixesAddStemCountButtonClickedSlot()
{
	QString line = m_miniPrefixesLine->text();
	int cursor = m_miniPrefixesLine->cursorPosition();

	line = line.insert( cursor, STEM_COUNT_FIELD );

	m_miniPrefixesLine->setText( line );
	m_miniPrefixesLine->setCursorPosition( cursor + STEM_COUNT_FIELD.length() );
}

QString ExportWizard::getCorpusWordMorphsField( CCorpusWord* pCorpusWord, bool markUpFlag )
{
	QString field = "", 
			type = "",
			url = m_projectName->text() + "_" + ALL_WORDS_FILE_TITLE + ".html";

	bool do_not_link_words = !m_allWordsFlag->isChecked() || m_allWordsAnalyzedOnlyFlag->isChecked();

	url.replace( " ", "_" );

//	StringToString* filter = m_pLexicon->GetOutFilter();  unused variable 'filter'

	CLParse* pLParse;

	for( int i = 1; i < pCorpusWord->Size(); i++ )
	{
		// All but the last piece with following delimiter
		pLParse = pCorpusWord->GetMorpheme(i);
		if( !pLParse ) continue;

		field += getLParseText( pLParse, markUpFlag );
		field += m_corpusWordsMorphemeFieldDelimiter->text();
	}
	
	// Last piece
	pLParse = pCorpusWord->GetMorpheme( pCorpusWord->Size() );
	if( !pLParse ) return field + "ERROR";

	if( pCorpusWord->Size() > 1 ) field += getLParseText( pLParse, markUpFlag );
	else field += getLParseText( pLParse, markUpFlag, do_not_link_words, "word", url );

	return field;
}


QString ExportWizard::getCompoundMorphsField( CCompound* pCompound, bool markUpFlag )
{
	QString field = "", 
			type = "",
			url = m_projectName->text() + "_" + ALL_WORDS_FILE_TITLE + ".html",
			linkerUrl = m_projectName->text() + "_" + LINKERS_FILE_TITLE + ".html";

	url.replace( " ", "_" );
	linkerUrl.replace( " ", "_" );

//	StringToString* filter = m_pLexicon->GetOutFilter(); unused variable 'filter'

	CLParse* pLParse;
	StemSet* pStems;

	for( int i = 1; i < pCompound->Size(); i++ )
	{
		// All but the last piece with following delimiter
		pStems = pCompound->GetComponent(i);
		if( pStems ) 
		{
			if( m_pLexicon->GetAllStems()->find( pStems->first()->Display() ) )
			{
				field += getLParseText( pStems->first(), markUpFlag );
				field += m_compoundsMorphemeFieldDelimiter->text();
			}
			else 
			{
				field += getLParseText( pStems->first(), markUpFlag, FALSE, "word", url );
				field += m_compoundsMorphemeFieldDelimiter->text();
			}
		}
		else
		{
			pLParse = pCompound->GetLinker(i);
			if( pLParse )
			{
				field += getLParseText( pLParse, markUpFlag, FALSE, "suffix", linkerUrl );
				field += m_compoundsMorphemeFieldDelimiter->text();
			}
		}
	}
	
	// Last piece
	pStems = pCompound->GetComponent( pCompound->Size() );
	if( !pStems ) return field + "ERROR";

	if( m_pLexicon->GetAllStems()->find( pStems->first()->Display() ) )
		field += getLParseText( pStems->first(), markUpFlag );
	else 
		field += getLParseText( pStems->first(), markUpFlag, FALSE, "word", url );

	return field;
}
	

void ExportWizard::updateCorpusWordsExampleSlot()
{
	if( !m_corpusWordsFlag->isChecked() ) return;
	if( m_pLexicon->GetWords()->GetCount() == 0 ) return;

	CCorpusWord* pCorpusWord=NULL; 
	QString example = "", 
			line = m_corpusWordsLine->text(),
			field;

	int i, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	for( i = 0; i < m_pLexicon->GetWords()->GetCount(); i++ )
	{
		pCorpusWord = m_pLexicon->GetWords()->GetAt(i);
		if( pCorpusWord->Size() > 1 ) break;
	}

	if( line.count( "%" ) % 2 == 1 )
	{
		m_corpusWordsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(CORPUS_WORDS_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(CORPUS_WORDS_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == WORD_FIELD )
		{
			example += pCorpusWord->Display( filter );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pCorpusWord->GetCorpusCount() );
		}
		if( field == MORPHS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pCorpusWord->Size() );
		}
		if( field == MORPHS_FIELD )
		{
			example += getCorpusWordMorphsField( pCorpusWord );
		}

		line = line.mid( end + 1 );
	}
		
	m_corpusWordsExampleText->setText( example );
}
	

void ExportWizard::updateCompoundsExampleSlot()
{
	if( !m_compoundsFlag->isChecked() ) return;
	if( m_pLexicon->GetCompounds()->GetCount() == 0 ) return;

	CCompound* pCompound=NULL;	
	QString example = "", 
			line = m_compoundsLine->text(),
			field;

	int i, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	for( i = 0; i < m_pLexicon->GetCompounds()->GetCount(); i++ )
	{
		pCompound = m_pLexicon->GetCompounds()->GetAt(i);
		if( pCompound->Size() > 1 ) break;
	}

	if( line.count( "%" ) % 2 == 1 )
	{
		m_compoundsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(COMPOUNDS_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(COMPOUNDS_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == COMPOUND_FIELD )
		{
			example += pCompound->Display(  filter );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pCompound->GetCorpusCount() );
		}
		if( field == MORPHS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pCompound->Size() );
		}
		if( field == MORPHS_FIELD )
		{
			example += getCompoundMorphsField( pCompound );
		}
		if( field == SUFFIXNESS_FIELD )
		{
			example += QString( "%1" ).arg( pCompound->GetSuffixness() );
		}
		if( field == PREFIXNESS_FIELD )
		{
			example += QString( "%1" ).arg( pCompound->GetPrefixness() );
		}

		line = line.mid( end + 1 );
	}
		
	m_compoundsExampleText->setText( example );
}
	

void ExportWizard::updateLinkersExampleSlot()
{
	if( !m_compoundsFlag->isChecked() ) return;
	if( m_pLexicon->GetLinkers()->GetCount() == 0 ) return;


	CLinker* pLinker;

	QString example = "", 
			line = m_linkersLine->text(),
			field;

	int start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	pLinker = m_pLexicon->GetLinkers()->GetAt(0);

	if( line.count( "%" ) % 2 == 1 )
	{
		m_linkersExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(LINKERS_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(LINKERS_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg(1);
		}
		if( field == LINKER_FIELD )
		{
			example += pLinker->Display( filter );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pLinker->GetCorpusCount() );
		}
		if( field == COMPOUND_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pLinker->GetCompoundCount() );
		}

		line = line.mid( end + 1 );
	}
		
	m_linkersExampleText->setText( example );	
}


void ExportWizard::updateAllWordsExampleSlot()
{
	if( !m_allWordsFlag->isChecked() ) return;
	if( m_pLexicon->GetAllWords()->count() == 0 ) return;

	CStem* pWord;
	pWord=NULL;
		
	CSignature* pSig;	
	pSig=NULL;
	
	QString example = "", 
			line = m_allWordsLine->text(),
			field;

	int i = 0, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	// Find the first analyzed word
	Q3DictIterator<StemSet> it( *m_pLexicon->GetAllWords() );
	for( ; it.current(); ++it )
	{
		i++;

		pWord = it.current()->first();
		
		if( !pWord ) continue;

		pSig = pWord->GetSuffixSignature();
		if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
		if( !pSig ) continue;

		if( pSig->Size() > 1 ) break;
	}

	// Make sure the line is formatted appropriately
	if( line.count( "%" ) % 2 == 1 )
	{
		m_allWordsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(ALL_WORDS_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(ALL_WORDS_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == WORD_FIELD )
		{
			example += pWord->Display(  filter );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pWord->GetCorpusCount() );
		}
		if( field == MINI_LEX_FIELD )
		{
			example += QString( "%1" ).arg( pWord->GetMyMini()->GetIndex() + 1 );
		}
		if( field == DESC_LENGTH_FIELD )
		{
			example += QString( "%1" ).arg( pWord->CalculateDL() );
		}
		if( field == TYPE_FIELD )
		{
			example += pWord->DisplayStemType();
		}
		if( field == SIGNATURE_FIELD )
		{
			if( pSig ) example += getLParseText( pSig );
			else example += " ";
		}
		if( field == SOURCE_FIELD )
		{
			if( pSig ) example += pSig->GetRemark();
			else example += pWord->GetConfidence();
		}
		if( field == PREFIX_FIELD )
		{
			example += pWord->GetPiece( pWord->GetPrefixLoc() ).Display( filter );
		}
		if( field == STEM_FIELD )
		{
			example += pWord->GetStem().Display( filter );
		}
		if( field == SUFFIX_FIELD )
		{
			example += pWord->GetPiece( pWord->GetSuffixLoc() ).Display( filter );
		}

		line = line.mid( end + 1 );
	}
		
	m_allWordsExampleText->setText( example );
}


void ExportWizard::updateAllStemsExampleSlot()
{
	if( !m_allStemsFlag->isChecked() ) return;
	if( m_pLexicon->GetAllStems()->count() == 0 ) return;

	CStem* pStem;
	pStem=NULL;
		
	CSignature* pSig;	
	pSig=NULL;
	
	QString example = "", 
			line = m_allStemsLine->text(),
			field;

	int i = 0, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	// Find the first analyzed word
	Q3DictIterator<StemSet> it( *m_pLexicon->GetAllStems() );
	for( ; it.current(); ++it )
	{
		i++;

		pStem = it.current()->first();
		
		if( !pStem ) continue;

		pSig = pStem->GetSuffixSignature();
		if( pSig == NULL ) pSig = pStem->GetPrefixSignature();
		if( !pSig ) continue;

		if( pSig->Size() > 1 ) break;
	}

	// Make sure the line is formatted appropriately
	if( line.count( "%" ) % 2 == 1 )
	{
		m_allStemsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(ALL_STEMS_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(ALL_STEMS_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == STEM_FIELD )
		{
			example += pStem->Display(  filter );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pStem->GetCorpusCount() );
		}
		if( field == MINI_LEX_FIELD )
		{
			example += QString( "%1" ).arg( pStem->GetMyMini()->GetIndex() + 1 );
		}
		if( field == DESC_LENGTH_FIELD )
		{
			example += QString( "%1" ).arg( pStem->CalculateDL() );
		}
		if( field == TYPE_FIELD )
		{
			example += pStem->DisplayStemType();
		}
		if( field == ORIGIN_FIELD )
		{
			example += pStem->GetConfidence();
		}
		if( field == SIGNATURE_FIELD )
		{
			if( pSig ) example += pSig->Display( '.', filter );
			else example += " ";
		}

		line = line.mid( end + 1 );
	}
		
	m_allStemsExampleText->setText( example );
}


void ExportWizard::updateAllSuffixesExampleSlot()
{
	if( !m_allSuffixesFlag->isChecked() ) return;
	if( m_pLexicon->GetAllSuffixes()->count() == 0 ) return;

	CSuffix* pSuffix;	
	pSuffix=NULL;
	
	QString example = "", 
			line = m_allSuffixesLine->text(),
			field;

	int i, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	// Find the first analyzed
	i = m_pLexicon->GetAllSuffixes()->count();
	Q3DictIterator<SuffixSet> it( *m_pLexicon->GetAllSuffixes() );
	for( ; it.current(); ++it )
	{
		i--;
		pSuffix = it.current()->last();
		if( pSuffix ) break;
	}

	// Make sure the line is formatted appropriately
	if( line.count( "%" ) % 2 == 1 )
	{
		m_allSuffixesExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(ALL_SUFFIXES_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(ALL_SUFFIXES_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == SUFFIX_FIELD )
		{
			example += pSuffix->Display( '.', filter );
		}
		if( field == MINI_LEX_FIELD )
		{
			example += QString( "%1" ).arg( pSuffix->GetMyMini()->GetIndex() + 1 );
		}
		if( field == DESC_LENGTH_FIELD )
		{
			example += QString( "%1" ).arg( pSuffix->ComputeDL() );
		}
		if( field == STEM_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pSuffix->GetStems()->count() );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pSuffix->GetCorpusCount() );
		}

		line = line.mid( end + 1 );
	}
		
	m_allSuffixesExampleText->setText( example );
}


void ExportWizard::updateAllPrefixesExampleSlot()
{
	if( !m_allPrefixesFlag->isChecked() ) return;
	if( m_pLexicon->GetAllPrefixes()->count() == 0 ) return;

	CPrefix* pPrefix;	
	pPrefix=NULL;
	
	QString example = "", 
			line = m_allPrefixesLine->text(),
			field;

	int i, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	// Find the first analyzed word
	i = m_pLexicon->GetAllPrefixes()->count();
	Q3DictIterator<PrefixSet> it( *m_pLexicon->GetAllPrefixes() );
	for( ; it.current(); ++it )
	{
		i--;
		pPrefix = it.current()->last();
		if( pPrefix ) break;
	}

	// Make sure the line is formatted appropriately
	if( line.count( "%" ) % 2 == 1 )
	{
		m_allPrefixesExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(ALL_PREFIXES_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(ALL_PREFIXES_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == PREFIX_FIELD )
		{
			example += pPrefix->Display( '.', filter );
		}
		if( field == MINI_LEX_FIELD )
		{
			example += QString( "%1" ).arg( pPrefix->GetMyMini()->GetIndex() + 1 );
		}
		if( field == DESC_LENGTH_FIELD )
		{
			example += QString( "%1" ).arg( pPrefix->ComputeDL() );
		}
		if( field == STEM_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pPrefix->GetStems()->count() );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pPrefix->GetCorpusCount() );
		}

		line = line.mid( end + 1 );
	}
		
	m_allPrefixesExampleText->setText( example );
}


void ExportWizard::updateAllSuffixSigsExampleSlot()
{
	if( !m_allSuffixSigsFlag->isChecked() ) return;
	if( m_pLexicon->GetAllSuffixSigs()->count() == 0 ) return;

	CSignature* pSig;	
	pSig=NULL;
	
	QString example = "", 
			line = m_allSuffixSigsLine->text(),
			field;

	int i = 0, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	// Find the first analyzed word
	i = m_pLexicon->GetAllSuffixSigs()->count();
	Q3DictIterator<SignatureSet> it( *m_pLexicon->GetAllSuffixSigs() );
	for( ; it.current(); ++it )
	{
		pSig = it.current()->first();
		if( pSig->Size() > 1 ) break;
		i++;
	}

	// Make sure the line is formatted appropriately
	if( line.count( "%" ) % 2 == 1 )
	{
		m_allSuffixSigsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(ALL_SUFFIX_SIGNATURES_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(ALL_SUFFIX_SIGNATURES_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == SIGNATURE_FIELD )
		{
			example += pSig->Display( '.', filter );
		}
		if( field == MINI_LEX_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetMyMini()->GetIndex() + 1 );
		}
		if( field == DESC_LENGTH_FIELD )
		{
			example += QString( "%1" ).arg( pSig->ComputeDLofModel() );
		}
		if( field == STEM_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetStemPtrList()->count() );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetCorpusCount() );
		}
		if( field == EXEMPLAR_FIELD )
		{
                        example += pSig->GetStemPtrList()->first()->Display( filter );
		}
		if( field == REMARKS_FIELD )
		{
			example += pSig->GetRemark();
		}
		if( field == ROBUSTNESS_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetRobustness() );
		}

		line = line.mid( end + 1 );
	}
		
	m_allSuffixSigsExampleText->setText( example );
}



void ExportWizard::updateAllPrefixSigsExampleSlot()
{
	if( !m_allPrefixSigsFlag->isChecked() ) return;
	if( m_pLexicon->GetAllPrefixSigs()->count() == 0 ) return;

	CSignature* pSig;	
	pSig=NULL;
	
	QString example = "", 
			line = m_allPrefixSigsLine->text(),
			field;

	int i = 0, start, end;

	StringToString* filter = m_pLexicon->GetOutFilter();

	// Find the first analyzed word
	i = m_pLexicon->GetAllPrefixSigs()->count();
	Q3DictIterator<SignatureSet> it( *m_pLexicon->GetAllPrefixSigs() );
	for( ; it.current(); ++it )
	{
		pSig = it.current()->first();
		if( pSig->Size() > 1 ) break;
		i++;
	}

	// Make sure the line is formatted appropriately
	if( line.count( "%" ) % 2 == 1 )
	{
		m_allPrefixSigsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
	
		setNextEnabled( page(ALL_PREFIX_SIGNATURES_FILE_PAGE), FALSE );
		setFinishEnabled( page(CONFIRMATION), FALSE );
		return;
	}
	
	setNextEnabled( page(ALL_PREFIX_SIGNATURES_FILE_PAGE), TRUE );
	setFinishEnabled( page(CONFIRMATION), TRUE );

	while( line.length() > 0 )
	{
		start = line.find( "%" );

		if( start < 0 ) 
		{
			example += line;
			break;
		}

		example += line.left( start );
		line = line.mid( start );
		end = line.find( "%", 1 );
		field = line.mid( 0, end + 1 );

		if( field == INDEX_FIELD )
		{
			example += QString( "%1" ).arg( i + 1 );
		}
		if( field == SIGNATURE_FIELD )
		{
			example += pSig->Display( '.', filter );
		}
		if( field == MINI_LEX_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetMyMini()->GetIndex() + 1 );
		}
		if( field == DESC_LENGTH_FIELD )
		{
			example += QString( "%1" ).arg( pSig->ComputeDLofModel() );
		}
		if( field == STEM_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetStemPtrList()->count() );
		}
		if( field == CORPUS_COUNT_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetCorpusCount() );
		}
		if( field == EXEMPLAR_FIELD )
		{
                        example += pSig->GetStemPtrList()->first()->Display( filter );
		}
		if( field == REMARKS_FIELD )
		{
			example += pSig->GetRemark();
		}
		if( field == ROBUSTNESS_FIELD )
		{
			example += QString( "%1" ).arg( pSig->GetRobustness() );
		}

		line = line.mid( end + 1 );
	}
		
	m_allPrefixSigsExampleText->setText( example );
}
	

void ExportWizard::updateMiniWordsExampleSlot()
{
	if( !m_miniWordsFlag->isChecked() ) return;
	if( m_pLexicon->GetMiniCount() == 0 ) return;

	int mini;
	CMiniLexicon* pMini;
	for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
	{	
		pMini = m_pLexicon->GetMiniLexicon(mini);
		if( !pMini || !pMini->GetWords() ) continue;
		if( pMini->GetWords()->GetCount() == 0 ) continue;

		CStem* pWord;	
		pWord=NULL;
		
		CSignature* pSig;

		QString example = "", 
				line = m_miniWordsLine->text(),
				field;

		int i, start, end;

		StringToString* filter = m_pLexicon->GetOutFilter();

		for( i = 0; i < pMini->GetWords()->GetCount(); i++ )
		{
			pWord = pMini->GetWords()->GetAt(i);
			if( pWord->Size() > 1 ) break;
		}

		if( line.count( "%" ) % 2 == 1 )
		{
			m_miniWordsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
		
			setNextEnabled( page(MINI_WORDS_FILE_PAGE), FALSE );
			setFinishEnabled( page(CONFIRMATION), FALSE );
			return;
		}
		 
		if( pWord->Size() > 1 )
		{
			pSig = pWord->GetSuffixSignature();
			if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
		}
		else pSig = NULL;
		
		setNextEnabled( page(MINI_WORDS_FILE_PAGE), TRUE );
		setFinishEnabled( page(CONFIRMATION), TRUE );

		while( line.length() > 0 )
		{
			start = line.find( "%" );

			if( start < 0 ) 
			{
				example += line;
				break;
			}

			example += line.left( start );
			line = line.mid( start );
			end = line.find( "%", 1 );
			field = line.mid( 0, end + 1 );

			if( field == INDEX_FIELD )
			{
				example += QString( "%1" ).arg( i + 1 );
			}
			if( field == WORD_FIELD )
			{
				example += pWord->Display( filter );
			}
			if( field == CORPUS_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pWord->GetCorpusCount() );
			}
			if( field == DESC_LENGTH_FIELD )
			{
				example += QString( "%1" ).arg( pWord->CalculateDL() );
			}
			if( field == TYPE_FIELD )
			{
				example += pWord->DisplayStemType();
			}
			if( field == SIGNATURE_FIELD )
			{
				if( pSig ) example += getLParseText( pSig );
				else example += "";
			}
			if( field == SOURCE_FIELD )
			{
				if( pSig ) example += pSig->GetRemark();
				else example += pWord->GetConfidence();
			}
			if( field == PREFIX_FIELD )
			{
				example += pWord->GetPiece( pWord->GetPrefixLoc() ).Display( filter );
			}
			if( field == STEM_FIELD )
			{
				example += pWord->GetStem().Display( filter );
			}
			if( field == SUFFIX_FIELD )
			{
				example += pWord->GetPiece( pWord->GetSuffixLoc() ).Display( filter );
			}

			line = line.mid( end + 1 );
		}
			
		m_miniWordsExampleText->setText( example );	
	}
}
	

void ExportWizard::updateMiniSignaturesExampleSlot()
{
	if( !m_miniSignaturesFlag->isChecked() ) return;
	if( m_pLexicon->GetMiniCount() == 0 ) return;

	int mini;
	CMiniLexicon* pMini;
	for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
	{	
		pMini = m_pLexicon->GetMiniLexicon(mini);
		if( !pMini || !pMini->GetSignatures() ) continue;
		if( pMini->GetSignatures()->GetCount() == 0 ) continue;

		CSignature* pSig;	
		pSig=NULL;

		QString example = "", 
				line = m_miniSignaturesLine->text(),
				field;

		int i, start, end;

		StringToString* filter = m_pLexicon->GetOutFilter();

		for( i = 0; i < pMini->GetSignatures()->GetCount(); i++ )
		{
			pSig = pMini->GetSignatures()->GetAt(i);
			if( pSig->Size() > 1 ) break;
		}

		if( line.count( "%" ) % 2 == 1 )
		{
			m_miniSignaturesExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
		
			setNextEnabled( page(MINI_SIGNATURES_FILE_PAGE), FALSE );
			setFinishEnabled( page(CONFIRMATION), FALSE );
			return;
		}
		
		setNextEnabled( page(MINI_SIGNATURES_FILE_PAGE), TRUE );
		setFinishEnabled( page(CONFIRMATION), TRUE );

		while( line.length() > 0 )
		{
			start = line.find( "%" );

			if( start < 0 ) 
			{
				example += line;
				break;
			}

			example += line.left( start );
			line = line.mid( start );
			end = line.find( "%", 1 );
			field = line.mid( 0, end + 1 );

			if( field == INDEX_FIELD )
			{
				example += QString( "%1" ).arg( i + 1 );
			}
			if( field == SIGNATURE_FIELD )
			{
				example += pSig->Display( '.', filter );
			}
			if( field == DESC_LENGTH_FIELD )
			{
				example += QString( "%1" ).arg( pSig->ComputeDLofModel() );
			}
			if( field == STEM_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pSig->GetStemPtrList()->count() );
			}
			if( field == CORPUS_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pSig->GetCorpusCount() );
			}
			if( field == EXEMPLAR_FIELD )
			{
                                example += pSig->GetStemPtrList()->first()->Display( filter );
			}
			if( field == REMARKS_FIELD )
			{
				example += pSig->GetRemark();
			}
			if( field == ROBUSTNESS_FIELD )
			{
				example += QString( "%1" ).arg( pSig->GetRobustness() );
			}

			line = line.mid( end + 1 );
		}
			
		m_miniSignaturesExampleText->setText( example );	
	}
}
	

void ExportWizard::updateMiniStemsExampleSlot()
{
	if( !m_miniStemsFlag->isChecked() ) return;
	if( m_pLexicon->GetMiniCount() == 0 ) return;

	int mini;
	CMiniLexicon* pMini;
	for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
	{	
		pMini = m_pLexicon->GetMiniLexicon(mini);
		if( !pMini || !pMini->GetStems() ) continue;
		if( pMini->GetStems()->GetCount() == 0 ) continue;

		CStem* pStem;
		pStem=NULL;	
		CSignature* pSig;	
		pSig=NULL;
		
		QString example = "", 
				line = m_miniStemsLine->text(),
				field;

		int i, start, end;

		StringToString* filter = m_pLexicon->GetOutFilter();

		for( i = 0; i < pMini->GetStems()->GetCount(); i++ )
		{
			pStem = pMini->GetStems()->GetAt(i);
			pSig = pStem->GetSuffixSignature();
			if( pSig == NULL ) pSig = pStem->GetPrefixSignature();

			if( pSig && pSig->Size() > 1 ) break;
		}

		if( line.count( "%" ) % 2 == 1 )
		{
			m_miniStemsExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
		
			setNextEnabled( page(MINI_STEMS_FILE_PAGE), FALSE );
			setFinishEnabled( page(CONFIRMATION), FALSE );
			return;
		}
		 		
		setNextEnabled( page(MINI_STEMS_FILE_PAGE), TRUE );
		setFinishEnabled( page(CONFIRMATION), TRUE );

		while( line.length() > 0 )
		{
			start = line.find( "%" );

			if( start < 0 ) 
			{
				example += line;
				break;
			}

			example += line.left( start );
			line = line.mid( start );
			end = line.find( "%", 1 );
			field = line.mid( 0, end + 1 );

			if( field == INDEX_FIELD )
			{
				example += QString( "%1" ).arg( i + 1 );
			}
			if( field == STEM_FIELD )
			{
				example += pStem->Display( filter );
			}
			if( field == CORPUS_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pStem->GetCorpusCount() );
			}
			if( field == DESC_LENGTH_FIELD )
			{
				example += QString( "%1" ).arg( pStem->CalculateDL() );
			}
			if( field == TYPE_FIELD )
			{
				example += pStem->DisplayStemType();
			}
			if( field == SIGNATURE_FIELD )
			{
				if( pSig ) example += getLParseText( pSig );
				else example += "";
			}
			if( field == ORIGIN_FIELD )
			{
/*				if( pSig ) example += pSig->GetRemark();
				else*/ example += pStem->GetConfidence();
			}

			line = line.mid( end + 1 );
		}
			
		m_miniStemsExampleText->setText( example );	
	}
}
	

void ExportWizard::updateMiniSuffixesExampleSlot()
{
	if( !m_miniSuffixesFlag->isChecked() ) return;
	if( m_pLexicon->GetMiniCount() == 0 ) return;

	int mini;
	CMiniLexicon* pMini;
	for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
	{	
		pMini = m_pLexicon->GetMiniLexicon(mini);
		if( !pMini || !pMini->GetSuffixes() ) continue;
		if( pMini->GetSuffixes()->GetCount() == 0 ) continue;

		CSuffix* pSuffix;

		QString example = "", 
				line = m_miniSuffixesLine->text(),
				field;

		int i, start, end;

		StringToString* filter = m_pLexicon->GetOutFilter();

		i = ( pMini->GetSuffixes()->GetCount() - 1 ) / 2;
		pSuffix = pMini->GetSuffixes()->GetAt(i);

		if( line.count( "%" ) % 2 == 1 )
		{
			m_miniSuffixesExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
		
			setNextEnabled( page(MINI_SUFFIXES_FILE_PAGE), FALSE );
			setFinishEnabled( page(CONFIRMATION), FALSE );
			return;
		}
		
		setNextEnabled( page(MINI_SUFFIXES_FILE_PAGE), TRUE );
		setFinishEnabled( page(CONFIRMATION), TRUE );

		while( line.length() > 0 )
		{
			start = line.find( "%" );

			if( start < 0 ) 
			{
				example += line;
				break;
			}

			example += line.left( start );
			line = line.mid( start );
			end = line.find( "%", 1 );
			field = line.mid( 0, end + 1 );

			if( field == INDEX_FIELD )
			{
				example += QString( "%1" ).arg( i + 1 );
			}
			if( field == SUFFIX_FIELD )
			{
				example += pSuffix->Display( filter );
			}
			if( field == CORPUS_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pSuffix->GetCorpusCount() );
			}
			if( field == DESC_LENGTH_FIELD )
			{
				example += QString( "%1" ).arg( pSuffix->ComputeDL() );
			}
			if( field == STEM_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pSuffix->GetUseCount() );
			}

			line = line.mid( end + 1 );
		}
			
		m_miniSuffixesExampleText->setText( example );	
	}
}
	

void ExportWizard::updateMiniPrefixesExampleSlot()
{
	if( !m_miniPrefixesFlag->isChecked() ) return;
	if( m_pLexicon->GetMiniCount() == 0 ) return;

	int mini;
	CMiniLexicon* pMini;
	for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
	{	
		pMini = m_pLexicon->GetMiniLexicon(mini);
		if( !pMini || !pMini->GetPrefixes() ) continue;
		if( pMini->GetPrefixes()->GetCount() == 0 ) continue;

		CPrefix* pPrefix;

		QString example = "", 
				line = m_miniPrefixesLine->text(),
				field;

		int i, start, end;

		StringToString* filter = m_pLexicon->GetOutFilter();

		i = ( pMini->GetPrefixes()->GetCount() - 1 ) / 2;
		pPrefix = pMini->GetPrefixes()->GetAt(i);

		if( line.count( "%" ) % 2 == 1 )
		{
			m_miniPrefixesExampleText->setText( "Error : odd number of \'%\'s in line designer!" );
		
			setNextEnabled( page(MINI_PREFIXES_FILE_PAGE), FALSE );
			setFinishEnabled( page(CONFIRMATION), FALSE );
			return;
		}
		
		setNextEnabled( page(MINI_PREFIXES_FILE_PAGE), TRUE );
		setFinishEnabled( page(CONFIRMATION), TRUE );

		while( line.length() > 0 )
		{
			start = line.find( "%" );

			if( start < 0 ) 
			{
				example += line;
				break;
			}

			example += line.left( start );
			line = line.mid( start );
			end = line.find( "%", 1 );
			field = line.mid( 0, end + 1 );

			if( field == INDEX_FIELD )
			{
				example += QString( "%1" ).arg( i + 1 );
			}
			if( field == PREFIX_FIELD )
			{
				example += pPrefix->Display( filter );
			}
			if( field == CORPUS_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pPrefix->GetCorpusCount() );
			}
			if( field == DESC_LENGTH_FIELD )
			{
				example += QString( "%1" ).arg( pPrefix->ComputeDL() );
			}
			if( field == STEM_COUNT_FIELD )
			{
				example += QString( "%1" ).arg( pPrefix->GetUseCount() );
			}

			line = line.mid( end + 1 );
		}
			
		m_miniPrefixesExampleText->setText( example );	
	}
}


void ExportWizard::changeCompoundColorSlot()
{   
	QColor color = QColorDialog::getColor( m_compoundStyle->foregroundColor(), this, "color_dialog" );

	if( color.isValid() ) m_compoundStyle->setPaletteForegroundColor( color );
}


void ExportWizard::changePrefixColorSlot()
{   
	QColor color = QColorDialog::getColor( m_prefixStyle->foregroundColor(), this, "color_dialog" );

	if( color.isValid() ) m_prefixStyle->setPaletteForegroundColor( color );
}


void ExportWizard::changeSignatureColorSlot()
{
	QColor color = QColorDialog::getColor( m_signatureStyle->foregroundColor(), this, "color_dialog" );

	if( color.isValid() ) m_signatureStyle->setPaletteForegroundColor( color );
}


void ExportWizard::changeStemColorSlot()
{
	QColor color = QColorDialog::getColor( m_stemStyle->foregroundColor(), this, "color_dialog" );

	if( color.isValid() ) m_stemStyle->setPaletteForegroundColor( color );
}


void ExportWizard::changeSuffixColorSlot()
{
	QColor color = QColorDialog::getColor( m_suffixStyle->foregroundColor(), this, "color_dialog" );

	if( color.isValid() ) m_suffixStyle->setPaletteForegroundColor( color );
}


void ExportWizard::changeWordColorSlot()
{
	QColor color = QColorDialog::getColor( m_wordStyle->foregroundColor(), this, "color_dialog" );

	if( color.isValid() ) m_wordStyle->setPaletteForegroundColor( color );
}


void ExportWizard::updateStylesSlot()
{
	if( !m_markUpFlag->isChecked() && !m_bothFlag->isChecked() ) return;

	QFont font;
	
	// Word style
	font = m_wordStyle->font();
	font.setBold( m_wordBoldFlag->isChecked() );
	font.setItalic( m_wordItalicFlag->isChecked() );
	m_wordStyle->setFont( font );
	
	// Signature style
	font = m_signatureStyle->font();
	font.setBold( m_signatureBoldFlag->isChecked() );
	font.setItalic( m_signatureItalicFlag->isChecked() );
	m_signatureStyle->setFont( font );
	
	// Stem style
	font = m_stemStyle->font();
	font.setBold( m_stemBoldFlag->isChecked() );
	font.setItalic( m_stemItalicFlag->isChecked() );
	m_stemStyle->setFont( font );
	
	// Suffix style
	font = m_suffixStyle->font();
	font.setBold( m_suffixBoldFlag->isChecked() );
	font.setItalic( m_suffixItalicFlag->isChecked() );
	m_suffixStyle->setFont( font );
	
	// Prefix style
	font = m_prefixStyle->font();
	font.setBold( m_prefixBoldFlag->isChecked() );
	font.setItalic( m_prefixItalicFlag->isChecked() );
	m_prefixStyle->setFont( font );
}


QString ExportWizard::getHTMLHeader( QString projectName, QString title, QString language, QString researchers, int myMini )
{
	QString header = "",
			projectTitle = projectName,
			url = "",
			miniName = "";
	
	CMiniLexicon* pMini;

	int mini;

	projectTitle.replace( " ", "_" );
	
	header += "<!doctype html public \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n\n";
	header += "<html>\n";
	header += "\t<head>\n";
	header += "\t\t<title>" + projectName;
	if( title != QString::null ) header += " : " + title;
	header += "</title>\n";
	header += "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"" + projectTitle + ".css\">\n";
	header += "\t</head>\n";
	header += "\t<body>\n";
	header += "\t\t<div id=\"top\">\n";
	header += "\t\t\t<h1>" + projectName;
	if( title != QString::null ) header += " : " + title;
	header += "</h1>\n";
	if( language.length() > 0 ) header += "\t\t\t<h2>Language: " + language + "</h2>\n";
	if( researchers.length() > 0 ) header += "\t\t\t<h2>Researcher(s): " + researchers + "</h2>\n";
	

	if( title != QString::null )
	{
		header += "\t\t\t<p>\n";
		
		if( m_brokenCorpusFlag->isChecked() ||
			m_corpusWordsFlag->isChecked() )
		{
			header += "\t\t\tCorpus: | ";
		}

		if( m_brokenCorpusFlag->isChecked() && m_pLexicon->GetCorpus()->count() > 0 )
		{
			if( title != BROKEN_CORPUS_FILE_TITLE ) 
			{
				url = projectTitle + "_" + BROKEN_CORPUS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += BROKEN_CORPUS_FILE_TITLE;
			
			if( title != BROKEN_CORPUS_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_corpusWordsFlag->isChecked() && m_pLexicon->GetWords()->GetCount() > 0 )
		{
			if( title != CORPUS_WORDS_FILE_TITLE ) 
			{
				url = projectTitle + "_" + CORPUS_WORDS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += CORPUS_WORDS_FILE_TITLE;
			
			if( title != CORPUS_WORDS_FILE_TITLE ) header += "</a>";

			header += " | ";
		}

		if( m_compoundsFlag->isChecked() ||
			m_allWordsFlag->isChecked() ||
			m_allStemsFlag->isChecked() ||
			m_allSuffixSigsFlag->isChecked() ||
			m_allPrefixSigsFlag->isChecked() ||
			m_allSuffixesFlag->isChecked() ||
			m_allPrefixesFlag->isChecked() )
		{
			if( m_brokenCorpusFlag->isChecked() ||
				m_corpusWordsFlag->isChecked() )
			{
				header += "<br>\n\t\t\t";
			}

			header += "Lexicon: | ";
		}

		if( m_allWordsFlag->isChecked() && m_pLexicon->GetAllWords()->count() > 0 )
		{
			if( title != ALL_WORDS_FILE_TITLE ) 
			{
				url = projectTitle + "_" + ALL_WORDS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += ALL_WORDS_FILE_TITLE;
			
			if( title != ALL_WORDS_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_allStemsFlag->isChecked() && m_pLexicon->GetAllStems()->count() > 0 )
		{
			if( title != ALL_STEMS_FILE_TITLE ) 
			{
				url = projectTitle + "_" + ALL_STEMS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += ALL_STEMS_FILE_TITLE;
			
			if( title != ALL_STEMS_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_allSuffixesFlag->isChecked() && m_pLexicon->GetAllSuffixes()->count() > 0 )
		{
			if( title != ALL_SUFFIXES_FILE_TITLE ) 
			{
				url = projectTitle + "_" + ALL_SUFFIXES_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += ALL_SUFFIXES_FILE_TITLE;
			
			if( title != ALL_SUFFIXES_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_allSuffixSigsFlag->isChecked() && m_pLexicon->GetAllSuffixSigs()->count() > 0 )
		{
			if( title != ALL_SUFFIX_SIGNATURES_FILE_TITLE ) 
			{
				url = projectTitle + "_" + ALL_SUFFIX_SIGNATURES_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += ALL_SUFFIX_SIGNATURES_FILE_TITLE;
			
			if( title != ALL_SUFFIX_SIGNATURES_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_allPrefixesFlag->isChecked() && m_pLexicon->GetAllPrefixes()->count() > 0 )
		{
			if( title != ALL_PREFIXES_FILE_TITLE ) 
			{
				url = projectTitle + "_" + ALL_PREFIXES_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += ALL_PREFIXES_FILE_TITLE;
			
			if( title != ALL_PREFIXES_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_allPrefixSigsFlag->isChecked() && m_pLexicon->GetAllPrefixSigs()->count() > 0 )
		{
			if( title != ALL_PREFIX_SIGNATURES_FILE_TITLE ) 
			{
				url = projectTitle + "_" + ALL_PREFIX_SIGNATURES_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += ALL_PREFIX_SIGNATURES_FILE_TITLE;
			
			if( title != ALL_PREFIX_SIGNATURES_FILE_TITLE ) header += "</a>";

			header += " | ";
		}
		if( m_compoundsFlag->isChecked() && m_pLexicon->GetCompounds()->GetCount() > 0 )
		{
			if( title != COMPOUNDS_FILE_TITLE ) 
			{
				url = projectTitle + "_" + COMPOUNDS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += COMPOUNDS_FILE_TITLE;
			
			if( title != COMPOUNDS_FILE_TITLE ) header += "</a>";

			header += " | ";
			
			if( title != LINKERS_FILE_TITLE ) 
			{
				url = projectTitle + "_" + LINKERS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				header += "<a class=\"top\" href=\"" + url + "\">";
			}

			header += LINKERS_FILE_TITLE;
			
			if( title != LINKERS_FILE_TITLE ) header += "</a>";

			header += " | ";
		}

		// Do mini lexica
		bool atLeastOneMiniLineWritten = FALSE;
		for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
		{	
			pMini = m_pLexicon->GetMiniLexicon(mini);
			if( !pMini || !pMini->GetWords() ) continue;
			if( pMini->GetWords()->GetCount() == 0 ) continue;

			miniName = QString( "Mini %1" ).arg( pMini->GetIndex() + 1 );

			if( m_miniWordsFlag->isChecked() ||
				m_miniSignaturesFlag->isChecked() ||
				m_miniStemsFlag->isChecked() ||
				m_miniPrefixesFlag->isChecked() ||
				m_miniSuffixesFlag->isChecked() )
			{
				if( m_brokenCorpusFlag->isChecked() ||
					m_corpusWordsFlag->isChecked() ||
					m_compoundsFlag->isChecked() ||
					m_allWordsFlag->isChecked() ||
					m_allStemsFlag->isChecked() ||
					m_allSuffixSigsFlag->isChecked() ||
					m_allPrefixSigsFlag->isChecked() ||
					m_allSuffixesFlag->isChecked() ||
					m_allPrefixesFlag->isChecked() ||
					atLeastOneMiniLineWritten )
				{
					header += "<br>\n\t\t\t";
				}

				header += miniName + ": | ";
				atLeastOneMiniLineWritten = TRUE;
			}

			if( m_miniWordsFlag->isChecked() && pMini->GetWords() && pMini->GetWords()->GetCount() > 0 )
			{
				if( title != MINI_WORDS_FILE_TITLE || mini != myMini )
				{
					url = projectTitle + "_" + miniName + "_" + MINI_WORDS_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					header += "<a class=\"top\" href=\"" + url + "\">";
				}

				header += MINI_WORDS_FILE_TITLE;

				if( title != MINI_WORDS_FILE_TITLE || mini != myMini ) header += "</a>";

				header += " | ";
			}
			if( m_miniStemsFlag->isChecked() && pMini->GetStems() && pMini->GetStems()->GetCount() > 0 )
			{
				if( title != MINI_STEMS_FILE_TITLE || mini != myMini )
				{
					url = projectTitle + "_" + miniName + "_" + MINI_STEMS_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					header += "<a class=\"top\" href=\"" + url + "\">";
				}

				header += MINI_STEMS_FILE_TITLE;

				if( title != MINI_STEMS_FILE_TITLE || mini != myMini ) header += "</a>";

				header += " | ";
			}
			if( m_miniPrefixesFlag->isChecked() && pMini->GetPrefixes() && pMini->GetPrefixes()->GetCount() > 0 )
			{
				if( title != MINI_PREFIXES_FILE_TITLE || mini != myMini )
				{
					url = projectTitle + "_" + miniName + "_" + MINI_PREFIXES_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					header += "<a class=\"top\" href=\"" + url + "\">";
				}

				header += MINI_PREFIXES_FILE_TITLE;

				if( title != MINI_PREFIXES_FILE_TITLE || mini != myMini ) header += "</a>";

				header += " | ";
			}
			if( m_miniSuffixesFlag->isChecked() && pMini->GetSuffixes() && pMini->GetSuffixes()->GetCount() > 0 )
			{
				if( title != MINI_SUFFIXES_FILE_TITLE || mini != myMini )
				{
					url = projectTitle + "_" + miniName + "_" + MINI_SUFFIXES_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					header += "<a class=\"top\" href=\"" + url + "\">";
				}

				header += MINI_SUFFIXES_FILE_TITLE;

				if( title != MINI_SUFFIXES_FILE_TITLE || mini != myMini ) header += "</a>";

				header += " | ";
			}
			if( m_miniSignaturesFlag->isChecked() && pMini->GetSignatures() && pMini->GetSignatures()->GetCount() > 0 )
			{
				if( title != MINI_SIGNATURES_FILE_TITLE || mini != myMini )
				{
					url = projectTitle + "_" + miniName + "_" + MINI_SIGNATURES_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					header += "<a class=\"top\" href=\"" + url + "\">";
				}

				header += MINI_SIGNATURES_FILE_TITLE;

				if( title != MINI_SIGNATURES_FILE_TITLE || mini != myMini ) header += "</a>";

				header += " | ";
			}
		}

		header += "</p>\n";
	}


	header += "\t\t</div>\n";
	header += "\t\t<div id=\"bottom\">\n";

	return header;
}


QString ExportWizard::getHTMLFooter()
{
	QString footer = "";
	
	footer += "\t\t\t<br>\n\t\t\t<hr color=\"#1B2025\">\n";
	footer += "\t\t\t<p>Created with <a href=\"#top\" onclick=\"window.open( \'http://linguistica.uchicago.edu/\', \'linguistica\' );\">Linguistica</a>.</p>\n";
	footer += "\t\t</div>\n";
	footer += "\t\t<br><br>\n";
	footer += "\t</body>\n";
	footer += "</html>\n";

	return footer;
}


QString ExportWizard::getLParseText( CLParse* pLParse, bool markUpFlag, bool noLinkFlag, QString forcedType, QString forcedURL )
{
	QString lparse = "",
			url,
			type;

	StringToString* filter = m_pLexicon->GetOutFilter();

	if( !pLParse ) return "&nbsp;";

	if( markUpFlag )
	{
		switch( pLParse->GetType() )
		{
		case PREFIX_CLASS:
			if( m_allPrefixesFlag->isChecked() && 
				m_pLexicon->GetAllPrefixes() &&
				m_pLexicon->GetAllPrefixes()->count() )
			{
				url = m_projectName->text() + "_" + ALL_PREFIXES_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				url += "#_" + pLParse->Display( filter ) + "_";
			}
			type = "prefix";
			break;
		case SIGNATURE_CLASS:
			if (is_initial(static_cast<CSignature*>(pLParse)
					->GetAffixLocation())) {
				if( m_allPrefixSigsFlag->isChecked() && 
					m_pLexicon->GetAllPrefixSigs() &&
					m_pLexicon->GetAllPrefixSigs()->count() )
				{
					url = m_projectName->text() + "_" + ALL_PREFIX_SIGNATURES_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					url += "#_" + pLParse->Display( filter ) + "_";
				}
			} else {
				if( m_allSuffixSigsFlag->isChecked() && 
					m_pLexicon->GetAllSuffixSigs() &&
					m_pLexicon->GetAllSuffixSigs()->count() )
				{
					url = m_projectName->text() + "_" + ALL_SUFFIX_SIGNATURES_FILE_TITLE + ".html";
					url.replace( " ", "_" );
					url += "#_" + pLParse->Display(  filter ) + "_";
				}
			}
			type = "signature";
			break;
		case STEM_CLASS:
			if( m_allStemsFlag->isChecked() && 
				m_pLexicon->GetAllStems() &&
				m_pLexicon->GetAllStems()->count() )
			{
				url = m_projectName->text() + "_" + ALL_STEMS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				url += "#_" + pLParse->Display(  filter ) + "_";
			}
			type = "stem";
			break;
		case SUFFIX_CLASS:
			if( m_allSuffixesFlag->isChecked() && 
				m_pLexicon->GetAllSuffixes() &&
				m_pLexicon->GetAllSuffixes()->count() )
			{
				url = m_projectName->text() + "_" + ALL_SUFFIXES_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				url += "#_" + pLParse->Display(  filter ) + "_";
			}
			type = "suffix";
			break;
		case COMPOUND_CLASS:
			if( m_compoundsFlag->isChecked() &&
				m_pLexicon->GetCompounds() &&
				m_pLexicon->GetCompounds()->GetCount() )
			{
				url = m_projectName->text() + "_" + COMPOUNDS_FILE_TITLE + ".html";
				url.replace( " ", "_" );
				url += "#_" + pLParse->Display( filter ) + "_";
			}
			type = "compound";
			break;
			
		default: break;
			
		}

		if( !forcedType.isNull() ) type = forcedType;
		if( !forcedURL.isNull() ) 
		{
			url = forcedURL;
			url += "#_" + pLParse->Display( filter ) + "_";
		}

		if( url.length() > 0 && !noLinkFlag ) lparse += "<a href=\"" + url + "\" class=\"data\">";
		if( type.length() > 0 ) lparse += "<span class=\"" + type + "\">";
	}
	
	if( pLParse->GetType() != SIGNATURE_CLASS ) lparse += pLParse->Display( filter );
	else lparse += pLParse->Display( '.', filter );

	if( markUpFlag )
	{
		if( type.length() > 0 ) lparse += "</span>";
		if( url.length() > 0 && !noLinkFlag ) lparse += "</a>";
	}

	return lparse;
}


void ExportWizard::saveParseImage( CEdge* edge, QString fileName, CanvasDialog* dlg )
{
	CanvasDialog* canvasDlg = dlg;
	
	if( !dlg )
		canvasDlg = new CanvasDialog( this, Qt::WStyle_Customize |
							Qt::WStyle_NormalBorder |
							Qt::WStyle_Title |
							Qt::WStyle_SysMenu );
	else
		canvasDlg->clear();

	QRect rectangle = edge->m_Daughters.first()->drawTree( canvasDlg->m_canvas, 10, 0, m_pLexicon->GetOutFilter() );

	canvasDlg->show();
	canvasDlg->saveToFile( rectangle, fileName, "PNG" );

	if( !dlg ) 
	{
		canvasDlg->close();
		delete canvasDlg;
	}
}







