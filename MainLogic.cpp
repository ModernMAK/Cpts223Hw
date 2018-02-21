#include "MainLogic.h"

//Clears queue, writes queue to file
void flushToFile(string filePath, queue<PlotData> * const &  dataCache)
{

	ofstream file;
	file.open(filePath.c_str());
	file << "N,A,T," << endl;
	while(!dataCache->empty())
	{
		PlotData data = dataCache->front();
		dataCache->pop();
		file << data.getN() << ","<< data.getA() << "," << data.getT() << "," << endl;
	}
	file.close();
}


//Runs all tests for an algorithm, searches for files in the given directory, stores results in cache
//Returns true when algo times out


bool runTest(string inputDirectory, int n, int algoId, queue<PlotData> * const &  dataCache)
{
	bool timedOut = false;
	int sum = 0;
	vector<int> v = vector<int>();
	double averageTime = 0.0;
	int iMax = 10;
	double timeCutoff = 60 * 0.5;//Times out at 30 seconds
	for (int i = 0; i < iMax; i++)
	{
		string fileName = "input_" + to_string(n) + "_" + to_string(i) + ".txt";
		string filePath = inputDirectory + "/" + fileName;
		loadFromFile(filePath, v);

		cout << "- - - - - - - - - - - - - - - - - -" << endl;
		cout << "Algorithm " << (algoId + 1) << endl;//Algorithm
		cout << "Set " << i << endl;//Algorithm
		printVector(v);//Prints the size and elements
		double time = timeAlgo(fetchAlgo(algoId), v, &sum);
		cout << "Sum:\t" << sum << endl;
		cout << "Time:\t" << time << endl;
		cout << "- - - - - - - - - - - - - - - - - -" << endl;

		//If the algorithm takes more than 15 minutes
		if(time > timeCutoff)
		{
			averageTime += (iMax - i - 1) * time;//Add the remaining estimates
			i = iMax;//Break
			timedOut = true;
		}
		averageTime += time;
	}
	dataCache->push(PlotData(n, algoId, averageTime / iMax));
	return timedOut;
}

//Load a vector from file
void loadFromFile(string filePath, vector<int> & a)
{
	a.clear();
	ifstream file;
	file.open(filePath.c_str());
	//Since there isn't a delimeter, and im too lazy to write a dirty parser
	//Sadness, had to anyways
	int temp = 0;
	bool isNeg = false;
	while (file.peek() >= 0) //Not -1, eof
	{
		temp = file.get();
		if (isdigit(temp))
		{
			temp -= '0';
			temp *= (isNeg ? -1 : 1);
			isNeg = false;
			a.push_back(temp);
		}
		else if (temp == '-')
			isNeg = true;
	}
	file.close();
}
//Prints the size and elements of a vector
void printVector(vector<int> & a)
{
	cout << "Size:\t" << a.size() << endl;
	cout << "Elements:\t";
	for (vector<int>::iterator i = a.begin(); i < a.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

string to_string(int i)
{
	//0 is special, it breaks my algorithm, so... catch it here
	if (i == 0) return "0";

	string output = "";
	stack<char> s = stack<char>();
	if (i < 0)
	{
		output += "-";
		i = -i;		
	}
	while(i > 0)
	{
		int digit = i % 10;
		i = i / 10;//integer division, truncates
		char temp = '0' + digit;
		s.push(temp);
	}
	while(!s.empty())
	{
		output += s.top();
		s.pop();
	}
	return output;
}
