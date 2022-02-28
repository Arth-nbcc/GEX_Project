#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include<vector>
#include<iostream>
#include<cstdlib>

class Enemy
{
private:
	sf::Texture* texture;
	sf::Sprite   sprite;

	sf::Vector2u windowBounds;
	sf::Vector2f direction;

	float damageTimer;
	float damageTimerMax;

	int		type;
	int		hp;
	int		hpMax;
	int		damageMin;
	int		damageMax;

public:
	Enemy(sf::Texture* texture, sf::Vector2u windowBounds,
		sf::Vector2f direction, sf::Vector2f scale,
		int type, int hpMax,
		int damageMax, int damageMin);

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

	///
	///functions
	/// 
	void	takeDamage(int damage);
	void	Update();
	void	Draw(sf::RenderTarget& target);

};

