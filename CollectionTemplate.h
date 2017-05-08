// Pair-of-tries class template
// Copyright © 2009 The University of Chicago
#ifndef COLLECTIONTEMPLATE_H
#define COLLECTIONTEMPLATE_H

#include "Trie.h"

#include <QString>
#include "generaldefinitions.h"

class CMiniLexicon;
class CLexicon;
class CPrefix;
class CLParse;
class CParse;
class CSuffixCollection;
class CPrefixCollection;
class CStemCollection;

template<class T> class TCollection : public CTrie {
protected:
	int m_CorpusCount;
	bool m_DeletePointers;
	int* m_DeletionArray;
	bool m_HashHasChangedFlag;
	QString m_MemberName;
	T** m_PointerArray;
	CLexicon* m_pLexicon;
	CMiniLexicon* m_pMiniLex;
	CTrie* m_pReverseTrie;
	CNode** m_pTerminalNodeArray;
	T** m_SortArray;
	bool m_SortValidFlag;
	enum eSortStyle m_SortStyle;
	double m_TotalUseCount;
public:
	// construction/destruction.

	TCollection();
	TCollection(CMiniLexicon* Mini, QString MemberName = QString());
	TCollection(CLexicon* Lex, QString MemberName = QString());
	~TCollection();

	// disable copy
private:
	TCollection(const TCollection& x);
	TCollection& operator=(const TCollection& x);
public:

	T* operator<< ( CParse* );
	T* operator<< ( CStringSurrogate );
	T* operator<< ( QString );
	T* operator^= ( CParse* );
	T* operator^= ( CStringSurrogate );
	T* operator^= ( QString );
	T* operator[] ( uint n );

	void				AddPointer( T* );
	T*				AddToCollection( const CParse& );
	T*				AddToCollection( const CStringSurrogate& );
	bool				Contains( CStringSurrogate& );
	void				CreatePointerArray();
	void				CreateReverseTrie();
	void				DeleteMarkedMembers();
	void				DoNotDeletePointers();
	void				DumpVisibleToLogFile();
	void				DumpVisibleWords( CWordCollection* );
	void				Empty();
	CStringSurrogate	FindMaximalMajorityPrefix();
	void				FindMemberExtensions ( int, TCollection<CLParse>& );
	T*					GetAt( uint );
	CStringSurrogate	GetAt_SS( int );
	T*					GetAtSort( int n );
	CStringSurrogate	GetAtSort_SS( int );
	int GetCorpusCount() const;
	CLexicon*           GetLexicon();
	CMiniLexicon*       GetMiniLexicon();
	CTrie*              GetReverseTrie();
	int                 GetSortValidFlag();
    int 				GetTotalUseCount() { return m_TotalUseCount; }
	CTrie*              GetTrie();
	virtual eLxaClass	GetType();
	int					GetWidth( CStringSurrogate ); // i.e., from Trie
	void				IncrementCorpusCount( int n = 1 );
	void				MarkForDeletion( int );
	void				RecomputeCorpusCount();
	bool				Remove( T* ); // doesn't delete T*
	void				RemoveAll();
	bool				RemoveMember( T* ); // deletes T*
	bool				RemoveMember( const CStringSurrogate& ); // deletes T*
	bool				RemoveMember( const CStringSurrogate&, bool ); // FSA
	CLParse*			SeekChain( T*, CLParse*, int );
	void				SetKey( T*, CParse& );
	void				SetKey( T*, QString );
	void				SetSortStyle( eSortStyle );
	void				SetSortValidFlag(bool value);
	void				Sort( eSortStyle );
	void				T_PredecessorFrequency( eSuccessorFrequencyMode,
												CStemCollection* Stems = NULL,
												CPrefixCollection* Suffixes = NULL,
												int MaxNeighborPredecessorCount = 1,
												int MaximumPrefixLength = 5,
												int MinimumStemLength = 3,
												int LeftMargin = -1,
												int RightMargin = -1 );
	void				T_SuccessorFrequency( eSuccessorFrequencyMode,
											  CStemCollection* Stems = NULL,
											  CSuffixCollection* Suffixes = NULL,
											  int MaxNeighborSuccessorCount = 1,
											  int MaximumSuffixLength = 5,
											  int MinimumStemLength = 3,
											  int LeftMargin = -1,
											  int RightMargin = -1 );
};

#include "CollectionTemplate.tcc"

#endif // COLLECTIONTEMPLATE_H
