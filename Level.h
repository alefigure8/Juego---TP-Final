#pragma once
#include <iostream>
#include <time.h> 
#include "SFML/Graphics.hpp"
#include "Block.h"
#include "Brick.h"
#include "Tree.h"
#include "Movable.h"
#include "Unbreakable.h"
#include "Target.h"
#include "Street.h"
#include "FileLevel.h"

class Level
{
private:
	int _level;
	static const int HEIGHT_MAP = 23;
	static const int WIDTH_MAP = 20;
	Block* _tile[HEIGHT_MAP][WIDTH_MAP];
	sf::Vector2f _grid;
	sf::Vector2i _targetIndex;
	char _map[HEIGHT_MAP][WIDTH_MAP];
	
	//File Level
	FileLevel fileLevel;

public:
	Level(int level);
	~Level();
	
	//getter
	Block* getTile(int i, int j);
	int getHeight();
	int getWidth();
	sf::Vector2i getTargetIndex();
	
	//Methods
	void initFile();
	void initLevel();
	void update();
	void render(sf::RenderWindow& window);
};

