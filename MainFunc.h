#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H
#include <string>
#include <vector>
#include "HashTableTestInterface.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::endl;

void loadFromFile(std::string fname, std::vector<string>&data);
void PerformInsertTest(HashTableTestInterface<string> * table, vector<string> & data);
void PerformSearchTest(HashTableTestInterface<string> * table, vector<string> & data);
void PrintTablePerformance(HashTableTestInterface<string> * table, int n, string msg = "");
void RunTests(HashTableTestInterface<string> * table, vector<string> & insert, vector<string> & search, string msg = "");

#endif