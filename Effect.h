#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"
#include "Helper.h"

class Effect
	: public Base
{
private:
	bool _state;
	float _currentImage;
	float _currentImageMax;
	Animation _animation;
	Helper* _effect_clock;
	
	void _initTexture(std::string texture);
	void _initClock();

public:
	Effect(std::string texture, sf::Vector2u imageCount);
	~Effect();

	//getter
	bool getState();
	float getRotation();
	float getCurrentImage();
	float getCurrentImageMax();
	
	//setter
	void setState(bool state);
	void setRotation(float deg);
	void setCurrentImage(float currentImage);

	//Methods
	void updateAnimation();
	void update();
};

