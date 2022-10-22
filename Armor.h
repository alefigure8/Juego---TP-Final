#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"

class Armor
	: public Base
{
public:
	sf::Sprite getArmor();
	float getRotationArmor();
	sf::Vector2f getOriginArmor();
	void setRotation(float degree);
	void move(float x, float y);
};

