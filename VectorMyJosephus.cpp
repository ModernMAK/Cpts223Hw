#include "VectorMyJosephus.h"

VectorMyJosephus::VectorMyJosephus()
{
	init(0, 0);
}

VectorMyJosephus::VectorMyJosephus(int N, int M)
{
	init(N, M);
}

VectorMyJosephus::~VectorMyJosephus()
{
	//We dont allocate anything...
}

void VectorMyJosephus::init(int N, int M)
{
	round = 0;
	size = this->N = N;
	this->M = M;
	circ = vector<Person>();
	for (auto i = 0; i < size; i++)
	{
		circ.push_back(Person(i));
	}

}

void VectorMyJosephus::clear()
{
	circ.clear();
	size = 0;
}

int VectorMyJosephus::currentSize()
{
	return size;
}

bool VectorMyJosephus::isEmpty()
{
	return size == 0;
}

Person VectorMyJosephus::eliminateNext()
{
	if (size <= 0)
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

void VectorMyJosephus::printAll()
{
	auto index = circ.begin();
	for (auto i = 0; i < size; i++)
	{
		(*index).print();
		cout << " ";
		++index;
	}
}

int VectorMyJosephus::eliminatedIndex()
{
	return (M * round) % size;
}
int VectorMyJosephus::currentRound()
{
	return round;
}

int VectorMyJosephus::startPlayers()
{
	return N;
}

int VectorMyJosephus::startPasses()
{
	return M;
}
