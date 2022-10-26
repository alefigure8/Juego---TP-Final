#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"
#include "Movable.h"
#include "Helper.h"

class Gameplay
{
private:
	//window config
	sf::RenderWindow* _window;
	float _rectWidth;
	float _rectHeight;
	std::string _nameGame;
	
	//objects compose
	Level* _level;
	Enemy* _enemy;
	std::vector<Enemy*> _enemies;
	Player* _player;
	std::vector<Bullet*> _bullet;
	Effect* _shoot;
	Helper* _clockEnemy;

	//methods
	sf::Vector2f _last_position_shoot;

	//Test
	Movable* _movable;
	
	//FILE
	int tanks[10] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3};
	int positionTankVector = 0;
	
	
	// Init functions
	void _initWindow();
	void _initPlayer();
	void _initEnemy();
	void _initBlock();
	Bullet* _initBullet();
	void _initEffect();
	void _initLevel();
	void _initHelpers();
	
public:
	//Constructor
	Gameplay();
	~Gameplay();

	//Update
	void updateColliders();
	void updateInput();
	void updateBullet();
	void updateEffect();
	void updateEnemies();
	void updatePollevents();
	void update();

	//Render
	void render();

	// run
	void run();
};

