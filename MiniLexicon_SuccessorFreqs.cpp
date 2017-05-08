// Analyzing words using discovered signatures
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include <Q3ValueList>
#include <QString>
#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "DLHistory.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "WordCollection.h"
#include "StringSurrogate.h"
#include "Parse.h"
#include "HTML.h"

// We accept any stem if it can match a good signature

void CMiniLexicon::TakeSignaturesFindStems( CSignatureCollection* Sigs )
{
	CStem*      pWord;
	const int   SizeThreshold = m_pLexicon->GetIntParameter( "TakeSignaturesFindStems\\SizeThreshold", 2 ); // 2;
	const int   StemCountThreshold = m_pLexicon->GetIntParameter( "TakeSignaturesFindStems\\StemCountThreshold", 2 ); // 2;// 8;
 	const int   MinimumStemLength = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 10 );

	CParse            PWord;
	QString           Word,
	Message;
	CStringSurrogate  ssAffix,
	ssWord,
	ssStem;
	CSignature*       pSig;

 	CWordCollection   TempWords (this);
	CWordCollection   WordsSplit (this);
	int               AffixLength;
	QString           msg;
	int               m;

	if( Sigs == NULL ) Sigs = m_pSignatures;

	GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": Take signatures to find stems" );
	GetDocument()->BeginCountDown();

  
	if( LogFileOn() )
	{ 
		*GetLogFile() <<LargeTitle( "Phase: Take Signatures, Find Stems"); 
	}
 

	bool analyzingSuffixes = TRUE;
	if( GetAffixLocation() == STEM_INITIAL || GetAffixLocation() == WORD_INITIAL ) analyzingSuffixes = FALSE;

	for (int i = 0; i < (int)m_pWords->GetCount(); i++)
	{
		if ( !m_pWords->GetAt(i)->MayBeParsed() )
		{
			continue;
		}
		TempWords << m_pWords->GetAt(i);
	}


//	We loop through the good signatures, and then run through
//	the words to see if they could belong to the good signatures.
//	We have to be careful, because a word might have belonged
//	to a different signature, and still have the marks of those
//	suffixes in its factorization.

    if (LogFileOn()  )
     {
        *GetLogFile() << StartTable << 
        	StartTableRow << 
        		MakeTableHeader(" --") <<
        		MakeTableHeader("Signature") << 
        	EndTableRow;  
    }
	// Go through signatures:
	Sigs->Sort(SIGS);

	for (int j = 0; j < (int)Sigs->GetCount(); j++) //Loop A
	{

		pSig = Sigs->GetAtSort(j);

        if (!pSig) continue; 

		if (LogFileOn() )
		{ 
			*GetLogFile() << 
				StartTableRow << 
					TableData(j) << 
					TableData(pSig->Display('.'))  << 
				EndTableRow;          
		}

		GetDocument()->CountDownOnStatusBar ( j, Sigs->GetCount(), 5 );
		GetDocument()->setStatusBar2 ( pSig->Display() );


		if ( pSig->Size() < SizeThreshold ) continue;
		if ( pSig->GetNumberOfStems() < StemCountThreshold ) continue;
 
		// Choose the first suffix in pSig that isn't NULL:
		int k = 1;
		if( pSig->GetPiece(1).IsNULL() ) k = 2;

 		Q3ValueList<CStem> TempStems2;  // replaces TempStems1 -- fix memory leak
   
		ssAffix = pSig->GetPiece(k);
		AffixLength = ssAffix.GetLength();

		for ( m = 0; m < (int)TempWords.GetCount(); m++)
		{//Loop B
			pWord = TempWords[m];
			ssWord = pWord->GetKey();

			if( analyzingSuffixes )
			{ //Loop C
				if ( ssWord.Right(AffixLength) == ssAffix.Display() )
				{
					if ( (int)ssWord.GetLength() == AffixLength ) { continue; }
					ssStem = ssWord;
					ssStem = ssStem.Left(ssWord.GetLength() - AffixLength );

					Q_ASSERT ( ssStem.GetLength() != 0);

					if ( (int) ssStem.GetLength() < MinimumStemLength ) continue;

					if ( LogFileOn() ) { *GetLogFile() << 
							StartTableRow <<
								TableData(QString("")) <<
								TableData(ssStem) <<
							EndTableRow; 
					}

					// put into Temp Stems all those stems from words which might be analyzed as ending in ssAffix.
 					TempStems2.append(ssStem);
				}
			}//Loop C
			else
			{//Loop C
				if ( ssWord.Left(AffixLength) == ssAffix.Display() )
				{
					if ( (int)ssWord.GetLength() == AffixLength ) { continue; }
					ssStem = ssWord;
					ssStem = ssStem.Right( ssWord.GetLength() - AffixLength );

					Q_ASSERT ( ssStem.GetLength() != 0);

					if ( (int) ssStem.GetLength() < MinimumStemLength ) continue;

					if ( LogFileOn() ) { *GetLogFile() << 
							StartTableRow <<
								TableData(QString("")) <<
								TableData(ssStem) <<
							EndTableRow; 
					}
					// put into Temp Stems all those stems from words which might be analyzed as ending in ssAffix.
					TempStems2.append(ssStem);
				}
			} // Loop C
		} // Loop B

		for ( m = 1; m <= pSig->Size(); m++)
		{ // Loop B
			if ( (int) m == k ) continue; // we've already done it --

			ssAffix = pSig->GetPiece(m);

			if (ssAffix.IsNULL()) {
				for (Q3ValueList<CStem>::iterator it = TempStems2.begin();
						it != TempStems2.end(); ++it) {
					for (; it != TempStems2.end() &&
								!(*m_pWords ^= *it);
							it = TempStems2.erase(it)) {
						if ( LogFileOn() ) *GetLogFile() <<
							StartTableRow <<
								TableData(QString("")) <<
								TableData(*it) <<
							EndTableRow;
					}
				}
			} else {
 				Q3ValueList<CStem>::Iterator it = TempStems2.begin(); 
            	while (it != TempStems2.end())
				{
 					CStem& stem = *it;
					if (LogFileOn() ) { *GetLogFile() << endl << stem.GetKey().Display(); }
					if( analyzingSuffixes ) PWord = stem.GetKey() + ssAffix;
					else PWord = ssAffix + stem.GetKey();

 					if ( LogFileOn() ) { *GetLogFile() << 
							StartTableRow <<
								TableData(QString("")) <<
								TableData(PWord ) <<
							EndTableRow; }

					if ( ! (TempWords ^= PWord) )
					{
						// this is too stringent: we probably want to keep some of these subsignatures.
//						if (LogFileOn() ) { *GetLogFile() <<  "  Missing: " << stem.GetKey().Display(); }
						if ( LogFileOn() ) { *GetLogFile() << 
							StartTableRow <<
								TableData("Missing") <<
								TableData(stem.GetKey()) <<
							EndTableRow; }
						it = TempStems2.erase(it);
					} 
					else ++it;
				}
			}
		}



		// Now start building up pSig again....


		Q3ValueList<CStem>::Iterator it;
		for (it = TempStems2.begin(); it != TempStems2.end(); ++it)
		{			//Loop B
			CStem& stem = *it;
			ssStem    = stem;

			for (int n = 1; n <= pSig->Size(); n++)
			{
				ssAffix = pSig->GetPiece(n);
				if (ssAffix.Display() == "NULL" ) continue;

				if( analyzingSuffixes ) PWord = ssStem + ssAffix;
				else PWord = ssAffix + ssStem;

				pWord = *m_pWords ^= PWord;
				Q_ASSERT (pWord);

				if( analyzingSuffixes )
				{
					pWord->ClearRootSuffixSplit();
					pWord->CutRightBeforeHere ( ssStem.GetLength() );
					pWord->SetStemLoc(1);
					pWord->SetSuffixLoc(2);
					m_pLexicon->UpdateWord( pWord );
				}
				else
				{
					pWord->ClearPrefixStemSplit();
					pWord->CutRightBeforeHere ( ssAffix.GetLength() );
					pWord->SetStemLoc(2);
					pWord->SetPrefixLoc(1);
					m_pLexicon->UpdateWord( pWord );
				}

				if (pWord->GetConfidence().length() == 0)
				{
					msg = "3: From sig find stem";
					pWord->AppendToConfidence( msg ) ;
				}
				if (LogFileOn() ) { *GetLogFile() << endl << "Reanalyzed word: "<< pWord->Display(); }
				if ( LogFileOn() ) { *GetLogFile() << 
							StartTableRow <<
								TableData("Reanalyzed word:") <<
								TableData(pWord) <<
							EndTableRow; }

			} // cycle through this signature
		}// cycle through this set of Stems //Loop B
	}// end of pSig loop Loop A

    if (LogFileOn() ) { *GetLogFile() << EndTable; }

	GetDocument()->setStatusBar2( "" );

	QString mini_name( "Mini-Lexicon %1" );
	msg = "From sigs find stems";
	CStringSurrogate ssRemark	= msg;

	TakeSplitWords_ProduceStemsAndSigs( ssRemark );

	TempWords.Empty();
	GetDocument()				->setStatusBar1( "" );
	mini_name					= mini_name.arg( GetIndex() + 1 );
	QString remark				= "From sigs: find stems";
	GetDLHistory()				->append( mini_name, remark, this );


	////////////////////////////////////////////////////////////
	//
	//  end of function
	//
	////////////////////////////////////////////////////////////

}

