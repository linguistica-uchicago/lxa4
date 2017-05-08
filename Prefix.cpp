// Implementation of CPrefix methods
// Copyright © 2009 The University of Chicago
#include "Prefix.h"

#include <Q3TextStream>
#include "MiniLexicon.h"
#include "Stem.h"
#include "PrefixCollection.h"
#include "WordCollection.h"
#include "log2.h"

// construction/destruction.

/**
	Constructs an empty prefix. <kbd>mini</kbd> is the mini-lexicon
	which will contain this prefix.
 */
CPrefix::CPrefix( CMiniLexicon* mini ) : CAffix( mini )
{}
/*
CPrefix::CPrefix(const QString Prefix) : CAffix(Prefix)
{}
*/

/**
	Constructs a prefix copy of a CStringSurrogate. <kbd>ssPrefix</kbd> is a
	surrogate of the prefix. <kbd>mini</kbd> is the mini-lexicon which will
	contain this prefix.
 */
CPrefix::CPrefix (const CStringSurrogate& ssPrefix, CMiniLexicon* mini ) : CAffix (ssPrefix, mini)
{}

/**
	Destroys this prefix.
 */
CPrefix::~CPrefix()
{}


// Prepare a list item for this prefix to be displayed
// in the triscreen interface
//
// Parameters:
//    List - the list item to be prepared
//    Line - what line to display on

/**
	Prepares a list view item for this prefix to be displayed in provided list view.
	<kbd>List</kbd> is the list view which will contain the new list view item. <kbd>filter</kbd>
	is an out filter for preparing strings for display. <kbd>char_count</kbd> is the number
	of characters in the lexicon, used for calculating description length. 
 */
void CPrefix::ListDisplay(Q3ListView* List,
	QMap<QString, QString>* filter, int char_count)
{
	static_cast<void>(new CPrefixListViewItem(
		List, Display(QChar(), filter),
		this, filter, char_count));
}

/**
	Returns a CParse copy of this prefix that expresses any allomorphy.
	<kbd>Output</kbd> is where the expressed prefix will be stored, it is
	also returned. The <kbd>DisplayDeletees</kbd> flag tells the function
	whether deleted portions of the morpheme should also be displayed, if
	they exist.
 */



CParse& CPrefix::Express( CParse& Output, bool DisplayDeletees )
{
  Output.ClearParse();
  QString lt = "<", rt = ">";

  if ( DisplayDeletees && m_Deletees.GetKeyLength() > 0 )
  {
    Output.Append( lt );
    Output.Append ( m_Deletees.Display() );
    Output.Append( rt );
  }
  Output.Append ( GetKey() );
  return Output;

}



// Remerge all words that use this prefix into a
// single piece
//
// Parameters:
//    Lexicon - holds stem-->prefix relationship
//    information

/**
	Merges the prefix with all associated stems. This is 
	the way the Lexicon destroys this prefix analysis. The
	prefix must be remerged with its stems. They become just
	a word with no morphology. <kbd>Lexicon</kbd> is the mini
	lexicon that contains this prefix and its associated stems.
 */
void  CPrefix::MergeMeWithMyStems ( CMiniLexicon* Lexicon )
{
  CStringSurrogate ssPrefix = GetKey(),
          ssStem;
  CParse      Word;
  CStem*      pWord = NULL;


  for (int j = 1; j <= (int)GetStemString()->Size(); j++)
  {
    ssStem = GetStemString()->GetPiece(j);
    Word = ssStem + ssPrefix;
    pWord = *Lexicon->GetWords() ^= Word;
    if (pWord)
    {
      pWord->ClearPrefixStemSplit();
    }
  }
}

/**
	Outputs the prefix to a text stream. This is useful when
	saving the Linguistica data to a file. <kbd>outf</kbd> is a 
	text stream handle.
 */
void CPrefix::OutputPrefix( Q3TextStream& outf )
{
	QString key;

	if( m_KeyLength == 0 ) key = "NULL";
	else key = Display( QChar(0), m_pMyMini->GetOutFilter() );

	outf.width(2);
	outf << " ";
	outf.setf(2);
	outf.width(12);
	outf << key;
	outf << "   ";

	outf.unsetf(2);
	outf.width(9);
	outf << m_UseCount;
	outf << "   ";
	outf.width(12);
	outf << GetCorpusCount();
	outf << "   ";
	outf.width(5);
	outf << m_Index;
	outf << "   " << endl;
}

double CPrefix::GetLengthOfPointerToMe()
{

	if (m_LengthOfPointerToMe == 0)
	{
		m_LengthOfPointerToMe = base2log ( m_pMyMini->GetPrefixes()->GetCorpusCount () / GetCorpusCount() );
	}
	return m_LengthOfPointerToMe;



}

#include "affix_list_view_item.tcc"
template class linguistica::affix_list_view_item<CPrefix>;
