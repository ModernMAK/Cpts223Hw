#include "JobComparar.h"

//Based on 
//http://www.cplusplus.com/reference/functional/greater/
bool JobComparar::operator()(const Job& x, const Job& y) const
{ 
	return x.getTicksRequired()<y.getTicksRequired();
}
