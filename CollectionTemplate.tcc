// Implementation of TCollection methods
// Copyright © 2009 The University of Chicago
#ifndef COLLECTIONTEMPLATE_TCC
#define COLLECTIONTEMPLATE_TCC

#include "CollectionTemplate.h"

#include <memory>
#include "Trie.h"
#include "Parse.h"
#include "LParse.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "linguisticamainwindow.h" 
#include "CompareFunc.h"

template<class T>
TCollection<T>::TCollection()
{
	m_CorpusCount			= 0;
	m_DeletePointers		= TRUE;
	m_DeletionArray			= NULL;
	m_HashHasChangedFlag	= FALSE;
	m_MemberName			= QString::null;
	m_PointerArray			= NULL;
	m_pLexicon				= NULL;
	m_pMiniLex				= NULL;
	m_pReverseTrie			= NULL;
	m_pTerminalNodeArray	= NULL;
	m_SortArray				= NULL;
	m_SortValidFlag			= 0;
	m_SortStyle				= KEY;
	m_TotalUseCount			= 0;
}


template<class T>
TCollection<T>::TCollection(CMiniLexicon* Mini, QString MemberName)
	: CTrie(),
	m_CorpusCount(0),
	m_DeletePointers(true),
	m_DeletionArray(),
	m_HashHasChangedFlag(false),
	m_MemberName(MemberName),
	m_PointerArray(),
	m_pLexicon((Mini != 0) ? Mini->GetLexicon() : 0),
	m_pMiniLex(Mini),
	m_pReverseTrie(),
	m_pTerminalNodeArray(),
	m_SortArray(),
	m_SortValidFlag(false),
	m_SortStyle(KEY),
	m_TotalUseCount(0.0) { }

template<class T>
TCollection<T>::TCollection( CLexicon* Lex, QString MemberName )
{
	m_CorpusCount			= 0;
	m_DeletePointers		= TRUE;
	m_DeletionArray			= NULL;
	m_HashHasChangedFlag	= FALSE;
	m_MemberName			= MemberName;
	m_PointerArray			= NULL;	
	m_pLexicon				= Lex;
	m_pMiniLex				= NULL;
	m_pReverseTrie			= NULL;
	m_pTerminalNodeArray	= NULL;
	m_SortArray				= NULL;
	m_SortValidFlag			= 0;
	m_SortStyle				= KEY;
	m_TotalUseCount			= 0;

}


template<class T>
TCollection<T>::~TCollection()
{
	if ( m_PointerArray )      { delete [] m_PointerArray; m_PointerArray = NULL;  }
	if ( m_SortArray )         { delete [] m_SortArray; m_SortArray = NULL;  }
	if ( m_DeletionArray)      { delete [] m_DeletionArray; m_DeletionArray = NULL; }
	if ( m_pTerminalNodeArray ) { delete [] m_pTerminalNodeArray; m_pTerminalNodeArray = NULL; }
	if ( m_pReverseTrie )       { delete m_pReverseTrie; m_pReverseTrie = NULL; }
}

template<class T>
T*  TCollection<T>::operator<<( CParse* pParse )
// Good for everything except CSignatures, which need punctuation.
{
	CNode*            pTerminal;
	int               Result;
	QString           Key;
	CStringSurrogate  cssKey;

	cssKey = pParse->GetKey();
	pTerminal = Insert (cssKey, &Result);
	if (Result == 1) {
		std::auto_ptr<T> morpheme(new T(pParse));
		morpheme->SetIndex(GetCount() - 1);
		pTerminal->SetPointer(morpheme.release());
	}
	T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());

	// Add to the reverse trie also
	if( m_pReverseTrie )
	{
		cssKey.SetBackwards( TRUE );
		pTerminal = m_pReverseTrie->Insert( cssKey, &Result );
		if( Result == 1 )
		{
			pTerminal->SetPointer(pT);
		}
	}

	IncrementCorpusCount(1);
	pT->IncrementCorpusCount(1);

	m_SortValidFlag      = FALSE;
	m_HashHasChangedFlag  = TRUE;

	return pT;
}


// Used primarily:
template<class T>
T*  TCollection<T>::operator<< (CStringSurrogate SS)
{
  QChar*        szWord = new QChar[SS.GetLength()];
  CNode*        pTerminal;
  int          Result;

  LxStrCpy( &SS, szWord, SS.GetLength() );
  
  pTerminal = Insert ( CStringSurrogate(szWord,0,SS.GetLength()), &Result );

	if (Result == 1) {
		std::auto_ptr<T> morpheme(new T(SS, m_pMiniLex));
		morpheme->SetIndex(GetCount() - 1);
		pTerminal->SetPointer(morpheme.release());
	}
	T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());

  // Add to the reverse trie also
  if( m_pReverseTrie )
  {
    pTerminal = m_pReverseTrie->Insert( CStringSurrogate(szWord,0,SS.GetLength(),TRUE), &Result );
    if( Result == 1 )
    {
      pTerminal->SetPointer(pT);
    }
  }

  IncrementCorpusCount(1);
  pT->IncrementCorpusCount(1);

  m_SortValidFlag      = FALSE;
  m_HashHasChangedFlag  = TRUE;

  delete [] szWord;

  return pT;           
}


template<class T>
T*  TCollection<T>::operator<< (QString szWord)
{
  CNode*    pTerminal;
  int      Result;
  QChar*    pKey;
  if ( szWord.isEmpty() ) { return NULL; }

  pKey = new QChar [ szWord.length()];
  LxStrCpy( szWord, pKey, szWord.length() );

  pTerminal = Insert (CStringSurrogate( pKey, 0, szWord.length() ), &Result);

	if (Result == 1) {
		std::auto_ptr<T> morpheme(new T(szWord, m_pMiniLex));
		morpheme->SetIndex(GetCount() - 1);
		pTerminal->SetPointer(morpheme.release());
	}
	T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());

  // Add to the reverse trie also
  if( m_pReverseTrie )
  {
    pTerminal = m_pReverseTrie->Insert(CStringSurrogate( pKey, 0, szWord.length() ), &Result);
    if( Result == 1 )
    {
      pTerminal->SetPointer(pT);
    }
  }

  IncrementCorpusCount(1);
  pT->IncrementCorpusCount(1);

  m_SortValidFlag      = FALSE;
  m_HashHasChangedFlag  = TRUE;
  if (m_ReverseFlag) { delete  pKey; }

  return pT;

}

template<class T> T* TCollection<T>::operator^=(CParse* string)
{
	if (string->GetKeyLength() < 1)
		return 0;
	Q_ASSERT(string->Size() >= 1);
	if (CNode* node = Find1(m_ReverseFlag ?
			CStringSurrogate(string->GetReverse()) :
			CStringSurrogate(string)))
		return static_cast<T*>(node->Get_T_Pointer());
	return 0;
}

template<class T> T* TCollection<T>::operator^=(CStringSurrogate string)
{
	if (string.GetLength() < 1)
		return 0;
	if (CNode* node = Find1(string))
		return static_cast<T*>(node->Get_T_Pointer());
	return 0;
}

template<class T> T* TCollection<T>::operator^=(QString string)
{
	if (string.isEmpty())
		return 0;
	if (CNode* node = Find1(CStringSurrogate(string)))
		return static_cast<T*>(node->Get_T_Pointer());
	return 0;
}


template<class T>
T*  TCollection<T>::operator[] ( uint n)
{
  if ( m_PointerArray == NULL || m_HashHasChangedFlag == TRUE )
  {
    CreatePointerArray();
  }

	Q_ASSERT(GetCount() >= 0);
	Q_ASSERT(n < static_cast<unsigned int>(GetCount()));

  return m_PointerArray[n];
}


template<class T>
void TCollection<T>::AddPointer(T* pT)
{
  CNode*    pTerminal;
  CStringSurrogate    ssWord = pT->GetKey();

  pTerminal = CTrie::operator<< (ssWord);
  pTerminal->SetPointer ( pT );

  // Add to the reverse trie also
  if( m_pReverseTrie )
  {
    ssWord.SetBackwards(TRUE);
    pTerminal = m_pReverseTrie->Insert( ssWord );
    pTerminal->SetPointer(pT);
  }
  
  pT->SetIndex ( GetCount() - 1);
  IncrementCorpusCount(pT->GetCorpusCount());
}


template<class T>
T*  TCollection<T>::AddToCollection (const CParse& Word)
{
  m_HashHasChangedFlag = TRUE;
  T* pT;
  pT = *this << Word;
  return  pT;
}


template<class T>
T*  TCollection<T>::AddToCollection (const CStringSurrogate& Word)
{
  T* pT;
  m_HashHasChangedFlag = TRUE;
  pT = *this << Word;
  return pT;
}


template<class T>
bool  TCollection<T>::Contains ( CStringSurrogate& string )
{
  T* pT = *this ^= string;
  if ( pT )
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}


template<class T>
void  TCollection<T>::CreatePointerArray()
{
	Q_ASSERT(m_DeletionArray == 0);
	const int size = GetCount();

	delete[] m_PointerArray;
	m_PointerArray = new T*[size];
	delete[] m_pTerminalNodeArray;
	m_pTerminalNodeArray = new CNode*[size];

	MakeATerminalPointerArray(m_pTerminalNodeArray);

	for (int i = 0; i < size; ++i) {
		m_PointerArray[i] = static_cast<T*>(
			m_pTerminalNodeArray[i]->Get_T_Pointer());
		m_PointerArray[i]->SetIndex(i);
	}

	m_HashHasChangedFlag = false;
}


template<class T>
void TCollection<T>::CreateReverseTrie()
{
  CNode*            pTerminal;
  CStringSurrogate  ssKey;
  
  if( m_pReverseTrie ) delete m_pReverseTrie;
  m_pReverseTrie = new CTrie( TRUE );
  m_pReverseTrie->SetAutoDelete( FALSE );

	// Build the reverse trie from the
	// forward trie
	for (int i = 0; i < GetCount(); ++i)
		if (T* pT = GetAt(i)) {
			ssKey = pT->GetKey();
			ssKey.SetBackwards();
			pTerminal = m_pReverseTrie->Insert(ssKey);
			pTerminal->SetPointer(pT);
		}
}


template<class T>
void TCollection<T>::DeleteMarkedMembers()
{
  // we want to do this without tripping the "trie has changed" flag along the way.

  if ( m_DeletionArray == NULL ) { return; }

  int count = GetCount();
  for (int i = 0; i < count; i++)
  {
    if ( m_DeletionArray[i] == 1 )
    {
      CStringSurrogate key = m_PointerArray[i]->GetKey();
      Q_ASSERT( RemoveFromTrie( key ) );
      if( m_pReverseTrie )
      {
        key.SetBackwards();
        Q_ASSERT( "void TCollection<T>::DeleteMarkedMembers() : Type existed in forward trie but not reverse trie." && m_pReverseTrie->RemoveFromTrie( key ) );
      }
    }
  }

//  m_LockState        = Unlocked;
  m_HashHasChangedFlag  = TRUE;
  delete m_DeletionArray;
  m_DeletionArray      = NULL;
}


template<class T>
void TCollection<T>::DoNotDeletePointers()
{
  m_DeletePointers = FALSE;
}


template<class T>
void  TCollection<T>::DumpVisibleToLogFile()
{
  if (! m_pLexicon->GetLogFileStream()) { return; }
  GetRoot1()->DumpVisibleToLogFile( m_pLexicon->GetLogFileStream(), m_ReverseFlag );
}


template<class T>
void  TCollection<T>::DumpVisibleWords(CWordCollection* Words)
{
  GetRoot1()->DumpVisibleWords(Words, FALSE);
}


template<class T>
void TCollection<T>::Empty()
{
  ResetToEmpty();
  if( m_pReverseTrie ) m_pReverseTrie->ResetToEmpty();
  if (m_SortArray) { delete [] m_SortArray; m_SortArray = NULL; }
  if (m_PointerArray) { delete [] m_PointerArray; m_PointerArray = NULL; }

  m_CorpusCount        = 0;
  m_SortValidFlag      = FALSE;
  m_HashHasChangedFlag = TRUE;
}


template<class T>
CStringSurrogate TCollection<T>::FindMaximalMajorityPrefix()
{
  CNode* pNode = FindLowestMajorityNode();

  if (pNode) return pNode->GetKey();
  else return CStringSurrogate();
}


template<class T>
void TCollection<T>::FindMemberExtensions (int SmallestStemSize, TCollection<CLParse>& Output )
{

  T*          pMorpheme;
  CLParse*      pChain = NULL;

  Sort (KEY);

  for (int  i = 0; i < GetCount(); i++)
  {
    pMorpheme  = GetAtSort(i);
    if (pMorpheme->GetLength() < SmallestStemSize + 1) { continue; }
    pChain    = SeekChain (pMorpheme, pChain, SmallestStemSize);
    if (pChain)
    {
      Output.AddPointer (pChain);
      m_pLexicon->AddToScreen ( pChain->Display() );
      pChain = NULL;
    }
  }
}

/*
template<class T>
CStringSurrogate TCollection<T>::FSAGetAtSS(uint n)
{
  Q_ASSERT ( n < (uint) GetCount() );

  if ( m_PointerArray == NULL || m_HashHasChangedFlag == TRUE )
  {
    CreatePointerArray();
    Q_ASSERT ( n == 0 );
  }

  return m_pTerminalNodeArray[n]->GetKey();
}
*/

template<class T>
T*  TCollection<T>::GetAt ( uint n )
{
	Q_ASSERT(GetCount() >= 0);
	Q_ASSERT(n < static_cast<unsigned int>(GetCount()));

  if ( m_PointerArray == NULL || m_HashHasChangedFlag == TRUE )
  {
    CreatePointerArray();
    Q_ASSERT ( n == 0 );
  }

  return m_PointerArray[n];
}


template<class T>
CStringSurrogate TCollection<T>::GetAt_SS( int n )
{
  CStringSurrogate Return ( GetAt(n)->GetKeyPointer(), 0, GetAt(n)->GetKeyLength() );

  return Return;
}


template<class T>
T* TCollection<T>::GetAtSort( int n )
{
	if( !m_SortArray || !m_SortValidFlag ) Sort( m_SortStyle );
	return m_SortArray[n];
}
 

template<class T> CStringSurrogate TCollection<T>::GetAtSort_SS(int n)
{
	if (m_SortArray == 0)
		Sort(m_SortStyle);
	return CStringSurrogate(m_SortArray[n]->GetKeyPointer(),
			m_SortArray[n]->GetKeyLength());
}

template<class T> int TCollection<T>::GetCorpusCount() const
{ return m_CorpusCount; }

template<class T>
CLexicon* TCollection<T>::GetLexicon()
{
	return m_pLexicon;
}


template<class T>
CMiniLexicon* TCollection<T>::GetMiniLexicon()
{
	return m_pMiniLex;
}


template<class T>
CTrie* TCollection<T>::GetReverseTrie()
{
	if( !m_pReverseTrie ) CreateReverseTrie();
	return m_pReverseTrie;
}


template<class T>
int  TCollection<T>::GetSortValidFlag()
{
  return m_SortValidFlag;
}


template<class T>
CTrie*  TCollection<T>::GetTrie()
{
	return this;
}


template<class T>
eLxaClass TCollection<T>::GetType()
{
	return COLLECTION_TEMPLATE;
}


template<class T>
int TCollection<T>::GetWidth( CStringSurrogate string )// i.e., from Trie
{
  CNode *pNode = Find1 ( string );
  return pNode->GetWidth();
}


template<class T>
void TCollection<T>::IncrementCorpusCount( int n )
{
	m_CorpusCount += n;
}


template<class T>
void TCollection<T>::MarkForDeletion(int n)
{
  if ( m_DeletionArray == NULL)
  {
     m_DeletionArray = new int [ GetCount() ];
    for (int i = 0; i < GetCount(); i++)
    {        
      m_DeletionArray[i] = 0;
    }
  }
  m_DeletionArray [n] = 1;
}


template<class T>
void TCollection<T>::RecomputeCorpusCount()
{
  m_CorpusCount = 0;
  for (int i = 0; i < GetCount(); i++)
  {
    m_CorpusCount += GetAt(i)->GetCorpusCount();
  }
  return;
}


template<class T>
bool TCollection<T>::Remove (T* pT) // this doesn't delete pT
{
  bool bResult;
  QString display = pT->Display();
  CStringSurrogate ssDisplay( display );

  bResult = RemoveFromTrie ( ssDisplay, FALSE );

  if ( bResult )
  {
    m_SortValidFlag      = FALSE;
    m_HashHasChangedFlag  = TRUE;

    if( m_pReverseTrie )
    {
      ssDisplay.SetBackwards();
      Q_ASSERT( "bool TCollection<T>::Remove (T* pT) : Type existed in forward trie but not reverse trie." && m_pReverseTrie->RemoveFromTrie( ssDisplay ) );
    }
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}


template<class T>
void TCollection<T>::RemoveAll()
{
  if ( m_SortArray ) { delete [] m_SortArray; m_SortArray = NULL; }
  if ( m_PointerArray ) { delete [] m_PointerArray; m_PointerArray = NULL; }

  ResetToEmpty();
  if( m_pReverseTrie ) m_pReverseTrie->ResetToEmpty();
}


template<class T>
bool TCollection<T>::RemoveMember ( T* pT )  // this deletes pT
{
  bool ReturnValue = Remove (pT);
  delete pT;
  return ReturnValue;
}

template<class T>
bool TCollection<T>::RemoveMember ( const CStringSurrogate& ssT )  // this deletes pT
{
  bool    bResult;

  bResult = RemoveFromTrie ( ssT );

  if ( bResult )
  {
    m_SortValidFlag      = FALSE;
    m_HashHasChangedFlag  = TRUE;
    if( m_pReverseTrie )
    {
      // XXX. remove from reverse trie
    }
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}


template<class T>
bool TCollection<T>::RemoveMember ( const CStringSurrogate& ssT, bool DeleteFlag )  // this can choose whether or not to delete pT
{

  bool    bResult;

  bResult = RemoveFromTrie ( ssT, DeleteFlag );

  if ( bResult )
  {
    m_SortValidFlag      = FALSE;
    m_HashHasChangedFlag  = TRUE;
    if( m_pReverseTrie )
    {
      CStringSurrogate ss_copy = ssT;
      ss_copy.SetBackwards();
      if (!m_pReverseTrie->RemoveFromTrie(ss_copy))
        Q_ASSERT( !"bool TCollection<T>::RemoveMember ( CStringSurrogate& ssT ) : Type existed in forward trie but not reverse trie." );
      ss_copy.SetBackwards(false);
    }
    return TRUE;
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

 

template<class T>
void TCollection<T>::SetKey( T* pT, CParse& NewKey )
{
  CNode* pTerminal;
  CStringSurrogate ssKey = pT->GetKey();

  RemoveFromTrie ( ssKey, FALSE);
  pTerminal = Insert ( NewKey.GetKey() );
  pTerminal->SetPointer (pT);

  if( m_pReverseTrie )
  {
    ssKey.SetBackwards();
    Q_ASSERT( m_pReverseTrie->RemoveFromTrie( ssKey ) && "bool TCollection<T>::RemoveMember ( CStringSurrogate& ssT ) : Type existed in forward trie but not reverse trie." );
    ssKey = NewKey.GetKey();
    ssKey.SetBackwards();
    pTerminal = m_pReverseTrie->Insert( ssKey );
    pTerminal->SetPointer(pT);
  }
}


template<class T>
void TCollection<T>::SetKey( T* pT, QString NewKey )
{
  CNode* pTerminal;
  CStringSurrogate ssKey = pT->GetKey();

  RemoveFromTrie ( ssKey );
  pTerminal = Insert ( NewKey );
  pTerminal->SetPointer (pT);

  if( m_pReverseTrie )
  {
    ssKey.SetBackwards();
    Q_ASSERT( m_pReverseTrie->RemoveFromTrie( ssKey ) && "bool TCollection<T>::RemoveMember ( CStringSurrogate& ssT ) : Type existed in forward trie but not reverse trie." );
    ssKey = NewKey;
    ssKey.SetBackwards();
    pTerminal = m_pReverseTrie->Insert( ssKey );
    pTerminal->SetPointer(pT);
  }
}


template<class T>
void  TCollection<T>::SetSortStyle(eSortStyle SS)
{
  m_SortStyle = SS;
}


template<class T>
void  TCollection<T>::SetSortValidFlag(bool value)
{
	m_SortValidFlag = value;
}
 

template<class T>
void  TCollection<T>::Sort( eSortStyle SS )
{
  int i;

  if (m_SortStyle == SS && m_SortValidFlag == TRUE)
  { return; }

  int Size = GetCount();

  if (m_SortArray) { delete [] m_SortArray; }
  m_SortArray = new T*[ Size ];

  for (i = 0; i < Size; i++)
  {
    m_SortArray[i] = GetAt( i );
  }

  switch ( SS )
  {
  case KEY:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareAlphabetically);
      break;
    }
  case COUNT :
  case CORPUSCOUNT:
    {
    qsort(m_SortArray, Size, sizeof(T*), CompareCorpusCount);
    break;
    }
  case SIGS:	
  case RULE_USE:
  case MORPHEME_GOODNESS:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareSortingQuantity);
      break;
    }
  case TEMPLATE_SORT:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareSortingQuantity);
      break;
    }
  case PARSE_SIZE:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareSize);
      break;
    }
  case SIGS_NUMBER_OF_STEMS:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareNumberOfStems);
      break;
    }
  case STEM_SUFFIXES:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareSortingString);
      break;
    }
  case REVERSE_KEY:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareReverseAlphabetically);
      break;
    }
  case LENGTH:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareLength);
      break;
    }
  case DL_SAVINGS:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareDLSavings);
      break;
    }
  case FREQUENCY:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareFrequency);
      break;
    }
  case MORPHEMECOUNT:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareMorphemeCount);
      break;
    }
  case USECOUNT:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareUseCount);
      break;
    }
  case SIG_REMARK:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareSigRemark);
      break;
    }
  case STEM_SOURCE:
    {
      qsort(m_SortArray, Size, sizeof(T*), CompareStemSource);
      break;
    }
  default:
      break;
  }

  for ( i = 0; i < Size; i++)
  {
    m_SortArray[i]->SetSortIndex(i);
  }

  m_SortStyle = SS;
  m_SortValidFlag = TRUE;
}


template<class T>
void TCollection<T>::T_PredecessorFrequency( eSuccessorFrequencyMode PFM,
                                             CStemCollection* Stems,
                                             CPrefixCollection* Prefixes,
                                             int MaxNeighborPredecessorCount,
                                             int MaximumPrefixLength,
                                             int MinimumStemLength,
                                             int RightMargin,
                                             int LeftMargin )
{
  T*               pWord;
  CStringSurrogate ssStem,
                   ssWord,
                   ssPrefix;
  int             WordLength,
                   nRightMargin,
                   nLeftMargin,
                   j;
  int              count = 0;
  CNode*           qNode;

  if( !m_pReverseTrie ) CreateReverseTrie();

  m_pLexicon->GetDocument()->BeginCountDown();

  for (int  i = 0; i < GetCount(); i++)
  {
    m_pLexicon->GetDocument()->CountDownOnStatusBar ( count++, GetCount(), 0 );

    pWord = GetAt(i);
    ssWord = *pWord;
    ssWord.SetBackwards();
    WordLength = pWord->GetKeyLength();

    if ( pWord->MayBeParsed() == FALSE ) continue; // if it's a compound, or parsed on the PF1 pass through this function.

    if (LeftMargin >= 0)
    {
      nLeftMargin = WordLength - LeftMargin;
    }
    else
    {
      nLeftMargin = WordLength - 1;
    }

    if (RightMargin >= 0)
    {
      nRightMargin = RightMargin;
    }
    else
    {
      nRightMargin = nLeftMargin - MaximumPrefixLength;
    }

    CNode* pNode = m_pReverseTrie->GetRoot1();

    int* SFArray = new int [WordLength + 2];

    // This array keeps track in position i of
    // how many alternatives to character i there are ( + 1) in the data.
    for (j = 0; j < WordLength + 2; j++) SFArray[j] = 0;

    int loc = 0;
    while ( loc <= WordLength )
    {
      for (; loc < pNode->m_BreakPoint && loc < WordLength; loc++)
      {
        SFArray[loc] = 1;
        Q_ASSERT (loc < WordLength);
      }
      if ( loc == WordLength)
      {
        SFArray[loc] = pNode->GetWidth();
        break;
      }
      else
      {
        SFArray[loc] = pNode->GetWidth();
        qNode = pNode->FindLetter ( ssWord[loc] );
        if (qNode == NULL)
        {
          Q_ASSERT ( pNode->GetKey() == ssWord );
          for ( ; loc <= WordLength; loc++)
          {
            SFArray[loc] = 1;
          }
          break;
        }
        else
        {
          pNode = qNode;
        }
        loc++;
      }
    }

    for (int w = nLeftMargin; w > nRightMargin && w >= MinimumStemLength ; w--)
    {

      ////////////////////////////////////////////////////////////////////
      if ( PFM == SF1 )
      {

        if (

          SFArray[w-1]  <= MaxNeighborPredecessorCount
          &&
          SFArray[w]      > 1
          &&
          SFArray[w+1]   <= MaxNeighborPredecessorCount
          )
        {
          pWord->CutRightBeforeHere( WordLength - w );

          break; //that is, use only the smallest prefix -- this is
          // wrong in some cases (assist-an-t, assist-an-ce, for example).
        }
      }

      ////////////////////////////////////////////////////////////////////
      // Here the condition is that the first piece must already exist in Stems,
      // and the second piece must already exist in Prefixes;
      // and the "peak"  need only be not LOWER than the neighbors are.
      if ( PFM == SF2 )
      {
        if ( SFArray[w-1]  <= SFArray[w]
          &&
          SFArray[w] > 1
          &&
          SFArray[w+1]  <= SFArray[w]
          )
        {

          ssStem = ssWord.Left(w - 1 );
          if ( ! ( *Stems ^= ssStem )  )
          {
            continue;
          }
          ssPrefix = ssWord.Right  ( ssWord  .GetLength() - w );
          //ssPrefix = ssPrefix.Left ( ssPrefix.GetLength() 1 );

          if ( ! ( *Prefixes ^=  ssPrefix  ))
          {
            continue;
          }

          pWord->CutRightBeforeHere(w);
          break; //that is, use only the smallest prefix -- this is
          // wrong in some cases (assist-an-t, assist-an-ce, for example).
        }
      }
    }
    delete [] SFArray;
  }
}


template<class T>
void TCollection<T>::T_SuccessorFrequency( eSuccessorFrequencyMode SFM,
                                           CStemCollection* Stems,
                                           CSuffixCollection* Suffixes,
                                           int MaxNeighborSuccessorCount,
                                           int MaximumSuffixLength,
                                           int MinimumStemLength,
                                           int LeftMargin,
                                           int RightMargin )
{
  T*               pWord;
  CStringSurrogate ssStem,
                   ssWord,
                   ssSuffix;
  int             WordLength,
                   nLeftMargin,
                   nRightMargin,
                   j;
  int              count = 0;
  CNode*           qNode;

  m_pLexicon->GetDocument()->BeginCountDown();

  for (int  i = 0; i < GetCount(); i++)
  {
    m_pLexicon->GetDocument()->CountDownOnStatusBar ( count++, GetCount(), 0 );
    
    pWord = GetAt(i);
    ssWord = *pWord;
    WordLength = pWord->GetKeyLength();

    if ( pWord->MayBeParsed() == FALSE ) continue; // if it's a compound, or parsed on the SF1 pass through this function.

    if (RightMargin >= 0)
    {
      nRightMargin = WordLength - RightMargin;
    }
    else
    {
      nRightMargin = WordLength - 1;
    }  

    if (LeftMargin >= 0)
    {
      nLeftMargin = LeftMargin;
    }
    else
    {
      nLeftMargin = nRightMargin - MaximumSuffixLength;
    }

    CNode* pNode = GetRoot1();

    int* SFArray = new int [WordLength + 2];

    // This array keeps track in position i of
    // how many alternatives to character i there are ( + 1) in the data.
    for (j = 0; j < WordLength + 2; j++) SFArray[j] = 0; 

    int loc = 0;
    while ( loc <= WordLength )
    {                     
      for (; loc < pNode->m_BreakPoint && loc < WordLength; loc++)
      {
        SFArray[loc] = 1;
        Q_ASSERT (loc < WordLength);
      }
      if ( loc == WordLength)
      {
        SFArray[loc] = pNode->GetWidth();
        break;
      }
      else
      {
        SFArray[loc] = pNode->GetWidth();
        qNode = pNode->FindLetter ( ssWord[loc] );
        if (qNode == NULL)
        {
          Q_ASSERT ( pNode->GetKey() == ssWord );
          for ( ; loc <= WordLength; loc++)
          {
            SFArray[loc] = 1;
          }
          break;
        }
        else
        {
          pNode = qNode;
        }
        loc++;
      }
    }

    for (int w = nRightMargin  ; w > 1 && w > nLeftMargin && w >= MinimumStemLength ; w--)
    {

      ////////////////////////////////////////////////////////////////////
      if ( SFM == SF1 )
      {

        if (

          SFArray[w-1]  <= MaxNeighborSuccessorCount
          &&
          SFArray[w]      > 1
          &&
          SFArray[w+1]   <= MaxNeighborSuccessorCount
          )
        {
          pWord->CutRightBeforeHere(w);

		  m_pLexicon->UpdateWord( pWord );

          break; //that is, use only the smallest suffix -- this is
          // wrong in some cases (assist-an-t, assist-an-ce, for example).
        }
      }       

      ////////////////////////////////////////////////////////////////////
      // Here the condition is that the first piece must already exist in Stems,
      // and the second piece must already exist in Suffixes;
      // and the "peak"  need only be not LOWER than the neighbors are.
      if ( SFM == SF2 )
      {
        if ( SFArray[w-1]  <= SFArray[w]
          &&
          SFArray[w] > 1
          &&
          SFArray[w+1]  <= SFArray[w]
          )
        {

          ssStem = ssWord.Left(w - 1 );
          if ( ! ( *Stems ^= ssStem )  )
          {
            continue;
          }
          ssSuffix = ssWord.Right  ( ssWord  .GetLength() - w );
          //ssSuffix = ssSuffix.Left ( ssSuffix.GetLength() 1 );

          if ( !( *Suffixes ^=  ssSuffix  ))
          {
            continue;
          }

          pWord->CutRightBeforeHere(w);

		  m_pLexicon->UpdateWord( pWord );
          break; //that is, use only the smallest suffix -- this is
          // wrong in some cases (assist-an-t, assist-an-ce, for example).
        }
      }
    }
    delete [] SFArray;
  }
}

#endif // COLLECTIONTEMPLATE_TCC
