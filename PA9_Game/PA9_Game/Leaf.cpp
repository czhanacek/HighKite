#include "Leaf.h"



Leaf::Leaf(std::string newContext) : DrawableWithPriority("leaf", newContext, 30) {
    addNewTexture("imgs/leaf-red.gif");
    setCurrentTexture(0);
    setPosition(-1 * (rand() % 1000), -100 + rand() % 200);
    //std::cout << "Y position is " << getPosition().y << std::endl;
    setScale((double)30 / spriteTextures[0]->getSize().x, (double)30 / spriteTextures[0]->getSize().y);
}

void Leaf::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    //std::cout << "leafs matter" << std::endl;
    if(clocks[0].getElapsedTime().asMilliseconds() > 10) {
        if(getPosition().y < 500 + rand() % 25) {
            setPosition(getPosition().x + rand() % 4, getPosition().y + pow(-1, rand() % 3) * (rand() % 4 ));
            clocks[0].restart();
        }
    }
}

Message Leaf::react(sf::Event e) {

}

void Leaf::receiveMessage(Message msg) {

}

Message Leaf::click() {

}

Message Leaf::unclick() {

}
