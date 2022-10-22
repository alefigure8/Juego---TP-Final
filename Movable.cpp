#include "Movable.h"
Movable::Movable(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion) : Block(image, imageCount) {
	_movement_speed = 5.f;
}


sf::Vector2f Movable::getLastPosition() {
	return _last_position;
}


void Movable::move(float x, float y) {
	_last_position = getPosition();
	getSprite().move(x * _movement_speed, y * _movement_speed);
}