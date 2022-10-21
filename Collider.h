#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::Sprite& sprite);
	~Collider();
	void Move(float dx, float dy) { _sprite.move(dx, dy); }
	bool CheckCollision(Collider& other, float push);
	sf::Vector2f GetPosition() { return _sprite.getPosition(); }
	sf::Vector2f GetHalfSize() { return { _sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2 }; }

private:
	sf::Sprite& _sprite;
};

