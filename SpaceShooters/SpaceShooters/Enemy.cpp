#include "Enemy.h"

enum eTypes { MOVELEFT = 0, FOLLOW, FOLLOWFAST, FOLLOWSLOW, FOLLOWSHOOT, FOLLOWFASTSHOOT };

Enemy::Enemy(sf::Texture* texture, sf::Vector2u windowBounds,
	sf::Vector2f position, sf::Vector2f direction,
	sf::Vector2f scale, int type,
	int hpMax, int damageMax, int damageMin)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;

	this->direction = direction;

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
	/// <summary>
	/// reset 
	/// </summary>
	/// <param name="damage"></param>
	this->damageTimer = this->damageTimerMax;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Enemy::Update()
{
	switch (this->type)
	{
	case MOVELEFT:
		this->sprite.move(this->direction.x * 10.f, this->direction.y * 10.f);
		break;

	default:
		break;
	}

	if (this->damageTimer > 0.f)
	{
		this->damageTimer -= 1.f;
		///
		///while hitted, set color red
		/// 
		this->sprite.setColor(sf::Color::Red);
		/// <summary>
		/// //if hitted, moves little backwards
		/// </summary>
		this->sprite.move(5.f, 0.f);
	}
	else
		this->sprite.setColor(sf::Color::White);

}

void Enemy::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//draw here

}
