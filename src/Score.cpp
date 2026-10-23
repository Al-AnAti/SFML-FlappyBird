#include "Score.h"
#include "Pipe.h"

Score::Score(std::vector<sf::Drawable*>& drawables, const sf::Font& font)
{
	newRecord = false;

	score = 0;
	readHScore();

	scoreText.setFont(font);
	hScoreText.setFont(font);

	scoreText.setString("Score: " + std::to_string(score));
	hScoreText.setString("Highest Score: " + std::to_string(hScore));

	scoreText.setCharacterSize(20);
	hScoreText.setCharacterSize(20);

	scoreText.setPosition({ 30, 30 });
	hScoreText.setPosition({ 1100, 30 });

	drawables.push_back(&scoreText);
	drawables.push_back(&hScoreText);
}

void Score::add()
{
	scoreText.setString("Score: " + std::to_string(++score));
	if (score > hScore)
	{
		newRecord = true;
		hScoreText.setString("Highest Score: " + std::to_string(++hScore));
	}
	if (score % plusEveryPoints == 0 && score != 0)
		Pipe::speed += fasterBy;
}

void Score::readHScore()
{
	std::ifstream inFile("score.txt");
	if (!inFile.is_open())
	{
		std::ofstream outFile("score.txt"); // creates empty file
		outFile.close();
		hScore = 0;
	}
	else
		inFile >> hScore;
}

void Score::writeHScore()
{
	std::ofstream outFile("score.txt", std::ios::trunc);
	if (outFile.is_open())
	{
		outFile << hScore;
		outFile.close();
	}
}
