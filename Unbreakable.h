#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Block.h"

class Unbreakable
	: public Block
{
public:
	Unbreakable(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = { 400.f, 400.f });
	~Unbreakable();
	void updateLife() override;
};


