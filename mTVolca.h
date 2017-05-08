// mTVolca class
// Copyright © 2009 The University of Chicago
#ifndef MTVOLCA_H
#define MTVOLCA_H

// See the cMT class in cMT.h for an overview of the Machine Translation code.

#include <QString>
#include <QMap>

typedef QMap<int, int> IntToInt;
typedef QMap<int, IntToInt*> IntToIntToInt;
typedef QMap<int, double> IntToDouble;
typedef QMap<int, IntToDouble*> IntToIntToDouble;

class mTVolca {
public:
	class cMT* m_myMT;
	QString m_projectDirectory;
	QString m_language1FileName;
	QString m_language2FileName;

	// Volca data.

	QMap<QString, int> m_language1Words;
	QMap<QString, int> m_language2Words;
	QMap<int, QString> m_language1WordIndex;
	QMap<int, QString> m_language2WordIndex;
	int m_language1TotalWords;
	int m_language2TotalWords;

	// sentence data.

	int m_countOfSentences;
	QMap<int, QMap<int, int>*> m_language1Sentences;
	QMap<int, QMap<int, int>*> m_language2Sentences;
	QMap<int, QMap<int, int>*> m_sentenceAlignments;

	// T pair index.

	QMap<int, QMap<int, double>*> m_fastWordsPairs;
	QMap<int, QMap<int, double>*> m_fastWordsSoftCounts;
public:
	// construction/destruction.

	mTVolca(cMT* driver, QString project_dir);
	virtual ~mTVolca();

	// disable default-construction, copy
private:
	mTVolca();
	mTVolca(const mTVolca& x);
	mTVolca& operator=(const mTVolca& x);
public:
	void initVolList();
	void readSentences();
	void setFastSearchPairsForT();
	void clearSentenceViterbiAlignment();
};

#endif // MTVOLCA_H
