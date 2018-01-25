#include "AbstractJosephus.h"



AbstractJosephus::AbstractJosephus()
{
	init(2, 1);
}


AbstractJosephus::~AbstractJosephus()
{
}

AbstractJosephus::AbstractJosephus(int N, int M)
{
	init(N, M);
}

void AbstractJosephus::init(int N, int M)
{
	this->size = N;
	this->N = N;
	this->M = M;
	this->nextElimPosition = 0;
	advanceElimPosition();//We could also put it in eliminateNext before eliminating...
}

int AbstractJosephus::currentSize()
{
	return size;
}

bool AbstractJosephus::isEmpty()
{
	return currentSize() == 0;
}

Person AbstractJosephus::eliminateNext()
{
	auto eliminated = getAndRemoveAt(nextElimPosition);
	advanceElimPosition();
	return eliminated;
}

void AbstractJosephus::reset(int N, int M)
{
	clear();
	init(N, M);
}
void AbstractJosephus::reset()
{
	reset(N, M);
}

void AbstractJosephus::advanceElimPosition()
{
	nextElimPosition = size > 0 ? (nextElimPosition + M) % size : size;
}
//Cant be inside init because constructors call the base instance.. which defeats the point of my init plans...
void AbstractJosephus::fillCircle()
{
	for (auto i = 0; i < size; i++)
	{
		addPerson(i);
	}
}
