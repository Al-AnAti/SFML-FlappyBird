#pragma once

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"

class Pipe
{
public:

	sf::RectangleShape top;
	sf::RectangleShape mid;
	sf::RectangleShape bot;

	inline static float speed = 3.f;
	bool passed;

private:
	inline static const float minHeight = 200.f;
	inline static const float maxHeight = 520.f;

	inline static const float p_width  = 60.f;
	inline static const float p_length = 500.f;
	inline static const float halfGap  = 140.f;

	inline static const int numberOfPipes = 4;
	inline static const float spawnXPoint = 1380.f;
	inline static const float spacing	  = 400.f;

public:
	Pipe(const sf::Vector2f& pos);
	static void generate(std::vector<std::unique_ptr<Pipe>>& pipes, std::vector<sf::Drawable*>& drawables);
	void move();
	void resetPosition();
	float getX() const;
	
private:
	static float randomHeight();
};