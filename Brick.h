#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Block.h"

class Brick
	: public Block
{
public:
	Brick(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = { 200.f, 200.f });
};

