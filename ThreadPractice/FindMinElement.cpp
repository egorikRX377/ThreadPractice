#include "FindMinElement.h"


using namespace std;


int findMinElement(vector<int>& vec, size_t start, size_t end)
{
	int minValue = vec[start];

	for (int i = start; i < end; i++)
	{
		if (vec[i] < minValue)
		{
			minValue = vec[i];
		}
	}

	return minValue;
}


int parallelFindMinElement(vector<int>& vec, int numThreads)
{
	size_t vecSize = vec.size();
	size_t segmentSize = vecSize / numThreads;

	vector<int> minValues;

	vector<thread> threads;

	for (int i = 0; i < numThreads; i++)
	{
		size_t start = i * segmentSize;
		size_t end = (i + 1 == numThreads) ? vecSize : (i + 1) * segmentSize;

		threads.emplace_back([&, start, end]() { minValues.push_back(findMinElement(vec, start, end)); });
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	int minElement = findMinElement(minValues, 0, minValues.size());

	return minElement;
}
