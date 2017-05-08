// Some methods for discovering allomorphs of stems
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include <memory>
#include <QList>
#include <QMap>
#include "Compound.h"
#include "Suffix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "CompoundCollection.h"
#include "SuffixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "CollectionTemplate.h"
#include "StringSurrogate.h"
#include "StringFunc.h"
#include "HTML.h"
#include "Typedefs.h"

typedef QMap<QString,QString>	StringToString;

/*

	Finding rules: first we find pairs of similar stems, and see HOW they differ.


	Suppose we find a lot of stems that differ by final -e. Then we look at the smaller stem's
	signature. If it contains a high incidence of
	(a) suffix -e;
	(b) one or two other suffixes F1, F2
	(c) F1 and F2 "go well"  with the signature of the larger stem(s);

	then:
	(d) Consider the hypothesis that F1 and F2 are of the form <e>F1 and <e>F2


*/

struct SigLetter {
	CSignature* m_SigPointer;
	CParse m_Letter;

	SigLetter(CSignature* Sig, const CStringSurrogate& SS)
		: m_SigPointer(Sig), m_Letter(SS) { }
};

void CMiniLexicon::RelateStems()
{
	const CStringSurrogate CSSofQNULL(TheStringNULL);
	const int MinimumSuffixCount = 5;

	if (LogFileOn()) *GetLogFile() <<
		LargeTitle( "Finding allomorphy (Version 2002)");
	m_pSuffixes->Sort(COUNT);

	// XXX. consider using boost::optional instead.
	std::auto_ptr<CParse> pPossibleDeletingSuffixes;

	// Major loop over deletable pseudo-suffixes
        QList<SigLetter*> SignaturesToFixList;
        //SignaturesToFixList.setAutoDelete(true);    //fix this -- so it doesn't become a memory leak. @@@
	CSuffixCollection SuffixesToEliminate;
	for (int f = 0; f < m_pSuffixes->GetCount(); ++f) {
		CSuffix* qSuffix = m_pSuffixes->GetAtSort(f);
		if (qSuffix->GetKeyLength() != 1)
			continue;
		if (qSuffix->GetUseCount() < MinimumSuffixCount)
			continue;

		/// possible suffix (like 'e' in English)
		CStringSurrogate ssDiffLetter = qSuffix->GetKey();

		if (LogFileOn()) *GetLogFile() <<
			SmallTitle(ssDiffLetter.Display());

		pPossibleDeletingSuffixes = std::auto_ptr<CParse>(new CParse);

		// Find all suffix candidates that MIGHT delete this DiffLetter
		// if DiffLetter == 'e', SuffixCandidates includes ing, ity.
		if (LogFileOn()) *GetLogFile() <<
			StartTable << StartTableRow
				<< MakeTableHeader(
				"Suffixes that do not follow this suffix")
				<< MakeTableHeader("Count") <<
			EndTableRow;

		{
			bool found = false;
			for (int i = 1; i < m_pSuffixes->GetCount(); ++i) {
				CSuffix* pSuffix = m_pSuffixes->GetAt(i);

				if (pSuffix->GetUseCount() < MinimumSuffixCount)
					continue;

				CStringSurrogate ssSuffix = pSuffix->GetKey();
				int TotalStemsWithSuffix;
				int HowManyEndWithThisLetter;
				HowManyStemsWithThisSuffixEndInThisLetter(
						ssSuffix,
						ssDiffLetter,
						TotalStemsWithSuffix,
						HowManyEndWithThisLetter);

				// XXX. Use “Threshold = 0.05” instead?

				const int MinimumStemCount = 5;
				const int MaximumExceptionCount = 5;

				// if suffix doesn’t begin with DiffLetter
				// and its count is very small, ignore it.
				if (TotalStemsWithSuffix <= MinimumStemCount &&
						ssSuffix.Left(ssDiffLetter.GetLength())
							!= ssDiffLetter)
					continue;

				if (LogFileOn()) *GetLogFile() <<
					StartTableRow <<
						TableData(ssSuffix) <<
						TableData(HowManyEndWithThisLetter) <<
					EndTableRow;

				if (HowManyEndWithThisLetter <= MaximumExceptionCount) {
					pPossibleDeletingSuffixes->Append(ssSuffix);
					found = true;
				}
			}

			if (LogFileOn() && !found) *GetLogFile() <<
				SmallTitle("None found");
		}

		// Simple signatures (2 affixes)
		// We now have a set of candidates that might delete DiffLetter
		// We will look at each signature, and see whether it
		// erroneously has a suffix that should really be thought
		// of as deleting from the stem rather than as a suffix.

		// 1. In our first test, we will look for signatures of the
		//    form: Letter.OtherSuffix, where OtherSuffix does not
		//    appear after stems ending in Letter, and where
		//    NULL.OtherSuffix does occur as a signature.

		if (LogFileOn()) *GetLogFile() <<
			StartTable << StartTableRow <<
				MakeTableHeader("Suspicious signature") <<
				MakeTableHeader("Paired signature" )<<
			EndTableRow;

		{
			bool found = false;
			for (int n = 0; n < m_pSignatures->GetCount(); ++n) {
				CSignature* pSig = m_pSignatures->GetAt(n);

				if (pSig -> Size() != 2)
					continue;
				if (!pSig -> Contains(ssDiffLetter))
					continue;

				QString OtherSuffix;
				if (pSig -> GetPiece(1) == ssDiffLetter)
					OtherSuffix = pSig->GetPiece(2).Display();
				else
					OtherSuffix = pSig->GetPiece(1).Display();

				if (OtherSuffix == TheStringNULL)
					continue;
				if (!pPossibleDeletingSuffixes->Contains(OtherSuffix))
					// OtherSuffix doesn't appear after DiffLetter
					continue;

				if (LogFileOn()) *GetLogFile() <<
					StartTableRow <<
						TableData(pSig->Display('+'));
				found = true;

				CParse TestSig;
				TestSig.Append(TheStringNULL);
				TestSig.Append(OtherSuffix);
				TestSig.Alphabetize();

				if (*m_pSignatures ^= TestSig) {
					SuffixesToEliminate << ssDiffLetter;

					std::auto_ptr<SigLetter> pSigLetter(
						new SigLetter(pSig, ssDiffLetter));
					SignaturesToFixList.append(
						pSigLetter.release());

					if (LogFileOn()) *GetLogFile() <<
						TableData(TestSig) << EndTableRow;
				} else {
					if (LogFileOn()) *GetLogFile() <<
						TableData(TestSig) <<
						TableData( " not found. ") <<
						EndTableRow;
				}
			}
			if (LogFileOn() && !found) *GetLogFile() <<
				StartTableRow <<
					TableData("None found.") <<
				EndTableRow;

			if (LogFileOn()) *GetLogFile() <<
				EndTable;
		}
		// NB: We should do the preceding test in a more
		// general way, that is:
		// Look for pairs of signatures of the form
		// A.B and A.xB, where x is the deleting letter;
		// the previous case is like this and where B is NULL.
		// Then A deletes x, i.e., A is really <x>A.

		// 2. In our other test, we look at the signatures
		// that contain both DiffLetter and one of the deleters,
		// and see, first of all, if a suffix appears more often
		// with NULL than with DiffLetter;
		// or, the suffix actually is of the form aX,
		// where a = DiffLetter, X occurs with NULL more
		// than aX occurs with a.

		if (!(SuffixesToEliminate ^= ssDiffLetter))
			continue;

		for (int m = 0; m < m_pSignatures->GetCount(); ++m) {
			CSignature* pSig = m_pSignatures->GetAt(m);
			if (!pSig -> Contains(ssDiffLetter))
				continue;

			for (int k = 1; k <= pSig->Size(); ++k) {
				CStringSurrogate ssSuffix = pSig->GetPiece(k);
				CSuffix* pSuffix = *m_pSuffixes ^= ssSuffix;

				if (pSuffix->GetDeletees()->Contains(ssDiffLetter))
					// we've already determined it deletes DiffLetter
					continue;

				if (StemsWithBothSuffixes(TheStringNULL, ssSuffix) >
						StemsWithBothSuffixes(
							ssDiffLetter, ssSuffix))
					// probably a deleter
					pSuffix->AddDeletee(ssDiffLetter);

				if (ssSuffix.Left(ssDiffLetter.GetLength()) ==
						ssDiffLetter) {
					// probably cut wrong, like "ement"
					CStringSurrogate ssTruncatedForm =
						ssSuffix.Mid(
						ssDiffLetter.GetLength());

					if (StemsWithBothSuffixes(TheStringNULL,
							ssTruncatedForm) >
							StemsWithBothSuffixes(
								ssDiffLetter,
								ssSuffix))
						pSuffix->AddDeletee(ssDiffLetter);
				}
			}
		}

		// Now put onto SignaturesToFixList all of the sigs that
		// are composed ONLY of deleting suffixes.
		if (LogFileOn()) *GetLogFile() << StartTable <<
			StartTableRow <<
				MakeTableHeader("Signatures to fix") <<
			EndTableRow;

		for (int m = 0; m < m_pSignatures->GetCount(); ++m) {
			CSignature* pSig = m_pSignatures->GetAt(m);

			if (!pSig->Contains(ssDiffLetter))
				continue;

			bool bFoundDeletee = false;
			bool bFoundDeleter = false;
			for (int k = 1; k <= pSig->Size(); ++k) {
				const CStringSurrogate ssSuffix = pSig->GetPiece(k);
				if (ssSuffix == ssDiffLetter) {
					bFoundDeletee = true;
					continue;
				}

				CSuffix* pSuffix = *m_pSuffixes ^= ssSuffix;
				Q_ASSERT(pSuffix != 0);
				if (!pSuffix->GetDeletees()
						->Contains(ssDiffLetter)) {
//					break;
				} else {
					bFoundDeleter = true;
				}
			}

			if (bFoundDeletee && bFoundDeleter) {
				std::auto_ptr<SigLetter> pSigLetter(new SigLetter(
						pSig, ssDiffLetter));

				if (LogFileOn()) *GetLogFile() << StartTableRow <<
					TableData(pSigLetter->m_SigPointer) <<
					EndTableRow;

				SignaturesToFixList.append(pSigLetter.release());
			}
		}

		if (LogFileOn()) *GetLogFile() << EndTable;
	} // end of checking this letter to see if it ever deletes.
	// End of Major loop over deletable pseudo-suffixes

	if (LogFileOn()) *GetLogFile() <<
		SmallerTitle("Now we do the changing for the simple signatures.");

        foreach (SigLetter* pSigLetter, SignaturesToFixList ) {
		CSignature* pSig = pSigLetter->m_SigPointer;
		CStringSurrogate ssDiffLetter = pSigLetter->m_Letter;

		// XXX. log:
		//	"1. Moving material from suffixes to stems:
		//	    ${pSigLetter->m_Letter}, in signature:
		//	    ${*pSigLetter->m_SigPointer}

		// this is where the real work happens
//		pPossibleDeletingSuffixes =
//			SuffixesWhichMightDeleteKey.find(ssDiffLetter.Display()));

		// XXX. pPossibleDeletingSuffixes kept on getting recreated
		// before, so something is probably awry.
		if (pPossibleDeletingSuffixes.get())
			MoveWordsStemSuffixBoundaryToRight(pSig,
				ssDiffLetter, pPossibleDeletingSuffixes.get());
	}

	// XXX. log: Suffixes to eliminate: ${SuffixesToEliminate}

	m_pSignatures->CleanUp();
	SignaturesToFixList.clear();
	m_pSignatures->CleanUp();

	// go through all the signatures,
	// and identify those that should be fixed.
	// For example, the signature e.<e>ing.es
	// will be marked to become NULL.<e>ing.s.		/
	if (LogFileOn()) *GetLogFile() << SmallTitle("Bigger signatures");
	if (LogFileOn()) *GetLogFile() <<
		"How many suffixes to eliminate? " <<
		SuffixesToEliminate.GetCount() <<
		"<br />";

	for (int k = 0; k < SuffixesToEliminate.GetCount(); ++k) {
		CSuffix* const pSuffixToEliminate = SuffixesToEliminate[k];
		const CStringSurrogate ssSuffixToEliminate =
			pSuffixToEliminate->GetKey();

		if (LogFileOn()) *GetLogFile() <<
			SmallerTitle(ssSuffixToEliminate.Display());

		if (LogFileOn()) *GetLogFile() << StartTable << StartTableRow <<
				MakeTableHeader("Signature") <<
				MakeTableHeader("Suffix") <<
				MakeTableHeader("Disposition") <<
			EndTableRow;

		for (int i = 0; i < m_pSignatures->GetCount(); ++i) {
			CSignature* const pSig = m_pSignatures->GetAt(i);

			bool ThisSigContainsDeletingSuffix = false;
			if (pSig->Contains(ssSuffixToEliminate) &&
					pSig->Size() > 2) {
				if (LogFileOn()) *GetLogFile() <<
					StartTable << StartTableRow <<
						TableData(pSig) <<
					EndTableRow;

				for (int j = 1; j <= pSig->Size(); ++j) {
					CStringSurrogate ssSuffix =
							pSig->GetPiece(j);

					if (LogFileOn()) *GetLogFile() <<
						StartTableRow <<
						TableData(ssSuffix);

					if (ssSuffix == ssSuffixToEliminate) {
						// 2. Suffix is the one we want
						// to make into NULL
						if (LogFileOn())
							*GetLogFile() <<
							TableData("Found the deleting (pseudo-)suffix") <<
							EndTableRow;
						continue;
					}

					if (pPossibleDeletingSuffixes.get() &&
							pPossibleDeletingSuffixes
							->Contains(ssSuffix)) {
						// 3. Suffix deletes the suffix
						// we want to make NULL --
						ThisSigContainsDeletingSuffix = true;

						// XXX. CStringSurrogate::StartsWith
						if (ssSuffix.Left(
							ssSuffixToEliminate.GetLength())
							== ssSuffixToEliminate) {
							// this is the "ement" case
							// -- we want to change the
							// suffix,
							// not make it an e-deleter

							// XXX. SuffixChangesToMake
							// map never populated
							QString NewSuffix = "";
//							QString NewSuffix =
//								SuffixChangesToMake[
//								ssSuffix.Display()];

							if (LogFileOn())
								*GetLogFile() <<
								TableData("We found the pseudosuffix at the beginning of a poor suffix; will change to: ") <<
								TableData(NewSuffix) <<
								EndTableRow;
							continue;
						}

						if (LogFileOn()) *GetLogFile() <<
							TableData("We found the pseudosuffix deleting before " ) <<
							TableData(ssSuffix) <<
							EndTableRow;
						continue;
					} else if (ssSuffix.Left(
						ssSuffixToEliminate.GetLength()) ==
						ssSuffixToEliminate) {
						// 4. Suffix starts with the suffix
						// we want to make NULL

						if ( LogFileOn()) *GetLogFile() <<
							TableData("We found") <<
							TableData(ssSuffix) <<
							EndTableRow;
						continue;
					}

					if (LogFileOn()) *GetLogFile() <<
						TableData("Not a deleter:") <<
						TableData(ssSuffix) <<
						EndTableRow;
				} // end of checking each suffix in the signature
			}

			if (!ThisSigContainsDeletingSuffix)
				continue;

			std::auto_ptr<SigLetter> pSigLetter(new SigLetter(
					pSig, ssSuffixToEliminate));
			SignaturesToFixList.append(pSigLetter.release());
		} // end of signature loop

		if (LogFileOn()) *GetLogFile() << EndTable;
	} // end of loop over suffixes being eliminated.

	if (LogFileOn()) *GetLogFile() <<
		SmallerTitle("Now we do the changing for more complex signatures");

	foreach (SigLetter* pSigLetter, SignaturesToFixList) {
		CSignature* pSig = pSigLetter->m_SigPointer;
		CStringSurrogate ssDiffLetter = pSigLetter->m_Letter;

		if (LogFileOn()) *GetLogFile() <<
			"<br><br>1. Moving material from suffixes to stems: " <<
			pSigLetter->m_Letter.Display() << ", in signature: " <<
			pSigLetter->m_SigPointer->Display();

		// this is where the real work happens:
//		SuffixesWhichMightDeleteKey.Lookup(ssDiffLetter.Display(),
//				pPossibleDeletingSuffixes);
		MoveWordsStemSuffixBoundaryToRight(pSig,
				pSigLetter->m_Letter.Display(),
				pPossibleDeletingSuffixes.get());
	}
	if (LogFileOn()) {
		*GetLogFile() << StartTable <<
			StartTableRow <<
				MakeTableHeader("Suffixes to eliminate:") <<
			EndTableRow;
		for (int k = 0; k < SuffixesToEliminate.GetCount(); ++k)
			*GetLogFile() << StartTableRow <<
				TableData(SuffixesToEliminate[k])
				<< EndTableRow;
		*GetLogFile() << EndTable;
	}
	m_pSignatures->CleanUp();
}




//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

/* The following function takes a stem, and adds FinalLetter to it, and then
	adds all the other suffixes in the stem's old SuffixList to the bigger
	stem -- whether that stem already existed or not.
	We should be sure to get rid of this stem only if ALL of its suffixes
	are shifted -- and many may not be.
*/

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void CMiniLexicon::ShiftFinalLetterToStem (CStem* pStem, QString& FinalLetter )
{
	QString				Word,
						Suffix,
						NewStem,
						Stem = pStem->GetKey().Display();
	CSS					ssWord,
						ssSuffix,
						ssStem;
	CStem*				pWord;
	CParse*				SuffixList = pStem->GetSuffixList();
	CSignature*			pNewSig;
	CSuffix*			pSuffix;


	ssStem = *pStem;



	for (int i = 1; i <= SuffixList->Size(); i++)
	{
		Suffix = SuffixList->GetPiece(i).Display();
		if ( Suffix == FinalLetter )
		{
			continue;
		}


		Word = Stem + Suffix;
		pWord = *m_pWords ^= Word;
//		Q_ASSERT (pWord);

		Suffix = "<" + FinalLetter + ">" + Suffix;
		pSuffix  = *m_pSuffixes << ssSuffix;
//		pSuffix->IncrementUseCount();

		NewStem = ssStem.Display() + FinalLetter;
		CStem* pBiggerStem = *m_pStems ^= NewStem;

		if (pBiggerStem != 0) {
			// the bigger stem already exists....
			pBiggerStem->AddSuffix( Suffix );
			pNewSig = *m_pSignatures << pBiggerStem->GetSuffixList();

			// ...get rid of OLD signature in Signatures;


			// Fix word structure



		}
		else
		{
			// the bigger stem is new...

		}

		pWord->AttachWordAndSuffixalStem(pBiggerStem);
	}


}


void CMiniLexicon::HowManyStemsWithThisSuffixEndInThisLetter (
													CStringSurrogate& Suffix,
													CStringSurrogate& Letter,
													int&		 TotalStemsWithSuffix,
													int&		 HowManyEndWithThisLetter )

{
	CSignature*			pSig;
	CSS					ssStem;
	CStem*              pStem;

	TotalStemsWithSuffix = 0;
	HowManyEndWithThisLetter = 0;

    Q_ASSERT (Letter.Display() != "e" || Suffix.Display() != "ing");

	for (int i = 0; i < m_pSignatures->GetCount(); i++)
	{
		pSig = m_pSignatures->GetAt(i);
		if ( ! pSig->Contains ( Suffix ) ) { continue; }
            //for (pStem = pSig->GetStemPtrList()->first(); pStem; pStem=pSig->GetStemPtrList()->next())
            for (int z= 0; z < pSig->GetStemPtrList()->size(); z++)
            {   pStem = pSig->GetStemPtrList()->at(z);
                ssStem = pStem->GetKey();
                TotalStemsWithSuffix++;
                if ( ssStem.Right (Letter.GetLength() ) == Letter )
                {
                        HowManyEndWithThisLetter++;
                }
            }
	}
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

/*
void CLexicon::FindStemChains()



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
{

	const int				SmallestStemSize = 5;
	TCollection<CLParse>		Output;
	CParse					Row;
	QString					Stem1, Stem2, StemDiff;
	CStem*					pStem1, *pStem2;
	CSignature*				pSig, *pSig2;
	CParse					NewSig;
	CStem*					pStem;
	CSuffix*				pSuffix, *qSuffix;
	const int				THRESHOLD = 3;
	CSuffixCollection		TempSuffixes;
	bool					bLongerStemWillBeDeletedFlag;


	StatusBar1 ( QString ("Smooth stems: find stem chains.") );

	Stems_Suffixed ->FindMemberExtensions ( SmallestStemSize, Output );

	// First figure out what the new suffixes will be, once we do merging.
	// We do this because some merging will eventually be rejected if it means
	// creating a new suffix only used once or twice.

	for (int i = 0; i < Output.GetCount(); i++)
	{
		Row		= Output.GetAt(i);
		//Stem	= Row.GetAt( Row.Size() );
		//pStem1	= *Stems ^= Stem;
		Q_ASSERT ( Row.Size() >= 2 );

		for (int j = 2; j <= Row.Size() ; j++)
		{
			Stem1 = Row.GetAt( j );
			pStem1 = *Stems_Suffixed ^= Stem1;

			Stem2	= Row.GetAt( j - 1 );
			StemDiff = Stem2.Mid ( Stem1.GetLength() );

			pStem2	= *Stems_Suffixed ^= Stem2;
			pSig2 = *Signatures ^= pStem2->GetSuffixList();

			NewSig = pSig2;
			NewSig.PrefixToAllPieces(StemDiff);

			for (int k = 1; k <= NewSig.Size(); k++)
			{
				TempSuffixes << NewSig.GetPiece(k);
			}

		}
	}

	for ( i = 0; i < Output.GetCount(); i++)
	{
		Row		= Output.GetAt(i);
		//Stem	= Row.GetAt( Row.Size() );

		Q_ASSERT ( Row.Size() >= 2 );

		for (int j = 2; j <= Row.Size() ; j++)
		{
			Stem1 = Row.GetAt( j );
			pStem1 = *Stems_Suffixed ^= Stem1;

			Stem2	= Row.GetAt( j - 1 );
			StemDiff = Stem2.Mid ( Stem1.GetLength() );

			pStem2	= *Stems_Suffixed ^= Stem2;
			NewSig = *pStem2->GetSuffixList();
			NewSig.PrefixToAllPieces(StemDiff);

			bLongerStemWillBeDeletedFlag = TRUE;
			for (int k = 1; k <= NewSig.Size(); k++)
			{
				qSuffix = TempSuffixes ^= NewSig.GetAt(k);

				if ( *Suffixes ^= NewSig.GetAt(k) ) // the new suffix is a recognized suffix;
				{ continue; } // i.e., this suffix is ok, but maybe the whole new signature is not.

				if ( !qSuffix ) { continue; }
				if ( qSuffix->GetCorpusCount() >=  THRESHOLD ) // the new suffix is used at least that many new times
				{ continue; }

				bLongerStemWillBeDeletedFlag = FALSE;
				// the signature is BAD, hence the stem should not be gotten rid of.

			}

			if ( bLongerStemWillBeDeletedFlag == FALSE )
			{ continue; } // don't delete this stem


			pStem2->Doomed();
			AddToScreen ( pStem1->GetKey() + " " + pStem2->GetKey() ) ;

			for ( k = 1; k <= NewSig.Size(); k++)
			{
				pStem1->AddSuffix( NewSig.GetAt(k) );
				pStem1->IncrementCorpusCount( pStem2->GetCorpusCount() );

				pSuffix = *Suffixes << NewSig.GetPiece(k);
				//pSuffix->IncrementCorpusCount ( ? );
			}
			// fix corpus counts all the way around now.

		}
	}







	CStemCollection*	NewStems = new CStemCollection(this);
	CStem * qStem;

	for (i = 0; i < Stems_Suffixed->GetCount(); i++)
	{
		pStem = Stems_Suffixed ->GetAt(i);
		if ( ! pStem->IsDoomed() )
		{
			qStem = *NewStems << *pStem;
		}
	}

	delete Stems_Suffixed;
	Stems_Suffixed = NewStems;

	delete Signatures;
	CSignatureCollection* NewSignatures = new CSignatureCollection(this, Suffixes, WORD_FINAL);
	for (i = 0; i < Stems_Suffixed->GetCount();i++)
	{
		pStem = Stems_Suffixed->GetAt(i);
		pSig = *NewSignatures << pStem->GetSuffixList();
//		*pSig << pStem;
		pSig->AttachToSuffixSig(pStem);
		pSig->IncrementCorpusCount (pStem->GetCorpusCount() );
	}

	Signatures = NewSignatures;

	StatusBar1 ( QString ("End of Smooth stems: finding stem chains.") );

}

*/

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



int	CMiniLexicon::StemsWithBothSuffixes(CStringSurrogate& ssSuffix1, CStringSurrogate& ssSuffix2)
{
	int				count = 0;
	CSignature*		pSig;


	for (int i = 0; i < m_pSignatures->GetCount(); i++)
	{
		pSig = m_pSignatures->GetAt(i);
		if ( pSig->Contains (ssSuffix1) && pSig->Contains(ssSuffix2) )
		{
			count += pSig->GetNumberOfStems();
		}
	}
	return count;
}
int	CMiniLexicon::StemsWithBothSuffixes(QString  Suffix1, CStringSurrogate& ssSuffix2)
{
	int				count = 0;
	CSignature*		pSig;


	for (int i = 0; i < m_pSignatures->GetCount(); i++)
	{
		pSig = m_pSignatures->GetAt(i);
		if ( pSig->Contains (Suffix1) && pSig->Contains(ssSuffix2) )
		{
			count += pSig->GetNumberOfStems();
		}
	}
	return count;
}

/*
void CMiniLexicon::MoveWordsStemSuffixBoundaryToRight(CSignature* pThisSig,
													 CStringSurrogate& ssDeletee,
													 CTypedPtrMap<CMapStringToString, CString, CString>& Remapper
													)
{
	CParse				PNewSig,
						POldSig,
						PMergedSig,
						PNewStem,
						PDeletee = ssDeletee;

	POSITION			Pos;
	bool				bModifiedSigExisted		= FALSE;
	CSignature			*pLargerModifiedSig,
						*pModifiedSig			= NULL,
						*pOldSigBecameSig		= NULL,
						*pOlderSig				= NULL;

	CStringSurrogate	ssStem,
						ssSuffix,
						ssNewSuffix;
	CStem*				pOldStem;

	CStem*				pNewStem;
	CParse				DummyParse,
						Word,
						WhatSigWillBecome,
						SuffixChanges;
	CSuffix*			pSuffix;
	CStem *				pWord;
	bool				bStemShouldRemain		= FALSE;
	bool				bOldSigRemains			= FALSE;
	bool				bNewStemAlreadyExisted	= FALSE;
	bool				val;
	int					i;
	//----------------------------------------------------------------//





	int* bStatus = new int [ pThisSig->Size() + 1];

	if ( m_LogFile )
	{
				*m_LogFile <<	"\n\tF1: Creating new signature: "	<<
								PNewSig.Display() <<
								" Residue of old sig: "<<
								WhatSigWillBecome.Display();
	}


	PNewSig = CreateADeletingSignature(
										pThisSig,
										PDeletee,
										SuffixChanges,
										bStatus,
										WhatSigWillBecome,
										Remapper
										);
	if ( m_LogFile )
	{
				*m_LogFile <<	"\n\tF1: Creating new signature: "	<<
								PNewSig.Display() <<
								" Residue of old sig: "<<
								WhatSigWillBecome.Display();
	}

	// TODO: fix this later. Eg local:  NULL.e.ly, creates a signature just NULL with locale. Not useful.
	if ( PNewSig.Size() == 1 ) {return; }

	// TODO: fix this later. Problem is what's left over is just NULL: e.g. NULL.e.ed
	if ( CSS( WhatSigWillBecome ) == CSS ( CString("NULL") ) )  { return; }


	pModifiedSig = *Signatures ^= PNewSig;
	if (! pModifiedSig )
	{
		pModifiedSig = *Signatures <<  &PNewSig ;
	}

	pModifiedSig->SetRemark ( pThisSig->GetRemark() + " + allomorphy" );

	if ( WhatSigWillBecome.Size() > 0 )
	{
		bOldSigRemains = TRUE;
		pOldSigBecameSig = *Signatures << &WhatSigWillBecome;
		pOldSigBecameSig  ->SetRemark( CString("Allomorphy2") );
	}

	//----------------------------------------------------------------//
	//	Loop through stems:
	//----------------------------------------------------------------//

	Pos = pThisSig->GetStemPtrList()->GetHeadPosition();
	CTypedPtrList<CPtrList, CStem*>* Temp = pThisSig->GetStemPtrList();
	while (Pos)
	{
		pOldStem		= pThisSig->GetStemPtrList()->GetNext(Pos);
		PNewStem		= pOldStem->GetPiece()    +     ssDeletee;
		PNewStem		.SimplifyParseStructure();
		pNewStem		= *Stems_Suffixed ^= PNewStem;



		if ( pNewStem )		// -- if the larger stem ("love") already existed
		{
				if ( m_LogFile ) { *m_LogFile << "\t NewStem: "<< pNewStem->GetKey()  << " existed.";		}

				bNewStemAlreadyExisted = TRUE;
				pLargerModifiedSig =
							ModifyAnExistingSignatureWithANewStem (	pOldStem, pNewStem, pThisSig );
		}
		else
		{
				if ( m_LogFile ) { *m_LogFile << "\t NewStem: "<< PNewStem.Display()  << " did not exist; it does now.";		}

				bNewStemAlreadyExisted = FALSE;
				pNewStem = CreateANewSignatureForThisStem ( PNewStem, pModifiedSig );

				val = pThisSig		->RemoveStem		( pOldStem );
				Q_ASSERT (val);


				if ( bOldSigRemains )
				{
					pOldStem			->SetSuffixList			( &WhatSigWillBecome );
					pOldStem			->SetSuffixSignature	( pOldSigBecameSig  );
				}
		}


		if ( m_LogFile ) { *m_LogFile << "\n\t\tF1: Changing stem: "<< pOldStem->GetKey() ;		}

		// go through each word associated with the OldStem, and change its suffix pointer.
		for (  i = 1; i <= (int) pThisSig->Size(); i++)
		{
			if ( bStatus[i] == FALSE )
			{
				bStemShouldRemain = TRUE;
				ssSuffix = pThisSig->GetPiece(i);
				if ( ssSuffix.IsNULL() )
				{
					Word = *pOldStem;
				}
				else
				{
					Word = pOldStem->GetPiece() + ssSuffix ;
				}

				LinkThisWordToThisSignature ( Word, pOldSigBecameSig );
				pThisSig		->RemoveWord (pWord);

				if ( !pOldSigBecameSig->GetStemPtrList()->Find( pOldStem ) )
				{
					pOldSigBecameSig->GetStemPtrList()->AddTail (pOldStem);
				}

				continue;
			} // this means the suffix doesn't delete the deleting suffix or anything

			ssNewSuffix		= SuffixChanges.GetPiece(i);

			pSuffix			= *Suffixes ^= ssNewSuffix;
			if ( ssNewSuffix.IsNULL() )
			{
				Word = PNewStem;
			}
			else
			{
				Word = pOldStem->GetPiece() + pThisSig->GetPiece(i) ;
			}

			pWord			= *Words ^= CStringSurrogate( Word );
			pWord			->AppendToConfidence( CString ("Allomorphy 2") );
			pWord			->SetSuffixPtr ( pSuffix );
			val = pThisSig	->RemoveWord (pWord);
	//		Q_ASSERT (val);

			// case like hostilit-y becoming hostility
			if ( ssNewSuffix.IsNULL() )
			{
				pWord->DoNotParse();
			}

			if ( bNewStemAlreadyExisted )
			{
				pWord				->SetSuffixSignature ( pLargerModifiedSig );
				pWord				->SetStemPtr ( pNewStem );
				pLargerModifiedSig	->AttachToSuffixSig ( pNewStem );
			}
			else
			{
				if ( m_LogFile ) { *m_LogFile << "\t NewStem: "<< PNewStem.Display()  << " did not exist.";		}
				pModifiedSig		->AttachToSuffixSig ( pNewStem, eDo_Not_Call_Words );
				pWord				->AttachSuffixSignature ( pModifiedSig );
				pWord				->SetStemPtr ( pNewStem );
			}


		}// cycle through the suffixes


		if ( bStemShouldRemain == FALSE )
		{
			Stems_Suffixed		->RemoveMember( pOldStem->GetPiece() );
		}


	}  // cycle of stems


}
*/
//		This is DEPRECATED! Not used in new code. The following version is used, the one underneath this.
void	CMiniLexicon::MoveWordsStemSuffixBoundaryToRight(CSignature* pThisSig,	 QString Deletee,  CParse* pSuffixCandidates )
{
	CSS ssDeletee;
	ssDeletee = Deletee;
	MoveWordsStemSuffixBoundaryToRight(pThisSig,  Deletee, pSuffixCandidates);
};

void	CMiniLexicon::MoveWordsStemSuffixBoundaryToRight(CSignature* pThisSig,
													 CStringSurrogate& ssDeletee,
													 CParse* pSuffixCandidates //3/04
													)
{
	CParse				PNewSig,
						POldSig,
						PMergedSig,
						PNewStem,
						PDeletee = ssDeletee;

	CSignature* pModifiedSig = NULL;
	CSignature* pOldSigBecameSig = NULL;
	CSignature* pOlderSig = NULL;

	CStringSurrogate	ssStem,
						ssSuffix,
						ssNewSuffix;
	CStem*				pOldStem;

	CStem*				pNewStem;
	CParse				DummyParse,
						Word,
						WhatSigWillBecome,
						SuffixChanges;
	CSuffix*			pSuffix;
	CStem *				pWord;
	bool				bStemShouldRemain = FALSE;

	bool				bOldSigRemains = FALSE;
	bool				bNewStemAlreadyExisted = FALSE;
	bool				val;
	int					i;
	//----------------------------------------------------------------//



	// this actually changes the signature itself:

	int* bStatus = new int [ pThisSig->Size() + 1];


	PNewSig = CreateADeletingSignature(
										pThisSig,
										PDeletee,
										SuffixChanges,
										bStatus,
										WhatSigWillBecome,
										pSuffixCandidates
										);
	if ( LogFileOn() )
	{
				*GetLogFile() <<	"<br><h4>" <<  pThisSig->Display() << " Creating new signature: "	<<
								PNewSig.Display('-') <<
								" Residue of old sig: "<<
								WhatSigWillBecome.Display() << "</h4>";
	}

	// TODO: fix this later. Eg local:  NULL.e.ly, creates a signature just NULL with locale. Not useful.
	if ( PNewSig.Size() == 1 ) {return; }

	// TODO: fix this later. Problem is what's left over is just NULL: e.g. NULL.e.ed
	if ( CSS( WhatSigWillBecome ) == CSS ( QString("NULL") ) )  { return; }

	pModifiedSig = *m_pSignatures ^= PNewSig;
	if (! pModifiedSig )
	{
		pModifiedSig = *m_pSignatures <<  &PNewSig ;
	}

	pModifiedSig->SetRemark ( pThisSig->GetRemark() + " + allomorphy" );

	if ( WhatSigWillBecome.Size() > 0 )
	{
		bOldSigRemains = TRUE;
		pOldSigBecameSig = *m_pSignatures << &WhatSigWillBecome;
		pOldSigBecameSig  ->SetRemark( QString("Allomorphy") );
	}

	//----------------------------------------------------------------//
	//	Loop through stems:
	//----------------------------------------------------------------//

     CStem* pStem;

	if ( LogFileOn() )	{ *GetLogFile() << endl << endl << StartTable <<
		StartTableRow  <<
			MakeTableHeader("NewStems") <<
			MakeTableHeader("Already existed?") <<
		EndTableRow;   }

    QList<CStem*>* Temp = pThisSig->GetStemPtrList();

     //for (pStem = Temp->first();pStem;pStem=Temp->next() )
     for (int z=0; z < Temp->size(); z++)
     {  pStem = Temp->at(z);
        pOldStem		= pStem;
        QString temp2 = pStem->Display();
        PNewStem		= *pOldStem    +     ssDeletee;
        PNewStem		.SimplifyParseStructure();
        QString temp4 = PNewStem.Display();
        pNewStem		= *m_pStems ^= PNewStem;
        QString temp3 = PNewStem.Display();

		// XXX. suppresses warning
		// `pLargerModifiedSig' may be used uninitialized
		// since g++ can’t figure out the control flow.
		CSignature* pLargerModifiedSig = 0;

		bNewStemAlreadyExisted = (pNewStem != 0);
		if (bNewStemAlreadyExisted) {
			// -- if the larger stem ("love") already existed
			if (LogFileOn()) *GetLogFile() <<
				StartTableRow <<
					TableData(pNewStem->GetKey()) <<
					TableData("yes")<<
				EndTableRow;
			pOlderSig = pNewStem->GetSuffixSignature();
			POldSig = *pNewStem->GetSuffixSignature();
			POldSig.MergeParse(PNewSig,  PMergedSig);

			pLargerModifiedSig = *m_pSignatures << &PMergedSig;
			pLargerModifiedSig->SetRemark(QString("Allomorphy1"));
			pNewStem->SetSuffixList(&PMergedSig);
			pNewStem->SetSuffixSignature( pLargerModifiedSig);
			pNewStem->SetConfidence(QString("Allomorphy1"));
			pThisSig->DetachStem(pOldStem, eDo_Not_Call_Words);
		} else {
				if ( LogFileOn() ) { *GetLogFile() <<
					StartTableRow <<
						TableData(PNewStem) <<
						TableData("no") <<
					EndTableRow;}

				pNewStem			= *m_pStems	<< PNewStem;
				pNewStem			->SetSuffixList		( pModifiedSig );
				pNewStem			->SetSuffixSignature( pModifiedSig  );
				pNewStem			->SetConfidence ( QString("Allomorphy2") );
				val = pThisSig		->RemoveStem		( pOldStem );
				Q_ASSERT (val);


				if ( bOldSigRemains )
				{
					pOldStem			->SetSuffixList			( &WhatSigWillBecome );
					pOldStem			->SetSuffixSignature	( pOldSigBecameSig  );
				}
		}



		// go through each word associated with the OldStem, and change its suffix pointer.
		for (i = 1; i <= pThisSig->Size(); ++i) {
			if ( bStatus[i] == FALSE )
			{
				bStemShouldRemain = TRUE;
				ssSuffix = pThisSig->GetPiece(i);
				if ( ssSuffix.IsNULL() )
				{
					Word = *pOldStem;
				}
				else
				{
					Word = CSS(pOldStem) + ssSuffix ;
				}

              //                if ( LogFileOn() ) { *GetLogFile() << TableData(Word);}

				pWord			= *m_pWords ^= CStringSurrogate( Word );
				pWord			->SetSuffixSignature (  pOldSigBecameSig );
				pWord			->AppendToConfidence(QString ("Allomorphy 1") );
				pOldSigBecameSig->AddWord( pWord );
                                if (   pOldSigBecameSig->GetStemPtrList()->indexOf ( pOldStem ) <  0 )
				{
					pOldSigBecameSig->GetStemPtrList()->append (pOldStem);
				}
				pThisSig		->RemoveWord (pWord);
				continue;
			} // this means the suffix doesn't delete the deleting suffix or anything

			ssNewSuffix		= SuffixChanges.GetPiece(i);

			pSuffix			= *m_pSuffixes ^= ssNewSuffix;
			if ( ssNewSuffix.IsNULL() )
			{
				Word = PNewStem;
			}
			else
			{
				Word = CSS(pOldStem) + pThisSig->GetPiece(i);
			}

            QString tempstr = Word.Display();
			if ( LogFileOn() ) { *GetLogFile() <<TableData( tempstr );		}
			pWord			= *m_pWords ^= CStringSurrogate( Word );
			pWord			->AppendToConfidence( QString ("Allomorphy 2") );
			pWord			->SetSuffixPtr ( pSuffix );
			val = pThisSig	->RemoveWord (pWord);
			Q_ASSERT (val);

			// case like hostilit-y becoming hostility
			if ( ssNewSuffix.IsNULL() )
			{
				pWord->DoNotParse();
			}

			if (bNewStemAlreadyExisted) {
				pWord->SetSuffixSignature(pLargerModifiedSig);
				pWord->SetStemPtr(pNewStem);
				pLargerModifiedSig->AttachToSuffixSig(pNewStem);
			} else {
//				if ( LogFileOn() ) { *GetLogFile() << "<td>"<< PNewStem.Display()  << " did not exist.</td>";		}
				pModifiedSig		->AttachToSuffixSig ( pNewStem, eDo_Not_Call_Words );
				pWord				->AttachSuffixSignature ( pModifiedSig );
				pWord				->SetStemPtr ( pNewStem );
			}


		}// cycle through the suffixes
        if ( LogFileOn() ) { *GetLogFile() << "</tr>";}

		if ( bStemShouldRemain == FALSE )
		{
			m_pStems	->RemoveMember( pOldStem );
		}



	}  // cycle of stems
	if ( LogFileOn() ) { *GetLogFile() << "</table>";}


}

/**
Takes as input a signature, a Deletee (stem final material that will be deleted)

*/
CParse CMiniLexicon::CreateADeletingSignature ( CSignature*		pSig,
										    CSS				Deletee,
										    CParse&			ReplacingSuffixes,
											int*			bStatus,
											CParse&			WhatSigWillBecome,
											CParse*			pSuffixCandidatesThatMightDeleteDeletee) //3/04
{


	CStringSurrogate	ssSuffix, ssTruncatedSuffix;


	CParse				PSuffix,
						NewSig,
						Suffix;
	CSuffix*			pSuffix,
						*pTruncatedSuffix;
	int					DeleteeLength = Deletee.GetLength();
	QString				QNULL ("NULL");

	ReplacingSuffixes.ClearParse();
	WhatSigWillBecome.ClearParse();

//    if ( LogFileOn() ) { *GetLogFile() << "<table><tr><th>Affix</th><th>Status</th></tr>";  }


    if ( LogFileOn() ) { *GetLogFile() <<
		StartTable <<
		StartTableRow <<
		MakeTableHeader ("Affix") <<
		MakeTableHeader ("Status") <<
		EndTableRow;
	};


	for (int n = 1; n <= pSig->Size(); n++)
	{   // Consider the suffixes in this signature. If one is the deletee, replace it by NULL.
		ssSuffix = pSig->GetPiece(n);
		if ( ssSuffix == Deletee )
		{
			NewSig.Append (QNULL );
			ReplacingSuffixes.Append ( QNULL );
			bStatus[n]		= TRUE;


			//if ( LogFileOn() ) { *GetLogFile() << "<tr><td>" << ssSuffix.Display() << "</td><td> is our deletee.</td></tr> ";}
			if ( LogFileOn() )
			{
				*GetLogFile() <<
				StartTableRow <<
				TableData(ssSuffix) <<
				TableData(" is our deletee") <<
				EndTableRow;
			}
		}
		else
		{
			pSuffix					= *m_pSuffixes ^= ssSuffix;
			ssTruncatedSuffix		= ssSuffix.Mid( Deletee.GetLength() );
			pTruncatedSuffix		= *m_pSuffixes ^= ssTruncatedSuffix;
			// 0: if the candidate doesn't delete the deleting suffix
			if ( ! pSuffixCandidatesThatMightDeleteDeletee->Contains( ssSuffix ) )
			{
				ReplacingSuffixes.Append ( QString ("***") );
				WhatSigWillBecome.Append( ssSuffix );
				bStatus[n]		 = FALSE;
				if ( LogFileOn() ) {
					*GetLogFile() <<
						StartTableRow						<<
							TableData ( ssSuffix )			<<
							TableData (" does not delete." )<<
						EndTableRow;
				}
            }
			// 1: this is the "ement" case
			else if (
					pTruncatedSuffix											&&
					pSuffix->GetKey().Left( DeleteeLength ) == Deletee		&&
					(  StemsWithBothSuffixes ( TheStringNULL,    ssTruncatedSuffix ) >
					   StemsWithBothSuffixes ( Deletee, ssSuffix          )
					)
			   )
			{
				NewSig				.Append( ssTruncatedSuffix );
				ReplacingSuffixes	.Append( ssTruncatedSuffix );
				bStatus[n]			= TRUE;
	if ( LogFileOn() )
				{
					*GetLogFile() <<
					StartTableRow <<
						TableData(ssSuffix) <<
						TableData(" the ement sort of case." ) <<
					EndTableRow;
					//*GetLogFile() << StartTableRow <<
					//						TableData( ssSuffix) <<
					//						TableData("the ement sort of case.") <<
					//					EndTableRow;;
				}

            }
			else if (
						StemsWithBothSuffixes ( TheStringNULL,    ssSuffix ) >
						StemsWithBothSuffixes ( Deletee  , ssSuffix    )
					)
			// 2: this is the case of a suffix that tdeletes a stem-final Deletee

			{
				pSuffix				->AddDeletee (Deletee);
				NewSig				.Append( ssSuffix );
				ReplacingSuffixes	.Append( ssSuffix );
				bStatus[n]			= TRUE;
                if ( LogFileOn() ) { *GetLogFile() <<
					StartTableRow <<
						TableData(ssSuffix) <<
						TableData(" is a deleter." ) <<
					EndTableRow;
				}
            }
			else
			// 3: another case where we'll say, for now, the candidate doesn't delete the deleting suffix:
			{
				ReplacingSuffixes.Append ( QString ("***") );
				WhatSigWillBecome.Append( ssSuffix );
				bStatus[n]		 = FALSE;
				if (LogFileOn()) *GetLogFile() <<
					StartTableRow <<
						TableData(ssSuffix) <<
						TableData(" maybe does not delete Deletee." ) <<
					EndTableRow;
			}
		}
	}
    if ( LogFileOn() ) { *GetLogFile() << EndTable;  }

	return NewSig;
}

/*
CParse CMiniLexicon::CreateADeletingSignature ( CSignature*		pSig,
										    CSS				Deletee,
										    CParse&			ReplacingSuffixes,
											int*			bStatus,
											CParse&			WhatSigWillBecome,
											StringToString& Remapper) //3/04
{


	CStringSurrogate	ssSuffix, ssTruncatedSuffix;

	CParse				PSuffix,
						NewSig,
						Suffix;
	int					DeleteeLength = Deletee.GetLength();
	QString				QNULL ("NULL"),
						Rewrite;

	ReplacingSuffixes.ClearParse();
	WhatSigWillBecome.ClearParse();



	for (int n = 1; n <= pSig->Size(); n++)
	{
		ssSuffix = pSig->GetPiece(n);
		if ( ssSuffix == Deletee )
		{
			NewSig.Append (QNULL) ;
			ReplacingSuffixes.Append (  QNULL);
			bStatus[n]		= TRUE;
		}
		else
		{	//if ( ! pSuffixCandidates->Contains( ssSuffix ) )

            QMap<QString,QString>::Iterator it;
            if ( Remapper.contains (ssSuffix.Display())   )
                //Remapper.Lookup( ssSuffix.SpellOut() ) )
			{
                Rewrite             =Remapper.find(ssSuffix.Display()).data();
				NewSig				.Append( Rewrite);
				ReplacingSuffixes	.Append( Rewrite);
				bStatus[n]			= TRUE;
			}
			else
			{
				ReplacingSuffixes.Append ( QString ("***") );
				WhatSigWillBecome.Append( ssSuffix );
				bStatus[n]		 = FALSE;
			}
		}
	}
	return NewSig;
}
*/
