#include "DrawableWithPriority.h"

class Leaf : public DrawableWithPriority {
    public:
        Leaf(std::string newContext);
        Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        Message react(sf::Event e);
        void receiveMessage(Message msg);
        Message click();
        Message unclick();
    private:
        int stoppingPlace;
        int windspeed;

};
