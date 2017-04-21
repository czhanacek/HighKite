#include "Boy.h"

Boy::Boy(std::string newName, std::string newContext, std::string filename) : DrawableWithPriority(newName, newContext, filename, 15) {
    setPosition(900, 100);
    addNewTexture("imgs/boy-bigmouth.gif");
    addNewTexture("imgs/boy-o-mouth.gif");
    addNewTexture("imgs/boy-smile.gif");
}

void Boy::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    int speed = 90;
    if(getContext() == "mainmenu") {
        //std::cout << totalElapsed.asSeconds() << std::endl;
        if(clocks[0].getElapsedTime().asSeconds() > 1.25 + ((rand() % 100 )) / 10) {
            clocks[0].restart();
            setCurrentTexture(getCurrentTextureIndex() + rand() % spriteTextures.size());
        }
    }
    else if(getContext() == "game") {
        bool updated = false;
        if(clocks.size() == 1) {
            clocks.push_back(sf::Clock());
        }
        if(clocks[0].getElapsedTime().asSeconds() > 0.25 + ((rand() % 100 )) / 10) {
            setCurrentTexture(getCurrentTextureIndex() + rand() % spriteTextures.size());
            clocks[0].restart();
        }
        if(clocks[1].getElapsedTime().asMilliseconds() >= 30) {
            if (getPosition().y >= 650) {
                setPosition(getPosition().x, 650);
            }
            else {
                setPosition(getPosition().x, getPosition().y + (speed / 30));
                clocks[1].restart();
            }

        }

    }

}

Message Boy::react(sf::Event e) {
    return Message();
}

void Boy::receiveMessage(Message msg) {

}

Message Boy::click() {
    return Message();
}

Message Boy::unclick() {
    return Message();
}
