#include <iostream>
#include "DrawableWithPriority.h"


class KiteObj : public DrawableWithPriority
{

public:
    KiteObj();
    ~KiteObj();
    virtual void update(sf::Time t);
    virtual Message react(sf::Event e);
    virtual void receiveMessage(Message msg);
    virtual Message click();
    virtual Message unclick();

private:

};
