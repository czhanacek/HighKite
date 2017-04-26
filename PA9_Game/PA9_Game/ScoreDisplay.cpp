#include "ScoreDisplay.h"
#include <string>


DigitOne::DigitOne() : DrawableWithPriority("DigitOne", "game", 13)
{
	//setScale(0.4, 0.4);
	setPosition(1225, 0);

	addNewTexture("imgs/zero.png");
	addNewTexture("imgs/one.png");
	addNewTexture("imgs/two.png");
	addNewTexture("imgs/three.png");
	addNewTexture("imgs/four.png");
	addNewTexture("imgs/five.png");
	addNewTexture("imgs/six.png");
	addNewTexture("imgs/seven.png");
	addNewTexture("imgs/eight.png");
	addNewTexture("imgs/nine.png");

}


DigitOne::~DigitOne()
{

}

void DigitOne::receiveMessage(Message msg)
{
	if (msg.getSender() == "ScoreTracker")
	{
		std::string strCurrentScore = msg.getContent();
		strCurrentScore.erase(0, 5);
		int intCurrentScore = atoi(strCurrentScore.c_str());

		setCurrentTexture(intCurrentScore);
	}

}

Message DigitOne::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
	return Message();
}
Message DigitOne::react(sf::Event e) {
	return Message();

}
Message DigitOne::click() {
	return Message();

}
Message DigitOne::unclick() {
	return Message();

}


DigitTwo::DigitTwo() : DrawableWithPriority("DigitTwo", "game", 14)
{
	setPosition(1200, 0);

	addNewTexture("imgs/zero.png");
	addNewTexture("imgs/one.png");
	addNewTexture("imgs/two.png");
	addNewTexture("imgs/three.png");
	addNewTexture("imgs/four.png");
	addNewTexture("imgs/five.png");
	addNewTexture("imgs/six.png");
	addNewTexture("imgs/seven.png");
	addNewTexture("imgs/eight.png");
	addNewTexture("imgs/nine.png");
}


DigitTwo::~DigitTwo()
{
}

void DigitTwo::receiveMessage(Message msg)
{
	if (msg.getSender() == "ScoreTracker")
	{
		std::string strCurrentScore = msg.getContent();
		int intCurrentScore = atoi(strCurrentScore.c_str());
		for (int i = 1; i < 2; ++i)
		{
				intCurrentScore = intCurrentScore - (intCurrentScore % 10);
				intCurrentScore = intCurrentScore / 10;
		}

		setCurrentTexture(intCurrentScore % 10);
	}

}


Message DigitTwo::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
	return Message();
}
Message DigitTwo::react(sf::Event e) {
	return Message();

}
Message DigitTwo::click() {
	return Message();

}
Message DigitTwo::unclick() {
	return Message();

}



DigitThree::DigitThree() : DrawableWithPriority("DigitThree", "game", 16)
{
	setPosition(1175, 0);

	addNewTexture("imgs/zero.png");
	addNewTexture("imgs/one.png");
	addNewTexture("imgs/two.png");
	addNewTexture("imgs/three.png");
	addNewTexture("imgs/four.png");
	addNewTexture("imgs/five.png");
	addNewTexture("imgs/six.png");
	addNewTexture("imgs/seven.png");
	addNewTexture("imgs/eight.png");
	addNewTexture("imgs/nine.png");
}


DigitThree::~DigitThree()
{
}

void DigitThree::receiveMessage(Message msg)
{
	if (msg.getSender() == "ScoreTracker")
	{
		std::string strCurrentScore = msg.getContent();
		int intCurrentScore = atoi(strCurrentScore.c_str());
		std::cout << "Score: " << intCurrentScore << std::endl;
		if(intCurrentScore >= 53 ) {
            std::cout << "Hello\n";

		}
		for (int i = 1; i < 3; ++i)
		{
			intCurrentScore = intCurrentScore - (intCurrentScore % 10);
			intCurrentScore = intCurrentScore / 10;
		}

		setCurrentTexture(intCurrentScore % 10);
	}
}


Message DigitThree::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
	return Message();
}
Message DigitThree::react(sf::Event e) {
	return Message();

}
Message DigitThree::click() {
	return Message();

}
Message DigitThree::unclick() {
	return Message();

}



DigitFour::DigitFour() : DrawableWithPriority("DigitFour", "game", 16)
{
	setPosition(1150, 0);

	addNewTexture("imgs/zero.png");
	addNewTexture("imgs/one.png");
	addNewTexture("imgs/two.png");
	addNewTexture("imgs/three.png");
	addNewTexture("imgs/four.png");
	addNewTexture("imgs/five.png");
	addNewTexture("imgs/six.png");
	addNewTexture("imgs/seven.png");
	addNewTexture("imgs/eight.png");
	addNewTexture("imgs/nine.png");
}


DigitFour::~DigitFour()
{
}

void DigitFour::receiveMessage(Message msg)
{
	if (msg.getSender() == "ScoreTracker")
	{
		std::string strCurrentScore = msg.getContent();
		int intCurrentScore = atoi(strCurrentScore.c_str());
		for (int i = 1; i < 4; ++i)
		{
			intCurrentScore = intCurrentScore - (intCurrentScore % 10);
			intCurrentScore = intCurrentScore / 10;
		}

		setCurrentTexture(intCurrentScore % 10);
	}
}


Message DigitFour::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
	return Message();
}
Message DigitFour::react(sf::Event e) {
	return Message();

}
Message DigitFour::click() {
	return Message();

}
Message DigitFour::unclick() {
	return Message();

}



DigitFive::DigitFive() : DrawableWithPriority("DigitFive", "game", 17)
{
	setPosition(1125, 0);

	addNewTexture("imgs/zero.png");
	addNewTexture("imgs/one.png");
	addNewTexture("imgs/two.png");
	addNewTexture("imgs/three.png");
	addNewTexture("imgs/four.png");
	addNewTexture("imgs/five.png");
	addNewTexture("imgs/six.png");
	addNewTexture("imgs/seven.png");
	addNewTexture("imgs/eight.png");
	addNewTexture("imgs/nine.png");
}


DigitFive::~DigitFive()
{
}

void DigitFive::receiveMessage(Message msg)
{
	if (msg.getSender() == "ScoreTracker")
	{
		std::string strCurrentScore = msg.getContent();
		int intCurrentScore = atoi(strCurrentScore.c_str());
		for (int i = 1; i < 5; ++i)
		{
			intCurrentScore = intCurrentScore - (intCurrentScore % 10);
			intCurrentScore = intCurrentScore / 10;
		}

		setCurrentTexture(intCurrentScore % 10);
	}

}

Message DigitFive::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
	return Message();
}
Message DigitFive::react(sf::Event e) {
	return Message();

}
Message DigitFive::click() {
	return Message();

}
Message DigitFive::unclick() {
	return Message();


}
