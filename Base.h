#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Collider.h"
#include "Animation.h"

class Base
{
protected:
	Animation _animation;
	sf::Sprite _sprite;
	sf::Texture _texture;
	int _life;
	int _max_life;
	
	void _initSprite();
	void _initTexture(std::string image, sf::Vector2u imageCount);
public:
	//Constructors
	Base(std::string image, sf::Vector2u imageCount);
	
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
