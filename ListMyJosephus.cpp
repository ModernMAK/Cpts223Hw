#include "ListMyJosephus.h"

ListMyJosephus::ListMyJosephus()
{
	init(2, 1);
}

ListMyJosephus::ListMyJosephus(int N, int M)
{
	init(N, M);
}

ListMyJosephus::~ListMyJosephus()
{
}

//Initializes the list
void ListMyJosephus::init(int N, int M)
{
	circ = list<Person>();
	AbstractJosephus::init(N, M);
	fillCircle();
}

//Clears the list
void ListMyJosephus::clear()
{
	circ.clear();
	size = 0;
}

//Prints all people in the list
void ListMyJosephus::printAll()
{
	auto index = circ.begin();
	while(index != circ.end())
	{
		(*index).print();
		cout << " ";
		++index;
	}
}

//Adds a person with the given position
void ListMyJosephus::addPerson(int position)
{
	circ.push_back(Person(position));
}

//Wraps position to size
Person ListMyJosephus::getAndRemoveAt(int position)
{
	auto removeAt = circ.begin();
	for (auto i = 0; i < position; i++)
		++removeAt;
	auto person = *removeAt;
	circ.erase(removeAt);
	size--;
	return person;
}
//
//ListMyJosephus::ListMyJosephus()
//{
//	init(0, 0);
//}
//ListMyJosephus::ListMyJosephus(int N, int M)
//{
//	init(N, M);
//}
//
//ListMyJosephus::~ListMyJosephus()
//{
//	//We dont allocate anything...
//}
//
//void ListMyJosephus::init(int N, int M)
//{
//	round = 1;
//	size = this->N = N;
//	potato = 0;
//	this->M = M;
//	circ = list<Person>();
//	for(auto i = 0; i < size; i++)
//	{
//		circ.push_back(Person(i));
//	}
//	
//}
//void ListMyJosephus::clear()
//{
//	circ.clear();
//	size = 0;
//}
//int ListMyJosephus::currentSize()
//{
//	return size;
//}
//bool ListMyJosephus::isEmpty()
//{
//	return size == 0;
//}
//Person ListMyJosephus::eliminateNext()
//{
//	if(size <= 0)
//	{
//		return Person();
//	}
//	potato = nextPotato();
//	auto removeAt = circ.begin();
//	for (auto i = 0; i < potato; i++)
//		++removeAt;
//	auto person = *removeAt;
//	circ.erase(removeAt);
//	potato++;
//	round++;
//	size--;
//	return person;
//}
//
//void ListMyJosephus::printAll()
//{
//	auto index = circ.begin();
//	for(auto i = 0; i < size; i++)
//	{
//		(*index).print();
//		cout << " ";
//		++index;
//	}
//}
//
//int ListMyJosephus::nextPotato()
//{
//	return (potato + M) % size;
//}
//
//int ListMyJosephus::currentRound()
//{
//	return round;
//}
//
//int ListMyJosephus::startPlayers()
//{
//	return N;
//}
//
//int ListMyJosephus::startPasses()
//{
//	return M;
//}
