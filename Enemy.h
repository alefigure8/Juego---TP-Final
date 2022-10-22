#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tank.h"

class Enemy
	: public Tank
{
public:
	Enemy(std::string image, sf::Vector2u imageCount, float speed, float speed_attack, int hp);
	~Enemy();
};

