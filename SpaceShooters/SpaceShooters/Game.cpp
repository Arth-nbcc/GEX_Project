#include "Game.h"

enum textures { player = 0, laser1, missile1, mainGun1 };

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);

	//init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	//init textures
	this->textures.push_back(sf::Texture());
	this->textures[player].loadFromFile("Textures/Ships/ship.png");

	this->textures.push_back(sf::Texture());
	this->textures[laser1].loadFromFile("Textures/Guns/laser1.png");

	this->textures.push_back(sf::Texture());
	this->textures[missile1].loadFromFile("Textures/Guns/missile1.png");

	this->textures.push_back(sf::Texture());
	this->textures[mainGun1].loadFromFile("Textures/Guns/gun1.png");

	//init player
	//1 player
	this->players.push_back(Player(this->textures));

	//2nd player
	/*this->players.push_back(Player(this->textures,
		sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::RShift));
	*/

	this->InitUI();
}

Game::~Game()
{

}

void Game::CombateUpdate()
{
	//window bounds
}

void Game::update()
{
	for (size_t i = 0; i < this->players.size(); i++)
	{
		//Update players
		this->players[i].Update(this->window->getSize());

		//Bullets update
		for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
		{
			this->players[i].getBullets()[k].Update();

			//window bound check, remove bullets
			if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x)
			{
				this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
				break; //break!!!
			}

			//enemy collision check
		}
	}
	//Update UI
	this->UpdateUI();

}

void Game::draw()
{
	this->window->clear();
	for (size_t i = 0; i < this->players.size(); i++)
	{
		players[i].Draw(*this->window);
	}
	this->DrawUI();
	this->window->display();
}

void Game::DrawUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		this->window->draw(this->followPlayerTexts[i]);
	}
	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		this->window->draw(this->staticPlayerTexts[i]);
	}
}

void Game::InitUI()
{
	sf::Text tempText;

	for (size_t i = 0; i < this->players.size(); i++)
	{
		//follow text init		
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		tempText.setFillColor(sf::Color::White);
		tempText.setString(std::to_string(i));

		this->followPlayerTexts.push_back(sf::Text(tempText));

		//static text init (for all players)
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		tempText.setFillColor(sf::Color::White);
		tempText.setString("");

		this->staticPlayerTexts.push_back(sf::Text(tempText));
	}
}

void Game::UpdateUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		this->followPlayerTexts[i].setPosition(this->players[i].getPosition().x, this->players[i].getPosition().y - 15.f);

		this->followPlayerTexts[i].setString(std::to_string(i) + "	 	" + this->players[i].getHpAsString());
	}
	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{

	}
}




