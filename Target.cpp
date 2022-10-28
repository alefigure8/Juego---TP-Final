#include "Target.h"

Target::Target(std::string image, sf::Vector2u imageCount)
    : Block(image, imageCount)
{
	_is_target = true;
}

Target::~Target()
{
}

