%module lxa
//%module(directors="1") lxa
%import "std_string.i"
%include "typemaps.i"

/*
// ``Director'' classes:
// see http://swig.org/Doc1.3/Python.html#Python_nn34
//
// I think this is not working right with templates.
%feature("director") Q3Dict;
%feature("director") Q3DictIterator;
%feature("director") Q3PtrList;
%feature("director") Q3PtrListIterator;
%feature("director") QList;
%feature("director") QListIterator;
*/

%ignore *::operator=;


%include "CAffix.i"
%include "CCorpusWordCollection.i"
%include "CCorpusWord.i"
%include "CDescriptionLength.i"
%include "CDLHistory.i"
%include "CLexicon.i"
%include "CLParse.i"
%include "CMiniLexicon.i"
%include "CorpusCount.i"
%include "CParse.i"
%include "CSignatureCollection.i"
%include "CSignature.i"
%include "CStemCollection.i"
%include "CStem.i"
%include "CStringSurrogate.i"
%include "CSuffixCollection.i"
%include "CTrie.i"
%include "CWordCollection.i"
%include "FSA.i"
%include "LinguisticaMainWindow.i"
%include "qt_q3dict.i"
%include "qt_q3ptrlist.i"
%include "qt_qbool.i"
%include "qt_qchar.i"
%include "qt_qlist.i"
%include "qt_qstring.i"
%include "qt_qstringlist.i"
%include "TCollection.i"

////// some enums:
%{
#include "generaldefinitions.h"
%}
// from generaldefinitions.h
%rename (eParseSortStyle_NotSorted)	eNotSorted;
%rename (eParseSortStyle_Alphabetized)	eAlphabetized;
%rename (eParseSortStyle_AlphabetizedFromEnd)	eAlphabetizedFromEnd;
%rename (eParseSortStyle_SortByPieceLength)	eSortByPieceLength;
enum eParseSortStyle
{
	eNotSorted,
	eAlphabetized,
	eAlphabetizedFromEnd,
	eSortByPieceLength
};
enum eSuccessorFrequencyMode
{
  SF1,  //, peak and neighbors are only "1"
  SF2,  //, peak, and both stem and suffix are already identified.
  SF3    //peak, that's all
};

typedef int	uint;


////////////////////////

%pythoncode %{
_app = _newApp()
_mainwindow = _LinguisticaMainWindow(0,None, _app)
lexicon = _mainwindow.GetLexicon()
lexicon.ClearAll()
def read_corpus(filename, number_of_words = 5000):
	lexicon.ReadCorpus(QString(filename), number_of_words)
	print '%8d word tokens read' % lexicon.GetTokenCount()
	print '%8d             used' % lexicon.GetCorpusCount()
	mini = lexicon.GetMiniLexicon( lexicon.GetActiveMiniIndex() )
	print '%8d word types' % (mini.GetNumberOfAnalyzedWords() + mini.GetNumberOfUnAnalyzedWords())
	print '%8d character types' % lexicon.GetNumberOfCharacterTypes()
	return

# ### Figure out the right way to do this:
# import sys
# sys.path += ('./swig',)
# import results
%}
