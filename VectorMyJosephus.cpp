#include "VectorMyJosephus.h"

VectorMyJosephus::VectorMyJosephus()
{
	init(2, 1);
}

VectorMyJosephus::VectorMyJosephus(int N, int M)
{
	init(N, M);
}

VectorMyJosephus::~VectorMyJosephus()
{
}

//Initializes the list
void VectorMyJosephus::init(int N, int M)
{
	circ = vector<Person>();
	AbstractJosephus::init(N, M);
	fillCircle();
}

//Clears the list
void VectorMyJosephus::clear()
{
	circ.clear();
	size = 0;
}

//Prints all people in the list
void VectorMyJosephus::printAll()
{
	auto index = circ.begin();
	while (index != circ.end())
	{
		(*index).print();
		cout << " ";
		++index;
	}
}

//Adds a person with the given position
void VectorMyJosephus::addPerson(int position)
{
	circ.push_back(Person(position));
}

//Wraps position to size
Person VectorMyJosephus::getAndRemoveAt(int position)
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
//VectorMyJosephus::VectorMyJosephus()
//{
//	init(0, 0);
//}
//
//VectorMyJosephus::VectorMyJosephus(int N, int M)
//{
//	init(N, M);
//}
//
//VectorMyJosephus::~VectorMyJosephus()
//{
//	//We dont allocate anything...
//}
//
//void VectorMyJosephus::init(int N, int M)
//{
//	round = 1;
//	size = this->N = N;
//	potato = 0;
//	this->M = M;
//	circ = vector<Person>();
//	for (auto i = 0; i < size; i++)
//	{
//		circ.push_back(Person(i));
//	}
//
//}
//
//void VectorMyJosephus::clear()
//{
//	circ.clear();
//	size = 0;
//}
//
//int VectorMyJosephus::currentSize()
//{
//	return size;
//}
//
//bool VectorMyJosephus::isEmpty()
//{
//	return size == 0;
//}
//
//Person VectorMyJosephus::eliminateNext()
//{
//	if (size <= 0)
//	{
//		return Person();
//	}
//	potato = nextPotato();
//	auto removeAt = circ.begin();
//	for (auto i = 0; i < potato; i++)
//		++removeAt;
//	auto person = *removeAt;
//	circ.erase(removeAt);
//	round++;
//	potato++;
//	size--;
//	return person;
//}
//
//void VectorMyJosephus::printAll()
//{
//	auto index = circ.begin();
//	for (auto i = 0; i < size; i++)
//	{
//		(*index).print();
//		cout << " ";
//		++index;
//	}
//}
//
//int VectorMyJosephus::nextPotato()
//{
//	return (potato + M) % size;
//}
//int VectorMyJosephus::currentRound()
//{
//	return round;
//}
//
//int VectorMyJosephus::startPlayers()
//{
//	return N;
//}
//
//int VectorMyJosephus::startPasses()
//{
//	return M;
//}
