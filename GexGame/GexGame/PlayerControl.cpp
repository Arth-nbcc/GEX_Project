#include "PlayerControl.h"

#include "Pacman.h"
#include "Command.h"
#include "CommandQueue.h"

#include <iostream> 

PlayerControl::PlayerControl()
{
	initializeKeys();
	initializeActions();
}

void PlayerControl::initializeKeys()
{
	// Set initial key bindings

	// arrows
	keyBindings[sf::Keyboard::Left]		= Action::MoveLeft;
	keyBindings[sf::Keyboard::Right]	= Action::MoveRight;
	keyBindings[sf::Keyboard::Up]		= Action::MoveUp;
	keyBindings[sf::Keyboard::Down]		= Action::MoveDown;

	// AWSD
	keyBindings[sf::Keyboard::A] = Action::MoveLeft;
	keyBindings[sf::Keyboard::D] = Action::MoveRight;
	keyBindings[sf::Keyboard::W] = Action::MoveUp;
	keyBindings[sf::Keyboard::S] = Action::MoveDown;

	

}


void PlayerControl::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = keyBindings.find(event.key.code);
		
		if ( found != keyBindings.end() && !isRealTimeAction(found->second) )
			commands.push(actionBindings[found->second]);
		
	}
}

void PlayerControl::handleRealTimeInput(CommandQueue& commands)
{

	for (auto [key, action] : keyBindings)
	{
		if (sf::Keyboard::isKeyPressed(key) && isRealTimeAction(action))
			commands.push(actionBindings[action]);
	}

}


void PlayerControl::assignKey(Action action, sf::Keyboard::Key key)
{
	// remove all keys that already map to action
	for (auto itr = keyBindings.begin(); itr != keyBindings.end();)
	{
		if (itr->second == action)
			keyBindings.erase(itr++);
		else
			++itr;
	}

	// insert new binding
	keyBindings[key] = action;
}

sf::Keyboard::Key PlayerControl::getAssignedKey(Action action) const
{
	for (auto [key, boundAction] : keyBindings)
	{
		if (boundAction == action)
			return key;
	}
	return sf::Keyboard::Unknown;
}

void PlayerControl::initializeActions()
{
	const float speed = 200.f;

	// Create action Bindings to control pacman
	 
	 
	// actionBindings[Action::MoveLeft].action =  
	// actionBindings[Action::MoveLeft].category = 
	// 
	// actionBindings[Action::MoveRight].action = 
	// actionBindings[Action::MoveRight].category = 
	// 
	// actionBindings[Action::MoveUp].action =  
	// actionBindings[Action::MoveUp].category =  
	// 
	// actionBindings[Action::MoveDown].action =  
	// actionBindings[Action::MoveDown].category =  
 
}

bool PlayerControl::isRealTimeAction(Action action)
{
	switch (action)
	{
	case Action::MoveDown:
	case Action::MoveUp:
	case Action::MoveLeft:
	case Action::MoveRight:
		return true;

	default:
		return false;
	}
}
