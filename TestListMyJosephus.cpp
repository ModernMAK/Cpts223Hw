#ifndef __TESTLISTMyJosephus_H__
#define __TESTLISTMyJosephus_H__
#include "MainLogic.h"
#include "ListMyJosephus.h"
int main(int argc, char *argv[])
{
	int M, N;
	promptGame(&N, &M);
	//List/Vector are exactly the same save for how they are implimented
	//Thankfully, my gameInterface gives me a reason to use this class
	ListMyJosephus * list = new ListMyJosephus(N, M);
	mainLogic(list);
	delete list;
}
#endif
