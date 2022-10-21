#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	sf::IntRect uvRect;
	sf::Texture _texture;
	Animation(std::string image, sf::Vector2u imageCount);
	~Animation();
	void update();
	sf::Vector2u getCurrentImage();
	void setCurrentImage(sf::Vector2u imageCurrent);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
};

