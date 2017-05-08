// Implementation of CTrie methods
// Copyright © 2009 The University of Chicago
#include "Trie.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <QTextOStream>
#include "linguisticamainwindow.h"
#include "StringSurrogate.h"
#include "Parse.h"
#include "Stem.h"
#include "MorphemeCollection.h"
#include "WordCollection.h"
#include "CompareFunc.h"
#include "Typedefs.h"

// CTrieListViewItem
/////////////////////////////////////////////////////////////

CTrieListViewItem::CTrieListViewItem( Q3ListView *parent, 
                    QString label1 )
: Q3ListViewItem( parent, label1 )
{}


CTrieListViewItem::CTrieListViewItem( Q3ListViewItem *parent,
                    QString label1 )
: Q3ListViewItem( parent, label1 )
{}

QString CTrieListViewItem::key( int column, bool ascending ) const
{
  //switch( column )
  //{
  //default:
    return Q3ListViewItem::key( column, ascending );
  //}
}

QString CTrieListViewItem::text( int column ) const
{
  //switch( column )
  //{
  //default:
    return Q3ListViewItem::text( column );
  //}
}


// CTrie
/////////////////////////////////////////////////////////////

CTrie::CTrie(bool ReverseFlag)
	: m_Root(new CNode()),
	m_NodeArray(),
	m_ReverseFlag(ReverseFlag),
	m_AutoDelete(true),
	m_Count(0),
	m_NumberOfNodes(1),
	m_TrieHasChangedFlag(true),
	m_IsAlphabetized(false) { }

CTrie::~CTrie()
{
	delete m_Root;
	delete[] m_NodeArray;
}

void CTrie::ResetToEmpty()
{
	delete m_Root;	// destructor deletes all child nodes
	m_Root = new CNode();
	m_Count = 0;
	m_NumberOfNodes = 1;
	m_TrieHasChangedFlag = true;
	m_IsAlphabetized = false;
	// m_NodeArray, m_ReverseFlag, and m_AutoDelete remain unchanged.
}

CNode* CTrie::operator<< ( CStringSurrogate ssS )
{
	return Insert(ssS);
}


CNode* CTrie::operator<< ( CParse* Parse )
{
	CStringSurrogate ss = Parse->GetKey(); 
	return Insert( ss );
}
    



void CTrie::ListDisplay (Q3ListView* List, LinguisticaMainWindow* doc, StringToString* filter, bool ReverseFlag )
{
  int count = 0;
  // Remove all previous columns
  while( List->columns() ) List->removeColumn( 0 );
 
  // Add column header
  if( m_ReverseFlag ) List->addColumn( "Reverse Trie" );
  else List->addColumn( "Forward Trie" );

  if( doc )     // TODO: is doc set and if so are these functions below right
  {
    doc->setStatusBar1( "Preparing trie for display" );
    doc->getProgressBar()->setTotalSteps( m_Count );
    m_Root->ListDisplay( List, doc, &count, filter, ReverseFlag );
    doc->setStatusBar1( "" );
    doc->getProgressBar()->reset();
  }
  else m_Root->ListDisplay( List, NULL, NULL, filter, ReverseFlag );
}


void CTrie::FindSFBumps( CMorphemeCollection& TempMorphemes, int SFThreshold )
{
	m_Root->FindSFBumps ( TempMorphemes, SFThreshold );
}


void CTrie::MakeCutsWhereCountExceeds( int count, int start, int end )
{
	m_Root->MakeCutsWhereCountExceeds( count, start, end );
}

//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//      Insert

CNode* CTrie::Insert( CStringSurrogate ssS, int* pResult )
{
  CNode* pNode = NULL;

  m_Root->Insert(ssS, m_NumberOfNodes, &pNode, pResult);

  if ( pResult && *pResult == 1 )
  {
    m_Count++;
  }

  m_TrieHasChangedFlag  = TRUE;
  m_IsAlphabetized    = FALSE;

  return pNode;
}

CNode* CTrie::Insert(CStringSurrogate ssS)
{
  int Result        = 0;
  int* pResult      = &Result;
  CNode* pNode      = NULL;

  m_Root->Insert(ssS, m_NumberOfNodes, &pNode, pResult);

  if ( pResult && *pResult == 1 )
  {
    m_Count++;
  }

  m_TrieHasChangedFlag  = TRUE;
  m_IsAlphabetized    = FALSE;

  return pNode;
}


//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//

void CTrie::MakeATerminalPointerArray( CNode** Array )
{
  int Index = 0;

  m_Root->MakeATerminalPointerArray( Array, Index );
  Q_ASSERT ( (int) Index == m_Count );

}



int CTrie::CountValidSubstrings( CStringSurrogate& ss )
{
	return m_Root->CountValidSubstrings( ss );
}



CNode*    CTrie::Find1 ( CStringSurrogate SS, bool PartialOK )
{
  CNode* pNode = m_Root->Find1(SS, PartialOK);
  return pNode;
}

bool   CTrie::RemoveFromTrie ( const CStringSurrogate string, bool RemovePointerFlag )
{
  CNode*  pNode = m_Root;
  CNode*  qNode = NULL;

  m_TrieHasChangedFlag = TRUE;

  while ( pNode )
  {
    for (int i = pNode->m_StartPoint + 1; i < pNode->m_BreakPoint; i++ )
    {
      if ( string[i] != pNode->m_Key [i] )
      {
        return FALSE;
      }
    }

    QChar c = string [ pNode->m_BreakPoint ];
    qNode = pNode->FindLetter( c );
    if ( qNode == NULL )
    {
      return FALSE;
    }

    if (qNode->GetKey() == string )
    {

      Q_ASSERT ( qNode->m_Pointer );
      qNode->m_ExistenceFlag = FALSE;
	  
      if ( RemovePointerFlag && m_AutoDelete )
      {
        delete qNode->m_Pointer;
      }
      qNode->m_Pointer = NULL;

      if ( qNode->m_Letters == NULL )
      {
        delete qNode;
        m_NumberOfNodes--;

        QChar*  NewLetters  = new QChar [ pNode->GetNumberOfBranches() - 1 ];
        CNode**  NewPointers = new CNode* [ pNode->GetNumberOfBranches() - 1 ];
        int k = 0;
        for (int j = 0; j < (int)pNode->GetNumberOfBranches(); j++)
        {
          if ( c == pNode->m_Letters[j] ) { continue; }
          NewLetters[k] = pNode->m_Letters[j];
          NewPointers[k] = pNode->m_Pointers[j];
          k++;
        }
        Q_ASSERT ( k == (int)pNode->GetNumberOfBranches()-1 );
        delete [] pNode->m_Letters;  pNode->m_Letters  = NewLetters;
        delete [] pNode->m_Pointers; pNode->m_Pointers = NewPointers;
        pNode->SetNumberOfBranches(k);


      }
      else
      {
        qNode->DoesNotExist();
      }

      m_Count--;
      return TRUE;
    }
    else
    {
      pNode = qNode;
      continue;
    }
  }
  Q_ASSERT (FALSE);
  return FALSE;
}


CNode* CTrie::SearchForPrefix(CStringSurrogate& CStringSurrogate, int& Result )
{
  CNode* pNode = NULL;
  Result = 0;
   pNode = m_Root->SearchForPrefix (CStringSurrogate, Result );

  return pNode;


}


//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//    Get At


CNode* CTrie::GetRoot1()
{
  return m_Root;
}

//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//    Alphabetize
void CTrie::Alphabetize()
{
  if ( m_IsAlphabetized == FALSE)
  {
    m_Root->Alphabetize();
  }
  m_IsAlphabetized = TRUE;
}

int CTrie::ComputeNumberOfEntries()
{
  return m_Root->ComputeNumberOfEntries(0);
}

void  CTrie::CreateNodeArray()
{
	// XXX. avoid delete/new cycle if there’s room
	delete[] m_NodeArray;
	m_NodeArray = new CNode*[m_NumberOfNodes];

	int Index = 0;
	m_Root->CreateNodeArray(m_NodeArray, Index);

	Q_ASSERT(Index = GetCount());
}

void CTrie::CreateSuffixSignatures(const CStringSurrogate& prefix, CParse* out)
{ CreateSuffixSignatures(&prefix, out); }

//----------------------------------------------------------------------------
void CTrie::CreateSuffixSignatures ( const CStringSurrogate* Prefix, CParse* pSignature)
{
  // This finds the location of Prefix in the Trie, and takes all of the
  // suffixes to it and creates a "signature" of them.

  CNode*          pNode;
  int            nResult;
  CStringSurrogate    ssInitial;
  CStringSurrogate    ssPrefix = *Prefix;

  Alphabetize();


  pNode = SearchForPrefix ( ssPrefix, nResult );

  Q_ASSERT ( nResult != 0 );

  if ( pNode && nResult == 2 )
  {
    ssInitial = pNode->GetKey().Mid( ssPrefix.GetLength() );
  }

  int Offset  =  ssPrefix.GetLength();
  if( pNode ) pNode->FindAllTerminalsBelowHere( pSignature, Offset );
}


//------------------------------------------------------------------------------------
// find the deepest node in the Trie whose count is more than half of m_Count
CNode*  CTrie::FindLowestMajorityNode()
{
  CNode* pNode = m_Root->FindLowestMajorityNode( m_Count );

  if ( pNode == m_Root ) { return NULL; }
  else
  {
    return pNode;
  }
}



void CTrie::MakeAllNodesVisible(bool Flag)
{
  m_Root->MakeAllVisible(Flag);
}


bool CTrie::MakeVisible( const CStringSurrogate string )
{
  return m_Root->MakeVisible(string);

}


//----------------------------------------------------------------//
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------//
//
//    New functions added for FSA


void CTrie::MakeMorphemeBoundariesAtThisWidth(int n, int MinimumStemLength)
{

  int    ThisLength = 0;
  m_Root->MakeMorphemeBoundariesAtThisWidth(n, MinimumStemLength, ThisLength);

}




//----------------------------------------------------------------//
  ////////////////////////////////////////////////////////////////
//----------------------------------------------------------------//

void CTrie::MakeCutsAtMorphemeBoundary()
{
  int depth = 0;
  m_Root->MakeCutsAtMorphemeBoundary( depth );
}


void CTrie::SetAutoDelete( bool b )
{
  m_AutoDelete = b;
  m_Root->SetAutoDelete(b);
}


        
// CNode
/////////////////////////////////////////////////////////////
 
CNode::CNode(QString s, int StartPoint, int BreakPoint)
	: m_Key(new QChar[s.length()]),	// filled below
	m_KeyLength(s.length()),
	m_CorpusCount(0),
	m_Pointer(),
	m_Letters(),
	m_NumberOfBranches(0),
	m_Pointers(),
	m_CountBelow(0),
	m_Visible(false),
	m_AutoDelete(true),	// *this owns m_Pointer
	// public:
	m_StartPoint(StartPoint),
	m_BreakPoint(BreakPoint),
	m_ExistenceFlag(false),
	m_MorphemeBoundary(false)
{ LxStrCpy(s, m_Key, s.length()); }

CNode::CNode(const CStringSurrogate& SS, int StartPoint, int BreakPoint)
	: m_Key(new QChar[SS.GetLength()]),	// filled below
	m_KeyLength(SS.GetLength()),
	m_CorpusCount(0),
	m_Pointer(),
	m_Letters(),
	m_NumberOfBranches(0),
	m_Pointers(),
	m_CountBelow(0),
	m_Visible(false),
	m_AutoDelete(true),	// *this owns m_Pointer
	// public:
	m_StartPoint(StartPoint),
	m_BreakPoint(BreakPoint),
	m_ExistenceFlag(false),
	m_MorphemeBoundary(false)
{ LxStrCpy(&SS, m_Key, SS.GetLength()); }

CNode::CNode()
	: m_Key(),
	m_KeyLength(0),
	m_CorpusCount(0),
	m_Pointer(),
	m_Letters(),
	m_NumberOfBranches(0),
	m_Pointers(),
	m_CountBelow(0),
	m_Visible(false),
	m_AutoDelete(true),	// *this owns m_Pointer
	// public:
	m_StartPoint(0),
	m_BreakPoint(0),
	m_ExistenceFlag(false),
	m_MorphemeBoundary(false) { }

CNode::~CNode()
{
	// Delete child nodes
	if (m_Letters != 0) {
		for (int i=0; i < m_NumberOfBranches; ++i)
			delete m_Pointers[i];
		delete[] m_Pointers;
	}
  
	// If we own it, delete data
	if (m_AutoDelete)
		delete m_Pointer;

	delete[] m_Key;
	delete[] m_Letters;
}

void CNode::SetAutoDelete( bool b )
{
  m_AutoDelete = b;
  for( int i=0; m_Letters && i < m_NumberOfBranches; i++ )
  {
    m_Pointers[i]->SetAutoDelete(b);
  }
}


int	CNode::CountValidSubstrings( CStringSurrogate& ss )
{
	int count = 0;

	if( m_ExistenceFlag ) count++; 
	
	CNode* pNode = FindLetter( ss[0] );
	if( pNode )
	{
		int step = pNode->m_BreakPoint - m_BreakPoint;
		CStringSurrogate ssMid = ss.Mid( step );
		count += pNode->CountValidSubstrings( ssMid );
	}

	return count;
}


void CNode::FindSFBumps ( CMorphemeCollection& TempMorphemes, int SFThreshold )
{
  if ( GetWidth() > SFThreshold )
  {
    TempMorphemes << CStringSurrogate( m_Key, 0, m_KeyLength );
  }

  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->FindSFBumps (  TempMorphemes, SFThreshold );
  }
}


void CNode::BreakAllWordsBelowHere(int BreakLocation, CWordCollection* Words )
{
  CStem* pWord;

  CStringSurrogate ssWord;

  if (   m_KeyLength > 2 &&  m_KeyLength > BreakLocation + 1)
  {
    ssWord = CSS(m_Key, 0, m_KeyLength);

    ssWord = ssWord.Mid(1, ssWord.GetLength() - 2 );// eliminate first and last #
    pWord = *Words ^= ssWord;
    if ( pWord )
      pWord->CutRightBeforeHere (BreakLocation  );
  }
}


CNode* CNode::Insert(CStringSurrogate& SS, int& NumberOfNodes,
			CNode** ppNode, int* pResult)
{
	using std::auto_ptr;
	using std::copy;
	using std::swap;

	// The node that is returned is the node immediately down from
	// node that called this function in the first place.
	// It may be "This" or it may not.
	// ppNode is a pointer to the Terminal node that is eventually
	// identified or created for the string in question.
	CStringSurrogate ssKey(this);
	auto_ptr<CNode> this_node(this);

	// Result: 1: new node added
	//         2: node already existed

	//-----------------------------------------------------------------------//

	// 1: A difference before m_BreakPoint: it's definitely a new string.
	// should i be initialized as m_StartPoint + 1??
	int i = m_StartPoint;
	for (; i < m_BreakPoint && i < SS.GetLength(); ++i) {
		// XXX. SS and ssKey could be backwards, hence the obscure test.
//		if ( SS[i] != ssKey[i] )
		if ( LxStrCmp( &SS, ssKey.GetKey(),1,1,SS.GetStart()+i,ssKey.GetStart()+i) ) {
			// we create a new node that dominates *this and also
			// dominates the other new node created, new_node.

			auto_ptr<CNode> prev(new CNode(ssKey.Left(i), m_StartPoint, i));
			prev->GetLink(this_node.release());
			++NumberOfNodes;
			m_StartPoint = i;

			auto_ptr<CNode> new_node(new CNode(SS, i, SS.GetLength()));
			new_node->Exists();
			CNode* inserted = new_node.get();
			prev->GetLink(new_node.release());
			++NumberOfNodes;

			*ppNode = inserted;

			// Declare success.
			if (pResult) *pResult = 1;

			prev->SetCountBelow((m_ExistenceFlag ? 0 : 1) + m_CountBelow + 1);
			prev->SetCorpusCount(m_CorpusCount + 1);
			inserted->SetCorpusCount(1);

			prev->SetAutoDelete(m_AutoDelete);
			inserted->SetAutoDelete(m_AutoDelete);

			return prev.release();
		}
	}
	// Now i == m_BreakPoint or i == SS.GetLength(),
	// and m_Key[j] == SS.m_Key[j] for all j < i

	//-----------------------------------------------------------------------//

	// 2. "s" is shorter than this node's Key:
	if (i < m_BreakPoint && i == SS.GetLength()) {
		auto_ptr<CNode> prev(new CNode(ssKey.Left(i), m_StartPoint, i));
		prev->GetLink(this_node.release());
		prev->Exists();
		++NumberOfNodes;
		m_StartPoint = i;
		*ppNode = prev.get();

		// Declare success.
		if (pResult) *pResult = 1;

		prev->SetCountBelow((m_ExistenceFlag ? 0 : 1) + m_CountBelow);
		prev->SetCorpusCount(m_CorpusCount + 1);
		prev->SetAutoDelete(m_AutoDelete);

		return prev.release();
	}

	//-----------------------------------------------------------------------//

	// 3. "s" is exactly this node's key:
	if (i == m_BreakPoint && i == SS.GetLength()) {
		if (m_ExistenceFlag)
			// Already present.
			*pResult = 2;
		else
			// Success.
			*pResult = 1;

		Exists();
		SetCorpusCount(m_CorpusCount + 1);

		*ppNode = this;

		return this_node.release();
	}

	//-----------------------------------------------------------------------//
	// 4. This node only takes us part way into the word:
	QChar Letter = SS[m_BreakPoint];
	for (int j = 0;  j < m_NumberOfBranches; ++j) {
		if (m_Letters[j] == Letter) {
			CNode* next = m_Pointers[j];
			int result;
			auto_ptr<CNode> new_node(next->Insert(SS, NumberOfNodes,
							ppNode, &result));
			if (pResult) *pResult = result;
			m_Pointers[j] = new_node.release();

			if (result == 1)
				// new descendent
				++m_CountBelow;

			++m_CorpusCount;
			return this_node.release();
		}
	}

	//-----------------------------------------------------------------------//
	// 5. the letter at BreakPoint is new:
	auto_ptr<CNode> new_node(new CNode(SS, m_BreakPoint, SS.GetLength()));
	new_node->Exists();
	new_node->SetCorpusCount(1);
	new_node->SetAutoDelete(m_AutoDelete);
	++NumberOfNodes;
	*ppNode = new_node.get();

	int length = m_NumberOfBranches;

	// XXX. use realloc work-alike
	QChar* NewLetters = new QChar[length + 1];
	CNode** NewPointers = new CNode*[length + 1];
	copy(m_Letters, m_Letters + length, NewLetters);
	copy(m_Pointers, m_Pointers + length, NewPointers);
	NewLetters[length] = Letter;
	NewPointers[length] = new_node.release();

	swap(m_Letters, NewLetters);
	swap(m_Pointers, NewPointers);
	++m_NumberOfBranches;

	delete[] NewLetters;
	delete[] NewPointers;

	// Declare success.
	if (pResult) *pResult = 1;

	++m_CountBelow;
	++m_CorpusCount;

	return this_node.release();

	//-----------------------------------------------------------------------//
	// end ///////////////////////
}


CNode** CNode::GetLink ( const CStringSurrogate s )
{
  int i;

  QChar c = s[m_BreakPoint];
  int length = 0;

  if (m_Letters)
  {
    length = m_NumberOfBranches;
  }
  for ( i = 0;  i < length; i++)
  {
    if (m_Letters[i] == c) return &m_Pointers[i];
  }

  QChar* NewLetters = new QChar[length + 1];
  CNode** NewPointers = new CNode*[length + 1];
  for ( i = 0; i < length; i++)
  {
    NewLetters[i] = m_Letters[i];
    NewPointers[i] = m_Pointers[i];
  }
  NewLetters[length] = c;
  m_NumberOfBranches++;
  delete m_Letters;
  m_Letters = NewLetters;
  delete m_Pointers;
  m_Pointers = NewPointers;
  m_Pointers[length] = new CNode(s, m_BreakPoint, m_BreakPoint);
  return &m_Pointers[length];
}


CNode* CNode::FindLetter (QChar c)
{

  int length = 0;
  if (m_Letters) { length = m_NumberOfBranches;}
  for (int i = 0;  i < length; i++)
  {
    if (m_Letters[i] == c) return m_Pointers[i];
  }

  return NULL;
}


//int CNode::GetCount() const
//{
//  return m_Count;
//}


CNode** CNode::GetLink(CNode* pNode)
{
	using std::copy;
	using std::swap;

	int length = m_NumberOfBranches;

	// case 1: pNode is terminal, has same Key as this:
	if (pNode->GetKeyLength() == m_BreakPoint)
		return 0;

	QChar c = pNode->GetKey()[m_BreakPoint];

	for (int i = 0;  i < length; ++i)
		if (m_Letters[i] == c)
			return &m_Pointers[i];

	// XXX. should use realloc workalike
	QChar* NewLetters = new QChar[length + 1];
	CNode** NewPointers = new CNode*[length + 1];
	copy(m_Letters, m_Letters + length, NewLetters);
	copy(m_Pointers, m_Pointers + length, NewPointers);
	NewLetters[length] = c;
	NewPointers[length] = pNode;

	swap(m_Letters, NewLetters);
	swap(m_Pointers, NewPointers);
	delete[] NewLetters;
	delete[] NewPointers;

	++m_NumberOfBranches;
	return &m_Pointers[length];
}

void CNode::MakeCutsWhereCountExceeds( int count, int start, int end )
{
  CStringSurrogate ssKey(m_Key,0,m_KeyLength);
//  QString spaces = "\n";
  int i;

  if( start < m_KeyLength && end+1 >= m_KeyLength && m_NumberOfBranches >= count )
  {
//    for( i=0; i < m_KeyLength; i++ ) spaces += " ";
    CutAllWordsHereAndBelow_AfterNLetters ( m_KeyLength );
  }
  
  if( end+1 >= m_KeyLength )
  {
    for( i=0; m_Letters && i < m_NumberOfBranches; i++ )
    {
      m_Pointers[i]->MakeCutsWhereCountExceeds( count, start, end );
    }
  }
}


CStringSurrogate CNode::GetKey()
{
  return CStringSurrogate(m_Key,0,m_KeyLength );
}


void  CNode::MakeATerminalPointerArray (CNode** Array, int& Index)
{

  if (m_ExistenceFlag)
  {
    Array[ Index ] = this;
    Index++;
  }

  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->MakeATerminalPointerArray(Array, Index);
  }

}


CNode* CNode::Find1(const CStringSurrogate string, bool PartialOK )
{
  if (m_Key && LxStrCmp( &string, m_Key, string.GetLength(), m_KeyLength ) == 0 && ( PartialOK || m_ExistenceFlag ) )
  {
    return this;
  }

  if( m_Key )
  {
    if( string.GetLength() < m_BreakPoint )
    {
      if( !PartialOK ) return NULL;
    }

    for( int i = m_StartPoint; i < m_BreakPoint-1; i++ )
    {
      if( string[i] != m_Key[i] )
      {
        if( PartialOK && ( i > m_StartPoint ) ) return this;
		else return NULL;
      }
    }
  }

  QChar c = string[m_BreakPoint];
  for ( int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    if ( c == m_Letters[i] )
    {
      return m_Pointers[i] ->Find1 (string);
    }
  }
  return NULL;
}


CNode* CNode::SearchForPrefix ( CStringSurrogate& SS, int& Result, int Letterno )
{
  CNode* pNode;
  Q_ASSERT ( Letterno == m_StartPoint);
  if ( Letterno < m_BreakPoint-1)
  {
    for (int i = Letterno + 1; i < m_BreakPoint; i++)
    {
      if ( i == SS.GetLength() )
      {
        Result = 2;
        return this;
        // Prefix is inside of this node, however!
      }
      if ( SS[i] != m_Key[i] )
      {
        Result = 0;
        return NULL;
        // Prefix not found!
      }
    }

  }

  Letterno = m_BreakPoint;

  if ( m_Key && SS == CStringSurrogate( m_Key, 0, m_KeyLength ) )
  {
    Result = 1;
    return this;
  }

  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
      if ( SS[Letterno] == m_Letters[i] )
      {
        pNode = FindLetter ( SS[m_BreakPoint] );
        pNode = pNode->SearchForPrefix ( SS, Result, m_BreakPoint);
        return pNode;
      }
  }
  Result = 0;
  return NULL;
}


void CNode::ListDisplay(Q3ListView* List, LinguisticaMainWindow* doc, int* count, StringToString* filter, bool ReverseFlag)
{
  QString Output;
  CStringSurrogate ssKey(m_Key,0,m_KeyLength);
  QString star = "*",
      width = "  Width: ",
      lt_curly = "  {",
      rt_curly = "}",
      below = " Count below: ";
      below += QString("%1").arg(m_CountBelow);

  // Advance counter
  if( doc && count )
  {
    // Update on multiples of 100
    if( (*count) % 100 == 0 )
    {
      doc->getProgressBar()->setProgress( *count );
    }
    *count = *count + 1;
  }

  if (m_Key)
  {
    Output.append ( ssKey.Display(filter) );
    if ( ReverseFlag == TRUE )
    {
      Output.append( " (" );
      QString reverse;
      LxStrCpy_R( ssKey.Display(filter),reverse,ssKey.GetLength(), ssKey.GetStart() );
      Output.append( reverse + ")" );
    }
  }


  if (m_ExistenceFlag )
  {
    Output.append (star);
  }
  Output.append ( width );
  Output += QString("%1").arg( GetWidth() );
  if ( m_Letters )
  {
    Output.append (lt_curly);
    Output.append ( CStringSurrogate( m_Letters, 0, m_NumberOfBranches ).Display(filter) );
    Output.append (rt_curly);
  }

  Output.append ( below );
  
  CTrieListViewItem* item = new CTrieListViewItem( List, Output );
  item->setSelectable(false);
  item->setOpen(true);

  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i] ->ListDisplay (item, doc, count, filter, ReverseFlag);
  }
}


void CNode::ListDisplay(Q3ListViewItem* List, LinguisticaMainWindow* doc, int* count, StringToString* filter, bool ReverseFlag)
{
  QString Output;
  CStringSurrogate ssKey(m_Key,0,m_KeyLength);
  QString star = "*",
      width = "  Width: ",
      lt_curly = "  {",
      rt_curly = "}",
      below = " Count below: ";
      below += QString("%1").arg(m_CountBelow);

  // Advance counter
  if( doc && count )
  {
    // Update on multiples of 100
    if( (*count) % 100 == 0 )
    {
      doc->getProgressBar()->setProgress( *count );
    }
    *count = *count + 1;
  }

  if (m_Key)
  {
    Output.append ( ssKey.Display(filter) );
    if ( ReverseFlag == TRUE )
    {
      Output.append( " (" );
      QString reverse;
      LxStrCpy_R( ssKey.Display(filter),reverse,ssKey.GetLength(), ssKey.GetStart() );
      Output.append( reverse + ")" );
    }
  }


  if (m_ExistenceFlag )
  {
    Output.append (star);
  }
  Output.append ( width );
  Output += QString("%1").arg( GetWidth() );
  if ( m_Letters )
  {
    Output.append (lt_curly);
    Output.append ( CStringSurrogate( m_Letters, 0, m_NumberOfBranches ).Display(filter) );
    Output.append (rt_curly);
  }

  Output.append ( below );
  
  CTrieListViewItem* item = new CTrieListViewItem( List, Output );
  item->setSelectable(false);
  item->setOpen(true);

  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i] ->ListDisplay (item, doc, count, filter, ReverseFlag);
  }
}


int CNode::GetWidth()
{
  int width = 0;
  if (m_ExistenceFlag) { width = 1;}

  if (m_Pointers) { return m_NumberOfBranches + width; } else {return width; }

}

namespace {
	// helper for CNode::Alphabetize
	// index_in<char>("Hello")(0) == 'H'.
	template<class T> class index_in : public std::unary_function<int, T> {
		const T* array;
	public:
		index_in(const T* v) : array(v) { }
		T operator()(int i) { return array[i]; }
	};
}

void CNode::Alphabetize()
{
	using std::copy;
	using std::swap;
	using std::transform;
	using std::mem_fun;

	const int Length = m_NumberOfBranches;

	if (Length == 0)
		// nothing to do
		return;

	QChar* NewLetters = new QChar[Length];
	CNode** NewPointers  = new CNode*[Length];

	std::vector<int> shuffle(Length);
	SortLetters(&shuffle[0], m_Letters, Length);

	transform(shuffle.begin(), shuffle.end(),
			NewLetters, index_in<QChar>(m_Letters));
	transform(shuffle.begin(), shuffle.end(),
			NewPointers, index_in<CNode*>(m_Pointers));
	swap(m_Letters, NewLetters);
	swap(m_Pointers, NewPointers);

	delete[] NewLetters;
	delete[] NewPointers;

	std::for_each(m_Pointers, m_Pointers + Length,
			mem_fun(&CNode::Alphabetize));
}


void* CNode::Get_T_Pointer()
{
  if (m_ExistenceFlag)
  {
    return m_Pointer;
  }
  else
  {
    return NULL;
  }
}


int CNode::ComputeNumberOfEntries(int count)
{
  if (m_ExistenceFlag)
  {
    count++;
  }

  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    count = m_Pointers[i]->ComputeNumberOfEntries(count);
  }
  return count;
}


void CNode::CreateNodeArray(CNode** NodeArray, int& Index)
{

  NodeArray[Index] = this;
  Index++;

  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->CreateNodeArray(NodeArray, Index);
  }

}


void CNode::FindAllTerminalsBelowHere( CParse* pSuffixes, int Offset )
{
  CStringSurrogate ssPiece;
  if( m_ExistenceFlag )
  {
    ssPiece = CStringSurrogate( m_Key,0,m_KeyLength );
    pSuffixes->Append( ssPiece.Mid( Offset ) );
  }

  for( int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++ )
  {
    m_Pointers[i]->FindAllTerminalsBelowHere ( pSuffixes, Offset );
  }

}


CNode* CNode::FindLowestMajorityNode(int Count)
{
  bool  FoundFlag = FALSE;
  CNode*  pNode;


  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    if ( m_Pointers[i]->GetCountBelow() > Count / 2 )
    {
      FoundFlag = TRUE;
      return pNode = m_Pointers[i]->FindLowestMajorityNode( Count );
    }

  }

  if ( FoundFlag == FALSE )
  {
    if (m_CountBelow > Count / 2 ) { return this; }
    else
    {
      return NULL;
    }
  }
  else return NULL;

}


void CNode::DumpVisibleToLogFile(QTextOStream* stream,  bool ReverseFlag)
{
  if (m_Visible && m_ExistenceFlag )
  {
    if (ReverseFlag)
    {
      QChar* string = new QChar[ m_KeyLength + 1];
      LxStrCpy_R(m_Key, string, m_KeyLength );
      *stream << string << endl;
      delete string;
    }
    else
      *stream << m_Key << endl;
  }
  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->DumpVisibleToLogFile(stream, ReverseFlag);
  }


}

/*
void CNode::DumpVisibleWords ( CWordCollection* Words,  bool ReverseFlag )
{
  if (m_Visible && m_ExistenceFlag )
  {
    if (ReverseFlag)
    {
       *Words << CStringSurrogate(m_Key, 0, m_KeyLength);
    }
    else
    {
      *Words << CStringSurrogate(m_Key, 0, m_KeyLength);
    }
  }
  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->DumpVisibleWords(Words, ReverseFlag);
  }

}
*/

void CNode::MakeAllVisible(bool Flag)
{
  m_Visible = Flag;
  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->MakeAllVisible(Flag);
  }
}


bool CNode::MakeVisible( const CStringSurrogate string )
{
  if (m_Key && LxStrCmp( &string, m_Key, string.GetLength(), m_KeyLength ) == 0 && m_ExistenceFlag)
  {
    m_Visible = TRUE;
    return TRUE;
  }

  if (m_Key)
  {
    if ( string.GetLength() < m_BreakPoint )
    {
      return FALSE;
    }
    for (int i = m_StartPoint; i < m_BreakPoint-1;i++)
    {
      if ( string[i] != m_Key[i] )
      {
        return FALSE;
      }
    }
  }


  QChar c = string[m_BreakPoint];
  for ( int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    if ( c == m_Letters[i] )
    {
      return m_Pointers[i] ->MakeVisible (string);
    }
  }
  return FALSE;
}


bool CNode::MakeMorphemeBoundariesAtThisWidth(int n, int MinimumStemLength, int ThisLength)
{
  bool val;
  bool bLowerIsBoundary = FALSE;
  int   KeyLen = 0;
  int  NumberOfBranches=0;

//  QString DebugString;
//  const char*  DebugStringDisplay;
//  int    DebugInt;


  if ( m_Key)
  {
    KeyLen = GetKeyLength();
    ThisLength = KeyLen;

  //  DebugString = QString(m_Key, KeyLen);
  //  DebugStringDisplay = DebugString.ascii();
  //  DebugInt = 1;
  }

  NumberOfBranches = GetNumberOfBranches();

   for (int i = 0 ; m_Letters && i < NumberOfBranches; i++)
  {
    val = m_Pointers[i]->MakeMorphemeBoundariesAtThisWidth(n, MinimumStemLength, ThisLength );
    if (val) bLowerIsBoundary = TRUE;
  }

   if ( ThisLength >= MinimumStemLength && GetWidth() >= n )
  {
    m_MorphemeBoundary = TRUE;
  }
  else
  {
    m_MorphemeBoundary = false;
  }

  return m_MorphemeBoundary;
}


void CNode::CutAllWordsHereAndBelow_AfterNLetters ( int n )
{
  int  NumberOfBranches=0;

  if ( m_ExistenceFlag )
  {
    ((CStem*)m_Pointer)->CutRightBeforeHere (n);
  }

  NumberOfBranches = GetNumberOfBranches();

  for (int i = 0 ; m_Letters && i < NumberOfBranches; i++)
  {
    m_Pointers[i]->CutAllWordsHereAndBelow_AfterNLetters ( n );
  }
}


void CNode::MakeCutsAtMorphemeBoundary( int depth )
{
  int ThisDepth = depth;
  int   KeyLen = 0;
  int  NumberOfBranches=0;

  if (m_Key)
  {
    KeyLen = GetKeyLength();
    ThisDepth = KeyLen;
  }

  if ( m_MorphemeBoundary )
  {
    CutAllWordsHereAndBelow_AfterNLetters ( ThisDepth );
  }

  NumberOfBranches = GetNumberOfBranches();

  for (int i = 0 ; m_Letters && i < NumberOfBranches; i++)
  {
    m_Pointers[i]->MakeCutsAtMorphemeBoundary(ThisDepth);
  }
}

int CTrie::ProjectTrieStructureOntoWord( CParse* parse )
{
	int status = 0;
	
	parse->ClearParseStructure();
	

	if( m_ReverseFlag )
	{	
		parse->ReverseMe();
		
		
	}

	
	status = m_Root->ProjectTrieStructureOntoWord( parse );
	
	
	if( m_ReverseFlag )
	{	
		parse->ReverseMe();
		
		
	}
	
	return status;
}

int CNode::ProjectTrieStructureOntoWord( CParse* parse, int position )
{

  CStringSurrogate ssKey(this);
  CStringSurrogate SS = parse->GetKey();
  
  int newPosition = position;



  // Result: -1: word doesn't exist
  //       0: word existed

  //-----------------------------------------------------------------------//

  // 1: A difference before m_BreakPoint: it's definitely a new string.
  int i = m_StartPoint;
  for (; (SS.GetLength() > 0) && m_Key && i < m_BreakPoint && i < SS.GetLength(); i++)
  {
	newPosition++;
	
//    if ( SS[i] != ssKey[i] )
    if ( LxStrCmp( &SS, ssKey.GetKey(),1,1,SS.GetStart()+i,ssKey.GetStart()+i) )
    {
      return -1;
    }
  }

  //-----------------------------------------------------------------------//

  // 2. "s" is shorter than this node's Key:
  if ( i < m_BreakPoint && i == SS.GetLength() )
  {
      return -1;
  }

  //-----------------------------------------------------------------------//

  // 3. "s" is exactly this node's key:
  if ( m_Key && LxStrCmp ( &SS, m_Key, SS.GetLength(), m_KeyLength, SS.GetStart() ) == 0 )
  {
  	parse->SetPieceValue( parse->Size(), (double) m_CorpusCount );
  
    return 0;
  }


  //-----------------------------------------------------------------------//
  // 4. This node only takes us part way into the word:
  QChar Letter = SS[m_BreakPoint];
  for (int j = 0;  m_Letters && j < (int)m_NumberOfBranches; j++)
  {
    if ( m_Letters[j] == Letter )
    {
	
	
		parse->SetPieceValue( parse->Size(), (double) m_CorpusCount );
		parse->CutNFromTheLeft( newPosition );
		
		
      	return m_Pointers[j]->ProjectTrieStructureOntoWord( parse, newPosition );
    }
  }


  //-----------------------------------------------------------------------//
  // 5. the letter at BreakPoint is new:
  return -1;

  //-----------------------------------------------------------------------//
  // end ///////////////////////
}

QString CTrie::Display()
{
	return QString( m_Root->Display( 0, m_ReverseFlag ) + "=========================" );
}

QString CNode::Display( int tabs, bool ReverseFlag )
{
  QString Output = " ";
  QString star = "*",
      width = "  Width: ",
      lt_curly = "  {",
      rt_curly = "}",
      below = " Count below: ";
      below += QString("%1").arg(m_CountBelow);

  CStringSurrogate ssKey(m_Key,0,m_KeyLength);
  int i;
  
	for( i = 0; i < tabs; i++ )
	{
		Output.append( "__" );
	}
	Output.append( " " );
	  
  if (m_Key)
  {
    Output.append ( ssKey.Display() );
    if ( ReverseFlag == TRUE )
    {
      Output.append( " (" );
      QString reverse;
      LxStrCpy_R( ssKey.Display(),reverse,ssKey.GetLength(), ssKey.GetStart() );
      Output.append( reverse + ")" );
    }
  }


  if (m_ExistenceFlag )
  {
    Output.append (star);
  }
//  Output.append ( width );
//  Output += QString("%1").arg( GetWidth() );
  if ( m_Letters )
  {
    Output.append (lt_curly);
    Output.append ( CStringSurrogate( m_Letters, 0, m_NumberOfBranches ).Display() );
    Output.append (rt_curly);
  }

//  Output.append ( below );
  
  Output.append ( "\n" );

  for (i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    Output.append( m_Pointers[i]->Display( tabs+1, ReverseFlag ) );
  }
  
  return Output;
}

