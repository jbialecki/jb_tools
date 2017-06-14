#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
	string line;
	while(getline(cin, line))
	{
		replace(line.begin(), line.end(), '~', '\n');
		cout << line << endl << endl;
	}
	return 0;
}
