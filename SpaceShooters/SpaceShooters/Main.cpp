#include"Game.h"
#include "dArr.h"
#include "SFML/Audio.hpp"

int main()
{
	/// Window
	sf::RenderWindow window(sf::VideoMode(1720, 880), "Space-Shooters", sf::Style::Default);

	sf::Clock clock;
	float dt = 0.f;

	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	//soundBuffer.loadFromFile("Textures/Music/MainMusic.ogg");

	sound.setBuffer(soundBuffer);
	sound.setLoop(true);
	sound.setVolume(50);
	sound.play();

	Game game(&window);

	/// Game Loop
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

		//for printing the dt of laptop
		dt = clock.restart().asSeconds();
		//std::cout << dt << "\n";

		game.update(dt);
		game.draw();
	}

	return 0;
}
//this computer dt is 0.016