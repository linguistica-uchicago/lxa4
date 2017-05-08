// Implementation of CCorpusWord methods
// Copyright © 2009 The University of Chicago
#include "CorpusWord.h"

#include "CompoundCollection.h"
#include "Linker.h"
#include "Stem.h"

//--------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------

CCorpusWord::CCorpusWord(CMiniLexicon* lex): CLParse( lex )
{
	m_morphemes.resize( m_PieceCount );

	m_updated = FALSE;
}


CCorpusWord::CCorpusWord(const CStringSurrogate& ssCorpusWord, CMiniLexicon* lex): CLParse( ssCorpusWord, lex )
{
	m_morphemes.resize( m_PieceCount );

	m_updated = FALSE;
}


CCorpusWord::CCorpusWord(CCorpusWord& CorpusWord): CLParse( CorpusWord, NULL )
{
	m_morphemes.resize( m_PieceCount );

	m_updated = FALSE;
}


CCorpusWord::CCorpusWord(const CLParse& LParse): CLParse( LParse, LParse.GetMyMini() )
{
	m_morphemes.resize( m_PieceCount );

	m_updated = FALSE;
}


CCorpusWord::CCorpusWord(const CParse& Parse, CMiniLexicon* lex): CLParse( Parse, lex )
{
	m_morphemes.resize( m_PieceCount );

	m_updated = FALSE;
}


CCorpusWord::~CCorpusWord()
{}



//-----------------------------------------------------------------
// Overloaded operators
//-----------------------------------------------------------------

void CCorpusWord::operator= (const CCorpusWord& RHS)
{
	CopyParse(RHS);
  
	m_morphemes.resize( m_PieceCount );
}


void CCorpusWord::Copy (CCorpusWord& RHS)
{
	CopyParse(RHS);
	
	m_morphemes.resize( m_PieceCount );
}


//--------------------------------------------------
// Public accessor methods
//--------------------------------------------------

CLParse* CCorpusWord::GetMorpheme( int i ) const
{ 
	if( i > 0 && i <= Size() ) return m_morphemes[i-1]; 
	else return NULL; 
}


eLxaClass CCorpusWord::GetMorphemeType( int i ) const 
{ 
	if( GetMorpheme(i) == NULL ) return NOTHING;
	else return GetMorpheme(i)->GetType();
}


//--------------------------------------------------
// Public mutator methods
//--------------------------------------------------

void CCorpusWord::CutRightBeforeHere( int i )
{
	CParse::CutRightBeforeHere(i);

	m_morphemes.resize( m_PieceCount );

	Q_ASSERT( m_LengthOfPieceVector >= Size() );

	for( int j = Size() - 1; j > 0; j-- )
	{
		if( m_Pieces[j+1] > i ) m_morphemes.insert( j, m_morphemes[j-1] );
	}
}


void CCorpusWord::MergePieces( int i )
{
	for (int j = i; j < m_PieceCount - 1; ++j)
		m_morphemes.insert( j, m_morphemes[j+1] );
	m_morphemes.remove( m_PieceCount - 1 );

	CParse::MergePieces(i);
	m_morphemes.resize( m_PieceCount );
}


void CCorpusWord::SetMorpheme( int i, CLParse* pMorph ) 
{ 
	if( i > 0 && i <= Size() ) m_morphemes.insert( i - 1, pMorph ); 
}


void CCorpusWord::SimplifyParseStructure()
{
	CParse::SimplifyParseStructure();
	
	m_morphemes.resize( m_PieceCount );
}


void CCorpusWord::CopyParseStructure( CCompound* other )
{
	CParse::CopyParseStructure( *other );

	StemSet* pStems;
	CLinker* pLinker;

	m_morphemes.resize( m_PieceCount );

	for( int i = 1; i <= other->Size(); i++ )
	{
		pStems = other->GetComponent(i);
		if( pStems ) m_morphemes.insert( i - 1, pStems->at(0) );
		else 
		{
			pLinker = other->GetLinker(i);
			if( pLinker ) m_morphemes.insert( i - 1, pLinker );
			else m_morphemes.remove(i);
		}
	}
}


void  CCorpusWord::SetLengthOfPieceVector(int i)
{ 
	m_LengthOfPieceVector = i; 
	m_morphemes.resize( m_PieceCount ); 
}
