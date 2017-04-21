#include "DrawableWithPriority.h"



class Cloud : public DrawableWithPriority {
    public:
        Cloud(std::string newName, std::string newContext);
        void update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        Message react(sf::Event e);
        void receiveMessage(Message msg);
        Message click();
        Message unclick();
    private:
        int peekInterval;
        bool movingOut;
        bool moving;

};
