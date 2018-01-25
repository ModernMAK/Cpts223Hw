#include "plotData.h"




void plotData::writeToFile(std::ofstream& ofile)
{
	ofile << M << "," << N << "," << totalEliminationTime << "," << eliminations << "," << averageEliminationTime() << std::endl;
}

double plotData::averageEliminationTime()
{
	return totalEliminationTime / eliminations;
}

plotData::plotData(int N, int M, double totalTime, int elims)
{
	this->M = M;
	this->N = N;
	this->totalEliminationTime = totalTime;
	this->eliminations = elims;
}
plotData::~plotData()
{
}
