#include "PowerUp.h"

void PowerUp::initPowerUp()
{
	int random = rand() % 6;
	switch (random)
	{
		case 0:
		{
			//DISTANCE
			if (!_texture.loadFromFile("Texture/pu_distance.png"))
				std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
			_distance = 130;
			_life = 0;
			_damage = 0;
			_speed = 0.f;
			_HP = 0;
			_shield = false;

		}
		break;
		case 1:
		{
			//LIFE
			if (!_texture.loadFromFile("Texture/pu_life.png"))
				std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
			_life = 1;
			_distance = 0;
			_damage = 0;
			_speed = 0.f;
			_HP = 0;
			_shield = false;
		}
		break;
		case 2:
		{
			//DAMAGE
			if (!_texture.loadFromFile("Texture/pu_damage.png"))
				std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
			_damage = 3;
			_distance = 0;
			_life = 0;
			_speed = 0.f;
			_HP = 0;
			_shield = false;
		}
		break;
		case 3:
		{
			//SPEED
			if (!_texture.loadFromFile("Texture/pu_speed.png"))
				std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
			_speed = 0.2f;
			_distance = 0;
			_life = 0;
			_damage = 0;
			_HP = 0;
			_shield = false;
		}
		break;
		case 4:
		{
			//HP
			if (!_texture.loadFromFile("Texture/pu_hp.png"))
				std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
			_HP = 1;
			_distance = 0;
			_life = 0;
			_damage = 0;
			_speed = 0.f;
			_shield = false;
		}
		break;
		case 5:
		{
			//SHIELD
			if (!_texture.loadFromFile("Texture/pu_shield.png"))
				std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
			_shield = true;
			_distance = 0;
			_life = 0;
			_damage = 0;
			_speed = 0.f;
			_HP = 0;
		}
		break;
	}
	
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
}

PowerUp::PowerUp()
{
	_distance = 0;
	_life = 0;
	_damage = 0;
	_speed = 0.f;
	_HP = 0;
	_shield = false;
	_isVisible = false;
	_canDelete = false;

	//init
	initHelper();

	//clock
	_clock_duration->setTime(300.f);
	_clock_spawn->setTime(600.f);
}

PowerUp::~PowerUp()
{
}

float PowerUp::getDistance()
{
	return _distance;
}

int PowerUp::getLife()
{
	return _life;
}

int PowerUp::getDamage()
{
	return _damage;
}

float PowerUp::getSpeed()
{
	return _speed;
}

int PowerUp::getHP()
{
	return _HP;
}

bool PowerUp::getShield()
{
	return _shield;
}

void PowerUp::initHelper()
{
	_clock_duration = new Helper;
	_clock_spawn = new Helper;
}



void PowerUp::update()
{
	updateSpawn();
	updateVisibility();
}

void PowerUp::updateSpawn()
{
	_clock_spawn->updateClock();

	if(_clock_spawn->isReady())
	{
		std::cout << "SPAWN" << std::endl;
		initPowerUp();
		_sprite.setPosition(rand() % 700 + 50, rand() % 500 + 5);
		_sprite.setScale({ 0.5f, 0.5f });
		_isVisible = true;
		_canDelete = false;
	}
}

void PowerUp::updateVisibility()
{
	if (_isVisible && !_canDelete)
	{
		_clock_duration->updateClock();
		if (_clock_duration->isReady())
		{
			std::cout << "DURATION" << std::endl;
			_isVisible = false;
		}
	}

	
}

void PowerUp::render(sf::RenderWindow& window)
{
	if (_isVisible && !_canDelete)
	{
		std::cout << "RENDER" << std::endl;
		window.draw(_sprite);
	}
}

bool PowerUp::isVisible()
{
	return _isVisible;
}

sf::FloatRect PowerUp::getBounds()
{
	return _sprite.getGlobalBounds();
}

void PowerUp::setCanDelete(bool canDelete)
{
	_canDelete = canDelete;
}
