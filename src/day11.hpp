#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

#define WORRYDIV 3
namespace challenges
{	
	enum Op
	{
		Add, Mult, MultSelf
	};

	class Monkey
	{
	public:
		uint64_t Inspects;
		std::queue<uint64_t> Items;
		std::pair<Op, uint64_t> Operation;
		uint64_t Test;
		Monkey* TargetTrue;
		Monkey* TargetFalse;

		Monkey()
		{
			Inspects = 0;
			TargetTrue = nullptr;
			TargetFalse = nullptr;
		}

		Monkey(Op op, uint64_t opVal, uint64_t test)
		{
			Operation.first = op;
			Operation.second = opVal;
			Test = test;
			Inspects = 0;
			TargetTrue = nullptr;
			TargetFalse = nullptr;
		}

		void Inspect()
		{
			while (Items.size() != 0)
			{
				Inspects++;
				uint64_t worry = 0;
				uint64_t item = Items.front();
				switch (Operation.first)
				{
				case Op::Add:
					worry = item + Operation.second;
					break;
				case Op::Mult:
					worry = item * Operation.second;
					break;
				case Op::MultSelf:
					worry = item * item;
					break;
				default:
					break;
				}
				//worry = std::round(worry / WORRYDIV);
				if (worry % Test == 0)
				{
					Items.pop();
					TargetTrue->Items.push(worry);
				}
				else
				{
					Items.pop();
					TargetFalse->Items.push(worry);
				}
			}
		}

		void SetTargets(Monkey* mTrue, Monkey* mFalse)
		{
			TargetTrue = mTrue;
			TargetFalse = mFalse;
		}
	};

	static void day11_p1()
	{
		std::vector<Monkey*> monkas;

		// create monkeys
		Monkey* m0 = new Monkey(Op::Mult, 11, 7);
		m0->Items.push(66);
		m0->Items.push(79);
		monkas.push_back(m0);
		Monkey* m1 = new Monkey(Op::Mult, 17, 13);
		m1->Items.push(84);
		m1->Items.push(94);
		m1->Items.push(94);
		m1->Items.push(81);
		m1->Items.push(98);
		m1->Items.push(75);
		monkas.push_back(m1);
		std::cout << m1->Items.front() << std::endl;
		Monkey* m2 = new Monkey(Op::Add, 8, 5);
		m2->Items.push(85);
		m2->Items.push(79);
		m2->Items.push(59);
		m2->Items.push(64);
		m2->Items.push(79);
		m2->Items.push(95);
		m2->Items.push(67);
		monkas.push_back(m2);
		Monkey* m3 = new Monkey(Op::Add, 3, 19);
		m3->Items.push(70);
		monkas.push_back(m3);
		Monkey* m4 = new Monkey(Op::Add, 4, 2);
		m4->Items.push(57);
		m4->Items.push(69);
		m4->Items.push(78);
		m4->Items.push(78);
		monkas.push_back(m4);
		Monkey* m5 = new Monkey(Op::Add, 7, 11);
		m5->Items.push(65);
		m5->Items.push(92);
		m5->Items.push(60);
		m5->Items.push(74);
		m5->Items.push(72);
		monkas.push_back(m5);
		Monkey* m6 = new Monkey(Op::MultSelf, 0, 17);
		m6->Items.push(77);
		m6->Items.push(91);
		m6->Items.push(91);
		monkas.push_back(m6);
		Monkey* m7 = new Monkey(Op::Add, 6, 3);
		m7->Items.push(76);
		m7->Items.push(58);
		m7->Items.push(57);
		m7->Items.push(55);
		m7->Items.push(67);
		m7->Items.push(77);
		m7->Items.push(54);
		m7->Items.push(99);
		monkas.push_back(m7);
		m0->SetTargets(m6, m7);
		m1->SetTargets(m5, m2);
		m2->SetTargets(m4, m5);
		m3->SetTargets(m6, m0);
		m4->SetTargets(m0, m3);
		m5->SetTargets(m3, m4);
		m6->SetTargets(m1, m7);
		m7->SetTargets(m2, m1);

		int rounds = 0;
		while (rounds < 10000)
		{
			for (Monkey* m : monkas)
			{
				m->Inspect();
			}
			rounds++;
		}

		std::pair<uint64_t, uint64_t> maxes;
		std::pair<uint64_t, int> maxIndex;
		maxIndex.first = 0;
		maxIndex.second = -1;
		for (int i = 0; i < monkas.size(); i++)
		{
			if (monkas[i]->Inspects > maxIndex.first)
			{
				maxIndex.first = monkas[i]->Inspects;
				maxIndex.second = i;
			}
		}
		maxes.first = maxIndex.first;
		maxIndex.first = 0;
		for (int i = 0; i < monkas.size(); i++)
		{
			if (i == maxIndex.second)
			{
				continue;
			}
			if (monkas[i]->Inspects > maxIndex.first)
			{
				maxIndex.first = monkas[i]->Inspects;
			}
		}
		maxes.second = maxIndex.first;

		uint64_t monkeyBusiness = maxes.first * maxes.second;
		std::cout << "Answer: " << monkeyBusiness << std::endl;
		// 10036356988
	}
}