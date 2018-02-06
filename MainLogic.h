#ifndef __MainLogic_H__
#define __MainLogic_H__
#include "Game.h"

inline void promptGame(int * N, int * M)
{
	string temp;
	cout << "# of Players? (N)" << endl;
	getline(cin, temp);
	*N = atoi(temp.c_str());
	temp = "";

	cout << "# of Potato Passes? (M)" << endl;
	getline(cin, temp);
	*M = atoi(temp.c_str());
}

inline void writeToFile(string fileName, queue<plotData> * data)
{
	ofstream file;
	file.open(fileName.c_str());

	while (data->size() > 0)
	{
		plotData inst = data->front();
		data->pop();
		file << inst.getM() << "," << inst.getN() << "," << inst.getTotalElimTime() << "," << inst.getTotalElimTime() << "," << inst.averageEliminationTime() << std::endl;
	}
	file.close();
}

inline void mainLogic(AbstractJosephus * gInterface)
{

	cout << endl << "!!! BEGAN TESTING " << " !!!" << endl;
	cout << endl << "!!! TESTING PLAY !!!" << endl;
	

	Game g = Game(gInterface);
	g.play();


	//Time Code, M Constant
	cout << endl << "!!! TESTING TIME DEPENDENCE ON PLAYERS!!!" << endl;
	queue<plotData> mData = queue<plotData>();
	double totalTime = 0;
	double testTime;
	int trials = 0;
	int eliminations = 0;
	int M = 3;
	int N;
	for (N = 4; N <= 1024; N *= 2)
	{
		trials++;
		g.reset(N, M);
		testTime = g.timePlay(&eliminations);		
		totalTime += testTime;
		mData.push(plotData(N, M, testTime, eliminations));
	}
	double averageTime = totalTime / trials;
	cout << "CPU time in seconds for M:" << M << " N:[4,8,16,32...1024]" << endl;
	cout << "Total Test Time : " << totalTime << endl;
	cout << "Average Test Time : " << averageTime << endl;
	cout << "Elim Times printed to file due to #" << endl;



	//Time Code, N constant
	cout << endl << "!!! TESTING TIME DEPENDENCE ON PLAYERS!!!" << endl;
	queue<plotData> nData = queue<plotData>();
	totalTime = 0;
	trials = 0;
	eliminations = 0;
	N = 1024;
	for (M = 2; M < N; M *= 2)
	{
		trials++;
		g.reset(N, M);
		testTime = g.timePlay(&eliminations);
		totalTime += testTime;
		nData.push(plotData(N, M, testTime, eliminations));
	}
	averageTime = totalTime / trials;
	cout << "CPU time in seconds for M:" << "[2,4,8,16,32...N)" << " N:" << N << endl;
	cout << "Total Test Time : " << totalTime << endl;
	cout << "Average Test Time : " << averageTime << endl;
	cout << "Elim Times printed to file due to #" << endl;


	//Done, Yay!
	cout << endl << "!!! FINISHED TESTING !!!" << endl;
	cout << endl << "!!! WRITING ELIM TIME RESULTS !!!" << endl;
	
	writeToFile("mData.csv", &mData);
	writeToFile("nData.csv", &nData);

	//Prompt to avoid closing the terminal!
	cout << endl << "!!! PRESS ANY KEY TO EXIT !!!" << endl;
	string temp;
	getline(cin, temp);
	
}
#endif
