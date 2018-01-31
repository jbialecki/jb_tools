#include <iostream>
#include "lba_counter.h"

using namespace std;
int main()
{
	TraceMap c;
	c.countTrace("aaa", "1020");
	c.countTrace("aaa", "3040");
	c.countTrace("aaa", "3040");
	c.countTrace("bbb", "3040");

	c.print();
	//cout << c.getCount("aaa") << "   " << c.getCount("bbb") << endl;
	return 0;
}
