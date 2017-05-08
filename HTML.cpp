// Implementation of log file formatting helpers
// Copyright © 2009 The University of Chicago
#include "HTML.h"

#include <QString>
#include "StringSurrogate.h"
#include "Parse.h"
#include "Signature.h"

QString MakeTableHeader(QString header ){  return "<th> "+ header + "</th> " ;}
QString LargeTitle (QString title)  	{ return "\n  <h1>" + title + "</h1>  \n ";}
QString SmallTitle (QString title)  	{ return "\n  <h2>" + title + "</h2>  \n ";}
QString SmallerTitle (QString title)	{ return "\n  <h3>" + title + "</h3>  \n ";}
QString TableData(QString stuff)   		{ return "<td>" + stuff + "</td>";}
QString TableData(CStringSurrogate stuff) { return "<td>" + stuff.Display() + "</td>";}
QString TableData(CParse& stuff)   		{ return "<td>" + stuff.Display() + "</td>";}
QString TableData(CSignature* pSig)     { return " <td>" + pSig->Display() + "</td>";}
QString TableData(int value)      		{ return "<td>" + QString("%1").arg(value,10) + "</td>";}
QString TableData(double value)    		{ return "<td>" + QString("%1").arg(value,10) + "</td>";}
QString TableData()						{ return "<td>" + QString(" ")+ "</td>";}

const QString StartTable 	("\n\n<table border=\"1\"> \n");
const QString EndTable 		("\n\n</table> \n");
const QString StartTableRow ("\n<tr>");
const QString EndTableRow 	("</tr>");
