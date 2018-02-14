#ifndef PLOT_DATA_H
#define PLOT_DATA_H
class PlotData
{
public:
	PlotData();
	PlotData(int n, int a, double t);
	~PlotData();
private:
	void init(int n, int a, double t);
	int n;
	int a;
	double t;
public:
	int getN();
	int getA();
	double getT();
};

#endif
