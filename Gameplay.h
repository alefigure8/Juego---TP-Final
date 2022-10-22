#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include "Effect.h"
#include "Movable.h"

class Gameplay
{
private:
	sf::RenderWindow* _window;
	Level* _level;
	Player* _player;
	std::vector<Bullet*> _bullet;
	sf::Vector2f _last_position_shoot;
	Effect* _shoot;

	//Test
	Movable* _movable;
	
	// Init functions
	void _initWindow();
	void _initPlayer();
	void _initBlock();
	Bullet* _initBullet();
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

