#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <iostream>
#include <map>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

void findFrequency(vector <string> vecOfStrings)
{
	map<std::string, int> countMap;

	//Iterate over the vector and store the frequency of each element in map
	for (auto& elem : vecOfStrings)
	{
		auto result = countMap.insert(pair<string, int>(elem, 1));
		if (result.second == false)
			result.first->second++;
	}

	// Iterate over the map
	for (auto& elem : countMap)
	{
		cout << elem.first << ": " << elem.second << endl;
	}
}

#endif