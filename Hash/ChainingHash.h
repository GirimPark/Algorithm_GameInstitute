#pragma once
#include <vector>
#include "HashFunctor.h"

template <typename T>
class ChainingHash
{
private:
	std::vector<std::vector<T>> m_bucket;
	int m_size;

public:
	ChainingHash() = default;
	ChainingHash(int size)
		: m_size(size)
	{
		m_bucket.resize(size);
	}
	~ChainingHash()
	{
		for(auto& outer : m_bucket)
		{
			outer.clear();
		}
		m_bucket.clear();
	}

public:
	void Emplace(HashFunctor<T> hashFunc, const T& value)
	{
		size_t key = hashFunc(value) % m_size;
		m_bucket[key].emplace_back(value);
	}
};