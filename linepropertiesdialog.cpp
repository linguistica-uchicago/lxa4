// Implementation of old FSA line properties dialog
// Copyright © 2009 The University of Chicago
#include "linepropertiesdialog.h"
#include <qmap.h>
#include <qstring.h>
#include <qnamespace.h>
#include <q3canvas.h>
#include <qdialog.h>

typedef QMap<QString,int>						StringToInt;

LinePropertiesDialog::LinePropertiesDialog( QWidget* parent,
							Qt::WindowFlags fl )
	: QDialog( parent, 0, false, fl ), Ui::LinePropertiesDialogBase()
{ setupUi( this ); }

void LinePropertiesDialog::exec(Q3CanvasItem* item)
{
	if (item == 0)
		return;

//	DiagramLine* ThisLine = static_cast<DiagramLine*>(item);

//	const bool IsPrefix = ThisLine->m_MyMorphology->m_IsPrefix;

//	this->FromStateNumber->setText(
//		QString::number(ThisLine->m_FromWhichState));
//	this->ToStateNumber->setText(
//		QString::number(ThisLine->m_ToWhichState));

//	const QMap<QString, QString>& morphemes = ThisLine->m_Morphemes;
//	int i = 0;
//	for (QMap<QString, QString>::const_iterator iter = morphemes.begin();
//			iter != morphemes.end(); ++iter, ++i) {
//		QString Line = iter.key();

//		if (IsPrefix)
//			Line = ThisLine->m_MyMorphology->Reverse(Line);
//		this->Morphemes->insertItem(Line, i);
//	}

	static_cast<void>(QDialog::exec());
}
