#pragma once

#include <fstream>
#include "SFML/Graphics.hpp"

class Score 
{
public:
	int score;
	bool newRecord;
	
private:
	sf::Text* scoreText;
	
	int hScore;
	sf::Text* hScoreText;

	inline static const int plusEveryPoints = 5;
	inline static const float fasterBy = 0.5;

public:
	Score(std::vector<sf::Drawable*>& drawbles, const sf::Font& font);
	~Score();
	void add();
	void readHScore();
	void writeHScore();
};