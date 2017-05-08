// Implementation of the CStem class’s word functions.
// Copyright © 2009 The University of Chicago
#include "Stem.h"

#include <Q3TextStream>
#include "MiniLexicon.h"
#include "Signature.h"
#include "Prefix.h"
#include "Suffix.h"
#include "StringFunc.h"

// Get the number of stems
//
// Returns:
//    int - 0, 1, or 2

int      CStem::GetNumberOfStems() const
{
  int count = m_NumberOfStems;
  if (count < 2 && m_Stem2Loc ) { count = 2; }
  return count;
}


// Find out if this word has a prefix
//
// Returns:
//    bool - true if a prefix has been
//    marked

bool CStem::HasAPrefix() const
{
  if (m_PrefixLoc > 0) return true;
  else return false;
}


// Increment the marked location of the suffix

void CStem::IncrementSuffixLocs()
{
  if (m_SuffixLoc) m_SuffixLoc++;
}


// Find out if this word has a marked
// suffix
//
// Returns:
//    bool - true if there is a
//    marked suffix

bool CStem::HasASuffix() const
{
  if (m_SuffixLoc > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


// Shift the stem/suffix boundary n spaces
// to the right
//
// Parameters:
//    n - number of spaces to shift, a
//    negative value is legal and shifts
//    to the left

void CStem::ShiftStemSuffixBoundary (int n) // how many positions to the right
{
//  QString f = "fixador";
// Q_ASSERT (CStringSurrogate(m_Key,0,GetKeyLength()) != CStringSurrogate(f.unicode(),0,f.length()) );
  CStringSurrogate ssSuffix;

  if ( n >= 0 )
  {
    if ( m_SuffixLoc == 0)
    {
      Q_ASSERT (FALSE);
      return;
    }

    ssSuffix = GetPiece( m_SuffixLoc );

    if ( ssSuffix.GetLength() < (int) n )
    {
      Q_ASSERT (FALSE);
      return;
    }
    if ( ssSuffix.GetLength() == (int) n ) // changed Oct 2002
    {
      ClearRootSuffixSplit();
      m_SuffixLoc = 0;
    }
    else
    {
      m_Pieces[m_StemLoc] += n;
    }

  }
  else // shift to the left...
  {
    if ( m_SuffixLoc == 0 )
    {
      m_StemLoc = 1;        // this is too simple -- prefixes --
      m_SuffixLoc = m_StemLoc + 1;
      CutRightBeforeHere ( GetKeyLength() + n  ); // sept 28 2002
    }
    else
    {
      m_Pieces[m_StemLoc] += n;
    }
  }
}
// Shift the prefix/stem boundary n spaces
// to the left
//
// Parameters:
//    n - number of spaces to shift, a
//    negative value is legal and shifts
//    to the right

void CStem::ShiftPrefixStemBoundary (int n) // how many positions to the left
{

  CStringSurrogate ssPrefix;

  if ( n >= 0 )
  {
    if ( m_PrefixLoc == 0)
    {
      Q_ASSERT (FALSE);
      return;
    }

    ssPrefix = GetPiece( m_PrefixLoc );

    if ( ssPrefix.GetLength() < (int) n )
    {
      Q_ASSERT (FALSE);
      return;
    }
    if ( ssPrefix.GetLength() == (int) n ) // changed Oct 2002
    {
      ClearPrefixStemSplit();
      m_PrefixLoc = 0;
    }
    else
    {
      m_Pieces[m_StemLoc] -= n;
    }

  }
  else // negative number means shift to the right
  {	  
    if ( m_PrefixLoc == 0 )
    {
      m_StemLoc = 2;       
      m_PrefixLoc = 1;
      CutRightBeforeHere ( -1 *n  ); // sept 28 2002
    }
    else
    {
      m_Pieces[m_PrefixLoc] += -1 * n;
    }
  }
}

// Get the marked stem of the word
//
// Returns:
//    CStringSurrogate - a surrogate string
//    of the stem

CStringSurrogate  CStem::GetStem( )
{
    if (m_strStem.GetKeyLength() > 0) {
        return CStringSurrogate(m_strStem);
    }
    if (m_StemLoc) {
        return GetPiece( m_StemLoc );
    }
  else
    return CStringSurrogate();
}


// Get the marked suffix of the word
//
// Returns:
//    CStringSurrogate - a surrogate string
//    of the suffix

CStringSurrogate CStem::GetSuffix() const
{

 if (m_strSuffix.GetKeyLength() > 0) {
        return CStringSurrogate (m_strSuffix);
    }
 if (m_SuffixLoc) {
    return GetPiece( m_SuffixLoc );
}
  else
    return CStringSurrogate();
}


// Get the marked prefix of the word
//
// Returns:
//    CStringSurrogate - a surrogate string
//    of the prefix

CStringSurrogate CStem::GetPrefix() const
{
  if (m_PrefixLoc)
    return GetPiece( m_PrefixLoc );
  else
    return CStringSurrogate();
}


// Attach a new prefix signature
//
// Parameters:
//    pSig = pointer to new signature

void CStem::AttachPrefixSignature( CSignature* pSig )
{
	if( m_pPrefixSignature && m_pPrefixSignature != pSig )
	{
		m_pPrefixSignature->DetachWord( this, eDo_Not_Call_Words );
	}
	m_pPrefixSignature = pSig;
}


// Attach a new suffix signature
//
// Parameters:
//    pSig = pointer to new signature

void CStem::AttachSuffixSignature(CSignature* pSig)
{
  if (m_pSuffixSignature && m_pSuffixSignature != pSig)
  {
    m_pSuffixSignature->DetachWord (this, eDo_Not_Call_Words);
  }
  m_pSuffixSignature = pSig;
}


// Attach a new stem and attach this word
// to the stem
//
// Parameters:
//    pStem - point to new stem

void CStem::AttachWordAndSuffixalStem(CStem* pStem)
{

  if (m_pStem && m_pStem != pStem)
  {
    m_pStem->RemoveWordFromWordPtrList( this );
    m_pStem->DetachSuffix ( m_pSuffix );
  }

  m_pStem = pStem;
  if (pStem)
  {
      pStem->AddWord (this); // it checks whether this is on pStem's list yet.


      m_pStem->IncrementWordCount();
 
      m_pStem->IncrementCorpusCount( GetCorpusCount() - 1 );
  }
	  
  }

void CStem::AttachWordAndPrefixalStem(CStem* pStem)
{
	if (m_pStem && m_pStem != pStem)
	{
		m_pStem->RemoveWordFromWordPtrList( this );
		m_pStem->DetachPrefix( m_pPrefix ); //todo this is causing a problem which
		//I can't identify -- but I think it should be there.  jg
	}

	m_pStem = pStem;
	if (pStem)
	{
		if( pStem->AddWord (this) )
		{
			m_pStem->IncrementWordCount();
			m_pStem->IncrementCorpusCount( GetCorpusCount() - 1 );
		}
	}
}


// Attach a new stem and new prefix and
// attach this word to both
//
// Parameters:
//    pNewStem - the new stem
//    pNewPrefix - the new prefix

void CStem::AttachWordStemAndPrefix(CStem* pNewStem, CPrefix* pNewPrefix)
{

  // Sending message to the old Prefix that it's being dropped.
  if (m_pPrefix)
  {
    m_pPrefix->IncrementCorpusCount  ( -GetCorpusCount() );
    m_pPrefix->RemoveFromStemPtrList ( m_pStem );
    m_pPrefix->RemoveStemString  ( m_pStem->GetKey() );
  }

  AttachWordAndPrefixalStem(pNewStem); // Also increments stem counts

  m_pPrefix = pNewPrefix;
  m_pStem->AddPrefix( m_pPrefix );
  m_pPrefix->AddStem( m_pStem );

  m_pPrefix->IncrementUseCount(); // July 2003
  m_pPrefix->IncrementCorpusCount( GetCorpusCount() - 1 );
//***

}


// Attach a new stem and new suffix and
// attach this word to both
//
// Parameters:
//    pNewStem - the new stem
//    pNewSuffix - the new suffix

void CStem::AttachWordStemAndSuffix(CStem* pNewStem, CSuffix* pNewSuffix)
{

  // Sending message to the old Suffix that it's being dropped.
  if (m_pSuffix)
  {
    m_pSuffix->IncrementCorpusCount  ( -GetCorpusCount() );
    m_pSuffix->RemoveFromStemPtrList ( m_pStem );
    m_pSuffix->RemoveStemString  ( m_pStem->GetKey() );
  }

  AttachWordAndSuffixalStem(pNewStem); // Also increments stem counts

  m_pSuffix = pNewSuffix;
  m_pStem->AddSuffix( m_pSuffix );
  m_pSuffix->AddStem( m_pStem );

  m_pSuffix->IncrementUseCount(); // July 2003
  m_pSuffix->IncrementCorpusCount( GetCorpusCount() - 1 );
//***

}



// Find out if this is a valid word
//
// Returns:
//    bool - true if the word is valid

bool    CStem::IsValid() const
{
  Q_ASSERT (m_StemType >= 0);
  Q_ASSERT (m_PieceCount < 2 || m_Pieces[1] > 0 );
  Q_ASSERT ( m_Pieces[m_PieceCount] == GetKeyLength() );
  if ( m_StemType < 0 ) return false;


  QString test, appnd;
  for (int i = 1; i <= m_PieceCount; i++)
  {
    CStringSurrogate SS = GetPiece(i);
    LxStrCpy( &SS, appnd, SS.GetLength() );
    test += appnd;
  }

  return true; // TODO: ???? what's being tested
}


// Delete the affix/stem separations

void    CStem::DeleteFactorization()
{
  SimplifyParseStructure();
  m_PrefixLoc = 0;
  m_StemLoc = 0;
  m_SuffixLoc = 0;
}


// Clear the pointers to stem, suffix, and
// signatures

void CStem::ClearPointers()
{
	m_pStem = NULL;
	m_pSuffix = NULL;
	m_pPrefix = NULL;
	m_pSuffixSignature = NULL;
	m_pPrefixSignature = NULL;
}


// Get the successor frequency
//
// Parameters:
//    n - the position before the break
//
// Returns:
//    int - the successor frequency

int CStem::SF(int n ) const // TODO: more descriptive name
{
  CStringSurrogate ssPrefix;
  if( n <= GetKeyLength() )
  {
    ssPrefix  = Left(n);
// TODO: uncomment lines when CNode and CLexicon are available
//    CNode* pNode =  m_Lexicon->GetWords()->GetTrie()->SearchForPrefix ( ssPrefix, Result );
//    return pNode->GetWidth( );
    return 0;
  }
  else return -1;   //TODO: is this change OK??
}


// Delete the prefix

void CStem::DeletePrefix()
{

  Q_ASSERT ( m_PrefixLoc == 1 );

  int PrefixLength = ThisPieceLength (m_PrefixLoc);
  int Length = GetKeyLength() - PrefixLength;

  m_AllocatedLength = GetKeyLength() - PrefixLength +1 ;
  QChar* NewKey = new QChar[ m_AllocatedLength];
  LxStrCpy(m_Key, NewKey, Length-PrefixLength, PrefixLength );
  m_PieceCount--;


  int* NewPieces = new int [ m_PieceCount - 1 ];
  for (int i = 1; i <= m_LengthOfPieceVector; i++)
  {
    NewPieces[i-1] = m_Pieces[i] - m_Pieces[1];
  }

  delete m_Pieces; m_Pieces = NewPieces;
  delete [] m_Key; m_Key = NewKey;

  m_LengthOfPieceVector--;
  m_StemLoc--;
  m_SuffixLoc--;
  if (m_Stem2Loc) { m_Stem2Loc--; }
  m_pPrefix = NULL;
}


// Get a CParse copy of this word in broken
// form
//
// Returns:
//    CParse - <stem>.+.<suffix>

CParse CStem::DisplayBrokenForm()
{
  QString plus = "+";
  if ( m_BrokenForm == NULL)
  {
    m_BrokenForm = new CParse();
    if ( m_pSuffix )
    {
      m_BrokenForm->Append ( GetStem()  );
      m_BrokenForm->Append ( plus );
      m_BrokenForm->Append ( GetSuffix() );
    }
    else
    {
      m_BrokenForm->Append ( CStringSurrogate(m_Key,0,m_KeyLength) );
    }
  }

  return *m_BrokenForm;
}


void CStem::OutputWord( Q3TextStream& outf, int index )
{
	QString pieces = "";

	for ( int j = 1; j <= Size(); j++ )
	{
		pieces += GetPiece(j).Display( m_pMyMini->GetOutFilter() ) + " ";
	}
	pieces = pieces.left( pieces.length() - 1 );

	outf << "  ";

	outf.setf(2);
	outf.width(5);
	outf << index + 1;
	outf << "   ";

	outf.unsetf(2); 
	outf.width(4);
	outf << Size();
	outf << "   ";

	outf.setf(2);
	outf.width(40);
	outf << pieces;
	outf << "   ";

	outf.unsetf(2);
	outf.width(12);
	outf << GetCorpusCount();
	outf << "   ";

	outf.width(10);
	outf << GetPrefixLoc();
	outf << "   ";

	outf.width(8);
	outf << GetStemLoc();
	outf << "   ";

	outf.width(10);
	outf << GetSuffixLoc();
	outf << "   ";

	if( GetSuffixLoc() == 0 )
	{
		if( GetPrefixLoc() == 0 ) outf << "NONE";
		else if( GetPrefixSignature() )
		{
			outf << GetPrefixSignature()->Display( '.', m_pMyMini->GetOutFilter() ) << " ";
		}
		else outf << "NONE";
	}
	else if( GetSuffixSignature() )
	{
		outf << GetSuffixSignature()->Display( '.', m_pMyMini->GetOutFilter() ) << " ";
	}
	else outf << "NONE";

	outf << endl;
}



bool CStem::IsAnalyzed()
{
	if (m_pSuffixSignature) return TRUE;
	if (m_pPrefixSignature) return TRUE;
	return FALSE;	
}

