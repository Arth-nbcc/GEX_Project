#include "Player.h"

unsigned Player::players = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

Player::Player(sf::Texture* texture, sf::Texture* bulletTexture,
	int UP, int DOWN,
	int LEFT, int RIGHT,
	int SHOOT)
	:level(1)
	, exp(0)
	, expNext(100)
	, HP(10)
	, hpMax(10)
	, damage(1)
	, damageMax(2)
	, score(0)
{
	this->texture = texture;
	this->bulletTexture = bulletTexture;

	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.13f, 0.13f);

	this->shootTimerMax = 25;
	this->shootTimer = this->shootTimerMax;
	this->damageTimer = 10;
	this->damageTimerMax = this->damageTimerMax;

	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	this->playerNr = Player::playerNr;
	Player::players++;
}

Player::~Player()
{
}

void Player::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::UP])))
		this->sprite.move(0.f, -10.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::DOWN])))
		this->sprite.move(0.f, 10.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::LEFT])))
		this->sprite.move(-10.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::RIGHT])))
		this->sprite.move(10.f, 0.f);
}

void Player::Combact()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::SHOOT]))
		&& this->shootTimer >= shootTimerMax)
	{
		this->bullets.push_back(
			Bullet(bulletTexture, this->playerCenter,
				sf::Vector2f(1.f, 0.f), 4.f,
				30.f, 0.5f));

		this->shootTimer = 0; //RESET TIMER
	}
}

void Player::Update(sf::Vector2u windowBounds)
{
	//update timers
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer++;

	//update positions
		//player Center
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	this->Movement();
	this->Combact();
}

void Player::Draw(sf::RenderTarget& target)
{
	//ordering in important, bullets draw beforing the player/sprite
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}

	target.draw(this->sprite);
}
