#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>

#include "Timer.h"

using namespace std;

set<string> wordSet;
int g_errorCnt = 0;

void LoadWords()
{
	fstream file;
	string word, filename;

	filename = "../english3.txt";
	file.open(filename.c_str());

	while (file >> word)
	{
		wordSet.insert(word);
	}

	cout << "파일 로드 완료, 총 데이터 수 : " << wordSet.size() << endl;
}

// djb2 알고리즘
void Insert_HashMap_Chaining(vector<vector<string>>& chainingBucket, const string& key)
{
	size_t hash = 5381;

	for (char c : key)
	{
		hash = ((hash << 5) + hash) + c;
	}

	hash %= 5381;

	chainingBucket[hash].emplace_back(key);
}

// 연속적인 메모리 공간이 부족하다
void Insert_HashMap_OA(vector<pair<string, int>>& OABucket, const string& key)
{
	size_t hash = 5381;

	for (char c : key)
	{
		hash = ((hash << 5) + hash) + c;
	}

	hash %= 5381;

	int collisionCnt = 0;
	while (!OABucket[hash].first.empty())
	{
		hash++;
		collisionCnt++;

		if (hash >= 5381)
			break;
	}

	if (hash < 5381)
	{
		OABucket[hash] = make_pair(key, collisionCnt);
	}
	else
	{
		g_errorCnt++;
	}
}

int main()
{
	LoadWords();

	Timer timer;

	/// myBucket 해시맵에 데이터 삽입(Chaining 기법)
	vector<vector<string>> chainingBucket(5381);

	cout << "myBucket insert elapsed time(Chaining) : ";
	timer.Start();

	for (const auto& it : wordSet)
	{
		Insert_HashMap_Chaining(chainingBucket, it);
	}

	timer.Stop();
	timer.GetElapsedTime();

	/// myBucket 해시맵에 데이터 삽입(OpenAddress 기법)
	vector<pair<string, int>> OABucket(5381);

	cout << "myBucket insert elapsed time(OpenAddress) : ";
	timer.Start();

	for (const auto& it : wordSet)
	{
		Insert_HashMap_OA(OABucket, it);
	}

	timer.Stop();
	timer.GetElapsedTime();

	cout << "OpenAddress Missed Some Data : " << g_errorCnt << endl;

	///	stlBucket 해시맵에 데이터 삽입
	unordered_map<string, string> stlBucket;

	cout << "stlBucket insert elapsed time : ";
	timer.Start();

	for (const auto& it : wordSet)
	{
		stlBucket.emplace(it, it);
	}

	timer.Stop();
	timer.GetElapsedTime();
}