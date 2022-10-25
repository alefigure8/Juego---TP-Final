#include "Gameplay.h"
#include <iostream>
#include<list> 
#include <string>
#include "SFML/Graphics.hpp"

void Gameplay::_initWindow()
{
	_window = new sf::RenderWindow(sf::VideoMode(_rectHeight, _rectWidth), _nameGame, sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);
	_window->setVerticalSyncEnabled(false);
	sf::View view(sf::FloatRect(-20, -15, _rectHeight, _rectWidth));
	_window->setView(view);
}

void Gameplay::_initPlayer()
{
	_player = new Player("Texture/tank1_body.png", "Texture/tank1_gun.png", sf::Vector2u(1, 1));

	// Init Position
	_player->getSprite().setPosition({ 200, 200 });
	_player->getArmor()->setPosition(_player->getPosition());
	_player->setWeight(1);
}

void Gameplay::_initEnemy()
{
	_enemy = new Enemy("Texture/tank1b_body.png", "Texture/tank1b_gun.png", sf::Vector2u(1, 1));

	//Init Position
	_enemy->getSprite().setPosition({ 400, 400 });
	_enemy->getArmor()->setPosition(_enemy->getPosition());
	_enemy->setAttackMax(10.f);
	_enemy->setWeight(2);

}

Bullet* Gameplay::_initBullet()
{
	// Init Player BUllet
	float PI = 3.14;
	float degree = _player->getArmor()->getRotationArmor();

	// Angulo de la bala
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion de la bala
	float armorPositionX = _player->getArmor()->getPosition().x + (_player->getArmor()->getBounds().width / 2 * velx);
	float armorPositionY = _player->getArmor()->getPosition().y + (_player->getArmor()->getBounds().height / 2 * vely);

	return new Bullet(armorPositionX, armorPositionY, velx, vely, degree - 180, "Texture/bulletGreen1.png");
	//return new BUllet(helper.amorPosition(_player), helper.vel(degree),degree-180,"Texture/bulletGreen1.png");
}

Bullet* Gameplay::_initBulletEnemy()
{
	// Init Enemy BUllet
	float PI = 3.14;
	float degree = _enemy->getArmor()->getRotationArmor();

	// Angulo de la bala
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion de la bala
	float armorPositionX = _enemy->getArmor()->getPosition().x + (_enemy->getArmor()->getBounds().width / 2 * velx);
	float armorPositionY = _enemy->getArmor()->getPosition().y + (_enemy->getArmor()->getBounds().height / 2 * vely);

	return new Bullet(armorPositionX, armorPositionY, velx, vely, degree - 180, "Texture/bulletGreen1.png");
	//return new BUllet(helper.amorPosition(_player), helper.vel(degree),degree-180,"Texture/bulletGreen1.png");
}

void Gameplay::_initBlock()
{
	_movable = new Movable("Texture/truck2b_destroyed.png", sf::Vector2u(1, 1));
	_movable->setPosition({ 200, 300 });
	_movable->setScale({ 0.7, 0.7 });
}

void Gameplay::_initLevel()
{
	_level = new Level;
}

void Gameplay::_initEffect()
{
	_shoot = new Effect("Texture/shotThin.png");
}

Gameplay::Gameplay()
{
	//Init variables
	_nameGame = "FORCE TANK";
	_rectHeight = 800;
	_rectWidth = 700;

	//Init functiones
	_initWindow();
	_initLevel();
	_initPlayer();
	_initEnemy();
	_initBlock();
	_initEffect();
}

Gameplay::~Gameplay()
{
	delete _window;
	delete _player;
	delete _enemy;

	for (auto* i : _bullet)
	{
		delete i;
	}

	delete _shoot;
}

void Gameplay::run()
{
	// Game Loop
	while (_window->isOpen())
	{
		updatePollevents();
		update();
		render();
	}
}

void Gameplay::updatePollevents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();

	}
}

void Gameplay::updateInput()
{
	//Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_player->move(0.f, -_player->getSpeedMovement());
		_player->setRotation(0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_player->move(0.f, _player->getSpeedMovement());
		_player->setRotation(180);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_player->move(-_player->getSpeedMovement(), 0.f);
		_player->setRotation(-90);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_player->move(_player->getSpeedMovement(), 0.f);
		_player->setRotation(90);
	}

	// Player Bullets
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player->canAttack())
	{
		_bullet.push_back(_initBullet());

		// Posicion desde la que disparo el tanque
		_last_position_shoot = { _player->getArmor()->getPosition().x, _player->getArmor()->getPosition().y };

		//Iniciar efecto
		_shoot->setState(true);
	}
}

void Gameplay::updateBullet()
{
	bool deleteBullet = false;
	bool deleteBullet2 = false;

	for (int j = 0; j < _level->getHeight(); j++) // HEIGHT
	{
		for (int h = 0; h < _level->getWidth(); h++) // WIDTH
		{
			//Bullet Player
			for (int i = 0; i < _bullet.size(); i++) // PLAYER BULLET
			{
				// Movimiento bala
				_bullet[i]->update();

				//Distancia de la bala
				float balaX = _bullet[i]->getPosition().x; //Posicion X de la bala
				float balaY = _bullet[i]->getPosition().y; //Posicion Y de la bala
				float distx = _last_position_shoot.x - balaX;
				float disty = _last_position_shoot.y - balaY;
				float distx2 = distx * distx;
				float disty2 = disty * disty;
				float dxy2 = distx2 + disty2;
				float dxy = sqrt(dxy2);

				if (
					_bullet[i]->getBounds().intersects(_level->getTile(j, h)->getBounds()) &&
					!deleteBullet &&
					_level->getTile(j, h)->getLife() > 0
					) // Colision Edificios
				{
					std::cout << "Disparo" << std::endl;
					delete _bullet.at(i);
					_bullet.erase(_bullet.begin() + i);
					deleteBullet = true;

					_level->getTile(j, h)->setLife(_level->getTile(j, h)->getLife() - 1);
				}
				else if (_bullet[i]->getBounds().intersects(_movable->getBounds()) && !deleteBullet) // Colision con caja
				{
					delete _bullet.at(i);
					_bullet.erase(_bullet.begin() + i);
					deleteBullet = true;

					_movable->setLife(_movable->getLife() - 1);
				}
				else if (_bullet[i]->getBounds().top > _window->getSize().y ||
					_bullet[i]->getBounds().top + _bullet[i]->getBounds().height < 0.f ||
					_bullet[i]->getBounds().left + _bullet[i]->getBounds().width > _window->getSize().x ||
					_bullet[i]->getBounds().left + _bullet[i]->getBounds().width < 0.f ||
					dxy > _bullet[i]->getMaxDistance()
					&& !deleteBullet)
				{
					delete _bullet.at(i);
					_bullet.erase(_bullet.begin() + i);
					deleteBullet = true;
				}
			}

			//Bullet Enemy
			for (int i = 0; i < _bullet_enemy.size(); i++) // PLAYER BULLET
			{
				// Movimiento bala
				_bullet_enemy[i]->update();

				//Distancia de la bala
				float balaXEnemy = _bullet_enemy[i]->getPosition().x; //Posicion X de la bala
				float balaYEnemy = _bullet_enemy[i]->getPosition().y; //Posicion Y de la bala
				float distxEnemy = _last_position_shoot_enemy.x - balaXEnemy;
				float distyEnemy = _last_position_shoot_enemy.y - balaYEnemy;
				float distx2Enemy = distxEnemy * distxEnemy;
				float disty2Enemy = distyEnemy * distyEnemy;
				float dxy2Enemy = distx2Enemy + disty2Enemy;
				float dxyEnemy = sqrt(dxy2Enemy);

				if (
					_bullet_enemy[i]->getBounds().intersects(_level->getTile(j, h)->getBounds()) &&
					!deleteBullet2 &&
					_level->getTile(j, h)->getLife() > 0
					) // Colision Edificios
				{
					std::cout << "Disparo" << std::endl;
					delete _bullet_enemy.at(i);
					_bullet_enemy.erase(_bullet_enemy.begin() + i);
					deleteBullet2 = true;

					_level->getTile(j, h)->setLife(_level->getTile(j, h)->getLife() - 1);
				}
				else if (_bullet_enemy[i]->getBounds().intersects(_movable->getBounds()) && !deleteBullet2) // Colision con caja
				{
					delete _bullet_enemy.at(i);
					_bullet_enemy.erase(_bullet_enemy.begin() + i);
					deleteBullet2 = true;

					_movable->setLife(_movable->getLife() - 1);
				}
				else if (_bullet_enemy[i]->getBounds().top > _window->getSize().y ||
					_bullet_enemy[i]->getBounds().top + _bullet_enemy[i]->getBounds().height < 0.f ||
					_bullet_enemy[i]->getBounds().left + _bullet_enemy[i]->getBounds().width > _window->getSize().x ||
					_bullet_enemy[i]->getBounds().left + _bullet_enemy[i]->getBounds().width < 0.f ||
					dxyEnemy > _bullet_enemy[i]->getMaxDistance()
					&& !deleteBullet2)
				{
					delete _bullet_enemy.at(i);
					_bullet_enemy.erase(_bullet_enemy.begin() + i);
					deleteBullet2 = true;
				}
				
			}
		}
	}

	//Enemy Bulltes
	if (_enemy->canAttack())
	{
		_bullet_enemy.push_back(_initBulletEnemy());
		_last_position_shoot_enemy = { _enemy->getArmor()->getPosition().x, _enemy->getArmor()->getPosition().y };
	}
}


void Gameplay::updateColliders()
{
	Collider player = _player->getCollider();
	Collider movable = _movable->getCollider();
	Collider enemy = _enemy->getCollider();

	for (int i = 0; i < _level->getHeight(); i++)
	{
		for (int j = 0; j < _level->getWidth(); j++)
		{
			if (_level->getTile(i, j)->getLife() > 0)
			{
				_level->getTile(i, j)->getCollider().CheckCollision(player, 1.f);
				
				// Cambiar direccion de enemigo si hay colision
				if(_level->getTile(i, j)->getCollider().CheckCollision(enemy, 1.0f))
				{
					_enemy->setMovementState(true);
					_enemy->updateMovement(_player->getPosition());
				}
				
				//Detener movimiento de los elementos movible si la casa tiene vida, sino no frenar
				if (_level->getTile(i, j)->getCollider().CheckCollision(movable, 1.f))
				{
					_movable->getCollider().CheckCollision(player, 1.f);
					_movable->getCollider().CheckCollision(enemy, 1.f);
				}
				else
				{
					_movable->getCollider().CheckCollision(player, 0.5f);
					_movable->getCollider().CheckCollision(enemy, 0.5f);
				}
			}
			else
			{
				_movable->getCollider().CheckCollision(player, 0.5f);
				_movable->getCollider().CheckCollision(enemy, 0.5f);
			}
		}
	}
	
	// Colision de Player y Enemigo
	if (_player->getWeight() > _enemy->getWeight())
	{
		_player->getCollider().CheckCollision(enemy, 0.5f);
		_enemy->getCollider().CheckCollision(player, 0.1);
	}
	else
	{
		_enemy->getCollider().CheckCollision(player, 0.5f);
		_player->getCollider().CheckCollision(enemy, 0.1);
	}

}

void Gameplay::updateEffect()
{
	// Manejar tiempo de efecto
	float _time_shoot = _shoot->getTime();

	if (_shoot->getTime() < _shoot->getTimeMax())
	{
		_time_shoot += 1.f;
		_shoot->setTime(_time_shoot);
	}

	if (_shoot->getTime() >= _shoot->getTimeMax())
	{
		_shoot->setTime(0.f);
		_shoot->setState(false);
	}

	float PI = 3.14;
	float degree = _player->getArmor()->getRotationArmor();

	// Angulo del arma
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion del arma
	float armaPosicionx = _player->getArmor()->getPosition().x + (_player->getArmor()->getBounds().width / 2 * velx);
	float armaPosiciony = _player->getArmor()->getPosition().y + (_player->getArmor()->getBounds().height / 2 * vely);

	_shoot->setPosition({ armaPosicionx, armaPosiciony });
	_shoot->setRotation(degree);
}

void Gameplay::update()
{
	//Inputs
	updateInput();

	//Balas
	updateBullet();

	//Player
	_player->updateArmor(*_window);
	_player->update(*_window);

	//Enemy
	_enemy->updateMovement(_player->getPosition());
	_enemy->update(*_window);
	
	//Bloque
	_movable->update();

	//Colliders
	updateColliders();

	//Efectos
	updateEffect();

	_level->update();
}

void Gameplay::render()
{
	// Clear
	_window->clear();

	//Mapa
	_level->render(*_window);

	//Bloque Caja
	if (_movable->getLife() > 0) // PROVISORIO. TODO VECTOR CAJAS Y BORRAR OBJETOS
	{
		_movable->render(*_window);
	}

	//Player
	_player->render(*_window);

	//Enemy
	_enemy->render(*_window);

	//Bullets
	for (auto* bullet : _bullet)
	{
		bullet->render(*_window);
	}

	for (auto* bulletEnemy : _bullet_enemy)
	{
		bulletEnemy->render(*_window);
	}

	//Efectos
	if (_shoot->getState())
	{
		_shoot->render(*_window);
	}

	//Display
	_window->display();
}