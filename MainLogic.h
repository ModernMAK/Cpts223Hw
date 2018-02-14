#ifndef MAIN_LOGIC_H
#define MAIN_LOGIC_H
#include "Algorithms.h"
#include "fstream"
#include "string"
#include "queue"
#include <iostream>
#include "PlotData.h"
using std::ifstream;
using std::ofstream;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::to_string;
using std::queue;

void flushToFile(string filePath, queue<PlotData> * const &  dataCache);
bool runTest(string inputDirectory, int n, int algoId, queue<PlotData> * const &  dataCache);
void loadFromFile(string filePath, vector<int> & a);
void printVector(vector<int> & a);

#endif