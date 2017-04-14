#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <SFML/Window/Keyboard.hpp>


class DrawableWithPriority : public sf::Sprite {
    public:
        DrawableWithPriority(int newPriority);
        DrawableWithPriority(std::string filename, int x, int y, int newPriority);
        DrawableWithPriority(std::string filename, int x, int y, int iPosX, int iPosY, int newPriority);
        virtual void update(sf::Time t);
        virtual void react(sf::Event e);
        ~DrawableWithPriority();
        void setPriority(int newPriority);
        int getPriority(void) const;
        std::vector<sf::Texture * > spriteTextures;
    private:
        int priority;

};


bool operator> (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
bool operator< (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator>= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator<= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
