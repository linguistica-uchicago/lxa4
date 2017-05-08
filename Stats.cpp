// Implementation of CStats methods
// Copyright © 2009 The University of Chicago
#include "Stats.h"

/*					CSTATS (by Jeremy O'Brien)
---------------------------------------------------------------------------------
	CStats is an object for Text Statistics. Simply put, it reads in a corpus,
	and outputs the frequently occurring words along with the number of times
	they occur and the standard deviation for them. Words with low standard
	deviation (relative to others) will be evenly distributed; words with high
	standard deviation will be unevenly distributed. Likewise, if a word is
	evenly distributed, then it is likely that it is a LOW-CONTENT word, while
	a word that is unevenly distributed will be a HIGH-CONTENT word.

*/

#include <cmath>
#include <QTextStream>
#include <Q3FileDialog>
#include <QIODevice>
#include <QFile>
#include "linguisticamainwindow.h"

typedef Q3ValueList<int> IntList;
typedef QMap<QString, IntList> StringToIntList;

/*					THINGS TO DO
-------------------------------------------------------------------------------

	(1)	better output (dialog box?)
	(2) getting better accuracy (not using unsigned long ints) while avoiding
		-1.INF errors
	(3)	have the program read in the same corpus as the "reread corpus" corpus
		(this might be too confusing for the user)

*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStats::CStats() {}

CStats::CStats(LinguisticaMainWindow* parent)
{
	m_parent = parent;
}

CStats::~CStats() {}



/////////////////////////////////////////////////////////////////////
// Reads the corpus. It makes m_StringMap into a map of words to 
// a list of indices of where these words occur in the corpus. The length
// of this list is therefore the # of occurrences.
// Note that words are make lowercase, commas and periods are removed,
// as are the 's suffixes (temporary fix)
/////////////////////////////////////////////////////////////////////

void CStats::readCorpus()
{
	m_StringMap.clear();
	QString					corpusFileName;
	QString					word;

	corpusFileName = Q3FileDialog::getOpenFileName( corpusFileName,
												 "TXT Files (*.txt)",
												 NULL,
												 "open file dialog",
												 "Choose a corpus file to open" );
	if ( corpusFileName.isEmpty() )
		return; 

	QFile corpusFile(corpusFileName);

	if ( corpusFile.open( QIODevice::ReadOnly ) ) 
	{

		Q3TextStream corpusStream( &corpusFile );
		int wordNum = 0;

		// we do stuff for each word
		while (!corpusStream.atEnd())
		{
			corpusStream >> word;

			word = word.lower();
			//QRegExp punctuation = QRegExp ( "\,|\.|\?|\'|\"");
			word.remove( "." ); word.remove( "," );
			word.remove( "'s" );	//temporary

			// the map will map strings to the indices of where they appear in the corpus
			m_StringMap[word].append(wordNum);

			// the corpus will be a QStringList representation of the file
			//m_Corpus.append(word);

			wordNum++;
			if (wordNum%512 == 0)
				m_parent->setStatusBar1(QString("reading word %1...").arg(wordNum));
		}
		
		// big distinction: m_CorpusSize is the # of words (starting at 1)
		// wordNum, or the index for an occurrence of a word, starts at 0
		m_CorpusSize = wordNum;

	}
	m_parent->setStatusBar1(QString("Reading complete"));

	corpusFile.close();

	output();
}


/////////////////////////////////////////////////////////////////////
// Although not a member function, this is the heart of the standard deviation
// system. It is very general, taking an array of numbers and the size of the array.
/////////////////////////////////////////////////////////////////////

long int standev( int* array, int N )
{
	/* formula is
	sigma = sqrt ( 1/N * [ sum (0 to N) xi^2 - N * mu^2 ] )
  http://en.wikipedia.org/math/46d26dc566d3b4ed00e4c6158bdd253e.png
    */
	using std::sqrt;

	long int				xi2		= 0;
	long int				sum		= 0;
	long int				mu		= 0;
	long int				sigma	= 0;
	
	for (int i = 0; i < N; i++)
	{
		xi2 += array[i] * array[i];
		sum += array[i];
	}

	mu = (long int) sum / (long int) N;
	sigma = sqrt( ( (long int) xi2 - (long int) N * mu * mu ) / (long int) N );
	return sigma;
}


/////////////////////////////////////////////////////////////////////
// CorpusDistribution takes a word from the corpus, and outputs the standard deviation of
// that word. Basically, it finds the distances between each occurrence of the word,
// and puts that into standev
/////////////////////////////////////////////////////////////////////

long int CStats::CorpusDistribution(QString &word) const
{

	IntList		indices		= m_StringMap[word];
	int			N			= indices.size();
	int*		array		= new int[N];

	IntList::const_iterator		it			= indices.begin();
	int						last		= indices.last();
//	IntList::const_iterator		end			= indices.end();

	int prevValue = 0;
	for (int i = 0; i < N; i++)
	{
		array[i] = *it - prevValue - 1;
		prevValue = *it;

		it++;
	}
	array[0] += m_CorpusSize - last;

	long int dist = standev(array,N);
	delete[] array;
	return dist;

}


/////////////////////////////////////////////////////////////////////
//	output is a the glue that holds this class together. This means it will probably
//	be the first to go when this class is modified. It saves the statistics to a file
//	"stats.txt", in the form of word, # of occurrences, standard deviation.
//	It goes down the map, looking at all the unique words, calculating corpus distribution
//  for each one.
/////////////////////////////////////////////////////////////////////

void CStats::output() const
{
	QFile out("stats.txt");
	out.open(QIODevice::WriteOnly);
	QTextStream outStream(&out);

	StringToIntList::const_iterator					it			= m_StringMap.begin();
	StringToIntList::const_iterator					end			= m_StringMap.end();

	int validWordNum = 0;
	int everyWordNum = 0;
	int uniqueWordNum = m_StringMap.keys().size();
//	int cutoff = (double) m_CorpusSize / (double) 6000;
	int cutoff = 6;
	

	outStream << "Word\t\t\t\t# of Occurrences\tStandard Deviation\n"
		      << "__________________________________________________________________________\n";
	while (it != end)
	{
		QString		word			= it.key();
		int			wordLength		= word.length();
		int			corpusCount		= it.data().size();

		if (corpusCount > cutoff)
		{
			double dist = CorpusDistribution(word);

			outStream << word << "\t\t\t";
			if (wordLength < 6) outStream << "\t";
			outStream << corpusCount << "\t\t\t" << dist << "\n";

			validWordNum++;
			if (validWordNum%16 == 0)
				m_parent->setStatusBar1(QString("writing word %1...").arg(validWordNum));

		}

//		else outStream << word << "\t\t\t\t" << m_StringMap[word] << "\n";

		everyWordNum++;
		m_parent->CountDownOnStatusBar(everyWordNum, uniqueWordNum);
	

		it++;
	}
	m_parent->EndCountDown();
	m_parent->setStatusBar1(QString("Output successful!"));

	out.close();

}
