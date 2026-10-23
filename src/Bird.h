#pragma once

#include "SFML/Graphics.hpp"

class Bird
{
public:
	sf::Sprite body;

private:
	sf::Texture texture;
	float speed;

	inline static const float weight = 0.5f;
	inline static const float jumpSTR = -10.f;
	inline static const float maxFallingSpeed = 8.f;

public:
	Bird();
	// body keeps a pointer to texture, so a copy would point at the wrong texture
	Bird(const Bird&) = delete;
	Bird& operator=(const Bird&) = delete;

	void reset();
	void jump();
	void Move();
};
