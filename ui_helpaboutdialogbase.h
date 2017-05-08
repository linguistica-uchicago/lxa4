/********************************************************************************
** Form generated from reading ui file 'helpaboutdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_HELPABOUTDIALOGBASE_H
#define UI_HELPABOUTDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HelpAboutDialogBase
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacer7;
    QLabel *lxaPixmapLabel;
    QSpacerItem *spacer6;
    QLabel *m_versionTextLabel;
    QLabel *crTextLabel;
    QLabel *infoTextLabel;
    QSpacerItem *spacer8;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacer5;
    QPushButton *acceptPushButton;
    QSpacerItem *spacer4;

    void setupUi(QDialog *HelpAboutDialogBase)
    {
        if (HelpAboutDialogBase->objectName().isEmpty())
            HelpAboutDialogBase->setObjectName(QString::fromUtf8("HelpAboutDialogBase"));
        HelpAboutDialogBase->resize(389, 632);
        vboxLayout = new QVBoxLayout(HelpAboutDialogBase);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacer7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer7);

        lxaPixmapLabel = new QLabel(HelpAboutDialogBase);
        lxaPixmapLabel->setObjectName(QString::fromUtf8("lxaPixmapLabel"));
        lxaPixmapLabel->setFrameShape(QFrame::Box);
        lxaPixmapLabel->setLineWidth(2);
        lxaPixmapLabel->setPixmap(QPixmap(QString::fromUtf8(":/uofc.xpm")));
        lxaPixmapLabel->setScaledContents(false);
        lxaPixmapLabel->setAlignment(Qt::AlignCenter);
        lxaPixmapLabel->setWordWrap(false);

        hboxLayout->addWidget(lxaPixmapLabel);

        spacer6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer6);


        vboxLayout->addLayout(hboxLayout);

        m_versionTextLabel = new QLabel(HelpAboutDialogBase);
        m_versionTextLabel->setObjectName(QString::fromUtf8("m_versionTextLabel"));
        m_versionTextLabel->setAlignment(Qt::AlignCenter);
        m_versionTextLabel->setWordWrap(true);

        vboxLayout->addWidget(m_versionTextLabel);

        crTextLabel = new QLabel(HelpAboutDialogBase);
        crTextLabel->setObjectName(QString::fromUtf8("crTextLabel"));
        crTextLabel->setAlignment(Qt::AlignCenter);
        crTextLabel->setWordWrap(false);

        vboxLayout->addWidget(crTextLabel);

        infoTextLabel = new QLabel(HelpAboutDialogBase);
        infoTextLabel->setObjectName(QString::fromUtf8("infoTextLabel"));
        infoTextLabel->setWordWrap(false);

        vboxLayout->addWidget(infoTextLabel);

        spacer8 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer8);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacer5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer5);

        acceptPushButton = new QPushButton(HelpAboutDialogBase);
        acceptPushButton->setObjectName(QString::fromUtf8("acceptPushButton"));

        hboxLayout1->addWidget(acceptPushButton);

        spacer4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer4);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(HelpAboutDialogBase);
        QObject::connect(acceptPushButton, SIGNAL(clicked()), HelpAboutDialogBase, SLOT(accept()));

        QMetaObject::connectSlotsByName(HelpAboutDialogBase);
    } // setupUi

    void retranslateUi(QDialog *HelpAboutDialogBase)
    {
        HelpAboutDialogBase->setWindowTitle(QApplication::translate("HelpAboutDialogBase", "About Linguistica", 0, QApplication::UnicodeUTF8));
        m_versionTextLabel->setText(QApplication::translate("HelpAboutDialogBase", "<h1><font face=\"Arial\">Linguistica</font></h1>", 0, QApplication::UnicodeUTF8));
        crTextLabel->setText(QApplication::translate("HelpAboutDialogBase", "\302\251 Copyright 2002-2005.", 0, QApplication::UnicodeUTF8));
        infoTextLabel->setText(QApplication::translate("HelpAboutDialogBase", "<p>Linguistica is a program which can be used to explore the unsupervised learning of natural language, with primary focus on morphology, which is to say, word-structure.</p>\n"
" <p>Linguistica was developed by the Linguistica Group at the University of Chicago.  Its members are:<br><br>\n"
" &nbsp;&nbsp;&nbsp;- John Goldsmith<br>\n"
" &nbsp;&nbsp;&nbsp;- Colin Sprague<br>\n"
" &nbsp;&nbsp;&nbsp;- Yu Hu<br><br>\n"
" Please see http://linguistica.uchicago.edu on the internet for documentation, contact information, and more about Linguistica.</p><br><br>", 0, QApplication::UnicodeUTF8));
        acceptPushButton->setText(QApplication::translate("HelpAboutDialogBase", "&OK", 0, QApplication::UnicodeUTF8));
        acceptPushButton->setShortcut(QApplication::translate("HelpAboutDialogBase", "Alt+O", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(HelpAboutDialogBase);
    } // retranslateUi

};

namespace Ui {
    class HelpAboutDialogBase: public Ui_HelpAboutDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPABOUTDIALOGBASE_H
