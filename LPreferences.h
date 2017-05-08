// key/value user settings service
// Copyright © 2009 The University of Chicago
#ifndef LPREFERENCES_H
#define LPREFERENCES_H

class CLPreferences;

#include <map>
#include <QString>
template<class K, class V> class QMap;

/// A CLPreferences object maintains a list of key/value pairs
/// representing parameters for Linguistica’s various algorithms.
///
/// Settings can be read from and written to a QSettings object
/// (for transparently remembering their values in the Windows
/// registry or a dotfile in the user’s home directory), a
/// named file (for importing or exporting preferences to share
/// them), or both.
///
/// Settings are read on construction and written on destruction
/// of the preferences object.  One can also explicitly request
/// a read or write of preferences using the LoadPrefs or
/// StorePrefs method.
///
/// The values of all parameters can be saved into memory and
/// restored using the data() method.  Example:
///
///	QSettings settings
///	CLPreferences prefs(&settings);
///	// Unless do_something_to() calls StorePrefs(), the
///	// following block has no effect on prefs.
///	{
///		CLPreferences::data_type saved = prefs.data();
///		do_something_to(prefs);
///		// oops! back that out:
///		prefs.data() = saved;
///	}
class CLPreferences {
public:
	typedef std::map<QString, QString> data_type;
private:
	// where to read/write settings for long-term storage
	/// pointer to a handle for a Windows Registry-style
	/// setting storage service.  Unused if null.
	class QSettings* registry;
	/// filename for an “exported settings” file to use.
	/// Unused if empty.
	QString prefs_filename;

	// Linguistica parameters
	data_type m;
public:
	// construction/destruction.

	/// preferences stored in *settings
	explicit CLPreferences(QSettings* settings);
	/// preferences stored in named file
	explicit CLPreferences(QString filename);
	/// save preferences to long-term storage
	~CLPreferences();
private:
	// disable default-construction and copy.
	CLPreferences();
	CLPreferences(const CLPreferences& x);
	CLPreferences& operator=(const CLPreferences& x);
public:

	// string preference values.

	QString GetPreference(QString key) const;
	void SetPreference(QString key, QString value);
	void RemovePreference(QString key);

	// integer preference values.

	/// result is -1 on error
	int GetIntPreference(QString key) const;
	void SetIntPreference(QString key, int value);
	void RemoveIntPreference(QString key) { RemovePreference(key); }

	// font preference values.

	class QFont GetFontPreference(QString key) const;
	void SetFontPreference(QString key, class QFont value);
	void RemoveFontPreference(QString key);

	// StringList preference values.

	void GetStringListPreference(QString key,
		class QStringList* out) const;
	void SetStringListPreference(QString key,
		const class QStringList& value);

	// dictionary preference values.

	void GetDictionaryPreference(QString key,
		QMap<QString, QString>* out) const;
	/// requires: no key in val.keys() contains a colon
	void SetDictionaryPreference(QString key,
		const QMap<QString, QString>& val);

	// mass storage and retrieval.

	void LoadPrefs();
	void StorePrefs() const;

	// export to file.

	void load_prefs_from_file(const QString& filename);
	/// requires: no key in m contains an equal sign
	void store_prefs_to_file(const QString& filename) const;

	// save/restore preference data.

	data_type& data() { return m; }
	const data_type& data() const { return m; }
};

#endif // LPREFERENCES_H
