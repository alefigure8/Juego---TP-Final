#include "Player.h"

Player::Player(std::string image, std::string armorTexture, sf::Vector2u imageCount) : Tank(image, armorTexture, imageCount)
{
	// Default values player
	_movement_speed = 1.0f;
	_attack_max = 5.f;
	_attack = _attack_max;
	_speed_attack = 0.2f;
	_hp = 1;

	//armor config
	_armor->getSprite().setScale(0.7f, -0.7f);
}

Player::~Player()
{
}


void Player::updateArmor(sf::RenderWindow& window)
{
	float armaCenterX = _armor->getPosition().x;
	float armaCenterY = _armor->getPosition().y;
	float mousePosX = sf::Mouse::getPosition(window).x;
	float mousePosY = sf::Mouse::getPosition(window).y;
	float atan = atan2(armaCenterX - mousePosX, mousePosY - armaCenterY);
	float deg = (atan / 3.14159265358979323846 * 180) + (atan > 0 ? 0 : 360);
	_armor->setRotation(abs(deg));
}