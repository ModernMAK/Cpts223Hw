#pragma once
#include <string>
using std::string;
using std::size_t;
struct SimpleHash
{
	size_t operator()(string const& obj) const noexcept
	{
		size_t hash = 0;
		for (char ch : obj)
			hash += ch;
		return hash;
	}
};

struct PrefixHash
{
	size_t operator()(string const& obj) const noexcept
	{
		if (obj.size() >= 2)
			return obj[0] + 27 * obj[1] + 729 * obj[2];
		if (obj.size() == 1)
			return obj[0] + 27 * obj[1];//obj[2] assumed 0
		if (obj.size() == 0)
			return obj[0];//obj[1] & obj[2] assumed 0
		return 0;//C++ is yelling at me that not all control paths return 0, this is to surpress that
	}
};

struct FullLengthHash
{
	size_t operator()(string const& obj) const noexcept
	{
		size_t hash = 0;
		for (char ch : obj)
			hash = 37 * hash + ch;
		return hash;
	}
};
