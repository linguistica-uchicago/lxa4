// Random string generator following a model of phonology
// Copyright © 2009 The University of Chicago
#ifndef MONTECARLO_H
#define MONTECARLO_H

class MonteCarlo;

#include <vector>
#include <QStringList>
#include <QString>
#include <Q3Dict>
#include "Parse.h"
#include "generaldefinitions.h"

//		This is a class that keeps track of unigram and bigram frequencies, and is
//		able to produce strings on the basis of those distributions.
//		The top level MonteCarlo keeps track of phone frequencies, and is
//		capable of setting up one MonteCarlo for *each* of its phones, so
//		that it can produce strings based on bigram frequencies. 
//		If we want that fancier kind, then the m_ModelType should be BIGRAM;
//		otherwise, it should be UNIGRAM.

class MonteCarlo
{
	QStringList			m_Keys;
	std::vector<double>		m_Values;
	int					m_Size;
	bool				m_ReadyForAction;

	Q3Dict<MonteCarlo>	m_MyBigrams;
	QString				m_MyFirstPhone;

public:
	
	eModelType			m_ModelType;


	MonteCarlo(int size);
	MonteCarlo(int size, QString MyFirstPhone );

	void						Dump				( Q3TextStream* );
	void						SetSize(int size)	{ m_Size = size; };
	int							GetSize()			{ return m_Size;};
	Q3Dict<MonteCarlo>*			GetMyBigrams()		{ return &m_MyBigrams; }
	void						StockDictionary		( QString key, double value, int i) { m_Keys.append (key); 
																			  m_Values [i] =  value; }

	void						Normalize			();
	

	QString						ReturnCharacter		(  );
	QString						ReturnCharacter		( QString PrecedingChar );
	CParse						ReturnString		( CParse& );
};

#endif // MONTECARLO_H
