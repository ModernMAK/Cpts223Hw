
#ifndef MISC_H
#define MISC_H

#include <stack>
#include "string"
using std::string;
using std::stack;

//No ITOA and we're not c++11 compliant (no to_string)
string to_string(int i);

#endif