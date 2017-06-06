#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <iomanip>

using namespace std;

enum LineType
{
	LT_NEW_THR = 0,
	LT_NEW_REC = 1,
	LT_PARAM = 2,
	LT_OTHER = 3,
};
class LogLine
{
public:
	void parseLine(const string &line, ostringstream *o);
	void processParams();
	void print(ostringstream &o);
	void clear();

	LineType type;
	string thrId;
	string label;
	string params;
	string processedParams;
	string time;
	string fileAndLine;

private:
	static unsigned int fawMax; // max length of fileAndLine

	void parseNewRec(const string &line);
	void parseNewThr(const string &line);
	void parseParam(const string &line);

	void printNewRec(ostringstream &o);
	void printNewThr(ostringstream &o) const;
	
};
LogLine lastRecordLine;
unsigned int LogLine::fawMax = 0;
int recordNo = 0;
void LogLine::clear()
{
	type = LT_NEW_THR;
	thrId = "";
	label = "";
	params = "";
	time = "";
	fileAndLine = "";
}
static LineType recognizeLineType(const string &line)
{
	if((line.size() >= 150) && (line[5] == '+') )
		return LT_NEW_THR;
	if( (line.size() >= 147) && (line[0] == '[')   &&   (line[3] == ']') )
		return LT_NEW_REC;
	if( (line.size() >= 100) && (line[5] == '|') )
		return LT_PARAM;
	return LT_OTHER;
}
void LogLine::parseLine(const string &line, ostringstream *o)
{
	LineType type = recognizeLineType(line);
	switch(type)
	{
	case LT_NEW_THR:
		if(o)
			lastRecordLine.print(*o);
		lastRecordLine.clear();
		lastRecordLine.type = type;
		lastRecordLine.parseNewThr(line);
		return;
	case LT_NEW_REC:
		if(o)
			lastRecordLine.print(*o);
		lastRecordLine.clear();
		lastRecordLine.type = type;
		lastRecordLine.parseNewRec(line);
		return;
	case LT_PARAM:
		lastRecordLine.parseParam(line);
		return;
	}
}

void LogLine::parseNewRec(const string &line)
{
	thrId = line.substr(0, 4);
	label = line.substr(7, 33);
	params = line.substr(40, 56);
	time = line.substr(99, 23);
	fileAndLine = line.substr(125, -1);
	if(fileAndLine.size() > fawMax)
		fawMax = fileAndLine.size();
}
void LogLine::parseParam(const string &line)
{
	string tmp;
	tmp = line.substr(40, 56);
	params.append(" ");
	params.append(tmp);
}
void LogLine::parseNewThr(const string &line)
{
	thrId = line.substr(0, 4);
	time = line.substr(99, 23);
}
void LogLine::processParams()
{
	ostringstream out;
	int pos = 0;
	int len = params.size();
	while(pos < len && params[pos] == ' ')
		pos++;
	while(pos < len)
	{
		while(pos < len && params[pos] != ' ')
			out << params[pos++];
		while(pos < len && params[pos] == ' ')
			pos++;
		out << ' ';
	}
	processedParams = out.str();
}

void LogLine::print(ostringstream &o)
{
	switch(type)
	{
	case LT_NEW_THR:
		printNewThr(o);
		return;
	case LT_NEW_REC:
		printNewRec(o);
		return;
	}
}

void LogLine::printNewRec(ostringstream &o) 
{
	processParams();
	o << thrId << " | " << setfill(' ') << setw(10) << recordNo++ << " | " << time << " | " << setfill(' ') << setw(fawMax) << fileAndLine << " | " << label << " | " << processedParams << endl;
}
void LogLine::printNewThr(ostringstream &o) const
{
	o << thrId << " | " << setfill(' ') << setw(10) << recordNo++ << " | " << time << " +----------------------------------------------------------------------------------------------+ " << endl;
}
int main(int argc, char* argv[])
{
	string line;
	list<LogLine> lines;
	int cnt = 0;
	ifstream f_in("c:\\prj\\logs\\Read_WDT\\Read_WDT_short.txt");
	ofstream f_out("c:\\prj\\logs\\Read_WDT\\processed_short.txt");
	int i = 0;
	while(getline(f_in, line))
	{
		++i;
		LogLine ll;
		ostringstream o;
		ll.parseLine(line, &o);
		f_out << o.str();

		if(i%10000 == 0)
			cout << i << endl;
	}
	
	cout << cnt << " lines" << endl;
	return 0;
}

