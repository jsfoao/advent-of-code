#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "utils/vec2.h"

#define GRID_X 25
#define GRID_Y 25

namespace challenges
{
	struct Input
	{
		Vector2 Direction;
		int Steps;

		Input()
		{
			Direction = Vector2::zero;
			Steps = 0;
		}
		Input(Vector2 dir, int steps)
		{
			Direction = dir;
			Steps = steps;
		}

		static Input ProcessInput(std::string str)
		{
			Input input;
			switch (str[0])
			{
			case 'R':
				input.Direction = Vector2::right;
				break;
			case 'L':
				input.Direction = -Vector2::right;
				break;
			case 'U':
				input.Direction = Vector2::up;
				break;
			case 'D':
				input.Direction = -Vector2::up;
				break;
			default:
				break;
			}
			std::string num = "";
			for (int i = 2; i < str.size(); i++)
			{
				num += str[i];
			}
			input.Steps = std::stoi(num);
			return input;
		}
	};

	struct Knot
	{
		static std::vector<Knot*> Knots;

		Knot* Ahead;
		Vector2 Position;
		std::vector<Vector2> Visited;
		bool IsHead;

		Knot(Knot* ahead, Vector2 pos)
		{
			Ahead = ahead;
			Position = pos;
			Knots.push_back(this);
			IsHead = ahead == nullptr;
		}

		Knot(Knot* ahead)
		{
			Ahead = ahead;
			Position = Vector2::zero;
			Knots.push_back(this);
			IsHead = ahead == nullptr;
		}

		void Step()
		{
			// step in direction
			Vector2 dir;
			Vector2 diff = Ahead->Position - Position;
			if (diff.x == 0)
			{
				dir.x = 0;
			}
			else
			{
				dir.x = diff.x / std::abs(diff.x);
			}
			if (diff.y == 0)
			{
				dir.y = 0;
			}
			else
			{
				dir.y = diff.y / std::abs(diff.y);
			}

			Vector2 final = Position + dir;
			if (final != Ahead->Position)
			{
				Position += dir;
			}

			// add to unique visited
			if (Visited.size() == 0)
			{
				Visited.push_back(Position);
			}
			else
			{
				bool found = false;
				for (Vector2 v : Visited)
				{
					found = Position == v;
					if (found)
						break;
				}
				if (!found)
					Visited.push_back(Position);
			}
		}

		int GetVisitedCount()
		{
			return Visited.size();
		}

		static Knot* GetHead()
		{
			return Knots.front();
		}

		static Knot* GetTail()
		{
			return Knots.back();
		}
	};

	std::vector<Knot*> Knot::Knots;

	void DrawGrid()
	{
		system("CLS");
		for (int y = GRID_Y; y >= -GRID_Y; y--)
		{
			for (int x = -GRID_X; x < GRID_X; x++)
			{
				std::string c = ".";
				for (int i = 0; i < Knot::Knots.size(); i++)
				{
					if (Knot::Knots[i]->Position != Vector2(x, y))
					{
						continue;
					}

					if (Knot::Knots[i]->IsHead)
					{
						c = "H";
						break;
					}
					c = std::to_string(i);
					break;
				}
				std::cout << c;
			}
			std::cout << std::endl;
		}
	}

	void day9_p1()
	{
		std::ifstream file("input\\day9.txt");
		std::string line;
		if (!file.is_open())
			return;

		const unsigned int totalKnots = 10;

		new Knot(nullptr);
		for (int i = 1; i < totalKnots; i++)
		{
			new Knot(Knot::Knots[i - 1]);
		}

		while (std::getline(file, line))
		{
			Input input = Input::ProcessInput(line);
			while (input.Steps > 0)
			{
				for (Knot* knot : Knot::Knots)
				{
					if (knot->IsHead)
					{
						knot->Position += input.Direction;
					}
					else
					{
						knot->Step();
					}
				}
				input.Steps--;
			}
		}
		file.close();

		std::cout << Knot::GetTail()->GetVisitedCount() << std::endl;
	}
}