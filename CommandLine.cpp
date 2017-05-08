// Implementation of command-line argument processing functions
// Copyright © 2009 The University of Chicago
#include "CommandLine.h"

#include <cstdio>
#include <QString>

/// Requires: variables referred to by arguments pre-initialized with
/// their default values.
int processCommandLineArgs(int argc, char** argv,
	QString& corpus, int& count, QString& logFile,
	QString& goldStdFile, QString& outputDir,
	bool& mini, bool& prefix, bool& suffix, bool& verbose,
	QString& error )
{
	QString arg, temp;
	int i, j;

	if( argc < 2 )
	{
		if( argv[0] == QString("-h") ||
			argv[0] == QString("--help") ||
			argv[1] == QString("-h") ||
			argv[1] == QString("--help") )
		{
			error = "";
			return -1;
		}
	}

	for( i=0; i<argc-1; i++ )
	{
		arg = QString( argv[i] );

		if( arg == "--help" || arg == "-h" )
		{
			error = "";
			return -1;
		}

		if( arg.find("-") == 0 )
		{
			if( arg.find("c") > 0 )
			{
				if( arg.length() > 2 )
				{
					error = "Illegal option combination : \'" + arg + "\'\n\n";
					return -1;
				}

				if( i < argc-2 )
				{
					temp = QString( argv[i+1] );
					// Check each digit is number
					for( j=0; j< static_cast <int> (temp.length()); j++ )
					{
						if( !temp[j].isNumber() )
						{
							error = "Illegal string following \'-c\' option : \'temp\'\n\n";
							return -1;
						}
					}
					count = temp.toInt();
				}
				else
				{
					error = "Illegal use of \'-c\' option.\n\n";
					return -1;
				}
			}
			else if( arg.find("g") > 0 )
			{
				if( arg.length() > 2 )
				{
					error = "Illegal option combination : \'" + arg + "\'\n\n";
					return -1;
				}

				if( i < argc-2 )
				{
					goldStdFile = QString( argv[i+1] );
				}
				else
				{
					error = "Illegal use of \'-g\' option.\n\n";
					return -1;
				}
			}
			else if( arg.find("l") > 0 )
			{
				if( arg.length() > 2 )
				{
					error = "Illegal option combination : \'" + arg + "\'\n\n";
					return -1;
				}

				if( i < argc-2 )
				{
					logFile = QString( argv[i+1] );
				}
				else
				{
					error = "Illegal use of \'-l\' option.\n\n";
					return -1;
				}
			}
			else if( arg.find("o") > 0 )
			{
				if( arg.length() > 2 )
				{
					error = "Illegal option combination : \'" + arg + "\'\n\n";
					return -1;
				}

				if( i < argc-2 )
				{
					outputDir = QString( argv[i+1] );
				}
				else
				{
					error = "Illegal use of \'-o\' option.\n\n";
					return -1;
				}
			}
			else
			{
				for( j = 1; j < static_cast <int> ( arg.length() ); j++ )
				{
					if( QString("fmpsv").find( arg[j] ) < 0 )
					{
						error = "Illegal option : \'" + QString( arg[j] ) + "\'\n\n";
						return -1;
					}
				}

				if( arg.find("m") > 0 ) mini = true;
				if( arg.find("p") > 0 ) prefix = true;
				if( arg.find("s") > 0 ) suffix = true;
				if( arg.find("v") > 0 ) verbose = true;
			}
		}
	}

	corpus = QString( argv[argc-1] );

	if( corpus == "--help" || corpus == "-h" )
	{
		error = "";
		return -1;
	}

	return 0;
}

void DisplayHelp()
{
	using std::printf;

	printf( "Usage: linguistica [options] corpus\n" );
	printf( "Options:\n" );
	printf( "  -c X\t\tX is an integer.  Read X number of words from the corpus for the analysis.  If omitted, default is 10000.\n" );
	printf( "  -g gold-std\tCompare results to this gold standard.  File must be XML format created by Alchemist and readable.\n" );
	printf( "  -h\t\tHelp: void use of all other options and arguments and print option informations.\n" );
	printf( "  -l log-file\tStore log information to this file name.  File must be writeable.\n" );
	printf( "  -m\t\tFind more than one level of morphology using mini-lexica.\n" );
	printf( "  -o output-dir\tOutput to this directory (default is same directory as corpus).  Directory must be writeable.\n" );
	printf( "  -p\t\tFind prefixes.\n" );
	printf( "  -s\t\tFind suffixes.\n" );
	printf( "  -v\t\tVerbose: print the log to the screen.\n\n" );

	printf( "Example:\n\n " );

	printf( "  linguistica -spm -l myLog.txt -c 50000 BrownCorpus.txt\n\n" );

	printf( "Using the first 50,000 distinct words of the file \'BrownCorpus.txt\',\n" );
	printf( "find more than one level of suffixes and prefixes using mini-lexica.  Keep\n" );
	printf( "a log of all actions in \'myLog.txt.\'\n\n" );
}
