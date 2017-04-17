#pragma once

#include "DrawableWithPriority.h"






class Button : public DrawableWithPriority
{
    public:
        Button(std::string newName, std::string unclickedFilename, std::string clickedFilename="", int xpos=0, int ypos=0);
        Message click(void);
        Message unclick(void);
        void receiveMessage(Message msg);
        virtual ~Button();
    protected:
    private:
};


