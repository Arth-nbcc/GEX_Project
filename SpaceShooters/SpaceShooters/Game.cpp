#include "Game.h"
#include <fstream>

enum textures { player = 0, laser1, missile1, mainGun1, enemy1 };

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(65);

	/// init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	/// init Textures
	this->initTextures();

	/// init player
	this->players.push_back(Player(this->textures));


	/// init Enemies (object)
	Enemy e1(
		&this->textures[enemy1], //texture
		this->window->getSize(), //windowBound
		sf::Vector2f(-1.f, 0.f), //direction
		sf::Vector2f(0.1f, 0.1f), //scale
		0,			             //type
		3,						 //hpMax
		3, 1);					 //damageMax, damageMin

	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 25.f;
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

	/// init textures regular
	this->textures.push_back(sf::Texture());
	this->textures[player].loadFromFile("Textures/Ships/player.png");

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
		/// update timer
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer++;

		/// spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.push_back(Enemy(
				&this->textures[enemy1],
				this->window->getSize(), //windowBounds is size of the window
				sf::Vector2f(-1.f, 0.f), //direction
				sf::Vector2f(0.1f, 0.1f), //scale
				0,						 //type
				3,						 //hpMax
				3, 1));					 //damageMax & DamageMin


			/// Reset timer
			this->enemySpawnTimer = 0;
		}

		/// update players, bullets and combat
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{

				/// UPDATE PLAYERS
				this->players[i].Update(this->window->getSize());


				/// Bullets update
				for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
				{
					this->players[i].getBullets()[k].Update();

					/// Enemy collision check with bullets		
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							//std::cout << "HIT" << "\n";
							this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);


							/// enemy take damage check					
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

							/// enemy dead						
							if (this->enemies[j].getHP() <= 0)
								//std::cout << "ERase" << "\n";
								this->enemies.erase(this->enemies.begin() + j);

							return;	//RETURN!!!
						}
					}

					/// Window bounds check			
					if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x)
					{
						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
						return;	//RETURN!!!
					}
				}
			}
		}

		/// player-enemy collision
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

			/// erase enemy when out of window
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
			this->players[index].getPosition().y + 25.f);

		this->followPlayerTexts.setString((players[index].getHpAsString()));
	}
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

	/// enemy Draw
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);

		/// UI
		this->UpdateUIEnemy(i);
		this->window->draw(this->enemyText);
	}

	/// Player Draw
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			players[i].Draw(*this->window);
			//UI
			this->UpdateUIPlayer(i); //update for player i

			/// UI Update		
			this->window->draw(this->followPlayerTexts);
		}
	}

	//Draw TextTags
	for (size_t i = 0; i < textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}

	/// Game Over
	if (this->playersAlive <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

void Game::InitUI()
{

	/// follow text init	(player health)
	this->followPlayerTexts.setFont(this->font);
	this->followPlayerTexts.setCharacterSize(14);
	this->followPlayerTexts.setFillColor(sf::Color::White);

	/// enemy (health)
	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(14);
	this->enemyText.setFillColor(sf::Color::White);

	/// game over
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(window->getSize().x / static_cast<float>(2) - 150.f, window->getSize().y / static_cast<float>(2));
}

void Game::DrawUI()
{

}





