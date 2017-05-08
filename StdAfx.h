// Convenience header including just about everything
// Copyright © 2009 The University of Chicago
#ifndef STDAFX_H
#define STDAFX_H

#include "Version.h"
#include "Config.h"
#include "Typedefs.h"

// Qt
#include <qapplication.h>
#include <qnamespace.h>
#include <qmessagebox.h>
#include <q3textstream.h>
#include <qdatetime.h>
#include <qtabwidget.h>
#include <qdom.h>
#include <QList.h>
#include <q3dict.h>
#include <q3groupbox.h>
#include <qdir.h>
#include <Q3PtrCollection>

// C headers
#include <cmath>
#include <cstdlib>
#include <ctime>

// Collections
#include "CollectionTemplate.h"
#include "Trie.h"
#include "StemCollection.h"
#include "SignatureCollection.h"
#include "WordCollection.h"
#include "SuffixCollection.h"
#include "PrefixCollection.h"
#include "LinkerCollection.h"
#include "MorphemeCollection.h"
#include "BiphoneCollection.h"
#include "PhoneCollection.h"
#include "CompoundCollection.h"
#include "TerminalRuleCollection.h"
#include "CorpusWordCollection.h"
#include "RuleCollection.h"

// Parse class family
#include "Parse.h"
#include "LParse.h"
#include "Stem.h"
#include "Signature.h"
#include "Morpheme.h"
#include "Affix.h"
#include "Prefix.h"
#include "Suffix.h"
#include "Linker.h"
#include "Compound.h"
#include "GrammarRule.h"
#include "Edge.h"
#include "CorpusWord.h"

// Phone class
#include "Phone.h"
 
// Sequencer
#include "Sequencer.h"

// MT
#include "cMT.h"
#include "mTVolca.h"
#include "cMTModel1.h"
#include "cMTModel2Norm.h"

// HMM
#include "StateEmitHMM.h"

// Statistics
#include "Stats.h"

// DCN
#include "DCNcorpussyl.h"
#include "DCNdcnword.h"
#include "DCNgrammar.h"
#include "DCNgrammarsyl.h"
#include "DCNlearning.h"
#include "DCNlearningsyl.h"
#include "DCNnetwork.h"
#include "DCNnetworksyl.h"
#include "DCNsnetwork.h"

// Remaining classes
#include "canvasdialog.h"
#include "EarleyParser.h"
#include "DescriptionLength.h"
#include "DLHistory.h"
#include "SparseVector.h"
#include "SparseIntVector.h"
#include "StringSurrogate.h"
#include "MiniLexicon.h"
#include "Lexicon.h"
#include "Preferences.h"
#include "LPreferences.h"
#include "exportwizard.h"
#include "preferencesdialog.h"
#include "helpaboutdialog.h"
#include "verifydialog.h"
#include "listbuilderdialog.h"
#include "corpusviewdialog.h"
#include "linguisticamainwindow.h"
#include "GraphicView.h"
#include "StringEditGrid.h" 
#include "Alignment.h" 
#include "TemplateCollection.h"
#include "Biphone.h"
#include "VeryLong.h"
#include "Datum.h"
#include "MonteCarlo.h"

// Utility functions/variables
#include "StringFunc.h"
#include "CompareFunc.h"
#include "CommandLine.h"
#include "ScrubRules.h"
#include "HTML.h"
#include "log2.h"

#endif // STDAFX_H
