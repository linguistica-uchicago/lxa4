// Implementation of CPrefixCollection methods
// Copyright © 2009 The University of Chicago
#include "PrefixCollection.h"

#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "Lexicon.h"
#include "MiniLexicon.h"
#include "Prefix.h"

CPrefixCollection::CPrefixCollection (CMiniLexicon* Lex)
{  
	m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
}



CPrefixCollection::CPrefixCollection ( )
{
  m_pLexicon = NULL;
  m_pMiniLex = NULL;
}


CPrefixCollection::~CPrefixCollection()
{
	if( m_pLexicon )
	{
		CPrefix* pPrefix;

		for( int i = 0; i < GetCount(); i++ )
		{
			pPrefix = GetAt(i);

			m_pLexicon->RemovePrefix( pPrefix );
		}
	}
}





CPrefix* CPrefixCollection::operator<< ( CStringSurrogate Prefix )
{
  CPrefix*  pPrefix;

  pPrefix = AddToCollection( Prefix );

  return pPrefix;
}


CPrefix* CPrefixCollection::operator<< ( CParse* Prefix )
{
  CPrefix*  pPrefix;

  pPrefix = AddToCollection (*Prefix);

  return pPrefix;
}


CPrefix* CPrefixCollection::operator<< ( QString Prefix )
{
  CPrefix*  pPrefix;

  CStringSurrogate ssPrefix( Prefix );
  pPrefix = AddToCollection( ssPrefix );

  return pPrefix;
}


void CPrefixCollection::AddPointer( CPrefix* pPrefix )
{
	TCollection<CPrefix>::AddPointer( pPrefix );

	if( m_pLexicon ) m_pLexicon->InsertPrefix( pPrefix );
}


CPrefix* CPrefixCollection::AddToCollection( CParse& Prefix )
{
	CPrefix* pPrefix = TCollection<CPrefix>::AddToCollection( Prefix );

	if( m_pLexicon ) m_pLexicon->InsertPrefix( pPrefix );

	return pPrefix;
}


CPrefix* CPrefixCollection::AddToCollection( CStringSurrogate& Prefix )
{
	CPrefix* pPrefix = TCollection<CPrefix>::AddToCollection( Prefix );

	if( m_pLexicon ) m_pLexicon->InsertPrefix( pPrefix );

	return pPrefix;
}


void CPrefixCollection::Empty()
{
	if( m_pLexicon )
	{
		CPrefix* pPrefix;

		for( int i = 0; i < GetCount(); i++ )
		{
			pPrefix = GetAt(i);

			m_pLexicon->RemovePrefix( pPrefix );
		}
	}

	TCollection<CPrefix>::Empty();
}


void CPrefixCollection::RemoveAll()
{
	if( m_pLexicon )
	{
		CPrefix* pPrefix;

		for( int i = 0; i < GetCount(); i++ )
		{
			pPrefix = GetAt(i);

			m_pLexicon->RemovePrefix( pPrefix );
		}
	}

	TCollection<CPrefix>::RemoveAll();
}


bool CPrefixCollection::Remove( CPrefix* pPrefix )
{
	if( m_pLexicon ) m_pLexicon->RemovePrefix( pPrefix );

	return TCollection<CPrefix>::Remove( pPrefix );
}


bool CPrefixCollection::RemoveMember( CPrefix* pPrefix )
{
	if( m_pLexicon ) m_pLexicon->RemovePrefix( pPrefix );

	return TCollection<CPrefix>::RemoveMember( pPrefix );
}


bool CPrefixCollection::RemoveMember( CStringSurrogate& Prefix )
{
	CPrefix* pPrefix = (CPrefix*)Find1( Prefix )->Get_T_Pointer();

	if( m_pLexicon ) m_pLexicon->RemovePrefix( pPrefix );

	return TCollection<CPrefix>::RemoveMember( Prefix );
}


bool CPrefixCollection::RemoveMember( CStringSurrogate& Prefix, bool b )
{
	CPrefix* pPrefix = (CPrefix*)Find1( Prefix )->Get_T_Pointer();

	if( m_pLexicon ) m_pLexicon->RemovePrefix( pPrefix );

	return TCollection<CPrefix>::RemoveMember( Prefix, b );
}


void CPrefixCollection::DeleteMarkedMembers()
{
	if ( m_DeletionArray == NULL ) { return; }

	int count = GetCount();
	for (int i = 0; i < count; i++)
	{
		if ( m_DeletionArray[i] == 1 )
		{
			if( m_pLexicon ) m_pLexicon->RemovePrefix( m_PointerArray[i] );
		}
	}

	TCollection<CPrefix>::DeleteMarkedMembers();
}


void CPrefixCollection::ListDisplay( Q3ListView* pView, StringToString* filter )
{

	pView->setRootIsDecorated( FALSE );
  pView->setSorting(1);
  // Clean it out first
  while( pView->columns() ) pView->removeColumn( 0 );

  // Add Column headers
  pView->addColumn( "Prefixes" );
  pView->addColumn( "Descr. Length" );
  pView->addColumn( "Corpus Count" );
  pView->addColumn( "Use Count" );
  pView->addColumn( "Stems" );

  if( m_pLexicon ) m_pLexicon->GetDocument()->setStatusBar1( "Creating prefix list for display" );
  if( m_pLexicon ) m_pLexicon->GetDocument()->BeginCountDown();

  if( m_SortValidFlag == FALSE )
  {
    Sort(COUNT);
  }

  // Display each item
  for (int i = 0; i < (int) GetCount(); i++)
  {
    GetAtSort(i)->ListDisplay( pView, filter, m_pLexicon->GetNumberOfCharacterTypes() );

    if( m_pLexicon ) m_pLexicon->GetDocument()->CountDownOnStatusBar( i, GetCount() );
  }

  if( m_pLexicon ) m_pLexicon->GetDocument()->setStatusBar1( "" );
  if( m_pLexicon ) m_pLexicon->GetDocument()->EndCountDown();
}


void CPrefixCollection::OutputPrefixes( QString FileName )
{
	Q_ASSERT(!FileName.isEmpty());
	QFile file( FileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream outf( &file );
		outf.setEncoding( Q3TextStream::Unicode );

		outf << "# Prefix Count" << endl;
		outf << "# ------------" << endl;
		outf << "  " << GetCount() << endl << endl;

		outf << "# Prefix       | Use Count | Corpus Count | Index | " << endl;
		outf << "# ------------------------------------------------- " << endl;
		
		Sort( CORPUSCOUNT );
		for (int i = 0; i < (int)GetCount(); i++)
		{
			GetAtSort(i)->OutputPrefix( outf );
		}

		file.close();
	}
}


void  CPrefixCollection::ReadPrefixFile (QString FileName)
{
	Q_ASSERT(!FileName.isEmpty());
	CPrefix*	pPrefix;
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

			pPrefix = *this << CStringSurrogate( Key );
			pPrefix->IncrementUseCount( UseCount );
			pPrefix->IncrementCorpusCount( CorpusCount );
		}

		file.close();
	} 
}


double	CPrefixCollection::GetDL_PhonologicalContent()
{
	double affix_total_dl = 0;
	int i;
	CPrefix* pAffix;
	for( i = 0; i < (int)GetCount(); i++ )
	{
		pAffix =  GetAt(i);
		affix_total_dl += pAffix->ComputeDL( m_pMiniLex->GetNumberOfCharacterTypes() );
	}
	return affix_total_dl ;
}
