/*
* VectorMyJosephus:
* This class implements a MyJosephus circle using an STL vector
* N : initial number of players
* M : interval to jump for next removal
*
* In your solution, make sure you have a separate .cpp file that defines the implementation for every .h file.
*/

#ifndef __VECTORMyJosephus_H__
#define __VECTORMyJosephus_H__

#include <iostream>
#include <vector>
#include "Person.h"
#include "AbstractJosephus.h"
using namespace std;

class VectorMyJosephus : public AbstractJosephus {
public:
	VectorMyJosephus();
	VectorMyJosephus(int N, int M);
	~VectorMyJosephus();
	void init(int N, int M);
	void clear() override;
	void printAll() override;
private:
	void addPerson(int position);
	Person getAndRemoveAt(int position);
	vector<Person> circ;
//public:
//	// Constructors:
//	// 		Provide a default empty playing circle constructor 
//	VectorMyJosephus();
//
//	//		- a constructor that initializes a playing circle of N people who 
//	//				will play this game
//	//		- both N and M are to be specified at input (during construction) and cannot change during the game.
//	//		- position values should be system assigned (i.e., by your code) in the order of insertion
//	//			for example, if N=5, then people {0,1,2,3,4} in the circle should be assigned positions:
//	//						{0,1,2,3,4} in that order respectively.
//
//	VectorMyJosephus(int N, int M);
//
//
//	// Destructor: make sure you free everything you allocated.
//	~VectorMyJosephus();
//
//	// Public methods:
//
//	//		This init function does the same thing as the argument constructor above.
//	//		This function is provided for convenience purposes:
//	//			To support the user code specifying either VectorMyJosephus(N,M) <or> VectorMyJosephus() first and then init(N,M). 
//	//			Both should achieve the same effect of initializing the game with N people and set M as the interval of elimination.
//	void init(int N, int M);
//
//	//	makes the circle empty 
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
//	int currentRound();
//	int startPlayers();
//	int startPasses();
//
//private:
//	vector<Person> circ;
//
//	int size;	// dynamic size of circle; initially size=N and then it will keep decreasing with each elimination
//	int N;		// the number of people at the start of the game.
//	int M;		// the interval of elimination; i.e., number of positions to skip before next elimination
//
//				// any other variables of your choice
//				// ....
//	int round;
//	int potato;
};



#endif