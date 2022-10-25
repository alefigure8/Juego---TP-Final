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
	sf::Vector2f _player_position;
public:
	Enemy(std::string image, std::string armorTexture, sf::Vector2u imageCount);
	~Enemy();

	//getters
	bool getMovementState();
	float getTimeDirection();


	//setters
	void setTimeDirection(float time);
	void setMovementState(bool state);
	
	//Methods
	void movement();
	bool canMove();

	//updates
	void updateTime();
	void updateArmor();
	void updateMovement(sf::Vector2f player_position);
	
};

