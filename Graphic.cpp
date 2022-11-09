#include "Graphic.h"

void Graphic::initText() {
	if (!_font.loadFromFile("Font/pixel.ttf"))
	{
		std::cout << "ERROR::FONT" << std::endl;
	}

	_text.setFillColor(sf::Color::White);
	_text.setStyle(sf::Text::Bold);
	_text.setCharacterSize(24);
	_text.setFont(_font);

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

void Graphic::update(Player* player, int enemies)
{
	//GUI_point();
	GUI_Player(player);
	GUI_Enemies(enemies);

}

void Graphic::render(sf::RenderWindow& window)
{
	window.draw(_text);
	window.draw(_icon);
}
