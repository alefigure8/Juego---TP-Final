#include "Enemy.h"

Enemy::Enemy(std::string image, std::string armorTexture, std::string bullet, sf::Vector2u imageCount)
	: Tank(image, armorTexture, imageCount)
{
	// Default values Enemies
	_movement_state = false;
	_movement_speed = 0.7f;
	_attack_max = 5.f;
	_attack = _attack_max;
	_speed_attack = 0.2f;
	_hp = 1;
	_time_direction = 20.f;
	_max_time_direction = _time_direction;
	_direction = NULL;
	_bulletImage = bullet;
	_bulletDistance = 120.f;

	//armor config
	_armor->getSprite().setScale(0.7f, -0.7f);

	//Buffer Rotation
	_buffer_size = 400;
	_buffer = new int[_buffer_size] {0};
	_buffer_position = 50;
	_buffer_position_aux = 0;

	//effect
	initEffect();

	//helper
	initHelper();
}

Enemy::~Enemy()
{
}

void Enemy::initEffect()
{
	_shoot = new Effect("Texture/shoot_1.png", sf::Vector2u(4, 1));
}

void Enemy::initHelper()
{
	_distance = new Helper;
}

Bullet* Enemy::initBullet()
{
	// Init Enemy BUllet
	float PI = 3.14;
	float degree = this->getArmor()->getRotationArmor();

	// Angulo de la bala
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion de la bala
	float armorPositionX = this->getArmor()->getPosition().x + (this->getArmor()->getBounds().width / 2 * velx);
	float armorPositionY = this->getArmor()->getPosition().y + (this->getArmor()->getBounds().height / 2 * vely);

	return new Bullet({ armorPositionX, armorPositionY }, { velx, vely }, degree - 180, _bulletDistance, _bulletImage);
	//return new BUllet(helper.amorPosition(_player), helper.vel(degree),degree-180,"Texture/bulletGreen1.png"); TODO agregar al helper
}

std::vector<Bullet*>& Enemy::getBullets()
{
	return _bullet;
}

void Enemy::movement()
{
	float distancePlayer = _distance->distance(_player_position, _sprite.getPosition());
	float distanceTarget = _distance->distance(_target_position, _sprite.getPosition());
	float distanceEnemyTarget = _distance->distance(_sprite.getPosition(), _target_position);
	float distanceEnemyPlayer = _distance->distance(_sprite.getPosition(), _player_position);
	
	int optionCase = 0;
	float distance = 50.f;

	//Generar Random direction
	if (_movement_state || canMove())
	{
		_direction = rand() % 3;

		if (_direction == 2)
		{
			optionCase = rand() % 4;
		}

		//Reset variables
		_movement_state = false;
		_time_direction = 0.f;
	}

	// Frenar movimiento
	if (distanceEnemyTarget  <= distance || distanceEnemyPlayer  <= distance)
	{
		_direction = 3;
	}
	
	if (_life >= 1)
	{
		if (distancePlayer < distanceTarget && _player_visibility)
		{
			switch (_direction)
			{
			case 0:
			{
				if (_player_position.x > _sprite.getPosition().x)
				{
					_sprite.move(_movement_speed, 0.f);
					_sprite.setRotation(90);
				}
				else
				{
					_sprite.move(-_movement_speed, 0.f);
					_sprite.setRotation(270);
				}
			}
			break;
			case 1:
			{

				if (_player_position.y > _sprite.getPosition().y)
				{
					_sprite.move(0.f, _movement_speed);
					_sprite.setRotation(180);
				}
				else
				{
					_sprite.move(0.f, -_movement_speed);
					_sprite.setRotation(-180);
				}
			}
			break;
			case 2:
			{
				switch (optionCase)
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
			break;
			case 3:
			{
				_sprite.move(0.f, 0.f);
			}
			break;
			}
		}
		else
		{
			switch (_direction)
			{
			case 0:
			{
				if (_target_position.x > _sprite.getPosition().x)
				{
					_sprite.move(_movement_speed, 0.f);
					_sprite.setRotation(90);
				}
				else
				{
					_sprite.move(-_movement_speed, 0.f);
					_sprite.setRotation(270);
				}
			}
			break;
			case 1:
			{

				if (_target_position.y > _sprite.getPosition().y)
				{
					_sprite.move(0.f, _movement_speed);
					_sprite.setRotation(180);
				}
				else
				{
					_sprite.move(0.f, -_movement_speed);
					_sprite.setRotation(-180);
				}
			}
			break;
			case 2:
			{
				switch (optionCase)
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
			break;
			case 3:
			{
				_sprite.move(0.f, 0.f);
			}
			break;
			}
		}
	}
}

void Enemy::setMovementState(bool state)
{
	_movement_state = state;
}

void Enemy::setBulletDistance(float distance)
{
	_bulletDistance = distance;
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

sf::Vector2f Enemy::getLastPositionShoot()
{
	return _last_position_shoot;
}

bool Enemy::canMove()
{
	if (_time_direction >= _max_time_direction)
	{
		_time_direction = 0.f;
		return true;
	}

	return false;
}

void Enemy::updateTime() 
{
	//Incremente el tiempo para cambio de direccion
	if (_time_direction < _max_time_direction)
		_time_direction += 0.3f;

}

void Enemy::updateArmor()
{
	float distancePlayer = _distance->distance(_player_position, _sprite.getPosition());
	float distanceTarget = _distance->distance(_target_position, _sprite.getPosition());
	
	if (_life >= 1)
	{
		//APUNTA ENEMIGO
		if (distancePlayer < distanceTarget && _player_visibility)
		{
			//armor´s degree
			float deg = _distance->degree(_player_position, _armor->getPosition());

			//Buffer para Delay TODO: Mejorar
			_buffer[_buffer_position] = deg;
			_buffer_position++;

			if (_buffer_position >= _buffer_size)
				_buffer_position = 0;

			_armor->setRotation(abs(_buffer[_buffer_position_aux]));
			_buffer_position_aux++;

			if (_buffer_position_aux >= _buffer_size)
				_buffer_position_aux = 0;

		}
		else //APUNTA BASE
		{
			float deg = _distance->degree(_target_position, _armor->getPosition());

			_buffer[_buffer_position] = deg;
			_buffer_position++;

			if (_buffer_position >= _buffer_size)
				_buffer_position = 0;

			_armor->setRotation(abs(_buffer[_buffer_position_aux]));
			_buffer_position_aux++;

			if (_buffer_position_aux >= _buffer_size)
				_buffer_position_aux = 0;
		}

	}
}

void Enemy::updateBullet()
{
	//Enemy Bulltes
	if (this->canAttack() && _life >=1)
	{
		_bullet.push_back(initBullet());
		_shoot->setState(true);
		_last_position_shoot = { this->getArmor()->getPosition().x, this->getArmor()->getPosition().y };
	}
}

void Enemy::updateEffect()
{
	//Armor position
	sf::Vector2f armorPosition = _distance->armorPosition(_armor->getRotationArmor(), _armor->getBounds(), _armor->getPosition());

	if (_shoot->getState())
	{
		_shoot->setPosition({ armorPosition.x, armorPosition.y });
		_shoot->setRotation(_armor->getRotationArmor());
		_shoot->update();
	}
}

void Enemy::updateMovement(Player *_player, sf::Vector2f target_position)
{
	//save player position
	_player_position = _player->getPosition();
	_player_visibility = _player->getVisibility();
	_target_position = target_position;

	movement();
	updateTime();
	updateArmor();
	updateBullet();
	updateEffect();
}

void Enemy::renderEffect(sf::RenderWindow& window)
{
	if (_shoot->getState())
	{
		_shoot->render(window);
	}
}
