#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include "dArr.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <cstdlib>


class Pickup
{
private:
	float dtMultiplier;
	int type;

	dArr<sf::Texture>* textures;
	sf::Sprite sprite;

	float aliveTimerMax;
	float aliveTimer;

public:
	Pickup(
		dArr<sf::Texture>* textures, sf::Vector2f position,
		int type, float duration);
	virtual ~Pickup();

	inline const int& getType() const { return this->type; }
	inline const bool canDelete()const { return this->aliveTimer >= this->aliveTimerMax; }
	inline sf::Vector2f getPosition() { return this->sprite.getPosition(); }

	bool checkCollision(sf::FloatRect rect);

	void Update(const float& dt);
	void Draw(sf::RenderTarget& target);
};

