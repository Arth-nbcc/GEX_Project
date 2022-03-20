#include "Enemy.h"
#include "math.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSLOW, FOLLOWSHOOT };

Enemy::Enemy(dArr<sf::Texture>& textures, sf::Vector2u windowBounds,
	sf::Vector2f position, sf::Vector2f direction,
	sf::Vector2f scale,
	int type, int playerFollowNr)
{
	this->dtMultiplier = 60.f;

	this->textures = &textures;
	this->type = type;
	this->sprite.setTexture((*this->textures)[this->type]);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;

	this->direction = direction;

	//position sets to randomly at Y cordinate 
	this->sprite.setPosition(this->windowBounds.x, (rand() % this->windowBounds.y) - this->sprite.getGlobalBounds().height);

	switch (this->type)
	{
	case MOVELEFT:
		this->maxVelocity = rand() % 15 + 7;
		this->hpMax = rand() % 3 + 1;
		this->hp = this->hpMax;
		this->damageMax = 3;
		this->damageMin = 1;
		break;

	case FOLLOW:
		this->maxVelocity = rand() % 10 + 5;
		this->hpMax = 1;
		this->hp = this->hpMax;
		this->damageMax = 1;
		this->damageMin = 1;
		break;
	default:
		this->maxVelocity = rand() % 10 + 5;
		break;
	}


	this->damageTimerMax = 5.f;
	this->damageTimer = 0;

	this->playerFollowNr = playerFollowNr; //when a enemy created it will assigned to player to follow it.
}

Enemy::~Enemy()
{
}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	/// reset 
	this->damageTimer = this->damageTimerMax;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Enemy::Update(const float& dt, sf::Vector2f playerPosition)
{
	sf::Vector2f normalizedDir;

	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.move(
			this->direction.x * this->maxVelocity * dt * this->dtMultiplier,
			this->direction.y * this->maxVelocity * dt * this->dtMultiplier);
		break;

	case FOLLOW:

		if (this->sprite.getPosition().x > playerPosition.x)
		{
			//distance between the player position and enemy position
			direction.x = playerPosition.x - this->sprite.getPosition().x;
			direction.y = playerPosition.y - this->sprite.getPosition().y;
		}
		//from 0 to 1. x part and y part, it gives an amount to move certain point in which direction the its placed
		normalizedDir = normalize(direction, vectorLength(direction));

		if (normalizedDir.y > 0.3)
			normalizedDir.y = 0.3;
		else if (normalizedDir.y < -0.3)
			normalizedDir.y = -0.3;

		if (normalizedDir.x > -0.7)
			normalizedDir.x = -0.7;

		this->sprite.setRotation(atan2(normalizedDir.y, normalizedDir.x) * (180 / 3.141592) + 180);

		//follow the player
		this->sprite.move(
			normalizedDir.x * this->maxVelocity * dt * this->dtMultiplier,
			normalizedDir.y * this->maxVelocity * dt * this->dtMultiplier);
		break;

	default:
		break;
	}

	if (this->damageTimer > 0.f)
	{
		this->damageTimer -= 1.f * dt * dtMultiplier;

		///while hitted, set color red
		this->sprite.setColor(sf::Color::Red);

		/// //if hitted, moves little backwards
		this->sprite.move(7.f * dt * dtMultiplier, 0.f);

	}
	else
		this->sprite.setColor(sf::Color::White);

}

void Enemy::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//draw here

}
