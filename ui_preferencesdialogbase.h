/********************************************************************************
** Form generated from reading ui file 'preferencesdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOGBASE_H
#define UI_PREFERENCESDIALOGBASE_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3ListView>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialogBase
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *m_UIPage;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    Q3GroupBox *groupBox1;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel1;
    Q3ListBox *m_MH_ListBox;
    QLabel *textLabel2;
    Q3TextEdit *m_MH_PreviewLineEdit;
    QVBoxLayout *vboxLayout3;
    QCheckBox *m_MH_BoldCheckBox;
    QCheckBox *m_MH_ItalicCheckBox;
    QCheckBox *m_MH_UnderlineCheckBox;
    QSpacerItem *spacer4;
    QPushButton *m_MH_ColorPushButton;
    Q3GroupBox *groupBox2;
    QVBoxLayout *vboxLayout4;
    Q3TextEdit *m_DSF_PreviewLineEdit;
    QHBoxLayout *hboxLayout2;
    QPushButton *m_DSF_FontButton;
    QSpacerItem *spacer4_2;
    QVBoxLayout *vboxLayout5;
    Q3GroupBox *groupBox9;
    QVBoxLayout *vboxLayout6;
    QCheckBox *m_NotificationsCheckBox;
    QHBoxLayout *hboxLayout3;
    QLineEdit *m_SigDelimiterLineEdit;
    QLabel *textLabel1_2;
    QSpacerItem *spacer11;
    Q3ButtonGroup *buttonGroup2;
    QVBoxLayout *vboxLayout7;
    QRadioButton *m_joinWithoutDashRadioButton;
    QRadioButton *m_joinWithDashRadioButton;
    QRadioButton *m_doNotJoinRadioButton;
    Q3ButtonGroup *buttonGroup2_2;
    QVBoxLayout *vboxLayout8;
    QCheckBox *m_removeHyphenCheckBox;
    QRadioButton *m_includeFullHyphenatedWordOnlyRadioButton;
    QRadioButton *m_includeSubstringsOfHyphenatedWordOnlyRadioButton;
    QRadioButton *m_includeFullHyphenatedWordAndSubstringsRadioButton;
    QSpacerItem *spacer12_2;
    QWidget *lexicon_preprocessing_tab_page;
    QHBoxLayout *hboxLayout4;
    QVBoxLayout *vboxLayout9;
    Q3GroupBox *groupBox3;
    QVBoxLayout *vboxLayout10;
    Q3ListBox *m_CC_ListBox;
    QHBoxLayout *hboxLayout5;
    QPushButton *m_CC_NewButton;
    QPushButton *m_CC_RemoveButton;
    Q3GroupBox *groupBox8;
    QVBoxLayout *vboxLayout11;
    QCheckBox *m_makeLowerCaseCheckBox;
    QCheckBox *m_removeNumbersCheckBox;
    QCheckBox *m_removePrecedingPunctCheckBox;
    QLineEdit *m_precedingPunctLineEdit;
    QCheckBox *m_removeInternalPunctCheckBox;
    QLineEdit *m_internalPunctLineEdit;
    QCheckBox *m_removeFollowingPunctCheckBox;
    QLineEdit *m_followingPunctLineEdit;
    QVBoxLayout *vboxLayout12;
    Q3GroupBox *m_newReplacementGroupBox;
    QVBoxLayout *vboxLayout13;
    QLabel *m_replaceTextLabel;
    QLineEdit *m_replaceLineEdit;
    QLabel *m_withTextLabel;
    QLineEdit *m_withLineEdit;
    QHBoxLayout *hboxLayout6;
    QPushButton *m_addButton;
    QSpacerItem *spacer12;
    QHBoxLayout *hboxLayout7;
    Q3ListBox *m_scrubListBox;
    QVBoxLayout *vboxLayout14;
    QPushButton *m_moveUpButton;
    QPushButton *m_moveDownButton;
    QSpacerItem *spacer13;
    QPushButton *m_removeButton;
    QHBoxLayout *hboxLayout8;
    QPushButton *m_importRulesButton;
    QPushButton *m_exportRulesButton;
    QSpacerItem *spacer20;
    QWidget *function_parameters_tab_page;
    QHBoxLayout *hboxLayout9;
    Q3ListView *m_paramListView;
    QVBoxLayout *vboxLayout15;
    QPushButton *m_resetValuePushButton;
    QPushButton *m_resetAllValsPushButton;
    QSpacerItem *spacer9;
    QHBoxLayout *hboxLayout10;
    QPushButton *m_LoadPrefsButton;
    QPushButton *m_SavePrefsButton;
    QSpacerItem *spacer10;
    QPushButton *m_helpButton;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *PreferencesDialogBase)
    {
        if (PreferencesDialogBase->objectName().isEmpty())
            PreferencesDialogBase->setObjectName(QString::fromUtf8("PreferencesDialogBase"));
        PreferencesDialogBase->resize(534, 459);
        PreferencesDialogBase->setWindowIcon(qt_get_icon(image0_ID));
        PreferencesDialogBase->setSizeGripEnabled(false);
        PreferencesDialogBase->setModal(true);
        vboxLayout = new QVBoxLayout(PreferencesDialogBase);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(PreferencesDialogBase);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        m_UIPage = new QWidget();
        m_UIPage->setObjectName(QString::fromUtf8("m_UIPage"));
        hboxLayout = new QHBoxLayout(m_UIPage);
        hboxLayout->setSpacing(6);
        hboxLayout->setMargin(11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        groupBox1 = new Q3GroupBox(m_UIPage);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setMargin(11);
        hboxLayout1 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout1);
        hboxLayout1->setAlignment(Qt::AlignTop);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        textLabel1 = new QLabel(groupBox1);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout2->addWidget(textLabel1);

        m_MH_ListBox = new Q3ListBox(groupBox1);
        m_MH_ListBox->setObjectName(QString::fromUtf8("m_MH_ListBox"));

        vboxLayout2->addWidget(m_MH_ListBox);

        textLabel2 = new QLabel(groupBox1);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout2->addWidget(textLabel2);

        m_MH_PreviewLineEdit = new Q3TextEdit(groupBox1);
        m_MH_PreviewLineEdit->setObjectName(QString::fromUtf8("m_MH_PreviewLineEdit"));
        m_MH_PreviewLineEdit->setMaximumSize(QSize(102, 25));
        m_MH_PreviewLineEdit->setWordWrap(Q3TextEdit::WidgetWidth);
        m_MH_PreviewLineEdit->setReadOnly(true);
        m_MH_PreviewLineEdit->setUndoRedoEnabled(false);

        vboxLayout2->addWidget(m_MH_PreviewLineEdit);


        hboxLayout1->addLayout(vboxLayout2);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        m_MH_BoldCheckBox = new QCheckBox(groupBox1);
        m_MH_BoldCheckBox->setObjectName(QString::fromUtf8("m_MH_BoldCheckBox"));

        vboxLayout3->addWidget(m_MH_BoldCheckBox);

        m_MH_ItalicCheckBox = new QCheckBox(groupBox1);
        m_MH_ItalicCheckBox->setObjectName(QString::fromUtf8("m_MH_ItalicCheckBox"));

        vboxLayout3->addWidget(m_MH_ItalicCheckBox);

        m_MH_UnderlineCheckBox = new QCheckBox(groupBox1);
        m_MH_UnderlineCheckBox->setObjectName(QString::fromUtf8("m_MH_UnderlineCheckBox"));

        vboxLayout3->addWidget(m_MH_UnderlineCheckBox);

        spacer4 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacer4);

        m_MH_ColorPushButton = new QPushButton(groupBox1);
        m_MH_ColorPushButton->setObjectName(QString::fromUtf8("m_MH_ColorPushButton"));
        m_MH_ColorPushButton->setMinimumSize(QSize(60, 25));
        m_MH_ColorPushButton->setMaximumSize(QSize(60, 25));

        vboxLayout3->addWidget(m_MH_ColorPushButton);


        hboxLayout1->addLayout(vboxLayout3);


        vboxLayout1->addWidget(groupBox1);

        groupBox2 = new Q3GroupBox(m_UIPage);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setMaximumSize(QSize(32767, 32767));
        groupBox2->setLineWidth(1);
        groupBox2->setMargin(0);
        groupBox2->setColumnLayout(0, Qt::Vertical);
        groupBox2->layout()->setSpacing(6);
        groupBox2->layout()->setMargin(11);
        vboxLayout4 = new QVBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox2->layout());
        if (boxlayout1)
            boxlayout1->addLayout(vboxLayout4);
        vboxLayout4->setAlignment(Qt::AlignTop);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        m_DSF_PreviewLineEdit = new Q3TextEdit(groupBox2);
        m_DSF_PreviewLineEdit->setObjectName(QString::fromUtf8("m_DSF_PreviewLineEdit"));
        m_DSF_PreviewLineEdit->setUndoRedoEnabled(false);

        vboxLayout4->addWidget(m_DSF_PreviewLineEdit);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        m_DSF_FontButton = new QPushButton(groupBox2);
        m_DSF_FontButton->setObjectName(QString::fromUtf8("m_DSF_FontButton"));

        hboxLayout2->addWidget(m_DSF_FontButton);

        spacer4_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer4_2);


        vboxLayout4->addLayout(hboxLayout2);


        vboxLayout1->addWidget(groupBox2);


        hboxLayout->addLayout(vboxLayout1);

        vboxLayout5 = new QVBoxLayout();
        vboxLayout5->setSpacing(6);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        groupBox9 = new Q3GroupBox(m_UIPage);
        groupBox9->setObjectName(QString::fromUtf8("groupBox9"));
        groupBox9->setColumnLayout(0, Qt::Vertical);
        groupBox9->layout()->setSpacing(6);
        groupBox9->layout()->setMargin(11);
        vboxLayout6 = new QVBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(groupBox9->layout());
        if (boxlayout2)
            boxlayout2->addLayout(vboxLayout6);
        vboxLayout6->setAlignment(Qt::AlignTop);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        m_NotificationsCheckBox = new QCheckBox(groupBox9);
        m_NotificationsCheckBox->setObjectName(QString::fromUtf8("m_NotificationsCheckBox"));
        m_NotificationsCheckBox->setChecked(true);

        vboxLayout6->addWidget(m_NotificationsCheckBox);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        m_SigDelimiterLineEdit = new QLineEdit(groupBox9);
        m_SigDelimiterLineEdit->setObjectName(QString::fromUtf8("m_SigDelimiterLineEdit"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_SigDelimiterLineEdit->sizePolicy().hasHeightForWidth());
        m_SigDelimiterLineEdit->setSizePolicy(sizePolicy);
        m_SigDelimiterLineEdit->setMinimumSize(QSize(20, 0));
        m_SigDelimiterLineEdit->setMaximumSize(QSize(20, 32767));
        m_SigDelimiterLineEdit->setMaxLength(1);
        m_SigDelimiterLineEdit->setCursorPosition(1);
        m_SigDelimiterLineEdit->setAlignment(Qt::AlignHCenter);

        hboxLayout3->addWidget(m_SigDelimiterLineEdit);

        textLabel1_2 = new QLabel(groupBox9);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        hboxLayout3->addWidget(textLabel1_2);

        spacer11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer11);


        vboxLayout6->addLayout(hboxLayout3);


        vboxLayout5->addWidget(groupBox9);

        buttonGroup2 = new Q3ButtonGroup(m_UIPage);
        buttonGroup2->setObjectName(QString::fromUtf8("buttonGroup2"));
        buttonGroup2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2->layout()->setSpacing(6);
        buttonGroup2->layout()->setMargin(11);
        vboxLayout7 = new QVBoxLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(buttonGroup2->layout());
        if (boxlayout3)
            boxlayout3->addLayout(vboxLayout7);
        vboxLayout7->setAlignment(Qt::AlignTop);
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        m_joinWithoutDashRadioButton = new QRadioButton(buttonGroup2);
        m_joinWithoutDashRadioButton->setObjectName(QString::fromUtf8("m_joinWithoutDashRadioButton"));
        m_joinWithoutDashRadioButton->setChecked(true);

        vboxLayout7->addWidget(m_joinWithoutDashRadioButton);

        m_joinWithDashRadioButton = new QRadioButton(buttonGroup2);
        m_joinWithDashRadioButton->setObjectName(QString::fromUtf8("m_joinWithDashRadioButton"));

        vboxLayout7->addWidget(m_joinWithDashRadioButton);

        m_doNotJoinRadioButton = new QRadioButton(buttonGroup2);
        m_doNotJoinRadioButton->setObjectName(QString::fromUtf8("m_doNotJoinRadioButton"));
        m_doNotJoinRadioButton->setChecked(false);

        vboxLayout7->addWidget(m_doNotJoinRadioButton);


        vboxLayout5->addWidget(buttonGroup2);

        buttonGroup2_2 = new Q3ButtonGroup(m_UIPage);
        buttonGroup2_2->setObjectName(QString::fromUtf8("buttonGroup2_2"));
        buttonGroup2_2->setColumnLayout(0, Qt::Vertical);
        buttonGroup2_2->layout()->setSpacing(6);
        buttonGroup2_2->layout()->setMargin(11);
        vboxLayout8 = new QVBoxLayout();
        QBoxLayout *boxlayout4 = qobject_cast<QBoxLayout *>(buttonGroup2_2->layout());
        if (boxlayout4)
            boxlayout4->addLayout(vboxLayout8);
        vboxLayout8->setAlignment(Qt::AlignTop);
        vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
        m_removeHyphenCheckBox = new QCheckBox(buttonGroup2_2);
        m_removeHyphenCheckBox->setObjectName(QString::fromUtf8("m_removeHyphenCheckBox"));
        m_removeHyphenCheckBox->setChecked(false);

        vboxLayout8->addWidget(m_removeHyphenCheckBox);

        m_includeFullHyphenatedWordOnlyRadioButton = new QRadioButton(buttonGroup2_2);
        m_includeFullHyphenatedWordOnlyRadioButton->setObjectName(QString::fromUtf8("m_includeFullHyphenatedWordOnlyRadioButton"));
        m_includeFullHyphenatedWordOnlyRadioButton->setChecked(false);

        vboxLayout8->addWidget(m_includeFullHyphenatedWordOnlyRadioButton);

        m_includeSubstringsOfHyphenatedWordOnlyRadioButton = new QRadioButton(buttonGroup2_2);
        m_includeSubstringsOfHyphenatedWordOnlyRadioButton->setObjectName(QString::fromUtf8("m_includeSubstringsOfHyphenatedWordOnlyRadioButton"));
        m_includeSubstringsOfHyphenatedWordOnlyRadioButton->setChecked(true);

        vboxLayout8->addWidget(m_includeSubstringsOfHyphenatedWordOnlyRadioButton);

        m_includeFullHyphenatedWordAndSubstringsRadioButton = new QRadioButton(buttonGroup2_2);
        m_includeFullHyphenatedWordAndSubstringsRadioButton->setObjectName(QString::fromUtf8("m_includeFullHyphenatedWordAndSubstringsRadioButton"));

        vboxLayout8->addWidget(m_includeFullHyphenatedWordAndSubstringsRadioButton);


        vboxLayout5->addWidget(buttonGroup2_2);

        spacer12_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout5->addItem(spacer12_2);


        hboxLayout->addLayout(vboxLayout5);

        tabWidget->addTab(m_UIPage, QString());
        lexicon_preprocessing_tab_page = new QWidget();
        lexicon_preprocessing_tab_page->setObjectName(QString::fromUtf8("lexicon_preprocessing_tab_page"));
        hboxLayout4 = new QHBoxLayout(lexicon_preprocessing_tab_page);
        hboxLayout4->setSpacing(6);
        hboxLayout4->setMargin(11);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        vboxLayout9 = new QVBoxLayout();
        vboxLayout9->setSpacing(6);
        vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
        groupBox3 = new Q3GroupBox(lexicon_preprocessing_tab_page);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        groupBox3->setColumnLayout(0, Qt::Vertical);
        groupBox3->layout()->setSpacing(6);
        groupBox3->layout()->setMargin(11);
        vboxLayout10 = new QVBoxLayout();
        QBoxLayout *boxlayout5 = qobject_cast<QBoxLayout *>(groupBox3->layout());
        if (boxlayout5)
            boxlayout5->addLayout(vboxLayout10);
        vboxLayout10->setAlignment(Qt::AlignTop);
        vboxLayout10->setObjectName(QString::fromUtf8("vboxLayout10"));
        m_CC_ListBox = new Q3ListBox(groupBox3);
        m_CC_ListBox->setObjectName(QString::fromUtf8("m_CC_ListBox"));
        m_CC_ListBox->setMaximumSize(QSize(175, 32767));
        m_CC_ListBox->setSelectionMode(Q3ListBox::Extended);

        vboxLayout10->addWidget(m_CC_ListBox);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        m_CC_NewButton = new QPushButton(groupBox3);
        m_CC_NewButton->setObjectName(QString::fromUtf8("m_CC_NewButton"));
        m_CC_NewButton->setMaximumSize(QSize(70, 32767));

        hboxLayout5->addWidget(m_CC_NewButton);

        m_CC_RemoveButton = new QPushButton(groupBox3);
        m_CC_RemoveButton->setObjectName(QString::fromUtf8("m_CC_RemoveButton"));
        m_CC_RemoveButton->setEnabled(false);
        m_CC_RemoveButton->setMaximumSize(QSize(70, 32767));

        hboxLayout5->addWidget(m_CC_RemoveButton);


        vboxLayout10->addLayout(hboxLayout5);


        vboxLayout9->addWidget(groupBox3);

        groupBox8 = new Q3GroupBox(lexicon_preprocessing_tab_page);
        groupBox8->setObjectName(QString::fromUtf8("groupBox8"));
        groupBox8->setColumnLayout(0, Qt::Vertical);
        groupBox8->layout()->setSpacing(6);
        groupBox8->layout()->setMargin(11);
        vboxLayout11 = new QVBoxLayout();
        QBoxLayout *boxlayout6 = qobject_cast<QBoxLayout *>(groupBox8->layout());
        if (boxlayout6)
            boxlayout6->addLayout(vboxLayout11);
        vboxLayout11->setAlignment(Qt::AlignTop);
        vboxLayout11->setObjectName(QString::fromUtf8("vboxLayout11"));
        m_makeLowerCaseCheckBox = new QCheckBox(groupBox8);
        m_makeLowerCaseCheckBox->setObjectName(QString::fromUtf8("m_makeLowerCaseCheckBox"));
        m_makeLowerCaseCheckBox->setChecked(true);

        vboxLayout11->addWidget(m_makeLowerCaseCheckBox);

        m_removeNumbersCheckBox = new QCheckBox(groupBox8);
        m_removeNumbersCheckBox->setObjectName(QString::fromUtf8("m_removeNumbersCheckBox"));

        vboxLayout11->addWidget(m_removeNumbersCheckBox);

        m_removePrecedingPunctCheckBox = new QCheckBox(groupBox8);
        m_removePrecedingPunctCheckBox->setObjectName(QString::fromUtf8("m_removePrecedingPunctCheckBox"));

        vboxLayout11->addWidget(m_removePrecedingPunctCheckBox);

        m_precedingPunctLineEdit = new QLineEdit(groupBox8);
        m_precedingPunctLineEdit->setObjectName(QString::fromUtf8("m_precedingPunctLineEdit"));
        m_precedingPunctLineEdit->setEnabled(false);
        m_precedingPunctLineEdit->setMaximumSize(QSize(175, 32767));

        vboxLayout11->addWidget(m_precedingPunctLineEdit);

        m_removeInternalPunctCheckBox = new QCheckBox(groupBox8);
        m_removeInternalPunctCheckBox->setObjectName(QString::fromUtf8("m_removeInternalPunctCheckBox"));

        vboxLayout11->addWidget(m_removeInternalPunctCheckBox);

        m_internalPunctLineEdit = new QLineEdit(groupBox8);
        m_internalPunctLineEdit->setObjectName(QString::fromUtf8("m_internalPunctLineEdit"));
        m_internalPunctLineEdit->setEnabled(false);
        m_internalPunctLineEdit->setMaximumSize(QSize(175, 32767));

        vboxLayout11->addWidget(m_internalPunctLineEdit);

        m_removeFollowingPunctCheckBox = new QCheckBox(groupBox8);
        m_removeFollowingPunctCheckBox->setObjectName(QString::fromUtf8("m_removeFollowingPunctCheckBox"));

        vboxLayout11->addWidget(m_removeFollowingPunctCheckBox);

        m_followingPunctLineEdit = new QLineEdit(groupBox8);
        m_followingPunctLineEdit->setObjectName(QString::fromUtf8("m_followingPunctLineEdit"));
        m_followingPunctLineEdit->setEnabled(false);
        m_followingPunctLineEdit->setMaximumSize(QSize(175, 32767));

        vboxLayout11->addWidget(m_followingPunctLineEdit);


        vboxLayout9->addWidget(groupBox8);


        hboxLayout4->addLayout(vboxLayout9);

        vboxLayout12 = new QVBoxLayout();
        vboxLayout12->setSpacing(6);
        vboxLayout12->setObjectName(QString::fromUtf8("vboxLayout12"));
        m_newReplacementGroupBox = new Q3GroupBox(lexicon_preprocessing_tab_page);
        m_newReplacementGroupBox->setObjectName(QString::fromUtf8("m_newReplacementGroupBox"));
        m_newReplacementGroupBox->setColumnLayout(0, Qt::Vertical);
        m_newReplacementGroupBox->layout()->setSpacing(6);
        m_newReplacementGroupBox->layout()->setMargin(11);
        vboxLayout13 = new QVBoxLayout();
        QBoxLayout *boxlayout7 = qobject_cast<QBoxLayout *>(m_newReplacementGroupBox->layout());
        if (boxlayout7)
            boxlayout7->addLayout(vboxLayout13);
        vboxLayout13->setAlignment(Qt::AlignTop);
        vboxLayout13->setObjectName(QString::fromUtf8("vboxLayout13"));
        m_replaceTextLabel = new QLabel(m_newReplacementGroupBox);
        m_replaceTextLabel->setObjectName(QString::fromUtf8("m_replaceTextLabel"));
        m_replaceTextLabel->setWordWrap(false);

        vboxLayout13->addWidget(m_replaceTextLabel);

        m_replaceLineEdit = new QLineEdit(m_newReplacementGroupBox);
        m_replaceLineEdit->setObjectName(QString::fromUtf8("m_replaceLineEdit"));
        m_replaceLineEdit->setMinimumSize(QSize(250, 0));

        vboxLayout13->addWidget(m_replaceLineEdit);

        m_withTextLabel = new QLabel(m_newReplacementGroupBox);
        m_withTextLabel->setObjectName(QString::fromUtf8("m_withTextLabel"));
        m_withTextLabel->setWordWrap(false);

        vboxLayout13->addWidget(m_withTextLabel);

        m_withLineEdit = new QLineEdit(m_newReplacementGroupBox);
        m_withLineEdit->setObjectName(QString::fromUtf8("m_withLineEdit"));
        m_withLineEdit->setMinimumSize(QSize(250, 0));

        vboxLayout13->addWidget(m_withLineEdit);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        m_addButton = new QPushButton(m_newReplacementGroupBox);
        m_addButton->setObjectName(QString::fromUtf8("m_addButton"));
        m_addButton->setEnabled(false);

        hboxLayout6->addWidget(m_addButton);

        spacer12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout6->addItem(spacer12);


        vboxLayout13->addLayout(hboxLayout6);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        m_scrubListBox = new Q3ListBox(m_newReplacementGroupBox);
        m_scrubListBox->setObjectName(QString::fromUtf8("m_scrubListBox"));
        m_scrubListBox->setSelectionMode(Q3ListBox::Extended);

        hboxLayout7->addWidget(m_scrubListBox);

        vboxLayout14 = new QVBoxLayout();
        vboxLayout14->setSpacing(6);
        vboxLayout14->setObjectName(QString::fromUtf8("vboxLayout14"));
        m_moveUpButton = new QPushButton(m_newReplacementGroupBox);
        m_moveUpButton->setObjectName(QString::fromUtf8("m_moveUpButton"));
        m_moveUpButton->setEnabled(false);

        vboxLayout14->addWidget(m_moveUpButton);

        m_moveDownButton = new QPushButton(m_newReplacementGroupBox);
        m_moveDownButton->setObjectName(QString::fromUtf8("m_moveDownButton"));
        m_moveDownButton->setEnabled(false);

        vboxLayout14->addWidget(m_moveDownButton);

        spacer13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout14->addItem(spacer13);

        m_removeButton = new QPushButton(m_newReplacementGroupBox);
        m_removeButton->setObjectName(QString::fromUtf8("m_removeButton"));
        m_removeButton->setEnabled(false);

        vboxLayout14->addWidget(m_removeButton);


        hboxLayout7->addLayout(vboxLayout14);


        vboxLayout13->addLayout(hboxLayout7);


        vboxLayout12->addWidget(m_newReplacementGroupBox);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        m_importRulesButton = new QPushButton(lexicon_preprocessing_tab_page);
        m_importRulesButton->setObjectName(QString::fromUtf8("m_importRulesButton"));

        hboxLayout8->addWidget(m_importRulesButton);

        m_exportRulesButton = new QPushButton(lexicon_preprocessing_tab_page);
        m_exportRulesButton->setObjectName(QString::fromUtf8("m_exportRulesButton"));
        m_exportRulesButton->setEnabled(true);

        hboxLayout8->addWidget(m_exportRulesButton);

        spacer20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacer20);


        vboxLayout12->addLayout(hboxLayout8);


        hboxLayout4->addLayout(vboxLayout12);

        tabWidget->addTab(lexicon_preprocessing_tab_page, QString());
        function_parameters_tab_page = new QWidget();
        function_parameters_tab_page->setObjectName(QString::fromUtf8("function_parameters_tab_page"));
        hboxLayout9 = new QHBoxLayout(function_parameters_tab_page);
        hboxLayout9->setSpacing(6);
        hboxLayout9->setMargin(11);
        hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
        m_paramListView = new Q3ListView(function_parameters_tab_page);
        m_paramListView->addColumn(QApplication::translate("PreferencesDialogBase", "Parameter", 0, QApplication::UnicodeUTF8));
        m_paramListView->header()->setClickEnabled(true, m_paramListView->header()->count() - 1);
        m_paramListView->header()->setResizeEnabled(true, m_paramListView->header()->count() - 1);
        m_paramListView->addColumn(QApplication::translate("PreferencesDialogBase", "Value", 0, QApplication::UnicodeUTF8));
        m_paramListView->header()->setClickEnabled(false, m_paramListView->header()->count() - 1);
        m_paramListView->header()->setResizeEnabled(true, m_paramListView->header()->count() - 1);
        m_paramListView->setObjectName(QString::fromUtf8("m_paramListView"));

        hboxLayout9->addWidget(m_paramListView);

        vboxLayout15 = new QVBoxLayout();
        vboxLayout15->setSpacing(6);
        vboxLayout15->setObjectName(QString::fromUtf8("vboxLayout15"));
        m_resetValuePushButton = new QPushButton(function_parameters_tab_page);
        m_resetValuePushButton->setObjectName(QString::fromUtf8("m_resetValuePushButton"));

        vboxLayout15->addWidget(m_resetValuePushButton);

        m_resetAllValsPushButton = new QPushButton(function_parameters_tab_page);
        m_resetAllValsPushButton->setObjectName(QString::fromUtf8("m_resetAllValsPushButton"));

        vboxLayout15->addWidget(m_resetAllValsPushButton);

        spacer9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout15->addItem(spacer9);


        hboxLayout9->addLayout(vboxLayout15);

        tabWidget->addTab(function_parameters_tab_page, QString());

        vboxLayout->addWidget(tabWidget);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
        m_LoadPrefsButton = new QPushButton(PreferencesDialogBase);
        m_LoadPrefsButton->setObjectName(QString::fromUtf8("m_LoadPrefsButton"));
        sizePolicy.setHeightForWidth(m_LoadPrefsButton->sizePolicy().hasHeightForWidth());
        m_LoadPrefsButton->setSizePolicy(sizePolicy);
        m_LoadPrefsButton->setMinimumSize(QSize(80, 25));
        m_LoadPrefsButton->setMaximumSize(QSize(80, 25));

        hboxLayout10->addWidget(m_LoadPrefsButton);

        m_SavePrefsButton = new QPushButton(PreferencesDialogBase);
        m_SavePrefsButton->setObjectName(QString::fromUtf8("m_SavePrefsButton"));
        sizePolicy.setHeightForWidth(m_SavePrefsButton->sizePolicy().hasHeightForWidth());
        m_SavePrefsButton->setSizePolicy(sizePolicy);
        m_SavePrefsButton->setMinimumSize(QSize(80, 25));
        m_SavePrefsButton->setMaximumSize(QSize(80, 25));

        hboxLayout10->addWidget(m_SavePrefsButton);

        spacer10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout10->addItem(spacer10);

        m_helpButton = new QPushButton(PreferencesDialogBase);
        m_helpButton->setObjectName(QString::fromUtf8("m_helpButton"));

        hboxLayout10->addWidget(m_helpButton);

        Horizontal_Spacing2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        hboxLayout10->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(PreferencesDialogBase);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
        buttonOk->setSizePolicy(sizePolicy);
        buttonOk->setMinimumSize(QSize(80, 25));
        buttonOk->setMaximumSize(QSize(80, 25));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout10->addWidget(buttonOk);

        buttonCancel = new QPushButton(PreferencesDialogBase);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
        buttonCancel->setSizePolicy(sizePolicy);
        buttonCancel->setMinimumSize(QSize(80, 25));
        buttonCancel->setMaximumSize(QSize(80, 25));
        buttonCancel->setAutoDefault(true);

        hboxLayout10->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout10);

        QWidget::setTabOrder(buttonOk, buttonCancel);
        QWidget::setTabOrder(buttonCancel, tabWidget);
        QWidget::setTabOrder(tabWidget, m_MH_ListBox);
        QWidget::setTabOrder(m_MH_ListBox, m_MH_BoldCheckBox);
        QWidget::setTabOrder(m_MH_BoldCheckBox, m_MH_ItalicCheckBox);
        QWidget::setTabOrder(m_MH_ItalicCheckBox, m_MH_UnderlineCheckBox);

        retranslateUi(PreferencesDialogBase);
        QObject::connect(buttonCancel, SIGNAL(clicked()), PreferencesDialogBase, SLOT(reject()));
        QObject::connect(buttonOk, SIGNAL(clicked()), PreferencesDialogBase, SLOT(accept()));
        QObject::connect(m_LoadPrefsButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(loadPrefsButtonClickedSlot()));
        QObject::connect(m_SavePrefsButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(savePrefsButtonClickedSlot()));
        QObject::connect(m_helpButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(help()));
        QObject::connect(m_MH_ListBox, SIGNAL(clicked(Q3ListBoxItem*)), PreferencesDialogBase, SLOT(mhListBoxHighlightedSlot()));
        QObject::connect(m_MH_BoldCheckBox, SIGNAL(clicked()), PreferencesDialogBase, SLOT(mhBoldCheckBoxClickedSlot()));
        QObject::connect(m_MH_ItalicCheckBox, SIGNAL(clicked()), PreferencesDialogBase, SLOT(mhItalicCheckBoxClickedSlot()));
        QObject::connect(m_MH_UnderlineCheckBox, SIGNAL(clicked()), PreferencesDialogBase, SLOT(mhUnderlineCheckBoxClickedSlot()));
        QObject::connect(m_MH_ColorPushButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(mhColorButtonClickedSlot()));
        QObject::connect(m_DSF_FontButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(dsfFontButtonClickedSlot()));
        QObject::connect(m_NotificationsCheckBox, SIGNAL(toggled(bool)), PreferencesDialogBase, SLOT(notificationsCheckBoxClickedSlot()));
        QObject::connect(m_SigDelimiterLineEdit, SIGNAL(textChanged(QString)), PreferencesDialogBase, SLOT(sigDelimiterChangedSlot(QString)));
        QObject::connect(m_CC_ListBox, SIGNAL(selectionChanged()), PreferencesDialogBase, SLOT(comboListBoxSelectionChangedSlot()));
        QObject::connect(m_CC_NewButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(newComboButtonClickedSlot()));
        QObject::connect(m_CC_RemoveButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(removeComboButtonClickedSlot()));
        QObject::connect(m_makeLowerCaseCheckBox, SIGNAL(toggled(bool)), PreferencesDialogBase, SLOT(makeLowerCaseCheckBoxToggled(bool)));
        QObject::connect(m_removeNumbersCheckBox, SIGNAL(toggled(bool)), PreferencesDialogBase, SLOT(removeNumbersCheckBoxToggled(bool)));
        QObject::connect(m_removePrecedingPunctCheckBox, SIGNAL(toggled(bool)), PreferencesDialogBase, SLOT(removePrecedingPunctCheckBoxToggled(bool)));
        QObject::connect(m_precedingPunctLineEdit, SIGNAL(textChanged(QString)), PreferencesDialogBase, SLOT(precedingPunctLineEditTextChanged(QString)));
        QObject::connect(m_removeInternalPunctCheckBox, SIGNAL(toggled(bool)), PreferencesDialogBase, SLOT(removeInternalPunctCheckBoxToggled(bool)));
        QObject::connect(m_internalPunctLineEdit, SIGNAL(textChanged(QString)), PreferencesDialogBase, SLOT(internalPunctLineEditTextChanged(QString)));
        QObject::connect(m_removeFollowingPunctCheckBox, SIGNAL(toggled(bool)), PreferencesDialogBase, SLOT(removeFollowingPunctCheckBoxToggled(bool)));
        QObject::connect(m_followingPunctLineEdit, SIGNAL(textChanged(QString)), PreferencesDialogBase, SLOT(followingPunctLineEditTextChanged(QString)));
        QObject::connect(m_replaceLineEdit, SIGNAL(textChanged(QString)), PreferencesDialogBase, SLOT(replaceStringsChanged()));
        QObject::connect(m_withLineEdit, SIGNAL(textChanged(QString)), PreferencesDialogBase, SLOT(replaceStringsChanged()));
        QObject::connect(m_addButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(addNewReplacementButtonPressed()));
        QObject::connect(m_scrubListBox, SIGNAL(selectionChanged()), PreferencesDialogBase, SLOT(scrubListBoxSelectionChanged()));
        QObject::connect(m_moveUpButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(moveUpButtonPressed()));
        QObject::connect(m_moveDownButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(moveDownButtonPressed()));
        QObject::connect(m_removeButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(removeReplacementButtonPressed()));
        QObject::connect(m_importRulesButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(importRulesButtonClickedSlot()));
        QObject::connect(m_exportRulesButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(exportRulesButtonClickedSlot()));
        QObject::connect(m_joinWithoutDashRadioButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(joinWithoutDashRadioButtonClickedSlot()));
        QObject::connect(m_joinWithDashRadioButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(joinWithDashRadioButtonClickedSlot()));
        QObject::connect(m_doNotJoinRadioButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(doNotJoinRadioButtonClickedSlot()));
        QObject::connect(m_includeSubstringsOfHyphenatedWordOnlyRadioButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(includeSubstringsOfHyphenatedWordOnlyRadioButtonClickedSlot()));
        QObject::connect(m_includeFullHyphenatedWordOnlyRadioButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(includeFullHyphenatedWordOnlyRadioButtonClickedSlot()));
        QObject::connect(m_includeFullHyphenatedWordAndSubstringsRadioButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(includeFullHyphenatedWordAndSubstringsRadioButtonClickedSlot()));
        QObject::connect(m_removeHyphenCheckBox, SIGNAL(clicked()), PreferencesDialogBase, SLOT(removeHyphenCheckBoxClickedSlot()));
        QObject::connect(m_paramListView, SIGNAL(itemRenamed(Q3ListViewItem*,int,QString)), PreferencesDialogBase, SLOT(paramListItemRenamedSlot(Q3ListViewItem*,int,QString)));
        QObject::connect(m_resetAllValsPushButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(resetAllValsPushButtonClickedSlot()));
        QObject::connect(m_resetValuePushButton, SIGNAL(clicked()), PreferencesDialogBase, SLOT(resetValuePushButtonClickedSlot()));

        QMetaObject::connectSlotsByName(PreferencesDialogBase);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialogBase)
    {
        PreferencesDialogBase->setWindowTitle(QApplication::translate("PreferencesDialogBase", "Linguistica : Preferences", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        tabWidget->setProperty("whatsThis", QVariant(QString()));
#endif // QT_NO_WHATSTHIS
        groupBox1->setTitle(QApplication::translate("PreferencesDialogBase", "Morphology Highlighting", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox1->setProperty("toolTip", QVariant(QString()));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        groupBox1->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Morphology Highlighting</tt></b></font>  <p>Specify the color and style of each morpheme type.  Changes will appear in the 'Command Line' window (bottom right) only.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        textLabel1->setText(QApplication::translate("PreferencesDialogBase", "Element:", 0, QApplication::UnicodeUTF8));
        m_MH_ListBox->clear();
        m_MH_ListBox->insertItem(QApplication::translate("PreferencesDialogBase", "Affix", 0, QApplication::UnicodeUTF8));
        m_MH_ListBox->insertItem(QApplication::translate("PreferencesDialogBase", "Signature", 0, QApplication::UnicodeUTF8));
        m_MH_ListBox->insertItem(QApplication::translate("PreferencesDialogBase", "Stem", 0, QApplication::UnicodeUTF8));
        m_MH_ListBox->insertItem(QApplication::translate("PreferencesDialogBase", "Word", 0, QApplication::UnicodeUTF8));
        m_MH_ListBox->insertItem(QApplication::translate("PreferencesDialogBase", "Error", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("PreferencesDialogBase", "Preview:", 0, QApplication::UnicodeUTF8));
        m_MH_PreviewLineEdit->setText(QApplication::translate("PreferencesDialogBase", "Preview", 0, QApplication::UnicodeUTF8));
        m_MH_BoldCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Bold", 0, QApplication::UnicodeUTF8));
        m_MH_ItalicCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Italic", 0, QApplication::UnicodeUTF8));
        m_MH_UnderlineCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Underline", 0, QApplication::UnicodeUTF8));
        m_MH_ColorPushButton->setText(QApplication::translate("PreferencesDialogBase", "Color", 0, QApplication::UnicodeUTF8));
        groupBox2->setTitle(QApplication::translate("PreferencesDialogBase", "Default Screen Font", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox2->setProperty("toolTip", QVariant(QString()));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        groupBox2->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Default Screen Font</tt></b></font>  <p>Change the family, decoration, and size of the default screen font.  This will affect all screens and changes will remain after closing and reopening the program.</p>  <p>The size and family of the 'Command Line' and 'Collection View' (right screens) can be changed under the 'Font' option of the 'View' menu, though this change will only be effective for the current session.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_DSF_PreviewLineEdit->setText(QApplication::translate("PreferencesDialogBase", "Editable preview text...", 0, QApplication::UnicodeUTF8));
        m_DSF_FontButton->setText(QApplication::translate("PreferencesDialogBase", "Change Screen Font", 0, QApplication::UnicodeUTF8));
        groupBox9->setTitle(QApplication::translate("PreferencesDialogBase", "General Options", 0, QApplication::UnicodeUTF8));
        m_NotificationsCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Show notifications", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        m_NotificationsCheckBox->setProperty("toolTip", QVariant(QString()));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        m_NotificationsCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Show notifications</tt></b></font>  <p>Toggles 'need save' notifications.</p>  <p>If a new lexicon is read or the program is closed without having saved the data, a prompt will appear asking whether the data should be saved.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_SigDelimiterLineEdit->setText(QApplication::translate("PreferencesDialogBase", ".", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_SigDelimiterLineEdit->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Signature delimiter</tt></b></font>  <p>This character will be used to delimit the affixes of a signature when printed to the screen and output to file.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        textLabel1_2->setText(QApplication::translate("PreferencesDialogBase", "Signature delimiter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        textLabel1_2->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Signature delimiter</tt></b></font>  <p>This character will be used to delimit the affixes of a signature when printed to the screen and output to file.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        buttonGroup2->setTitle(QApplication::translate("PreferencesDialogBase", "Line Final Hyphen", 0, QApplication::UnicodeUTF8));
        m_joinWithoutDashRadioButton->setText(QApplication::translate("PreferencesDialogBase", "Join word, remove dash", 0, QApplication::UnicodeUTF8));
        m_joinWithDashRadioButton->setText(QApplication::translate("PreferencesDialogBase", "Join word, leave dash", 0, QApplication::UnicodeUTF8));
        m_doNotJoinRadioButton->setText(QApplication::translate("PreferencesDialogBase", "Do not join word", 0, QApplication::UnicodeUTF8));
        buttonGroup2_2->setTitle(QApplication::translate("PreferencesDialogBase", "Word Internal Hyphen", 0, QApplication::UnicodeUTF8));
        m_removeHyphenCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Remove hyphen from full word", 0, QApplication::UnicodeUTF8));
        m_includeFullHyphenatedWordOnlyRadioButton->setText(QApplication::translate("PreferencesDialogBase", "Include only full word in word list", 0, QApplication::UnicodeUTF8));
        m_includeSubstringsOfHyphenatedWordOnlyRadioButton->setText(QApplication::translate("PreferencesDialogBase", "Include only substrings in word list", 0, QApplication::UnicodeUTF8));
        m_includeFullHyphenatedWordAndSubstringsRadioButton->setText(QApplication::translate("PreferencesDialogBase", "Include full word and substings", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(m_UIPage), QApplication::translate("PreferencesDialogBase", "Miscellaneous", 0, QApplication::UnicodeUTF8));
        groupBox3->setTitle(QApplication::translate("PreferencesDialogBase", "Character Combinations", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        groupBox3->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Character Combinations</tt></b></font>  <p>Combines multiple characters into one for analysis, displays and outputs the combination as multiple characters.</p>  <p>To add a combination, simply write the string of characters to be combined in the field provided after clicking the 'New...' button.</p>\n"
"<p>Combinations are made after scrubbing.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_CC_NewButton->setText(QApplication::translate("PreferencesDialogBase", "New...", 0, QApplication::UnicodeUTF8));
        m_CC_RemoveButton->setText(QApplication::translate("PreferencesDialogBase", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox8->setTitle(QApplication::translate("PreferencesDialogBase", "Common Scrubbing Rules", 0, QApplication::UnicodeUTF8));
        m_makeLowerCaseCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Make lower case", 0, QApplication::UnicodeUTF8));
        m_makeLowerCaseCheckBox->setShortcut(QString());
#ifndef QT_NO_WHATSTHIS
        m_makeLowerCaseCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Make lower case</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Make all characters lower case.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Replaces all upper case characters in every word with its lower case equivalent.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_removeNumbersCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Remove &numbers", 0, QApplication::UnicodeUTF8));
        m_removeNumbersCheckBox->setShortcut(QApplication::translate("PreferencesDialogBase", "Alt+N", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_removeNumbersCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove numbers</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all numbers.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every word that contains a digit (0-9) in every word. This might produce undesired results. For example, ordinal numbers (e.g. \"4th\") will also be removed.</p> <p>More precise number removal rules can be created using the 'Advanced Scrubbing Rules' tools.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_removePrecedingPunctCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Remove preceding punctuation:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_removePrecedingPunctCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove preceding punctuation</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all listed punctuation from the beginning of words.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every character listed in the text field that occurs at the front of the word. Any character that is separated from the front word boundary by only another listed character or characters will also be removed.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_precedingPunctLineEdit->setText(QApplication::translate("PreferencesDialogBase", "\"'$([{<-*", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_precedingPunctLineEdit->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove preceding punctuation</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all listed punctuation from the beginning of words.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every character listed in the text field that occurs at the front of the word. Any character that is separated from the front word boundary by only another listed character or characters will also be removed.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_removeInternalPunctCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Remove internal punctuation:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_removeInternalPunctCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove internal punctuation</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all listed punctuation from the middle of words.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every character listed in the text field that occurs inside the word. Any character that is separated from both word boundaries by any character not listed will be removed.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_internalPunctLineEdit->setText(QApplication::translate("PreferencesDialogBase", ".,", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_internalPunctLineEdit->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove internal punctuation</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all listed punctuation from the middle of words.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every character listed in the text field that occurs inside the word. Any character that is separated from both word boundaries by any character not listed will be removed.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_removeFollowingPunctCheckBox->setText(QApplication::translate("PreferencesDialogBase", "Remove following punctuation:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_removeFollowingPunctCheckBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove following punctuation</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all listed punctuation from the end of words.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every character listed in the text field that occurs at the end of the word. Any character that is separated from the back word boundary by only another listed character or characters will also be removed.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_followingPunctLineEdit->setText(QApplication::translate("PreferencesDialogBase", ".,?!;:\"')]}/>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_followingPunctLineEdit->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove following punctuation</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove all listed punctuation from the end of words.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes every character listed in the text field that occurs at the end of the word. Any character that is separated from the back word boundary by only another listed character or characters will also be removed.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_newReplacementGroupBox->setTitle(QApplication::translate("PreferencesDialogBase", "Advanced Scrubbing Rules", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_newReplacementGroupBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>New replacement</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Create custom, regular expression replacement rules.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Create scrubbing rules which replace every occurrence of the \"Find\" regular expression with the \"Replace with\" string.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Variables matching a set of parentheses may be used in the replacement string to avoid deleting parts of the regular expression. The variables are numbers delimited with the escape character '\\'.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Following is an example of a replace rule using variables. To replace every occurrence of the letter 'u' that occurs between two other vowels with a 'w': \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <blockquote>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  Find: ([aeiou])u([aeiou])<br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  Replace with: \\1w\\2<br><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  </blockquote>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  The result"
                        "ing replacement for the word 'naua' will be 'nawa'. If the two parenthesized expressions were not replaced as variables, the vowels on either side would be lost and the result would be 'nw'.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>For a good tutorial on regular expressions, see:\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <blockquote>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  	http://www.regular-expressions.info<br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  </blockquote>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  </p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_replaceTextLabel->setText(QApplication::translate("PreferencesDialogBase", "Find (regular expression):", 0, QApplication::UnicodeUTF8));
        m_withTextLabel->setText(QApplication::translate("PreferencesDialogBase", "Replace with:", 0, QApplication::UnicodeUTF8));
        m_addButton->setText(QApplication::translate("PreferencesDialogBase", "Add", 0, QApplication::UnicodeUTF8));
        m_scrubListBox->clear();
        m_scrubListBox->insertItem(QApplication::translate("PreferencesDialogBase", "Make lower case", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_scrubListBox->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Scrubbing rules</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>An ordered list of scrubbing rules.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>This list contains all the scrubbing rules that will be used, organized in the order they will be applied to each word. Rules above will be applied below rules beneath.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>This list also includes rules from the \"Scrubbing\" tab. All available rules can be re-ordered and removed using the buttons on the right side of the list.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_moveUpButton->setText(QApplication::translate("PreferencesDialogBase", "Move up", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_moveUpButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Move up</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Move one or more rules up in the application order.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Moves all selected rules up one spot in the application order.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_moveDownButton->setText(QApplication::translate("PreferencesDialogBase", "Move down", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_moveDownButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Move down</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Move one or more rules down in the application order.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Moves all selected rules down one spot in the application order.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_removeButton->setText(QApplication::translate("PreferencesDialogBase", "Remove", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_removeButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Remove</tt></b></font><br>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Remove a rule from the scrubbing list.</p>\n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
" \n"
"\n"
"  <p>Removes all selected rules from the scrubbing list, including scrubbing rules from the \"Scrubbing\" tab.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_importRulesButton->setText(QApplication::translate("PreferencesDialogBase", "Import Rules", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_importRulesButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Import Rules</tt></b></font>\n"
"<p>Import scrubbing rules from a text file that were created by this or another program (usually Alchemist).</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_exportRulesButton->setText(QApplication::translate("PreferencesDialogBase", "Export Rules", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_exportRulesButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Export Rules</tt></b></font><br>    <p>Export scrubbing rules to a text file to be used by another program.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        tabWidget->setTabText(tabWidget->indexOf(lexicon_preprocessing_tab_page), QApplication::translate("PreferencesDialogBase", "Lexicon Preprocessing", 0, QApplication::UnicodeUTF8));
        m_paramListView->header()->setLabel(0, QApplication::translate("PreferencesDialogBase", "Parameter", 0, QApplication::UnicodeUTF8));
        m_paramListView->header()->setLabel(1, QApplication::translate("PreferencesDialogBase", "Value", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_paramListView->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Function Parameters</tt></b></font>  <p>Change parameters used by analytical functions within Linguistica.</p>  <p>All listed parameters can be changed and will affect the analyses made by Linguistica. To reset any of the parameters to the defaults, use the buttons on the right side.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_resetValuePushButton->setText(QApplication::translate("PreferencesDialogBase", "Reset Selected", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_resetValuePushButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Function Parameters</tt></b></font>  <p>Change parameters used by analytical functions within Linguistica.</p>  <p>All listed parameters can be changed and will affect the analyses made by Linguistica. To reset any of the parameters to the defaults, use the buttons on the right side.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_resetAllValsPushButton->setText(QApplication::translate("PreferencesDialogBase", "Reset All", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        m_resetAllValsPushButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<font color=\"#555500\" size=\"+1\"><b><tt>Function Parameters</tt></b></font>  <p>Change parameters used by analytical functions within Linguistica.</p>  <p>All listed parameters can be changed and will affect the analyses made by Linguistica. To reset any of the parameters to the defaults, use the buttons on the right side.</p>", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        tabWidget->setTabText(tabWidget->indexOf(function_parameters_tab_page), QApplication::translate("PreferencesDialogBase", "Function Parameters", 0, QApplication::UnicodeUTF8));
        m_LoadPrefsButton->setText(QApplication::translate("PreferencesDialogBase", "Load", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        m_LoadPrefsButton->setProperty("toolTip", QVariant(QApplication::translate("PreferencesDialogBase", "Load Preferences", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        m_LoadPrefsButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<strong>Load Preferences</strong>  <br><br>Load corpus or language specific preferences from a file.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_SavePrefsButton->setText(QApplication::translate("PreferencesDialogBase", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        m_SavePrefsButton->setProperty("toolTip", QVariant(QApplication::translate("PreferencesDialogBase", "Save Preferences", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        m_SavePrefsButton->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<strong>Save Preferences</strong>  <br><br>Save corpus or language specific preferences to a file.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        m_helpButton->setText(QApplication::translate("PreferencesDialogBase", "&Help", 0, QApplication::UnicodeUTF8));
        m_helpButton->setShortcut(QApplication::translate("PreferencesDialogBase", "Alt+H", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("PreferencesDialogBase", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
#ifndef QT_NO_TOOLTIP
        buttonOk->setProperty("toolTip", QVariant(QApplication::translate("PreferencesDialogBase", "Accept", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        buttonOk->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<strong>Accept</strong> <br><br>Accept preference changes.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        buttonCancel->setText(QApplication::translate("PreferencesDialogBase", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
#ifndef QT_NO_TOOLTIP
        buttonCancel->setProperty("toolTip", QVariant(QApplication::translate("PreferencesDialogBase", "Reject", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        buttonCancel->setProperty("whatsThis", QVariant(QApplication::translate("PreferencesDialogBase", "<strong>Reject</strong> <br><br>Reject preference changes.", 0, QApplication::UnicodeUTF8)));
#endif // QT_NO_WHATSTHIS
        Q_UNUSED(PreferencesDialogBase);
    } // retranslateUi


protected:
    enum IconID
    {
        image0_ID,
        unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
    static const char* const image0_data[] = { 
"32 32 35 1",
". c None",
"c c #0f0f0f",
"h c #3a0909",
"D c #40210e",
"f c #450808",
"w c #4b0606",
"s c #4e0606",
"t c #4f0606",
"C c #500606",
"m c #510606",
"p c #63380f",
"n c #66320e",
"q c #672e0d",
"o c #682c0c",
"g c #692c0c",
"d c #692e0d",
"A c #774410",
"B c #784310",
"b c #7f0000",
"# c #800000",
"z c #805112",
"e c #a6400b",
"a c #a7410b",
"r c #a8420b",
"v c #a9450c",
"l c #ac490b",
"j c #b0510e",
"k c #bc6411",
"u c #bd6611",
"E c #c06811",
"x c #c06a12",
"y c #c26e12",
"F c #ce8116",
"G c #e09f1a",
"i c #e1a01c",
"................................",
"..........##....................",
"..#.##.....#ab.#...#............",
"..##b......cde.f...#............",
"....##......cg#hijf#............",
"....klb....#.mjnnhc....#........",
".....k##...bnob##......#........",
".....np#...ea#b........b........",
"#.....n#.#leb#.......##bk.......",
"#b#j.#nb#qg###...##.###rj...#...",
".#sd.#ktlgb#....#bb.b#je#...#...",
"..#ob#ptb#......brr.bjua#.#b#...",
"..#bd#pb........l##.#r##bb#l#...",
"...#g##...##...kla#lva#beoni....",
"....ql#..wjk..#x#uvjqgvjmm##....",
"....#vb#wv...#lbyzoAqwftm###....",
"h...#lbklb...ke#zzBgbb#enm#b#...",
"f##.#jsqb#...##bzB#b#.bbidd#s...",
".fkj.j####....##gob##.#..#vrC#..",
"..hrvnm##b..#..#w##b#...###lob#.",
"..hhrj##.#..###...#.#..#blqwfc#.",
"....wj##.##.##b...b###bbjvnbb#..",
"...##kb####.#.fD#..qo#krEsc#b#..",
"###lxb###b..bb#wl#.kAAo##t##....",
".##wwra##b##b#.btob###eb#f......",
"..##ftbbbb.b####bo###jFrwt#.....",
"....##wpnlb#llj..#bbpkvblo##....",
"....dojvbjlba#ba##brqEb.bga.....",
"..#bs...###lbfhfb#Glw#...####...",
"...#....bb.xwhb##.kbsf.....#b#..",
"..##....#bvjf.#.#..###..........",
"...........#........#..........."};


    switch (id) {
        case image0_ID: return QPixmap((const char**)image0_data);
        default: return QPixmap();
    } // switch
    } // icon

};

namespace Ui {
    class PreferencesDialogBase: public Ui_PreferencesDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOGBASE_H
