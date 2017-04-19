#pragma once
#include "Message.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <SFML/Window/Keyboard.hpp>


class DrawableWithPriority : public sf::Sprite {
    public:
        DrawableWithPriority(std::string newName, std::string newContext, int newPriority);
        DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int newPriority);
        DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int newPriority);
        DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int newPriority);
        virtual void update(sf::Time t);
        virtual Message react(sf::Event e);
        virtual void receiveMessage(Message msg);
        virtual Message click();
        virtual Message unclick();
        std::string getName();
        std::string getContext();
        unsigned int getSizeX(void);
        unsigned int getSizeY(void);
        ~DrawableWithPriority();
        void setPriority(int newPriority);
        int getPriority(void) const;
        std::vector<sf::Texture * > spriteTextures;
        int addNewTexture(std::string filename);
    private:
        int priority;
        std::string name;
        std::string context;

};


bool operator> (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
bool operator< (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator>= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator<= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
