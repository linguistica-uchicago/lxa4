// Finite-state automaton representation of morphology
// Copyright © 2009 The University of Chicago
#ifndef FSA_H
#define FSA_H

#include <QList>
#include <Q3ListView>
#include <Q3TextEdit>
#include <QTableView>
#include <QStandardItemModel>
#include "MiniLexicon.h"
#include <QStringList>
#include <QList>
#include <QString>

class FSA;
class FSAedge;
class FSAstate;
class SigAlignment;

class FSAMorpheme {
  QString str;
  int m_corpusCount;

public:
  FSAMorpheme(QString qs,int cc):str(qs),m_corpusCount(cc){};  

  double GetDL(int characterCount) const;
  const QString & toStr() const {return str;};

  bool operator==(const FSAMorpheme & other) const;

  friend class FSA;  
  friend class FSAedge;
  friend class FSAstate;
};

typedef QList<FSAMorpheme*> FSAMorphemeList;
typedef QList<FSAstate*> FSAstateCollection;
typedef QList<FSAedge*> FSAedgeCollection;

extern QString join(const FSAMorphemeList& v, const QString& delim);

class FSA {
	FSAstateCollection* 		m_States;
	FSAedgeCollection* 		m_Edges;
	FSAstateCollection* 		m_StartStates;
	QList<FSAedgeCollection*> 	m_FSAPathList;
	bool 				m_searched;
	int 				m_MaxPathLength;
	CMiniLexicon* 			m_lexicon;
	int 				m_charCount;
	// the same morpheme may occur at multiple edges
	QMap<QString, FSAMorpheme*> 	m_morphemes;
	int 				m_nextStartStateId;
	int 				m_nextStateId;
public:
	// construction/destruction.

	FSA();
	explicit FSA(CMiniLexicon* pMiniLex);
	~FSA();

	// disable copy.
private:
	FSA(const FSA& x);
	FSA& operator=(const FSA& x);
public:

	// insert.

	void AddSignature(CSignature* pSig);
	void AddState(FSAstate* state);
	void AddEdge(FSAedge* edge);

	// remove.

	void RemoveEdge(FSAedge* edge);

	/// description length
	double ComputeDL();

	// output to GUI.

	void FSAListDisplay(Q3ListView* widget,
		QMap<QString, QString>* filter,
		bool unused);

	// display helpers.

	/// list paths to leaves in m_FSAPathList
	void DoSearch();
	void ResetDisplay();

	/// state list
	FSAstateCollection* GetStates() { return m_States;}

	// linguistic analysis.

	/// sample function that does some manipulation of FSA
	void FSATestFunc();

	static int GetRobustness(FSAedgeCollection * pPath);

	friend class FSAedge;
};

class FSAedge {
	FSAMorphemeList m_Morphemes;
	FSAstate* m_FromState;
	FSAstate* m_ToState;
	FSA* m_FSA;
public:
	// construction/destruction.

	explicit FSAedge(FSA* pFSA, FSAstate* start = 0, FSAstate* end = 0);
//	FSAedge(FSA* pFSA, FSAstate* start, FSAstate* end, class CParse* pLabels);
	// suppress implied default constructor
private:
	FSAedge();
public:
	// destructor implicitly defined.

	// disable copy.
private:
	FSAedge(const FSAedge& x);
	FSAedge& operator=(const FSAedge& x);
public:

	// morpheme list.

	void AddMorpheme(const QString& morpheme_text, int count);
	void RemoveMorpheme(FSAMorpheme* morpheme);
	FSAMorphemeList* GetMorphemes() { return &m_Morphemes; }

	// source and target states.

	FSAstate* GetFromState() const { return m_FromState; }
	FSAstate* GetToState() const { return m_ToState; }
};

class FSAstate
{
	FSAedgeCollection m_EdgesOut;
	FSAedgeCollection m_EdgesIn;
	int m_MaxDepth;
	QString m_stateLabel;

	// XXX. only used for breadth-first search
	QList<FSAedgeCollection*> m_PathList; //list of paths to this node
	int m_DiscoverCount;
public:
	QList<FSAedgeCollection*>* GetPathList(){ return &m_PathList; }
	void addPath(FSAedgeCollection* pPath) { m_PathList.append(pPath);}
	void setMaxDepth(int d){this->m_MaxDepth=d;}
	int  getMaxDepth(){return this->m_MaxDepth;}

	FSAstate(FSA* pFSA);

	FSAedgeCollection* GetEdgesOut() { return &m_EdgesOut; }
	void AddEdgeOut(FSAedge* pEdge);

	FSAedgeCollection* GetEdgesIn() { return &m_EdgesIn; }
	void AddEdgeIn(FSAedge* pEdge);

	friend class FSA;
	friend class FSAListViewItem;
};

class SigAlignment
{
  class CSignature*	m_Sig1;  // the standard of comparison
  class CSignature*	m_Sig2;  // the signature being reanalyzed

  int				m_Length; // number of affixes in longer signature
  
};

/// Qt3-style row object for a table displaying the FSA
/// Each row corresponds to a complete edge path
class FSAListViewItem : public Q3ListViewItem {
	QPixmap* m_pImage;
	/// points to path to some final state
	FSAedgeCollection* m_pPath;
public:
	// construction/destruction.

	FSAListViewItem(Q3ListView* pView, FSAedgeCollection* path)
		: Q3ListViewItem(pView), m_pImage(), m_pPath(path) { }
	FSAListViewItem(FSAListViewItem* pParent, FSAedgeCollection* path)
		: Q3ListViewItem(pParent), m_pImage(), m_pPath(path) { }
	// disable default-construction.
private:
	FSAListViewItem();
public:
	~FSAListViewItem();

	// copy.

	FSAListViewItem(const FSAListViewItem& x)
		: Q3ListViewItem(x),
		// drop cached pixmap to avoid deleting it twice
		m_pImage(),
		m_pPath(x.m_pPath) { }
	FSAListViewItem& operator=(const FSAListViewItem& x)
	{
		Q3ListViewItem::operator=(x);
		m_pImage = 0;
		m_pPath = x.m_pPath;
		return *this;
	}

	// output to GUI.

	/// graphical display
	/// repeated requests are fast since created image is cached
	QPixmap* GetQPixmap();
	/// write information about path to “command line” pane
	void DisplayEdgePath(Q3TextEdit* m_commandLine);

	/// start state
	FSAstate* GetLVStartState()
		{ return m_pPath->first()->GetFromState(); }
private:
	/// helper for graphical display
	void build_pixmap();

  friend class FSA;
};

#ifndef USE_GRAPHVIZ
inline void FSAListViewItem::build_pixmap()
{
	// not using graphviz, empty image
	m_pImage = new QPixmap;
}
#endif

#endif // FSA_H
