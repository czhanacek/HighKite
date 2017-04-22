#pragma once

#include "KiteObj.h"


KiteObj::KiteObj() : DrawableWithPriority("Kite", "game", 50)
{

    addNewTexture("imgs/orange.jpg");
    setCurrentTexture(0);
    setScale(0.25, 0.25);
    setPosition(640, 600);

}

KiteObj::~KiteObj()
{

}

void KiteObj::update(sf::Time t)
{


}
Message KiteObj::react(sf::Event e)
{

}

void KiteObj::receiveMessage(Message msg)
{

}

Message KiteObj::click()
{

}

Message KiteObj::unclick()
{

}
