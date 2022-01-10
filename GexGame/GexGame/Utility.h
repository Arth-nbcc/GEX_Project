#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sf {
	class Sprite;
	class Text;
}

// random 
int randomInt(int exclusiveMax);

// center sprite origin
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& sprite);

// vector functions
float length(sf::Vector2f v);
sf::Vector2f nomalizeVector(sf::Vector2f v);

// trig helper 
const float PI = 3.14159265f;

inline float radToDeg(float rad) {
	return rad * 180.f / PI;
}

inline float degToRad(float deg) {
	return deg * PI / 180.f;
}

inline float bering(float x, float y) {
	return 180 - radToDeg(std::atan2(x, y)); 
}

inline float bering(sf::Vector2f v) {
	return 180 - radToDeg(std::atan2(v.x, v.y));
}

namespace gex {
	inline float	sin(float deg) { return std::sin(degToRad(deg)); }
	inline float	cos(float deg) { return std::cos(degToRad(deg)); }
	inline float	atan2(float opp, float adj) { return radToDeg(std::atan2(opp, adj)); }
}