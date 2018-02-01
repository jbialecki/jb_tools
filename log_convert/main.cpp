#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "log_convert.h"

using namespace std;


static const int labelMax = 34;
static const int fileAndLineMax = 80;

void printNewRec(const LogRecord *record, ostringstream &o, int recordNo)
{
	o << record->getThrId() << " | ";
	o << setfill(' ') << setw(10) << recordNo << " | ";
	o << record->getTime() << " | ";
	o << setfill(' ') << setw(fileAndLineMax) << record->getFileAndLine() << " | ";
	o << setw(labelMax) << record->getLabel() << " | ";
	o << record->getParams() << endl;
}


void printNewThr(const LogRecord *record, ostringstream &o, int recordNo)
{
	o << record->getThrId() << " | ";
	o << setfill(' ') << setw(10) << recordNo << " | ";
	o << record->getTime();
	o << " +----------------------------------------------------------------------------------------------+ " << endl;
}


void print(const LogRecord *record, ostringstream &o, int recordNo)
{
	switch(record->getType())
	{
	case RecordType::CTX_SWITCH:
		printNewThr(record, o, recordNo);
		return;
	case RecordType::TRACE:
		printNewRec(record, o, recordNo);
		return;
	}
}
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
	int recordNo = 1;
	while(getline(f_in, line))
	{
		LogParser parser;
		LogRecord *recordPtr = nullptr;
		recordPtr = parser.parseLine(line);
		if(recordPtr != nullptr)
		{
			ostringstream o;
			print(recordPtr, o, recordNo);
			f_out << o.str();
			recordNo++;
		}
		if(recordNo%10000 == 0)
			cout << recordNo << endl;
	}
	
	cout << "OK" << endl;
	return 0;
}

