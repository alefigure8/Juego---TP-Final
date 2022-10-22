#include "Armor.h"


Armor::Armor(std::string image) : Base(image)
{
}

sf::Sprite Armor::getArmor()
{
	return _sprite;
}

float Armor::getRotationArmor()
{
	return _sprite.getRotation();
}

sf::Vector2f Armor::getOriginArmor()
{
	return _sprite.getOrigin();
}

void Armor::setRotation(float degree)
{
	_sprite.setRotation(degree);
}

void Armor::move(float x, float y)
{
	_sprite.rotate(x);
}