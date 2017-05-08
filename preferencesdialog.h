// Preferences dialog
// Copyright © 2009 The University of Chicago
#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include "ui_preferencesdialogbase.h"

#include <QColorDialog>
#include <Q3WhatsThis>
#include <QRadioButton>
#include <QPushButton>
#include <Q3ListView>
#include <QCheckBox>
#include <Q3ListBox>
#include <QStringList>
#include <QString>
#include <QRegExp>
#include <Q3Dict>
#include <QColor>
#include <QFont>
#include <Qt>

class CLPreferences;
typedef QMap<QString,QString>	StringToString;

class PreferencesDialog : public QDialog, public Ui::PreferencesDialogBase
{
    Q_OBJECT
public:
	PreferencesDialog( CLPreferences*, StringToString* params = 0,
				QWidget* parent = 0, Qt::WindowFlags fl = 0 );
	~PreferencesDialog();

	QFont* GetMHFont( QString );
	QColor* GetMHColor( QString );

	void RedrawPreviews();

	void LoadPreferences( QString );
	void SavePreferences( QString );

protected:

protected slots:
	// Created in Qt Designer 
    virtual void mhListBoxHighlightedSlot();
    virtual void mhBoldCheckBoxClickedSlot();
    virtual void mhItalicCheckBoxClickedSlot();
    virtual void mhUnderlineCheckBoxClickedSlot();
    virtual void mhColorButtonClickedSlot();
    virtual void dsfFontButtonClickedSlot();
    virtual void loadPrefsButtonClickedSlot();
    virtual void savePrefsButtonClickedSlot();
    virtual void notificationsCheckBoxClickedSlot();
    virtual void sigDelimiterChangedSlot(const QString&);
    virtual void resetValuePushButtonClickedSlot();
    virtual void resetAllValsPushButtonClickedSlot();
    virtual void paramListItemRenamedSlot(Q3ListViewItem*, int, const QString&);
    virtual void help();
    virtual void importRulesButtonClickedSlot();
    virtual void exportRulesButtonClickedSlot();
    virtual void makeLowerCaseCheckBoxToggled(bool);
    virtual void removeNumbersCheckBoxToggled(bool);
    virtual void removePrecedingPunctCheckBoxToggled(bool);
    virtual void removeInternalPunctCheckBoxToggled(bool);
    virtual void removeFollowingPunctCheckBoxToggled(bool);
    virtual void addNewReplacementButtonPressed();
    virtual void moveUpButtonPressed();
    virtual void moveDownButtonPressed();
    virtual void removeReplacementButtonPressed();
    virtual void scrubListBoxSelectionChanged();
    virtual void replaceStringsChanged();
    virtual void precedingPunctLineEditTextChanged(const QString&);
    virtual void internalPunctLineEditTextChanged(const QString&);
    virtual void followingPunctLineEditTextChanged(const QString&);
	virtual void newComboButtonClickedSlot();
	virtual void removeComboButtonClickedSlot();
	virtual void comboListBoxSelectionChangedSlot();
	virtual void joinWithoutDashRadioButtonClickedSlot();
	virtual void joinWithDashRadioButtonClickedSlot();
	virtual void doNotJoinRadioButtonClickedSlot();

	// Hyphenated compound words
	virtual void removeHyphenCheckBoxClickedSlot();
	virtual void includeFullHyphenatedWordOnlyRadioButtonClickedSlot();
	virtual void includeSubstringsOfHyphenatedWordOnlyRadioButtonClickedSlot();
	virtual void includeFullHyphenatedWordAndSubstringsRadioButtonClickedSlot();

private:
	CLPreferences*		m_Prefs;
	StringToString*		m_DefaultParams;
	StringToString*		m_replacements;

	bool m_initialized;

	void init();
	void initParams();
};

#endif // PREFERENCESDIALOG_H
