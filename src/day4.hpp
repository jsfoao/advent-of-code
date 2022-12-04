#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace challenges
{
	struct Range
	{
		unsigned int Min;
		unsigned int Max;

		Range(int min, int max)
		{
			Min = min;
			Max = max;
		}
	};

	void day4_p1()
	{
		std::ifstream file("input\\day4.txt");
		std::string line;
		if (!file.is_open())
			return;
		
		int total = 0;
		while (std::getline(file, line))
		{
			Range range1(line[0] - '0', line[2] - '0');
			Range range2(line[4] - '0', line[6] - '0');
			if (range1.Min >= range2.Min && range1.Max <= range2.Max)
			{
				total++;
				continue;
			}
			if (range2.Min >= range1.Min && range2.Max <= range1.Max)
			{
				total++;
			}
		}
		file.close();

		std::cout << "Answer: " << total << std::endl;
	}
}