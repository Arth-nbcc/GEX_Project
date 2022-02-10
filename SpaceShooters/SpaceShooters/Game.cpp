#include "Game.h"

enum textures { player = 0, laser1, missile1, mainGun1, enemy1 };

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

	this->textures.push_back(sf::Texture());
	this->textures[enemy1].loadFromFile("Textures/Ships/enemy1.png");

	//init player
	//1 player
	this->players.push_back(Player(this->textures));

	//init Enemies
	Enemy e1(
		&this->textures[enemy1], this->window->getSize(),
		sf::Vector2f(0.f, 0.f),
		sf::Vector2f(-1.f, 0.f), sf::Vector2f(0.1f, 0.1f),
		0, rand() % 3 + 1, 3, 1);

	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimer = 10;
	this->enemySpawnTimerMax = this->enemySpawnTimerMax;

	//2nd player
	/*this->players.push_back(Player(this->textures,
		sf::Keyboard::I, sf::Keyboard::K,
		sf::Keyboard::J, sf::Keyboard::L,
		sf::Keyboard::RShift));
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
	//update timers
	if (this->enemySpawnTimer < this->enemySpawnTimerMax)
		this->enemySpawnTimer++;

	//spawn enemies
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
	{
		this->enemies.push_back(Enemy(
			&this->textures[enemy1], this->window->getSize(),
			sf::Vector2f(0.f, 0.f),
			sf::Vector2f(-1.f, 0.f), sf::Vector2f(0.1f, 0.1f),
			0, rand() % 3 + 1, 3, 1));

		this->enemySpawnTimer = 0;	//Reset timer
	}

	for (size_t i = 0; i < this->players.size(); i++)
	{
		//UPDATE PLAYERS
		this->players[i].Update(this->window->getSize());

		//Bullets update
		for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
		{
			this->players[i].getBullets()[k].Update();

			//Enemy collision check
			for (size_t j = 0; j < this->enemies.size(); j++)
			{
				if (this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
				{
					std::cout << "HIT" << "\n";
					this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);

					if (this->enemies[j].getHP() > 0)
						this->enemies[j].takeDamage(this->players[i].getdamage());

					if (this->enemies[j].getHP() <= 0)
						std::cout << "ERase" << "\n";
					this->enemies.erase(this->enemies.begin() + j);

					return;	//RETURN!!!
				}
			}
			//Window bounds check
			if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x)
			{
				this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
				return;	//RETURN!!!
			}
		}
	}
	//erase enemy when reaching out to the boundry
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Update();

		if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
		{
			this->enemies.erase(this->enemies.begin() + i);
			break; //break !!!
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

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemyText.setPosition(this->enemies[i].getPosition());
		this->enemyText.setString(
			std::to_string(this->enemies[i].getHP())
			+ "/" +
			std::to_string(this->enemies[i].getHPMax()));

		this->enemies[i].Draw(*this->window);
		this->window->draw(this->enemyText);
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

	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(sf::Color::White);

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




