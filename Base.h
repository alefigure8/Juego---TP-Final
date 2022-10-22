#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Collider.h"


class Base
{
protected:
	sf::Sprite _sprite;
	sf::Texture _texture;
	int _life;
	int _max_life;
	
	void _initSprite();
	void _initTexture(std::string texture);
public:
	Base(std::string texture);
	Base();
	
	//Getters
	int getLife();
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	sf::Sprite& getSprite();
	Collider getCollider();
	
	//Setters
	void setPosition(sf::Vector2f position);
	void setLife(int life);

	//Methods
	void update();
	void render(sf::RenderWindow& window);
};
