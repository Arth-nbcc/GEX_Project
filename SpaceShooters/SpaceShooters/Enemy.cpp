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

}

Enemy::~Enemy()
{
}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
		this->hp = 0;
}

void Enemy::Update()
{
	switch (this->type)
	{
	case 0:
		this->sprite.move(this->direction.x * 10.f, this->direction.y * 10.f);
		break;

	default:
		break;
	}
}

void Enemy::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//draw here

}
