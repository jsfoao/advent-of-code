#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

namespace challenges
{
	int UniqueRange(std::string data, int start, int range)
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
		const int range = 4;
		while (std::getline(file, line))
		{
			for (int i = 0; i < line.size() - range; i++)
			{
				count = UniqueRange(line, i, range);
				if (count != 0)
				{
					break;
				}
			}
		}
		file.close();

		std::cout << count << std::endl;
	}

	void day6_p2()
	{
		std::ifstream file("input\\day6.txt");
		std::string line;
		if (!file.is_open())
			return;

		int count = 0;
		const int range = 14;
		while (std::getline(file, line))
		{
			for (int i = 0; i < line.size() - range; i++)
			{
				count = UniqueRange(line, i, range);
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