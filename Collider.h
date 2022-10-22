#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::Sprite& sprite);
	~Collider();
	void Move(float dx, float dy) { _sprite.move(dx, dy); }
	bool CheckCollision(Collider& other, float push);
	sf::Vector2f GetPosition();
	sf::Vector2f GetHalfSize();

private:
	sf::Sprite& _sprite;
};

