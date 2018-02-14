#include "MainLogic.h"
using std::getline;
int main()
{
	//Prompt File Path to load Inputs from
	cout << "Please enter the folder containing the inputs." << endl;
	string inputDirectory;
	getline(cin, inputDirectory);
	queue<PlotData> dataCache = queue<PlotData>();
	bool timedOutTracker[4] = { false,false,false,false };
	for (int i = 8; i < 8192; i *= 2) {
		for (int j = 0; j < 4; j++)
		{
			if (!timedOutTracker[j]) 
			{
				timedOutTracker[j] = runTest(inputDirectory, i, j, &dataCache);
				if (timedOutTracker[j])
					cout << "!!! ALGORITHM " << (j + 1) << " TIMED OUT !!!" << endl;
			}
			else
			{
				cout << "!!! SKIPPING ALGORITHM " << (j + 1) << " ON " << i << " ELEMENTS DUE TO TIMING OUT !!!" << endl;
			}
		}
	}
	
	//Report the running Time
	flushToFile("results.csv", &dataCache);

	cout << "Saved results." << endl << "Press Enter to Exit..." << endl;
	char exitFlag;
	cin >> exitFlag;
}
