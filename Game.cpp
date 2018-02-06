#include "Game.h"
Game::Game(AbstractJosephus* josephus)
{
	gameInterface = josephus;
}

Game::~Game()
{
}

void Game::init(int N, int M)
{
	gameInterface->init(N, M);
}

void Game::clear()
{
	gameInterface->clear();
}

int Game::currentSize()
{
	return gameInterface->currentSize();
}

bool Game::isEmpty()
{
	return gameInterface->isEmpty();
}

Person Game::eliminateNext()
{
	return gameInterface->eliminateNext();
}

Person Game::timeEliminateNext(double* elimTime)
{
	clock_t start = clock();
	Person elim = eliminateNext();
	clock_t end = clock();
	*elimTime = (double)(end - start) / CLOCKS_PER_SEC;
	return elim;
}

void Game::printAll()
{
	gameInterface->printAll();
}

void Game::reset()
{
	gameInterface->reset();
}

void Game::reset(int N, int M)
{
	gameInterface->reset(N,M);
}

void Game::play()
{
	queue<Person> elims = queue<Person>();
	int currentRound = 1;
	while(currentSize() > 1)
	{
		//Dont print on last round
		cout << "Round " << currentRound << endl;
		printAll();
		cout << endl;
		Person lost = eliminateNext();
		elims.push(lost);
		cout << "Eliminated ";
		lost.print();
		cout << endl;
		cout << "- - - - -" << endl;
		currentRound++;
	}
	cout << "Elimination Order" << endl;
	while(elims.size() > 0)
	{
		Person p = elims.front();
		elims.pop();
		p.print();
		cout << " ";
	}	
	cout << endl;
	cout << "Winner" << endl;
	eliminateNext().print();
	cout << endl;
}

double Game::timePlay(int * eliminations)
{
	double elimTime = 0;
	double totalTime = 0;
	queue<Person> elims = queue<Person>();
	while (gameInterface->currentSize() > 0)
	{
		Person lost = timeEliminateNext(&elimTime);
		elims.push(lost);
		totalTime += elimTime;
	}
	*eliminations = elims.size();
	return totalTime;
}
