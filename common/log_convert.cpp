#include <iomanip>
#include "log_convert.h"

using namespace std;

static LogRecord lastRecord;
static LogRecord currRecord;

void trim(string &s)
{
	int pos1 = s.find_first_not_of(" ");
	int pos2 = s.find_last_not_of(" ");
	if(pos1 == -1)
		s = "";
	else
		s = s.substr(pos1, pos2-pos1+1);
}

LogRecord::LogRecord()
{
	clear();
}
void LogRecord::clear()
{
	type = RecordType::NOT_DEFINED;
	thrId = "";
	label = "";
	rawParams = "";
	time = "";
	fileAndLine = "";
	processedParams = "";
}
RecordType  LogRecord::getType() const
{
	return type;
}
const char *LogRecord::getThrId() const
{
	return thrId.c_str();
}
const char *LogRecord::getLabel() const
{
	return label.c_str();
}
const char *LogRecord::getParams() const
{
	return processedParams.c_str();
}
const char *LogRecord::getTime() const
{
	return time.c_str();
}
const char *LogRecord::getFileAndLine() const
{
	return fileAndLine.c_str();
}
static LineType recognizeLineType(const string &line)
{
	if((line.size() >= 150) && (line[7] == '+') )
		return LineType::NEW_THR;
	if( (line.size() >= 147) && (line[0] == '[')  )
		return LineType::NEW_REC;
	if( (line.size() >= 100) && (line[7] == '|') )
		return LineType::PARAM;
	return LineType::OTHER;
}
LogRecord *LogParser::parseLine(const string &line)
{
	LineType type = recognizeLineType(line);
	switch(type)
	{
	case LineType::NEW_THR:
		currRecord.processParams();
		lastRecord = currRecord;
		currRecord.clear();
		currRecord.type = RecordType::CTX_SWITCH;
		currRecord.parseNewThr(line);
		if(lastRecord.type == RecordType::NOT_DEFINED)
			return nullptr;
		return &lastRecord;
	case LineType::NEW_REC:
		currRecord.processParams();
		lastRecord = currRecord;
		currRecord.clear();
		currRecord.type = RecordType::TRACE;
		currRecord.parseNewRec(line);
		if(lastRecord.type == RecordType::NOT_DEFINED)
			return nullptr;
		return &lastRecord;
	case LineType::PARAM:
		currRecord.parseParam(line);
		return NULL;
	default:
		return NULL;
	}
}

void LogRecord::parseNewRec(const string &line)
{
	int pos[3]; // positions of '|'
	pos[0] = line.find_first_of("|", 0);
	if(pos[0] == -1)
		return;
	for(int i=1; i<3; i++)
	{
		pos[i] = line.find_first_of("|", pos[i-1]+1);
		if(pos[i] == -1)
			return;
	}
	thrId = line.substr(0, pos[0]);
	trim(thrId);
	time = line.substr(pos[1]+1, pos[2]-pos[1]-1);
	trim(time);
	fileAndLine = line.substr(pos[2]+1, -1);
	trim(fileAndLine);
	int pos_e = line.find_first_of("=", pos[0]+1);
	if(pos_e == -1)
		label = line.substr(pos[0]+1, pos[1]-pos[0]-1);
	else
	{
		// seek the word just before '='
		int pos_eow = line.find_last_not_of(" ", pos_e-1);
		int pos_bow = line.find_last_of(" ", pos_eow);
		label = line.substr(pos[0]+1, pos_bow-pos[0]-1);
		rawParams = line.substr(pos_bow+1, pos[1]-pos_bow-1);
	}
	trim(label);
	trim(rawParams);
}
void LogRecord::parseParam(const string &line)
{
	int pos[2]; // positions of '|'
	pos[0] = line.find_first_of("|", 0);
	if(pos[0] == -1)
		return;
	pos[1] = line.find_first_of("|", pos[0]+1);
	if(pos[1] == -1)
		return;
	string tmp = line.substr(pos[0]+1, pos[1]-pos[0]-1);
	trim(tmp);

	rawParams.append(" ");
	rawParams.append(tmp);
}
void LogRecord::parseNewThr(const string &line)
{
	int pos[3]; // positions of '+'
	pos[0] = line.find_first_of("+", 0);
	if(pos[0] == -1)
		return;
	for(int i=1; i<3; i++)
	{
		pos[i] = line.find_first_of("+", pos[i-1]+1);
		if(pos[i] == -1)
			return;
	}

	thrId = line.substr(0, pos[0]);
	trim(thrId);
	if(thrId.back() == '-')
		thrId.erase(thrId.size()-1);
		
	time = line.substr(pos[1]+1, pos[2]-pos[1]-1);
	trim(time);
}
void LogRecord::processParams()
{
	//removes spaces
	ostringstream out;
	int pos = 0;
	int len = rawParams.size();
	while(pos < len && rawParams[pos] == ' ')
		pos++;
	while(pos < len)
	{
		while(pos < len && rawParams[pos] != ' ')
			out << rawParams[pos++];
		while(pos < len && rawParams[pos] == ' ')
			pos++;
		out << ' ';
	}
	processedParams = out.str();
}


