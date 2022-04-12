#include "TextTag.h"

TextTag::TextTag(
	sf::Font* font, std::string text, sf::Color color,
	sf::Vector2f position, sf::Vector2f direction,
	unsigned int size, float timerMax, bool accelerate)
{
	//dt
	this->dtMultiplier = 62.f;

	//text 
	this->text.setFont(*font);
	this->text.setCharacterSize(size);
	this->text.setPosition(position);
	this->text.setString(text);
	this->text.setFillColor(color);

	//text speed, direction
	this->speed = 2.5f;
	this->direction.x = direction.x;
	this->direction.y = direction.y;

	//timers
	this->timerMax = timerMax;
	this->timer = this->timerMax;
	this->accelerate = accelerate;

}

TextTag::~TextTag()
{
}

void TextTag::Update(const float& dt)
{
	//Update timer
	if (this->timer > 0.f)
	{
		this->timer -= 1.f * dt * this->dtMultiplier;

		if (this->accelerate)
		{
			if (this->timer > this->timerMax / 2)
			{
				this->text.move(
					this->direction.x * (this->speed * 3.f) * dt * this->dtMultiplier,
					this->direction.y * (this->speed * 30.f) * dt * this->dtMultiplier);
			}
			else
			{
				this->text.move(
					this->direction.x * this->speed * dt * this->dtMultiplier,
					this->direction.y * this->speed * dt * this->dtMultiplier);
			}
		}
		else
		{
			this->text.move(
				this->direction.x * this->speed * dt * this->dtMultiplier,
				this->direction.y * this->speed * dt * this->dtMultiplier);
		}
	}
	else
	{
		this->text.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

void TextTag::Draw(sf::RenderTarget& target)
{
	target.draw(this->text);
}