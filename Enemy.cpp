#include "Enemy.h"

Enemy::Enemy(std::string image, std::string armorTexture, sf::Vector2u imageCount)
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

	//armor config
	_armor->getSprite().setScale(0.7f, -0.7f);

}

Enemy::~Enemy()
{
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

	return new Bullet(armorPositionX, armorPositionY, velx, vely, degree - 180, "Texture/bulletGreen1.png");
	//return new BUllet(helper.amorPosition(_player), helper.vel(degree),degree-180,"Texture/bulletGreen1.png");
}

std::vector<Bullet*>& Enemy::getBullets()
{
	return _bullet;
}

void Enemy::movement()
{
	float player_positionX = _player_position.x;
	float player_positionY = _player_position.y;
	float enemy_positionX = _sprite.getPosition().x;
	float enemy_positionY = _sprite.getPosition().y;
	float nearPlayerX = player_positionX - enemy_positionX;
	float nearPlayerY = player_positionY - enemy_positionY;
	float STOPMOVING = 60;

	int optionCase = 0;
	
	//Si colisiona o el tiempo de movimiento se supera, entonces se mueve
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

	//Si el tanque está a menos de 60 X y 60 Y del player, se detiene.
	if (abs(nearPlayerX) < STOPMOVING && abs(nearPlayerY) < STOPMOVING)
	{
		_direction = 3;
	}


	switch (_direction)
	{
		case 0:
		{
			if (player_positionX > _sprite.getPosition().x)
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

			if (player_positionY > _sprite.getPosition().y)
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
			//TODO MEJORAR LOGICA DEL CASE 2
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
			//Se detiene
			_sprite.move(0.f, 0.f);
		break;
	}


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
	//Variables (PASAR A FUNCION QUE RETORNE UN VECTOR2F)
	float player_positionX = _player_position.x;
	float player_positionY = _player_position.y;
	float enemy_positionX = _sprite.getPosition().x;
	float enemy_positionY = _sprite.getPosition().y;
	float nearPlayerX = player_positionX - enemy_positionX;
	float nearPlayerY = player_positionY - enemy_positionY;

	//Siestá yendo hacia el player
	float armaCenterX = _armor->getPosition().x;
	float armaCenterY = _armor->getPosition().y;
	float atan = atan2(armaCenterX - player_positionX, player_positionY - armaCenterY);
	float deg = (atan / 3.14159265358979323846 * 180) + (atan > 0 ? 0 : 360);
	_armor->setRotation(abs(deg));

	//Si está yendo hacia la base
}

void Enemy::updateBullet()
{
	//Enemy Bulltes
	if (this->canAttack())
	{
		_bullet.push_back(initBullet());
		_last_position_shoot = { this->getArmor()->getPosition().x, this->getArmor()->getPosition().y };
	}
}

void Enemy::updateMovement(sf::Vector2f player_position)
{
	//save player position
	_player_position = player_position;

	movement();
	updateTime();
	updateArmor();
	updateBullet();
}
