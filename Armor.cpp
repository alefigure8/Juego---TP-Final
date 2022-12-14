#include "Armor.h"


Armor::Armor(std::string image, sf::Vector2u imageCount) : Base(image), _animation(image, imageCount)
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

void Armor::updateAnimation(sf::Vector2u currentImagect)
{
	_animation.setCurrentImage(currentImagect);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.uvRect.width / 2, _animation.uvRect.height / 2);
	_animation.update();
}