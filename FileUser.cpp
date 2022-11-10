#include "FileUser.h"

FileUser::FileUser()
{
	_name = "";
	_points = 0;
}

FileUser::~FileUser()
{
}

std::string FileUser::getName()
{
	return _name;
}

int FileUser::getPoints()
{
	return _points;
}

void FileUser::setName(std::string name)
{
	_name = name;
}

void FileUser::setPoints(int points)
{
	_points = points;
}

FileUser* FileUser::sortUsers()
{
	int cant = howManyUsers();
	FileUser* users = new FileUser[cant];
	for (int i = 0; i < cant; i++)
	{
		loadUser(i);
		users[i].setName(_name);
		users[i].setPoints(_points);
	}

	for (int i = 0; i < cant; i++)
	{
		for (int j = 0; j < cant - 1; j++)
		{
			if (users[j].getPoints() < users[j + 1].getPoints())
			{
				FileUser aux = users[j];
				users[j] = users[j + 1];
				users[j + 1] = aux;
			}
		}
	}
	
	return users;
}

int FileUser::howManyUsers()
{
	FILE* pFile;
	pFile = fopen("Files/user.dat", "rb");
	int count = 0;
	fseek(pFile, 0, SEEK_END);
	int bytes = ftell(pFile);
	int tam = sizeof * this;
	fclose(pFile);
	return bytes / tam;
}

bool FileUser::saveUser(std::string name, int points)
{
	FILE* p;
	p = fopen("Files/user.dat", "ab");
	
	if (p == NULL)
	{
		return false;
	}

	this->setName(name);
	this->setPoints(points);
	bool write = fwrite(this, sizeof* this, 1, p);
	fclose(p);
	return write;
}

bool FileUser::loadUser(int pos)
{
	FILE* p;
	p = fopen("Files/user.dat", "rb");
	
	if (p == NULL) return false;
	
	fseek(p, pos * sizeof* this, 0);
	bool read = fread(this, sizeof* this, 1, p);
	fclose(p);
	return read;
}
