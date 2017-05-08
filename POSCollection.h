// Results from part-of-speech discovery for display
// Copyright © 2009 The University of Chicago
#ifndef POSCOLLECTION_H
#define POSCOLLECTION_H

#include <Q3PtrList>
#include "POS.h"
template<class K, class V> class QMap;

/// Result type for CMiniLexicon::FindMajorSignatures().
///
/// Basically, this is a vector of LxPoS objects (which it owns).
///
/// Each LxPoS object contains information about a family of
/// related signatures (a suspected "part of speech") for the user
/// to inspect.
///
/// Hopefully, FindMajorSignatures() should discover categories such
/// as noun, verb, and adjective.  If it does, this will allow us to
/// display a list of parts of speech to the user to help organize
/// the signature list.
class LxPoSCollection : public Q3PtrList<LxPoS> {
public:
	LxPoSCollection();
	~LxPoSCollection();

	void ListDisplay(class Q3ListView* widget);
};

#endif // POSCOLLECTION_H
