#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <deque>

#define STACKS 9
namespace challenges
{
	void day5_p1()
	{
		std::ifstream file("input\\day5.txt");
		std::string line;
		if (!file.is_open())
			return;

		std::deque<char> stacks[STACKS];

		std::string numString = "";
		int moveIndex = 0;

		while (std::getline(file, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				char c = line[i];
				// create stack data from text
				// is character
				if (line[i] >= 65 && line[i] <= 90)
				{
					int stackIndex = (i - 1) / 4;
					stacks[stackIndex].push_back(line[i]);
				}

				// create move data from text
				if (line[0] != 'm')
					continue;

				int moveData[3];
				bool newNumCondition = line[i] == 'f' || line[i] == 't' || i == line.size() - 1;
				// is digit
				if (line[i] >= 48 && line[i] <= 57)
				{
					numString += line[i];
				}
				if (newNumCondition)
				{
					moveData[moveIndex] = std::stoi(numString);
					numString = "";
					moveIndex++;
				}

				// execute command
				if (moveIndex != 3)
					continue;

				for (int i = 0; i < moveData[0]; i++)
				{
					char top = stacks[moveData[1] - 1].front();
					stacks[moveData[1] - 1].pop_front();
					stacks[moveData[2] - 1].push_front(top);
				}
				moveIndex = 0;
			}
		}
		file.close();

		for (int i = 0; i < STACKS; i++)
		{
			std::cout << stacks[i].front();
		}
		std::cout << std::endl;
	}

	void day5_p2()
	{
		std::ifstream file("input\\day5.txt");
		std::string line;
		if (!file.is_open())
			return;

		std::deque<char> stacks[STACKS];

		std::string numString = "";
		int moveIndex = 0;

		while (std::getline(file, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				char c = line[i];
				// create stack data from text
				// is character
				if (line[i] >= 65 && line[i] <= 90)
				{
					int stackIndex = (i - 1) / 4;
					stacks[stackIndex].push_back(line[i]);
				}

				// create move data from text
				if (line[0] != 'm')
					continue;

				int moveData[3];
				bool newNumCondition = line[i] == 'f' || line[i] == 't' || i == line.size() - 1;
				// is digit
				if (line[i] >= 48 && line[i] <= 57)
				{
					numString += line[i];
				}
				if (newNumCondition)
				{
					moveData[moveIndex] = std::stoi(numString);
					numString = "";
					moveIndex++;
				}

				// execute command
				if (moveIndex != 3)
					continue;

				std::vector<char> data;

				for (int i = 0; i < moveData[0]; i++)
				{
					char top = stacks[moveData[1] - 1].front();
					data.push_back(top);
					stacks[moveData[1] - 1].pop_front();
				}

				for (int i = data.size() - 1; i >= 0; i--)
				{
					stacks[moveData[2] - 1].push_front(data[i]);
				}
				moveIndex = 0;
			}
		}
		file.close();

		for (int i = 0; i < STACKS; i++)
		{
			std::cout << stacks[i].front();
		}
		std::cout << std::endl;
	}
}