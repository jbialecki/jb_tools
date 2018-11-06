#include "param_convert.h"
#include "txt_utils.h"

using namespace std;

void parseParams(const char *paramStr, map<string, string> &paramMap)
{
	list<string> wl; // word list
	splitIntoWords(paramStr, wl);
	list<string>::const_iterator it = wl.begin();
	while(it!=wl.end())
	{
		string key = *it;
		it++;
		if(it == wl.end())
			return;
		if(it->compare("=")!=0)
			return;
		it++;
		string value = *it;
		it++;
		paramMap[key] = value;
	}
}

