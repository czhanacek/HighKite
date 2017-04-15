#pragma once

#include "DrawableWithPriority.h"






class Button : public DrawableWithPriority
{
    public:
        Button(std::string unclickedFilename, std::string clickedFilename="", int xpos=0, int ypos=0);
        void click(void);
        void unclick(void);
        virtual ~Button();
    protected:
    private:
};


