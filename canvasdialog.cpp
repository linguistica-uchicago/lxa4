// Implementation of CanvasDialog methods
// Copyright © 2009 The University of Chicago
#include "canvasdialog.h"

#include <Q3VBoxLayout>
#include <QPixmap>

CanvasDialog::CanvasDialog(QWidget* parent, Qt::WindowFlags fl)
	: QDialog( parent, 0, false, fl ), Ui::CanvasDialogBase(),
	m_canvasDialogLayout(), // initialized below
	m_canvas(new Q3Canvas(width(), height())),
	m_canvasView() // initialized below
{
	setupUi(this);


	m_canvasView = new Q3CanvasView(m_canvas, this);
	m_canvasDialogLayout = new Q3VBoxLayout(this, 11, 6);
	m_canvasDialogLayout->addWidget(m_canvasView);
	m_canvas->update();
}

CanvasDialog::~CanvasDialog() { delete m_canvas; }

void CanvasDialog::saveToFile( const QRect& rectangle, const QString& fileName, const char* format )
{
	QPixmap image = QPixmap::grabWidget( m_canvasView,
										 rectangle.left() - 5,
										 rectangle.top() - 5,
										 rectangle.width() + 10,
										 rectangle.height() + 10 );

	image.save( fileName, format );
}


void CanvasDialog::clear()
{
	Q3CanvasItemList list = m_canvasView->canvas()->allItems();
	Q3CanvasItemList::Iterator it = list.begin();
	for( ; it != list.end(); ++it )
	{
		if ( *it ) delete *it;
	}
}

