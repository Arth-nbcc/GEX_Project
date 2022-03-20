#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include "dArr.h"
#include<vector>
#include<iostream>
#include<cstdlib>


class Enemy
{
private:
	dArr<sf::Texture>* textures;
	sf::Sprite   sprite;

	sf::Vector2u windowBounds;
	sf::Vector2f direction;

	float dtMultiplier;

	float damageTimer;
	float damageTimerMax;

	int		type;
	int		hp;
	int		hpMax;
	float	damageMin;
	float	damageMax;
	float   maxVelocity;

	int playerFollowNr;

public:
	Enemy(dArr<sf::Texture>& textures, sf::Vector2u windowBounds,
		sf::Vector2f position, sf::Vector2f direction,
		sf::Vector2f scale,
		int type, int playerFollowNr);

	virtual ~Enemy();

	///
	///Accessors
	///
	inline const int	getDamage()const { return this->damageMin; }
	inline const int	getHP()const { return this->hp; }
	inline const int	getHPMax()const { return this->hpMax; }
	inline const bool	isDead()const { return this->hp <= 0; }
	inline sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline sf::Vector2f getPosition() const { return this->sprite.getPosition(); }
	inline const int& getPlayerFollowNr()const { return this->playerFollowNr; }

	///
	///functions
	/// 
	void	takeDamage(int damage);
	void	Update(const float& dt, sf::Vector2f playerPosition);
	void	Draw(sf::RenderTarget& target);

	//finds the length of a vector
	float vectorLength(sf::Vector2f v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}
	//normalize that vector
	sf::Vector2f normalize(sf::Vector2f v, float length)
	{
		if (length == 0)
			return sf::Vector2f(0.f, 0.f);
		else
			return v / length;
	}

};

