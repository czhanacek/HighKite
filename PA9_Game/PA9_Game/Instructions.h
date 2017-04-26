#include "DrawableWithPriority.h"


class Instructions : public DrawableWithPriority {
public:
    Instructions(std::string newName, std::string newContext, int x, int y);
    Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
    Message react(sf::Event e);
    void receiveMessage(Message msg);
    Message click();
    Message unclick();

};
