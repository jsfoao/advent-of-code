#include <iostream>
#include <vector>
#include <string>
#include "fileutils.h"

namespace challenges
{
	bool IsDigit(char character)
	{
		return character >= 48 && character <= 57;
	}

	void day1()
	{
		std::string input = FileUtils::ReadFile("input\\day1.txt");

		// table
		int max = 0;
		int topMaxes[3] = { 0, 0, 0 };

		// elf properties
		int total = 0;
		std::string numString = "";
		int num = 0;

		for (int i = 0; i < input.size(); i++)
		{
			if (IsDigit(input[i]))
			{
				numString += input[i];
				continue;
			}

			if (numString != "")
			{
				// add to current elf
				int num = std::stoi(numString);
				total += num;
				numString = "";
				num = 0;
			}

			// close current elf, open new elf
			if (input[i] == '\n' && input[i + 1] == '\n')
			{

				int index = -1;
				int lowestMax = 99999999999;
				for (int j = 0; j < 3; j++)
				{
					if (topMaxes[j] <= lowestMax)
					{
						lowestMax = topMaxes[j];
						index = j;
					}
				}
				if (total > lowestMax)
				{
					topMaxes[index] = total;
				}

				if (total > max)
				{
					max = total;
				}
				total = 0;
			}
		}

		// sum of top 3 maxes
		int sumTop = 0;
		for (int i = 0; i < 3; i++)
		{
			sumTop += topMaxes[i];
		}

		std::cout << "Answer P1: " << max << std::endl;
		std::cout << "Answer P2: " << sumTop << std::endl;
	}
}