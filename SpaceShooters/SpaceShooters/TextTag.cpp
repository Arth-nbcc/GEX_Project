#include "TextTag.h"

TextTag::TextTag(sf::Font* font, std::string text, sf::Color color,
	sf::Vector2f position, unsigned int size, float timerMax)
{
	//text 
	this->text.setFont(*font);
	this->text.setCharacterSize(size);
	this->text.setPosition(position);
	this->text.setString(text);
	this->text.setFillColor(color);

	//text speed, direction
	this->speed = 2.5f;
	this->direction.x = 0.f;
	this->direction.y = -1.f;

	//timers
	this->timerMax = timerMax;
	this->timer = this->timerMax;

}

TextTag::~TextTag()
{
}

void TextTag::Update()
{
	//update timer
	if (this->timer > 0.f)
	{
		this->timer -= 1.f;

		this->text.move(
			this->direction.x * this->speed,
			this->direction.y * this->speed);
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