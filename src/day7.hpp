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
	class Object
	{
	public:
		Object* Parent;
		std::string Name;
		unsigned int ID;
		unsigned int Size;
		std::string Path;

		Object()
		{
			Parent = nullptr;
			Name = "";
			ID = DEFAULT_ID;
			Size = 0;
			Path = "";
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

	class Directory : public Object
	{
	public:
		std::vector<Object*> Children;

	public:
		Directory(Directory* parent, std::string name)
		{
			Name = name;
			ID = DIRECTORY_ID;
			Size = 0;
			if (parent != nullptr)
			{
				parent->AddChild(this);
				Parent = parent;
			}
			Path = GeneratePath();
		}

		Object* AddChild(Object* child)
		{
			Children.push_back(child);
			child->Parent = this;

			Directory* curr = this;
			while (curr != nullptr)
			{
				curr->Size += child->Size;
				curr = (Directory*)curr->Parent;
			}

			//Directory* dir = (Directory*)child->Parent;
			//dir->RemoveChild(child);
			return child;
		}

		bool RemoveChild(Object* child)
		{
			for (int i = 0; i < Children.size(); i++)
			{
				if (Children[i] == child)
				{
					Children.erase(Children.begin() + i);
					Directory* curr = this;
					while (curr != nullptr)
					{
						curr->Size -= child->Size;
						curr = (Directory*)curr->Parent;
					}
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
			Path = GeneratePath();
		}
	};

	class FileManager
	{
	public:
		Directory* Root;
		Directory* Current;
		std::vector<Object*> Objects;

	public:
		FileManager()
		{
			Root = (Directory*)Create(DIRECTORY_ID, "/", nullptr);
			Current = Root;
		}

		Object* Create(unsigned int typeId, std::string name, Directory* parent, unsigned int size = 0)
		{
			if (typeId == DIRECTORY_ID)
			{
				Directory* dir = new Directory(parent, name);
				Objects.push_back(dir);
				return dir;
			}
			else if (typeId == FILE_ID)
			{
				File* fil = new File(parent, name, size);
				Objects.push_back(fil);
				return fil;
			}
		}

		Object* Find(std::string name)
		{
			for (Object* obj : Objects)
			{
				if (obj->Name == name)
				{
					return obj;
				}
			}
			std::cout << "WARNING::FILEMANAGER::FIND : Couldn't find object of name: " << name << std::endl;
		}

		Directory* FindDir(std::string name)
		{
			for (Object* obj : Objects)
			{
				if (obj->Name == name)
				{
					return (Directory*)obj;
				}
			}
			std::cout << "WARNING::FILEMANAGER::FIND : Couldn't find object of name: " << name << std::endl;
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

	class CommandManager
	{
	private:
		FileManager* m_FileManager;

	public:
		void ReadCommand(std::string input)
		{
			// cd
			if (input[2] == 'c' && input[3] == 'd')
			{
				// cd ..
				if (input[5] == '.' && input[6] == '.')
				{
					// command
					if (m_FileManager->Current->Parent != nullptr)
					{
						SetCurrent(m_FileManager->Current->Parent);
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
					Object* obj = m_FileManager->Find(objInput);
					SetCurrent(obj);
				}
			}
			
			//// ls
			//if (input[2] == 'l' && input[3] == 's')
			//{
			//}

			// file
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
				m_FileManager->Create(FILE_ID, fileName, m_FileManager->Current, std::stoi(cmdInput));
			}

			// directory
			else if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r')
			{
				std::string dirInput = "";
				for (int i = 4; i < input.size(); i++)
				{
					dirInput += input[i];
				}
				m_FileManager->Create(DIRECTORY_ID, dirInput, m_FileManager->Current);
			}
		}

		void SetCurrent(Object* obj)
		{
			if (obj->ID != DIRECTORY_ID)
			{
				return;
			}
			m_FileManager->Current = (Directory*)obj;
			//std::cout << "Manager > Current : " << obj->Name << std::endl;
		}


		void Bind(FileManager* fm)
		{
			m_FileManager = fm;
		}

		void Unbind()
		{
			m_FileManager = nullptr;
		}
	};





	void day7_p1()
	{
		std::ifstream file("input\\day7.txt");
		std::string line;
		if (!file.is_open())
			return;

		FileManager* fm = new FileManager();
		CommandManager* cm = new CommandManager();
		cm->Bind(fm);

		while (std::getline(file, line))
		{
			cm->ReadCommand(line);
		}

		int sum = 0;
		for (Object* obj : fm->Objects)
		{
			if (obj->ID == DIRECTORY_ID && obj->Size < 100000)
			{
				sum += obj->Size;
			}

			int deep = 0;
			Directory* curr = (Directory*)obj;
			while (curr != nullptr)
			{
				deep++;
				curr = (Directory*)curr->Parent;
			}

			for (int i = 0; i < deep; i++)
			{
				std::cout << "--";
			}

			if (obj->ID == DIRECTORY_ID)
			{
				std::cout << "(" << obj->Name << ")" << " (" << obj->Size << ")" << " - " << obj->Path << std::endl;
			}
			if (obj->ID == FILE_ID)
			{
				std::cout << obj->Name << " (" << obj->Size << ")" << " - " << obj->Path << std::endl;
			}
		}
		file.close();

		std::cout << "Answer: " << sum << std::endl;
	}
}