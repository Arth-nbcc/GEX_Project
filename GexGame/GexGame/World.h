#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"

#include "SpriteNode.h"
//#include "Aircraft.h"
#include "Pacman.h"
#include "CommandQueue.h"
#include "Command.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

namespace sf {
	class RenderWindow;
}


class World 
{
public: 
					World(const World&) = delete;

	explicit		World(sf::RenderWindow& window, FontHolder_t& fonts);

	void			update(sf::Time dt);
	void			draw();
	 
	CommandQueue&	getCommandQueue();

private:
	void			loadTextures();
	void			buildScene();

	void			adaptPlayerPosition();
	void			adaptPlayerVelocity();

	 
	sf::FloatRect	getViewBounds() const;
	sf::FloatRect	getBattlefield() const;

	 
	void			handleCollisions();
	void			destroyEntitiesOutOfView();
	

private:

	enum Layer
	{
		Background = 0,
		Air,
		LayerCount
	};
	

private:
	sf::RenderWindow&					window;
	sf::View							worldView;
	TextureHolder_t						textures;
	FontHolder_t&						fonts;

	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;
	CommandQueue						commands;

	sf::FloatRect						worldBounds;

	sf::Vector2f						spawnPosition;
	float								scrollSpeed;
	
	
	Pacman*								playerPacman;

};

