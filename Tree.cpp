#include "Tree.h"

Tree::Tree(std::string image, sf::Vector2u imageCount, sf::Vector2f position)
	: Block(image, imageCount)
{
	this->setPosition(position);
	this->setLife(0);
}

Tree::~Tree()
{
}
