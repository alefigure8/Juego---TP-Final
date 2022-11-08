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
#include "FileLevel.h"
#include "PowerUp.h"
#include "Sound.h"
#include "Graphic.h"
#include "Menu.h"
#include "Screen.h"

class Gameplay
{
private:
	//Variables
	int _levelNumber;
	float _bulletDistance;
	bool _gameOver;
	bool _backMenu;
	//int _points;
	
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
	Sound* _sound;
	Graphic* _GUI;
	Screen* _screen;
	
	//Menu
	Menu* _menu;
	//bool _isMenu;

	//efectos
	Effect* _shoot;

	//methods
	sf::Vector2f _last_position_shoot;

	//Test
	Movable* _movable;
	Tree* _tree;
	std::vector<Tree*>  _trees;
	
	//File Level
	FileLevel _fileLevel;
	int _tanksDeleted;
	int* _tanks;
	int _tanksNumber;
	int _positionTankVector;

	//PowerUp
	PowerUp* _powerUp;

	sf::Vector2f tree[1] = { {100, 500} };
	
	// Init functions
	void _initWindow();
	void _initGame();
	bool _initLevel();
	void _initPowerUp();
	void _initFile();
	void _initPlayer();
	void _initEnemy();
	void _initBlock();
	Bullet* _initBullet();
	void _initEffect();
	void _initHelpers();
	void _initSounds();
	void _initGraphic();
	void _initMenu();
	void _initScreen();

	// delete
	void _deleteGame();

	//restar game
	void _restartGame();
	void _endGame();

	//Next level
	void _nextLevel();
	
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
	void updateGUI();
	void updateScreen();
	void updateLevel();
	void update();

	//Render
	void render();

	// run
	void run();
};

