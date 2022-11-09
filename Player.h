#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tank.h"
class Player
	: public Tank
{
private:
	bool _visibility;
	
public:
	Player(std::string image, std::string armorTexture, sf::Vector2u imageCount);
	~Player();
	
	//getter
	bool getVisibility();

	//setter
	void setVisibility(bool visibility);
	
	//Methods
	void reset();
	void updateArmor(sf::RenderWindow& window);
};

