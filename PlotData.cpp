#include "PlotData.h"



PlotData::PlotData()
{
	init(0, 0, 0.0);
}

PlotData::PlotData(int n, int a, double t)
{
	init(n,a,t);
}


PlotData::~PlotData()
{
}

void PlotData::init(int n, int a, double t)
{
	this->n = n;
	this->a = a;
	this->t = t;
}

int PlotData::getN()
{
	return this->n;
}
int PlotData::getA()
{
	return this->a;
}
double PlotData::getT()
{
	return this->t;
}


