//#include "StdAfx.h"
#include <QString>
#include "Slice.h"
#include "linguisticamainwindow.h"
#include "WordCollection.h"
#include "Stem.h"
#include "CompareFunc.h"
#include "HTML.h"




snippet::snippet(QString s)
{
    m_string = s;
    m_count = 1;

};


StringInventory::StringInventory()
{

}
snippet* StringInventory::getsnippetpointer (QString a)
{
    snippet* s;
    s = find(a);
    if (s) return s;
    s = new snippet(a);
    insert (a,s);
    return s;


}
snippet* StringInventory::operator<< (QString a)
{
    return getsnippetpointer(a);
}
StringPtrList::StringPtrList(QString s, StringInventory* inventory)
{
    m_key = s;
    m_MyStringInventory = inventory;
}
Slice* StringInventory::addword(QString s)
{
    snippet* pstring;
    s = "#"+ s + "#";
    Slice* pslice = new Slice(s, this);

    for (int start = 0; start < s.length(); start++)
    {
        for (int length = 1; start + length <= s.length(); length++)
        {
            pstring = getsnippetpointer(s.mid(start,length));
            if (pstring) 
            { 
                pslice->append(pstring);
            }
            else {
                pstring = new snippet(s.mid(start,length));
                pslice->append(pstring);
            }
            
        }    
    }
    pslice->sort();
    return pslice;
}
 
//--------------------------------------------------------------------------------------------------------------------//
//			add word collection  
//--------------------------------------------------------------------------------------------------------------------//
void StringInventory::addwordcollection ( CWordCollection *         Words,
                                          SliceCollection&          Slices,
                                         LinguisticaMainWindow*     pDoc)
{
        Slice* pslice;
 	if (pDoc)
	{
		pDoc->BeginCountDown();
		pDoc->setStatusBar1( "Computing word slices." );
	}
	for (int i = 0; i < Words->GetCount(); i++)
	{
		pslice = addword(Words->GetAt(i)->Display());
                Slices.append(pslice);

		pDoc->setStatusBar1 ( Words->GetAt(i)->Display());
		pDoc->CountDownOnStatusBar( i, Words->GetCount(), 0 );
	}
 
 	if (pDoc) pDoc->EndCountDown();

 	pDoc->setStatusBar1( "End of computing word slices." );
}
bool snippetSort(const snippet* s1, const snippet* s2)
{
  if (s1->getlength() < s2->getlength() ) return FALSE;
  if (s1->getlength() > s2->getlength()) return TRIE;
  if (s1->getkey() < s2->getkey() ) return TRUE;
    return FALSE;
}


void Slice::sort()
{
    qSort(begin(), end(), snippetSort );
    return;
}


 
//--------------------------------------------------------------------------------------------------------------------//
//			Write to log file
//-----------------------------------------------------------------------------------------------------------------//
 
void SliceCollection::writetolog( QTextStream& stream )
{

    stream << StartTable <<
                StartTableRow <<
                        MakeTableHeader ("Word " ) <<
                        MakeTableHeader ("Word " ) <<
                        MakeTableHeader ("xxx") <<
                EndTableRow ;
 

        for (int i = 0; i < size(); i++)
	{
		stream << StartTableRow <<
                                TableData( at(i)->getkey() );
				 
                for (int j = 0; j < at(i)->size(); j++)
                {
                        stream << TableData(  at(i)->at(j)->getkey() ) ;
		}
		stream << EndTableRow;
		stream << endl;
	}
	stream << EndTable;
}








snippet* largestcommonsubstring( Slice* slice1, Slice* slice2, uint minimum)
{
    snippet* s1, *s2;
    int index1 (0), index2(0);

    while (index1 < slice1->size() && index2 < slice2->size() )
    {
        s1 = slice1->at(index1);
        s2 = slice2->at(index2);
        if (s1->getlength() < minimum || s2->getlength() < minimum ) {return NULL;}
        if (s1->getlength() >  s2->getlength() )
        { index1++;  continue;}

        if (s2->getlength() > s1->getlength() )
        { index2++;  continue; }
        
        if (s1 == s2) {return s1;}
 
        if ( s2->getkey()  > s1->getkey() )
        {
           index1++;
        }
        else 
        {
            index2++;
        }        
    }
    return NULL;
}
int largestcommonsubstringlength( Slice* slice1, Slice* slice2, uint minimum)
{
    snippet* s;
    s = largestcommonsubstring(slice1, slice2, minimum);
    if (!s) return 0; 
        else return s->getlength();
}

//--------------------------------------------------------------------------------------------------------------------//
//			Slice pair collection 
//--------------------------------------------------------------------------------------------------------------------//

void SliceCollection::FindWordPairs (  LinguisticaMainWindow* 	pDoc, CLexicon* lexicon, uint minimumlength)
{
    Slice* s1, *s2;
    int length;
    int index1 , index2 ;

	int THRESHOLD = 4;
 	if (pDoc)
	{
		pDoc->BeginCountDown();
		pDoc->setStatusBar2( "Finding related word pairs." );
	}
 	if (lexicon->LogFileOn() )
        {*lexicon->GetLogFileStream()
                    << StartTable << 
					StartTableRow <<
						MakeTableHeader ("Word 1" ) <<
						MakeTableHeader ("Word 2" ) <<
                        EndTableRow ;}
	  	

       for (index1 = 0; index1 < size(); index1++)
	{	
                s1 = at(index1);
                pDoc->setStatusBar1(s1->getkey());
	
                for (index2= index1 + 1; index2 < size(); index2++)
                {
                    s2 = at(index2);
  		    length = largestcommonsubstringlength(s1, s2, minimumlength) ;
                    if 	( length > THRESHOLD )
			{	
                            if (lexicon->LogFileOn() )
                            {
                            *lexicon->GetLogFileStream() <<
                            StartTableRow <<
                                TableData (s1->getkey() ) <<
                                TableData (s2->getkey() ) <<
                                TableData (length  ) <<
                                TableData ( largestcommonsubstring(s1,s2)->getkey() ) <<
                            EndTableRow;
                            }
                        }
		}
	}		
 	if (pDoc) pDoc->EndCountDown();

 	pDoc->setStatusBar1( "End of computing word slices." );
}


 
