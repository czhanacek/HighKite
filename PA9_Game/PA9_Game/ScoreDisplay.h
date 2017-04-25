#pragma once
#include "DrawableWithPriority.h"

class DigitOne : public DrawableWithPriority
{
public:
	DigitOne();
	~DigitOne();
	void receiveMessage(Message msg);
	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
	Message react(sf::Event e);
	Message click();
	Message unclick();

private:
	std::vector<DrawableWithPriority *> numbers;
};


class DigitTwo : public DrawableWithPriority
{
public:
	DigitTwo();
	~DigitTwo();
	void receiveMessage(Message msg);
	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
	Message react(sf::Event e);
	Message click();
	Message unclick();

private:
	std::vector<DrawableWithPriority *> numbers;
};


class DigitThree : public DrawableWithPriority
{
public:
	DigitThree();
	~DigitThree();
	void receiveMessage(Message msg);
	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
	Message react(sf::Event e);
	Message click();
	Message unclick();

private:
	std::vector<DrawableWithPriority *> numbers;
};


class DigitFour : public DrawableWithPriority
{
public:
	DigitFour();
	~DigitFour();
	void receiveMessage(Message msg);
	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
	Message react(sf::Event e);
	Message click();
	Message unclick();

private:
	std::vector<DrawableWithPriority *> numbers;
};


class DigitFive : public DrawableWithPriority
{
public:
	DigitFive();
	~DigitFive();
	void receiveMessage(Message msg);
	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
	Message react(sf::Event e);
	Message click();
	Message unclick();

private:
	std::vector<DrawableWithPriority *> numbers;
};