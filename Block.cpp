#include "Block.h"


Block::Block(std::string image, sf::Vector2u imageCount) : _animation(image, imageCount), Base(image)
{
	_life = imageCount.x;
	_max_life = imageCount.x;
	_is_target = false;
}

Block::~Block()
{

}

int Block::getLife()
{
	return _life;
}

bool Block::getTarget()
{
	return _is_target;
}

void Block::setLife(int life)
{
	_life = life;
}

void Block::setAngle(float deg)
{
	_sprite.rotate(deg);
}

void Block::setTarget(bool target)
{
	_is_target = target;
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