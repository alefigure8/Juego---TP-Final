#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tank.h"
#include <time.h>

class Enemy
	: public Tank
{
private:
	bool _movement_state;
	int _direction;
	float _time_direction;
	float _max_time_direction;
public:
	Enemy(std::string image, std::string armorTexture, sf::Vector2u imageCount);
	~Enemy();
	
	//Methods
	void movement();
	bool canMove();
	void updateMovement();
	
	void setMovementState(bool state);
	bool getMovementState();
	
	void setTimeDirection(float time);
	float getTimeDirection();
};

