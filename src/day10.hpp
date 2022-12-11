#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace challenges
{
	static int cycle = 0;
	static int curr = 1;
	static int sum = 0;
	static int check[6] = { 20, 60, 100, 140, 180, 220 };

	static void Cycle()
	{
		cycle++;
		for (int i = 0; i < 6; i++)
		{
			if (cycle == check[i])
			{
				sum += check[i] * curr;
			}
		}
	}
	
	static int lineCycle = 40;
	static int adjust = 0;
	static void CycleDraw()
	{
		cycle++;
		if (cycle > lineCycle)
		{
			std::cout << std::endl;
			lineCycle += 40;
			adjust += 40;
		}
		if (cycle == curr + adjust || cycle == curr + 1 + adjust || cycle == curr + 2 + adjust)
		{
			std::cout << "#";
		}
		else
		{
			std::cout << ".";
		}
	}

	static void day10_p1()
	{
		std::ifstream file("input\\day10.txt");
		std::string line;
		if (!file.is_open())
			return;

		while (std::getline(file, line))
		{
			if (line == "noop")
			{
				Cycle();
				continue;
			}

			if (line[0] == 'a')
			{
				std::string num = "";
				for (int i = 5; i < line.size(); i++)
				{
					num += line[i];
				}
				int val = std::stoi(num);

				int c = 2;
				while (c > 0)
				{
					Cycle();
					c--;
				}
				curr += val;
			}
		}
		file.close();

		std::cout << "Answer: " << sum << std::endl;
	}


	static void day10_p2()
	{
		std::ifstream file("input\\day10.txt");
		std::string line;
		if (!file.is_open())
			return;

		while (std::getline(file, line))
		{
			if (line == "noop")
			{
				CycleDraw();
				continue;
			}

			if (line[0] == 'a')
			{
				std::string num = "";
				for (int i = 5; i < line.size(); i++)
				{
					num += line[i];
				}
				int val = std::stoi(num);
				
				int c = 2;
				while (c > 0)
				{
					CycleDraw();
					c--;
				}
				curr += val;
			}
		}
		file.close();
	}
}