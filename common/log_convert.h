#ifndef __LOG_CONVERT__H__
#define __LOG_CONVERT__H__

#include <string>
#include <fstream>

enum class LineType
{
	NEW_THR = 0,
	NEW_REC = 1,
	PARAM = 2,
	OTHER = 3,
};


enum class RecordType
{
	CTX_SWITCH = 0,
	TRACE = 1,
	NOT_DEFINED = 2,
};


class LogRecord
{
public:
	LogRecord();
	void print(std::ostringstream &o) const;
	void clear();

	RecordType type;
	std::string thrId;
	std::string label;
	std::string processedParams;
	std::string time;
	std::string fileAndLine;

private:
	std::string rawParams;

	void parseNewRec(const std::string &line);
	void parseNewThr(const std::string &line);
	void parseParam(const std::string &line);
	void processParams();

	void printNewRec(std::ostringstream &o) const;
	void printNewThr(std::ostringstream &o) const;

	friend class LogParser;
};


class LogParser
{
public:
	LogRecord *parseLine(const std::string &line);
};

#endif
