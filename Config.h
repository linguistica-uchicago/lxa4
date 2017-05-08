// Compile-time user configuration
// Copyright © 2009 The University of Chicago
#ifndef CONFIG_H
#define CONFIG_H

#include <QChar>

// Base used for filtering character sequences into
// unused unicode single characters.  2500 is the beginning
// of the box drawing characters in Unicode.
const int FILTER_BASE = 2500;

const QChar GRAMMAR_RULE_WILD_CARD = '_';

#endif // CONFIG_H
