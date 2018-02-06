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
	vector<Person>::iterator index = circ.begin();
	while (index != circ.end())
	{
		(*index).print();
		std::cout << " ";
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
	vector<Person>::iterator removeAt = circ.begin();
	for (int i = 0; i < position; i++)
		++removeAt;
	Person person = *removeAt;
	circ.erase(removeAt);
	size--;
	return person;
}