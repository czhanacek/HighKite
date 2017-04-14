#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Window/Keyboard.hpp>


class DrawableWithPriority : public sf::Sprite {
    public:
        DrawableWithPriority(int newPriority);
        ~DrawableWithPriority();
        void setPriority(int newPriority);
        int getPriority(void) const;
    private:
        int priority;
};


bool operator> (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
bool operator< (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator>= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
//bool operator<= (const DrawableWithPriority &d1, const DrawableWithPriority &d2);
