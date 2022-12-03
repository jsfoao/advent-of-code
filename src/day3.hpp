#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace challenges
{
	char CommonChar(std::string line)
	{
		for (int i = 0; i < line.size() / 2; i++)
		{
			for (int j = line.size() / 2; j < line.size(); j++)
			{
				char c1 = line[i];
				char c2 = line[j];
				if (c1 == c2)
				{
					return c1;
				}
			}
		}
	}

	void day3_p1()
	{
		std::ifstream file("input\\day3.txt");
		std::string line;
		if (!file.is_open())
			return;

		int sum = 0;
		while (std::getline(file, line))
		{
			char common = CommonChar(line);
			int score = 0;
			if (std::isupper(common))
			{
				score = common - 'A' + 27;
			}
			else
			{
				score = common - 'a' + 1;
			}
			sum += score;
			std::cout << score << std::endl;
		}

		std::cout << "Answer: " << sum << std::endl;
		file.close();
	}
}