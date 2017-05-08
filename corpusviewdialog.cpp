// Implementation of “Linguistica : Corpus View” dialog
// Copyright © 2009 The University of Chicago
#include "corpusviewdialog.h"

#include "linguisticamainwindow.h"
#include "LPreferences.h"
#include "Lexicon.h"
#include "CorpusWord.h"

CorpusViewDialog::CorpusViewDialog( QStringList* left, QStringList* right,
					QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, 0, false, fl ), Ui::CorpusViewDialogBase()
{
	setupUi( this );

	m_left = left;
	m_right = right;

	m_pLexicon = NULL;

	init();
}


CorpusViewDialog::CorpusViewDialog( CLexicon* pLexicon, QWidget* parent,
							Qt::WindowFlags fl )
    : QDialog( parent, 0, false, fl ), Ui::CorpusViewDialogBase()
{
	setupUi( this );

	m_left = pLexicon->GetCorpus();
	m_right = pLexicon->GetCorpus();

	m_pLexicon = pLexicon;

	init();
}


void CorpusViewDialog::init()
{
	m_lx = 0;
	m_ly = 0;

	m_rx = 0;
	m_ry = 0;

	if( m_pLexicon ) 
	{
		m_showMarkedUpTextCheckBox->setEnabled( TRUE );
	}

	m_scrolling = FALSE;

	m_leftTextEdit->setText( m_left->join( "\n\n" ) );
	m_rightTextEdit->setText( m_right->join( "\n\n" ) );
}


void CorpusViewDialog::showMarkedUpText( bool b )
{
	CCorpusWord* pCorpusWord;
	CLParse* pMorpheme;
	
	StringToString* OutFilter = m_pLexicon->GetOutFilter();

	if(b && m_pLexicon)
	{
		m_leftTextEdit->setText( m_left->join( "\n\n" ) );
		m_rightTextEdit->clear();

		// Mark up the text in the right edit using lexical
		// information
		for( QStringList::Iterator lineIt = m_right->begin(); lineIt != m_right->end(); ++lineIt )
		{
			QStringList line = QStringList::split( " ", *lineIt );

			for( QStringList::Iterator wordIt = line.begin(); wordIt != line.end(); ++wordIt )
			{
				pCorpusWord = m_pLexicon->GetCorpusMap()->find( *wordIt );
				
				if( pCorpusWord )
				{
					if( pCorpusWord->Size() > 1 )
					{
						for( int i = 1; i <= pCorpusWord->Size(); i++ )
						{
							pMorpheme = pCorpusWord->GetMorpheme(i);

							if( !pMorpheme ) 
							{
								setRightStyle( "Error" );
								m_rightTextEdit->insert( pCorpusWord->GetPiece(i).Display( OutFilter ) );
								setRightStyle( "Main" );
								if( i < pCorpusWord->Size() ) m_rightTextEdit->insert( "+" );
								continue;
							}

							switch( pMorpheme->GetType() )
							{
							case STEM_CLASS:
								// Print with stem mark-up
								setRightStyle( "Stem" );
								m_rightTextEdit->insert( pMorpheme->Display( OutFilter ) );
								setRightStyle( "Main" );
								if( i < pCorpusWord->Size() ) m_rightTextEdit->insert( "+" );
								break;
							case SUFFIX_CLASS:
							case PREFIX_CLASS:
							case LINKER_CLASS:
								// Print with affix mark-up
								setRightStyle( "Affix" );
								m_rightTextEdit->insert( pMorpheme->Display( OutFilter ) );
								setRightStyle( "Main" );
								if( i < pCorpusWord->Size() ) m_rightTextEdit->insert( "+" );
								break;
							default:
								// Don't know why, print with error mark-up
								setRightStyle( "Error" );
								m_rightTextEdit->insert( pMorpheme->Display( OutFilter ) );
								setRightStyle( "Main" );
								if( i < pCorpusWord->Size() ) m_rightTextEdit->insert( "+" );
								break;
							}
						}
					}
					else
					{
						// CorpusWord is an unanalyzed word, print with word
						// mark-up
						setRightStyle( "Word" );
						m_rightTextEdit->insert( pCorpusWord->Display( OutFilter ) );
						setRightStyle( "Main" );
					}

					m_rightTextEdit->insert( " " );
				}
				else
				{
					// CorpusWord doesn't exist, just print the string without
					// mark-up
					m_rightTextEdit->insert( *wordIt );
					m_rightTextEdit->insert( " " );
				}
			}

			// End of line;
			m_rightTextEdit->insert( "\n\n" );
		}
	}
	else
	{
		m_leftTextEdit->setText( m_left->join( "\n\n" ) );
		m_rightTextEdit->setText( m_right->join( "\n\n" ) );
	}
}


void CorpusViewDialog::moveRightView( int x, int y )
{
	if( !m_bindScrollBarsCheckBox->isChecked() ) return;
	if( m_scrolling ) return;

	int byX = x - m_lx,
		byY = y - m_ly;

	m_lx = x;
	m_ly = y;

	m_scrolling = TRUE;
	m_rightTextEdit->scrollBy( byX, byY );
	m_scrolling = FALSE;
}


void CorpusViewDialog::moveLeftView( int x, int y )
{
	if( !m_bindScrollBarsCheckBox->isChecked() ) return;
	if( m_scrolling ) return;

	int byX = x - m_rx,
		byY = y - m_ry;

	m_rx = x;
	m_ry = y;

	m_scrolling = TRUE;
	m_leftTextEdit->scrollBy( byX, byY );
	m_scrolling = FALSE;
}


void CorpusViewDialog::wordWrap( bool b )
{
	if(b)
	{
		m_leftTextEdit->setWordWrap( Q3TextEdit::WidgetWidth );
		m_rightTextEdit->setWordWrap( Q3TextEdit::WidgetWidth );
	}
	else
	{
		m_leftTextEdit->setWordWrap( Q3TextEdit::NoWrap );
		m_rightTextEdit->setWordWrap( Q3TextEdit::NoWrap );
	}
}


void CorpusViewDialog::setRightStyle( QString style )
{ 
	// So far, possible values are "Main", "Affix", "Stem", 
	// "Word", "Signature", and "Error". Someday there may
	// be more. Nothing happens if the style doesn't exist.

	QFont font = m_pLexicon->GetDocument()->GetEastFont();
	QString color = m_pLexicon->GetDocument()->GetPreferences()->GetPreference( style + "_Color" );
	if( color.length() == 0 ) color = "black";

	m_rightTextEdit->setColor( QColor( color ) );

	m_rightTextEdit->setFamily( font.family() );
	m_rightTextEdit->setPointSize( font.pointSize() );

	font = m_pLexicon->GetDocument()->GetPreferences()->GetFontPreference( style );
	m_rightTextEdit->setBold( font.bold() );
	m_rightTextEdit->setItalic( font.italic() );
	m_rightTextEdit->setUnderline( font.underline() );
}

