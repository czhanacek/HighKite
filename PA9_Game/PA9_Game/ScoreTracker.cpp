#include "ScoreTracker.h"



ScoreTracker::ScoreTracker() : DrawableWithPriority("ScoreSun", "game", "imgs/sun.png", 13)
{
	setScale(0.4, 0.4);
	setPosition(1050, -50);
	score = 0;
}


ScoreTracker::~ScoreTracker()
{
}

void ScoreTracker::setScore(int newScore)
{
	score = newScore;
}

int ScoreTracker::getScore()
{
	return score;
}

Message ScoreTracker::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
	//std::cout << "Score" << getScore() << std::endl;
	if (getContext() == "game") {
		if (clocks[0].getElapsedTime().asMilliseconds() > 400) {
			setScore(getScore() + 1);
			clocks[0].restart();
		}
	}

	std::string CurrentScore = "000000";
	int scoretemp = score, digit = 0;

	int index = 5;

	while (scoretemp != 0)
	{
		digit = (scoretemp % 10) + 48;
		CurrentScore[index] = digit;

		scoretemp = scoretemp - (scoretemp % 10);
		scoretemp = scoretemp / 10;

		--index;

	}

	return Message("ScoreTracker", CurrentScore);
}

void ScoreTracker::receiveMessage(Message msg)
{

}