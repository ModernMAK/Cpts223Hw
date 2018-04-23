#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include "MainFunc.h"
#include "HashingFunc.h"

int main()
{
	vector<string> dataArray, queryArray;
	LinearHashTable<string, FullLengthHash> lhs;
	QuadraticHashTable<string, FullLengthHash> qhs;
	ChainingHashTable<string, FullLengthHash> chs;

	loadFromFile("OHenry.txt", dataArray);
	loadFromFile("queries.txt", queryArray);

	cout << "Running Collision Tests" << endl << endl;

	RunTests(&lhs, dataArray, queryArray, "Linear");
	RunTests(&qhs, dataArray, queryArray, "Quadratic");
	RunTests(&chs, dataArray, queryArray, "Chaining");

	cout << "Press Enter to exit" << endl;
	string garbage;
	getline(cin, garbage);
	return EXIT_SUCCESS;
}