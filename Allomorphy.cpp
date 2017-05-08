// Implementation of AffixAlignment, SignatureAlignment methods
// Copyright © 2009 The University of Chicago
#include "Allomorphy.h"

#include <QTextStream>
#include "Signature.h"
#include "StringSurrogate.h"
#include "Parse.h"
#include "StringFunc.h"
#include "HTML.h"
#include "Typedefs.h"

AffixAlignment::AffixAlignment(QString Affix1, QString Affix2)
	: m_OriginalAffix1(), m_OriginalAffix2(),
	m_Affix1(Affix1), m_Affix2(Affix2),
	m_Margin1(), m_Margin2(),
	m_Shift1(), m_Shift2(),
	m_Status(Affix1 == Affix2 ? IDENTICAL : DIFFERENT),
	m_Agreement_unigram(0.0),
	m_Agreement_bigram(0.0),
	m_Disagreement_unigram(0.0),
	m_Disagreement_bigram(0.0) { }

AffixAlignment::AffixAlignment(QString Margin1, QString Affix1,
		QString Margin2, QString Affix2)
	: m_OriginalAffix1(), m_OriginalAffix2(),
	m_Affix1(Affix1), m_Affix2(Affix2),
	m_Margin1(Margin1), m_Margin2(Margin2),
	m_Shift1(), m_Shift2(),
	m_Status(Affix1 == Affix2 ? IDENTICAL : DIFFERENT),
	m_Agreement_unigram(0.0),
	m_Agreement_bigram(0.0),
	m_Disagreement_unigram(0.0),
	m_Disagreement_bigram(0.0) { }

SignatureAlignment::SignatureAlignment(CSignature* Sig1, CSignature* Sig2)
	: m_SigPtr1(Sig1), m_SigPtr2(Sig2),
	m_AffixAlignments(),
	m_Sig1(Sig1), m_Sig2(Sig2),
	m_Sig1AlignedAffixes(), m_Sig2AlignedAffixes() { }

void SignatureAlignment::FindBestAlignment()
{
    QString Morph, OtherMorph, MarginPiece;
    AffixAlignment* pAlign;
	CParse Margins1, Margins2, Suffixes1, Suffixes2;
    int i, j, morphlength, morphlength2;
    CSS ssMorph, ssOtherMorph;
  
//-------------------------------- Step 1 --------------------------------------------------------//
    // first, look for identical affixes in the sigs;
    for (i = 1; i <= m_Sig1.Size(); i++)
    {
        Morph = m_Sig1.GetPiece(i).Display();
        for ( j = 1; j <= m_Sig2.Size(); j++)
        {
            OtherMorph = m_Sig2.GetPiece(j).Display();
            if (OtherMorph == Morph)
            {
                pAlign = new AffixAlignment (Morph, Morph);
                m_AffixAlignments.append( pAlign );
				if (!m_Sig1AlignedAffixes.Contains( Morph )) m_Sig1AlignedAffixes. Append ( Morph );
				if (!m_Sig2AlignedAffixes.Contains( Morph )) m_Sig2AlignedAffixes. Append ( Morph );
                break;
            }
 
        }
    }
 
//-------------------------------- Step 2 --------------------------------------------------------//
    // now look for non-identical but end-matching affix pairs, like "es/s"
	
    for ( i = 1; i <= m_Sig1.Size(); i++)  
    {
                ssMorph = m_Sig1.GetPiece(i);
		morphlength = ssMorph.GetLength();

        for ( j = 1; j <= m_Sig2.Size(); j++)
        {
			ssOtherMorph = m_Sig2.GetPiece(j);
			morphlength2 = ssOtherMorph.GetLength();
			if ( morphlength2 == morphlength ) { continue; }

 		    if ( ssOtherMorph.Right( morphlength ) == ssMorph )
            {
                    MarginPiece = ssOtherMorph.Left(morphlength2 - morphlength).Display();
                    pAlign = new AffixAlignment (TheStringNULL, ssMorph.Display(), 
                                                 MarginPiece,   ssMorph.Display() );
                    m_AffixAlignments.append(pAlign);
					Margins1. Append (TheStringNULL);
					Margins2. Append (MarginPiece);
					Suffixes1.Append (ssMorph);
					Suffixes2.Append (ssMorph);
					if (!m_Sig1AlignedAffixes.Contains( ssMorph )) m_Sig1AlignedAffixes. Append ( ssMorph );
					if (!m_Sig2AlignedAffixes.Contains( ssOtherMorph )) m_Sig2AlignedAffixes. Append ( ssOtherMorph );
			}
            if ( ssMorph.Right(morphlength2) == ssOtherMorph  )
            {
					MarginPiece = ssMorph.Left( morphlength - morphlength2 ).Display();
					pAlign = new AffixAlignment ( MarginPiece,   ssOtherMorph.Display(),
                                                TheStringNULL, ssOtherMorph.Display() );
					m_AffixAlignments.append(pAlign);
					Margins1. Append (MarginPiece);
					if (!Margins2.ContainsNULL()) Margins2. Append (TheStringNULL);
					Suffixes1.Append (ssOtherMorph);
					Suffixes2.Append (ssOtherMorph);             
					if (!m_Sig1AlignedAffixes.Contains( ssMorph      )) m_Sig1AlignedAffixes. Append ( ssMorph      );
					if (!m_Sig2AlignedAffixes.Contains( ssOtherMorph )) m_Sig2AlignedAffixes. Append ( ssOtherMorph );

            } 
        }
    }
//-------------------------------- Step 3 --------------------------------------------------------//
    // if one of the signatures has an X in its margin region, and it also has an X as an affix and the other
    // signature has a NULL, then we can align the X and the NULL:
	
	if (m_Sig1.ContainsNULL())
	{
		for ( i = 1; i <= m_Sig2.Size(); i++)
		{
			Morph = m_Sig2.GetPiece (i).Display() ;
                        if (Morph == TheStringNULL) continue;
			if ( Margins2.Contains( Morph ) )
			{
					pAlign = new AffixAlignment ( TheStringNULL, TheStringNULL,
                                                Morph, TheStringNULL);
					m_AffixAlignments.append(pAlign);
                
	                if (!Margins1. ContainsNULL())  Margins1. Append (TheStringNULL);				  
					if (!Suffixes1.ContainsNULL())  Suffixes1.Append (TheStringNULL);
					if (!Suffixes2.ContainsNULL())  Suffixes2.Append (TheStringNULL);
					if (!m_Sig1AlignedAffixes.ContainsNULL()     ) m_Sig1AlignedAffixes. Append ( TheStringNULL );
					if (!m_Sig2AlignedAffixes.Contains( Morph )  ) m_Sig2AlignedAffixes. Append ( Morph );

			}
		}
	}

	if (m_Sig2.ContainsNULL())
	{
		for ( i = 1; i <= m_Sig1.Size(); i++)
		{
            if ( m_Sig1.GetPiece(i).IsNULL() ) continue;
			Morph = m_Sig1.GetPiece (i).Display() ;
			if ( Margins1.Contains( Morph ) )
			{
					pAlign = new AffixAlignment ( Morph, TheStringNULL,
												TheStringNULL, TheStringNULL);
					m_AffixAlignments.append(pAlign);

					Margins2.Append(TheStringNULL);
					Suffixes1.Append (TheStringNULL);
					Suffixes2.Append(TheStringNULL);
					if (!m_Sig2AlignedAffixes.ContainsNULL()     ) m_Sig2AlignedAffixes. Append ( TheStringNULL );
					if (!m_Sig1AlignedAffixes.Contains( Morph )  ) m_Sig1AlignedAffixes. Append ( Morph );

			}
		}
	}
}


void SignatureAlignment::Display(QTextStream& LogStream)
{
    AffixAlignment* pAlign;
 
    if (m_AffixAlignments.count()  > 0) 
    {
        LogStream <<
            m_Sig1.Display('-') << "<br>" << m_Sig2.Display('-') << 
            StartTable      << 
            StartTableRow   <<
                MakeTableHeader ("Shift region 1")  <<
                MakeTableHeader ("Margin region 1") <<
                MakeTableHeader ("Affix 1")         <<
                MakeTableHeader ("Shift region 2")  <<
                MakeTableHeader ("Margin region 2") <<
                MakeTableHeader ("Affix 2") << 
            EndTableRow     <<  endl;
    
        for (int i = 0; i < m_AffixAlignments.size(); i++)
        {    
            pAlign = m_AffixAlignments.at(i);
            LogStream << 
                StartTableRow <<
                    TableData( pAlign->GetShift1() ) <<
                    TableData( pAlign->GetMargin1()) <<
                    TableData( pAlign->GetAffix1() ) <<
                    TableData( pAlign->GetShift2() ) <<
                    TableData( pAlign->GetMargin2()) <<
                    TableData( pAlign->GetAffix2() ) <<
                EndTableRow << endl;
        }
        
		 
		
		LogStream           << EndTable;
    }

}
