/*#include "Game.h"*/

/*void Game::initVentana()
{
	this->ventana = new sf::RenderWindow(sf::VideoMode(512, 512), "juego", sf::Style::Close | sf::Style::Titlebar);
	this->ventana->setFramerateLimit(60);
}

void Game::update()
{
	sf::Event e;
	while (this->ventana->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			this->ventana->close();
	}
}

void Game::render()
{
	this->ventana->clear(sf::Color::Green);
	this->ventana->display();
}

Game::Game()
{
	this->initVentana();
}

Game::~Game()
{
}

void Game::run()
{
	while (this->ventana->isOpen()) {
		this->update();
		this->render();
	}
}
*/