// Implementation of CSuffixCollection methods
// Copyright © 2009 The University of Chicago
#include "SuffixCollection.h"

#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Suffix.h"
#include "log2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSuffixCollection::CSuffixCollection(CMiniLexicon* Lex)
{
  // do the creation of TCollection with ptr to Lexicon and name of class
	m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
}


CSuffixCollection::CSuffixCollection( )
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL;
}


CSuffixCollection::~CSuffixCollection()
{
	if( m_pLexicon )
	{
		CSuffix* pSuffix;
		for( int i = 0; i < GetCount(); i++ )
		{
			pSuffix = GetAt(i);

			m_pLexicon->RemoveSuffix( pSuffix );
		}
	}
}


void CSuffixCollection::ListDisplay(Q3ListView* pView, StringToString* filter, bool ExpressDeletees )
{
  CSuffix*      pSuffix;

  pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);

  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  //    Add Column headers
  pView->addColumn( "Suffixes"		);
  pView->addColumn( "Descr. Length" );
  pView->addColumn( "Length of Ptr"	);
  pView->addColumn( "Corpus Count"	);
  pView->addColumn( "Use Count"		);
  pView->addColumn( "Stems"			);

  // Column three gets really wide, limit
  // the width to 100
  pView->setColumnWidthMode( 3, Q3ListView::Manual );
  pView->setColumnWidth( 3, 100 );

  if( m_pLexicon ) m_pLexicon->GetDocument()->setStatusBar1( "Creating suffix list for display" );
  if( m_pLexicon ) m_pLexicon->GetDocument()->BeginCountDown();


  if (m_SortValidFlag == FALSE)
  {
    Sort(COUNT);
  }

  for (int i = 0; i < (int)GetCount(); i++)
  {
    pSuffix = GetAtSort(i);
    pSuffix->ListDisplay( pView, filter, ExpressDeletees, m_pLexicon->GetNumberOfCharacterTypes() );

    if( m_pLexicon ) m_pLexicon->GetDocument()->CountDownOnStatusBar(i, GetCount());
  }

  if( m_pLexicon ) m_pLexicon->GetDocument()->setStatusBar1( "" );
  if( m_pLexicon ) m_pLexicon->GetDocument()->BeginCountDown();
}


CSuffix* CSuffixCollection::operator<< ( CStringSurrogate& Suffix )
{
  CSuffix*  pSuffix;

  pSuffix = AddToCollection( Suffix );

  return pSuffix;
}


CSuffix* CSuffixCollection::operator<< ( CParse* Suffix )
{
  CSuffix*  pSuffix;

  pSuffix = AddToCollection (*Suffix);

  return pSuffix;
}


CSuffix* CSuffixCollection::operator<< ( CParse& Suffix )
{
  CSuffix*  pSuffix;

  pSuffix = AddToCollection (Suffix);

  return pSuffix;
}

CSuffix* CSuffixCollection::operator<< ( QString Suffix )
{
  CSuffix*  pSuffix;

  CStringSurrogate cssSuffix( Suffix );

  pSuffix = AddToCollection( cssSuffix );

  return pSuffix;
}


void CSuffixCollection::AddPointer( CSuffix* pSuffix )
{
	TCollection<CSuffix>::AddPointer( pSuffix );

	if( m_pLexicon ) m_pLexicon->InsertSuffix( pSuffix );
}


CSuffix* CSuffixCollection::AddToCollection( CParse& Suffix )
{
	CSuffix* pSuffix = TCollection<CSuffix>::AddToCollection( Suffix );

	if( m_pLexicon ) m_pLexicon->InsertSuffix( pSuffix );

	return pSuffix;
}


CSuffix* CSuffixCollection::AddToCollection( CStringSurrogate& Suffix )
{
	CSuffix* pSuffix = TCollection<CSuffix>::AddToCollection( Suffix );

	if( m_pLexicon ) m_pLexicon->InsertSuffix( pSuffix );

	return pSuffix;
}


void CSuffixCollection::Empty()
{
	if( m_pLexicon )
	{
		CSuffix* pSuffix;

		for( int i = 0; i < GetCount(); i++ )
		{
			pSuffix = GetAt(i);

			m_pLexicon->RemoveSuffix( pSuffix );
		}
	}

	TCollection<CSuffix>::Empty();
}


void CSuffixCollection::RemoveAll()
{
	if( m_pLexicon )
	{
		CSuffix* pSuffix;

		for( int i = 0; i < GetCount(); i++ )
		{
			pSuffix = GetAt(i);

			m_pLexicon->RemoveSuffix( pSuffix );
		}
	}

	TCollection<CSuffix>::RemoveAll();
}


bool CSuffixCollection::Remove( CSuffix* pSuffix )
{
	if( m_pLexicon ) m_pLexicon->RemoveSuffix( pSuffix );

	return TCollection<CSuffix>::Remove( pSuffix );
}


bool CSuffixCollection::RemoveMember( CSuffix* pSuffix )
{
	if( m_pLexicon ) m_pLexicon->RemoveSuffix( pSuffix );

	return TCollection<CSuffix>::RemoveMember( pSuffix );
}


bool CSuffixCollection::RemoveMember( CStringSurrogate& Suffix )
{
	CSuffix* pSuffix = (CSuffix*)Find1( Suffix )->Get_T_Pointer();

	if( m_pLexicon ) m_pLexicon->RemoveSuffix( pSuffix );

	return TCollection<CSuffix>::RemoveMember( Suffix );
}


bool CSuffixCollection::RemoveMember( CStringSurrogate& Suffix, bool b )
{
	CSuffix* pSuffix = (CSuffix*)Find1( Suffix )->Get_T_Pointer();

	if( m_pLexicon ) m_pLexicon->RemoveSuffix( pSuffix );

	return TCollection<CSuffix>::RemoveMember( Suffix, b );
}

int CSuffixCollection::GetTotalUseCount() 
{  if (m_TotalUseCount <= 0) 
      CalculateTotalUseCount();
    return m_TotalUseCount;
}

void CSuffixCollection::CalculateTotalUseCount()
{
	m_TotalUseCount = 0;
       for (int i = 0; i < GetCount(); i++)
       {	   m_TotalUseCount += GetAt(i)->GetUseCount();
       }
}

void CSuffixCollection::DeleteMarkedMembers()
{
	if ( m_DeletionArray == NULL ) { return; }

	int count = GetCount();
	for (int i = 0; i < count; i++)
	{
		if ( m_DeletionArray[i] == 1 )
		{
			if( m_pLexicon ) m_pLexicon->RemoveSuffix( m_PointerArray[i] );
		}
	}

	TCollection<CSuffix>::DeleteMarkedMembers();
}


void CSuffixCollection::OutputSuffixes( QString FileName )
{
	QFile file( FileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream outf( &file );
		outf.setEncoding( Q3TextStream::Unicode );

		outf << "# Suffix Count" << endl;
		outf << "# ------------" << endl;
		outf << "  " << GetCount() << endl << endl;

		outf << "# Suffix       | Use Count | Corpus Count | Index | " << endl;
		outf << "# ------------------------------------------------- " << endl;
		
		Sort( CORPUSCOUNT );
		for (int i = 0; i < (int)GetCount(); i++)
		{
			GetAtSort(i)->OutputSuffix( outf );
		}

		file.close();
	}
}


void  CSuffixCollection::ReadSuffixFile (QString FileName)
{
	CSuffix*	pSuffix;
	QFile		file(FileName);
	QString	Buffer, Key;
	int		Index,
	size,
	UseCount,
	CorpusCount,
	LineCount = 0;

	if( file.exists() && file.open( QIODevice::ReadOnly ) )
	{
		Q3TextStream inf(&file);
		inf.setEncoding ( Q3TextStream::Locale );

		Buffer = inf.readLine();
		Q_ASSERT( Buffer[0] == '#' );

		Buffer = inf.readLine();
		Q_ASSERT( Buffer[0] == '#' );

		inf >> size;

		Buffer = inf.readLine(); // end of size line
		Q_ASSERT( Buffer.length() == 0 );

		Buffer = inf.readLine(); // blank line
		Q_ASSERT( Buffer.length() == 0 );

		Buffer = inf.readLine();
		Q_ASSERT( Buffer[0] == '#' );

		Buffer = inf.readLine();
		Q_ASSERT( Buffer[0] == '#' );

		while( !inf.atEnd() && LineCount < size )
		{
			LineCount++;

			inf >> Key;
			inf >> UseCount;
			inf >> CorpusCount;
			inf >> Index;

			// Filter all sequences that should be
			// analyzed as one character
			Key = Filter( m_pLexicon->GetInFilter(), Key );

			pSuffix = *this <<   Key ;
			pSuffix->IncrementUseCount( UseCount );
			pSuffix->IncrementCorpusCount( CorpusCount );
		}

		file.close();
	}  
}

double	CSuffixCollection::GetDL_PhonologicalContent()
{
	double affix_total_dl = 0;
	int i;
	CSuffix* pAffix;
	for( i = 0; i < (int)GetCount(); i++ )
	{
		pAffix =  GetAt(i);
		affix_total_dl += pAffix->ComputeDL( m_pMiniLex->GetNumberOfCharacterTypes() );
	}
	return affix_total_dl ;
}


double	CSuffixCollection::CalculatePointersToMySuffixes(eMDL_STYLE style )//sum of pointers to members; this should be removed, and replaced by "GetLengthOfPointerToMe"
{
	double			Denominator = 0;
	double			ptr;
//	CSuffix *		pSuffix;
	int				i = 0;
					m_DLofPointersToMyMembers = 0;
					m_CorpusCount = 0;
 	
	if (style == CorpusCount )
	{
		for (i = 0; i < GetCount(); i++)
		{
			m_CorpusCount += GetAt(i)->GetCorpusCount();
		}
		for (i = 0; i < GetCount(); i++)
		{
			ptr = base2log ( m_CorpusCount / GetAt(i)->GetCorpusCount() );
			m_DLofPointersToMyMembers += ptr;
		}

	}
	else if (style  == GrammarCount )
	{
		for (i = 0; i < GetCount(); i++)
		{
			Denominator += GetAt(i)->GetUseCount();
		}
		for (i = 0; i < GetCount(); i++)
		{
			ptr = base2log ( Denominator/ GetAt(i)->GetUseCount() );
			m_DLofPointersToMyMembers += ptr;
		}
	}
	return m_DLofPointersToMyMembers;
}
