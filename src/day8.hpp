#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define GRID_X 5
#define GRID_Y 5
namespace challenges
{
	bool IsVisible(unsigned int grid[GRID_X][GRID_Y], int x, int y)
	{
		int curr = grid[x][y];
		int block = 0;
		for (int ix = 0; ix < GRID_X; ix++)
		{
			if (ix == x)
			{
				if (block == 0)
					break;
				continue;
			}

			if (grid[ix][y] >= curr)
			{
				block++;
				if (block == 2)
					break;
				ix = x;
			}
		}

		if (block != 2)
			return true;

		block = 0;
		for (int iy = 0; iy < GRID_Y; iy++)
		{
			if (iy == y)
			{
				if (block == 0)
					break;
				continue;
			}

			if (grid[x][iy] >= curr)
			{
				block++;
				if (block == 2)
					break;
				iy = y;
			}
		}

		if (block != 2)
			return true;

		return false;
	}

	int ScenicScore(unsigned int grid[GRID_X][GRID_Y], int x, int y)
	{
		if (x == 2 && y == 3)
		{
			std::cout << "hello" << std::endl;
		}

		int curr = grid[x][y];
		int score = 1;

		// left
		bool blocked = false;
		for (int xl = x - 1; xl >= 0; xl--)
		{
			if (grid[xl][y] >= curr)
			{
				score *= std::abs(xl - x);
				blocked = true;
				break;
			}
		}
		if (!blocked)
		{
			score *= x;
		}

		// right
		blocked = false;
		for (int xr = x + 1; xr < GRID_X; xr++)
		{
			if (grid[xr][y] >= curr)
			{
				score *= std::abs(xr - x);
				blocked = true;
				break;
			}
		}
		if (!blocked)
		{
			score *= GRID_X - x;
		}

		// bottom
		blocked = false;
		for (int yb = y + 1; yb < GRID_Y; yb++)
		{
			if (grid[x][yb] >= curr)
			{
				score *= std::abs(yb - y);
				blocked = true;
				break;
			}
		}
		if (!blocked)
		{
			score *= GRID_Y - y;
		}

		// top
		blocked = false;
		for (int yt = x - 1; yt >= 0; yt--)
		{
			if (grid[x][yt] >= curr)
			{
				score *= std::abs(yt - y);
				blocked = true;
				break;
			}
		}
		if (!blocked)
		{
			score *= y;
		}

		return score;
	}

	void day8_p1()
	{
		std::ifstream file("input\\day8.txt");
		std::string line;
		if (!file.is_open())
			return;

		unsigned int grid[GRID_X][GRID_Y] = {0};
		int y = 0;
		while (std::getline(file, line))
		{
			for (int x = 0; x < line.size(); x++)
			{
				std::string c(1, line[x]);
				grid[x][y] = std::stoi(c);
			}
			y++;
		}
		file.close();

		int visible = GRID_X * 2 + GRID_Y * 2 - 4;
		for (int y = 1; y < GRID_Y - 1; y++)
		{
			for (int x = 1; x < GRID_X - 1; x++)
			{
				visible += IsVisible(grid, x, y);
			}
		}

		std::cout << "Answer: " << visible << std::endl;
	}

	void day8_p2()
	{
		std::ifstream file("input\\day8.txt");
		std::string line;
		if (!file.is_open())
			return;

		unsigned int grid[GRID_X][GRID_Y] = { 0 };
		int y = 0;
		while (std::getline(file, line))
		{
			for (int x = 0; x < line.size(); x++)
			{
				std::string c(1, line[x]);
				grid[x][y] = std::stoi(c);
			}
			y++;
		}
		file.close();

		int max = 0;
		for (int y = 1; y < GRID_Y - 1; y++)
		{
			for (int x = 1; x < GRID_X - 1; x++)
			{
				int score = ScenicScore(grid, x, y);
				if (score > max)
				{
					max = score;
				}
			}
		}

		std::cout << "Answer: " << max << std::endl;
	}
}