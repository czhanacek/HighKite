#include "DrawableWithPriority.h"

class Boy : public DrawableWithPriority {
    public:
        Boy(std::string newName, std::string newContext, std::string filename);

        void update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        Message react(sf::Event e);
        void receiveMessage(Message msg);
        Message click();
        Message unclick();
};
