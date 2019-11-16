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
#include <stack>
#include <sstream>
#include <fstream>
#include "PairComparer.h"

using namespace std;

priority_queue< pair<char, int>, vector<pair<char, int>>, MaxHeapPairComparer> max_pq{};

string inttoBinary(int someNum);

void findFrequency(vector <char> vecOfStrings)
{
	unordered_map<char, int> countMap;

	//Iterate over the vector and store the frequency of each element in map
	for (auto& elem : vecOfStrings)
	{
		if (elem > 0 && isalpha(elem))
		{
			elem = tolower(elem);
			auto result = countMap.insert(pair<char, int>(elem, 1));
			if (result.second == false)
				result.first->second++;
		}
	}

	ofstream binarymapfile;
	binarymapfile.open("binarymap.txt");
	int count = 1;

	// Iterate over the map
	for (auto& elem : countMap)
	{
		max_pq.push(make_pair(elem.first, elem.second));
		//cout << elem.first << ": " << elem.second << endl;
		cout << endl;
		binarymapfile << elem.first << ": " << " (" << elem.second << ") " << inttoBinary(count) << endl;
		count++;
	}

	binarymapfile.close();
}

void saveFrequency(vector <char> vecOfStrings)
{
	unordered_map<char, int> countMap;

	//Iterate over the vector and store the frequency of each element in map
	for (auto& elem : vecOfStrings)
	{
		if (elem > 0 && isalpha(elem))
		{
			elem = tolower(elem);
			auto result = countMap.insert(pair<char, int>(elem, 1));
			if (result.second == false)
				result.first->second++;
		}
	}

	ofstream binaryfile;
	binaryfile.open("binaryfile.txt");
	int count = 1;

	// Iterate over the map
	for (auto& elem : countMap)
	{
		max_pq.push(make_pair(elem.first, elem.second));
		//cout << elem.first << ": " << elem.second << endl;
		cout << endl;
		binaryfile << inttoBinary(count);
		count++;
	}

	binaryfile.close();
}

string inttoBinary(int someNum)
{
	stack<char>bits{};
	while (someNum > 0)
	{
		if ((someNum & 1) == true)
		{
			bits.push('1');
		}
		else
		{
			 bits.push('0');
		}
		someNum = someNum >> 1;
	}
	ostringstream result;
	while (bits.empty() == false)
	{
		result << bits.top();
		bits.pop();
	}
	return result.str();
}

#endif
