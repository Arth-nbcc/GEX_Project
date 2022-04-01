
#include"Player.h"
#include "Enemy.h"
#include "TextTag.h"
#include "dArr.h"
#include "Pickup.h"

class Game
{
private:
	sf::RenderWindow* window;
	float dtMultiplier;

	bool	 paused;
	float	 keyTimeMax;
	float	 keyTime;

	sf::Clock scoreTimer;
	int		 scoreTime;
	unsigned score;
	unsigned scoreMultiplier;

	/// Text player
	sf::Font font;
	sf::Text followPlayerTexts; //(health)

	//Text enemy
	sf::Text enemyText; //(health)

	//Text Gameover
	sf::Text gameOverText;

	//score
	sf::Text scoreText;

	sf::Text controlsText;

	/// Players class
	dArr<Player> players;
	int playersAlive;

	//textTags class
	dArr<TextTag> textTags;

	//pickups
	dArr<Pickup> pickups;

	/// Textures
	std::vector<sf::Texture> textures;
	dArr<sf::Texture> enemyTextures;
	dArr<sf::Texture> pickupTextures;;
	sf::Texture auraTextures;

	//background
	sf::Texture background;
	sf::Sprite worldBackground;

	/// Enemie class
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;

	float		enemySpawnTimer;
	float		enemySpawnTimerMax;

public:
	Game(sf::RenderWindow* window);
	virtual ~Game();


	/// Accessors
	inline	sf::RenderWindow& getWindow() { return *this->window; }
	//de-reference //it will not create seperate memory, it will just copy code directly to calling function.

	//Setters


	/// Functions
	void		InitUI();
	void		UpdateUIPlayer(int index);
	void		UpdateUIEnemy(int index);
	void		update(const float& dt);
	void		draw();
	void		DrawUI();
	void		backgroundDraw();
	void		initTextures();
};

///NOTE: to acess member of a function or variable, we use . operator.
///		-> is used to access the same when we are working with pointers. no confusion!
/// this-> refers to current instance of class. pass current object as parameter, refers current class instance variable