#pragma once
#include <QString>
#include <Q3Dict>
#include <QList>
#include <QTextStream>
//#include "StdAfx.h"
class StringPtrList;
class CWordCollection;
class LinguisticaMainWindow;
class CLexicon;

typedef StringPtrList Slice;
class SliceCollection;

/**
        A snippet  is a representation
    of a string which also contains information number of times it is used.
    The primary purpose of this object is so that we can access a pointer to each one.
 */
class snippet
{
    QString m_string;
    int     m_count;
public:
    snippet(QString);
    uint getlength() const {return  m_string.length();}
    QString getkey() const {return m_string;}

};
    bool lessThan(const snippet* s1, const snippet* s2);
/**
	This is simply a dictionary that allows us to go from a QString to a pointer to 
    a snippet with the same key that is in the inventory.
 */
class StringInventory : public Q3Dict<snippet> //
{
public:
    
    StringInventory();
    void addwordcollection ( CWordCollection*, SliceCollection&, LinguisticaMainWindow*);
    snippet* getsnippetpointer (QString);
    snippet* operator<< (QString);
    Slice*  addword (QString);
};
/**
        A slice is a list of pointers to a snippet for every substring in the key of the slice.
    It is the principal class in this file.
 */
class StringPtrList:  public QList<snippet*>  // a.k.a. Slice
{
public:

    QString             m_key;
    StringInventory*    m_MyStringInventory;
    
    StringPtrList(QString key, StringInventory*);

    void                sort();
    int                 getlength() {return m_key.length();}
    QString getkey()    {return m_key;}
};

class SliceCollection: public QList<Slice*>
{
public:
    void writetolog(QTextStream& );
    void FindWordPairs (LinguisticaMainWindow*, CLexicon*, uint minimumlength = 0);
};

int largestcommonsubstringlength( Slice*, Slice*, uint minimum = 0);
snippet* largestcommonsubstring( Slice*, Slice*, uint minimum =0);
