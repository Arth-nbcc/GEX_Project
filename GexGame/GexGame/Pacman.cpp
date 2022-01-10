

#include "Pacman.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "Category.h"
#include "TextNode.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <memory>
#include <stdexcept>

Pacman::Pacman(const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Entity(100)
	, sprite(textures.get(TextureID::Pacman))
	, score(0)
	, pointsDisplay(nullptr)
	 
{
	centerOrigin(sprite);

	std::unique_ptr<TextNode> points(new TextNode(fonts, ""));
	pointsDisplay = points.get(); ///< raw pointer to healthDisplay node
	attachChild(std::move(points));

	updateTexts();

}

void Pacman::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int Pacman::getCategory() const
{ 
	return Category::Pacman;
}

void Pacman::updateScore(int points)
{
	score += points;
}


sf::FloatRect Pacman::getBoundingRect() const
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

bool Pacman::isMarkedForRemoval() const
{
	return isDestroyed();
}

void Pacman::remove()
{
 	Entity::remove();
}

void Pacman::updateCurrent(sf::Time dt, CommandQueue& commands)
{ 
	updateTexts();
	Entity::updateCurrent(dt, commands);
}

void Pacman::updateTexts()
{
	 // update the text and display the score
}

