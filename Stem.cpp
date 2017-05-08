// Implementation of CStem methods
// Copyright © 2009 The University of Chicago
#include "Stem.h"

#include <Q3TextStream>
#include <QList>
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "EarleyParser.h"
#include "Signature.h"
#include "Prefix.h"
#include "Suffix.h"
#include "Biphone.h"
#include "Phone.h"
#include "BiphoneCollection.h"
#include "PhoneCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "log2.h"
#include "Typedefs.h"

CLexicon* CStem::m_Lexicon;  // assign value !  :TODO

//--------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------

CStem::CStem( CMiniLexicon* mini ): CLParse( mini )
{
  m_BrokenForm			= NULL;
  m_Confidence			= "";
  m_NumberOfStems		= 0;
  m_pPrefix			= NULL;
  m_pPrefixSignature            = NULL;
  m_PrefixLoc			= 0;
  m_pStem			= 0;
  m_pSuffix			= NULL;
  m_pSuffixSignature            = NULL;
  m_Regular			= 0;
  m_SimpleFlag			= false;
  m_Stem2Loc			= 0;
  m_StemLoc			= 0;
  m_SuffixLoc			= 0;
  m_WordCount			= 0;
  m_StemType			= UNKNOWN;
  m_WordPtrList			= new QList<CStem*>();
  m_LengthOfPointerToMe         = 0;
  m_MyEarleyParser              = NULL;
  m_UnigramLogProb		= 0;
  m_BigramLogProb		= 0;
  m_BigramComplexity            = 0; // average
  m_UnigramComplexity           = 0; // average
  m_Tier2_LocalMI_Score         = 0;
  m_Tier2_DistantMI_Score       = 0;
  m_LocalMI_Plog		= 0;
  m_DistantMI_Plog		= 0;
  m_HMM_LogProbability          = 0;

  m_SuffixList.Alphabetize();
  m_PrefixList.Alphabetize();

  m_CompoundCount               = 0.0;
  m_Affixness                   = 0.0;
  m_PhonologicalContent         = 0;
  m_donephonology               = false;
}


CStem::CStem(const CStringSurrogate& ssStem, CMiniLexicon* mini ): CLParse(ssStem, mini)
{
  m_BrokenForm   	= NULL;
  m_Confidence    	= "";
  m_NumberOfStems 	= 0;
  m_pPrefix      	= NULL;
  m_pPrefixSignature = NULL;
  m_PrefixLoc      	= 0;
  m_pStem        	= 0;
  m_pSuffix      	= NULL;
  m_Regular      	= 0;
  m_SimpleFlag    	= false;
  m_Stem2Loc      	= 0;
  m_StemLoc      	= 0;
  m_SuffixLoc      	= 0;
  m_pSuffixSignature  = NULL;
  m_WordCount      	= 0;
  m_StemType      	= UNKNOWN;
  m_WordPtrList 	= new QList<CStem*>();
  m_MyEarleyParser	= NULL;

  m_UnigramLogProb 		= 0;
  m_BigramLogProb 		= 0;
  m_BigramComplexity 	= 0;
  m_UnigramComplexity 	= 0;
  m_Tier2_LocalMI_Score = 0;
  m_Tier2_DistantMI_Score = 0;
  m_LocalMI_Plog 		= 0;
  m_DistantMI_Plog 		= 0;
  m_HMM_LogProbability    = 0;
  m_SuffixList.Alphabetize();
  m_PrefixList.Alphabetize();

  m_CompoundCount  = 0.0;
  m_Affixness = 0.0;
  m_LengthOfPointerToMe = 0;
  m_PhonologicalContent = 0;

  m_donephonology = false; 
}

CStem::CStem(CStem& Stem): CLParse (Stem, Stem.GetMyMini())
{
  m_BrokenForm          = NULL;
  m_Confidence          = Stem.GetConfidence();
  m_NumberOfStems       = Stem.GetNumberOfStems();
  m_pPrefix             = Stem.GetPrefixPtr();
  m_pPrefixSignature    = Stem.GetPrefixSignature();
  m_PrefixLoc           = Stem.GetPrefixLoc();
  m_pStem               = Stem.GetStemPtr();
  m_strStem             = Stem.m_strStem;
  m_pSuffix             = Stem.GetSuffixPtr();
  m_pSuffixSignature    = Stem.GetSuffixSignature();
  m_Regular             = Stem.GetRegular();
  m_SimpleFlag          = Stem.GetSimpleFlag();
  m_Stem2Loc            = Stem.GetStem2Loc();
  m_StemLoc             = Stem.GetStemLoc();
  m_StemType            = Stem.GetStemType();
  m_SuffixLoc           = Stem.GetSuffixLoc();
  m_WordCount           = Stem.GetWordCount();
  m_LengthOfPointerToMe	= Stem.GetLengthOfPointerToMe();
  m_WordPtrList         = new QList<CStem*>();
  QList<CStem*>* list   = Stem.GetWordPtrList();
  for (int z = 0; z < list->size(); z++)
  {
        m_WordPtrList->append( list->at(z) );
  }
  m_MyEarleyParser       = NULL;

  m_Phonology_Tier1 = Stem.m_Phonology_Tier1;
  m_Phonology_Tier2 = Stem.m_Phonology_Tier2;
  m_Phonology_Tier1_Skeleton = Stem.m_Phonology_Tier1_Skeleton;
  m_UnigramLogProb = Stem.m_UnigramLogProb;
	m_BigramLogProb = Stem.m_BigramLogProb;
	m_BigramComplexity = Stem.m_BigramComplexity;
	m_UnigramComplexity = Stem.m_UnigramComplexity;
	m_Tier2_LocalMI_Score  = Stem.GetTier2_LocalMI_Score();
	m_Tier2_LocalMI_Score  = Stem.GetTier2_DistantMI_Score();

  m_CompoundCount  = Stem.GetCompoundCount();
  m_Affixness = Stem.GetAffixness();
  m_PhonologicalContent = 0;

  m_donephonology = Stem.m_donephonology; 

}


CStem::CStem(const CLParse& LParse): CLParse (LParse, LParse.GetMyMini())
{
  m_BrokenForm    = NULL;
  m_Confidence    = "";
  m_NumberOfStems    = 0;
  m_pPrefix      = NULL;
  m_pPrefixSignature  = NULL;
  m_PrefixLoc      = 0;
  m_pStem        = 0;
  m_pSuffix      = NULL;
  m_Regular      = 0;
  m_SimpleFlag    = false;
  m_Stem2Loc      = 0;
  m_StemLoc      = 0;
  m_SuffixLoc      = 0;
  m_pSuffixSignature  = NULL;
  m_WordCount      = 0;
  m_StemType      = UNKNOWN;
  m_WordPtrList = new QList<CStem*>();
  m_MyEarleyParser       = NULL;

//  m_SuffixList.SetAlphabetical();
//  m_PrefixList.SetAlphabetical();
  	m_UnigramLogProb = 0;
	m_BigramLogProb = 0;
	m_BigramComplexity = 0;
	m_UnigramComplexity = 0;
	
	m_LengthOfPointerToMe = 0;

  m_CompoundCount  = 0.0;
  m_Affixness = 0.0;
  m_PhonologicalContent = 0;

  m_donephonology = false; 
}


CStem::CStem(const CParse& Parse, CMiniLexicon* mini ): CLParse (Parse, mini)
{
  m_BrokenForm    = NULL;
  m_Confidence    = "";
  m_NumberOfStems    = 0;
  m_pPrefix      = NULL;
  m_pPrefixSignature  = NULL;
  m_PrefixLoc      = 0;
  m_pStem        = 0;
  m_pSuffix      = NULL;
  m_pSuffixSignature  = NULL;
  m_Regular      = 0;
  m_SimpleFlag    = false;
  m_Stem2Loc      = 0;
  m_StemLoc      = 0;
  m_SuffixLoc      = 0;
  m_WordCount      = 0;
  m_StemType      = UNKNOWN;
  m_WordPtrList = new QList<CStem*>();
  m_MyEarleyParser       = NULL;

//  m_SuffixList.SetAlphabetical();
//  m_PrefixList.SetAlphabetical();
  m_UnigramLogProb = 0;
  m_BigramLogProb = 0;
  m_BigramComplexity = 0;
  m_UnigramComplexity = 0;


  m_CompoundCount  = 0.0;
  m_Affixness = 0.0;
  m_PhonologicalContent = 0;

  m_donephonology = false; 
	m_LengthOfPointerToMe = 0;

}


CStem::~CStem()
{
  if( m_BrokenForm ) delete m_BrokenForm;
  if( m_WordPtrList ) delete m_WordPtrList;
  if( m_MyEarleyParser) delete m_MyEarleyParser;
}



//-----------------------------------------------------------------
// Overloaded operators
//-----------------------------------------------------------------

void CStem::operator= (const CStem& RHS)
{
  CopyParse(RHS);

  m_BrokenForm					= NULL;
  m_Confidence					= RHS.GetConfidence();
  m_NumberOfStems				= RHS.GetNumberOfStems();
  m_pPrefix						= RHS.GetPrefixPtr();
  m_pPrefixSignature			= RHS.GetPrefixSignature();
  m_PrefixLoc					= RHS.GetPrefixLoc();
  m_pStem						= RHS.GetStemPtr();
  m_pSuffix						= RHS.GetSuffixPtr();
  m_pSuffixSignature			= RHS.GetSuffixSignature();
  m_Regular						= RHS.GetRegular();
  m_SimpleFlag					= RHS.GetSimpleFlag();
  m_Stem2Loc					= RHS.GetStem2Loc();
  m_StemLoc						= RHS.GetStemLoc();
  m_StemType					= RHS.GetStemType();
  m_SuffixLoc					= RHS.GetSuffixLoc();
  m_WordCount					= RHS.GetWordCount();
  m_Phonology_Tier1				= RHS.m_Phonology_Tier1;
  m_Phonology_Tier2				= RHS.m_Phonology_Tier2;
  m_Phonology_Tier1_Skeleton	= RHS.m_Phonology_Tier1_Skeleton;
  m_CompoundCount				= RHS.GetCompoundCount();
  m_Affixness					= RHS.GetAffixness();
  m_MyEarleyParser              = RHS.GetMyEarleyParser();
//  m_LengthOfPointerToMe			= RHS.GetLengthOfPointerToMe();

//  m_SuffixList.SetAlphabetical();
//  m_PrefixList.SetAlphabetical();

}


void CStem::Copy (CStem& RHS)
{
  CopyParse(RHS);

  m_BrokenForm    = NULL;
  m_Confidence    = RHS.GetConfidence();
  m_NumberOfStems    = RHS.GetNumberOfStems();
  m_pPrefix      = RHS.GetPrefixPtr();
  m_pPrefixSignature  = RHS.GetPrefixSignature();
  m_PrefixLoc      = RHS.GetPrefixLoc();
  m_pStem        = RHS.GetStemPtr();
  m_pSuffix      = RHS.GetSuffixPtr();
  m_pSuffixSignature  = RHS.GetSuffixSignature();
  m_Regular      = RHS.GetRegular();
  m_SimpleFlag    = RHS.GetSimpleFlag();
  m_Stem2Loc      = RHS.GetStem2Loc();
  m_StemLoc      = RHS.GetStemLoc();
  m_StemType      = RHS.GetStemType();
  m_SuffixLoc      = RHS.GetSuffixLoc();
  m_WordCount      = RHS.GetWordCount();
  m_MyEarleyParser = RHS.GetMyEarleyParser();
//  m_SuffixList.SetAlphabetical();
//  m_PrefixList.SetAlphabetical();

  m_CompoundCount  = RHS.GetCompoundCount();
  m_Affixness = RHS.GetAffixness();
  	m_LengthOfPointerToMe = RHS.GetLengthOfPointerToMe();
}

 

//-----------------------------------------------------------------
// Other methods
//-----------------------------------------------------------------


// Copy utility for stems
//
// Parameters:
//    RHS - the stem to be copied

void CStem::CopyStemInformation(CStem* RHS)
{
  m_Confidence = RHS->GetConfidence();
  SetCorpusCount(RHS->GetCorpusCount());
  m_NumberOfStems  = RHS->GetNumberOfStems();
  m_pPrefix = RHS->GetPrefixPtr();

  if ( RHS->GetPrefixList() )
  {
    m_PrefixList = RHS->GetPrefixList();
  }

  m_PrefixLoc = RHS->GetPrefixLoc();

  if ( RHS->GetPrefixSignature() )
  {
    m_pPrefixSignature = RHS->GetPrefixSignature();
  }

  m_pStem  = RHS->GetStemPtr();
  m_pSuffix = RHS->GetSuffixPtr();
  m_Regular = RHS->GetRegular();
  m_SimpleFlag = RHS->GetSimpleFlag();
  m_Stem2Loc = RHS->GetStem2Loc();
  m_StemLoc = RHS->GetStemLoc();
  m_StemType = RHS->GetStemType();
  m_SuffixLoc  = RHS->GetSuffixLoc();

  if ( RHS->GetSuffixList() )
  {
    m_SuffixList = RHS->GetSuffixList();
  }

  if ( RHS->GetSuffixSignature() )
  {
    m_pSuffixSignature = RHS->GetSuffixSignature();
  }

  m_WordCount = RHS->GetWordCount();

  CStem* word;
  for (int z = 0; z < RHS->GetWordPtrList()->size(); z++)
  {     word = RHS->GetWordPtrList()->at(z);
        m_WordPtrList->append( word );
    }

  m_CompoundCount  = RHS->GetCompoundCount();
  m_Affixness = RHS->GetAffixness();
  	m_LengthOfPointerToMe =  RHS->GetLengthOfPointerToMe();
    m_MyEarleyParser = RHS->GetMyEarleyParser();
}




// Add the prefix 'NULL' to the list of prefixes

void CStem::AddNULLPrefix()
{
  m_WordCount++;
  QString Null = "NULL";
  if ( ! m_PrefixList.ContainsNULL() )
  {
//    if(!m_PrefixList.Alphabetical()) m_PrefixList.Alphabetize();
    m_PrefixList.Append (CStringSurrogate(Null.unicode(),0,Null.length()));
  }
}


// Add the suffix 'NULL' to the list of suffixes

void CStem::AddNULLSuffix()
{
  m_WordCount++;
  QString Null = "NULL";
  if ( ! m_SuffixList.ContainsNULL() )
  {
//    if(!m_SuffixList.Alphabetical()) m_SuffixList.Alphabetize();
    m_SuffixList.Append (CStringSurrogate(Null.unicode(),0,Null.length()));
  }
}


// Add a word to the word list

bool CStem::AddWord (CStem* pWord)
{
        if ( m_WordPtrList->indexOf(pWord) < 0 )
	{
		m_WordPtrList->append (pWord);
		return TRUE;
	}
	return FALSE;
}


// Add a prefix to the prefix list
//
// Parameters:
//    pPrefix - pointer to the prefix to
//    be added

void CStem::AddPrefix (CPrefix* pPrefix)
{
  if (! ContainsPrefix (pPrefix)) {
//    if(!m_PrefixList.Alphabetical()) m_PrefixList.Alphabetize();
    m_PrefixList.Append (pPrefix->GetKey());
  }
}


// Add a suffix to the suffix list
//
// Parameters:
//    pSuffix - pointer to the suffix to
//    be added

void CStem::AddSuffix(CSuffix* pSuffix)
{
  if ( !ContainsSuffix (pSuffix) ) {
//    if(!m_SuffixList.Alphabetical()) m_SuffixList.Alphabetize();
    m_SuffixList.Append (pSuffix->GetKey());
  }
}

 


// Add a suffix to the suffix list
//
// Parameters:
//    key - surrogate string of the suffix to
//    be added

void CStem::AddSuffix(const CStringSurrogate& key)
{
  if ( !m_SuffixList.Contains (key) ) {
//    if(!m_SuffixList.Alphabetical()) m_SuffixList.Alphabetize();
    m_SuffixList.Append (key);
  }
}


// Copy a list of suffixes into the suffix list
//
// Parameters:
//    pParse - the list of new suffixes

void CStem::CopySuffixList(CParse* pParse)
{
  for (int i = 1; i <= (int)pParse->Size(); i++)
  {
    AddSuffix ( pParse->GetPiece(i) );
  }
}


// Find out if the prefix list contains a specific
// prefix
//
// Parameters:
//    Prefix - the prefix in question
//
// Returns:
//    bool - true if the prefix is in our list

bool  CStem::ContainsPrefix(CPrefix* Prefix) const
{
  if ( m_PrefixList.Contains (Prefix->GetKey()) ) {
    return true;
  } else {
    return false;
  }
}

bool  CStem::ContainsPrefix(const CStringSurrogate& Prefix) const
{
  if ( m_PrefixList.Contains (Prefix) ) {
    return true;
  } else {
    return false;
  }
}

QString	CStem::GetSortingString	()	
{ 
	QString sortString = GetSuffixList()->Display(); return sortString; 
}
// Add a prefix to the prefix list
//
// Parameters:
//    Prefix - prefix surrogate to be added be added

void CStem::AddPrefix(const CStringSurrogate& Prefix)
{
  if ( !ContainsPrefix (Prefix) )
  {
    m_PrefixList.Append (Prefix);
  }
}


// Find out if the suffix list contains a specific
// suffix
//
// Parameters:
//    Suffix - the suffix to look for
//
// Returns:
//    bool - true if the suffix is in the list

bool  CStem::ContainsSuffix(CSuffix* Suffix) const
{
  if (m_SuffixList.Contains (Suffix->GetKey() ) ){
    return true;
  } else {
    return false;
  }
}


// Increment the word count
//
// Parameters:
//    n - amount to increment, default = 1

void CStem::IncrementWordCount (int n )
{
  m_WordCount += n;
  Q_ASSERT (m_WordCount > 0);
  Q_ASSERT (m_WordCount < 1000000);
}


// Get the prefix
//
// Parameters:
//    Prefix - the parse to put the prefix in

void    CStem::GetPrefix ( CParse& Prefix ) const
{
    if (m_strPrefix.GetKeyLength() > 0) {
        Prefix =  m_strPrefix;
        return;
    }
    Prefix = GetPiece( m_PrefixLoc );
}


// Get the suffix
//
// Parameters:
//    Output - the parse to put the suffix in

void    CStem::GetSuffix(CParse& Output ) const
{
  if (m_strSuffix.GetKeyLength() > 0) {
        Output =  m_strSuffix;
        return;
    }
  Output = GetPiece( m_SuffixLoc );
}


// Get the stem
//
// Parameters:
//    Output - the parse to put the stem in

void    CStem::GetStem(CParse& Output) const
{
    if (m_strStem.GetKeyLength() > 0) {
        Output =  m_strStem;
        return;
    }
    Output = GetPiece( m_StemLoc );
}




// Display the type of this stem
//
// Returns:
//    QString - the type of this stem

QString CStem::DisplayStemType() const
{
  switch (m_StemType)
  {
  case NORMAL:
    { return ""; } // return "Normal":
  case BIWORD_COMPOUND:
    { return "2 word compound"; }
  case MULTIPLE_COMPOUND:
    { return "Multiple-word compound"; }
  case POSSIBLE_COMPOUND:
    { return "Possible compound"; };
  case NUMBER:
    { return "Number"; }
  case UNKNOWN:
    { return "??"; }
  case ENDS_IN_HYPHEN:
    { return "Ends in hyphen"; }
  case STEM_COMPOUND:
    { return "Compound"; }
  case STEM_NORMAL:
    { return "Stem"; }
  case STEM_PLUS_SUFFIX:
    { return "Stem & Suffix"; }
  case POLYWORD_PIECE:
    { return "Polyword piece"; }
  default:
    { return "???"; }
  }
}


// Merge the prefix and stem

void CStem::ClearPrefixStemSplit()
{
  if ( m_StemLoc && m_PrefixLoc)
  {
    MergePieces (m_PrefixLoc);
  }

  m_PrefixLoc = 0;
  m_StemLoc = 1;
}



 
// Merge the root and suffix

void CStem::ClearRootSuffixSplit()
{
  if ( m_StemLoc && HasASuffix()  )
  {
    MergePieces (m_StemLoc);
  }
  if ( m_StemLoc == 1)
  {
    m_StemLoc  = 0;
  }
}

// Calculate the description length
//
// Returns:
//    float - the descrition length

float CStem::CalculateDL() const
{
  //float Value = 0;

  const float  PointerLength = (float) base2log ( 27 );

  return PointerLength * GetKeyLength();  // -cs- 01/31 : return PointerLength * GetLength();
}


// TODO : define this function
// Get the sorting quantity
//
// Returns:
//    float - the sorting quantity

float CStem::GetSortingQuantity() const
{
  Q_ASSERT (0);
  return 0;
}

/// used in allomorphy code.
void CStem::RepairSuffixList(const CMiniLexicon* Lexicon)
{
	struct not_implemented { };
	throw not_implemented();
	static_cast<void>(Lexicon);

//	QString NewSuffix;
//	CSuffix* pNewSuffix;

//	for (int i = 1; i <= m_SuffixList.Size(); ++i) {
		// TODO: Get John's help to fix, I don't understand.
//		CStringSurrogate ssSuffix = m_SuffixList.GetPiece(i);
//		CSuffix* pOldSuffix = *Lexicon->GetSuffixes() ^= ssSuffix;

//		SuffixStringTranslation.GetPiece(ssSuffix.SpellOut(), NewSuffix);
//		pNewSuffix = *Lexicon->GetSuffixes() ^=
//	}
}

// Detach a specific suffix from the list
//
// Parameters:
//    pSuffix - the suffix to detach

void CStem::DetachSuffix(CSuffix* pSuffix)
{
  Q_ASSERT (pSuffix);
  m_SuffixList.Remove ( pSuffix->GetKey() );
  pSuffix->RemoveFromStemPtrList ( this );
  pSuffix->RemoveStemString ( GetKey() );
}



// Detach a specific prefix from the list
//
// Parameters:
//    pPrefix - the prefix to detach

void CStem::DetachPrefix(CPrefix* pPrefix)
{
  Q_ASSERT (pPrefix);
  m_PrefixList.Remove ( pPrefix->GetKey() );
  pPrefix->RemoveFromStemPtrList ( this );
  pPrefix->RemoveStemString ( GetKey() );
}


// Remove a word from the word list
//
// Parameters:
//    pWord - pointer to the word to be removed

void CStem::RemoveWordFromWordPtrList(CStem* pWord)
{

  m_WordPtrList->remove(pWord);

}


// Replace the old suffix signature and return it
//
// Parameters:
//    pNewSig - the new signature
//
// Returns:
//    CSignature* - the old signature

CSignature* CStem::ChangeSuffixSignature(CSignature* pNewSig)
{
  CSignature* pOldSig = m_pSuffixSignature;

  if ( pOldSig )
  {
    pOldSig->DetachStem (this, eCall_Words );
  }

  m_pSuffixSignature = pNewSig;

  return pOldSig;
}


CParse* CStem::GetPhonology_Tier1 () { return &m_Phonology_Tier1; }

CParse* CStem::GetPhonology_Tier2 () { return &m_Phonology_Tier2; }


void CStem::CreatePhonologyFromOrthography(eAddBoundarySymbols AddBoundaries)
{
	int i;

	if (m_Phonology_Tier1.GetKeyLength() > 0 ) return;

	if (AddBoundaries == BOUNDARIES) 
	{
		m_Phonology_Tier1.Append (QChar('#'));
	}

	for (i = 0; i < GetKeyLength(); i++)
	{
		m_Phonology_Tier1.Append ( CSS(m_Key,i,1) );
	}

	if (AddBoundaries == BOUNDARIES) 
	{
		m_Phonology_Tier1.Append (QChar('#'));
	}
}

void CStem::SetPhonology_Tier1 (CParse* PhonoRep)
{
	 
	m_Phonology_Tier1.Append (QChar('#'));
	m_Phonology_Tier1.Append (PhonoRep);
	m_Phonology_Tier1.Append (QChar('#'));
	QString temp = m_Phonology_Tier1.Display();
}

void CStem::SplitPhonologyToTiers (ePhonologySplitType Type, CParse& PhonesToMove)
{
	const QString DummySymbol = "*";

	m_Phonology_Tier2.ClearParse();
	QString temp = PhonesToMove.Display();
	QString TheWord = m_Phonology_Tier1.Display();

	for (int i = 1; i <= m_Phonology_Tier1.Size(); i++)
	{
		if (PhonesToMove.Contains ( m_Phonology_Tier1.GetPiece(i) ) )
		{			
			m_Phonology_Tier2.Append ( m_Phonology_Tier1.GetPiece(i) );
			
			if ( Type == Split_LeaveSlot )
			{
				CSS dummy( DummySymbol );
				m_Phonology_Tier1.Replace (i, dummy );
				QString temp2 = m_Phonology_Tier1.Display();
			}
			QString temp3 = m_Phonology_Tier2.Display();
		}
	}


}
 
void CStem::CreateCVTemplate (CParse* Vowels)
// this is here specifically to do probabilistic tests on projections to C and V. 
{
	QString V ("V"), C("C"); QString boundary ("#");
	
	m_Phonology_Tier1_Skeleton.ClearParse();
	m_Phonology_Tier1_Skeleton.Append ( boundary );
 	
	CParse VowelsAndAsterisk ( *Vowels);
	VowelsAndAsterisk.Append ('*');
 

	for (int i = 2; i < m_Phonology_Tier1.Size(); i++)
	{
		QString b; b= m_Phonology_Tier1.GetPiece(i).Display();
		if (VowelsAndAsterisk.Contains ( m_Phonology_Tier1.GetPiece(i) ) )
		{
			m_Phonology_Tier1_Skeleton.Append ( V );
		}
		else
		{
			m_Phonology_Tier1_Skeleton.Append ( C );
		}
	}
	m_Phonology_Tier1_Skeleton.Append ( boundary );
}

void CStem::ComputeProbabilities(CWordCollection* Words)
{
	int i;
	CPhone*				pPhone, *prevPhone, *qPhone;
	prevPhone=NULL;
	
	QString				biphone;
	CBiphone*			pBiphone;

	m_BigramLogProb					= 0;
	m_UnigramLogProb				= 0;

	m_Tier2_LocalMI_Score			= 0;
	m_Tier2_DistantMI_Score			= 0;

	m_LocalMI_TotalBoltzmannScore	= 0;	
	m_DistantMI_TotalBoltzmannScore	= 0;

	QString temp = Display();

	for (i= 1; i <= m_Phonology_Tier1.Size(); i++)
	{
		QString temp2 = m_Phonology_Tier1.GetPiece (i).Display();
		pPhone = *Words->GetPhones() ^= m_Phonology_Tier1.GetPiece (i);
		Q_ASSERT (pPhone);
		if (i == 1)
		{
			prevPhone = pPhone;
			continue;
		}
		m_UnigramLogProb += pPhone->m_LogFreq; 
 
		pBiphone = Words->GetPhones()->GetMyBiphones()->GetBiphone (prevPhone, pPhone);	
		if ( !pBiphone ) 
		{
			return ;
		}
		
		double mi = pBiphone->m_MI;

		m_BigramLogProb += pPhone->m_LogFreq - mi;
		prevPhone = pPhone;

	}
	m_UnigramComplexity = m_UnigramLogProb / (m_Phonology_Tier1.Size()-1);
	m_BigramComplexity  = m_BigramLogProb  / (m_Phonology_Tier1.Size()-1);

	if (m_Phonology_Tier2.Size() == 0 ) return;


	for (i = 1; i <= m_Phonology_Tier2.Size(); i++)
	{		
		pPhone = *Words->GetPhones() ^= m_Phonology_Tier2.GetPiece (i);		
		if (i == 1)
		{
			prevPhone = pPhone;
			continue;
		}
		
		//QString temp; temp = prevPhone->Display() + "--" + pPhone->Display();
		pBiphone = Words->GetPhones_Tier2()->GetMyBiphones()->GetBiphone (prevPhone, pPhone);	
		if ( !pBiphone ) 
		{
			return ;
		}
		else
		{
			m_Tier2_LocalMI_Score += pBiphone->m_MI;
		}
		prevPhone = pPhone;
	}
	
	m_LocalMI_TotalBoltzmannScore = m_BigramLogProb - m_Tier2_LocalMI_Score;
	
	//m_FieldComplexity = 0;
	m_Tier2_DistantMI_Score = 0;
	
	for (i = 1; i <= m_Phonology_Tier2.Size(); i++)
	{		
		pPhone = *Words->GetPhones() ^= m_Phonology_Tier2.GetPiece (i);		
		for (int j= i+1; j <= m_Phonology_Tier2.Size(); j++)
		{
			qPhone = *Words->GetPhones() ^= m_Phonology_Tier2.GetPiece (j);	
			QString temp; temp = pPhone->Display() + "--" + qPhone->Display();
			pBiphone = Words->m_Phones_Tier2->GetMyBiphones()->GetBiphone (pPhone, qPhone);	
			if (pBiphone)
			{
				m_Tier2_DistantMI_Score += pBiphone->m_MI / (j-i);
			}
		}
	}

	m_DistantMI_TotalBoltzmannScore = m_BigramLogProb - m_Tier2_DistantMI_Score;
	return; 

}

void	CStem::ComputeBoltzmannProbabilities( double Z, double ZStar)
{	 	
	if (Z != 0 )
	{		
		m_LocalMI_Plog = m_LocalMI_TotalBoltzmannScore + base2log( Z) ;	
	}
	
	if (ZStar != 0)
	{
		m_DistantMI_Plog = m_BigramLogProb - m_Tier2_DistantMI_Score + base2log( ZStar );		
	}
	
}



void	CStem::GetPhonogyTier1InfoForGraph(CWordCollection* Words)
{
	int					i;
	CPhone*				pPhone, *prevPhone;
	prevPhone = NULL;
	QString				biphone;
	CBiphone*			pBiphone;
	double				ugram; 
	double				mi;

	m_phonologies.clear(); 
	m_unigrams.clear(); 
	m_mis.clear();

	m_countofunigrams = 0; 
	m_countofmis = 0; 
	m_maxpositive =0; 
	m_maxnegative =0; 

	for (i= 1; i <= m_Phonology_Tier1.Size(); i++)
	{
		QString temp2 = m_Phonology_Tier1.GetPiece (i).Display();
		pPhone = *Words->GetPhones() ^= m_Phonology_Tier1.GetPiece (i);
		Q_ASSERT (pPhone);
		if (i == 1)
		{
			prevPhone = pPhone;
			continue;
		}
		ugram = pPhone->m_LogFreq; 
 
		pBiphone = Words->GetPhones()->GetMyBiphones()->GetBiphone (prevPhone, pPhone);	
		
		Q_ASSERT (pBiphone);

		mi = pBiphone->m_MI;

		
		m_phonologies.insert(m_countofunigrams, temp2);
		m_unigrams.insert(m_countofunigrams, ugram);
		m_mis.insert(m_countofmis, mi);

		m_countofunigrams++;
		m_countofmis++; 

		prevPhone = pPhone;

		if ( ugram > 0)
		{
			if ( ugram > m_maxpositive)
			{
				m_maxpositive = ugram; 
			}
		}
	
		if ( mi > 0)
		{
			if ( mi > m_maxpositive)
			{
				m_maxpositive = mi; 
			}
		}
		else
		{
			if ( mi < m_maxnegative)
			{
				m_maxnegative = mi; 
			}
		}


	}

	m_donephonology = true; 

}


/*
void CStem::ComputeBoltzmannProbability(CWordCollection* Words)
{
 
	int i;
 
	CBiphone* pBiphone;
	CBiphoneCollection&  Tier2Biphones = *Words->m_Phones_Tier2->GetMyBiphones();
	CPhone*			pPhone, *prevPhone;
	QString			biphone;
 
	QString temp = Display();
	QString temp2 = m_Phonology_Tier2.Display();
 
	//Tier 2 computations: 
	if (Words->m_MyZ > 0 ) 
	{

		m_Tier2_MIScore = 0;

		for (i = 1; i <= m_Phonology_Tier2.Size(); i++)

		{
	 		pPhone = *Words->GetPhones() ^= m_Phonology_Tier2.GetPiece (i);
			Q_ASSERT (pPhone);
			if (i == 1)
			{
				prevPhone = pPhone;
				continue;
			}
			biphone = prevPhone->Display() + "." + pPhone->Display();
			pBiphone = *Words->GetPhones_Tier2()->GetMyBiphones() ^= biphone;
			
			if (! pBiphone ) continue;  // ############################### there should be a check here -->>>>>>
			m_Tier2_MIScore += pBiphone->m_MI;
			prevPhone = pPhone;
		}
		m_BoltzmannLogProb =    m_BigramLogProb  - m_Tier2_MIScore + log (Words->m_MyZ ); // fixed bug, I had subtracted Z instead
	}
}
*/
QString	CStem::GetProbabilityInformation() 
{
	QString Output, MI;


	Output = QString ("\nUnigram log probability %1  \nUnigram complexity  %2  \nBigram log probability  %3 \nBigram complexity %4 \nTier 2 MI score %5\nLocal tier 2 model score: %6 \nLocal tier 2 model log probability: %7 \nDistant tier 2 MI:  %8 \nDistant tier 2 model score %9"  )
		.arg (m_UnigramLogProb )				//1		
		.arg (m_UnigramComplexity )				//3
		.arg (m_BigramLogProb )					//2
		.arg (m_BigramComplexity )				//4
		.arg (m_Tier2_LocalMI_Score )			//5
		.arg (m_LocalMI_TotalBoltzmannScore)	//6
		.arg (m_LocalMI_Plog )					//7
		.arg (m_Tier2_DistantMI_Score )			//8
		.arg (m_DistantMI_TotalBoltzmannScore );	//9

 
	return Output;

}


void CStem::OutputStem( Q3TextStream& outf, int index )
{
	QString confidence;
// "# Index | Stem                 | Confidence           | Corpus Count | Affix Count | Affixes"

	outf << "  ";

	outf.setf(2);
	outf.width(5);
	outf << index + 1;
	outf << "   ";

	outf.width(20);
	outf << Display();
	outf << "   ";

	outf.width(20);
	confidence = GetConfidence();
	if( confidence == "" ) confidence = "NONE";
	outf << confidence.replace( " ", "_" );
	outf << "   ";

	outf.unsetf(2); 
	outf.width(12);
	outf << GetCorpusCount();
	outf << "   ";

	outf.width(11);
	if( GetSuffixSignature() )
	{ 
		outf << GetSuffixSignature()->Size();
		outf << "   ";

		outf.setf(2);
		outf << GetSuffixSignature()->Display( ' ', m_pMyMini->GetOutFilter() );
		outf << " ";
	}
	else if( GetPrefixSignature() )
	{
		outf << GetPrefixSignature()->Size();
		outf << "   ";

		outf.setf(2);
		outf << GetPrefixSignature()->Display( ' ', m_pMyMini->GetOutFilter() );
		outf << " ";
	}
	else
	{
		outf << 0;
		outf << "   ";

		outf.setf(2);
		outf << "NONE";
		outf << " ";
	}

	outf << endl;
}

	
double CStem::GetLengthOfPointerToMe() const
{
	if (m_LengthOfPointerToMe > 0) return m_LengthOfPointerToMe;

	m_LengthOfPointerToMe = base2log ( m_pMyMini->GetStems()->GetCorpusCount () / GetCorpusCount() );



	return m_LengthOfPointerToMe;
}
double CStem::GetLengthOfPointerToMe_2() //JG August 2006  
{
	if (m_LengthOfPointerToMe > 0) return m_LengthOfPointerToMe;

	m_LengthOfPointerToMe = base2log ( m_pMyMini->GetStems()->GetCorpusCount () / GetCorpusCount() );



	return m_LengthOfPointerToMe;
}
 
// Get the corpus counts of each suffix with this stem
//
// Parameters:
//     
int*    CStem::GetSuffixCounts(int* output) 
{
	if (output) delete output; // error if this occurs.
	output = new int[ GetNumberOfSuffixes() ];
	 
	QString		Word, Suffix;
	CStem* 		pWord;
	int i;
	for ( i = 1; i <= m_SuffixList.Size(); i++)
	{
		Suffix = m_SuffixList.GetPiece(i).Display();
		if (Suffix == "NULL") Suffix = ""; 
		Word = Display() + Suffix;
		pWord = *m_pMyMini->GetWords() ^= CSS(Word);
		output[i-1] = pWord->GetCorpusCount();
	}
	return output;
}

double CStem::GetPhonologicalInformationContent(CLexicon* MotherLexicon) const
{
	if (m_PhonologicalContent == 0 && MotherLexicon != 0) 
	{ 
		CalculatePhonologicalInformationContent(MotherLexicon);
	}
	return m_PhonologicalContent;
}

double CStem::CalculatePhonologicalInformationContent(CLexicon* Lexicon) const
{
	
	if (m_BigramLogProb > 0) 
	{
		m_PhonologicalContent = m_BigramLogProb;
	}
	else
	{
		m_PhonologicalContent = 0; // @@@ fix 
		m_PhonologicalContent = ComputeDL( Lexicon->GetNumberOfCharacterTypes() );
	}	
	return m_PhonologicalContent; 
}
 
