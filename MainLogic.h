#ifndef MAIN_LOGIC_H
#define MAIN_LOGIC_H
#include "Algorithms.h"
#include "fstream"
#include "string"
#include "queue"
#include <iostream>
#include "PlotData.h"
#include "stack"
using std::ifstream;
using std::ofstream;
using std::string;
using std::stack;
using std::cin;
using std::cout;
using std::endl;


//using std::to_string;
using std::queue;
//Flush the queue to a file
void flushToFile(string filePath, queue<PlotData> * const &  dataCache);
//Run the test, pulling data from the input directory, with n elements, the algoId, and the cache to store to
bool runTest(string inputDirectory, int n, int algoId, queue<PlotData> * const &  dataCache);
//Load an array from a file, and store in a
void loadFromFile(string filePath, vector<int> & a);
//Print the vector
void printVector(vector<int> & a);
//No ITOA and we're not c++11 compliant (no to_string)
string to_string(int i);


#endif