#include "Cherry.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "Category.h"

#include <SFML/Graphics/RenderTarget.hpp>

Cherry::Cherry(const TextureHolder_t& textures)
	: Entity(1)
{
	 
}

void Cherry::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	 
}

unsigned int Cherry::getCategory() const
{
	return 0;
}

sf::FloatRect Cherry::getBoundingRect() const
{
	return  sf::FloatRect();
}
