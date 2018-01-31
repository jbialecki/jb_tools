#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "log_convert.h"

using namespace std;

int main(int argc, char* argv[])
{
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
	int i = 0;
	while(getline(f_in, line))
	{
		++i;
		LogParser parser;
		LogRecord *recordPtr = nullptr;
		recordPtr = parser.parseLine(line);
		if(recordPtr != nullptr)
		{
			ostringstream o;
			recordPtr->print(o);
			f_out << o.str();
		}
		if(i%10000 == 0)
			cout << i << endl;
	}
	
	cout << "OK" << endl;
	return 0;
}

