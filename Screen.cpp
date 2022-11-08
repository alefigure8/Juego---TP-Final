#include "Screen.h"

Screen::Screen()
{
	_time = 0;
	_time_max = 100.f;
	_showInstuction = false;
	_showScreen = false;
}

Screen::~Screen()
{
}

void Screen::initInstruction()
{
	_showInstuction = true;
	initTexture("Menu/screen instruction.png");
	_screen.setTexture(_texture);
}

void Screen::initIntroLevel(int level)
{
	_showScreen = true;
	std::string textureLevels[3] = { "Menu/dia_1.png","Menu/dia_2.png", "Menu/dia_3.png" };
	initTexture(textureLevels[level]);
	_screen.setTexture(_texture);
}

void Screen::initBadEnding()
{
	_showScreen = true;
	initTexture("Menu/bad_end.png");
	_screen.setTexture(_texture);
}

void Screen::initGoodEnding()
{
	_showScreen = true;
	initTexture("Menu/good_end.png");
	_screen.setTexture(_texture);
}

void Screen::initTexture(std::string texture)
{
	if (!_texture.loadFromFile(texture))
		std::cout << "ERROR::TEXTURE" << std::endl;
}

bool Screen::getShowInstruction()
{
	return	_showInstuction;
}

bool Screen::getShowScreen()
{
	return _showScreen;
}

void Screen::setShow(bool show)
{
	_showInstuction = show;
}

void Screen::update()
{
	updateClock();
	
	if (isReady())
	{
		if (!_showScreen)
		{
			_showInstuction = false;
			//Inicializa la primera pantalla del nivel ni bien termina las instrucciones
			initIntroLevel(0);
		}
		else
		{
			_showScreen = false;
		}
	}
}

void Screen::render(sf::RenderWindow& window)
{
	window.draw(_screen);
}

bool Screen::isReady()
{
	if (_time >= _time_max)
	{
		_time = 0.f;
		return true;
	}

	return false;
}

void Screen::updateClock()
{
	if (_time < _time_max)
		_time += 0.5f;
}