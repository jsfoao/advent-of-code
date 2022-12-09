#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "utils/vec2.h"

namespace challenges
{
	Vector2 Step(Vector2 dir, Vector2& head, Vector2& tail)
	{
		head += dir;

		Vector2 tailDir;
		Vector2 diff = head - tail;
		if (diff.x == 0)
		{
			tailDir.x = 0;
		}
		else
		{
			tailDir.x = diff.x / std::abs(diff.x);
		}
		if (diff.y == 0)
		{
			tailDir.y = 0;
		}
		else
		{
			tailDir.y = diff.y / std::abs(diff.y);
		}

		Vector2 goal = tail + tailDir;
		if (goal != head)
		{
			tail += tailDir;
		}

		return tail;
	}

	void day9_p1()
	{
		std::ifstream file("input\\day9.txt");
		std::string line;
		if (!file.is_open())
			return;

		Vector2 head = Vector2::zero;
		Vector2 tail = Vector2::zero;
		std::vector<Vector2> visited;

		while (std::getline(file, line))
		{
			// process line
			Vector2 dir;
			switch (line[0])
			{
			case 'R':
				dir = Vector2::right;
				break;
			case 'L':
				dir = -Vector2::right;
				break;
			case 'U':
				dir = Vector2::up;
				break;
			case 'D':
				dir = -Vector2::up;
				break;
			default:
				break;
			}
			std::string num = "";
			for (int i = 2; i < line.size(); i++)
			{
				num += line[i];
			}
			Vector2 visit;
			unsigned int steps = std::stoi(num);
			for (unsigned int i = 0; i < steps; i++)
			{
				visit = Step(dir, head, tail);

				if (visited.size() == 0)
				{
					visited.push_back(visit);
				}
				else
				{
					bool found = false;
					for (Vector2 v : visited)
					{
						found = visit == v;
						if (visit == v)
						{
							found = true;
							break;
						}
					}
					if (!found)
					{
						visited.push_back(visit);
					}
				}
			}
		}
		file.close();

		std::cout << visited.size() << std::endl;
	}
}