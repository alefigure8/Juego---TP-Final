#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	
	void addMenu(std::string title, int position);
	void render(sf::RenderWindow& window);
	void restart();
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	bool getContinue();

private:
	sf::Sprite _background;
	sf::Sprite _title;
	sf::Texture _texture_title;
	sf::Texture _texture_bg;
	int _selectedItemIndex;
	bool _continue;
	int _cant;
	int* _posY;
	sf::Vector2f _screen;
	sf::Font _font;
	sf::Text* _text;
	sf::Text _description;
};

