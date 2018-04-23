#ifndef HASH_TABLE_INTERFACE
#define HASH_TABLE_INTERFACE
#include<ctime>

template<typename HashedObj>
class HashTableTestInterface
{
public:
	HashTableTestInterface() { _totalCollisions = 0; _timeStart = _timeEnd = clock(); }
	virtual ~HashTableTestInterface(){}

	virtual bool contains(const HashedObj & x) const = 0;

	virtual void makeEmpty() = 0;

	virtual bool insert(const HashedObj & x) = 0;

	virtual bool insert(HashedObj && x) = 0;

	virtual bool remove(const HashedObj & x) = 0;


	virtual bool testInsert(const HashedObj & x) = 0;

	virtual bool testInsert(HashedObj && x) = 0;

	int getTotalCollisions() const { return _totalCollisions; }
	void resetTotalCollisions() { _totalCollisions = 0; }
	void startTimer() { _timeStart = clock(); }
	void stopTimer() { _timeEnd = clock(); }
	void resetTimer() { _timeEnd = _timeStart = clock(); }
	double getTimeElapsed() const { return static_cast<double>(_timeEnd - _timeStart) / CLOCKS_PER_SEC; }

protected:
	void addCollision() { ++_totalCollisions; }
	int _totalCollisions;
	clock_t _timeStart;
	clock_t _timeEnd;

};

bool isPrime(int n);
int nextPrime(int n);
#endif
