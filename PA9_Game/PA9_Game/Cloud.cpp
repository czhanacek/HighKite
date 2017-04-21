#include "Cloud.h"


Cloud::Cloud(std::string newName, std::string newContext) : DrawableWithPriority(newName, newContext, 15) {
    addNewTexture("imgs/windycloud.gif");
    peekInterval = 10 + rand() % 10;
    setCurrentTexture(0);
    movingOut = true;
    moving = false;
    setScale(0.35, 0.35);
    setPosition(0, 0);

    move(-1 * (int)getSizeX(), 30);
    std::cout << getSizeX() << std::endl;
    clocks.push_back(sf::Clock());
}

void Cloud::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    if(clocks[0].getElapsedTime().asMilliseconds() > 10) {
        clocks[0].restart();
        if(getPosition().x + getSizeX() < 400 && movingOut && moving) {
            move(4, 0);
        }
        if(getPosition().x + getSizeX() >= 400) {
            movingOut = false;
        }
        if((!movingOut && moving)) {
            move(-1, 0);
            movingOut = false;
        }
        if(getPosition().x + getSizeX() < 0 && !movingOut) {
            moving = false;
        }

    }
    if(clocks[1].getElapsedTime().asSeconds() > peekInterval && !moving && getPosition().x + getSizeX() <= 0) {
        moving = true;
        movingOut = true;
        peekInterval = 10 + rand() % 10;
        clocks[1].restart();
        std::cout << "cloud moving now!\n";
    }
}

Message Cloud::react(sf::Event e) {

}

void Cloud::receiveMessage(Message msg) {

}

Message Cloud::click() {

}

Message Cloud::unclick() {

}
