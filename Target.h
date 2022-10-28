#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Block.h"

class Target
	:public Block
{
public:
	Target(std::string image, sf::Vector2u imageCount);
	~Target();
};

