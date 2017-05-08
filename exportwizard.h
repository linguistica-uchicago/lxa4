// “Linguistica Export Wizard” dialog for saving analysis to files
// Copyright © 2009 The University of Chicago
#ifndef EXPORTWIZARD_H
#define EXPORTWIZARD_H

#include <Q3Wizard>
#include "ui_exportwizardbase.h"

#include <QSettings>
#include <Qt>
#include "canvasdialog.h"

class CLexicon;
class CCorpusWord;
class CCompound;
class CLParse;
class CEdge;

const int PROJECT_INFO_PAGE					= 0;
const int STYLE_SHEET_PAGE					= 1;
const int CORPUS_WORDS_FILE_PAGE			= 2;
const int COMPOUNDS_FILE_PAGE				= 3;
const int LINKERS_FILE_PAGE					= 4;
const int ALL_WORDS_FILE_PAGE				= 5;
const int ALL_STEMS_FILE_PAGE				= 6;
const int ALL_SUFFIXES_FILE_PAGE			= 7;
const int ALL_SUFFIX_SIGNATURES_FILE_PAGE	= 8;
const int ALL_PREFIXES_FILE_PAGE			= 9;
const int ALL_PREFIX_SIGNATURES_FILE_PAGE	= 10;
const int MINI_WORDS_FILE_PAGE				= 11;
const int MINI_SIGNATURES_FILE_PAGE			= 12;
const int MINI_STEMS_FILE_PAGE				= 13;
const int MINI_SUFFIXES_FILE_PAGE			= 14;
const int MINI_PREFIXES_FILE_PAGE			= 15;
const int CONFIRMATION						= 16;

// Field variables
const QString INDEX_FIELD			= "%INDEX%";
const QString WORD_FIELD			= "%WORD%";
const QString CORPUS_COUNT_FIELD	= "%C_COUNT%";
const QString MORPHS_COUNT_FIELD	= "%M_COUNT%";
const QString MORPHS_FIELD			= "%MORPHS%";
const QString MINI_LEX_FIELD		= "%MINI_LEX%";
const QString DESC_LENGTH_FIELD		= "%DESC_LENGTH%";
const QString TYPE_FIELD			= "%TYPE%";
const QString SIGNATURE_FIELD		= "%SIGNATURE%";
const QString SOURCE_FIELD			= "%SOURCE%";
const QString PREFIX_FIELD			= "%PREFIX%";
const QString STEM_FIELD			= "%STEM%";
const QString SUFFIX_FIELD			= "%SUFFIX%";
const QString ORIGIN_FIELD			= "%ORIGIN%";
const QString STEM_COUNT_FIELD		= "%S_COUNT%";
const QString EXEMPLAR_FIELD		= "%EXEMPLAR%";
const QString REMARKS_FIELD			= "%REMARKS%";
const QString ROBUSTNESS_FIELD		= "%ROBUSTNESS%";
const QString STEMS_FIELD			= "%STEMS%";
const QString COMPOUND_FIELD		= "%COMPOUND%";
const QString PARSE_FIELD			= "%PARSE%";
const QString SUFFIXNESS_FIELD		= "%SUFFIXNESS%";
const QString PREFIXNESS_FIELD		= "%PREFIXNESS%";
const QString LINKER_FIELD			= "%LINKER%";
const QString COMPOUND_COUNT_FIELD	= "%COMP_COUNT%";
const QString COMPOUNDS_FIELD		= "%COMPOUNDS%";

// Field titles
const QString INDEX_FIELD_TITLE				= "Index";
const QString WORD_FIELD_TITLE				= "Words";
const QString CORPUS_COUNT_FIELD_TITLE		= "Corpus Count";
const QString MORPHS_COUNT_FIELD_TITLE		= "Morph Count";
const QString MORPHS_FIELD_TITLE			= "Morphs";
const QString MINI_LEX_FIELD_TITLE			= "Mini-Lex";
const QString DESC_LENGTH_FIELD_TITLE		= "Desc. Length";
const QString TYPE_FIELD_TITLE				= "Type";
const QString SIGNATURE_FIELD_TITLE			= "Signature";
const QString SOURCE_FIELD_TITLE			= "Source";
const QString PREFIX_FIELD_TITLE			= "Prefix";
const QString STEM_FIELD_TITLE				= "Stem";
const QString SUFFIX_FIELD_TITLE			= "Suffix";
const QString ORIGIN_FIELD_TITLE			= "Origin";
const QString STEM_COUNT_FIELD_TITLE		= "Stem Count";
const QString EXEMPLAR_FIELD_TITLE			= "Exemplar";
const QString REMARKS_FIELD_TITLE			= "Remarks";
const QString ROBUSTNESS_FIELD_TITLE		= "Robustness";
const QString STEMS_FIELD_TITLE				= "Stems";
const QString COMPOUND_FIELD_TITLE			= "Compound";
const QString PARSE_FIELD_TITLE				= "Parse";
const QString SUFFIXNESS_FIELD_TITLE		= "Suffixness";
const QString PREFIXNESS_FIELD_TITLE		= "Prefixness";
const QString LINKER_FIELD_TITLE			= "Linker";
const QString COMPOUND_COUNT_FIELD_TITLE	= "Compound Count";
const QString COMPOUNDS_FIELD_TITLE			= "Compounds";

// File titles
const QString BROKEN_CORPUS_FILE_TITLE			= "Broken Corpus";
const QString CORPUS_WORDS_FILE_TITLE			= "Corpus Words";
const QString COMPOUNDS_FILE_TITLE				= "Compounds";
const QString LINKERS_FILE_TITLE				= "Linkers";
const QString ALL_WORDS_FILE_TITLE				= "All Words";
const QString ALL_STEMS_FILE_TITLE				= "All Stems";
const QString ALL_SUFFIX_SIGNATURES_FILE_TITLE	= "All Suffix Signatures";
const QString ALL_PREFIX_SIGNATURES_FILE_TITLE	= "All Prefix Signatures";
const QString ALL_SUFFIXES_FILE_TITLE			= "All Suffixes";
const QString ALL_PREFIXES_FILE_TITLE			= "All Prefixes";
const QString MINI_WORDS_FILE_TITLE				= "Words";
const QString MINI_STEMS_FILE_TITLE				= "Stems";
const QString MINI_SIGNATURES_FILE_TITLE		= "Signatures";
const QString MINI_SUFFIXES_FILE_TITLE			= "Suffixes";
const QString MINI_PREFIXES_FILE_TITLE			= "Prefixes";

const QString SETTINGS = "/linguistica.uchicago.edu/Linguistica/Export/";


class ExportWizard : public Q3Wizard, private Ui::ExportWizardBase
{
    Q_OBJECT

	CLexicon* m_pLexicon;
	QSettings* m_pSettings;

public:
	ExportWizard( CLexicon* pLexicon, QWidget* parent = 0, Qt::WindowFlags fl = 0 );

	void exportAll();

public slots:
	void browseOutputDirSlot();
	void corpusWordsCheckedSlot(bool);
	void compoundsCheckedSlot(bool);
	void allWordsCheckedSlot(bool);
	void allSuffixSignaturesCheckedSlot(bool);
	void allPrefixSignaturesCheckedSlot(bool);
	void allStemsCheckedSlot(bool);
	void allSuffixesCheckedSlot(bool);
	void allPrefixesCheckedSlot(bool);
	void wordsCheckedSlot(bool);
	void signaturesCheckedSlot(bool);
	void stemsCheckedSlot(bool);
	void suffixesCheckedSlot(bool);
	void prefixesCheckedSlot(bool);
	
	//unused parameter (bool b)
	//void simpleTextToggledSlot(bool);
	void simpleTextToggledSlot( );
	
	//void markUpToggledSlot(bool);
	void markUpToggledSlot( );

	//void bothToggledSlot(bool);
	void bothToggledSlot( );
	
	void validateProjectInformationSlot();

	// Style
	void changePrefixColorSlot();
	void changeSignatureColorSlot();
	void changeStemColorSlot();
	void changeSuffixColorSlot();
	void changeWordColorSlot();
	void changeCompoundColorSlot();
	void updateStylesSlot();

	// Corpus words
	void corpusWordsAddIndexButtonClickedSlot();
	void corpusWordsAddWordButtonClickedSlot();
	void corpusWordsAddCorpusCountButtonClickedSlot();
	void corpusWordsAddMorphCountButtonClickedSlot();
	void corpusWordsAddMorphsButtonClickedSlot();
	void updateCorpusWordsExampleSlot();

	// Compounds
	void compoundsAddIndexButtonClickedSlot();
	void compoundsAddCompoundButtonClickedSlot();
	void compoundsAddCorpusCountButtonClickedSlot();
	void compoundsAddMorphCountButtonClickedSlot();
	void compoundsAddMorphsButtonClickedSlot();
	void compoundsAddParseButtonClickedSlot();
	void compoundsAddSuffixnessButtonClickedSlot();
	void compoundsAddPrefixnessButtonClickedSlot();
	void updateCompoundsExampleSlot();

	// Linkers
	void linkersAddIndexButtonClickedSlot();
	void linkersAddLinkerButtonClickedSlot();
	void linkersAddCorpusCountButtonClickedSlot();
	void linkersAddCompoundCountButtonClickedSlot();
	void updateLinkersExampleSlot();

	// All words
	void allWordsAddIndexButtonClickedSlot();
	void allWordsAddWordButtonClickedSlot();
	void allWordsAddMiniLexButtonClickedSlot();
	void allWordsAddDescLengthButtonClickedSlot();
	void allWordsAddCorpusCountButtonClickedSlot();
	void allWordsAddTypeButtonClickedSlot();
	void allWordsAddSignatureButtonClickedSlot();
	void allWordsAddSourceButtonClickedSlot();
	void allWordsAddPrefixButtonClickedSlot();
	void allWordsAddStemButtonClickedSlot();
	void allWordsAddSuffixButtonClickedSlot();
	void updateAllWordsExampleSlot();

	// All stems
	void allStemsAddIndexButtonClickedSlot();
	void allStemsAddStemButtonClickedSlot();
	void allStemsAddMiniLexButtonClickedSlot();
	void allStemsAddDescLengthButtonClickedSlot();
	void allStemsAddCorpusCountButtonClickedSlot();
	void allStemsAddTypeButtonClickedSlot();
	void allStemsAddSignatureButtonClickedSlot();
	void allStemsAddOriginButtonClickedSlot();
	void updateAllStemsExampleSlot();

	// All suffixes
	void allSuffixesAddIndexButtonClickedSlot();
	void allSuffixesAddSuffixButtonClickedSlot();
	void allSuffixesAddMiniLexButtonClickedSlot();
	void allSuffixesAddDescLengthButtonClickedSlot();
	void allSuffixesAddCorpusCountButtonClickedSlot();
	void allSuffixesAddStemCountButtonClickedSlot();
	void updateAllSuffixesExampleSlot();

	// All suffix signatures
	void allSuffixSigsAddIndexButtonClickedSlot();
	void allSuffixSigsAddSignatureButtonClickedSlot();
	void allSuffixSigsAddMiniLexButtonClickedSlot();
	void allSuffixSigsAddDescLengthButtonClickedSlot();
	void allSuffixSigsAddCorpusCountButtonClickedSlot();
	void allSuffixSigsAddExemplarButtonClickedSlot();
	void allSuffixSigsAddStemCountButtonClickedSlot();
	void allSuffixSigsAddRemarksButtonClickedSlot();
	void allSuffixSigsAddRobustnessButtonClickedSlot();
	void updateAllSuffixSigsExampleSlot();

	// All prefixes
	void allPrefixesAddIndexButtonClickedSlot();
	void allPrefixesAddPrefixButtonClickedSlot();
	void allPrefixesAddMiniLexButtonClickedSlot();
	void allPrefixesAddDescLengthButtonClickedSlot();
	void allPrefixesAddCorpusCountButtonClickedSlot();
	void allPrefixesAddStemCountButtonClickedSlot();
	void updateAllPrefixesExampleSlot();

	// All prefix signatures
	void allPrefixSigsAddIndexButtonClickedSlot();
	void allPrefixSigsAddSignatureButtonClickedSlot();
	void allPrefixSigsAddMiniLexButtonClickedSlot();
	void allPrefixSigsAddDescLengthButtonClickedSlot();
	void allPrefixSigsAddCorpusCountButtonClickedSlot();
	void allPrefixSigsAddExemplarButtonClickedSlot();
	void allPrefixSigsAddStemCountButtonClickedSlot();
	void allPrefixSigsAddRemarksButtonClickedSlot();
	void allPrefixSigsAddRobustnessButtonClickedSlot();
	void updateAllPrefixSigsExampleSlot();

	// Mini words
	void miniWordsAddIndexButtonClickedSlot();
	void miniWordsAddWordButtonClickedSlot();
	void miniWordsAddDescLengthButtonClickedSlot();
	void miniWordsAddCorpusCountButtonClickedSlot();
	void miniWordsAddTypeButtonClickedSlot();
	void miniWordsAddSignatureButtonClickedSlot();
	void miniWordsAddSourceButtonClickedSlot();
	void miniWordsAddPrefixButtonClickedSlot();
	void miniWordsAddStemButtonClickedSlot();
	void miniWordsAddSuffixButtonClickedSlot();
	void updateMiniWordsExampleSlot();

	// Mini stems
	void miniStemsAddIndexButtonClickedSlot();
	void miniStemsAddStemButtonClickedSlot();
	void miniStemsAddDescLengthButtonClickedSlot();
	void miniStemsAddCorpusCountButtonClickedSlot();
	void miniStemsAddTypeButtonClickedSlot();
	void miniStemsAddSignatureButtonClickedSlot();
	void miniStemsAddOriginButtonClickedSlot();
	void updateMiniStemsExampleSlot();

	// Mini signatures
	void miniSignaturesAddIndexButtonClickedSlot();
	void miniSignaturesAddSignatureButtonClickedSlot();
	void miniSignaturesAddDescLengthButtonClickedSlot();
	void miniSignaturesAddCorpusCountButtonClickedSlot();
	void miniSignaturesAddExemplarButtonClickedSlot();
	void miniSignaturesAddStemCountButtonClickedSlot();
	void miniSignaturesAddRemarksButtonClickedSlot();
	void miniSignaturesAddRobustnessButtonClickedSlot();
	void updateMiniSignaturesExampleSlot();

	// Mini suffixes
	void miniSuffixesAddIndexButtonClickedSlot();
	void miniSuffixesAddSuffixButtonClickedSlot();
	void miniSuffixesAddDescLengthButtonClickedSlot();
	void miniSuffixesAddCorpusCountButtonClickedSlot();
	void miniSuffixesAddStemCountButtonClickedSlot();
	void updateMiniSuffixesExampleSlot();

	// Mini prefixes
	void miniPrefixesAddIndexButtonClickedSlot();
	void miniPrefixesAddPrefixButtonClickedSlot();
	void miniPrefixesAddDescLengthButtonClickedSlot();
	void miniPrefixesAddCorpusCountButtonClickedSlot();
	void miniPrefixesAddStemCountButtonClickedSlot();
	void updateMiniPrefixesExampleSlot();

private:
	void	load();
	void	save();

	QString getCorpusWordMorphsField( CCorpusWord*, bool markUpFlag = FALSE );
	QString getCompoundMorphsField( CCompound*, bool markUpFlag = FALSE );
	QString getHTMLHeader( QString, QString, QString language = QString::null, QString researchers = QString::null, int myMini = -1 );
	QString getHTMLFooter();
	QString getLParseText( CLParse*, bool markUpFlag = FALSE, bool noLinkFlag = FALSE, QString forcedType = QString::null, QString forcedURL = QString::null );
	
	void	exportIndex();
	void	exportStyleSheet();
	void	exportCorpusWords();
	void	exportBrokenCorpus();
	void	exportCompounds();
	void	exportLinkers();
	void	exportAllWords();
	void	exportAllSuffixes();
	void	exportAllSuffixSigs();
	void	exportAllPrefixes();
	void	exportAllPrefixSigs();
	void	exportAllStems();
	void	exportMiniWords();
	void	exportMiniSignatures();
	void	exportMiniStems();
	void	exportMiniSuffixes();
	void	exportMiniPrefixes();

	void	saveParseImage( CEdge*, QString, CanvasDialog* dlg = NULL );
};

#endif // EXPORTWIZARD_H
