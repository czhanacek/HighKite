#include "DrawableWithPriority.h"

class Leaf : public DrawableWithPriority {
    public:
        Leaf(std::string newContext);
        virtual void update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        virtual Message react(sf::Event e);
        virtual void receiveMessage(Message msg);
        virtual Message click();
        virtual Message unclick();


};
