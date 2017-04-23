#pragma once
#include "KiteObj.h"

KiteObj::KiteObj() : DrawableWithPriority("Kite", "game", 50)
{
    mXPos = 640;
    mYPos = 300;
    mXVelocity = 0;
    mYVelocity = 0;
    mAngle = 0.0;
    addNewTexture("imgs/orange.jpg");
    setCurrentTexture(0);
    setScale(0.25, 0.25);
    setPosition(640, 300);
}

KiteObj::~KiteObj()
{

}

Message KiteObj::update(sf::Time t, sf::Time y)
{
    setPosition(getPosition().x + mXVelocity, 300 - mYVelocity);

    return Message();
}

Message KiteObj::react(sf::Event e)
{
    return Message();
}

void KiteObj::receiveMessage(Message msg)
{
    if(msg.getSender() == "gamewrapper"){
        if(msg.getContent() == "L pressed"){
            // This line will max out the xVelocity
            if(mXVelocity < 3){
            std::cout << "Velocity increased in POSITIVE x" << std::endl;
                mXVelocity++;
            }
        }
        else if(msg.getContent() == "S pressed"){
            // This line will max out the xVelocity
            if(mXVelocity > -3){
            std::cout << "Velocity increased in NEGATIVE x" << std::endl;
                mXVelocity--;
            }
        }
        else if(msg.getContent() == "L released"){
        }
        else if(msg.getContent() == "S released"){
        }
    }
    keepInBounds();
}

Message KiteObj::click()
{

}

Message KiteObj::unclick()
{

}

void KiteObj::keepInBounds(){
    if(getPosition().x < 1){
        mXVelocity = 0;
        setPosition(1, getPosition().y);
        std::cout << "Reached Left edge!" << std::endl;
    }
    else if(getPosition().x + getSizeX() > 1279){

        mXVelocity = 0;
        setPosition(1279 - getSizeX(), getPosition().y);
        std::cout << "Reached Right edge!" << std::endl;
    }
}
