#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Base.h"
#include "Animation.h"
#include "Armor.h"
#include "Effect.h"

class Tank
	: public Base
{
protected:
	Armor* _armor;
	Effect* _explotion;
	Effect* _bigger_explotion;
	sf::Texture _armorTexture;
	sf::Vector2f _last_position;
	int _life_post;
	int _weight;
	float _movement_speed;
	float _attack;
	float _attack_max;
	float _speed_attack;
	int _hp;
	bool _alreadyDead;
	bool _canDelete;
	sf::Vector2f _spawn_position[3]{ sf::Vector2f(50.f, 100.f), sf::Vector2f(300.f, 100.f), sf::Vector2f(650.f, 100.f) };

	//Animacion
	Animation _animation;
	int _damage;
	int _max_damage;

	//Init
	void _initArmor(std::string armorTexture, sf::Vector2u imageCount);
	void initEffect();

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
	int getLifePost();
	bool getCanDelete();
	
	//setter
	void setLife(int life);
	void setRotation(float degree);
	void setAttackMax(float speed);
	void setSpeedMovement(float speed);
	void setHP(int hp);
	void setWeight(int weight);
	void setDamage(int damage);
	void setLifePost(int life_post);

	//methods
	bool canAttack();
	void move(float x, float y);
	Collider getCollider();
	void updateAttack();
	void updateAnimation();
	void updateEffect();
	void updateLife();
	void update(sf::RenderWindow& window);
	void renderEffectExplotion(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};

