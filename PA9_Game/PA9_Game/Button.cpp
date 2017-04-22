#include "Button.h"

Button::Button(std::string newName, std::string newContext, std::string unclickedFilename, std::string clickedFilename, int xpos, int ypos) : DrawableWithPriority(newName, newContext, unclickedFilename, 10) {
    setPosition(xpos, ypos);
    windspeed = 0;
    moveOverride = false;
    originalX = xpos;
    originalY = ypos;
    removeMe = false;
    bounceInterval = rand() % 5000;
    ticker = 0;
    movingUp = false;
    clocks.push_back(sf::Clock());
    if(clickedFilename != "") {
        addNewTexture(clickedFilename);
    }
}

Button::~Button() {

}
Message Button::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {

    if(clocks[1].getElapsedTime().asMilliseconds() >= bounceInterval || moveOverride == true) {
        if(clocks[0].getElapsedTime().asMilliseconds() >= 10) {
            ticker++;
            clocks[0].restart();
            if(movingUp == false && abs(getPosition().y - originalY) < 25 ) {
                move(windspeed, pow(ticker, 0.5) / 20);
            }
            if(getPosition().y - originalY >= 25 && ticker > 1 && movingUp == false) {
                movingUp = true;
                ticker = 0;
            }
            if(movingUp == true && abs(getPosition().y - originalY) >= 0){
                move(windspeed, -pow(ticker, 0.5) / 20);
            }
            if(getPosition().y - originalY < 0 && ticker > 1 && movingUp == true) {
                movingUp = false;
                ticker = 0;
            }
        }
    }

    return Message();
}

Message Button::react(sf::Event e) {
    return Message();
}



void Button::receiveMessage(Message msg) {
    if(msg.getSender() == "cloud" && msg.getContent() == "blowing") {
        moveOverride = true;
        if(rand() % 10 == 1 && windspeed < 5) {
                windspeed++;
        }
    }
    if(msg.getSender() == "cloud" && msg.getContent() == "not blowing" && windspeed > 0){
        moveOverride = true;
        if(rand() % 2 == 1 && windspeed >= 5) {
                windspeed--;
        }
    }
}

Message Button::click(void) {
    setTexture(*(spriteTextures[1]));
    return Message(getName(), "clicked");
}
Message Button::unclick(void) {
    setTexture(*(spriteTextures[0]));
    return Message(getName(), "unclicked");
}
