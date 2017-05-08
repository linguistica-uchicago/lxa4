// Explicit requests for implicit type conversion
// Copyright © 2009 The University of Chicago
#ifndef IMPLICIT_CAST_H
#define IMPLICIT_CAST_H

namespace linguistica {
	template<class T, class U> T implicit_cast(U x);
}

/// Helper function: Convert CPrefix* or CSuffix* to CAffix*
/// Reference: B. Stroustroup, "The C++ Programming Language"
///
/// Usage:
///	CPrefix* prefix;
///	CSuffix* suffix;
///	/* ... */
/// 	CAffix* affix = analyzingSuffixes ?
///		implicit_cast<CAffix*>(suffix) :
///		implicit_cast<CAffix*>(prefix);
template<class T, class U> T linguistica::implicit_cast(U x) { return x; }

#endif // IMPLICIT_CAST_H
