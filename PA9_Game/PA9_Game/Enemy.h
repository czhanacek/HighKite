#pragma once
#define RIGHT 1
#define DOWN_R 2
#define DOWN_L 3
#define LEFT 4
#include <math.h>


class Enemy : public sf::Sprite
{
public:
	Enemy(float positionX, float positionY)
	{
		setPosition(positionX, positionY);
	}

	float getMovementSpeedHorizontal()
	{
		return movementSpeedHorizontal;
	}

	float getMovementSpeedDown()
	{
		return movementSpeedDown;
	}

	int getMovementTracker()
	{
		return movementTracker;
	}

	int getDirection()
	{
		return direction;
	}

	void setMovementTracker(int newTracker)
	{
		movementTracker = newTracker;
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

	virtual void movement() = 0;

private:
	float movementSpeedDown;
	float movementSpeedHorizontal;
	int movementTracker = 0;
	int direction;

};

class Bird : public Enemy
{
public:
	Bird(float positionX, float positionY): Enemy(positionX, positionY)
	{
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(0);
		setDirection(1);
	}

	~Bird()
	{
	}

	 void movement()  // birds will move only straight down for the time being 
	{	
		sf::Sprite::move(getMovementSpeedHorizontal(), getMovementSpeedDown());
	}

private:

};

class Eagle : public Enemy
{
public:
	Eagle(float positionX, float positionY) : Enemy(positionX, positionY)
	{
		setMovementSpeedDown(2);
		setMovementSpeedHorizontal(2);
		setDirection(1);
	}
	~Eagle()
	{}

	void movement()
	{
		
		sf::Sprite::move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

		angle++;
		if (angle % 180 == 0)
		{
			setDirection(getDirection() * -1);
		}
	}
private:
	int angle = 0;
};

class Seagull : public Enemy
{
public:
	Seagull(float positionX, float positionY) : Enemy(positionX, positionY) {
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(2);
		setDirection(1);
	}
	~Seagull(){}

	void movement()
	{
		if (fullRotation == false)
		{
			sf::Sprite::move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown());
			angle++;
		}
		else
		{
			sf::Sprite::move(0, getMovementSpeedDown());
		}

		
		if (angle == 360)
		{
			setMovementSpeedDown(4);
			fullRotation = true;
		}
		
	}
private:
	int angle = 0;
	bool fullRotation = false;
};

class ShootingStar : public Enemy
{
public:
	ShootingStar(float positionX, float positionY) : Enemy(positionX, positionY) {
		setMovementSpeedDown(1);
		setMovementSpeedHorizontal(2);
		setDirection(1);
	}
	~ShootingStar() {}

	void movement()
	{
		sf::Sprite::move(getMovementSpeedHorizontal(), getMovementSpeedDown());
	}
private:

};

class Nuke : public Enemy
{
public:
	Nuke(float positionX, float positionY) : Enemy(positionX, positionY) {
		setMovementSpeedDown(2);
		setMovementSpeedHorizontal(0);
		setDirection(1);
	}
	~Nuke() {}

	void movement()
	{
		//go to middle of screen then blow up
		if (this->getPosition().y < 330)
		{
			sf::Sprite::move(getMovementSpeedHorizontal(), getMovementSpeedDown());
			setMovementTracker(getMovementTracker() + 1);
		}

		
	}

private:
};

class Spaceship : public Enemy
{
public:
	Spaceship(float positionX, float positionY) : Enemy(positionX, positionY) {
		setMovementSpeedDown(3);
		setMovementSpeedHorizontal(5);
		setDirection(1);
	}
	~Spaceship() {}
	
	
	void movement()
	{

		sf::Sprite::move(cos(angle * 3.14159265358979323846 / 180) * getMovementSpeedHorizontal(), sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

		angle += 1;

		if (angle % 180 == 0)
		{
			setDirection(getDirection() * -1);
		}
	}

	int angle = 0;
	sf::Sprite bullet;
private:
	
};

class Projectile : public sf::RectangleShape
{
public:
	Projectile() :RectangleShape()
	{
		this->setFillColor(sf::Color::Green);
		this->setSize(sf::Vector2f(5, 5));
		this->setOutlineColor(sf::Color::Green);
		this->setOutlineThickness(1);
	}
private:

};

class Missile : public Enemy
{
public:
	Missile(float positionX, float positionY) : Enemy(positionX, positionY) {
		setMovementSpeedDown(2);
		setMovementSpeedHorizontal(3);
		setDirection(-1);
	}
	~Missile() {}

	void movement()
	{
		sf::Sprite::move(getMovementSpeedHorizontal(), getDirection()*getMovementSpeedDown());
	}
private:

};

class Football : public Enemy
{
public:
	Football(float positionX, float positionY) : Enemy(positionX, positionY)
	{
		setMovementSpeedDown(10);
		setMovementSpeedHorizontal(10);
		setDirection(-1);
		
	}
	~Football()
	{}

	void movement()
	{
		sf::Sprite::move(sin(angle * 3.14159265358979323846 / 180)*getMovementSpeedHorizontal() , cos(angle * 3.14159265358979323846 / 180)*getMovementSpeedDown() * getDirection());

		angle++;
		if (angle == 181)
		{
			setMovementSpeedDown(0);
			setMovementSpeedHorizontal(0);
		}
	}
private:
	int angle = 0;
};

