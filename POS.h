// Merged signatures, representing a single part of speech (one hopes!)
// Copyright © 2009 The University of Chicago
#ifndef POS_H
#define POS_H

#include "Signature.h"
#include <q3listview.h>
class GUIPOS;

class LxPoS : public CLParse 
{
    CSignature*     m_Signature; // owned by another Collection; this is just a pointer.
    CParse          m_SatelliteAffixes;//affixes taken by stems of this POS.
    double          m_Robustness;


public:
    LxPoS           (CSignature* , CMiniLexicon* mini);
	virtual ~LxPoS();

    int             GetSize()               { return m_Signature->Size();   }
    CSignature*     GetSignature()          { return m_Signature;           }
    CParse*         GetSatelliteAffixes()   { return &m_SatelliteAffixes;   }
    double          GetRobustness()         { return m_Robustness;          }
    void            AddRobustness(double r) { m_Robustness += r;            } 
    void            ListDisplay(Q3ListView* m_collectionView, 
                        QString  );
    void            ListDisplay(Q3ListViewItem* m_collectionView, 
                        QString  );
};



//---------------  GUI -----------------------------------------//

class GUIPOSListViewItem: public Q3ListViewItem
{

public:
  //--------------------------------------------------
  // Constructors/Destructor
  //--------------------------------------------------


    GUIPOSListViewItem( Q3ListView* parent = NULL );  
    GUIPOSListViewItem( Q3ListView *parent, 
                        QString, 
                        LxPoS*);

   GUIPOSListViewItem( Q3ListViewItem *parent,
                        QString,
                        LxPoS*);
              
  virtual QString   text ( int ) const;
  virtual QString   key ( int, bool ) const;
  LxPoS* GetPoS() const { return m_PoS; }
  void              SetPoS( LxPoS* qPoS  )              { m_PoS= qPoS;                          }
  CParse*           GetSatelliteAffixes()               { return m_PoS->GetSatelliteAffixes(); }
  Q3ListView*        GetParent()                         { return m_parentlist;                  }
  void              PoSListDisplay  (Q3ListView*,     QString, LxPoS*); 
  void              PoSListDisplay  (Q3ListViewItem*, QString, LxPoS*); 
  int compare(Q3ListViewItem *item, int col, bool asc) const;
  //--------------------------------------------------
  // Protected member variables
  //--------------------------------------------------

protected:
  
  LxPoS*            m_PoS;
  StringToString*   m_filter;
  QString           m_label;
  Q3ListView*        m_parentlist;
  int			    m_mini;
};

#endif // POS_H
