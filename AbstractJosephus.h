
#ifndef __ABSTRACTMyJosephus_H__
#define __ABSTRACTMyJosephus_H__
#include "Person.h"

class AbstractJosephus
{
public:
	AbstractJosephus();
	virtual ~AbstractJosephus();
	AbstractJosephus(int N, int M);

	virtual void init(int N, int M);
	virtual void clear() = 0;
	int currentSize();
	bool isEmpty();
	Person eliminateNext();
	virtual void printAll() = 0;
	void reset();
	void reset(int N, int M);
protected://So subclasses can modify them
	void advanceElimPosition();
	void fillCircle();
	virtual void addPerson(int position) = 0;
	virtual Person getAndRemoveAt(int position) = 0;
	int size;
	int N;
	int M;
	int nextElimPosition;
};
#endif
