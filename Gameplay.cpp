#include "Gameplay.h"

void Gameplay::_initWindow()
{
	_window = new sf::RenderWindow(sf::VideoMode(900, 700), "FORCE TANK", sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);
	_window->setVerticalSyncEnabled(false);
	sf::View view(sf::FloatRect(-20, -15, 900, 700));
	_window->setView(view);
}

Gameplay::Gameplay()
{
	_initWindow();
	//_initPlayer();
	//_initBloque();
	//_initEfectos();
}

Gameplay::~Gameplay()
{
	delete _window;

	//delete _player;

	/*for (auto* i : _balas)
	{
		delete i;
	}*/

	//delete _disparo;
}

void Gameplay::updatePollevents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();

	}
}

void Gameplay::update()
{
	//Inputs
	//updateInput();

	//Balas
	//updateBalas();

	//Player
	//_player->update(*_window);

	//Bloque
	//_bloque_caja->update();
	//_bloque_arbol->update();

	//Colliders
	//updateColliders();

	//Efectos
	//updateEfectos();

	//_mapa->update();
}

void Gameplay::render()
{
	// Clear
	_window->clear();

	//Mapa
	//_mapa->render(*_window);

	//Bloque Caja
	//if (_bloque_caja->getLife() > 0) // PROVISORIO. TODO VECTOR CAJAS Y BORRAR OBJETOS
	//{
	//	_bloque_caja->render(*_window);
	//}

	//Player
	//_player->render(*_window);

	//Bullets
	/*for (auto* bala : _balas)
	{
		bala->render(*_window);
	}*/

	//Efectos
	/*if (_disparo->getEstado())
	{
		_disparo->render(*_window);
	}*/

	//Bloque Arbol
	//_bloque_arbol->render(*_window);

	//Display
	_window->display();
}

void Gameplay::run()
{
	// Game Loop
	while (_window->isOpen())
	{
		updatePollevents();
		update();
		render();
	}
}

