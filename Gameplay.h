#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"
#include "Movable.h"

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
	Player* _player;
	Enemy* _enemy;
	std::vector<Bullet*> _bullet;
	std::vector<Bullet*> _bullet_enemy;
	Effect* _shoot;

	//methods
	sf::Vector2f _last_position_shoot;
	sf::Vector2f _last_position_shoot_enemy;

	//Test
	Movable* _movable;
	
	// Init functions
	void _initWindow();
	void _initPlayer();
	void _initEnemy();
	void _initBlock();
	Bullet* _initBullet();
	Bullet* _initBulletEnemy();
	void _initEffect();
	void _initLevel();
	
public:
	//Constructor
	Gameplay();
	~Gameplay();

	//Update
	void updateColliders();
	void updateInput();
	void updateBullet();
	void updateEffect();
	void updatePollevents();
	void update();

	//Render
	void render();

	// run
	void run();
};

