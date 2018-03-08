#include "Misc.h"

string to_string(int i)
{
	//0 is special, it breaks my algorithm, so... catch it here
	if (i == 0) return "0";

	string output = "";
	stack<char> s = stack<char>();

	if (i < 0)
	{
		output += "-";
		i = -i;
	}
	while (i > 0)
	{
		int digit = i % 10;
		i = i / 10;//integer division, truncates
		char temp = '0' + digit;
		s.push(temp);
	}
	while (!s.empty())
	{
		output += s.top();
		s.pop();
	}
	return output;
}