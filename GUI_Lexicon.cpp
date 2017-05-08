// Implementation of CLexicon methods passing lists to Qt
// Copyright © 2009 The University of Chicago
#include "Lexicon.h"

#include "linguisticamainwindow.h"
#include "LPreferences.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "CorpusWord.h"
#include "Signature.h"
#include "Compound.h"
#include "Linker.h"
#include "Suffix.h"
#include "Prefix.h"
#include "Stem.h"
#include "CorpusWordCollection.h"
#include "SignatureCollection.h"
#include "CompoundCollection.h"
#include "LinkerCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "StemCollection.h"
#include "WordCollection.h"
#include "Typedefs.h"

void CLexicon::CorpusWordListDisplay( Q3ListView* pView, StringToString* filter, bool bAnalyzedWordsOnly )
{
	Q3ListViewItem* item;

	CCorpusWord* pCorpusWord;

	pView->setRootIsDecorated( FALSE );

	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );
	
	// Add column headings
	pView->addColumn( "Words" );
	pView->addColumn( "Parsed" );

	m_pCorpusWords->Sort(KEY);
	
	for( int i = 0; i < m_pCorpusWords->GetCount(); i++ )
	{
		pCorpusWord = m_pCorpusWords->GetAt(i);

		if( !bAnalyzedWordsOnly || pCorpusWord->Size() > 1 )
		{
			item = new Q3ListViewItem( pView, pCorpusWord->Display( '.', filter ), pCorpusWord->Display( '.', filter ) );
		}
	}
}

void CLexicon::PrefixListDisplay(Q3ListView* pView)
{
	CPrefix* pPrefix;

	CPrefixListViewItem* item;

	pView->setRootIsDecorated( FALSE );

	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );

	// Add Column headers
	pView->addColumn( "Prefix" );
	pView->addColumn( "Desc. Length" );
	pView->addColumn( "Corpus Count" );
	pView->addColumn( "Use Count" );
	pView->addColumn( "Stems" );

	Q3DictIterator<PrefixSet> it( m_AllPrefixes );
    for( ; it.current(); ++it )
	{
		
                //for( pPrefix = it.current()->first(); pPrefix; pPrefix = it.current()->next() )
                for (int z = 0; z < it.current()->size(); z++)
                {       pPrefix = it.current()->at(z);
			item = new CPrefixListViewItem( pView,
											pPrefix->Display(  GetOutFilter() ),
											pPrefix,
											GetOutFilter(),
											GetNumberOfCharacterTypes() );
		}
	}
}

void CLexicon::SuffixListDisplay(Q3ListView* pView)
{
	CSuffix* pSuffix;

	CSuffixListViewItem* item;

	pView->setRootIsDecorated( FALSE );

	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );

	// Add Column headers
	pView->addColumn( "Suffix" );
	pView->addColumn( "Desc. Length" );
	pView->addColumn( "Corpus Count" );
	pView->addColumn( "Use Count" );
	pView->addColumn( "Stems" );

	Q3DictIterator<SuffixSet> it( m_AllSuffixes );
    for( ; it.current(); ++it )
	{
		
                //for( pSuffix = it.current()->first(); pSuffix; pSuffix = it.current()->next() )
                for (int z = 0; z < it.current()->size(); z++)
                {       pSuffix = it.current()->at(z);
			item = new CSuffixListViewItem( pView, pSuffix->Display( GetOutFilter() ),
								pSuffix,
								GetOutFilter(),
								GetNumberOfCharacterTypes() );
		}
	}
}

void CLexicon::SignatureListDisplay(Q3ListView* pView,
	enum eDocumentType docType)
{
	CSignature*				pSignature;
	CSignatureListViewItem* item;

	pView->setRootIsDecorated( FALSE );

	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );

	// Add Column headers
	pView->addColumn( "Signatures" );
	pView->addColumn( "Mini" );
	pView->addColumn( "Exemplar" );
	pView->addColumn( "Desc. Length" );
	pView->addColumn( "Corpus Count" );
	pView->addColumn( "Sigs" );
	pView->addColumn( "Remarks" );
	pView->addColumn( "Robustness" );
	pView->addColumn( "Sort Alphabetically" );
	
	Q3DictIterator<SignatureSet> it( m_AllSuffixSigs );

	QString sigDelimiter = m_pDoc->GetPreferences()->GetPreference( "Sig_Delimiter" );
	if( sigDelimiter.length() < 1 ) sigDelimiter = ".";

	switch( docType )
	{
	case SUFFIX_SIGNATURES:
		// Do nothing, default is suffix sig
		break;
	case PREFIX_SIGNATURES:
		it = Q3DictIterator<SignatureSet>( m_AllPrefixSigs );
		break;
	case SIGNATURES:
	default:
		return;
	}

	for( ; it.current(); ++it )
	{
		
                //for( pSignature = it.current()->first(); pSignature; pSignature = it.current()->next() )
                for (int z = 0; z < it.current()->size(); z++)
                {       pSignature = it.current()->at(z);
			item = new CSignatureListViewItem( pView,
											   pSignature->Display( sigDelimiter.at(0), GetOutFilter() ),
											   pSignature->GetMyMini()->GetIndex(),
											   pSignature,
											   GetOutFilter() );
		}
	}
}

void CLexicon::StemListDisplay(Q3ListView* pView)
{
	CStem* pStem;

	CStemListViewItem* item;

	pView->setRootIsDecorated( FALSE );

	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );

	// Add Column headers
	pView->addColumn( "Stem" );
	pView->addColumn( "Mini" );
	pView->addColumn( "Descr. Length" );
	pView->addColumn( "Corpus count" );
	pView->addColumn( "Suffix sig" );
	pView->addColumn( "Prefix sig" );
	pView->addColumn( "Origin" );
	pView->addColumn( "Type" );

	Q3DictIterator<StemSet> it( m_AllStems );
    for( ; it.current(); ++it )
	{		
                //for( pStem = it.current()->first(); pStem; pStem = it.current()->next() )
                for (int z= 0; z < it.current()->size(); z++)
                {
                        pStem = it.current()->at(z);
			item = new CStemListViewItem( pView,
										  pStem->Display( GetOutFilter() ),
										  pStem->GetMyMini()->GetIndex(),
										  pStem,
										  GetOutFilter(),
										  GetNumberOfCharacterTypes() );
		}
	}
}

void CLexicon::WordListDisplay(Q3ListView* pView, bool analyzedOnly)
{
	CStem* pWord;

	CWordListViewItem* item;

	pView->setRootIsDecorated( FALSE );

	// Remove all previous columns
	while( pView->columns() ) pView->removeColumn( 0 );

	//    Add Column headers
	pView->addColumn( "Word" );
	pView->addColumn( "Mini" );
	pView->addColumn( "Desc. Length" );
	pView->addColumn( "Corpus Count" );
	pView->addColumn( "Type" );
	pView->addColumn( "Signature" );
	pView->addColumn( "Source" );
	pView->addColumn( "Prefix" );
	pView->addColumn( "Stem" );
	pView->addColumn( "Suffix" );

	Q3DictIterator<StemSet> it( m_AllWords );
    for( ; it.current(); ++it )
	{
                //for( pWord = it.current()->first(); pWord; pWord = it.current()->next() )
                for (int z = 0; z < it.current()->size(); z++)
                {       pWord = it.current()->at(z);
			if( !analyzedOnly || pWord->Size() > 1 )
			{
				item = new CWordListViewItem( pView, pWord->Display( GetOutFilter() ),
											  pWord->GetMyMini()->GetIndex(),
											  pWord,
											  GetOutFilter(),
											  Lexicon_Word,
											  GetNumberOfCharacterTypes() );
			}
		}
	}
}

