#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{
}

void Sound::playExplosion()
{
	if (!_buffer.loadFromFile("Sound/explosion.wav"))
		std::cout << "Gameplay::Error sound" << std::endl;

	play();
}

void Sound::PlayPowerup()
{
	if (!_buffer.loadFromFile("Sound/powerUp.wav"))
		std::cout << "Gameplay::Error sound" << std::endl;

	play();
}

void Sound::playBullet()
{
	if (!_buffer.loadFromFile("Sound/bullet_player.wav"))
		std::cout << "Gameplay::Error sound" << std::endl;
	
	play();
}

void Sound::playeBulletEnemies()
{
	if (!_buffer.loadFromFile("Sound/bullet_tanks.wav"))
		std::cout << "Gameplay::Error sound" << std::endl;

	play();
}

void Sound::playHit()
{
	if (!_buffer.loadFromFile("Sound/hitTank.wav"))
		std::cout << "Gameplay::Error sound" << std::endl;

	play();
}

void Sound::play()
{
	_sound.setBuffer(_buffer);
	_sound.play();
}
