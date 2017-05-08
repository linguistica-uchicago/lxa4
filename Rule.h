// CRule class
// Copyright © 2009 The University of Chicago
#ifndef RULE_H
#define RULE_H

#include <QString>
#include "Parse.h"
#include "TemplateCollection.h"
#include "LParse.h"

enum RULETYPE {SUBSTITUTION, DELETION, SUBSTITUTION2FOR1};       
class CSignatureCollection;

struct  SigPair
{

	QString  Key;
	CParse	Sig1;
	CParse	Sig2;
	int		Count;
	CParse	Sig1Stems;
};
 
class CRule: public CLParse
{	QString					Input;
	QString					Output;
	char					LeftEnv;
	char					RightEnv;
	RULETYPE				Type;
	CParse					Examples;
	int						RuleCount;
	TCollection<CLParse>	Sigs1;
	TCollection<CLParse>	Sigs2;



public:
	CRule	();
	CRule (CRule& Rule); 
	CRule	(CRule*);
	CRule(	RULETYPE, QString& strRule);
	~CRule();
	
//	void	Display(CListCtrl&, int position);

 
	QString GetInput();
	QString GetOutput();

	void	SetInput(QString);
	void	SetOutput (QString);
	QString	GetLeftEnvString();
	char	GetLeftEnv();
	void	SetLeftEnv(char);
	QString	GetRightEnvString();
	char	GetRightEnv();
	void	SetRightEnv(char);
	RULETYPE GetType();
	void	SetType(RULETYPE);
	int		ExampleLength();
	void	AddExample(QString);
	void	SetExamples(QString& ex);
	
	CParse&  GetExamples();
	int		GetRuleCount();
	CParse	Display();
	QString SpellOutRule();
	void	Clear();
	void	IncrementRuleCount(int n = 1);
	
	float GetSortingQuantity() const; // number of stems that use it.
};

#endif // RULE_H
