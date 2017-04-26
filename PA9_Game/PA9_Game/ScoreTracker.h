#pragma once
#include "DrawableWithPriority.h"

class ScoreTracker : public DrawableWithPriority
{
public:
	ScoreTracker();
	~ScoreTracker();

	void setScore(int newScore);
	int getScore();

	void receiveMessage(Message msg);
	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);

private:
	int score;
};

