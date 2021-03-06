// miscellaneous enums
// Copyright © 2009 The University of Chicago
#ifndef GENERALDEFINITIONS_H
#define GENERALDEFINITIONS_H

enum eParseSortStyle
{
    eNotSorted,
    eAlphabetized,
    eAlphabetizedFromEnd,
    eSortByPieceLength
};

enum eCurrentDisplay
{
	eGraphics, 
	eCollection
};


enum eWhichTree
{
  Upper,
  Lower
};


enum eLxaClass // For preserialization, serialization, deserialization
{
	LINGUISTICA_MAIN_WINDOW,
	LEXICON_CLASS,
	MINI_LEXICON_CLASS,
	WORD_COLLECTION_CLASS,
	STEM_COLLECTION_CLASS,
	COMPOUND_COLLECTION_CLASS,
	LINKER_COLLECTION_CLASS,
	SUFFIX_COLLECTION_CLASS,
	PREFIX_COLLECTION_CLASS,
	SIGNATURE_COLLECTION_CLASS,
	CORPUS_WORD_CLASS,
	STEM_CLASS,
	COMPOUND_CLASS,
	LINKER_CLASS,
	SUFFIX_CLASS,
	PREFIX_CLASS,
	SIGNATURE_CLASS,
	AFFIX_CLASS,
	LPARSE_CLASS,
	PARSE_CLASS,
	TRIE_CLASS,
	TRIE_NODE_CLASS,
	DLHISTORY_CLASS,
	COLLECTION_TEMPLATE,
	NOTHING
};


enum eDocumentType  // for the Collection View
{
  NO_DOC,
  CORPUS_DOC,
  WORDS,
  ANALYZED_WORDS,
  PROPER_NAMES,
  TEMPWORDS,
  STEMS,
  STEMS_SUFFIXED,
  STEMS_PREFIXED,
  ROOTS,
  MDL_TYPE,
  SIGNATURES,
  PREFIX_SIGNATURES,
  SUFFIX_SIGNATURES,
  PREFIX_SIGNATURE_SUBSET,
  INNER_SIGNATURES,
  SIGNATURE_SUBSET,
  SUFFIXES,
  PREFIXES,
  COMPOUNDS,
  COMPOUND_COMPONENTS,
  LINKERS,
  CORPUS_WORDS,
  ANALYZED_CORPUS_WORDS,
  ALL_WORDS,
  ALL_ANALYZED_WORDS,
  ALL_STEMS,
  ALL_SUFFIXES,
  ALL_SUFFIX_SIGNATURES,
  ALL_PREFIXES,
  ALL_PREFIX_SIGNATURES,
  COMPOUND_ELEMENTS, // first and second members of compounds
  TEMP_SUFFIXES,
  TEMP_STEMS,
  GOOD_BEGINNINGS,
  GOOD_ENDINGS,
  POLYMORPHEMES,
  POLYWORDS,
  RULES,
  MORPHEMES,
  FIRST_MORPHEME,
  SECOND_MORPHEME,
  REVERSE_TRIE,
  TRIE,
  EIGENVECTOR,
  COLLAPSE_TWO_SIGNATURES,
  COLLOCATIONS,
  PROBLEM_SIGNATURES,
  LITTLE_SIGNATURES,
  BAD_WORDS,
  PREFIX_TRIE,
  PREFIX_SIGNATURES_OF_ROOTS,
  ROOTS_SUFFIXES_PREFIXES,
  STEM_TRIE,
  REVERSE_STEM_TRIE,
  INITIAL_TEMPLATES,
  PREFIXING_TEMPLATES,
  TEMPLATES,
  GOLDSTANDARD,
  TOKENS_REQUESTED,
  MINI_LEXICON,
  BORROWED_SIGNATURES,
  FSA_DOC,
  INITIALMORPHOLOGY,
  WORKINGMORPHOLOGY,
  PREFIXINITIALMORPHOLOGY,
  PREFIXWORKINGMORPHOLOGY,
  HMM_LEXICON,
  HMM_CORPUS,
  STRINGEDITDISTANCE,
  INITIALSTRINGEDITTEMPLATES,
  WORKINGSTRINGEDITTEMPLATES,
  BIPHONES,
  PHONES,
  PHONES_Tier2,
  BIPHONES_Tier2,
  PHONES_Tier1_Skeleton,
  BIPHONES_Tier1_Skeleton,
  DESCRIPTION_LENGTH,
  DESCRIPTION_LENGTH_HISTORY,
  HMM_Document,
  BIGRAM_INFORMATION,
  UNIGRAM_INFORMATION,
  TIER2MI,
  UNANALYZED_WORDS,
  POS // Parts of speech.
};


enum eSortStyle
{
  KEY,
  REVERSE_KEY,
  CORPUSCOUNT,
  COUNT,
  SIGS,
  PARSE_SIZE,
  RULE_USE,
  LENGTH,
  DL_SAVINGS,
  FREQUENCY,
  MORPHEMECOUNT,
  MORPHEME_GOODNESS,
  SIGS_NUMBER_OF_STEMS,
  STEM_SUFFIXES,
  USECOUNT,
  SIG_REMARK,
  STEM_SOURCE,
  SIG_MENTORS,
  TEMPLATE_SORT,
  TEMPLATE_SORT_COLUMN
};


enum eBiphoneSortStyle
{
	MI,
	WMI,
	BIPHONE_KEY
};


enum ePhoneSortStyle
{
	PHONE_FREQ,
	PHONE_KEY
};


enum eStemType
{
  NORMAL            = 1,
  STEM_PLUS_SUFFIX  = 2,
  STEM_NORMAL       = 4,
  STEM_COMPOUND     = 8,
  BIWORD_COMPOUND   = 16,
  MULTIPLE_COMPOUND = 32,
  POSSIBLE_COMPOUND = 64,
  NUMBER            = 128,
  UNKNOWN           = 256,
  ENDS_IN_HYPHEN    = 512,
  POLYWORD_PIECE    = 1024
};

enum eInterfaceMessages
{
  ADD_WORDS,
  ADD_TEMPWORDS,
  ADD_SIGNATURES,
  ADD_PREFIX_SIGNATURES,
  ADD_STEMS,
  ADD_SUFFIXES,
  ADD_PREFIXES,
  ADD_MAXIMUM_SUFFIX_LENGTH,
  ADD_MAXIMUM_PREFIX_LENGTH,
  ADD_MINIMUM_SIGNATURE_LENGTH,
  ADD_MIN_LENGTH_STEM,
  ADD_MINIMUM_LENGTH_SIGNATURE,
  ADD_MINIMUM_NUMBER_STEMS_IN_SIGNATURE,
  ADD_MAX_SUCCESSOR_FREQ_SCORE,
  ADD_COMPOUNDS,
  ADD_TRIGRAM_BRANCHES,
  ADD_POLYMORPHEMES,
  ADD_POLYWORDS,
  ADD_THRESHOLD,
  ADD_FIND_GOOD_WORDINITIALS,
  ADD_INPUT_DOCUMENT_TYPE,
  ADD_GOOD_BEGINNINGS,
  ADD_PROPER_NAMES
};


enum eWindow
{
  TREE,
  COLLECTION,
  EDITVIEW
};


enum ePossibleStates
{
  NONE,
  LIST_OF_SIGNATURES,
  LIST_OF_PREFIX_SIGNATURES
};


enum eSuccessorFrequencyMode
{
  SF1,  //, peak and neighbors are only "1"
  SF2,  //, peak, and both stem and suffix are already identified.
  SF3    //peak, that's all
};


enum eInputDocumentType
{
  CORPUS,
  WORDLIST    // we will ignore proper names in this case
};


enum eNodeType
{
  DataNode,
  BranchingNode,
  BadType
};


enum eLockState
{
  Locked,
  Unlocked
};


enum eDetachment_Parameter
{
  eDo_Not_Call_Words,
  eCall_Words
};


enum eAlignmentOperation
{
  FromBelow,
  FromLeft,
  FromBelowAndLeft,
  Start,
  End,
  IdenticalMatch,
  NonIdenticalMatch
};


enum eAllomorphyType
{
  SuffixAllomorphy,
  StemAllomorphy,
  SignatureAllomorphy
};


enum ePOS
{
  POS_Noun,
  POS_Verb,
  POS_Adjective,
  POS_Other
};


enum eSplitType
{
  LENGTHWEIGHTING,
  NOLENGTHWEIGHTING,
  BOLTZMANN,
  BOLTZMANN2
};


enum eVerifyResult
{
  RESULT_CANCEL,
  RESULT_YES,
  RESULT_NO
};


enum eWhichWords
{
  WW_All,
  WW_AnalyzedOnly,
  WW_UnanalyzedOnly
};


enum eAffixationType
{
	TYPE_Prefix,
	TYPE_Suffix,
	TYPE_Unknown
};


enum ePhonologySplitType
{
	Split_LeaveSlot,
	Split_LeaveCopy
};


enum eTier
{
	TIER_1,
	TIER_2,
	TIER_1_SKELETON
};


enum eWordDisplayMode
{
	MiniLexicon_MorphologyStuffFirst,
	MiniLexicon_PhonologyStuffFirst,
    Lexicon_Word
};

enum eAddBoundarySymbols
{
	NO_BOUNDARIES,
	BOUNDARIES

};

enum eModelType
{
	UNIGRAM,
	BIGRAM
};


enum eHmmDataType
{
	HMMNONE,
	PHONE_TIER1,
	PHONE_TIER2,
	PARSE
};

enum eMDL_STYLE
{
	CorpusCount,
	GrammarCount
};

enum eRecomputeStyle
{
	Recompute,
	ComputeOnlyIfNecessary
};

enum eStateType
{
    StartState,
    AcceptState,
    NormalState
};

#endif // GENERALDEFINITIONS_H
