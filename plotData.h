#ifndef __PlotData_H__
#define __PlotData_H__
#include <fstream>

struct plotData
{
public:
	plotData(int N, int M, double totalTime, int elims);

	~plotData();

	//void writeToFile(std::ofstream& ofile);
	int getM();
	int getN();
	double getTotalElimTime();
	int getElims();
	double averageEliminationTime();
private:
	int M;
	int N;
	double totalEliminationTime;
	int eliminations;
};
#endif