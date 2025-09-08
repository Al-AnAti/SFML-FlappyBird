#include <iostream>
#include "Bird.h"

Bird::Bird()
{
	speed = maxFallingSpeed;

	texture = new sf::Texture();
	texture->loadFromFile("BlueBird.png");

	body.setTexture(*texture);
	body.setPosition({ 640.f, 200.f });
	body.setScale({ -2.25f, 2.25f });
}

void Bird::jump()
{
	speed = jumpSTR;
}

void Bird::Move()
{
	body.move({ 0.f, speed });
	if (speed < maxFallingSpeed)
		speed += weight;
	body.setRotation(speed * 4.f);
}
