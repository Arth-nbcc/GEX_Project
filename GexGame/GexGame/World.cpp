#include "World.h"
#include "Utility.h"
#include <algorithm>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Cherry.h"
#include "Ghost.h"
 

World::World(sf::RenderWindow& window, FontHolder_t& fonts) 
	: window(window)
	, worldView(window.getDefaultView())
	, textures()
	, fonts(fonts)
	, sceneGraph()
	, sceneLayers()
	, commands()
	, worldBounds(0.f, 0.f, worldView.getSize().x , worldView.getSize().y)
	, spawnPosition(40.f, 320.f)
	, scrollSpeed(0.f)
	, playerPacman(nullptr)
{
	loadTextures();
	buildScene();

	// worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt)
{
	playerPacman->setVelocity(0.f, 0.f);

	destroyEntitiesOutOfView();
	

	// apply all command
	while (!commands.isEmpty())
	{
		sceneGraph.onCommand(commands.pop(), dt);
	}
	
	adaptPlayerVelocity();
	handleCollisions();
	sceneGraph.removeWrecks();

	sceneGraph.update(dt, commands); 
	adaptPlayerPosition(); 
}

void World::draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return commands;
}

void World::loadTextures()
{
	textures.load(TextureID::Desert, "../Media/Textures/Desert.png");

	textures.load(TextureID::Pacman, "../Media/Textures/Pacman.png");
	textures.load(TextureID::Cherry, "../Media/Textures/Cherry.png");
	textures.load(TextureID::Ghost, "../Media/Textures/Ghost.png");
}

void World::buildScene()
{
	// set up layer nodes
	for (std::size_t i = 0; i < LayerCount; ++i) {

		Category::type category = (i == Air) ? Category::SceneAirLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}

	// prepare tiled background 

	sf::Texture& texture = textures.get(TextureID::Desert);
	texture.setRepeated(true);

	sf::IntRect  textureRect(worldBounds);

	auto backgroundSprite =  std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachChild(std::move(backgroundSprite));


	// Add pacman/player
	auto pacman = std::make_unique<Pacman>(textures, fonts);
	playerPacman = pacman.get();
	playerPacman->setPosition(spawnPosition);
	sceneLayers[Air]->attachChild(std::move(pacman));

	// add cherry
	 

	// add ghosts
	
	// four sets of four ghosts, 
	 


}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());
	
	const float borderDistance = 40.f;

	sf::Vector2f position = playerPacman->getPosition();

	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

	playerPacman->setPosition(position);

}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = playerPacman->getVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f)
		playerPacman->setVelocity(velocity / std::sqrt(2.f));

	playerPacman->accelerate(0.f, scrollSpeed);

}


sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(worldView.getCenter() - worldView.getSize() / 2.f , worldView.getSize() );
}

sf::FloatRect World::getBattlefield() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}



bool matchesCategories(SceneNode::Pair& colliders, Category::type type1, Category::type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);


	for (auto pair : collisionPairs)
	{
		// handle pacman and cherry collision 
		 
		// hadnle pacman and ghost collision 
		  
	}
}

void World::destroyEntitiesOutOfView()
{
	auto battlefield = getBattlefield();

	Command command;
	command.category = Category::SpaceJunk;

	command.action = derivedAction<Entity>([this, battlefield](Entity& e, sf::Time dt)
		{
			if (!battlefield.intersects(e.getBoundingRect()))
				e.remove();
		});

	commands.push(command);
}
