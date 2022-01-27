#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	window->setFramerateLimit(60);

	//init textures
	playerTexture.loadFromFile("Textures/ship.png");

	//init player
	player = new Player(&this->playerTexture);
}

Game::~Game()
{
	delete player;
}

void Game::update()
{
	player->Update();
}

void Game::draw()
{
	window->clear();
	player->Draw(*window);
	window->display();
}
