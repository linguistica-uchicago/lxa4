// Implementation of finite-state automaton class
// Copyright © 2009 The University of Chicago
#include "FSA.h"

#include <functional>
#include <numeric>
#include <QTableWidgetItem>
#include <QPixmap>
#include "MiniLexicon.h"
#include "Signature.h"
#include "Parse.h"
#include "SignatureCollection.h"
#include "StemCollection.h"
#include "WordCollection.h"
#include "SuffixCollection.h"
#include "Suffix.h"
#include "Stem.h"
#include "log2.h"

#ifdef USE_GRAPHVIZ
#include <graphviz/gvc.h>
#endif 

#define TEST_FUNC_MAX 32 

double FSAMorpheme::GetDL(int characterCount) const 
{
	if (this->str == "NULL")
		return 0.0;
	return double(this->str.size()) * base2log(characterCount);
}

bool FSAMorpheme::operator==(const FSAMorpheme & other) const
{
   return this->toStr() == other.toStr();
}

namespace linguistica {
namespace join_helper {
	class cat_with_delim : public std::binary_function<
				QString, const FSAMorpheme*, QString> {
		const QString& delim;
	public:
		cat_with_delim(const QString& d) : delim(d) { }
		QString operator()(const QString& lhs,
				const FSAMorpheme* rhs) const
		{
			QString result = lhs;
			result.append(delim);
			result.append(rhs->toStr());
			return result;
		}
	};
}
}

QString join(const FSAMorphemeList& v, const QString& delim)
{
	using linguistica::join_helper::cat_with_delim;
	using std::accumulate;

	FSAMorphemeList::const_iterator iter = v.constBegin();
	if (iter == v.constEnd())
		// empty list
		return QString();

	const QString first = (*iter)->toStr();
	return accumulate(++iter, v.constEnd(), first, cat_with_delim(delim));
}
 
FSAstate::FSAstate(FSA* pFSA)
	: m_EdgesOut(), m_EdgesIn(),
	m_MaxDepth(-1), m_stateLabel(),
	m_PathList(), m_DiscoverCount(0)
{ pFSA->AddState(this); }

/*int FSAstate::getWordCount() const
{
  int sumIn=0,sumOut=0;

  for(int j=0; j<this->GetEdgesIn()->size();j++) {
    FSAedge* pEdge = this->GetEdgesIn()->at(j);
    for(int k=0; k<pEdge->GetMorphemes()->size(); k++)
    {
      sumIn += pEdge->GetMorphemes()->at(k)->m_corpusCount;
    }
  }

  for(int j=0; j<this->GetEdgesOut()->size();j++) {
    FSAedge* pEdge = this->GetEdgesOut()->at(j);
    for(int k=0; k<pEdge->GetMorphemes()->size(); k++)
      sumOut += pEdge->GetMorphemes()->at(k)->m_corpusCount;
  }

  Q_ASSERT(sumIn==0 || sumOut==0 || sumOut==sumIn);
  Q_ASSERT(sumOut+sumIn > 0);

  if(sumIn)
    return sumIn;
  else
    return sumOut;
}*/


void FSAstate::AddEdgeOut(FSAedge* pEdge)
{
  this->m_EdgesOut.append(pEdge);
} 

void FSAstate::AddEdgeIn(FSAedge* pEdge)
{
  this->m_EdgesIn.append(pEdge);
} 
//----------------------------------------------------------------// 
FSAedge::FSAedge(FSA* pFSA, FSAstate* pStartState, FSAstate* pEndState)
  : m_Morphemes(), m_FromState(pStartState), m_ToState(pEndState), m_FSA(pFSA)
{
  pFSA->AddEdge(this); 
}
/*
FSAedge::FSAedge(FSA* pFSA, FSAstate* pStartState, FSAstate* pEndState, CParse* pLabels)
  : m_Morphemes(), // initialized below
  m_FromState(pStartState),
  m_ToState(pEndState)
{
  pFSA->AddEdge(this);
  pLabels->CreateQStringList(m_Morphemes);
}*/

//void FSAedge::AddMorpheme(Morpheme* pMorph)
void FSAedge::AddMorpheme(const QString& str, int addedCount)
{
  Q_ASSERT(addedCount);
  //if Morpheme not included in FSA, update
  if(this->m_FSA->m_morphemes.contains(str))
  {
    FSAMorpheme * pMorph = this->m_FSA->m_morphemes[str];
    pMorph->m_corpusCount+=addedCount;
  } else {
    FSAMorpheme * pMorph = new FSAMorpheme(str,addedCount);
    this->m_FSA->m_morphemes.insert(str, pMorph);
  }

  this->m_Morphemes.append( new FSAMorpheme(str,addedCount) );
}

void FSAedge::RemoveMorpheme(FSAMorpheme * pMorph)
{
  QString str = pMorph->toStr(); 
  int count = pMorph->m_corpusCount;
  this->GetMorphemes()->remove(pMorph);
  FSAMorpheme * FsaMorph = this->m_FSA->m_morphemes[str];
  Q_ASSERT(FsaMorph);
  Q_ASSERT(FsaMorph->m_corpusCount >= count);
  if(count == FsaMorph->m_corpusCount ) //remove from FSA
    this->m_FSA->m_morphemes.remove(str);
  else
    this->m_FSA->m_morphemes[str]->m_corpusCount-=count;
}

FSA::FSA()
	: m_States(), m_Edges(), m_StartStates(),
	m_FSAPathList(), m_searched(false), m_MaxPathLength(0),
	m_lexicon(), m_charCount(0),
	m_morphemes(),
	m_nextStartStateId(0), m_nextStateId(0) { }

FSA::FSA(CMiniLexicon* pMiniLexicon)
	: m_States(new FSAstateCollection),
	m_Edges(new FSAedgeCollection),
	m_StartStates(new FSAstateCollection),
	m_FSAPathList(), m_searched(false), m_MaxPathLength(0),
	m_lexicon(pMiniLexicon),
	m_charCount(pMiniLexicon->GetNumberOfCharacterTypes()),
	m_morphemes(),
	m_nextStartStateId(0), m_nextStateId(0)
{
//m_StartState->setMaxDepth(0);
// this->AddState(m_StartState);

  //int MinimumNumberOfStemsForDisplay = 2; 
  //if (pMiniLexicon->GetSignatures()->GetCount() < 20 ) MinimumNumberOfStemsForDisplay = 1;
  //int MinimumNumberOfAffixesForDisplay = 1; //make this adjustable by user @@@@

  for (int i = 0; i < pMiniLexicon->GetSignatures()->GetCount(); i++)
  {
    CSignature* pSig = pMiniLexicon->GetSignatures()->GetAt(i);

    //if (pSig->GetNumberOfStems() < MinimumNumberOfStemsForDisplay ) continue;
    //if (pSig->Size() < MinimumNumberOfAffixesForDisplay ) continue;

    AddSignature(pSig);
  }
}

FSA::~FSA()
{
  while(!m_Edges->isEmpty()) 
  {
    FSAedge* pEdge = m_Edges->takeFirst();
    while(!(pEdge->GetMorphemes()->isEmpty()))
      delete pEdge->GetMorphemes()->takeFirst();
    delete pEdge;
  }

  while(!m_States->isEmpty())
  {
    FSAstate* pState = m_States->takeFirst();
    while(!pState->m_PathList.isEmpty())
      delete pState->m_PathList.takeFirst();
    delete pState;
  }

  QMap<QString, FSAMorpheme*>::iterator i = m_morphemes.begin();
  while (i != m_morphemes.end()) {
    delete i.value();
    ++i;
  }

  delete this->m_States;
  delete this->m_Edges;
  delete this->m_StartStates;
}

void FSA::AddSignature(CSignature* pSig)
{
  //std::cout << "---- Signature " <<pSig->GetNumberOfStems()<<" "<< pSig->GetNumberOfAffixes()<< std::endl; 

   //add start state 
  FSAstate* pStart = new FSAstate(this);
  pStart->setMaxDepth(0);
  this->m_StartStates->append(pStart);

  FSAstate* pMiddle = new FSAstate(this);
  FSAstate* pEnd    = new FSAstate(this);

   
  CStringSurrogate ssStem;
  FSAedge* pEdge1 = new FSAedge(this, pStart, pMiddle);
  for (int i = 0; i < pSig->GetNumberOfStems(); i++)
  {
    CStem* pStem = pSig->GetStemPtrList()->at(i);
    QString str = pStem->Display();

    int corpusCount = pStem->GetCorpusCount();
    Q_ASSERT(corpusCount>0);
    if(str.size()>0)
    {
      //std::cout << "\tStem:"<<str.toStdString() <<"."<< corpusCount <<std::endl;
      pEdge1->AddMorpheme( str,corpusCount); //TODO
    }
  }

  FSAedge* pEdge2 = new FSAedge(this, pMiddle, pEnd);
  for (int i = 0; i < pSig->GetNumberOfAffixes(); i++)
  {
    CSuffix* pSuffix= pSig->GetSuffixPtrList()->at(i);
    QString suffixStr = pSuffix->Display();
    int corpusCount = 0;

    for(int j=0;j<pEdge1->GetMorphemes()->size();j++)
    {
      int stemCount = pEdge1->GetMorphemes()->at(j)->m_corpusCount;
      Q_ASSERT(stemCount>0);
      QString analyzedWord = pEdge1->GetMorphemes()->at(j)->toStr();
      if (suffixStr!="NULL") 
        analyzedWord.append(suffixStr);

      CWordCollection* wc = this->m_lexicon->GetWords();

      CStem* pStem = ( *wc^=analyzedWord);
      Q_ASSERT(pStem);

      corpusCount+=(pStem->GetCorpusCount());
    }

    if(suffixStr.size()>0)
    {
      //std::cout << "\t\tSuffix "<< suffixStr.toStdString() <<"."<<corpusCount<<std::endl;
      pEdge2->AddMorpheme(suffixStr, corpusCount);
    }
  }
}
//----------------------------------------------------------------// 


void FSA::AddState(FSAstate* pState)
{
  m_States->append(pState);
};

void FSA::AddEdge(FSAedge* pEdge)
{
  m_Edges->append(pEdge);
   pEdge->GetFromState()->AddEdgeOut(pEdge);
   pEdge->GetToState()->AddEdgeIn(pEdge);
};

void FSA::RemoveEdge(FSAedge* pEdge)
{
   this->m_Edges->remove(pEdge);
   pEdge->GetFromState()->m_EdgesOut.remove(pEdge);
   pEdge->GetToState()->m_EdgesIn.remove(pEdge);

   //delete all paths that contain this edge
   for(int i=0; i<this->m_FSAPathList.size(); i++)
   {
     FSAedgeCollection* pPath = this->m_FSAPathList.at(i);
     if(pPath->contains(pEdge))
     {
       this->m_FSAPathList.remove(pPath); 
       delete pPath;
     }
   }
   delete pEdge;
};

void FSA::FSATestFunc()
{
 CSuffixCollection* lexSuffixes = this->m_lexicon->GetSuffixes();

 lexSuffixes->Sort(COUNT);
 

 CStemCollection* lexStems = this->m_lexicon->GetStems();

 for (int i=0;i<lexSuffixes->GetCount();i++)
 {
  if(i>=TEST_FUNC_MAX) {
    //std::cout << "BREAK" << std::endl;
    break;
  }
  CSuffix* pSuffix = lexSuffixes->GetAtSort(i);
  //std::cout << "Suffix:" << pSuffix->Display().toStdString() << std::endl;
  QString suffixStr = pSuffix->Display();

  for(int i=0; i<m_Edges->size(); i++)
  {
    FSAedge * pEdge3=NULL;
    FSAedge * pEdge4=NULL;
    FSAedge* pEdge = m_Edges->at(i);
    FSAMorphemeList * morphemes = pEdge->GetMorphemes();
    for(int j=0;j<morphemes->size();j++)
    {
      FSAMorpheme* pMorph = morphemes->at(j);
      QString edgeStr = pMorph->toStr();
      if (edgeStr.endsWith(suffixStr) && edgeStr!=suffixStr)
      {
        QString stemStr = edgeStr.left(edgeStr.length() - suffixStr.length());

        CStem * pStem = (*lexStems^=stemStr);
        //continue if stemStr not in Lexicon
        if(!pStem)
          continue;

        //continue if stem does not take suffix
        CSignature * pSig = pStem->GetSuffixSignature();
        bool acceptsSuffix = false;
        for (int k = 0;k<pSig->GetSuffixPtrList()->count();k++) 
        {
          CSuffix* pSuffix= pSig->GetSuffixPtrList()->at(k);
          if(pSuffix->Display() == suffixStr )
          { acceptsSuffix = true; break; }
        }
        if (!acceptsSuffix)
          continue;

        //count of morpheme that will be removed
        int count_moved = pMorph->m_corpusCount;

        if(pEdge3==NULL)
        { 
          FSAstate* pNewState= new FSAstate(this);
          pEdge3 = new FSAedge(this, pEdge->GetFromState(),pNewState);
          pEdge4 = new FSAedge(this, pNewState,pEdge->GetToState());
          pEdge4->AddMorpheme(suffixStr,count_moved);
        }
        else
        {
          //increment pEdge4
          Q_ASSERT(pEdge4->GetMorphemes()->size()==1);
          pEdge4->GetMorphemes()->at(0)->m_corpusCount += count_moved;
        }

        //TODO: iterator
        //pEdge->GetMorphemes()->remove(p_edgeStr);
        pEdge->RemoveMorpheme(morphemes->at(j));
        j--;

        edgeStr.chop(suffixStr.length());
        pEdge3->AddMorpheme(edgeStr, count_moved);

        //if we removed all morphemes, remove edge
        if(pEdge->GetMorphemes()->empty())
        {
          //std::cout << "Removing edge " << std::endl;
          this->RemoveEdge(pEdge);
          break;
        }
      }
    } 
  }
 }
}

void FSA::DoSearch()
{
  if(this->m_searched)
    return;

  this->m_searched = true;

  // get 'depth' of FSA
  this-> m_MaxPathLength=0;
  FSAstateCollection queue;
  //queue.append(this->m_StartState);
  for ( int i=0;i < this->m_StartStates->size(); i++) 
  {
    FSAstate* pStartState=this->m_StartStates->at(i); 

    //add empty path
    FSAedgeCollection* pPath = new FSAedgeCollection();
    pStartState->addPath(pPath);

    queue.append(pStartState);

    while(!queue.isEmpty())
    {
     FSAstate* pState = queue.takeFirst();

     FSAedgeCollection* edgeList = pState->GetEdgesOut();

     //if at leaf, add paths to FSA and do not search outbound edges
     if(edgeList->size() == 0)
     {
       this->m_FSAPathList += *(pState->GetPathList());
       continue;
     }

     //iter over outbound edges
     for ( int i=0;i < edgeList->size(); i++) {
        FSAedge*  pEdge = edgeList->at(i);
        FSAstate* pChildState = pEdge->GetToState();
        pChildState->m_DiscoverCount++;

        //add paths to pChildState
        for (int l=0; l < pState->GetPathList()->size(); l++)
        {
          FSAedgeCollection* pPath = pState->GetPathList()->at(l);

          FSAedgeCollection* pNewPath = new FSAedgeCollection(*pPath);
          pNewPath->append(pEdge);
          pChildState->addPath(pNewPath);
        }

        int maxChildDepth = pChildState->getMaxDepth();

        //set length of max path to child
        if(maxChildDepth==-1 || pState->getMaxDepth()+1 > maxChildDepth)
        {
          pChildState->setMaxDepth(pState->getMaxDepth()+1);
          maxChildDepth = pChildState->getMaxDepth();
        }

        if (maxChildDepth > m_MaxPathLength) 
        {
          m_MaxPathLength=maxChildDepth; 
        }

        Q_ASSERT(pChildState->m_DiscoverCount  <= pChildState->GetEdgesIn()->size());

        if(pChildState->m_DiscoverCount == pChildState->GetEdgesIn()->size())
          queue.append(pChildState);       
      }
    }
  }
  std::cout<< "FSA DL:"<<this->ComputeDL() << std::endl;
}

int FSA::GetRobustness(FSAedgeCollection * pPath)
{
  QStringList pathWordsWorking;
  int pathCharCount = 0;
  FSAMorphemeList* pEdge0Morphemes = pPath->at(0)->GetMorphemes();
  for(int j=0;j<pEdge0Morphemes->size();j++)
  {
    pathCharCount+=pEdge0Morphemes->at(j)->toStr().length();
    pathWordsWorking.append(pEdge0Morphemes->at(j)->toStr());
  }

  for(int i=1; i<pPath->size(); i++)
  {
    FSAedge* pEdge = pPath->at(i);
    QStringList newWords;
    FSAMorphemeList* mList = pEdge->GetMorphemes();
    for(int j=0;j<mList->size();j++)
    {
      QString morph = mList->at(j)->toStr();
      //std::cout<< "At morpheme:"<< morph.toStdString() <<std::endl;
      pathCharCount += morph.length();
      for(int k=0;k<pathWordsWorking.size();k++)
      {
        QString newWord = pathWordsWorking.at(k) + morph;
        //std::cout<< "  created: "<< newWord.toStdString() <<std::endl;
        newWords.append(newWord);
      } 
    }
    pathWordsWorking.clear();
    for(int j=0;j<newWords.size();j++)
      pathWordsWorking.append(newWords.at(j));
  }//end edge

  int charsReplacedCount = 0;
  for(int i=0;i<pathWordsWorking.size();i++)
  {
    charsReplacedCount+=pathWordsWorking.at(i).length();
  } 

  //std::cout<< "  charsReplaced: "<< charsReplacedCount << " pathCharCount: "<< pathCharCount << std::endl;
  return charsReplacedCount-pathCharCount;
};

void FSA::FSAListDisplay(Q3ListView* pView,
	QMap<class QString, class QString>* /* out filter not supported yet */,
	bool /* “analyzed words only” flag for future use */)
{
  pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);
  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );
  pView->clear();

  // get 'depth' of FSA

  this->DoSearch();

  pView->setSorting(0); //sort on 0th column

  // Add Column headers
//std::cout<<"Graph Max: "<<m_MaxPathLength <<std::endl;
   QStringList headers;
   for (int i = 0;i<this->m_MaxPathLength;i++)
   {
     pView->addColumn( QString( "Edge %1" ).arg(i)); 
   }
   pView->addColumn( QString( "Robustness" ));
  //m_pLexicon->GetDocument()->setStatusBar1( "Displaying FSA" );

  //associate each start state with it's parent list view item (row).
  //  If start state only has one outbound path then there will 
  //  be only one lv item, otherwise lv items/paths will be associated
  //  with a placeholder parent path 
  QMap<FSAstate*,FSAListViewItem*> lvMap;
  //create placeholder lvItem for start states with >=1 path
  for (int i=0;i<this->m_FSAPathList.size();i++)
  {
    FSAedgeCollection * pPath= this->m_FSAPathList.at(i);
    FSAstate * pStartState = pPath->at(0)->GetFromState();
    if(!lvMap.contains(pStartState) && pStartState->GetEdgesOut()->size()>1)
    {
      FSAListViewItem * lvtop = new FSAListViewItem(pView,pPath);
      lvtop->setVisible(TRUE);
      lvtop->setOpen(TRUE);
      lvtop->setText(0,"All paths: ");
      lvMap.insert(pStartState,lvtop);
    }
  }

  //store totaled robustness values for subgraph starting at each start state
  QMap<FSAstate*,int> robustnessMap; 

  //Add Item for each start state
/*
  for (int i=0;i<this->m_StartStates->size();i++)
  {
    FSAstate* pStartState = m_StartStates->at(i);

    FSAListViewItem * pStartStateItem= new FSAListViewItem(pView, this->m_FSAPathList.at(0)); //LEAK
    pStartStateItem->setVisible(TRUE);
    pStartStateItem->setOpen(TRUE);

    lvMap.insert(pStartState,pStartStateItem); 
  }*/

 //add every path as row to list view
  //for (int i=0;i<this->m_FSAPathList.size();i++)
  for (int i=0;i<this->m_FSAPathList.size();i++)
  {
    FSAedgeCollection* pPath = m_FSAPathList.at(i);  

    int robustness = FSA::GetRobustness(pPath);
    QString robustnessStr = QString("%1").arg(robustness,16);

    FSAListViewItem *lvItem;
    //get parent list view item
    FSAstate* pStartState=pPath->at(0)->GetFromState(); 
    FSAListViewItem * pParent=lvMap.value(pStartState);
    if(pParent==NULL)
    {
      lvItem = new FSAListViewItem(pView, pPath);
      lvMap.insert(pStartState,lvItem);
    }
    else
    {
      lvItem = new FSAListViewItem(pParent,pPath);

      int oldVal = robustnessMap.value(pStartState);
      robustnessMap.insert(pStartState,robustness+oldVal); //score of lvItem,pPath
    }

    lvItem->setVisible(TRUE);
    lvItem->setOpen(TRUE);

    int col_idx=0;
    // first column
    for(int i=0;i<pPath->size();i++)
    {
      FSAedge* pEdge = pPath->at(i);
      FSAMorphemeList* labelList = pEdge->GetMorphemes();
      QString label = join(*labelList, QString(' '));
      if(label.length() > 64) 
        label= QString("%1 ... %2 (%3)")
          .arg(labelList->first()->toStr())
          .arg(labelList->last()->toStr())
          .arg(labelList->size());

      //populate table
      lvItem->setText(col_idx,label+"  ");
 
      //if this edge spans multiple columns, 
      //then columns / use whitespace
      col_idx = pEdge->GetToState()->getMaxDepth();

      //iterate
      //FSAedgeCollection * edgeList = pEdge->GetToState()->GetEdgesOut();
      //pEdge = ((edgeList->isEmpty())? NULL : edgeList->first());
    }
    lvItem->setText(m_MaxPathLength,robustnessStr); 

  }
  QMap<FSAstate*,FSAListViewItem*>::iterator lvm_it = lvMap.begin();
  while (lvm_it != lvMap.end())
  {
    FSAstate* pState = lvm_it.key();
    if(pState->GetEdgesOut()->size() > 1)
    {
      int robVal = robustnessMap.value(pState);
      QString robustnessStr = QString("%1").arg(robVal,16);
      lvm_it.value()->setText(m_MaxPathLength,robustnessStr);

    }
    lvm_it++;
  }

}
//--------------------------------------------------------//

FSAListViewItem::~FSAListViewItem()
{
  if(m_pImage) delete m_pImage;
}

QPixmap* FSAListViewItem::GetQPixmap()
{
  if (m_pImage == 0)
   // build_pixmap();

  return m_pImage;
}

//#ifdef USE_GRAPHVIZ
#ifndef NO_GRAPHVIZ
/*
void FSAListViewItem::build_pixmap()
{
	// Init graph
	const char outputName[] = "tmp.png";
	QMap<FSAstate*,Agnode_t*> nodeMap;

	// generate new image
	GVC_t* gvc = gvContext();
	graph_t* g = agopen(const_cast<char*>("tmpgraph"), AGDIGRAPHSTRICT);

	// left-to-right orientation
	agraphattr(g, const_cast<char*>("rankdir"), const_cast<char*>(""));
	agset(g, const_cast<char*>("rankdir"), const_cast<char*>("LR"));

	QString& start_state_name = this->GetLVStartState()->m_stateLabel;
	if (start_state_name.isEmpty())
		start_state_name = "S";

	// create new Agnode_t for start state
	nodeMap.insert(this->GetLVStartState(),
		 agnode(g, start_state_name.toUtf8().data()));

	QList<FSAstate*> queue;
	queue.append(this->GetLVStartState());

	//now do search
	int j=1;
	while (!queue.isEmpty()) {
		FSAstate* pCurState = queue.takeFirst();

		FSAedgeCollection& edges = *pCurState->GetEdgesOut();
		for (int i = 0; i < edges.size(); ++i) {
			FSAedge* pEdge = edges.at(i);
			FSAstate* pNextState = pEdge->GetToState();

			//label node, if does not already have a label
			if (pNextState->m_stateLabel.isEmpty())
				 pNextState->m_stateLabel =
						QString("N%1").arg(j++);

			if (!nodeMap.contains(pNextState)) {
				QString label_text = pNextState->m_stateLabel;
				nodeMap.insert(pNextState,
					agnode(g, label_text.toUtf8().data()));
				 queue.append(pNextState);
			}

			// make edge label
			FSAMorphemeList* labelList = pEdge->GetMorphemes();
			QString label = join(*labelList, QString(' '));
         if(label.length() > 64)
           label= QString("%1 ... %2 (%3)")
               .arg(labelList->first()->toStr())
               .arg(labelList->last()->toStr())
               .arg(labelList->size());

			// make edge
			Agedge_t* e1 = agedge(g, nodeMap.value(pCurState),
					nodeMap.value(pNextState));
			agedgeattr(g, const_cast<char*>("label"),
					const_cast<char*>(""));
			agset(e1, const_cast<char*>("label"),
					const_cast<char*>(label.toUtf8().data()));

			// make bold if:
			if (
				// start state has >=2 outbound paths
				GetLVStartState()->GetEdgesOut()->size() >= 2 &&
				// edge in path
				this->m_pPath->contains(pEdge))
			{
				agedgeattr(g, const_cast<char*>("style"),
						const_cast<char*>(""));
				agset(e1, const_cast<char*>("style"),
						const_cast<char*>("bold"));
			}
		}
	}

	gvLayout(gvc, g, const_cast<char*>("dot"));
	gvRenderFilename(gvc, g, const_cast<char*>("png"),
			const_cast<char*>(outputName));

	// cleanup - free Layout
	gvFreeLayout(gvc, g);

	// free graph
	agclose(g);

	// close output file and free context
	gvFreeContext(gvc);

	// save image
	delete m_pImage;
	m_pImage = new QPixmap(outputName);
}
*/
#endif

void FSAListViewItem::DisplayEdgePath(Q3TextEdit* m_commandLine)
{
  int i = 0;
  FSAedge* pEdge=this->m_pPath->at(0);//GetEdge();
  int tablength = 0; //FIX
  while( pEdge ){
    m_commandLine->insert( QString( "Edge %1:\n\n" ).arg(i++) );
    FSAMorphemeList* morphemes = pEdge->GetMorphemes();

    //display as table
    int nColumns = 5;
    for (int  j = 0; j < morphemes->size(); )
    {
      for( int k=0; k < nColumns && j<morphemes->size(); k++ )
      {
        QString text = morphemes->at(j++)->toStr();//.stripWhiteSpace();
        m_commandLine->insert( text + "\t" );

        // Make tab length depend on the longest
        // word and font size
        int wordlength = text.length() * m_commandLine->pointSize();
        if( tablength < wordlength ) tablength = wordlength;
      }
      m_commandLine->insert( "\n" );
    }
    m_commandLine->insert( "\n" );

    //m_commandLine->insert(join(*morphemes, QString(' ')));
    FSAedgeCollection * edgeList = pEdge->GetToState()->GetEdgesOut();
    if(!edgeList->isEmpty())
      pEdge=edgeList->first();
    else
      pEdge=NULL;
    m_commandLine->insert("\n\n");
  }
  m_commandLine->setTabStopWidth( tablength );
}


void FSA::ResetDisplay()
{
  this->m_searched=false;
  this->m_FSAPathList.clear();

  for ( int i=0;i < this->GetStates()->size(); i++) 
  {
    FSAstate* pState=this->GetStates()->at(i); 
    pState->GetPathList()->clear();
    //CHEAP!!
    pState->m_DiscoverCount=0;
    pState->m_stateLabel=QString("");
  }

}


double FSA::ComputeDL()
{
  double morphemesDL=0;

  QMap<QString,FSAMorpheme*>::iterator m_it;
  int mSum=0; // sum morphCounter
  for (m_it = this->m_morphemes.begin(); m_it!=m_morphemes.end(); m_it++)
    mSum += m_it.value()->m_corpusCount;

  QMap<QString,double> morphPtrDLMap;
  for (m_it = this->m_morphemes.begin(); m_it!=m_morphemes.end(); m_it++)
  {
    FSAMorpheme* pMorph = m_it.value();

    morphemesDL += pMorph->GetDL(this->m_charCount);

    //lenght of pointer to morpheme
    double cnt = pMorph->m_corpusCount; // morphCounter.value(mi.key()); 
    double pDL = base2log(mSum/cnt);
    //std::cout << mi.key().toStdString() << " \tDL: " << pDL << std::endl;
    morphPtrDLMap.insert(pMorph->toStr(), pDL);
  }

  std::cout << "morphemes DL: " << morphemesDL << std::endl;

  double allStatesDL=0;
  
  QMap<FSAedge*,double> edgePtrDLMap;
  for (int i=0; i<this->m_States->size(); i++)
  {
    FSAstate* pState = this->m_States->at(i);
    double stateDL = 0;
    for (int j=0; j<pState->m_EdgesOut.size(); j++)
    {
      FSAedge* pEdge = pState->GetEdgesOut()->at(j);
      int edgeWordCount = 0;

      for(int k=0; k<pEdge->GetMorphemes()->size(); k++)
      {
        FSAMorpheme* pMorph = pEdge->GetMorphemes()->at(k);
        const QString & morphStr = pMorph->toStr();
        edgeWordCount += pMorph->m_corpusCount;
        stateDL += morphPtrDLMap[morphStr];
      }

      double edgePtrDL = base2log(mSum/edgeWordCount);
      stateDL+=edgePtrDL;
      edgePtrDLMap.insert(pEdge,edgePtrDL); 
    }
    allStatesDL+=stateDL;
  }
  std::cout << "states DL: " << allStatesDL << std::endl;

  return morphemesDL + allStatesDL;
}

