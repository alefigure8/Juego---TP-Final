#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Gameplay
{
private:
	sf::RenderWindow* _window;
	void _initWindow();
	
public:
	//Constructor
	Gameplay();
	~Gameplay();

	//Update
	void updatePollevents();
	void update();

	//Render
	void render();

	// run
	void run();
};

