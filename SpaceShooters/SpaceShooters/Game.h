
#include"Player.h"
#include "Enemy.h"
#include "TextTag.h"

class Game
{
private:
	sf::RenderWindow* window;

	/// <summary>
	/// Text
	/// </summary>
	sf::Font font;
	sf::Text followPlayerTexts;
	//sf::Text staticPlayerTexts;
	sf::Text enemyText;
	sf::Text gameOverText;

	/// <summary>
	/// Players
	/// </summary>
	std::vector<Player> players;
	int playersAlive;

	//textTags
	std::vector<TextTag> textTags;

	/// <summary>
	/// Textures
	/// </summary>
	std::vector<sf::Texture> textures;
	sf::Texture auraTextures;

	/// <summary>
	/// Enemies
	/// </summary>
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;

	int		enemySpawnTimer;
	int		enemySpawnTimerMax;

public:
	Game(sf::RenderWindow* window);
	virtual ~Game();

	/// <summary>
	/// Accessors
	/// </summary>
	/// <returns></returns>
	inline		sf::RenderWindow& getWindow() { return *this->window; } //de-reference //it will not create seperate memory, it willl just copy code directly to calling function.

	//Setters

	/// <summary>
	/// Functions
	/// </summary>
	void		InitUI();
	void		UpdateUIPlayer(int index);
	void		UpdateUIEnemy(int index);
	void		update();
	void		draw();
	void		DrawUI();
	void		initTextures();
};

///NOTE: to acess member of a function or variable, we use . operator.
///		-> is used to access the same when we are working with pointers. no confusion!
/// this-> refers to current instance of class. pass current object as parameter, refers current class instance variable