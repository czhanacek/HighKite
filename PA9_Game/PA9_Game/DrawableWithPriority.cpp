#include "DrawableWithPriority.h"


DrawableWithPriority::DrawableWithPriority(int newPriority) : sf::Sprite() {
    setPriority(newPriority);
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

bool operator> (const DrawableWithPriority &d1, const DrawableWithPriority &d2) {
    if(d1.getPriority() > d2.getPriority()) {
        return true;
    }
    else {
        return false;
    }

}

DrawableWithPriority::DrawableWithPriority(std::string filename, int x, int y, int newPriority) {
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

void DrawableWithPriority::update(sf::Time t) {
    // nothing here
}

void DrawableWithPriority::react(sf::Event e) {

    // Some example code to demonstrate the functionality of this function ;)
//    if(e.type == sf::Event::KeyPressed) {
//        if(e.key.code == sf::Keyboard::L) {
//            setPosition(getPosition().x + 10, getPosition().y);
//
//        }
//    }


}


DrawableWithPriority::DrawableWithPriority(std::string filename, int x, int y, int iPosX, int iPosY, int newPriority) {
    sf::Texture * textu = new sf::Texture();
    bool loaded = textu->loadFromFile(filename);
    if(loaded) {
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
    }
    else {
        return false;
    }

}
