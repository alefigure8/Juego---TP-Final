#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Block.h"

class Movable
	: public Block
{
private:
	sf::Vector2f _last_position;
	float _movement_speed;
	
public:
	Movable(std::string image, sf::Vector2u imageCount, sf::Vector2f position = { 200.f, 200.f });

	//getters
	sf::Vector2f getLastPosition();

	//setters
	void move(float x, float y);

};

