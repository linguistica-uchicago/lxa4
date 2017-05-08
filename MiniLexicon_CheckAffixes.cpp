// Reconsidering discovered suffix-based morphology
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include <memory>
#include "linguisticamainwindow.h"
#include "DLHistory.h"
#include "Lexicon.h"
#include "Signature.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Affix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "StemCollection.h"
#include "WordCollection.h"
#include "HTML.h"
 
void CMiniLexicon::CheckSignatures() // Suffixes/Check signatures
{
	int                   NumberOfLettersToShift = 0;
	int                   InternalCount = 0;
	int                   LoopCount = 0;
	int                   LoopLimit = m_pLexicon->GetIntParameter( "CheckSignatures\\LoopLimit", 1 ); // 3 );
	int                   i, j, count;
	CSignature*           pSig, *qSig;
	CStem*                pStem, *qStem;
	QString               Null = "NULL", msg;
	CStringSurrogate      ssStem;
	CParse                PWord;
	const int             StemCountThreshold = m_pLexicon->GetIntParameter( "CheckSignatures\\StemCountThreshold", 2 );
	CAffix*               pAffix;
	CStringSurrogate      ssAffix;
	bool				  analyzingSuffixes = TRUE;
	if( m_AffixLocation == STEM_INITIAL || m_AffixLocation == WORD_INITIAL ) analyzingSuffixes = FALSE;

	std::auto_ptr<CSignatureCollection> Actions(analyzingSuffixes ?
		new CSignatureCollection(this, m_pSuffixes, m_AffixLocation ) :
		new CSignatureCollection(this, m_pPrefixes, m_AffixLocation ));

	GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": Check signatures: stem/suffix edge." );
	GetDocument()->BeginCountDown();
	
	if ( LogFileOn() )
	{
		if( analyzingSuffixes )
		{
			*GetLogFile() <<LargeTitle( "Phase: Check signatures (stem/suffix edge)");
		}
		else *GetLogFile() << LargeTitle("Phase: Check signatures (prefix/stem edge)");
	}

    
    //======================================================================//
    //                  Principal loop, through Signatures
	//======================================================================//

	while ( LoopCount < LoopLimit )
	{
		LoopCount++;
	
		Actions->Empty();
		InternalCount = 0;
		m_pSignatures->Sort(SIGS);

	
	    //----------------------------------------------------------------//
        //  Call to "CheckOut" to check each signature.
        //----------------------------------------------------------------//

        for ( i = 0; i < (int)m_pSignatures->GetCount(); i++)
		{
			msg = QString("%1").arg(LoopCount) + ": " + QString("%1").arg( m_pSignatures->GetCount() - i );
			GetDocument()->setStatusBar2( msg );
			GetDocument()->CountDownOnStatusBar( i, m_pSignatures->GetCount() );
			pSig = m_pSignatures->GetAtSort(i);
			pSig->SetAffixLocation( m_AffixLocation );
	
			if ( pSig->GetNumberOfStems() < StemCountThreshold ) { continue; }
	
  			//==========================================================
			NumberOfLettersToShift = pSig->CheckOut(this);
			//==========================================================
	
			if ( NumberOfLettersToShift > 0)
			{
				InternalCount ++;
	
				qSig = *Actions << pSig;
			
				qSig->SetCorpusCount( NumberOfLettersToShift );// non-standard meaning!
			}
		}
	
	    //----------------------------------------------------------------//
        //  If there are no signatures being modified, leave function..
        //----------------------------------------------------------------//


		if ( InternalCount == 0 )
		{
			if( analyzingSuffixes )
			{
				GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": End of Check signatures: stem/suffix edge." );
			}
			else GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": End of Check signatures: prefix/stem edge." );
			GetDocument()->setStatusBar2 ( "" ) ;

	        if ( LogFileOn() )
	        {
                *GetLogFile() << "No signatures to modify now. <hl>";
            }
			return;
		}
	

  	    //----------------------------------------------------------------//
        //  Section *A*
		//  Now we make the changes in the words which we have identified above.
		//  Bear in mind that the (positive or negative) integer in Sig.CorpusCount is the number of
		//  letters to the right or left that the stem/suffix cut should be shifted.
        //
        //----------------------------------------------------------------//
	
	
		if ( LogFileOn())
		{
			*GetLogFile() << SmallTitle("Remaking signature") << 
                    StartTable << StartTableRow << 
                    	MakeTableHeader("New signature") << 
                    	MakeTableHeader("Old stem") << 
                    	MakeTableHeader("New stem"); 
		}
	
		for (int k = 0; k < (int)Actions->GetCount(); k++)
		{
			//---------------------------------------------------------------------------//
	        //  Loop through each signature about to be modified.
			//---------------------------------------------------------------------------//
			pSig = Actions->GetAt(k);
			int		NumberOfLettersShifted = pSig->GetCorpusCount(); // non-standard meaning.
			
			///--------------------------------------------------------------------------//
			if ( LogFileOn())
			{
				*GetLogFile() <<  
					StartTableRow <<
						TableData(pSig) <<
					EndTableRow;
			}			
			//---------------------------------------------------------------------------//
	        //  Loop through each stem in this signature
			//---------------------------------------------------------------------------//

                        for (int z = 0; z < pSig->GetStemPtrList()->size(); z++)
                        {
                            pStem = pSig->GetStemPtrList()->at(z);
                            ssStem = pStem->GetKey();
	
                            if ( LogFileOn())
                            {
					*GetLogFile() << endl << 
							StartTableRow <<
								TableData() <<
								TableData() <<
								TableData(ssStem);
                            }
                            for (int m = 1; m <= pSig->Size(); m++)
                            {
					ssAffix = pSig->GetPiece(m);
					if ( ssAffix == CStringSurrogate(Null) )
					{
						ssAffix.MakeNull();
					}
			
					if( analyzingSuffixes ) PWord = ssStem + ssAffix;
					else PWord = ssAffix + ssStem;
			
					CStem* pWord = *m_pWords ^= PWord;
	
		
					if( analyzingSuffixes )
					{
						if( ssAffix.GetLength() == 0 && pWord->GetSuffixLoc() > 0 ) continue; // the stem has an internal analysis already 3/2003
					}
					else
					{
						if( ssAffix.GetLength() == 0 && pWord->GetStemLoc() > 0 ) continue;
					}
		
					if ( pWord->GetWordType() == BIWORD_COMPOUND   ||
						pWord->GetWordType() == MULTIPLE_COMPOUND ||
						pWord->GetWordType() == POSSIBLE_COMPOUND    )
					{
						continue;
					}
		
					Q_ASSERT ( pWord->IsValid() );
					
					if ( (int)ssStem.GetLength() <=  NumberOfLettersShifted ) { continue; } ;
					// TODO: do the same thing below for prefixes if necessary

					if( analyzingSuffixes ) pWord->ShiftStemSuffixBoundary ( -1 * NumberOfLettersShifted );  
					//else pWord->ShiftPrefixStemBoundary( pSig->GetCorpusCount() );
		
					Q_ASSERT ( pWord->IsValid() );
					if ( LogFileOn())
					{
						*GetLogFile() <<
							TableData(pWord->GetStem())<<
							EndTableRow;
					}
                            }// each affix in the signature
			}
                        if ( LogFileOn())
			{
				*GetLogFile() << endl << "</tr>"  << endl; 
			}
		}   // loop over signatures being remade
  	    //----------------------------------------------------------------//
        //               End of Section *A*
        //
        //----------------------------------------------------------------//

        
        if ( LogFileOn())
		{
			*GetLogFile() << endl << "</table>" << endl; 
		}
	
 		
        //-------------------------------------------------------------//
  //////////////////////////////////////////////////////////////////////////////
  //  Redo Signatures
  	QString Remark ("Checking signatures");
  	CStringSurrogate ssRemark ( Remark);   
//    RebuildAffixesStemsAndSignaturesFromWordSplits( ssRemark );

   ///////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++////////////
   ///////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++////////////

		std::auto_ptr<CStemCollection> OldStems(m_pStems);
		m_pStems  = new CStemCollection(this);
		
		
		if ( analyzingSuffixes )
		{
			delete m_pSuffixes;
			m_pSuffixes = new CSuffixCollection (this);
		}
		else
		{
			delete m_pPrefixes;
			m_pPrefixes = new CPrefixCollection (this);
		}

		std::auto_ptr<CSignatureCollection> OldSignatures(m_pSignatures);
		if( analyzingSuffixes ) 
		{
			m_pSignatures = new CSignatureCollection(this, m_pSuffixes, WORD_FINAL);
		}
		else 
		{
			m_pSignatures = new CSignatureCollection( this, m_pPrefixes, WORD_INITIAL );
		}
		
		for (i = 0; i < (int)m_pWords->GetCount(); i++)
		{
			CStem* pWord = m_pWords->GetAt(i);
			pWord->ClearPointers();
		
			if( pWord->GetWordType() == MULTIPLE_COMPOUND ||
				pWord->GetWordType() == BIWORD_COMPOUND   ||
				pWord->GetWordType() == POSSIBLE_COMPOUND   ) continue;
				
			if (pWord->Size() < 2) continue;
		
			Q_ASSERT (pWord->IsValid());
		
			if( analyzingSuffixes )
			{
        
				pStem  = *m_pStems << pWord->GetPiece(1);
				pAffix = *m_pSuffixes << pWord->GetPiece(2).Display();
			}
			else
			{
				pStem = *m_pStems << pWord->GetPiece(2);
				pAffix = *m_pPrefixes << pWord->GetPiece(1);
			}
				
			qStem  = *OldStems ^= pStem->GetKey();
			if ( qStem )
			{
				pStem->SetConfidence( qStem->GetConfidence() );
			}
			else
			{
				msg = "Check sigs";
				pStem->SetConfidence( msg );
			}
		
			if( analyzingSuffixes ) pWord->AttachWordStemAndSuffix ( pStem, (CSuffix*)pAffix );
			else pWord->AttachWordStemAndPrefix( pStem, (CPrefix*)pAffix );

 
			m_pStems->IncrementCorpusCount ( (int) pWord->GetCorpusCount() );
		
			if( analyzingSuffixes )
			{
				pWord->SetStemLoc(1);
				pWord->SetSuffixLoc(2);
				m_pLexicon->UpdateWord( pWord );
			}
			else
			{
				pWord->SetStemLoc(2);
				pWord->SetPrefixLoc(1);				
				m_pLexicon->UpdateWord( pWord );
			}
			
			pWord->DoNotParse();
		}
		
		for ( i = 0; i < (int)m_pStems ->GetCount(); i++) // Stem iteration
		{
			pStem = m_pStems->GetAt(i);

			if (CStem* pWord = *m_pWords ^= pStem) {
				if( analyzingSuffixes )
				{
					pStem->AddSuffix( Null );
					pAffix = *m_pSuffixes << TheStringNULL;
					pAffix->IncrementUseCount();
					pAffix->IncrementCorpusCount( pWord->GetCorpusCount() - 1);
					pAffix->AddStem(pStem);
					pStem->IncrementCorpusCount ( pWord->GetCorpusCount() );// June 2005
				}
				else
				{
					pStem->AddPrefix( Null );
					pAffix = *m_pPrefixes << CStringSurrogate(Null);
					pAffix->IncrementUseCount();
					pAffix->IncrementCorpusCount( pWord->GetCorpusCount() - 1);
					pAffix->AddStem(pStem);
					pStem->IncrementCorpusCount ( pWord->GetCorpusCount() );// June 2005

				}
			}

			if( analyzingSuffixes )
			{
				pSig = *m_pSignatures << pStem->GetSuffixList();
				pSig->AttachToSuffixSig(pStem);
			}
			else
			{
				pSig = *m_pSignatures << pStem->GetPrefixList();
				pSig->AttachToPrefixSig(pStem);
			}		
		
			foreach (CStem* pWord, *pStem->GetWordPtrList()) {
				if (analyzingSuffixes)
					pWord->SetSuffixSignature(pSig);
				else
					pWord->SetPrefixSignature(pSig);
			}
		
			qSig  = *OldSignatures ^= pSig;
			if ( qSig )
			{
				pSig->SetRemark( qSig->GetRemark() );  
			}
			else
			{
				msg = "Check sigs";
				pSig->SetRemark( msg );
			}
		}// Stem iteration

		if ( LogFileOn())
		{
			*GetLogFile() << endl << "</table>" << endl; 
		}    

         
    

	}
	//======================================================================//
    //  End of principal loop 
	//======================================================================//

    //-----------------------------------------------------------------//
	// Reconnect affixes to new stem pointers by means of the spelled-out stems (StemString)
    //-----------------------------------------------------------------//

    if( analyzingSuffixes ) count = m_pSuffixes->GetCount();
	else count = m_pPrefixes->GetCount();
	
	for( i = 0; i < count; i++ )
	{
		if( analyzingSuffixes )	pAffix = m_pSuffixes->GetAt(i);
		else pAffix = m_pPrefixes->GetAt(i);
		if( pAffix ) 
		{
			pAffix->ClearStemPtrList();

			for( j = 1; j <= pAffix->GetNumberOfStems(); j++ )
			{
				pStem = *m_pStems ^= pAffix->GetStemString()->GetPiece(j);
				if( pStem ) pAffix->AddStem( pStem );
			}
		}
	}
    //-----------------------------------------------------------------//
    //-----------------------------------------------------------------//
	
	
	if( analyzingSuffixes )
		GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": End of Check signatures: stem/suffix edge." );
	else
		GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": End of Check signatures: prefix/stem edge." );
	GetDocument()->setStatusBar2 ( "" ) ;
	
	GetDocument()->EndCountDown();

	

	QString mini_name( "Mini-Lexicon %1" );
	mini_name = mini_name.arg( GetIndex() + 1 );
	QString remark = "Check stem/suffix cut";
	GetDLHistory()->append( mini_name, remark, this );
}
