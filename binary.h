#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <queue>
#include "PairComparer.h"

using namespace std;

priority_queue< pair<char, int>, vector<pair<char, int>>, MaxHeapPairComparer> max_pq{};

void findFrequency(vector <char> vecOfStrings)
{
	unordered_map<char, int> countMap;

	//Iterate over the vector and store the frequency of each element in map
	for (auto& elem : vecOfStrings)
	{
		auto result = countMap.insert(pair<char, int>(elem, 1));
		if (result.second == false)
			result.first->second++;
	}

	// Iterate over the map
	for (auto& elem : countMap)
	{
		max_pq.push(make_pair(elem.first, elem.second));
		cout << elem.first << ": " << elem.second << endl;
	}
}

#endif
