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

	RecordType  getType() const;
	const char *getThrId() const;
	const char *getLabel() const;
	const char *getParams() const;
	const char *getTime() const;
	const char *getFileAndLine() const;

	const std::string& getLabelStr() const;

private:
	RecordType type;
	std::string thrId;
	std::string label;
	std::string rawParams;
	std::string processedParams;
	std::string time;
	std::string fileAndLine;

	void clear();
	void parseNewRec(const std::string &line);
	void parseNewThr(const std::string &line);
	void parseParam(const std::string &line);
	void processParams();

	friend class LogParser;
};


class LogParser
{
public:
	LogRecord *parseLine(const std::string &line);
};

#endif
