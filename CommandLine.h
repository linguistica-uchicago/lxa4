// Functions to process command-line arguments
// Copyright © 2009 The University of Chicago
#ifndef COMMANDLINE_H
#define COMMANDLINE_H

extern int processCommandLineArgs(int argc, char** argv,
	class QString& corpus, int& count, class QString& logFile,
	class QString& goldStdFile, class QString& outputDir,
	bool& mini, bool& prefix, bool& suffix, bool& verbose,
	class QString& error);

extern void DisplayHelp();

#endif // COMMANDLINE_H
