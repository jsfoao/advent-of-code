#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

#define RANGE 14
namespace challenges
{
	int UniqueRange(std::string data, int start, int range = RANGE)
	{
		int end = start + range;
		int index = 0;
		for (int i = start; i < end; i++)
		{
			for (int j = i + 1; j < end; j++)
			{
				if (data[i] == data[j])
				{
					return 0;
				}
				index = j;
			}
		}
		return index + 1;
	}

	void day6_p1()
	{
		std::ifstream file("input\\day6.txt");
		std::string line;
		if (!file.is_open())
			return;

		int count = 0;
		while (std::getline(file, line))
		{
			for (int i = 0; i < line.size() - RANGE; i++)
			{
				count = UniqueRange(line, i);
				if (count != 0)
				{
					break;
				}
			}
		}
		file.close();

		std::cout << count << std::endl;
	}
}