#include "Leaf.h"



Leaf::Leaf(std::string newContext) : DrawableWithPriority("leaf", newContext, 4) {
    windspeed = 0;
    if(rand() % 2  == 1) {
        addNewTexture("imgs/leaf-red.png");
    }
    else {
        addNewTexture("imgs/leaf-yellow.png");
    }
    stoppingPlace = rand() % 130 + 410;
    setCurrentTexture(0);
    removeMe = false;
    setPosition(-1 * (rand() % 200), -100 + rand() % 400);
    //std::cout << "Y position is " << getPosition().y << std::endl;
    setScale((double)30 / spriteTextures[0]->getSize().x, (double)30 / spriteTextures[0]->getSize().y);
}

Message Leaf::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    //std::cout << "leafs matter" << std::endl;
    if(getContext() == "mainmenu") {
        if(clocks[0].getElapsedTime().asMilliseconds() > 10) {
            if(getPosition().y < stoppingPlace + rand() % 25) {
                setPosition(getPosition().x + windspeed + rand() % 4, getPosition().y + pow(-1, rand() % 3) * (rand() % 4 ));
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
            setPosition(getPosition().x + windspeed +rand() % 4, getPosition().y + pow(-1, rand() % 3) * (rand() % 4 ));
            setRotation(getRotation() + rand() % 30 - 15);
            clocks[0].restart();

        }
        if(clocks[1].getElapsedTime().asMilliseconds() >= 30) {
            setPosition(getPosition().x, getPosition().y + (speed / 30));
                clocks[1].restart();
        }
    }
    return Message();
}

Message Leaf::react(sf::Event e) {
    return Message();
}

void Leaf::receiveMessage(Message msg) {
    if(msg.getSender() == "cloud" && msg.getContent() == "blowing") {
        if(rand() % 5 == 1 && windspeed < 10) {
                windspeed++;
        }
        //std::cout << "Received blowing message from cloud\n";
    }
    if(msg.getSender() == "cloud" && msg.getContent() == "not blowing" && windspeed > 0){

        if(rand() % 2 == 1 && windspeed >= 10) {
                windspeed--;
        }
        //std::cout << "Received not blowing message from cloud\n";
    }
}

Message Leaf::click() {
    return Message();
}

Message Leaf::unclick() {
    return Message();
}
