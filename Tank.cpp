#include "Tank.h"


void Tank::_initArmor(std::string armorTexture)
{
	_armor = new Armor(armorTexture);
	_armor->setPosition(_sprite.getPosition());
}

Tank::Tank(std::string image, std::string armorTexture, sf::Vector2u imageCount) : _animation(image, imageCount), Base(image)
{
	//Init Armor
	_initArmor(armorTexture);

	//Tank Config
	_sprite.setScale(0.7f, 0.7f);
	
	//Init Variables
	_damage = imageCount.x;
	_max_damage = imageCount.x;
	_movement_speed = 1.0f;
	_attack_max = 5.f;
	_attack = _attack_max;
	_weight = 3;

	//set Life
	_life = 1;
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

int Tank::getLife()
{
	return _life;
}

void Tank::setLife(int life)
{
	_life = life;
	_max_life = _life;
}

void Tank::move(float x, float y)
{
	_last_position = _sprite.getPosition();
	_sprite.move(_movement_speed * x, _movement_speed * y);
	_armor->setPosition({ _sprite.getPosition().x, _sprite.getPosition().y });
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

int Tank::getHP()
{
	return _hp;
}

int Tank::getWeight()
{
	return _weight;
}

int Tank::getDamage()
{
	return _damage;
}

void Tank::setAttackMax(float time)
{
	_attack_max = time;
}

void Tank::setSpeedMovement(float speed)
{
	_movement_speed = speed;
}

void Tank::setHP(int hp)
{
	_hp = hp;
}

void Tank::setWeight(int weight)
{
	_weight = weight;
}

void Tank::setDamage(int damage)
{
	_damage = damage;
	_max_damage = _damage;
	
	//Actualizar vida
	updateLife();
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

void Tank::updateAnimation()
{
	if (_damage <= 0)
		_damage = 0;
	
	sf::Vector2u currentImage = _animation.getCurrentImage();
	currentImage.x = _max_damage - _damage;
	_animation.setCurrentImage(currentImage);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.uvRect.width / 2, _animation.uvRect.height / 2);
	_animation.update();
}

void Tank::update(sf::RenderWindow& window)
{
	updateAnimation();
	_armor->update();
	_armor->setPosition(_sprite.getPosition());
	updateAttack();
}

void Tank::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
	window.draw(_armor->getArmor());
}

void Tank::updateLife() 
{
	if (_damage == 0)
		_life--;
	
	if (_life < 0)
		_life = 0;
}