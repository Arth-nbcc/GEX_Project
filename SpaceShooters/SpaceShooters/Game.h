
#include"Player.h"
#include "Enemy.h"


class Game
{
private:
	sf::RenderWindow* window;

	//text
	sf::Font font;
	std::vector<sf::Text>followPlayerTexts;
	std::vector<sf::Text>staticPlayerTexts;
	sf::Text enemyText;

	//players
	std::vector<Player> players;

	//Textures
	std::vector<sf::Texture> textures;

	//Enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;

	int		enemySpawnTimer;
	int		enemySpawnTimerMax;

public:
	Game(sf::RenderWindow* window);
	virtual ~Game();

	//Accessors
	inline		sf::RenderWindow& getWindow() { return *this->window; } //de-reference //it will not create seperate memory, it willl just copy code directly to calling function.

	//Setters

	//functions
	void		InitUI();
	void		UpdateUI();
	void		CombateUpdate();
	void		update();
	void		draw();
	void		DrawUI();
};

//NOTE: to acess member of a function or variable, we use . operator.
//		-> is used to access the same when we are working with pointers. no confusion!
// this-> refers to current instance of class. pass current object as parameter, refers current class instance variable