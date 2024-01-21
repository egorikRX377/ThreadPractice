#pragma once
#include <vector>
#include <thread>	


using namespace std;

int findMinElement(vector<int>& vec, size_t start, size_t end);

int parallelFindMinElement(vector<int>& vec, int numThreads);

