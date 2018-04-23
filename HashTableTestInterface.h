#ifndef HASH_TABLE_INTERFACE
#define HASH_TABLE_INTERFACE
template<typename HashedObj>
class HashTableTestInterface
{
public:
	HashTableTestInterface() { _totalCollisions = 0; }
	virtual ~HashTableTestInterface(){}

	virtual bool contains(const HashedObj & x) const = 0;

	virtual void makeEmpty() = 0;

	virtual bool insert(const HashedObj & x) = 0;

	virtual bool insert(HashedObj && x) = 0;

	virtual bool remove(const HashedObj & x) = 0;

	int getTotalCollisions() const { return _totalCollisions; }

protected:
	int _totalCollisions;

};
#endif
