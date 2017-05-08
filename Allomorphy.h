// Driver and result type for alignment of similar signatures
// Copyright © 2009 The University of Chicago
#ifndef ALLOMORPHY_H
#define ALLOMORPHY_H

#include <QTextStream>
#include <QList>
#include "Parse.h"

enum eAlignmentStatus {IDENTICAL, DIFFERENT};

class AffixAlignment {
	QString m_OriginalAffix1;
	QString m_OriginalAffix2;
	QString m_Affix1;
	QString m_Affix2;
	QString m_Margin1;
	QString m_Margin2;
	QString m_Shift1;
	QString m_Shift2;
	enum eAlignmentStatus m_Status;
	/// size in bits of overlap of letters/phonemes
	double m_Agreement_unigram;
	/// size in bits of overlap of bigram-letters/phonemes
	double m_Agreement_bigram;
	/// size in bits of symmetric difference.
	double m_Disagreement_unigram;
	double m_Disagreement_bigram;
public:
	// construction/destruction.

	AffixAlignment(QString Affix1, QString Affix2);
	AffixAlignment(QString Margin1, QString Affix1,
		QString Margin2, QString Affix2);
	// destructor implicitly defined.

	// copy-construction and assignment implicitly defined.
private:
	// disable default-construction
	AffixAlignment();
public:
	// aligned affixes.

	QString GetAffix1() const { return m_Affix1;}
	QString GetAffix2() const { return m_Affix2;}
	QString GetMargin1() const { return m_Margin1;}
	QString GetMargin2() const { return m_Margin2;}
	QString GetShift1() const { return m_Shift1;}
	QString GetShift2() const { return m_Shift2;}
};

/// m_Sig1 is shorter than m_Sig2, or of same length.
class SignatureAlignment {
	class CSignature* m_SigPtr1;
	class CSignature* m_SigPtr2;
        QList<AffixAlignment*> m_AffixAlignments;
	CParse m_Sig1;
	CParse m_Sig2;
	CParse m_Sig1AlignedAffixes;
	CParse m_Sig2AlignedAffixes;
public:
	// construction/destruction.

	SignatureAlignment(class CSignature* Sig1, class CSignature* Sig2);
	// destructor implicitly defined

	// disable default-construction, copy
private:
	SignatureAlignment();
	SignatureAlignment(const SignatureAlignment& x);
	SignatureAlignment& operator=(const SignatureAlignment& x);
public:

	// Levenshtein’s string-edit-distance algorithm

	void FindBestAlignment();
	/// success?
	bool AllSig1AffixesAligned();
	bool AllSig2AffixesAligned();
	/// result from string-edit-distance algorithm
        QList<AffixAlignment*>* GetAffixAlignments()
		{ return &m_AffixAlignments; }

	/// output to file
        void Display(QTextStream& LogStream);
};

#endif // ALLOMORPHY_H
