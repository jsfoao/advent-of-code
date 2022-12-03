#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

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

	char CommonCharLines(std::string line1, std::string line2, std::string line3)
	{
		std::vector<char> common;
		for (int i = 0; i < line1.size(); i++)
		{
			for (int j = 0; j < line2.size(); j++)
			{
				char c1 = line1[i];
				char c2 = line2[j];
				if (c1 == c2)
				{
					for (int k = 0; k < line3.size(); k++)
					{
						char c3 = line3[k];
						if (c2 == c3)
						{
							return c1;
						}
					}
				}
			}
		}
	}

	int GetCharScore(char c)
	{
		int score = 0;
		if (std::isupper(c))
		{
			score = c - 'A' + 27;
		}
		else
		{
			score = c - 'a' + 1;
		}
		return score;
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

	void day3_p2()
	{
		std::ifstream file("input\\day3.txt");
		std::string line;
		if (!file.is_open())
			return;

		int sum = 0;
		int count = 0;
		std::string line1;
		std::string line2;
		std::string line3;
		while (std::getline(file, line))
		{
			count++;
			if (count == 1)
			{
				line1 = line;
			}
			if (count == 2)
			{
				line2 = line;
			}
			if (count == 3)
			{
				line3 = line;
				char common = CommonCharLines(line1, line2, line3);
				int score = GetCharScore(common);
				sum += score;
				count = 0;
				std::cout << common << ": " << score << std::endl;
			}
		}

		std::cout << "Answer: " << sum << std::endl;
		file.close();
	}
}