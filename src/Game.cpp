#include <iostream>

#include "Game.h"
#include "Bird.h"
#include "Pipe.h"
#include "Score.h"

Game::Game() 
{
	window.create(sf::VideoMode(static_cast<unsigned>(WIDTH), static_cast<unsigned>(HEIGHT)), "FlappyBird");
	window.setFramerateLimit(60);

	if (!font.loadFromFile("assets/fonts/arial.ttf"))
	{
		std::cerr << "Failed to load font!" << std::endl;
		exit(1);
	}

	init();
}

void Game::init()
{
	finished = false;
	drawables.clear();
	pipes.clear();

	Pipe::generate(pipes, drawables);

	bird.reset();
	drawables.push_back(&bird.body);

	score = std::make_unique<Score>(drawables, font);
}

void Game::Run()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			input(event);
		}

		if (!finished)
		{
			update();
			checkCollisions();
		}
		
		render();
	}
}

void Game::update()
{
	for (auto& p : pipes)
	{
		p->move();
		if (p->getX() < -200.f)
			p->resetPosition();
	}
	bird.Move();
}

void Game::render()
{
	window.clear(sf::Color(45, 60, 70));

	for (auto& shape : drawables)
		window.draw(*shape);

	window.display();
}

void Game::input(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
		{
			if (!finished)
				bird.jump();
		} break;
		case sf::Keyboard::R:
		{
			if (finished)
				init();
		} break;
		case sf::Keyboard::Escape:
		{
			window.close();
		} break;
		default:
			break;
		}
	}	
}

void Game::checkCollisions()
{
	sf::FloatRect birdBounds = bird.body.getGlobalBounds();
	birdBounds.left += 5;
	birdBounds.width -= 10;
	birdBounds.top += 5;
	birdBounds.height -= 10;

	for (auto& p : pipes)
	{
		if (birdBounds.intersects(p->top.getGlobalBounds())  ||
			birdBounds.intersects(p->bot.getGlobalBounds())  || 
			birdBounds.top > 700 ||
			birdBounds.top < 0)
		{
			gameOver();
			return;
		}

		if (birdBounds.intersects(p->mid.getGlobalBounds()) && !p->passed)
		{
			p->passed = true;
			score->add();
		}
	}
}

void Game::gameOver()
{
	finished = true;

	if (score->newRecord)
		score->writeHScore();

	gameOverText.setString("Game Over!");
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(40);
	gameOverText.setOrigin({ gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2 });
	gameOverText.setPosition({ Game::WIDTH / 2, Game::HEIGHT / 2 });
	drawables.push_back(&gameOverText);
}