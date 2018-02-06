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
	list<Person>::iterator index = circ.begin();
	while(index != circ.end())
	{
		(*index).print();
		std::cout << " ";
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
	list<Person>::iterator removeAt = circ.begin();
	for (int i = 0; i < position; i++)
		++removeAt;
	Person person = *removeAt;
	circ.erase(removeAt);
	size--;
	return person;
}