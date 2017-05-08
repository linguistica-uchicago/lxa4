// Implementation of CAffix methods
// Copyright © 2009 The University of Chicago
#include "Affix.h"
#include "Stem.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Typedefs.h"
#include "log2.h"

// construction/destruction.

/// skeleton of an affix object owned by mini.
/// one should probably initialize the underlying CLParse object with
/// CLParse methods afterwards.
CAffix::CAffix(CMiniLexicon* mini)
	: CLParse(mini),
	m_UseCount(0),
	m_StemString(),
        m_StemPtrList(new QList<CStem*>),
	m_CompressedLength(0.0),
	m_Deletees(),	// initialized below
	m_Morphees(),	// initialized below
	m_LengthOfPointerToMe(0.0),
	m_PhonologicalInformationContent(0.0),
	m_UnigramLogProb(0.0),
	m_BigramLogProb(0.0)
{
	m_Deletees.Alphabetize();
	m_Morphees.Alphabetize();
}

/// affix object owned by mini, with underlying string str
/// Copies in the string str, so it’s okay if str becomes invalid later.
CAffix::CAffix(const CStringSurrogate& str,
	CMiniLexicon* mini)
	: CLParse(str, mini),
	m_UseCount(0),
	m_StemString(),
        m_StemPtrList(new QList<CStem*>),
	m_CompressedLength(0.0),
	m_Deletees(),	// initialized below
	m_Morphees(),	// initialized below
	m_LengthOfPointerToMe(0.0),
	m_PhonologicalInformationContent(0.0),
	m_UnigramLogProb(0.0),
	m_BigramLogProb(0.0)
{
	m_Deletees.Alphabetize();
	m_Morphees.Alphabetize();
}

CAffix::~CAffix() { delete m_StemPtrList; }

//-------------------------------------------
// Public mutator/accessor methods
//-------------------------------------------


// Increment the count of how many times this
//
// Parameters:
//		n - the amount to increment

/**
	Increment the number of stems associated with this CAffix.
 */
void CAffix::IncrementUseCount (int n) 
{ 
	m_UseCount += n;
	Q_ASSERT ( m_UseCount > 0);
	Q_ASSERT ( m_UseCount < 1000000 );
}


// Append a new stem to the string without
// adding it to the list of stem pointers
//
// Parameters:
//		Stem - the new stem

/** 
	Append a new CStringSurrogate stem representation to the list of stems. <kbd>Stem</kbd>
	is a surrogate of the string to be added.
 */
void CAffix::AppendToStemString(const CStringSurrogate& Stem)
{
 
	if( !m_StemString.Contains( Stem ) ) m_StemString.Append(Stem);
}


// Add a stem to the list of stems and append
// to the stem string
//
// Parameters:
//		pStem - the stem to be added

/**
	Add a new CStem pointer to the list of stems. <kbd>pStem</kbd> is a pointer
	to the stem that will be added.
 */
void CAffix::AddStem(CStem* pStem)
{
        if( ! m_StemPtrList->contains(pStem) )
	{
		m_StemPtrList->append(pStem);
		AppendToStemString( pStem->GetKey() );
	}
}


// Remove a stem from the list of stem pointers
//
// Parameters:
//		pStemToRemove - pointer to the stem that 
//		will be	removed from the list

/**
	Remove a CStem pointer from the list of stems. <kbd>pStemToRemove</kbd> is
	a pointer to the stem that will be removed.
 */
void CAffix::RemoveFromStemPtrList(CStem* pStemToRemove)
{
        m_StemPtrList->removeAll(pStemToRemove);
}


// Remove a stem from the string without attempting
// to remove it from the pointer list
//
// Parameters:
//		ssStem - the stem to be removed

/**
	Remove a CStringSurrogate stem representation from the list of stems. <kbd>ssStem</kbd>
	is the surrogate string to be removed.
 */
void CAffix::RemoveStemString(const CStringSurrogate& ssStem )
{
	m_StemString.Remove( ssStem );
}


/**
	Add a CStringSurrogate deletee. Deletees are substrings that are deleted
	from an allomorph. <kbd>ssDeletee</kbd> is a surrogate representation
	of the deletee.
 */
void CAffix::AddDeletee( CStringSurrogate ssDeletee )
{
	if( !m_Deletees.Contains( ssDeletee ) ) 
	{
		m_Deletees.Append( ssDeletee );
	}
}

/**
	Add a CStringSurrogate morphee pair. Morphees are substrings that are
	different in an allomorph. <kbd>y</kbd> is the substring that is changed.
	<kbd>i</kbd> is the substring <i>y</i> is changed into.
 */
void CAffix::AddMorphee	( CStringSurrogate y, CStringSurrogate i )
{
	QString New;
	New = y.Display() + "\\" + i.Display();
	if( !m_Morphees.Contains( New ) )
	{
		m_Morphees.Append (New);
	}
}
QString CAffix::ExpressAffix( bool ExpressDeletees )
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
		Outstring +=ltCu ;
		Outstring += ssMorphees.Display();
		Outstring += rtCu ;
	}

    Outstring += GetKey().Display() ;
 	return Outstring;
}


double CAffix::GetLengthOfPointerToMe()
{
      if (m_LengthOfPointerToMe <= 0)
	{ 
           bool CORPUS_BASED_AFFIX_COUNT = m_pMyMini->GetIntParameter( "SignatureDL\\CorpusBasedAffixCount", 0 );
 	   if (CORPUS_BASED_AFFIX_COUNT )
	   {
		m_LengthOfPointerToMe = base2log ( m_pMyMini->GetCorpusCount () / GetCorpusCount()  );
	   }
	   else
	   {
 		m_LengthOfPointerToMe = base2log ( m_pMyMini->GetCorpusCount () / GetCorpusCount()   );
	   }
       }
      return m_LengthOfPointerToMe;
}

double CAffix::GetPhonologicalInformationContent()
{
	if (m_PhonologicalInformationContent == 0)
        {
           bool CORPUS_BASED_AFFIX_COUNT = m_pMyMini->GetIntParameter( "SignatureDL\\CorpusBasedAffixCount", 0 );
 	   if (CORPUS_BASED_AFFIX_COUNT )
	   {
		m_PhonologicalInformationContent = base2log ( m_pMyMini->GetCorpusCount () / GetCorpusCount()  );
	   }
	   else
	   {
 		m_PhonologicalInformationContent = base2log ( m_pMyMini->GetCorpusCount () / GetCorpusCount()   );
	   }
        }
	return m_PhonologicalInformationContent;
}


void CAffix::CalculatePhonologicalInformationContent ( CLexicon* Lexicon )
{
	if (m_BigramLogProb > 0) 
	{
		m_PhonologicalInformationContent = m_BigramLogProb;
	}
	else
	{
		m_PhonologicalInformationContent = ComputeDL( Lexicon->GetNumberOfCharacterTypes() );
	}	
	return; 
}
 
