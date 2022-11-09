#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Sound.h"

class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	
	//Init
	void initFont();
	void initImages();
	void initSound();
		
	//Getter
	int getPressedItem();
	bool getContinue();
	bool getShow();

	//setter
	void setShow(bool show);
	
	void stopSound();
	void MoveUp();
	void MoveDown();
	void addMenu(std::string title, int position);
	void restart();
	void render(sf::RenderWindow& window);

private:
	sf::Sprite _background;
	sf::Sprite _title;
	sf::Texture _texture_title;
	sf::Texture _texture_bg;
	sf::RectangleShape* _btn;
	int _selectedItemIndex;
	bool _continue;
	int _cant;
	int* _posY;
	sf::Vector2f _screen;
	sf::Font _font;
	sf::Text* _text;
	sf::Text _description;
	bool _show;

	Sound* _sound;
};

