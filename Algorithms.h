#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>
#include <ctime>

using std::vector;

int maxSubSum1(const vector<int> & a);

int maxSubSum2(const vector<int> & a);

int max3(int l, int r, int border);
int maxSumRec(const vector<int> & a, int left, int right);
int maxSubSum3(const vector<int> & a);

int maxSubSum4(const vector<int> & a);

typedef int(*AlgoDelagate) (const vector<int> & a);
//maxSum type solved from
//https://stackoverflow.com/questions/17771406/c-initial-value-of-reference-to-non-const-must-be-an-lvalue
//Could have kept it *, but... SAFE PROGRAMMING!
double timeAlgo(AlgoDelagate algo, const vector<int> & vector, int * const & maxSum);

AlgoDelagate fetchAlgo(int j);
#endif