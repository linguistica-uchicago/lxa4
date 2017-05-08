// Base for collection class template
// Copyright © 2009 The University of Chicago
#ifndef TRIE_H
#define TRIE_H

#include <QList>
#include <q3textstream.h>
#include <q3listview.h>
#include <q3dict.h>
#include <qstring.h>
#include <QTextOStream>

#include "StringFunc.h"
#include "StringSurrogate.h"
#include "Parse.h"

class CMorphemeCollection;
class CNode;
class CTrie;
class CWordCollection;
class LinguisticaMainWindow;


//typedef QMap<QString,QString>  StringToString;


class CTrieListViewItem : public Q3ListViewItem
{
public:
  CTrieListViewItem( Q3ListView* parent = NULL );
  CTrieListViewItem( Q3ListView *parent,
             QString = QString::null );
  CTrieListViewItem( Q3ListViewItem *parent,
             QString = QString::null );

  virtual QString text ( int ) const;
  virtual QString key ( int, bool ) const;
};

class CNode {
	/// m_Key[0]..m_Key[m_KeyLength - 1] is a string containing this
	/// node’s key.
	/// The memory pointed to is owned by the node.
	QChar* m_Key;
	int m_KeyLength;

	int m_CorpusCount;

	/// Callers can optionally store data in m_Pointer.
	/// If m_AutoDelete is true, CNode takes responsibility for deleting it.
	/// XXX. Unfortunately, in that case, the object’s destructor will not
	/// be called.
	void* m_Pointer;

	/// m_Pointers[0]..m_Pointers[m_NumberOfBranches - 1]
	/// point to child nodes.
	///
	/// Each child’s key is this node’s key with the corresponding char
	/// from m_Letters[0]..m_Letters[m_NumberOfBranches - 1] appended.
	///
	/// The memory for the m_Pointers and m_Letters arrays and the child
	/// nodes are owned by this node.
	QChar* m_Letters;
	int m_NumberOfBranches;
	CNode** m_Pointers;

	int m_CountBelow;
	/// We can "activate" just part of the trie with this
	bool m_Visible; 
	bool m_AutoDelete;
public:
	/// This node’s key is m_Key[0]..m_Key[m_BreakPoint - 1],
	/// and its parent’s key is m_Key[0]..m_Key[m_StartPoint - 1].
	/// Thus, 0 <= m_StartPoint <= m_BreakPoint <= m_KeyLength always holds,
	/// and m_StartPoint < m_BreakPoint for all nodes except the root.
	int m_StartPoint;
	int m_BreakPoint;
	bool m_ExistenceFlag;                 
	bool m_MorphemeBoundary; // FSA
public:
	// construction/destruction.

	CNode();
	CNode(const CStringSurrogate& key, int start_index, int break_index);
	CNode(QString key, int start_index, int break_index);
	~CNode();

	// disable copy
private:
	CNode(const CNode& x);
	CNode& operator=(const CNode& x);
public:
	// label.

	CStringSurrogate GetKey();
	int GetKeyLength() { return m_KeyLength; }
	QChar* GetKeyPointer() { return m_Key; }

	// child nodes.

	CNode* GetBranch(int i) const
	{
		if (i >= m_NumberOfBranches || i < 0 )
			return 0;
		return m_Pointers[i];
	}
	int GetNumberOfBranches() const { return m_NumberOfBranches; }
	void SetNumberOfBranches(int n) { m_NumberOfBranches = n; }
	CNode* FindLetter(QChar ch);
	/// number of children, plus 1 if ExistenceFlag is true
	int GetWidth();

	// associated data.

	void DoesNotExist() { m_ExistenceFlag = false; }
	void Exists () { m_ExistenceFlag = true; }
	void* Get_T_Pointer();
	void SetPointer(void* pT) { m_Pointer = pT; }
	/// delete associated data for descendent nodes when they
	/// are destroyed?
	/// XXX. if set to true, the associated data will only be
	/// deleted as a void pointer.  This results in undefined
	/// behavior, since no destructor is called.
	void SetAutoDelete(bool b = true);

	// corpus count.

	int GetCorpusCount () const { return m_CorpusCount; }
	void SetCorpusCount(int n) { m_CorpusCount = n; }

	// find.

	CNode* Find1(const CStringSurrogate key, bool PartialOK = 0 );

	// insert.

	CNode* Insert(CStringSurrogate& str, int& num_nodes,
		CNode** new_terminal = 0, int* result = 0);
	CNode** GetLink(const CStringSurrogate str);
	CNode** GetLink(CStringSurrogate& str);
	/// Requires: this node’s key is a prefix of new_node’s
	/// If this node’s and new_node’s keys coincide, does nothing
	/// and result is null.
	/// Otherwise, let c be the first character after this node’s
	/// key in new_node’s key.
	///
	/// If this node has a child corresponding to the letter c,
	/// result is a pointer to the corresponding edge.
	///
	/// If not, this node adopts new_node as a child corresponding
	/// to the letter c, and the result is a pointer to the new edge.
	///
	/// Example:
	///	CNode* new_node = acquire_new_node_somehow();
	///	for (CNode** edge = &root;
	///			edge != 0;
	///			edge = (*edge)->GetLink(new_node))
	///		// do nothing
	///		;
	CNode** GetLink(CNode* new_node);

	// iteration.

	/// invoke CStem::CutRightBeforeHere(index) on each word from words
	/// found in the trie
	void BreakAllWordsBelowHere(int index, CWordCollection* words);
	/// result is count plus the number of nodes with ExistenceFlag true
	int ComputeNumberOfEntries(int count);
	/// result is the number of prefixes of str that exist in the trie
	/// XXX. some false positives might be included in that count
	int CountValidSubstrings(CStringSurrogate& str);
	/// invoke CStem::CutRightBeforeHere(index) on
	/// static_cast<CStem*>(m_Pointer) for each descendent node
	void CutAllWordsHereAndBelow_AfterNLetters(int index); // FSA
	/// append existing descendents’ key.mid(Offset)s to *out.
	void FindAllTerminalsBelowHere(CParse* out, int Offset = 0);
	/// deepest descendent for which GetCountBelow() > count / 2
	/// if no such descendent exists, result is null.
	CNode* FindLowestMajorityNode(int count);
	/// append each descendent with GetWidth() > threshold to out
	void FindSFBumps(CMorphemeCollection& out, int threshold);
	void MakeCutsAtMorphemeBoundary(int depth); // FSA
	void MakeCutsWhereCountExceeds(int count, int start, int end);
	bool MakeMorphemeBoundariesAtThisWidth(int n, int min_stem_len,
		int this_len); // FSA
	CNode* SearchForPrefix(CStringSurrogate& str, int& result,
		int Letterno = 0);

	// sort.

	/// put child nodes in alphabetical order,
	/// then call Alphabetize() on each child node.
	void Alphabetize();

	// output.

	QString Display(int tabs, bool reversed);
	void DumpVisibleToLogFile(QTextOStream* out, bool reversed);
	// void DumpVisibleWords(CWordCollection* out, bool reversed);
	/// list all descendent nodes as out[i], out[i+1], ... and set i
	/// to the index after the last descendent.
	void CreateNodeArray(CNode** out, int& i);
	/// list existent descendent nodes as out[i], out[i+1], ... and
	/// set i to the index after the last existing descendent
	void MakeATerminalPointerArray(CNode** out, int& i);
	/// cut *parse at each index where there is an existing node
	/// and save the corresponding corpus counts as piece values.
	int ProjectTrieStructureOntoWord(CParse* parse, int position = 0);

	// number of existing descendents.

	int GetCountBelow() { return m_CountBelow; }
	void SetCountBelow(int n) { m_CountBelow = n; }

	// output to GUI.

	void ListDisplay(Q3ListView* widget,
		LinguisticaMainWindow* doc = 0,
		int* count = 0,
		QMap<QString, QString>* filter = 0,
		bool ReverseFlag = false);
	void ListDisplay(Q3ListViewItem* parent,
		LinguisticaMainWindow* doc = 0,
		int* count = 0,
		QMap<QString, QString>* filter = 0,
		bool ReverseFlag = false);

	// invisible branches.

	/// if Flag is TRUE, make all visible, else all invisible
	void MakeAllVisible(bool flag);
	bool MakeVisible(const CStringSurrogate str);

	friend class CTrie;
};

class CTrie {
protected:
	CNode* m_Root;
	/// List of all nodes, for iterating over all nodes.
	/// created when required by CreateNodeArray(), owned by the trie
	/// not updated as the trie changes
	mutable CNode** m_NodeArray;
	bool m_ReverseFlag;  // For output functions
	bool m_AutoDelete;
	/// Number of nodes below root (always >= 0).
	int m_Count;
	int m_NumberOfNodes;
	bool m_TrieHasChangedFlag;
	bool m_IsAlphabetized;
public:
	// construction/destruction.

	explicit CTrie(bool ReverseFlag = false);
	virtual ~CTrie();

	/// delete associated data for nodes when they are removed
	/// or trie is destroyed?
	/// XXX. if set to true, the associated data will only be
	/// deleted as a void pointer.  This results in undefined
	/// behavior, since no destructor is called.
	void SetAutoDelete(bool b = true);

	// disable copy.
private:
	CTrie(const CTrie& x);
	CTrie& operator=(const CTrie& x);
public:
	// assign.

	/// Replace with a default-constructed trie,
	/// except remember the reversed and auto-delete flags.
	void ResetToEmpty(); // just removes structure;

	// insert.

	CNode* operator<<(CStringSurrogate str);
	CNode* operator<<(CParse str) { return *this << &str; }
	/// deprecated
	CNode* operator<<(CParse* str);
	CNode* Insert(CStringSurrogate str);
	CNode* Insert(CStringSurrogate str, int* result);

	// remove.

	bool RemoveFromTrie(const CStringSurrogate,
		bool RemovePointerFlag = true);

	// find.

	CNode* Find1(CStringSurrogate, bool PartialOK = 0);

	// size.

	int ComputeNumberOfEntries();
	int GetCount() { return m_Count; }
	int GetSize() { return m_Count; }

	// output.

	QString Display();
	void CreateNodeArray();
	CNode** GetNodeArray() { return m_NodeArray; }

	// sort.

	void Alphabetize();

	// reverse keys.

	bool IsReverse() { return m_ReverseFlag; }

	/// root node
	CNode* GetRoot1();

	// affix discovery.

	/// result is the number of prefixes of str that exist in the trie
	int CountValidSubstrings(CStringSurrogate& str);
	/// write a list of suffixes corresponding to prefix to *out
	void CreateSuffixSignatures(const CStringSurrogate& prefix, CParse* out);
	/// deprecated
	void CreateSuffixSignatures(const CStringSurrogate*, CParse*);
	void FindSFBumps(CMorphemeCollection& out, int threshold);

	/// deepest descendent for which GetCountBelow() > GetCount() / 2
	CNode* FindLowestMajorityNode();

	// node count.

	void IncrementCount(int n = 1) { m_Count += n; }

	// hide branch.

	void MakeAllNodesVisible(bool flag); // see MakeVisible
	bool MakeVisible(const CStringSurrogate key);

	// output.

	/// requires: Array[0]..Array[GetCount() - 1] are valid to write to
	/// list existent nodes to those locations
	void MakeATerminalPointerArray(CNode** Array);
	/// output to GUI
	void ListDisplay(Q3ListView* widget,
		LinguisticaMainWindow* doc = 0,
		QMap<QString, QString>* filter = 0,
		bool ReverseFlag = false);
	/// cut *parse at each index where there is an existing node
	/// and save the corresponding corpus counts as piece values.
	int ProjectTrieStructureOntoWord(CParse* parse);

	void MakeCutsAtMorphemeBoundary(); // FSA
	void MakeCutsWhereCountExceeds(int, int start = 1, int end = 10000);
	void MakeMorphemeBoundariesAtThisWidth(int, int); // FSA
	CNode* SearchForPrefix(CStringSurrogate& str, int& result);
};

#endif // TRIE_H
