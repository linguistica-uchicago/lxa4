// Log file formatting helpers
// Copyright © 2009 The University of Chicago
#ifndef HTML_H
#define HTML_H

class QString;
class CStringSurrogate;
class CParse;

extern QString MakeTableHeader(QString header);
extern QString TableData(QString stuff);
extern QString TableData(CStringSurrogate stuff);
extern QString TableData(CParse& stuff);
extern QString TableData(int value);
extern QString TableData(double value);
extern QString TableData();
extern QString LargeTitle(QString title);
extern QString SmallTitle(QString title);
extern QString SmallerTitle(QString title);

extern const QString StartTable;
extern const QString EndTable;
extern const QString StartTableRow;
extern const QString EndTableRow;

#endif // HTML_H
