// Updating the main window’s tree view
// Copyright © 2009 The University of Chicago
#include "linguisticamainwindow.h"

#include "MiniLexicon.h"
#include "Lexicon.h"
#include "TreeViewItem.h"
#include "LPreferences.h"
#include "StateEmitHMM.h"
#include "CorpusWord.h"
#include "DLHistory.h"
#include "Suffix.h"
#include "Prefix.h"
#include "CorpusWordCollection.h"
#include "SignatureCollection.h"
#include "TemplateCollection.h"
#include "CompoundCollection.h"
#include "LinkerCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "BiphoneCollection.h"
#include "PhoneCollection.h"
#include "StemCollection.h"
#include "WordCollection.h"
#include "POSCollection.h"
#include "AffixLocation.h"

/** \page page1 How to make a variable be displayed in the Tree View (left window)

  Most of the functions here are sensitive to what information has been computed in CLexicon and
  the MiniLexicons. A few are triggered under any conditions, but most are triggered only
  if certain items have already been computed. 


  \section sec The main screen
  

*/

void LinguisticaMainWindow::updateTreeViewSlot()
{
  // Adapted from MFC version: CMyTree::UpdateUpperTree, CMyTree::UpdateStatistics

  int     count,    // used for various counts
          index;    // mini-lexicon index
  index = 0;
  count = 0;

//  bool      add = TRUE;

  CStem* pWord;

  Q3ListViewItem  * MiscItem      = NULL,
		  * MiscItem1       = NULL,
          * LexiconItem     = NULL,
          * WordsReadItem   = NULL,
          * PrefixesItem    = NULL,
          * SuffixesItem    = NULL,
          * WordsItem       = NULL,
 		  * CompoundsItem   = NULL,
          * ComponentItem   = NULL,
		  *	STRINGEDITITEM  = NULL,
		  * CorpusWordsItem = NULL;
		  
 
  // Clear the tree
  m_treeView->clear();
  m_treeView->setFont( GetFontPreference( "Main" ) );
  m_treeView->hideColumn(1);

//**************************************************************************************
// A NOTE ON THE ORGANIZATION OF THIS FUNCTION:
// The items are inserted into the tree in reverse order respective to their group.  They
// are organized by depth here, i.e. what is connected to the root is the first group,
// then do the groups of items connected to this first group, etc.  The only items that
// get their own name are those that have children.  The rest use MiscItem
//**************************************************************************************


//======================================================================================//
  // START CONNECTED DIRECTLY TO m_treeView
//======================================================================================//


	count = GetNumberOfTokens();
	if( count >= 0 )
	{
		MiscItem = new CTreeViewItem( m_treeView,
									  "Tokens requested: " + IntToStringWithCommas( count ),
									  TOKENS_REQUESTED );
		MiscItem->setSelectable(false);
	}  

//======================================================================================//

	if( m_lexicon->GetWords() && m_lexicon->GetMiniCount() )
	{
		count = m_lexicon->GetTokenCount();
		if ( count >= 0 )
		{
			WordsReadItem = new CTreeViewItem( m_treeView,
											   "Tokens read: " + IntToStringWithCommas( count ) );
			WordsReadItem->setSelectable(false);
			WordsReadItem->setOpen(true);
		}

//======================================================================================//

		LexiconItem = new CTreeViewItem( m_treeView,
						 "Lexicon : click items to display them" );
		LexiconItem->setSelectable(false);
		LexiconItem->setOpen(true);
	}

//======================================================================================//

  if ( m_projectDirectory.length()  )
  {
    MiscItem = new CTreeViewItem( m_treeView, "Project directory: " + m_projectDirectory );
    MiscItem->setSelectable(false);
  }
  else
  {
    MiscItem = new CTreeViewItem( m_treeView, "No project directory." );
    MiscItem->setSelectable(false);
  }

//======================================================================================//

  if ( m_logging )
  {
    MiscItem = new CTreeViewItem( m_treeView, "Log file (now on) " + GetLogFileName() );
    MiscItem->setSelectable(false);
  }
  else
  {
    MiscItem = new CTreeViewItem( m_treeView, "Log file (now off) " + GetLogFileName() );
    MiscItem->setSelectable(false);
  }

//=================================================================================================
  // END CONNECTED DIRECTLY TO m_treeView
  // START CONNECTED TO LexiconItem
//=================================================================================================

	if ( LexiconItem && m_lexicon->GetHMM() )
	{		
		MiscItem = new CTreeViewItem( LexiconItem,
									   "HMM",
									   HMM_Document);
		double dl = m_lexicon->GetHMM()->GetLogProbability();
		MiscItem1 = new CTreeViewItem(MiscItem,"HMM description length: " + IntToStringWithCommas(int( dl) )
									   );		
		MiscItem1 = new CTreeViewItem(MiscItem,
									  "Iterations: " + IntToStringWithCommas( m_lexicon->GetHMM()->m_NumberOfIterations )
									   );		
		MiscItem1 = new CTreeViewItem(MiscItem,
									  "Number of states: " + IntToStringWithCommas( m_lexicon->GetHMM()->m_countOfStates )
									   );		
	}
	MiscItem->setOpen(true);

//======================================================================================//

  if( LexiconItem )
  {
	  if( m_lexicon->GetDLHistory()->count() > 0 )
	  {
		 MiscItem = new CTreeViewItem( LexiconItem,
									   "Description length history",
									   DESCRIPTION_LENGTH_HISTORY );
	  }
  }

//////////////////////////////
//// StringEdit Display

	if ((LexiconItem != NULL) && (m_Words_InitialTemplates != NULL))
	{
		if ( m_Words_InitialTemplates ->GetCount() > 0)
		{
			STRINGEDITITEM = new CTreeViewItem( LexiconItem,
										  "StringEditDistanceTemplates: " + IntToStringWithCommas( 2 ), 
										  STRINGEDITDISTANCE, -1);

			count = m_Words_Templates ->GetCount();
			if ( count != 0)
			{
				MiscItem = new CTreeViewItem( STRINGEDITITEM,
										  "StringEdit_Templates: " + IntToStringWithCommas( count ), 
										  WORKINGSTRINGEDITTEMPLATES, -1);

			}

			count = m_Words_InitialTemplates ->GetCount();
			MiscItem = new CTreeViewItem( STRINGEDITITEM,
										  "StringEdit_InitialTemplates: " + IntToStringWithCommas( count ), 
										  INITIALSTRINGEDITTEMPLATES, -1);
		}
	}

		count = 0;
		Q3DictIterator<PrefixSet> it5( *m_lexicon->GetAllPrefixes() );
		for( ; it5.current(); ++it5 )
		{
			count += it5.current()->count();
		}
		if( count > 0 )
		{
			PrefixesItem = new CTreeViewItem( LexiconItem,
											  "All Prefixes " + IntToStringWithCommas( count ),
											  ALL_PREFIXES );
			PrefixesItem->setOpen( TRUE );
		}    
//======================================================================================//
		count = 0;
		Q3DictIterator<SuffixSet> it4( *m_lexicon->GetAllSuffixes() );
		for( ; it4.current(); ++it4 )
		{
			count += it4.current()->count();
		}
		if( count > 0 )
		{
			SuffixesItem = new CTreeViewItem( LexiconItem,
											  "All Suffixes " + IntToStringWithCommas( count ),
											  ALL_SUFFIXES );
			SuffixesItem->setOpen( TRUE );
		}
//======================================================================================//
		count = 0;
		Q3DictIterator<StemSet> it1( *m_lexicon->GetAllStems() );
		for( ; it1.current(); ++it1 )
		{
			count += it1.current()->count();
		}
		if( count > 0 )
		{
			MiscItem = new CTreeViewItem( LexiconItem,
										  "All Stems " + IntToStringWithCommas( count ),
										  ALL_STEMS );
		}
 //======================================================================================//
		count = 0;
		Q3DictIterator<StemSet> it2( *m_lexicon->GetAllWords() );
		for( ; it2.current(); ++it2 )
		{
			count += it2.current()->count();
		}

		if( count > 0 )
		{
			WordsItem = new CTreeViewItem( LexiconItem,
										  "All Words " + IntToStringWithCommas( count ),
										  ALL_WORDS );
			WordsItem->setOpen( TRUE );
		}	
//======================================================================================//
	  if( m_lexicon->GetMiniCount() )
	  {
		for( index = m_lexicon->GetMiniSize() - 1; index >= 0; index-- )
		{
			if( m_lexicon->GetMiniLexicon( index ) )
				MiscItem = GetMiniLexiconSubTree( LexiconItem, index );
		}
	  }
//======================================================================================//
		count = m_lexicon->GetCompounds()->GetCount();
		if( count > 0 )
		{
			CompoundsItem = new CTreeViewItem( LexiconItem,
											   "Compounds " + IntToStringWithCommas( count ),
											   COMPOUNDS );
			CompoundsItem->setOpen( TRUE );
            int count2 = m_lexicon->GetCompounds()->GetComponents()->GetSize();
            ComponentItem = new CTreeViewItem( CompoundsItem, "Components "+ IntToStringWithCommas (count2),
                                                COMPOUND_COMPONENTS);
		}
//======================================================================================//

	  count = m_lexicon->GetWords()->GetCount();
	  if( count > 0 )
	  {
		CorpusWordsItem = new CTreeViewItem( LexiconItem,
											 "Corpus Words " + IntToStringWithCommas( count ),
											 CORPUS_WORDS );
		CorpusWordsItem->setOpen( TRUE );
	  }
//=================================================================================================
  // END CONNECTED TO LexiconItem
  // START CONNECTED TO CorpusWordsItem
//=================================================================================================

	count = 0;
	if( CorpusWordsItem )
	{

		CCorpusWord* pCorpusWord;
		CCorpusWordCollection* pWords = m_lexicon->GetWords();

		pWords->Sort( KEY );

		for( int i = 0; i < pWords->GetCount(); i++ )
		{
			pCorpusWord = pWords->GetAtSort(i);

			if( pCorpusWord->Size() > 1 )
			{
				count++;
			}
		}

		if( count > 0 )
		{
			MiscItem = new CTreeViewItem( CorpusWordsItem,
										  "Analyzed " + IntToStringWithCommas( count ),
										  ANALYZED_CORPUS_WORDS );
		}
	}
 
//=================================================================================================
  // END CONNECTED TO CorpusWordsItem
  // START CONNECTED TO WordsItem
//=================================================================================================

	count = 0;

	bool analyzed_exists;
	Q3DictIterator<StemSet> it3( *m_lexicon->GetAllWords() );
        for( ; it3.current(); ++it3 )
	{
            analyzed_exists = FALSE;
            //for( pWord = it3.current()->first(); pWord; pWord = it3.current()->next() )
            for (int z = 0; z < it3.current()->size(); z++)
            {
                pWord = it3.current()->at(z);
                if( pWord->Size() > 1 )
                {
                        analyzed_exists = TRUE;
                        count++;
                }
            }
	}

	if( count > 0 )
	{
		MiscItem = new CTreeViewItem( WordsItem,
									  "Analyzed " + IntToStringWithCommas( count ),
									  ALL_ANALYZED_WORDS );
	}

//=================================================================================================
  // END CONNECTED TO WordsItem
  // START CONNECTED TO SuffixesItem
//=================================================================================================

	count = 0;

	Q3DictIterator<SignatureSet> it7( *m_lexicon->GetAllSuffixSigs() );
	for( ; it7.current(); ++it7 )
	{
		count += it7.current()->count();
	}
	if( count > 0 )
	{
		MiscItem = new CTreeViewItem( SuffixesItem,
									  "Signatures " + IntToStringWithCommas( count ),
									  ALL_SUFFIX_SIGNATURES );
	}

//=================================================================================================
  // END CONNECTED TO SuffixesItem
  // START CONNECTED TO PrefixesItem
//=================================================================================================

	count = 0;

	Q3DictIterator<SignatureSet> it6( *m_lexicon->GetAllPrefixSigs() );
	for( ; it6.current(); ++it6 )
	{
		count += it6.current()->count();
	}
	if( count > 0 )
	{
		MiscItem = new CTreeViewItem( PrefixesItem,
									  "Signatures " + IntToStringWithCommas( count ),
									  ALL_PREFIX_SIGNATURES );
	}

//=================================================================================================
  // END CONNECTED TO PrefixesItem
  // START CONNECTED TO WordsReadItem
//=================================================================================================

	if( WordsReadItem )
	{
		if( m_lexicon->GetWords() )
		{
			count = m_lexicon->GetWords()->GetCount();
			if( count > 0 )
			{
				MiscItem = new CTreeViewItem( WordsReadItem,
											  "Distinct types read: " + IntToStringWithCommas( count ) );
				MiscItem->setSelectable(false);
			}
		} 

//======================================================================================//

		count = m_lexicon->GetCorpusCount();
		if( count >= 0 )
		{
			MiscItem = new CTreeViewItem( WordsReadItem,
										  "Tokens included: " + IntToStringWithCommas( count ) );
			MiscItem->setSelectable(false);
		} 
	}


//=================================================================================================
  // END CONNECTED TO WordsReadItem
  // START CONNECTED TO CompoundsItem
//=================================================================================================

	count = m_lexicon->GetLinkers()->GetCount();
	if( count > 0 )
	{
		MiscItem = new CTreeViewItem( CompoundsItem,
									  "Linkers " + IntToStringWithCommas( count ),
									  LINKERS, index );
	}
}



Q3ListViewItem* LinguisticaMainWindow::GetMiniLexiconSubTree(
	Q3ListViewItem* parent, int index)
{
	CMiniLexicon* lexicon = m_lexicon->GetMiniLexicon(index);
	if (lexicon == 0)
		// nothing to draw
		return 0;

	enum eAffixLocation affixLocation = lexicon->GetAffixLocation();

	// Items are inserted into the tree in reverse order
	// respective to their group.  They are organized by depth here,
	// i.e. what is connected to the root is the first group,
	// then do the groups of items connected to this first group, etc.
	// The only items that get their own name are those that have children.

	Q3ListViewItem* LexiconItem =
		// owned by parent
		new CTreeViewItem(parent,
			QString(
				m_lexicon->GetActiveMiniIndex() == index
				? "Mini-Lexicon %1\t**ACTIVE**"
				: "Mini-Lexicon %1")
				.arg(index+1),
			MINI_LEXICON, index);
	LexiconItem->setSelectable(false);
	LexiconItem->setOpen(true);
	// START CONNECTED TO LexiconItem
	if (lexicon->GetFSA() != 0)
	  static_cast<void>(new CTreeViewItem(
			LexiconItem, "FSA", FSA_DOC, index));

	// XXX. HMMLexemes, HMM Corpus Tokens?

	if (LexiconItem != 0)
		if (m_lexicon->GetDLHistory()->count() > 0)
			static_cast<void>(new CTreeViewItem(
				LexiconItem,
				"Description length",
				DESCRIPTION_LENGTH));

	// Suffixes or prefixes

	Q3ListViewItem* AffixesItem = 0;
	if (is_initial(affixLocation)) {
		// XXX. update to match suffix case

		const int count = lexicon->GetPrefixes()->GetCount();

		if (count > 0) {
			AffixesItem = new CTreeViewItem(LexiconItem,
				QString("Prefixes %1").arg(
				IntToStringWithCommas(count)),
				PREFIXES,
				index);
			AffixesItem->setOpen( true );
		}
	} else {
		const int count = lexicon->GetSuffixes()->GetCount();
		const int usecount = lexicon->GetSuffixes()->GetTotalUseCount();
		lexicon->GetSuffixes()->RecomputeCorpusCount();
		const int corpuscount = lexicon->GetSuffixes()->GetCorpusCount();

		if (count > 0) {
			AffixesItem = new CTreeViewItem(LexiconItem,
				QString("Suffixes %1 : %2 : %3").arg(
				IntToStringWithCommas(count),
				IntToStringWithCommas(usecount),
				IntToStringWithCommas(corpuscount)),
				SUFFIXES,
				index);
			AffixesItem->setOpen(true);
		}
	}

	{
		int dummy;
		const int count =
			lexicon->GetWords()->HowManyAreAnalyzed(dummy, this);
		if (count > 0) {
			static_cast<void>(new CTreeViewItem(LexiconItem,
				QString("Analyzed words %1").arg(
				IntToStringWithCommas(count)),
				ANALYZED_WORDS,
				index));
		}
	}

	Q3ListViewItem* WordsItem = 0;
	{
		const int count = lexicon->GetWords()->GetCount();
		if (count > 0) {
			QString caption = QString("Words %1 Z: %2")
				.arg(IntToStringWithCommas(count))
				.arg(lexicon->GetWords()->GetZ_Local());
			WordsItem = new CTreeViewItem(LexiconItem,
				caption, WORDS, index);
			WordsItem->setOpen(true);
		}
	}
	// END CONNECTED TO LexiconItem
	// START CONNECTED TO WordsItem
	{
		const int count = lexicon->GetWords()->GetTrie()->GetCount();
		if (count > 0) {
			if (lexicon->GetWords()->GetReverseTrie() != 0) {
				static_cast<void>(new CTreeViewItem(
						WordsItem,
						QString("Reverse trie %1")
						.arg(IntToStringWithCommas(count)),
						REVERSE_TRIE, index));
			}

			static_cast<void>(new CTreeViewItem(
					WordsItem,
					QString("Forward trie %1")
					.arg(IntToStringWithCommas(count)),
					TRIE, index));

		}
	}

	// XXX. lexicon->GetVowels()?

	{
		const int tier1_bigrams = lexicon->GetWords()
			->GetPhonologicalContentTier1Bigrams();
		// XXX. probably a typo.
		if (tier1_bigrams != 0) {
			static_cast<void>(new CTreeViewItem(
				WordsItem,
				QString("Unigram description length %1")
				.arg(IntToStringWithCommas(
					lexicon->GetWords()
					->GetPhonologicalContentUnigrams())),
				UNIGRAM_INFORMATION, index));
		}

		if (tier1_bigrams != 0) {
			static_cast<void>(new CTreeViewItem(
				WordsItem,
				QString("Bigram description length %1")
				.arg(IntToStringWithCommas(tier1_bigrams)),
				BIGRAM_INFORMATION, index));
		}
	}

	if (const int distant_log_pr =
			lexicon->GetWords()->GetDistantMI_Plog())
		static_cast<void>(new CTreeViewItem(
			WordsItem,
			QString("Distant MI model plog: %1")
			.arg(IntToStringWithCommas(distant_log_pr)),
			BIGRAM_INFORMATION, index));

	if (const int local_log_pr =
			lexicon->GetWords()->GetLocalMI_Plog())
		static_cast<void>(new CTreeViewItem(
			WordsItem,
			QString("Local MI model plog: %1")
			.arg(IntToStringWithCommas(local_log_pr)),
			BIGRAM_INFORMATION, index));

	if (const double distant_denom =
			lexicon->GetWords()->GetZ_Distant())
		static_cast<void>(new CTreeViewItem(
			WordsItem,
			QString("Z (distant model): %1")
			.arg(distant_denom),
			BIGRAM_INFORMATION, index));

	if (const double local_denom =
			lexicon->GetWords()->GetZ_Local())
		static_cast<void>(new CTreeViewItem(
			WordsItem,
			QString("Z (local) : %1")
			.arg(local_denom),
			BIGRAM_INFORMATION, index));

	// Phones inside words
	// Tier 2
	if (CPhoneCollection* phones = lexicon->GetWords()->GetPhones_Tier2()) {
		const int count = phones->GetCount();
		const int totalcount = phones->GetCorpusCount();

		if (count > 0) {
			Q3ListViewItem* Tier2Item =
				// owned by WordsItem
				new CTreeViewItem(WordsItem,
					"Tier 2 ",
					PHONES_Tier2, index);
				Tier2Item->setOpen(true);

			static_cast<void>(new CTreeViewItem(Tier2Item,
					QString("Phones %1 : %2")
					.arg(IntToStringWithCommas(count),
					IntToStringWithCommas(totalcount)),
					PHONES_Tier2, index));

			// Tier 2 biphones
			CBiphoneCollection* biphones = phones->GetMyBiphones();
			const int biphone_count = biphones->count();
			const int total_biphone_count = biphones->m_TotalCount;
			if (biphone_count > 0) {
				static_cast<void>(new CTreeViewItem(
					Tier2Item,
					QString("Biphones %1 : %2")
					.arg(IntToStringWithCommas(biphone_count),
					IntToStringWithCommas(total_biphone_count)),
					BIPHONES_Tier2, index));

				if (const int local_score = lexicon->GetWords()
						->GetTier2_LocalMI_Score())
					static_cast<void>(new CTreeViewItem(
						Tier2Item,
						QString("Tier 2 Local MI score %1")
						.arg(IntToStringWithCommas(
						local_score)),
						TIER2MI, index));

				if (const int distant_score = lexicon->GetWords()
						->GetTier2_DistantMI_Score())
					static_cast<void>(new CTreeViewItem(
						Tier2Item,
						QString("Tier 2 Distant MI score %1")
						.arg(IntToStringWithCommas(
						distant_score)),
						TIER2MI, index));
			}
		}
	}

	// Tier 1 Skeleton
	{
		CPhoneCollection* phones =
			lexicon->GetWords()->GetPhones_Tier1_Skeleton();
		const int count = phones->GetCount();
		const int totalcount = phones->GetCorpusCount();

		if (count > 0) {
			Q3ListViewItem* Tier1Item =
				// owned by WordsItem
				new CTreeViewItem(WordsItem,
					"Tier 1 Skeleton ",
					PHONES_Tier1_Skeleton, index);
				Tier1Item->setOpen(true);

			static_cast<void>(new CTreeViewItem(
					Tier1Item,
					QString("Phones (skeleton) %1 : %2")
					.arg(IntToStringWithCommas(count),
					IntToStringWithCommas(totalcount)),
					PHONES_Tier1_Skeleton, index));

			CBiphoneCollection* biphones = phones->GetMyBiphones();
			const int biphone_count = biphones->count();
			const int biphone_totalcount = biphones->m_TotalCount;
			if (biphone_count > 0) {
				static_cast<void>(new CTreeViewItem(
					Tier1Item,
					QString("Biphones (skeleton) %1 : %2")
					.arg(IntToStringWithCommas(biphone_count),
					IntToStringWithCommas(biphone_totalcount)),
					BIPHONES_Tier1_Skeleton, index));
			}
		}
	}

	{
		// Tier 1
		CPhoneCollection* phones = lexicon->GetWords()->GetPhones();
		const int count = phones->GetCount();
		const int totalcount = phones->GetCorpusCount();

		if (count > 0) {
			Q3ListViewItem* Tier1Item =
				// owned by WordsItem
				new CTreeViewItem(WordsItem,
					"Tier 1 ",
					PHONES, index);
				Tier1Item->setOpen(true);

			static_cast<void>(new CTreeViewItem(
					Tier1Item,
					QString("Phones %1 : %2")
					.arg(IntToStringWithCommas(count),
					IntToStringWithCommas(totalcount)),
					PHONES, index));

			CBiphoneCollection* biphones = phones->GetMyBiphones();
			const int biphone_count = biphones->count();
			const int biphone_totalcount = biphones->m_TotalCount;
			if (biphone_count > 0) {
				static_cast<void>(new CTreeViewItem(
					Tier1Item,
					QString("Biphones %1 : %2")
					.arg(IntToStringWithCommas(biphone_count),
					IntToStringWithCommas(biphone_totalcount)),
					BIPHONES, index));
			}
		}
	}
	// END CONNECTED TO WordsItem

	// START CONNECTED TO AffixesItem
	{
		const int count = lexicon->GetStems()->GetCount();
		if (count > 0) {
			static_cast<void>(new CTreeViewItem(
				AffixesItem,
				QString("Stems %1")
				.arg(IntToStringWithCommas(count)),
				STEMS, index));
		}
	}

	{
		const int count = lexicon->GetSignatures()->GetCount();
		if (count > 0) {
			static_cast<void>(new CTreeViewItem(
				AffixesItem,
				QString("Signatures %1")
				.arg(IntToStringWithCommas(count)),
				SIGNATURES, index));
		}
	}

	if (LxPoSCollection* parts_of_speech = lexicon->GetPOS()) {
		const int count = parts_of_speech->count();

		static_cast<void>(new CTreeViewItem(AffixesItem,
			QString("Parts of speech %1")
			.arg(IntToStringWithCommas(count)),
			POS, index));
	}

	return LexiconItem;
}
