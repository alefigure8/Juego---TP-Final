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
#include "Tree.h"

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
	Helper* _clockEnemy;
	Helper* _distance;

	//efectos
	Effect* _shoot;

	//methods
	sf::Vector2f _last_position_shoot;

	//Test
	Movable* _movable;
	Tree* _tree;
	std::vector<Tree*>  _trees;
	
	//FILE
	int tanks[10] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3};
	sf::Vector2f tree[1] = { {100, 500} };
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
	void updateBlock();
	void updateEnemies();
	void updatePlayer();
	void updatePollevents();
	void update();

	//Render
	void render();

	// run
	void run();
};

