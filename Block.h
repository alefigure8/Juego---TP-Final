#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"

class Block 
	: public Base
{
private:
	Animation _animation;
	int _life;
	int _max_life;
	void _initTexture(std::string image, sf::Vector2u imageCount);
public:
	Block(std::string image, sf::Vector2u imageCount);
	~Block();
	int getLife();
	void setLife(int life);
	void setScale(sf::Vector2f scale);
	void setAngle(float deg);
	void update();
};

