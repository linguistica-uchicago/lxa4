// Dialog to display analyzed corpus
// Copyright © 2009 The University of Chicago
#ifndef CORPUSVIEWDIALOG_H
#define CORPUSVIEWDIALOG_H

#include <QDialog>
#include "ui_corpusviewdialogbase.h"

#include <Qt>

class CLexicon;

class CorpusViewDialog : public QDialog, private Ui::CorpusViewDialogBase
{
    Q_OBJECT

	QStringList* m_left;
	QStringList* m_right;

	bool m_scrolling;

	int m_lx, m_ly, m_rx, m_ry;

	CLexicon* m_pLexicon;

protected: 
	void init();
	void setRightStyle( QString style );

public:
	CorpusViewDialog( QStringList* left, QStringList* right,
				QWidget* parent = 0, Qt::WindowFlags fl = 0 );
	CorpusViewDialog( CLexicon* pLexicon, QWidget* parent = 0,
						Qt::WindowFlags fl = 0 );

public slots:

	void showMarkedUpText(bool);
	void moveRightView(int,int);
	void moveLeftView(int,int);
	void wordWrap(bool);

};

#endif // CORPUSVIEWDIALOG_H
