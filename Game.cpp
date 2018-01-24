#include "Game.h"

Game::Game(bool useList, int N, int M)
{
	this->useList = useList;
	if (useList)
	{
		list = ListMyJosephus(N, M);
		vector = VectorMyJosephus();//Dont need it, but knowing c++, and without it being a pointer, but to not risk it
	}
	else
	{
		list = ListMyJosephus();//See vector above
		vector = VectorMyJosephus(N, M);
	}
}

Game::~Game()
{
}

void Game::init(int N, int M)
{
	if (useList)
		list.init(N,M);
	else
		vector.init(N,M);
}

void Game::clear()
{
	if (useList)
		list.clear();
	else
		vector.clear();
}

int Game::currentSize()
{
	return useList ? list.currentSize() : vector.currentSize();
}

bool Game::isEmpty()
{
	return useList ? list.isEmpty() : vector.isEmpty();
}

Person Game::eliminateNext()
{
	return useList ? list.eliminateNext() :	vector.eliminateNext();
}

void Game::printAll()
{
	if (useList)
		list.printAll();
	else
		vector.printAll();
}

int Game::eliminatedIndex()
{
	return useList ? list.eliminatedIndex() : vector.eliminatedIndex();
}
int Game::currentRound()
{
	return useList ? list.currentRound() : vector.currentRound();
}

void Game::play(bool printRounds)
{
	auto elims = queue<Person>();
	while(currentSize() > 0)
	{
		//Dont print on last round regardless
		if (printRounds && currentSize() > 1)
		{
			cout << "Round " << currentRound() << endl;
			printAll();
			cout << endl;
			cout << "- - - - -" << endl;
		}
		auto lost = eliminateNext();
		elims.push(lost);
	}
	cout << "Elimination Order" << endl;
	while(elims.size() > 0)
	{
		auto p = elims.front();
		p.print();
		cout << " ";
	}
}

void Game::reset()
{
	clear();
	init(startPlayers(), startPasses());
}

double Game::time()
{
	auto start = clock();
	play(false);
	auto end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}

int Game::startPlayers()
{
	return useList ? list.startPlayers() : vector.startPlayers();
}

int Game::startPasses()
{
	return useList ? list.startPasses() : vector.startPasses();
}

