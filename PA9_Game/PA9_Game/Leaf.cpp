#include "Leaf.h"



Leaf::Leaf(std::string newContext) : DrawableWithPriority("leaf", newContext, 4) {
    if(rand() % 2  == 1) {
        addNewTexture("imgs/leaf-red.gif");
    }
    else {
        addNewTexture("imgs/leaf-yellow.gif");
    }
    stoppingPlace = rand() % 130 + 410;
    setCurrentTexture(0);
    removeMe = false;
    setPosition(-1 * (rand() % 200), -100 + rand() % 400);
    //std::cout << "Y position is " << getPosition().y << std::endl;
    setScale((double)30 / spriteTextures[0]->getSize().x, (double)30 / spriteTextures[0]->getSize().y);
}

void Leaf::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    //std::cout << "leafs matter" << std::endl;
    if(getContext() == "mainmenu") {
        if(clocks[0].getElapsedTime().asMilliseconds() > 10) {
            if(getPosition().y < stoppingPlace + rand() % 25) {
                setPosition(getPosition().x + rand() % 4, getPosition().y + pow(-1, rand() % 3) * (rand() % 4 ));
                setRotation(getRotation() + rand() % 15 - 7);
                clocks[0].restart();
            }
        }
    }
    int speed = 90;
    if(getContext() == "game") {
        if(clocks.size() == 1) {
            clocks.push_back(sf::Clock());
        }
        if(clocks[0].getElapsedTime().asMilliseconds() > 10) {
            setPosition(getPosition().x + rand() % 4, getPosition().y + pow(-1, rand() % 3) * (rand() % 4 ));
            setRotation(getRotation() + rand() % 15 - 7);
            clocks[0].restart();

        }
        if(clocks[1].getElapsedTime().asMilliseconds() >= 30) {
            setPosition(getPosition().x, getPosition().y + (speed / 30));
                clocks[1].restart();
        }
    }
}

Message Leaf::react(sf::Event e) {
    return Message();
}

void Leaf::receiveMessage(Message msg) {

}

Message Leaf::click() {
    return Message();
}

Message Leaf::unclick() {
    return Message();
}
