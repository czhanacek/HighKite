#pragma once

#include "DrawableWithPriority.h"

#include <math.h>

// The idea behind the enemy class is that it has common attributes that will be shared among all the enemies:
// horizontal/vertical speed,  and its direction
// all these values have appropriate setters and getter

class Enemy : public DrawableWithPriority
{
public:
	Enemy(std::string newName, std::string newContext, std::string filename, int x, int y, int newPriority) : DrawableWithPriority(newName, newContext, filename, x, y, newPriority)
	{
        setEnemyStatus(true);
	}

	Enemy(std::string newName, std::string newContext, int newPriority) :DrawableWithPriority(newName, newContext, newPriority)
	{
        setEnemyStatus(true);
	}

	Enemy(std::string newName, std::string newContext, std::string filename, int newPriority) :DrawableWithPriority(newName, newContext, filename, newPriority)
	{
        setEnemyStatus(true);
	}

	Enemy(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int newPriority) :DrawableWithPriority(newName, newContext, filename, x, y, iPosX, iPosY, newPriority)
	{
        setEnemyStatus(true);
	}


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

	//replace movement with an overriden update()


private:
	float movementSpeedDown;
	float movementSpeedHorizontal;
	int direction;

};


// Bird only goes striaght down, the most basic of enemies!
class Bird : public Enemy
{
public:

	Bird(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
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
			if(getMovementSpeedHorizontal() > 0) {
			    textureOffset = 0;

			}
			else {
                textureOffset = 1;
			}
			setCurrentTexture((currentFrame * numberOfTextureSets) + textureOffset);
			//setCurrentTexture(getCurrentTextureIndex() + 1);
			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() >= 500) {
			// Update Animation
			clocks[1].restart();
		}
		return Message();
	}

private:

};

// Like the Bird, Eagle will move downwards but it will go down in a sine-like path, hence the need
// for a angle data member
class Eagle : public Enemy
{
public:
	Eagle(std::string newName, std::string newContext) : Enemy(newName, newContext, 15)
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
			if (angle % 180 == 0)
			{
				setDirection(getDirection()*-1);
				setCurrentTexture(getCurrentTextureIndex() + 1);
			}

			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() >= 100) {
			// Update Animation
			setRotation((getRotation() + 1) *-1);
			clocks[1].restart();
		}
		return Message();
	}

private:
	int angle = rand() % 180;
};


//The seagull first goes in a circle and divebombs straight downwards, hence the need for the angle data member again
class Seagull : public Enemy
{
public:
	Seagull(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
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
		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x) + this->spriteTextures[0]->getSize().x), -500);
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
            if(angle > 180) {
                setCurrentTexture(1);

            }
			if (angle == 360)  //we set fullRotation to true if angle = 360 ie when the seagull has gone around in a full circle
			{
				setMovementSpeedDown(4);

				fullRotation = true;
			}
			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() >= 500) {
			// Update animation
			clocks[1].restart();
		}
        return Message();
	}
private:
	int angle = 0;
	bool fullRotation = false;
};


//Stereotypically, stars are depicted as traveling in a diagonal manner, coming in from a corner og a page, picture, etc.
//hence our ShootingStar will do the same
class ShootingStar : public Enemy
{
public:

	ShootingStar(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(3);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(-50, -50 + ( rand() % 11 - 10));
		clocks.push_back(sf::Clock());
	}

	~ShootingStar() {}

	void update()
	{
			if (clocks[0].getElapsedTime().asMilliseconds() == 100) {
				sf::Sprite::move(getMovementSpeedHorizontal(), getMovementSpeedDown());
				clocks[0].restart();
			}
			if (clocks[1].getElapsedTime().asMilliseconds() == 100) {
				this->setRotation(getRotation() + 1);
				clocks[1].restart();
			}

	}
private:

};


//THe nuke should travel to the middle of the screen and explode once it is at the middle
class Nuke : public Enemy
{
public:

	Nuke(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(0);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x) + this->spriteTextures[0]->getSize().x), 50);
		clocks.push_back(sf::Clock());
	}

	~Nuke() {}

	void update()
	{
		//go to middle of screen then blow up
		if (clocks[0].getElapsedTime().asMilliseconds() == 100) {
			sf::Sprite::move(getMovementSpeedHorizontal(), getMovementSpeedDown());
			clocks[0].restart();
		}
		if (this->getPosition().y == 600)
		{
			// BLOW UP!
		}

	}

private:
};


//The spaceship should travel downwards like the eagle did, in a sine path, while shooting beams at certain intervals
class Spaceship : public Enemy
{
public:

	Spaceship(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		setCurrentTexture(0);
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(1);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(rand() % (1280 - 2 * (this->spriteTextures[0]->getSize().x) + this->spriteTextures[0]->getSize().x), -50);
		clocks.push_back(sf::Clock());
	}

	~Spaceship() {}


	void update()  // birds will move only straight down for the time being
	{
		if (clocks[0].getElapsedTime().asMilliseconds() == 100) {
				sf::Sprite::move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

				angle++;
				if (angle % 180 == 0)
				{
					setDirection(getDirection()*-1);
				}

				clocks[0].restart();
			}
		if (clocks[1].getElapsedTime().asSeconds() == 3) {
				// Shoot!
				clocks[1].restart();
		}
	}

private:
	int angle = 0;
};

// The missile will travel the opposite of how the ShootingStar did;
//It will come from one of the bottom corners and go towards the opposite corner
class Missile : public Enemy
{
public:

	Missile(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(2);
		setDirection(-1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(-50, 770 + (rand() % 11 - 10));
		clocks.push_back(sf::Clock());
	}

	~Missile() {}

	void update()
	{
		if (clocks[0].getElapsedTime().asMilliseconds() == 100) {
			sf::Sprite::move(getDirection()* getMovementSpeedHorizontal(), getDirection()*getMovementSpeedDown());
			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() == 100) {
		// change animation
			clocks[1].restart();
		}

	}
private:

};


// THe football will travel in a semisphere path, going from the bottom corner to the other bottom corner
class Football : public Enemy
{
public:
	Football(std::string newName, std::string newContext) :Enemy(newName, newContext, 15)
	{
		// use addNewTexture() to add texture to this enemy and add to texture vector
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(1);
		setDirection(1);
		//set scale and position
		setScale(0.35, 0.35);
		setPosition(-50, 650 + (rand() % 11 - 10));
		clocks.push_back(sf::Clock());
	}

	~Football()
	{}

	void update()
	{
		if (clocks[0].getElapsedTime().asMilliseconds() == 100) {
		sf::Sprite::move(sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedHorizontal(), cos(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

			angle++;
			if (angle == 181)
			{
				//Not sure what to do here
			}
			clocks[0].restart();
		}
		if (clocks[1].getElapsedTime().asMilliseconds() == 500) {
			//Update Animation
			clocks[1].restart();

		}
	}
private:
	int angle = 0;
};

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
		addNewTexture("imgs/button.jpg");
		setCurrentTexture(0);
		setMovementSpeedDown(2);
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
	    move(getMovementSpeedHorizontal(), getMovementSpeedDown());
		if (clocks[0].getElapsedTime().asMilliseconds() >= 100) {  //Movement
			if (divebomb && getMovementSpeedDown() != 4)
			{
				if (abs(this->getPosition().x - Target->getPosition().x) < 10)
				{
					setDirection(0);
					setMovementSpeedDown(4);
				}
				clocks[0].restart();
			}
		}

		if (clocks[1].getElapsedTime().asSeconds() >= 2 && !divebomb) {
				if (this->getPosition().x < Target->getPosition().x && getDirection() != 1) //Kite is to right of Mothership
				{
					setDirection(1);
				}
				else if (this->getPosition().x > Target->getPosition().x && getDirection() != -1) //Kite is to left of Mothership
				{
					setDirection(-1);
				}
				else //Mothership is directly above kite
				{
					setDirection(0);
				}
				clocks[1].restart();
		}

		if (clocks[2].getElapsedTime().asSeconds() >= 3 && !divebomb) {
				//Shoot!
				amountShot++;
				if (amountShot >= 5)
				{
				    divebomb = true;
					setMovementSpeedDown(6);
				}
				clocks[2].restart();
				//Maybe look into shootingg instead when ship is really close to kite?
		}

		if (clocks[3].getElapsedTime().asMilliseconds() >= 500) {
				//Update amnimation
				clocks[3].restart();
		}
        return Message();
	}
};
