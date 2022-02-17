#include "Game.h"

enum textures { player = 0, laser1, missile1, mainGun1, enemy1 };

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(65);

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

	//init Enemies (object)
	Enemy e1(
		&this->textures[enemy1], this->window->getSize(),
		sf::Vector2f(0.f, 0.f),
		sf::Vector2f(-1.f, 0.f), sf::Vector2f(0.1f, 0.1f),
		0, rand() % 3 + 1, 3, 1);

	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 20;
	this->enemySpawnTimer = this->enemySpawnTimerMax;


	//2nd player
	//this->players.push_back(Player(this->textures,
	//	sf::Keyboard::I, sf::Keyboard::K,
	//	sf::Keyboard::J, sf::Keyboard::L,
	//	sf::Keyboard::RShift));
	this->playersAlive = this->players.size();

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
	if (this->players.size() > 0)
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
		//update players, bullets and combat
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				//UPDATE PLAYERS
				this->players[i].Update(this->window->getSize());

				//Bullets update
				for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
				{
					this->players[i].getBullets()[k].Update();

					//Enemy collision check with bullets
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							//std::cout << "HIT" << "\n";
							this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);

							//enemy take damage check
							if (this->enemies[j].getHP() > 0)
								this->enemies[j].takeDamage(this->players[i].getdamage());

							//enemy dead
							if (this->enemies[j].getHP() <= 0)
								//std::cout << "ERase" << "\n";
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
		}
		//player-enemy collision
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update();

			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
				{
					if (this->players[k].isAlive())
					{
						this->players[k].takeDamage(this->enemies[i].getDamage());

						if (!this->players[k].isAlive())
							this->playersAlive--;

						this->enemies.erase(this->enemies.begin() + i);
						return;
					}
				}
			}

			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
			{
				this->enemies.erase(this->enemies.begin() + i);
				return; //break !!!
			}
		}
	}
}

void Game::UpdateUIPlayer(int index)
{
	if (index >= this->players.size())
		std::cout << "error getting text (UpdateUI)";
	else
	{
		this->followPlayerTexts.setPosition(
			this->players[index].getPosition().x,
			this->players[index].getPosition().y - 20.f);

		this->followPlayerTexts.setString(std::to_string(index)
			+ "	 	" +
			this->players[index].getHpAsString());
	}
	//static enemy text
}

void Game::UpdateUIEnemy(int index)
{
	this->enemyText.setPosition(this->enemies[index].getPosition());
	this->enemyText.setString(
		std::to_string(this->enemies[index].getHP())
		+ "/" +
		std::to_string(this->enemies[index].getHPMax()));

}

void Game::draw()
{
	this->window->clear();

	//enemy
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);
		//UI
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	//player
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			players[i].Draw(*this->window);
			//UI
			this->UpdateUIPlayer(i); //update for player i
			this->window->draw(this->followPlayerTexts); //UI update
		}
	}

	//game over
	if (this->playersAlive <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

void Game::InitUI()
{
	sf::Text tempText;

	//follow text init		
	this->followPlayerTexts.setFont(font);
	this->followPlayerTexts.setCharacterSize(14);
	this->followPlayerTexts.setFillColor(sf::Color::White);

	//static text init (for all players)
	this->staticPlayerTexts.setFont(font);
	this->staticPlayerTexts.setCharacterSize(14);
	this->staticPlayerTexts.setFillColor(sf::Color::White);

	//enemy health
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(sf::Color::White);

	//game over
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(this->window->getSize().x / 2 - 150.f, this->window->getSize().y / 2);
}

void Game::DrawUI()
{

}





