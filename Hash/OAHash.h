#pragma once
#include <vector>
#include "HashFunctor.h"

template <typename T>
class OAHash
{
private:
	std::vector<T> m_bucket;
	int m_size;

public:
	OAHash() = default;
	OAHash(int size)
		: m_size(size)
	{
		m_bucket.resize(size);
	}
	~OAHash()
	{
		m_bucket.clear();
	}

public:
	void Emplace(HashFunctor<T> hashFunc, const T& value)
	{
		size_t hash = hashFunc(value) % m_size;
		size_t originHash = hash;

		bool flag = false;
		while (!m_bucket[hash].empty())
		{
			hash++;

			if (hash == m_size)
			{
				hash = 0;
				flag = true;
			}

			if (hash == originHash && flag)
			{
				printf("Open Address Bucket Crushed!\n");
			}
		}

 		m_bucket[hash] = value;
	}
};

