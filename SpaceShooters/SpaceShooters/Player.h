#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include<iostream>

class Player
{
private:
	sf::Texture* texture;
	sf::Sprite			sprite;
	sf::RectangleShape	hitbox;

	int controls[5];

	int level;
	int exp;
	int expNext;

	int HP;
	int hpMax;

	int damage;
	int damageMax;

	int score;

public:
	Player(sf::Texture* texture,
		int UP = 22, int DOWN = 18,
		int LEFT = 0, int RIGHT = 3,
		int SHOOT = 57);

	virtual ~Player();

	void	Movement(); //for keyboard
	void	Update();
	void	Draw(sf::RenderTarget& target);
};

