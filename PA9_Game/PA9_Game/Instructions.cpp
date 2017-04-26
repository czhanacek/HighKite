#include "Instructions.h"


Instructions::Instructions(std::string newName, std::string newContext, int x, int y) : DrawableWithPriority(newName, newContext, 35) {
    addNewTexture("imgs/instructions.png");

    setCurrentTexture(0);
    setPosition((x / 2) - (spriteTextures[getCurrentTextureIndex()]->getSize().x / 2), (y / 2) - (spriteTextures[getCurrentTextureIndex()]->getSize().y / 2));
}

Message Instructions::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    return Message();
}

Message Instructions::react(sf::Event e) {
    return Message();
}

void Instructions::receiveMessage(Message msg) {

}

Message Instructions::click() {
    return Message(getName(), "clicked");
}

Message Instructions::unclick() {
    return Message(getName(), "unclicked");
}
