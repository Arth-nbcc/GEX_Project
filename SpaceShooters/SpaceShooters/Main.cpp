#include"Game.h"

int main()
{
	//window
	sf::RenderWindow window(sf::VideoMode(1720, 880), "Space-Shooters", sf::Style::Default);
	window.setFramerateLimit(65);

	Game game(&window);

	//Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		game.update();
		game.draw();
	}

	return 0;
}