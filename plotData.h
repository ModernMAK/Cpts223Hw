#ifndef __PlotData_H__
#define __PlotData_H__
#include <fstream>

struct plotData
{
public:
	plotData(int N, int M, double totalTime, int elims);

	~plotData();

	void writeToFile(std::ofstream& ofile);

private:
	int M;
	int N;
	double totalEliminationTime;
	int eliminations;
	double averageEliminationTime();
};
#endif