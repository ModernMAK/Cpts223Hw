#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include "MainFunc.h"
#include "HashingFunc.h"

int main()
{
	vector<string> dataArray, queryArray;
	QuadraticHashTable<string, FullLengthHash> flhs;
	QuadraticHashTable<string, PrefixHash> phs;
	QuadraticHashTable<string, SimpleHash> shs;

	loadFromFile("OHenry.txt", dataArray);
	loadFromFile("queries.txt", queryArray);

	cout << "Running Hash Tests" << endl  << endl;

	RunTests(&flhs, dataArray, queryArray, "Full-Length");
	RunTests(&phs, dataArray, queryArray, "Prefix");
	RunTests(&shs, dataArray, queryArray, "Simple");

	cout << "Press Enter to exit" << endl;
	string garbage;
	getline(cin, garbage);
	return EXIT_SUCCESS;
}