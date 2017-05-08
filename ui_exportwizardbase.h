/********************************************************************************
** Form generated from reading ui file 'exportwizardbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_EXPORTWIZARDBASE_H
#define UI_EXPORTWIZARDBASE_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <Qt3Support/Q3Wizard>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportWizardBase
{
public:
    QWidget *project_info;
    QVBoxLayout *vboxLayout;
    Q3GroupBox *groupBox1;
    QGridLayout *gridLayout;
    QLineEdit *m_language;
    QLabel *textLabel4;
    QLineEdit *m_researchers;
    QLabel *textLabel3;
    QLabel *textLabel2;
    QLineEdit *m_projectName;
    Q3GroupBox *groupBox2;
    QGridLayout *gridLayout1;
    QCheckBox *m_brokenCorpusFlag;
    QCheckBox *m_miniSignaturesFlag;
    QCheckBox *m_miniSuffixesFlag;
    QCheckBox *m_miniWordsFlag;
    QLabel *textLabel5;
    QCheckBox *m_miniPrefixesFlag;
    QCheckBox *m_miniStemsFlag;
    QCheckBox *m_allSuffixSigsFlag;
    QCheckBox *m_allPrefixesFlag;
    QCheckBox *m_allPrefixSigsFlag;
    QCheckBox *m_allSuffixesFlag;
    QCheckBox *m_allWordsFlag;
    QCheckBox *m_compoundsFlag;
    QCheckBox *m_allStemsFlag;
    QCheckBox *m_corpusWordsFlag;
    QLabel *textLabel6;
    QLabel *textLabel1_2;
    Q3ButtonGroup *buttonGroup1;
    QHBoxLayout *hboxLayout;
    QRadioButton *m_simpleTextFlag;
    QRadioButton *m_markUpFlag;
    QRadioButton *m_bothFlag;
    Q3GroupBox *groupBox3;
    QHBoxLayout *hboxLayout1;
    QLineEdit *m_outputDirectory;
    QPushButton *m_outputDirBrowseButton;
    QWidget *style_sheet;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout2;
    Q3GroupBox *groupBox29;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel6_2;
    QLabel *m_wordStyle;
    QHBoxLayout *hboxLayout4;
    QCheckBox *m_wordBoldFlag;
    QCheckBox *m_wordItalicFlag;
    QPushButton *m_wordColorButton;
    Q3GroupBox *groupBox29_5;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel6_2_5;
    QLabel *m_stemStyle;
    QHBoxLayout *hboxLayout6;
    QCheckBox *m_stemBoldFlag;
    QCheckBox *m_stemItalicFlag;
    QPushButton *m_stemColorButton;
    QSpacerItem *spacer37;
    QHBoxLayout *hboxLayout7;
    Q3GroupBox *groupBox29_3;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout8;
    QLabel *textLabel6_2_3;
    QLabel *m_suffixStyle;
    QHBoxLayout *hboxLayout9;
    QCheckBox *m_suffixBoldFlag;
    QCheckBox *m_suffixItalicFlag;
    QPushButton *m_suffixColorButton;
    Q3GroupBox *groupBox29_4;
    QVBoxLayout *vboxLayout5;
    QHBoxLayout *hboxLayout10;
    QLabel *textLabel6_2_4;
    QLabel *m_prefixStyle;
    QHBoxLayout *hboxLayout11;
    QCheckBox *m_prefixBoldFlag;
    QCheckBox *m_prefixItalicFlag;
    QPushButton *m_prefixColorButton;
    QSpacerItem *spacer36;
    QHBoxLayout *hboxLayout12;
    Q3GroupBox *groupBox29_2;
    QVBoxLayout *vboxLayout6;
    QHBoxLayout *hboxLayout13;
    QLabel *textLabel6_2_2;
    QLabel *m_signatureStyle;
    QHBoxLayout *hboxLayout14;
    QCheckBox *m_signatureBoldFlag;
    QCheckBox *m_signatureItalicFlag;
    QPushButton *m_signatureColorButton;
    Q3GroupBox *groupBox29_6;
    QVBoxLayout *vboxLayout7;
    QHBoxLayout *hboxLayout15;
    QLabel *textLabel6_2_6;
    QLabel *m_compoundStyle;
    QHBoxLayout *hboxLayout16;
    QCheckBox *m_compoundBoldFlag;
    QCheckBox *m_compoundItalicFlag;
    QPushButton *m_compoundColorButton;
    QSpacerItem *spacer35;
    QSpacerItem *spacer14;
    QWidget *corpus_word_file_layout;
    QVBoxLayout *vboxLayout8;
    QHBoxLayout *hboxLayout17;
    Q3ButtonGroup *buttonGroup5;
    QVBoxLayout *vboxLayout9;
    QCheckBox *m_corpusWordsAnalyzedOnlyFlag;
    QCheckBox *m_corpusWordsColumnTitlesFlag;
    QCheckBox *m_corpusWordsUniformFieldWidthsFlag;
    Q3ButtonGroup *buttonGroup2;
    QVBoxLayout *vboxLayout10;
    QRadioButton *m_corpusWordsAlphabeticalSortFlag;
    QRadioButton *m_corpusWordsCorpusCountSortFlag;
    QRadioButton *m_corpusWordsMorphemeCountSortFlag;
    QSpacerItem *spacer20;
    Q3ButtonGroup *buttonGroup3;
    QVBoxLayout *vboxLayout11;
    QLineEdit *m_corpusWordsLine;
    QHBoxLayout *hboxLayout18;
    QPushButton *m_corpusWordsAddIndexButton;
    QPushButton *m_corpusWordsAddWordButton;
    QPushButton *m_corpusWordsAddCorpusCountButton;
    QPushButton *m_corpusWordsAddMorphCountButton;
    QPushButton *m_corpusWordsAddMorphsButton;
    QSpacerItem *spacer18;
    QHBoxLayout *hboxLayout19;
    Q3GroupBox *groupBox17;
    QHBoxLayout *hboxLayout20;
    QLabel *textLabel3_2;
    QLineEdit *m_corpusWordsMorphemeFieldDelimiter;
    QLabel *textLabel4_2;
    QSpacerItem *spacer19;
    Q3GroupBox *groupBox18;
    QVBoxLayout *vboxLayout12;
    QLabel *m_corpusWordsExampleText;
    QSpacerItem *spacer12;
    QWidget *compounds_file_layout_page;
    QVBoxLayout *vboxLayout13;
    QHBoxLayout *hboxLayout21;
    Q3ButtonGroup *buttonGroup5_3;
    QVBoxLayout *vboxLayout14;
    QCheckBox *m_compoundsColumnTitlesFlag;
    QCheckBox *m_compoundsUniformFieldWidthsFlag;
    Q3ButtonGroup *buttonGroup2_3;
    QVBoxLayout *vboxLayout15;
    QRadioButton *m_compoundsAlphabeticalSortFlag;
    QRadioButton *m_compoundsCorpusCountSortFlag;
    QRadioButton *m_compoundsMorphemeCountSortFlag;
    QSpacerItem *spacer20_4;
    Q3ButtonGroup *buttonGroup3_3;
    QVBoxLayout *vboxLayout16;
    QLineEdit *m_compoundsLine;
    QHBoxLayout *hboxLayout22;
    QPushButton *m_compoundsAddIndexButton;
    QPushButton *m_compoundsAddWordButton;
    QPushButton *m_compoundsAddCorpusCountButton;
    QPushButton *m_compoundsAddMorphCountButton;
    QSpacerItem *spacer18_3;
    QHBoxLayout *hboxLayout23;
    QPushButton *m_compoundsAddMorphsButton;
    QPushButton *m_compoundsAddSuffixnessButton;
    QPushButton *m_compoundsAddPrefixnessButton;
    QPushButton *m_compoundsAddParseButton;
    QSpacerItem *spacer53;
    QHBoxLayout *hboxLayout24;
    Q3GroupBox *groupBox17_2;
    QHBoxLayout *hboxLayout25;
    QLabel *textLabel3_2_2;
    QLineEdit *m_compoundsMorphemeFieldDelimiter;
    QLabel *textLabel4_2_2;
    QSpacerItem *spacer19_3;
    Q3GroupBox *groupBox18_3;
    QVBoxLayout *vboxLayout17;
    QLabel *m_compoundsExampleText;
    QSpacerItem *spacer12_2;
    QWidget *linkers_file_layout_page;
    QVBoxLayout *vboxLayout18;
    QHBoxLayout *hboxLayout26;
    Q3ButtonGroup *buttonGroup5_2_2_2_3_3_3;
    QVBoxLayout *vboxLayout19;
    QCheckBox *m_linkersColumnTitlesFlag;
    QCheckBox *m_linkersUniformFieldWidthsFlag;
    QCheckBox *m_linkersIncludeCompoundListFlag;
    Q3ButtonGroup *buttonGroup2_2_3_2_3;
    QVBoxLayout *vboxLayout20;
    QRadioButton *m_linkersAlphabeticalSortFlag;
    QRadioButton *m_linkersCorpusCountSortFlag;
    QSpacerItem *spacer20_2_2_2_3_3_3;
    Q3ButtonGroup *buttonGroup3_2_2_2_3_3_3;
    QVBoxLayout *vboxLayout21;
    QLineEdit *m_linkersLine;
    QHBoxLayout *hboxLayout27;
    QPushButton *m_linkersAddIndexButton;
    QPushButton *m_linkersAddLinkerButton;
    QPushButton *m_linkersAddCorpusCountButton;
    QPushButton *m_linkersAddCompoundCountButton;
    QSpacerItem *spacer16_3_3_3;
    Q3GroupBox *groupBox18_2_2_2_3_3_3;
    QVBoxLayout *vboxLayout22;
    QLabel *m_linkersExampleText;
    QSpacerItem *spacer10_2_2_3_3_3;
    QWidget *all_words_file_layout_page;
    QVBoxLayout *vboxLayout23;
    QHBoxLayout *hboxLayout28;
    Q3ButtonGroup *buttonGroup5_2;
    QVBoxLayout *vboxLayout24;
    QCheckBox *m_allWordsAnalyzedOnlyFlag;
    QCheckBox *m_allWordsColumnTitlesFlag;
    QCheckBox *m_allWordsUniformFieldWidthsFlag;
    QSpacerItem *spacer20_2;
    Q3ButtonGroup *buttonGroup3_2;
    QVBoxLayout *vboxLayout25;
    QLineEdit *m_allWordsLine;
    QHBoxLayout *hboxLayout29;
    QPushButton *m_allWordsAddIndexButton;
    QPushButton *m_allWordsAddWordButton;
    QPushButton *m_allWordsAddMiniLexButton;
    QPushButton *m_allWordsAddDescLengthButton;
    QPushButton *m_allWordsAddCorpusCountButton;
    QPushButton *m_allWordsAddTypeButton;
    QSpacerItem *spacer18_2;
    QHBoxLayout *hboxLayout30;
    QPushButton *m_allWordsAddSignatureButton;
    QPushButton *m_allWordsAddSourceButton;
    QPushButton *m_allWordsAddPrefixButton;
    QPushButton *m_allWordsAddStemButton;
    QPushButton *m_allWordsAddSuffixButton;
    QSpacerItem *spacer19_2;
    Q3GroupBox *groupBox18_2;
    QVBoxLayout *vboxLayout26;
    QLabel *m_allWordsExampleText;
    QSpacerItem *spacer10;
    QWidget *all_stems_file_layout_page;
    QVBoxLayout *vboxLayout27;
    QHBoxLayout *hboxLayout31;
    Q3ButtonGroup *buttonGroup5_2_2;
    QVBoxLayout *vboxLayout28;
    QCheckBox *m_allStemsColumnTitlesFlag;
    QCheckBox *m_allStemsUniformFieldWidthsFlag;
    QSpacerItem *spacer20_2_2;
    Q3ButtonGroup *buttonGroup3_2_2;
    QVBoxLayout *vboxLayout29;
    QLineEdit *m_allStemsLine;
    QHBoxLayout *hboxLayout32;
    QPushButton *m_allStemsAddIndexButton;
    QPushButton *m_allStemsAddStemButton;
    QPushButton *m_allStemsAddMiniLexButton;
    QPushButton *m_allStemsAddCorpusCountButton;
    QSpacerItem *spacer20_3;
    QHBoxLayout *hboxLayout33;
    QPushButton *m_allStemsAddDescLengthButton;
    QPushButton *m_allStemsAddSignatureButton;
    QPushButton *m_allStemsAddOriginButton;
    QPushButton *m_allStemsAddTypeButton;
    QSpacerItem *spacer21;
    Q3GroupBox *groupBox18_2_2;
    QVBoxLayout *vboxLayout30;
    QLabel *m_allStemsExampleText;
    QSpacerItem *spacer10_2;
    QWidget *all_suffixes_file_layout_page;
    QVBoxLayout *vboxLayout31;
    QHBoxLayout *hboxLayout34;
    Q3ButtonGroup *buttonGroup5_2_2_2_3;
    QVBoxLayout *vboxLayout32;
    QCheckBox *m_allSuffixesColumnTitlesFlag;
    QCheckBox *m_allSuffixesUniformFieldWidthsFlag;
    QCheckBox *m_allSuffixesIncludeStemListFlag;
    QSpacerItem *spacer20_2_2_2_3;
    Q3ButtonGroup *buttonGroup3_2_2_2_3;
    QVBoxLayout *vboxLayout33;
    QLineEdit *m_allSuffixesLine;
    QHBoxLayout *hboxLayout35;
    QPushButton *m_allSuffixesAddIndexButton;
    QPushButton *m_allSuffixesAddSuffixButton;
    QPushButton *m_allSuffixesAddMiniLexButton;
    QPushButton *m_allSuffixesAddCorpusCountButton;
    QPushButton *m_allSuffixesAddStemCountButton;
    QPushButton *m_allSuffixesAddDescLengthButton;
    QSpacerItem *spacer16_3;
    Q3GroupBox *groupBox18_2_2_2_3;
    QVBoxLayout *vboxLayout34;
    QLabel *m_allSuffixesExampleText;
    QSpacerItem *spacer10_2_2_3;
    QWidget *all_suffix_signatures_file_layout_page;
    QVBoxLayout *vboxLayout35;
    QHBoxLayout *hboxLayout36;
    Q3ButtonGroup *buttonGroup5_2_2_2;
    QVBoxLayout *vboxLayout36;
    QCheckBox *m_allSuffixSigsColumnTitlesFlag;
    QCheckBox *m_allSuffixSigsUniformFieldWidthsFlag;
    QCheckBox *m_allSuffixSigsIncludeStemListFlag;
    QSpacerItem *spacer20_2_2_2;
    Q3ButtonGroup *buttonGroup3_2_2_2;
    QVBoxLayout *vboxLayout37;
    QLineEdit *m_allSuffixSigsLine;
    QHBoxLayout *hboxLayout37;
    QPushButton *m_allSuffixSigsAddIndexButton;
    QPushButton *m_allSuffixSigsAddSigButton;
    QPushButton *m_allSuffixSigsAddMiniLexButton;
    QPushButton *m_allSuffixSigsAddCorpusCountButton;
    QPushButton *m_allSuffixSigsAddStemCountButton;
    QSpacerItem *spacer16;
    QHBoxLayout *hboxLayout38;
    QPushButton *m_allSuffixSigsAddDescLengthButton;
    QPushButton *m_allSuffixSigsAddRobustnessButton;
    QPushButton *m_allSuffixSigsAddExemplarButton;
    QPushButton *m_allSuffixSigsAddRemarksButton;
    QSpacerItem *spacer17;
    Q3GroupBox *groupBox18_2_2_2;
    QVBoxLayout *vboxLayout38;
    QLabel *m_allSuffixSigsExampleText;
    QSpacerItem *spacer10_2_2;
    QWidget *all_prefixes_file_layout_page;
    QVBoxLayout *vboxLayout39;
    QHBoxLayout *hboxLayout39;
    Q3ButtonGroup *buttonGroup5_2_2_2_3_2;
    QVBoxLayout *vboxLayout40;
    QCheckBox *m_allPrefixesColumnTitlesFlag;
    QCheckBox *m_allPrefixesUniformFieldWidthsFlag;
    QCheckBox *m_allPrefixesIncludeStemListFlag;
    QSpacerItem *spacer20_2_2_2_3_2;
    Q3ButtonGroup *buttonGroup3_2_2_2_3_2;
    QVBoxLayout *vboxLayout41;
    QLineEdit *m_allPrefixesLine;
    QHBoxLayout *hboxLayout40;
    QPushButton *m_allPrefixesAddIndexButton;
    QPushButton *m_allPrefixesAddPrefixButton;
    QPushButton *m_allPrefixesAddMiniLexButton;
    QPushButton *m_allPrefixesAddCorpusCountButton;
    QPushButton *m_allPrefixesAddStemCountButton;
    QPushButton *m_allPrefixesAddDescLengthButton;
    QSpacerItem *spacer16_3_2;
    Q3GroupBox *groupBox18_2_2_2_3_2;
    QVBoxLayout *vboxLayout42;
    QLabel *m_allPrefixesExampleText;
    QSpacerItem *spacer10_2_2_3_2;
    QWidget *all_prefix_signatures_file_layout_page;
    QVBoxLayout *vboxLayout43;
    QHBoxLayout *hboxLayout41;
    Q3ButtonGroup *buttonGroup5_2_2_2_2;
    QVBoxLayout *vboxLayout44;
    QCheckBox *m_allPrefixSigsColumnTitlesFlag;
    QCheckBox *m_allPrefixSigsUniformFieldWidthsFlag;
    QCheckBox *m_allPrefixSigsIncludeStemListFlag;
    QSpacerItem *spacer20_2_2_2_2;
    Q3ButtonGroup *buttonGroup3_2_2_2_2;
    QVBoxLayout *vboxLayout45;
    QLineEdit *m_allPrefixSigsLine;
    QHBoxLayout *hboxLayout42;
    QPushButton *m_allPrefixSigsAddIndexButton;
    QPushButton *m_allPrefixSigsAddSigButton;
    QPushButton *m_allPrefixSigsAddMiniLexButton;
    QPushButton *m_allPrefixSigsAddCorpusCountButton;
    QPushButton *m_allPrefixSigsAddStemCountButton;
    QSpacerItem *spacer16_2;
    QHBoxLayout *hboxLayout43;
    QPushButton *m_allPrefixSigsAddDescLengthButton;
    QPushButton *m_allPrefixSigsAddRobustnessButton;
    QPushButton *m_allPrefixSigsAddExemplarButton;
    QPushButton *m_allPrefixSigsAddRemarksButton;
    QSpacerItem *spacer17_2;
    Q3GroupBox *groupBox18_2_2_2_2;
    QVBoxLayout *vboxLayout46;
    QLabel *m_allPrefixSigsExampleText;
    QSpacerItem *spacer10_2_2_2;
    QWidget *minilexicon_words_file_layout_page;
    QVBoxLayout *vboxLayout47;
    QHBoxLayout *hboxLayout44;
    Q3ButtonGroup *buttonGroup5_2_3;
    QVBoxLayout *vboxLayout48;
    QCheckBox *m_miniWordsAnalyzedOnlyFlag;
    QCheckBox *m_miniWordsColumnTitlesFlag;
    QCheckBox *m_miniWordsUniformFieldWidthsFlag;
    Q3ButtonGroup *buttonGroup2_2;
    QVBoxLayout *vboxLayout49;
    QRadioButton *m_miniWordsAlphabeticalSortFlag;
    QRadioButton *m_miniWordsCorpusCountSortFlag;
    QRadioButton *m_miniWordsMorphemeCountSortFlag;
    QSpacerItem *spacer20_2_3;
    Q3ButtonGroup *buttonGroup3_2_3;
    QVBoxLayout *vboxLayout50;
    QLineEdit *m_miniWordsLine;
    QHBoxLayout *hboxLayout45;
    QPushButton *m_miniWordsAddIndexButton;
    QPushButton *m_miniWordsAddWordButton;
    QPushButton *m_miniWordsAddDescLengthButton;
    QPushButton *m_miniWordsAddCorpusCountButton;
    QPushButton *m_miniWordsAddTypeButton;
    QSpacerItem *spacer18_2_2;
    QHBoxLayout *hboxLayout46;
    QPushButton *m_miniWordsAddSignatureButton;
    QPushButton *m_miniWordsAddSourceButton;
    QPushButton *m_miniWordsAddPrefixButton;
    QPushButton *m_miniWordsAddStemButton;
    QPushButton *m_miniWordsAddSuffixButton;
    QSpacerItem *spacer19_2_2;
    Q3GroupBox *groupBox18_2_3;
    QVBoxLayout *vboxLayout51;
    QLabel *m_miniWordsExampleText;
    QSpacerItem *spacer10_3;
    QWidget *minilexicon_signatures_file_layout_page;
    QVBoxLayout *vboxLayout52;
    QHBoxLayout *hboxLayout47;
    Q3ButtonGroup *buttonGroup5_2_2_2_4;
    QVBoxLayout *vboxLayout53;
    QCheckBox *m_miniSignaturesColumnTitlesFlag;
    QCheckBox *m_miniSignaturesUniformFieldWidthsFlag;
    QCheckBox *m_miniSignaturesIncludeStemListFlag;
    Q3ButtonGroup *buttonGroup2_2_3;
    QVBoxLayout *vboxLayout54;
    QRadioButton *m_miniSignaturesAlphabeticalSortFlag;
    QRadioButton *m_miniSignaturesCorpusCountSortFlag;
    QRadioButton *m_miniSignaturesStemCountSortFlag;
    QSpacerItem *spacer20_2_2_2_4;
    Q3ButtonGroup *buttonGroup3_2_2_2_4;
    QVBoxLayout *vboxLayout55;
    QLineEdit *m_miniSignaturesLine;
    QHBoxLayout *hboxLayout48;
    QPushButton *m_miniSignaturesAddIndexButton;
    QPushButton *m_miniSignaturesAddSigButton;
    QPushButton *m_miniSignaturesAddCorpusCountButton;
    QPushButton *m_miniSignaturesAddStemCountButton;
    QSpacerItem *spacer16_4;
    QHBoxLayout *hboxLayout49;
    QPushButton *m_miniSignaturesAddDescLengthButton;
    QPushButton *m_miniSignaturesAddRobustnessButton;
    QPushButton *m_miniSignaturesAddExemplarButton;
    QPushButton *m_miniSignaturesAddRemarksButton;
    QSpacerItem *spacer17_3;
    Q3GroupBox *groupBox18_2_2_2_4;
    QVBoxLayout *vboxLayout56;
    QLabel *m_miniSignaturesExampleText;
    QSpacerItem *spacer10_2_2_4;
    QWidget *minilexicon_stems_file_layout_page;
    QVBoxLayout *vboxLayout57;
    QHBoxLayout *hboxLayout50;
    Q3ButtonGroup *buttonGroup5_2_3_2;
    QVBoxLayout *vboxLayout58;
    QCheckBox *m_miniStemsColumnTitlesFlag;
    QCheckBox *m_miniStemsUniformFieldWidthsFlag;
    Q3ButtonGroup *buttonGroup2_2_2;
    QVBoxLayout *vboxLayout59;
    QRadioButton *m_miniStemsAlphabeticalSortFlag;
    QRadioButton *m_miniStemsCorpusCountSortFlag;
    QSpacerItem *spacer20_2_3_2;
    Q3ButtonGroup *buttonGroup3_2_3_2;
    QVBoxLayout *vboxLayout60;
    QLineEdit *m_miniStemsLine;
    QHBoxLayout *hboxLayout51;
    QPushButton *m_miniStemsAddIndexButton;
    QPushButton *m_miniStemsAddStemButton;
    QPushButton *m_miniStemsAddDescLengthButton;
    QPushButton *m_miniStemsAddCorpusCountButton;
    QSpacerItem *spacer18_2_2_2;
    QHBoxLayout *hboxLayout52;
    QPushButton *m_miniStemsAddSignatureButton;
    QPushButton *m_miniStemsAddOriginButton;
    QPushButton *m_miniStemsAddTypeButton;
    QSpacerItem *spacer19_2_2_2;
    Q3GroupBox *groupBox18_2_3_2;
    QVBoxLayout *vboxLayout61;
    QLabel *m_miniStemsExampleText;
    QSpacerItem *spacer10_3_2;
    QWidget *minilexicon_suffixes_file_layout_page;
    QVBoxLayout *vboxLayout62;
    QHBoxLayout *hboxLayout53;
    Q3ButtonGroup *buttonGroup5_2_2_2_3_3;
    QVBoxLayout *vboxLayout63;
    QCheckBox *m_miniSuffixesColumnTitlesFlag;
    QCheckBox *m_miniSuffixesUniformFieldWidthsFlag;
    QCheckBox *m_miniSuffixesIncludeStemListFlag;
    Q3ButtonGroup *buttonGroup2_2_3_2;
    QVBoxLayout *vboxLayout64;
    QRadioButton *m_miniSuffixesAlphabeticalSortFlag;
    QRadioButton *m_miniSuffixesCorpusCountSortFlag;
    QRadioButton *m_miniSuffixesStemCountSortFlag;
    QSpacerItem *spacer20_2_2_2_3_3;
    Q3ButtonGroup *buttonGroup3_2_2_2_3_3;
    QVBoxLayout *vboxLayout65;
    QLineEdit *m_miniSuffixesLine;
    QHBoxLayout *hboxLayout54;
    QPushButton *m_miniSuffixesAddIndexButton;
    QPushButton *m_miniSuffixesAddSuffixButton;
    QPushButton *m_miniSuffixesAddCorpusCountButton;
    QPushButton *m_miniSuffixesAddStemCountButton;
    QPushButton *m_miniSuffixesAddDescLengthButton;
    QSpacerItem *spacer16_3_3;
    Q3GroupBox *groupBox18_2_2_2_3_3;
    QVBoxLayout *vboxLayout66;
    QLabel *m_miniSuffixesExampleText;
    QSpacerItem *spacer10_2_2_3_3;
    QWidget *minilexicon_prefixes_file_layout_page;
    QVBoxLayout *vboxLayout67;
    QHBoxLayout *hboxLayout55;
    Q3ButtonGroup *buttonGroup5_2_2_2_3_3_2;
    QVBoxLayout *vboxLayout68;
    QCheckBox *m_miniPrefixesColumnTitlesFlag;
    QCheckBox *m_miniPrefixesUniformFieldWidthsFlag;
    QCheckBox *m_miniPrefixesIncludeStemListFlag;
    Q3ButtonGroup *buttonGroup2_2_3_2_2;
    QVBoxLayout *vboxLayout69;
    QRadioButton *m_miniPrefixesAlphabeticalSortFlag;
    QRadioButton *m_miniPrefixesCorpusCountSortFlag;
    QRadioButton *m_miniPrefixesStemCountSortFlag;
    QSpacerItem *spacer20_2_2_2_3_3_2;
    Q3ButtonGroup *buttonGroup3_2_2_2_3_3_2;
    QVBoxLayout *vboxLayout70;
    QLineEdit *m_miniPrefixesLine;
    QHBoxLayout *hboxLayout56;
    QPushButton *m_miniPrefixesAddIndexButton;
    QPushButton *m_miniPrefixesAddPrefixButton;
    QPushButton *m_miniPrefixesAddCorpusCountButton;
    QPushButton *m_miniPrefixesAddStemCountButton;
    QPushButton *m_miniPrefixesAddDescLengthButton;
    QSpacerItem *spacer16_3_3_2;
    Q3GroupBox *groupBox18_2_2_2_3_3_2;
    QVBoxLayout *vboxLayout71;
    QLabel *m_miniPrefixesExampleText;
    QSpacerItem *spacer10_2_2_3_3_2;
    QWidget *overwrite_confirmation_page;
    QVBoxLayout *vboxLayout72;
    QLabel *m_confirmationLabel;
    Q3TextEdit *m_confirmation;

    void setupUi(Q3Wizard *ExportWizardBase)
    {
        if (ExportWizardBase->objectName().isEmpty())
            ExportWizardBase->setObjectName(QString::fromUtf8("ExportWizardBase"));
        ExportWizardBase->resize(600, 532);
        project_info = new QWidget(ExportWizardBase);
        project_info->setObjectName(QString::fromUtf8("project_info"));
        vboxLayout = new QVBoxLayout(project_info);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        groupBox1 = new Q3GroupBox(project_info);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setMargin(11);
        gridLayout = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout);
        gridLayout->setAlignment(Qt::AlignTop);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_language = new QLineEdit(groupBox1);
        m_language->setObjectName(QString::fromUtf8("m_language"));

        gridLayout->addWidget(m_language, 1, 1, 1, 1);

        textLabel4 = new QLabel(groupBox1);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setWordWrap(false);

        gridLayout->addWidget(textLabel4, 2, 0, 1, 1);

        m_researchers = new QLineEdit(groupBox1);
        m_researchers->setObjectName(QString::fromUtf8("m_researchers"));

        gridLayout->addWidget(m_researchers, 2, 1, 1, 1);

        textLabel3 = new QLabel(groupBox1);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setWordWrap(false);

        gridLayout->addWidget(textLabel3, 1, 0, 1, 1);

        textLabel2 = new QLabel(groupBox1);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 0, 0, 1, 1);

        m_projectName = new QLineEdit(groupBox1);
        m_projectName->setObjectName(QString::fromUtf8("m_projectName"));

        gridLayout->addWidget(m_projectName, 0, 1, 1, 1);


        vboxLayout->addWidget(groupBox1);

        groupBox2 = new Q3GroupBox(project_info);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setColumnLayout(0, Qt::Vertical);
        groupBox2->layout()->setSpacing(6);
        groupBox2->layout()->setMargin(11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox2->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        m_brokenCorpusFlag = new QCheckBox(groupBox2);
        m_brokenCorpusFlag->setObjectName(QString::fromUtf8("m_brokenCorpusFlag"));

        gridLayout1->addWidget(m_brokenCorpusFlag, 1, 0, 1, 1);

        m_miniSignaturesFlag = new QCheckBox(groupBox2);
        m_miniSignaturesFlag->setObjectName(QString::fromUtf8("m_miniSignaturesFlag"));

        gridLayout1->addWidget(m_miniSignaturesFlag, 6, 2, 1, 2);

        m_miniSuffixesFlag = new QCheckBox(groupBox2);
        m_miniSuffixesFlag->setObjectName(QString::fromUtf8("m_miniSuffixesFlag"));

        gridLayout1->addWidget(m_miniSuffixesFlag, 6, 1, 1, 1);

        m_miniWordsFlag = new QCheckBox(groupBox2);
        m_miniWordsFlag->setObjectName(QString::fromUtf8("m_miniWordsFlag"));

        gridLayout1->addWidget(m_miniWordsFlag, 6, 0, 1, 1);

        textLabel5 = new QLabel(groupBox2);
        textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
        textLabel5->setWordWrap(false);

        gridLayout1->addWidget(textLabel5, 5, 0, 1, 2);

        m_miniPrefixesFlag = new QCheckBox(groupBox2);
        m_miniPrefixesFlag->setObjectName(QString::fromUtf8("m_miniPrefixesFlag"));

        gridLayout1->addWidget(m_miniPrefixesFlag, 7, 1, 1, 2);

        m_miniStemsFlag = new QCheckBox(groupBox2);
        m_miniStemsFlag->setObjectName(QString::fromUtf8("m_miniStemsFlag"));

        gridLayout1->addWidget(m_miniStemsFlag, 7, 0, 1, 1);

        m_allSuffixSigsFlag = new QCheckBox(groupBox2);
        m_allSuffixSigsFlag->setObjectName(QString::fromUtf8("m_allSuffixSigsFlag"));

        gridLayout1->addWidget(m_allSuffixSigsFlag, 3, 2, 1, 1);

        m_allPrefixesFlag = new QCheckBox(groupBox2);
        m_allPrefixesFlag->setObjectName(QString::fromUtf8("m_allPrefixesFlag"));

        gridLayout1->addWidget(m_allPrefixesFlag, 4, 1, 1, 1);

        m_allPrefixSigsFlag = new QCheckBox(groupBox2);
        m_allPrefixSigsFlag->setObjectName(QString::fromUtf8("m_allPrefixSigsFlag"));

        gridLayout1->addWidget(m_allPrefixSigsFlag, 4, 2, 1, 1);

        m_allSuffixesFlag = new QCheckBox(groupBox2);
        m_allSuffixesFlag->setObjectName(QString::fromUtf8("m_allSuffixesFlag"));

        gridLayout1->addWidget(m_allSuffixesFlag, 3, 1, 1, 1);

        m_allWordsFlag = new QCheckBox(groupBox2);
        m_allWordsFlag->setObjectName(QString::fromUtf8("m_allWordsFlag"));

        gridLayout1->addWidget(m_allWordsFlag, 3, 0, 1, 1);

        m_compoundsFlag = new QCheckBox(groupBox2);
        m_compoundsFlag->setObjectName(QString::fromUtf8("m_compoundsFlag"));
        m_compoundsFlag->setEnabled(true);

        gridLayout1->addWidget(m_compoundsFlag, 3, 3, 1, 1);

        m_allStemsFlag = new QCheckBox(groupBox2);
        m_allStemsFlag->setObjectName(QString::fromUtf8("m_allStemsFlag"));

        gridLayout1->addWidget(m_allStemsFlag, 4, 0, 1, 1);

        m_corpusWordsFlag = new QCheckBox(groupBox2);
        m_corpusWordsFlag->setObjectName(QString::fromUtf8("m_corpusWordsFlag"));

        gridLayout1->addWidget(m_corpusWordsFlag, 1, 1, 1, 1);

        textLabel6 = new QLabel(groupBox2);
        textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
        textLabel6->setWordWrap(false);

        gridLayout1->addWidget(textLabel6, 2, 0, 1, 1);

        textLabel1_2 = new QLabel(groupBox2);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        gridLayout1->addWidget(textLabel1_2, 0, 0, 1, 1);


        vboxLayout->addWidget(groupBox2);

        buttonGroup1 = new Q3ButtonGroup(project_info);
        buttonGroup1->setObjectName(QString::fromUtf8("buttonGroup1"));
        buttonGroup1->setColumnLayout(0, Qt::Vertical);
        buttonGroup1->layout()->setSpacing(6);
        buttonGroup1->layout()->setMargin(11);
        hboxLayout = new QHBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(buttonGroup1->layout());
        if (boxlayout2)
            boxlayout2->addLayout(hboxLayout);
        hboxLayout->setAlignment(Qt::AlignTop);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        m_simpleTextFlag = new QRadioButton(buttonGroup1);
        m_simpleTextFlag->setObjectName(QString::fromUtf8("m_simpleTextFlag"));
        m_simpleTextFlag->setChecked(true);

        hboxLayout->addWidget(m_simpleTextFlag);

        m_markUpFlag = new QRadioButton(buttonGroup1);
        m_markUpFlag->setObjectName(QString::fromUtf8("m_markUpFlag"));

        hboxLayout->addWidget(m_markUpFlag);

        m_bothFlag = new QRadioButton(buttonGroup1);
        m_bothFlag->setObjectName(QString::fromUtf8("m_bothFlag"));
        m_bothFlag->setMaximumSize(QSize(75, 32767));

        hboxLayout->addWidget(m_bothFlag);


        vboxLayout->addWidget(buttonGroup1);

        groupBox3 = new Q3GroupBox(project_info);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        groupBox3->setColumnLayout(0, Qt::Vertical);
        groupBox3->layout()->setSpacing(6);
        groupBox3->layout()->setMargin(11);
        hboxLayout1 = new QHBoxLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(groupBox3->layout());
        if (boxlayout3)
            boxlayout3->addLayout(hboxLayout1);
        hboxLayout1->setAlignment(Qt::AlignTop);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        m_outputDirectory = new QLineEdit(groupBox3);
        m_outputDirectory->setObjectName(QString::fromUtf8("m_outputDirectory"));
        m_outputDirectory->setMinimumSize(QSize(300, 0));
        m_outputDirectory->setReadOnly(true);

        hboxLayout1->addWidget(m_outputDirectory);

        m_outputDirBrowseButton = new QPushButton(groupBox3);
        m_outputDirBrowseButton->setObjectName(QString::fromUtf8("m_outputDirBrowseButton"));

        hboxLayout1->addWidget(m_outputDirBrowseButton);


        vboxLayout->addWidget(groupBox3);

        ExportWizardBase->addPage(project_info, QString::fromUtf8("Project Information"));
        style_sheet = new QWidget(ExportWizardBase);
        style_sheet->setObjectName(QString::fromUtf8("style_sheet"));
        vboxLayout1 = new QVBoxLayout(style_sheet);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setMargin(11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        groupBox29 = new Q3GroupBox(style_sheet);
        groupBox29->setObjectName(QString::fromUtf8("groupBox29"));
        groupBox29->setColumnLayout(0, Qt::Vertical);
        groupBox29->layout()->setSpacing(6);
        groupBox29->layout()->setMargin(11);
        vboxLayout2 = new QVBoxLayout();
        QBoxLayout *boxlayout4 = qobject_cast<QBoxLayout *>(groupBox29->layout());
        if (boxlayout4)
            boxlayout4->addLayout(vboxLayout2);
        vboxLayout2->setAlignment(Qt::AlignTop);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        textLabel6_2 = new QLabel(groupBox29);
        textLabel6_2->setObjectName(QString::fromUtf8("textLabel6_2"));
        textLabel6_2->setWordWrap(false);

        hboxLayout3->addWidget(textLabel6_2);

        m_wordStyle = new QLabel(groupBox29);
        m_wordStyle->setObjectName(QString::fromUtf8("m_wordStyle"));
        m_wordStyle->setMinimumSize(QSize(0, 30));
        m_wordStyle->setFrameShape(QFrame::Box);
        m_wordStyle->setAlignment(Qt::AlignCenter);
        m_wordStyle->setWordWrap(false);

        hboxLayout3->addWidget(m_wordStyle);


        vboxLayout2->addLayout(hboxLayout3);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        m_wordBoldFlag = new QCheckBox(groupBox29);
        m_wordBoldFlag->setObjectName(QString::fromUtf8("m_wordBoldFlag"));

        hboxLayout4->addWidget(m_wordBoldFlag);

        m_wordItalicFlag = new QCheckBox(groupBox29);
        m_wordItalicFlag->setObjectName(QString::fromUtf8("m_wordItalicFlag"));

        hboxLayout4->addWidget(m_wordItalicFlag);

        m_wordColorButton = new QPushButton(groupBox29);
        m_wordColorButton->setObjectName(QString::fromUtf8("m_wordColorButton"));

        hboxLayout4->addWidget(m_wordColorButton);


        vboxLayout2->addLayout(hboxLayout4);


        hboxLayout2->addWidget(groupBox29);

        groupBox29_5 = new Q3GroupBox(style_sheet);
        groupBox29_5->setObjectName(QString::fromUtf8("groupBox29_5"));
        groupBox29_5->setColumnLayout(0, Qt::Vertical);
        groupBox29_5->layout()->setSpacing(6);
        groupBox29_5->layout()->setMargin(11);
        vboxLayout3 = new QVBoxLayout();
        QBoxLayout *boxlayout5 = qobject_cast<QBoxLayout *>(groupBox29_5->layout());
        if (boxlayout5)
            boxlayout5->addLayout(vboxLayout3);
        vboxLayout3->setAlignment(Qt::AlignTop);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        textLabel6_2_5 = new QLabel(groupBox29_5);
        textLabel6_2_5->setObjectName(QString::fromUtf8("textLabel6_2_5"));
        textLabel6_2_5->setWordWrap(false);

        hboxLayout5->addWidget(textLabel6_2_5);

        m_stemStyle = new QLabel(groupBox29_5);
        m_stemStyle->setObjectName(QString::fromUtf8("m_stemStyle"));
        m_stemStyle->setMinimumSize(QSize(0, 30));
        m_stemStyle->setFrameShape(QFrame::Box);
        m_stemStyle->setAlignment(Qt::AlignCenter);
        m_stemStyle->setWordWrap(false);

        hboxLayout5->addWidget(m_stemStyle);


        vboxLayout3->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        m_stemBoldFlag = new QCheckBox(groupBox29_5);
        m_stemBoldFlag->setObjectName(QString::fromUtf8("m_stemBoldFlag"));

        hboxLayout6->addWidget(m_stemBoldFlag);

        m_stemItalicFlag = new QCheckBox(groupBox29_5);
        m_stemItalicFlag->setObjectName(QString::fromUtf8("m_stemItalicFlag"));

        hboxLayout6->addWidget(m_stemItalicFlag);

        m_stemColorButton = new QPushButton(groupBox29_5);
        m_stemColorButton->setObjectName(QString::fromUtf8("m_stemColorButton"));

        hboxLayout6->addWidget(m_stemColorButton);


        vboxLayout3->addLayout(hboxLayout6);


        hboxLayout2->addWidget(groupBox29_5);

        spacer37 = new QSpacerItem(130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer37);


        vboxLayout1->addLayout(hboxLayout2);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        groupBox29_3 = new Q3GroupBox(style_sheet);
        groupBox29_3->setObjectName(QString::fromUtf8("groupBox29_3"));
        groupBox29_3->setColumnLayout(0, Qt::Vertical);
        groupBox29_3->layout()->setSpacing(6);
        groupBox29_3->layout()->setMargin(11);
        vboxLayout4 = new QVBoxLayout();
        QBoxLayout *boxlayout6 = qobject_cast<QBoxLayout *>(groupBox29_3->layout());
        if (boxlayout6)
            boxlayout6->addLayout(vboxLayout4);
        vboxLayout4->setAlignment(Qt::AlignTop);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        textLabel6_2_3 = new QLabel(groupBox29_3);
        textLabel6_2_3->setObjectName(QString::fromUtf8("textLabel6_2_3"));
        textLabel6_2_3->setWordWrap(false);

        hboxLayout8->addWidget(textLabel6_2_3);

        m_suffixStyle = new QLabel(groupBox29_3);
        m_suffixStyle->setObjectName(QString::fromUtf8("m_suffixStyle"));
        m_suffixStyle->setMinimumSize(QSize(0, 30));
        m_suffixStyle->setFrameShape(QFrame::Box);
        m_suffixStyle->setAlignment(Qt::AlignCenter);
        m_suffixStyle->setWordWrap(false);

        hboxLayout8->addWidget(m_suffixStyle);


        vboxLayout4->addLayout(hboxLayout8);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        m_suffixBoldFlag = new QCheckBox(groupBox29_3);
        m_suffixBoldFlag->setObjectName(QString::fromUtf8("m_suffixBoldFlag"));

        hboxLayout9->addWidget(m_suffixBoldFlag);

        m_suffixItalicFlag = new QCheckBox(groupBox29_3);
        m_suffixItalicFlag->setObjectName(QString::fromUtf8("m_suffixItalicFlag"));

        hboxLayout9->addWidget(m_suffixItalicFlag);

        m_suffixColorButton = new QPushButton(groupBox29_3);
        m_suffixColorButton->setObjectName(QString::fromUtf8("m_suffixColorButton"));

        hboxLayout9->addWidget(m_suffixColorButton);


        vboxLayout4->addLayout(hboxLayout9);


        hboxLayout7->addWidget(groupBox29_3);

        groupBox29_4 = new Q3GroupBox(style_sheet);
        groupBox29_4->setObjectName(QString::fromUtf8("groupBox29_4"));
        groupBox29_4->setColumnLayout(0, Qt::Vertical);
        groupBox29_4->layout()->setSpacing(6);
        groupBox29_4->layout()->setMargin(11);
        vboxLayout5 = new QVBoxLayout();
        QBoxLayout *boxlayout7 = qobject_cast<QBoxLayout *>(groupBox29_4->layout());
        if (boxlayout7)
            boxlayout7->addLayout(vboxLayout5);
        vboxLayout5->setAlignment(Qt::AlignTop);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        textLabel6_2_4 = new QLabel(groupBox29_4);
        textLabel6_2_4->setObjectName(QString::fromUtf8("textLabel6_2_4"));
        textLabel6_2_4->setWordWrap(false);

        hboxLayout10->addWidget(textLabel6_2_4);

        m_prefixStyle = new QLabel(groupBox29_4);
        m_prefixStyle->setObjectName(QString::fromUtf8("m_prefixStyle"));
        m_prefixStyle->setMinimumSize(QSize(0, 30));
        m_prefixStyle->setFrameShape(QFrame::Box);
        m_prefixStyle->setAlignment(Qt::AlignCenter);
        m_prefixStyle->setWordWrap(false);

        hboxLayout10->addWidget(m_prefixStyle);


        vboxLayout5->addLayout(hboxLayout10);

        hboxLayout11 = new QHBoxLayout();
        hboxLayout11->setSpacing(6);
        hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
        m_prefixBoldFlag = new QCheckBox(groupBox29_4);
        m_prefixBoldFlag->setObjectName(QString::fromUtf8("m_prefixBoldFlag"));

        hboxLayout11->addWidget(m_prefixBoldFlag);

        m_prefixItalicFlag = new QCheckBox(groupBox29_4);
        m_prefixItalicFlag->setObjectName(QString::fromUtf8("m_prefixItalicFlag"));

        hboxLayout11->addWidget(m_prefixItalicFlag);

        m_prefixColorButton = new QPushButton(groupBox29_4);
        m_prefixColorButton->setObjectName(QString::fromUtf8("m_prefixColorButton"));

        hboxLayout11->addWidget(m_prefixColorButton);


        vboxLayout5->addLayout(hboxLayout11);


        hboxLayout7->addWidget(groupBox29_4);

        spacer36 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(spacer36);


        vboxLayout1->addLayout(hboxLayout7);

        hboxLayout12 = new QHBoxLayout();
        hboxLayout12->setSpacing(6);
        hboxLayout12->setObjectName(QString::fromUtf8("hboxLayout12"));
        groupBox29_2 = new Q3GroupBox(style_sheet);
        groupBox29_2->setObjectName(QString::fromUtf8("groupBox29_2"));
        groupBox29_2->setColumnLayout(0, Qt::Vertical);
        groupBox29_2->layout()->setSpacing(6);
        groupBox29_2->layout()->setMargin(11);
        vboxLayout6 = new QVBoxLayout();
        QBoxLayout *boxlayout8 = qobject_cast<QBoxLayout *>(groupBox29_2->layout());
        if (boxlayout8)
            boxlayout8->addLayout(vboxLayout6);
        vboxLayout6->setAlignment(Qt::AlignTop);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        hboxLayout13 = new QHBoxLayout();
        hboxLayout13->setSpacing(6);
        hboxLayout13->setObjectName(QString::fromUtf8("hboxLayout13"));
        textLabel6_2_2 = new QLabel(groupBox29_2);
        textLabel6_2_2->setObjectName(QString::fromUtf8("textLabel6_2_2"));
        textLabel6_2_2->setWordWrap(false);

        hboxLayout13->addWidget(textLabel6_2_2);

        m_signatureStyle = new QLabel(groupBox29_2);
        m_signatureStyle->setObjectName(QString::fromUtf8("m_signatureStyle"));
        m_signatureStyle->setMinimumSize(QSize(0, 30));
        m_signatureStyle->setFrameShape(QFrame::Box);
        m_signatureStyle->setAlignment(Qt::AlignCenter);
        m_signatureStyle->setWordWrap(false);

        hboxLayout13->addWidget(m_signatureStyle);


        vboxLayout6->addLayout(hboxLayout13);

        hboxLayout14 = new QHBoxLayout();
        hboxLayout14->setSpacing(6);
        hboxLayout14->setObjectName(QString::fromUtf8("hboxLayout14"));
        m_signatureBoldFlag = new QCheckBox(groupBox29_2);
        m_signatureBoldFlag->setObjectName(QString::fromUtf8("m_signatureBoldFlag"));

        hboxLayout14->addWidget(m_signatureBoldFlag);

        m_signatureItalicFlag = new QCheckBox(groupBox29_2);
        m_signatureItalicFlag->setObjectName(QString::fromUtf8("m_signatureItalicFlag"));

        hboxLayout14->addWidget(m_signatureItalicFlag);

        m_signatureColorButton = new QPushButton(groupBox29_2);
        m_signatureColorButton->setObjectName(QString::fromUtf8("m_signatureColorButton"));

        hboxLayout14->addWidget(m_signatureColorButton);


        vboxLayout6->addLayout(hboxLayout14);


        hboxLayout12->addWidget(groupBox29_2);

        groupBox29_6 = new Q3GroupBox(style_sheet);
        groupBox29_6->setObjectName(QString::fromUtf8("groupBox29_6"));
        groupBox29_6->setColumnLayout(0, Qt::Vertical);
        groupBox29_6->layout()->setSpacing(6);
        groupBox29_6->layout()->setMargin(11);
        vboxLayout7 = new QVBoxLayout();
        QBoxLayout *boxlayout9 = qobject_cast<QBoxLayout *>(groupBox29_6->layout());
        if (boxlayout9)
            boxlayout9->addLayout(vboxLayout7);
        vboxLayout7->setAlignment(Qt::AlignTop);
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        hboxLayout15 = new QHBoxLayout();
        hboxLayout15->setSpacing(6);
        hboxLayout15->setObjectName(QString::fromUtf8("hboxLayout15"));
        textLabel6_2_6 = new QLabel(groupBox29_6);
        textLabel6_2_6->setObjectName(QString::fromUtf8("textLabel6_2_6"));
        textLabel6_2_6->setWordWrap(false);

        hboxLayout15->addWidget(textLabel6_2_6);

        m_compoundStyle = new QLabel(groupBox29_6);
        m_compoundStyle->setObjectName(QString::fromUtf8("m_compoundStyle"));
        m_compoundStyle->setMinimumSize(QSize(0, 30));
        m_compoundStyle->setFrameShape(QFrame::Box);
        m_compoundStyle->setAlignment(Qt::AlignCenter);
        m_compoundStyle->setWordWrap(false);

        hboxLayout15->addWidget(m_compoundStyle);


        vboxLayout7->addLayout(hboxLayout15);

        hboxLayout16 = new QHBoxLayout();
        hboxLayout16->setSpacing(6);
        hboxLayout16->setObjectName(QString::fromUtf8("hboxLayout16"));
        m_compoundBoldFlag = new QCheckBox(groupBox29_6);
        m_compoundBoldFlag->setObjectName(QString::fromUtf8("m_compoundBoldFlag"));

        hboxLayout16->addWidget(m_compoundBoldFlag);

        m_compoundItalicFlag = new QCheckBox(groupBox29_6);
        m_compoundItalicFlag->setObjectName(QString::fromUtf8("m_compoundItalicFlag"));

        hboxLayout16->addWidget(m_compoundItalicFlag);

        m_compoundColorButton = new QPushButton(groupBox29_6);
        m_compoundColorButton->setObjectName(QString::fromUtf8("m_compoundColorButton"));

        hboxLayout16->addWidget(m_compoundColorButton);


        vboxLayout7->addLayout(hboxLayout16);


        hboxLayout12->addWidget(groupBox29_6);

        spacer35 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout12->addItem(spacer35);


        vboxLayout1->addLayout(hboxLayout12);

        spacer14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacer14);

        ExportWizardBase->addPage(style_sheet, QString::fromUtf8("Text Styles"));
        corpus_word_file_layout = new QWidget(ExportWizardBase);
        corpus_word_file_layout->setObjectName(QString::fromUtf8("corpus_word_file_layout"));
        vboxLayout8 = new QVBoxLayout(corpus_word_file_layout);
        vboxLayout8->setSpacing(6);
        vboxLayout8->setMargin(11);
        vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
        vboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout17 = new QHBoxLayout();
        hboxLayout17->setSpacing(6);
        hboxLayout17->setObjectName(QString::fromUtf8("hboxLayout17"));
        buttonGroup5 = new Q3ButtonGroup(corpus_word_file_layout);
        buttonGroup5->setObjectName(QString::fromUtf8("buttonGroup5"));
        buttonGroup5->setColumnLayout(0, Qt::Vertical);
        buttonGroup5->layout()->setSpacing(6);
        buttonGroup5->layout()->setMargin(11);
        vboxLayout9 = new QVBoxLayout();
        QBoxLayout *boxlayout10 = qobject_cast<QBoxLayout *>(buttonGroup5->layout());
        if (boxlayout10)
            boxlayout10->addLayout(vboxLayout9);
        vboxLayout9->setAlignment(Qt::AlignTop);
        vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
        m_corpusWordsAnalyzedOnlyFlag = new QCheckBox(buttonGroup5);
        m_corpusWordsAnalyzedOnlyFlag->setObjectName(QString::fromUtf8("m_corpusWordsAnalyzedOnlyFlag"));

        vboxLayout9->addWidget(m_corpusWordsAnalyzedOnlyFlag);

        m_corpusWordsColumnTitlesFlag = new QCheckBox(buttonGroup5);
        m_corpusWordsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_corpusWordsColumnTitlesFlag"));
        m_corpusWordsColumnTitlesFlag->setChecked(true);

        vboxLayout9->addWidget(m_corpusWordsColumnTitlesFlag);

        m_corpusWordsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5);
        m_corpusWordsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_corpusWordsUniformFieldWidthsFlag"));
        m_corpusWordsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout9->addWidget(m_corpusWordsUniformFieldWidthsFlag);


        hboxLayout17->addWidget(buttonGroup5);

        buttonGroup2 = new Q3ButtonGroup(corpus_word_file_layout);
        buttonGroup2->setObjectName(QString::fromUtf8("buttonGroup2"));
        buttonGroup2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2->layout()->setSpacing(6);
        buttonGroup2->layout()->setMargin(11);
        vboxLayout10 = new QVBoxLayout();
        QBoxLayout *boxlayout11 = qobject_cast<QBoxLayout *>(buttonGroup2->layout());
        if (boxlayout11)
            boxlayout11->addLayout(vboxLayout10);
        vboxLayout10->setAlignment(Qt::AlignTop);
        vboxLayout10->setObjectName(QString::fromUtf8("vboxLayout10"));
        m_corpusWordsAlphabeticalSortFlag = new QRadioButton(buttonGroup2);
        m_corpusWordsAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_corpusWordsAlphabeticalSortFlag"));
        m_corpusWordsAlphabeticalSortFlag->setChecked(true);

        vboxLayout10->addWidget(m_corpusWordsAlphabeticalSortFlag);

        m_corpusWordsCorpusCountSortFlag = new QRadioButton(buttonGroup2);
        m_corpusWordsCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_corpusWordsCorpusCountSortFlag"));

        vboxLayout10->addWidget(m_corpusWordsCorpusCountSortFlag);

        m_corpusWordsMorphemeCountSortFlag = new QRadioButton(buttonGroup2);
        m_corpusWordsMorphemeCountSortFlag->setObjectName(QString::fromUtf8("m_corpusWordsMorphemeCountSortFlag"));

        vboxLayout10->addWidget(m_corpusWordsMorphemeCountSortFlag);


        hboxLayout17->addWidget(buttonGroup2);

        spacer20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout17->addItem(spacer20);


        vboxLayout8->addLayout(hboxLayout17);

        buttonGroup3 = new Q3ButtonGroup(corpus_word_file_layout);
        buttonGroup3->setObjectName(QString::fromUtf8("buttonGroup3"));
        buttonGroup3->setColumnLayout(0, Qt::Vertical);
        buttonGroup3->layout()->setSpacing(6);
        buttonGroup3->layout()->setMargin(11);
        vboxLayout11 = new QVBoxLayout();
        QBoxLayout *boxlayout12 = qobject_cast<QBoxLayout *>(buttonGroup3->layout());
        if (boxlayout12)
            boxlayout12->addLayout(vboxLayout11);
        vboxLayout11->setAlignment(Qt::AlignTop);
        vboxLayout11->setObjectName(QString::fromUtf8("vboxLayout11"));
        m_corpusWordsLine = new QLineEdit(buttonGroup3);
        m_corpusWordsLine->setObjectName(QString::fromUtf8("m_corpusWordsLine"));

        vboxLayout11->addWidget(m_corpusWordsLine);

        hboxLayout18 = new QHBoxLayout();
        hboxLayout18->setSpacing(6);
        hboxLayout18->setObjectName(QString::fromUtf8("hboxLayout18"));
        m_corpusWordsAddIndexButton = new QPushButton(buttonGroup3);
        m_corpusWordsAddIndexButton->setObjectName(QString::fromUtf8("m_corpusWordsAddIndexButton"));

        hboxLayout18->addWidget(m_corpusWordsAddIndexButton);

        m_corpusWordsAddWordButton = new QPushButton(buttonGroup3);
        m_corpusWordsAddWordButton->setObjectName(QString::fromUtf8("m_corpusWordsAddWordButton"));

        hboxLayout18->addWidget(m_corpusWordsAddWordButton);

        m_corpusWordsAddCorpusCountButton = new QPushButton(buttonGroup3);
        m_corpusWordsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_corpusWordsAddCorpusCountButton"));

        hboxLayout18->addWidget(m_corpusWordsAddCorpusCountButton);

        m_corpusWordsAddMorphCountButton = new QPushButton(buttonGroup3);
        m_corpusWordsAddMorphCountButton->setObjectName(QString::fromUtf8("m_corpusWordsAddMorphCountButton"));

        hboxLayout18->addWidget(m_corpusWordsAddMorphCountButton);

        m_corpusWordsAddMorphsButton = new QPushButton(buttonGroup3);
        m_corpusWordsAddMorphsButton->setObjectName(QString::fromUtf8("m_corpusWordsAddMorphsButton"));

        hboxLayout18->addWidget(m_corpusWordsAddMorphsButton);

        spacer18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout18->addItem(spacer18);


        vboxLayout11->addLayout(hboxLayout18);


        vboxLayout8->addWidget(buttonGroup3);

        hboxLayout19 = new QHBoxLayout();
        hboxLayout19->setSpacing(6);
        hboxLayout19->setObjectName(QString::fromUtf8("hboxLayout19"));
        groupBox17 = new Q3GroupBox(corpus_word_file_layout);
        groupBox17->setObjectName(QString::fromUtf8("groupBox17"));
        groupBox17->setColumnLayout(0, Qt::Vertical);
        groupBox17->layout()->setSpacing(6);
        groupBox17->layout()->setMargin(11);
        hboxLayout20 = new QHBoxLayout();
        QBoxLayout *boxlayout13 = qobject_cast<QBoxLayout *>(groupBox17->layout());
        if (boxlayout13)
            boxlayout13->addLayout(hboxLayout20);
        hboxLayout20->setAlignment(Qt::AlignTop);
        hboxLayout20->setObjectName(QString::fromUtf8("hboxLayout20"));
        textLabel3_2 = new QLabel(groupBox17);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setWordWrap(false);

        hboxLayout20->addWidget(textLabel3_2);

        m_corpusWordsMorphemeFieldDelimiter = new QLineEdit(groupBox17);
        m_corpusWordsMorphemeFieldDelimiter->setObjectName(QString::fromUtf8("m_corpusWordsMorphemeFieldDelimiter"));
        m_corpusWordsMorphemeFieldDelimiter->setMaximumSize(QSize(50, 32767));
        m_corpusWordsMorphemeFieldDelimiter->setAlignment(Qt::AlignHCenter);

        hboxLayout20->addWidget(m_corpusWordsMorphemeFieldDelimiter);

        textLabel4_2 = new QLabel(groupBox17);
        textLabel4_2->setObjectName(QString::fromUtf8("textLabel4_2"));
        textLabel4_2->setWordWrap(false);

        hboxLayout20->addWidget(textLabel4_2);


        hboxLayout19->addWidget(groupBox17);

        spacer19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout19->addItem(spacer19);


        vboxLayout8->addLayout(hboxLayout19);

        groupBox18 = new Q3GroupBox(corpus_word_file_layout);
        groupBox18->setObjectName(QString::fromUtf8("groupBox18"));
        groupBox18->setColumnLayout(0, Qt::Vertical);
        groupBox18->layout()->setSpacing(6);
        groupBox18->layout()->setMargin(11);
        vboxLayout12 = new QVBoxLayout();
        QBoxLayout *boxlayout14 = qobject_cast<QBoxLayout *>(groupBox18->layout());
        if (boxlayout14)
            boxlayout14->addLayout(vboxLayout12);
        vboxLayout12->setAlignment(Qt::AlignTop);
        vboxLayout12->setObjectName(QString::fromUtf8("vboxLayout12"));
        m_corpusWordsExampleText = new QLabel(groupBox18);
        m_corpusWordsExampleText->setObjectName(QString::fromUtf8("m_corpusWordsExampleText"));
        m_corpusWordsExampleText->setFrameShape(QFrame::Box);
        m_corpusWordsExampleText->setWordWrap(false);

        vboxLayout12->addWidget(m_corpusWordsExampleText);


        vboxLayout8->addWidget(groupBox18);

        spacer12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout8->addItem(spacer12);

        ExportWizardBase->addPage(corpus_word_file_layout, QString::fromUtf8("Corpus Words File Layout"));
        compounds_file_layout_page = new QWidget(ExportWizardBase);
        compounds_file_layout_page->setObjectName(QString::fromUtf8("compounds_file_layout_page"));
        vboxLayout13 = new QVBoxLayout(compounds_file_layout_page);
        vboxLayout13->setSpacing(6);
        vboxLayout13->setMargin(11);
        vboxLayout13->setObjectName(QString::fromUtf8("vboxLayout13"));
        vboxLayout13->setContentsMargins(0, 0, 0, 0);
        hboxLayout21 = new QHBoxLayout();
        hboxLayout21->setSpacing(6);
        hboxLayout21->setObjectName(QString::fromUtf8("hboxLayout21"));
        buttonGroup5_3 = new Q3ButtonGroup(compounds_file_layout_page);
        buttonGroup5_3->setObjectName(QString::fromUtf8("buttonGroup5_3"));
        buttonGroup5_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_3->layout()->setSpacing(6);
        buttonGroup5_3->layout()->setMargin(11);
        vboxLayout14 = new QVBoxLayout();
        QBoxLayout *boxlayout15 = qobject_cast<QBoxLayout *>(buttonGroup5_3->layout());
        if (boxlayout15)
            boxlayout15->addLayout(vboxLayout14);
        vboxLayout14->setAlignment(Qt::AlignTop);
        vboxLayout14->setObjectName(QString::fromUtf8("vboxLayout14"));
        m_compoundsColumnTitlesFlag = new QCheckBox(buttonGroup5_3);
        m_compoundsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_compoundsColumnTitlesFlag"));
        m_compoundsColumnTitlesFlag->setChecked(true);

        vboxLayout14->addWidget(m_compoundsColumnTitlesFlag);

        m_compoundsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_3);
        m_compoundsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_compoundsUniformFieldWidthsFlag"));
        m_compoundsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout14->addWidget(m_compoundsUniformFieldWidthsFlag);


        hboxLayout21->addWidget(buttonGroup5_3);

        buttonGroup2_3 = new Q3ButtonGroup(compounds_file_layout_page);
        buttonGroup2_3->setObjectName(QString::fromUtf8("buttonGroup2_3"));
        buttonGroup2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_3->layout()->setSpacing(6);
        buttonGroup2_3->layout()->setMargin(11);
        vboxLayout15 = new QVBoxLayout();
        QBoxLayout *boxlayout16 = qobject_cast<QBoxLayout *>(buttonGroup2_3->layout());
        if (boxlayout16)
            boxlayout16->addLayout(vboxLayout15);
        vboxLayout15->setAlignment(Qt::AlignTop);
        vboxLayout15->setObjectName(QString::fromUtf8("vboxLayout15"));
        m_compoundsAlphabeticalSortFlag = new QRadioButton(buttonGroup2_3);
        m_compoundsAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_compoundsAlphabeticalSortFlag"));
        m_compoundsAlphabeticalSortFlag->setChecked(true);

        vboxLayout15->addWidget(m_compoundsAlphabeticalSortFlag);

        m_compoundsCorpusCountSortFlag = new QRadioButton(buttonGroup2_3);
        m_compoundsCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_compoundsCorpusCountSortFlag"));

        vboxLayout15->addWidget(m_compoundsCorpusCountSortFlag);

        m_compoundsMorphemeCountSortFlag = new QRadioButton(buttonGroup2_3);
        m_compoundsMorphemeCountSortFlag->setObjectName(QString::fromUtf8("m_compoundsMorphemeCountSortFlag"));

        vboxLayout15->addWidget(m_compoundsMorphemeCountSortFlag);


        hboxLayout21->addWidget(buttonGroup2_3);

        spacer20_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout21->addItem(spacer20_4);


        vboxLayout13->addLayout(hboxLayout21);

        buttonGroup3_3 = new Q3ButtonGroup(compounds_file_layout_page);
        buttonGroup3_3->setObjectName(QString::fromUtf8("buttonGroup3_3"));
        buttonGroup3_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_3->layout()->setSpacing(6);
        buttonGroup3_3->layout()->setMargin(11);
        vboxLayout16 = new QVBoxLayout();
        QBoxLayout *boxlayout17 = qobject_cast<QBoxLayout *>(buttonGroup3_3->layout());
        if (boxlayout17)
            boxlayout17->addLayout(vboxLayout16);
        vboxLayout16->setAlignment(Qt::AlignTop);
        vboxLayout16->setObjectName(QString::fromUtf8("vboxLayout16"));
        m_compoundsLine = new QLineEdit(buttonGroup3_3);
        m_compoundsLine->setObjectName(QString::fromUtf8("m_compoundsLine"));

        vboxLayout16->addWidget(m_compoundsLine);

        hboxLayout22 = new QHBoxLayout();
        hboxLayout22->setSpacing(6);
        hboxLayout22->setObjectName(QString::fromUtf8("hboxLayout22"));
        m_compoundsAddIndexButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddIndexButton->setObjectName(QString::fromUtf8("m_compoundsAddIndexButton"));

        hboxLayout22->addWidget(m_compoundsAddIndexButton);

        m_compoundsAddWordButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddWordButton->setObjectName(QString::fromUtf8("m_compoundsAddWordButton"));

        hboxLayout22->addWidget(m_compoundsAddWordButton);

        m_compoundsAddCorpusCountButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_compoundsAddCorpusCountButton"));

        hboxLayout22->addWidget(m_compoundsAddCorpusCountButton);

        m_compoundsAddMorphCountButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddMorphCountButton->setObjectName(QString::fromUtf8("m_compoundsAddMorphCountButton"));

        hboxLayout22->addWidget(m_compoundsAddMorphCountButton);

        spacer18_3 = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout22->addItem(spacer18_3);


        vboxLayout16->addLayout(hboxLayout22);

        hboxLayout23 = new QHBoxLayout();
        hboxLayout23->setSpacing(6);
        hboxLayout23->setObjectName(QString::fromUtf8("hboxLayout23"));
        m_compoundsAddMorphsButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddMorphsButton->setObjectName(QString::fromUtf8("m_compoundsAddMorphsButton"));

        hboxLayout23->addWidget(m_compoundsAddMorphsButton);

        m_compoundsAddSuffixnessButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddSuffixnessButton->setObjectName(QString::fromUtf8("m_compoundsAddSuffixnessButton"));

        hboxLayout23->addWidget(m_compoundsAddSuffixnessButton);

        m_compoundsAddPrefixnessButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddPrefixnessButton->setObjectName(QString::fromUtf8("m_compoundsAddPrefixnessButton"));

        hboxLayout23->addWidget(m_compoundsAddPrefixnessButton);

        m_compoundsAddParseButton = new QPushButton(buttonGroup3_3);
        m_compoundsAddParseButton->setObjectName(QString::fromUtf8("m_compoundsAddParseButton"));

        hboxLayout23->addWidget(m_compoundsAddParseButton);

        spacer53 = new QSpacerItem(180, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout23->addItem(spacer53);


        vboxLayout16->addLayout(hboxLayout23);


        vboxLayout13->addWidget(buttonGroup3_3);

        hboxLayout24 = new QHBoxLayout();
        hboxLayout24->setSpacing(6);
        hboxLayout24->setObjectName(QString::fromUtf8("hboxLayout24"));
        groupBox17_2 = new Q3GroupBox(compounds_file_layout_page);
        groupBox17_2->setObjectName(QString::fromUtf8("groupBox17_2"));
        groupBox17_2->setColumnLayout(0, Qt::Vertical);
        groupBox17_2->layout()->setSpacing(6);
        groupBox17_2->layout()->setMargin(11);
        hboxLayout25 = new QHBoxLayout();
        QBoxLayout *boxlayout18 = qobject_cast<QBoxLayout *>(groupBox17_2->layout());
        if (boxlayout18)
            boxlayout18->addLayout(hboxLayout25);
        hboxLayout25->setAlignment(Qt::AlignTop);
        hboxLayout25->setObjectName(QString::fromUtf8("hboxLayout25"));
        textLabel3_2_2 = new QLabel(groupBox17_2);
        textLabel3_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2"));
        textLabel3_2_2->setWordWrap(false);

        hboxLayout25->addWidget(textLabel3_2_2);

        m_compoundsMorphemeFieldDelimiter = new QLineEdit(groupBox17_2);
        m_compoundsMorphemeFieldDelimiter->setObjectName(QString::fromUtf8("m_compoundsMorphemeFieldDelimiter"));
        m_compoundsMorphemeFieldDelimiter->setMaximumSize(QSize(50, 32767));
        m_compoundsMorphemeFieldDelimiter->setAlignment(Qt::AlignHCenter);

        hboxLayout25->addWidget(m_compoundsMorphemeFieldDelimiter);

        textLabel4_2_2 = new QLabel(groupBox17_2);
        textLabel4_2_2->setObjectName(QString::fromUtf8("textLabel4_2_2"));
        textLabel4_2_2->setWordWrap(false);

        hboxLayout25->addWidget(textLabel4_2_2);


        hboxLayout24->addWidget(groupBox17_2);

        spacer19_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout24->addItem(spacer19_3);


        vboxLayout13->addLayout(hboxLayout24);

        groupBox18_3 = new Q3GroupBox(compounds_file_layout_page);
        groupBox18_3->setObjectName(QString::fromUtf8("groupBox18_3"));
        groupBox18_3->setColumnLayout(0, Qt::Vertical);
        groupBox18_3->layout()->setSpacing(6);
        groupBox18_3->layout()->setMargin(11);
        vboxLayout17 = new QVBoxLayout();
        QBoxLayout *boxlayout19 = qobject_cast<QBoxLayout *>(groupBox18_3->layout());
        if (boxlayout19)
            boxlayout19->addLayout(vboxLayout17);
        vboxLayout17->setAlignment(Qt::AlignTop);
        vboxLayout17->setObjectName(QString::fromUtf8("vboxLayout17"));
        m_compoundsExampleText = new QLabel(groupBox18_3);
        m_compoundsExampleText->setObjectName(QString::fromUtf8("m_compoundsExampleText"));
        m_compoundsExampleText->setFrameShape(QFrame::Box);
        m_compoundsExampleText->setWordWrap(false);

        vboxLayout17->addWidget(m_compoundsExampleText);


        vboxLayout13->addWidget(groupBox18_3);

        spacer12_2 = new QSpacerItem(20, 96, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout13->addItem(spacer12_2);

        ExportWizardBase->addPage(compounds_file_layout_page, QString::fromUtf8("Compounds File Layout"));
        linkers_file_layout_page = new QWidget(ExportWizardBase);
        linkers_file_layout_page->setObjectName(QString::fromUtf8("linkers_file_layout_page"));
        vboxLayout18 = new QVBoxLayout(linkers_file_layout_page);
        vboxLayout18->setSpacing(6);
        vboxLayout18->setMargin(11);
        vboxLayout18->setObjectName(QString::fromUtf8("vboxLayout18"));
        vboxLayout18->setContentsMargins(0, 0, 0, 0);
        hboxLayout26 = new QHBoxLayout();
        hboxLayout26->setSpacing(6);
        hboxLayout26->setObjectName(QString::fromUtf8("hboxLayout26"));
        buttonGroup5_2_2_2_3_3_3 = new Q3ButtonGroup(linkers_file_layout_page);
        buttonGroup5_2_2_2_3_3_3->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_3_3_3"));
        buttonGroup5_2_2_2_3_3_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_3_3_3->layout()->setSpacing(6);
        buttonGroup5_2_2_2_3_3_3->layout()->setMargin(11);
        vboxLayout19 = new QVBoxLayout();
        QBoxLayout *boxlayout20 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_3_3_3->layout());
        if (boxlayout20)
            boxlayout20->addLayout(vboxLayout19);
        vboxLayout19->setAlignment(Qt::AlignTop);
        vboxLayout19->setObjectName(QString::fromUtf8("vboxLayout19"));
        m_linkersColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_3_3_3);
        m_linkersColumnTitlesFlag->setObjectName(QString::fromUtf8("m_linkersColumnTitlesFlag"));
        m_linkersColumnTitlesFlag->setChecked(true);

        vboxLayout19->addWidget(m_linkersColumnTitlesFlag);

        m_linkersUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_3_3_3);
        m_linkersUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_linkersUniformFieldWidthsFlag"));
        m_linkersUniformFieldWidthsFlag->setChecked(true);

        vboxLayout19->addWidget(m_linkersUniformFieldWidthsFlag);

        m_linkersIncludeCompoundListFlag = new QCheckBox(buttonGroup5_2_2_2_3_3_3);
        m_linkersIncludeCompoundListFlag->setObjectName(QString::fromUtf8("m_linkersIncludeCompoundListFlag"));
        m_linkersIncludeCompoundListFlag->setChecked(true);

        vboxLayout19->addWidget(m_linkersIncludeCompoundListFlag);


        hboxLayout26->addWidget(buttonGroup5_2_2_2_3_3_3);

        buttonGroup2_2_3_2_3 = new Q3ButtonGroup(linkers_file_layout_page);
        buttonGroup2_2_3_2_3->setObjectName(QString::fromUtf8("buttonGroup2_2_3_2_3"));
        buttonGroup2_2_3_2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2_3_2_3->layout()->setSpacing(6);
        buttonGroup2_2_3_2_3->layout()->setMargin(11);
        vboxLayout20 = new QVBoxLayout();
        QBoxLayout *boxlayout21 = qobject_cast<QBoxLayout *>(buttonGroup2_2_3_2_3->layout());
        if (boxlayout21)
            boxlayout21->addLayout(vboxLayout20);
        vboxLayout20->setAlignment(Qt::AlignTop);
        vboxLayout20->setObjectName(QString::fromUtf8("vboxLayout20"));
        m_linkersAlphabeticalSortFlag = new QRadioButton(buttonGroup2_2_3_2_3);
        m_linkersAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_linkersAlphabeticalSortFlag"));
        m_linkersAlphabeticalSortFlag->setChecked(true);

        vboxLayout20->addWidget(m_linkersAlphabeticalSortFlag);

        m_linkersCorpusCountSortFlag = new QRadioButton(buttonGroup2_2_3_2_3);
        m_linkersCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_linkersCorpusCountSortFlag"));

        vboxLayout20->addWidget(m_linkersCorpusCountSortFlag);


        hboxLayout26->addWidget(buttonGroup2_2_3_2_3);

        spacer20_2_2_2_3_3_3 = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout26->addItem(spacer20_2_2_2_3_3_3);


        vboxLayout18->addLayout(hboxLayout26);

        buttonGroup3_2_2_2_3_3_3 = new Q3ButtonGroup(linkers_file_layout_page);
        buttonGroup3_2_2_2_3_3_3->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_3_3_3"));
        buttonGroup3_2_2_2_3_3_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_3_3_3->layout()->setSpacing(6);
        buttonGroup3_2_2_2_3_3_3->layout()->setMargin(11);
        vboxLayout21 = new QVBoxLayout();
        QBoxLayout *boxlayout22 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_3_3_3->layout());
        if (boxlayout22)
            boxlayout22->addLayout(vboxLayout21);
        vboxLayout21->setAlignment(Qt::AlignTop);
        vboxLayout21->setObjectName(QString::fromUtf8("vboxLayout21"));
        m_linkersLine = new QLineEdit(buttonGroup3_2_2_2_3_3_3);
        m_linkersLine->setObjectName(QString::fromUtf8("m_linkersLine"));

        vboxLayout21->addWidget(m_linkersLine);

        hboxLayout27 = new QHBoxLayout();
        hboxLayout27->setSpacing(6);
        hboxLayout27->setObjectName(QString::fromUtf8("hboxLayout27"));
        m_linkersAddIndexButton = new QPushButton(buttonGroup3_2_2_2_3_3_3);
        m_linkersAddIndexButton->setObjectName(QString::fromUtf8("m_linkersAddIndexButton"));

        hboxLayout27->addWidget(m_linkersAddIndexButton);

        m_linkersAddLinkerButton = new QPushButton(buttonGroup3_2_2_2_3_3_3);
        m_linkersAddLinkerButton->setObjectName(QString::fromUtf8("m_linkersAddLinkerButton"));

        hboxLayout27->addWidget(m_linkersAddLinkerButton);

        m_linkersAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_3_3_3);
        m_linkersAddCorpusCountButton->setObjectName(QString::fromUtf8("m_linkersAddCorpusCountButton"));

        hboxLayout27->addWidget(m_linkersAddCorpusCountButton);

        m_linkersAddCompoundCountButton = new QPushButton(buttonGroup3_2_2_2_3_3_3);
        m_linkersAddCompoundCountButton->setObjectName(QString::fromUtf8("m_linkersAddCompoundCountButton"));

        hboxLayout27->addWidget(m_linkersAddCompoundCountButton);

        spacer16_3_3_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout27->addItem(spacer16_3_3_3);


        vboxLayout21->addLayout(hboxLayout27);


        vboxLayout18->addWidget(buttonGroup3_2_2_2_3_3_3);

        groupBox18_2_2_2_3_3_3 = new Q3GroupBox(linkers_file_layout_page);
        groupBox18_2_2_2_3_3_3->setObjectName(QString::fromUtf8("groupBox18_2_2_2_3_3_3"));
        groupBox18_2_2_2_3_3_3->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_3_3_3->layout()->setSpacing(6);
        groupBox18_2_2_2_3_3_3->layout()->setMargin(11);
        vboxLayout22 = new QVBoxLayout();
        QBoxLayout *boxlayout23 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_3_3_3->layout());
        if (boxlayout23)
            boxlayout23->addLayout(vboxLayout22);
        vboxLayout22->setAlignment(Qt::AlignTop);
        vboxLayout22->setObjectName(QString::fromUtf8("vboxLayout22"));
        m_linkersExampleText = new QLabel(groupBox18_2_2_2_3_3_3);
        m_linkersExampleText->setObjectName(QString::fromUtf8("m_linkersExampleText"));
        m_linkersExampleText->setFrameShape(QFrame::Box);
        m_linkersExampleText->setWordWrap(false);

        vboxLayout22->addWidget(m_linkersExampleText);


        vboxLayout18->addWidget(groupBox18_2_2_2_3_3_3);

        spacer10_2_2_3_3_3 = new QSpacerItem(20, 186, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout18->addItem(spacer10_2_2_3_3_3);

        ExportWizardBase->addPage(linkers_file_layout_page, QString::fromUtf8("Linkers File Layout"));
        all_words_file_layout_page = new QWidget(ExportWizardBase);
        all_words_file_layout_page->setObjectName(QString::fromUtf8("all_words_file_layout_page"));
        vboxLayout23 = new QVBoxLayout(all_words_file_layout_page);
        vboxLayout23->setSpacing(6);
        vboxLayout23->setMargin(11);
        vboxLayout23->setObjectName(QString::fromUtf8("vboxLayout23"));
        vboxLayout23->setContentsMargins(0, 0, 0, 0);
        hboxLayout28 = new QHBoxLayout();
        hboxLayout28->setSpacing(6);
        hboxLayout28->setObjectName(QString::fromUtf8("hboxLayout28"));
        buttonGroup5_2 = new Q3ButtonGroup(all_words_file_layout_page);
        buttonGroup5_2->setObjectName(QString::fromUtf8("buttonGroup5_2"));
        buttonGroup5_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2->layout()->setSpacing(6);
        buttonGroup5_2->layout()->setMargin(11);
        vboxLayout24 = new QVBoxLayout();
        QBoxLayout *boxlayout24 = qobject_cast<QBoxLayout *>(buttonGroup5_2->layout());
        if (boxlayout24)
            boxlayout24->addLayout(vboxLayout24);
        vboxLayout24->setAlignment(Qt::AlignTop);
        vboxLayout24->setObjectName(QString::fromUtf8("vboxLayout24"));
        m_allWordsAnalyzedOnlyFlag = new QCheckBox(buttonGroup5_2);
        m_allWordsAnalyzedOnlyFlag->setObjectName(QString::fromUtf8("m_allWordsAnalyzedOnlyFlag"));

        vboxLayout24->addWidget(m_allWordsAnalyzedOnlyFlag);

        m_allWordsColumnTitlesFlag = new QCheckBox(buttonGroup5_2);
        m_allWordsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_allWordsColumnTitlesFlag"));
        m_allWordsColumnTitlesFlag->setChecked(true);

        vboxLayout24->addWidget(m_allWordsColumnTitlesFlag);

        m_allWordsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2);
        m_allWordsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_allWordsUniformFieldWidthsFlag"));
        m_allWordsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout24->addWidget(m_allWordsUniformFieldWidthsFlag);


        hboxLayout28->addWidget(buttonGroup5_2);

        spacer20_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout28->addItem(spacer20_2);


        vboxLayout23->addLayout(hboxLayout28);

        buttonGroup3_2 = new Q3ButtonGroup(all_words_file_layout_page);
        buttonGroup3_2->setObjectName(QString::fromUtf8("buttonGroup3_2"));
        buttonGroup3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2->layout()->setSpacing(6);
        buttonGroup3_2->layout()->setMargin(11);
        vboxLayout25 = new QVBoxLayout();
        QBoxLayout *boxlayout25 = qobject_cast<QBoxLayout *>(buttonGroup3_2->layout());
        if (boxlayout25)
            boxlayout25->addLayout(vboxLayout25);
        vboxLayout25->setAlignment(Qt::AlignTop);
        vboxLayout25->setObjectName(QString::fromUtf8("vboxLayout25"));
        m_allWordsLine = new QLineEdit(buttonGroup3_2);
        m_allWordsLine->setObjectName(QString::fromUtf8("m_allWordsLine"));

        vboxLayout25->addWidget(m_allWordsLine);

        hboxLayout29 = new QHBoxLayout();
        hboxLayout29->setSpacing(6);
        hboxLayout29->setObjectName(QString::fromUtf8("hboxLayout29"));
        m_allWordsAddIndexButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddIndexButton->setObjectName(QString::fromUtf8("m_allWordsAddIndexButton"));

        hboxLayout29->addWidget(m_allWordsAddIndexButton);

        m_allWordsAddWordButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddWordButton->setObjectName(QString::fromUtf8("m_allWordsAddWordButton"));

        hboxLayout29->addWidget(m_allWordsAddWordButton);

        m_allWordsAddMiniLexButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddMiniLexButton->setObjectName(QString::fromUtf8("m_allWordsAddMiniLexButton"));

        hboxLayout29->addWidget(m_allWordsAddMiniLexButton);

        m_allWordsAddDescLengthButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddDescLengthButton->setObjectName(QString::fromUtf8("m_allWordsAddDescLengthButton"));

        hboxLayout29->addWidget(m_allWordsAddDescLengthButton);

        m_allWordsAddCorpusCountButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_allWordsAddCorpusCountButton"));

        hboxLayout29->addWidget(m_allWordsAddCorpusCountButton);

        m_allWordsAddTypeButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddTypeButton->setObjectName(QString::fromUtf8("m_allWordsAddTypeButton"));

        hboxLayout29->addWidget(m_allWordsAddTypeButton);

        spacer18_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout29->addItem(spacer18_2);


        vboxLayout25->addLayout(hboxLayout29);

        hboxLayout30 = new QHBoxLayout();
        hboxLayout30->setSpacing(6);
        hboxLayout30->setObjectName(QString::fromUtf8("hboxLayout30"));
        m_allWordsAddSignatureButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddSignatureButton->setObjectName(QString::fromUtf8("m_allWordsAddSignatureButton"));

        hboxLayout30->addWidget(m_allWordsAddSignatureButton);

        m_allWordsAddSourceButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddSourceButton->setObjectName(QString::fromUtf8("m_allWordsAddSourceButton"));

        hboxLayout30->addWidget(m_allWordsAddSourceButton);

        m_allWordsAddPrefixButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddPrefixButton->setObjectName(QString::fromUtf8("m_allWordsAddPrefixButton"));

        hboxLayout30->addWidget(m_allWordsAddPrefixButton);

        m_allWordsAddStemButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddStemButton->setObjectName(QString::fromUtf8("m_allWordsAddStemButton"));

        hboxLayout30->addWidget(m_allWordsAddStemButton);

        m_allWordsAddSuffixButton = new QPushButton(buttonGroup3_2);
        m_allWordsAddSuffixButton->setObjectName(QString::fromUtf8("m_allWordsAddSuffixButton"));

        hboxLayout30->addWidget(m_allWordsAddSuffixButton);

        spacer19_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout30->addItem(spacer19_2);


        vboxLayout25->addLayout(hboxLayout30);


        vboxLayout23->addWidget(buttonGroup3_2);

        groupBox18_2 = new Q3GroupBox(all_words_file_layout_page);
        groupBox18_2->setObjectName(QString::fromUtf8("groupBox18_2"));
        groupBox18_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2->layout()->setSpacing(6);
        groupBox18_2->layout()->setMargin(11);
        vboxLayout26 = new QVBoxLayout();
        QBoxLayout *boxlayout26 = qobject_cast<QBoxLayout *>(groupBox18_2->layout());
        if (boxlayout26)
            boxlayout26->addLayout(vboxLayout26);
        vboxLayout26->setAlignment(Qt::AlignTop);
        vboxLayout26->setObjectName(QString::fromUtf8("vboxLayout26"));
        m_allWordsExampleText = new QLabel(groupBox18_2);
        m_allWordsExampleText->setObjectName(QString::fromUtf8("m_allWordsExampleText"));
        m_allWordsExampleText->setFrameShape(QFrame::Box);
        m_allWordsExampleText->setWordWrap(false);

        vboxLayout26->addWidget(m_allWordsExampleText);


        vboxLayout23->addWidget(groupBox18_2);

        spacer10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout23->addItem(spacer10);

        ExportWizardBase->addPage(all_words_file_layout_page, QString::fromUtf8("All Words File Layout"));
        all_stems_file_layout_page = new QWidget(ExportWizardBase);
        all_stems_file_layout_page->setObjectName(QString::fromUtf8("all_stems_file_layout_page"));
        vboxLayout27 = new QVBoxLayout(all_stems_file_layout_page);
        vboxLayout27->setSpacing(6);
        vboxLayout27->setMargin(11);
        vboxLayout27->setObjectName(QString::fromUtf8("vboxLayout27"));
        vboxLayout27->setContentsMargins(0, 0, 0, 0);
        hboxLayout31 = new QHBoxLayout();
        hboxLayout31->setSpacing(6);
        hboxLayout31->setObjectName(QString::fromUtf8("hboxLayout31"));
        buttonGroup5_2_2 = new Q3ButtonGroup(all_stems_file_layout_page);
        buttonGroup5_2_2->setObjectName(QString::fromUtf8("buttonGroup5_2_2"));
        buttonGroup5_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2->layout()->setSpacing(6);
        buttonGroup5_2_2->layout()->setMargin(11);
        vboxLayout28 = new QVBoxLayout();
        QBoxLayout *boxlayout27 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2->layout());
        if (boxlayout27)
            boxlayout27->addLayout(vboxLayout28);
        vboxLayout28->setAlignment(Qt::AlignTop);
        vboxLayout28->setObjectName(QString::fromUtf8("vboxLayout28"));
        m_allStemsColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2);
        m_allStemsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_allStemsColumnTitlesFlag"));
        m_allStemsColumnTitlesFlag->setChecked(true);

        vboxLayout28->addWidget(m_allStemsColumnTitlesFlag);

        m_allStemsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2);
        m_allStemsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_allStemsUniformFieldWidthsFlag"));
        m_allStemsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout28->addWidget(m_allStemsUniformFieldWidthsFlag);


        hboxLayout31->addWidget(buttonGroup5_2_2);

        spacer20_2_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout31->addItem(spacer20_2_2);


        vboxLayout27->addLayout(hboxLayout31);

        buttonGroup3_2_2 = new Q3ButtonGroup(all_stems_file_layout_page);
        buttonGroup3_2_2->setObjectName(QString::fromUtf8("buttonGroup3_2_2"));
        buttonGroup3_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2->layout()->setSpacing(6);
        buttonGroup3_2_2->layout()->setMargin(11);
        vboxLayout29 = new QVBoxLayout();
        QBoxLayout *boxlayout28 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2->layout());
        if (boxlayout28)
            boxlayout28->addLayout(vboxLayout29);
        vboxLayout29->setAlignment(Qt::AlignTop);
        vboxLayout29->setObjectName(QString::fromUtf8("vboxLayout29"));
        m_allStemsLine = new QLineEdit(buttonGroup3_2_2);
        m_allStemsLine->setObjectName(QString::fromUtf8("m_allStemsLine"));

        vboxLayout29->addWidget(m_allStemsLine);

        hboxLayout32 = new QHBoxLayout();
        hboxLayout32->setSpacing(6);
        hboxLayout32->setObjectName(QString::fromUtf8("hboxLayout32"));
        m_allStemsAddIndexButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddIndexButton->setObjectName(QString::fromUtf8("m_allStemsAddIndexButton"));

        hboxLayout32->addWidget(m_allStemsAddIndexButton);

        m_allStemsAddStemButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddStemButton->setObjectName(QString::fromUtf8("m_allStemsAddStemButton"));

        hboxLayout32->addWidget(m_allStemsAddStemButton);

        m_allStemsAddMiniLexButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddMiniLexButton->setObjectName(QString::fromUtf8("m_allStemsAddMiniLexButton"));

        hboxLayout32->addWidget(m_allStemsAddMiniLexButton);

        m_allStemsAddCorpusCountButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_allStemsAddCorpusCountButton"));

        hboxLayout32->addWidget(m_allStemsAddCorpusCountButton);

        spacer20_3 = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout32->addItem(spacer20_3);


        vboxLayout29->addLayout(hboxLayout32);

        hboxLayout33 = new QHBoxLayout();
        hboxLayout33->setSpacing(6);
        hboxLayout33->setObjectName(QString::fromUtf8("hboxLayout33"));
        m_allStemsAddDescLengthButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddDescLengthButton->setObjectName(QString::fromUtf8("m_allStemsAddDescLengthButton"));

        hboxLayout33->addWidget(m_allStemsAddDescLengthButton);

        m_allStemsAddSignatureButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddSignatureButton->setObjectName(QString::fromUtf8("m_allStemsAddSignatureButton"));

        hboxLayout33->addWidget(m_allStemsAddSignatureButton);

        m_allStemsAddOriginButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddOriginButton->setObjectName(QString::fromUtf8("m_allStemsAddOriginButton"));

        hboxLayout33->addWidget(m_allStemsAddOriginButton);

        m_allStemsAddTypeButton = new QPushButton(buttonGroup3_2_2);
        m_allStemsAddTypeButton->setObjectName(QString::fromUtf8("m_allStemsAddTypeButton"));

        hboxLayout33->addWidget(m_allStemsAddTypeButton);

        spacer21 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout33->addItem(spacer21);


        vboxLayout29->addLayout(hboxLayout33);


        vboxLayout27->addWidget(buttonGroup3_2_2);

        groupBox18_2_2 = new Q3GroupBox(all_stems_file_layout_page);
        groupBox18_2_2->setObjectName(QString::fromUtf8("groupBox18_2_2"));
        groupBox18_2_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2->layout()->setSpacing(6);
        groupBox18_2_2->layout()->setMargin(11);
        vboxLayout30 = new QVBoxLayout();
        QBoxLayout *boxlayout29 = qobject_cast<QBoxLayout *>(groupBox18_2_2->layout());
        if (boxlayout29)
            boxlayout29->addLayout(vboxLayout30);
        vboxLayout30->setAlignment(Qt::AlignTop);
        vboxLayout30->setObjectName(QString::fromUtf8("vboxLayout30"));
        m_allStemsExampleText = new QLabel(groupBox18_2_2);
        m_allStemsExampleText->setObjectName(QString::fromUtf8("m_allStemsExampleText"));
        m_allStemsExampleText->setFrameShape(QFrame::Box);
        m_allStemsExampleText->setWordWrap(false);

        vboxLayout30->addWidget(m_allStemsExampleText);


        vboxLayout27->addWidget(groupBox18_2_2);

        spacer10_2 = new QSpacerItem(20, 105, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout27->addItem(spacer10_2);

        ExportWizardBase->addPage(all_stems_file_layout_page, QString::fromUtf8("All Stems File Layout"));
        all_suffixes_file_layout_page = new QWidget(ExportWizardBase);
        all_suffixes_file_layout_page->setObjectName(QString::fromUtf8("all_suffixes_file_layout_page"));
        vboxLayout31 = new QVBoxLayout(all_suffixes_file_layout_page);
        vboxLayout31->setSpacing(6);
        vboxLayout31->setMargin(11);
        vboxLayout31->setObjectName(QString::fromUtf8("vboxLayout31"));
        vboxLayout31->setContentsMargins(0, 0, 0, 0);
        hboxLayout34 = new QHBoxLayout();
        hboxLayout34->setSpacing(6);
        hboxLayout34->setObjectName(QString::fromUtf8("hboxLayout34"));
        buttonGroup5_2_2_2_3 = new Q3ButtonGroup(all_suffixes_file_layout_page);
        buttonGroup5_2_2_2_3->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_3"));
        buttonGroup5_2_2_2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_3->layout()->setSpacing(6);
        buttonGroup5_2_2_2_3->layout()->setMargin(11);
        vboxLayout32 = new QVBoxLayout();
        QBoxLayout *boxlayout30 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_3->layout());
        if (boxlayout30)
            boxlayout30->addLayout(vboxLayout32);
        vboxLayout32->setAlignment(Qt::AlignTop);
        vboxLayout32->setObjectName(QString::fromUtf8("vboxLayout32"));
        m_allSuffixesColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_3);
        m_allSuffixesColumnTitlesFlag->setObjectName(QString::fromUtf8("m_allSuffixesColumnTitlesFlag"));
        m_allSuffixesColumnTitlesFlag->setChecked(true);

        vboxLayout32->addWidget(m_allSuffixesColumnTitlesFlag);

        m_allSuffixesUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_3);
        m_allSuffixesUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_allSuffixesUniformFieldWidthsFlag"));
        m_allSuffixesUniformFieldWidthsFlag->setChecked(true);

        vboxLayout32->addWidget(m_allSuffixesUniformFieldWidthsFlag);

        m_allSuffixesIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2_3);
        m_allSuffixesIncludeStemListFlag->setObjectName(QString::fromUtf8("m_allSuffixesIncludeStemListFlag"));
        m_allSuffixesIncludeStemListFlag->setChecked(true);

        vboxLayout32->addWidget(m_allSuffixesIncludeStemListFlag);


        hboxLayout34->addWidget(buttonGroup5_2_2_2_3);

        spacer20_2_2_2_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout34->addItem(spacer20_2_2_2_3);


        vboxLayout31->addLayout(hboxLayout34);

        buttonGroup3_2_2_2_3 = new Q3ButtonGroup(all_suffixes_file_layout_page);
        buttonGroup3_2_2_2_3->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_3"));
        buttonGroup3_2_2_2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_3->layout()->setSpacing(6);
        buttonGroup3_2_2_2_3->layout()->setMargin(11);
        vboxLayout33 = new QVBoxLayout();
        QBoxLayout *boxlayout31 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_3->layout());
        if (boxlayout31)
            boxlayout31->addLayout(vboxLayout33);
        vboxLayout33->setAlignment(Qt::AlignTop);
        vboxLayout33->setObjectName(QString::fromUtf8("vboxLayout33"));
        m_allSuffixesLine = new QLineEdit(buttonGroup3_2_2_2_3);
        m_allSuffixesLine->setObjectName(QString::fromUtf8("m_allSuffixesLine"));

        vboxLayout33->addWidget(m_allSuffixesLine);

        hboxLayout35 = new QHBoxLayout();
        hboxLayout35->setSpacing(6);
        hboxLayout35->setObjectName(QString::fromUtf8("hboxLayout35"));
        m_allSuffixesAddIndexButton = new QPushButton(buttonGroup3_2_2_2_3);
        m_allSuffixesAddIndexButton->setObjectName(QString::fromUtf8("m_allSuffixesAddIndexButton"));

        hboxLayout35->addWidget(m_allSuffixesAddIndexButton);

        m_allSuffixesAddSuffixButton = new QPushButton(buttonGroup3_2_2_2_3);
        m_allSuffixesAddSuffixButton->setObjectName(QString::fromUtf8("m_allSuffixesAddSuffixButton"));

        hboxLayout35->addWidget(m_allSuffixesAddSuffixButton);

        m_allSuffixesAddMiniLexButton = new QPushButton(buttonGroup3_2_2_2_3);
        m_allSuffixesAddMiniLexButton->setObjectName(QString::fromUtf8("m_allSuffixesAddMiniLexButton"));

        hboxLayout35->addWidget(m_allSuffixesAddMiniLexButton);

        m_allSuffixesAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_3);
        m_allSuffixesAddCorpusCountButton->setObjectName(QString::fromUtf8("m_allSuffixesAddCorpusCountButton"));

        hboxLayout35->addWidget(m_allSuffixesAddCorpusCountButton);

        m_allSuffixesAddStemCountButton = new QPushButton(buttonGroup3_2_2_2_3);
        m_allSuffixesAddStemCountButton->setObjectName(QString::fromUtf8("m_allSuffixesAddStemCountButton"));

        hboxLayout35->addWidget(m_allSuffixesAddStemCountButton);

        m_allSuffixesAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2_3);
        m_allSuffixesAddDescLengthButton->setObjectName(QString::fromUtf8("m_allSuffixesAddDescLengthButton"));

        hboxLayout35->addWidget(m_allSuffixesAddDescLengthButton);

        spacer16_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout35->addItem(spacer16_3);


        vboxLayout33->addLayout(hboxLayout35);


        vboxLayout31->addWidget(buttonGroup3_2_2_2_3);

        groupBox18_2_2_2_3 = new Q3GroupBox(all_suffixes_file_layout_page);
        groupBox18_2_2_2_3->setObjectName(QString::fromUtf8("groupBox18_2_2_2_3"));
        groupBox18_2_2_2_3->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_3->layout()->setSpacing(6);
        groupBox18_2_2_2_3->layout()->setMargin(11);
        vboxLayout34 = new QVBoxLayout();
        QBoxLayout *boxlayout32 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_3->layout());
        if (boxlayout32)
            boxlayout32->addLayout(vboxLayout34);
        vboxLayout34->setAlignment(Qt::AlignTop);
        vboxLayout34->setObjectName(QString::fromUtf8("vboxLayout34"));
        m_allSuffixesExampleText = new QLabel(groupBox18_2_2_2_3);
        m_allSuffixesExampleText->setObjectName(QString::fromUtf8("m_allSuffixesExampleText"));
        m_allSuffixesExampleText->setFrameShape(QFrame::Box);
        m_allSuffixesExampleText->setWordWrap(false);

        vboxLayout34->addWidget(m_allSuffixesExampleText);


        vboxLayout31->addWidget(groupBox18_2_2_2_3);

        spacer10_2_2_3 = new QSpacerItem(20, 115, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout31->addItem(spacer10_2_2_3);

        ExportWizardBase->addPage(all_suffixes_file_layout_page, QString::fromUtf8("All Suffixes File Layout"));
        all_suffix_signatures_file_layout_page = new QWidget(ExportWizardBase);
        all_suffix_signatures_file_layout_page->setObjectName(QString::fromUtf8("all_suffix_signatures_file_layout_page"));
        vboxLayout35 = new QVBoxLayout(all_suffix_signatures_file_layout_page);
        vboxLayout35->setSpacing(6);
        vboxLayout35->setMargin(11);
        vboxLayout35->setObjectName(QString::fromUtf8("vboxLayout35"));
        vboxLayout35->setContentsMargins(0, 0, 0, 0);
        hboxLayout36 = new QHBoxLayout();
        hboxLayout36->setSpacing(6);
        hboxLayout36->setObjectName(QString::fromUtf8("hboxLayout36"));
        buttonGroup5_2_2_2 = new Q3ButtonGroup(all_suffix_signatures_file_layout_page);
        buttonGroup5_2_2_2->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2"));
        buttonGroup5_2_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2->layout()->setSpacing(6);
        buttonGroup5_2_2_2->layout()->setMargin(11);
        vboxLayout36 = new QVBoxLayout();
        QBoxLayout *boxlayout33 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2->layout());
        if (boxlayout33)
            boxlayout33->addLayout(vboxLayout36);
        vboxLayout36->setAlignment(Qt::AlignTop);
        vboxLayout36->setObjectName(QString::fromUtf8("vboxLayout36"));
        m_allSuffixSigsColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2);
        m_allSuffixSigsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_allSuffixSigsColumnTitlesFlag"));
        m_allSuffixSigsColumnTitlesFlag->setChecked(true);

        vboxLayout36->addWidget(m_allSuffixSigsColumnTitlesFlag);

        m_allSuffixSigsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2);
        m_allSuffixSigsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_allSuffixSigsUniformFieldWidthsFlag"));
        m_allSuffixSigsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout36->addWidget(m_allSuffixSigsUniformFieldWidthsFlag);

        m_allSuffixSigsIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2);
        m_allSuffixSigsIncludeStemListFlag->setObjectName(QString::fromUtf8("m_allSuffixSigsIncludeStemListFlag"));
        m_allSuffixSigsIncludeStemListFlag->setChecked(true);

        vboxLayout36->addWidget(m_allSuffixSigsIncludeStemListFlag);


        hboxLayout36->addWidget(buttonGroup5_2_2_2);

        spacer20_2_2_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout36->addItem(spacer20_2_2_2);


        vboxLayout35->addLayout(hboxLayout36);

        buttonGroup3_2_2_2 = new Q3ButtonGroup(all_suffix_signatures_file_layout_page);
        buttonGroup3_2_2_2->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2"));
        buttonGroup3_2_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2->layout()->setSpacing(6);
        buttonGroup3_2_2_2->layout()->setMargin(11);
        vboxLayout37 = new QVBoxLayout();
        QBoxLayout *boxlayout34 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2->layout());
        if (boxlayout34)
            boxlayout34->addLayout(vboxLayout37);
        vboxLayout37->setAlignment(Qt::AlignTop);
        vboxLayout37->setObjectName(QString::fromUtf8("vboxLayout37"));
        m_allSuffixSigsLine = new QLineEdit(buttonGroup3_2_2_2);
        m_allSuffixSigsLine->setObjectName(QString::fromUtf8("m_allSuffixSigsLine"));

        vboxLayout37->addWidget(m_allSuffixSigsLine);

        hboxLayout37 = new QHBoxLayout();
        hboxLayout37->setSpacing(6);
        hboxLayout37->setObjectName(QString::fromUtf8("hboxLayout37"));
        m_allSuffixSigsAddIndexButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddIndexButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddIndexButton"));

        hboxLayout37->addWidget(m_allSuffixSigsAddIndexButton);

        m_allSuffixSigsAddSigButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddSigButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddSigButton"));

        hboxLayout37->addWidget(m_allSuffixSigsAddSigButton);

        m_allSuffixSigsAddMiniLexButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddMiniLexButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddMiniLexButton"));

        hboxLayout37->addWidget(m_allSuffixSigsAddMiniLexButton);

        m_allSuffixSigsAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddCorpusCountButton"));

        hboxLayout37->addWidget(m_allSuffixSigsAddCorpusCountButton);

        m_allSuffixSigsAddStemCountButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddStemCountButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddStemCountButton"));

        hboxLayout37->addWidget(m_allSuffixSigsAddStemCountButton);

        spacer16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout37->addItem(spacer16);


        vboxLayout37->addLayout(hboxLayout37);

        hboxLayout38 = new QHBoxLayout();
        hboxLayout38->setSpacing(6);
        hboxLayout38->setObjectName(QString::fromUtf8("hboxLayout38"));
        m_allSuffixSigsAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddDescLengthButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddDescLengthButton"));

        hboxLayout38->addWidget(m_allSuffixSigsAddDescLengthButton);

        m_allSuffixSigsAddRobustnessButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddRobustnessButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddRobustnessButton"));

        hboxLayout38->addWidget(m_allSuffixSigsAddRobustnessButton);

        m_allSuffixSigsAddExemplarButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddExemplarButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddExemplarButton"));

        hboxLayout38->addWidget(m_allSuffixSigsAddExemplarButton);

        m_allSuffixSigsAddRemarksButton = new QPushButton(buttonGroup3_2_2_2);
        m_allSuffixSigsAddRemarksButton->setObjectName(QString::fromUtf8("m_allSuffixSigsAddRemarksButton"));

        hboxLayout38->addWidget(m_allSuffixSigsAddRemarksButton);

        spacer17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout38->addItem(spacer17);


        vboxLayout37->addLayout(hboxLayout38);


        vboxLayout35->addWidget(buttonGroup3_2_2_2);

        groupBox18_2_2_2 = new Q3GroupBox(all_suffix_signatures_file_layout_page);
        groupBox18_2_2_2->setObjectName(QString::fromUtf8("groupBox18_2_2_2"));
        groupBox18_2_2_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2->layout()->setSpacing(6);
        groupBox18_2_2_2->layout()->setMargin(11);
        vboxLayout38 = new QVBoxLayout();
        QBoxLayout *boxlayout35 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2->layout());
        if (boxlayout35)
            boxlayout35->addLayout(vboxLayout38);
        vboxLayout38->setAlignment(Qt::AlignTop);
        vboxLayout38->setObjectName(QString::fromUtf8("vboxLayout38"));
        m_allSuffixSigsExampleText = new QLabel(groupBox18_2_2_2);
        m_allSuffixSigsExampleText->setObjectName(QString::fromUtf8("m_allSuffixSigsExampleText"));
        m_allSuffixSigsExampleText->setFrameShape(QFrame::Box);
        m_allSuffixSigsExampleText->setWordWrap(false);

        vboxLayout38->addWidget(m_allSuffixSigsExampleText);


        vboxLayout35->addWidget(groupBox18_2_2_2);

        spacer10_2_2 = new QSpacerItem(20, 130, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout35->addItem(spacer10_2_2);

        ExportWizardBase->addPage(all_suffix_signatures_file_layout_page, QString::fromUtf8("All Suffix Signatures File Layout"));
        all_prefixes_file_layout_page = new QWidget(ExportWizardBase);
        all_prefixes_file_layout_page->setObjectName(QString::fromUtf8("all_prefixes_file_layout_page"));
        vboxLayout39 = new QVBoxLayout(all_prefixes_file_layout_page);
        vboxLayout39->setSpacing(6);
        vboxLayout39->setMargin(11);
        vboxLayout39->setObjectName(QString::fromUtf8("vboxLayout39"));
        vboxLayout39->setContentsMargins(0, 0, 0, 0);
        hboxLayout39 = new QHBoxLayout();
        hboxLayout39->setSpacing(6);
        hboxLayout39->setObjectName(QString::fromUtf8("hboxLayout39"));
        buttonGroup5_2_2_2_3_2 = new Q3ButtonGroup(all_prefixes_file_layout_page);
        buttonGroup5_2_2_2_3_2->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_3_2"));
        buttonGroup5_2_2_2_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_3_2->layout()->setSpacing(6);
        buttonGroup5_2_2_2_3_2->layout()->setMargin(11);
        vboxLayout40 = new QVBoxLayout();
        QBoxLayout *boxlayout36 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_3_2->layout());
        if (boxlayout36)
            boxlayout36->addLayout(vboxLayout40);
        vboxLayout40->setAlignment(Qt::AlignTop);
        vboxLayout40->setObjectName(QString::fromUtf8("vboxLayout40"));
        m_allPrefixesColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_3_2);
        m_allPrefixesColumnTitlesFlag->setObjectName(QString::fromUtf8("m_allPrefixesColumnTitlesFlag"));
        m_allPrefixesColumnTitlesFlag->setChecked(true);

        vboxLayout40->addWidget(m_allPrefixesColumnTitlesFlag);

        m_allPrefixesUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_3_2);
        m_allPrefixesUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_allPrefixesUniformFieldWidthsFlag"));
        m_allPrefixesUniformFieldWidthsFlag->setChecked(true);

        vboxLayout40->addWidget(m_allPrefixesUniformFieldWidthsFlag);

        m_allPrefixesIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2_3_2);
        m_allPrefixesIncludeStemListFlag->setObjectName(QString::fromUtf8("m_allPrefixesIncludeStemListFlag"));
        m_allPrefixesIncludeStemListFlag->setChecked(true);

        vboxLayout40->addWidget(m_allPrefixesIncludeStemListFlag);


        hboxLayout39->addWidget(buttonGroup5_2_2_2_3_2);

        spacer20_2_2_2_3_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout39->addItem(spacer20_2_2_2_3_2);


        vboxLayout39->addLayout(hboxLayout39);

        buttonGroup3_2_2_2_3_2 = new Q3ButtonGroup(all_prefixes_file_layout_page);
        buttonGroup3_2_2_2_3_2->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_3_2"));
        buttonGroup3_2_2_2_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_3_2->layout()->setSpacing(6);
        buttonGroup3_2_2_2_3_2->layout()->setMargin(11);
        vboxLayout41 = new QVBoxLayout();
        QBoxLayout *boxlayout37 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_3_2->layout());
        if (boxlayout37)
            boxlayout37->addLayout(vboxLayout41);
        vboxLayout41->setAlignment(Qt::AlignTop);
        vboxLayout41->setObjectName(QString::fromUtf8("vboxLayout41"));
        m_allPrefixesLine = new QLineEdit(buttonGroup3_2_2_2_3_2);
        m_allPrefixesLine->setObjectName(QString::fromUtf8("m_allPrefixesLine"));

        vboxLayout41->addWidget(m_allPrefixesLine);

        hboxLayout40 = new QHBoxLayout();
        hboxLayout40->setSpacing(6);
        hboxLayout40->setObjectName(QString::fromUtf8("hboxLayout40"));
        m_allPrefixesAddIndexButton = new QPushButton(buttonGroup3_2_2_2_3_2);
        m_allPrefixesAddIndexButton->setObjectName(QString::fromUtf8("m_allPrefixesAddIndexButton"));

        hboxLayout40->addWidget(m_allPrefixesAddIndexButton);

        m_allPrefixesAddPrefixButton = new QPushButton(buttonGroup3_2_2_2_3_2);
        m_allPrefixesAddPrefixButton->setObjectName(QString::fromUtf8("m_allPrefixesAddPrefixButton"));

        hboxLayout40->addWidget(m_allPrefixesAddPrefixButton);

        m_allPrefixesAddMiniLexButton = new QPushButton(buttonGroup3_2_2_2_3_2);
        m_allPrefixesAddMiniLexButton->setObjectName(QString::fromUtf8("m_allPrefixesAddMiniLexButton"));

        hboxLayout40->addWidget(m_allPrefixesAddMiniLexButton);

        m_allPrefixesAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_3_2);
        m_allPrefixesAddCorpusCountButton->setObjectName(QString::fromUtf8("m_allPrefixesAddCorpusCountButton"));

        hboxLayout40->addWidget(m_allPrefixesAddCorpusCountButton);

        m_allPrefixesAddStemCountButton = new QPushButton(buttonGroup3_2_2_2_3_2);
        m_allPrefixesAddStemCountButton->setObjectName(QString::fromUtf8("m_allPrefixesAddStemCountButton"));

        hboxLayout40->addWidget(m_allPrefixesAddStemCountButton);

        m_allPrefixesAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2_3_2);
        m_allPrefixesAddDescLengthButton->setObjectName(QString::fromUtf8("m_allPrefixesAddDescLengthButton"));

        hboxLayout40->addWidget(m_allPrefixesAddDescLengthButton);

        spacer16_3_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout40->addItem(spacer16_3_2);


        vboxLayout41->addLayout(hboxLayout40);


        vboxLayout39->addWidget(buttonGroup3_2_2_2_3_2);

        groupBox18_2_2_2_3_2 = new Q3GroupBox(all_prefixes_file_layout_page);
        groupBox18_2_2_2_3_2->setObjectName(QString::fromUtf8("groupBox18_2_2_2_3_2"));
        groupBox18_2_2_2_3_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_3_2->layout()->setSpacing(6);
        groupBox18_2_2_2_3_2->layout()->setMargin(11);
        vboxLayout42 = new QVBoxLayout();
        QBoxLayout *boxlayout38 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_3_2->layout());
        if (boxlayout38)
            boxlayout38->addLayout(vboxLayout42);
        vboxLayout42->setAlignment(Qt::AlignTop);
        vboxLayout42->setObjectName(QString::fromUtf8("vboxLayout42"));
        m_allPrefixesExampleText = new QLabel(groupBox18_2_2_2_3_2);
        m_allPrefixesExampleText->setObjectName(QString::fromUtf8("m_allPrefixesExampleText"));
        m_allPrefixesExampleText->setFrameShape(QFrame::Box);
        m_allPrefixesExampleText->setWordWrap(false);

        vboxLayout42->addWidget(m_allPrefixesExampleText);


        vboxLayout39->addWidget(groupBox18_2_2_2_3_2);

        spacer10_2_2_3_2 = new QSpacerItem(20, 148, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout39->addItem(spacer10_2_2_3_2);

        ExportWizardBase->addPage(all_prefixes_file_layout_page, QString::fromUtf8("All Prefixes File Layout"));
        all_prefix_signatures_file_layout_page = new QWidget(ExportWizardBase);
        all_prefix_signatures_file_layout_page->setObjectName(QString::fromUtf8("all_prefix_signatures_file_layout_page"));
        vboxLayout43 = new QVBoxLayout(all_prefix_signatures_file_layout_page);
        vboxLayout43->setSpacing(6);
        vboxLayout43->setMargin(11);
        vboxLayout43->setObjectName(QString::fromUtf8("vboxLayout43"));
        vboxLayout43->setContentsMargins(0, 0, 0, 0);
        hboxLayout41 = new QHBoxLayout();
        hboxLayout41->setSpacing(6);
        hboxLayout41->setObjectName(QString::fromUtf8("hboxLayout41"));
        buttonGroup5_2_2_2_2 = new Q3ButtonGroup(all_prefix_signatures_file_layout_page);
        buttonGroup5_2_2_2_2->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_2"));
        buttonGroup5_2_2_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_2->layout()->setSpacing(6);
        buttonGroup5_2_2_2_2->layout()->setMargin(11);
        vboxLayout44 = new QVBoxLayout();
        QBoxLayout *boxlayout39 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_2->layout());
        if (boxlayout39)
            boxlayout39->addLayout(vboxLayout44);
        vboxLayout44->setAlignment(Qt::AlignTop);
        vboxLayout44->setObjectName(QString::fromUtf8("vboxLayout44"));
        m_allPrefixSigsColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_2);
        m_allPrefixSigsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_allPrefixSigsColumnTitlesFlag"));
        m_allPrefixSigsColumnTitlesFlag->setChecked(true);

        vboxLayout44->addWidget(m_allPrefixSigsColumnTitlesFlag);

        m_allPrefixSigsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_2);
        m_allPrefixSigsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_allPrefixSigsUniformFieldWidthsFlag"));
        m_allPrefixSigsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout44->addWidget(m_allPrefixSigsUniformFieldWidthsFlag);

        m_allPrefixSigsIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2_2);
        m_allPrefixSigsIncludeStemListFlag->setObjectName(QString::fromUtf8("m_allPrefixSigsIncludeStemListFlag"));
        m_allPrefixSigsIncludeStemListFlag->setChecked(true);

        vboxLayout44->addWidget(m_allPrefixSigsIncludeStemListFlag);


        hboxLayout41->addWidget(buttonGroup5_2_2_2_2);

        spacer20_2_2_2_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout41->addItem(spacer20_2_2_2_2);


        vboxLayout43->addLayout(hboxLayout41);

        buttonGroup3_2_2_2_2 = new Q3ButtonGroup(all_prefix_signatures_file_layout_page);
        buttonGroup3_2_2_2_2->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_2"));
        buttonGroup3_2_2_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_2->layout()->setSpacing(6);
        buttonGroup3_2_2_2_2->layout()->setMargin(11);
        vboxLayout45 = new QVBoxLayout();
        QBoxLayout *boxlayout40 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_2->layout());
        if (boxlayout40)
            boxlayout40->addLayout(vboxLayout45);
        vboxLayout45->setAlignment(Qt::AlignTop);
        vboxLayout45->setObjectName(QString::fromUtf8("vboxLayout45"));
        m_allPrefixSigsLine = new QLineEdit(buttonGroup3_2_2_2_2);
        m_allPrefixSigsLine->setObjectName(QString::fromUtf8("m_allPrefixSigsLine"));

        vboxLayout45->addWidget(m_allPrefixSigsLine);

        hboxLayout42 = new QHBoxLayout();
        hboxLayout42->setSpacing(6);
        hboxLayout42->setObjectName(QString::fromUtf8("hboxLayout42"));
        m_allPrefixSigsAddIndexButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddIndexButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddIndexButton"));

        hboxLayout42->addWidget(m_allPrefixSigsAddIndexButton);

        m_allPrefixSigsAddSigButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddSigButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddSigButton"));

        hboxLayout42->addWidget(m_allPrefixSigsAddSigButton);

        m_allPrefixSigsAddMiniLexButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddMiniLexButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddMiniLexButton"));

        hboxLayout42->addWidget(m_allPrefixSigsAddMiniLexButton);

        m_allPrefixSigsAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddCorpusCountButton"));

        hboxLayout42->addWidget(m_allPrefixSigsAddCorpusCountButton);

        m_allPrefixSigsAddStemCountButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddStemCountButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddStemCountButton"));

        hboxLayout42->addWidget(m_allPrefixSigsAddStemCountButton);

        spacer16_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout42->addItem(spacer16_2);


        vboxLayout45->addLayout(hboxLayout42);

        hboxLayout43 = new QHBoxLayout();
        hboxLayout43->setSpacing(6);
        hboxLayout43->setObjectName(QString::fromUtf8("hboxLayout43"));
        m_allPrefixSigsAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddDescLengthButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddDescLengthButton"));

        hboxLayout43->addWidget(m_allPrefixSigsAddDescLengthButton);

        m_allPrefixSigsAddRobustnessButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddRobustnessButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddRobustnessButton"));

        hboxLayout43->addWidget(m_allPrefixSigsAddRobustnessButton);

        m_allPrefixSigsAddExemplarButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddExemplarButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddExemplarButton"));

        hboxLayout43->addWidget(m_allPrefixSigsAddExemplarButton);

        m_allPrefixSigsAddRemarksButton = new QPushButton(buttonGroup3_2_2_2_2);
        m_allPrefixSigsAddRemarksButton->setObjectName(QString::fromUtf8("m_allPrefixSigsAddRemarksButton"));

        hboxLayout43->addWidget(m_allPrefixSigsAddRemarksButton);

        spacer17_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout43->addItem(spacer17_2);


        vboxLayout45->addLayout(hboxLayout43);


        vboxLayout43->addWidget(buttonGroup3_2_2_2_2);

        groupBox18_2_2_2_2 = new Q3GroupBox(all_prefix_signatures_file_layout_page);
        groupBox18_2_2_2_2->setObjectName(QString::fromUtf8("groupBox18_2_2_2_2"));
        groupBox18_2_2_2_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_2->layout()->setSpacing(6);
        groupBox18_2_2_2_2->layout()->setMargin(11);
        vboxLayout46 = new QVBoxLayout();
        QBoxLayout *boxlayout41 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_2->layout());
        if (boxlayout41)
            boxlayout41->addLayout(vboxLayout46);
        vboxLayout46->setAlignment(Qt::AlignTop);
        vboxLayout46->setObjectName(QString::fromUtf8("vboxLayout46"));
        m_allPrefixSigsExampleText = new QLabel(groupBox18_2_2_2_2);
        m_allPrefixSigsExampleText->setObjectName(QString::fromUtf8("m_allPrefixSigsExampleText"));
        m_allPrefixSigsExampleText->setFrameShape(QFrame::Box);
        m_allPrefixSigsExampleText->setWordWrap(false);

        vboxLayout46->addWidget(m_allPrefixSigsExampleText);


        vboxLayout43->addWidget(groupBox18_2_2_2_2);

        spacer10_2_2_2 = new QSpacerItem(20, 136, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout43->addItem(spacer10_2_2_2);

        ExportWizardBase->addPage(all_prefix_signatures_file_layout_page, QString::fromUtf8("All Prefix Signatures File Layout"));
        minilexicon_words_file_layout_page = new QWidget(ExportWizardBase);
        minilexicon_words_file_layout_page->setObjectName(QString::fromUtf8("minilexicon_words_file_layout_page"));
        vboxLayout47 = new QVBoxLayout(minilexicon_words_file_layout_page);
        vboxLayout47->setSpacing(6);
        vboxLayout47->setMargin(11);
        vboxLayout47->setObjectName(QString::fromUtf8("vboxLayout47"));
        vboxLayout47->setContentsMargins(0, 0, 0, 0);
        hboxLayout44 = new QHBoxLayout();
        hboxLayout44->setSpacing(6);
        hboxLayout44->setObjectName(QString::fromUtf8("hboxLayout44"));
        buttonGroup5_2_3 = new Q3ButtonGroup(minilexicon_words_file_layout_page);
        buttonGroup5_2_3->setObjectName(QString::fromUtf8("buttonGroup5_2_3"));
        buttonGroup5_2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_3->layout()->setSpacing(6);
        buttonGroup5_2_3->layout()->setMargin(11);
        vboxLayout48 = new QVBoxLayout();
        QBoxLayout *boxlayout42 = qobject_cast<QBoxLayout *>(buttonGroup5_2_3->layout());
        if (boxlayout42)
            boxlayout42->addLayout(vboxLayout48);
        vboxLayout48->setAlignment(Qt::AlignTop);
        vboxLayout48->setObjectName(QString::fromUtf8("vboxLayout48"));
        m_miniWordsAnalyzedOnlyFlag = new QCheckBox(buttonGroup5_2_3);
        m_miniWordsAnalyzedOnlyFlag->setObjectName(QString::fromUtf8("m_miniWordsAnalyzedOnlyFlag"));

        vboxLayout48->addWidget(m_miniWordsAnalyzedOnlyFlag);

        m_miniWordsColumnTitlesFlag = new QCheckBox(buttonGroup5_2_3);
        m_miniWordsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_miniWordsColumnTitlesFlag"));
        m_miniWordsColumnTitlesFlag->setChecked(true);

        vboxLayout48->addWidget(m_miniWordsColumnTitlesFlag);

        m_miniWordsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_3);
        m_miniWordsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_miniWordsUniformFieldWidthsFlag"));
        m_miniWordsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout48->addWidget(m_miniWordsUniformFieldWidthsFlag);


        hboxLayout44->addWidget(buttonGroup5_2_3);

        buttonGroup2_2 = new Q3ButtonGroup(minilexicon_words_file_layout_page);
        buttonGroup2_2->setObjectName(QString::fromUtf8("buttonGroup2_2"));
        buttonGroup2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2->layout()->setSpacing(6);
        buttonGroup2_2->layout()->setMargin(11);
        vboxLayout49 = new QVBoxLayout();
        QBoxLayout *boxlayout43 = qobject_cast<QBoxLayout *>(buttonGroup2_2->layout());
        if (boxlayout43)
            boxlayout43->addLayout(vboxLayout49);
        vboxLayout49->setAlignment(Qt::AlignTop);
        vboxLayout49->setObjectName(QString::fromUtf8("vboxLayout49"));
        m_miniWordsAlphabeticalSortFlag = new QRadioButton(buttonGroup2_2);
        m_miniWordsAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_miniWordsAlphabeticalSortFlag"));
        m_miniWordsAlphabeticalSortFlag->setChecked(true);

        vboxLayout49->addWidget(m_miniWordsAlphabeticalSortFlag);

        m_miniWordsCorpusCountSortFlag = new QRadioButton(buttonGroup2_2);
        m_miniWordsCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_miniWordsCorpusCountSortFlag"));

        vboxLayout49->addWidget(m_miniWordsCorpusCountSortFlag);

        m_miniWordsMorphemeCountSortFlag = new QRadioButton(buttonGroup2_2);
        m_miniWordsMorphemeCountSortFlag->setObjectName(QString::fromUtf8("m_miniWordsMorphemeCountSortFlag"));

        vboxLayout49->addWidget(m_miniWordsMorphemeCountSortFlag);


        hboxLayout44->addWidget(buttonGroup2_2);

        spacer20_2_3 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout44->addItem(spacer20_2_3);


        vboxLayout47->addLayout(hboxLayout44);

        buttonGroup3_2_3 = new Q3ButtonGroup(minilexicon_words_file_layout_page);
        buttonGroup3_2_3->setObjectName(QString::fromUtf8("buttonGroup3_2_3"));
        buttonGroup3_2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_3->layout()->setSpacing(6);
        buttonGroup3_2_3->layout()->setMargin(11);
        vboxLayout50 = new QVBoxLayout();
        QBoxLayout *boxlayout44 = qobject_cast<QBoxLayout *>(buttonGroup3_2_3->layout());
        if (boxlayout44)
            boxlayout44->addLayout(vboxLayout50);
        vboxLayout50->setAlignment(Qt::AlignTop);
        vboxLayout50->setObjectName(QString::fromUtf8("vboxLayout50"));
        m_miniWordsLine = new QLineEdit(buttonGroup3_2_3);
        m_miniWordsLine->setObjectName(QString::fromUtf8("m_miniWordsLine"));

        vboxLayout50->addWidget(m_miniWordsLine);

        hboxLayout45 = new QHBoxLayout();
        hboxLayout45->setSpacing(6);
        hboxLayout45->setObjectName(QString::fromUtf8("hboxLayout45"));
        m_miniWordsAddIndexButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddIndexButton->setObjectName(QString::fromUtf8("m_miniWordsAddIndexButton"));

        hboxLayout45->addWidget(m_miniWordsAddIndexButton);

        m_miniWordsAddWordButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddWordButton->setObjectName(QString::fromUtf8("m_miniWordsAddWordButton"));

        hboxLayout45->addWidget(m_miniWordsAddWordButton);

        m_miniWordsAddDescLengthButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddDescLengthButton->setObjectName(QString::fromUtf8("m_miniWordsAddDescLengthButton"));

        hboxLayout45->addWidget(m_miniWordsAddDescLengthButton);

        m_miniWordsAddCorpusCountButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_miniWordsAddCorpusCountButton"));

        hboxLayout45->addWidget(m_miniWordsAddCorpusCountButton);

        m_miniWordsAddTypeButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddTypeButton->setObjectName(QString::fromUtf8("m_miniWordsAddTypeButton"));

        hboxLayout45->addWidget(m_miniWordsAddTypeButton);

        spacer18_2_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout45->addItem(spacer18_2_2);


        vboxLayout50->addLayout(hboxLayout45);

        hboxLayout46 = new QHBoxLayout();
        hboxLayout46->setSpacing(6);
        hboxLayout46->setObjectName(QString::fromUtf8("hboxLayout46"));
        m_miniWordsAddSignatureButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddSignatureButton->setObjectName(QString::fromUtf8("m_miniWordsAddSignatureButton"));

        hboxLayout46->addWidget(m_miniWordsAddSignatureButton);

        m_miniWordsAddSourceButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddSourceButton->setObjectName(QString::fromUtf8("m_miniWordsAddSourceButton"));

        hboxLayout46->addWidget(m_miniWordsAddSourceButton);

        m_miniWordsAddPrefixButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddPrefixButton->setObjectName(QString::fromUtf8("m_miniWordsAddPrefixButton"));

        hboxLayout46->addWidget(m_miniWordsAddPrefixButton);

        m_miniWordsAddStemButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddStemButton->setObjectName(QString::fromUtf8("m_miniWordsAddStemButton"));

        hboxLayout46->addWidget(m_miniWordsAddStemButton);

        m_miniWordsAddSuffixButton = new QPushButton(buttonGroup3_2_3);
        m_miniWordsAddSuffixButton->setObjectName(QString::fromUtf8("m_miniWordsAddSuffixButton"));

        hboxLayout46->addWidget(m_miniWordsAddSuffixButton);

        spacer19_2_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout46->addItem(spacer19_2_2);


        vboxLayout50->addLayout(hboxLayout46);


        vboxLayout47->addWidget(buttonGroup3_2_3);

        groupBox18_2_3 = new Q3GroupBox(minilexicon_words_file_layout_page);
        groupBox18_2_3->setObjectName(QString::fromUtf8("groupBox18_2_3"));
        groupBox18_2_3->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_3->layout()->setSpacing(6);
        groupBox18_2_3->layout()->setMargin(11);
        vboxLayout51 = new QVBoxLayout();
        QBoxLayout *boxlayout45 = qobject_cast<QBoxLayout *>(groupBox18_2_3->layout());
        if (boxlayout45)
            boxlayout45->addLayout(vboxLayout51);
        vboxLayout51->setAlignment(Qt::AlignTop);
        vboxLayout51->setObjectName(QString::fromUtf8("vboxLayout51"));
        m_miniWordsExampleText = new QLabel(groupBox18_2_3);
        m_miniWordsExampleText->setObjectName(QString::fromUtf8("m_miniWordsExampleText"));
        m_miniWordsExampleText->setFrameShape(QFrame::Box);
        m_miniWordsExampleText->setWordWrap(false);

        vboxLayout51->addWidget(m_miniWordsExampleText);


        vboxLayout47->addWidget(groupBox18_2_3);

        spacer10_3 = new QSpacerItem(20, 115, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout47->addItem(spacer10_3);

        ExportWizardBase->addPage(minilexicon_words_file_layout_page, QString::fromUtf8("Mini-Lexicon Words File Layout"));
        minilexicon_signatures_file_layout_page = new QWidget(ExportWizardBase);
        minilexicon_signatures_file_layout_page->setObjectName(QString::fromUtf8("minilexicon_signatures_file_layout_page"));
        vboxLayout52 = new QVBoxLayout(minilexicon_signatures_file_layout_page);
        vboxLayout52->setSpacing(6);
        vboxLayout52->setMargin(11);
        vboxLayout52->setObjectName(QString::fromUtf8("vboxLayout52"));
        vboxLayout52->setContentsMargins(0, 0, 0, 0);
        hboxLayout47 = new QHBoxLayout();
        hboxLayout47->setSpacing(6);
        hboxLayout47->setObjectName(QString::fromUtf8("hboxLayout47"));
        buttonGroup5_2_2_2_4 = new Q3ButtonGroup(minilexicon_signatures_file_layout_page);
        buttonGroup5_2_2_2_4->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_4"));
        buttonGroup5_2_2_2_4->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_4->layout()->setSpacing(6);
        buttonGroup5_2_2_2_4->layout()->setMargin(11);
        vboxLayout53 = new QVBoxLayout();
        QBoxLayout *boxlayout46 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_4->layout());
        if (boxlayout46)
            boxlayout46->addLayout(vboxLayout53);
        vboxLayout53->setAlignment(Qt::AlignTop);
        vboxLayout53->setObjectName(QString::fromUtf8("vboxLayout53"));
        m_miniSignaturesColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_4);
        m_miniSignaturesColumnTitlesFlag->setObjectName(QString::fromUtf8("m_miniSignaturesColumnTitlesFlag"));
        m_miniSignaturesColumnTitlesFlag->setChecked(true);

        vboxLayout53->addWidget(m_miniSignaturesColumnTitlesFlag);

        m_miniSignaturesUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_4);
        m_miniSignaturesUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_miniSignaturesUniformFieldWidthsFlag"));
        m_miniSignaturesUniformFieldWidthsFlag->setChecked(true);

        vboxLayout53->addWidget(m_miniSignaturesUniformFieldWidthsFlag);

        m_miniSignaturesIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2_4);
        m_miniSignaturesIncludeStemListFlag->setObjectName(QString::fromUtf8("m_miniSignaturesIncludeStemListFlag"));
        m_miniSignaturesIncludeStemListFlag->setChecked(true);

        vboxLayout53->addWidget(m_miniSignaturesIncludeStemListFlag);


        hboxLayout47->addWidget(buttonGroup5_2_2_2_4);

        buttonGroup2_2_3 = new Q3ButtonGroup(minilexicon_signatures_file_layout_page);
        buttonGroup2_2_3->setObjectName(QString::fromUtf8("buttonGroup2_2_3"));
        buttonGroup2_2_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2_3->layout()->setSpacing(6);
        buttonGroup2_2_3->layout()->setMargin(11);
        vboxLayout54 = new QVBoxLayout();
        QBoxLayout *boxlayout47 = qobject_cast<QBoxLayout *>(buttonGroup2_2_3->layout());
        if (boxlayout47)
            boxlayout47->addLayout(vboxLayout54);
        vboxLayout54->setAlignment(Qt::AlignTop);
        vboxLayout54->setObjectName(QString::fromUtf8("vboxLayout54"));
        m_miniSignaturesAlphabeticalSortFlag = new QRadioButton(buttonGroup2_2_3);
        m_miniSignaturesAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_miniSignaturesAlphabeticalSortFlag"));
        m_miniSignaturesAlphabeticalSortFlag->setChecked(true);

        vboxLayout54->addWidget(m_miniSignaturesAlphabeticalSortFlag);

        m_miniSignaturesCorpusCountSortFlag = new QRadioButton(buttonGroup2_2_3);
        m_miniSignaturesCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_miniSignaturesCorpusCountSortFlag"));

        vboxLayout54->addWidget(m_miniSignaturesCorpusCountSortFlag);

        m_miniSignaturesStemCountSortFlag = new QRadioButton(buttonGroup2_2_3);
        m_miniSignaturesStemCountSortFlag->setObjectName(QString::fromUtf8("m_miniSignaturesStemCountSortFlag"));

        vboxLayout54->addWidget(m_miniSignaturesStemCountSortFlag);


        hboxLayout47->addWidget(buttonGroup2_2_3);

        spacer20_2_2_2_4 = new QSpacerItem(250, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout47->addItem(spacer20_2_2_2_4);


        vboxLayout52->addLayout(hboxLayout47);

        buttonGroup3_2_2_2_4 = new Q3ButtonGroup(minilexicon_signatures_file_layout_page);
        buttonGroup3_2_2_2_4->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_4"));
        buttonGroup3_2_2_2_4->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_4->layout()->setSpacing(6);
        buttonGroup3_2_2_2_4->layout()->setMargin(11);
        vboxLayout55 = new QVBoxLayout();
        QBoxLayout *boxlayout48 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_4->layout());
        if (boxlayout48)
            boxlayout48->addLayout(vboxLayout55);
        vboxLayout55->setAlignment(Qt::AlignTop);
        vboxLayout55->setObjectName(QString::fromUtf8("vboxLayout55"));
        m_miniSignaturesLine = new QLineEdit(buttonGroup3_2_2_2_4);
        m_miniSignaturesLine->setObjectName(QString::fromUtf8("m_miniSignaturesLine"));

        vboxLayout55->addWidget(m_miniSignaturesLine);

        hboxLayout48 = new QHBoxLayout();
        hboxLayout48->setSpacing(6);
        hboxLayout48->setObjectName(QString::fromUtf8("hboxLayout48"));
        m_miniSignaturesAddIndexButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddIndexButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddIndexButton"));

        hboxLayout48->addWidget(m_miniSignaturesAddIndexButton);

        m_miniSignaturesAddSigButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddSigButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddSigButton"));

        hboxLayout48->addWidget(m_miniSignaturesAddSigButton);

        m_miniSignaturesAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddCorpusCountButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddCorpusCountButton"));

        hboxLayout48->addWidget(m_miniSignaturesAddCorpusCountButton);

        m_miniSignaturesAddStemCountButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddStemCountButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddStemCountButton"));

        hboxLayout48->addWidget(m_miniSignaturesAddStemCountButton);

        spacer16_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout48->addItem(spacer16_4);


        vboxLayout55->addLayout(hboxLayout48);

        hboxLayout49 = new QHBoxLayout();
        hboxLayout49->setSpacing(6);
        hboxLayout49->setObjectName(QString::fromUtf8("hboxLayout49"));
        m_miniSignaturesAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddDescLengthButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddDescLengthButton"));

        hboxLayout49->addWidget(m_miniSignaturesAddDescLengthButton);

        m_miniSignaturesAddRobustnessButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddRobustnessButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddRobustnessButton"));

        hboxLayout49->addWidget(m_miniSignaturesAddRobustnessButton);

        m_miniSignaturesAddExemplarButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddExemplarButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddExemplarButton"));

        hboxLayout49->addWidget(m_miniSignaturesAddExemplarButton);

        m_miniSignaturesAddRemarksButton = new QPushButton(buttonGroup3_2_2_2_4);
        m_miniSignaturesAddRemarksButton->setObjectName(QString::fromUtf8("m_miniSignaturesAddRemarksButton"));

        hboxLayout49->addWidget(m_miniSignaturesAddRemarksButton);

        spacer17_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout49->addItem(spacer17_3);


        vboxLayout55->addLayout(hboxLayout49);


        vboxLayout52->addWidget(buttonGroup3_2_2_2_4);

        groupBox18_2_2_2_4 = new Q3GroupBox(minilexicon_signatures_file_layout_page);
        groupBox18_2_2_2_4->setObjectName(QString::fromUtf8("groupBox18_2_2_2_4"));
        groupBox18_2_2_2_4->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_4->layout()->setSpacing(6);
        groupBox18_2_2_2_4->layout()->setMargin(11);
        vboxLayout56 = new QVBoxLayout();
        QBoxLayout *boxlayout49 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_4->layout());
        if (boxlayout49)
            boxlayout49->addLayout(vboxLayout56);
        vboxLayout56->setAlignment(Qt::AlignTop);
        vboxLayout56->setObjectName(QString::fromUtf8("vboxLayout56"));
        m_miniSignaturesExampleText = new QLabel(groupBox18_2_2_2_4);
        m_miniSignaturesExampleText->setObjectName(QString::fromUtf8("m_miniSignaturesExampleText"));
        m_miniSignaturesExampleText->setFrameShape(QFrame::Box);
        m_miniSignaturesExampleText->setWordWrap(false);

        vboxLayout56->addWidget(m_miniSignaturesExampleText);


        vboxLayout52->addWidget(groupBox18_2_2_2_4);

        spacer10_2_2_4 = new QSpacerItem(20, 153, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout52->addItem(spacer10_2_2_4);

        ExportWizardBase->addPage(minilexicon_signatures_file_layout_page, QString::fromUtf8("Mini-Lexicon Signatures File Layout"));
        minilexicon_stems_file_layout_page = new QWidget(ExportWizardBase);
        minilexicon_stems_file_layout_page->setObjectName(QString::fromUtf8("minilexicon_stems_file_layout_page"));
        vboxLayout57 = new QVBoxLayout(minilexicon_stems_file_layout_page);
        vboxLayout57->setSpacing(6);
        vboxLayout57->setMargin(11);
        vboxLayout57->setObjectName(QString::fromUtf8("vboxLayout57"));
        vboxLayout57->setContentsMargins(0, 0, 0, 0);
        hboxLayout50 = new QHBoxLayout();
        hboxLayout50->setSpacing(6);
        hboxLayout50->setObjectName(QString::fromUtf8("hboxLayout50"));
        buttonGroup5_2_3_2 = new Q3ButtonGroup(minilexicon_stems_file_layout_page);
        buttonGroup5_2_3_2->setObjectName(QString::fromUtf8("buttonGroup5_2_3_2"));
        buttonGroup5_2_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_3_2->layout()->setSpacing(6);
        buttonGroup5_2_3_2->layout()->setMargin(11);
        vboxLayout58 = new QVBoxLayout();
        QBoxLayout *boxlayout50 = qobject_cast<QBoxLayout *>(buttonGroup5_2_3_2->layout());
        if (boxlayout50)
            boxlayout50->addLayout(vboxLayout58);
        vboxLayout58->setAlignment(Qt::AlignTop);
        vboxLayout58->setObjectName(QString::fromUtf8("vboxLayout58"));
        m_miniStemsColumnTitlesFlag = new QCheckBox(buttonGroup5_2_3_2);
        m_miniStemsColumnTitlesFlag->setObjectName(QString::fromUtf8("m_miniStemsColumnTitlesFlag"));
        m_miniStemsColumnTitlesFlag->setChecked(true);

        vboxLayout58->addWidget(m_miniStemsColumnTitlesFlag);

        m_miniStemsUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_3_2);
        m_miniStemsUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_miniStemsUniformFieldWidthsFlag"));
        m_miniStemsUniformFieldWidthsFlag->setChecked(true);

        vboxLayout58->addWidget(m_miniStemsUniformFieldWidthsFlag);


        hboxLayout50->addWidget(buttonGroup5_2_3_2);

        buttonGroup2_2_2 = new Q3ButtonGroup(minilexicon_stems_file_layout_page);
        buttonGroup2_2_2->setObjectName(QString::fromUtf8("buttonGroup2_2_2"));
        buttonGroup2_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2_2->layout()->setSpacing(6);
        buttonGroup2_2_2->layout()->setMargin(11);
        vboxLayout59 = new QVBoxLayout();
        QBoxLayout *boxlayout51 = qobject_cast<QBoxLayout *>(buttonGroup2_2_2->layout());
        if (boxlayout51)
            boxlayout51->addLayout(vboxLayout59);
        vboxLayout59->setAlignment(Qt::AlignTop);
        vboxLayout59->setObjectName(QString::fromUtf8("vboxLayout59"));
        m_miniStemsAlphabeticalSortFlag = new QRadioButton(buttonGroup2_2_2);
        m_miniStemsAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_miniStemsAlphabeticalSortFlag"));
        m_miniStemsAlphabeticalSortFlag->setChecked(true);

        vboxLayout59->addWidget(m_miniStemsAlphabeticalSortFlag);

        m_miniStemsCorpusCountSortFlag = new QRadioButton(buttonGroup2_2_2);
        m_miniStemsCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_miniStemsCorpusCountSortFlag"));

        vboxLayout59->addWidget(m_miniStemsCorpusCountSortFlag);


        hboxLayout50->addWidget(buttonGroup2_2_2);

        spacer20_2_3_2 = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout50->addItem(spacer20_2_3_2);


        vboxLayout57->addLayout(hboxLayout50);

        buttonGroup3_2_3_2 = new Q3ButtonGroup(minilexicon_stems_file_layout_page);
        buttonGroup3_2_3_2->setObjectName(QString::fromUtf8("buttonGroup3_2_3_2"));
        buttonGroup3_2_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_3_2->layout()->setSpacing(6);
        buttonGroup3_2_3_2->layout()->setMargin(11);
        vboxLayout60 = new QVBoxLayout();
        QBoxLayout *boxlayout52 = qobject_cast<QBoxLayout *>(buttonGroup3_2_3_2->layout());
        if (boxlayout52)
            boxlayout52->addLayout(vboxLayout60);
        vboxLayout60->setAlignment(Qt::AlignTop);
        vboxLayout60->setObjectName(QString::fromUtf8("vboxLayout60"));
        m_miniStemsLine = new QLineEdit(buttonGroup3_2_3_2);
        m_miniStemsLine->setObjectName(QString::fromUtf8("m_miniStemsLine"));

        vboxLayout60->addWidget(m_miniStemsLine);

        hboxLayout51 = new QHBoxLayout();
        hboxLayout51->setSpacing(6);
        hboxLayout51->setObjectName(QString::fromUtf8("hboxLayout51"));
        m_miniStemsAddIndexButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddIndexButton->setObjectName(QString::fromUtf8("m_miniStemsAddIndexButton"));

        hboxLayout51->addWidget(m_miniStemsAddIndexButton);

        m_miniStemsAddStemButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddStemButton->setObjectName(QString::fromUtf8("m_miniStemsAddStemButton"));

        hboxLayout51->addWidget(m_miniStemsAddStemButton);

        m_miniStemsAddDescLengthButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddDescLengthButton->setObjectName(QString::fromUtf8("m_miniStemsAddDescLengthButton"));

        hboxLayout51->addWidget(m_miniStemsAddDescLengthButton);

        m_miniStemsAddCorpusCountButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddCorpusCountButton->setObjectName(QString::fromUtf8("m_miniStemsAddCorpusCountButton"));

        hboxLayout51->addWidget(m_miniStemsAddCorpusCountButton);

        spacer18_2_2_2 = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout51->addItem(spacer18_2_2_2);


        vboxLayout60->addLayout(hboxLayout51);

        hboxLayout52 = new QHBoxLayout();
        hboxLayout52->setSpacing(6);
        hboxLayout52->setObjectName(QString::fromUtf8("hboxLayout52"));
        m_miniStemsAddSignatureButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddSignatureButton->setObjectName(QString::fromUtf8("m_miniStemsAddSignatureButton"));

        hboxLayout52->addWidget(m_miniStemsAddSignatureButton);

        m_miniStemsAddOriginButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddOriginButton->setObjectName(QString::fromUtf8("m_miniStemsAddOriginButton"));

        hboxLayout52->addWidget(m_miniStemsAddOriginButton);

        m_miniStemsAddTypeButton = new QPushButton(buttonGroup3_2_3_2);
        m_miniStemsAddTypeButton->setObjectName(QString::fromUtf8("m_miniStemsAddTypeButton"));

        hboxLayout52->addWidget(m_miniStemsAddTypeButton);

        spacer19_2_2_2 = new QSpacerItem(280, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout52->addItem(spacer19_2_2_2);


        vboxLayout60->addLayout(hboxLayout52);


        vboxLayout57->addWidget(buttonGroup3_2_3_2);

        groupBox18_2_3_2 = new Q3GroupBox(minilexicon_stems_file_layout_page);
        groupBox18_2_3_2->setObjectName(QString::fromUtf8("groupBox18_2_3_2"));
        groupBox18_2_3_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_3_2->layout()->setSpacing(6);
        groupBox18_2_3_2->layout()->setMargin(11);
        vboxLayout61 = new QVBoxLayout();
        QBoxLayout *boxlayout53 = qobject_cast<QBoxLayout *>(groupBox18_2_3_2->layout());
        if (boxlayout53)
            boxlayout53->addLayout(vboxLayout61);
        vboxLayout61->setAlignment(Qt::AlignTop);
        vboxLayout61->setObjectName(QString::fromUtf8("vboxLayout61"));
        m_miniStemsExampleText = new QLabel(groupBox18_2_3_2);
        m_miniStemsExampleText->setObjectName(QString::fromUtf8("m_miniStemsExampleText"));
        m_miniStemsExampleText->setFrameShape(QFrame::Box);
        m_miniStemsExampleText->setWordWrap(false);

        vboxLayout61->addWidget(m_miniStemsExampleText);


        vboxLayout57->addWidget(groupBox18_2_3_2);

        spacer10_3_2 = new QSpacerItem(20, 153, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout57->addItem(spacer10_3_2);

        ExportWizardBase->addPage(minilexicon_stems_file_layout_page, QString::fromUtf8("Mini-Lexicon Stems File Layout"));
        minilexicon_suffixes_file_layout_page = new QWidget(ExportWizardBase);
        minilexicon_suffixes_file_layout_page->setObjectName(QString::fromUtf8("minilexicon_suffixes_file_layout_page"));
        vboxLayout62 = new QVBoxLayout(minilexicon_suffixes_file_layout_page);
        vboxLayout62->setSpacing(6);
        vboxLayout62->setMargin(11);
        vboxLayout62->setObjectName(QString::fromUtf8("vboxLayout62"));
        vboxLayout62->setContentsMargins(0, 0, 0, 0);
        hboxLayout53 = new QHBoxLayout();
        hboxLayout53->setSpacing(6);
        hboxLayout53->setObjectName(QString::fromUtf8("hboxLayout53"));
        buttonGroup5_2_2_2_3_3 = new Q3ButtonGroup(minilexicon_suffixes_file_layout_page);
        buttonGroup5_2_2_2_3_3->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_3_3"));
        buttonGroup5_2_2_2_3_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_3_3->layout()->setSpacing(6);
        buttonGroup5_2_2_2_3_3->layout()->setMargin(11);
        vboxLayout63 = new QVBoxLayout();
        QBoxLayout *boxlayout54 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_3_3->layout());
        if (boxlayout54)
            boxlayout54->addLayout(vboxLayout63);
        vboxLayout63->setAlignment(Qt::AlignTop);
        vboxLayout63->setObjectName(QString::fromUtf8("vboxLayout63"));
        m_miniSuffixesColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_3_3);
        m_miniSuffixesColumnTitlesFlag->setObjectName(QString::fromUtf8("m_miniSuffixesColumnTitlesFlag"));
        m_miniSuffixesColumnTitlesFlag->setChecked(true);

        vboxLayout63->addWidget(m_miniSuffixesColumnTitlesFlag);

        m_miniSuffixesUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_3_3);
        m_miniSuffixesUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_miniSuffixesUniformFieldWidthsFlag"));
        m_miniSuffixesUniformFieldWidthsFlag->setChecked(true);

        vboxLayout63->addWidget(m_miniSuffixesUniformFieldWidthsFlag);

        m_miniSuffixesIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2_3_3);
        m_miniSuffixesIncludeStemListFlag->setObjectName(QString::fromUtf8("m_miniSuffixesIncludeStemListFlag"));
        m_miniSuffixesIncludeStemListFlag->setChecked(true);

        vboxLayout63->addWidget(m_miniSuffixesIncludeStemListFlag);


        hboxLayout53->addWidget(buttonGroup5_2_2_2_3_3);

        buttonGroup2_2_3_2 = new Q3ButtonGroup(minilexicon_suffixes_file_layout_page);
        buttonGroup2_2_3_2->setObjectName(QString::fromUtf8("buttonGroup2_2_3_2"));
        buttonGroup2_2_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2_3_2->layout()->setSpacing(6);
        buttonGroup2_2_3_2->layout()->setMargin(11);
        vboxLayout64 = new QVBoxLayout();
        QBoxLayout *boxlayout55 = qobject_cast<QBoxLayout *>(buttonGroup2_2_3_2->layout());
        if (boxlayout55)
            boxlayout55->addLayout(vboxLayout64);
        vboxLayout64->setAlignment(Qt::AlignTop);
        vboxLayout64->setObjectName(QString::fromUtf8("vboxLayout64"));
        m_miniSuffixesAlphabeticalSortFlag = new QRadioButton(buttonGroup2_2_3_2);
        m_miniSuffixesAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_miniSuffixesAlphabeticalSortFlag"));
        m_miniSuffixesAlphabeticalSortFlag->setChecked(true);

        vboxLayout64->addWidget(m_miniSuffixesAlphabeticalSortFlag);

        m_miniSuffixesCorpusCountSortFlag = new QRadioButton(buttonGroup2_2_3_2);
        m_miniSuffixesCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_miniSuffixesCorpusCountSortFlag"));

        vboxLayout64->addWidget(m_miniSuffixesCorpusCountSortFlag);

        m_miniSuffixesStemCountSortFlag = new QRadioButton(buttonGroup2_2_3_2);
        m_miniSuffixesStemCountSortFlag->setObjectName(QString::fromUtf8("m_miniSuffixesStemCountSortFlag"));

        vboxLayout64->addWidget(m_miniSuffixesStemCountSortFlag);


        hboxLayout53->addWidget(buttonGroup2_2_3_2);

        spacer20_2_2_2_3_3 = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout53->addItem(spacer20_2_2_2_3_3);


        vboxLayout62->addLayout(hboxLayout53);

        buttonGroup3_2_2_2_3_3 = new Q3ButtonGroup(minilexicon_suffixes_file_layout_page);
        buttonGroup3_2_2_2_3_3->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_3_3"));
        buttonGroup3_2_2_2_3_3->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_3_3->layout()->setSpacing(6);
        buttonGroup3_2_2_2_3_3->layout()->setMargin(11);
        vboxLayout65 = new QVBoxLayout();
        QBoxLayout *boxlayout56 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_3_3->layout());
        if (boxlayout56)
            boxlayout56->addLayout(vboxLayout65);
        vboxLayout65->setAlignment(Qt::AlignTop);
        vboxLayout65->setObjectName(QString::fromUtf8("vboxLayout65"));
        m_miniSuffixesLine = new QLineEdit(buttonGroup3_2_2_2_3_3);
        m_miniSuffixesLine->setObjectName(QString::fromUtf8("m_miniSuffixesLine"));

        vboxLayout65->addWidget(m_miniSuffixesLine);

        hboxLayout54 = new QHBoxLayout();
        hboxLayout54->setSpacing(6);
        hboxLayout54->setObjectName(QString::fromUtf8("hboxLayout54"));
        m_miniSuffixesAddIndexButton = new QPushButton(buttonGroup3_2_2_2_3_3);
        m_miniSuffixesAddIndexButton->setObjectName(QString::fromUtf8("m_miniSuffixesAddIndexButton"));

        hboxLayout54->addWidget(m_miniSuffixesAddIndexButton);

        m_miniSuffixesAddSuffixButton = new QPushButton(buttonGroup3_2_2_2_3_3);
        m_miniSuffixesAddSuffixButton->setObjectName(QString::fromUtf8("m_miniSuffixesAddSuffixButton"));

        hboxLayout54->addWidget(m_miniSuffixesAddSuffixButton);

        m_miniSuffixesAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_3_3);
        m_miniSuffixesAddCorpusCountButton->setObjectName(QString::fromUtf8("m_miniSuffixesAddCorpusCountButton"));

        hboxLayout54->addWidget(m_miniSuffixesAddCorpusCountButton);

        m_miniSuffixesAddStemCountButton = new QPushButton(buttonGroup3_2_2_2_3_3);
        m_miniSuffixesAddStemCountButton->setObjectName(QString::fromUtf8("m_miniSuffixesAddStemCountButton"));

        hboxLayout54->addWidget(m_miniSuffixesAddStemCountButton);

        m_miniSuffixesAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2_3_3);
        m_miniSuffixesAddDescLengthButton->setObjectName(QString::fromUtf8("m_miniSuffixesAddDescLengthButton"));

        hboxLayout54->addWidget(m_miniSuffixesAddDescLengthButton);

        spacer16_3_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout54->addItem(spacer16_3_3);


        vboxLayout65->addLayout(hboxLayout54);


        vboxLayout62->addWidget(buttonGroup3_2_2_2_3_3);

        groupBox18_2_2_2_3_3 = new Q3GroupBox(minilexicon_suffixes_file_layout_page);
        groupBox18_2_2_2_3_3->setObjectName(QString::fromUtf8("groupBox18_2_2_2_3_3"));
        groupBox18_2_2_2_3_3->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_3_3->layout()->setSpacing(6);
        groupBox18_2_2_2_3_3->layout()->setMargin(11);
        vboxLayout66 = new QVBoxLayout();
        QBoxLayout *boxlayout57 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_3_3->layout());
        if (boxlayout57)
            boxlayout57->addLayout(vboxLayout66);
        vboxLayout66->setAlignment(Qt::AlignTop);
        vboxLayout66->setObjectName(QString::fromUtf8("vboxLayout66"));
        m_miniSuffixesExampleText = new QLabel(groupBox18_2_2_2_3_3);
        m_miniSuffixesExampleText->setObjectName(QString::fromUtf8("m_miniSuffixesExampleText"));
        m_miniSuffixesExampleText->setFrameShape(QFrame::Box);
        m_miniSuffixesExampleText->setWordWrap(false);

        vboxLayout66->addWidget(m_miniSuffixesExampleText);


        vboxLayout62->addWidget(groupBox18_2_2_2_3_3);

        spacer10_2_2_3_3 = new QSpacerItem(20, 186, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout62->addItem(spacer10_2_2_3_3);

        ExportWizardBase->addPage(minilexicon_suffixes_file_layout_page, QString::fromUtf8("Mini-Lexicon Suffixes File Layout"));
        minilexicon_prefixes_file_layout_page = new QWidget(ExportWizardBase);
        minilexicon_prefixes_file_layout_page->setObjectName(QString::fromUtf8("minilexicon_prefixes_file_layout_page"));
        vboxLayout67 = new QVBoxLayout(minilexicon_prefixes_file_layout_page);
        vboxLayout67->setSpacing(6);
        vboxLayout67->setMargin(11);
        vboxLayout67->setObjectName(QString::fromUtf8("vboxLayout67"));
        vboxLayout67->setContentsMargins(0, 0, 0, 0);
        hboxLayout55 = new QHBoxLayout();
        hboxLayout55->setSpacing(6);
        hboxLayout55->setObjectName(QString::fromUtf8("hboxLayout55"));
        buttonGroup5_2_2_2_3_3_2 = new Q3ButtonGroup(minilexicon_prefixes_file_layout_page);
        buttonGroup5_2_2_2_3_3_2->setObjectName(QString::fromUtf8("buttonGroup5_2_2_2_3_3_2"));
        buttonGroup5_2_2_2_3_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup5_2_2_2_3_3_2->layout()->setSpacing(6);
        buttonGroup5_2_2_2_3_3_2->layout()->setMargin(11);
        vboxLayout68 = new QVBoxLayout();
        QBoxLayout *boxlayout58 = qobject_cast<QBoxLayout *>(buttonGroup5_2_2_2_3_3_2->layout());
        if (boxlayout58)
            boxlayout58->addLayout(vboxLayout68);
        vboxLayout68->setAlignment(Qt::AlignTop);
        vboxLayout68->setObjectName(QString::fromUtf8("vboxLayout68"));
        m_miniPrefixesColumnTitlesFlag = new QCheckBox(buttonGroup5_2_2_2_3_3_2);
        m_miniPrefixesColumnTitlesFlag->setObjectName(QString::fromUtf8("m_miniPrefixesColumnTitlesFlag"));
        m_miniPrefixesColumnTitlesFlag->setChecked(true);

        vboxLayout68->addWidget(m_miniPrefixesColumnTitlesFlag);

        m_miniPrefixesUniformFieldWidthsFlag = new QCheckBox(buttonGroup5_2_2_2_3_3_2);
        m_miniPrefixesUniformFieldWidthsFlag->setObjectName(QString::fromUtf8("m_miniPrefixesUniformFieldWidthsFlag"));
        m_miniPrefixesUniformFieldWidthsFlag->setChecked(true);

        vboxLayout68->addWidget(m_miniPrefixesUniformFieldWidthsFlag);

        m_miniPrefixesIncludeStemListFlag = new QCheckBox(buttonGroup5_2_2_2_3_3_2);
        m_miniPrefixesIncludeStemListFlag->setObjectName(QString::fromUtf8("m_miniPrefixesIncludeStemListFlag"));
        m_miniPrefixesIncludeStemListFlag->setChecked(true);

        vboxLayout68->addWidget(m_miniPrefixesIncludeStemListFlag);


        hboxLayout55->addWidget(buttonGroup5_2_2_2_3_3_2);

        buttonGroup2_2_3_2_2 = new Q3ButtonGroup(minilexicon_prefixes_file_layout_page);
        buttonGroup2_2_3_2_2->setObjectName(QString::fromUtf8("buttonGroup2_2_3_2_2"));
        buttonGroup2_2_3_2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2_3_2_2->layout()->setSpacing(6);
        buttonGroup2_2_3_2_2->layout()->setMargin(11);
        vboxLayout69 = new QVBoxLayout();
        QBoxLayout *boxlayout59 = qobject_cast<QBoxLayout *>(buttonGroup2_2_3_2_2->layout());
        if (boxlayout59)
            boxlayout59->addLayout(vboxLayout69);
        vboxLayout69->setAlignment(Qt::AlignTop);
        vboxLayout69->setObjectName(QString::fromUtf8("vboxLayout69"));
        m_miniPrefixesAlphabeticalSortFlag = new QRadioButton(buttonGroup2_2_3_2_2);
        m_miniPrefixesAlphabeticalSortFlag->setObjectName(QString::fromUtf8("m_miniPrefixesAlphabeticalSortFlag"));
        m_miniPrefixesAlphabeticalSortFlag->setChecked(true);

        vboxLayout69->addWidget(m_miniPrefixesAlphabeticalSortFlag);

        m_miniPrefixesCorpusCountSortFlag = new QRadioButton(buttonGroup2_2_3_2_2);
        m_miniPrefixesCorpusCountSortFlag->setObjectName(QString::fromUtf8("m_miniPrefixesCorpusCountSortFlag"));

        vboxLayout69->addWidget(m_miniPrefixesCorpusCountSortFlag);

        m_miniPrefixesStemCountSortFlag = new QRadioButton(buttonGroup2_2_3_2_2);
        m_miniPrefixesStemCountSortFlag->setObjectName(QString::fromUtf8("m_miniPrefixesStemCountSortFlag"));

        vboxLayout69->addWidget(m_miniPrefixesStemCountSortFlag);


        hboxLayout55->addWidget(buttonGroup2_2_3_2_2);

        spacer20_2_2_2_3_3_2 = new QSpacerItem(260, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout55->addItem(spacer20_2_2_2_3_3_2);


        vboxLayout67->addLayout(hboxLayout55);

        buttonGroup3_2_2_2_3_3_2 = new Q3ButtonGroup(minilexicon_prefixes_file_layout_page);
        buttonGroup3_2_2_2_3_3_2->setObjectName(QString::fromUtf8("buttonGroup3_2_2_2_3_3_2"));
        buttonGroup3_2_2_2_3_3_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup3_2_2_2_3_3_2->layout()->setSpacing(6);
        buttonGroup3_2_2_2_3_3_2->layout()->setMargin(11);
        vboxLayout70 = new QVBoxLayout();
        QBoxLayout *boxlayout60 = qobject_cast<QBoxLayout *>(buttonGroup3_2_2_2_3_3_2->layout());
        if (boxlayout60)
            boxlayout60->addLayout(vboxLayout70);
        vboxLayout70->setAlignment(Qt::AlignTop);
        vboxLayout70->setObjectName(QString::fromUtf8("vboxLayout70"));
        m_miniPrefixesLine = new QLineEdit(buttonGroup3_2_2_2_3_3_2);
        m_miniPrefixesLine->setObjectName(QString::fromUtf8("m_miniPrefixesLine"));

        vboxLayout70->addWidget(m_miniPrefixesLine);

        hboxLayout56 = new QHBoxLayout();
        hboxLayout56->setSpacing(6);
        hboxLayout56->setObjectName(QString::fromUtf8("hboxLayout56"));
        m_miniPrefixesAddIndexButton = new QPushButton(buttonGroup3_2_2_2_3_3_2);
        m_miniPrefixesAddIndexButton->setObjectName(QString::fromUtf8("m_miniPrefixesAddIndexButton"));

        hboxLayout56->addWidget(m_miniPrefixesAddIndexButton);

        m_miniPrefixesAddPrefixButton = new QPushButton(buttonGroup3_2_2_2_3_3_2);
        m_miniPrefixesAddPrefixButton->setObjectName(QString::fromUtf8("m_miniPrefixesAddPrefixButton"));

        hboxLayout56->addWidget(m_miniPrefixesAddPrefixButton);

        m_miniPrefixesAddCorpusCountButton = new QPushButton(buttonGroup3_2_2_2_3_3_2);
        m_miniPrefixesAddCorpusCountButton->setObjectName(QString::fromUtf8("m_miniPrefixesAddCorpusCountButton"));

        hboxLayout56->addWidget(m_miniPrefixesAddCorpusCountButton);

        m_miniPrefixesAddStemCountButton = new QPushButton(buttonGroup3_2_2_2_3_3_2);
        m_miniPrefixesAddStemCountButton->setObjectName(QString::fromUtf8("m_miniPrefixesAddStemCountButton"));

        hboxLayout56->addWidget(m_miniPrefixesAddStemCountButton);

        m_miniPrefixesAddDescLengthButton = new QPushButton(buttonGroup3_2_2_2_3_3_2);
        m_miniPrefixesAddDescLengthButton->setObjectName(QString::fromUtf8("m_miniPrefixesAddDescLengthButton"));

        hboxLayout56->addWidget(m_miniPrefixesAddDescLengthButton);

        spacer16_3_3_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout56->addItem(spacer16_3_3_2);


        vboxLayout70->addLayout(hboxLayout56);


        vboxLayout67->addWidget(buttonGroup3_2_2_2_3_3_2);

        groupBox18_2_2_2_3_3_2 = new Q3GroupBox(minilexicon_prefixes_file_layout_page);
        groupBox18_2_2_2_3_3_2->setObjectName(QString::fromUtf8("groupBox18_2_2_2_3_3_2"));
        groupBox18_2_2_2_3_3_2->setColumnLayout(0, Qt::Vertical);
        groupBox18_2_2_2_3_3_2->layout()->setSpacing(6);
        groupBox18_2_2_2_3_3_2->layout()->setMargin(11);
        vboxLayout71 = new QVBoxLayout();
        QBoxLayout *boxlayout61 = qobject_cast<QBoxLayout *>(groupBox18_2_2_2_3_3_2->layout());
        if (boxlayout61)
            boxlayout61->addLayout(vboxLayout71);
        vboxLayout71->setAlignment(Qt::AlignTop);
        vboxLayout71->setObjectName(QString::fromUtf8("vboxLayout71"));
        m_miniPrefixesExampleText = new QLabel(groupBox18_2_2_2_3_3_2);
        m_miniPrefixesExampleText->setObjectName(QString::fromUtf8("m_miniPrefixesExampleText"));
        m_miniPrefixesExampleText->setFrameShape(QFrame::Box);
        m_miniPrefixesExampleText->setWordWrap(false);

        vboxLayout71->addWidget(m_miniPrefixesExampleText);


        vboxLayout67->addWidget(groupBox18_2_2_2_3_3_2);

        spacer10_2_2_3_3_2 = new QSpacerItem(20, 186, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout67->addItem(spacer10_2_2_3_3_2);

        ExportWizardBase->addPage(minilexicon_prefixes_file_layout_page, QString::fromUtf8("Mini-Lexicon Prefixes File Layout"));
        overwrite_confirmation_page = new QWidget(ExportWizardBase);
        overwrite_confirmation_page->setObjectName(QString::fromUtf8("overwrite_confirmation_page"));
        vboxLayout72 = new QVBoxLayout(overwrite_confirmation_page);
        vboxLayout72->setSpacing(6);
        vboxLayout72->setMargin(11);
        vboxLayout72->setObjectName(QString::fromUtf8("vboxLayout72"));
        vboxLayout72->setContentsMargins(0, 0, 0, 0);
        m_confirmationLabel = new QLabel(overwrite_confirmation_page);
        m_confirmationLabel->setObjectName(QString::fromUtf8("m_confirmationLabel"));
        m_confirmationLabel->setScaledContents(false);
        m_confirmationLabel->setAlignment(Qt::AlignTop|Qt::AlignLeft);
        m_confirmationLabel->setWordWrap(false);

        vboxLayout72->addWidget(m_confirmationLabel);

        m_confirmation = new Q3TextEdit(overwrite_confirmation_page);
        m_confirmation->setObjectName(QString::fromUtf8("m_confirmation"));

        vboxLayout72->addWidget(m_confirmation);

        ExportWizardBase->addPage(overwrite_confirmation_page, QString::fromUtf8("Confirmation"));
        QWidget::setTabOrder(m_projectName, m_language);
        QWidget::setTabOrder(m_language, m_researchers);
        QWidget::setTabOrder(m_researchers, m_brokenCorpusFlag);
        QWidget::setTabOrder(m_brokenCorpusFlag, m_corpusWordsFlag);
        QWidget::setTabOrder(m_corpusWordsFlag, m_compoundsFlag);
        QWidget::setTabOrder(m_compoundsFlag, m_miniWordsFlag);
        QWidget::setTabOrder(m_miniWordsFlag, m_miniSignaturesFlag);
        QWidget::setTabOrder(m_miniSignaturesFlag, m_miniStemsFlag);
        QWidget::setTabOrder(m_miniStemsFlag, m_miniSuffixesFlag);
        QWidget::setTabOrder(m_miniSuffixesFlag, m_miniPrefixesFlag);
        QWidget::setTabOrder(m_miniPrefixesFlag, m_simpleTextFlag);
        QWidget::setTabOrder(m_simpleTextFlag, m_outputDirectory);
        QWidget::setTabOrder(m_outputDirectory, m_outputDirBrowseButton);

        retranslateUi(ExportWizardBase);
        QObject::connect(m_allPrefixesAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixesAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_allPrefixesAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixesAddDescLengthButtonClickedSlot()));
        QObject::connect(m_allPrefixesAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixesAddIndexButtonClickedSlot()));
        QObject::connect(m_allPrefixesAddMiniLexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixesAddMiniLexButtonClickedSlot()));
        QObject::connect(m_allPrefixesAddPrefixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixesAddPrefixButtonClickedSlot()));
        QObject::connect(m_allPrefixesAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixesAddStemCountButtonClickedSlot()));
        QObject::connect(m_allPrefixesFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(allPrefixesCheckedSlot(bool)));
        QObject::connect(m_allPrefixesLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllPrefixesExampleSlot()));
        QObject::connect(m_allPrefixSigsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddDescLengthButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddExemplarButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddExemplarButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddIndexButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddMiniLexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddMiniLexButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddRemarksButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddRemarksButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddRobustnessButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddRobustnessButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddSigButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddSignatureButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allPrefixSigsAddStemCountButtonClickedSlot()));
        QObject::connect(m_allPrefixSigsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(allPrefixSignaturesCheckedSlot(bool)));
        QObject::connect(m_allPrefixSigsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllPrefixSigsExampleSlot()));
        QObject::connect(m_allStemsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_allStemsAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddDescLengthButtonClickedSlot()));
        QObject::connect(m_allStemsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddIndexButtonClickedSlot()));
        QObject::connect(m_allStemsAddMiniLexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddMiniLexButtonClickedSlot()));
        QObject::connect(m_allStemsAddOriginButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddOriginButtonClickedSlot()));
        QObject::connect(m_allStemsAddSignatureButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddSignatureButtonClickedSlot()));
        QObject::connect(m_allStemsAddStemButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddStemButtonClickedSlot()));
        QObject::connect(m_allStemsAddTypeButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allStemsAddTypeButtonClickedSlot()));
        QObject::connect(m_allStemsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(allStemsCheckedSlot(bool)));
        QObject::connect(m_allStemsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllStemsExampleSlot()));
        QObject::connect(m_allSuffixesAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixesAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_allSuffixesAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixesAddDescLengthButtonClickedSlot()));
        QObject::connect(m_allSuffixesAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixesAddIndexButtonClickedSlot()));
        QObject::connect(m_allSuffixesAddMiniLexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixesAddMiniLexButtonClickedSlot()));
        QObject::connect(m_allSuffixesAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixesAddStemCountButtonClickedSlot()));
        QObject::connect(m_allSuffixesAddSuffixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixesAddSuffixButtonClickedSlot()));
        QObject::connect(m_allSuffixesFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(allSuffixesCheckedSlot(bool)));
        QObject::connect(m_allSuffixesLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllSuffixesExampleSlot()));
        QObject::connect(m_allSuffixSigsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddDescLengthButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddExemplarButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddExemplarButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddIndexButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddMiniLexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddMiniLexButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddRemarksButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddRemarksButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddRobustnessButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddRobustnessButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddSigButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddSignatureButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allSuffixSigsAddStemCountButtonClickedSlot()));
        QObject::connect(m_allSuffixSigsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(allSuffixSignaturesCheckedSlot(bool)));
        QObject::connect(m_allSuffixSigsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllSuffixSigsExampleSlot()));
        QObject::connect(m_allSuffixSigsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllSigsExampleSlot()));
        QObject::connect(m_allWordsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_allWordsAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddDescLengthButtonClickedSlot()));
        QObject::connect(m_allWordsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddIndexButtonClickedSlot()));
        QObject::connect(m_allWordsAddMiniLexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddMiniLexButtonClickedSlot()));
        QObject::connect(m_allWordsAddPrefixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddPrefixButtonClickedSlot()));
        QObject::connect(m_allWordsAddSignatureButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddSignatureButtonClickedSlot()));
        QObject::connect(m_allWordsAddSourceButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddSourceButtonClickedSlot()));
        QObject::connect(m_allWordsAddStemButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddStemButtonClickedSlot()));
        QObject::connect(m_allWordsAddSuffixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddSuffixButtonClickedSlot()));
        QObject::connect(m_allWordsAddTypeButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddTypeButtonClickedSlot()));
        QObject::connect(m_allWordsAddWordButton, SIGNAL(clicked()), ExportWizardBase, SLOT(allWordsAddWordButtonClickedSlot()));
        QObject::connect(m_allWordsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(allWordsCheckedSlot(bool)));
        QObject::connect(m_allWordsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateAllWordsExampleSlot()));
        QObject::connect(m_bothFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(bothToggledSlot(bool)));
        QObject::connect(m_brokenCorpusFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_compoundColorButton, SIGNAL(clicked()), ExportWizardBase, SLOT(changeCompoundColorSlot()));
        QObject::connect(m_compoundsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_compoundsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddIndexButtonClickedSlot()));
        QObject::connect(m_compoundsAddMorphCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddMorphCountButtonClickedSlot()));
        QObject::connect(m_compoundsAddMorphsButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddMorphsButtonClickedSlot()));
        QObject::connect(m_compoundsAddParseButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddParseButtonClickedSlot()));
        QObject::connect(m_compoundsAddPrefixnessButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddPrefixnessButtonClickedSlot()));
        QObject::connect(m_compoundsAddSuffixnessButton, SIGNAL(clicked()), ExportWizardBase, SLOT(compoundsAddSuffixnessButtonClickedSlot()));
        QObject::connect(m_compoundsFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_compoundsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(compoundsCheckedSlot(bool)));
        QObject::connect(m_compoundsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateCompoundsExampleSlot()));
        QObject::connect(m_compoundsMorphemeFieldDelimiter, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateCompoundsExampleSlot()));
        QObject::connect(m_corpusWordsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(corpusWordsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_corpusWordsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(corpusWordsAddIndexButtonClickedSlot()));
        QObject::connect(m_corpusWordsAddMorphCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(corpusWordsAddMorphCountButtonClickedSlot()));
        QObject::connect(m_corpusWordsAddMorphsButton, SIGNAL(clicked()), ExportWizardBase, SLOT(corpusWordsAddMorphsButtonClickedSlot()));
        QObject::connect(m_corpusWordsAddWordButton, SIGNAL(clicked()), ExportWizardBase, SLOT(corpusWordsAddWordButtonClickedSlot()));
        QObject::connect(m_corpusWordsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(corpusWordsCheckedSlot(bool)));
        QObject::connect(m_corpusWordsFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_corpusWordsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateCorpusWordsExampleSlot()));
        QObject::connect(m_corpusWordsMorphemeFieldDelimiter, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateCorpusWordsExampleSlot()));
        QObject::connect(m_linkersAddCompoundCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(linkersAddCompoundCountButtonClickedSlot()));
        QObject::connect(m_linkersAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(linkersAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_linkersAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(linkersAddIndexButtonClickedSlot()));
        QObject::connect(m_linkersAddLinkerButton, SIGNAL(clicked()), ExportWizardBase, SLOT(linkersAddLinkerButtonClickedSlot()));
        QObject::connect(m_linkersLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateLinkersExampleSlot()));
        QObject::connect(m_markUpFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(markUpToggledSlot(bool)));
        QObject::connect(m_miniPrefixesAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniPrefixesAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_miniPrefixesAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniPrefixesAddDescLengthButtonClickedSlot()));
        QObject::connect(m_miniPrefixesAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniPrefixesAddIndexButtonClickedSlot()));
        QObject::connect(m_miniPrefixesAddPrefixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniPrefixesAddPrefixButtonClickedSlot()));
        QObject::connect(m_miniPrefixesAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniPrefixesAddStemCountButtonClickedSlot()));
        QObject::connect(m_miniPrefixesFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_miniPrefixesFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(prefixesCheckedSlot(bool)));
        QObject::connect(m_miniPrefixesLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateMiniPrefixesExampleSlot()));
        QObject::connect(m_miniSignaturesAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddDescLengthButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddExemplarButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddExemplarButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddIndexButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddRemarksButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddRemarksButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddRobustnessButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddRobustnessButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddSigButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddSignatureButtonClickedSlot()));
        QObject::connect(m_miniSignaturesAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSignaturesAddStemCountButtonClickedSlot()));
        QObject::connect(m_miniSignaturesFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_miniSignaturesFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(signaturesCheckedSlot(bool)));
        QObject::connect(m_miniSignaturesLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateMiniSignaturesExampleSlot()));
        QObject::connect(m_miniStemsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_miniStemsAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddDescLengthButtonClickedSlot()));
        QObject::connect(m_miniStemsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddIndexButtonClickedSlot()));
        QObject::connect(m_miniStemsAddOriginButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddOriginButtonClickedSlot()));
        QObject::connect(m_miniStemsAddSignatureButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddSignatureButtonClickedSlot()));
        QObject::connect(m_miniStemsAddStemButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddStemButtonClickedSlot()));
        QObject::connect(m_miniStemsAddTypeButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniStemsAddTypeButtonClickedSlot()));
        QObject::connect(m_miniStemsFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_miniStemsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(stemsCheckedSlot(bool)));
        QObject::connect(m_miniStemsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateMiniStemsExampleSlot()));
        QObject::connect(m_miniSuffixesAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSuffixesAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_miniSuffixesAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSuffixesAddDescLengthButtonClickedSlot()));
        QObject::connect(m_miniSuffixesAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSuffixesAddIndexButtonClickedSlot()));
        QObject::connect(m_miniSuffixesAddStemCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSuffixesAddStemCountButtonClickedSlot()));
        QObject::connect(m_miniSuffixesAddSuffixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniSuffixesAddSuffixButtonClickedSlot()));
        QObject::connect(m_miniSuffixesFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_miniSuffixesFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(suffixesCheckedSlot(bool)));
        QObject::connect(m_miniSuffixesLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateMiniSuffixesExampleSlot()));
        QObject::connect(m_miniWordsAddCorpusCountButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddCorpusCountButtonClickedSlot()));
        QObject::connect(m_miniWordsAddDescLengthButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddDescLengthButtonClickedSlot()));
        QObject::connect(m_miniWordsAddIndexButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddIndexButtonClickedSlot()));
        QObject::connect(m_miniWordsAddPrefixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddPrefixButtonClickedSlot()));
        QObject::connect(m_miniWordsAddSignatureButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddSignatureButtonClickedSlot()));
        QObject::connect(m_miniWordsAddSourceButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddSourceButtonClickedSlot()));
        QObject::connect(m_miniWordsAddStemButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddStemButtonClickedSlot()));
        QObject::connect(m_miniWordsAddSuffixButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddSuffixButtonClickedSlot()));
        QObject::connect(m_miniWordsAddTypeButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddTypeButtonClickedSlot()));
        QObject::connect(m_miniWordsAddWordButton, SIGNAL(clicked()), ExportWizardBase, SLOT(miniWordsAddWordButtonClickedSlot()));
        QObject::connect(m_miniWordsFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(wordsCheckedSlot(bool)));
        QObject::connect(m_miniWordsFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_miniWordsLine, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(updateMiniWordsExampleSlot()));
        QObject::connect(m_outputDirBrowseButton, SIGNAL(clicked()), ExportWizardBase, SLOT(browseOutputDirSlot()));
        QObject::connect(m_outputDirBrowseButton, SIGNAL(clicked()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_outputDirectory, SIGNAL(textChanged(QString)), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_prefixBoldFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_prefixColorButton, SIGNAL(clicked()), ExportWizardBase, SLOT(changePrefixColorSlot()));
        QObject::connect(m_prefixItalicFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_projectName, SIGNAL(lostFocus()), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_signatureBoldFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_signatureColorButton, SIGNAL(clicked()), ExportWizardBase, SLOT(changeSignatureColorSlot()));
        QObject::connect(m_signatureItalicFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_simpleTextFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(simpleTextToggledSlot(bool)));
        QObject::connect(m_stemBoldFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_stemColorButton, SIGNAL(clicked()), ExportWizardBase, SLOT(changeStemColorSlot()));
        QObject::connect(m_stemItalicFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_suffixBoldFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_suffixColorButton, SIGNAL(clicked()), ExportWizardBase, SLOT(changeSuffixColorSlot()));
        QObject::connect(m_suffixItalicFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_wordBoldFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_wordColorButton, SIGNAL(clicked()), ExportWizardBase, SLOT(changeWordColorSlot()));
        QObject::connect(m_wordItalicFlag, SIGNAL(clicked()), ExportWizardBase, SLOT(updateStylesSlot()));
        QObject::connect(m_simpleTextFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_markUpFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(validateProjectInformationSlot()));
        QObject::connect(m_bothFlag, SIGNAL(toggled(bool)), ExportWizardBase, SLOT(validateProjectInformationSlot()));

        QMetaObject::connectSlotsByName(ExportWizardBase);
    } // setupUi

    void retranslateUi(Q3Wizard *ExportWizardBase)
    {
        ExportWizardBase->setWindowTitle(QApplication::translate("ExportWizardBase", "Linguistica Export Wizard", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("ExportWizardBase", "Project Information", 0, QApplication::UnicodeUTF8));
        textLabel4->setText(QApplication::translate("ExportWizardBase", "Researcher(s):", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("ExportWizardBase", "Language:", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("ExportWizardBase", "<p align=\"left\">Project&nbsp;Name:</p>", 0, QApplication::UnicodeUTF8));
        groupBox2->setTitle(QApplication::translate("ExportWizardBase", "Outputs", 0, QApplication::UnicodeUTF8));
        m_brokenCorpusFlag->setText(QApplication::translate("ExportWizardBase", "Broken Corpus", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesFlag->setText(QApplication::translate("ExportWizardBase", "Signatures", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesFlag->setText(QApplication::translate("ExportWizardBase", "Suffixes", 0, QApplication::UnicodeUTF8));
        m_miniWordsFlag->setText(QApplication::translate("ExportWizardBase", "Words", 0, QApplication::UnicodeUTF8));
        textLabel5->setText(QApplication::translate("ExportWizardBase", "Mini-Lexica:", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesFlag->setText(QApplication::translate("ExportWizardBase", "Prefixes", 0, QApplication::UnicodeUTF8));
        m_miniStemsFlag->setText(QApplication::translate("ExportWizardBase", "Stems", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsFlag->setText(QApplication::translate("ExportWizardBase", "All Suffix Signatures", 0, QApplication::UnicodeUTF8));
        m_allPrefixesFlag->setText(QApplication::translate("ExportWizardBase", "All Prefixes", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsFlag->setText(QApplication::translate("ExportWizardBase", "All Prefix Signatures", 0, QApplication::UnicodeUTF8));
        m_allSuffixesFlag->setText(QApplication::translate("ExportWizardBase", "All Suffixes", 0, QApplication::UnicodeUTF8));
        m_allWordsFlag->setText(QApplication::translate("ExportWizardBase", "All Words", 0, QApplication::UnicodeUTF8));
        m_compoundsFlag->setText(QApplication::translate("ExportWizardBase", "Compounds", 0, QApplication::UnicodeUTF8));
        m_allStemsFlag->setText(QApplication::translate("ExportWizardBase", "All Stems", 0, QApplication::UnicodeUTF8));
        m_corpusWordsFlag->setText(QApplication::translate("ExportWizardBase", "Corpus Words", 0, QApplication::UnicodeUTF8));
        textLabel6->setText(QApplication::translate("ExportWizardBase", "Lexicon:", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("ExportWizardBase", "Corpus:", 0, QApplication::UnicodeUTF8));
        buttonGroup1->setTitle(QApplication::translate("ExportWizardBase", "Output Type", 0, QApplication::UnicodeUTF8));
        m_simpleTextFlag->setText(QApplication::translate("ExportWizardBase", "Simple Text (*.txt)", 0, QApplication::UnicodeUTF8));
        m_markUpFlag->setText(QApplication::translate("ExportWizardBase", "Mark-Up (*.html)", 0, QApplication::UnicodeUTF8));
        m_bothFlag->setText(QApplication::translate("ExportWizardBase", "Both", 0, QApplication::UnicodeUTF8));
        groupBox3->setTitle(QApplication::translate("ExportWizardBase", "Output Directory", 0, QApplication::UnicodeUTF8));
        m_outputDirBrowseButton->setText(QApplication::translate("ExportWizardBase", "Browse...", 0, QApplication::UnicodeUTF8));
        ExportWizardBase->setTitle(project_info, QApplication::translate("ExportWizardBase", "Project Information", 0, QApplication::UnicodeUTF8));
        groupBox29->setTitle(QApplication::translate("ExportWizardBase", "Word Style", 0, QApplication::UnicodeUTF8));
        textLabel6_2->setText(QApplication::translate("ExportWizardBase", "Example:", 0, QApplication::UnicodeUTF8));
        m_wordStyle->setText(QApplication::translate("ExportWizardBase", "word", 0, QApplication::UnicodeUTF8));
        m_wordBoldFlag->setText(QApplication::translate("ExportWizardBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_wordItalicFlag->setText(QApplication::translate("ExportWizardBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_wordColorButton->setText(QApplication::translate("ExportWizardBase", "Change Color", 0, QApplication::UnicodeUTF8));
        groupBox29_5->setTitle(QApplication::translate("ExportWizardBase", "Stem Style", 0, QApplication::UnicodeUTF8));
        textLabel6_2_5->setText(QApplication::translate("ExportWizardBase", "Example:", 0, QApplication::UnicodeUTF8));
        m_stemStyle->setText(QApplication::translate("ExportWizardBase", "stem", 0, QApplication::UnicodeUTF8));
        m_stemBoldFlag->setText(QApplication::translate("ExportWizardBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_stemItalicFlag->setText(QApplication::translate("ExportWizardBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_stemColorButton->setText(QApplication::translate("ExportWizardBase", "Change Color", 0, QApplication::UnicodeUTF8));
        groupBox29_3->setTitle(QApplication::translate("ExportWizardBase", "Suffix Style", 0, QApplication::UnicodeUTF8));
        textLabel6_2_3->setText(QApplication::translate("ExportWizardBase", "Example:", 0, QApplication::UnicodeUTF8));
        m_suffixStyle->setText(QApplication::translate("ExportWizardBase", "ing", 0, QApplication::UnicodeUTF8));
        m_suffixBoldFlag->setText(QApplication::translate("ExportWizardBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_suffixItalicFlag->setText(QApplication::translate("ExportWizardBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_suffixColorButton->setText(QApplication::translate("ExportWizardBase", "Change Color", 0, QApplication::UnicodeUTF8));
        groupBox29_4->setTitle(QApplication::translate("ExportWizardBase", "Prefix Style", 0, QApplication::UnicodeUTF8));
        textLabel6_2_4->setText(QApplication::translate("ExportWizardBase", "Example:", 0, QApplication::UnicodeUTF8));
        m_prefixStyle->setText(QApplication::translate("ExportWizardBase", "pre", 0, QApplication::UnicodeUTF8));
        m_prefixBoldFlag->setText(QApplication::translate("ExportWizardBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_prefixItalicFlag->setText(QApplication::translate("ExportWizardBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_prefixColorButton->setText(QApplication::translate("ExportWizardBase", "Change Color", 0, QApplication::UnicodeUTF8));
        groupBox29_2->setTitle(QApplication::translate("ExportWizardBase", "Signature Style", 0, QApplication::UnicodeUTF8));
        textLabel6_2_2->setText(QApplication::translate("ExportWizardBase", "Example:", 0, QApplication::UnicodeUTF8));
        m_signatureStyle->setText(QApplication::translate("ExportWizardBase", "NULL.ed.ing.s", 0, QApplication::UnicodeUTF8));
        m_signatureBoldFlag->setText(QApplication::translate("ExportWizardBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_signatureItalicFlag->setText(QApplication::translate("ExportWizardBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_signatureColorButton->setText(QApplication::translate("ExportWizardBase", "Change Color", 0, QApplication::UnicodeUTF8));
        groupBox29_6->setTitle(QApplication::translate("ExportWizardBase", "Compound Style", 0, QApplication::UnicodeUTF8));
        textLabel6_2_6->setText(QApplication::translate("ExportWizardBase", "Example:", 0, QApplication::UnicodeUTF8));
        m_compoundStyle->setText(QApplication::translate("ExportWizardBase", "compound", 0, QApplication::UnicodeUTF8));
        m_compoundBoldFlag->setText(QApplication::translate("ExportWizardBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_compoundItalicFlag->setText(QApplication::translate("ExportWizardBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_compoundColorButton->setText(QApplication::translate("ExportWizardBase", "Change Color", 0, QApplication::UnicodeUTF8));
        ExportWizardBase->setTitle(style_sheet, QApplication::translate("ExportWizardBase", "Text Styles", 0, QApplication::UnicodeUTF8));
        buttonGroup5->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_corpusWordsAnalyzedOnlyFlag->setText(QApplication::translate("ExportWizardBase", "Analyzed words only", 0, QApplication::UnicodeUTF8));
        m_corpusWordsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_corpusWordsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        buttonGroup2->setTitle(QApplication::translate("ExportWizardBase", "Corpus Word Order", 0, QApplication::UnicodeUTF8));
        m_corpusWordsAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_corpusWordsCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        m_corpusWordsMorphemeCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Morpheme count", 0, QApplication::UnicodeUTF8));
        buttonGroup3->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_corpusWordsLine->setText(QString());
        m_corpusWordsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_corpusWordsAddWordButton->setText(QApplication::translate("ExportWizardBase", "Word", 0, QApplication::UnicodeUTF8));
        m_corpusWordsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_corpusWordsAddMorphCountButton->setText(QApplication::translate("ExportWizardBase", "Morph Count", 0, QApplication::UnicodeUTF8));
        m_corpusWordsAddMorphsButton->setText(QApplication::translate("ExportWizardBase", "Morphs", 0, QApplication::UnicodeUTF8));
        groupBox17->setTitle(QApplication::translate("ExportWizardBase", "Morphs Field Delimiter (%MORPHS%)", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("ExportWizardBase", "<p align=\"center\">morpheme&nbsp;<tt>i</tt></p>", 0, QApplication::UnicodeUTF8));
        m_corpusWordsMorphemeFieldDelimiter->setText(QApplication::translate("ExportWizardBase", ".", 0, QApplication::UnicodeUTF8));
        textLabel4_2->setText(QApplication::translate("ExportWizardBase", "<p align=\"center\">morpheme&nbsp;<tt>j</tt></p>", 0, QApplication::UnicodeUTF8));
        groupBox18->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_corpusWordsExampleText->setText(QString());
        ExportWizardBase->setTitle(corpus_word_file_layout, QApplication::translate("ExportWizardBase", "Corpus Words File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_3->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_compoundsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_compoundsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        buttonGroup2_3->setTitle(QApplication::translate("ExportWizardBase", "Compound Order", 0, QApplication::UnicodeUTF8));
        m_compoundsAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_compoundsCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        m_compoundsMorphemeCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Morpheme count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_3->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_compoundsLine->setText(QString());
        m_compoundsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_compoundsAddWordButton->setText(QApplication::translate("ExportWizardBase", "Compound", 0, QApplication::UnicodeUTF8));
        m_compoundsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_compoundsAddMorphCountButton->setText(QApplication::translate("ExportWizardBase", "Morph Count", 0, QApplication::UnicodeUTF8));
        m_compoundsAddMorphsButton->setText(QApplication::translate("ExportWizardBase", "Morphs", 0, QApplication::UnicodeUTF8));
        m_compoundsAddSuffixnessButton->setText(QApplication::translate("ExportWizardBase", "Suffixness", 0, QApplication::UnicodeUTF8));
        m_compoundsAddPrefixnessButton->setText(QApplication::translate("ExportWizardBase", "Prefixness", 0, QApplication::UnicodeUTF8));
        m_compoundsAddParseButton->setText(QApplication::translate("ExportWizardBase", "Parse", 0, QApplication::UnicodeUTF8));
        groupBox17_2->setTitle(QApplication::translate("ExportWizardBase", "Morphs Field Delimiter (%MORPHS%)", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2->setText(QApplication::translate("ExportWizardBase", "<p align=\"center\">morpheme&nbsp;<tt>i</tt></p>", 0, QApplication::UnicodeUTF8));
        m_compoundsMorphemeFieldDelimiter->setText(QApplication::translate("ExportWizardBase", ".", 0, QApplication::UnicodeUTF8));
        textLabel4_2_2->setText(QApplication::translate("ExportWizardBase", "<p align=\"center\">morpheme&nbsp;<tt>j</tt></p>", 0, QApplication::UnicodeUTF8));
        groupBox18_3->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_compoundsExampleText->setText(QString());
        ExportWizardBase->setTitle(compounds_file_layout_page, QApplication::translate("ExportWizardBase", "Compounds File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_3_3_3->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_linkersColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_linkersUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_linkersIncludeCompoundListFlag->setText(QApplication::translate("ExportWizardBase", "Include compound list", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2_3_2_3->setTitle(QApplication::translate("ExportWizardBase", "Linker Order", 0, QApplication::UnicodeUTF8));
        m_linkersAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_linkersCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_3_3_3->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_linkersLine->setText(QString());
        m_linkersAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_linkersAddLinkerButton->setText(QApplication::translate("ExportWizardBase", "Linker", 0, QApplication::UnicodeUTF8));
        m_linkersAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_linkersAddCompoundCountButton->setText(QApplication::translate("ExportWizardBase", "Compound Count", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_3_3_3->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_linkersExampleText->setText(QString());
        ExportWizardBase->setTitle(linkers_file_layout_page, QApplication::translate("ExportWizardBase", "Linkers File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_allWordsAnalyzedOnlyFlag->setText(QApplication::translate("ExportWizardBase", "Analyzed words only", 0, QApplication::UnicodeUTF8));
        m_allWordsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_allWordsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_allWordsLine->setText(QString());
        m_allWordsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_allWordsAddWordButton->setText(QApplication::translate("ExportWizardBase", "Word", 0, QApplication::UnicodeUTF8));
        m_allWordsAddMiniLexButton->setText(QApplication::translate("ExportWizardBase", "Mini-Lexicon", 0, QApplication::UnicodeUTF8));
        m_allWordsAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_allWordsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_allWordsAddTypeButton->setText(QApplication::translate("ExportWizardBase", "Type", 0, QApplication::UnicodeUTF8));
        m_allWordsAddSignatureButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_allWordsAddSourceButton->setText(QApplication::translate("ExportWizardBase", "Source", 0, QApplication::UnicodeUTF8));
        m_allWordsAddPrefixButton->setText(QApplication::translate("ExportWizardBase", "Prefix", 0, QApplication::UnicodeUTF8));
        m_allWordsAddStemButton->setText(QApplication::translate("ExportWizardBase", "Stem", 0, QApplication::UnicodeUTF8));
        m_allWordsAddSuffixButton->setText(QApplication::translate("ExportWizardBase", "Suffix", 0, QApplication::UnicodeUTF8));
        groupBox18_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_allWordsExampleText->setText(QString());
        ExportWizardBase->setTitle(all_words_file_layout_page, QApplication::translate("ExportWizardBase", "All Words File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_allStemsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_allStemsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_allStemsLine->setText(QString());
        m_allStemsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_allStemsAddStemButton->setText(QApplication::translate("ExportWizardBase", "Stem", 0, QApplication::UnicodeUTF8));
        m_allStemsAddMiniLexButton->setText(QApplication::translate("ExportWizardBase", "Mini-Lexicon", 0, QApplication::UnicodeUTF8));
        m_allStemsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_allStemsAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_allStemsAddSignatureButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_allStemsAddOriginButton->setText(QApplication::translate("ExportWizardBase", "Origin", 0, QApplication::UnicodeUTF8));
        m_allStemsAddTypeButton->setText(QApplication::translate("ExportWizardBase", "Type", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_allStemsExampleText->setText(QString());
        ExportWizardBase->setTitle(all_stems_file_layout_page, QApplication::translate("ExportWizardBase", "All Stems File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_3->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_allSuffixesColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_allSuffixesUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_allSuffixesIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_3->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_allSuffixesLine->setText(QString());
        m_allSuffixesAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_allSuffixesAddSuffixButton->setText(QApplication::translate("ExportWizardBase", "Suffix", 0, QApplication::UnicodeUTF8));
        m_allSuffixesAddMiniLexButton->setText(QApplication::translate("ExportWizardBase", "Mini-Lexicon", 0, QApplication::UnicodeUTF8));
        m_allSuffixesAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_allSuffixesAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_allSuffixesAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_3->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_allSuffixesExampleText->setText(QString());
        ExportWizardBase->setTitle(all_suffixes_file_layout_page, QApplication::translate("ExportWizardBase", "All Suffixes File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsLine->setText(QString());
        m_allSuffixSigsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddSigButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddMiniLexButton->setText(QApplication::translate("ExportWizardBase", "Mini-Lexicon", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddRobustnessButton->setText(QApplication::translate("ExportWizardBase", "Robustness", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddExemplarButton->setText(QApplication::translate("ExportWizardBase", "Exemplar", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsAddRemarksButton->setText(QApplication::translate("ExportWizardBase", "Remarks", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_allSuffixSigsExampleText->setText(QString());
        ExportWizardBase->setTitle(all_suffix_signatures_file_layout_page, QApplication::translate("ExportWizardBase", "All Suffix Signatures File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_allPrefixesColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_allPrefixesUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_allPrefixesIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_allPrefixesLine->setText(QString());
        m_allPrefixesAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_allPrefixesAddPrefixButton->setText(QApplication::translate("ExportWizardBase", "Prefix", 0, QApplication::UnicodeUTF8));
        m_allPrefixesAddMiniLexButton->setText(QApplication::translate("ExportWizardBase", "Mini-Lexicon", 0, QApplication::UnicodeUTF8));
        m_allPrefixesAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_allPrefixesAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_allPrefixesAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_allPrefixesExampleText->setText(QString());
        ExportWizardBase->setTitle(all_prefixes_file_layout_page, QApplication::translate("ExportWizardBase", "All Prefixes File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsLine->setText(QString());
        m_allPrefixSigsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddSigButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddMiniLexButton->setText(QApplication::translate("ExportWizardBase", "Mini-Lexicon", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddRobustnessButton->setText(QApplication::translate("ExportWizardBase", "Robustness", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddExemplarButton->setText(QApplication::translate("ExportWizardBase", "Exemplar", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsAddRemarksButton->setText(QApplication::translate("ExportWizardBase", "Remarks", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_allPrefixSigsExampleText->setText(QString());
        ExportWizardBase->setTitle(all_prefix_signatures_file_layout_page, QApplication::translate("ExportWizardBase", "All Prefix Signatures File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_3->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_miniWordsAnalyzedOnlyFlag->setText(QApplication::translate("ExportWizardBase", "Analyzed words only", 0, QApplication::UnicodeUTF8));
        m_miniWordsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_miniWordsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2->setTitle(QApplication::translate("ExportWizardBase", "Word Order", 0, QApplication::UnicodeUTF8));
        m_miniWordsAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_miniWordsCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        m_miniWordsMorphemeCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Morpheme count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_3->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_miniWordsLine->setText(QString());
        m_miniWordsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddWordButton->setText(QApplication::translate("ExportWizardBase", "Word", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddTypeButton->setText(QApplication::translate("ExportWizardBase", "Type", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddSignatureButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddSourceButton->setText(QApplication::translate("ExportWizardBase", "Source", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddPrefixButton->setText(QApplication::translate("ExportWizardBase", "Prefix", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddStemButton->setText(QApplication::translate("ExportWizardBase", "Stem", 0, QApplication::UnicodeUTF8));
        m_miniWordsAddSuffixButton->setText(QApplication::translate("ExportWizardBase", "Suffix", 0, QApplication::UnicodeUTF8));
        groupBox18_2_3->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_miniWordsExampleText->setText(QString());
        ExportWizardBase->setTitle(minilexicon_words_file_layout_page, QApplication::translate("ExportWizardBase", "Mini-Lexicon Words File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_4->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2_3->setTitle(QApplication::translate("ExportWizardBase", "Signature Order", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesStemCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Stem count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_4->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesLine->setText(QString());
        m_miniSignaturesAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddSigButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddRobustnessButton->setText(QApplication::translate("ExportWizardBase", "Robustness", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddExemplarButton->setText(QApplication::translate("ExportWizardBase", "Exemplar", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesAddRemarksButton->setText(QApplication::translate("ExportWizardBase", "Remarks", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_4->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_miniSignaturesExampleText->setText(QString());
        ExportWizardBase->setTitle(minilexicon_signatures_file_layout_page, QApplication::translate("ExportWizardBase", "Mini-Lexicon Signatures File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_miniStemsColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_miniStemsUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2_2->setTitle(QApplication::translate("ExportWizardBase", "Word Order", 0, QApplication::UnicodeUTF8));
        m_miniStemsAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_miniStemsCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_miniStemsLine->setText(QString());
        m_miniStemsAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_miniStemsAddStemButton->setText(QApplication::translate("ExportWizardBase", "Stem", 0, QApplication::UnicodeUTF8));
        m_miniStemsAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        m_miniStemsAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_miniStemsAddSignatureButton->setText(QApplication::translate("ExportWizardBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_miniStemsAddOriginButton->setText(QApplication::translate("ExportWizardBase", "Origin", 0, QApplication::UnicodeUTF8));
        m_miniStemsAddTypeButton->setText(QApplication::translate("ExportWizardBase", "Type", 0, QApplication::UnicodeUTF8));
        groupBox18_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_miniStemsExampleText->setText(QString());
        ExportWizardBase->setTitle(minilexicon_stems_file_layout_page, QApplication::translate("ExportWizardBase", "Mini-Lexicon Stems File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_3_3->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2_3_2->setTitle(QApplication::translate("ExportWizardBase", "Suffix Order", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesStemCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Stem count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_3_3->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesLine->setText(QString());
        m_miniSuffixesAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesAddSuffixButton->setText(QApplication::translate("ExportWizardBase", "Suffix", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_3_3->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_miniSuffixesExampleText->setText(QString());
        ExportWizardBase->setTitle(minilexicon_suffixes_file_layout_page, QApplication::translate("ExportWizardBase", "Mini-Lexicon Suffixes File Layout", 0, QApplication::UnicodeUTF8));
        buttonGroup5_2_2_2_3_3_2->setTitle(QApplication::translate("ExportWizardBase", "Options", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesColumnTitlesFlag->setText(QApplication::translate("ExportWizardBase", "Column titles", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesUniformFieldWidthsFlag->setText(QApplication::translate("ExportWizardBase", "Uniform field widths", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesIncludeStemListFlag->setText(QApplication::translate("ExportWizardBase", "Include stem list", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2_3_2_2->setTitle(QApplication::translate("ExportWizardBase", "Prefix Order", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesAlphabeticalSortFlag->setText(QApplication::translate("ExportWizardBase", "Alphabetical", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesCorpusCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Corpus count", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesStemCountSortFlag->setText(QApplication::translate("ExportWizardBase", "Stem count", 0, QApplication::UnicodeUTF8));
        buttonGroup3_2_2_2_3_3_2->setTitle(QApplication::translate("ExportWizardBase", "Line Designer", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesLine->setText(QString());
        m_miniPrefixesAddIndexButton->setText(QApplication::translate("ExportWizardBase", "Index", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesAddPrefixButton->setText(QApplication::translate("ExportWizardBase", "Prefix", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesAddCorpusCountButton->setText(QApplication::translate("ExportWizardBase", "Corpus Count", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesAddStemCountButton->setText(QApplication::translate("ExportWizardBase", "Stem Count", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesAddDescLengthButton->setText(QApplication::translate("ExportWizardBase", "Desc. Length", 0, QApplication::UnicodeUTF8));
        groupBox18_2_2_2_3_3_2->setTitle(QApplication::translate("ExportWizardBase", "Example Line", 0, QApplication::UnicodeUTF8));
        m_miniPrefixesExampleText->setText(QString());
        ExportWizardBase->setTitle(minilexicon_prefixes_file_layout_page, QApplication::translate("ExportWizardBase", "Mini-Lexicon Prefixes File Layout", 0, QApplication::UnicodeUTF8));
        m_confirmationLabel->setText(QApplication::translate("ExportWizardBase", "The following directory and files will be created/overwritten:", 0, QApplication::UnicodeUTF8));
        ExportWizardBase->setTitle(overwrite_confirmation_page, QApplication::translate("ExportWizardBase", "Confirmation", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ExportWizardBase);
    } // retranslateUi

};

namespace Ui {
    class ExportWizardBase: public Ui_ExportWizardBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTWIZARDBASE_H
