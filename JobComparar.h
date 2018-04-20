
#ifndef JOB_COMPARAR_H 
#define JOB_COMPARAR_H
#include "Job.h"

//Based on 
//http://www.cplusplus.com/reference/functional/greater/
//We use this instead of making a comparison operator for Job since Jobs aren't inherintly value types
//Additionally, it would make sense to compare them by their UNIQUE ID, not their runtime
//To make this better, we could replace it with a lambda, but this is clear and consice.
struct JobComparar : std::binary_function <Job, Job, bool> {
	bool operator() (const Job& x, const Job& y) const;
};
#endif