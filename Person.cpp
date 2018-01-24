#include "Person.h"

Person::Person()
{
	this->position = -1;
}

Person::Person(int position)
{
	this->position = position;
}

Person::~Person()
{
	//We dont allocate anything...
}

void Person::print()
{
	std::cout << position;
}
