#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{
}

sf::Sound Sound::GetSoundConfig() {
	return _sound;
}

void Sound::playExplosion()
{
	buffer("Sound/explosion.wav");
	play();
}

void Sound::PlayPowerup()
{
	buffer("Sound/powerUp.wav");
	play();
}

void Sound::playBullet()
{
	buffer("Sound/bullet_player.wav");
	play();
}

void Sound::playeBulletEnemies()
{
	buffer("Sound/bullet_tanks.wav");
	play();
}

void Sound::playHit()
{
	buffer("Sound/hitTank.wav");
	play();
}

void Sound::playTheme(float volume)
{
	buffer("Sound/theme.wav");
	_sound.setVolume(volume);
	play();
}

void Sound::stop()
{
	_sound.stop();
}

void Sound::buffer(std::string file)
{
	if (!_buffer.loadFromFile(file))
		std::cout << "Gameplay::Error sound" << std::endl;
}

void Sound::play()
{
	_sound.setBuffer(_buffer);
	_sound.play();
}
