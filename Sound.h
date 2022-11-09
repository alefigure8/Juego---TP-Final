#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Sound
{
private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	
public:
	Sound();
	~Sound();
	sf::Sound GetSoundConfig();
	void playExplosion();
	void PlayPowerup();
	void playBullet();
	void playeBulletEnemies();
	void playHit();
	void playTheme(float volume);
	void buffer(std::string file);
	void stop();
	void play();
};

