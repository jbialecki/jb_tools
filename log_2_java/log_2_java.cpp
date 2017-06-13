#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <iomanip>

using namespace std;

// typical line:
// [T5] |         25 | 1359604763.932.672.000s | st_mgr.cpp              :5079 | ST check initiator protocol       | protocolError = 00

class Record
{
public:
	Record();
	string logLine;
	string srcFile;
	string srcLine;
	int srcLineInt;
	string msg;    
};
Record::Record()
{
	srcLineInt = 0;
}
void trim(string &s)
{
	int pos1 = s.find_first_not_of(" ");
	int pos2 = s.find_last_not_of(" ");
	if(pos1 == -1)
		s = "";
	else
		s = s.substr(pos1, pos2-pos1+1);
}
void parseLine(const string &line, Record &r)
{
	int pos[5]; // positions of '|'
	pos[0] = line.find_first_of("|", 0);
	if(pos[0] == -1)
	{
		r.msg = "### BAD RECORD ###";
		return;
	}
	for(int i=1; i<5; i++)
	{
		pos[i] = line.find_first_of("|", pos[i-1]+1);
		if(pos[i] == -1)
		{
			r.msg = "### BAD RECORD ###";
			return;
		}
	}
	int pos_a = line.find_first_of(":", pos[2]+1); // position of ':'
	if(pos_a == -1)
	{
		r.msg = "### BAD RECORD ###";
		return;
	}

	r.logLine = line.substr(pos[0]+1, pos[1]-pos[0]-1);
	r.srcFile = line.substr(pos[2]+1, pos_a -pos[2]-1);
	r.srcLine = line.substr(pos_a +1, pos[3]-pos_a -1);
	r.msg     = line.substr(pos[3]+1, pos[4]-pos[3]-1);

	trim(r.logLine);
	trim(r.srcFile);
	trim(r.srcLine);
	trim(r.msg    );
}
void printLine(const string &line, ofstream &out)
{
	static int recNo = 1;
	Record r;
	parseLine(line, r);
	out << "DefaultMutableTreeNode label" << recNo++ << " = addMsg(root, \"" << r.msg << "\", \"" << r.srcFile << "\", " << r.srcLine << ", " << r.logLine << ");\n";
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout << "Syntax error. Correct syntax:" << endl;
		cout << "log_2_java in_file out_file" << endl;
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
	while(getline(f_in, line))
		printLine(line, f_out);		 
	cout << "OK" << endl;
	return 0;
}
