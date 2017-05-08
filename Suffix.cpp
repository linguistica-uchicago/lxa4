// Implementation of CSuffix methods
// Copyright © 2009 The University of Chicago
#include "Suffix.h"

#include <Q3TextStream>
#include "MiniLexicon.h"
#include "Stem.h"
#include "WordCollection.h"
#include "StringSurrogate.h"
#include "CompareFunc.h"
#include "Typedefs.h"

// construction/destruction.

CSuffix::CSuffix( CMiniLexicon* mini ) : CAffix( mini )
{}

CSuffix::CSuffix (const CStringSurrogate& Key, CMiniLexicon* mini ): CAffix(Key, mini) 
{}

CSuffix::~CSuffix()
{}



//-----------------------------------------------------------------
// Other methods
//-----------------------------------------------------------------


// TODO: Rewrite for Qt
// Create the list item to be displayed in
// the triscreen
//
// Parameters:
//		List - the list item to be built
//		Line - what line it will be displayed
//		on

void CSuffix::ListDisplay(Q3ListView* List, StringToString* filter, bool ExpressDeletees, int char_count )
{
	CParse display;
	Express( display, ExpressDeletees ); 
	static_cast<void>(new CSuffixListViewItem(List,
		display.Display(QChar(), filter),
		this, filter, char_count));
}


// Remerge all words that use this suffix into a 
// single piece
//
// Parameters:
//		Lexicon - holds stem-->suffix relationship
//		information

void	CSuffix::MergeMeWithMyStems (CMiniLexicon* Lexicon)
{
	CStringSurrogate ssSuffix = GetKey(),
					ssStem;
	CParse			Word;
	CStem*			pWord = NULL;


	for (int j = 1; j <= (int)GetStemString()->Size(); j++)
	{
		ssStem = GetStemString()->GetPiece(j);
		Word = ssStem + ssSuffix;
		pWord = *Lexicon->GetWords() ^= Word;
		if (pWord) 
		{
			pWord->ClearRootSuffixSplit();
		}
	}
}

QString CSuffix::DisplaySuffix(  bool ExpressDeletees )
{
	QString Outstring;
	QString ltSq = "<", 
			rtSq = ">",
			ltCu = "{",
			rtCu = "}";

	if ( ExpressDeletees && m_Deletees.GetKeyLength() > 0 )
	{
        Outstring += ltSq;
        Outstring += m_Deletees.Display();
        Outstring += rtSq;
    }
	if ( ExpressDeletees && m_Morphees.GetKeyLength() > 0 )
	{
		QString strMorphees = m_Morphees.Display();
		CSS ssMorphees( strMorphees );
		Outstring += ltCu ;
		Outstring += ssMorphees.Display() ;
		Outstring += rtCu ;
	}

	Outstring += GetKey().Display();
 
	return Outstring;
}


CParse& CSuffix::Express( CParse& Output, bool ExpressDeletees )
{
	Output.ClearParse();
	QString ltSq = "<", 
			rtSq = ">",
			ltCu = "{",
			rtCu = "}";

	if ( ExpressDeletees && m_Deletees.GetKeyLength() > 0 )
	{
		QString strDeletees = m_Deletees.Display();
		CSS ssDeletees( strDeletees );
		Output.Append( ltSq );
		Output.Append( ssDeletees );
		Output.Append( rtSq );
	}
	if ( ExpressDeletees && m_Morphees.GetKeyLength() > 0 )
	{
		QString strMorphees = m_Morphees.Display();
		CSS ssMorphees( strMorphees );
		Output.Append( ltCu );
		Output.Append ( ssMorphees );
		Output.Append( rtCu );
	}

	Output.Append ( GetKey() );
	Output.SimplifyParseStructure();
	return Output;
}


void CSuffix::OutputSuffix( Q3TextStream& outf )
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

#include "affix_list_view_item.tcc"
template class linguistica::affix_list_view_item<CSuffix>;
