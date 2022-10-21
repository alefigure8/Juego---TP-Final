#include "Base.h"

void Base::_initTexture(std::string image, sf::Vector2u imageCount)
{
	//Load Texture
	if (!_texture.loadFromFile(image))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Base::Base(std::string image, sf::Vector2u imageCount) : _animation(image, imageCount)
{
	_initTexture(image, imageCount);
	_initSprite();
	_life = imageCount.x;
	_max_life = imageCount.x;
}

void Base::_initSprite()
{
	_sprite.setTexture(_texture);
}

sf::FloatRect Base::getBounds()
{
	return _sprite.getGlobalBounds();
}

sf::Sprite& Base::getSprite()
{
	return _sprite;
}

int Base::getLife()
{
	return _life;
}

Collider Base::getCollider()
{
	return Collider(_sprite);
}


sf::Vector2f Base::getPosition()
{
	return _sprite.getPosition();
}

void Base::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Base::setLife(int life)
{
	_life = life;
}

void Base::update()
{
	// Update animacion con la vida que le queda al objeto
	if (_life <= 0)
		_life = 0;
	sf::Vector2u currentImage = _animation.getCurrentImage();
	currentImage.x = _max_life - _life;
	_animation.setCurrentImage(currentImage);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.uvRect.width / 2, _animation.uvRect.height / 2);
	_animation.update();
}

void Base::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}