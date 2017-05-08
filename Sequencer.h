// CSequencer, sentenceItem classes
// Copyright © 2009 The University of Chicago
#ifndef SEQUENCER_H
#define SEQUENCER_H

class CSequencer;
class sentenceItem;

#include <Q3SortedList>
#include <QString>
#include <QMap>

typedef QMap<int, QString> IntToString;
typedef QMap<int, double> IntToDouble;
typedef QMap<QString, int> StringToInt;
typedef QMap<QString, double> StringToDouble;
typedef Q3SortedList<sentenceItem> SortedSentences;

class CSequencer 
{

private:
	// Parameters
	int									m_K; 
	int									m_resultK;
	int									m_maxlineintrain;
	int									m_maxlineintest;

private:
	class LinguisticaMainWindow* m_parent;
	
	QString								separator;

	StringToInt							m_bigrams;
	StringToInt							m_trigrams; 

	StringToInt							m_bigramsbase;
	StringToInt							m_trigramsbase; 

	StringToDouble						m_bigramprob;
	StringToDouble						m_trigramprob;

	int									m_totalbigrams;
	int									m_totaltrigrams;
	int									m_totalbigramsbase;
	int									m_totaltrigramsbase;


public:
	CSequencer();
	CSequencer(LinguisticaMainWindow*);

	~CSequencer(); 


	void		readCorpus();
	void		sequenceASentence(int&, int&, QString inputSentence = QString("")); 
	void		sequenceASentence2(int&, int&, QString inputSentence = QString("")); 
	void		sequenizeFromABigram(QString, double, StringToInt&, int, int, SortedSentences&, int); 
	void		sequenize2(StringToInt, int, int, SortedSentences&, int); 
	void		sequencerTestAFile(); 

};



class sentenceItem
{
public:

	double					m_value;
	QString					m_key; 
	StringToInt				m_bagofwords;
	IntToString				m_historystrings;
	IntToDouble				m_historyscores;
	int						m_stepnumber;
	int						m_numberofwordsinsentence; // only used for sequencerize2

public:
	sentenceItem(){};
	~sentenceItem(){};

	sentenceItem(double value, QString& key, StringToInt& bagofwords, int stepnumber,IntToString& historystrings, IntToDouble& historyscores) {m_value = value; \
								m_key = key; m_bagofwords = bagofwords; m_stepnumber = stepnumber; m_historystrings = historystrings; m_historyscores = historyscores;\
								m_historystrings.insert(m_stepnumber, m_key); m_historyscores.insert(m_stepnumber, m_value); m_numberofwordsinsentence = 0; };


	sentenceItem(sentenceItem* other) {m_value = other ->m_value; \
								m_key = other ->m_key; m_bagofwords = other ->m_bagofwords; \
								m_stepnumber = other ->m_stepnumber; \
								m_historystrings = other ->m_historystrings; \
								m_historyscores = other ->m_historyscores;\
								m_numberofwordsinsentence = other ->m_numberofwordsinsentence;
								};



	bool	operator<(const sentenceItem& another) {return !(m_value > another.m_value); };
	bool	operator==(const sentenceItem& another) {return (m_value == another.m_value);};



};

#endif // SEQUENCER_H
