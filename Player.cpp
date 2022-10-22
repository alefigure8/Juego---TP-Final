#include "Player.h"

Player::Player(std::string image, sf::Vector2u imageCount) : Tank(image, imageCount)
{
	// Default values player
	_movement_speed = 3.f;
	_attack_max = 5.f;
	_attack = _attack_max;
	_speed_attack = 0.2f;
	_hp = 1;
}

Player::~Player()
{
}
