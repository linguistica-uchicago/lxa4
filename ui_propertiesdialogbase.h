/********************************************************************************
** Form generated from reading ui file 'propertiesdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PROPERTIESDIALOGBASE_H
#define UI_PROPERTIESDIALOGBASE_H

#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <Qt3Support/Q3CanvasText>

QT_BEGIN_NAMESPACE

class Ui_PropertiesDialogBase
{
public:
    QVBoxLayout *vboxLayout;
    Q3GroupBox *rectGeometryGroupBox;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *xLabel;
    QLineEdit *StateNumber;
    QHBoxLayout *hboxLayout1;
    QLabel *widthLabel;
    QLineEdit *WordsPassing;
    QHBoxLayout *hboxLayout2;
    QLabel *widthLabel_2;
    QLineEdit *LayerNumber;
    Q3GroupBox *lineGeometryGroupBox;
    QVBoxLayout *vboxLayout2;
    Q3ListBox *MorphemeChoices;
    Q3GroupBox *lineGeometryGroupBox_2;
    QVBoxLayout *vboxLayout3;
    Q3ListBox *ParentMorphemes;
    Q3GroupBox *lineGeometryGroupBox_2_2;
    QVBoxLayout *vboxLayout4;
    Q3ListBox *Ancestors;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacer23;
    QPushButton *okButton;
    QSpacerItem *spacer22;

    void setupUi(QDialog *PropertiesDialogBase)
    {
        if (PropertiesDialogBase->objectName().isEmpty())
            PropertiesDialogBase->setObjectName(QString::fromUtf8("PropertiesDialogBase"));
        PropertiesDialogBase->resize(325, 619);
        vboxLayout = new QVBoxLayout(PropertiesDialogBase);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        rectGeometryGroupBox = new Q3GroupBox(PropertiesDialogBase);
        rectGeometryGroupBox->setObjectName(QString::fromUtf8("rectGeometryGroupBox"));
        rectGeometryGroupBox->setEnabled(true);
        rectGeometryGroupBox->setFrameShape(Q3GroupBox::Box);
        rectGeometryGroupBox->setFrameShadow(Q3GroupBox::Sunken);
        rectGeometryGroupBox->setColumnLayout(0, Qt::Vertical);
        rectGeometryGroupBox->layout()->setSpacing(6);
        rectGeometryGroupBox->layout()->setMargin(11);
        vboxLayout1 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(rectGeometryGroupBox->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout1);
        vboxLayout1->setAlignment(Qt::AlignTop);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        xLabel = new QLabel(rectGeometryGroupBox);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));
        xLabel->setWordWrap(false);

        hboxLayout->addWidget(xLabel);

        StateNumber = new QLineEdit(rectGeometryGroupBox);
        StateNumber->setObjectName(QString::fromUtf8("StateNumber"));
        StateNumber->setEnabled(false);

        hboxLayout->addWidget(StateNumber);


        vboxLayout1->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        widthLabel = new QLabel(rectGeometryGroupBox);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
        widthLabel->setWordWrap(false);

        hboxLayout1->addWidget(widthLabel);

        WordsPassing = new QLineEdit(rectGeometryGroupBox);
        WordsPassing->setObjectName(QString::fromUtf8("WordsPassing"));
        WordsPassing->setEnabled(false);

        hboxLayout1->addWidget(WordsPassing);


        vboxLayout1->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        widthLabel_2 = new QLabel(rectGeometryGroupBox);
        widthLabel_2->setObjectName(QString::fromUtf8("widthLabel_2"));
        widthLabel_2->setWordWrap(false);

        hboxLayout2->addWidget(widthLabel_2);

        LayerNumber = new QLineEdit(rectGeometryGroupBox);
        LayerNumber->setObjectName(QString::fromUtf8("LayerNumber"));
        LayerNumber->setEnabled(false);

        hboxLayout2->addWidget(LayerNumber);


        vboxLayout1->addLayout(hboxLayout2);


        vboxLayout->addWidget(rectGeometryGroupBox);

        lineGeometryGroupBox = new Q3GroupBox(PropertiesDialogBase);
        lineGeometryGroupBox->setObjectName(QString::fromUtf8("lineGeometryGroupBox"));
        lineGeometryGroupBox->setColumnLayout(0, Qt::Vertical);
        lineGeometryGroupBox->layout()->setSpacing(6);
        lineGeometryGroupBox->layout()->setMargin(11);
        vboxLayout2 = new QVBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(lineGeometryGroupBox->layout());
        if (boxlayout1)
            boxlayout1->addLayout(vboxLayout2);
        vboxLayout2->setAlignment(Qt::AlignTop);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        MorphemeChoices = new Q3ListBox(lineGeometryGroupBox);
        MorphemeChoices->setObjectName(QString::fromUtf8("MorphemeChoices"));
        MorphemeChoices->setEnabled(true);

        vboxLayout2->addWidget(MorphemeChoices);


        vboxLayout->addWidget(lineGeometryGroupBox);

        lineGeometryGroupBox_2 = new Q3GroupBox(PropertiesDialogBase);
        lineGeometryGroupBox_2->setObjectName(QString::fromUtf8("lineGeometryGroupBox_2"));
        lineGeometryGroupBox_2->setColumnLayout(0, Qt::Vertical);
        lineGeometryGroupBox_2->layout()->setSpacing(6);
        lineGeometryGroupBox_2->layout()->setMargin(11);
        vboxLayout3 = new QVBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(lineGeometryGroupBox_2->layout());
        if (boxlayout2)
            boxlayout2->addLayout(vboxLayout3);
        vboxLayout3->setAlignment(Qt::AlignTop);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        ParentMorphemes = new Q3ListBox(lineGeometryGroupBox_2);
        ParentMorphemes->setObjectName(QString::fromUtf8("ParentMorphemes"));
        ParentMorphemes->setEnabled(true);

        vboxLayout3->addWidget(ParentMorphemes);


        vboxLayout->addWidget(lineGeometryGroupBox_2);

        lineGeometryGroupBox_2_2 = new Q3GroupBox(PropertiesDialogBase);
        lineGeometryGroupBox_2_2->setObjectName(QString::fromUtf8("lineGeometryGroupBox_2_2"));
        lineGeometryGroupBox_2_2->setColumnLayout(0, Qt::Vertical);
        lineGeometryGroupBox_2_2->layout()->setSpacing(6);
        lineGeometryGroupBox_2_2->layout()->setMargin(11);
        vboxLayout4 = new QVBoxLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(lineGeometryGroupBox_2_2->layout());
        if (boxlayout3)
            boxlayout3->addLayout(vboxLayout4);
        vboxLayout4->setAlignment(Qt::AlignTop);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        Ancestors = new Q3ListBox(lineGeometryGroupBox_2_2);
        Ancestors->setObjectName(QString::fromUtf8("Ancestors"));
        Ancestors->setEnabled(true);

        vboxLayout4->addWidget(Ancestors);


        vboxLayout->addWidget(lineGeometryGroupBox_2_2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        spacer23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer23);

        okButton = new QPushButton(PropertiesDialogBase);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setDefault(true);

        hboxLayout3->addWidget(okButton);

        spacer22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer22);


        vboxLayout->addLayout(hboxLayout3);


        retranslateUi(PropertiesDialogBase);
        QObject::connect(okButton, SIGNAL(clicked()), PropertiesDialogBase, SLOT(accept()));

        QMetaObject::connectSlotsByName(PropertiesDialogBase);
    } // setupUi

    void retranslateUi(QDialog *PropertiesDialogBase)
    {
        PropertiesDialogBase->setWindowTitle(QApplication::translate("PropertiesDialogBase", "Properties", 0, QApplication::UnicodeUTF8));
        rectGeometryGroupBox->setTitle(QApplication::translate("PropertiesDialogBase", "State Property", 0, QApplication::UnicodeUTF8));
        xLabel->setText(QApplication::translate("PropertiesDialogBase", "StateNumber:", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("PropertiesDialogBase", "Words Passing :", 0, QApplication::UnicodeUTF8));
        widthLabel_2->setText(QApplication::translate("PropertiesDialogBase", "Layer Number :", 0, QApplication::UnicodeUTF8));
        lineGeometryGroupBox->setTitle(QApplication::translate("PropertiesDialogBase", "Morpheme Choices", 0, QApplication::UnicodeUTF8));
        lineGeometryGroupBox_2->setTitle(QApplication::translate("PropertiesDialogBase", "Parent Morphemes", 0, QApplication::UnicodeUTF8));
        lineGeometryGroupBox_2_2->setTitle(QApplication::translate("PropertiesDialogBase", "Ancestors", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PropertiesDialogBase", "OK", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(PropertiesDialogBase);
    } // retranslateUi

};

namespace Ui {
    class PropertiesDialogBase: public Ui_PropertiesDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESDIALOGBASE_H
