#include <iostream>
#include "DrawableWithPriority.h"


class KiteObj : public DrawableWithPriority
{

public:
    KiteObj();
    ~KiteObj();
    virtual Message update(sf::Time t, sf::Time y);
    virtual Message react(sf::Event e);
    virtual void receiveMessage(Message msg);
    virtual Message click();
    virtual Message unclick();
    void keepInBounds();

private:
    int mXPos;
    int mYPos;
    int mXVelocity;
    int mYVelocity;
    float mAngle;

};
