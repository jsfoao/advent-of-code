#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Range
{
	unsigned int Min;
	unsigned int Max;

	Range()
	{
		Min = 0;
		Max = 0;
	}

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
		std::string num = "";
		std::vector<int> nums;
		for (int i = 0; i < line.size(); i++)
		{
			if (i == line.size() - 1)
			{
				num += line[i];
				nums.push_back(std::stoi(num));
				num = "";
				continue;
			}
			if (line[i] == '-' || line[i] == ',')
			{
				nums.push_back(std::stoi(num));
				num = "";
				continue;
			}
			num += line[i];
		}

		Range range1(nums[0], nums[1]);
		Range range2(nums[2], nums[3]);
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

void day4_p2()
{
	std::ifstream file("input\\day4.txt");
	std::string line;
	if (!file.is_open())
		return;

	int total = 0;
	while (std::getline(file, line))
	{
		std::string num = "";
		std::vector<int> nums;
		for (int i = 0; i < line.size(); i++)
		{
			if (i == line.size() - 1)
			{
				num += line[i];
				nums.push_back(std::stoi(num));
				num = "";
				continue;
			}
			if (line[i] == '-' || line[i] == ',')
			{
				nums.push_back(std::stoi(num));
				num = "";
				continue;
			}
			num += line[i];
		}

		Range range1(nums[0], nums[1]);
		Range range2(nums[2], nums[3]);
		if (range1.Min >= range2.Min && range1.Max <= range2.Max)
		{
			total++;
			continue;
		}
		if (range2.Min >= range1.Min && range2.Max <= range1.Max)
		{
			total++;
			continue;
		}
		if (range1.Max >= range2.Min && range1.Min <= range2.Max)
		{
			total++;
			continue;
		}
		if (range2.Max >= range1.Min && range2.Min <= range1.Max)
		{
			total++;
			continue;
		}
	}
	file.close();

	std::cout << "Answer: " << total << std::endl;
}

int main()
{
	day4_p2();
}
