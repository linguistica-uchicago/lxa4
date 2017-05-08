// Functions to write morpheme data to files
// Copyright © 2009 The University of Chicago
#include "exportwizard.h"

#include "Config.h"
#include <QFile>
#include <QDir>
#include <Q3TextStream>
#include <QString>
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
#include "WordCollection.h"
#include "StemCollection.h"

void ExportWizard::exportAll()
{
        QString projectName = m_projectName->text();
        projectName.replace( " ", "_" );

        QDir dir( m_outputDirectory->text() );
        dir.mkdir( projectName );
        dir.cd( projectName );

        QDir::setCurrent( dir.path() );

        if( m_markUpFlag->isChecked() ||
                m_bothFlag->isChecked() )
        {
                                                                                                        exportStyleSheet();
                                                                                                        exportIndex();
        }

        if( m_brokenCorpusFlag->isChecked() &&
                m_pLexicon->GetCorpus()->count() )			exportBrokenCorpus();

        if( m_corpusWordsFlag->isChecked() &&
                m_pLexicon->GetWords() &&
                m_pLexicon->GetWords()->GetCount() )		exportCorpusWords();

        if( m_compoundsFlag->isChecked() &&
                m_pLexicon->GetCompounds() &&
                m_pLexicon->GetCompounds()->GetCount() )
        {
                                                                                                        exportCompounds();
                                                                                                        exportLinkers();
        }

        if( m_allWordsFlag->isChecked() &&
                m_pLexicon->GetAllWords() &&
                m_pLexicon->GetAllWords()->count() )		exportAllWords();

        if( m_allStemsFlag->isChecked() &&
                m_pLexicon->GetAllStems() &&
                m_pLexicon->GetAllStems()->count() )		exportAllStems();

        if( m_allSuffixesFlag->isChecked() &&
                m_pLexicon->GetAllSuffixes() &&
                m_pLexicon->GetAllSuffixes()->count() )		exportAllSuffixes();

        if( m_allSuffixSigsFlag->isChecked() &&
                m_pLexicon->GetAllSuffixSigs() &&
                m_pLexicon->GetAllSuffixSigs()->count() )	exportAllSuffixSigs();

        if( m_allPrefixesFlag->isChecked() &&
                m_pLexicon->GetAllPrefixes() &&
                m_pLexicon->GetAllPrefixes()->count() )		exportAllPrefixes();

        if( m_allPrefixSigsFlag->isChecked() &&
                m_pLexicon->GetAllPrefixSigs() &&
                m_pLexicon->GetAllPrefixSigs()->count() )	exportAllPrefixSigs();



        if( m_miniWordsFlag->isChecked() )		exportMiniWords();
        if( m_miniSignaturesFlag->isChecked() ) exportMiniSignatures();
        if( m_miniStemsFlag->isChecked() )		exportMiniStems();
        if( m_miniSuffixesFlag->isChecked() )	exportMiniSuffixes();
        if( m_miniPrefixesFlag->isChecked() )	exportMiniPrefixes();


        // Save settings
        save();
}


void ExportWizard::exportStyleSheet()
{
        QFile* file;
        Q3TextStream* out;

        QString projectName = m_projectName->text();
        projectName.replace( " ", "_" );

        file = new QFile( projectName + ".css" );
        if( file->open( QIODevice::WriteOnly ) )
        {
                // Prepare stream
                out = new Q3TextStream( file );
                out->setEncoding( Q3TextStream::Unicode );

                // BODY
                *out << "BODY\n";
                *out << "{\n";
                *out << "\tmargin : 0px 0px 0px 0px;\n";
                *out << "\tpadding : 0px 0px 0px 0px;\n";
                *out << "}\n\n\n";

                // H1
                *out << "H1\n";
                *out << "{\n";
                *out << "\tleft : 20px;\n";
                *out << "\ttop : 20px;\n";
                *out << "\tfont-family : Arial, Helvetica, sans-serif;\n";
                *out << "\tfont-size : 16px;\n";
                *out << "\tcolor : #FFFFFF;\n";
                *out << "\tfont-weight : bold;\n";
                *out << "\tline-height : 20px;\n";
                *out << "}\n\n\n";

                // H2
                *out << "H2\n";
                *out << "{\n";
                *out << "\tleft : 20px;\n";
                *out << "\tfont-family : Arial, Helvetica, sans-serif;\n";
                *out << "\tfont-size : 12px;\n";
                *out << "\tcolor : #FFFFFF;\n";
                *out << "\tfont-weight : bold;\n";
                *out << "\tline-height : 7px;\n";
                *out << "}\n\n\n";

                // TD
                *out << "TD\n";
                *out << "{\n";
                *out << "\tfont-family : Verdana, Geneva, Arial, Helvetica, sans-serif;\n";
                *out << "\tfont-size : 12px;\n";
                *out << "}\n\n\n";

                // A.top
                *out << "A.top\n";
                *out << "{\n";
                *out << "\tcolor : #E2EAF1;\n";
                *out << "\ttext-decoration : none;\n";
                *out << "\tfont-weight : normal;\n";
                *out << "}\n\n\n";

                // A:HOVER.top
                *out << "A:HOVER.top\n";
                *out << "{\n";
                *out << "\tcolor : #FFFF00;\n";
                *out << "\ttext-decoration : underline;\n";
                *out << "\tfont-weight : normal;\n";
                *out << "}\n\n\n";

                // A.bookmark
                *out << "A.bookmark\n";
                *out << "{\n";
                *out << "\tfont-weight : normal;\n";
                *out << "\ttext-decoration : none;\n";
                *out << "}\n\n\n";

                // A:HOVER.bookmark
                *out << "A:HOVER.bookmark\n";
                *out << "{\n";
                *out << "\tfont-weight : normal;\n";
                *out << "\ttext-decoration : none;\n";
                *out << "}\n\n\n";

                // A.data
                *out << "A.data\n";
                *out << "{\n";
                *out << "\tfont-weight : normal;\n";
                *out << "\tcolor : #000000;\n";
                *out << "\ttext-decoration : none;\n";
                *out << "}\n\n\n";

                // A:HOVER.data
                *out << "A:HOVER.data\n";
                *out << "{\n";
                *out << "\tfont-weight : normal;\n";
                *out << "\ttext-decoration : underline;\n";
                *out << "\tcolor : #CC6600;\n";
                *out << "}\n\n\n";

                // A
                *out << "A\n";
                *out << "{\n";
                *out << "\tcolor : #CC6600;\n";
                *out << "\tfont-weight : bold;\n";
                *out << "\ttext-decoration : none;\n";
                *out << "}\n\n\n";

                // A:HOVER
                *out << "A:HOVER\n";
                *out << "{\n";
                *out << "\ttext-decoration : underline;\n";
                *out << "\tfont-weight : bold;\n";
                *out << "\tcolor : #5A6C7E;\n";
                *out << "}\n\n\n";

                // id = top
                *out << "#top\n";
                *out << "{\n";
                *out << "\tleft : 0px;\n";
                *out << "\ttop : 0px;\n";
                *out << "\twidth : 100%;\n";
                *out << "\tbackground-color : #5A6C7E;\n";
                *out << "\tborder-bottom : 2px solid #1B2025;\n";
                *out << "\tpadding : 10px 10px 10px 10px;\n";
                *out << "\tfont-family : Verdana, Geneva, Arial, Helvetica, sans-serif;\n";
                *out << "\tfont-size : 10px;\n";
                *out << "\tcolor : #FFFFFF;\n";
                *out << "\tfont-weight : bold;\n";
                *out << "}\n\n\n";

                // id = bottom
                *out << "#bottom\n";
                *out << "{\n";
                *out << "\tleft : 0px;\n";
                *out << "\ttop : 70px;\n";
                *out << "\tfont-family : Verdana, Geneva, Arial, Helvetica, sans-serif;\n";
                *out << "\tfont-size : 12px;\n";
                *out << "\tpadding : 10px 10px 10px 10px;\n";
                *out << "}\n\n\n";

                // class = title
                *out << ".title\n";
                *out << "{\n";
                *out << "\tcolor : #1B2025;\n";
                *out << "\tfont-size : 12px;\n";
                *out << "\tfont-weight : bold;\n";
                *out << "}\n\n\n";

                // class = word
                *out << ".word\n";
                *out << "{\n";
                *out << "\tcolor : " + m_wordStyle->paletteForegroundColor().name() + ";\n";
                if( m_wordStyle->font().bold() ) *out << "\tfont-weight : bold;\n";
                if( m_wordStyle->font().italic() ) *out << "\tfont-style : italic;\n";
                *out << "}\n\n\n";

                // class = stem
                *out << ".stem\n";
                *out << "{\n";
                *out << "\tcolor : " + m_stemStyle->paletteForegroundColor().name() + ";\n";
                if( m_stemStyle->font().bold() ) *out << "\tfont-weight : bold;\n";
                if( m_stemStyle->font().italic() ) *out << "\tfont-style : italic;\n";
                *out << "}\n\n\n";

                // class = suffix
                *out << ".suffix\n";
                *out << "{\n";
                *out << "\tcolor : " + m_suffixStyle->paletteForegroundColor().name() + ";\n";
                if( m_suffixStyle->font().bold() ) *out << "\tfont-weight : bold;\n";
                if( m_suffixStyle->font().italic() ) *out << "\tfont-style : italic;\n";
                *out << "}\n\n\n";

                // class = prefix
                *out << ".prefix\n";
                *out << "{\n";
                *out << "\tcolor : " + m_prefixStyle->paletteForegroundColor().name() + ";\n";
                if( m_prefixStyle->font().bold() ) *out << "\tfont-weight : bold;\n";
                if( m_prefixStyle->font().italic() ) *out << "\tfont-style : italic;\n";
                *out << "}\n\n\n";

                // class = signature
                *out << ".signature\n";
                *out << "{\n";
                *out << "\tcolor : " + m_signatureStyle->paletteForegroundColor().name() + ";\n";
                if( m_signatureStyle->font().bold() ) *out << "\tfont-weight : bold;\n";
                if( m_signatureStyle->font().italic() ) *out << "\tfont-style : italic;\n";
                *out << "}\n\n\n";

                // class = compound
                *out << ".compound\n";
                *out << "{\n";
                *out << "\tcolor : " + m_compoundStyle->paletteForegroundColor().name() + ";\n";
                if( m_compoundStyle->font().bold() ) *out << "\tfont-weight : bold;\n";
                if( m_compoundStyle->font().italic() ) *out << "\tfont-style : italic;\n";
                *out << "}\n\n\n";

                file->close();
                delete file; file = NULL;
                delete out;	out = NULL;
        }
}


void ExportWizard::exportBrokenCorpus()
{
        QFile* file;
        Q3TextStream* out;

        CCorpusWord* pCorpusWord;

        StringToString* filter = m_pLexicon->GetOutFilter();

        CLParse* pLParse;

        QString fileName = m_projectName->text() + "_" + BROKEN_CORPUS_FILE_TITLE,
                        word, url;

        bool do_not_link_words = !m_allWordsFlag->isChecked() || m_allWordsAnalyzedOnlyFlag->isChecked();

        fileName.replace( " ", "_" );

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        for( QStringList::Iterator lineIt = m_pLexicon->GetCorpus()->begin(); lineIt != m_pLexicon->GetCorpus()->end(); ++lineIt )
                        {
                                QStringList line = QStringList::split( " ", *lineIt );

                                for( QStringList::Iterator wordIt = line.begin(); wordIt != line.end(); ++wordIt )
                                {
                                        pCorpusWord = m_pLexicon->GetCorpusMap()->find( *wordIt );

                                        if( pCorpusWord ) *out << pCorpusWord->Display( '+', filter ) << " ";
                                        else *out << *wordIt << " ";
                                }

                                *out << endl;
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), BROKEN_CORPUS_FILE_TITLE, m_language->text(), m_researchers->text() );

                        for( QStringList::Iterator lineIt = m_pLexicon->GetCorpus()->begin(); lineIt != m_pLexicon->GetCorpus()->end(); ++lineIt )
                        {
                                if( (*lineIt).length() == 0 ) continue;

                                QStringList line = QStringList::split( " ", *lineIt );

                                *out << "\t\t\t<p>";

                                for( QStringList::Iterator wordIt = line.begin(); wordIt != line.end(); ++wordIt )
                                {
                                        pCorpusWord = m_pLexicon->GetCorpusMap()->find( *wordIt );

                                        word = "";

                                        if( pCorpusWord )
                                        {
                                                if( pCorpusWord->Size() > 1 )
                                                {
                                                        for( int i = 1; i < pCorpusWord->Size(); i++ )
                                                        {
                                                                // All but the last piece with following delimiter
                                                                pLParse = pCorpusWord->GetMorpheme(i);
                                                                if( !pLParse ) continue;

                                                                word += getLParseText( pLParse, TRUE );

                                                                word += "+";
                                                        }

                                                        // Last piece
                                                        pLParse = pCorpusWord->GetMorpheme( pCorpusWord->Size() );
                                                        if( pLParse ) word += getLParseText( pLParse, TRUE );
                                                }
                                                else
                                                {
                                                        // If it's one piece we force mark it as a word
                                                        pLParse = pCorpusWord->GetMorpheme(1);
                                                        if( !pLParse ) continue;

                                                        url = m_projectName->text() + "_" + ALL_WORDS_FILE_TITLE + ".html";
                                                        url.replace( " ", "_" );
                                                        word += getLParseText( pLParse, TRUE, do_not_link_words, "word", url );
                                                }

                                                *out << word << " ";
                                        }
                                        else
                                        {
                                                *out << *wordIt << " ";
                                        }
                                }

                                *out << "</p>\n";
                        }

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportCorpusWords()
{
        QFile* file;
        Q3TextStream* out;

        CCorpusWord* pCorpusWord;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, start, end, index;

        int i;

        QString line, field,
                        fileName = m_projectName->text() + "_" + CORPUS_WORDS_FILE_TITLE;

        fileName.replace( " ", "_" );

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_corpusWordsUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_corpusWordsColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[WORD_FIELD] = WORD_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[MORPHS_COUNT_FIELD] = MORPHS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[MORPHS_FIELD] = MORPHS_FIELD_TITLE.length();
                                }

                                m_pLexicon->GetWords()->Sort(PARSE_SIZE);
                                for( i = 0; i < m_pLexicon->GetWords()->GetCount(); i++ )
                                {
                                        pCorpusWord = m_pLexicon->GetWords()->GetAtSort(i);

                                        if( m_corpusWordsLine->text().find( INDEX_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg(i).length();
                                                if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                        }
                                        if( m_corpusWordsLine->text().find( WORD_FIELD ) >= 0 )
                                        {
                                                width = pCorpusWord->Display( filter ).length();
                                                if( width > fieldWidths[WORD_FIELD] ) fieldWidths[WORD_FIELD] = width;
                                        }
                                        if( m_corpusWordsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCorpusWord->GetCorpusCount() ).length();
                                                if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                        }
                                        if( m_corpusWordsLine->text().find( MORPHS_COUNT_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCorpusWord->Size() ).length();
                                                if( width > fieldWidths[MORPHS_COUNT_FIELD] ) fieldWidths[MORPHS_COUNT_FIELD] = width;
                                        }
                                        if( m_corpusWordsLine->text().find( MORPHS_FIELD ) >= 0 )
                                        {
                                                width = getCorpusWordMorphsField( pCorpusWord ).length();
                                                if( width > fieldWidths[MORPHS_FIELD] ) fieldWidths[MORPHS_FIELD] = width;
                                        }
                                }
                        }


                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_corpusWordsColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_corpusWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[WORD_FIELD] );
                                                *out << WORD_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_COUNT_FIELD] );
                                                *out << MORPHS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_FIELD] );
                                                *out << MORPHS_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }


                        // Sort appropriately
                        if( m_corpusWordsMorphemeCountSortFlag->isChecked() ) m_pLexicon->GetWords()->Sort(PARSE_SIZE);
                        else if( m_corpusWordsCorpusCountSortFlag->isChecked() ) m_pLexicon->GetWords()->Sort(CORPUSCOUNT);
                        else m_pLexicon->GetWords()->Sort(KEY);

                        // Output text file stuff
                        index = 1;
                        for( i = 0; i < m_pLexicon->GetWords()->GetCount(); i++ )
                        {
                                pCorpusWord = m_pLexicon->GetWords()->GetAtSort(i);

                                if( m_corpusWordsAnalyzedOnlyFlag->isChecked() && pCorpusWord->Size() < 2 ) continue;

                                if( m_corpusWordsColumnTitlesFlag->isChecked() ) *out << "  ";

                                line = m_corpusWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << index++;
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[WORD_FIELD] );
                                                *out << pCorpusWord->Display( filter );
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << pCorpusWord->GetCorpusCount();
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_COUNT_FIELD] );
                                                *out << pCorpusWord->Size();
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_FIELD] );
                                                *out << getCorpusWordMorphsField( pCorpusWord );
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), CORPUS_WORDS_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_corpusWordsColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_corpusWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << WORD_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MORPHS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << MORPHS_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }


                        // Sort appropriately
                        if( m_corpusWordsMorphemeCountSortFlag->isChecked() ) m_pLexicon->GetWords()->Sort(PARSE_SIZE);
                        else if( m_corpusWordsCorpusCountSortFlag->isChecked() ) m_pLexicon->GetWords()->Sort(CORPUSCOUNT);
                        else m_pLexicon->GetWords()->Sort(KEY);


                        // Output html file stuff
                        index = 1;
                        for( i = 0; i < m_pLexicon->GetWords()->GetCount(); i++ )
                        {
                                pCorpusWord = m_pLexicon->GetWords()->GetAtSort(i);

                                if( m_corpusWordsAnalyzedOnlyFlag->isChecked() && pCorpusWord->Size() < 2 ) continue;

                                *out << "\t\t\t\t<tr>\n";

                                line = m_corpusWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << index++ << "</td>\n";
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pCorpusWord->Display( filter ) << "</td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << QString( "%1" ).arg( pCorpusWord->GetCorpusCount() ) << "</td>\n";
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << QString( "%1" ).arg( pCorpusWord->Size() ) << "</td>\n";
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getCorpusWordMorphsField( pCorpusWord, TRUE ) << "</td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";

                                if( index % 20 == 0 )
                                {
                                        *out << "\t\t\t\t<tr>\n";
                                        *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_corpusWordsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                        *out << "\t\t\t\t</tr>\n";
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportCompounds()
{
        QFile* file;
        Q3TextStream* out;

        CCompound* pCompound;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, start, end, index;

        int i;

        QString line, field,
                        fileName = m_projectName->text() + "_" + COMPOUNDS_FILE_TITLE,
                        projectName = m_projectName->text();

        projectName.replace( " ", "_" );
        fileName.replace( " ", "_" );

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_compoundsUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_compoundsColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[COMPOUND_FIELD] = COMPOUND_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[MORPHS_COUNT_FIELD] = MORPHS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[MORPHS_FIELD] = MORPHS_FIELD_TITLE.length();
                                        fieldWidths[SUFFIXNESS_FIELD] = SUFFIXNESS_FIELD_TITLE.length();
                                        fieldWidths[PREFIXNESS_FIELD] = PREFIXNESS_FIELD_TITLE.length();
                                        fieldWidths[PARSE_FIELD] = PARSE_FIELD_TITLE.length();
                                }

                                m_pLexicon->GetCompounds()->Sort(PARSE_SIZE);
                                for( i = 0; i < m_pLexicon->GetCompounds()->GetCount(); i++ )
                                {
                                        pCompound = m_pLexicon->GetCompounds()->GetAtSort(i);

                                        if( m_compoundsLine->text().find( INDEX_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg(i).length();
                                                if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( COMPOUND_FIELD ) >= 0 )
                                        {
                                                width = pCompound->Display( filter ).length();
                                                if( width > fieldWidths[COMPOUND_FIELD] ) fieldWidths[COMPOUND_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCompound->GetCorpusCount() ).length();
                                                if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( MORPHS_COUNT_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCompound->Size() ).length();
                                                if( width > fieldWidths[MORPHS_COUNT_FIELD] ) fieldWidths[MORPHS_COUNT_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( MORPHS_FIELD ) >= 0 )
                                        {
                                                width = getCompoundMorphsField( pCompound ).length();
                                                if( width > fieldWidths[MORPHS_FIELD] ) fieldWidths[MORPHS_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( SUFFIXNESS_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCompound->GetSuffixness() ).length();
                                                if( width > fieldWidths[SUFFIXNESS_FIELD] ) fieldWidths[SUFFIXNESS_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( PREFIXNESS_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCompound->GetPrefixness() ).length();
                                                if( width > fieldWidths[PREFIXNESS_FIELD] ) fieldWidths[PREFIXNESS_FIELD] = width;
                                        }
                                        if( m_compoundsLine->text().find( PARSE_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pCompound->DisplayBestParse( filter ) ).length();
                                                if( width > fieldWidths[PARSE_FIELD] ) fieldWidths[PARSE_FIELD] = width;
                                        }
                                }
                        }


                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_compoundsColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_compoundsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == COMPOUND_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[COMPOUND_FIELD] );
                                                *out << COMPOUND_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_COUNT_FIELD] );
                                                *out << MORPHS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_FIELD] );
                                                *out << MORPHS_FIELD_TITLE;
                                        }
                                        if( field == SUFFIXNESS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIXNESS_FIELD] );
                                                *out << SUFFIXNESS_FIELD_TITLE;
                                        }
                                        if( field == PREFIXNESS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIXNESS_FIELD] );
                                                *out << PREFIXNESS_FIELD_TITLE;
                                        }
                                        if( field == PARSE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PARSE_FIELD] );
                                                *out << PARSE_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }


                        // Sort appropriately
                        if( m_compoundsMorphemeCountSortFlag->isChecked() ) m_pLexicon->GetCompounds()->Sort(PARSE_SIZE);
                        else if( m_compoundsCorpusCountSortFlag->isChecked() ) m_pLexicon->GetCompounds()->Sort(CORPUSCOUNT);
                        else m_pLexicon->GetCompounds()->Sort(KEY);

                        // Output text file stuff
                        index = 1;
                        for( i = 0; i < m_pLexicon->GetCompounds()->GetCount(); i++ )
                        {
                                pCompound = m_pLexicon->GetCompounds()->GetAtSort(i);

                                if( m_compoundsColumnTitlesFlag->isChecked() ) *out << "  ";

                                line = m_compoundsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << index++;
                                        }
                                        if( field == COMPOUND_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[COMPOUND_FIELD] );
                                                *out << pCompound->Display( filter );
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << pCompound->GetCorpusCount();
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_COUNT_FIELD] );
                                                *out << pCompound->Size();
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MORPHS_FIELD] );
                                                *out << getCompoundMorphsField( pCompound );
                                        }
                                        if( field == SUFFIXNESS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIXNESS_FIELD] );
                                                *out << pCompound->GetSuffixness();
                                        }
                                        if( field == PREFIXNESS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIXNESS_FIELD] );
                                                *out << pCompound->GetPrefixness();
                                        }
                                        if( field == PARSE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PARSE_FIELD] );
                                                *out << pCompound->DisplayBestParse( filter );
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), COMPOUNDS_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_compoundsColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_compoundsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == COMPOUND_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << COMPOUND_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MORPHS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << MORPHS_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SUFFIXNESS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SUFFIXNESS_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == PREFIXNESS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << PREFIXNESS_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == PARSE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << PARSE_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }


                        // Sort appropriately
                        if( m_compoundsMorphemeCountSortFlag->isChecked() ) m_pLexicon->GetCompounds()->Sort(PARSE_SIZE);
                        else if( m_compoundsCorpusCountSortFlag->isChecked() ) m_pLexicon->GetCompounds()->Sort(CORPUSCOUNT);
                        else m_pLexicon->GetCompounds()->Sort(KEY);

                        QDir dir( m_outputDirectory->text() );
                        dir.cd( projectName );
                        if( m_compoundsLine->text().contains( PARSE_FIELD ) ) dir.mkdir( "images" );

                        QString picName;

                        CanvasDialog* canvasDlg = new CanvasDialog( this,
                                                        Qt::WStyle_Customize |
                                                        Qt::WStyle_NormalBorder |
                                                        Qt::WStyle_Title |
                                                        Qt::WStyle_SysMenu );

                        // Output html file stuff
                        index = 1;
                        for( i = 0; i < m_pLexicon->GetCompounds()->GetCount(); i++ )
                        {
                                pCompound = m_pLexicon->GetCompounds()->GetAtSort(i);

                                if( m_compoundsLine->text().contains( PARSE_FIELD ) )
                                {
                                        picName = pCompound->Display( filter );

                                        // Remove Windows' illegal file characters
                                        picName.remove( "\\" );
                                        picName.remove( "/" );
                                        picName.remove( ":" );
                                        picName.remove( "*" );
                                        picName.remove( "?" );
                                        picName.remove( "\"" );
                                        picName.remove( "<" );
                                        picName.remove( ">" );
                                        picName.remove( "|" );

                                        saveParseImage( pCompound->GetParse( pCompound->GetBestParse() ),
                                                                        "images/" + picName + ".png", canvasDlg );
                                }

                                *out << "\t\t\t\t<tr>\n";

                                line = m_compoundsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << index++ << "</td>\n";
                                        }
                                        if( field == COMPOUND_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\"><a name=\"_" << pCompound->Display(  filter  ) << "_\" class=\"bookmark\">" << getLParseText( pCompound, TRUE, TRUE ) << "</a></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << QString( "%1" ).arg( pCompound->GetCorpusCount() ) << "</td>\n";
                                        }
                                        if( field == MORPHS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << QString( "%1" ).arg( pCompound->Size() ) << "</td>\n";
                                        }
                                        if( field == MORPHS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getCompoundMorphsField( pCompound, TRUE ) << "</td>\n";
                                        }
                                        if( field == SUFFIXNESS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << QString( "%1" ).arg( pCompound->GetSuffixness() ) << "</td>\n";
                                        }
                                        if( field == PREFIXNESS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << QString( "%1" ).arg( pCompound->GetPrefixness() ) << "</td>\n";
                                        }
                                        if( field == PARSE_FIELD )
                                        {
                                                picName = pCompound->Display(  filter  );

                                                // Remove Windows' illegal file characters
                                                picName.remove( "\\" );
                                                picName.remove( "/" );
                                                picName.remove( ":" );
                                                picName.remove( "*" );
                                                picName.remove( "?" );
                                                picName.remove( "\"" );
                                                picName.remove( "<" );
                                                picName.remove( ">" );
                                                picName.remove( "|" );

                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\"><img src=\"images/" << picName << ".png\" border=\"0\" /></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";

                                if( index % 20 == 0 )
                                {
                                        *out << "\t\t\t\t<tr>\n";
                                        *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_compoundsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                        *out << "\t\t\t\t</tr>\n";
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                        delete canvasDlg; canvasDlg = NULL;
                }
        }
}


void ExportWizard::exportLinkers()
{
        QFile* file;
        Q3TextStream* out;

        CLinker* pLinker;
        CCompound* pCompound;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int i, j,
                width, start,
                end, index,
                count;

        QString line, field, fileName, url, type = "compound";

        fileName = m_projectName->text() + "_" + LINKERS_FILE_TITLE;
        fileName.replace( " ", "_" );

        url = m_projectName->text() + "_" + COMPOUNDS_FILE_TITLE + ".html";
        url.replace( " ", "_" );

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_linkersUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_linkersColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[LINKER_FIELD] = LINKER_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[COMPOUND_COUNT_FIELD] = COMPOUND_COUNT_FIELD_TITLE.length();
                                        if( m_linkersIncludeCompoundListFlag->isChecked() ) fieldWidths[COMPOUNDS_FIELD] = 0;
                                }

                                m_pLexicon->GetLinkers()->Sort(PARSE_SIZE);
                                for( i = 0; i < m_pLexicon->GetLinkers()->GetCount(); i++ )
                                {
                                        pLinker = m_pLexicon->GetLinkers()->GetAtSort(i);

                                        if( m_linkersLine->text().find( INDEX_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( i + 1 ).length();
                                                if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                        }
                                        if( m_linkersLine->text().find( LINKER_FIELD ) >= 0 )
                                        {
                                                width = pLinker->Display(  filter  ).length();
                                                if( width > fieldWidths[LINKER_FIELD] ) fieldWidths[LINKER_FIELD] = width;
                                        }
                                        if( m_linkersLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pLinker->GetCorpusCount() ).length();
                                                if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                        }
                                        if( m_linkersLine->text().find( COMPOUND_COUNT_FIELD ) >= 0 )
                                        {
                                                width = QString( "%1" ).arg( pLinker->GetCompoundCount() ).length();
                                                if( width > fieldWidths[COMPOUND_COUNT_FIELD] ) fieldWidths[COMPOUND_COUNT_FIELD] = width;
                                        }
                                        if( m_linkersIncludeCompoundListFlag->isChecked() )
                                        {
                                                width = 0;
                                                for( j = 0; j < pLinker->GetNumberOfCompounds(); j++ )
                                                {
                                                        pCompound = pLinker->GetAtCompound(j);

                                                        if( width < static_cast <int> (pCompound->Display(  filter  ).length() ) ) width = static_cast <int> (pCompound->Display(  filter  ).length());
                                                }
                                                if( width > fieldWidths[COMPOUNDS_FIELD] ) fieldWidths[COMPOUNDS_FIELD] = width;
                                        }
                                }
                        }


                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_linkersColumnTitlesFlag->isChecked() )

                        *out << "# ";

                        line = m_linkersLine->text();

                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                        while( line.length() > 0 )
                        {
                                start = line.find( "%" );

                                if( start < 0 )
                                {
                                        *out << line;
                                        break;
                                }

                                *out << line.left( start );
                                line = line.mid( start );
                                end = line.find( "%", 1 );
                                field = line.mid( 0, end + 1 );

                                if( field == INDEX_FIELD )
                                {
                                        out->unsetf(2);
                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                        *out << INDEX_FIELD_TITLE;
                                }
                                if( field == LINKER_FIELD )
                                {
                                        out->setf(2);
                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[LINKER_FIELD] );
                                        *out << LINKER_FIELD_TITLE;
                                }
                                if( field == CORPUS_COUNT_FIELD )
                                {
                                        out->unsetf(2);
                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                        *out << CORPUS_COUNT_FIELD_TITLE;
                                }
                                if( field == COMPOUND_COUNT_FIELD )
                                {
                                        out->unsetf(2);
                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[COMPOUND_COUNT_FIELD] );
                                        *out << COMPOUND_COUNT_FIELD_TITLE;
                                }

                                line = line.mid( end + 1 );
                        }

                        *out << endl;


                        // Sort appropriately
                        if( m_linkersCorpusCountSortFlag->isChecked() ) m_pLexicon->GetLinkers()->Sort(CORPUSCOUNT);
                        else m_pLexicon->GetLinkers()->Sort(KEY);

                        // Output text file stuff
                        index = 1;
                        for( i = 0; i < m_pLexicon->GetLinkers()->GetCount(); i++ )
                        {
                                pLinker = m_pLexicon->GetLinkers()->GetAtSort(i);

                                if( m_linkersColumnTitlesFlag->isChecked() ) *out << "  ";

                                line = m_linkersLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << index++;
                                        }
                                        if( field == LINKER_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[LINKER_FIELD] );
                                                *out << pLinker->Display(  filter  );
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << pLinker->GetCorpusCount();
                                        }
                                        if( field == COMPOUND_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[COMPOUND_COUNT_FIELD] );
                                                *out << pLinker->GetCompoundCount();
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;

                                if( m_linkersIncludeCompoundListFlag->isChecked() )
                                {
                                        count = 0;
                                        if( m_linkersColumnTitlesFlag->isChecked() )
                                        {
                                                *out << "# " << COMPOUNDS_FIELD_TITLE << endl;
                                                *out << "# -------------------------------------------\n";
                                        }

                                        for( j = 0; j < pLinker->GetNumberOfCompounds(); j++ )
                                        {
                                                pCompound = pLinker->GetAtCompound(j);

                                                if( count % 5 == 0 )
                                                {
                                                        *out << endl;

                                                        if( m_linkersColumnTitlesFlag->isChecked() ) *out << "  ";
                                                }

                                                out->setf(2);
                                                out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                *out << pCompound->Display(  filter  );
                                                count++;
                                        }

                                        *out << "\n\n\n";
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), LINKERS_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_linkersColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_linkersLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == LINKER_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << LINKER_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == COMPOUND_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << COMPOUND_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }


                        // Sort appropriately
                        if( m_linkersCorpusCountSortFlag->isChecked() ) m_pLexicon->GetLinkers()->Sort(CORPUSCOUNT);
                        else m_pLexicon->GetLinkers()->Sort(KEY);


                        // Output html file stuff
                        index = 1;
                        for( i = 0; i < m_pLexicon->GetLinkers()->GetCount(); i++ )
                        {
                                pLinker = m_pLexicon->GetLinkers()->GetAtSort(i);

                                *out << "\t\t\t\t<tr>\n";

                                line = m_linkersLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td";
                                                if( !m_linkersIncludeCompoundListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                *out << ">" << index++ << "</td>\n";
                                        }
                                        if( field == LINKER_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td";
                                                if( !m_linkersIncludeCompoundListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                *out << ">" << "<a name=\"_" << pLinker->Display(  filter  ) << "_\" class=\"bookmark\">" << getLParseText( pLinker, TRUE, TRUE ) << "</a></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td";
                                                if( !m_linkersIncludeCompoundListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                *out << " align=\"center\">" << pLinker->GetCorpusCount() << "</td>\n";
                                        }
                                        if( field == COMPOUND_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td";
                                                if( !m_linkersIncludeCompoundListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                *out << " align=\"center\">" << pLinker->GetCompoundCount() << "</td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";

                                if( m_linkersIncludeCompoundListFlag->isChecked() )
                                {
                                        *out << "\t\t\t\t<tr>\n";
                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_linkersLine->text().count( "%" ) / 2 ) << "\">\n";
                                        *out << "\t\t\t\t\t\t<span class=\"title\">" << COMPOUNDS_FIELD_TITLE << "</span><br>\n";
                                        *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                        count = 0;
                                        *out << "\t\t\t\t\t\t\t<tr>\n";
                                        for( j = 0; j < pLinker->GetNumberOfCompounds(); j++ )
                                        {
                                                pCompound = pLinker->GetAtCompound(j);

                                                if( count > 0 && count % 5 == 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t</tr>\n";
                                                        *out << "\t\t\t\t\t\t\t<tr>\n";
                                                }

                                                *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pCompound, TRUE, FALSE ) << "</td>\n";
                                                count++;
                                        }
                                        while( count > 5 && count % 5 != 0 )
                                        {
                                                *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                count++;
                                        }

                                        *out << "\t\t\t\t\t\t\t</tr>\n";

                                        *out << "\t\t\t\t\t\t</table><br>\n";
                                        *out << "\t\t\t\t\t</td>\n";
                                        *out << "\t\t\t\t</tr>\n";
                                }

                                if( index % 20 == 0 )
                                {
                                        *out << "\t\t\t\t<tr>\n";
                                        *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_linkersLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                        *out << "\t\t\t\t</tr>\n";
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportAllWords()
{
        QFile* file;
        Q3TextStream* out;

        StemSet* pWords;

        CStem* pWord;
        CSignature* pSig;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, start, end, index;

        QString line, field,
                        fileName = m_projectName->text() + "_" + ALL_WORDS_FILE_TITLE;

        QStringList alphabetized;

        fileName.replace( " ", "_" );

        Q3DictIterator<StemSet> it( *m_pLexicon->GetAllWords() );

        // Get all words for alphabetization
        for( ; it.current(); ++it )
        {
                alphabetized.append( it.currentKey() );
        }

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_allWordsUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_allWordsColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[WORD_FIELD] = WORD_FIELD_TITLE.length();
                                        fieldWidths[MINI_LEX_FIELD] = MINI_LEX_FIELD_TITLE.length();
                                        fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[TYPE_FIELD] = TYPE_FIELD_TITLE.length();
                                        fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                        fieldWidths[SOURCE_FIELD] = SOURCE_FIELD_TITLE.length();
                                        fieldWidths[PREFIX_FIELD] = PREFIX_FIELD_TITLE.length();
                                        fieldWidths[STEM_FIELD] = STEM_FIELD_TITLE.length();
                                        fieldWidths[SUFFIX_FIELD] = SUFFIX_FIELD_TITLE.length();
                                }

                                index = 0;
                                it.toFirst();
                                for( ; it.current(); ++it )
                                {
                                        pWords = it.current();

                                        //for( pWord = pWords->first(); pWord; pWord = pWords->next() )
                                        for (int z = 0; z < pWords->size(); z++)
                                        {       pWord = pWords->at(z);
                                                if( m_allWordsAnalyzedOnlyFlag->isChecked() && pWord->Size() < 2 ) continue;

                                                index++;

                                                if( pWord->Size() > 1 )
                                                {
                                                        pSig = pWord->GetSuffixSignature();
                                                        if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
                                                }
                                                else pSig = NULL;

                                                if( m_allWordsLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( index ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( WORD_FIELD ) >= 0 )
                                                {
                                                        width = pWord->Display(  filter  ).length();
                                                        if( width > fieldWidths[WORD_FIELD] ) fieldWidths[WORD_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( MINI_LEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pWord->GetMyMini()->GetIndex() + 1 + 1 ).length();
                                                        if( width > fieldWidths[MINI_LEX_FIELD] ) fieldWidths[MINI_LEX_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pWord->CalculateDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pWord->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( TYPE_FIELD ) >= 0 )
                                                {
                                                        width = pWord->DisplayStemType().length();
                                                        if( width > fieldWidths[TYPE_FIELD] ) fieldWidths[TYPE_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->Display( '.', filter ).length();
                                                        else width = 0;
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( SOURCE_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->GetRemark().length();
                                                        else width = pWord->GetConfidence().length();
                                                        if( width > fieldWidths[SOURCE_FIELD] ) fieldWidths[SOURCE_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( PREFIX_FIELD ) >= 0 )
                                                {
                                                        width = pWord->GetPiece( pWord->GetPrefixLoc() ).Display( filter ).length();
                                                        if( width > fieldWidths[PREFIX_FIELD] ) fieldWidths[PREFIX_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( STEM_FIELD ) >= 0 )
                                                {
                                                        width = pWord->GetStem().Display( filter ).length();
                                                        if( width > fieldWidths[STEM_FIELD] ) fieldWidths[STEM_FIELD] = width;
                                                }
                                                if( m_allWordsLine->text().find( SUFFIX_FIELD ) >= 0 )
                                                {
                                                        width = pWord->GetPiece( pWord->GetSuffixLoc() ).Display( filter ).length();
                                                        if( width > fieldWidths[SUFFIX_FIELD] ) fieldWidths[SUFFIX_FIELD] = width;
                                                }
                                        }
                                }
                        }


                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_allWordsColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_allWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[WORD_FIELD] );
                                                *out << WORD_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                *out << MINI_LEX_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == TYPE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                *out << TYPE_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == SOURCE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SOURCE_FIELD] );
                                                *out << SOURCE_FIELD_TITLE;
                                        }
                                        if( field == PREFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                *out << PREFIX_FIELD_TITLE;
                                        }
                                        if( field == STEM_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                *out << STEM_FIELD_TITLE;
                                        }
                                        if( field == SUFFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                *out << SUFFIX_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output text file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pWords = ( *m_pLexicon->GetAllWords() )[ *sIt ];

                                for (int z = 0; z < pWords->size(); z++)
                                {       pWord = pWords->at(z);
                                        if( m_allWordsAnalyzedOnlyFlag->isChecked() && pWord->Size() < 2 ) continue;

                                        index++;

                                        if( m_allWordsColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_allWordsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        if( pWord->Size() > 1 )
                                        {
                                                pSig = pWord->GetSuffixSignature();
                                                if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
                                        }
                                        else pSig = NULL;

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index;
                                                }
                                                if( field == WORD_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[WORD_FIELD] );
                                                        *out << pWord->Display(  filter  );
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pWord->GetCorpusCount();
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                        *out << pWord->GetMyMini()->GetIndex() + 1 + 1;
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pWord->CalculateDL();
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                        *out << pWord->DisplayStemType();
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        if( pSig ) *out << getLParseText( pSig );
                                                        else *out << " ";
                                                }
                                                if( field == SOURCE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SOURCE_FIELD] );
                                                        if( pSig ) *out << pSig->GetRemark();
                                                        else *out << pWord->GetConfidence();
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                        *out << pWord->GetPiece( pWord->GetPrefixLoc() ).Display( filter );
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                        *out << pWord->GetStem().Display( filter );
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                        *out << pWord->GetPiece( pWord->GetSuffixLoc() ).Display( filter );
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                QString url;

                bool do_not_link_words = !m_miniWordsFlag->isChecked() || m_miniWordsAnalyzedOnlyFlag->isChecked();

                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), ALL_WORDS_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_allWordsColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_allWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << WORD_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MINI_LEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == TYPE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << TYPE_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SOURCE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SOURCE_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == PREFIX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << PREFIX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == STEM_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << STEM_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SUFFIX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SUFFIX_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output html file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pWords = ( *m_pLexicon->GetAllWords() )[ *sIt ];
                                for (int y = 0; y < pWords->size(); y++)
                                {       pWords->at(y);
                                        if( m_allWordsAnalyzedOnlyFlag->isChecked() && pWord->Size() < 2 ) continue;

                                        *out << "\t\t\t\t<tr>\n";

                                        index++;

                                        line = m_allWordsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        if( pWord->Size() > 1 )
                                        {
                                                pSig = pWord->GetSuffixSignature();
                                                if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
                                        }
                                        else pSig = NULL;

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << index << "</td>\n";
                                                }
                                                if( field == WORD_FIELD )
                                                {
                                                        bool do_not_link_word = do_not_link_words && pWord->Size() < 2;
                                                        url = m_projectName->text() + QString( "_Mini_%1_Words.html" ).arg( pWord->GetMyMini()->GetIndex() + 1 );
                                                        url.replace( " ", "_" );
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord, TRUE, do_not_link_word, "word", url ) << "</td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << pWord->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << pWord->GetMyMini()->GetIndex() + 1 << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pWord->CalculateDL() << "</td>\n";
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pWord->DisplayStemType() << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pSig, TRUE ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }
                                                if( field == SOURCE_FIELD )
                                                {
                                                        if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pSig->GetRemark() << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pWord->GetConfidence() << "</td>\n";
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        if( pWord->GetPrefixPtr() ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord->GetPrefixPtr(), TRUE ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        if( pWord->GetStemPtr() ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord->GetStemPtr(), TRUE ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        if( pWord->GetSuffixPtr() ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord->GetSuffixPtr(), TRUE ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_allWordsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportAllStems()
{
        QFile* file;
        Q3TextStream* out;

        StemSet* pStems;

        CStem* pStem;
        CSignature* pSig;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, start, end, index;

        QString line, field,
                        fileName = m_projectName->text() + "_" + ALL_STEMS_FILE_TITLE;

        QStringList alphabetized;

        fileName.replace( " ", "_" );

        Q3DictIterator<StemSet> it( *m_pLexicon->GetAllStems() );

        // Get all words for alphabetization
        for( ; it.current(); ++it )
        {
                alphabetized.append( it.currentKey() );
        }

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_allStemsUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_allStemsColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[STEM_FIELD] = STEM_FIELD_TITLE.length();
                                        fieldWidths[MINI_LEX_FIELD] = MINI_LEX_FIELD_TITLE.length();
                                        fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[TYPE_FIELD] = TYPE_FIELD_TITLE.length();
                                        fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                        fieldWidths[ORIGIN_FIELD] = ORIGIN_FIELD_TITLE.length();
                                }

                                index = 0;
                                it.toFirst();
                                for( ; it.current(); ++it )
                                {
                                        pStems = it.current();

                                        for (int z = 0; z < pStems->size(); z++)
                                        {       pStem = pStems->at(z);
                                                index++;

                                                pSig = pStem->GetSuffixSignature();
                                                if( !pSig ) pSig = pStem->GetPrefixSignature();

                                                if( m_allStemsLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( index ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( STEM_FIELD ) >= 0 )
                                                {
                                                        width = pStem->Display(  filter  ).length();
                                                        if( width > fieldWidths[STEM_FIELD] ) fieldWidths[STEM_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( MINI_LEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pStem->GetMyMini()->GetIndex() + 1 ).length();
                                                        if( width > fieldWidths[MINI_LEX_FIELD] ) fieldWidths[MINI_LEX_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pStem->CalculateDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pStem->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( TYPE_FIELD ) >= 0 )
                                                {
                                                        width = pStem->DisplayStemType().length();
                                                        if( width > fieldWidths[TYPE_FIELD] ) fieldWidths[TYPE_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->Display( '.', filter ).length();
                                                        else width = 0;
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_allStemsLine->text().find( ORIGIN_FIELD ) >= 0 )
                                                {
                                                        width = pStem->GetConfidence().length();
                                                        if( width > fieldWidths[ORIGIN_FIELD] ) fieldWidths[ORIGIN_FIELD] = width;
                                                }
                                        }
                                }
                        }


                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_allStemsColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_allStemsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == STEM_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                *out << STEM_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                *out << MINI_LEX_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == TYPE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                *out << TYPE_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == ORIGIN_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[ORIGIN_FIELD] );
                                                *out << ORIGIN_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output text file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pStems = ( *m_pLexicon->GetAllStems() )[ *sIt ];

                                for (int y = 0; y < pStems->size(); y++)
                                {       pStem = pStems->at(y);
                                        index++;

                                        pSig = pStem->GetSuffixSignature();
                                        if( !pSig ) pSig = pStem->GetPrefixSignature();

                                        if( m_allStemsColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_allStemsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index;
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                        *out << pStem->Display(  filter  );
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pStem->GetCorpusCount();
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                        *out << pStem->GetMyMini()->GetIndex() + 1;
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pStem->CalculateDL();
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                        *out << pStem->DisplayStemType();
                                                }
                                                if( field == ORIGIN_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[ORIGIN_FIELD] );
                                                        *out << pStem->GetConfidence();
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        if( pSig ) *out << pSig->Display( '.', filter );
                                                        else *out << " ";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                QString url;

                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), ALL_STEMS_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_allStemsColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_allStemsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == STEM_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << STEM_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MINI_LEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == TYPE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << TYPE_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == ORIGIN_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << ORIGIN_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output html file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pStems = ( *m_pLexicon->GetAllStems() )[ *sIt ];

                                for (int z = 0; z < pStems->size(); z++)
                                {       pStem = pStems->at(z);
                                        *out << "\t\t\t\t<tr>\n";

                                        index++;

                                        pSig = pStem->GetSuffixSignature();
                                        if( !pSig ) pSig = pStem->GetPrefixSignature();

                                        line = m_allStemsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << index << "</td>\n";
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_Stems.html" ).arg( pStem->GetMyMini()->GetIndex() + 1 );
                                                        url.replace( " ", "_" );
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\"><a name=\"_" + pStem->Display() + "_\">" << getLParseText( pStem, TRUE, FALSE, "stem", url ) << "</a></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << pStem->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << pStem->GetMyMini()->GetIndex() + 1 << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pStem->CalculateDL() << "</td>\n";
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pStem->DisplayStemType() << "</td>\n";
                                                }
                                                if( field == ORIGIN_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pStem->GetConfidence() << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pSig, TRUE ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_allStemsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportAllSuffixSigs()
{
        QFile* file;
        Q3TextStream* out;

        SignatureSet* pSigs;

        CSignature* pSig;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, count, start, end, index;

        QString line, field,
                        fileName = m_projectName->text() + "_" + ALL_SUFFIX_SIGNATURES_FILE_TITLE;

        QStringList alphabetized;

        fileName.replace( " ", "_" );

        Q3DictIterator<SignatureSet> it( *m_pLexicon->GetAllSuffixSigs() );

        // Get all words for alphabetization
        for( ; it.current(); ++it )
        {
                alphabetized.append( it.currentKey() );
        }

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_allSuffixSigsUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_allSuffixSigsColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                        fieldWidths[MINI_LEX_FIELD] = MINI_LEX_FIELD_TITLE.length();
                                        fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                        fieldWidths[EXEMPLAR_FIELD] = EXEMPLAR_FIELD_TITLE.length();
                                        fieldWidths[REMARKS_FIELD] = REMARKS_FIELD_TITLE.length();
                                        fieldWidths[ROBUSTNESS_FIELD] = ROBUSTNESS_FIELD_TITLE.length();
                                        if( m_allSuffixSigsIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                }

                                index = 0;
                                it.toFirst();
                                for( ; it.current(); ++it )
                                {
                                        pSigs = it.current();

                                        for (int z= 0; z < pSigs->size(); z++)
                                        {       pSig = pSigs->at(z);
                                                index++;

                                                if( m_allSuffixSigsLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( index ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        width = pSig->Display( '.', filter ).length();
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( MINI_LEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetMyMini()->GetIndex() + 1 ).length();
                                                        if( width > fieldWidths[MINI_LEX_FIELD] ) fieldWidths[MINI_LEX_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->ComputeDLofModel() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetNumberOfStems() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( EXEMPLAR_FIELD ) >= 0 )
                                                {
                                                        width = pSig->GetStemPtrList()->first()->Display(  filter  ).length();
                                                        if( width > fieldWidths[EXEMPLAR_FIELD] ) fieldWidths[EXEMPLAR_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( REMARKS_FIELD ) >= 0 )
                                                {
                                                        width = pSig->GetRemark().length();
                                                        if( width > fieldWidths[REMARKS_FIELD] ) fieldWidths[REMARKS_FIELD] = width;
                                                }
                                                if( m_allSuffixSigsLine->text().find( ROBUSTNESS_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetRobustness() ).length();
                                                        if( width > fieldWidths[ROBUSTNESS_FIELD] ) fieldWidths[ROBUSTNESS_FIELD] = width;
                                                }

                                                if( m_allSuffixSigsIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                        for (int z= 0; z < pSig->GetStemPtrList()->size(); z++)
                                                        {       pStem = pSig->GetStemPtrList()->at(z);
                                                                if( width < static_cast <int> (pStem->Display(  filter  ).length()) ) width = static_cast <int> (pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }
                        }

                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_allSuffixSigsColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_allSuffixSigsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                *out << MINI_LEX_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }
                                        if( field == EXEMPLAR_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[EXEMPLAR_FIELD] );
                                                *out << EXEMPLAR_FIELD_TITLE;
                                        }
                                        if( field == REMARKS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[REMARKS_FIELD] );
                                                *out << REMARKS_FIELD_TITLE;
                                        }
                                        if( field == ROBUSTNESS_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[ROBUSTNESS_FIELD] );
                                                *out << ROBUSTNESS_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output text file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pSigs = ( *m_pLexicon->GetAllSuffixSigs() )[ *sIt ];

                                //for( pSig = pSigs->first(); pSig; pSig = pSigs->next() )
                                for (int z = 0; z < pSigs->size(); z++)
                                {       pSig = pSigs->at(z);
                                        index++;

                                        if( m_allSuffixSigsColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_allSuffixSigsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index;
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        *out << pSig->Display( '.', filter );
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                        *out << pSig->GetMyMini()->GetIndex() + 1;
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pSig->ComputeDLofModel();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pSig->GetStemPtrList()->count();
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pSig->GetCorpusCount();
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[EXEMPLAR_FIELD] );
                                                        *out << pSig->GetStemPtrList()->first()->Display(  filter  );
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[REMARKS_FIELD] );
                                                        *out << pSig->GetRemark();
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[ROBUSTNESS_FIELD] );
                                                        *out << pSig->GetRobustness();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_allSuffixSigsIncludeStemListFlag->isChecked() )
                                        {
                                                count = 0;
                                                if( m_allSuffixSigsColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                for (int y = 0; y < pSig->GetStemPtrList()->size(); y++)
                                                {       pStem = pSig->GetStemPtrList()->at(y);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_allSuffixSigsColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                QString url;

                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), ALL_SUFFIX_SIGNATURES_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_allSuffixSigsColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_allSuffixSigsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MINI_LEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == EXEMPLAR_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << EXEMPLAR_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == REMARKS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << REMARKS_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == ROBUSTNESS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\" align=\"center\">" << ROBUSTNESS_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output html file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pSigs = ( *m_pLexicon->GetAllSuffixSigs() )[ *sIt ];

                                //for( pSig = pSigs->first(); pSig; pSig = pSigs->next() )
                                for (int z = 0; z < pSigs->size(); z++)
                                {       pSig = pSigs->at(z);
                                        *out << "\t\t\t\t<tr>\n";

                                        index++;

                                        line = m_allSuffixSigsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_Signatures.html" ).arg( pSig->GetMyMini()->GetIndex() + 1 );
                                                        url.replace( " ", "_" );
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << "><a name=\"_" + pSig->Display( NULL<  filter  ) + "_\">" << getLParseText( pSig, TRUE, FALSE, "signature", url ) << "</a></td>\n";
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetMyMini()->GetIndex() + 1 << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSig->ComputeDLofModel() << "</td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetStemPtrList()->count() << "</td>\n";
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << getLParseText( pSig->GetStemPtrList()->first(), TRUE, FALSE ) << "</td>\n";
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSig->GetRemark() << "</td>\n";
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetRobustness() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_allSuffixSigsIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_allSuffixSigsLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                for (int z = 0; z < pSig->GetStemPtrList()->size(); z++)
                                                {       pStem = pSig->GetStemPtrList()->at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_allSuffixSigsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportAllSuffixes()
{
        QFile* file;
        Q3TextStream* out;

        SuffixSet* pSuffixes;

        CSuffix* pSuffix;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, count, start, end, index;

        QString line, field,
                        fileName = m_projectName->text() + "_" + ALL_SUFFIXES_FILE_TITLE;

        QStringList alphabetized;

        fileName.replace( " ", "_" );

        Q3DictIterator<SuffixSet> it( *m_pLexicon->GetAllSuffixes() );

        // Get all words for alphabetization
        for( ; it.current(); ++it )
        {
                alphabetized.append( it.currentKey() );
        }

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_allSuffixesUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_allSuffixesColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[SUFFIX_FIELD] = SUFFIX_FIELD_TITLE.length();
                                        fieldWidths[MINI_LEX_FIELD] = MINI_LEX_FIELD_TITLE.length();
                                        fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                        if( m_allSuffixesIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                }

                                index = 0;
                                it.toFirst();
                                for( ; it.current(); ++it )
                                {
                                        pSuffixes = it.current();

                                        //for( pSuffix = pSuffixes->first(); pSuffix; pSuffix = pSuffixes->next() )
                                        for (int z = 0; z < pSuffixes->size(); z++)
                                        {       pSuffix = pSuffixes->at(z);
                                                index++;

                                                if( m_allSuffixesLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( index ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_allSuffixesLine->text().find( SUFFIX_FIELD ) >= 0 )
                                                {
                                                        width = pSuffix->Display(  filter  ).length();
                                                        if( width > fieldWidths[SUFFIX_FIELD] ) fieldWidths[SUFFIX_FIELD] = width;
                                                }
                                                if( m_allSuffixesLine->text().find( MINI_LEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->GetMyMini()->GetIndex() + 1 ).length();
                                                        if( width > fieldWidths[MINI_LEX_FIELD] ) fieldWidths[MINI_LEX_FIELD] = width;
                                                }
                                                if( m_allSuffixesLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->ComputeDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_allSuffixesLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_allSuffixesLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->GetNumberOfStems() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }

                                                if( m_allSuffixesIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        for (int i = 0; i < pSuffix->GetStems()->size(); i++)
                                                        //for( pStem = pSuffix->GetStems()->first(); pStem; pStem = pSuffix->GetStems()->next() )
                                                        {
                                                                pStem = pSuffix->GetStems()->at(i);
                                                                if( width < (static_cast <int> (pStem->Display(  filter  ).length()) ) ) width = static_cast <int> ( pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }
                        }

                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_allSuffixesColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_allSuffixesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == SUFFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                *out << SUFFIX_FIELD_TITLE;
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                *out << MINI_LEX_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output text file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pSuffixes = ( *m_pLexicon->GetAllSuffixes() )[ *sIt ];

                                //for( pSuffix = pSuffixes->first(); pSuffix; pSuffix = pSuffixes->next() )
                                for (int z = 0; z < pSuffixes->size(); z++)
                                {       pSuffix = pSuffixes->at(z);
                                        index++;

                                        if( m_allSuffixesColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_allSuffixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index;
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                        *out << pSuffix->Display( '.', filter );
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                        *out << pSuffix->GetMyMini()->GetIndex() + 1;
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pSuffix->ComputeDL();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pSuffix->GetStems()->count();
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pSuffix->GetCorpusCount();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_allSuffixesIncludeStemListFlag->isChecked() )
                                        {
                                                count = 0;
                                                if( m_allSuffixesColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pSuffix->GetStems()->first(); pStem; pStem = pSuffix->GetStems()->next() )
                                                for (int z = 0; z < pSuffix->GetStems()->size(); z++)
                                                {       pStem = pSuffix->GetStems()->at(z);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_allSuffixesColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                QString url;

                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), ALL_SUFFIXES_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_allSuffixesColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_allSuffixesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SUFFIX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SUFFIX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MINI_LEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output html file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pSuffixes = ( *m_pLexicon->GetAllSuffixes() )[ *sIt ];

                                //for( pSuffix = pSuffixes->first(); pSuffix; pSuffix = pSuffixes->next() )
                                for (int y = 0; y < pSuffixes->size(); y++)
                                {       pSuffix = pSuffixes->at(y);
                                        *out << "\t\t\t\t<tr>\n";

                                        index++;

                                        line = m_allSuffixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index << "</td>\n";
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_Suffixes.html" ).arg( pSuffix->GetMyMini()->GetIndex() + 1 );
                                                        url.replace( " ", "_" );
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << "><a name=\"_" + pSuffix->Display() + "_\">" << getLParseText( pSuffix, TRUE, FALSE, "suffix", url ) << "</a></td>\n";
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSuffix->GetMyMini()->GetIndex() + 1 << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSuffix->ComputeDL() << "</td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSuffix->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSuffix->GetStems()->count() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_allSuffixesIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_allSuffixesLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";

                                                //for( pStem = pSuffix->GetStems()->first(); pStem; pStem = pSuffix->GetStems()->next() )
                                                for (int z = 0; z < pSuffix->GetStems()->size(); z++)
                                                {       pStem = pSuffix->GetStems() -> at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_allSuffixesLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportAllPrefixSigs()
{
        QFile* file;
        Q3TextStream* out;

        SignatureSet* pSigs;

        CSignature* pSig;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, count, start, end, index;

        QString line, field,
                        fileName = m_projectName->text() + "_" + ALL_PREFIX_SIGNATURES_FILE_TITLE;

        QStringList alphabetized;

        fileName.replace( " ", "_" );

        Q3DictIterator<SignatureSet> it( *m_pLexicon->GetAllPrefixSigs() );

        // Get all words for alphabetization
        for( ; it.current(); ++it )
        {
                alphabetized.append( it.currentKey() );
        }

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_allPrefixSigsUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_allPrefixSigsColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                        fieldWidths[MINI_LEX_FIELD] = MINI_LEX_FIELD_TITLE.length();
                                        fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                        fieldWidths[EXEMPLAR_FIELD] = EXEMPLAR_FIELD_TITLE.length();
                                        fieldWidths[REMARKS_FIELD] = REMARKS_FIELD_TITLE.length();
                                        fieldWidths[ROBUSTNESS_FIELD] = ROBUSTNESS_FIELD_TITLE.length();
                                        if( m_allPrefixSigsIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                }

                                index = 0;
                                it.toFirst();
                                for( ; it.current(); ++it )
                                {
                                        pSigs = it.current();

                                        //for( pSig = pSigs->first(); pSig; pSig = pSigs->next() )
                                        for (int z = 0; z < pSigs->size(); z++)
                                        {       pSig = pSigs->at(z);
                                                index++;

                                                if( m_allPrefixSigsLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( index ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        width = pSig->Display( '.', filter ).length();
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( MINI_LEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetMyMini()->GetIndex() + 1 ).length();
                                                        if( width > fieldWidths[MINI_LEX_FIELD] ) fieldWidths[MINI_LEX_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->ComputeDLofModel() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetNumberOfStems() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( EXEMPLAR_FIELD ) >= 0 )
                                                {
                                                        width = pSig->GetStemPtrList()->first()->Display(  filter  ).length();
                                                        if( width > fieldWidths[EXEMPLAR_FIELD] ) fieldWidths[EXEMPLAR_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( REMARKS_FIELD ) >= 0 )
                                                {
                                                        width = pSig->GetRemark().length();
                                                        if( width > fieldWidths[REMARKS_FIELD] ) fieldWidths[REMARKS_FIELD] = width;
                                                }
                                                if( m_allPrefixSigsLine->text().find( ROBUSTNESS_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetRobustness() ).length();
                                                        if( width > fieldWidths[ROBUSTNESS_FIELD] ) fieldWidths[ROBUSTNESS_FIELD] = width;
                                                }

                                                if( m_allPrefixSigsIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                        for (int z = 0; z < pSig->GetStemPtrList()->size(); z++)
                                                        {       pStem = pSig->GetStemPtrList()->at(z);
                                                                if( width < static_cast <int> (pStem->Display(  filter  ).length()) ) width = static_cast <int> ( pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }
                        }

                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_allPrefixSigsColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_allPrefixSigsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                *out << MINI_LEX_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }
                                        if( field == EXEMPLAR_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[EXEMPLAR_FIELD] );
                                                *out << EXEMPLAR_FIELD_TITLE;
                                        }
                                        if( field == REMARKS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[REMARKS_FIELD] );
                                                *out << REMARKS_FIELD_TITLE;
                                        }
                                        if( field == ROBUSTNESS_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[ROBUSTNESS_FIELD] );
                                                *out << ROBUSTNESS_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output text file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pSigs = ( *m_pLexicon->GetAllPrefixSigs() )[ *sIt ];

                                //for( pSig = pSigs->first(); pSig; pSig = pSigs->next() )
                                for (int z = 0; z < pSigs->size(); z++)
                                {       pSig = pSigs->at(z);
                                        index++;

                                        if( m_allPrefixSigsColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_allPrefixSigsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index;
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        *out << pSig->Display( '.', filter );
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                        *out << pSig->GetMyMini()->GetIndex() + 1;
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pSig->ComputeDLofModel();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pSig->GetStemPtrList()->count();
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pSig->GetCorpusCount();
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[EXEMPLAR_FIELD] );
                                                        *out << pSig->GetStemPtrList()->first()->Display(  filter  );
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[REMARKS_FIELD] );
                                                        *out << pSig->GetRemark();
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[ROBUSTNESS_FIELD] );
                                                        *out << pSig->GetRobustness();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_allPrefixSigsIncludeStemListFlag->isChecked() )
                                        {
                                                count = 0;
                                                if( m_allPrefixSigsColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                for (int z = 0; z < pSig->GetStemPtrList()->size(); z++)
                                                {       pStem = pSig->GetStemPtrList()->at(z);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_allPrefixSigsColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                QString url;

                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), ALL_PREFIX_SIGNATURES_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_allPrefixSigsColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_allPrefixSigsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MINI_LEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == EXEMPLAR_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << EXEMPLAR_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == REMARKS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << REMARKS_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == ROBUSTNESS_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\" align=\"center\">" << ROBUSTNESS_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output html file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pSigs = ( *m_pLexicon->GetAllPrefixSigs() )[ *sIt ];

                                //for( pSig = pSigs->first(); pSig; pSig = pSigs->next() )
                                for (int z = 0; z < pSigs->size(); z++)
                                {       pSig = pSigs->at(z);
                                        *out << "\t\t\t\t<tr>\n";

                                        index++;

                                        line = m_allPrefixSigsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_Signatures.html" ).arg( pSig->GetMyMini()->GetIndex() + 1 );
                                                        url.replace( " ", "_" );
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << "><a name=\"_" + pSig->Display( filter  ) + "_\">" << getLParseText( pSig, TRUE, FALSE, "signature", url ) << "</a></td>\n";
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetMyMini()->GetIndex() + 1 << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSig->ComputeDLofModel() << "</td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetStemPtrList()->count() << "</td>\n";
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << getLParseText( pSig->GetStemPtrList()->first(), TRUE, FALSE ) << "</td>\n";
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSig->GetRemark() << "</td>\n";
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixSigsIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetRobustness() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_allPrefixSigsIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_allPrefixSigsLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                for (int z = 0; z < pSig->GetStemPtrList()->size();z++)
                                                {       pStem = pSig->GetStemPtrList()->at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_allPrefixSigsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportAllPrefixes()
{
        QFile* file;
        Q3TextStream* out;

        PrefixSet* pPrefixes;

        CPrefix* pPrefix;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int width, count, start, end, index;

        QString line, field,
                        fileName = m_projectName->text() + "_" + ALL_PREFIXES_FILE_TITLE;

        QStringList alphabetized;

        fileName.replace( " ", "_" );

        Q3DictIterator<PrefixSet> it( *m_pLexicon->GetAllPrefixes() );

        // Get all words for alphabetization
        for( ; it.current(); ++it )
        {
                alphabetized.append( it.currentKey() );
        }

        // Write simple text file
        if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
        {
                file = new QFile( fileName + ".txt" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        fieldWidths.clear();

                        // Get field widths
                        if( m_allPrefixesUniformFieldWidthsFlag->isChecked() )
                        {
                                if( m_allPrefixesColumnTitlesFlag->isChecked() )
                                {
                                        fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                        fieldWidths[PREFIX_FIELD] = PREFIX_FIELD_TITLE.length();
                                        fieldWidths[MINI_LEX_FIELD] = MINI_LEX_FIELD_TITLE.length();
                                        fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                        fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                        fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                        if( m_allPrefixesIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                }

                                index = 0;
                                it.toFirst();
                                for( ; it.current(); ++it )
                                {
                                        pPrefixes = it.current();

                                        //for( pPrefix = pPrefixes->first(); pPrefix; pPrefix = pPrefixes->next() )
                                        for (int z = 0; z < pPrefixes->size(); z++)
                                        {       pPrefix = pPrefixes->at(z);
                                                index++;

                                                if( m_allPrefixesLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( index ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_allPrefixesLine->text().find( PREFIX_FIELD ) >= 0 )
                                                {
                                                        width = pPrefix->Display(  filter  ).length();
                                                        if( width > fieldWidths[PREFIX_FIELD] ) fieldWidths[PREFIX_FIELD] = width;
                                                }
                                                if( m_allPrefixesLine->text().find( MINI_LEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->GetMyMini()->GetIndex() + 1 ).length();
                                                        if( width > fieldWidths[MINI_LEX_FIELD] ) fieldWidths[MINI_LEX_FIELD] = width;
                                                }
                                                if( m_allPrefixesLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->ComputeDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_allPrefixesLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_allPrefixesLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->GetNumberOfStems() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }

                                                if( m_allPrefixesIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        //for( pStem = pPrefix->GetStems()->first(); pStem; pStem = pPrefix->GetStems()->next() )
                                                        for (int z = 0; z < pPrefix->GetStems()->size(); z++)
                                                        {
                                                                pStem = pPrefix->GetStems()->at(z);
                                                                if( width < static_cast <int> (pStem->Display(  filter  ).length())) width = static_cast <int> (pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }
                        }

                        // Prepare stream
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );


                        // Add title line
                        if( m_allPrefixesColumnTitlesFlag->isChecked() )
                        {
                                *out << "# ";

                                line = m_allPrefixesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == PREFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                *out << PREFIX_FIELD_TITLE;
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                *out << MINI_LEX_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output text file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pPrefixes = ( *m_pLexicon->GetAllPrefixes() )[ *sIt ];

                                //for( pPrefix = pPrefixes->first(); pPrefix; pPrefix = pPrefixes->next() )
                                for (int z = 0; z < pPrefixes->size(); z++)
                                {       pPrefix = pPrefixes->at(z);
                                        index++;

                                        if( m_allPrefixesColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_allPrefixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index;
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                        *out << pPrefix->Display( '.', filter );
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[MINI_LEX_FIELD] );
                                                        *out << pPrefix->GetMyMini()->GetIndex() + 1;
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pPrefix->ComputeDL();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pPrefix->GetStems()->count();
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pPrefix->GetCorpusCount();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_allPrefixesIncludeStemListFlag->isChecked() )
                                        {
                                                count = 0;
                                                if( m_allPrefixesColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pPrefix->GetStems()->first(); pStem; pStem = pPrefix->GetStems()->next() )
                                                for (int z = 0; z < pPrefix->GetStems()->size(); z++)
                                                {
                                                        pStem = pPrefix->GetStems()->at(z);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_allPrefixesColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }
                        }

                        file->close();
                        delete file; file = NULL;
                        delete out;	out = NULL;
                }
        }

        // Write mark-up file
        if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
        {
                QString url;

                file = new QFile( fileName + ".html" );
                if( file->open( QIODevice::WriteOnly ) )
                {
                        out = new Q3TextStream( file );
                        out->setEncoding( Q3TextStream::Unicode );

                        // Output html file stuff
                        *out << getHTMLHeader( m_projectName->text(), ALL_PREFIXES_FILE_TITLE, m_language->text(), m_researchers->text() );

                        *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                        // Add title line
                        if( m_allPrefixesColumnTitlesFlag->isChecked() )
                        {
                                *out << "\t\t\t\t<tr>\n";

                                line = m_allPrefixesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );
                                        if( start < 0 ) break;

                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == PREFIX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << PREFIX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == MINI_LEX_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << MINI_LEX_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << "\t\t\t\t</tr>\n";
                        }

                        // Alphabetize list
                        alphabetized.sort();

                        // Output html file stuff
                        index = 0;
                        for( QStringList::Iterator sIt = alphabetized.begin(); sIt != alphabetized.end(); ++sIt )
                        {
                                pPrefixes = ( *m_pLexicon->GetAllPrefixes() )[ *sIt ];

                                //for( pPrefix = pPrefixes->first(); pPrefix; pPrefix = pPrefixes->next() )
                                for (int z=0; z < pPrefixes->size(); z++)
                                {       pPrefix = pPrefixes->at(z);
                                        *out << "\t\t\t\t<tr>\n";

                                        index++;

                                        line = m_allPrefixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index << "</td>\n";
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_Prefixes.html" ).arg( pPrefix->GetMyMini()->GetIndex() + 1 );
                                                        url.replace( " ", "_" );
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << "><a name=\"_" + pPrefix->Display() + "_\">" << getLParseText( pPrefix, TRUE, FALSE, "suffix", url ) << "</a></td>\n";
                                                }
                                                if( field == MINI_LEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pPrefix->GetMyMini()->GetIndex() + 1 << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pPrefix->ComputeDL() << "</td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pPrefix->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_allPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pPrefix->GetStems()->count() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_allPrefixesIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_allPrefixesLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                //for( pStem = pPrefix->GetStems()->first(); pStem; pStem = pPrefix->GetStems()->next() )
                                                for (int z = 0; z < pPrefix->GetStems()->size(); z++)
                                                {
                                                        pStem = pPrefix->GetStems()->at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_allPrefixesLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }
                        }

                        *out << "\t\t\t</table>\n";

                        *out << getHTMLFooter();

                        file->close();
                        delete file; file = NULL;
                        delete out; out = NULL;
                }
        }
}


void ExportWizard::exportMiniWords()
{
        QFile* file;
        Q3TextStream* out;

        CStem* pWord;
        CSignature* pSig;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int i, mini,
                width, start,
                end, index;

        QString line, field, fileName, url, type;

        CMiniLexicon* pMini;
        for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
        {
                pMini = m_pLexicon->GetMiniLexicon(mini);
                if( !pMini || !pMini->GetWords() ) continue;
                if( pMini->GetWords()->GetCount() == 0 ) continue;

                fileName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_WORDS_FILE_TITLE;
                fileName.replace( " ", "_" );

                // Write simple text file
                if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".txt" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                fieldWidths.clear();

                                // Get field widths
                                if( m_miniWordsUniformFieldWidthsFlag->isChecked() )
                                {
                                        if( m_miniWordsColumnTitlesFlag->isChecked() )
                                        {
                                                fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                                fieldWidths[WORD_FIELD] = WORD_FIELD_TITLE.length();
                                                fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                                fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                                fieldWidths[TYPE_FIELD] = TYPE_FIELD_TITLE.length();
                                                fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                                fieldWidths[SOURCE_FIELD] = SOURCE_FIELD_TITLE.length();
                                                fieldWidths[PREFIX_FIELD] = PREFIX_FIELD_TITLE.length();
                                                fieldWidths[STEM_FIELD] = STEM_FIELD_TITLE.length();
                                                fieldWidths[SUFFIX_FIELD] = SUFFIX_FIELD_TITLE.length();
                                        }

                                        pMini->GetWords()->Sort(PARSE_SIZE);
                                        for( i = 0; i < pMini->GetWords()->GetCount(); i++ )
                                        {
                                                pWord = pMini->GetWords()->GetAtSort(i);

                                                if( pWord->Size() > 1 )
                                                {
                                                        pSig = pWord->GetSuffixSignature();
                                                        if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
                                                }
                                                else pSig = NULL;

                                                if( m_miniWordsLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( i + 1 ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( WORD_FIELD ) >= 0 )
                                                {
                                                        width = pWord->Display(  filter  ).length();
                                                        if( width > fieldWidths[WORD_FIELD] ) fieldWidths[WORD_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pWord->CalculateDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pWord->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( TYPE_FIELD ) >= 0 )
                                                {
                                                        width = pWord->DisplayStemType().length();
                                                        if( width > fieldWidths[TYPE_FIELD] ) fieldWidths[TYPE_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->Display( '.', filter ).length();
                                                        else width = 0;
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( SOURCE_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->GetRemark().length();
                                                        else width = pWord->GetConfidence().length();
                                                        if( width > fieldWidths[SOURCE_FIELD] ) fieldWidths[SOURCE_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( PREFIX_FIELD ) >= 0 )
                                                {
                                                        width = pWord->GetPiece( pWord->GetPrefixLoc() ).Display( filter ).length();
                                                        if( width > fieldWidths[PREFIX_FIELD] ) fieldWidths[PREFIX_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( STEM_FIELD ) >= 0 )
                                                {
                                                        width = pWord->GetStem().Display( filter ).length();
                                                        if( width > fieldWidths[STEM_FIELD] ) fieldWidths[STEM_FIELD] = width;
                                                }
                                                if( m_miniWordsLine->text().find( SUFFIX_FIELD ) >= 0 )
                                                {
                                                        width = pWord->GetPiece( pWord->GetSuffixLoc() ).Display( filter ).length();
                                                        if( width > fieldWidths[SUFFIX_FIELD] ) fieldWidths[SUFFIX_FIELD] = width;
                                                }
                                        }
                                }


                                // Prepare stream
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );


                                // Add title line
                                if( m_miniWordsColumnTitlesFlag->isChecked() )

                                *out << "# ";

                                line = m_miniWordsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == WORD_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[WORD_FIELD] );
                                                *out << WORD_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == TYPE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                *out << TYPE_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == SOURCE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SOURCE_FIELD] );
                                                *out << SOURCE_FIELD_TITLE;
                                        }
                                        if( field == PREFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                *out << PREFIX_FIELD_TITLE;
                                        }
                                        if( field == STEM_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                *out << STEM_FIELD_TITLE;
                                        }
                                        if( field == SUFFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                *out << SUFFIX_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;


                                // Sort appropriately
                                if( m_miniWordsMorphemeCountSortFlag->isChecked() ) pMini->GetWords()->Sort(PARSE_SIZE);
                                else if( m_miniWordsCorpusCountSortFlag->isChecked() ) pMini->GetWords()->Sort(CORPUSCOUNT);
                                else pMini->GetWords()->Sort(KEY);

                                // Output text file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetWords()->GetCount(); i++ )
                                {
                                        pWord = pMini->GetWords()->GetAtSort(i);

                                        if( pWord->Size() > 1 )
                                        {
                                                pSig = pWord->GetSuffixSignature();
                                                if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
                                        }
                                        else pSig = NULL;

                                        if( m_miniWordsAnalyzedOnlyFlag->isChecked() && pWord->Size() < 2 ) continue;

                                        if( m_miniWordsColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_miniWordsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index++;
                                                }
                                                if( field == WORD_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[WORD_FIELD] );
                                                        *out << pWord->Display(  filter  );
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pWord->GetCorpusCount();
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pWord->CalculateDL();
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                        *out << pWord->DisplayStemType();
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        if( pSig ) *out << getLParseText( pSig );
                                                        else *out << " ";
                                                }
                                                if( field == SOURCE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SOURCE_FIELD] );
                                                        if( pSig ) *out << pSig->GetRemark();
                                                        else *out << pWord->GetConfidence();
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                        *out << pWord->GetPiece( pWord->GetPrefixLoc() ).Display( filter );
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                        *out << pWord->GetStem().Display( filter );
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                        *out << pWord->GetPiece( pWord->GetSuffixLoc() ).Display( filter );
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;
                                }

                                file->close();
                                delete file; file = NULL;
                                delete out;	out = NULL;
                        }
                }

                // Write mark-up file
                if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".html" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );

                                // Output html file stuff
                                *out << getHTMLHeader( m_projectName->text(), MINI_WORDS_FILE_TITLE, m_language->text(), m_researchers->text(), pMini->GetIndex() );

                                *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                                // Add title line
                                if( m_miniWordsColumnTitlesFlag->isChecked() )
                                {
                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniWordsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == WORD_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << WORD_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << TYPE_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == SOURCE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SOURCE_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << PREFIX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << STEM_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SUFFIX_FIELD_TITLE << "</span></td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";
                                }


                                // Sort appropriately
                                if( m_miniWordsMorphemeCountSortFlag->isChecked() ) pMini->GetWords()->Sort(PARSE_SIZE);
                                else if( m_miniWordsCorpusCountSortFlag->isChecked() ) pMini->GetWords()->Sort(CORPUSCOUNT);
                                else pMini->GetWords()->Sort(KEY);


                                // Output html file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetWords()->GetCount(); i++ )
                                {
                                        pWord = pMini->GetWords()->GetAtSort(i);

                                        if( pWord->Size() > 1 )
                                        {
                                                pSig = pWord->GetSuffixSignature();
                                                if( pSig == NULL ) pSig = pWord->GetPrefixSignature();
                                        }
                                        else pSig = NULL;

                                        if( m_miniWordsAnalyzedOnlyFlag->isChecked() && pWord->Size() < 2 ) continue;

                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniWordsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << index++ << "</td>\n";
                                                }
                                                if( field == WORD_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\"><a name=\"_" << pWord->Display(  filter  ) << "_\" class=\"bookmark\">" << getLParseText( pWord, TRUE, TRUE, "word" ) << "</a></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << pWord->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pWord->CalculateDL() << "</td>\n";
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pWord->DisplayStemType() << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_SIGNATURES_FILE_TITLE + ".html";
                                                        url.replace( " ", "_" );
                                                        type = "signature";
                                                        if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pSig, TRUE, FALSE, type, url ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }
                                                if( field == SOURCE_FIELD )
                                                {
                                                        if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pSig->GetRemark() << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pWord->GetConfidence() << "</td>\n";
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_PREFIXES_FILE_TITLE + ".html";
                                                        url.replace( " ", "_" );
                                                        type = "prefix";
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord->GetPrefixPtr(), TRUE, FALSE, type, url ) << "</td>\n";
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_STEMS_FILE_TITLE + ".html";
                                                        url.replace( " ", "_" );
                                                        type = "stem";
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord->GetStemPtr(), TRUE, FALSE, type, url ) << "</td>\n";
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_SUFFIXES_FILE_TITLE + ".html";
                                                        url.replace( " ", "_" );
                                                        type = "suffix";
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pWord->GetSuffixPtr(), TRUE, FALSE, type, url ) << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_miniWordsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }

                                *out << "\t\t\t</table>\n";

                                *out << getHTMLFooter();

                                file->close();
                                delete file; file = NULL;
                                delete out; out = NULL;
                        }
                }
        }
}


void ExportWizard::exportMiniSignatures()
{
        QFile* file;
        Q3TextStream* out;

        CSignature* pSig;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int i, mini,
                width, start,
                end, index,
                count;

        QString line, field, fileName, url, type = "stem";

        CMiniLexicon* pMini;
        for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
        {
                pMini = m_pLexicon->GetMiniLexicon(mini);
                if( !pMini || !pMini->GetSignatures() ) continue;
                if( pMini->GetSignatures()->GetCount() == 0 ) continue;

                fileName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_SIGNATURES_FILE_TITLE;
                fileName.replace( " ", "_" );

                url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_STEMS_FILE_TITLE + ".html";
                url.replace( " ", "_" );

                // Write simple text file
                if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".txt" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                fieldWidths.clear();

                                // Get field widths
                                if( m_miniSignaturesUniformFieldWidthsFlag->isChecked() )
                                {
                                        if( m_miniSignaturesColumnTitlesFlag->isChecked() )
                                        {
                                                fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                                fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                                fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                                fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                                fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                                fieldWidths[EXEMPLAR_FIELD] = EXEMPLAR_FIELD_TITLE.length();
                                                fieldWidths[REMARKS_FIELD] = REMARKS_FIELD_TITLE.length();
                                                fieldWidths[ROBUSTNESS_FIELD] = ROBUSTNESS_FIELD_TITLE.length();
                                                if( m_miniSignaturesIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                        }

                                        pMini->GetSignatures()->Sort(PARSE_SIZE);
                                        for( i = 0; i < pMini->GetSignatures()->GetCount(); i++ )
                                        {
                                                pSig = pMini->GetSignatures()->GetAtSort(i);

                                                if( m_miniSignaturesLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg(i).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        width = pSig->Display( '.', filter ).length();
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->ComputeDLofModel() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetNumberOfStems() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( EXEMPLAR_FIELD ) >= 0 )
                                                {
                                                        width = pSig->GetStemPtrList()->first()->Display(  filter  ).length();
                                                        if( width > fieldWidths[EXEMPLAR_FIELD] ) fieldWidths[EXEMPLAR_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( REMARKS_FIELD ) >= 0 )
                                                {
                                                        width = pSig->GetRemark().length();
                                                        if( width > fieldWidths[REMARKS_FIELD] ) fieldWidths[REMARKS_FIELD] = width;
                                                }
                                                if( m_miniSignaturesLine->text().find( ROBUSTNESS_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSig->GetRobustness() ).length();
                                                        if( width > fieldWidths[ROBUSTNESS_FIELD] ) fieldWidths[ROBUSTNESS_FIELD] = width;
                                                }

                                                if( m_miniSignaturesIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                        for (int z = 0; z < pSig->GetStemPtrList()->size(); z++)
                                                        {       pStem = pSig->GetStemPtrList()->at(z);
                                                                if( width < static_cast <int> (pStem->Display(  filter  ).length()) ) width = static_cast <int> (pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }


                                // Prepare stream
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );


                                // Add title line
                                if( m_miniSignaturesColumnTitlesFlag->isChecked() )

                                *out << "# ";

                                line = m_miniSignaturesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }
                                        if( field == EXEMPLAR_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[EXEMPLAR_FIELD] );
                                                *out << EXEMPLAR_FIELD_TITLE;
                                        }
                                        if( field == REMARKS_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[REMARKS_FIELD] );
                                                *out << REMARKS_FIELD_TITLE;
                                        }
                                        if( field == ROBUSTNESS_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[ROBUSTNESS_FIELD] );
                                                *out << ROBUSTNESS_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;


                                // Sort appropriately
                                if( m_miniSignaturesStemCountSortFlag->isChecked() ) pMini->GetSignatures()->Sort(SIGS_NUMBER_OF_STEMS);
                                else if( m_miniSignaturesCorpusCountSortFlag->isChecked() ) pMini->GetSignatures()->Sort(CORPUSCOUNT);
                                else pMini->GetSignatures()->Sort(KEY);

                                // Output text file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetSignatures()->GetCount(); i++ )
                                {
                                        pSig = pMini->GetSignatures()->GetAtSort(i);

                                        if( m_miniSignaturesColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_miniSignaturesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index++;
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        *out << pSig->Display( '.', filter );
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pSig->ComputeDLofModel();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pSig->GetStemPtrList()->count();
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pSig->GetCorpusCount();
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[EXEMPLAR_FIELD] );
                                                        *out << pSig->GetStemPtrList()->first()->Display(  filter  );
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[REMARKS_FIELD] );
                                                        *out << pSig->GetRemark();
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[ROBUSTNESS_FIELD] );
                                                        *out << pSig->GetRobustness();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_miniSignaturesIncludeStemListFlag->isChecked() )
                                        {
                                                *out << endl;

                                                count = 0;
                                                if( m_miniSignaturesColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                for (int z= 0; z < pSig->GetStemPtrList()->size(); z++)
                                                {       pStem = pSig->GetStemPtrList()->at(z);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_miniSignaturesColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }

                                file->close();
                                delete file; file = NULL;
                                delete out;	out = NULL;
                        }
                }

                // Write mark-up file
                if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".html" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );

                                // Output html file stuff
                                *out << getHTMLHeader( m_projectName->text(), MINI_SIGNATURES_FILE_TITLE, m_language->text(), m_researchers->text(), pMini->GetIndex() );

                                *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                                // Add title line
                                if( m_miniSignaturesColumnTitlesFlag->isChecked() )
                                {
                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniSignaturesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << EXEMPLAR_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << REMARKS_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << ROBUSTNESS_FIELD_TITLE << "</span></td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";
                                }


                                // Sort appropriately
                                if( m_miniSignaturesStemCountSortFlag->isChecked() ) pMini->GetSignatures()->Sort(SIGS_NUMBER_OF_STEMS);
                                else if( m_miniSignaturesCorpusCountSortFlag->isChecked() ) pMini->GetSignatures()->Sort(CORPUSCOUNT);
                                else pMini->GetSignatures()->Sort(KEY);


                                // Output html file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetSignatures()->GetCount(); i++ )
                                {
                                        pSig = pMini->GetSignatures()->GetAtSort(i);

                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniSignaturesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index++ << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << "><a name=\"_" << pSig->Display( filter  ) << "_\" class=\"bookmark\">" << getLParseText( pSig, TRUE, TRUE, "signature" ) << "</a></td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSig->ComputeDLofModel() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetStemPtrList()->count() << "</td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == EXEMPLAR_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << getLParseText( pSig->GetStemPtrList()->first(), TRUE, FALSE, type, url ) << "</td>\n";
                                                }
                                                if( field == REMARKS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSig->GetRemark() << "</td>\n";
                                                }
                                                if( field == ROBUSTNESS_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSignaturesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << " align=\"center\">" << pSig->GetRobustness() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_miniSignaturesIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_miniSignaturesLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                //for( pStem = pSig->GetStemPtrList()->first(); pStem; pStem = pSig->GetStemPtrList()->next() )
                                                for (int z = 0; z < pSig->GetStemPtrList()->size();z++)
                                                {       pStem = pSig->GetStemPtrList()->at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE, type, url ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_miniSignaturesLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }

                                *out << "\t\t\t</table>\n";

                                *out << getHTMLFooter();

                                file->close();
                                delete file; file = NULL;
                                delete out; out = NULL;
                        }
                }
        }
}


void ExportWizard::exportMiniStems()
{
        QFile* file;
        Q3TextStream* out;

        CStem* pStem;
        CSignature* pSig;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int i, mini,
                width, start,
                end, index;

        QString line, field, fileName, url, type;

        CMiniLexicon* pMini;
        for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
        {
                pMini = m_pLexicon->GetMiniLexicon(mini);
                if( !pMini || !pMini->GetStems() ) continue;
                if( pMini->GetStems()->GetCount() == 0 ) continue;

                fileName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_STEMS_FILE_TITLE;
                fileName.replace( " ", "_" );

                // Write simple text file
                if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".txt" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                fieldWidths.clear();

                                // Get field widths
                                if( m_miniStemsUniformFieldWidthsFlag->isChecked() )
                                {
                                        if( m_miniStemsColumnTitlesFlag->isChecked() )
                                        {
                                                fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                                fieldWidths[STEM_FIELD] = STEM_FIELD_TITLE.length();
                                                fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                                fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                                fieldWidths[TYPE_FIELD] = TYPE_FIELD_TITLE.length();
                                                fieldWidths[SIGNATURE_FIELD] = SIGNATURE_FIELD_TITLE.length();
                                                fieldWidths[ORIGIN_FIELD] = ORIGIN_FIELD_TITLE.length();
                                        }

                                        pMini->GetStems()->Sort(PARSE_SIZE);
                                        for( i = 0; i < pMini->GetStems()->GetCount(); i++ )
                                        {
                                                pStem = pMini->GetStems()->GetAtSort(i);

                                                pSig = pStem->GetSuffixSignature();
                                                if( pSig == NULL ) pSig = pStem->GetPrefixSignature();

                                                if( m_miniStemsLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( i + 1 ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_miniStemsLine->text().find( STEM_FIELD ) >= 0 )
                                                {
                                                        width = pStem->Display(  filter  ).length();
                                                        if( width > fieldWidths[STEM_FIELD] ) fieldWidths[STEM_FIELD] = width;
                                                }
                                                if( m_miniStemsLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pStem->CalculateDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_miniStemsLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pStem->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_miniStemsLine->text().find( TYPE_FIELD ) >= 0 )
                                                {
                                                        width = pStem->DisplayStemType().length();
                                                        if( width > fieldWidths[TYPE_FIELD] ) fieldWidths[TYPE_FIELD] = width;
                                                }
                                                if( m_miniStemsLine->text().find( SIGNATURE_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->Display( '.', filter ).length();
                                                        else width = 0;
                                                        if( width > fieldWidths[SIGNATURE_FIELD] ) fieldWidths[SIGNATURE_FIELD] = width;
                                                }
                                                if( m_miniStemsLine->text().find( ORIGIN_FIELD ) >= 0 )
                                                {
                                                        if( pSig ) width = pSig->GetRemark().length();
                                                        else width = pStem->GetConfidence().length();
                                                        if( width > fieldWidths[ORIGIN_FIELD] ) fieldWidths[ORIGIN_FIELD] = width;
                                                }
                                        }
                                }


                                // Prepare stream
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );


                                // Add title line
                                if( m_miniStemsColumnTitlesFlag->isChecked() )

                                *out << "# ";

                                line = m_miniStemsLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == STEM_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                *out << STEM_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }
                                        if( field == TYPE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                *out << TYPE_FIELD_TITLE;
                                        }
                                        if( field == SIGNATURE_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                *out << SIGNATURE_FIELD_TITLE;
                                        }
                                        if( field == ORIGIN_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[ORIGIN_FIELD] );
                                                *out << ORIGIN_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;


                                // Sort appropriately
                                if( m_miniStemsCorpusCountSortFlag->isChecked() ) pMini->GetStems()->Sort(CORPUSCOUNT);
                                else pMini->GetStems()->Sort(KEY);

                                // Output text file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetStems()->GetCount(); i++ )
                                {
                                        pStem = pMini->GetStems()->GetAtSort(i);

                                        pSig = pStem->GetSuffixSignature();
                                        if( pSig == NULL ) pSig = pStem->GetPrefixSignature();

                                        if( m_miniStemsColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_miniStemsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index++;
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_FIELD] );
                                                        *out << pStem->Display(  filter  );
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pStem->GetCorpusCount();
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pStem->CalculateDL();
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[TYPE_FIELD] );
                                                        *out << pStem->DisplayStemType();
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SIGNATURE_FIELD] );
                                                        if( pSig ) *out << getLParseText( pSig );
                                                        else *out << " ";
                                                }
                                                if( field == ORIGIN_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SOURCE_FIELD] );
/*							if( pSig ) *out << pSig->GetRemark();
                                                        else*/ *out << pStem->GetConfidence();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;
                                }

                                file->close();
                                delete file; file = NULL;
                                delete out;	out = NULL;
                        }
                }

                // Write mark-up file
                if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".html" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );

                                // Output html file stuff
                                *out << getHTMLHeader( m_projectName->text(), MINI_STEMS_FILE_TITLE, m_language->text(), m_researchers->text(), pMini->GetIndex() );

                                *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                                // Add title line
                                if( m_miniStemsColumnTitlesFlag->isChecked() )
                                {
                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniStemsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << STEM_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << TYPE_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SIGNATURE_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == ORIGIN_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << ORIGIN_FIELD_TITLE << "</span></td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";
                                }


                                // Sort appropriately
                                if( m_miniStemsCorpusCountSortFlag->isChecked() ) pMini->GetStems()->Sort(CORPUSCOUNT);
                                else pMini->GetStems()->Sort(KEY);


                                // Output html file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetStems()->GetCount(); i++ )
                                {
                                        pStem = pMini->GetStems()->GetAtSort(i);

                                        pSig = pStem->GetSuffixSignature();
                                        if( pSig == NULL ) pSig = pStem->GetPrefixSignature();

                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniStemsLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << index++ << "</td>\n";
                                                }
                                                if( field == STEM_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\"><a name=\"_" << pStem->Display(  filter  ) << "_\" class=\"bookmark\">" << getLParseText( pStem, TRUE, TRUE ) << "</a></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" align=\"center\">" << pStem->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pStem->CalculateDL() << "</td>\n";
                                                }
                                                if( field == TYPE_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pStem->DisplayStemType() << "</td>\n";
                                                }
                                                if( field == SIGNATURE_FIELD )
                                                {
                                                        url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_SIGNATURES_FILE_TITLE + ".html";
                                                        url.replace( " ", "_" );
                                                        type = "signature";
                                                        if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << getLParseText( pSig, TRUE, FALSE, type, url ) << "</td>\n";
                                                        else *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">&nbsp;</td>\n";
                                                }
                                                if( field == ORIGIN_FIELD )
                                                {
/*							if( pSig ) *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pSig->GetRemark() << "</td>\n";
                                                        else*/ *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\">" << pStem->GetConfidence() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_miniStemsLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }

                                *out << "\t\t\t</table>\n";

                                *out << getHTMLFooter();

                                file->close();
                                delete file; file = NULL;
                                delete out; out = NULL;
                        }
                }
        }
}


void ExportWizard::exportMiniSuffixes()
{
        QFile* file;
        Q3TextStream* out;

        CSuffix* pSuffix;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int i, mini,
                width, start,
                end, index,
                count;

        QString line, field, fileName, url, type = "stem";

        CMiniLexicon* pMini;
        for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
        {
                pMini = m_pLexicon->GetMiniLexicon(mini);
                if( !pMini || !pMini->GetSuffixes() ) continue;
                if( pMini->GetSuffixes()->GetCount() == 0 ) continue;

                fileName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_SUFFIXES_FILE_TITLE;
                fileName.replace( " ", "_" );

                url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_STEMS_FILE_TITLE + ".html";
                url.replace( " ", "_" );


                // Write simple text file
                if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".txt" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                fieldWidths.clear();

                                // Get field widths
                                if( m_miniSuffixesUniformFieldWidthsFlag->isChecked() )
                                {
                                        if( m_miniSuffixesColumnTitlesFlag->isChecked() )
                                        {
                                                fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                                fieldWidths[SUFFIX_FIELD] = SUFFIX_FIELD_TITLE.length();
                                                fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                                fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                                fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                                if( m_miniSuffixesIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                        }

                                        pMini->GetSuffixes()->Sort(PARSE_SIZE);
                                        for( i = 0; i < pMini->GetSuffixes()->GetCount(); i++ )
                                        {
                                                pSuffix = pMini->GetSuffixes()->GetAtSort(i);

                                                if( m_miniSuffixesLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( i + 1 ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_miniSuffixesLine->text().find( SUFFIX_FIELD ) >= 0 )
                                                {
                                                        width = pSuffix->Display(  filter  ).length();
                                                        if( width > fieldWidths[SUFFIX_FIELD] ) fieldWidths[SUFFIX_FIELD] = width;
                                                }
                                                if( m_miniSuffixesLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->ComputeDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_miniSuffixesLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_miniSuffixesLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pSuffix->GetUseCount() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }
                                                if( m_miniSuffixesIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        //for( pStem = pSuffix->GetStems()->first(); pStem; pStem = pSuffix->GetStems()->next() )
                                                        for (int z = 0; z < pSuffix->GetStems()->size(); z++)
                                                        {       pStem = pSuffix->GetStems()->at(z);
                                                                if( width < static_cast <int> (pStem->Display(  filter  ).length()) ) width = static_cast <int> (pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }


                                // Prepare stream
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );


                                // Add title line
                                if( m_miniSuffixesColumnTitlesFlag->isChecked() )

                                *out << "# ";

                                line = m_miniSuffixesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == SUFFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                *out << SUFFIX_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;


                                // Sort appropriately
                                if( m_miniSuffixesCorpusCountSortFlag->isChecked() ) pMini->GetSuffixes()->Sort(CORPUSCOUNT);
                                else pMini->GetSuffixes()->Sort(KEY);

                                // Output text file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetSuffixes()->GetCount(); i++ )
                                {
                                        pSuffix = pMini->GetSuffixes()->GetAtSort(i);

                                        if( m_miniSuffixesColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_miniSuffixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index++;
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[SUFFIX_FIELD] );
                                                        *out << pSuffix->Display(  filter  );
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pSuffix->GetCorpusCount();
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pSuffix->ComputeDL();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pSuffix->GetUseCount();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_miniSuffixesIncludeStemListFlag->isChecked() )
                                        {
                                                count = 0;
                                                if( m_miniSuffixesColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pSuffix->GetStems()->first(); pStem; pStem = pSuffix->GetStems()->next() )
                                                for (int z = 0; z < pSuffix->GetStems()->size(); z++)
                                                {       pStem = pSuffix->GetStems()->at(z);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_miniSuffixesColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }

                                file->close();
                                delete file; file = NULL;
                                delete out;	out = NULL;
                        }
                }

                // Write mark-up file
                if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".html" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );

                                // Output html file stuff
                                *out << getHTMLHeader( m_projectName->text(), MINI_SUFFIXES_FILE_TITLE, m_language->text(), m_researchers->text(), pMini->GetIndex() );

                                *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                                // Add title line
                                if( m_miniSuffixesColumnTitlesFlag->isChecked() )
                                {
                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniSuffixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << SUFFIX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";
                                }


                                // Sort appropriately
                                if( m_miniSuffixesCorpusCountSortFlag->isChecked() ) pMini->GetSuffixes()->Sort(CORPUSCOUNT);
                                else pMini->GetSuffixes()->Sort(KEY);


                                // Output html file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetSuffixes()->GetCount(); i++ )
                                {
                                        pSuffix = pMini->GetSuffixes()->GetAtSort(i);

                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniSuffixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index++ << "</td>\n";
                                                }
                                                if( field == SUFFIX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << "<a name=\"_" << pSuffix->Display(  filter  ) << "_\" class=\"bookmark\">" << getLParseText( pSuffix, TRUE, TRUE ) << "</a></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSuffix->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSuffix->GetUseCount() << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniSuffixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pSuffix->ComputeDL() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_miniSuffixesIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_miniSuffixesLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                //for( pStem = pSuffix->GetStems()->first(); pStem; pStem = pSuffix->GetStems()->next() )
                                                for (int z = 0; z < pSuffix->GetStems()->size(); z++)
                                                {       pStem = pSuffix->GetStems()->at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE, type, url ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_miniSuffixesLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }

                                *out << "\t\t\t</table>\n";

                                *out << getHTMLFooter();

                                file->close();
                                delete file; file = NULL;
                                delete out; out = NULL;
                        }
                }
        }

}


void ExportWizard::exportMiniPrefixes()
{
        QFile* file;
        Q3TextStream* out;

        CPrefix* pPrefix;
        CStem* pStem;

        StringToString* filter = m_pLexicon->GetOutFilter();

        QMap<QString,int> fieldWidths;
        int i, mini,
                width, start,
                end, index,
                count;

        QString line, field, fileName, url, type = "stem";

        CMiniLexicon* pMini;
        for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
        {
                pMini = m_pLexicon->GetMiniLexicon(mini);
                if( !pMini || !pMini->GetPrefixes() ) continue;
                if( pMini->GetPrefixes()->GetCount() == 0 ) continue;

                fileName = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_PREFIXES_FILE_TITLE;
                fileName.replace( " ", "_" );

                url = m_projectName->text() + QString( "_Mini_%1_" ).arg( pMini->GetIndex() + 1 ) + MINI_STEMS_FILE_TITLE + ".html";
                url.replace( " ", "_" );


                // Write simple text file
                if( m_simpleTextFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".txt" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                fieldWidths.clear();

                                // Get field widths
                                if( m_miniPrefixesUniformFieldWidthsFlag->isChecked() )
                                {
                                        if( m_miniPrefixesColumnTitlesFlag->isChecked() )
                                        {
                                                fieldWidths[INDEX_FIELD] = INDEX_FIELD_TITLE.length();
                                                fieldWidths[PREFIX_FIELD] = PREFIX_FIELD_TITLE.length();
                                                fieldWidths[DESC_LENGTH_FIELD] = DESC_LENGTH_FIELD_TITLE.length();
                                                fieldWidths[CORPUS_COUNT_FIELD] = CORPUS_COUNT_FIELD_TITLE.length();
                                                fieldWidths[STEM_COUNT_FIELD] = STEM_COUNT_FIELD_TITLE.length();
                                                if( m_miniPrefixesIncludeStemListFlag->isChecked() ) fieldWidths[STEMS_FIELD] = 0;
                                        }

                                        pMini->GetPrefixes()->Sort(PARSE_SIZE);
                                        for( i = 0; i < pMini->GetPrefixes()->GetCount(); i++ )
                                        {
                                                pPrefix = pMini->GetPrefixes()->GetAtSort(i);

                                                if( m_miniPrefixesLine->text().find( INDEX_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( i + 1 ).length();
                                                        if( width > fieldWidths[INDEX_FIELD] ) fieldWidths[INDEX_FIELD] = width;
                                                }
                                                if( m_miniPrefixesLine->text().find( PREFIX_FIELD ) >= 0 )
                                                {
                                                        width = pPrefix->Display(  filter  ).length();
                                                        if( width > fieldWidths[PREFIX_FIELD] ) fieldWidths[PREFIX_FIELD] = width;
                                                }
                                                if( m_miniPrefixesLine->text().find( DESC_LENGTH_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->ComputeDL() ).length();
                                                        if( width > fieldWidths[DESC_LENGTH_FIELD] ) fieldWidths[DESC_LENGTH_FIELD] = width;
                                                }
                                                if( m_miniPrefixesLine->text().find( CORPUS_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->GetCorpusCount() ).length();
                                                        if( width > fieldWidths[CORPUS_COUNT_FIELD] ) fieldWidths[CORPUS_COUNT_FIELD] = width;
                                                }
                                                if( m_miniPrefixesLine->text().find( STEM_COUNT_FIELD ) >= 0 )
                                                {
                                                        width = QString( "%1" ).arg( pPrefix->GetUseCount() ).length();
                                                        if( width > fieldWidths[STEM_COUNT_FIELD] ) fieldWidths[STEM_COUNT_FIELD] = width;
                                                }
                                                if( m_miniPrefixesIncludeStemListFlag->isChecked() )
                                                {
                                                        width = 0;
                                                        //for( pStem = pPrefix->GetStems()->first(); pStem; pStem = pPrefix->GetStems()->next() )
                                                        for (int z = 0; z < pPrefix->GetStems()->size(); z++)
                                                        {
                                                                pStem = pPrefix->GetStems()->at(z);
                                                                if( width < static_cast <int> (pStem->Display(  filter  ).length()) ) width = static_cast <int> ( pStem->Display(  filter  ).length());
                                                        }
                                                        if( width > fieldWidths[STEMS_FIELD] ) fieldWidths[STEMS_FIELD] = width;
                                                }
                                        }
                                }


                                // Prepare stream
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );


                                // Add title line
                                if( m_miniPrefixesColumnTitlesFlag->isChecked() )

                                *out << "# ";

                                line = m_miniPrefixesLine->text();

                                Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                while( line.length() > 0 )
                                {
                                        start = line.find( "%" );

                                        if( start < 0 )
                                        {
                                                *out << line;
                                                break;
                                        }

                                        *out << line.left( start );
                                        line = line.mid( start );
                                        end = line.find( "%", 1 );
                                        field = line.mid( 0, end + 1 );

                                        if( field == INDEX_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                *out << INDEX_FIELD_TITLE;
                                        }
                                        if( field == PREFIX_FIELD )
                                        {
                                                out->setf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                *out << PREFIX_FIELD_TITLE;
                                        }
                                        if( field == CORPUS_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                *out << CORPUS_COUNT_FIELD_TITLE;
                                        }
                                        if( field == STEM_COUNT_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                *out << STEM_COUNT_FIELD_TITLE;
                                        }
                                        if( field == DESC_LENGTH_FIELD )
                                        {
                                                out->unsetf(2);
                                                if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                *out << DESC_LENGTH_FIELD_TITLE;
                                        }

                                        line = line.mid( end + 1 );
                                }

                                *out << endl;


                                // Sort appropriately
                                if( m_miniPrefixesCorpusCountSortFlag->isChecked() ) pMini->GetPrefixes()->Sort(CORPUSCOUNT);
                                else pMini->GetPrefixes()->Sort(KEY);

                                // Output text file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetPrefixes()->GetCount(); i++ )
                                {
                                        pPrefix = pMini->GetPrefixes()->GetAtSort(i);

                                        if( m_miniPrefixesColumnTitlesFlag->isChecked() ) *out << "  ";

                                        line = m_miniPrefixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 )
                                                {
                                                        *out << line;
                                                        break;
                                                }

                                                *out << line.left( start );
                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[INDEX_FIELD] );
                                                        *out << index++;
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        out->setf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[PREFIX_FIELD] );
                                                        *out << pPrefix->Display(  filter  );
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[CORPUS_COUNT_FIELD] );
                                                        *out << pPrefix->GetCorpusCount();
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[DESC_LENGTH_FIELD] );
                                                        *out << pPrefix->ComputeDL();
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        out->unsetf(2);
                                                        if( fieldWidths.count() > 0 ) out->width( fieldWidths[STEM_COUNT_FIELD] );
                                                        *out << pPrefix->GetUseCount();
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << endl;

                                        if( m_miniPrefixesIncludeStemListFlag->isChecked() )
                                        {
                                                count = 0;
                                                if( m_miniPrefixesColumnTitlesFlag->isChecked() )
                                                {
                                                        *out << "# " << STEMS_FIELD_TITLE << endl;
                                                        *out << "# -------------------------------------------\n";
                                                }
                                                //for( pStem = pPrefix->GetStems()->first(); pStem; pStem = pPrefix->GetStems()->next() )
                                                for (int z = 0; z < pPrefix->GetStems()->size(); z++)
                                                {       pStem = pPrefix->GetStems()->at(z);
                                                        if( count % 5 == 0 )
                                                        {
                                                                *out << endl;

                                                                if( m_miniPrefixesColumnTitlesFlag->isChecked() ) *out << "  ";
                                                        }

                                                        out->setf(2);
                                                        out->width( fieldWidths[STEMS_FIELD] + 1 );
                                                        *out << pStem->Display(  filter  );
                                                        count++;
                                                }

                                                *out << "\n\n\n";
                                        }
                                }

                                file->close();
                                delete file; file = NULL;
                                delete out;	out = NULL;
                        }
                }

                // Write mark-up file
                if( m_markUpFlag->isChecked() || m_bothFlag->isChecked() )
                {
                        file = new QFile( fileName + ".html" );
                        if( file->open( QIODevice::WriteOnly ) )
                        {
                                out = new Q3TextStream( file );
                                out->setEncoding( Q3TextStream::Unicode );

                                // Output html file stuff
                                *out << getHTMLHeader( m_projectName->text(), MINI_PREFIXES_FILE_TITLE, m_language->text(), m_researchers->text(), pMini->GetIndex() );

                                *out << "\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"0px\">\n";

                                // Add title line
                                if( m_miniPrefixesColumnTitlesFlag->isChecked() )
                                {
                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniPrefixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );

                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << INDEX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << PREFIX_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << CORPUS_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\" align=\"center\"><span class=\"title\">" << STEM_COUNT_FIELD_TITLE << "</span></td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td style=\"border-bottom : 2px solid #1B2025;\"><span class=\"title\">" << DESC_LENGTH_FIELD_TITLE << "</span></td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";
                                }


                                // Sort appropriately
                                if( m_miniPrefixesCorpusCountSortFlag->isChecked() ) pMini->GetPrefixes()->Sort(CORPUSCOUNT);
                                else pMini->GetPrefixes()->Sort(KEY);


                                // Output html file stuff
                                index = 1;
                                for( i = 0; i < pMini->GetPrefixes()->GetCount(); i++ )
                                {
                                        pPrefix = pMini->GetPrefixes()->GetAtSort(i);

                                        *out << "\t\t\t\t<tr>\n";

                                        line = m_miniPrefixesLine->text();

                                        Q_ASSERT( line.count( "%" ) % 2 == 0 );

                                        while( line.length() > 0 )
                                        {
                                                start = line.find( "%" );
                                                if( start < 0 ) break;

                                                line = line.mid( start );
                                                end = line.find( "%", 1 );
                                                field = line.mid( 0, end + 1 );

                                                if( field == INDEX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << index++ << "</td>\n";
                                                }
                                                if( field == PREFIX_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << "<a name=\"_" << pPrefix->Display(  filter  ) << "_\" class=\"bookmark\">" << getLParseText( pPrefix, TRUE, TRUE ) << "</a></td>\n";
                                                }
                                                if( field == CORPUS_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pPrefix->GetCorpusCount() << "</td>\n";
                                                }
                                                if( field == STEM_COUNT_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pPrefix->GetUseCount() << "</td>\n";
                                                }
                                                if( field == DESC_LENGTH_FIELD )
                                                {
                                                        *out << "\t\t\t\t\t<td";
                                                        if( !m_miniPrefixesIncludeStemListFlag->isChecked() ) *out << " style=\"border-bottom : 1px solid #5A6C7E;\"";
                                                        *out << ">" << pPrefix->ComputeDL() << "</td>\n";
                                                }

                                                line = line.mid( end + 1 );
                                        }

                                        *out << "\t\t\t\t</tr>\n";

                                        if( m_miniPrefixesIncludeStemListFlag->isChecked() )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td style=\"border-bottom : 1px solid #5A6C7E;\" colspan=\"" << ( m_miniPrefixesLine->text().count( "%" ) / 2 ) << "\">\n";
                                                *out << "\t\t\t\t\t\t<span class=\"title\">" << STEMS_FIELD_TITLE << "</span><br>\n";
                                                *out << "\t\t\t\t\t\t<table cellspacing=\"0px\" cellpadding=\"5px\" border=\"1px\">\n";

                                                count = 0;
                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                //for( pStem = pPrefix->GetStems()->first(); pStem; pStem = pPrefix->GetStems()->next() )
                                                for (int z= 0; z < pPrefix->GetStems()->size(); z++)
                                                {
                                                        pStem = pPrefix->GetStems()->at(z);
                                                        if( count > 0 && count % 5 == 0 )
                                                        {
                                                                *out << "\t\t\t\t\t\t\t</tr>\n";
                                                                *out << "\t\t\t\t\t\t\t<tr>\n";
                                                        }

                                                        *out << "\t\t\t\t\t\t\t\t<td>" << getLParseText( pStem, TRUE, FALSE, type, url ) << "</td>\n";
                                                        count++;
                                                }
                                                while( count > 5 && count % 5 != 0 )
                                                {
                                                        *out << "\t\t\t\t\t\t\t\t<td>&nbsp;</td>\n";
                                                        count++;
                                                }

                                                *out << "\t\t\t\t\t\t\t</tr>\n";

                                                *out << "\t\t\t\t\t\t</table><br>\n";
                                                *out << "\t\t\t\t\t</td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }

                                        if( index % 20 == 0 )
                                        {
                                                *out << "\t\t\t\t<tr>\n";
                                                *out << "\t\t\t\t\t<td colspan=\"" + QString( "%1" ).arg( m_miniPrefixesLine->text().count( "%" ) / 2 ) + "\" style=\"border-bottom : 1px solid #5A6C7E;\" align=\"right\"><a href=\"#top\">Return to top</a></td>\n";
                                                *out << "\t\t\t\t</tr>\n";
                                        }
                                }

                                *out << "\t\t\t</table>\n";

                                *out << getHTMLFooter();

                                file->close();
                                delete file; file = NULL;
                                delete out; out = NULL;
                        }
                }
        }
}


void ExportWizard::exportIndex()
{
        QString projectName = m_projectName->text(),
                        language = m_language->text(),
                        researchers = m_researchers->text(),
                        url, projectTitle = projectName,
                        miniName;

        CMiniLexicon* pMini;
        int mini;

        projectTitle.replace( " ", "_" );

        QFile* file = new QFile( "index.html" );
        if( file->open( QIODevice::WriteOnly ) )
        {
                Q3TextStream* out;
                out = new Q3TextStream( file );
                out->setEncoding( Q3TextStream::Unicode );

                // Output html file stuff
                *out << getHTMLHeader( m_projectName->text(), QString::null, m_language->text(), m_researchers->text() );

                *out << "\t\t\t<table cellpadding=\"3px\" cellspacing=\"0px\" border=\"0px\">\n";

                if( ( m_brokenCorpusFlag->isChecked() && m_pLexicon->GetCorpus()->count() > 0 ) ||
                        ( m_corpusWordsFlag->isChecked() && m_pLexicon->GetWords()->GetCount() > 0 ) )
                {
                        *out << "\t\t\t<tr>\n";
                        *out << "\t\t\t\t<td colspan=\"3\">&nbsp;</td>\n";
                        *out << "\t\t\t</tr>\n\t\t\t<tr>\n";
                        *out << "\t\t\t\t<td align=\"left\" colspan=\"3\"><div class=\"title\">Corpus:</div></td>\n";
                        *out << "\t\t\t</tr>\n";
                }
                if( m_brokenCorpusFlag->isChecked() && m_pLexicon->GetCorpus()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + BROKEN_CORPUS_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << BROKEN_CORPUS_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetTokenCount() == 1 ) *out << "\t\t\t\t\t<td>1 token</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetTokenCount() << " tokens</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_corpusWordsFlag->isChecked() && m_pLexicon->GetWords()->GetCount() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + CORPUS_WORDS_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << CORPUS_WORDS_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetWords()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 word</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetWords()->GetCount() << " words</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }


                if( ( m_allWordsFlag->isChecked() && m_pLexicon->GetAllWords()->count() > 0 ) ||
                        ( m_allStemsFlag->isChecked() && m_pLexicon->GetAllStems()->count() > 0 ) ||
                        ( m_compoundsFlag->isChecked() && m_pLexicon->GetCompounds()->GetCount() > 0 ) ||
                        ( m_allSuffixesFlag->isChecked() && m_pLexicon->GetAllSuffixes()->count() > 0 ) ||
                        ( m_allSuffixSigsFlag->isChecked() && m_pLexicon->GetAllSuffixSigs()->count() > 0 ) ||
                        ( m_allPrefixesFlag->isChecked() && m_pLexicon->GetAllPrefixes()->count() > 0 ) ||
                        ( m_allPrefixSigsFlag->isChecked() && m_pLexicon->GetAllPrefixSigs()->count() > 0 ) )
                {
                        *out << "\t\t\t<tr>\n";
                        *out << "\t\t\t\t<td colspan=\"3\">&nbsp;</td>\n";
                        *out << "\t\t\t</tr>\n\t\t\t<tr>\n";
                        *out << "\t\t\t\t<td align=\"left\" colspan=\"3\"><div class=\"title\">Lexicon:</div></td>\n";
                        *out << "\t\t\t</tr>\n";
                }
                if( m_allWordsFlag->isChecked() && m_pLexicon->GetAllWords()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + ALL_WORDS_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << ALL_WORDS_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetAllWords()->count() == 1 ) *out << "\t\t\t\t\t<td>1 word</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetAllWords()->count() << " words</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_allStemsFlag->isChecked() && m_pLexicon->GetAllStems()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + ALL_STEMS_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << ALL_STEMS_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetAllStems()->count() == 1 ) *out << "\t\t\t\t\t<td>1 stem</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetAllStems()->count() << " stems</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_allSuffixesFlag->isChecked() && m_pLexicon->GetAllSuffixes()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + ALL_SUFFIXES_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << ALL_SUFFIXES_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetAllSuffixes()->count() == 1 ) *out << "\t\t\t\t\t<td>1 suffix</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetAllSuffixes()->count() << " suffixes</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_allSuffixSigsFlag->isChecked() && m_pLexicon->GetAllSuffixSigs()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + ALL_SUFFIX_SIGNATURES_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << ALL_SUFFIX_SIGNATURES_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetAllSuffixSigs()->count() == 1 ) *out << "\t\t\t\t\t<td>1 signature</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetAllSuffixSigs()->count() << " signatures</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_allPrefixesFlag->isChecked() && m_pLexicon->GetAllPrefixes()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + ALL_PREFIXES_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << ALL_PREFIXES_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetAllPrefixes()->count() == 1 ) *out << "\t\t\t\t\t<td>1 prefix</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetAllPrefixes()->count() << " prefixes</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_allPrefixSigsFlag->isChecked() && m_pLexicon->GetAllPrefixSigs()->count() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + ALL_PREFIX_SIGNATURES_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << ALL_PREFIX_SIGNATURES_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetAllPrefixSigs()->count() == 1 ) *out << "\t\t\t\t\t<td>1 signature</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetAllPrefixSigs()->count() << " signatures</td>\n";
                        *out << "\t\t\t\t</tr>\n";
                }
                if( m_compoundsFlag->isChecked() && m_pLexicon->GetCompounds()->GetCount() > 0 )
                {
                        *out << "\t\t\t\t<tr>\n";
                        *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                        *out << "\t\t\t\t\t<td>";

                        url = projectTitle + "_" + COMPOUNDS_FILE_TITLE + ".html";
                        url.replace( " ", "_" );
                        *out << "<a href=\"" + url + "\">";

                        *out << COMPOUNDS_FILE_TITLE;

                        *out << "</a>";

                        *out << "</td>\n";
                        if( m_pLexicon->GetCompounds()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 compound</td>\n";
                        else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetCompounds()->GetCount() << " compounds</td>\n";
                        *out << "\t\t\t\t</tr>\n";

                        if( m_pLexicon->GetLinkers()->GetCount() > 0 )
                        {
                                *out << "\t\t\t\t<tr>\n";
                                *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                                *out << "\t\t\t\t\t<td>";

                                url = projectTitle + "_" + LINKERS_FILE_TITLE + ".html";
                                url.replace( " ", "_" );
                                *out << "<a href=\"" + url + "\">";

                                *out << LINKERS_FILE_TITLE;

                                *out << "</a>";

                                *out << "</td>\n";
                                if( m_pLexicon->GetLinkers()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 linker</td>\n";
                                else *out << "\t\t\t\t\t<td>" << m_pLexicon->GetLinkers()->GetCount() << " linkers</td>\n";
                                *out << "\t\t\t\t</tr>\n";
                        }
                }


                // Do mini lexica
                for( mini = 0; mini < m_pLexicon->GetMiniSize(); mini++ )
                {
                        pMini = m_pLexicon->GetMiniLexicon(mini);
                        if( !pMini || !pMini->GetWords() ) continue;
                        if( pMini->GetWords()->GetCount() == 0 ) continue;

                        miniName = QString( "Mini-Lexicon %1" ).arg( pMini->GetIndex() + 1 );

                        if( ( m_miniWordsFlag->isChecked() && pMini->GetWords() && pMini->GetWords()->GetCount() > 0 ) ||
                                ( m_miniSignaturesFlag->isChecked() && pMini->GetSignatures() && pMini->GetSignatures()->GetCount() > 0 ) ||
                                ( m_miniStemsFlag->isChecked() && pMini->GetStems() && pMini->GetStems()->GetCount() > 0 ) ||
                                ( m_miniPrefixesFlag->isChecked() && pMini->GetPrefixes() && pMini->GetPrefixes()->GetCount() > 0 ) ||
                                ( m_miniSuffixesFlag->isChecked() && pMini->GetSuffixes() && pMini->GetSuffixes()->GetCount() > 0 ) )
                        {
                                *out << "\t\t\t<tr>\n";
                                *out << "\t\t\t\t<td colspan=\"3\">&nbsp;</td>\n";
                                *out << "\t\t\t</tr>\n\t\t\t<tr>\n";
                                *out << "\t\t\t\t<td align=\"left\" colspan=\"3\"><div class=\"title\">" + miniName + ":</div></td>\n";
                                *out << "\t\t\t</tr>\n";
                        }

                        miniName = QString( "Mini %1" ).arg( pMini->GetIndex() + 1 );

                        if( m_miniWordsFlag->isChecked() && pMini->GetWords() && pMini->GetWords()->GetCount() > 0 )
                        {
                                *out << "\t\t\t\t<tr>\n";
                                *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                                *out << "\t\t\t\t\t<td>";

                                url = projectTitle + "_" + miniName + "_" + MINI_WORDS_FILE_TITLE + ".html";
                                url.replace( " ", "_" );
                                *out << "<a href=\"" + url + "\">";

                                *out << MINI_WORDS_FILE_TITLE;

                                *out << "</a>";

                                *out << "</td>\n";
                                if( pMini->GetWords()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 word</td>\n";
                                else *out << "\t\t\t\t\t<td>" << pMini->GetWords()->GetCount() << " words</td>\n";
                                *out << "\t\t\t\t</tr>\n";
                        }
                        if( m_miniStemsFlag->isChecked() && pMini->GetStems() && pMini->GetStems()->GetCount() > 0 )
                        {
                                *out << "\t\t\t\t<tr>\n";
                                *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                                *out << "\t\t\t\t\t<td>";

                                url = projectTitle + "_" + miniName + "_" + MINI_STEMS_FILE_TITLE + ".html";
                                url.replace( " ", "_" );
                                *out << "<a href=\"" + url + "\">";

                                *out << MINI_STEMS_FILE_TITLE;

                                *out << "</a>";

                                *out << "</td>\n";
                                if( pMini->GetStems()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 stem</td>\n";
                                else *out << "\t\t\t\t\t<td>" << pMini->GetStems()->GetCount() << " stems</td>\n";
                                *out << "\t\t\t\t</tr>\n";
                        }
                        if( m_miniPrefixesFlag->isChecked() && pMini->GetPrefixes() && pMini->GetPrefixes()->GetCount() > 0 )
                        {
                                *out << "\t\t\t\t<tr>\n";
                                *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                                *out << "\t\t\t\t\t<td>";

                                url = projectTitle + "_" + miniName + "_" + MINI_PREFIXES_FILE_TITLE + ".html";
                                url.replace( " ", "_" );
                                *out << "<a href=\"" + url + "\">";

                                *out << MINI_PREFIXES_FILE_TITLE;

                                *out << "</a>";

                                *out << "</td>\n";
                                if( pMini->GetPrefixes()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 prefix</td>\n";
                                else *out << "\t\t\t\t\t<td>" << pMini->GetPrefixes()->GetCount() << " prefixes</td>\n";
                                *out << "\t\t\t\t</tr>\n";
                        }
                        if( m_miniSuffixesFlag->isChecked() && pMini->GetSuffixes() && pMini->GetSuffixes()->GetCount() > 0 )
                        {
                                *out << "\t\t\t\t<tr>\n";
                                *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                                *out << "\t\t\t\t\t<td>";

                                url = projectTitle + "_" + miniName + "_" + MINI_SUFFIXES_FILE_TITLE + ".html";
                                url.replace( " ", "_" );
                                *out << "<a href=\"" + url + "\">";

                                *out << MINI_SUFFIXES_FILE_TITLE;

                                *out << "</a>";

                                *out << "</td>\n";
                                if( pMini->GetSuffixes()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 suffix</td>\n";
                                else *out << "\t\t\t\t\t<td>" << pMini->GetSuffixes()->GetCount() << " suffixes</td>\n";
                                *out << "\t\t\t\t</tr>\n";
                        }
                        if( m_miniSignaturesFlag->isChecked() && pMini->GetSignatures() && pMini->GetSignatures()->GetCount() > 0 )
                        {
                                *out << "\t\t\t\t<tr>\n";
                                *out << "\t\t\t\t\t<td>&nbsp;</td>\n";
                                *out << "\t\t\t\t\t<td>";

                                url = projectTitle + "_" + miniName + "_" + MINI_SIGNATURES_FILE_TITLE + ".html";
                                url.replace( " ", "_" );
                                *out << "<a href=\"" + url + "\">";

                                *out << MINI_SIGNATURES_FILE_TITLE;

                                *out << "</a>";

                                *out << "</td>\n";
                                if( pMini->GetSignatures()->GetCount() == 1 ) *out << "\t\t\t\t\t<td>1 signature</td>\n";
                                else *out << "\t\t\t\t\t<td>" << pMini->GetSignatures()->GetCount() << " signatures</td>\n";
                                *out << "\t\t\t\t</tr>\n";
                        }
                }

                *out << "\t\t\t</table>\n";

                *out << getHTMLFooter();

                file->close();
                delete file; file = NULL;
                delete out; out = NULL;
        }
}
