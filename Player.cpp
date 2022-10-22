#include "Player.h"

Player::Player(std::string image, std::string armorTexture, sf::Vector2u imageCount) : Tank(image, armorTexture, imageCount)
{
	// Default values player
	_movement_speed = 3.f;
	_attack_max = 5.f;
	_attack = _attack_max;
	_speed_attack = 0.2f;
	_hp = 1;

	//Init armor
	_armor->getSprite().setScale(0.7f, -0.7f);
}

Player::~Player()
{
}
