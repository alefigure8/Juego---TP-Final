#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "FileUser.h"

class Screen
{
private:
	sf::Sprite _screen;
	sf::Texture _texture;
	sf::Font _fonts;
	sf::Text _text;
	sf::Text _name;
	sf::Text* _points;
	sf::Text* _names;
	sf::Text* _ranks;
	int _pointsPlayer;
	int _cantRanking;
	std::string _namePlayer;
	FileUser* _fileUser;
	bool _showInstuction;
	bool _showScreen;
	bool _showPoints;
	bool _showEnterName;
	bool _endScreen;
	bool _showIntro;
	float _time;
	float _time_max;
	sf::Vector2f _screenSize;
	
public:
	Screen(sf::Vector2f screen);
	~Screen();
	
	//clock
	bool isReady();
	void updateClock();

	//Screen
	void initInstruction();
	void initIntroLevel(int level);
	void initBadEnding();
	void initGoodEnding();
	void initStory();
	void initPoint();
	void initEnterName(int points);
	void initTexture(std::string texture);
	void initFonts(std::string texture);
	
	//getters & setters
	bool getShowInstruction();
	bool getShowIntro();
	bool getShowScreen();
	bool getShowPoints();
	bool getShowEnterName();
	bool getEndScreen();
	
	void setShowEnterName(bool show);
	void setShowInstruction(bool show);
	void setShowIntro(bool show);
	void setShowPoints(bool show);
	void setShow(bool show);
	void setEndScreen(bool end);
	
	//Methods
	void update();
	void updateInputs(sf::Event _event);
	void render(sf::RenderWindow& window);
	
};

