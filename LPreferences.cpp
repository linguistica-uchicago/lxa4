// Implementation of CLPreferences methods
// Copyright © 2009 The University of Chicago
#include "LPreferences.h"
#include "Config.h"
#include <QTextStream>
#include <QIODevice>
#include <QSettings>
#include <QFile>
#include <QFont>
#include <QMap>

namespace {
	QString assert_nonempty(QString s)
	{
		Q_ASSERT(!s.isEmpty());
		return s;
	}
}

// construction/destruction.

CLPreferences::CLPreferences(QSettings* settings)
	: registry(settings), prefs_filename(), m()
{ LoadPrefs(); }

CLPreferences::CLPreferences(QString filename)
	: registry(), prefs_filename(assert_nonempty(filename)), m()
{ LoadPrefs(); }

CLPreferences::~CLPreferences()
{ StorePrefs(); }

// string preference values.

QString CLPreferences::GetPreference(QString key) const
{
	const data_type::const_iterator p = m.find(key);

	if (p != m.end())
		return p->second;
	else
		return QString();
}

void CLPreferences::SetPreference(QString key, QString value)
{
	if (value.isEmpty())
		// XXX. Warning: after SetPreference(k, v),
		// this means GetPreference(k) is not necessarily v.
		m[key] = QString("EMPTY");
	else
		m[key] = value;
}

void CLPreferences::RemovePreference(QString key)
{ m.erase(key); }

// integer preference values.

int CLPreferences::GetIntPreference(QString key) const
{
	bool ok;
	const int rv = GetPreference(key).toInt(&ok);
	if (!ok)
		return -1;
	return rv;
}

void CLPreferences::SetIntPreference(QString key, int value)
{ SetPreference(key, QString::number(value)); }

// font preference values.

QFont CLPreferences::GetFontPreference(QString key) const
{
	const QString family_key = QString("%1_Family").arg(key);
	const QString size_key = QString("%1_PointSize").arg(key);
	const QString bold_key = QString("%1_Bold").arg(key);
	const QString italic_key = QString("%1_Italic").arg(key);
	const QString ul_key = QString("%1_Underline").arg(key);

	const QString family = GetPreference(family_key);
	const int size = GetIntPreference(size_key);
	const int bold = GetIntPreference(bold_key);
	const int italic = GetIntPreference(italic_key);
	const int ul = GetIntPreference(ul_key);

	QFont font;
	if (!family.isEmpty())
		font.setFamily(family);
	if (size > 0) {
		font.setPointSize(size);
	} else if (size != -1) {
		// XXX. don’t complain
	}
	if (bold != -1)
		font.setBold(bold != 0);
	if (italic != -1)
		font.setItalic(italic != 0);
	if (ul != -1)
		font.setUnderline(ul != 0);
	return font;
}

void CLPreferences::SetFontPreference(QString key, QFont f)
{
	const QString family_key = QString("%1_Family").arg(key);
	const QString size_key = QString("%1_PointSize").arg(key);
	const QString bold_key = QString("%1_Bold").arg(key);
	const QString italic_key = QString("%1_Italic").arg(key);
	const QString ul_key = QString("%1_Underline").arg(key);

	SetPreference(family_key, f.family());
	SetIntPreference(size_key, f.pointSize());
	SetIntPreference(bold_key, f.bold());
	SetIntPreference(italic_key, f.italic());
	SetIntPreference(ul_key, f.underline());
}

void CLPreferences::RemoveFontPreference( QString key )
{
	const QString family_key = QString("%1_Family").arg(key);
	const QString size_key = QString("%1_PointSize").arg(key);
	const QString bold_key = QString("%1_Bold").arg(key);
	const QString italic_key = QString("%1_Italic").arg(key);
	const QString ul_key = QString("%1_Underline").arg(key);

	// XXX. optimize by taking advantage of proximity of keys

	RemovePreference(family_key);
	RemovePreference(size_key);
	RemovePreference(bold_key);
	RemovePreference(italic_key);
	RemovePreference(ul_key);
}

// string list preference values.

namespace {
	const QChar string_list_delimiter = QChar(FILTER_BASE);
}

void CLPreferences::GetStringListPreference(QString key,
		QStringList* out) const
{
	Q_ASSERT(out != 0);
	const QString value = GetPreference(key).trimmed();

	if (value == "EMPTY")
		out->clear();
	else
		*out = value.split(string_list_delimiter);
}

void CLPreferences::SetStringListPreference(QString key,
		const QStringList& value)
{ SetPreference(key, value.join(string_list_delimiter)); }

// dictionary preference values.

namespace {
	const QChar definition_sep = ':';
}

void CLPreferences::GetDictionaryPreference(QString key,
		QMap<QString, QString>* out) const
{
	Q_ASSERT(out != 0);

	const QString value = GetPreference(key).trimmed();
	for (int pos = 0, nextpos; pos != value.size(); pos = nextpos) {
		nextpos = value.indexOf(string_list_delimiter, pos);
		if (nextpos == -1)
			// last entry
			nextpos = value.size();
		else
			++nextpos;

		const int colon_pos = value.indexOf(definition_sep, pos);
		if (colon_pos == -1 || colon_pos >= nextpos)
			// no colon in entry!
			// XXX. don’t complain.
			continue;

		const QString definend =
			value.mid(pos, colon_pos - pos);
		const QString definition =
			value.mid(colon_pos + 1, nextpos - 1 - colon_pos - 1);
		(*out)[definend] = definition;
	}
}

void CLPreferences::SetDictionaryPreference(QString key,
	const QMap<QString, QString>& in)
{
	QMap<QString, QString>::const_iterator iter = in.begin();
	if (iter == in.end()) {
		SetPreference(key, "");
		return;
	}

	Q_ASSERT(!iter.key().contains(definition_sep));
	QString val;
	val.append(iter.key());
	val.append(definition_sep);
	val.append(iter.value());

	for (++iter; iter != in.end(); ++iter) {
		Q_ASSERT(!iter.key().contains(definition_sep));
		val.append(string_list_delimiter);
		val.append(iter.key());
		val.append(definition_sep);
		val.append(iter.value());
	}
	SetPreference(key, val);
}

// mass storage and retrieval.

void CLPreferences::LoadPrefs()
{
	// XXX. Preferences can only be read from one source at a time.
	Q_ASSERT((registry != 0 ? 1 : 0) +
			(prefs_filename.isEmpty() ? 0 : 1) <= 1);

	if (registry != 0) {
		registry->beginGroup(
			"/linguistica.uchicago.edu/Linguistica/Preferences");
		m.clear();
		foreach (QString key, registry->allKeys())
			m[key] = registry->readEntry(key);
		registry->endGroup();
	}

	if (!prefs_filename.isEmpty())
		load_prefs_from_file(prefs_filename);
}

void CLPreferences::StorePrefs() const
{
	if (registry != 0) {
		registry->beginGroup(
			"/linguistica.uchicago.edu/Linguistica/Preferences");
		registry->remove("");
		for (data_type::const_iterator iter = m.begin();
				iter != m.end(); ++iter) {
			if (iter->first.isEmpty() || iter->second.isEmpty())
				continue;
			registry->setValue(iter->first, iter->second);
		}
		registry->endGroup();
	}
	
	if (!prefs_filename.isEmpty())
		store_prefs_to_file(prefs_filename);
}

// save/restore preference data.

namespace {
	const QChar prefs_file_kv_sep = '=';
}

void CLPreferences::load_prefs_from_file(const QString& filename)
{
	Q_ASSERT(!filename.isEmpty());
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
		return;
	QTextStream in(&file);
	in.setCodec(QTextCodec::codecForName("UTF-8"));

	m.clear();
	while (!in.atEnd()) {
		const QString line = in.readLine();
		const int eq_pos = line.indexOf(prefs_file_kv_sep);
		m[line.left(eq_pos)] = line.mid(eq_pos + 1);
	}
}

void CLPreferences::store_prefs_to_file(const QString& filename) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		return;
	QTextStream out(&file);
	out.setCodec(QTextCodec::codecForName("UTF-8"));

	for (data_type::const_iterator iter = m.begin();
			iter != m.end(); ++iter) {
		if (iter->first.isEmpty() || iter->second.isEmpty())
			continue;
		Q_ASSERT(!iter->first.contains(prefs_file_kv_sep));

		// format: key=value\n
		out << iter->first << prefs_file_kv_sep << iter->second;
		out << endl;
	}
}
