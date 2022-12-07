#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace challenges
{
	// $ is command
	// cd changes current directory
		// cd x moves IN one level: Looks for x in current directory and makes x current directory
		// cd .. moves OUT one level: Finds parent directory and makes it current directory
		// cd / makes current directory the outermost directory
	//ls prints all files and directories in current directory
		// 

	class Object
	{
	public:
		Object* Parent;
		std::string Name;
		unsigned int ID;
		unsigned int Size;
	};

	class Directory : public Object
	{
	public:
		std::vector<Object*> Children;

	public:
		Directory()
		{
			Parent = nullptr;
			Name = "";
			ID = 0;
		}

		Directory(Directory* parent, std::string name)
		{
			Parent = parent;
			Name = name;
			ID = 0;
		}

		Object* AddChild(Object* child)
		{
			Children.push_back(child);
			if (child->Parent == nullptr)
			{
				child->Parent = this;
			}
			else
			{
				Directory* dir = (Directory*)child->Parent;
				dir->RemoveChild(child);
			}
			return child;
		}

		bool RemoveChild(Object* child)
		{
			for (int i = 0; i < Children.size(); i++)
			{
				if (Children[i] == child)
				{
					Children.erase(Children.begin() + i);
					return true;
				}
			}
			return false;
		}
	};

	class File : public Object
	{
	public:
		Directory* Parent;
	};

	class Manager
	{
	public:
	};






	void day7_p1()
	{
		std::ifstream file("input\\day7.txt");
		std::string line;
		if (!file.is_open())
			return;

		while (std::getline(file, line))
		{
		}
		file.close();
	}
}