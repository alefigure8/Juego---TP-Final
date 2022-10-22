#include "Block.h"

void Block::_initTexture(std::string image, sf::Vector2u imageCount)
{
	//Load Texture
	if (!_texture.loadFromFile(image))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Block::Block(std::string image, sf::Vector2u imageCount) : _animation(image, imageCount)
{
	_initTexture(image, imageCount);
	_initSprite();
	_life = imageCount.x;
	_max_life = imageCount.x;
}

Block::~Block()
{

}

int Block::getLife()
{
	return _life;
}

void Block::setLife(int life)
{
	_life = life;
}

void Block::setAngle(float deg)
{
	_sprite.rotate(deg);
}

void Block::updateAnimation()
{
	if (_life <= 0)
		_life = 0;
	
	sf::Vector2u currentImage = _animation.getCurrentImage();
	currentImage.x = _max_life - _life;
	_animation.setCurrentImage(currentImage);
	_sprite.setTextureRect(_animation.uvRect);
	_sprite.setOrigin(_animation.uvRect.width / 2, _animation.uvRect.height / 2);
	_animation.update();
}

void Block::update()
{
	updateAnimation();
}

void Block::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}