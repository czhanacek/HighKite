#pragma once
#include "KiteObj.h"

KiteObj::KiteObj() : DrawableWithPriority("Kite", "game", 50)
{
    mXVelocity = 0;
    mYVelocity = 0;
    mAngle = 0.0;
    setContext("mainmenu");
    removeMe = false;
    addNewTexture("imgs/kite1.png");
    addNewTexture("imgs/kite2.png");
    addNewTexture("imgs/kite3.png");
    addNewTexture("imgs/kite4.png");
    addNewTexture("imgs/kite5.png");
    setCurrentTexture(0);
    setScale(0.17, 0.17);
    setPosition(775, 113);

    clocks.push_back(sf::Clock());
}

KiteObj::~KiteObj()
{
}

Message KiteObj::update(sf::Time t, sf::Time y)
{
    std::cout << clocks[1].getElapsedTime().asSeconds() << std::endl;
    // This will generate some random rotation on the kite

    if(clocks[0].getElapsedTime().asMilliseconds() % 60 == 0){
        clocks[0].restart();
        setCurrentTexture(getCurrentTextureIndex() + rand() % spriteTextures.size());
        DrawableWithPriority::setRotation(rand() % 6 - 3 + mXVelocity);

    }
    // This stops the kite after it's gotten into position for the menu start
    if(getPosition().y == 449){
        mYVelocity = 0;
        mXVelocity = 0;
        setPosition(getPosition().x, 450);
    }

    move(mXVelocity, mYVelocity);

    return Message();
}

Message KiteObj::react(sf::Event e)
{
    return Message();
}

void KiteObj::receiveMessage(Message msg)
{
    if(msg.getSender() == "gamewrapper"){
        if(mXVelocity == 0){
            clocks[0].restart();
        }
        if(msg.getContent() == "L pressed"){
            // This line will max out the xVelocity

            if(mXVelocity < 5){
            std::cout << "Velocity increased in POSITIVE x" << std::endl;
                mXVelocity = 5;
            }
        }
        else if(msg.getContent() == "L pressed but S held"){

        }
        else if(msg.getContent() == "S pressed"){
            // This line will max out the xVelocity
            if(mXVelocity > -5){
            std::cout << "Velocity increased in NEGATIVE x" << std::endl;
                mXVelocity = -5;
            }
        }
        else if(msg.getContent() == "S pressed but L held"){

        }
        else if(msg.getContent() == "L released"){
            mXVelocity = 0;
        }
        else if(msg.getContent() == "L released but S held"){

        }
        else if(msg.getContent() == "S released"){
            mXVelocity = 0;
        }
        else if(msg.getContent() == "S released but L held"){

        }
        else if(msg.getContent() == "Game started"){
            mYVelocity = 1;
            mXVelocity = -1;
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
