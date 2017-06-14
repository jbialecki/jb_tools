#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		cout << "Syntax error. Correct syntax:" << endl;
		cout << "grp pattern in_file" << endl;
		return 1;
	}
	ifstream f_in(argv[2]);
	if(!f_in.is_open())
	{
		cout << "in_file not found: " << argv[2] << endl;
		return 1;
	}
	
	string line;
	while(getline(f_in, line))
	{
		if(line.find(argv[1]) != -1)
			cout << line << endl;
	}
	return 0;
}	
