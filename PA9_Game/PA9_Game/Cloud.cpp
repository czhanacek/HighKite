#include "Cloud.h"


Cloud::Cloud(std::string newName, std::string newContext) : DrawableWithPriority(newName, newContext, 15) {
    addNewTexture("imgs/windycloud.png");
    addNewSound("sounds/windy.ogg");
    peekInterval = rand() % 10;
    removeMe = false;
    setCurrentTexture(0);
    movingOut = true;
    moving = false;
    setScale(0.35, 0.35);
    setPosition(0, 0);

    move(-1 * (int)getSizeX(), 30);
    std::cout << getSizeX() << std::endl;
    clocks.push_back(sf::Clock());
}

Message Cloud::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    if(clocks[0].getElapsedTime().asMilliseconds() >= 10) {
        clocks[0].restart();
        if(getPosition().x + getSizeX() < 400 && movingOut && moving) {
            move(3, 0);
        }
        if(getPosition().x + getSizeX() >= 400) {
            movingOut = false;
        }
        if((!movingOut && moving)) {
            move(-7, 0);
            soundplayer.setVolume(soundplayer.getVolume() - 3);
            movingOut = false;
        }
        if(getPosition().x + getSizeX() < 0 && !movingOut) {
            moving = false;
        }
    }

    if(moving) {

        return Message(getName(), "blowing");
    }
    else {

        return Message(getName(), "not blowing");
    }
}

Message Cloud::react(sf::Event e) {
    return Message();
}

void Cloud::receiveMessage(Message msg) {
    if(msg.getSender() == "playGame" && msg.getContent() == "unclicked") {
        moving = true;
        playSound(0);
        movingOut = true;
        peekInterval = 20 + rand() % 10;
    }
}

Message Cloud::click() {
    return Message();
}

Message Cloud::unclick() {
    return Message();
}
