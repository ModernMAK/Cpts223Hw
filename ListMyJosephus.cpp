#include "ListMyJosephus.h"

ListMyJosephus::ListMyJosephus()
{
	init(0, 0);
}
ListMyJosephus::ListMyJosephus(int N, int M)
{
	init(N, M);
}

ListMyJosephus::~ListMyJosephus()
{
	//We dont allocate anything...
}

void ListMyJosephus::init(int N, int M)
{
	round = 0;
	size = this->N = N;
	this->M = M;
	circ = list<Person>();
	for(auto i = 0; i < size; i++)
	{
		circ.push_back(Person(i));
	}
	
}
void ListMyJosephus::clear()
{
	circ.clear();
	size = 0;
}
int ListMyJosephus::currentSize()
{
	return size;
}
bool ListMyJosephus::isEmpty()
{
	return size == 0;
}
Person ListMyJosephus::eliminateNext()
{
	if(size <= 0)
	{
		return Person();
	}
	auto elim = eliminatedIndex();
	auto removeAt = circ.begin();
	for (auto i = 0; i < elim; i++)
		++removeAt;
	auto person = *removeAt;
	circ.erase(removeAt);
	round++;
	size--;
	return person;
}

void ListMyJosephus::printAll()
{
	auto index = circ.begin();
	for(auto i = 0; i < size; i++)
	{
		(*index).print();
		cout << " ";
		++index;
	}
}

int ListMyJosephus::eliminatedIndex()
{
	return (M * round) % size;
}

int ListMyJosephus::currentRound()
{
	return round;
}

int ListMyJosephus::startPlayers()
{
	return N;
}

int ListMyJosephus::startPasses()
{
	return M;
}
