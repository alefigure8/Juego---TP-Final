#include "Effect.h"


void Effect::_initTexture(std::string texture)
{
	//Load Texture
	if (!_texture.loadFromFile(texture))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Effect::Effect(std::string texture)
{
	_timeMax = 10.f;
	_time = _timeMax;
	_state = false;
	_initTexture(texture);
	_initSprite();
	_sprite.setScale(0.2f, 0.2f);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top);
}

Effect::~Effect()
{
}

bool Effect::getState()
{
	return _state;
}

float Effect::getRotation()
{
	return _sprite.getRotation();
}

float Effect::getTime()
{
	return _time;
}

float Effect::getTimeMax()
{
	return _timeMax;
}

void Effect::setTime(float time)
{
	_time = time;
}

void Effect::setTimeMax(float timeMax)
{
	_timeMax = timeMax;
}

void Effect::setRotation(float deg)
{
	_sprite.setRotation(deg);
}

void Effect::setState(bool state)
{
	_state = state;
}
