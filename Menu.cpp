#include "Menu.h"

Menu::Menu(float width, float height)
{
	_screen.x = width;
	_screen.y = height;
	_cant = 3;
	_selectedItemIndex = 0;
	_continue = false;
	_show = true;
	
	initImages();
	initFont();
	initSound();
	
	//Options
	_text = new sf::Text[_cant];
	_btn = new sf::RectangleShape[_cant];
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
	_text[position].setFillColor(sf::Color::White);
	_text[position].setString(title);
	_text[position].setPosition(sf::Vector2f(_screen.x / 2 - _text[position].getLocalBounds().width / 2, 300.f + (position + 1) * 50.f));
	_btn[position].setFillColor(position == 0 ? sf::Color{ 255, 255, 255, 100 } : sf::Color{0, 0, 0, 150});
	_btn[position].setSize({ _text[position].getLocalBounds().width + 30.f, 40.f});
	_btn[position].setPosition(sf::Vector2f(_screen.x / 2 - _btn[position].getSize().x / 2, 300.f + (position + 1) * 50.f));
	_btn[position].setOutlineThickness(3);
	_btn[position].setOutlineColor(sf::Color(0, 0, 0, 180));
}

void Menu::render(sf::RenderWindow& window)
{
	window.draw(_background);

	for (int i = 0; i < _cant; i++)
	{
		window.draw(_btn[i]);
		window.draw(_text[i]);
	}

}

void Menu::setShow(bool show)
{
	_show = show;
}

void Menu::MoveUp()
{

	if (_selectedItemIndex - 1 >= 0)
	{
		_btn[_selectedItemIndex].setFillColor(sf::Color{ 0, 0, 0, 150 });
		_selectedItemIndex--;
		_btn[_selectedItemIndex].setFillColor(sf::Color{ 255, 255, 255, 100 });
	}

}

void Menu::MoveDown()
{

	if (_selectedItemIndex + 1 < _cant)
	{
		_btn[_selectedItemIndex].setFillColor(sf::Color{ 0, 0, 0, 150 });
		_selectedItemIndex++;
		_btn[_selectedItemIndex].setFillColor(sf::Color{ 255, 255, 255, 100 });
	}

}

int Menu::getPressedItem()
{
	return _selectedItemIndex;
}

bool Menu::getContinue()
{
	return _continue;
}

bool Menu::getShow()
{
	return _show;
}

void Menu::initFont()
{
	//Font
	if (!_font.loadFromFile("Font/pixel.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	_description.setFont(_font);
	_description.setString("Grupo 17 - Laboratorio de Computacion II - 2022");
	_description.setCharacterSize(15);
	_description.setPosition(sf::Vector2f(_screen.x / 2 - _description.getLocalBounds().width / 2, 600.f));
}

void Menu::initImages()
{

	if (!_texture_bg.loadFromFile("Menu/bg.png"))
	{
		std::cout << "Error loading texture" << std::endl;
	}

	_background.setTexture(_texture_bg);
	_background.setPosition({ -20, -15 });
}

void Menu::initSound()
{
	_sound = new Sound();
	_sound->GetSoundConfig().setVolume(5.f);
	_sound->playTheme(20.f);
	_sound->play();
}

void Menu::stopSound()
{
	_sound->stop();
}


void Menu::restart()
{
	_cant = 4;
	_selectedItemIndex = 0;
	_continue = true;
	delete [] _text;
	_text = new sf::Text[_cant];
	delete[] _btn;
	_btn = new sf::RectangleShape[_cant];
	addMenu("CONTINUE", 0);
	addMenu("RESTART", 1);
	addMenu("RANKING", 2);
	addMenu("EXIT", 3);
}