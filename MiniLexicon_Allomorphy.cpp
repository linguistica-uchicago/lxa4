// Small wrapper method
#include "MiniLexicon.h"
#include "SignatureCollection.h"

// XXX. move to Lexicon_Allomorphy.cpp

void CMiniLexicon::FindAllomorphy()
{
    m_pSignatures->FindAllomorphy(); 
//    RelateStems();
}
