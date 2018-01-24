#ifndef __TESTVECTORMyJosephus_H__
#define __TESTVECTORMyJosephus_H__
#include "Game.h"
#include <string>
int main(int argc, char *argv[])
{
	cout << "!!! BEGAN TESTING VECTOR !!!" << endl;
	cout << "!!! TESTING PLAY !!!" << endl;

	string temp;
	cout << "# of Players?" << endl;
	getline(cin, temp);
	auto N = stoi(temp);
	temp = "";

	cout << "# of Potato Passes?" << endl;
	getline(cin, temp);
	auto M = stoi(temp);
	temp = "";

	auto g = Game(false, N, M);
	g.play();
	

	cout << "!!! TESTING RESET !!!" << endl;
	g.reset();


	cout << "!!! TESTING TIME !!!" << endl;
	auto time = g.time();
	cout << "CPU elapsed time in seconds: " << time << endl;

	cout << "!!! FINISHED TESTING VECTOR !!!" << endl;
}
#endif
