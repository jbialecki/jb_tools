
#include <txt_utils.h>

using namespace std;

void splitIntoWords(const char *txt, list<string> &wordList)
{
	int i = 0;
	while(true)
	{
		while( (txt[i]!=0) && (txt[i]==' ' || txt[i]=='\t') )
		i++;

		if(txt[i]==0)
			return;

		int pos = i;		

		while( txt[i]!=0 && txt[i]!=' ' && txt[i]!='\t' )
			i++;

		string word(&txt[pos], i-pos);
		wordList.push_back(word);
	}
}
