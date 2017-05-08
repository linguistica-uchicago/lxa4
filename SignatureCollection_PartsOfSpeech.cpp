// Part of speech discovery
// Copyright © 2009 The University of Chicago
#include "MiniLexicon.h"

#include <memory>
#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <QString>
#include "SignatureCollection.h"
#include "Signature.h"
#include "POS.h"
#include "POSCollection.h"
#include "Parse.h"

QString HTMLfileStart("<html><head> "
	"<link rel=\"stylesheet\" type=\"text/css\" href=\"lxa.css\"> "
	"</head>"
	"<body><table>");

void CMiniLexicon::FindMajorSignatures()
{
	// XXX. add more options, for prefixes, etc.
	// XXX. Make this a user-defined parameter
	const int NumberOfTopSignatures = 250;
	const int MinimumSignatureSize	= 2;
	const QString filename = "c:\\PartsOfSpeech.html";

	// open log file
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		// open failed
		return;
	QTextStream outf(&file);

	if (m_pPOS == 0) m_pPOS = new LxPoSCollection;

	outf << HTMLfileStart;
	outf << "<tr><th>Signature</th><th>Satellite</th></tr>";

	// For each signature: if it's good enough, make it a part of speech
	m_pSignatures->FindDisplayOrdering();
	for (int i = 0, count = 0;
			i < m_pSignatures->GetCount() &&
			count < NumberOfTopSignatures;
			++i) {
		CSignature* pSig = m_pSignatures->GetAtSort(i);

		outf << "<tr><td>" << pSig->Display('-') << "</td>";

		// hack: simulate labelled continue statement
		struct not_eligible { };
		try {
			// a sig P is a "mentor" to sig Q if P is more robust
			// than Q and P contains Q
			if (pSig->GetMentor() != 0)
				// not a part of speech: subsumed under mentor
				throw not_eligible();

			if (pSig->Size() < MinimumSignatureSize)
				// not a part of speech: too simple
				throw not_eligible();

			for (LxPoS* qPOS = m_pPOS->first();
					qPOS != 0; qPOS=m_pPOS->next()) {
				// If pSig has exactly one more affix than a
				// signature already in PoS, then pSig can't
				// be a PoS, and its extra affix is entered as a satellite.
				CSignature* qSig = qPOS->GetSignature();

				if (qSig->Size() + 1 == pSig->Size() &&
						qSig->Contains (pSig)) {
					CParse Suffix = qSig->Intersection(*pSig);
					qSig->AppendSatelliteAffix (Suffix);
					outf<< "<td>" << Suffix.Display();
					throw not_eligible();
				}
			}
		} catch (not_eligible) { continue; }

		std::auto_ptr<LxPoS> new_pos(new LxPoS(pSig, this));
		LxPoS* pPOS = new_pos.get();

		// Record affix frequencies
		for (int k = 1; k <= pSig->Size(); ++k) {
			pPOS->SetPieceValue( k, pSig->GetNumberOfStems() );
			outf << "<td>"<<pSig->GetPiece(k).Display() << "</td>";
		}

		// Calculate robustness
		pPOS->AddRobustness(pSig->GetRobustness());

		// Save part-of-speech
		m_pPOS->append(new_pos.release());
		++count;

		outf << "<td>"<< pSig->GetNumberOfStems()  <<"</td></tr>";
                CSignature *qSig;
		// For each mentee:
                for (int z = 0; z < pSig->GetMentorList()->size(); z++)
                {       qSig = pSig->GetMentorList()->at(z);
			outf << "<tr><td></td>" << qSig->Display('-');

			// Adjust robustness for mentee.
			pPOS->AddRobustness( qSig->GetRobustness() );

			// Adjust affix frequencies for mentee.
			for (int k = 1; k <= qSig->Size(); ++k) {
				pPOS->IncrementPieceValue( qSig->GetPiece(k), qSig->GetNumberOfStems() );
				outf << "<td>" << qSig->GetPiece(k).Display() <<"</td><td>" <<qSig->GetNumberOfStems() <<"</td><td>";

			}
			outf << "</tr>";
		}

		// Write affix frequencies to log.
		for (int m = 1; m <= pPOS->Size(); m++) {
			 outf << "<tr><td>" << pPOS->GetPiece(m).Display() <<"</td><td>"
				 << pPOS->GetPieceValue(m)<<"</td></tr>";
		}
	}
	outf <<"</table></body></html>";
}
