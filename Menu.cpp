#include "Menu.h"

Menu::Menu(float width, float height)
{
	_screen.x = width;
	_screen.y = height;
	
	//Backgorund
	if (!_texture_title.loadFromFile("Texture/bg.png"))
	{
		std::cout << "Error loading texture" << std::endl;
	}
	
	
	if (!_texture_bg.loadFromFile("Texture/bg2.png"))
	{
		std::cout << "Error loading texture" << std::endl;
	}
	
	_background.setTexture(_texture_bg);
	_background.setPosition({ -20, -15 });
	_title.setTexture(_texture_title);
	_title.setPosition(sf::Vector2f(_screen.x / 2 - _title.getGlobalBounds().width / 2, 100.f));
	
	//Font
	if (!_font.loadFromFile("Font/pixel.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	_description.setFont(_font);
	_description.setString("Grupo 17 - Laboratorio de Computacion II - 2022");
	_description.setCharacterSize(15);
	_description.setPosition(sf::Vector2f(_screen.x / 2 - _description.getLocalBounds().width / 2, 600.f));
	
	_cant = 3;
	_text = new sf::Text[_cant];
	_selectedItemIndex = 0;
	_continue = false;

	//Options
	addMenu("PLAY", 0);
	addMenu("RANKING", 1);
	addMenu("EXIT", 2);
}

Menu::~Menu()
{
}

void Menu::addMenu(std::string title, int position)
{
	_text[position].setFont(_font);
	_text[position].setFillColor(position == 0 ? sf::Color::Green : sf::Color::White);
	_text[position].setString(title);
	_text[position].setPosition(sf::Vector2f(_screen.x / 2 - _text[position].getLocalBounds().width / 2, 300.f + (position + 1) * 50.f));
}

void Menu::render(sf::RenderWindow& window)
{
	window.draw(_background);
	window.draw(_description);
	window.draw(_title);

	for (int i = 0; i < _cant; i++)
	{
		window.draw(_text[i]);
	}

}

void Menu::MoveUp()
{

	if (_selectedItemIndex - 1 >= 0)
	{
		_text[_selectedItemIndex].setFillColor(sf::Color::White);
		_selectedItemIndex--;
		_text[_selectedItemIndex].setFillColor(sf::Color::Green);
	}

}

void Menu::MoveDown()
{

	if (_selectedItemIndex + 1 < _cant)
	{
		_text[_selectedItemIndex].setFillColor(sf::Color::White);
		_selectedItemIndex++;
		_text[_selectedItemIndex].setFillColor(sf::Color::Green);
	}

}

int Menu::GetPressedItem()
{
	return _selectedItemIndex;
}

bool Menu::getContinue()
{
	return _continue;
}

void Menu::restart()
{
	_cant = 4;
	_selectedItemIndex = 0;
	_continue = true;
	delete [] _text;
	_text = new sf::Text[_cant];
	addMenu("CONTINUE", 0);
	addMenu("RESTART", 1);
	addMenu("RANKING", 2);
	addMenu("EXIT", 3);
}