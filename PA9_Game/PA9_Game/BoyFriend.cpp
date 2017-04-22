#include "BoyFriend.h"

BoyFriend::BoyFriend(std::string newName, std::string newContext, std::string filename) : DrawableWithPriority(newName, newContext, filename, 15) {
    setPosition(100, 400);
    addNewTexture("imgs/boy-bigmouth.gif");
    removeMe = false;
}

Message BoyFriend::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    int speed = 90;

    if(getContext() == "game") {
        if(clocks[0].getElapsedTime().asMilliseconds() >= 30) {
            setPosition(getPosition().x, getPosition().y + (speed / 30));
            clocks[0].restart();
        }

    }
    return Message();
}

Message BoyFriend::react(sf::Event e) {
    return Message();
}

void BoyFriend::receiveMessage(Message msg) {

}

Message BoyFriend::click() {
    return Message();
}

Message BoyFriend::unclick() {
    return Message();
}
