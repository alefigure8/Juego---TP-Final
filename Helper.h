#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Helper
{
private:
	//Variables Clock
	float _time;
	float _time_max;

public:
	Helper();
	~Helper();
	
	//Getter & Setters Clock
	void setTime(float time);
	float getTime();
	
	// Clock Method
	bool isReady();
	
	//Clock Update
	void updateClock();

	//distance
	float distance(sf::Vector2f player, sf::Vector2f enemy);
	float degree(sf::Vector2f player, sf::Vector2f enemy);
	sf::Vector2f armorPosition(float degree, sf::FloatRect bounds, sf::Vector2f position);
};
