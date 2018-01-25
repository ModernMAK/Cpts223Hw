
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
	Game(AbstractJosephus* josephus);
	~Game();
	void init(int N, int M);
	void clear();
	int currentSize();
	bool isEmpty();
	Person eliminateNext();
	Person timeEliminateNext(double * elimTime);
	virtual void printAll();
	void play();
	void reset();
	void reset(int N, int M);
	double timePlay(int * eliminations);
private:
	AbstractJosephus * gameInterface;

//	Game(bool useList, int M, int N);
//	~Game();
//	void init(int N, int M);
//	void clear();
//
//	//	prints the number of people still playing the game (i.e., not yet eliminated) 
//	int currentSize();
//
//	//	returns true if circle is empty
//	bool isEmpty();
//
//	// eliminates the next person as per the game's rule
//	Person eliminateNext();
//
//	// prints the current content of circle in sequence starting from the person with the least position number
//	void printAll();
//
//	// any other member functions of your choice
//	// ....
//	int nextPotato();
//	void play();
//	void reset();
//	void reset(int N, int M);
//	int currentRound();
//	int startPlayers();
//	int startPasses();
//	Person timeEliminateNext(double*time);
//	double timePlay(int * eliminations);
//
//private:
//	VectorMyJosephus vector;
//	ListMyJosephus list;
//	bool useList;
};

#endif