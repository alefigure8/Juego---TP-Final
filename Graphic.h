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
	sf::Font _point_font;
	sf::Font _level_font;
	sf::Text _text;
	sf::Text _icon;
	sf::Text _point;
	sf::Text _level;
	
public:
	Graphic();
	~Graphic();
	void initText();
	void GUI_Point(int points);
	void GUI_Level(int level);
	void GUI_Player(Player* player);
	void GUI_Enemies(int enemies);
	void update(Player* player, int enemies, int points, int level);
	void render(sf::RenderWindow& window);
};

