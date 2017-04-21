#pragma once
#include "DrawableWithPriority.h"


DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, int newPriority) : sf::Sprite() {
    setPriority(newPriority);

    clocks.push_back(sf::Clock());

    context = newContext;
    name = newName;
}

DrawableWithPriority::~DrawableWithPriority() {
    for(int i = 0; i < spriteTextures.size(); i++) {
        delete spriteTextures[i];
    }
}

void DrawableWithPriority::setPriority(int newPriority) {
    priority = newPriority;

}
int  DrawableWithPriority::getPriority (void) const {
    return priority;

}

// You better overload your click function!
Message DrawableWithPriority::click(void ) {
    std::cout << "I got clicked!\n";
    std::cout << "My size is (" << getSizeX() << ", " << getSizeY() << ")\n";
    int location = spriteTextures.size();
    spriteTextures.push_back(new sf::Texture());
    bool loaded = spriteTextures[location]->loadFromFile("imgs/apple.gif");
    if(loaded) {
        std::cout << spriteTextures[location]->getSize().x << std::endl;
        setScale((double)getSizeX() / spriteTextures[location]->getSize().x, (double)getSizeY() / spriteTextures[location]->getSize().y);
    }
    setTexture(*(spriteTextures[location]));
    return Message();

}

unsigned int DrawableWithPriority::getSizeX(void) {
    return getScale().x * getTexture()->getSize().x;
}

unsigned int DrawableWithPriority::getSizeY(void) {
    return getScale().y * getTexture()->getSize().y;
}



bool operator> (const DrawableWithPriority &d1, const DrawableWithPriority &d2) {
    if(d1.getPriority() > d2.getPriority()) {
        return true;
    } else {
        return false;
    }

}

DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int newPriority) {
    name = newName;

    clocks.push_back(sf::Clock());

    context = newContext;
    sf::Texture * textu = new sf::Texture();
    bool loaded = textu->loadFromFile(filename);
    if(loaded) {
        setScale((double)x / textu->getSize().x, (double)y / textu->getSize().y);
    }
    int location = spriteTextures.size();
    spriteTextures.push_back(textu);
    setTexture(*(spriteTextures[location]));
    priority = newPriority;
}

void DrawableWithPriority::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {

}


Message DrawableWithPriority::react(sf::Event e) {

    // Some example code to demonstrate the functionality of this function ;)
//    if(e.type == sf::Event::KeyPressed) {
//        if(e.key.code == sf::Keyboard::L) {
//            setPosition(getPosition().x + 10, getPosition().y);
//
//        }
//    }
    return Message();

}

// Loads a new texture given a filename. Returns the index of the texture in the spriteTexture vector
// if the texture was loaded successfully. If not loaded successfully, it returns -1.
int DrawableWithPriority::addNewTexture(std::string filename) {
    sf::Texture * textu = new sf::Texture();
    bool loaded = textu->loadFromFile(filename);
    if(loaded) {
        int location = spriteTextures.size();
        spriteTextures.push_back(textu);
        return location;
    } else {
        return -1;
    }
}

std::string DrawableWithPriority::getName(void) {
    return name;
}
DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int newPriority) {
    name = newName;
    clocks.push_back(sf::Clock());

    context = newContext;
    sf::Texture * textu = new sf::Texture();
    bool loaded = textu->loadFromFile(filename);
    int location = spriteTextures.size();
    spriteTextures.push_back(textu);
    setTexture(*(spriteTextures[location]));
    priority = newPriority;
}

Message DrawableWithPriority::unclick() {
    return Message();
}

std::string DrawableWithPriority::getContext() {
    return context;
}

int DrawableWithPriority::getCurrentTextureIndex(void) {
    return currentTextureIndex;
}

void DrawableWithPriority::setCurrentTexture(int index) {
    if(index < 0) {
        index = spriteTextures.size() - 1;
    } else if(index > spriteTextures.size() - 1) {
        index = 0;
    }
    setTexture(*(spriteTextures[index]));
    currentTextureIndex = index;
}



void DrawableWithPriority::receiveMessage(Message msg) {
    // This should be overloaded by subclasses
}


DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int newPriority) {
    name = newName;
    context = newContext;
    clocks.push_back(sf::Clock());
    sf::Texture * textu = new sf::Texture();
    bool loaded = textu->loadFromFile(filename);
    if(loaded) {
        std::cout << textu->getSize().x << std::endl;
        setScale((double)x / textu->getSize().x, (double)y / textu->getSize().y);
    }
    int location = spriteTextures.size();
    spriteTextures.push_back(textu);
    setTexture(*(spriteTextures[location]));
    priority = newPriority;
    setPosition(iPosX, iPosY);

}

bool operator< (const DrawableWithPriority &d1, const DrawableWithPriority &d2) {
    if(d1.getPriority() < d2.getPriority()) {
        return true;
    } else {
        return false;
    }

}
