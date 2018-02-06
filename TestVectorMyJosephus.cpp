#ifndef __TESTVECTORMyJosephus_H__
#define __TESTVECTORMyJosephus_H__
#include "MainLogic.h"
#include "VectorMyJosephus.h"
int main(int argc, char *argv[])
{
	int M, N;
	promptGame(&N, &M);
	//List/Vector are exactly the same save for how they are implimented
	//Thankfully, my gameInterface gives me a reason to use this class
	VectorMyJosephus * vector = new VectorMyJosephus(N, M);
	mainLogic(vector);
	delete vector;
}
#endif
