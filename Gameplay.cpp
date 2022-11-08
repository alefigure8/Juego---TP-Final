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

void Gameplay::_initGame()
{
	_positionTankVector = 0;
	_tanksDeleted = 0;
	//_points = 0;

	if (_initLevel())
	{
		_initPlayer();
		_initEnemy();
		_initBlock();
		_initEffect();
		_initHelpers();
		_initPowerUp();
		_initSounds();
		_initGraphic();
	}
	else
	{
		_gameOver = true;
	}
}

void Gameplay::_initPowerUp()
{
	_powerUp = new PowerUp;
}

bool Gameplay::_initLevel()
{
	delete _level;

	_level = new Level();

	if (_level->initFile(_levelNumber))
	{
		_initFile();
		return true;
	}

	return false;
}

void Gameplay::_initFile()
{
	if (_fileLevel.loadLevels(_levelNumber))
	{
		//Enemies
		_tanksNumber = _fileLevel.getEnemiesNumber();
		_tanks = new int[_tanksNumber];

		for (int i = 0; i < _tanksNumber; i++)
		{
			_tanks[i] = _fileLevel.getEnemies()[i];
		}
	}

	//Movales


	//Trees
}

void Gameplay::_initPlayer()
{
	_player = new Player("Texture/tank1_body_2.png", "Texture/tank1_gun_2.png", sf::Vector2u(3, 1));

	// Init values
	_player->getSprite().setPosition({ _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().x - 50, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().y - 150 });
	_player->getArmor()->setPosition(_player->getPosition());
	_player->setWeight(1);
	_player->setLife(3);
}

void Gameplay::_initEnemy()
{
	if (_positionTankVector < _tanksNumber)
	{
		switch (_tanks[_positionTankVector])
		{
		case 1:
		{
			//ENEMY 1
			_enemy = new Enemy("Texture/enemy_body1.png", "Texture/tank1b_gun_2.png", "Texture/bullet_tank_1.png", sf::Vector2u(2, 1));

			//Init Position
			_enemy->getArmor()->setPosition(_enemy->getPosition());
			_enemy->setAttackMax(15.f);
			_enemy->setWeight(2);
			_enemy->setSpeedMovement(0.7f);
			_enemy->setHP(2);
			_enemy->setLifePost(3);
			_enemy->setBulletDistance(90.f);

			//Push
			_enemies.push_back(_enemy);
			_positionTankVector++;
		}
		break;
		case 2:
		{
			//ENEMY 2
			_enemy = new Enemy("Texture/enemy_body2.png", "Texture/tank3c_gun_2.png", "Texture/bullet_tank_2.png", sf::Vector2u(2, 1));

			//Init Position
			_enemy->getArmor()->setPosition(_enemy->getPosition());
			_enemy->setAttackMax(20.f);
			_enemy->setSpeedMovement(1.1f);
			_enemy->setWeight(1);
			_enemy->setHP(1);
			_enemy->setLifePost(3);
			_enemy->setBulletDistance(120.f);

			//push
			_enemies.push_back(_enemy);
			_positionTankVector++;

		}
		break;
		case 3:
		{
			//ENEMY 3
			_enemy = new Enemy("Texture/enemy_body3.png", "Texture/tank2b_gun_4.png", "Texture/bullet_tank_3.png", sf::Vector2u(3, 1));

			//Init Position
			_enemy->getArmor()->setPosition(_enemy->getPosition());
			_enemy->setAttackMax(15.f);
			_enemy->setSpeedMovement(0.5f);
			_enemy->setWeight(3);
			_enemy->setHP(3);
			_enemy->setLifePost(3);
			_enemy->setBulletDistance(200.f);

			//Push
			_enemies.push_back(_enemy);
			_positionTankVector++;
		}
		break;
		}
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

	return new Bullet({ armorPositionX, armorPositionY }, { velx, vely }, degree - 180, _bulletDistance, "Texture/bullet_player_1.png");
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


void Gameplay::_initHelpers()
{
	//Reloj de los Enemigos
	_clockEnemy = new Helper;
	_clockEnemy->setTime(100.f);

	//Distancias
	_distance = new Helper;
}

void Gameplay::_initSounds()
{
	_sound = new Sound;
}

void Gameplay::_initGraphic()
{
	_GUI = new Graphic;
}

void Gameplay::_initMenu()
{
	_menu = new Menu(_window->getSize().x, _window->getSize().y);
}

void Gameplay::_initScreen()
{
	_screen = new Screen;
}

void Gameplay::_deleteGame()
{
	delete _player;
	_bullet.clear();
	_enemies.clear();
	delete _shoot;
}

void Gameplay::_restartGame()
{
	_levelNumber = 1;
	_screen->initIntroLevel(_levelNumber - 1);
	_deleteGame();
	_initGame();
}

void Gameplay::_endGame()
{
	_backMenu = false;
	_levelNumber = 1;
	_gameOver = false;
}

void Gameplay::_nextLevel()
{
	_deleteGame();
	_initGame();
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
	_levelNumber = 1;
	_bulletDistance = 120.f;
	_tanksDeleted = 0;
	_gameOver = false;
	_backMenu = false;
	
	//Init functiones
	_initWindow();
	_initMenu();
	_initScreen();
}

Gameplay::~Gameplay()
{
	delete _window;
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

		if (_menu->getShow()) {
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					_menu->MoveUp();
					break;

				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					_menu->MoveDown();
					break;
				case sf::Keyboard::Enter:
				{
					if (_menu->getContinue()) {

						if (_menu->getPressedItem() == 0)
						{
							_menu->setShow(false);
						}
						else if (_menu->getPressedItem() == 1)
						{
							_restartGame();
							_menu->setShow(false);
						}
						else if (_menu->getPressedItem() == 2)
						{
							// hanlde Ranking
						}
						else if (_menu->getPressedItem() == 3)
						{
							_window->close();
						}
					}
					else
					{
						if (_menu->getPressedItem() == 0)
						{
							_menu->setShow(false);
							_screen->initInstruction();
							_initGame();
						}
						else if (_menu->getPressedItem() == 1)
						{
							// hanlde Ranking
							
						}
						else if (_menu->getPressedItem() == 2)
						{
							_window->close();
						}
					}
					_menu->stopSound();
				}
				break;
				}
				break;
			case sf::Event::Closed:
				_window->close();
				break;
			}
		}
		else
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					_menu->setShow(true);
					_menu->restart();
					break;
				}
				break;
			case sf::Event::Closed:
				_window->close();
				break;
			}
		}
	}
}

void Gameplay::updateGUI()
{
	_GUI->update(_player, _tanksNumber -  _tanksDeleted);
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

		// Sonido de disparo
		_sound->playBullet();

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
				float dxy = _distance->distance(_bullet[i]->getPosition(), _last_position_shoot);
				

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

					if (_level->getTile(j, h)->getLife() == 1)
					{
						_sound->playExplosion();
					}
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
						//Sonido
						_sound->playHit();

						// Damage
						_enemies[j]->setDamage(_enemies[j]->getDamage() - _player->getHP());
						
						// Sumar enemigo eliminado
						if (_enemies[j]->getDamage() == 0)
						{
							_tanksDeleted++;
						}
						
						//Borrar enemigo si la vida llega a 0
						if (_enemies[j]->getLife() == 0)
						{
							_enemies[j]->setLifePost(_enemies[j]->getLifePost() - 1);
						}

						//Borrar bala
						delete _bullet.at(i);
						_bullet.erase(_bullet.begin() + i);
						deleteBullet2 = true;
						
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
					float dxyEnemy = _distance->distance(enemy->getBullets()[i]->getPosition(), enemy->getLastPositionShoot());
				
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


						if (_level->getTile(j, h)->getLife() == 1)
						{
							_sound->playExplosion();
						}
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

						//Saca puntos de damage
						_player->setDamage(_player->getDamage() - enemy->getHP() <= 0 ? 0 : _player->getDamage() - enemy->getHP());
						
						//Respawn
						if (_player->getDamage() == 0)
						{
							_player->reset();
							_player->getSprite().setPosition({ _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().x - 50, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().y - 150 });
						}

						//Check Base Life. Si llega a 0, Game Over
					}

					//Si la bala del enemigo golpea a otro enemigo
					for (int j = 0; j < _enemies.size(); j++)
					{
						if (enemy->getBullets()[i]->getBounds().intersects(_enemies[j]->getBounds()) && enemy != _enemies[j] && !deleteBullet2)
						{
							delete enemy->getBullets()[i];
							deleteBullet2 = true;
							enemy->getBullets().erase(enemy->getBullets().begin() + i);
							
							//Borrar enemigo si la vida llega a 0
							if (_enemies[j]->getLife() == 0)
							{
								_enemies[j]->setLifePost(_enemies[j]->getLifePost() - 1);
							}
							
							//Se sacan puntos hasta quedar a 1 punto, pero no se matan entre si
							if (_enemies[j]->getDamage() > 1)
							{
								_enemies[j]->setDamage(_enemies[j]->getDamage() - 1);
							}
						}
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

	for (int i = 0; i < _level->getHeight(); i++)
	{
		for (int j = 0; j < _level->getWidth(); j++)
		{
			if (_level->getTile(i, j)->getLife() > 1)
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

					// Colision entre los mismos enemigos
					for (auto* enemy2 : _enemies)
					{
						if (enemy != enemy2)
						{
							Collider enemyC2 = enemy2->getCollider();
							enemyC.CheckCollision(enemyC2, 1.0f);
						}
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
	
	//ENEMIES
	for (auto* enemy : _enemies)
	{
		Collider enemyC = enemy->getCollider();
		
		enemy->getCollider().CheckCollision(player, 0.8f);
		_player->getCollider().CheckCollision(enemyC, 0.5f);

		for (auto* enemy2 : _enemies)
		{
			if (enemy != enemy2)
			{
				Collider enemyC2 = enemy2->getCollider();
				
				if (enemyC.CheckCollision(enemyC2, 0.9f))
				{
					enemy->setMovementState(true);
					enemy->updateMovement(_player, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition());
				}
			}
		}
	}

	//POWERUPS
	if (_powerUp->isVisible())
	{
		if (_player->getBounds().intersects(_powerUp->getBounds()))
		{
			//Sonido
			_sound->PlayPowerup();

			_powerUp->setCanDelete(true);

			//Daño del palyer
			_player->setDamage(_powerUp->getDamage() == 0 ? _player->getDamage() : _powerUp->getDamage());
			
			//Vida del Player
			_player->setLife(_player->getLife() + _powerUp->getLife() >= 5 ? 5 : _player->getLife() + _powerUp->getLife());
			
			//Fuerza de Player
			_player->setHP(_player->getHP() + _powerUp->getHP() >= 3 ? 3 : _player->getHP() + _powerUp->getHP());

			//Velocidad Player
			_player->setSpeedMovement(_player->getSpeedMovement() + _powerUp->getSpeed() >= 1.4 ? 1.4 : _player->getSpeedMovement() + _powerUp->getSpeed());

			//Distancia de disparo
			_bulletDistance + _powerUp->getDistance() >= 250.f ? 250.f : _powerUp->getDistance() + _bulletDistance;
			
			//Escudo en base
			if (_powerUp->getShield())
			{
				for (int i = 0; i < _level->getHeight(); i++)
				{
					for (int j = 0; j < _level->getWidth(); j++)
					{
						if (_level->getTile(i, j)->getIsShield())
						{
							_level->getTile(i, j)->setLife(3);
						}
							
					}
				}
			}
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

	//Borrar enemigo si llega a post life 0
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->getLifePost() == 0 && _enemies[i]->getCanDelete())
		{
			//Sacar vida a los enemigos cerca
			for (auto* enemy : _enemies)
			{
				float distanciaEnemigo = _distance->distance(_enemies[i]->getPosition(), enemy->getPosition());
				
				if(distanciaEnemigo < 40.f)
				{
					enemy->setDamage(enemy->getDamage() - 2 <=0 ? 1 : enemy->getDamage() - 2);
					
				}
				else if (distanciaEnemigo < 60.f)
				{
					enemy->setDamage(enemy->getDamage() - 1 <= 0 ? 1 : enemy->getDamage() - 1);
				}
			}

			//Sacar vida a player cerca
			float distanciaPlayer = _distance->distance(_enemies[i]->getPosition(), _player->getPosition());
		
			if (distanciaPlayer < 40.f)
			{
				_player->setDamage(_player->getDamage() - 2 <= 0 ? 0 : _player->getDamage() - 2);

				if (_player->getDamage() == 0)
				{
					_player->getSprite().setPosition({ _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().x - 50, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().y - 150 });
				}
			}
			else if (distanciaPlayer < 60.f)
			{
				_player->setDamage(_player->getDamage() - 1 <= 0 ? 0 : _player->getDamage() - 1);

				if (_player->getDamage() == 0)
				{
					_player->getSprite().setPosition({ _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().x - 50, _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getPosition().y - 150 });

				}
			}
			//Borrar enemigo
			delete _enemies.at(i);
			_enemies.erase(_enemies.begin() + i);
		}
	}
}

void Gameplay::updatePlayer()
{
	_player->updateArmor(*_window);
	_player->update(*_window);

	//Si la vida del player es 0 o la vida del puente es 0
	if (_player->getLife() == 0 || _level->getTile(_level->getTargetIndex().x, _level->getTargetIndex().y)->getLife() == 0)
	{
		_screen->initBadEnding();
		_backMenu = true;
		_deleteGame();
	}
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

void Gameplay::updateScreen()
{
	if (_screen->getShowInstruction() || _screen->getShowScreen())
	{
		_screen->update();
	}


	if (!_screen->getShowScreen() && _backMenu)
	{
		_menu->setShow(true);
		_endGame();
	}

}

void Gameplay::updateLevel()
{

	// si matamos a todos los enemigos cambiamos de nivel
	if (_tanksDeleted - _tanksNumber == 0 && !_gameOver)
	{
		_levelNumber++;
		_nextLevel();

		if (!_gameOver)
		{
			_screen->initIntroLevel(_levelNumber - 1);

		}
		else
		{
			//Final bueno por terminar los niveles
			_backMenu = true;
			_screen->initGoodEnding();
		}
	}
}

void Gameplay::update()
{
	updateScreen();
	

	if (!_menu->getShow() && !_screen->getShowInstruction() && !_screen->getShowScreen())
	{
		//Level
		updateLevel();

		if (!_gameOver)
		{
			//Inputs
			updateInput();

			//Efectos
			updateEffect();

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

			//level
			_level->update();

			//Helpers
			_clockEnemy->updateClock();

			//PowerUps
			_powerUp->update();

			//GUI
			updateGUI();
		}
	}
}

void Gameplay::render()
{
	// Clear
	_window->clear();

	if (_menu->getShow())
	{
		// Menu
		_menu->render(*_window);
	}
	else if (_screen->getShowInstruction() || _screen->getShowScreen())
	{
		_screen->render(*_window);
	}
	else if(!_gameOver)
	{
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

		//PowerUps
		_powerUp->render(*_window);

		//GUI
		_GUI->render(*_window);
	}

	//Display
	_window->display();
}