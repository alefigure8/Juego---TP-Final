#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <iomanip>
#include <sstream>

class Graphic
{
private:
	sf::Font _font;
	sf::Font _icon_font;
	sf::Text _text;
	sf::Text _icon;
	
public:
	Graphic();
	~Graphic();
	void initText();
	//void GUI_point(int points);
	void GUI_Player(Player* player);
	void GUI_Enemies(int enemies);
	void update(Player* player, int enemies);
	void render(sf::RenderWindow& window);
};

