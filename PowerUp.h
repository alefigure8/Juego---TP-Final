#pragma once
#include "SFML/Graphics.hpp"
#include "Helper.h"
#include <iostream>

class PowerUp
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	bool _isVisible;
	bool _canDelete;
	float _distance;
	int _life;
	int _damage;
	float _speed;
	int _HP;
	bool _shield;
	Helper* _clock_spawn;
	Helper* _clock_duration;

public:
	PowerUp();
	~PowerUp();

	float getDistance();
	int getLife();
	int getDamage();
	float getSpeed();
	int getHP();
	bool getShield();
	bool isVisible();
	sf::FloatRect getBounds();

	void setCanDelete(bool canDelete);

	void initHelper();
	void initPowerUp();
	void update();
	void updateSpawn();
	void updateVisibility();
	void render(sf::RenderWindow& window);
};

