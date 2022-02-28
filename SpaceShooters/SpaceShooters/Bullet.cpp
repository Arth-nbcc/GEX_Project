#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture,
	sf::Vector2f position, sf::Vector2f scale,
	sf::Vector2f direction, float initialVelocity,
	float maxVelocity, float acceleration)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;
	this->direction = direction;

	this->currentVelocity = sf::Vector2f(
		initialVelocity * this->direction.x,
		initialVelocity * this->direction.y);

	this->sprite.setScale(scale);
	this->sprite.setPosition(
		sf::Vector2f(
			position.x - this->sprite.getGlobalBounds().width / 2,
			position.y - this->sprite.getGlobalBounds().height / 2));
}

Bullet::~Bullet()
{
}

void Bullet::Movement()
{
	if (this->acceleration > 0.f)
	{
		if (this->currentVelocity.x < this->maxVelocity)

			///accelerate in the pressed direction, velocity increasing by acceleration and multiply by direction
			this->currentVelocity.x += this->acceleration * this->direction.x;

		if (this->currentVelocity.y < this->maxVelocity)

			///accelarate in the pressed direction, valocity increasing by accelaration and multiply by direction			
			this->currentVelocity.y += this->acceleration * this->direction.y;
	}
	else
	{
		this->currentVelocity = sf::Vector2f(
			this->maxVelocity * this->direction.x,
			this->maxVelocity * this->direction.y);
	}

	this->sprite.move(this->currentVelocity);
}

void Bullet::Update()
{
	this->Movement();
}

void Bullet::Draw(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
