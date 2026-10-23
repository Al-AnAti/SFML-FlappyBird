#pragma once

#include <fstream>
#include <vector>
#include "SFML/Graphics.hpp"

class Score
{
public:
	int score;
	bool newRecord;

private:
	sf::Text scoreText;

	int hScore;
	sf::Text hScoreText;

	inline static const int plusEveryPoints = 5;
	inline static const float fasterBy = 0.5;

public:
	Score(std::vector<sf::Drawable*>& drawables, const sf::Font& font);
	// drawables holds pointers to the texts, so Score must stay where it is
	Score(const Score&) = delete;
	Score& operator=(const Score&) = delete;

	void add();
	void readHScore();
	void writeHScore();
};
