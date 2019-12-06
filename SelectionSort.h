#pragma once
#include "Sorter.h"

template <typename T>

void Selectsort(vector<T>& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		int smallest_index = i;
		for (int j = i + 1; j < data.size(); j++)
		{
			if (data[j] < data[smallest_index])
			{
				smallest_index = j;
			}
		}

		T temp = data[i];
		data[i] = data[smallest_index];
		data[smallest_index] = temp;
	}
};