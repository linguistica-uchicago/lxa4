// Implementation of CStemCollection methods
// Copyright © 2009 The University of Chicago
#include "StemCollection.h"

#include <Q3TextStream>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Stem.h"
#include "SignatureCollection.h"
#include "StringSurrogate.h"
#include "Typedefs.h"
#include "implicit_cast.h"
using linguistica::implicit_cast;

namespace {
	typedef TCollection<CStem> base;
}

// construction/destruction.

CStemCollection::CStemCollection()
	: base(),
	m_AffixLocation(WORD_FINAL),
	m_TotalUseCount(0.0) { }

CStemCollection::CStemCollection(CMiniLexicon* Lex)
	: base(Lex, "Stems"),
	m_TotalUseCount(0.0) { }

CStemCollection::~CStemCollection()
{
	if (m_pLexicon != 0)
		for (int i = 0; i < GetCount(); ++i) {
			CStem* pStem = GetAt(i);
			m_pLexicon->RemoveStem(pStem);
		}
}

// Qt3-style collection view.
// see GUIclasses.cpp for CStemCollection::ListDisplay() definition.

// input/output to file.

void CStemCollection::OutputStems(QString FileName)
{
	QFile file( FileName );

	if( file.open( QIODevice::WriteOnly ) )
	{
		Q3TextStream outf( &file );
		outf.setEncoding( Q3TextStream::Unicode );

		outf << "# Stem Count" << endl;
		outf << "# ------------" << endl;
		outf << "  " << GetCount() << endl << endl;

		outf << "# Index | Stem                 | Confidence           | Corpus Count | Affix Count | Affixes " << endl;
		outf << "# ------------------------------------------------------------------------------------------ " << endl;

		Sort( CORPUSCOUNT );
		for (int i = 0; i < (int)GetCount(); i++)
		{
			GetAtSort(i)->OutputStem( outf, i );
		}

		file.close();
	}
}

void CStemCollection::ReadStemFile(QString FileName,
				enum eAffixLocation affixLoc)
{
	CStem*		pStem;
	CSignature*	pSig;
	QFile		file(FileName);
	QString		buffer,
				stem,
				confidence;

	CNode*		pTerminal;

	int			index,
				size,
				corpusCount,
				affixCount,
				lineCount = 0;

	if( file.exists() && file.open( QIODevice::ReadOnly ) )
	{
		Q3TextStream inf(&file);
		inf.setEncoding ( Q3TextStream::Locale );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		inf >> size;

		buffer = inf.readLine(); // end of size line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine(); // blank line
		Q_ASSERT( buffer.length() == 0 );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		buffer = inf.readLine();
		Q_ASSERT( buffer[0] == '#' );

		m_pLexicon->GetDocument()->BeginCountDown();

		while( !inf.atEnd() && lineCount < size )
		{
			m_pLexicon->GetDocument()->CountDownOnStatusBar( lineCount, size );

			lineCount++;

			inf >> index
				>> stem
				>> confidence
				>> corpusCount
				>> affixCount;

			stem = Filter( m_pLexicon->GetInFilter(), stem );
			confidence = confidence.replace( "_", " " );

			pStem = new CStem( CSS( stem ), m_pMiniLex );

			for (int j = 1; j <= affixCount; j++)
			{
				inf >> buffer;

				// Filter all sequences that should be
				// analyzed as one character
				buffer = Filter( m_pLexicon->GetInFilter(), buffer );

				switch( affixLoc )
				{
					case WORD_INITIAL:
					case STEM_INITIAL:
						pStem->GetPrefixList()->Append( buffer );
						break;

					case WORD_FINAL:
					case STEM_FINAL:
					default:
						pStem->GetSuffixList()->Append( buffer );
						break;
				}
			}

			if( affixCount > 0 )
			{
				switch( affixLoc )
				{
					case WORD_INITIAL:
					case STEM_INITIAL:
						pSig = *m_pMiniLex->GetSignatures() ^= pStem->GetPrefixList();
						pStem->SetPrefixSignature( pSig );
						break;

					case WORD_FINAL:
					case STEM_FINAL:
					default:
						pSig = *m_pMiniLex->GetSignatures() ^= pStem->GetSuffixList();
						pStem->SetSuffixSignature( pSig );
						break;
				}
			}

			if( confidence != "NONE" ) pStem->SetConfidence( confidence );

			pStem->SetWordCount( affixCount );
			pStem->SetCorpusCount( corpusCount );

			pTerminal = Insert( CSS( stem ) );
			pTerminal->SetPointer( pStem );
		}

		file.close();
	}
}

// insert.

CStem* CStemCollection::operator<<(const CStem* stem)
{ return operator<<(implicit_cast<const CParse*>(stem)); }

CStem* CStemCollection::operator<<(const CParse* stem)
{
	CStringSurrogate text = stem->GetKey();
	CStem* new_stem = AddToCollection(text);

	QChar* alphabetized_text = LxAlphabetizeString(
					stem->GetKeyPointer(),
					stem->GetKeyLength());
	new_stem->SetAlphabetizedForm(QString(alphabetized_text,
					stem->GetKeyLength()));
	return new_stem;
}

CStem* CStemCollection::operator<<(CStringSurrogate stem_text)
{
	CStem* new_stem = AddToCollection(stem_text);

	QChar* alphabetized_text = LxAlphabetizeString(
					stem_text.Display().unicode(),
					stem_text.GetLength());
	new_stem->SetAlphabetizedForm(QString(alphabetized_text,
					stem_text.GetLength()));
	return new_stem;
}

CStem* CStemCollection::operator<<(QString stem_text)
{
	CStringSurrogate text(stem_text);
	CStem* new_stem = AddToCollection(text);
	QChar* alphabetized_text = LxAlphabetizeString(
					stem_text.unicode(),
					stem_text.length());
	new_stem->SetAlphabetizedForm(QString(alphabetized_text,
					stem_text.length()));
	return new_stem;
}

void CStemCollection::AddPointer(CStem* stem)
{
	base::AddPointer(stem);
	if (m_pLexicon != 0)
		m_pLexicon->InsertStem(stem);
}

CStem* CStemCollection::AddToCollection(const CParse& stem_text)
{
	CStem* new_stem = base::AddToCollection(stem_text);
	if (m_pLexicon != 0)
		m_pLexicon->InsertStem(new_stem);
	return new_stem;
}

CStem* CStemCollection::AddToCollection(const CStringSurrogate& stem_text)
{
	CStem* new_stem = base::AddToCollection(stem_text);
	if (m_pLexicon != 0)
		m_pLexicon->InsertStem(new_stem);
	return new_stem;
}

// clear.

void CStemCollection::Empty()
{
	if (m_pLexicon != 0)
		for (int i = 0; i < GetCount(); ++i) {
			CStem* stem = GetAt(i);
			m_pLexicon->RemoveStem(stem);
		}

	base::Empty();
}

void CStemCollection::RemoveAll()
{
	if (m_pLexicon != 0)
		for (int i = 0; i < GetCount(); ++i) {
			CStem* stem = GetAt(i);
			m_pLexicon->RemoveStem(stem);
		}

	base::RemoveAll();
}

// remove.

bool CStemCollection::Remove(CStem* stem)
{
	if (m_pLexicon != 0)
		m_pLexicon->RemoveStem(stem);
	return base::Remove(stem);
}

bool CStemCollection::RemoveMember(CStem* stem)
{
	if (m_pLexicon != 0)
		m_pLexicon->RemoveStem(stem);
	return base::RemoveMember(stem);
}

bool CStemCollection::RemoveMember(const CStringSurrogate& stem_text)
{
	CStem* stem = static_cast<CStem*>(Find1(stem_text)->Get_T_Pointer());
	return RemoveMember(stem);
}

bool CStemCollection::RemoveMember(const CStringSurrogate& stem_text,
					bool b)
{
	CStem* stem = static_cast<CStem*>(Find1(stem_text)->Get_T_Pointer());
	if (m_pLexicon != 0)
		m_pLexicon->RemoveStem(stem);
	return base::RemoveMember(stem_text, b);
}

void CStemCollection::DeleteMarkedMembers()
{
	// XXX. add hook to base for on-deletion actions so this can
	// be cleaned up.

	if (base::m_DeletionArray == 0)
		return;

	if (m_pLexicon != 0) {
		int count = GetCount();
		for (int i = 0; i < count; ++i)
			if (base::m_DeletionArray[i] == 1)
				 m_pLexicon->RemoveStem(m_PointerArray[i]);
	}
	base::DeleteMarkedMembers();
}

// accessors.

double CStemCollection::GetTotalUseCount()
{
	m_TotalUseCount = 0;

	if (!is_initial(m_AffixLocation))
		for (int i = 0; i < GetCount(); ++i) {
			CStem* stem = GetAt(i);
			m_TotalUseCount += stem->GetNumberOfSuffixes();
		}
	else
		for (int i = 0; i < GetCount(); ++i) {
			CStem* stem = GetAt(i);
			m_TotalUseCount += stem->GetNumberOfPrefixes();
		}
	return m_TotalUseCount;
}

// description length.
// see DescriptionLength.cpp for
// CStemCollection::CalculateTotalPhonologicalInformationContent(),
// CStemCollection::CalculateSumOfPointersToMyStems() definitions.
