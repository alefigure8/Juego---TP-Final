#include "Effect.h"


void Effect::_initTexture(std::string texture)
{
	//Load Texture
	if (!_texture.loadFromFile(texture))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

void Effect::_initClock()
{
	_effect_clock = new Helper();
}

Effect::Effect(std::string texture, sf::Vector2u imageCount) : _animation(texture, imageCount)
{
	_initClock();
	_initTexture(texture);
	_initSprite();
	_effect_clock->setTime(1.f);
	_currentImage = 0;
	_currentImageMax = imageCount.x;
	_state = false;
	_sprite.setScale(0.4f, 0.4f);
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

float Effect::getCurrentImage()
{
	return _currentImage;
}

float Effect::getCurrentImageMax()
{
	return _currentImageMax;
}

void Effect::setRotation(float deg)
{
	_sprite.setRotation(deg);
}

void Effect::setCurrentImage(float currentImage)
{
	_currentImage = currentImage;
}

void Effect::setState(bool state)
{
	_state = state;
}

void Effect::update()
{
	_effect_clock->updateClock();
	updateAnimation();
}

void Effect::updateAnimation()
{
	if (_currentImage <= _currentImageMax && _effect_clock->isReady())
	{
		sf::Vector2u currentImage = _animation.getCurrentImage();
		currentImage.x = _currentImage;
		
		_animation.setCurrentImage(currentImage);
		_sprite.setTextureRect(_animation.uvRect);
		_sprite.setOrigin(_animation.uvRect.width / 2, _animation.uvRect.height / 2);
		_animation.update();

		_currentImage++;
	}
		
	if (_currentImage > _currentImageMax)
	{
		_currentImage = 0;
		_state = false;
	}
			
}
//
//void Effect::render(sf::RenderWindow& window)
//{
//
//	if (_state)
//	{
//		window.draw(_sprite);
//	}
//}