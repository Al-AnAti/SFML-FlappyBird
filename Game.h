#pragma once

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

	std::vector<sf::Drawable*> drawables;

	std::vector<Pipe*> pipes;
	Bird bird;
	Score* score;

public:
	Game();
	~Game();
	void Run();

private:
	void init();
	void update();
	void render();
	void input(sf::Event event);
	void checkCollisions();
	void gameOver();
};