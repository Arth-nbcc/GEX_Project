#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include<vector>
#include<iostream>
#include<cstdlib>


class TextTag
{
private:
	float dtMultiplier;

	sf::Font* font;
	sf::Text  text;

	sf::Vector2f direction;
	float speed;
	float timerMax;
	float timer;
	bool follow;


public:
	TextTag(sf::Font* font, std::string text, sf::Color color,
		sf::Vector2f position, unsigned int size, float timerMax);

	virtual ~TextTag();

	//Accessors
		//will get this timer and check if it is 0, if yes, remove textTags
	inline const float& getTimer()const { return this->timer; }

	//functiuons
	void Update(const float& dt);
	void Draw(sf::RenderTarget& target);
};

