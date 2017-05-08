// Driver to output a CWordCollection to GUI
// Copyright © 2009 The University of Chicago
#ifndef GUICLASSES_H
#define GUICLASSES_H

#include "generaldefinitions.h"

template<class K, class V> class QMap;

class GUIWordCollection {
	class CWordCollection* m_Words;
	class CMiniLexicon* m_MiniLexicon;
	enum eWordDisplayMode m_DisplayMode;
public:
	GUIWordCollection(class CMiniLexicon*, class CWordCollection*);
	void ListDisplay(class Q3ListView*,
			QMap<class QString, class QString>* filter,
			bool bAnalyzedWordsOnly);
};

#endif // GUICLASSES_H
