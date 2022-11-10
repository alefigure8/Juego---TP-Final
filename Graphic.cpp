#include "Graphic.h"

void Graphic::initText() {
	if (!_font.loadFromFile("Font/pixel.ttf"))
	{
		std::cout << "ERROR::FONT" << std::endl;
	}

	// Player
	_text.setFillColor(sf::Color::White);
	_text.setStyle(sf::Text::Bold);
	_text.setCharacterSize(24);
	_text.setFont(_font);

	//Points
	_point.setFillColor(sf::Color::White);
	_point.setStyle(sf::Text::Bold);
	_point.setCharacterSize(24);
	_point.setFont(_font);
	
	//Level
	_level.setFillColor(sf::Color::White);
	_level.setStyle(sf::Text::Bold);
	_level.setCharacterSize(24);
	_level.setFont(_font);
	
	if (!_icon_font.loadFromFile("Font/tanks.ttf"))
	{
		std::cout << "ERROR::ICON" << std::endl;
	}

	_icon.setPosition({ 720.f, 0.f});
	_icon.setFillColor(sf::Color::White);
	_icon.setStyle(sf::Text::Bold);
	_icon.setCharacterSize(15);
	_icon.setFont(_icon_font);
}

Graphic::Graphic()
{
	initText();
}

Graphic::~Graphic()
{
}


void Graphic::GUI_Player(Player* player)
{
	// Format speed float
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << player->getSpeedMovement();
	std::string speed_str = stream.str();
	
	_text.setString(
		"Life: " + std::to_string(player->getLife()) + '\n' +
		"Damage: " + std::to_string(player->getDamage()) + '\n' +
		"HP: " + std::to_string(player->getHP()) + '\n' +
		"Speed: " + speed_str  + '\n'
	);
}

void Graphic::GUI_Enemies(int enemies)
{
	std::string enemiesIcons = "";

	for (int i = 0; i < enemies; i++)
	{
		if (i > 0 && i % 2 == 0)
		{
			enemiesIcons += '\n';
		}
		enemiesIcons += "D";
	}

	_icon.setString(enemiesIcons);
}

void Graphic::GUI_Point(int points)
{
	_point.setString("Points: " + std::to_string(points));
	_point.setPosition({ 270.f, 0.f });
}

void Graphic::GUI_Level(int level)
{
	_level.setString("Level: " + std::to_string(level));
	_level.setPosition({ 500.f, 0.f });
}

void Graphic::update(Player* player, int enemies, int points, int level)
{
	GUI_Player(player);
	GUI_Enemies(enemies);
	GUI_Point(points);
	GUI_Level(level);
}

void Graphic::render(sf::RenderWindow& window)
{
	window.draw(_text);
	window.draw(_icon);
	window.draw(_point);
	window.draw(_level);
}
