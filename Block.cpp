#include "Block.h"


Block::Block(std::string image, sf::Vector2u imageCount) : _animation(image, imageCount), Base(image)
{
	_life = imageCount.x;
	_max_life = imageCount.x;
	_is_target = false;
	_alreadyDead = false;
	_haveEffect = false;
	_isShield = false;
}

Block::~Block()
{

}

void Block::initEffect()
{
	_explotion = new Effect("Texture/explotion_1.png", sf::Vector2u(10, 1));
	_explotion->getSprite().setScale({0.3f, 0.3f});
}

int Block::getLife()
{
	return _life;
}

int Block::getMaxLife()
{
	return _max_life;
}

bool Block::getIsShield()
{
	return _isShield;
}

bool Block::getTarget()
{
	return _is_target;
}

bool Block::getHAveEffect()
{
	return _haveEffect;
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

void Block::setHaveEffect(bool haveEffect)
{
	_haveEffect = haveEffect;
	
	if (_haveEffect)
		initEffect();;
}

void Block::setIsShield(bool isShield)
{
	_isShield = isShield;
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

void Block::updateEffect()
{
	if (_haveEffect)
	{
		if (_life <= 1 && !_alreadyDead)
		{
			_explotion->setState(true);
		}
	
		if (_explotion->getState())
		{
			_explotion->setPosition(_sprite.getPosition());
			_explotion->update();
			
			if(_explotion->getCurrentImage()==_explotion->getCurrentImageMax())
				_alreadyDead = true;
		}
	}
}

void Block::update()
{
	updateEffect();
	updateAnimation();
}

void Block::renderEffect(sf::RenderWindow& window)
{
	if (_haveEffect)
	{
		if (_explotion->getState() && !_alreadyDead)
			_explotion->render(window);
	}
}

void Block::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}