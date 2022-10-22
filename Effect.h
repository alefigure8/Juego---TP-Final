#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"

class Effect
	: public Base
{
private:
	float _timeMax;
	float _time;
	bool _state;
	void _initTexture(std::string texture);

public:
	Effect(std::string texture);
	~Effect();

	//getter
	float getTime();
	float getTimeMax();
	bool getState();
	float getRotation();
	
	//setter
	void setTime(float time);
	void setTimeMax(float time);
	void setState(bool state);
	void setRotation(float deg);
};

