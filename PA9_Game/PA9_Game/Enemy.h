#pragma once

#include "DrawableWithPriority.h"

#include <math.h>
// Last updated: 4-25-17, 7:13

// The idea behind the enemy class is that it has common attributes that will be shared among all the enemies:
// horizontal/vertical speed,  and its direction
// all these values have appropriate setters and getter
// All enemies are based off the DrawableWithPriority class

class Enemy : public DrawableWithPriority
{
public:
	Enemy(std::string newName, std::string newContext, int newPriority) :DrawableWithPriority(newName, newContext, newPriority)
	{
		setEnemyStatus(true);
	}
	// The enemy's speeds and directions will be set in its constructor. However, they can be modified in update()

	float getMovementSpeedHorizontal()
	{
		return movementSpeedHorizontal;
	}

	float getMovementSpeedDown()
	{
		return movementSpeedDown;
	}

	int getDirection()
	{
		return direction;
	}

	void setMovementSpeedHorizontal(float newSpeed)
	{
		movementSpeedHorizontal = newSpeed;
	}

	void setMovementSpeedDown(float newSpeed)
	{
		movementSpeedDown = newSpeed;
	}

	void setDirection(int newDirection)
	{
		direction = newDirection;
	}
    bool startScream = false;
	//All enemies will have an overriden update() function


private:
	float movementSpeedDown;
	float movementSpeedHorizontal;
	int direction;

};

// The bird moves diagonally, it is a very basic enemy
class Bird : public Enemy //FINAL
{
public:

	Bird(std::string newName, std::string newContext) :Enemy("Bird", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewSound("sounds/hawkscream.ogg");
		addNewTexture("imgs/bird-1.png");
		addNewTexture("imgs/bird-1-flipped.png");
		addNewTexture("imgs/bird-2.png");
		addNewTexture("imgs/bird-2-flipped.png");
		addNewTexture("imgs/bird-3.png");
		addNewTexture("imgs/bird-3-flipped.png");
		addNewTexture("imgs/bird-4.png");
		addNewTexture("imgs/bird-4-flipped.png");
		addNewTexture("imgs/bird-5.png");
		addNewTexture("imgs/bird-5-flipped.png");
		addNewTexture("imgs/bird-6.png");
		addNewTexture("imgs/bird-6-flipped.png");
		addNewTexture("imgs/bird-7.png");
		addNewTexture("imgs/bird-7-flipped.png");
		addNewTexture("imgs/bird-8.png");
		addNewTexture("imgs/bird-8-flipped.png");
		numberOfTextureSets = 2;
		setCurrentTexture(0);
		setMovementSpeedDown(3);
		setMovementSpeedHorizontal(4 * pow(-1, rand() % 3));

		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(-1 * rand() % 400, -500);
		//setPosition(100, 100);

		clocks.push_back(sf::Clock());
	}

	~Bird()
	{
	}

	Message update(sf::Time t, sf::Time y)  // birds will move only straight down for the time being
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 20) {
			move(getMovementSpeedHorizontal(), getMovementSpeedDown());
			currentFrame++;
			if (getMovementSpeedHorizontal() > 0) {
				textureOffset = 0;

			}
			else {
				textureOffset = 1;
			}
			setCurrentTexture((currentFrame * numberOfTextureSets) + textureOffset);
			clocks[0].restart();
		}

		return Message();
	}
   Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
        if(msg.getSender() == getName() && msg.getContent() == "collided," + signature)
        {
            setColor(sf::Color(255,0,0,200));
            move(0,25);
            if(!startScream)
            {
                startScream = true;
                playSound(0);
            }
        }

    }


    Message click()
    {
        return Message();
   }

    Message unclick()
    {
        return Message();
   }

private:

};

// Like the Bird, Eagle will move downwards but it will go down in a sine-like path, hence the need
// for an angle data member
class Eagle : public Enemy  //FINAL
{
public:
	Eagle(std::string newName, std::string newContext) : Enemy("Eagle", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewTexture("imgs/eagle.png");
		addNewTexture("imgs/eagle-flipped.png");
		setCurrentTexture(0);
		setMovementSpeedDown(5);
		setMovementSpeedHorizontal(5);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x) + this->spriteTextures[0]->getSize().x), -500);

		clocks.push_back(sf::Clock());
	}

	~Eagle()
	{}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)  // birds will move only straight down for the time being
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

			angle++;
			if (angle % 180 == 0)  // THis check ensures the Eagle keeps moving down and doesn't get stuck in an eternal circle loop
			{
				setDirection(getDirection()*-1);
				setCurrentTexture(getCurrentTextureIndex() + 1);
			}

			clocks[0].restart();
		}
		return Message();
	}
   Message react(sf::Event e)
   {
        return Message();
   }

   void receiveMessage(Message msg)
    {
        if(msg.getSender() == getName() && msg.getContent() == "collided," + signature)
        {
            setColor(sf::Color(255,0,0,200));
            move(0,25);
            if(!startScream)
            {
                startScream = true;
                playSound(0);
            }
        }

    }
    Message click()
    {
    return Message();
   }

    Message unclick()
    {
        return Message();
   }
private:
	int angle = rand() % 180;
};


//The seagull first goes in a circle and divebombs straight downwards, hence the need for the angle data member again
class Seagull : public Enemy
{
public:
	Seagull(std::string newName, std::string newContext) :Enemy("Seagull", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewTexture("imgs/seagull.png");
		addNewTexture("imgs/seagull-flipped.png");
		setCurrentTexture(0);
		setMovementSpeedDown(7);
		setMovementSpeedHorizontal(5);
		setDirection(1);
		//set scale and position
		double prelim = rand() % 50 + 35;
		double seagullSize = (prelim / 100.0);
		setScale(seagullSize, seagullSize);
		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x)) + this->spriteTextures[0]->getSize().x, -500);

		clocks.push_back(sf::Clock());
	}

	~Seagull() {}

	Message update(sf::Time blah1, sf::Time blah2)
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			if (fullRotation == false)  // we move in a circle until the seagull has gone in a circle
			{
				move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown());
				setRotation(getRotation() + 1);

				angle++;
			}
			else  // DIVEBOMB!
			{
				move(0, getMovementSpeedDown());
			}
			if (angle > 180) {
				setCurrentTexture(1);
			}
			if (angle == 360)  //we set fullRotation to true if angle = 360 ie when the seagull has gone around in a full circle
			{
				setMovementSpeedDown(4);

				fullRotation = true;
			}
			clocks[0].restart();
		}

		return Message();

	}
	  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
        if(msg.getSender() == getName() && msg.getContent() == "collided," + signature)
        {
            setColor(sf::Color(255,0,0,200));
            move(0,25);
            if(!startScream)
            {
                startScream = true;
                playSound(0);
            }
        }

    }
    Message click()
    {
        return Message();
   }

    Message unclick()
    {
        return Message();
   }
private:
	int angle = 0;
	bool fullRotation = false;
	bool divebomb = false;
};


//Stereotypically, stars are depicted as traveling in a diagonal manner, coming in from a corner of a page, picture, video etc.
//hence our ShootingStar will do the same
class ShootingStar : public Enemy
{
public:

	ShootingStar(std::string newName, std::string newContext) :Enemy("ShootingStar", "game", 15)
	{
		int speed = rand() % 6 + 2;
		// use addNewTexture() to add texture to this enemy and add to texture vector
		setMovementSpeedDown(speed);
		setMovementSpeedHorizontal(3);
		//set scale and position
		setScale(0.35, 0.35);
		// The star should span from either of the top corners
		// Depending on the corner from which it spans, the star will either travel to the bottom left or bottom right corner
		if (rand() % 2 == 1)
		{
			setPosition(-50, -50 + (rand() % 11 - 10));  //coming in from top left
			setDirection(1);
			addNewTexture("imgs/shootingStar-2.png");
			setCurrentTexture(0);
		}
		else
		{
			setPosition(1330, -50 + (rand() % 11 - 10));  //coming in from top right
			setDirection(-1);
			addNewTexture("imgs/shootingStar-1.png");
			setCurrentTexture(0);
		}
		clocks.push_back(sf::Clock());
	}

	~ShootingStar() {}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			move(getDirection()*getMovementSpeedHorizontal(), getMovementSpeedDown());
			clocks[0].restart();
		}
		return Message();
	}
  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
        return Message();
   }

    Message unclick()
    {
        return Message();
   }
private:

};


//THe nuke should travel to the middle of the screen and explode once it is at the middle
// The player will never see it coming!
class Nuke : public Enemy
{
public:

	Nuke(std::string newName, std::string newContext) :Enemy("Nuke", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewTexture("imgs/nuke-1.png");
		addNewTexture("imgs/nuke-2.png");
		setCurrentTexture(0);
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(0);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x) + this->spriteTextures[0]->getSize().x), -500);
		clocks.push_back(sf::Clock());
	}

	~Nuke() {}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		//go to middle of screen then blow up
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			move(getMovementSpeedHorizontal(), getMovementSpeedDown());
			clocks[0].restart();
		}
		if (this->getPosition().y >= 450)
		{
			//when the nuke "blows" up, it should change it animation to an explosion
			if (!blownUp)
			{
				setCurrentTexture(1);
				setScale(2,2);
				blownUp = true;
			}
			// BLOW UP!
		}
		return Message();
	}
	  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
        return Message();
   }

    Message unclick()
    {
       return Message();
   }

private:
	bool blownUp= false;
};


//The spaceship should travel downwards like the eagle did, in a sine path, while shooting beams at certain intervals
class Spaceship : public Enemy
{
public:

	Spaceship(std::string newName, std::string newContext) :Enemy("Spaceship", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewTexture("imgs/spaceship-1.png");
		addNewTexture("imgs/spaceship-2.png");
		setCurrentTexture(0);
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(2);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);

		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x) + this->spriteTextures[0]->getSize().x), -500);
		clocks.push_back(sf::Clock());
	}

	~Spaceship() {}


	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			//The Spaceship will move downwards in a Sine Path, hence the need for cos() and sin()
			move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

			angle++;
			if (angle % 180 == 0)
			{
				setDirection(getDirection()*-1);
				if (angle % 360 == 0)
				{
					setCurrentTexture(0);
				}
				else
				{
					setCurrentTexture(1);
				}
			}

			clocks[0].restart();
		}
		//if (clocks[1].getElapsedTime().asSeconds() == 2) { //For now, the Spaceship will only shoot at every 2 seconds
		//		// Shoot!
		//		clocks[1].restart();
		//}
		return Message();
	}
  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
       return Message();
   }

    Message unclick()
    {
        return Message();
   }
private:
	int angle = rand() % 360;
};

// The missile will travel the opposite of how the ShootingStar did;
//It will come from one of the bottom corners and go towards the opposite corner
class Missile : public Enemy
{
public:
	int speed = 0;
	Missile(std::string newName, std::string newContext) :Enemy("Missile", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		speed = rand() % 5 + 1;
		setMovementSpeedHorizontal(2);
		setDirection(-1);
		//set scale and position
		setPosition(-50, 770 + (rand() % 11 - 10));

		// The Missile should span from either of the bottom corners
		// Depending on the corner from which it spans, the Missile will either travel to the top left or top right corner
		if (rand() % 2 == 1)
		{
			setPosition(-50, 770 + (rand() % 11 - 10));		//Travel to the top right corner
			setMovementSpeedDown(-speed);
			setDirection(1);
			addNewTexture("imgs/missile-left-1.png");
			addNewTexture("imgs/missile-left-2.png");
			addNewTexture("imgs/missile-left-3.png");
			setCurrentTexture(0);
		}
		else
		{
			setPosition(1330, 770 + (rand() % 11 - 10));	//Travel to the top Left corner
			setMovementSpeedDown(-speed);
			setDirection(-1);
			addNewTexture("imgs/missile-right-1.png");
			addNewTexture("imgs/missile-right-2.png");
			addNewTexture("imgs/missile-right-3.png");
			setCurrentTexture(0);
		}
		clocks.push_back(sf::Clock());
	}

	~Missile() {}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			move(getDirection()* getMovementSpeedHorizontal(), getMovementSpeedDown());
			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() >= 30) {
			setCurrentTexture(rand() % 3);
			clocks[1].restart();
		}

		return Message();
	}

	  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
       return Message();
   }

    Message unclick()
    {
        return Message();
   }
private:

};


// THe football will travel in a semisphere path, going from the bottom corner to the other bottom corner
class Football : public Enemy
{
public:
	Football(std::string newName, std::string newContext) :Enemy("Football", "game", 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewTexture("imgs/football-1.png");
		addNewTexture("imgs/football-2.png");
		setCurrentTexture(0);
		setMovementSpeedDown(6);

		setDirection(-1);
		//set scale and position
		setScale(0.35, 0.35);
		if (rand() % 2 == 1)
		{
			setPosition(-50, 650 + (rand() % 11 - 10));
			setMovementSpeedHorizontal(8);
		}
		else
		{
			setPosition(1320, 650 + (rand() % 11 - 10));
			setMovementSpeedHorizontal(-8);
		}
		clocks.push_back(sf::Clock());
	}

	~Football()
	{}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		//The football should travel a semisphere path on screen
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {
			move(sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedHorizontal(), cos(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

			angle++;
			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() >= 300) {
			setCurrentTexture(rand() % 2);
			setRotation(getRotation() + 5);
			clocks[1].restart();

		}
		if (angle >= 200)
		{
		setPosition(-50, 1500);
		}
		return Message();
	}

	  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
        return Message();
   }

    Message unclick()
    {
        return Message();
   }
private:
	int angle = 0;
};

// The way the Mothership works is by passing in the address of the kite, and then the Mothership is able to check periodically where
// the kite is, and it is able to follow it
// We shoot beams at the kite every few intervals and then divebomb when we are close enough to the Kite's X coordinate
class Mothership : public Enemy
{
private:
	int amountShot = 0;
	bool divebomb = false;
	DrawableWithPriority* Target;
public:

	Mothership(std::string newName, std::string newContext, DrawableWithPriority* newTarget) : Enemy(newName, newContext, 15)
	{
		Target = newTarget; //Now we can keep track of where the kite is
							// use addNewTexture() to add texture to this enemy and add to texture vector
		addNewTexture("imgs/spaceship-1.png");
		addNewTexture("imgs/spaceship-2.png");
		setCurrentTexture(0);
		setMovementSpeedDown(0);
		setMovementSpeedHorizontal(2);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(-50, 30);
		clocks.push_back(sf::Clock());
		clocks.push_back(sf::Clock());
		clocks.push_back(sf::Clock());
		clocks.push_back(sf::Clock());


	}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 30) {  //Move every 30 milliseconds
			move(getDirection()*getMovementSpeedHorizontal(), getMovementSpeedDown());
			clocks[0].restart();
		}

		// Here we check whether to divebomb or to keep following the kite
		if (clocks[1].getElapsedTime().asMilliseconds() >= 500 && divebomb && getMovementSpeedDown() != 4) {
			//We enter this if statement once we have shot 5 times
			//We do the getMovementSpeedDown check so that we dont check once the spaceship is dive bombing
			// Once we are divebombing, there is no moving horizontally
			if (abs(this->getPosition().x - Target->getPosition().x) < 10)
			{
				//We divebomb as soon as the mothership's X coordinate is 10 away from the kite's X coordinate
				setDirection(0);
				setMovementSpeedDown(5);
			}
			clocks[1].restart();
		}

		if (clocks[2].getElapsedTime().asSeconds() >= 2 && !divebomb) {
			//Here we check if we are still following the kite
			if (this->getPosition().x < Target->getPosition().x && getDirection() != 1) //Kite is to right of Mothership
			{
				setCurrentTexture(0);
				setDirection(1);
			}
			else if (this->getPosition().x > Target->getPosition().x && getDirection() != -1) //Kite is to left of Mothership
			{
				setCurrentTexture(1);
				setDirection(-1);
			}
			else //Mothership is directly above kite
			{
				setDirection(0);
			}
			clocks[2].restart();
		}

		if (clocks[3].getElapsedTime().asSeconds() >= 7) {
			////Shoot!
			//amountShot++;
			//if (amountShot >= 5)
			//{
			divebomb = true;
			//	setMovementSpeedDown(6);
			//}
			//clocks[3].restart();
			////Maybe look into shootingg instead when ship is really close to kite?
		}

		if (this->getPosition().x < 1)
		{
			setPosition(getSizeX(), this->getPosition().y);
		}
		else if (this->getPosition().x > 1279)
		{
			setPosition(1279 - getSizeX(), this->getPosition().y);
		}
		return Message();
	}
	  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
       return Message();
   }

    Message unclick()
    {
        return Message();
   }
};

class Andy : public Enemy
{
public:
	Andy(std::string newName, std::string newContext) : Enemy(newName, newContext, 15)
	{
		addNewTexture("imgs/andrew.png");
		setScale(.35, .35);
		setCurrentTexture(0);
		setMovementSpeedDown(0);
		setMovementSpeedHorizontal(10);
		setOrigin(-60, 30);
		setPosition(-60, 30);
		clocks.push_back(sf::Clock());
		setDirection(1);
	}
	~Andy() {}

	Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate)
	{
		if (clocks[0].getElapsedTime().asMilliseconds() >= 1500)
		{
			setPosition(rand() % 1250 + 10, rand() % 680 + 10);
			setRotation(rand() %360);
			clocks[0].restart();
		}
		if (this->getPosition().x >= 300 || this->getPosition().x <= -100)
		{
			setDirection(getDirection()*-1);
		}

		return Message();
	}
	  Message react(sf::Event e)
   {
        return Message();
   }

    void receiveMessage(Message msg)
    {
    }
    Message click()
    {
        return Message();
   }

    Message unclick()
    {
        return Message();
   }
};
