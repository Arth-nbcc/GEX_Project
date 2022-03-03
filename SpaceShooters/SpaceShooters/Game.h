
#include"Player.h"
#include "Enemy.h"
#include "TextTag.h"

class Game
{
private:
	sf::RenderWindow* window;
	float dtMultiplier;

	/// Text player
	sf::Font font;
	sf::Text followPlayerTexts; //(health)

	//Text enemy
	sf::Text enemyText; //(health)

	//Text Gameover
	sf::Text gameOverText;


	/// Players class
	std::vector<Player> players;
	int playersAlive;

	//textTags class
	std::vector<TextTag> textTags;


	/// Textures
	std::vector<sf::Texture> textures;
	sf::Texture auraTextures;

	/// Enemie class
	std::vector<Enemy> enemies;
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
	void		initTextures();
};

///NOTE: to acess member of a function or variable, we use . operator.
///		-> is used to access the same when we are working with pointers. no confusion!
/// this-> refers to current instance of class. pass current object as parameter, refers current class instance variable