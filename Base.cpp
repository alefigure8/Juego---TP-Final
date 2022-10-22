#include "Base.h"

void Base::_initTexture(std::string texture)
{
	//Load Texture Default
	if (!_texture.loadFromFile(texture))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Base::Base(std::string texture)
{
	_initTexture(texture);
	_initSprite();
}

Base::Base()
{
	_life = 0;
	_max_life = _life;
}

void Base::_initSprite()
{
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
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

}

void Base::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}