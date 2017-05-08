// Editing preferences
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include "preferencesdialog.h"
#include "LPreferences.h"
#include "Lexicon.h"

void LinguisticaMainWindow::preferencesEditSlot()
{
	PreferencesDialog prefDlg(&m_preferences,
				m_lexicon->GetDefaultParams(), this);
	// Save preferences in case we cancel
	CLPreferences::data_type saved_prefs = m_preferences.data();

	if (prefDlg.exec() == QDialog::Accepted)
		// User clicked 'OK', update settings
		updateAllViewsSignal();
	else
		// User clicked 'Cancel', revert to old preferences
		m_preferences.data() = saved_prefs;

	m_preferences.StorePrefs();
}
