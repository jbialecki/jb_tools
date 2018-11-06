#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "param_convert.h"
#include "log_convert.h"

const char separator = ';';

using namespace std;

class Cmd
{
public:
	string startLba;
	string len;
	string tag;
	string cmdBlock;

	string t_CrCmdReceived;
	void print(ostringstream &o, int cmdNum) const;
	static void printHeader(ostringstream &o);
};
void Cmd::printHeader(ostringstream &o)
{
	o << "cmdNum" << separator << "startLba" << separator << "len" << separator << "tag" << separator << "CR cmd received" << endl;
}
void Cmd::print(ostringstream &o, int cmdNum) const
{
	o << cmdNum<< separator << startLba << separator << len << separator << tag << separator << t_CrCmdReceived << endl;
}
int main(int argc, char* argv[])
{
	/*
	map<string, string> ll;
	parseParams("param1 = kota param2 = ccc", ll);
	for(map<string, string>::const_iterator it=ll.begin(); it!=ll.end(); it++)
	{
		cout << it->first << " = " << it->second << endl;
	}
*/
	if(argc != 3)
	{
		cout << "Syntax error. Correct syntax:" << endl;
		cout << "log_convert in_file out_file" << endl;
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

	int cmdNum = 0;
	map<int, Cmd> cmdMap;

	while(getline(f_in, line))
	{
		LogParser parser;
		LogRecord *recordPtr = nullptr;
		recordPtr = parser.parseLine(line);
		if((recordPtr != nullptr) && (recordPtr->getType()==RecordType::TRACE))
		{
			if(recordPtr->getLabelStr().compare("CR cmd received") == 0)
			{
				Cmd cmd;
				map<string, string> params;
				parseParams(recordPtr->getParams(), params);
				cmd.tag = params["Tag"];
				cmd.startLba = params["CmdStartLBA"];
				cmd.len = params["CmdLen"];
				cmd.t_CrCmdReceived = recordPtr->getTime();

				cmdMap[cmdNum++] = cmd;


				recordNo++;

				if(recordNo%100 == 0)
					cout << recordNo << endl;
			}
		}
	}


	ostringstream o;
	Cmd::printHeader(o);
	f_out << o.str();
	for(map<int, Cmd>::const_iterator it=cmdMap.begin(); it!=cmdMap.end(); it++ )
	{
		ostringstream o;
		it->second.print(o, it->first);
		f_out << o.str();
	}


	cout << "OK" << endl;
	return 0;
}

