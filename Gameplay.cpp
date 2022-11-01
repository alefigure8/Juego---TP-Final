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
	_player = new Player("Texture/tank1_body_2.png", "Texture/tank1_gun_2.png", sf::Vector2u(3, 1));

	// Init Position
	_player->getSprite().setPosition({ _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().x - 50, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().y - 150 });
	_player->getArmor()->setPosition(_player->getPosition());
	_player->setWeight(1);
	_player->setLife(3);
}

void Gameplay::_initEnemy()
{
	//TODO: Definir HP de Tanques
	switch(tanks[positionTankVector])
	{
	case 1:
	{
		//ENEMY 1
		_enemy = new Enemy("Texture/enemy_body1.png", "Texture/tank1b_gun_2.png", "Texture/bullet_tank_1.png", sf::Vector2u(2, 1));
		
		//Init Position
		_enemy->getArmor()->setPosition(_enemy->getPosition());
		_enemy->setAttackMax(15.f);
		_enemy->setWeight(2);
		_enemy->setSpeedMovement(0.8f);
		_enemy->setHP(1);
		
		//Push
		_enemies.push_back(_enemy);
		positionTankVector++;
	}
		break;
	case 2:
	{
		//ENEMY 2
		_enemy = new Enemy("Texture/enemy_body2.png", "Texture/tank3c_gun_2.png", "Texture/bullet_tank_2.png", sf::Vector2u(2, 1));
		
		//Init Position
		_enemy->getArmor()->setPosition(_enemy->getPosition());
		_enemy->setAttackMax(20.f);
		_enemy->setSpeedMovement(1.3f);
		_enemy->setWeight(1);
		_enemy->setHP(2);
		
		//push
		_enemies.push_back(_enemy);
		positionTankVector++;
		
	}
		break;
	case 3:
	{
		//ENEMY 3
		_enemy = new Enemy("Texture/enemy_body3.png", "Texture/tank2b_gun_4.png", "Texture/bullet_tank_3.png", sf::Vector2u(3, 1));

		//Init Position
		_enemy->getArmor()->setPosition(_enemy->getPosition());
		_enemy->setAttackMax(25.f);
		_enemy->setSpeedMovement(0.5f);
		_enemy->setWeight(3);
		_enemy->setHP(3);

		//Push
		_enemies.push_back(_enemy);
		positionTankVector++;
	}
		break;
	}
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

	return new Bullet(armorPositionX, armorPositionY, velx, vely, degree - 180, "Texture/bullet_player_1.png");
	//return new BUllet(helper.amorPosition(_player), helper.vel(degree),degree-180,"Texture/bulletGreen1.png");
}

void Gameplay::_initBlock()
{
	_movable = new Movable("Texture/truck_1.png", sf::Vector2u(2, 1));
	_movable->setPosition({ 200, 300 });
	_movable->setScale({ 0.7, 0.7 });


	for (int i = 0; i < 1; i++)
	{
		_tree = new Tree("Texture/tree_1.png", sf::Vector2u(1, 1));
		_tree->setPosition(tree[i]);
		_trees.push_back(_tree);
	}
}

void Gameplay::_initLevel()
{
	_level = new Level;
}

void Gameplay::_initHelpers()
{
	//Reloj de los Enemigos
	_clockEnemy = new Helper;
	_clockEnemy->setTime(100.f);
}

void Gameplay::_initEffect()
{
	_shoot = new Effect("Texture/shoot_1.png", sf::Vector2u(4, 1));
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
	_initHelpers();
}

Gameplay::~Gameplay()
{
	delete _window;
	delete _player;

	for (auto* i : _bullet)
	{
		delete i;
	}

	for (auto* i : _enemies)
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
					) // Colision bloques
				{
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
				
				//Enemies
				for (int j = 0; j < _enemies.size(); j++)
				{
					if (_bullet[i]->getBounds().intersects(_enemies[j]->getBounds()) && !deleteBullet2)
					{
						delete _bullet.at(i);
						_bullet.erase(_bullet.begin() + i);
						deleteBullet2 = true;

						_enemies[j]->setDamage(_enemies[j]->getDamage() - 1);
						
						//Borrar enemigo si la vida llega a 0
						//if (_enemies[j]->getLife()==0)
						//{
						//	delete _enemies.at(j);
						//	_enemies.erase(_enemies.begin() + j);
						//}
					}
				}
			}

			//Bullet Enemies
			for (auto* enemy : _enemies)
			{
				for (int i = 0; i < enemy->getBullets().size(); i++)
				{
					
					// Movimiento bala
					enemy->getBullets()[i]->update();

					//Distancia de la bala
					float balaXEnemy = enemy->getBullets()[i]->getPosition().x; //Posicion X de la bala
					float balaYEnemy = enemy->getBullets()[i]->getPosition().y; //Posicion Y de la bala
					float distxEnemy = enemy->getLastPositionShoot().x - balaXEnemy;
					float distyEnemy = enemy->getLastPositionShoot().y - balaYEnemy;
					float distx2Enemy = distxEnemy * distxEnemy;
					float disty2Enemy = distyEnemy * distyEnemy;
					float dxy2Enemy = distx2Enemy + disty2Enemy;
					float dxyEnemy = sqrt(dxy2Enemy);
				
					if (
						enemy->getBullets()[i]->getBounds().intersects(_level->getTile(j, h)->getBounds()) &&
						!deleteBullet2 &&
						_level->getTile(j, h)->getLife() > 0
						) // Colision Edificios
					{
						delete enemy->getBullets().at(i);
						enemy->getBullets().erase(enemy->getBullets().begin() + i);
						deleteBullet2 = true;

						_level->getTile(j, h)->setLife(_level->getTile(j, h)->getLife() - enemy->getHP());
					}
					else if (enemy->getBullets()[i]->getBounds().intersects(_movable->getBounds()) && !deleteBullet2) // Colision con caja
					{
						delete enemy->getBullets().at(i);
						enemy->getBullets().erase(enemy->getBullets().begin() + i);
						deleteBullet2 = true;

						_movable->setLife(_movable->getLife() - enemy->getHP());
					}
					else if (enemy->getBullets()[i]->getBounds().top > _window->getSize().y ||
						enemy->getBullets()[i]->getBounds().top + enemy->getBullets()[i]->getBounds().height < 0.f ||
						enemy->getBullets()[i]->getBounds().left + enemy->getBullets()[i]->getBounds().width > _window->getSize().x ||
						enemy->getBullets()[i]->getBounds().left + enemy->getBullets()[i]->getBounds().width < 0.f ||
						dxyEnemy > enemy->getBullets()[i]->getMaxDistance()
						&& !deleteBullet2)
					{
						delete enemy->getBullets().at(i);
						enemy->getBullets().erase(enemy->getBullets().begin() + i);
						deleteBullet2 = true;
					}
					else if (enemy->getBullets()[i]->getBounds().intersects(_player->getBounds()) && !deleteBullet2) // Colision con player
					{
						delete enemy->getBullets().at(i);
						enemy->getBullets().erase(enemy->getBullets().begin() + i);
						deleteBullet2 = true;

						_player->setDamage(_player->getDamage() - 1);//TODO: Logica de Damage y Life
						
						if (_player->getDamage() == 3)
						{
							_player->getSprite().setPosition({ _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().x - 50, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().y - 150 });
						}

						//if Life es 0, Game Over

						//Check Base Life. Si llega a 0, Game Over
					}
				}
			}
		}
	}
}


void Gameplay::updateColliders()
{
	Collider player = _player->getCollider();
	Collider movable = _movable->getCollider();
	//Collider enemy = _enemy->getCollider();

	for (int i = 0; i < _level->getHeight(); i++)
	{
		for (int j = 0; j < _level->getWidth(); j++)
		{
			if (_level->getTile(i, j)->getLife() > 1) //TODO MEJORAR 1 o 0
			{
				_level->getTile(i, j)->getCollider().CheckCollision(player, 1.f);
				
				for (auto* enemy : _enemies)
				{
					Collider enemyC = enemy->getCollider();
					// Cambiar direccion de enemigo si hay colision
					if(_level->getTile(i, j)->getCollider().CheckCollision(enemyC, 1.0f))
					{
						enemy->setMovementState(true);
						enemy->updateMovement( _player, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition());
					}
				}
				
				//Detener movimiento de los elementos movible si la casa tiene vida, sino no frenar
				if (_level->getTile(i, j)->getCollider().CheckCollision(movable, 1.f))
				{
					_movable->getCollider().CheckCollision(player, 1.f);

					for (auto* enemy : _enemies)
					{
						Collider enemyC = enemy->getCollider();
						// Cambiar direccion de enemigo si hay colision
						_movable->getCollider().CheckCollision(enemyC, 1.f);
					}
				}
				else
				{
					_movable->getCollider().CheckCollision(player, 0.5f);
					for (auto* enemy : _enemies)
					{
						Collider enemyC = enemy->getCollider();
						// Cambiar direccion de enemigo si hay colision
						_movable->getCollider().CheckCollision(enemyC, 0.5);
					}
				}
			}
			else
			{
				_movable->getCollider().CheckCollision(player, 0.5f);
				
				for (auto* enemy : _enemies)
				{
					Collider enemyC = enemy->getCollider();
					// Cambiar direccion de enemigo si hay colision
					_movable->getCollider().CheckCollision(enemyC, 0.5f);
				}
			}
		}
	}
	
	for (auto* enemy : _enemies)
	{
		Collider enemyC = enemy->getCollider();
		
		if (_player->getWeight() > enemy->getWeight())
		{

				_player->getCollider().CheckCollision(enemyC, 0.5f);
				// Cambiar direccion de enemigo si hay colision
				_movable->getCollider().CheckCollision(enemyC, 0.1f);

		}
		else
		{
				// Cambiar direccion de enemigo si hay colision
				_movable->getCollider().CheckCollision(enemyC, 0.5f);
				_player->getCollider().CheckCollision(enemyC, 0.1);
		}
	}
}

void Gameplay::updateEffect()
{
	//BALAS PLAYER
	
	// Manejar tiempo de efecto
	float PI = 3.14;
	float degree = _player->getArmor()->getRotationArmor();

	// Angulo del arma
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion del arma
	float armaPosicionx = _player->getArmor()->getPosition().x + (_player->getArmor()->getBounds().width / 2 * velx);
	float armaPosiciony = _player->getArmor()->getPosition().y + (_player->getArmor()->getBounds().height / 2 * vely);

	
	if (_shoot->getState())
	{
		_shoot->setPosition({ armaPosicionx, armaPosiciony });
		_shoot->setRotation(degree);
		_shoot->update();
	}
	
}

void Gameplay::updateEnemies()
{
	int enemiesWithLife = 0;
	
	for (auto* enemy : _enemies)
	{
		if (enemy->getLife() > 0)
		{
			enemiesWithLife++;
		}
	}
		
	if (enemiesWithLife < 2 || (_clockEnemy->isReady() && enemiesWithLife < 3))
	{
		_initEnemy();
	}

	for (auto* enemy : _enemies)
	{
		enemy->updateMovement(_player, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition());
		enemy->update(*_window);
	}
}

void Gameplay::updatePlayer()
{
	_player->updateArmor(*_window);
	_player->update(*_window);
}

void Gameplay::updateBlock()
{
	_movable->update();
	
	//trees
	for (int i = 0; i < _trees.size(); i++)
	{
		_trees[i]->update();
		
		if (_trees[i]->getPosition().x + 10 < _player->getPosition().x ||
			_trees[i]->getPosition().x - 10 > _player->getPosition().x ||
			_trees[i]->getPosition().y + 10 < _player->getPosition().y ||
			_trees[i]->getPosition().y - 10 > _player->getPosition().y)
		{
			_player->setVisibility(true);
		}
		else
		{
			_player->setVisibility(false);
		}
	}
}

void Gameplay::update()
{
	//Inputs
	updateInput();

	//Balas
	updateBullet();

	//Spawn de eneigos
	updateEnemies();

	//player
	updatePlayer();
	
	//Bloque
	updateBlock();

	//Colliders
	updateColliders();

	//Efectos
	updateEffect();

	//level
	_level->update();

	//Helpers
	_clockEnemy->updateClock();
}

void Gameplay::render()
{
	// Clear
	_window->clear();

	//Mapa
	_level->render(*_window);

	//Bloque Caja
	_movable->render(*_window);

	//Player
	_player->render(*_window);

	//trees
	for (auto* tree : _trees)
	{
		tree->render(*_window);
	}

	//Enemy
	// Vector enemigos
	for (auto* enemy : _enemies)
	{
		enemy->render(*_window);
		enemy->renderEffect(*_window);
	}

	//Bullets
	for (auto* bullet : _bullet)
	{
		bullet->render(*_window);
	}

	// Vector enemigos
	for (auto* enemy : _enemies)
	{
		for (auto* bullet : enemy->getBullets())
		{
			bullet->render(*_window);
		}
	}

	//Efectos
	if (_shoot->getState())
	{
		_shoot->render(*_window);
	}

	//Display
	_window->display();
}