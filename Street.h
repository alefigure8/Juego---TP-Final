#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Block.h"

class Street
	: public Block
{
public:
	Street(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = { 300.f, 300.f });
	~Street();
};

