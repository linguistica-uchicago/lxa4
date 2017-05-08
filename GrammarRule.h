// CGrammarRule, CTerminalRule, CWildcardRule classes
// Copyright © 2009 The University of Chicago
#ifndef GRAMMARRULE_H
#define GRAMMARRULE_H

#include "Parse.h"

class CGrammarRule : public CParse
{
protected:
	int		m_SortIndex;
	int		m_Index;

public:
	CGrammarRule();
	virtual ~CGrammarRule();

	virtual CStringSurrogate	GetLHS();
	virtual CParse				GetRHS();
	virtual QString				Display();

	virtual bool				isTerminal() { return FALSE; }
	
	void						SetSortIndex( int n ) { m_SortIndex = n; }
	int							GetSortIndex() const { return m_SortIndex; }	
	void						SetIndex( int n ) { m_Index = n; }
	int							GetIndex() const {  return m_Index; }
};


// Terminal Rule
//==========================================

class CTerminalRule : public CGrammarRule
{
protected:
	CParse  m_leftSide;

public:
	CTerminalRule( QString leftSide );
	virtual ~CTerminalRule();

	virtual CStringSurrogate	GetLHS();
	virtual CParse				GetRHS();
	virtual QString				Display();

	virtual bool				isTerminal() { return TRUE; }
};


// Wild Card Rule
//==========================================

class CWildCardRule : public CGrammarRule
{
protected:
	int m_Width;

public:
	CWildCardRule( QString, int );
	virtual ~CWildCardRule();

	virtual CStringSurrogate	GetLHS();
	virtual CParse				GetRHS();
	virtual QString				Display();

	virtual bool				isTerminal() { return TRUE; }
};

#endif // #define GRAMMARRULE_H
