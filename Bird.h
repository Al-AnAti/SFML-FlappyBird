#pragma once

#include "SFML/Graphics.hpp"

class Bird
{
public: 
	//sf::CircleShape body;
	sf::Texture* texture;
	sf::Sprite body;

private:
	float speed;

	inline static const float weight = 0.5f;
	inline static const float jumpSTR = -10.f;
	inline static const float maxFallingSpeed = 8.f;

public:
	Bird();
	void jump();
	void Move();
};