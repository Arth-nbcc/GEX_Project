#include "Ghost.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "Category.h"

#include <SFML/Graphics/RenderTarget.hpp>

Ghost::Ghost(const TextureHolder_t& textures)
	: Entity(1)
{
}

void Ghost::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

unsigned int Ghost::getCategory() const
{
	return 0;
}

sf::FloatRect Ghost::getBoundingRect() const
{
	return sf::FloatRect();
}

void Ghost::updateCurrent(sf::Time dt, CommandQueue& commands)
{

	// make sure ghosts don't leave view
	// make sure they change direction when they reach bounds

}
