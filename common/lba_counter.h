#ifndef __LBA_COUNTER__HH__
#define __LBA_COUNTER__HH__

#include <string>
#include <map>
#include <set>

class LbaCounter
{
public:
	void incCount(const char *lba);
	int getCount(const char *lba) const;

	void print() const;
private:
	std::map<std::string, int> lbaCounter;
};


class TraceMap
{
public:
	void countTrace(const char *trace, const char *lba);
	void print() const;
private:
	std::map<std::string, LbaCounter> traceMap;
	std::set<std::string> allLbas;
};

#endif
