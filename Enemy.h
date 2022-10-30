#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tank.h"
#include "Bullet.h"
#include <time.h>
#include "Helper.h"
#include "Player.h"
#include "Target.h"

class Enemy
	: public Tank
{
private:
	std::vector<Bullet*> _bullet;
	std::string _bulletImage;
	bool _movement_state;
	int _direction;
	float _time_direction;
	float _max_time_direction;
	sf::Vector2f _player_position;
	sf::Vector2f _target_position;
	bool _player_visibility;
	sf::Vector2f _last_position_shoot;

	//Buffer
	int* _buffer;
	int _buffer_size;
	int _buffer_position;
	int _buffer_position_aux;
	
public:
	Enemy(std::string image, std::string armorTexture, std::string bullet, sf::Vector2u imageCount);
	~Enemy();

	Bullet* initBullet();
	std::vector<Bullet*>& getBullets();
	
	//getters
	bool getMovementState();
	float getTimeDirection();
	sf::Vector2f getLastPositionShoot();


	//setters
	void setTimeDirection(float time);
	void setMovementState(bool state);
	
	//Methods
	void movement();
	bool canMove();

	//updates
	void updateTime();
	void updateArmor();
	void updateBullet();
	void updateMovement(Player *_player, sf::Vector2f target_position);
	
};

