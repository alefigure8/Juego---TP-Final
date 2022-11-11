#include "Screen.h"

Screen::Screen(sf::Vector2f screen)
{
	_time = 0;
	_time_max = 100.f;
	_showInstuction = false;
	_showScreen = false;
	_showPoints = false;
	_showEnterName = false;
	_endScreen = false;
	_showIntro;
	_screenSize = screen;
	_fileUser = new FileUser;
	_pointsPlayer = 0;
	_namePlayer = "";
	_cantRanking = 0;
	_points = new sf::Text[10];
	_ranks = new sf::Text[10];
	_names = new sf::Text[10];
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

void Screen::initStory()
{
	_showIntro = true;
	_time_max = 200.f;
	initTexture("Menu/intro.png");
	_screen.setTexture(_texture);
}

void Screen::initPoint()
{
	_showPoints = true;
	int _SHOWRANK = 10;
	_cantRanking = _fileUser->howManyUsers();

	initFonts("Font/pixel.ttf");
	initTexture("Menu/points.png");
	_screen.setTexture(_texture);

	_cantRanking = _fileUser->howManyUsers();
	
	FileUser* users = _fileUser->sortUsers();
	
	for (int i = 0; i < _cantRanking; i++)
	{
		if (i < 8)
		{
			_points[i].setFont(_fonts);
			_ranks[i].setFont(_fonts);
			_names[i].setFont(_fonts);

			_ranks[i].setFillColor(sf::Color::White);
			_points[i].setFillColor(sf::Color::White);
			_names[i].setFillColor(sf::Color::White);

			_ranks[i].setCharacterSize(20);
			_points[i].setCharacterSize(20);
			_names[i].setCharacterSize(20);


			_ranks[i].setString(std::to_string(i + 1));
			_points[i].setString(std::to_string(users[i].getPoints()));
			_names[i].setString(users[i].getName());

			float posY = 250.f + (30.f * i);
			_ranks[i].setPosition({ 150.f, posY });
			_points[i].setPosition({ 335.f, posY });
			_names[i].setPosition({ 535.f, posY });
		}
	}
}

void Screen::initEnterName(int points)
{
	_showEnterName = true;
	_pointsPlayer = points;

	initFonts("Font/pixel.ttf");

	_name.setFont(_fonts);
	_name.setFillColor(sf::Color::Black);
	_name.setCharacterSize(30);
	_name.setLetterSpacing(10.f);

	_text.setFont(_fonts);
	_text.setString("Puntos: " + std::to_string(_pointsPlayer));
	_text.setCharacterSize(30);
	_text.setPosition(sf::Vector2f((_screenSize.x / 2 - _text.getLocalBounds().width / 2), 350.f));

	initTexture("Menu/enter_name.png");
	_screen.setTexture(_texture);
}

void Screen::initTexture(std::string texture)
{
	if (!_texture.loadFromFile(texture))
		std::cout << "ERROR::TEXTURE" << std::endl;
}

void Screen::initFonts(std::string texture)
{
	if (!_fonts.loadFromFile(texture))
		std::cout << "ERROR::TEXTURE" << std::endl;
}

bool Screen::getShowInstruction()
{
	return	_showInstuction;
}

bool Screen::getShowIntro()
{
	return _showIntro;
}

bool Screen::getShowScreen()
{
	return _showScreen;
}

bool Screen::getShowPoints()
{
	return _showPoints;
}

void Screen::setShowPoints(bool show)
{
	_showPoints = show;
}

bool Screen::getShowEnterName()
{
	return _showEnterName;
}

void Screen::setShowEnterName(bool show)
{
	_showEnterName = show;
}

void Screen::setShowInstruction(bool show)
{
	_showInstuction = show;
}

void Screen::setShowIntro(bool show)
{
	_showIntro = show;
}

bool Screen::getEndScreen()
{
	return _endScreen;
}

void Screen::setShow(bool show)
{
	_showInstuction = show;
}

void Screen::setEndScreen(bool end)
{
	_endScreen = end;
}

void Screen::updateInputs(sf::Event _event)
{
	//Delete
	if (_event.type == sf::Event::KeyPressed)
	{
		if (_event.key.code == sf::Keyboard::BackSpace)
		{
			if (_namePlayer.size() > 0)
			{
				_namePlayer.erase();
				_name.setString("");
			}
		}

		if (_event.key.code == sf::Keyboard::Enter)
		{
			//Salvar archivo
			if (_fileUser->saveUser(_namePlayer, _pointsPlayer))
			{
				//Reset name
				_namePlayer.erase();
				_name.setString("");
				
				//false screens
				_showEnterName = false;
				_showPoints = false;
				_endScreen = true;
			}
		}
	}

	//Write
	if (_event.type == sf::Event::TextEntered)
	{
		if (_event.text.unicode < 128)
		{

			if (_namePlayer.size() < 4)
			{
				_namePlayer += static_cast<char>(_event.text.unicode);
				_name.setString(_namePlayer);
			}
			
		}
	}

	_name.setPosition({ _screenSize.x / 2 - _name.getLocalBounds().width / 2, 150.f});
}

void Screen::update()
{
	if (_showScreen || _showIntro)
		updateClock();
	
	if (isReady())
	{
		if (!_showScreen)
		{
			
			_showIntro = false;
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
	_screen.setPosition({ -20, -15 });

	window.draw(_screen);

	if (_showEnterName)
	{
		window.draw(_text);
		window.draw(_name);
	}

	if (_showPoints)
	{
		for (int i = 0; i < _cantRanking; i++)
		{
			window.draw(_points[i]);
			window.draw(_names[i]);
			window.draw(_ranks[i]);
		}
	}
}

bool Screen::isReady()
{
	if (_time >= _time_max)
	{
		_time = 0.f;
		_time_max = 100.f;
		return true;
	}

	return false;
}

void Screen::updateClock()
{
	if (_time < _time_max)
		_time += 0.5f;
}