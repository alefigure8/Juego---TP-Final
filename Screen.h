#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Screen
{
private:
	sf::Sprite _screen;
	sf::Texture _texture;
	bool _showInstuction;
	bool _showScreen;
	float _time;
	float _time_max;
	
public:
	Screen();
	~Screen();
	
	//clock
	bool isReady();
	void updateClock();

	//Screen
	void initInstruction();
	void initIntroLevel(int level);
	void initBadEnding();
	void initGoodEnding();
	void initTexture(std::string texture);
	
	//getters & setters
	bool getShowInstruction();
	bool getShowScreen();
	void setShow(bool show);
	
	//Methods
	void update();
	void render(sf::RenderWindow& window);
	
};

