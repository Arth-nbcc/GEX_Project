#include "Game.h"
#include <fstream>

enum textures { player = 0, laser1, missile1, mainGun1, enemy1 };

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(65);

	/// <summary>
	/// init fonts
	/// </summary>
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	/// <summary>
	/// init Textures
	/// </summary>
	this->initTextures();

	/// <summary>
	/// init player
	/// </summary>
	this->players.push_back(Player(this->textures));

	/// <summary>
	/// init Enemies (object)
	/// </summary>
	Enemy e1(
		&this->textures[enemy1], this->window->getSize(),
		sf::Vector2f(0.f, 0.f),
		sf::Vector2f(-1.f, 0.f), sf::Vector2f(0.1f, 0.1f),
		rand() % 2, rand() % 3 + 1, 3, 1);

	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 20.f;
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

void Game::initTextures()
{
	/// <summary>
	/// init textures regular
	/// </summary>
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

	//init aura textures

}

void Game::update()
{
	if (this->players.size() > 0)
	{
		/// <summary>
		/// update timer
		/// </summary>
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer++;

		/// <summary>
		/// spawn enemies
		/// </summary>
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.push_back(Enemy(
				&this->textures[enemy1], this->window->getSize(),
				sf::Vector2f(0.f, 0.f),
				sf::Vector2f(-1.f, 0.f), sf::Vector2f(0.1f, 0.1f),
				0, rand() % 3 + 1, 3, 1));

			/// <summary>
			/// Reset timer
			/// </summary>
			this->enemySpawnTimer = 0;
		}
		/// <summary>
		/// update players, bullets and combat
		/// </summary>
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				/// <summary>
				/// UPDATE PLAYERS
				/// </summary>
				this->players[i].Update(this->window->getSize());

				/// <summary>
				/// Bullets update
				/// </summary>
				for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
				{
					this->players[i].getBullets()[k].Update();

					/// <summary>
					/// Enemy collision check with bullets
					/// </summary>
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							//std::cout << "HIT" << "\n";
							this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);

							/// <summary>
							/// enemy take damage check
							/// </summary>
							int damage = this->players[i].getdamage();
							if (this->enemies[j].getHP() > 0)
							{
								this->enemies[j].takeDamage(damage);

								//textTags
								this->textTags.push_back(
									TextTag(
										&this->font,
										"-" + std::to_string(damage),
										sf::Color::Red,
										sf::Vector2f(
											this->enemies[j].getPosition().x + 20.f,
											this->enemies[j].getPosition().y - 20.f),
										30, 20.f));
							}

							/// <summary>
							/// enemy dead
							/// </summary>
							if (this->enemies[j].getHP() <= 0)
								//std::cout << "ERase" << "\n";
								this->enemies.erase(this->enemies.begin() + j);

							return;	//RETURN!!!
						}
					}
					/// <summary>
					/// Window bounds check
					/// </summary>
					if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x)
					{
						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
						return;	//RETURN!!!
					}
				}
			}
		}
		/// <summary>
		/// player-enemy collision
		/// </summary>
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update();

			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
				{
					if (this->players[k].isAlive())
					{
						int damage = this->enemies[i].getDamage();
						this->players[k].takeDamage(damage);

						//textTags
						this->textTags.push_back(
							TextTag(
								&this->font,
								"-" + std::to_string(damage),
								sf::Color::Red,
								sf::Vector2f(
									this->players[k].getPosition().x + 20.f,
									this->players[k].getPosition().y - 20.f),
								30, 20.f));

						//player death
						if (!this->players[k].isAlive())
							this->playersAlive--;

						this->enemies.erase(this->enemies.begin() + i);
						return;
					}
				}
			}
			/// <summary>
			/// erase enemy when out of window
			/// </summary>
			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
			{
				this->enemies.erase(this->enemies.begin() + i);
				return; //break !!!
			}
		}
		//update TextTags
		for (size_t i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].Update();

			if (this->textTags[i].getTimer() <= 0.f)
			{
				this->textTags.erase(this->textTags.begin() + i);
				break;
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

	/// <summary>
	/// enemy Draw
	/// </summary>
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);
		/// <summary>
		/// UI
		/// </summary>
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	/// <summary>
	/// Player Draw
	/// </summary>
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			players[i].Draw(*this->window);
			//UI
			this->UpdateUIPlayer(i); //update for player i
			/// <summary>
			/// UI Update
			/// </summary>
			this->window->draw(this->followPlayerTexts);
		}
	}

	//Draw TextTags
	for (size_t i = 0; i < textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}

	/// <summary>
	/// Game Over
	/// </summary>
	if (this->playersAlive <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

void Game::InitUI()
{
	/// <summary>
	/// follow text init	
	/// </summary>
	this->followPlayerTexts.setFont(font);
	this->followPlayerTexts.setCharacterSize(14);
	this->followPlayerTexts.setFillColor(sf::Color::White);

	/// <summary>
	/// static text init (for all players)
	/// </summary>
	//this->staticPlayerTexts.setFont(font);
	//this->staticPlayerTexts.setCharacterSize(14);
	//this->staticPlayerTexts.setFillColor(sf::Color::White);

	/// <summary>
	/// enemy health
	/// </summary>
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(sf::Color::White);

	/// <summary>
	/// game over
	/// </summary>
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(window->getSize().x / static_cast<float>(2) - 150.f, window->getSize().y / static_cast<float>(2));
}

void Game::DrawUI()
{

}





