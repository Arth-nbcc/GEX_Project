#include "State.h"
#include "StateStack.h"

State::Context::Context(
    sf::RenderWindow& window,
    TextureHolder_t& textures, 
    FontHolder_t& fonts, 
    PlayerControl& player)

    : window(&window)
    , textures(&textures)
    , fonts(&fonts)
    , player(&player)
{}



State::State(StateStack& stack, Context context)
    : stack(&stack)
    , context(context)
{}

State::~State()
{}


void State::requestStackPush(StateID stateID)
{
    stack->pushState(stateID);
}

void State::requestStackPop()
{
    stack->popState();
}

void State::requestStateClear()
{
    stack->clearStates();
}

State::Context State::getContext() const
{
    return context;
}
