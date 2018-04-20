#include "Scheduler.h"
#include <fstream>
using std::cin;
using std::ifstream;
int promptCluster();
int promptInt(string msg);
string promptStr(string msg);
void promptJob(string* desc, int* processors, int *ticks);
void parseLine(string line, string* desc, int* processors, int *ticks);
string toUpperString(string input);


int main()
{
	Scheduler s(promptCluster());
	cout << endl;
	int tickCounter = 1;
	string jobDesc;
	int jobProcessors;
	int jobTicks;
	ifstream file("input.txt");
	bool hasIdled = false;
	bool isDone = false;
	while (!isDone)
	{
		cout << "---------------------" << endl;
		cout << "Tick #" << tickCounter << endl;
		if (!file.eof())
		{
			string line = "";
			getline(file, line);
			parseLine(line, &jobDesc, &jobProcessors, &jobTicks);
			s.submitJob(jobDesc, jobProcessors, jobTicks);
		}
		s.tick();
		s.print();
		if (s.isIdle())
		{
			if (hasIdled)
			{
				isDone = true;
				break;
			}
			else
			{
				cout << "Scheduler Is Idle, will shut down if Idle next tick" << endl;
				hasIdled = true;
			}
		}
		tickCounter++;
	}
	promptStr("Press enter to exit...\n");
}

////Manual Input tester
//int main()
//{
//	Scheduler s(promptCluster());
//	cout << endl;
//	int tickCounter = 1;
//	string jobDesc;
//	int jobProcessors;
//	int jobTicks;
//	bool hasIdled = false;
//	while (true)
//	{
//		cout << "Tick #" << tickCounter << endl;
//		promptJob(&jobDesc, &jobProcessors, &jobTicks);
//		cout << endl;
//		s.submitJob(jobDesc, jobProcessors, jobTicks);
//		s.tick();
//		s.print();
//		if (s.isIdle())
//		{
//			if (hasIdled)
//				exit(EXIT_SUCCESS);
//			else
//			{
//				cout << "Scheduler Is Idle, will shut down if Idle next tick" << endl;
//				hasIdled = true;
//			}
//		}
//		tickCounter++;
//
//	}
//}


int promptCluster()
{
	int num;
	do {
		num = promptInt("How many Processors does this cluster have?\n");
		if (num <= 0)
			cout << "You need at least 1 processor!" << endl;
	} while (num <= 0);
	return num;
}
string toUpperString(string input)
{
	
	string output = string(input);//Make input mutable
	for (int i = 0; i < input.size(); i++)
		output[i] = toupper(output[i]);
	return output;
} 
void parseLine(string line, string* desc, int* processors, int *ticks)
{
	line += "  ";//Garuntees 2 spaces, doesnt affect the end result if entered properly
	int offset = 0;
	int found = 0;

	string temp[3];
	for(int i = 0; i < 3; i++)
	{
		found = line.find(" ",offset);
		temp[i] = line.substr(offset, found - offset);
		offset = found+1;
	}

	*desc = toUpperString(temp[0]);
	*processors = stoi(temp[1]);
	*ticks = stoi(temp[2]);
}
void promptJob(string* desc, int* processors, int *ticks)
{
	string prompt = "Please enter a Job in the format of:\tJOB_NAME #_Processors #_Ticks\n";
	string s = promptStr(prompt);
	//For quick and easy use
	if (s == "")
		s = "NULL 0 0";
	parseLine(s, desc, processors, ticks);
}
int promptInt(string msg)
{
	return stoi(promptStr(msg));
}
string promptStr(string msg)
{
	string a;
	cout << msg;
	getline(cin, a);
	return a;
}
