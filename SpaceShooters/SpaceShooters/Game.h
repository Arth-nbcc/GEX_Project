#include"Player.h"
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include<iostream>

class Game
{
private:
	sf::RenderWindow* window;
	Player* player;
	sf::Texture playerTexture;

public:
	Game(sf::RenderWindow* window);
	virtual ~Game();

	//Accessors
	inline		sf::RenderWindow& getWindow() { return *this->window; } //de-reference //it will not create seperate memory, it willl just copy code directly to calling function.
	//Setters

	//functions
	void		update();
	void		draw();

};

//NOTE: to acess member of a function or variable, we use . operator.
//		-> is used to access the same when we are working with pointers. no confusion!
// this-> refers to current instance of class. pass current object as parameter, refers current class instance variable