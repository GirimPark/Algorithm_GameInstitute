#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>

#include "ChainingHash.h"
#include "OAHash.h"

#include "Timer.h"

using namespace std;

set<string> wordSet;

constexpr int BUCKET_SIZE = 200000;

void LoadWords()
{
	fstream file;
	string word, filename;

	filename = "../english3.txt";
	file.open(filename.c_str());

	while (file >> word)
	{
		wordSet.emplace(word);
	}

	cout << "���� �ε� �Ϸ�, �� ������ �� : " << wordSet.size() << endl;
}

int main()
{
	LoadWords();

	Timer timer;
	HashFunctor<string> hashFunctor;

	/// myBucket �ؽøʿ� ������ ����(Chaining ���)
	ChainingHash<string> chainingBucket(5381);

	cout << "myBucket insert elapsed time(Chaining) : ";
	timer.Start();

	for (const auto& it : wordSet)
	{
		chainingBucket.Emplace(hashFunctor, it);
	}

	timer.Stop();
	timer.GetElapsedTime();

	/// myBucket �ؽøʿ� ������ ����(OpenAddress ���)
	OAHash<string> OABucket(BUCKET_SIZE);

	cout << "myBucket insert elapsed time(OpenAddress) : ";
	timer.Start();

	for (const auto& it : wordSet)
	{
		OABucket.Emplace(hashFunctor, it);
	}

	timer.Stop();
	timer.GetElapsedTime();

	///	stlBucket �ؽøʿ� ������ ����
	unordered_map<string, string> stlBucket(BUCKET_SIZE);

	cout << "stlBucket insert elapsed time : ";
	timer.Start();

	for (const auto& it : wordSet)
	{
		stlBucket.emplace(it, it);
	}

	timer.Stop();
	timer.GetElapsedTime();
}