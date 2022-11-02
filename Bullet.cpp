#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f direction, float degree, std::string texture) : Base(texture)
{
	_max_distance = 120.f;
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().top);
	_sprite.setPosition(pos.x, pos.y);
	_sprite.setScale(0.5f, 0.5f);
	_sprite.setRotation(degree);
	_direction.x = direction.x;
	_direction.y = direction.y;
	_movement_speed = 0.01f;
}

Bullet::~Bullet()
{
	
}

float Bullet::getMaxDistance()
{
	return _max_distance;
}

void Bullet::setMaxDistance(float distance)
{
	_max_distance = distance;
}

void Bullet::update()
{
	_sprite.move(_direction * _movement_speed);
}
