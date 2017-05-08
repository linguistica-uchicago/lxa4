// Helper class with number-of-occurences-in-corpus for a linguistic construct
// Copyright © 2009 The University of Chicago
#ifndef CORPUSCOUNT_H
#define CORPUSCOUNT_H

namespace linguistica {
	class corpus_count;
}

#include <iostream>

/// It is useful to remember how many times each morpheme, phoneme,
/// morphological signature, and part of speech occurs in the corpus
/// to be analyzed:
///
///  * The information content of an instance of that construct is
///     -log2(corpus count of construct /
///           corpus count of genre of construct)
///    [So, for example, the encoding length of "hello" is
///    -log2(# of appearances of "hello" / total # of words in corpus)]
///
///  * When displaying results, it is convenient to sort by corpus count.
///
///  * If the corpus count is very low, we can skip some costly operations
///     on a construct and be reasonably sure we are not introducing too
///     much error.
///
/// This class maintains a corpus count for a linguistic construct and
/// provides methods for accessing and modifying it.
///
/// The count is a "token count" (total number of appearances), not
/// "use count" (number of distinct contexts in which this appears).
class linguistica::corpus_count {
	/// Always nonnegative.
	int m_corpus_count;
public:
	/// thrown if corpus count drops below zero
	struct underflow { };
private:
	void check_underflow()
	{
		static bool check_enabled = false;

		if (m_corpus_count < 0) {
			using std::cerr;
			using std::endl;

			if (check_enabled) {
				// XXX. This shouldn't happen.
				cerr << "corpus count underflow for object ";
				cerr << this << ": ";
				cerr << m_corpus_count << endl;
				check_enabled = false;
			}
			m_corpus_count = 0;
		}
	}
public:
	corpus_count() : m_corpus_count(0) { }
	corpus_count(int n) : m_corpus_count(n)
	{ check_underflow(); }
	// copy constructor, assignment operator defined implicitly.
	virtual ~corpus_count() { }

	corpus_count& operator=(int n) { SetCorpusCount(n); return *this; }

	inline int GetCorpusCount() const { return m_corpus_count; }

	void IncrementCorpusCount(int incr)
	{ m_corpus_count += incr; check_underflow(); }

	void SetCorpusCount(int n)
	{ m_corpus_count = n; check_underflow(); }
};

#endif // CORPUSCOUNT_H
