// Affix position: initial (prefix) or final (suffix)
// Copyright © 2009 The University of Chicago
#ifndef AFFIXLOCATION_H
#define AFFIXLOCATION_H

enum eAffixLocation {
	WORD_FINAL,
	STEM_FINAL,
	STEM_INITIAL,
	WORD_INITIAL
};

inline bool is_initial(enum eAffixLocation l)
{ return l == STEM_INITIAL || l == WORD_INITIAL; }

#endif // AFFIXLOCATION_H
