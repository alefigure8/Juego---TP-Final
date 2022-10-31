#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"
#include "Helper.h"
#include "Effect.h"

class Block 
	: public Base
{
protected:
	Animation _animation;
	Effect* _explotion;
	bool _alreadyDead;
	bool _haveEffect;

public:
	Block(std::string image, sf::Vector2u imageCount);
	~Block();

	void initEffect();
	
	//getter
	int getLife();
	bool getTarget();
	bool getHAveEffect();
	
	//setter
	void setLife(int life);
	void setScale(sf::Vector2f scale);
	void setAngle(float deg);
	void setTarget(bool target);
	void setHaveEffect(bool haveEffect);
	
	//update
	virtual void updateLife(){};
	void updateAnimation();
	void updateEffect();
	void update();

	void renderEffect(sf::RenderWindow& window);
};

