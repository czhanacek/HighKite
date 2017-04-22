#include "DrawableWithPriority.h"

class BoyFriend : public DrawableWithPriority {
    public:
        BoyFriend(std::string newName, std::string newContext, std::string filename);

        Message update(sf::Time totalElapsed, sf::Time sinceLastUpdate);
        Message react(sf::Event e);
        void receiveMessage(Message msg);
        Message click();
        Message unclick();
};
