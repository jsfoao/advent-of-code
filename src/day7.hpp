#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define DEFAULT 0
#define DIRECTORY 1
#define FILE 2

namespace challenges
{
	class Debug
	{
	public:
		static unsigned int FileLine;
		static void Log(std::string log)
		{
			std::cout << "Log: " << log << " (" << FileLine << ")" << std::endl;
		}
	};

	unsigned int Debug::FileLine = 0;

	class Object
	{
	protected:
		static Object* m_Root;
		static Object* m_Current;
		static std::vector<Object*> m_Objects;

		unsigned int m_Size;
	public:
		Object* Parent;
		std::vector<Object*> Children;
		std::string Name;
		unsigned int ID;
		std::string Path;

	protected:
		Object(unsigned int id, std::string name, Object* parent, unsigned int size = 0, bool root = false)
		{
			Name = name;
			ID = id;
			m_Size = size;
			if (!root)
			{
				Parent = parent;
				Parent->AddChild(this);
			}
			Path = GeneratePath();
		}

		void Resize(int resize)
		{
			m_Size += resize;
		}

	public:
		Object* AddChild(Object* child)
		{
			if (ID != DIRECTORY)
			{
				Debug::Log("AddChild: Not a directory");
			}

			Children.push_back(child);
			child->Parent = this;

			Object* curr = this;
			while (curr != nullptr)
			{
				curr->m_Size += child->m_Size;
				curr = curr->Parent;
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
					Object* curr = this;
					while (curr != nullptr)
					{
						curr->m_Size -= child->m_Size;
						curr = curr->Parent;
					}
					m_Size -= child->m_Size;
					return true;
				}
			}
			return false;
		}

		unsigned int GetSize()
		{
			return m_Size;
		}
		
		// creates root folder
		static void Init()
		{
			m_Root = Create(DIRECTORY, "/", nullptr, 0, true);
			SetCurrent(m_Root);
		}

		static Object* Create(unsigned int id, std::string name, Object* parent, unsigned int size = 0, bool root = false)
		{
			Object* obj = new Object(id, name, parent, size, root);
			AddObject(obj);
			return obj;
		}

		static Object* FindAll(std::string name)
		{
			for (Object* obj : m_Objects)
			{
				if (obj->Name == name)
				{
					return obj;
				}
			}
			Debug::Log("FindAll: Couldn't find object in all directories");
		}

		static Object* Find(std::string name)
		{
			if (name == "/")
			{
				return m_Root;
			}
			for (Object* obj : Object::GetCurrent()->Children)
			{
				if (obj->Name == name)
				{
					return obj;
				}
			}
			Debug::Log("Find: Couldn't find object in this directory");
		}

		static std::vector<Object*> GetObjects()
		{
			return m_Objects;
		}

		static Object* AddObject(Object* obj)
		{
			m_Objects.push_back(obj);
			return obj;
		}

		static Object* GetRoot()
		{
			return m_Root;
		}

		static Object* GetCurrent()
		{
			return m_Current;
		}

		static void SetCurrent(Object* curr)
		{
			if (curr->ID != DIRECTORY || curr == nullptr)
			{
				Debug::Log("SetCurrent: Can't set to invalid directory");
				return;
			}
			m_Current = curr;
		}

	protected:
		std::string GeneratePath()
		{
			Object* curr = Parent;
			std::string path = "";
			path += Name;
			while (curr != nullptr)
			{
				path += "/" + curr->Name;
				curr = curr->Parent;
			}
			return path;
		}
	};

	Object* Object::m_Root = nullptr;
	Object* Object::m_Current = nullptr;
	std::vector<Object*> Object::m_Objects;

	class Command
	{
	public:
		static void ReadCommand(std::string input)
		{
			// cd
			if (input[2] == 'c' && input[3] == 'd')
			{
				// cd ..
				if (input[5] == '.' && input[6] == '.')
				{
					// command
					if (Object::GetCurrent()->Parent != nullptr)
					{
						Object::SetCurrent(Object::GetCurrent()->Parent);
					}
				}
				// cd x
				else if (input[5] != ' ')
				{
					std::string objInput = "";
					for (int i = 5; i < input.size(); i++)
					{
						objInput += input[i];
					}

					//command
					Object* obj = Object::Find(objInput);
					Object::SetCurrent(obj);
				}
			}
			
			//// ls
			//if (input[2] == 'l' && input[3] == 's')
			//{
			//}

			// create file under current direcotry
			else if (input[0] >= '1' && input[0] <= '9')
			{
				std::string cmdInput = "";
				bool flag = false;
				int num = 0;
				std::string fileName = "";
				for (int i = 0; i < input.size(); i++)
				{
					if (input[i] == ' ')
					{
						flag = true;
						continue;
					}
					if (flag)
					{
						fileName += input[i];
					}
					else
					{
						cmdInput += input[i];
					}
				}
				Object::Create(FILE, fileName, Object::GetCurrent(), std::stoi(cmdInput));
			}

			// create directory under current directory
			else if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r')
			{
				std::string dirInput = "";
				for (int i = 4; i < input.size(); i++)
				{
					dirInput += input[i];
				}
				Object::Create(DIRECTORY, dirInput, Object::GetCurrent());
			}
		}
	};

	void day7_p1()
	{
		std::ifstream file("input\\day7.txt");
		std::string line;
		if (!file.is_open())
			return;

		Object::Init();

		unsigned int l = 1;
		while (std::getline(file, line))
		{
			Debug::FileLine = l;
			Command::ReadCommand(line);
			l++;
		}
		file.close();

		int sum = 0;
		for (Object* obj : Object::GetObjects())
		{
			if (obj->ID == DIRECTORY && obj->GetSize() < 100000)
			{
				sum += obj->GetSize();
			}
		}

		std::cout << "Answer: " << sum << std::endl;
	}

	void day7_p2()
	{
		std::ifstream file("input\\day7.txt");
		std::string line;
		if (!file.is_open())
			return;

		Object::Init();

		unsigned int l = 1;
		while (std::getline(file, line))
		{
			Debug::FileLine = l;
			Command::ReadCommand(line);
			l++;
		}
		file.close();

		int space = 30000000 - (70000000 - Object::GetRoot()->GetSize());
		std::vector<int> mins;
		int min = 70000000;
		for (Object* obj : Object::GetObjects())
		{
			int size = obj->GetSize();
			if (obj->ID == DIRECTORY && size >= space)
			{
				if (size < min)
				{
					min = size;
				}
			}
		}

		std::cout << "Answer: " << min << std::endl;
	}
}