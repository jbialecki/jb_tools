#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "log_convert.h"
#include "lba_counter.h"

using namespace std;

const char * findLba(const char *params)
{
	static string ret;
	string u = params;
	std::transform(u.begin(), u.end(), u.begin(), ::toupper);

	int pos = u.find("LBA = ");
	if(pos == -1)
		return nullptr;
	pos += 6;
	int pos2 = u.find(" ", pos);
	if(pos2 != -1)
		ret = u.substr(pos, pos2-pos);
	else
		ret = u.substr(pos);
	return ret.c_str();
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout << "Syntax error. Correct syntax:" << endl;
		cout << "trace_lba_cntr in_file out_file" << endl;
		return 1;
	}

	ifstream f_in(argv[1]);
	if(!f_in.is_open())
	{
		cout << "in_file not found: " << argv[1] << endl;
		return 1;
	}


	ofstream f_out(argv[2]);
	if(!f_out.is_open())
	{
		cout << "Can not create out_file: " << argv[2] << endl;
		return 1;
	}

	string line;
	int recordNo = 1;
	TraceMap tm;
	LogParser parser;
	while(getline(f_in, line))
	{
		LogRecord *recordPtr = nullptr;
		recordPtr = parser.parseLine(line);
		if(recordPtr != nullptr)
		{
			const char *lba = findLba(recordPtr->getParams());
			if(lba != nullptr)
				tm.countTrace(recordPtr->getLabel(), lba);
			recordNo++;
		}
		if(recordNo%10000 == 0)
			cout << recordNo << endl;
	}
	
//	cout << "OK" << endl;
	set<string> s;
	s.insert("00000000,6DB393A0");
	s.insert("00000000,6DA51B48");
	s.insert("00000000,6E32AA18");
	s.insert("00000000,6DE34B30");
	s.insert("00000000,6DEA2D10");
	s.insert("00000000,6E325C20");
	s.insert("00000000,6E2211D8");
	s.insert("00000000,6DE2C050");
	s.insert("00000000,6DA4DCF8");
	s.insert("00000000,6D9CE300");
	tm.allLbas.swap(s);
	ostringstream o;
	tm.print(o);
	f_out << o.str();
	return 0;
}

