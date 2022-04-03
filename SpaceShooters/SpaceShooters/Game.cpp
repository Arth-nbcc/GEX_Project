#include "Game.h"
#include <fstream>

enum textures { player = 0, laser1, missile1, mainGun1, aura };

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	//this->window->setFramerateLimit(60);
	this->dtMultiplier = 60.f;

	/// init fonts
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	/// init Textures
	this->initTextures();

	//background
	this->worldBackground.setTexture(this->background);

	//score
	this->scoreMultiplier = 1;
	this->score = 0;

	/// init player
	this->players.add(Player(this->textures));

	/// init Enemies (object)


	this->enemySpawnTimerMax = 35.f;
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
	this->textures[aura].loadFromFile("Textures/Aura/green.png");

	sf::Texture temp;

	//enemy
	temp.loadFromFile("Textures/Ships/enemy2.png");
	this->enemyTextures.add(sf::Texture(temp));
	temp.loadFromFile("Textures/Ships/enemy1.png");
	this->enemyTextures.add(sf::Texture(temp));

	//pickup
	temp.loadFromFile("Textures/Guns/health.png");
	this->pickupTextures.add(sf::Texture(temp));
	temp.loadFromFile("Textures/Guns/bullet+.png");
	this->pickupTextures.add(sf::Texture(temp));
	temp.loadFromFile("Textures/Guns/bullet++.png");
	this->pickupTextures.add(sf::Texture(temp));

	//background
	//this->background.loadFromFile("Textures/Background/background1.jpg");

}


void Game::update(const float& dt)
{
	//Keytime update
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f * dt * this->dtMultiplier;

	//Pause Screen
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && this->keyTime >= this->keyTimeMax)
	{
		if (this->paused)
			this->paused = false;
		else
			this->paused = true;

		this->keyTime = 0.f;
	}

	//if (this->paused)
	//{
	//	for (size_t i = 0; i < this->players.size(); i++)
	//	{
	//		if (this->players[i].isAlive())
	//		{
	//			change Aura here	//TO-DO thing
	//		}
	//	}
	//}

	if (this->players.size() > 0 && !this->paused)
	{
		/// update timer
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer += 1.f * dt * this->dtMultiplier;

		/// spawn enemies
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.add(Enemy(
				this->enemyTextures,
				this->window->getSize(), //windowBounds is size of the window
				sf::Vector2f(0.f, 0.f),	 //position
				sf::Vector2f(-1.f, 0.f), //direction
				sf::Vector2f(0.1f, 0.1f), //scale
				rand() % 2,				 //type
				0));					//playerfollowNr

		   /// Reset timer
			this->enemySpawnTimer = 0;
		}

		/// update players, bullets and combat
		for (size_t i = 0; i < this->players.size(); i++)
		{
			if (this->players[i].isAlive())
			{

				/// UPDATE PLAYERS
				this->players[i].Update(this->window->getSize(), dt);


				/// Bullets update
				for (size_t k = 0; k < this->players[i].getBulletsSize(); k++)
				{
					this->players[i].getBullets(k).Update(dt);

					/// Enemy collision check with bullets		
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullets(k).getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							//std::cout << "HIT" << "\n";
							this->players[i].removeBullet(k);


							/// enemy take damage check					
							int damage = this->players[i].getdamage();
							if (this->enemies[j].getHP() > 0)
							{
								this->enemies[j].takeDamage(damage);

								//textTags
								this->textTags.add(
									TextTag(
										&this->font,					//font
										"-" + std::to_string(damage),	//Text
										sf::Color::Red,					//color
										sf::Vector2f(					//position
											this->enemies[j].getPosition().x + 20.f,
											this->enemies[j].getPosition().y - 20.f),
										30, 20.f));						//size & timer
							}

							/// enemy dead						
							if (this->enemies[j].getHP() <= 0)
							{
								//score
								int score = this->enemies[j].getHPMax();
								this->players[i].gainScore(score);

								//add pickups
								int pickupChance = rand() % 10;

								if (pickupChance > 7)
								{
									this->pickups.add(Pickup(
										&this->pickupTextures,	//texture
										this->enemies[j].getPosition(),	//position
										rand() % 3,		//type
										150.f	//duration
									));
								}

								//std::cout << "ERase" << "\n";
								this->enemies.remove(j);
							}
							return;	//RETURN!!!
						}
					}

					/// Window bounds check			
					if (this->players[i].getBullets(k).getPosition().x > this->window->getSize().x)
					{
						this->players[i].removeBullet(k);
						return;	//RETURN!!!
					}
				}
			}
			//Update Score
			this->score = 0;
			this->score += players[i].getScore();
			this->scoreText.setString(
				"Score: " + std::to_string(this->score));
		}

		/// player-enemy collision
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
				{
					if (this->players[k].isAlive())
					{
						int damage = this->enemies[i].getDamage();
						this->players[k].takeDamage(damage);

						//textTags
						this->textTags.add(
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

						this->enemies.remove(i);
						return;
					}
				}
			}

			/// erase enemy when out of window
			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
			{
				this->enemies.remove(i);
				return; //break !!!
			}
		}
		//update TextTags
		for (size_t i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].Update(dt);

			if (this->textTags[i].getTimer() <= 0.f)
			{
				this->textTags.remove(i);
				break;
			}
		}

		//update pickups
		for (size_t i = 0; i < this->pickups.size(); i++)
		{
			this->pickups[i].Update(dt);

			for (size_t k = 0; k < players.size(); k++)
			{
				if (this->pickups[i].checkCollision(this->players[k].getGlobalBounds()))
				{
					switch (this->pickups[i].getType())
					{
					case 0:		//HP
						this->players[k].gainHP(this->players[k].getHpMax() / 5);
						break;

					case 1:		//Missile +
						this->players[k].setGunLevel(1);
						break;

					case 2:		//Missile ++
						this->players[k].setGunLevel(2);
						break;

					default:
						//TO-DO thing HP
						if (this->players[k].getHp() <= 8)
						{
							this->players[k].setGunLevel(0);
						}
						break;
					}

					this->pickups.remove(i);
					break;
				}
				if (this->pickups[i].canDelete())
				{
					this->pickups.remove(i);
					break;
				}
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
			this->players[index].getPosition().y + 15.f);

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

	//background
	this->backgroundDraw();

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

	//pickups
	for (size_t i = 0; i < pickups.size(); i++)
	{
		this->pickups[i].Draw(*window);
	}
	this->DrawUI();

	this->window->display();
}

void Game::backgroundDraw()
{
	this->window->draw(this->worldBackground);
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
	this->gameOverText.setString(
		"GAME OVER!\nScore: " +
		std::to_string(this->score) +
		"\n\nPress ENTER to RESTART");
	this->gameOverText.setPosition(window->getSize().x / static_cast<float>(2) - 150.f, window->getSize().y / static_cast<float>(2));

	//score Text
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(32);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(10.f, 10.f);

	//Control Texts
	this->controlsText.setFont(this->font);
	this->controlsText.setCharacterSize(40);
	this->controlsText.setFillColor(sf::Color::Green);
	this->controlsText.setString(
		"A: LEFT\nD: RIGHT\nW: UP\nS: DOWN\nSPACE: SHOOT\nESC: QUIT");
	this->controlsText.setPosition(40.f, 550.f);
}

void Game::DrawUI()
{
	//Draw TextTags
	for (size_t i = 0; i < textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}

	/// Game Over
	if (this->playersAlive <= 0)
	{
		this->window->draw(this->gameOverText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			for (size_t i = 0; i < this->players.size(); i++)
			{
				this->players[i].Reset();
			}

			this->playersAlive = this->players.size();
			this->score = 0;
			this->enemySpawnTimerMax = 35.f;
			this->scoreTime = 0;
			this->scoreTimer.restart();
			this->enemies.clear();
			this->pickups.clear();
		}
	}

	//Control Text
	if (this->paused)
		this->window->draw(this->controlsText);

	//Score Text
	this->window->draw(this->scoreText);
}





