#pragma once
#include "Message.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <string>
#include <SFML/Window/Keyboard.hpp>


class DrawableWithPriority : public sf::Sprite {
    public:
        DrawableWithPriority(std::string newName, std::string newContext, int newPriority);
        DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int newPriority);
        DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int newPriority);
        DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int newPriority);


        virtual Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        virtual Message react(sf::Event e);
        virtual void receiveMessage(Message msg);
        virtual Message click();
        virtual Message unclick();
        std::string getName();
        std::string getContext();
        void setContext(std::string newContext);
        unsigned int getSizeX(void);
        unsigned int getSizeY(void);
        ~DrawableWithPriority();
        void setPriority(int newPriority);
        int getPriority(void) const;
        std::vector<sf::Texture * > spriteTextures;
        std::vector<sf::SoundBuffer *> sounds;
        sf::Sound soundplayer;
        //int32_t millisecondsSinceLastUpdate;
        std::vector<sf::Clock> clocks;
        bool removeMe;
        int addNewTexture(std::string filename);
        int addNewSound(std::string filename);
        void playSound(int index);
        int getCurrentSoundIndex(void);
        int getCurrentTextureIndex(void);
        void setCurrentTexture(int index);


    private:
        int priority;

        std::string name;
        std::string context;
        int currentSoundIndex;
        int currentTextureIndex;

};


bool operator> (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
bool operator< (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator>= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator<= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
