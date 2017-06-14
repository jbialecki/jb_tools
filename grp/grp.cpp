#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void printSyntaxMsg()
{
	cout << "Syntax error. Correct syntax:" << endl;
	cout << "grp pattern in_file [+printLines]" << endl;
}

int main(int argc, char* argv[])
{
	if(argc < 3 || argc > 4)
	{
		printSyntaxMsg();
		return 1;
	}
	ifstream f_in(argv[2]);
	if(!f_in.is_open())
	{
		cout << "in_file not found: " << argv[2] << endl;
		return 1;
	}
	int printLines = 1;
	if(argc == 4)
	{
		printLines = 0;
		if(argv[3][0] != '+')
			printSyntaxMsg();
		string str(&argv[3][1]);
		istringstream ii(str);
		ii >> printLines;
		if(printLines == 0)
		{
			cout << "printLines must be positive number" << endl;
			return 1;
		}
	}
	
	string line;
	while(getline(f_in, line))
	{
		if(line.find(argv[1]) != -1)
		{
			cout << line << endl;
			for(int i=1; i<printLines; i++)
			{
				getline(f_in, line);
				cout << line << endl;
			}
			if(printLines > 1)
				cout << endl;
		}
	}
	return 0;
}	
