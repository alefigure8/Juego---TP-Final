#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tank.h"
class Player
	: public Tank
{
public:
	Player(std::string image, sf::Vector2u imageCount);
	~Player();
};

