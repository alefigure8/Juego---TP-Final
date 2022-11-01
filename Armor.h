#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"
#include "Effect.h"

class Armor
	: public Base
{
protected:
	Animation _animation;
public:
	Armor(std::string image, sf::Vector2u imageCount);

	//getter
	sf::Sprite getArmor();
	float getRotationArmor();
	sf::Vector2f getOriginArmor();
	
	//setter
	void setRotation(float degree);

	//methods
	void move(float x, float y);
	void updateAnimation(sf::Vector2u currentImagect);
};

