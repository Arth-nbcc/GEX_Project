#include"Bullet.h"

class Player
{
private:
	int playerNr;

	sf::Vector2f playerCenter;

	sf::Sprite			sprite;
	sf::RectangleShape	hitbox;

	//Accessories
	sf::Sprite	 mainGunSprite;

	std::vector<Bullet> bullets;

	sf::Texture* missile1Texture;
	sf::Texture* missile2Texture;
	sf::Texture* laserTexture;


	int controls[5];

	//player shooth movement
	sf::Vector2f	currentVelocity;
	float			maxVelocity;
	float			acceleration;
	sf::Vector2f	direction;
	float			stabilizerForce;

	int		level;
	int		exp;
	int		expNext;

	int		hp;
	int		hpMax;

	int		damage;
	int		damageMax;

	int		score;

	int		currentWeapon;

	//upgrades
	int		mainGunLevel;
	bool	dualMissile1;
	bool	dualMissile2;

	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;

public:
	Player(std::vector<sf::Texture>& textures,
		int UP = 22, int DOWN = 18,
		int LEFT = 0, int RIGHT = 3,
		int SHOOT = 57);

	virtual ~Player();

	//Accessors
	inline std::vector<Bullet>& getBullets() { return this->bullets; } //reference for bullets
	inline const sf::Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const sf::String getHpAsString()const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
	inline const int getdamage()const { return rand() % this->damageMax + this->damage; }
	inline sf::FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp()const { return this->hp; }
	inline const int& getHpMax()const { return this->hpMax; }

	//functions
	void	UpdateAccessories();
	void	Combact();
	void	Movement(); //for keyboard
	void	Update(sf::Vector2u windowBounds);
	void	Draw(sf::RenderTarget& target);

	//Statics
	static	unsigned players;

};

