/********************************************************************************
** Form generated from reading ui file 'canvasdialogbase.ui'
**
** Created: Thu Nov 5 16:02:33 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CANVASDIALOGBASE_H
#define UI_CANVASDIALOGBASE_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CanvasDialogBase
{
public:

    void setupUi(QDialog *CanvasDialogBase)
    {
        if (CanvasDialogBase->objectName().isEmpty())
            CanvasDialogBase->setObjectName(QString::fromUtf8("CanvasDialogBase"));
        CanvasDialogBase->resize(600, 480);

        retranslateUi(CanvasDialogBase);

        QMetaObject::connectSlotsByName(CanvasDialogBase);
    } // setupUi

    void retranslateUi(QDialog *CanvasDialogBase)
    {
        CanvasDialogBase->setWindowTitle(QApplication::translate("CanvasDialogBase", "Linguistica : Canvas Dialog", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CanvasDialogBase);
    } // retranslateUi

};

namespace Ui {
    class CanvasDialogBase: public Ui_CanvasDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVASDIALOGBASE_H
