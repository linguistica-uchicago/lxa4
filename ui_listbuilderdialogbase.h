/********************************************************************************
** Form generated from reading ui file 'listbuilderdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LISTBUILDERDIALOGBASE_H
#define UI_LISTBUILDERDIALOGBASE_H

#include <Qt3Support/Q3ListBox>
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

class Ui_ListBuilderDialogBase
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *textLabel1;
    Q3ListBox *m_NotIncluded;
    QVBoxLayout *vboxLayout2;
    QSpacerItem *spacer3;
    QPushButton *m_buttonAdd;
    QPushButton *m_buttonRemove;
    QSpacerItem *spacer4;
    QVBoxLayout *vboxLayout3;
    QLabel *textLabel2;
    Q3ListBox *m_Included;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *ListBuilderDialogBase)
    {
        if (ListBuilderDialogBase->objectName().isEmpty())
            ListBuilderDialogBase->setObjectName(QString::fromUtf8("ListBuilderDialogBase"));
        ListBuilderDialogBase->resize(512, 308);
        ListBuilderDialogBase->setWindowIcon(qt_get_icon(image0_ID));
        ListBuilderDialogBase->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(ListBuilderDialogBase);
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        textLabel1 = new QLabel(ListBuilderDialogBase);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        vboxLayout1->addWidget(textLabel1);

        m_NotIncluded = new Q3ListBox(ListBuilderDialogBase);
        m_NotIncluded->setObjectName(QString::fromUtf8("m_NotIncluded"));

        vboxLayout1->addWidget(m_NotIncluded);


        hboxLayout->addLayout(vboxLayout1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        spacer3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacer3);

        m_buttonAdd = new QPushButton(ListBuilderDialogBase);
        m_buttonAdd->setObjectName(QString::fromUtf8("m_buttonAdd"));

        vboxLayout2->addWidget(m_buttonAdd);

        m_buttonRemove = new QPushButton(ListBuilderDialogBase);
        m_buttonRemove->setObjectName(QString::fromUtf8("m_buttonRemove"));

        vboxLayout2->addWidget(m_buttonRemove);

        spacer4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacer4);


        hboxLayout->addLayout(vboxLayout2);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        textLabel2 = new QLabel(ListBuilderDialogBase);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        vboxLayout3->addWidget(textLabel2);

        m_Included = new Q3ListBox(ListBuilderDialogBase);
        m_Included->setObjectName(QString::fromUtf8("m_Included"));

        vboxLayout3->addWidget(m_Included);


        hboxLayout->addLayout(vboxLayout3);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setMargin(0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(ListBuilderDialogBase);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout1->addWidget(buttonOk);

        buttonCancel = new QPushButton(ListBuilderDialogBase);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout1->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(ListBuilderDialogBase);
        QObject::connect(buttonCancel, SIGNAL(clicked()), ListBuilderDialogBase, SLOT(reject()));
        QObject::connect(buttonOk, SIGNAL(clicked()), ListBuilderDialogBase, SLOT(accept()));
        QObject::connect(m_buttonAdd, SIGNAL(clicked()), ListBuilderDialogBase, SLOT(addListItemSlot()));
        QObject::connect(m_buttonRemove, SIGNAL(clicked()), ListBuilderDialogBase, SLOT(removeListItemSlot()));
        QObject::connect(m_Included, SIGNAL(doubleClicked(Q3ListBoxItem*)), ListBuilderDialogBase, SLOT(removeListItemSlot()));
        QObject::connect(m_NotIncluded, SIGNAL(doubleClicked(Q3ListBoxItem*)), ListBuilderDialogBase, SLOT(addListItemSlot()));

        QMetaObject::connectSlotsByName(ListBuilderDialogBase);
    } // setupUi

    void retranslateUi(QDialog *ListBuilderDialogBase)
    {
        ListBuilderDialogBase->setWindowTitle(QApplication::translate("ListBuilderDialogBase", "Linguistica", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("ListBuilderDialogBase", "<b>Not included:</b>", 0, QApplication::UnicodeUTF8));
        m_buttonAdd->setText(QApplication::translate("ListBuilderDialogBase", "&Add -->", 0, QApplication::UnicodeUTF8));
        m_buttonAdd->setShortcut(QApplication::translate("ListBuilderDialogBase", "Alt+A", 0, QApplication::UnicodeUTF8));
        m_buttonRemove->setText(QApplication::translate("ListBuilderDialogBase", "<-- &Remove", 0, QApplication::UnicodeUTF8));
        m_buttonRemove->setShortcut(QApplication::translate("ListBuilderDialogBase", "Alt+R", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("ListBuilderDialogBase", "<b>Included:</b>", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("ListBuilderDialogBase", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("ListBuilderDialogBase", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
        Q_UNUSED(ListBuilderDialogBase);
    } // retranslateUi


protected:
    enum IconID
    {
        image0_ID,
        unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
    static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7a, 0x7a, 0xf4, 0x00, 0x00, 0x05,
    0xd1, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xc5, 0x97, 0x4d, 0x6c, 0x14,
    0x65, 0x18, 0xc7, 0x7f, 0xef, 0xec, 0x76, 0xba, 0x32, 0xed, 0x96, 0x2a,
    0xb0, 0x05, 0x83, 0x84, 0x03, 0xa5, 0x4d, 0x96, 0x5a, 0x08, 0x24, 0x64,
    0xa8, 0xb1, 0xb4, 0xe9, 0xd2, 0x95, 0x53, 0x2f, 0x10, 0x63, 0x34, 0x40,
    0xca, 0xcd, 0x70, 0xd2, 0xc4, 0x48, 0x22, 0x12, 0xc2, 0x45, 0x48, 0x34,
    0xc4, 0x70, 0x22, 0xe0, 0x05, 0x89, 0x70, 0xe0, 0x84, 0x4b, 0x5b, 0xbb,
    0x54, 0x84, 0x91, 0x50, 0x02, 0x58, 0x1a, 0x84, 0x0a, 0x89, 0x50, 0xa4,
    0x2d, 0x02, 0xf6, 0x63, 0x97, 0x2e, 0xd3, 0xee, 0xbe, 0x1e, 0x76, 0x66,
    0x3a, 0xb3, 0xb3, 0xad, 0x48, 0x62, 0x7c, 0x2e, 0x33, 0x79, 0xdf, 0x67,
    0x9e, 0x8f, 0xff, 0xf3, 0x39, 0xc2, 0x30, 0x0c, 0xfe, 0x4f, 0x52, 0x5e,
    0x94, 0xb1, 0x53, 0xd7, 0x65, 0xa7, 0xae, 0xcb, 0xff, 0xcc, 0x00, 0x5b,
    0xf8, 0x6c, 0x8a, 0x62, 0x86, 0x21, 0x00, 0xee, 0xed, 0x6e, 0x91, 0x1d,
    0x2e, 0xde, 0x42, 0x23, 0x5f, 0xda, 0x00, 0x5b, 0x80, 0x74, 0x29, 0x2b,
    0xa4, 0x2f, 0x2b, 0x2a, 0x38, 0xff, 0x44, 0x61, 0x65, 0xa3, 0x06, 0xc0,
    0xc5, 0x50, 0xe8, 0xdf, 0xea, 0x9b, 0xdd, 0x80, 0x98, 0x61, 0x88, 0x98,
    0x61, 0x08, 0xc1, 0xec, 0x9e, 0x24, 0x12, 0x09, 0xf1, 0xed, 0x3d, 0x85,
    0x9f, 0x1e, 0x0b, 0x3a, 0x75, 0x5d, 0xa6, 0x85, 0xe0, 0xf5, 0x81, 0x2d,
    0xf2, 0xd1, 0x81, 0x56, 0xb9, 0xa7, 0xa9, 0xe9, 0xa5, 0xc2, 0xe3, 0xcb,
    0x81, 0x86, 0xf6, 0x4a, 0xa2, 0x71, 0x8d, 0x8e, 0x22, 0x46, 0x74, 0xea,
    0xba, 0x4c, 0x24, 0x12, 0x62, 0x78, 0xc0, 0xa4, 0xbe, 0x2d, 0x4c, 0xb4,
    0xb6, 0x84, 0xfd, 0x87, 0xc6, 0xf9, 0xe2, 0xec, 0x14, 0x97, 0x4b, 0x4b,
    0x7d, 0xc8, 0xbd, 0x48, 0x48, 0x82, 0x85, 0x07, 0xf3, 0x76, 0x9c, 0x11,
    0x1c, 0xdd, 0x2c, 0x05, 0x69, 0x3a, 0x75, 0x5d, 0xba, 0x85, 0x4a, 0xe0,
    0x9b, 0x0f, 0x5b, 0x65, 0xa4, 0x5a, 0xe5, 0xda, 0xe9, 0x71, 0x96, 0x58,
    0xe7, 0xdb, 0x66, 0x09, 0xd9, 0x8b, 0x90, 0xcf, 0x00, 0x80, 0x93, 0x57,
    0xb3, 0x64, 0xd7, 0x57, 0xb0, 0xf4, 0xd2, 0x98, 0xe7, 0x7c, 0x65, 0xa3,
    0x46, 0x8d, 0xc8, 0x72, 0xfb, 0x5c, 0x9a, 0xb9, 0x72, 0xc5, 0x6d, 0xf0,
    0x3f, 0x91, 0x52, 0x0c, 0xa6, 0x6d, 0x5f, 0x9f, 0x15, 0x01, 0x73, 0xe6,
    0xb8, 0x53, 0xd7, 0xe5, 0xc3, 0x7d, 0x2d, 0x12, 0xe0, 0xd6, 0xb9, 0x34,
    0x00, 0x9b, 0xe6, 0x50, 0xee, 0xae, 0xa4, 0x67, 0x47, 0x37, 0xcf, 0x69,
    0x87, 0x02, 0xd0, 0x61, 0x7d, 0xf0, 0xe8, 0x40, 0xab, 0xa7, 0xbc, 0xa4,
    0xf5, 0x3e, 0x54, 0x57, 0x4e, 0xf7, 0xa0, 0x60, 0xa0, 0x27, 0x4d, 0x31,
    0xad, 0x6e, 0x85, 0x6e, 0x87, 0x6a, 0x9b, 0x34, 0x52, 0x4f, 0xb2, 0x3e,
    0x5e, 0x8f, 0x01, 0x76, 0xe6, 0x5f, 0x55, 0x55, 0x3a, 0xee, 0xce, 0xdc,
    0x6d, 0x59, 0x13, 0xe0, 0xba, 0xaa, 0x12, 0x8d, 0x6b, 0x28, 0x39, 0xc9,
    0xa2, 0xfe, 0x14, 0x30, 0x53, 0x2d, 0x6e, 0x81, 0x92, 0x19, 0xb8, 0xed,
    0x67, 0x7d, 0x5b, 0x98, 0x5c, 0x0e, 0xae, 0x9f, 0x1e, 0x9f, 0x0b, 0x80,
    0x7c, 0x0e, 0xc4, 0x0c, 0x43, 0xa0, 0xeb, 0x72, 0x38, 0xa7, 0xd2, 0xa1,
    0xeb, 0x52, 0x00, 0x27, 0xfa, 0x73, 0x00, 0xdc, 0x48, 0xa4, 0x89, 0x30,
    0x7b, 0xbc, 0xa5, 0xe5, 0xa9, 0x9b, 0xea, 0xdb, 0xc2, 0x94, 0x2f, 0x0c,
    0x30, 0x39, 0x3a, 0xe3, 0xbd, 0x6d, 0x68, 0xa1, 0x10, 0x4f, 0x12, 0x46,
    0xfa, 0x53, 0x3c, 0xaa, 0x2b, 0x27, 0xd2, 0x37, 0x91, 0x17, 0x64, 0x9a,
    0x73, 0xc6, 0x1a, 0x60, 0x55, 0x5c, 0xa3, 0x3f, 0x91, 0xcf, 0x8b, 0x37,
    0x2c, 0x05, 0x99, 0xb1, 0xac, 0xe3, 0xb9, 0x04, 0xc7, 0x29, 0x37, 0xaf,
    0x4d, 0x9e, 0x46, 0x24, 0x00, 0x72, 0x79, 0x10, 0x97, 0x5e, 0x1a, 0xf3,
    0x28, 0x2f, 0xd6, 0xa2, 0xed, 0x04, 0x5b, 0xb9, 0x31, 0x8f, 0xc0, 0xc3,
    0x7d, 0x2d, 0xb2, 0xb6, 0xa5, 0x0c, 0x69, 0x71, 0x49, 0xf2, 0x95, 0x33,
    0x12, 0x2d, 0xe3, 0xe1, 0x9a, 0x30, 0xeb, 0xb6, 0x56, 0xfa, 0x90, 0xf4,
    0x34, 0xa2, 0x98, 0x61, 0x88, 0x9c, 0x22, 0x88, 0xc6, 0xbd, 0x90, 0xee,
    0x6f, 0x6c, 0x94, 0xf5, 0x6d, 0x61, 0x1a, 0xda, 0x2b, 0x9d, 0xb3, 0x4e,
    0x5d, 0x97, 0x41, 0x55, 0xd0, 0x9f, 0x48, 0xb3, 0x68, 0x85, 0x4a, 0x6d,
    0x4b, 0x19, 0xc1, 0x50, 0x80, 0xe4, 0x88, 0xe0, 0xfc, 0x9f, 0x82, 0xda,
    0x96, 0x32, 0x56, 0xb7, 0x85, 0x39, 0x65, 0x4c, 0x31, 0x32, 0x60, 0xb2,
    0xe4, 0xea, 0x38, 0xc7, 0xb6, 0x3d, 0xf0, 0x21, 0xe8, 0xeb, 0x03, 0x8b,
    0xfb, 0x26, 0xc8, 0x46, 0xca, 0x9c, 0x0a, 0xe8, 0x55, 0x55, 0x3e, 0x78,
    0x5b, 0x65, 0xd1, 0xc7, 0x67, 0x3d, 0x68, 0x44, 0xe3, 0x1a, 0xe7, 0x0e,
    0x3f, 0xa5, 0x79, 0xd7, 0xab, 0x24, 0x07, 0x61, 0x78, 0x08, 0x2a, 0xaa,
    0x14, 0x20, 0xcb, 0xfd, 0x01, 0x93, 0x23, 0x77, 0x14, 0xe6, 0xe5, 0x72,
    0x28, 0xc0, 0x9b, 0xa6, 0xe9, 0x53, 0xec, 0x20, 0xf0, 0x51, 0x73, 0xb3,
    0xaf, 0x4e, 0x03, 0xc1, 0xfc, 0x51, 0x43, 0x7b, 0x25, 0xdb, 0x9b, 0x4b,
    0xb8, 0xd9, 0x95, 0xf2, 0xdc, 0x37, 0xb4, 0x57, 0x62, 0x4e, 0xe6, 0xe3,
    0x9d, 0x1c, 0xcc, 0x9f, 0xcd, 0x8f, 0x04, 0x19, 0x1f, 0x9e, 0xa6, 0xaa,
    0x6f, 0x82, 0xb5, 0xa6, 0xc9, 0x86, 0x4c, 0x86, 0xad, 0x7a, 0x09, 0x0b,
    0xa3, 0x21, 0x7e, 0x51, 0x55, 0x60, 0xa6, 0xac, 0x3d, 0x06, 0x68, 0x52,
    0xfa, 0xe2, 0x1b, 0x0c, 0x05, 0xb8, 0xa6, 0xaa, 0x9c, 0xba, 0x3c, 0xcd,
    0x8d, 0x84, 0xbf, 0xf6, 0x2f, 0x1c, 0xf9, 0x8b, 0x81, 0x9e, 0xb4, 0x53,
    0x72, 0x99, 0xf1, 0x1c, 0xa1, 0xee, 0x51, 0x16, 0xf5, 0xa7, 0x10, 0xe4,
    0x9b, 0x94, 0x04, 0x6e, 0xf7, 0xa4, 0xd9, 0xbd, 0x2b, 0x4c, 0x55, 0x4d,
    0x29, 0x23, 0x75, 0xe5, 0xd8, 0xe5, 0xee, 0x31, 0x60, 0x6f, 0x32, 0x29,
    0x2e, 0x86, 0x42, 0x34, 0xb4, 0x57, 0xf2, 0xe8, 0x40, 0xab, 0xd3, 0xfb,
    0xd7, 0x98, 0x26, 0x8b, 0xfb, 0x26, 0x8a, 0x36, 0x1e, 0x9b, 0x47, 0x00,
    0x23, 0xbf, 0x99, 0x8c, 0x8e, 0x4c, 0x53, 0x58, 0x62, 0xb6, 0x21, 0x7f,
    0x54, 0x9f, 0x14, 0x91, 0xbe, 0x09, 0x1a, 0x23, 0x92, 0x9a, 0x26, 0x0d,
    0xa5, 0x00, 0x05, 0x05, 0x60, 0x6f, 0x32, 0x29, 0x3e, 0x3b, 0x9e, 0x21,
    0x33, 0x96, 0x65, 0x70, 0x4f, 0x4c, 0x7e, 0x7f, 0x0f, 0x07, 0x36, 0x1b,
    0x3a, 0x9b, 0xec, 0x8f, 0x6d, 0x23, 0xee, 0x0f, 0x98, 0x54, 0x59, 0x9e,
    0xbb, 0xf9, 0xec, 0x7b, 0x9b, 0xff, 0xd7, 0xae, 0x14, 0xc1, 0x52, 0xa8,
    0xaa, 0x56, 0x3d, 0xa1, 0xf0, 0x54, 0xc1, 0xa1, 0x9f, 0x73, 0xc8, 0xac,
    0xe4, 0x9d, 0x65, 0x33, 0x89, 0xe3, 0x94, 0x67, 0x81, 0x11, 0xf6, 0xa4,
    0xdc, 0xdd, 0xd3, 0xe3, 0x74, 0xc6, 0xc2, 0x9e, 0x61, 0x37, 0x9f, 0x68,
    0x5c, 0x63, 0xa8, 0xae, 0x9c, 0x63, 0xdd, 0x53, 0xdc, 0xbd, 0x33, 0xcd,
    0x57, 0x15, 0x15, 0x0e, 0x8f, 0x53, 0x05, 0x07, 0xbb, 0xbb, 0x05, 0xe4,
    0x4b, 0x6e, 0xe7, 0xe6, 0x40, 0x21, 0xea, 0x45, 0x47, 0xb3, 0x9b, 0xdc,
    0x5e, 0xd9, 0x8a, 0x01, 0x56, 0xb7, 0x85, 0x79, 0x9e, 0xca, 0x21, 0x83,
    0x82, 0xb5, 0x96, 0x53, 0x1b, 0x32, 0x19, 0x07, 0x21, 0xdf, 0x4a, 0xb6,
    0xce, 0x34, 0x29, 0x7b, 0x2d, 0xe0, 0x28, 0x98, 0x6d, 0x3f, 0x34, 0x42,
    0x21, 0x3e, 0x7d, 0xaf, 0xd5, 0x49, 0xde, 0x4d, 0x86, 0x21, 0x86, 0xea,
    0xca, 0x19, 0x8e, 0x96, 0x01, 0xf0, 0x56, 0x7b, 0x25, 0xb5, 0x4d, 0x1a,
    0xf3, 0x23, 0x01, 0x8e, 0xff, 0x68, 0xf2, 0xdd, 0x5d, 0x51, 0x34, 0x9f,
    0xc4, 0xe7, 0x2e, 0x67, 0xa2, 0x71, 0x8d, 0x05, 0xcb, 0x4b, 0x39, 0x77,
    0xf8, 0xa9, 0x87, 0x59, 0x32, 0x03, 0xaf, 0xbd, 0x29, 0x09, 0xa0, 0x57,
    0x55, 0xd9, 0xde, 0x5c, 0x42, 0x7f, 0x22, 0x4d, 0xcc, 0x30, 0xc4, 0xb3,
    0xa3, 0x9b, 0x65, 0xd7, 0xef, 0x79, 0x71, 0x63, 0xc3, 0xd3, 0x54, 0x59,
    0x03, 0xec, 0x9a, 0xaa, 0xb2, 0xda, 0x15, 0x52, 0x8f, 0x01, 0x86, 0x61,
    0x38, 0x5e, 0xf6, 0x5a, 0x89, 0xf7, 0x7e, 0x43, 0x09, 0x52, 0xc2, 0x6d,
    0x6b, 0xf6, 0xbb, 0x33, 0xdc, 0x7e, 0x8f, 0x19, 0x86, 0xe8, 0xd0, 0x75,
    0x79, 0x5d, 0x55, 0x59, 0x5c, 0xad, 0x12, 0xb1, 0x12, 0xd1, 0xa6, 0xea,
    0x46, 0x8d, 0xdb, 0xd6, 0xf8, 0xbe, 0x18, 0x0a, 0xb1, 0x37, 0x99, 0x2c,
    0x3a, 0x53, 0x14, 0xb7, 0x55, 0xeb, 0x4c, 0x13, 0x53, 0x51, 0x38, 0x71,
    0x61, 0x8a, 0x5b, 0xd6, 0xd6, 0x63, 0xc3, 0x13, 0xb3, 0x6a, 0xdb, 0x96,
    0xd2, 0x69, 0x0d, 0x98, 0x7a, 0xcb, 0x33, 0xb7, 0xf4, 0xfa, 0xb6, 0x30,
    0x35, 0x1b, 0x35, 0x6a, 0x9b, 0x34, 0x7a, 0x55, 0x95, 0x79, 0xb9, 0xdc,
    0xac, 0xfb, 0xa1, 0x28, 0xfc, 0x33, 0x72, 0xa3, 0x51, 0xb5, 0xe6, 0x15,
    0x02, 0xa6, 0x24, 0x16, 0xc9, 0x3a, 0x0d, 0xc9, 0x9e, 0x13, 0xc1, 0x50,
    0xc0, 0x69, 0xcf, 0xee, 0xa4, 0x7b, 0xb0, 0xbe, 0x82, 0x77, 0xa3, 0x0a,
    0x4f, 0xee, 0x4d, 0x71, 0xb3, 0x2b, 0xc5, 0xaa, 0xb8, 0xc6, 0x0f, 0x83,
    0xc2, 0x09, 0x47, 0x61, 0x08, 0x7c, 0xb3, 0x60, 0xa4, 0xae, 0x1c, 0x99,
    0x93, 0xec, 0x5c, 0xa1, 0xf0, 0x3c, 0x95, 0xe5, 0x66, 0x57, 0x8a, 0x60,
    0x5b, 0x98, 0x55, 0x71, 0x8d, 0x1b, 0x89, 0x34, 0x53, 0x19, 0x9c, 0x9d,
    0xb0, 0x66, 0xb4, 0x45, 0xda, 0x61, 0x82, 0xfc, 0x5e, 0x30, 0xfc, 0x38,
    0x47, 0x30, 0xa8, 0x70, 0xb3, 0x2b, 0xc5, 0x26, 0x2b, 0x4c, 0x22, 0x5a,
    0xc6, 0xca, 0x8d, 0x1a, 0xcb, 0xf6, 0x77, 0xf9, 0xc2, 0xe0, 0x20, 0x60,
    0x7b, 0x71, 0x4d, 0x55, 0xf9, 0xa4, 0xa7, 0xc7, 0x33, 0x78, 0xec, 0xf7,
    0xa8, 0x65, 0x84, 0x11, 0x0a, 0x91, 0x16, 0x02, 0x4d, 0x4a, 0xf4, 0x4c,
    0x06, 0x01, 0x6c, 0x3b, 0xb6, 0x84, 0x2b, 0x27, 0xc7, 0x38, 0xd6, 0x3d,
    0xc5, 0x3a, 0xd3, 0xa4, 0x70, 0x6b, 0x72, 0x2b, 0x75, 0xdf, 0xf9, 0xf6,
    0x01, 0xb7, 0x72, 0xc0, 0xc9, 0x83, 0x98, 0x61, 0x88, 0x05, 0xcb, 0x4b,
    0xb9, 0xa2, 0xaa, 0xa4, 0x85, 0xa0, 0x65, 0x72, 0x92, 0x0d, 0x96, 0xf2,
    0x98, 0x61, 0x88, 0x3b, 0x17, 0x27, 0xb9, 0x91, 0x48, 0x13, 0xc0, 0xff,
    0xc7, 0xe4, 0x5e, 0xe3, 0x0a, 0x07, 0x92, 0xef, 0xdf, 0xd0, 0x07, 0x91,
    0xf5, 0x1c, 0xdc, 0x13, 0x93, 0xa3, 0x43, 0xd3, 0x98, 0x8a, 0xc2, 0xc1,
    0xee, 0x6e, 0x61, 0x2b, 0xb6, 0xf9, 0xe6, 0xed, 0x38, 0x23, 0x04, 0xf9,
    0x19, 0xb2, 0x21, 0x93, 0x29, 0x26, 0x8a, 0x98, 0x61, 0x88, 0x4d, 0x05,
    0x3b, 0xa5, 0x2f, 0x09, 0xe7, 0xa2, 0xc2, 0x6e, 0xf8, 0xb2, 0x3c, 0x6e,
    0xfa, 0x1b, 0x6c, 0x54, 0xf0, 0x7f, 0x13, 0xac, 0x88, 0xb0, 0x00, 0x00,
    0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

    switch (id) {
        case image0_ID:  { QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img); }
        default: return QPixmap();
    } // switch
    } // icon

};

namespace Ui {
    class ListBuilderDialogBase: public Ui_ListBuilderDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTBUILDERDIALOGBASE_H
