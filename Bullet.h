#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"

class Bullet
	: public Base
{
private:
	sf::Vector2f _direction;
	float _movement_speed;
	float _max_distance;

public:
	Bullet(sf::Vector2f pos, sf::Vector2f direction, float degree, std::string texture);
	~Bullet();
	
	//getter
	float getMaxDistance();
	
	//setter
	void setMaxDistance(float distance);

	//methods
	void update();
};

