#include <random>

#include "Pipe.h"

Pipe::Pipe(const sf::Vector2f& pos)
{
	speed = 5.f;
	passed = false;

	sf::Vector2f topPos{pos.x, pos.y - p_length - halfGap};
	sf::Vector2f botPos{pos.x, pos.y + halfGap};

	top.setPosition(topPos);
	bot.setPosition(botPos);

	top.setSize({ p_width, p_length });
	bot.setSize({ p_width, p_length });

	top.setFillColor(sf::Color(50, 220, 50, 255));
	bot.setFillColor(sf::Color(50, 220, 50, 255));

	top.setOutlineThickness(2);
	bot.setOutlineThickness(2);

	top.setOutlineColor(sf::Color::Black);
	bot.setOutlineColor(sf::Color::Black);

	sf::Vector2f midPos{pos.x + p_width - 10, pos.y - halfGap};
	mid.setPosition(midPos);
	mid.setSize({ 10, halfGap * 2 });
}

void Pipe::generate(std::vector<std::unique_ptr<Pipe>>& pipes, std::vector<sf::Drawable*>& drawables)
{
	for (int i = 0; i < numberOfPipes; i++)
	{
		sf::Vector2f vec2{ spawnXPoint + i * spacing, randomHeight()};
		auto& p = pipes.emplace_back(std::make_unique<Pipe>(vec2));
		drawables.push_back(&p->top);
		drawables.push_back(&p->bot);
	}
}

void Pipe::move()
{
	sf::Vector2f delta(-speed, 0.f);
	top.move(delta);
	mid.move(delta);
	bot.move(delta);
}

float Pipe::getX() const
{
	return top.getPosition().x;
}

float Pipe::randomHeight()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(static_cast<int>(minHeight), static_cast<int>(maxHeight));

	int randomNumber = dist(gen);

	return static_cast<float>(randomNumber);
}

void Pipe::resetPosition()
{
	passed = false;
	float y = randomHeight();
	top.setPosition({ spawnXPoint, y - p_length - halfGap });
	mid.setPosition({ spawnXPoint + p_width - 10, y - halfGap });
	bot.setPosition({ spawnXPoint, y + halfGap });
}