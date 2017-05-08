// Mini-lexicon’s collection of words
// Copyright © 2009 The University of Chicago
#ifndef WORDCOLLECTION_H
#define WORDCOLLECTION_H

// See the CMiniLexicon class in MiniLexicon.h for an overview of
// suffix/signature-based discovery of morphology.

#include "CollectionTemplate.h"

#include "AffixLocation.h"
class CSignatureCollection;
class CPhoneCollection;
class CStem;

class CWordCollection : public TCollection<CStem> {
public:
	enum eAffixLocation m_AffixLocation;
	enum eWordDisplayMode m_DisplayMode;
	CPhoneCollection* m_Phones_Tier1;
	CPhoneCollection* m_Phones_Tier2;
	CPhoneCollection* m_Phones_Tier1_Skeleton;

	double m_PhonologicalContent_Unigram;
	double m_PhonologicalContent_Bigram;
	double m_Tier2_LocalMI_Score;
	double m_Tier2_DistantMI_Score;

	/// includes Tier1 bigram content
	double m_LocalMI_TotalBoltzmannScore;
	double m_LocalMI_Plog;
	/// includes Tier1 bigram content
	double m_DistantMI_TotalBoltzmannScore;
	double m_DistantMI_Plog;

	double m_MyZ_Local;
	double m_MyZ_Distant;
	CParse* m_Vowels;
public:
	// construction/destruction.

	explicit CWordCollection(CMiniLexicon* lexicon = 0);
	~CWordCollection();

	// disable copy
private:
	CWordCollection(const CWordCollection& x);
	CWordCollection& operator=(const CWordCollection& x);
public:

	CStem*			operator<< ( CStem* );
    	CStem*			operator<< ( CStem& );
	CStem*			operator<< ( CStringSurrogate& );
	CStem*			operator<< ( CParse* );
	CStem*			operator<< ( QString );
	void			AddPointer( CStem* );
	CStem*			AddToCollection( CParse& );
	CStem*			AddToCollection( CStringSurrogate& );
	
	void			Empty();
	void			RemoveAll();
	bool			Remove( CStem* ); // doesn't delete CStem*
	bool			RemoveMember( CStem* ); // deletes CStem*
	bool			RemoveMember( CStringSurrogate& ); // deletes CStem*
	bool			RemoveMember( CStringSurrogate&, bool ); // FSA
	void			DeleteMarkedMembers();

  // Accessors
  void             AssignSignatureFromStemsAffixPointer ( eAffixLocation );
  int              HowManyAreAnalyzed ( int& HowManyNotAnalyzed, LinguisticaMainWindow* doc = NULL  );
//  void             ListDisplay ( QListView*,
//                                 StringToString* Filter = NULL,
//                                 bool AnalyzedWordsOnly = FALSE );
  void					OutputWords ( QString );
  void					OutputWordsForTesting ( QString );
  CPhoneCollection*		 GetPhones();
  CPhoneCollection*		 GetPhones_Tier2();
  CPhoneCollection*		 GetPhones_Tier1_Skeleton();
//  QString			GetVowels() {return m_Vowels; }
  // Mutators
  void             ReadWordFile ( QString );

  void             PredecessorFreq1( CStemCollection*,
                                          CPrefixCollection*,
                                          CSignatureCollection*,
                                          eSuccessorFrequencyMode,
                                          int );

                    
  void             SuccessorFreq1 ( CStemCollection*,
                                    CSuffixCollection*,
                                    CSignatureCollection*,
                                    eSuccessorFrequencyMode,
                                    int );
 
  void  FindAllWordNeighbors(CLexicon*); 
 //Phonology
 //------------------------------------------------------
  void		CountPhonesAndBiphones(enum eTier tier);
  void		DoPhonology();
  void		CreateCVTemplate();

  void		SplitPhonologyToTiers (ePhonologySplitType );
  void		CreatePhonologyFromOrthography();
  void		ComputeProbabilitiesOfWords(  );
  void          GetPhonologyTierInfoForGraphOfWords( ); 
  double	ComputeZeta();  
  void		ComputeBoltzmannProbabilities();
 
  double	ComputeZ();
  double	ComputeZStar(); // Field method on tier 2;  

  double	GetPhonologicalContentTier1Bigrams()	{ return m_PhonologicalContent_Bigram; }
  double	GetPhonologicalContentUnigrams()		{ return m_PhonologicalContent_Unigram; }
  double	GetZ_Local()							{ return m_MyZ_Local; }
  double	GetZ_Distant()							{ return m_MyZ_Distant; }
 
  double	GetTier2_LocalMI_Score()	{ return m_Tier2_LocalMI_Score; }  
  double	GetLocalMI_Plog()			{ return m_LocalMI_Plog; }
  double	GetTier2_DistantMI_Score()	{ return m_Tier2_DistantMI_Score; }
  double	GetDistantMI_Plog()			{ return m_DistantMI_Plog; }
};

#endif // WORDCOLLECTION_H
