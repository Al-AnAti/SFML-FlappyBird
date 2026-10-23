#include "Bird.h"

Bird::Bird()
{
	texture.loadFromFile("assets/textures/BlueBird.png");

	body.setTexture(texture);
	body.setScale({ -2.25f, 2.25f });

	reset();
}

void Bird::reset()
{
	speed = maxFallingSpeed;
	body.setPosition({ 640.f, 200.f });
	body.setRotation(0.f);
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
