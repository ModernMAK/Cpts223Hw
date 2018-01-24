
#ifndef __GAME_H__
#define __GAME_H__

#include "VectorMyJosephus.h"
#include "ListMyJosephus.h"
#include <queue>
#include<ctime>



//Facade for testing, would have been easier by creating an interface class... but lazy
class Game
{
public:
	Game(bool useList, int M, int N);
	~Game();
	void init(int N, int M);
	void clear();

	//	prints the number of people still playing the game (i.e., not yet eliminated) 
	int currentSize();

	//	returns true if circle is empty
	bool isEmpty();

	// eliminates the next person as per the game's rule
	Person eliminateNext();

	// prints the current content of circle in sequence starting from the person with the least position number
	void printAll();

	// any other member functions of your choice
	// ....
	int eliminatedIndex();
	void play(bool printRounds = true);
	void reset();
	int currentRound();
	double time();
	int startPlayers();
	int startPasses();

private:
	VectorMyJosephus vector;
	ListMyJosephus list;
	bool useList;
};

#endif