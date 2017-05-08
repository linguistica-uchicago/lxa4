// “Linguistica : Canvas Dialog” dialog
// Copyright © 2009 The University of Chicago
#ifndef CANVASDIALOG_H
#define CANVASDIALOG_H

#include <QDialog>
#include "ui_canvasdialogbase.h"

#include <Q3VBoxLayout>
#include <Q3Canvas>
#include <Qt>

class CanvasDialog : public QDialog, private Ui::CanvasDialogBase {
	Q_OBJECT
	Q3VBoxLayout* m_canvasDialogLayout;
public:
	Q3Canvas* m_canvas;
	Q3CanvasView* m_canvasView;
public:
	// construction/destruction.

	CanvasDialog(QWidget* parent = 0, Qt::WindowFlags fl = 0);
	~CanvasDialog();

	// disable copy
private:
	CanvasDialog(const CanvasDialog& x);
	CanvasDialog& operator=(const CanvasDialog& x);
public:
	/// save image to file
	void saveToFile(const QRect& rectangle,
		const QString& filename, const char* format);
	/// clear canvas
	void clear();
};

#endif // CANVASDIALOG_H
