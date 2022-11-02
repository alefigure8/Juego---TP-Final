#include "Helper.h"

Helper::Helper()
{
	_time = 0;
	_time_max = _time;
}

Helper::~Helper()
{
}

void Helper::setTime(float time)
{
	_time = time;
	_time_max = _time;
}

float Helper::getTime()
{
	return _time;
}

bool Helper::isReady()
{
	if (_time >= _time_max)
	{
		_time = 0.f;
		return true;
	}

	return false;
}

void Helper::updateClock()
{
	if (_time < _time_max)
		_time += 0.5f;
}

float Helper::distance(sf::Vector2f player, sf::Vector2f enemy)
{
	float player_positionX = player.x;
	float player_positionY = player.y;

	float enemy_positionX = enemy.x;
	float enemy_positionY = enemy.y;

	float nearPlayerX = player_positionX - enemy_positionX;
	float nearPlayerY = player_positionY - enemy_positionY;

	float distancePlayer = sqrt(pow(nearPlayerX, 2) + pow(nearPlayerY, 2));

	return distancePlayer;
}

float Helper::degree(sf::Vector2f target, sf::Vector2f armor)
{
	double pi = 3.14159265358979323846;
	float armaCenterX = armor.x;
	float armaCenterY = armor.y;
	float atan = atan2(armaCenterX - target.x, target.y - armaCenterY);
	float deg = (atan / pi * 180) + (atan > 0 ? 0 : 360);

	return deg;
}

sf::Vector2f Helper::armorPosition(float degree, sf::FloatRect bounds, sf::Vector2f position)
{
	// Manejar tiempo de efecto
	float PI = 3.14;

	// Angulo del arma
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion del arma
	float armaPosicionx = position.x + (bounds.width / 2 * velx);
	float armaPosiciony = position.y + (bounds.height / 2 * vely);

	return sf::Vector2f({ armaPosicionx, armaPosiciony });
}
