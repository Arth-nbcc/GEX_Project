#pragma once
#include "Entity.h"

#include "ResourceIdentifiers.h"
#include "Command.h"
#include "CommandQueue.h"

#include <SFML/Graphics/Sprite.hpp>

class Ghost : public Entity
{
public:
	Ghost(const TextureHolder_t& textures);

	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned int	getCategory() const override;

	virtual sf::FloatRect	getBoundingRect() const override;

private:
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
	sf::Sprite				sprite;
};

