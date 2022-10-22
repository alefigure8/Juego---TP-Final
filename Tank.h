#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"
#include "Armor.h"

class Tank
	: public Base
{
protected:
	Armor* _armor;
	sf::Vector2f _last_position;
	float _movement_speed;
	float _attack;
	float _attack_max;
	float _speed_attack;
	int _hp;

	Animation _animation;
	int _life;
	int _max_life;
	void _initTexture(std::string image, sf::Vector2u imageCount);

public:
	Tank(std::string image, sf::Vector2u imageCount);
	~Tank();
	
	//getter
	sf::Vector2f getLastPosition();
	Armor* getArmor();
	int getLife();
	void setLife(int life);
	float getSpeedAttack();
	float getSpeedMovement();
	int getHP();
	
	//setter
	void setRotation(float degree);
	void setSpeedAttack(float speed);
	void setSpeedMovement(float speed);
	void setHP(int hp);
	
	//methods
	bool canAttack();
	void move(float x, float y);
	Collider getCollider();
	void updateAttack();
	void updateArmor(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};

