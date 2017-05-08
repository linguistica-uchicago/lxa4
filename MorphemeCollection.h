// CMorphemeCollection class
// Copyright © 2009 The University of Chicago
#ifndef MORPHEMECOLLECTION_H
#define MORPHEMECOLLECTION_H

#include "CollectionTemplate.h"
#include <q3textstream.h>

class CMorpheme;
class CMorphemeCollection;
class CMyCollectionView;
class CMiniLexicon;
class CLexicion;

void operator<< (Q3TextStream& , CMorphemeCollection&);

class CMorphemeCollection:  public TCollection<CMorpheme> 
{
  friend void operator<< (Q3TextStream& , CMorphemeCollection&);




  double m_TotalDLSavings;


public:
  CMorphemeCollection();
  CMorphemeCollection( CMiniLexicon* );
  ~CMorphemeCollection();
  void Display( CMyCollectionView*  );

  CMorpheme* operator<< ( CStringSurrogate);
  CMorpheme* operator<< ( CMorpheme* );
  void operator<< ( CMorphemeCollection* );

  void      Empty();

  double      GetTotalDLSavings() { return m_TotalDLSavings; };
  void      ViterbiParse ( CWordCollection* Words );

  bool      Forward  (const char* Word, double* ForwardProb );
  bool      Backward (const char* Word, double* BackwardProb );

  bool      Forward_Bigrams  (const char* Word, double* ForwardProb );
  bool      Backward_Bigrams (const char* Word, double* BackwardProb );


  void      ClearAllMorphemeCounts();

  void      OutputMorphemes ( QString& Filename);
};

#endif // MORPHEMECOLLECTION_H
