// Implementation of CGrammarRule methods
// Copyright © 2009 The University of Chicago
#include "GrammarRule.h"

#include "Config.h"
#include <QString>
#include "StringSurrogate.h"
#include "Parse.h"
#include "Typedefs.h"

CGrammarRule::CGrammarRule()
{}


CGrammarRule::~CGrammarRule()
{}


CSS CGrammarRule::GetLHS()
{
	return GetPiece(1);
}


CParse CGrammarRule::GetRHS()
{
	CParse rightHandSide;
	for( int i = 2; i <= m_PieceCount; i++ )
	{
		rightHandSide.Append( GetPiece(i) );
	}

	return rightHandSide;
}


QString CGrammarRule::Display()
{
	QString String,
			Separator = "+";
	
	String = GetPiece(1).Display() + " -> " + GetPiece(2).Display();
	for( int i =  3; i <= m_PieceCount; i++ )
	{
		String += Separator;
		String += GetPiece(i).Display();
	}

 	return String;
}



// Terminal Rule
//==========================================

CTerminalRule::CTerminalRule( QString leftSide )
{
	m_leftSide = CSS( leftSide );
}


CTerminalRule::~CTerminalRule()
{}


CSS CTerminalRule::GetLHS()
{
	return m_leftSide.GetKey();
}


CParse CTerminalRule::GetRHS()
{
	CParse rightSide( GetKey() );
	for( int i = 0; i <= rightSide.GetKeyLength(); i++ )
	{
		rightSide.CutNFromTheLeft(i);
	}

	return rightSide;
}


QString CTerminalRule::Display()
{
	QString String,
			Separator = "+";
	
	String = m_leftSide.Display() + " -> " + QString( GetKey()[0] );
	for( int i = 1; i < GetKeyLength(); i++ )
	{
		String += Separator;
		String += QString( GetKey()[i] );
	}

 	return String;
}


// Wild Card Rule
//==========================================

CWildCardRule::CWildCardRule( QString leftSide, int width )
{
	Append( leftSide );
	m_Width = width;
}


CWildCardRule::~CWildCardRule()
{}


CSS CWildCardRule::GetLHS()
{
	return GetKey();
}


CParse CWildCardRule::GetRHS()
{
	int i;
	QString rightSide = "";
	for( i = 0; i < m_Width; i++ )
	{
		rightSide += GRAMMAR_RULE_WILD_CARD;
	}

	CSS ss( rightSide );
	CParse parse( ss );
	for( i = 0; i <= parse.GetKeyLength(); i++ )
	{
		parse.CutNFromTheLeft(i);
	}

	return parse;
}


QString CWildCardRule::Display()
{
	QString String,
			Separator = "+";
	
	String = GetLHS().Display() + " -> " + GRAMMAR_RULE_WILD_CARD;
	for( int i = 1; i < m_Width; i++ )
	{
		String += Separator;
		String += GRAMMAR_RULE_WILD_CARD;
	}

 	return String;
}
