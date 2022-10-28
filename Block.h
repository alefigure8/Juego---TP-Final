#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"

class Block 
	: public Base
{
protected:
	Animation _animation;


public:
	Block(std::string image, sf::Vector2u imageCount);
	~Block();
	
	//getter
	int getLife();
	bool getTarget();
	
	//setter
	void setLife(int life);
	void setScale(sf::Vector2f scale);
	void setAngle(float deg);
	void setTarget(bool target);
	
	//update
	virtual void updateLife(){};
	void updateAnimation();
	void update();
};

