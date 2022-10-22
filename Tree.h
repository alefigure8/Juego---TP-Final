#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Block.h"
class Tree
	: public Block
{
public:
	Tree(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = { 300.f, 300.f });
	~Tree();
};

