#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class FileLevel
{
private:
	char _level[460] = {0};
	int _enemies[15] = {0};
	sf::Vector2f _trees[6] = { {0.f, 0.f} };
	sf::Vector2f _movables[6] = { {0.f, 0.f} };
	int _levelNumber;
	int _enemiesNumber;
	int _treesNumber;
	int _movablesNumber;
	int points;
	int life;

public:
	FileLevel();
	~FileLevel();
	
	//getter
	char* getLevel();
	int* getEnemies();
	sf::Vector2f* getTrees();
	sf::Vector2f* getMovables();
	int getMovablesNumber();
	int getEnemiesNumber();
	int getTreesNumber();
	int getLevelNumber();
	int getPoints();
	int getLife();

	//setter
	void setLevel(char level[23][20]);
	void setEnemies(int enemies[15]);
	void setTrees(sf::Vector2f trees[6]);
	void setMovables(sf::Vector2f movables[6]);
	void setLevelNumber(int levelNumber);
	void setEnemiesNumber(int enemiesNumber);
	void setTreesNumber(int treesNumber);
	void setMovablesNumber(int movablesNumber);
	void setPoints(int points);
	void setLife(int life);

	//Savers
	bool saveLevel(int level);
	
	//Loader
	bool loadLevels(int level);
};


