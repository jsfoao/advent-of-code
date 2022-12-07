#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define DEFAULT_ID 0
#define DIRECTORY_ID 1
#define FILE_ID 2

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

		Object()
		{
			Parent = nullptr;
			Name = "";
			ID = DEFAULT_ID;
		}
	};

	class Directory : public Object
	{
	public:
		std::vector<Object*> Children;
		bool IsRoot;

	public:
		Directory(Directory* parent, std::string name)
		{
			Name = name;
			ID = DIRECTORY_ID;
			Size = 0;
			if (parent != nullptr)
			{
				IsRoot = false;
				parent->AddChild(this);
				Parent = parent;
			}
			else
			{
				IsRoot = true;
			}
		}

		Object* AddChild(Object* child)
		{
			Children.push_back(child);
			Size += child->Size;
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
					Size -= child->Size;
					return true;
				}
			}
			return false;
		}
	};

	class File : public Object
	{
	public:
		File(Directory* parent, std::string name, unsigned int size)
		{
			Name = name;
			ID = FILE_ID;
			Size = size;
			parent->AddChild(this);
			Parent = parent;
		}
	};

	class FileManager
	{
	public:
		Directory* Root;
		Directory* Current;

	public:
		FileManager()
		{
			Root = new Directory(nullptr, "/");
			Current = Root;
		}

		static void Print(Directory* directory)
		{
			std::cout << directory->Name << " (" << "folder" << ", " << directory->Size << ")" << std::endl;
			for (Object* obj : directory->Children)
			{
				std::string type = "";
				if (obj->ID == DIRECTORY_ID)
					type = "folder";
				else if (obj->ID == FILE_ID)
					type = "file";

				std::cout << "-- " << obj->Name << " (" << type << ", " << obj->Size << ")" << std::endl;
			}
		}
	};

	class Command
	{
	public:
		std::string Input;

	public:
		Command(std::string input)
		{
			Input = input;
		}

		virtual void Execute() {};
	};

	class CommandManager
	{
	public:
		std::vector<Command> Commands;

	public:
		void ReadCommand(std::string input)
		{
			for (Command command : Commands)
			{
				if (input == command.Input)
				{
					command.Execute();
				}
			}
		}

		void Register(Command command)
		{
			Commands.push_back(command);
		}

		void Unregister(Command command)
		{
			for (size_t i = 0; i < Commands.size(); i++)
			{
				if (command.Input == Commands[i].Input)
				{
					Commands.erase(Commands.begin() + i);
				}
			}
		}

		void PrintCommands()
		{
			std::cout << "Commands: ";
			for (Command command : Commands)
			{
				std::cout << command.Input << ", ";
			}
			std::cout << std::endl;
		}
	};





	void day7_p1()
	{
		std::ifstream file("input\\day7.txt");
		std::string line;
		if (!file.is_open())
			return;

		CommandManager commandManager;
		commandManager.Register(Command("cd"));
		commandManager.Register(Command("ls"));
		//commandManager.PrintCommands();

		FileManager fileManager;
		Directory* dir = new Directory(fileManager.Root, "random");
		File* fil = new File(fileManager.Root, "hello.txt", 10);
		FileManager::Print(fileManager.Root);



		//while (std::getline(file, line))
		//{
		//}
		file.close();
	}
}