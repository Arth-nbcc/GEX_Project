#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSLOW, FOLLOWSHOOT };

Enemy::Enemy(sf::Texture* texture, sf::Vector2u windowBounds,
	sf::Vector2f direction, sf::Vector2f scale,
	int type, int hpMax,
	int damageMax, int damageMin)
{
	this->dtMultiplier = 60.f;

	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;

	this->direction = direction;

	//position sets to randomly at Y cordinate 
	this->sprite.setPosition(this->windowBounds.x, (rand() % this->windowBounds.y) - this->sprite.getGlobalBounds().height);

	this->type = type;

	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->damageMax = damageMax;
	this->damageMin = damageMin;

	this->damageTimerMax = 5.f;
	this->damageTimer = 0;
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

void Enemy::Update(const float& dt)
{
	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.move(
			this->direction.x * 10.f * dt * this->dtMultiplier,
			this->direction.y);
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
