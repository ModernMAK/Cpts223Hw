#include "MainFunc.h"


void RunTests(HashTableTestInterface<string> * table, vector<string> & insert, vector<string> & search, string msg)
{
	PerformInsertTest(table, insert);
	PrintTablePerformance(table, insert.size(), msg + " Insert");
	table->resetTotalCollisions();
	PerformSearchTest(table, search);
	PrintTablePerformance(table, insert.size(), msg + " Search");

}

void PrintTablePerformance(HashTableTestInterface<string> * table, int n, string msg)
{
	if (msg != "")
		std::cout << msg << endl;
	cout << "TOTAL, AVERAGE, COLLISIONS" << endl;
	cout << table->getTimeElapsed() << ", " << (table->getTimeElapsed() / n) << ", " << table->getTotalCollisions() << endl << endl;
}

void PerformInsertTest(HashTableTestInterface<string> * table, vector<string> & data)
{
	table->startTimer();
	for (vector<string>::iterator it = data.begin(); it != data.end(); ++it)
	{
		table->testInsert(*it);
	}
	table->stopTimer();
}
void PerformSearchTest(HashTableTestInterface<string> * table, vector<string> & data)
{
	table->startTimer();
	for (vector<string>::iterator it = data.begin(); it != data.end(); ++it)
	{
		table->contains(*it);
	}
	table->stopTimer();
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