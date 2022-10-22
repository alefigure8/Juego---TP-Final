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
	Bullet(float pos_x, float pos_y, float x, float y, float degree);
	~Bullet();
	
	//getter
	float getMaxDistance();
	
	//setter
	void setMaxDistance(float distance);
};

