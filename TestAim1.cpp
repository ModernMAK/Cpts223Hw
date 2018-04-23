#include "string.h"
#include "vector"
#include "fstream"
#include <string>
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "SeparateChaining.h"

using std::string;
using std::vector;
using std::ifstream;
using std::getline;

void loadFromFile(string fname, vector<string>&data);


void main()
{
	vector<string> dataArray, queryArray;
	LinearHashTable<>

	loadFromFile("OHenry.txt", dataArray);
	loadFromFile("queries.txt", queryArray);


}


void loadFromFile(string fname, vector<string> & data)
{
	ifstream f = ifstream(fname);
	string buffer;
	while (!f.eof())
	{
		getline(f, buffer);
		data.push_back(buffer);
	}
	f.close();
}