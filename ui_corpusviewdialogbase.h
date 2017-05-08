/********************************************************************************
** Form generated from reading ui file 'corpusviewdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CORPUSVIEWDIALOGBASE_H
#define UI_CORPUSVIEWDIALOGBASE_H

#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CorpusViewDialogBase
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    Q3GroupBox *groupBox1;
    QHBoxLayout *hboxLayout1;
    QCheckBox *m_bindScrollBarsCheckBox;
    QCheckBox *m_wordWrapCheckBox;
    QCheckBox *m_showMarkedUpTextCheckBox;
    QSpacerItem *spacer4;
    QHBoxLayout *hboxLayout2;
    Q3TextEdit *m_leftTextEdit;
    Q3TextEdit *m_rightTextEdit;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;

    void setupUi(QDialog *CorpusViewDialogBase)
    {
        if (CorpusViewDialogBase->objectName().isEmpty())
            CorpusViewDialogBase->setObjectName(QString::fromUtf8("CorpusViewDialogBase"));
        CorpusViewDialogBase->resize(839, 721);
        CorpusViewDialogBase->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(CorpusViewDialogBase);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        groupBox1 = new Q3GroupBox(CorpusViewDialogBase);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setMaximumSize(QSize(32767, 32767));
        groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setMargin(11);
        hboxLayout1 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout1);
        hboxLayout1->setAlignment(Qt::AlignTop);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        m_bindScrollBarsCheckBox = new QCheckBox(groupBox1);
        m_bindScrollBarsCheckBox->setObjectName(QString::fromUtf8("m_bindScrollBarsCheckBox"));
        m_bindScrollBarsCheckBox->setChecked(true);

        hboxLayout1->addWidget(m_bindScrollBarsCheckBox);

        m_wordWrapCheckBox = new QCheckBox(groupBox1);
        m_wordWrapCheckBox->setObjectName(QString::fromUtf8("m_wordWrapCheckBox"));
        m_wordWrapCheckBox->setChecked(true);

        hboxLayout1->addWidget(m_wordWrapCheckBox);

        m_showMarkedUpTextCheckBox = new QCheckBox(groupBox1);
        m_showMarkedUpTextCheckBox->setObjectName(QString::fromUtf8("m_showMarkedUpTextCheckBox"));
        m_showMarkedUpTextCheckBox->setEnabled(false);

        hboxLayout1->addWidget(m_showMarkedUpTextCheckBox);


        hboxLayout->addWidget(groupBox1);

        spacer4 = new QSpacerItem(329, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer4);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        m_leftTextEdit = new Q3TextEdit(CorpusViewDialogBase);
        m_leftTextEdit->setObjectName(QString::fromUtf8("m_leftTextEdit"));
        m_leftTextEdit->setReadOnly(true);
        m_leftTextEdit->setUndoRedoEnabled(false);

        hboxLayout2->addWidget(m_leftTextEdit);

        m_rightTextEdit = new Q3TextEdit(CorpusViewDialogBase);
        m_rightTextEdit->setObjectName(QString::fromUtf8("m_rightTextEdit"));
        m_rightTextEdit->setReadOnly(true);
        m_rightTextEdit->setUndoRedoEnabled(false);

        hboxLayout2->addWidget(m_rightTextEdit);


        vboxLayout->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setMargin(0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        Horizontal_Spacing2 = new QSpacerItem(290, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(CorpusViewDialogBase);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout3->addWidget(buttonOk);


        vboxLayout->addLayout(hboxLayout3);


        retranslateUi(CorpusViewDialogBase);
        QObject::connect(buttonOk, SIGNAL(clicked()), CorpusViewDialogBase, SLOT(accept()));
        QObject::connect(m_showMarkedUpTextCheckBox, SIGNAL(toggled(bool)), CorpusViewDialogBase, SLOT(showMarkedUpText(bool)));
        QObject::connect(m_leftTextEdit, SIGNAL(contentsMoving(int,int)), CorpusViewDialogBase, SLOT(moveRightView(int,int)));
        QObject::connect(m_rightTextEdit, SIGNAL(contentsMoving(int,int)), CorpusViewDialogBase, SLOT(moveLeftView(int,int)));
        QObject::connect(m_wordWrapCheckBox, SIGNAL(toggled(bool)), CorpusViewDialogBase, SLOT(wordWrap(bool)));

        QMetaObject::connectSlotsByName(CorpusViewDialogBase);
    } // setupUi

    void retranslateUi(QDialog *CorpusViewDialogBase)
    {
        CorpusViewDialogBase->setWindowTitle(QApplication::translate("CorpusViewDialogBase", "Linguistica : Corpus View", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("CorpusViewDialogBase", "Options", 0, QApplication::UnicodeUTF8));
        m_bindScrollBarsCheckBox->setText(QApplication::translate("CorpusViewDialogBase", "&Bind scroll bars", 0, QApplication::UnicodeUTF8));
        m_bindScrollBarsCheckBox->setShortcut(QApplication::translate("CorpusViewDialogBase", "Alt+B", 0, QApplication::UnicodeUTF8));
        m_wordWrapCheckBox->setText(QApplication::translate("CorpusViewDialogBase", "&Word wrap", 0, QApplication::UnicodeUTF8));
        m_wordWrapCheckBox->setShortcut(QApplication::translate("CorpusViewDialogBase", "Alt+W", 0, QApplication::UnicodeUTF8));
        m_showMarkedUpTextCheckBox->setText(QApplication::translate("CorpusViewDialogBase", "&Show marked-up text", 0, QApplication::UnicodeUTF8));
        m_showMarkedUpTextCheckBox->setShortcut(QApplication::translate("CorpusViewDialogBase", "Alt+S", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("CorpusViewDialogBase", "&Close", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QApplication::translate("CorpusViewDialogBase", "Alt+C", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CorpusViewDialogBase);
    } // retranslateUi

};

namespace Ui {
    class CorpusViewDialogBase: public Ui_CorpusViewDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORPUSVIEWDIALOGBASE_H
