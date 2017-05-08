// Implementation of CLParse methods
// Copyright © 2009 The University of Chicago
#include "LParse.h"

#include "StringFunc.h"
using linguistica::corpus_count;

//--------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------


/**
	Constructs an empty CLParse. <kbd>mini</kbd> is the mini-lexicon
	that contains this parse.
 */
CLParse::CLParse( CMiniLexicon* mini )
	: CParse(), corpus_count(),
	m_DoNotParse(false),
	m_DoomFlag(false),
	m_Index(0),
	m_SortIndex(0),
	m_Trigrams(),
	m_AlphabetizedForm(),
	m_pMyMini(mini) { }

/**
	Constructs a CLParse copy of a single QChar. <kbd>c</kbd> is the QChar
	to be copied. <kbd>mini</kbd> is the mini-lexicon that contains this 
	parse.
 */
CLParse::CLParse(const QChar& c, CMiniLexicon* mini)
	: CParse(c), corpus_count(),
	m_DoNotParse(false),
	m_DoomFlag(false),
	m_Index(0),
	m_SortIndex(0),
	m_Trigrams(),
	m_AlphabetizedForm(),
	m_pMyMini(mini) { }

/**
	Constructs a CLParse copy of a CParse. <kbd>Parse</kbd> is the parse to be
	copied. <kbd>mini</kbd> is the mini-lexicon that contains this parse.
 */
CLParse::CLParse(const CParse& Parse, CMiniLexicon* mini)
	: CParse(Parse), corpus_count(),
	m_DoNotParse(false),
	m_DoomFlag(false),
	m_Index(0),
	m_SortIndex(0),
	m_Trigrams(),
	m_AlphabetizedForm(),
	m_pMyMini(mini) { }

/**
	Constructs a CLParse copy from a pointer to a CParse. <kbd>pParse</kbd> is the parse to be
	copied. <kbd>mini</kbd> is the mini-lexicon that contains this parse.
 */
CLParse::CLParse(const CParse* pParse, CMiniLexicon* mini)
	: CParse(*pParse), corpus_count(),
	m_DoNotParse(false),
	m_DoomFlag(false),
	m_Index(0),
	m_SortIndex(0),
	m_Trigrams(),
	m_AlphabetizedForm(),
	m_pMyMini(mini) { }

/**
	Constructs a CLParse copy of a CStringSurrogate. <kbd>SS</kbd> is the surrogate to be
	copied. <kbd>mini</kbd> is the mini-lexicon that contains this parse.
 */
CLParse::CLParse(const CStringSurrogate& SS, CMiniLexicon* mini)
	: CParse(SS), corpus_count(),
	m_DoNotParse(false),
	m_DoomFlag(false),
	m_Index(0),
	m_SortIndex(0),
	m_Trigrams(),
	m_AlphabetizedForm(),
	m_pMyMini(mini) { }

/**
	Constructs a copy of another CLParse. <kbd>LParse</kbd> is the other CLParse to be
	copied.
 */
CLParse::CLParse(CLParse& LParse)
	: CParse(LParse), corpus_count(LParse),
	m_DoNotParse(LParse.m_DoNotParse),
	m_DoomFlag(LParse.m_DoomFlag),
	m_Index(0),
	m_SortIndex(0),
	m_Trigrams(new CParse(*LParse.m_Trigrams)),
	m_AlphabetizedForm(),
	m_pMyMini(LParse.m_pMyMini) { }

/**
	Destroys this CLParse.
 */
CLParse::~CLParse()
{ delete m_Trigrams; }

/**
	Constructs a copy of another CLParse. <kbd>LParse</kbd> is the other CLParse to be
	copied.
 */
CLParse& CLParse::operator=(const CLParse& LParse)
{
	if (&LParse == this) return *this;

	CParse::operator=(LParse);
	corpus_count::operator=(LParse);

	m_DoNotParse = LParse.m_DoNotParse;
	m_DoomFlag = LParse.m_DoomFlag;

	Q_ASSERT(m_Trigrams == 0 ||
		m_Trigrams != LParse.m_Trigrams);
	delete m_Trigrams;
	m_Trigrams = new CParse(*LParse.m_Trigrams);

	m_AlphabetizedForm.clear();
	m_pMyMini = LParse.m_pMyMini;

	return *this;
}


//-----------------------------------------------------------------
// Other methods
//-----------------------------------------------------------------


// Prepare this word for input
//
// Parameters:
//		LowerCaseFlag - if true, all characters
//		are set to lower case

/**
	Replaces and removes different punctuation marks and makes other
	changes to prepare the parse for input into a collection. <kbd>LowerCaseFlag</kbd> should
	be set to <i>TRUE</i> if the characters of the parse should be made lower case. 
	<kbd>punctuation</kbd> is a list of punctuation marks to be handled.
 */

void	CLParse::PrepareWordForInput( bool LowerCaseFlag, QString punctuation )  
{
	int		Length = GetKeyLength();
//	int		count = 0;
	int		i, z, loc;
	QString ellipsis = "...",
			dash = "--";
	QChar	apostrophe = '\'',
			period = '.',
			space = ' ';

	if( punctuation == "EMPTY" ) punctuation = "";

	// Nov 4 1999: deal with 3+ periods at word edges, or between
	//	words without white spaces (Tom Sawyer has the former).
	//  Clearly we don't want to get rid of periods inside abbrevations
	//	like U.S.A., but 3+ periods will get treated as a single
	//	punctuation with no internal structure; let's call it
	//	'&'. 

	// if it's a pure number, just delete it.
	// This is a bad solution regarding syntax, of course,
	// so this is just temporary --


/*	for( i=0; i < Length; i++ )
	{
		
	}*/

	//  dealing with "..." 
	for (i = 0; i < Length-3; i++)
	{
		// TODO: not sure if this is the correct 
		// change, are we looking for any occurrence 
		// of "..." or just at the beginning of m_Key?
		loc = LxStrCmp( m_Key, ellipsis, 3, 3); 
		if ( loc == 0  ) 
		{				
			CutRightBeforeHere( loc );
			if ( loc < Length-3 )
			{
				CutRightBeforeHere( i+3 );
			}
		}
	}
	// dealing with Dash '--'

	for (i = 0; i < Length-2; i++)
	{
		if ( m_Key[i] == '-' && m_Key[i+1] == '-' )
		{
			if ( i > 0  ) 
			{				
				CutRightBeforeHere( i );
			}
			if ( i < Length-2 )
			{
				CutRightBeforeHere( i+2 );
			}		
		}

	}



	if (LowerCaseFlag)
	{
		// make lower case;
		LxStrLwr ( m_Key, GetKeyLength() );
	}

	// do nothing to a '--' (if that's all it is)
	if ( LxStrCmp( m_Key, dash, 2, 2 ) == 0 ) 
	{
		return; 
	}

	// these wrongly break up numbers, don't forget, and currency amounts

	if (Length > 2) {
		if ( m_Key[Length-2] != apostrophe &&
			 ( punctuation.find( m_Key[Length-2] ) > -1 ||
			   ( punctuation.length() == 0 && m_Key[Length-2].isPunct() ) ) )
		{	
			CutRightBeforeHere (Length-2);
			if (Length > 3) {					// because the brown corpus has things like " jr.," 
				if ( ( punctuation.find( m_Key[Length-3] ) > -1 ||
			           ( punctuation.length() == 0 && m_Key[Length-3].isPunct() ) ) ) 
				{
					CutRightBeforeHere (Length - 3);
				}
			}
		}
	}
	
	for ( z = 1; z < 3; z++)
	{
		if (Length > 1) {
			if ( m_Key[Length-z] != apostrophe &&
				 ( punctuation.find( m_Key[Length-z] ) > -1 ||
			       ( punctuation.length() == 0 && m_Key[Length-z].isPunct() ) ) )
			{	
				CutRightBeforeHere (Length-z);		 
			}
		
		
  			if ( punctuation.find( m_Key[0] ) > -1 ||
			     ( punctuation.length() == 0 && m_Key[0].isPunct() ) ) 	
			{
				CutRightBeforeHere( 1 );
			}	 
		}
	}
	// The following could be done better in an earlier loop, but it needs
	// to be done: if a Piece of the word now begins with a hyphen, cut the hyphen off:
	for ( z = 1; z <= Size(); z++ ) //PieceCount; z++)
	{
		if ( m_Key[m_Pieces[z-1]] == '-' && ThisPieceLength(z) > 1 ) 
		{
			CutRightBeforeHere (m_Pieces[z-1]+1);
		}
	}

	return ;
}

// Get the trigrams for this LParse
//
// Returns:
//		CParse* - a pointer to the trigrams

/**
	Returns the trigrams of this LParse.
 */
CParse* CLParse::GetTrigrams()
{
	return m_Trigrams;
}

/**
	Calculates the trigrams of this LParse.
 */
void CLParse::CalculateTrigrams()
{
	if( m_Trigrams ) delete m_Trigrams;
	m_Trigrams = new CParse();
	m_Trigrams->FindAlphabetizedTrigrams( m_Key, m_KeyLength );
}


// Compare the number of matches between
// the trigrams of this and those of another 
// LParse
//
// Parameters:
//		Other - the other parse
//
// Returns:
//		int - the number of matches

/**
	Returns the number of matches of trigrams in this
	CLParse and the trigrams of another. <kbd>Other</kbd> is
	the other CLParse whose trigrams will be compared.
 */
int	CLParse::CompareTrigrams( CLParse& Other )
{
	CalculateTrigrams();
	return 	GetTrigrams()->CountOverlapAlphabetized( *Other.GetTrigrams() );
}
