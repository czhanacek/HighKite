#pragma once

#include "DrawableWithPriority.h"

class Button : public DrawableWithPriority
{
    public:
        Button(std::string newName, std::string newContext, std::string unclickedFilename, std::string clickedFilename="", int xpos=0, int ypos=0);
        Message click(void);
        Message unclick(void);
        void receiveMessage(Message msg);
        ~Button();
        Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        Message react(sf::Event e);

    protected:
    private:
        bool movingUp, moveOverride;
        int originalX, originalY, bounceInterval, ticker, windspeed;

};


