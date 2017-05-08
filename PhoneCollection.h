// Description length bookkeeping, search, and display of encountered phonemes
// Copyright © 2009 The University of Chicago
#ifndef PHONECOLLECTION_H
#define PHONECOLLECTION_H
 
class CPhoneCollection;

#include "CollectionTemplate.h"
#include "Phone.h"
#include "generaldefinitions.h"

class MonteCarlo;

class CPhoneCollection : public TCollection<CPhone>
{
	class CWordCollection* 		m_MyWords;
	class CBiphoneCollection* 	m_MyBiphones;
	
	double* 					m_expMI;
	double* 					m_expMIFromBoundary;
	double* 					m_expMIToBoundary;
public:
	CPhoneCollection(class CWordCollection*);

	virtual ~CPhoneCollection();
	class CBiphoneCollection* 	GetMyBiphones() { return m_MyBiphones; }

	void 						CountPhonesAndBiphonesInWord(class CStem*,
									enum eTier WhichTier);
	void 						Normalize();
	bool 						ValidPhone(class QString&);
	void 						ListDisplay(class Q3ListView*);
	double* 					ZFunctionTier1(int r, int s, double* output);
	double 						ComputeZ();
	void 						ZFunctionOnTier2(int s, double* results);
	double	 					ZFunctionTier1(int r, int s);
	double 						GetSumOfMyMIs();
	void 						PopulateMonteCarlo(class MonteCarlo* pMyMonteCarlo);

	void						ComputeStringAgreementAndDisagreement(CLParse* string1, CLParse* string2,
									double& agreement_unigram,    double& agreement_bigram,
									double& disagreement_unigram, double& disagreement_bigram);
 
};

#endif // PHONECOLLECTION_H

//	The PhoneCollection class is a collection of phones, along with a pointer to a collection of 
//  biphones, which keeps track of conditional probabilities.
