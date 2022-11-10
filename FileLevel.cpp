#include "FileLevel.h"


FileLevel::FileLevel()
{
	_levelNumber = 0;
	_enemiesNumber = 0;
	_treesNumber = 0;
	_movablesNumber = 0; 
	points = 0;
	life = 3;
}

FileLevel::~FileLevel()
{
	
}

bool FileLevel::saveLevel(int level)
{
	FILE* pFile;
	pFile = fopen("Files/levels.dat", "rb+");
	
	if (pFile == NULL) {
		std::cout << "Error opening file" << std::endl;
		return false;
	};
	
	fseek(pFile, sizeof*this * (level - 1) , SEEK_SET);
	bool write = fwrite(this, sizeof * this, 1, pFile);
	fclose(pFile);
	return write;
}

bool FileLevel::loadLevels(int level)
{
	FILE* pFile = fopen("Files/levels.dat", "rb");
	
	if (pFile == NULL) {
		std::cout << "Error opening file" << std::endl;
		return false;
	};
	
	fseek(pFile, 0, SEEK_SET);
	fseek(pFile, sizeof * this * (level - 1), SEEK_SET);
	bool read = fread(this, sizeof * this, 1, pFile);
	fclose(pFile);
	
	return read;
}

int FileLevel::getEnemiesNumber()
{
	return _enemiesNumber;
}

int FileLevel::getTreesNumber()
{
	return _treesNumber;
}

int FileLevel::getMovablesNumber()
{
	return _movablesNumber;
}

int FileLevel::getLevelNumber()
{
	return _levelNumber;
}

char* FileLevel::getLevel()
{
	return _level;
}

int* FileLevel::getEnemies()
{
	return _enemies;
}

sf::Vector2f* FileLevel::getTrees()
{
	return _trees;
}

sf::Vector2f* FileLevel::getMovables()
{
	return _movables;
}

int FileLevel::getPoints()
{
	return points;
}

int FileLevel::getLife()
{
	return life;
}

void FileLevel::setLevel(char level[23][20])
{
	int k = 0;
	
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			_level[k++] = level[i][j];
		}
	}
}

void FileLevel::setEnemies(int enemies[15])
{
	for (int i = 0; i < 15; i++)
	{
		_enemies[i] = enemies[i];
	}
}

void FileLevel::setTrees(sf::Vector2f* trees)
{
	for (int i = 0; i < 6; i++)
	{
		_trees[i] = trees[i];
	}
}

void FileLevel::setMovables(sf::Vector2f* movables)
{
	for (int i = 0; i < 6; i++)
	{
		_movables[i] = movables[i];
	}
}

void FileLevel::setLevelNumber(int levelNumber)
{
	_levelNumber = levelNumber;
}

void FileLevel::setEnemiesNumber(int enemiesNumber)
{
	_enemiesNumber = enemiesNumber;
}

void FileLevel::setTreesNumber(int treesNumber)
{
	_treesNumber = treesNumber;
}

void FileLevel::setMovablesNumber(int movablesNumber)
{
	_movablesNumber = movablesNumber;
}

void FileLevel::setPoints(int points)
{
	this->points = points;
}

void FileLevel::setLife(int life)
{
	this->life = life;
}



