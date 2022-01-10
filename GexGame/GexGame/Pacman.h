#pragma once


#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "Command.h"
#include "CommandQueue.h"


#include <SFML/Graphics/Sprite.hpp>

class TextNode;

class Pacman : public Entity
{
public:
	
public:
	Pacman(const TextureHolder_t& textures, const FontHolder_t& fonts);

	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned int	getCategory() const override;

	void					updateScore(int points);

	virtual sf::FloatRect	getBoundingRect() const override;

	 
	virtual bool			isMarkedForRemoval() const override;
	virtual void			remove() override;


private: 
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands) override;
	void					updateTexts();
	
private:
	sf::Sprite				sprite;
	
	int						score;
	TextNode*				pointsDisplay;
};