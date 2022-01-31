#include"Bullet.h"

class Player
{
private:
	int playerNr;

	sf::Vector2f playerCenter;

	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;

	sf::Texture* texture;
	sf::Texture* bulletTexture;

	sf::Sprite			sprite;
	sf::RectangleShape	hitbox;

	std::vector<Bullet> bullets;

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
	Player(sf::Texture* texture, sf::Texture* bulletTexture,
		int UP = 22, int DOWN = 18,
		int LEFT = 0, int RIGHT = 3,
		int SHOOT = 57);

	virtual ~Player();

	//Accessors
	inline std::vector<Bullet>& getBullets() { return this->bullets; } //reference for bullets
	inline const sf::Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const sf::String getHpAsString()const { return std::to_string(this->HP) + "/" + std::to_string(this->hpMax); }

	//functions
	void	Combact();
	void	Movement(); //for keyboard
	void	Update(sf::Vector2u windowBounds);
	void	Draw(sf::RenderTarget& target);

	//Statics
	static	unsigned players;

};

