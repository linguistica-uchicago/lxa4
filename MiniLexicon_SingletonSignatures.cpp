// Fixing false signatures like -t-ion
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "DLHistory.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Affix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "PrefixCollection.h"
#include "SuffixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "HTML.h"

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////// 
void	CMiniLexicon::FindSingletonSignatures()
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
{
	int MinimumAffixCount  = 50;
	int MinimumAffixLength = 2;
	int MinimumStemLength  = 3;

	CStem*			 pStem;
	CParse		 	 NewSig;
	CSignature*		 pNewSig;
	CStringSurrogate ssSubAffix;
	CAffix*			 pSubAffix;	
	bool analyzingSuffixes = TRUE;
	if( m_AffixLocation == WORD_INITIAL || m_AffixLocation == STEM_INITIAL ) analyzingSuffixes = FALSE;
	QString msg = "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": Finding singleton signatures";
	GetDocument()->setStatusBar1 ( msg );
	GetDocument()->BeginCountDown(); 
	 
	// loop through suffixes


	/*	Some of the singleton signatures that were created during SF1 can
		now be checked, and seen to be faulty. E.g., there is a strong
		tendency in English to choose -tion in SF1, whereas now we
		know this is not a smart choice. Maybe this should be a general
		check of suffixes, though.

	TODO: This strategy works poorly, though, for words that end in -ies, since
		es gets chosen over -ies.
	*/

	if( analyzingSuffixes )
	{
		 m_pSuffixes->Sort(LENGTH);
		if (LogFileOn())
		{
			*GetLogFile() << LargeTitle("Phase: Finding singleton suffixes") << StartTable <<endl;
		}

		for (int i = 0; i < (int)m_pSuffixes->GetCount(); i++)
		{
			CSuffix* pSuffix = m_pSuffixes->GetAtSort(i);
			int SuffixLength	= pSuffix->GetKeyLength();
			int ThisUseCount	= pSuffix->GetUseCount();

			GetDocument()->CountDownOnStatusBar( i, m_pSuffixes->GetCount() );

			if ( ThisUseCount			< MinimumAffixCount ) continue; // 50
			if ( SuffixLength				< MinimumAffixLength) continue; // 3

			CStringSurrogate ssSuffix		= pSuffix->GetKey();

			// if there's a shorter subsuffix of length 2 or more which has a higher count,
			// then don't use this suffix, use that one;
			bool bIgnoreThisSuffixFlag = FALSE;
			for (int i = SuffixLength - 1; i >= 2; i--)
			{
				ssSubAffix = ssSuffix.Right (i);
				pSubAffix = *m_pSuffixes ^= ssSubAffix;
				if ( pSubAffix		&&	 pSubAffix->GetUseCount() > ThisUseCount )
				{
					bIgnoreThisSuffixFlag = TRUE;
					if (LogFileOn())
					{
										*GetLogFile() <<	"\nIgnore	"				<<
										ssSuffix.Display() <<
										"\t"				<<
										pSubAffix->Display(); 
					}
				}
			}
			if ( bIgnoreThisSuffixFlag ) { continue; }

			for (int w = 0; w < (int)m_pWords->GetCount(); w++)
			{
				CStem* pWord = m_pWords->GetAt(w);

				if ( pWord->Size() > 1 ) continue;
				if ( pWord->GetKeyLength() < SuffixLength + MinimumStemLength ) continue;
				if (FALSE && LogFileOn())
				{
						*GetLogFile()	<<	
						StartTableRow <<
							TableData(pWord) <<
						EndTableRow << endl; 				}

				if ( pWord->GetKey().Right( SuffixLength ) == ssSuffix )
				{
 					if (LogFileOn())
					{
							*GetLogFile()	<<
							StartTableRow <<
								TableData(ssSuffix) <<
								TableData (pWord) <<
							EndTableRow << endl;
					}

					pWord->CutNFromTheRight( SuffixLength );
					pStem = *m_pStems << pWord->GetPiece(1);

					pWord->SetStemLoc(1);
					pWord->SetSuffixLoc(2);
					pWord->SetStemPtr( pStem );
					pWord->SetSuffixPtr( pSuffix );
					pWord->AppendToConfidence( "Singleton sig" );
					m_pLexicon->UpdateWord( pWord );



					NewSig.ClearParse();

					bool bOldStemExisted = FALSE;
					// if pStem had a signature before...
					if ( pStem->GetSuffixSignature() )
					{
						NewSig = pStem->GetSuffixList();
						bOldStemExisted = TRUE;
						if ( LogFileOn() ) { *GetLogFile() << "\t Singleton signature: to a stem that already existed. "<< pStem->GetKey().Display()	<< " existed.";		}
					}
					if(!NewSig.GetSortStyle() != eAlphabetized) NewSig.Alphabetize();
					NewSig.Append(ssSuffix);

					// Word: detach from pSig, attach to pNewSig
					// pStem: add new word to its list
					// this should do both:
					pWord->AttachWordAndSuffixalStem( pStem );

					pNewSig = *m_pSignatures << &NewSig;
					pNewSig->AddWord( pWord ); // increments it by 1 too many?
					pNewSig->GetStemPtrList()->append( pStem );

					// pSig: if the stem previously existed, we must remove it
					// from its old sig and give it to its new.

					pWord->AttachSuffixSignature ( pNewSig );


					// in fact, we need to remove all the stems from the old
					// sig and give them to the new sig: this should do it;

					pNewSig->AttachStemFromDifferentSuffixSignature (pStem);

					QString rmk = "Singleton";
					pNewSig->SetRemark (rmk);
				}
			}
		}
		if (LogFileOn()){ *GetLogFile() <<"</table>"<< endl; }
	}
	else
	{
		m_pPrefixes->Sort(LENGTH);

		for (int i = 0; i < (int)m_pPrefixes->GetCount(); i++)
		{
			CPrefix* pPrefix	= m_pPrefixes->GetAtSort(i);
			int PrefixLength	= pPrefix->GetKeyLength();
			int ThisUseCount	= pPrefix->GetUseCount();

			GetDocument()->CountDownOnStatusBar( i, m_pPrefixes->GetCount() );

			if ( ThisUseCount < MinimumAffixCount ) continue; // 50
			if ( PrefixLength < MinimumAffixLength) continue; // 3

			CStringSurrogate ssPrefix		= pPrefix->GetKey();


			// if there's a shorter subprefix of length 2 or more which has a higher count,
			// then don't use this prefix, use that one;
			bool bIgnoreThisPrefixFlag = FALSE;
			for (int i = PrefixLength - 1; i >= 2; i--)
			{
				ssSubAffix = ssPrefix.Right (i);
				pSubAffix = *m_pPrefixes ^= ssSubAffix;
				if ( pSubAffix		&&	 pSubAffix->GetUseCount() > ThisUseCount )
				{
					bIgnoreThisPrefixFlag = TRUE;
					if (LogFileOn())
					{
										*GetLogFile() <<	"\nIgnore	"				<<
										ssPrefix.Display() <<
										"\t"				<<
										pSubAffix->Display(); 
					}
				}
			}
			if ( bIgnoreThisPrefixFlag ) { continue; }

			for (int w = 0; w < (int)m_pWords->GetCount(); w++)
			{
				CStem* pWord = m_pWords->GetAt(w);

				if ( pWord->Size() > 1 ) continue;
				if ( pWord->GetKeyLength() < PrefixLength + MinimumStemLength ) continue;

				if ( pWord->GetKey().Left( PrefixLength ) == ssPrefix )
				{

					if (LogFileOn())	 { *GetLogFile() << "\n" << ssPrefix.Display() << "\t" << pWord->Display(); }

					pWord->CutNFromTheLeft( PrefixLength );
					pStem = *m_pStems << pWord->GetPiece(2);

					pWord->SetStemLoc(2);
					pWord->SetPrefixLoc(1);
					pWord->SetStemPtr(pStem);
					pWord->SetPrefixPtr(pPrefix);
					pWord->AppendToConfidence ("Singleton sig");
					m_pLexicon->UpdateWord( pWord );



					NewSig.ClearParse();

					bool bOldStemExisted = FALSE;
					// if pStem had a signature before...
					if ( pStem->GetPrefixSignature() )
					{
						NewSig = pStem->GetPrefixList();
						bOldStemExisted = TRUE;
						if ( LogFileOn() ) { *GetLogFile() << "\t Singleton signature: to a stem that already existed. "<< pStem->GetKey().Display()	<< " existed.";		}
					}
					if ( NewSig.GetSortStyle() != eAlphabetized)  NewSig.Alphabetize();
					NewSig.Append(ssPrefix);

					if (LogFileOn())	 { *GetLogFile() << " " << NewSig.Display(); }


					// Word: detach from pSig, attach to pNewSig
					// pStem: add new word to its list
					// this should do both:
					pWord->AttachWordAndPrefixalStem (pStem);



					pNewSig = *m_pSignatures << &NewSig;
					pNewSig->AddWord( pWord ); // increments it by 1 too many?
					pNewSig->GetStemPtrList()->append(pStem);

					// pSig: if the stem previously existed, we must remove it
					// from its old sig and give it to its new.

					pWord->AttachPrefixSignature ( pNewSig );


					// in fact, we need to remove all the stems from the old
					// sig and give them to the new sig: this should do it;

					pNewSig->AttachStemFromDifferentPrefixSignature (pStem);



					QString rmk = "Singleton";
					pNewSig->SetRemark (rmk);
				}
			}
		}
	}
	msg				= "";
	QString mini_name( "Mini-Lexicon %1" );

	GetDocument()	->setStatusBar1 ( msg );
	GetDocument()	->EndCountDown();

 	mini_name		= mini_name.arg( GetIndex() + 1 );
	QString remark	= "Find singleton signatures";
	GetDLHistory()	->append( mini_name, remark, this );
}
