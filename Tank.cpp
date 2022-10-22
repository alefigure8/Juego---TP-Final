#include "Tank.h"
void Tank::_initTexture(std::string image, sf::Vector2u imageCount)
{
	//Load Texture
	if (!_texture.loadFromFile(image))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Tank::Tank(std::string image, sf::Vector2u imageCount) : _animation(image, imageCount)
{
	//Init Sprite
	_initTexture(image, imageCount);
	_initSprite();
	_sprite.setScale(0.7f, 0.7f);
	_sprite.setPosition(200, 200);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
	_life = imageCount.x;
	_max_life = imageCount.x;
	
	// Iniciar Arma
	_armor = new Armor;
	_armor->setPosition(_sprite.getPosition().x, _sprite.getPosition().y);

	// Propiedades
	_movement_speed = 3.f;
	_attack_max = 5.f;
	_attack = _attack_max;
}

Tank::~Tank()
{

}

sf::Vector2f Tank::getLastPosition()
{
	return _last_position;
}

Armor* Tank::getArmor()
{
	return _armor;
}

void Tank::move(float x, float y)
{
	_last_position = _sprite.getPosition();
	_sprite.move(_movement_speed * x, _movement_speed * y);
	_armor->setPosition(_sprite.getPosition().x, _sprite.getPosition().y);
}

void Tank::setRotation(float degree)
{
	_sprite.setRotation(degree);
}

Collider Tank::getCollider()
{
	return Collider(_sprite);
}

float Tank::getSpeedAttack()
{
	return _speed_attack;
}

float Tank::getSpeedMovement()
{
	return _movement_speed;
}

void Tank::setSpeedAttack(float speed)
{
	_speed_attack = speed;
}

void Tank::setSpeedMovement(float speed)
{
	_movement_speed = speed;
}


void Tank::updateAttack()
{
	if (_attack < _attack_max)
		_attack += _speed_attack;
}

bool Tank::canAttack()
{
	if (_attack >= _attack_max)
	{
		_attack = 0.f;
		return true;
	}

	return false;
}

void Tank::updateArmor(sf::RenderWindow& window)
{
	float armaCenterX = _armor->getPosition().x;
	float armaCenterY = _armor->getPosition().y;
	float mousePosX = sf::Mouse::getPosition(window).x;
	float mousePosY = sf::Mouse::getPosition(window).y;
	float atan = atan2(armaCenterX - mousePosX, mousePosY - armaCenterY);
	float deg = (atan / 3.14159265358979323846 * 180) + (atan > 0 ? 0 : 360);
	_armor->setRotation(abs(deg));
}

void Tank::update(sf::RenderWindow& window)
{
	updateArmor(window);
	_armor->update();
	updateAttack();
}

void Tank::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
	window.draw(_arma->getArma());
}