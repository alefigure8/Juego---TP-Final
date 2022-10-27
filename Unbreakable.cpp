#include "Unbreakable.h"

Unbreakable::Unbreakable(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion)
	: Block(image, imageCount)
{
}

Unbreakable::~Unbreakable()
{
}

void Unbreakable::updateLife()
{
	if (_life < 2) //TODO MEJORAR
	{
		_life = 2;
	}
}
