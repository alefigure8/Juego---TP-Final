#include "Enemy.h"

Enemy::Enemy(std::string image, sf::Vector2u imageCount, float speed, float speed_attack, int hp) 
	: Tank(image, imageCount)
{
	_speed_attack = speed_attack;
	_attack_max = _speed_attack;
	_movement_speed = speed;
	_hp = hp;
}

Enemy::~Enemy()
{
}
