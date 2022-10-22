#include "Gameplay.h"
#include <iostream>
#include<list> 
#include <string>
#include "SFML/Graphics.hpp"

void Gameplay::_initWindow()
{
	_window = new sf::RenderWindow(sf::VideoMode(900, 700), "FORCE TANK", sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);
	_window->setVerticalSyncEnabled(false);
	sf::View view(sf::FloatRect(-20, -15, 900, 700));
	_window->setView(view);
}

void Gameplay::_initPlayer()
{
	_player = new Player("Texture/tank1_body.png", sf::Vector2u(1, 1));
}

Bullet* Gameplay::_initBullet()
{
	float PI = 3.14;
	float degree = _player->getArmor()->getRotationArmor();

	// Angulo de la bala
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion de la bala
	float armorPositionX = _player->getArmor()->getPosition().x + (_player->getArmor()->getBounds().width / 2 * velx);
	float armorPositionY = _player->getArmor()->getPosition().y + (_player->getArmor()->getBounds().height / 2 * vely);

	return new Bullet(armorPositionX, armorPositionY, velx, vely, degree - 180);
}

void Gameplay::_initBlock()
{
	_movable = new Movable("Texture/truck2b_destroyed.png", sf::Vector2u(1, 1));
	_movable->setPosition({ 200, 300 });
	_movable->setScale({ 0.7, 0.7 });
	//_bloque_arbol = new Arbol("Texture/treeGreen_large.png", sf::Vector2u(1, 1));
	//_bloque_arbol->setPosition({ 100, 150 });
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
	_initWindow();
	_initLevel();
	_initPlayer();
	_initBlock();
	_initEffect();
}

Gameplay::~Gameplay()
{
	delete _window;

	delete _player;

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
		_player->move(0.f, -0.4f);
		_player->setRotation(0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_player->move(0.f, 0.4f);
		_player->setRotation(180);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_player->move(-0.4f, 0.f);
		_player->setRotation(-90);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_player->move(0.4f, 0.f);
		_player->setRotation(90);
	}

	// Balas
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
	bool balaBorrada = false;

	for (int j = 0; j < _level->getHeight(); j++) // cada Casa
	{
		for (int h = 0; h < _level->getWidth(); h++)
		{
			for (int i = 0; i < _bullet.size(); i++) //cada Bala
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
					!balaBorrada &&
					_level->getTile(j, h)->getLife() > 0
					) // Colision Edificios
				{
					std::cout << "Disparo" << std::endl;
					delete _bullet.at(i);
					_bullet.erase(_bullet.begin() + i);
					balaBorrada = true;

					_level->getTile(j, h)->setLife(_level->getTile(j, h)->getLife() - 1);
				}
				else if (_bullet[i]->getBounds().intersects(_movable->getBounds()) && !balaBorrada) // Colision con caja
				{
					delete _bullet.at(i);
					_bullet.erase(_bullet.begin() + i);
					balaBorrada = true;

					_movable->setLife(_movable->getLife() - 1);
				}
				else if (_bullet[i]->getBounds().top > _window->getSize().y ||
					_bullet[i]->getBounds().top + _bullet[i]->getBounds().height < 0.f ||
					_bullet[i]->getBounds().left + _bullet[i]->getBounds().width > _window->getSize().x ||
					_bullet[i]->getBounds().left + _bullet[i]->getBounds().width < 0.f ||
					dxy > _bullet[i]->getMaxDistance()
					&& !balaBorrada)
				{
					delete _bullet.at(i);
					_bullet.erase(_bullet.begin() + i);
					balaBorrada = true;
				}

			}
		}
	}
}


//Collider bloque
void Gameplay::updateColliders()
{
	Collider c = _player->getCollider();
	Collider c2 = _movable->getCollider();

	for (int i = 0; i < _level->getHeight(); i++)
	{
		for (int j = 0; j < _level->getWidth(); j++)
		{
			if (_level->getTile(i, j)->getLife() > 0)
			{
				//Si la casa tiene vida, detiene al camion y a nosotros
				_level->getTile(i, j)->getCollider().CheckCollision(c, 1.f);

				if (_level->getTile(i, j)->getCollider().CheckCollision(c2, 1.f))
				{
					_movable->getCollider().CheckCollision(c, 1.f);
				}
				else
				{
					_movable->getCollider().CheckCollision(c, 0.5f);
				}
			}
			else
			{
				//Si la casa no tiene vida, podemos seguir moviendonos y al camion
				_movable->getCollider().CheckCollision(c, 0.5f);
			}
		}
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
	_player->update(*_window);

	//Bloque
	_movable->update();
	//_bloque_arbol->update();

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

	//Bullets
	for (auto* bala : _bullet)
	{
		bala->render(*_window);
	}

	//Efectos
	if (_shoot->getState())
	{
		_shoot->render(*_window);
	}

	//Bloque Arbol
	//_bloque_arbol->render(*_window);

	//Display
	_window->display();
}