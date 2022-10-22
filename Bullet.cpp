#include "Bullet.h"


Bullet::Bullet(float pos_x, float pos_y, float x, float y, float degree, std::string texture) : Base(texture)
{
	_max_distance = 120.f;
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().top);
	_sprite.setPosition(pos_x, pos_y);
	_sprite.setScale(0.5f, 0.5f);
	_sprite.setRotation(degree);
	_direction.x = x;
	_direction.y = y;
	_movement_speed = 0.05f;
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
	_sprite.move(_movement_speed * _direction);
}
