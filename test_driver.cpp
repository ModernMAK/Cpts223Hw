#include "MainLogic.h"
using std::getline;

//Uncomment to make life easy when piping cout to a text file
//#define FORCE_INPUT_DIR

int main()
{

#ifdef FORCE_INPUT_DIR
	//Force File Path to load Inputs from
	string inputDirectory = "inputs";
#else 
	//Prompt File Path to load Inputs from
	cout << "Please enter the folder containing the inputs." << endl;
	string inputDirectory;
	getline(cin, inputDirectory);
#endif
	//Queue to store data
	queue<PlotData> dataCache = queue<PlotData>();
	//Allows us to skip absurdly long runs (looking at you algo 1)
	bool timedOutTracker[4] = { false,false,false,false };
	//Travel from 8 to 8192 by multiples of 2
	for (int i = 8; i <= 8192; i *= 2) {
		//For each algorithm
		for (int j = 0; j < 4; j++)
		{
			//Display whether algo time out
			if (!timedOutTracker[j]) 
			{
				//Run the trial, cahce whether we timed out
				timedOutTracker[j] = runTest(inputDirectory, i, j, &dataCache);
				//Notify timeout
				if (timedOutTracker[j])
					cout << "!!! ALGORITHM " << (j + 1) << " TIMED OUT !!!" << endl;
			}
			else
			{
				//Notify timeout
				cout << "!!! SKIPPING ALGORITHM " << (j + 1) << " ON " << i << " ELEMENTS DUE TO TIMING OUT !!!" << endl;
			}
		}
	}
	
	//Report the running Time to a file
	flushToFile("results.csv", &dataCache);

	cout << "Saved results." << endl << "Press Enter to Exit..." << endl;
	getline(cin, inputDirectory);//Recycle variable
}
