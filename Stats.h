// Corpus word frequency histogram
// Copyright © 2009 The University of Chicago
#ifndef STATS_H
#define STATS_H

#include <Q3ValueList>
#include <QString>
#include <QMap>

class CStats 
{

private:
	class LinguisticaMainWindow*		m_parent;
	QMap<QString, Q3ValueList<int> >	m_StringMap;
//	QStringList					m_Corpus;
	int						m_CorpusSize;

	long int			CorpusDistribution(QString &word) const;



public:
	CStats();
	CStats(LinguisticaMainWindow*);

	virtual		~CStats(); 


	void		readCorpus();
	void		output() const;
 

};

#endif // STATS_H
