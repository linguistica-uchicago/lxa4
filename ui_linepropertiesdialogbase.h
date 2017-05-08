/********************************************************************************
** Form generated from reading ui file 'linepropertiesdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LINEPROPERTIESDIALOGBASE_H
#define UI_LINEPROPERTIESDIALOGBASE_H

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

class Ui_LinePropertiesDialogBase
{
public:
    QVBoxLayout *vboxLayout;
    Q3GroupBox *rectGeometryGroupBox;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *xLabel;
    QLineEdit *FromStateNumber;
    QHBoxLayout *hboxLayout1;
    QLabel *widthLabel;
    QLineEdit *ToStateNumber;
    Q3GroupBox *lineGeometryGroupBox;
    QVBoxLayout *vboxLayout2;
    Q3ListBox *Morphemes;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacer6;
    QPushButton *okButton;
    QSpacerItem *spacer7;

    void setupUi(QDialog *LinePropertiesDialogBase)
    {
        if (LinePropertiesDialogBase->objectName().isEmpty())
            LinePropertiesDialogBase->setObjectName(QString::fromUtf8("LinePropertiesDialogBase"));
        LinePropertiesDialogBase->resize(325, 338);
        vboxLayout = new QVBoxLayout(LinePropertiesDialogBase);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        rectGeometryGroupBox = new Q3GroupBox(LinePropertiesDialogBase);
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

        FromStateNumber = new QLineEdit(rectGeometryGroupBox);
        FromStateNumber->setObjectName(QString::fromUtf8("FromStateNumber"));
        FromStateNumber->setEnabled(false);

        hboxLayout->addWidget(FromStateNumber);


        vboxLayout1->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        widthLabel = new QLabel(rectGeometryGroupBox);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
        widthLabel->setWordWrap(false);

        hboxLayout1->addWidget(widthLabel);

        ToStateNumber = new QLineEdit(rectGeometryGroupBox);
        ToStateNumber->setObjectName(QString::fromUtf8("ToStateNumber"));
        ToStateNumber->setEnabled(false);

        hboxLayout1->addWidget(ToStateNumber);


        vboxLayout1->addLayout(hboxLayout1);


        vboxLayout->addWidget(rectGeometryGroupBox);

        lineGeometryGroupBox = new Q3GroupBox(LinePropertiesDialogBase);
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
        Morphemes = new Q3ListBox(lineGeometryGroupBox);
        Morphemes->setObjectName(QString::fromUtf8("Morphemes"));
        Morphemes->setEnabled(true);

        vboxLayout2->addWidget(Morphemes);


        vboxLayout->addWidget(lineGeometryGroupBox);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacer6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer6);

        okButton = new QPushButton(LinePropertiesDialogBase);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setDefault(true);

        hboxLayout2->addWidget(okButton);

        spacer7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacer7);


        vboxLayout->addLayout(hboxLayout2);


        retranslateUi(LinePropertiesDialogBase);
        QObject::connect(okButton, SIGNAL(clicked()), LinePropertiesDialogBase, SLOT(accept()));

        QMetaObject::connectSlotsByName(LinePropertiesDialogBase);
    } // setupUi

    void retranslateUi(QDialog *LinePropertiesDialogBase)
    {
        LinePropertiesDialogBase->setWindowTitle(QApplication::translate("LinePropertiesDialogBase", "Properties", 0, QApplication::UnicodeUTF8));
        rectGeometryGroupBox->setTitle(QApplication::translate("LinePropertiesDialogBase", "Direction", 0, QApplication::UnicodeUTF8));
        xLabel->setText(QApplication::translate("LinePropertiesDialogBase", "From State :", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("LinePropertiesDialogBase", "To State :", 0, QApplication::UnicodeUTF8));
        lineGeometryGroupBox->setTitle(QApplication::translate("LinePropertiesDialogBase", "Morphemes With This Line", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("LinePropertiesDialogBase", "OK", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LinePropertiesDialogBase);
    } // retranslateUi

};

namespace Ui {
    class LinePropertiesDialogBase: public Ui_LinePropertiesDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEPROPERTIESDIALOGBASE_H
