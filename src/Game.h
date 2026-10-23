#pragma once

#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "Pipe.h"
#include "Bird.h"
#include "Score.h"

class Game
{
public:
	inline static const float WIDTH  = 1280.f;
	inline static const float HEIGHT = 720.f;

private:
	bool finished;

	sf::RenderWindow window;
	sf::Event event;
	sf::Font font;

	// Everything drawn each frame. Doesn't own anything: the objects
	// belong to pipes, bird, score and gameOverText below.
	std::vector<sf::Drawable*> drawables;

	std::vector<std::unique_ptr<Pipe>> pipes;
	Bird bird;
	std::unique_ptr<Score> score;
	sf::Text gameOverText;

public:
	Game();
	void Run();

private:
	void init();
	void update();
	void render();
	void input(sf::Event event);
	void checkCollisions();
	void gameOver();
};
