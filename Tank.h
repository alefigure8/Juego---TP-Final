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
	sf::Texture _armorTexture;
	sf::Vector2f _last_position;
	int _weight;
	float _movement_speed;
	float _attack;
	float _attack_max;
	float _speed_attack;
	int _hp;
	sf::Vector2f _spawn_position[3]{ sf::Vector2f(50.f, 100.f), sf::Vector2f(300.f, 100.f), sf::Vector2f(650.f, 100.f) };

	//Animacion
	Animation _animation;
	int _damage;
	int _max_damage;

	//Init
	void _initArmor(std::string armorTexture);

public:
	Tank(std::string image, std::string armorTexture, sf::Vector2u imageCount);
	~Tank();
	
	//getter
	sf::Vector2f getLastPosition();
	Armor* getArmor();
	int getLife();
	float getSpeedAttack();
	float getSpeedMovement();
	int getHP();
	int getWeight();
	int getDamage();
	
	//setter
	void setLife(int life);
	void setRotation(float degree);
	void setAttackMax(float speed);
	void setSpeedMovement(float speed);
	void setHP(int hp);
	void setWeight(int weight);
	void setDamage(int damage);
	
	//methods
	bool canAttack();
	void move(float x, float y);
	Collider getCollider();
	void updateAttack();
	void updateAnimation();
	void updateLife();
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};

