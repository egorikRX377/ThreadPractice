#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <vector>

using namespace std;


void SinglethreadMultiplication(vector<int>& vec, int multiplier, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		vec[i] *= multiplier;
	}
}

void MultithreadMultiplication(vector<int>& vec, int multiplier, unsigned int numOfThreads)
{
	int vectorSize = vec.size();
	int segmentSize = vectorSize / numOfThreads;

	vector<thread> threads;

	for (int i = 0; i < numOfThreads; i++)
	{
		int start = i * segmentSize;
		int end = (i + 1 == numOfThreads - 1) ? vectorSize : (i + 1) * segmentSize;
		threads.emplace_back(SinglethreadMultiplication, ref(vec), multiplier, start, end);
	}

	for (auto& item : threads)
	{
		item.join();
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	vector<int> data1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<int> data2(data1);

	int multiplier = 2;

	SinglethreadMultiplication(data1, multiplier, 0, 10);

	for (const auto& item : data1)
	{
		cout << item << ' ';
	}

	cout << endl;

	MultithreadMultiplication(data2, multiplier, thread::hardware_concurrency());

	for (const auto& item : data2)
	{
		cout << item << ' ';
	}

	cout << endl;
	return 0;
}