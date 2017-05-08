// Implementation of CSignatureCollection methods
// Copyright © 2009 The University of Chicago
#include "SignatureCollection.h"

#include <exception>
#include <iostream>
#include <memory>
#include <QTextStream>
#include <QMessageBox>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Allomorphy.h"
#include "Signature.h"
#include "Prefix.h"
#include "Suffix.h"
#include "Stem.h"
#include "PrefixCollection.h"
#include "SuffixCollection.h"
#include "StemCollection.h"
#include "HTML.h"
#include "log2.h"

CSignatureCollection::CSignatureCollection() 
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL;
    m_MemberName = "Signatures";
    MySuffixes = NULL;
    MyPrefixes = NULL;
	m_DLofPointersToMyMembers	=0;
}
CSignatureCollection::CSignatureCollection( CMiniLexicon* Lex )
{
    m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
    m_MemberName = "Signatures";
    m_SignatureType = m_pMiniLex->GetAffixLocation();
    MySuffixes = NULL;
    MyPrefixes = NULL;
	m_DLofPointersToMyMembers	=0;

}
CSignatureCollection::CSignatureCollection (CMiniLexicon* Lex, CSuffixCollection* suffixes, eAffixLocation AfLoc)
{
    m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
    m_MemberName    = "Signatures";
    MySuffixes      = suffixes;
    m_SignatureType    = AfLoc;
    MyPrefixes = NULL;
	m_DLofPointersToMyMembers	=0;

}
CSignatureCollection::CSignatureCollection (CMiniLexicon* Lex, CPrefixCollection* Prefixes, eAffixLocation AfLoc)
{
    m_pMiniLex = Lex;
	if( m_pMiniLex ) m_pLexicon = m_pMiniLex->GetLexicon();
    m_MemberName    = "Signatures";
    MyPrefixes      = Prefixes;
    m_SignatureType    = AfLoc;
    MySuffixes = NULL;
	m_DLofPointersToMyMembers	=0;

}
CSignatureCollection::CSignatureCollection (eAffixLocation  SigType)
{
	m_pMiniLex = NULL;
	m_pLexicon = NULL;
    m_SignatureType = SigType;
    m_MemberName = "Signatures";
    MySuffixes = NULL;
    MyPrefixes = NULL;
		m_DLofPointersToMyMembers	=0;

}


CSignatureCollection::~CSignatureCollection()
{
	if( m_pLexicon )
	{
		CSignature* pSig;

		for( int i = 0; i < GetCount(); i++ )
		{
			pSig = GetAt(i);

			if( m_pLexicon ) 
			{
				switch( m_SignatureType )
				{
				case STEM_INITIAL:
				case WORD_INITIAL:
					m_pLexicon->RemovePrefixSig( pSig );
					break;
				case WORD_FINAL:
				case STEM_FINAL:
				default:
					m_pLexicon->RemoveSuffixSig( pSig );
				}
			}
		}
	}
}
CSignature*   CSignatureCollection::operator^= (QString Signature) //" Lookup"
{
   if( Signature.length() < 1  ) return NULL;
 
  CNode *pNode = Find1 ( CStringSurrogate( Signature.unicode(),0,Signature.length() ) );
  if ( pNode )
  {
    return (CSignature*) pNode->Get_T_Pointer();
  }
  else { return NULL; }

}
CSignature*   CSignatureCollection::operator^= (CParse& Parse) //" Lookup"
{
  // Return NULL if parse is empty.
  if( Parse.GetKeyLength() < 1 || Parse.Size() < 1 ) return NULL;

  Parse.Alphabetize();

  QString display = Parse.Display('.');
  CNode *pNode = Find1 ( CStringSurrogate( display.unicode(),0,display.length() ) );
  if ( pNode )
  {
    return (CSignature*) pNode->Get_T_Pointer();
  }
  else { return NULL; }

}
CSignature*   CSignatureCollection::operator^= (CParse* pParse) //" Lookup"
{
  // Return NULL if parse is empty.
  if( pParse->GetKeyLength() < 1 || pParse->Size() < 1 ) return NULL;

  pParse->Alphabetize();

  QString display = pParse->Display('.');
  CNode *pNode = Find1 ( CStringSurrogate( display.unicode(),0,display.length() ) );
  if ( pNode )
  {
    return (CSignature*) pNode->Get_T_Pointer();
  }
  else { return NULL; }

}
CSignature*   CSignatureCollection::operator^= (CStringSurrogate&  Signature) //" Lookup"
{
  // Return NULL if Signature is empty.
  if( Signature.GetLength() < 1 ) return NULL;

  CNode *pNode = Find1 ( Signature );
  if ( pNode )
  {
    return (CSignature*) pNode->Get_T_Pointer();
  }
  else { return NULL; }


}

void CSignatureCollection::SetMyPrefixes(CPrefixCollection* pAC){   MyPrefixes = pAC;}
void CSignatureCollection::SetMySuffixes(CSuffixCollection* pAC){   MySuffixes = pAC;}


void CSignatureCollection::FindDisplayOrdering()  
{
  int         Size = GetCount(),
              i;
  CSignature* pSig,
              *qSig;


  Sort (SIGS);

  for ( i = 0; i < Size; i++)
  {
    pSig = GetAtSort(i);  // We're looking for pSig's mentor, if it has one
    if (pSig->Size() < 2) continue;
    for (int j = 0; j < i; j++)
    {
      qSig = GetAtSort(j);

      if ( qSig->Contains(pSig) )
      {
        pSig->SetMentor (qSig);
        break;
      }
      else pSig->SetMentor( NULL );
    }
  }
   
  m_SortStyle = SIG_MENTORS;
  m_SortValidFlag = TRUE;
//  delete [] TempArray;
}
void CSignatureCollection::ListDisplay(Q3ListView* pView, StringToString* filter)
{

   int MinimumNumberOfStemsForDisplay = 2; //make this adjustable by user @@@@
  if (GetCount() < 20 ) MinimumNumberOfStemsForDisplay = 1;

  int MinimumNumberOfAffixesForDisplay = 2; //make this adjustable by user @@@@
 

   pView->setSorting(6);
 
   // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );
  pView->clear();
 
  // Add Column headers
  pView->addColumn( "Signatures" );
  pView->addColumn( "Exemplar" );
  pView->addColumn( "Descr. Length (model)" );
  pView->addColumn( "Corpus Count" );
  pView->addColumn( "Stem Count" );
  pView->addColumn( "Source" );
  pView->addColumn( "Robustness" );

  pView->setColumnAlignment(0, Qt::AlignLeft );
 
  m_pLexicon->GetDocument()->setStatusBar1( "Creating signature list for display" );
  m_pLexicon->GetDocument()->BeginCountDown();

 
 
  FindDisplayOrdering();
  int i; 
	

  CSignature* pSig, *qSig;
  for ( i = GetCount()-1; i >=0 ; i--)
  {
    pSig = GetAtSort(i);
    if (pSig->GetMentor()) {continue;}
    if (pSig->GetNumberOfStems() < MinimumNumberOfStemsForDisplay ) continue;    
    if (pSig->Size() < MinimumNumberOfAffixesForDisplay ) continue;    

    CSignatureListViewItem* item = new CSignatureListViewItem( pView, pSig->Express(), m_pMiniLex->GetIndex(), pSig, filter );
     if (pSig->GetMentorList() )
    {
        for (int z = 0; z < pSig->GetMentorList()->size(); z++)
        {
             qSig = pSig->GetMentorList()->at(z);
             if (qSig->GetNumberOfStems() < MinimumNumberOfStemsForDisplay ) continue;    
             new CSignatureListViewItem( item, qSig->Display(), m_pMiniLex->GetIndex(), qSig, filter );
        }
        item->setOpen(TRUE);
    }
  }
  m_pLexicon->GetDocument()->setStatusBar1( "" );
  m_pLexicon->GetDocument()->EndCountDown();
}

void CSignatureCollection::BorrowedSigsDisplay( Q3ListView* pView, StringToString* filter )
{

  // Remove all previous columns
  while( pView->columns() ) pView->removeColumn( 0 );

  // Add Column headers
  pView->addColumn( "Signatures" );
  pView->addColumn( "Source" );

  m_pLexicon->GetDocument()->setStatusBar1( "Creating signature list for display" );
  m_pLexicon->GetDocument()->BeginCountDown();

  // Display each item
  for (int i = 0; i < (int)GetCount(); i++)
  {
    GetAt(i)->BorrowedSigsDisplay( pView, filter );
    m_pLexicon->GetDocument()->CountDownOnStatusBar(i, GetCount());
  }

  m_pLexicon->GetDocument()->setStatusBar1( "" );
  m_pLexicon->GetDocument()->EndCountDown();
}


////////////////////////////////////////////////////
////////////////////////////////////////////////////
//
//
//      Verbose Output
//
//
////////////////////////////////////////////////////
////////////////////////////////////////////////////


void CSignatureCollection::OutputSignatures( QString FileName )
{
	QFile file( FileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
                QTextStream outf( &file );
                outf.setEncoding( QTextStream::Unicode );

		outf << "# Signature Count" << endl;
		outf << "# ---------------" << endl;
		outf << "  " << GetCount() << endl << endl;

		outf << "# Signature    Stem Count   Corpus Count " << endl;
		outf << "# -------------------------------------- " << endl;
		outf << "# Remark " << endl;
		outf << "# ------ " << endl;
		outf << "# Stems " << endl;
		outf << "# ----- " << endl;
		
		Sort( CORPUSCOUNT );
		for (int i = 0; i < (int)GetCount(); i++)
		{
			GetAtSort(i)->OutputSignature( outf );
		}

		file.close();
	}
}



////////////////////////////////////////////////////
////////////////////////////////////////////////////
//
//
//      Limited Output
//
//
////////////////////////////////////////////////////
////////////////////////////////////////////////////

/*void CSignatureCollection::LimitedOutput (QString Filename)
{
	QFile	file( Filename );

	if( file.open( IO_WriteOnly ) )
	{
		QTextStream	outf( &file );
		int			TotalWordCount = 0;
		CSignature*	pSig;
		QString		dummy;
		int			i = 0,
					counter = 0;
		int			NumEntries = GetCount();

		outf.setf(2);  // Set fields left justified
		outf << "# Index Signature StemCount AffixCount log(StemCount)*log(AffixCount)" << endl << endl;
	
		Sort(SIGS);
		for( i = 0; i < NumEntries; i++  )
		{
			pSig = GetAtSort(i);

			outf << ++counter << " ";
			outf << pSig -> Display( '.', m_pLexicon->GetOutFilter() ) << " ";
			outf << pSig -> GetStems().Size() << " ";
			outf << pSig->GetNumberOfAffixes()
				<< " " << log( pSig->GetStems().Size() ) * log ( pSig->GetNumberOfAffixes() )
				<< endl;
		
			TotalWordCount += pSig->GetStemPtrList()->count() * pSig->GetNumberOfAffixes();
		}

		outf << endl << "Total number of words covered: " << TotalWordCount;

		file.close();
	}
	return;
}*/

namespace {
	struct cannot_parse_input : virtual std::exception { };

	/// skip blank lines and comments
	QString get_line(QTextStream& in)
	{
		QString buf;
		do {
			buf = in.readLine();
		} while (buf.isEmpty() || buf[0] == '#');
		return buf;
	}

	/// swallow end of line, throwing an exception if that involves
	/// useful data.
	void check_end_of_line(QTextStream& in)
	{
		QString remainder = in.readLine();
		if (!remainder.isEmpty())
			throw cannot_parse_input();
	}

	int string_to_int(QString s)
	{
		bool ok;
		int result = s.toInt(&ok);
		if (!ok)
			throw cannot_parse_input();
		return result;
	}
}

void CSignatureCollection::ReadSignatureFile(QString Filename,
		enum eAffixLocation SigType) { try
{
	QFile file(Filename);
	if (!file.open(QIODevice::ReadOnly))
		return;

	QTextStream inf(&file);

	const int signature_count = string_to_int(
		get_line(inf).trimmed());

	delete[] m_PointerArray;
	m_PointerArray = new CSignature*[signature_count];

	for (int count = 1; count <= signature_count; ++count) {
		QString sig_header = get_line(inf).trimmed();

		// line 1:
		// SP+ signature SP+ stem count SP+ corpus count SP+
		QTextStream line_in(&sig_header, QIODevice::ReadOnly);
		QString sig_graphemes, stem_count_text,
				corpus_count_text;
		line_in >> sig_graphemes >>
			stem_count_text >> corpus_count_text;
		check_end_of_line(line_in);

		const QString sig_text = Filter(m_pLexicon->GetInFilter(),
				sig_graphemes);
		const int stem_count = string_to_int(stem_count_text);
		const int corpus_count = string_to_int(corpus_count_text);

		// line 2: signature origin
		QString remark = get_line(inf).trimmed();
		remark.replace(QChar('_'), QChar(' '));

		std::auto_ptr<CSignature> sig(new CSignature(
			SigType, m_pMiniLex));
		sig->IngestSignature(sig_text);
		sig->ComputeSignatureVector(m_pMiniLex);
		sig->SetCorpusCount(corpus_count);
		sig->SetRemark(remark);
		sig->SetSignatureCollection(this);

		for (int i = 0; i < stem_count; ++i) {
			QString stem;
			inf >> stem;
			// We haven’t read the Stems.txt file
			// yet, so just swallow each stem here.
			// The stems will be read from Signatures.txt
			// when it is read again in
			// ReadSignatureFileBis.
		}

		CNode* terminal = Insert(sig_text);
		m_PointerArray[GetCount() - 1] = sig.get();
		terminal->SetPointer(sig.release());
	}
} catch (cannot_parse_input) {
	// XXX. report to user
	std::cerr << "Signature.txt: cannot parse" << std::endl;
}
}

void CSignatureCollection::ReadSignatureFileBis(QString Filename) { try
{
	CStemCollection* stems_ptr = m_pMiniLex->GetStems();
	if (stems_ptr == 0)
		return;
	CStemCollection& stems = *stems_ptr;

	QFile file(Filename);
	if (!file.open(QIODevice::ReadOnly))
		return;
	QTextStream inf(&file);

	const int signature_count = string_to_int(
		get_line(inf).trimmed());

	for (int i = 0; i < signature_count; ++i) {
		// see ReadSignatureFile().
		QString sig_header = get_line(inf).trimmed();
		QTextStream line_in(&sig_header, QIODevice::ReadOnly);
		QString sig_graphemes, stem_count_text,
				corpus_count_text;
		line_in >> sig_graphemes >>
			stem_count_text >> corpus_count_text;
		check_end_of_line(line_in);

		const QString sig_text = Filter(m_pLexicon->GetInFilter(),
				sig_graphemes);
		const int stem_count = string_to_int(stem_count_text);

		CParse sig_parse;
		sig_parse.IngestSignature(sig_text);
		CSignature* sig = *this ^= sig_parse;
		Q_ASSERT(sig != 0);

		for (int j = 0; j < stem_count; ++j) {
			QString stem_graphemes;
			inf >> stem_graphemes;

			const QString stem_text = Filter(
				m_pLexicon->GetInFilter(), stem_graphemes);

			CStem* stem = stems ^= stem_text;
			if (stem == 0)
				// XXX. stem missing from Stems.txt
				continue;

			sig->GetStemPtrList()->append(stem);
		}

		if (is_initial(sig->GetAffixLocation())) {
			foreach (CStem* stem, *sig->GetStemPtrList())
				for (int j = 1; j <= sig->Size(); ++j) {
					CPrefix* affix =
						*m_pMiniLex->GetPrefixes() ^=
						sig->GetPiece(i);
					if (affix == 0)
						throw cannot_parse_input();
					affix->AddStem(stem);
				}
		} else {
			foreach (CStem* stem, *sig->GetStemPtrList())
				for (int j = 1; j <= sig->Size(); ++j) {
					CSuffix* affix =
						*m_pMiniLex->GetSuffixes() ^=
						sig->GetPiece(i);
					if (affix == 0)
						throw cannot_parse_input();
					affix->AddStem(stem);
				}
		}
	}
	Sort(SIGS);
} catch (cannot_parse_input) {
	// XXX. report to user
	std::cerr << "Signature.txt: cannot re-parse" << std::endl;
}
}


void CSignatureCollection::CheckRobustness()
{
  CSignature*    pSig, *qSig;
  QString    status;
  status = "Checking sig robustness";
   m_pLexicon->GetDocument()->setStatusBar1 (status);
  Sort (SIGS);
  for (int i = 1; i < (int)GetCount(); i++)
  {
    status = QString("%1").arg(GetCount() - i);
    m_pLexicon->GetDocument()->setStatusBar2( status );
    pSig = GetAtSort(i);
    for (int j = 0; j < i; j++)
    {
      qSig = GetAtSort(j);
      if ( qSig->Contains (pSig) )
      {
        pSig->SetRobustness ( qSig->GetRobustness () );
        break;
      }
    }
  }
  status = "Robustness checking complete.";
  m_pLexicon->GetDocument()->setStatusBar1 (status);
}



int CSignatureCollection::GetTotalNumberOfWords()
{
  int Total = 0;
  for (int i = 0; i < (int)GetCount(); i++)
  {
    Total += GetAt(i)->GetNumberOfStems() * GetAt(i)->Size();
  }
  return Total;
}


int  CSignatureCollection::TheseTwoSuffixesShareHowManyStems(CSuffix* pSuffix1, CSuffix* pSuffix2)
{
  CSignature * pSig;
  int    count = 0;
  for (int i = 0; i < (int)GetCount(); i++)
  {
    pSig= GetAt(i);
    if ( pSig->Contains (pSuffix1) && pSig->Contains (pSuffix2) )
    {
      count+= pSig->GetNumberOfStems();
    }
  }
  return count;
}

void CSignatureCollection::CleanUp()
{
  CSignature* pSig;

  for (int i = 0; i < (int) GetCount(); i++)
  {
    pSig = GetAt(i);
    if ( pSig->GetNumberOfStems() <= 0 || pSig->GetCorpusCount() <= 0 )  // -cs- 20040906 : added the second argument
    {
      // -cs- 20040602 : DeleteMarkedMembers wasn't actually finding any of the 
	  // members to be to be deleted, so I changed it to remove them automatically, 
	  // this fixed our word display bug (words weren't connected to their signature

//      MarkForDeletion(i);
      RemoveMember(pSig);
    }
  }
//  DeleteMarkedMembers();
}



CSignature*  CSignatureCollection::operator<< (CParse* pParse)
{
  CSignature*   pSig;
  CNode*        pTerminal;
  int           Result;
  CSuffix* 	    pSuffix;
  CPrefix*      pPrefix;

  pParse->Alphabetize(); // Jan 2009 JG

  QString       display = pParse->Display('.');
  CParse        SpelledOutSig = CStringSurrogate(display.unicode(),0,display.length());


  pTerminal = Insert (SpelledOutSig.GetKey(), &Result);
  if ( Result == 1)
  {
    pSig = new CSignature( pParse, m_pMiniLex );
    pTerminal->SetPointer( pSig );
    if (m_pMiniLex)
      {
        if (m_SignatureType == WORD_INITIAL ||
            m_SignatureType == STEM_INITIAL)        // Dec 2008
        {
            for (int i = 1; i <= pParse->Size(); i++)
            {
               pPrefix = *m_pMiniLex->GetPrefixes() ^= pParse->GetPiece(i);         
               if(pPrefix) 
               {
                 pSig->GetPrefixPtrList()->append( pPrefix ); 
               }
            }
             
        }
        else
        {
            for (int i = 1; i <= pParse->Size(); i++)
            {
               pSuffix = *m_pMiniLex->GetSuffixes() ^= pParse->GetPiece(i);         
               if(pSuffix) 
               {
                 pSig->GetSuffixPtrList()->append( pSuffix ); 
               }
            }
        }    
    }

  }
  else
  {
    pSig =(CSignature*) pTerminal->Get_T_Pointer();
  }

  if( m_pLexicon ) 
  {
	  switch( m_SignatureType )
	  {
	  case STEM_INITIAL:
	  case WORD_INITIAL:
		  m_pLexicon->InsertPrefixSig( pSig );
		  break;
	  case WORD_FINAL:
	  case STEM_FINAL:
	  default:
		m_pLexicon->InsertSuffixSig( pSig );
	  }
  }

  IncrementCorpusCount(1);
  pSig->IncrementCorpusCount(1);

  m_SortValidFlag      = FALSE;
  m_HashHasChangedFlag  = TRUE;

  pSig->SetLexicon( m_pMiniLex );
  pSig->SetSignatureCollection ( this );

 //todo
  pSig->SetAffixLocation ( m_SignatureType );

  return pSig;


}

CSignature*  CSignatureCollection::operator<< (CSignature* Sig)
{
  CSignature*  pSig;
  CNode*       pTerminal;
  int          Result;
  CSuffix*     pSuffix;
  CPrefix*     pPrefix;
  
  Sig->Alphabetize();

  CParse       SpelledOutSig = CStringSurrogate(Sig->Display('.').unicode(),0,Sig->Display('.').length());

  pTerminal = Insert (SpelledOutSig.GetKey(), &Result);
  if ( Result == 1)
  {
    pSig = new CSignature(*Sig);
    pTerminal->SetPointer (pSig);
    if (m_pMiniLex)
    {if (m_SignatureType == WORD_INITIAL)    
        {
            for (int i = 1; i <= Sig->Size(); i++)
             {
               pPrefix = *m_pMiniLex->GetPrefixes() ^= Sig->GetPiece(i);         
               if(pPrefix) 
               {
                 pSig->GetPrefixPtrList()->append( pPrefix ); 
               }
             }
          }
    } else
    {
        {
            for (int i = 1; i <= Sig->Size(); i++)
             {
               pSuffix = *m_pMiniLex->GetSuffixes() ^= Sig->GetPiece(i);         
               if(pSuffix) 
               {
                 pSig->GetSuffixPtrList()->append( pSuffix ); 
               }
             }
          }
    }
  
  
  
  
  }
  else
  {
    pSig =(CSignature*) pTerminal->Get_T_Pointer();
  }

  if( m_pLexicon ) 
  {
	  switch( m_SignatureType )
	  {
	  case STEM_INITIAL:
	  case WORD_INITIAL:
		  m_pLexicon->InsertPrefixSig( pSig );
		  break;
	  case WORD_FINAL:
	  case STEM_FINAL:
	  default:
		m_pLexicon->InsertSuffixSig( pSig );
	  }
  }
 
  IncrementCorpusCount(1);
  pSig->IncrementCorpusCount(1);

  m_SortValidFlag      = FALSE;
  m_HashHasChangedFlag  = TRUE;

  pSig->SetLexicon( m_pMiniLex );
  pSig->SetSignatureCollection ( this );

   //todo
  pSig->SetAffixLocation ( m_SignatureType );
  return pSig;
}


void CSignatureCollection::AddPointer( CSignature* pSignature )
{
	TCollection<CSignature>::AddPointer( pSignature );

  if( m_pLexicon ) 
  {
	  switch( m_SignatureType )
	  {
	  case STEM_INITIAL:
	  case WORD_INITIAL:
		  m_pLexicon->InsertPrefixSig( pSignature );
		  break;
	  case WORD_FINAL:
	  case STEM_FINAL:
	  default:
		m_pLexicon->InsertSuffixSig( pSignature );
	  }
  }
}


CSignature* CSignatureCollection::AddToCollection( CParse& Signature )
{
	CSignature* pSignature = TCollection<CSignature>::AddToCollection( Signature );

	if( m_pLexicon ) 
	{
		switch( m_SignatureType )
		{
		case STEM_INITIAL:
		case WORD_INITIAL:
			m_pLexicon->InsertPrefixSig( pSignature );
			break;
		case WORD_FINAL:
		case STEM_FINAL:
		default:
			m_pLexicon->InsertSuffixSig( pSignature );
		}
	}

	return pSignature;
}


CSignature* CSignatureCollection::AddToCollection( CStringSurrogate& Signature )
{
	CSignature* pSignature = TCollection<CSignature>::AddToCollection( Signature );

	if( m_pLexicon ) 
	{
		switch( m_SignatureType )
		{
		case STEM_INITIAL:
		case WORD_INITIAL:
			m_pLexicon->InsertPrefixSig( pSignature );
			break;
		case WORD_FINAL:
		case STEM_FINAL:
		default:
			m_pLexicon->InsertSuffixSig( pSignature );
		}
	}

	return pSignature;
}


void CSignatureCollection::Empty()
{
	if( m_pLexicon )
	{
		CSignature* pSignature;

		for( int i = 0; i < GetCount(); i++ )
		{
			pSignature = GetAt(i);

			switch( m_SignatureType )
			{
			case STEM_INITIAL:
			case WORD_INITIAL:
				Q_ASSERT( m_pLexicon->RemovePrefixSig( pSignature ) );
				break;
			case WORD_FINAL:
			case STEM_FINAL:
			default:
				Q_ASSERT( m_pLexicon->RemoveSuffixSig( pSignature ) );
			}
		}
	}

	TCollection<CSignature>::Empty();
}


void CSignatureCollection::RemoveAll()
{
	if( m_pLexicon )
	{
		CSignature* pSignature;

		for( int i = 0; i < GetCount(); i++ )
		{
			pSignature = GetAt(i);

			switch( m_SignatureType )
			{
			case STEM_INITIAL:
			case WORD_INITIAL:
				Q_ASSERT( m_pLexicon->RemovePrefixSig( pSignature ) );
				break;
			case WORD_FINAL:
			case STEM_FINAL:
			default:
				Q_ASSERT( m_pLexicon->RemoveSuffixSig( pSignature ) );
			}
		}
	}

	TCollection<CSignature>::RemoveAll();
}


bool CSignatureCollection::Remove( CSignature* pSignature )
{

	if( m_pLexicon ) 
	{
		switch( m_SignatureType )
		{
		case STEM_INITIAL:
		case WORD_INITIAL:
			Q_ASSERT( m_pLexicon->RemovePrefixSig( pSignature ) );
			break;
		case WORD_FINAL:
		case STEM_FINAL:
		default:
			Q_ASSERT( m_pLexicon->RemoveSuffixSig( pSignature ) );
		}
	}

	return TCollection<CSignature>::Remove( pSignature );
}


bool CSignatureCollection::RemoveMember( CSignature* pSignature )
{

	if( m_pLexicon ) 
	{
		switch( m_SignatureType )
		{
		case STEM_INITIAL:
		case WORD_INITIAL:
			Q_ASSERT( m_pLexicon->RemovePrefixSig( pSignature ) );
			break;
		case WORD_FINAL:
		case STEM_FINAL:
		default:
			Q_ASSERT( m_pLexicon->RemoveSuffixSig( pSignature ) );
		}
	}

	return TCollection<CSignature>::RemoveMember( pSignature );
}


bool CSignatureCollection::RemoveMember( CStringSurrogate& Signature )
{
	CSignature* pSignature = (CSignature*)Find1( Signature )->Get_T_Pointer();

	if( m_pLexicon ) 
	{
		switch( m_SignatureType )
		{
		case STEM_INITIAL:
		case WORD_INITIAL:
			Q_ASSERT( m_pLexicon->RemovePrefixSig( pSignature ) );
			break;
		case WORD_FINAL:
		case STEM_FINAL:
		default:
			Q_ASSERT( m_pLexicon->RemoveSuffixSig( pSignature ) );
		}
	}

	return TCollection<CSignature>::RemoveMember( Signature );
}


bool CSignatureCollection::RemoveMember( CStringSurrogate& Signature, bool b )
{
	CSignature* pSignature = (CSignature*)Find1( Signature )->Get_T_Pointer();

	if( m_pLexicon ) 
	{
		switch( m_SignatureType )
		{
		case STEM_INITIAL:
		case WORD_INITIAL:
			Q_ASSERT( m_pLexicon->RemovePrefixSig( pSignature ) );
			break;
		case WORD_FINAL:
		case STEM_FINAL:
		default:
			Q_ASSERT( m_pLexicon->RemoveSuffixSig( pSignature ) );
		}
	}

	return TCollection<CSignature>::RemoveMember( Signature, b );
}


void CSignatureCollection::DeleteMarkedMembers()
{
	if ( m_DeletionArray == NULL ) { return; }

	int count = GetCount();
	for (int i = 0; i < count; i++)
	{
		if ( m_DeletionArray[i] == 1 )
		{
			if( m_pLexicon ) 
			{
				switch( m_SignatureType )
				{
				case STEM_INITIAL:
				case WORD_INITIAL:
					m_pLexicon->RemovePrefixSig( m_PointerArray[i] );
					break;
				case WORD_FINAL:
				case STEM_FINAL:
				default:
					m_pLexicon->RemoveSuffixSig( m_PointerArray[i] );
				}
			}
		}
	}

	TCollection<CSignature>::DeleteMarkedMembers();
}


void CSignatureCollection::GetIndividualCountsForEachStem ()
{
	CSignature*		pSig;
	int				i;


	for (i = 0; i < GetCount(); i++)
	{
		pSig = GetAt(i);

	}


}

double CSignatureCollection::ComputeDLofInternalPointersOfEachMember(
		enum eMDL_STYLE mdlStyle)
{
	const enum eRecomputeStyle RecomputeFlag = ComputeOnlyIfNecessary;
	
	m_SumOfDLofPointersInternalToEachMember = 0;
	for (int i = 0; i < GetCount(); ++i) {
		CSignature* sig = GetAt(i);

		m_SumOfDLofPointersInternalToEachMember += 
			sig->GetSumOfDLofInternalPointers(
				mdlStyle, RecomputeFlag);
	}
	return m_SumOfDLofPointersInternalToEachMember;
}

// MDL JG August 2006
 double	CSignatureCollection::ComputeLengthOfPointersToEachOfMyMembers (eMDL_STYLE style )
 {
	double			Denominator = 0;
	double			ptr;
	int				i = 0;
					m_DLofPointersToMyMembers = 0;
	
	 
	if (style == CorpusCount )
	{
		for (i = 0; i < GetCount(); i++)
		{
			Denominator += GetAt(i)->GetCorpusCount();
		}
		for (i = 0; i < GetCount(); i++)
		{
			ptr = base2log ( Denominator/ GetAt(i)->GetCorpusCount() );
			GetAt(i)->SetLengthOfPointerToMe (ptr ) ;
			m_DLofPointersToMyMembers += ptr;
		}

	}
	else if (style == GrammarCount )
	{
		for (i = 0; i < GetCount(); i++)
		{
			Denominator += GetAt(i)->GetNumberOfStems() * GetAt(i)->GetNumberOfAffixes();
		}
		for (i = 0; i < GetCount(); i++)
		{
			ptr = base2log ( Denominator/ GetAt(i)->GetCorpusCount() );
			GetAt(i)->SetLengthOfPointerToMe (ptr ) ;
			m_DLofPointersToMyMembers += ptr;
		}
	}
	return m_DLofPointersToMyMembers;
}
///----------------------------------------------------------->>>>>
///----------------------------------------------------------->>>>>
//			Allomorphy
///----------------------------------------------------------->>>>>
void CSignatureCollection::FindAllomorphy()
{
    SignatureAlignment* pSigAlignment;

    if (GetMiniLexicon()->LogFileOn() ) 
    { 
        *GetMiniLexicon()->GetLogFile() <<  LargeTitle("Allomorphy");
     }

	CSignature *pSig, *qSig=NULL;
	int          MinimumNumberOfStems = 15;
	int i, j;

	for (i=0; i < GetCount(); i++)
   {
		    pSig = GetAtSort(i);
		    if (pSig->GetNumberOfStems() < MinimumNumberOfStems ) {continue;}
			if (pSig->Size() < 2 ) {continue;}
			
			for (j = i+1; j < GetCount(); j++)
		    {
	       	       qSig = GetAtSort(j);

                   if (qSig->GetNumberOfStems() < MinimumNumberOfStems ) {continue;}
				   if (qSig->Size() < 2 ) {continue;}

                   pSigAlignment = new SignatureAlignment (pSig, qSig);
                   pSigAlignment->FindBestAlignment(); 
                   if (GetMiniLexicon()->LogFileOn()
					   && pSigAlignment->GetAffixAlignments()->count() > 1)
						{  pSigAlignment->Display( *GetMiniLexicon()->GetLogFile()); }
            }
    }
 }












///----------------------------------------------------------->>>>>
///----------------------------------------------------------->>>>>
