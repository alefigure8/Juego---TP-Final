#include "Animation.h"
Animation::Animation(std::string image, sf::Vector2u imageCount)
{
	_texture.loadFromFile(image);
	this->imageCount = imageCount;
	currentImage.x = 0;

	uvRect.width = _texture.getSize().x / float(imageCount.x);
	uvRect.height = _texture.getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::update()
{
	if (currentImage.x >= imageCount.x)
		currentImage.x = imageCount.x - 1;

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

sf::Vector2u Animation::getCurrentImage()
{
	return currentImage;
}

void Animation::setCurrentImage(sf::Vector2u imageCurrent)
{
	currentImage = imageCurrent;
}