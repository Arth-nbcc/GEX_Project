#pragma once

namespace sf {
	class Texture;
	class Font;
}

enum class TextureID
{
	Pacman,
	Ghost,
	Cherry,
	Background,

	Eagle, 
	Raptor,
	Avenger,
	Desert,
	TitleScreen,

	Bullet,
	Missile,

	HealthRefill,
	MissileRefill,
	FireSpread,
	FireRate,
};

enum class FontID
{
	Main
};

// forward declaration
template <typename Resource, typename Id>
class ResourceHolder;

using TextureHolder_t = ResourceHolder<sf::Texture, TextureID>;
using FontHolder_t = ResourceHolder<sf::Font, FontID>;