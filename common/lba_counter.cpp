#include <iostream>
#include "lba_counter.h"

static const char separator = ';';

using namespace std;

void LbaCounter::incCount(const char *lba)
{
	map<string, int>::iterator it = lbaCounter.find(lba);
	if(it == lbaCounter.end())
		lbaCounter.insert(pair<string, int>(lba, 1));
	else
		it->second++;
}

int LbaCounter::getCount(const char *lba) const
{
	map<string, int>::const_iterator it = lbaCounter.find(lba);
	if(it == lbaCounter.end())
		return 0;
	return it->second;
}

void LbaCounter::print() const
{
	map<string, int>::const_iterator it = lbaCounter.begin();
	for( ; it!=lbaCounter.end(); it++)
		cout << it->first << ": " << it->second << endl;
}

void TraceMap::countTrace(const char *trace, const char *lba)
{
	map<string, LbaCounter>::iterator it = traceMap.find(trace);
	if(it == traceMap.end())
	{
		LbaCounter lbaCounter;
		lbaCounter.incCount(lba);
		traceMap.insert(pair<string, LbaCounter>(trace, lbaCounter));
	}
	else
	{
		it->second.incCount(lba);
	}
	allLbas.insert(lba);
}
void TraceMap::print() const
{
	// header
	cout << "trace";
	for(set<string>::const_iterator lbaIt = allLbas.begin(); lbaIt != allLbas.end(); lbaIt++)
		cout << separator << *lbaIt;
	cout << endl;
	map<string, LbaCounter>::const_iterator traceIt = traceMap.begin();
	for( ; traceIt!=traceMap.end(); traceIt++)
	{
		cout << traceIt->first;

		for( set<string>::const_iterator aIt = allLbas.begin(); aIt != allLbas.end(); aIt++)
			cout << separator << traceIt->second.getCount(aIt->c_str());
		cout << endl;
	}
}
void TraceMap::print(ostringstream &o) const
{
	// header
	o << "trace";
	for(set<string>::const_iterator lbaIt = allLbas.begin(); lbaIt != allLbas.end(); lbaIt++)
		o << separator << *lbaIt;
	o << endl;
	map<string, LbaCounter>::const_iterator traceIt = traceMap.begin();
	for( ; traceIt!=traceMap.end(); traceIt++)
	{
		o << traceIt->first;

		for( set<string>::const_iterator aIt = allLbas.begin(); aIt != allLbas.end(); aIt++)
			o << separator << traceIt->second.getCount(aIt->c_str());
		o << endl;
	}
}
