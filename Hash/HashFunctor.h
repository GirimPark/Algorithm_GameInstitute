#pragma once
#include <string>

template <typename T>
class HashFunctor
{
public:
	// djb2 알고리즘
	size_t operator()(const T& input) const
	{
		size_t hash = 5381;
		hash = (((hash << 5) + hash) + (input)) % 5381;

		return hash;
	}
};


template <>
class HashFunctor<std::string>
{
public:
	// djb2 알고리즘
	size_t operator()(const std::string& input) const
	{
		size_t hash = 5381;

		for (char c : input)
		{
			hash = ((hash << 5) + hash) + c;
		}

		return hash;
	}
};