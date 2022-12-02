#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace challenges
{
	void day2_p1()
	{
		std::ifstream file("input\\day2.txt");
		std::string line;
		if (!file.is_open())
			return;

		int sum = 0;
		int resTable[9] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };
		while (std::getline(file, line))
		{
			int opp = line[0]-'A';
			int pl = line[2]-'X';
			int res = 0;
			if (pl == resTable[opp + 3 + 1])
				res = 2;
			if (pl == resTable[opp + 3])
				res = 1;
			sum += (res * 3) + pl + 1;
		}
		file.close();

		std::cout << "Answer: " << sum << std::endl;
	}

	void day2_p2()
	{
		std::ifstream file("input\\day2.txt");
		std::string line;
		if (!file.is_open())
			return;

		int sum = 0;
		int resTable[9] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };
		while (std::getline(file, line))
		{
			int opp = line[0]-'A';
			int res = line[2]-'X';
			int pl = resTable[opp + res + 2];
			sum += (res * 3) + pl + 1;
		}
		file.close();
		
		std::cout << "Answer: " << sum << std::endl;
	}
}