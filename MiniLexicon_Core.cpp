// Suffix/signature-based discovery of morphology: core
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include <memory>
#include <vector>
#include <QList>
#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "DLHistory.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "WordCollection.h"
#include "StemCollection.h"
#include "CompareFunc.h"
#include "StringFunc.h"
#include "HTML.h"
#include "AffixLocation.h"
#include "implicit_cast.h"
#include <list>
using linguistica::implicit_cast;
 

void CMiniLexicon::TakeSplitWords_ProduceStemsAndSigs( CStringSurrogate& Remark,
                                                       CWordCollection* pWords,
                                                       CStemCollection* pStems,
                                                       CPrefixCollection* pPrefixes,
                                                       CSuffixCollection* pSuffixes )

{
        if( pWords == NULL )    { pWords = m_pWords; };
        if( pStems == NULL )    { pStems = m_pStems; }
	if( pPrefixes == NULL ) { pPrefixes = m_pPrefixes; }
	if( pSuffixes == NULL ) { pSuffixes = m_pSuffixes; }

	RebuildAffixesStemsAndSignaturesFromWordSplits( Remark );
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//
//    void  RebuildAffixesStemsAndSignaturesFromWordSplits();
//      this is called by RebuildAffixesStemsAndSignatures()
//
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void CMiniLexicon::RebuildAffixesStemsAndSignaturesFromWordSplits( CStringSurrogate& Remark )
{
  int      HowManySuffixes = 0, HowManyPrefixes = 0;
  int i;
  CStemCollection       *OldStems;
  CStringSurrogate      ssPrefix,
                        ssStem,
                        ssSuffix;
  CStem*                pWord       = NULL;
  CSuffix*              pSuffix     = NULL;
  CStem*                pStem, *qStem;
  CPrefix*              pPrefix     = NULL;
  CSuffix*              pNullSuffix = NULL;
  CPrefix*              pNullPrefix = NULL;
  GetDocument()->setStatusBar2 ( "Rebuilding all signature structures." );
  if (LogFileOn()) { *GetLogFile() << SmallTitle("Rebuilding all signature structures");}
  bool analyzingSuffixes = TRUE;
  if( m_AffixLocation == STEM_INITIAL || m_AffixLocation == WORD_INITIAL ) analyzingSuffixes = FALSE;
  if ( analyzingSuffixes )
  { 
    m_pSuffixes->RemoveAll();
    pNullSuffix = *m_pSuffixes << TheStringNULL;
  }
  else
  {
    m_pPrefixes->RemoveAll();
    pNullPrefix = *m_pPrefixes << TheStringNULL;
  }
  OldStems = m_pStems;
  m_pStems = new CStemCollection(this);
  GetDocument()->BeginCountDown();
  for ( i = 0; i < (int)m_pWords->GetCount(); i++)
  {
    GetDocument()->setStatusBar2 ( "Rebuilding all signature structures: words." );

    
    pWord = m_pWords->GetAt(i);
    if (! pWord) continue;  //@@@@@@

	Q_ASSERT (pWord);

    if( pWord->Size() < 2 )
	{
		pWord->SetSuffixSignature( NULL );
		pWord->SetPrefixSignature( NULL );
	}

    GetDocument()->CountDownOnStatusBar(i, m_pWords->GetCount());

    if( pWord->GetWordType() == BIWORD_COMPOUND   ||
        pWord->GetWordType() == MULTIPLE_COMPOUND ||
        pWord->GetWordType() == NUMBER              ) continue;

    Q_ASSERT (pWord->IsValid());

    //  ***    rebuild stems, part 1  ***
   
    ssStem = pWord->GetStem();

    if( ssStem.GetLength() == 0 )
    {
      pWord->SetStemLoc(1);
      pWord->SetSuffixLoc(0);
      pWord->SetPrefixLoc(0);
      continue;
    }

    //  *** rebuild affixes:  ***

    if( analyzingSuffixes )
    {
      ssSuffix = pWord->GetSuffix();
      if (ssSuffix.GetLength() < 1)      { continue; }
      pSuffix = (*m_pSuffixes) << ssSuffix;
      if (!pSuffix) continue; 
      pSuffix->IncrementCorpusCount( pWord->GetCorpusCount() - 1 );
      pSuffix->IncrementUseCount();
      pWord->SetSuffixPtr(pSuffix);
      HowManySuffixes++;
    }
    else
    {
      ssPrefix = pWord->GetPrefix();
      if ( ssPrefix.GetLength() < 1)
      {
        continue;
      }
      pPrefix = (*m_pPrefixes) << ssPrefix;
      pPrefix->IncrementCorpusCount( pWord->GetCorpusCount() - 1 );
      pPrefix->IncrementUseCount();

      pWord->SetPrefixPtr(pPrefix);

      HowManyPrefixes++;
    }
    
    // ***  attach affix to stem     ***

     if( analyzingSuffixes )
    { 
      pStem		= (*m_pStems)	<< ssStem ;
      if (! pStem) continue; 
      pWord		->AttachWordAndSuffixalStem(pStem);
      pSuffix	= (*m_pSuffixes) ^= pWord->GetSuffix();  // 2005-06-24 : changed from insertion (<<) to find (^=)      
      if ( ! pSuffix ) continue; 
      pSuffix	->AddStem(pStem);       
    }
    else
    {
      pStem		= (*m_pStems) << ssStem;
      pWord		->AttachWordAndPrefixalStem(pStem);
      pPrefix	= (*m_pPrefixes) ^= pWord->GetPrefix();  // 2005-06-24 : changed from insertion (<<) to find (^=)
      pPrefix	->AddStem(pStem);
    }
              
    pStem->SetConfidence( pWord->GetConfidence() );

    qStem = *OldStems ^= pStem->GetKey();
    if ( qStem )
    {
      pStem->SetConfidence( qStem->GetConfidence() );
    }
    else
    {
      pStem->SetConfidence( Remark.Display() );
    }           

    Q_ASSERT ( pWord->IsValid() );

    if( analyzingSuffixes )
    {
      pStem->AddSuffix( pSuffix );
    }
    else
    {
      pStem->AddPrefix( pPrefix );
    }
    if (LogFileOn()) { *GetLogFile() <<"</tr>";}

}// loop over words
if ( LogFileOn() ) {  *GetLogFile() << "</table>"; }
if ( LogFileOn() ) {  *GetLogFile() << "End of word loop."; }
  /* in what follows:   **************************************************
   * if a stem is also a word, then we add NULL
   * to the stem's factorization.
     *
   *
   *    ***    Stems Loop    ****
   ***********************************************************************/
  GetDocument()->BeginCountDown();
  GetDocument()->setStatusBar2 ( "Rebuilding all signature structures:stems." );
  if (LogFileOn()) 
  { 
      *GetLogFile() <<SmallTitle("Stem loop") << StartTable;
  }
  for ( i = 0; i < (int)m_pStems->GetCount(); i++)
  { 
    
    pStem = m_pStems->GetAt(i);
    GetDocument()->CountDownOnStatusBar(i, m_pStems->GetCount());
    if (LogFileOn()) 
    { 
      *GetLogFile() << StartTableRow <<
                            TableData(pStem)<<
                        EndTableRow;
    }
    if( analyzingSuffixes )
    {
      if( pStem->GetNumberOfSuffixes() < 1 ) continue;
    }
    else
    {
      if( pStem->GetNumberOfPrefixes() < 1 ) continue;
    }
    pWord = *m_pWords ^= pStem->GetKey();
    if (pWord)
    {
      if( analyzingSuffixes )
      {
        pStem->AddNULLSuffix();
        pNullSuffix->IncrementUseCount();
        pNullSuffix->IncrementCorpusCount( pWord->GetCorpusCount() );
        pStem->IncrementWordCount(); // Nov 24 99 JG
        pNullSuffix->AddStem( pStem );
      }
      else
      {
        pStem->AddNULLPrefix();
        pNullPrefix->IncrementUseCount();
        pNullPrefix->IncrementCorpusCount( pWord->GetCorpusCount() );
        pStem->IncrementWordCount();
        pNullPrefix->AddStem( pStem );
      }
      
      pStem->IncrementCorpusCount( pWord->GetCorpusCount() );
    }
    pStem->GetSuffixList()->Alphabetize(); // added oct 2008
    if (LogFileOn())  
    { 
        *GetLogFile() <<	StartTableRow <<
        						TableData(pStem);
        if (pStem->GetSuffixSignature())
        {
            *GetLogFile() << TableData(pStem->GetSuffixSignature()) <<
            EndTableRow;
        }
    }
    } // end of stem loop  

  if (LogFileOn())   { *GetLogFile() << EndTable;}
    delete OldStems; 
    FindAllSignatures();
}

//      Find All Signatures (from each Stem signatures)

/*  This scans the Stems, forming entries in This
 *  for each Class signature (the concatenation of
 *  suffixes taken by a stem
 *  It also makes a CPtrList for each signature
 *  It also makes a pointer to the Sig for each Stem. <<<<
 */
void CMiniLexicon::FindAllSignatures()
{
	LinguisticaMainWindow& doc = *GetDocument();

	const int MinimumSignatureLength = m_pLexicon->GetIntParameter(
			"Main\\MinimumSignatureLength", 1);
	const bool analyzingSuffixes = !is_initial(m_AffixLocation);

	doc.setStatusBar2("Find all signatures.");

	std::auto_ptr<CSignatureCollection> OldSignatures(m_pSignatures);
	m_pSignatures = analyzingSuffixes ?
		new CSignatureCollection(this, m_pSuffixes, m_AffixLocation) :
		new CSignatureCollection(this, m_pPrefixes, m_AffixLocation);

	// For each stem: generate signature from prefix/suffix list
	doc.BeginCountDown();
	const int num_stems = m_pStems->GetCount();
	for (int i = num_stems - 1; i >= 0 ; --i) {
		CStem& stem = *m_pStems->GetAt(i);

		doc.CountDownOnStatusBar(num_stems-1 - i, num_stems-1);

		CParse& affixes = analyzingSuffixes ?
				*stem.GetSuffixList() :
				*stem.GetPrefixList();

                QList<CSuffix*> suffixes;	// used if analyzingSu ffixes
                QList<CPrefix*> prefixes;	// used if !analyzingPrefixes
                // Look up prefixes/suffixes for the new signature’s
		// prefix/suffix pointer list
		for (int j = 1; j <= affixes.Size(); ++j) {
			CStringSurrogate affix_text = affixes.GetPiece(j);

                        analyzingSuffixes ? suffixes.append(*m_pSuffixes ^= affix_text):
                                            prefixes.append(*m_pPrefixes ^= affix_text);
		}
//---------------------------------------------------------------------------------//
// New non-Qt form:
                std::list<CSuffix*>  suffixesSTL;       // used if analyzingSuffixes April 2012 JG I had to add "std::"  here
                std::list<CPrefix*>  prefixesSTL;       // used if analyzingSuffixes

                for (int j = 1; j <= affixes.Size(); ++j) {
                        CStringSurrogate affix_text = affixes.GetPiece(j);

                        analyzingSuffixes ? suffixesSTL.push_back(*m_pSuffixes ^= affix_text): //April 2012 JG Was " append", I change dto 
                                            prefixesSTL.push_back(*m_pPrefixes ^= affix_text);
                }


//---------------------------------------------------------------------------------//
		// If not enough affixes, clear this stem’s signature.
		// Otherwise, record the new signature.
		CSignature* new_sig;
		if (affixes.Size() < MinimumSignatureLength) new_sig = 0;
		else new_sig = *m_pSignatures << &affixes;
		if (analyzingSuffixes) {
			if (new_sig != 0)
				new_sig->AttachToSuffixSig(&stem);
			stem.SetSuffixSignature(new_sig);
			foreach (CStem* word, *stem.GetWordPtrList())
				word->SetSuffixSignature(new_sig);
		} else {
			if (new_sig != 0)
				new_sig->AttachToPrefixSig(&stem);
			stem.SetPrefixSignature(new_sig);
			foreach (CStem* word, *stem.GetWordPtrList())
				word->SetPrefixSignature(new_sig);
		}

		// Record signature origin.
		if (new_sig != 0) {
			if (CSignature* old_sig = *OldSignatures ^= new_sig)
				new_sig->SetRemark(old_sig->GetRemark());
			else
				new_sig->SetRemark(
					QString("From known stem and %1")
					.arg(analyzingSuffixes ?
						"suffix" : "prefix"));
		}

		// Record prefix/suffix list.
		if (new_sig != 0) {
			if (analyzingSuffixes)
				*new_sig->GetSuffixPtrList() = suffixes;
			else
				*new_sig->GetPrefixPtrList() = prefixes;
		}

		// new_sig->IncrementCorpusCount(stem.GetCorpusCount());
	}

//	if (analyzingSuffixes)
//		m_pSuffixes->CalculatePointersToMySuffixes(eMDL_STYLE);

	doc.setStatusBar2("");
}


//////////////////////////////////////////////////////
//    From Stems Find Suffixes  Modified JG Oct 18 2003
//////////////////////////////////////////////////////
void CMiniLexicon::FromStemsFindAffixes()
{
  CStem*        		pStem;
  CAffix*      			pAffix, * qAffix;
  CStem*        		pWord;
  CSignature*   		pSig;
  int           		w = 0, StemLength, s;

  CStringSurrogate  ssStem, ssAffix, ssWord, ssTemp;
  CSuffixCollection	TempSuffixes;    // Was member variable m_TempAffixes
  CPrefixCollection	TempPrefixes;    // Was member variable m_TempAffixes
  CParse        		Word;

  const double  RobustnessThreshold         = (double)m_pLexicon->GetIntParameter( "FromStemsFindSuffixes\\RobustnessThreshold", 10 );
  const int     MinimumNumberOfOccurrences  = m_pLexicon->GetIntParameter( "FromStemsFindSuffixes\\MinimumNumberOfOccurrences", 3 );
  const int     MinimumStemLength           = m_pLexicon->GetIntParameter( "Main\\MinimumStemLength", 3 );
  bool          analyzingSuffixes = TRUE;
  
  if( m_AffixLocation == STEM_INITIAL || m_AffixLocation == WORD_INITIAL ) analyzingSuffixes = FALSE;
	
  std::auto_ptr<CSuffixCollection> TempSuffixesFinal;
  std::auto_ptr<CPrefixCollection> TempPrefixesFinal;
  if( analyzingSuffixes )
  {
	TempSuffixesFinal = std::auto_ptr<CSuffixCollection>(
			new CSuffixCollection( this ));
  }
  else
  {
	TempPrefixesFinal = std::auto_ptr<CPrefixCollection>(
			new CPrefixCollection( this ));
  }
	
  if( m_pStems->GetCount() == 0 ) return;

  m_pStems->Sort(KEY);
  m_pWords->Sort(KEY);

  m_pSignatures->CheckRobustness();  // TODO: check this for prefix compatibility

  if( analyzingSuffixes ) GetDocument()->setStatusBar1  ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": From stems, find suffixes" );
  else  GetDocument()->setStatusBar1  ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": From stems, find prefixes" );
	
  GetDocument()->BeginCountDown();

  if (LogFileOn() ) 
  {
    *GetLogFile() << SmallTitle("Phase: From known stems, find new affixes") << StartTable <<
    		StartTableRow <<
    			MakeTableHeader ("Stems") <<
    			MakeTableHeader("Robustness") <<
    			MakeTableHeader ("Affix")<<
    		EndTableRow;
                 
        
  }

  for ( s = 0; s < (int)m_pStems->GetCount(); s++)
  {
    pStem = m_pStems->GetAtSort(s);
    ssStem = pStem->GetKey();
      if (LogFileOn() ) 
      {
        *GetLogFile() << StartTableRow <<
        					TableData(ssStem); 
      }


   
    // ----------------------------------------------------------------------------
    StemLength = ssStem.GetLength();
    if ( (int) StemLength < MinimumStemLength ) continue;

    // ----------------------------------------------------------------------------
    /*  Here is where to test to see if the stem's signature is really robust */
    if( analyzingSuffixes ) pSig = pStem->GetSuffixSignature();
		else pSig = pStem->GetPrefixSignature();
      if (LogFileOn() ) 
      {
        *GetLogFile() << TableData( pSig->GetRobustness()) ; ; 
      }
		

    if ( pSig->GetRobustness() < RobustnessThreshold ) continue;
		
    // ----------------------------------------------------------------------------
    // New formulation:
	CParse StemContinuations;
	if (analyzingSuffixes) {
		m_pWords->GetTrie()->CreateSuffixSignatures(
			pStem->GetKey(), &StemContinuations);
	} else {
		 ssTemp = pStem->GetKey();
		 ssTemp.SetBackwards( TRUE );
		 m_pWords->GetReverseTrie()->CreateSuffixSignatures( &ssTemp, &StemContinuations );
		 ssTemp.SetBackwards( FALSE );
	}
		
    for (int i = 1; i < (int) StemContinuations.Size(); i++)
    {
      ssAffix  = StemContinuations.GetPiece(i);
	  if( analyzingSuffixes )
      {
		 Word   = ssStem + ssAffix;
      	 pWord  = *m_pWords ^= Word;
      	 if ( m_pWords->GetAtSort(w)->GetSuffixLoc() > 0 )   
                { continue;    }
      	 if ( m_pWords->GetAtSort(w)->GetStem2Loc() > 0 )  
                { w++; continue;} // or use WordType
      	 if ( *m_pSuffixes ^= ssAffix )          
            { continue;    }
      	 pAffix  = TempSuffixes << ssAffix;
         if ( LogFileOn() ) 
              { 
	            *GetLogFile() << StartTableRow <<
	            					TableData()<<
	            					TableData()<<
	            					TableData(ssAffix)<<
                                    EndTableRow;
              }   
      }
    else
      {
		 ssAffix.SetBackwards( TRUE );
		 Word = ssAffix + ssStem;
      	 pWord = *m_pWords ^= Word;
      	 if ( m_pWords->GetAtSort(w)->GetPrefixLoc() > 0 ) 
             continue;
      	 if ( m_pWords->GetAtSort(w)->GetStem2Loc() > 0 )  
            { w++; continue;} // or use WordType
      	 if ( *m_pPrefixes ^= ssAffix )          
            { continue;    }
      	 pAffix = TempPrefixes << ssAffix;
		 ssAffix.SetBackwards( FALSE );
      }
    }
  }
  if ( LogFileOn() ) 
 {
   *GetLogFile() << EndTable;
 }
  ///////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////

  if( analyzingSuffixes )
  {
    if ( LogFileOn() ) 
    { 
       *GetLogFile() << 
       		SmallTitle("Testing proposed affixes") << 
       		StartTable <<
	       		StartTableRow <<
	       			MakeTableHeader ("Affix") <<
	       			MakeTableHeader("Count") <<
	       		EndTableRow; 
    } 
  	for ( s = 0; s < (int)TempSuffixes.GetCount(); s++)
  	{
       pAffix = TempSuffixes.GetAt(s);
       if (LogFileOn() ) { *GetLogFile() << 
				StartTableRow <<
					TableData(pAffix) <<
					TableData(pAffix->GetUseCount()) <<
				EndTableRow; }
       if ( pAffix->GetUseCount() >= MinimumNumberOfOccurrences )
       {
      	  qAffix = *TempSuffixesFinal << pAffix;

      	  if ( LogFileOn() && qAffix )
          { *GetLogFile() << endl << "Yes " + pAffix->GetKey().Display(); }
    	  else if ( LogFileOn())
    	  { *GetLogFile() << endl << "No " + pAffix->GetKey().Display(); }
       }
  	}
       if ( LogFileOn() ) 
    { 
       *GetLogFile() << "</table>";
    } 

  }
  else
  {
  	for ( s = 0; s < (int)TempPrefixes.GetCount(); s++)
  	{
    	pAffix = TempPrefixes.GetAt(s);

    	if ( pAffix->GetUseCount() >= MinimumNumberOfOccurrences )
    	{
      	   qAffix = *TempPrefixesFinal << pAffix->GetKey();

      	    if ( LogFileOn() && qAffix)
      	    { *GetLogFile() << endl << "Yes " + pAffix->GetKey().Display(); }
    	    }
    	    else if ( LogFileOn())
    	    { *GetLogFile() << endl << "No " + pAffix->GetKey().Display(); }
  	}
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////

  // Now we'll look to see how often these acceptable suffixes are
  // used on real stems
   if ( LogFileOn())
  { *GetLogFile() << SmallerTitle("How acceptable are these suffixes?") <<
  		StartTable << 
  			StartTableRow <<
  				MakeTableHeader ("Stems") << 
  				MakeTableHeader( "Direction") << 
  				MakeTableHeader ("Word") << 
  			EndTableRow; }
 
  //GetDocument()->CountDownOnStatusBar ( -1 );	
	if( analyzingSuffixes )
	{
  	w=0;
  	for ( s = 0; s < (int)m_pStems->GetCount(); s++)
  	{
    	pStem = m_pStems->GetAtSort(s);
    	ssStem = pStem->GetKey();

    	StemLength = ssStem.GetLength();

    	if ( (int)StemLength < MinimumStemLength ) continue;

      	if ( LogFileOn())
        { *GetLogFile() << StartTableRow <<
                            TableData(ssStem) <<
                        EndTableRow;
        }

    	/* make sure the Words-ptr is above Stem in the Word list  */
    	
        /*  Going up...                  */
    	while ( w > 0 && 
                w < (int)m_pWords->GetCount() && 
                m_pWords->GetAtSort(w)->GetKey().Display() >= ssStem.Display() )
    	{ w--; }

    	/* bring the Words-ptr down to Stem    */
    	while ( w < (int)(m_pWords->GetCount() - 1) && 
                m_pWords->GetAtSort(w)->GetKey().Display() < ssStem.Display()  )
    	{ w++;  }

        
        ///////-------------------------------------------------/////////
        
        ///////-------------------------------------------------/////////


        //      Considering all words beginning with ssStem             //
		while ( w < (int)m_pWords->GetCount() && 
                m_pWords->GetAtSort(w)->GetKey().Left ( StemLength ) == ssStem  )
    	
        {
            if ( LogFileOn())
       	    { 
			    *GetLogFile() << StartTableRow <<
			    					TableData() <<
			    					TableData (m_pWords->GetAtSort(w)->GetKey()) ;
       	    }
 
            if ( m_pWords->GetAtSort(w)->GetSuffixLoc() > 0 ) 
            { 
                w++; 
                if (LogFileOn()){ *GetLogFile() << TableData(" already has suffix ") << 
                							EndTableRow;}
                continue; 
            } //the word is already analyzed
      	    
            if ( m_pWords->GetAtSort(w)->GetStem2Loc()  > 0 ) 
            { 
                    w++; 
                    if (LogFileOn()){ *GetLogFile() << TableData(" is a compound") <<
                    								EndTableRow;}
                    continue; 
            }  
      	    
            ssWord  = m_pWords->GetAtSort(w)->GetKey();
      	    ssAffix = ssWord.Right ( ssWord.GetLength() - StemLength );

            if ( LogFileOn())
            { 
                *GetLogFile() <<StartTableRow <<
				 TableData( "suffix (a)") <<
				 TableData( ssAffix ) <<
				EndTableRow;
            }
            if ( (pAffix = (*TempSuffixesFinal ^= ssAffix)) )
      	    {
        	 	if ( LogFileOn())
                { *GetLogFile() << 	TableData( "Already exists suffix") <<
						TableData(ssAffix) <<
					EndTableRow;
                }
                pWord = m_pWords->GetAtSort(w);
        	pWord->CutRightBeforeHere ( StemLength );
        	pWord->AppendToConfidence ( "somewhat uncertain." );
        	pWord->SetStemLoc(1);
        	pWord->SetSuffixLoc(2);
        	pAffix->IncrementUseCount();
        	if ( LogFileOn())
        	{ 
		    *GetLogFile() << endl << "Cut : " << pWord->Display();
        	}
		m_pLexicon->UpdateWord( pWord );
      	    }
            else
            {
                if ( LogFileOn())
                { *GetLogFile() <<  TableData("Suffix not found") << EndTableRow ;
                }
            }
            
            w++;
            
            
    	}
    } // end of loop through stems collection
    if ( LogFileOn())
    { *GetLogFile() << EndTable;}  
     
	
  	QString Remark ("From stems find suffixes");
  	CStringSurrogate ssRemark ( Remark);
  	
    
   RebuildAffixesStemsAndSignaturesFromWordSplits( ssRemark );
  	
   GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": End -- from stems, find suffixes" );

 
   } // end of suffixes
	else  // Prefixes!
 {
  	w=0;
	m_pWords->Sort( REVERSE_KEY );
		
  	for ( s = 0; s < (int)m_pStems->GetCount(); s++)
  	{
    		pStem = m_pStems->GetAtSort(s);
    		ssStem = pStem->GetKey();
		StemLength = ssStem.GetLength();

    	if ( (int)StemLength < MinimumStemLength ) continue;
			
    	/* make sure the Words-ptr is above Stem in the Word list  */
    	/* This is rarely executed                  */
			ssStem.SetBackwards( TRUE );
    	while ( w > 0 && w < (int)m_pWords->GetCount() )
    	{ 
		ssWord = m_pWords->GetAtSort(w)->GetKey();
		ssWord.SetBackwards( TRUE );
		if( ssWord.Display() >= ssStem.Display() ) break;
		w--; 
	}

    	/* bring the Words-ptr down to Stem    */
    	while ( w < (int)(m_pWords->GetCount() - 1) )
	    {
		ssWord = m_pWords->GetAtSort(w)->GetKey();
		ssWord.SetBackwards( TRUE );
		if( ssWord.Display() < ssStem.Display() ) break;
    		    w++; 
	    }
			
			ssWord.SetBackwards( FALSE );
			ssStem.SetBackwards( FALSE );

	while ( w < (int)m_pWords->GetCount() && m_pWords->GetAtSort(w)->GetKey().Right ( StemLength ) == ssStem.Display() )
    	    {
      	        if ( m_pWords->GetAtSort(w)->GetPrefixLoc() > 0 ) { w++; continue; }
      	        if ( m_pWords->GetAtSort(w)->GetStem2Loc() > 0 )  { w++; continue; } // or use WordType
      	        ssWord = m_pWords->GetAtSort(w)->GetKey();

      	        ssAffix = ssWord.Left ( ssWord.GetLength() - StemLength );
      	        if ( (pAffix = (*TempPrefixesFinal ^= ssAffix)) )
      	        {
        	        pWord = m_pWords->GetAtSort(w);
        	        pWord->CutRightBeforeHere( ssWord.GetLength() - StemLength );
        	        pWord->AppendToConfidence( "somewhat uncertain." );
        	        pWord->SetStemLoc(2);
        	        pWord->SetPrefixLoc(1);
        	        pAffix->IncrementUseCount();
        	        if ( LogFileOn())
        	        {
				 *GetLogFile() << endl << "Cut : " << pWord->Display();
        	        }
			        m_pLexicon->UpdateWord( pWord );
      	        }
      	        w++;
    	    }
	}
	
  	QString Remark ("From stems find prefixes");
  	CStringSurrogate ssRemark ( Remark);
  	RebuildAffixesStemsAndSignaturesFromWordSplits( ssRemark );
  	GetDocument()->setStatusBar1 ( "Mini-Lexicon " + QString("%1").arg( m_Index+1 ) + ": End -- from stems, find prefixes" );
		
 } // end of prefixes --


	GetDocument()->setStatusBar2 ( QString () );

	QString mini_name( "Mini-Lexicon %1" );
	mini_name = mini_name.arg( GetIndex() + 1 );
	QString remark = "From stems: find affixes";
	GetDLHistory()->append( mini_name, remark, this );

}


void CMiniLexicon::ExtendKnownStemsToKnownAffixes()
{
	LinguisticaMainWindow& doc = *GetDocument();

	// We will be iterating over stems and words, so sort them.
	m_pStems->Sort(KEY);
	m_pWords->Sort(KEY);

	// Give the user some text to stare at
	doc.BeginCountDown();
	doc.setStatusBar1(
		QString("Mini-Lexicon %1: Extend known stems and suffixes")
		.arg(m_Index + 1));

	const bool analyzingSuffixes = !is_initial(m_AffixLocation);

	if (LogFileOn()) {
		*GetLogFile() <<
			LargeTitle("Phase: Extending analysis "
				"based on known stems and known affixes.") <<
			StartTable <<
			StartTableRow;
		if (analyzingSuffixes) {
			*GetLogFile() << MakeTableHeader("Stem") <<
				MakeTableHeader("Suffix");
		} else {
			*GetLogFile() << MakeTableHeader("Prefix") <<
				MakeTableHeader("Stem");
		}
		*GetLogFile() << EndTableRow;
	}

	// For each stem:
	const int TopCount = m_pStems->GetCount();
	doc.setStatusBar2("Going through the stems ");
	for (int t = 0; t < TopCount; ++t) {
		CStem& stem = *m_pStems->GetAtSort(t);

		doc.CountDownOnStatusBar(t, TopCount);

		CStringSurrogate affix_text = analyzingSuffixes ?
				stem.GetSuffixList()->GetPiece(1) :
				stem.GetPrefixList()->GetPiece(1);
		const int stem_length = stem.GetKeyLength();
		const CStringSurrogate stem_text = stem.GetKey();

		// Write "" instead of "NULL".
		affix_text.ConvertNULL();

		const CParse word = analyzingSuffixes ?
				stem_text + affix_text :
				affix_text + stem_text;

		int SortIndex = 0;
		CStem* found_word = *m_pWords ^= word;
		if (found_word != 0)
			SortIndex = found_word->GetSortIndex();

		// First word starting with (resp ending with) stem text
		int TopIndex = SortIndex;
		if (analyzingSuffixes) {
			while (TopIndex >= 1 &&
					m_pWords->GetAtSort(TopIndex - 1)
					->GetKey().Left(stem_length) == stem_text)
				--TopIndex;
		} else {
			while (TopIndex >= 1 &&
					m_pWords->GetAtSort(TopIndex - 1)
					->GetKey().Right(stem_length) == stem_text)
				--TopIndex;
		}

		// Last word starting with (resp ending with) stem text
		int BottomIndex = SortIndex;
		if (analyzingSuffixes) {
			while (BottomIndex+1 < m_pWords->GetCount() &&
					m_pWords->GetAtSort(BottomIndex+1)
					->GetKey().Left(stem_length) == stem_text)
				++BottomIndex;
		} else {
			while (BottomIndex+1 < m_pWords->GetCount() &&
					m_pWords->GetAtSort(BottomIndex+1)
					->GetKey().Right(stem_length) == stem_text)
				++BottomIndex;
		}

		// For each word starting with (resp ending with) stem text:
		for (int w = TopIndex; w <= BottomIndex; ++w) {
			CStem& word2 = *m_pWords->GetAtSort(w);

			// Ignore already analyzed words
			const enum eStemType word2_type = word2.GetWordType();
			const int affix_loc = analyzingSuffixes ?
					word2.GetSuffixLoc() :
					word2.GetPrefixLoc();
			if (affix_loc != 0 ||
					word2_type == BIWORD_COMPOUND ||
					word2_type == MULTIPLE_COMPOUND ||
					word2_type == POSSIBLE_COMPOUND)
				continue;

			// Investigate possible affix
			const CStringSurrogate word2_text = word2.GetKey();
			const int affixlen = word2_text.GetLength() - stem_length;
			const CStringSurrogate PossibleAffix =
					analyzingSuffixes ?
					word2_text.Right(affixlen) :
					word2_text.Left(affixlen);
			CAffix* found_affix;
                        analyzingSuffixes ?
                                found_affix = *m_pSuffixes ^= PossibleAffix:
                                found_affix = *m_pPrefixes ^= PossibleAffix;
                        if (found_affix == 0)
				continue;

			// Affix present.  Rewrite word2 as stem + affix.
			// (Do not update counts yet.)
			if (analyzingSuffixes) {
				word2.CutRightBeforeHere(stem_length);
				word2.SetStemLoc(1);
				word2.SetSuffixLoc(2);
				stem.AddSuffix(static_cast<CSuffix*>(found_affix));
				found_affix->AddStem(&stem);
			} else {
				word2.CutRightBeforeHere(affixlen);
				word2.SetStemLoc(2);
				word2.SetPrefixLoc(1);
				stem.AddPrefix(static_cast<CPrefix*>(found_affix));
				found_affix->AddStem(&stem);
			}

			if (LogFileOn()) {
				*GetLogFile() << endl << StartTableRow;
				if (analyzingSuffixes)
					*GetLogFile() <<
						TableData(stem) <<
						TableData(*found_affix);
				else
					*GetLogFile() <<
						TableData(*found_affix) <<
						TableData(stem);
				*GetLogFile() << EndTableRow;
			}
			m_pLexicon->UpdateWord(&word2);
		}
	}

        if (LogFileOn()) *GetLogFile() << EndTable;

	//////////////////////////////////////////////////////////////////////////////
	//	Redo Signatures
	QString Remark("From known stems and suffixes");
	CStringSurrogate ssRemark(Remark);

	doc.setStatusBar2 ("Going through the words." );

	std::auto_ptr<CSignatureCollection> OldSignatures(m_pSignatures);
	m_pSignatures = analyzingSuffixes ?
			new CSignatureCollection(this, m_pSuffixes, m_AffixLocation) :
			new CSignatureCollection(this, m_pPrefixes, m_AffixLocation);

	// for each word: update counts to reflect new parse.
	doc.BeginCountDown();
	for (int i = 0; i < m_pWords->GetCount(); ++i) {
		CStem& word = *m_pWords->GetAt(i);
		doc.CountDownOnStatusBar(i, m_pWords->GetCount());

		// skip compound words
		if (!word.MayBeParsed()) continue;

		// skip unanalyzed words
		if (word.Size() < 2) continue;

		// find stem and affix
		CStem* stem;
		// XXX. drop these initializations once gcc can figure
		// out they are initialized later.
		CPrefix* prefix = 0;	// used if !analyzingSuffixes
		CSuffix* suffix = 0;	// used if analyzingSuffixes
		if (analyzingSuffixes) {
			stem = *m_pStems << word.GetPiece(1);
			suffix = *m_pSuffixes << word.GetPiece(2).Display();
		} else {
			stem = *m_pStems << word.GetPiece(2);
			prefix = *m_pPrefixes << word.GetPiece(1).Display();
		}

		// update counts
		if (analyzingSuffixes)
			word.AttachWordStemAndSuffix(stem, suffix);
		else
			word.AttachWordStemAndPrefix(stem, prefix);
		m_pLexicon->UpdateWord(&word);

		if (analyzingSuffixes) {
			word.SetStemLoc(1);
			word.SetSuffixLoc(2);
			word.SetSuffixPtr(suffix);
		} else {
			word.SetStemLoc(2);
			word.SetPrefixLoc(1);
			word.SetPrefixPtr(prefix);
		}
		word.DoNotParse();
		m_pLexicon->UpdateWord(&word);

		CAffix* affix = analyzingSuffixes ?
			implicit_cast<CAffix*>(suffix) :
			implicit_cast<CAffix*>(prefix);
		stem->IncrementCorpusCount(word.GetCorpusCount() - 1);
		affix->IncrementCorpusCount(word.GetCorpusCount() - 1);
		stem->IncrementWordCount();
	}

	// for each stem:
	for (int i = 0; i < m_pStems->GetCount(); ++i) {
		CStem& stem = *m_pStems->GetAt(i);

		// if appears as word, record that
		if (CStem* stem_as_word = *m_pWords ^= stem.GetKey()) {
			if (analyzingSuffixes) {
				CSuffix* null_suffix = *m_pSuffixes << TheStringNULL;
				Q_ASSERT(null_suffix != 0);

				stem.AddSuffix(null_suffix);
				null_suffix->AddStem(&stem);
			} else {
				CPrefix* null_prefix = *m_pPrefixes << TheStringNULL;
				Q_ASSERT(null_prefix != 0);

				stem.AddPrefix(null_prefix);
				null_prefix->AddStem(&stem);
			}
			stem.AddWord(stem_as_word);
		}

		// create signature
		CSignature* new_sig;
		if (analyzingSuffixes) {
			stem.GetSuffixList()->Alphabetize();
			new_sig = *m_pSignatures << stem.GetSuffixList();
			new_sig->AttachToSuffixSig(&stem);
		} else {
			stem.GetPrefixList()->Alphabetize();
			new_sig = *m_pSignatures << stem.GetPrefixList();
			new_sig->AttachToPrefixSig(&stem);
		}

		// record new signature
		foreach (CStem* word, *stem.GetWordPtrList()) {
			if (analyzingSuffixes)
				word->SetSuffixSignature(new_sig);
			else
				word->SetPrefixSignature(new_sig);

			if (CSignature* old_sig = *OldSignatures ^= new_sig)
				new_sig->SetRemark(old_sig->GetRemark());
			else
				new_sig->SetRemark(QString("Known stems to suffixes"));
		}
	}

	doc.setStatusBar1(QString("Mini-Lexicon %1: "
			"End of using known stems and %2")
			.arg(m_Index + 1)
			.arg(analyzingSuffixes ? "suffixes" : "prefixes"));
	doc.EndCountDown();

	GetDLHistory()->append(
		QString("Mini-Lexicon %1").arg(m_Index + 1),
		QString("Known stems and affixes"),
		this);
}

/*
 * At the moment, this function decides too early whether to
 * allow a stem to be used. It ought to build up the TempSignatures,
 * and after all stems have been tried, decide which way to split
 * a stem is the best.
 */

/* Take a word W.
 *    Consider all splits for W such that its suffix is already in Suffixes.
 *      Put the stem in TempStems, and attach the suffix to the stem.
 *      Look at all words that start like that stem;
 *           Attach the suffixes found in those words to that stem.
 *      Done?
 *      Now, if there are more than 2 suffixes on that stem now,
 *           put the stem's signature in a TempSignature collection.
 *      Find cost = cost (Sig).
 *      If cost is negative, go ahead and make all those splits.
 *  End of loop.
 */
void CMiniLexicon::LooseFit()
{
	// Cost of a sig =
	//    Sum over all of its stems :
	//	  log ( CorpusSize / Stem-count )      ( cost    )
	//	  length ( stem ) * cost of a letter   ( savings )
	//
	//    Sum over all of its suffixes:
	//	  log ( CorpusSize / suffix-count )    ( cost    )
	//	  length ( suffix ) * cost of a letter ( savings )
	using std::auto_ptr;
	using std::vector;

	LinguisticaMainWindow& doc = *GetDocument();
	const bool analyzingSuffixes = !is_initial(m_AffixLocation);
	const int MinimumAffixLength = m_pLexicon->GetIntParameter(
			analyzingSuffixes ?
			"Main\\MinimumSuffixLength" :
			"Main\\MinimumPrefixLength", 2);
	const int MaximumAffixLength = m_pLexicon->GetIntParameter(
			analyzingSuffixes ?
			"Main\\MaximumSuffixLength" :
			"Main\\MaximumPrefixLength", 7);
	int MinimumStemLength = m_pLexicon->GetIntParameter(
			"Main\\MinimumStemLength", 3);
	if (MinimumStemLength < 1)
		// do not allow empty stems
		// XXX. notify user that value was ignored
		MinimumStemLength = 1;

	if (LogFileOn())
		*GetLogFile() << endl <<
			LargeTitle("Phase: Loose fit of known signatures")<<
			StartTable;

	auto_ptr<CSignatureCollection> proposed_sigs(analyzingSuffixes ?
		new CSignatureCollection(this, m_pSuffixes, m_AffixLocation) :
		new CSignatureCollection(this, m_pPrefixes, m_AffixLocation));
	auto_ptr<CSignatureCollection> existing_sigs(analyzingSuffixes ?
		new CSignatureCollection(this, m_pSuffixes, m_AffixLocation) :
		new CSignatureCollection(this, m_pPrefixes, m_AffixLocation));
	auto_ptr<CSignatureCollection> novel_sigs(analyzingSuffixes ?
		new CSignatureCollection(this, m_pSuffixes, m_AffixLocation) :
		new CSignatureCollection(this, m_pPrefixes, m_AffixLocation));

	if (m_pWords->GetCount() == 0)
		// Need to read corpus first.
		return;

	// We will  be iterating over words, so sort them.
	m_pWords->Sort(KEY);

	// Give the user something to look at.
	doc.BeginCountDown();
	doc.setStatusBar1(
		QString("Mini-Lexicon %1: Loose fit.").arg(m_Index+1));


	// For each word: look for known prefixes/suffixes and consider them.
	// Fill proposed_sigs with candidates.
	CStemCollection potential_stems;
	const int num_words = m_pWords->GetCount();
	for (int w = 0; w < num_words; ++w) {
		CStem& word = *m_pWords->GetAtSort(w);
		doc.CountDownOnStatusBar(w, num_words);

		if (word.Size() > 1)
			// already analyzed
			continue;

		if (word.GetKeyLength() < 2)
			// too small to analyze
			continue;

		CStringSurrogate word_text = word.GetKey();

		// For each textual prefix/suffix of word: if known, consider.
		for (int i = MaximumAffixLength; i >= MinimumAffixLength; --i) {
			Q_ASSERT(MinimumStemLength >= 1);
			if (word_text.GetLength() - i < MinimumStemLength)
				// corresponding stem is too short
				continue;

			CStringSurrogate affix_text = analyzingSuffixes ?
				word_text.Right(i) : word_text.Left(i);
			CAffix* affix = analyzingSuffixes ?
				implicit_cast<CAffix*>(*m_pSuffixes ^= affix_text) :
				implicit_cast<CAffix*>(*m_pPrefixes ^= affix_text);

			if (affix == 0)
				// suffix not known
				continue;

			Q_ASSERT(word_text.GetLength() > i);
			CStringSurrogate stem_text = analyzingSuffixes ?
				word_text.Left(word_text.GetLength()-i) :
				word_text.Right(word_text.GetLength()-i);

			if (*m_pStems ^= stem_text)
				// stem already known
				continue;

			if (potential_stems ^= stem_text)
				// stem already under consideration
				continue;

			if (LogFileOn())
				*GetLogFile() << StartTableRow <<
						TableData(stem_text);
			CStem* stem = potential_stems << stem_text;

			// build signature from remaining words
			CParse empirical_sig;
			if (analyzingSuffixes) {
				m_pWords->CreateSuffixSignatures(
						&stem_text, &empirical_sig);
			} else {
				if (!m_pWords->GetReverseTrie())
					m_pWords->CreateReverseTrie();

				// build list of reversed prefixes
				CParse backwards_sig;
				stem_text.SetBackwards();
				m_pWords->GetReverseTrie()->CreateSuffixSignatures(
						&stem_text, &backwards_sig);
				stem_text.SetBackwards(false);

				// reverse them to get actual prefixes
				for (int n = 1; n <= backwards_sig.Size(); ++n) {
					CStringSurrogate prefix =
						backwards_sig.GetPiece(n);

					prefix.SetBackwards();
					empirical_sig.Append(prefix);
					prefix.SetBackwards(false);
				}
			}

			// for each prefix/suffix that appears with stem:
			//  throw it out if it's obviously bad, but
			//  otherwise record it in *stem.
			for (int n = 1; n <= empirical_sig.Size(); ++n) {
				CStringSurrogate affix2 = empirical_sig.GetPiece(n);

				// word this affix was taken from
				CParse word2_text = analyzingSuffixes ?
						stem_text + affix2 :
						affix2 + stem_text;
				CStem* word2 = *m_pWords ^= word2_text;
				Q_ASSERT(word2 != 0);

				if (word2->Size() > 1)
					// previously analyzed
					continue;

				// If affix is of reasonable size or is
				// known from elsewhere, add it to stem's list.
				const int affix2_len = affix2.GetLength();
				const bool reasonable_size =
					affix2_len >= MinimumAffixLength ||
					affix2_len <= MaximumAffixLength;

				if (reasonable_size || (analyzingSuffixes ?
						(*m_pSuffixes ^= affix2) != 0:
						(*m_pPrefixes ^= affix2) != 0)) {
					if (analyzingSuffixes)
						stem->AddSuffix(affix2);
					else
						stem->AddPrefix(affix2);
				}
			}
			// special case: stem appears with null affix
			if (CStem* word2 = *m_pWords ^= stem_text) {
				if (word2->Size() > 1) {
					// previously analyzed
				} else {
					if (analyzingSuffixes)
						stem->AddNULLSuffix();
					else
						stem->AddNULLPrefix();
				}
			}

			// fetch recorded affixes
			CParse& affixes = analyzingSuffixes ?
				*stem->GetSuffixList() :
				*stem->GetPrefixList();

			// At least the affix that prompted this search
			// should be among them.
			Q_ASSERT(affixes.Contains(affix_text));
			Q_ASSERT(affixes.Size() > 0);

			// build new signature
			CSignature* new_sig = *proposed_sigs << &affixes;

			if (analyzingSuffixes)
				new_sig->AttachToSuffixSig(stem, false);
			else
				new_sig->AttachToPrefixSig(stem, false);
			new_sig->SetAffixLocation(m_AffixLocation);

			if (LogFileOn())
				*GetLogFile() <<
					TableData(new_sig->Display());
		} // for each textual prefix/suffix
			if( LogFileOn() ) *GetLogFile() << StartTableRow << EndTableRow;  // Blank line between stem-families
	} // for each word

	// Now we have, or might have, a set of candidate splittings,
	// so let's compare them.
	// If any of the corresponding signatures are already real,
	// then we take the stem corresponding to the sig with the
	// highest value for Robustness.
	// Otherwise we use the Cost function for signatures.

	if (LogFileOn())
		*GetLogFile() << SmallTitle("Proposed signatures") <<
			StartTable <<
			StartTableRow <<
				MakeTableHeader("Signature") <<
				MakeTableHeader("status")<<
			EndTableRow;

	// First find the set of existing signatures (won't be many).
	for (int i = 0; i < proposed_sigs->GetCount(); ++i) {
		CSignature* sig = (*proposed_sigs)[i];

		if (sig->Size() < 2 && sig->GetKeyLength() < 4) {
			// total length < 4!  Way too small.
			if (LogFileOn()) *GetLogFile() <<
				StartTableRow <<
					TableData("too small: ") <<
					TableData(sig->Display()) <<
				EndTableRow;
			continue;
		}

		// known signature?
		if (*m_pSignatures ^= sig) *existing_sigs << sig;
		else *novel_sigs << sig;
	}
	if (LogFileOn()) *GetLogFile() << EndTable;

	{
		// Sort existing signatures by robustness
		const int size = existing_sigs->GetCount();

		if (LogFileOn()) *GetLogFile() << StartTable <<
				StartTableRow <<
					MakeTableHeader("Pre-existing signature") <<
					MakeTableHeader("Robustness")<<
				EndTableRow;

		// calculate each signature’s robustness
		vector<double> Robustness;
		Robustness.reserve(size);
		for (int i = 0; i < size; ++i) {
			CSignature* sig = (*existing_sigs)[i];

			Robustness.push_back(sig->GetRobustness());
			if (LogFileOn()) *GetLogFile() <<
					StartTableRow <<
						TableData(sig->Display()) <<
						TableData(Robustness[i]) <<
					EndTableRow;
		}

		if (LogFileOn()) *GetLogFile() 				<<
 				StartTableRow 				<<
					MakeTableHeader("Signature") 	<<
					MakeTableHeader("Stem") 	<<
				EndTableRow;

		// For each existing signature (sorted by robustness):
		// analyze (cut) unanalyzed words according to this signature.
		vector<int> shuffle(size);
		SortVector(&shuffle[0], &Robustness[0], size);
		for (int j = 0; j < size; ++j) {
			CSignature* sig = (*existing_sigs)[shuffle[j]];

			if (LogFileOn()) *GetLogFile() 			<<
				StartTableRow 				<<
					TableData(sig->Display()) 	<<
				EndTableRow;

			// Analyze (cut) unanalyzed words according to signature.
			foreach (CStem* stem, *sig->GetStemPtrList()) {
				if ( LogFileOn()) *GetLogFile() <<
 					StartTableRow 		<<
						TableData() 	<<
						TableData(stem->GetKey()) <<
					EndTableRow;

				// For each affix in signature:
				for (int k = 1; k <= sig->Size(); ++k) {
					CStringSurrogate affix = sig->GetPiece(k);

					affix.SetBackwards(false);
					if (affix.IsNULL())
						// stem + NULL affix needs no cut
						continue;

					// get correspond word
					CParse word_text = analyzingSuffixes ?
						stem->GetKey() + affix :
						affix + stem->GetKey();
					CStem* word = *m_pWords ^= word_text;
					Q_ASSERT(word != 0);

					if (word->Size() > 1 )
						// already analyzed
						continue;

					if (LogFileOn()) *GetLogFile() <<
						StartTableRow <<
							TableData() <<
							TableData() << 
							TableData(word->GetKey()) <<
						EndTableRow;

					// analyze word
					const int cut_point = analyzingSuffixes ?
						stem->GetKeyLength() :
						word->GetKeyLength() -
							stem->GetKeyLength();
					word->CutRightBeforeHere(cut_point);
					if (analyzingSuffixes) {
						word->SetStemLoc(1);
						word->SetSuffixLoc(2);
					} else {
						word->SetStemLoc(2);
						word->SetPrefixLoc(1);
					}
					m_pLexicon->UpdateWord(word);
				}
			}
		}
		if (LogFileOn()) *GetLogFile() << EndTable;
	}

	{
		// Consider novel signatures.
		const int size = novel_sigs->GetCount();

		if (LogFileOn()) *GetLogFile() 			<<
			SmallTitle("Novel signatures: ")	<<
			StartTable;

		// for each signature: calculate cost function
		vector<double> Cost;
		Cost.reserve(size);
		for (int i = 0; i < size; ++i)
			Cost.push_back((*novel_sigs)[i]->FindCost(this));

		// for each novel signature, in least-cost-first order:
		// Analyze (cut) unanalyzed words according to this signature.
		// Stop when the cost becomes positive.
		vector<int> shuffle(size);
		SortVector(&shuffle[0], &Cost[0], size);
		for (int j = size-1; j >= 0 && Cost[shuffle[j]] < 0; --j) {
			CSignature* sig = (*novel_sigs)[shuffle[j]];
			if (LogFileOn()) *GetLogFile() 			<< 
					StartTableRow 					<<
 						TableData (sig->Display()) 	<< 
						TableData ( Cost[shuffle[j]] );
			foreach (CStem* stem, *sig->GetStemPtrList()) {
				for (int k=1; k <= sig->Size(); ++k) {
					CStringSurrogate affix = sig->GetPiece(k);
					if (affix.IsNULL())
						// no cut for NULL suffix
						continue;

					// Get corresponding word.
					CParse word_text = analyzingSuffixes ?
						stem->GetKey() + affix :
						affix + stem->GetKey();
					CStem* word = *m_pWords ^= word_text;
					Q_ASSERT(word != 0);

					if (word->Size() > 1)
						// already analyzed
						continue;
					const int cut_point = analyzingSuffixes ?
						stem->GetKeyLength() :
						word->GetKeyLength() -
							stem->GetKeyLength();
					word->CutRightBeforeHere(cut_point);
					if (analyzingSuffixes) {
						word->SetStemLoc(1);
						word->SetSuffixLoc(2);
					} else {
						word->SetStemLoc(2);
						word->SetPrefixLoc(1);
					}
					m_pLexicon->UpdateWord(word);

					if( LogFileOn() ) *GetLogFile() << TableData( word );
				}
				if( LogFileOn() ) *GetLogFile() << EndTableRow;
			}
		}
		// XXX. report cost of first rejected signature to log
	}

	// Rebuild m_pSignatures, m_pWords; record new stems and affixes

	auto_ptr<CSignatureCollection> old_sigs(m_pSignatures);
	m_pSignatures = analyzingSuffixes ?
		new CSignatureCollection(this, m_pSuffixes, m_AffixLocation) :
		new CSignatureCollection(this, m_pPrefixes, m_AffixLocation);

	// for each word: record its new analysis
	doc.BeginCountDown();
	Q_ASSERT(num_words == m_pWords->GetCount());
	for (int i = 0; i < num_words; ++i) {
		CStem& word = *m_pWords->GetAt(i);

		doc.CountDownOnStatusBar(i, num_words);

		if (!word.MayBeParsed())
			// compound word
			continue;
		else if (word.Size() < 2)
			// not analyzed
			continue;
		else
			// analyzed as stem + affix
			Q_ASSERT(analyzingSuffixes ?
					word.GetSuffixLoc() != 0 :
					word.GetPrefixLoc() != 0);

		word.ClearPointers();
		CStem* stem = *m_pStems << word.GetPiece(analyzingSuffixes ? 1 : 2);
		if (analyzingSuffixes) {
			CSuffix* affix = *m_pSuffixes << word.GetPiece(2).Display();
			word.AttachWordStemAndSuffix(stem, affix);
		} else {
			CPrefix* affix = *m_pPrefixes << word.GetPiece(1).Display();
			word.AttachWordStemAndPrefix(stem, affix);
		}
		word.SetStemLoc(analyzingSuffixes ? 1 : 2);
		if (analyzingSuffixes) word.SetSuffixLoc(2);
		else word.SetPrefixLoc(1);
		m_pLexicon->UpdateWord(&word);

		word.DoNotParse();
	}

	// for each stem: record corresponding signature
	doc.BeginCountDown();
	const int num_stems = m_pStems->GetCount();
	for (int i = 0; i < num_stems; ++i) {
		CStem& stem = *m_pStems->GetAt(i);

		doc.CountDownOnStatusBar(i, num_stems);

		// check for appearance with null affix
		if (*m_pWords ^= stem.GetKey()) {
			CAffix* affix;
			if (analyzingSuffixes) {
				CSuffix* suffix = *m_pSuffixes << TheStringNULL;
				stem.AddSuffix(suffix);
				affix = suffix;
			} else {
				CPrefix* prefix = *m_pPrefixes << TheStringNULL;
				stem.AddPrefix(prefix);
				affix = prefix;
			}
			affix->AddStem(&stem);

			// TODO: this should be matched to null suffix counts
			affix->IncrementUseCount();
		}

		// build new signature.
		CParse* const affix_list = analyzingSuffixes ?
				stem.GetSuffixList() : stem.GetPrefixList();
		CSignature* new_sig = *m_pSignatures << affix_list;
		if (analyzingSuffixes)
			new_sig->AttachToSuffixSig(&stem, false);
		else
			new_sig->AttachToPrefixSig(&stem, false);


		foreach (CStem* word, *new_sig->GetWordPtrList()) {
			if (analyzingSuffixes)
				word->SetSuffixSignature(new_sig);
			else
				word->SetPrefixSignature(new_sig);
		}

		// record signature origin.
		if (CSignature* old_sig = *old_sigs ^= new_sig)
			new_sig->SetRemark(old_sig->GetRemark());
		else
			new_sig->SetRemark(QString("Loose fit"));
	}

	doc.setStatusBar1(QString("Mini-Lexicon %1: End of loose fit." )
			.arg(m_Index+1));
	GetDLHistory()->append(
			QString("Mini-Lexicon %1").arg(m_Index+1),
			QString("Loose Fit"),
			this);
}

int CMiniLexicon::GetNumberOfStems()
{
	return m_pStems->GetCount();
}
