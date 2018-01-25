#include "Game.h"
//
//Game::Game(bool useList, int N, int M)
//{
//	this->useList = useList;
//	if (useList)
//	{
//		list = ListMyJosephus(N, M);
//		vector = VectorMyJosephus();//Dont need it, but knowing c++, and without it being a pointer, but to not risk it
//	}
//	else
//	{
//		list = ListMyJosephus();//See vector above
//		vector = VectorMyJosephus(N, M);
//	}
//}
//
//Game::Game(AbstractJosephus* josephus)
//{
//}
//
//Game::~Game()
//{
//}
//
//void Game::init(int N, int M)
//{
//	if (useList)
//		list.init(N,M);
//	else
//		vector.init(N,M);
//}
//
//void Game::clear()
//{
//	if (useList)
//		list.clear();
//	else
//		vector.clear();
//}
//
//int Game::currentSize()
//{
//	return useList ? list.currentSize() : vector.currentSize();
//}
//
//bool Game::isEmpty()
//{
//	return useList ? list.isEmpty() : vector.isEmpty();
//}
//
//Person Game::eliminateNext()
//{
//	return useList ? list.eliminateNext() :	vector.eliminateNext();
//}
//
//void Game::printAll()
//{
//	if (useList)
//		list.printAll();
//	else
//		vector.printAll();
//}
//
//int Game::nextPotato()
//{
//	return useList ? list.nextPotato() : vector.nextPotato();
//}
//int Game::currentRound()
//{
//	return useList ? list.currentRound() : vector.currentRound();
//}
//
//void Game::play()
//{
//	auto elims = queue<Person>();
//	while(currentSize() > 1)
//	{
//		//Dont print on last round
//		cout << "Round " << currentRound() << endl;
//		printAll();
//		cout << endl;
//		auto lost = eliminateNext();
//		elims.push(lost);
//		cout << "Eliminated ";
//		lost.print();
//		cout << endl;
//		cout << "- - - - -" << endl;
//		
//	}
//	cout << "Elimination Order" << endl;
//	while(elims.size() > 0)
//	{
//		auto p = elims.front();
//		elims.pop();
//		p.print();
//		cout << " ";
//	}	
//	cout << endl;
//	cout << "Winner" << endl;
//	eliminateNext().print();
//	cout << endl;
//}
//
//void Game::reset()
//{
//	reset(startPlayers(), startPasses());
//}
//void Game::reset(int N, int M)
//{
//	clear();
//	init(N, M);
//}
//
//Person Game::timeEliminateNext(double*time)
//{
//	auto start = clock();
//	auto elim = eliminateNext();
//	auto end = clock();
//	*time = (double)(end - start) / CLOCKS_PER_SEC;
//	return elim;
//}
//double Game::timePlay(int * eliminations)
//{
//	double elimTime = 0;
//	double totalTime = 0;
//	auto elims = queue<Person>();
//	while (currentSize() > 0)
//	{
//		auto lost = timeEliminateNext(&elimTime);
//		elims.push(lost);
//		totalTime += elimTime;
//	}
//	*eliminations = elims.size();
//	return totalTime;
//}
//
//
//int Game::startPlayers()
//{
//	return useList ? list.startPlayers() : vector.startPlayers();
//}
//
//int Game::startPasses()
//{
//	return useList ? list.startPasses() : vector.startPasses();
//}
//
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
	auto start = clock();
	auto elim = eliminateNext();
	auto end = clock();
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
	auto elims = queue<Person>();
	auto currentRound = 1;
	while(currentSize() > 1)
	{
		//Dont print on last round
		cout << "Round " << currentRound << endl;
		printAll();
		cout << endl;
		auto lost = eliminateNext();
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
		auto p = elims.front();
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
	auto elims = queue<Person>();
	while (gameInterface->currentSize() > 0)
	{
		auto lost = timeEliminateNext(&elimTime);
		elims.push(lost);
		totalTime += elimTime;
	}
	*eliminations = elims.size();
	return totalTime;
}
