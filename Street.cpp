#include "Street.h"

Street::Street(std::string image, sf::Vector2u imageCount, sf::Vector2f position)
	: Block(image, imageCount)
{
	this->setPosition(position);
	this->setLife(0);
}

Street::~Street()
{
}
