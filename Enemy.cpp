#include "Enemy.h"

Enemy::Enemy(std::string image, std::string armorTexture, sf::Vector2u imageCount)
	: Tank(image, armorTexture, imageCount)
{
	// Default values Enemies
	_movement_state = false;
	_movement_speed = 1.0f;
	_attack_max = 5.f;
	_attack = _attack_max;
	_speed_attack = 0.2f;
	_hp = 1;
	_time_direction = 5.f;
	_max_time_direction = _time_direction;

	//armor config
	_armor->getSprite().setScale(0.7f, -0.7f);
}

Enemy::~Enemy()
{
}

void Enemy::movement()
{
	std::cout << _movement_state << std::endl;
	
	if (_movement_state)
	{
		_direction = rand() % 4;
	
	}
	switch(_direction)
	{
	case 0:
		_sprite.move(_movement_speed, 0.f);
		_sprite.setRotation(90);
		break;
	case 1:
		_sprite.move(-_movement_speed, 0.f);
		_sprite.setRotation(270);
		break;
	case 2:
		_sprite.move(0.f, _movement_speed);
		_sprite.setRotation(180);
		break;
	case 3:
		_sprite.move(0.f, -_movement_speed);
		_sprite.setRotation(0);
		break;

	}
}

void Enemy::updateMovement()
{
	movement();
}

void Enemy::setMovementState(bool state)
{
	_movement_state = state;
}

bool Enemy::getMovementState()
{
	return _movement_state;
}

void Enemy::setTimeDirection(float time)
{
	_time_direction += time;
}

float Enemy::getTimeDirection()
{
	return _time_direction;
}
