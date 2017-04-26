#pragma once
#include "DrawableWithPriority.h"

// THERE ARE FOUR DIFFERENT CONSTRUCTORS FOR THIS CLASS
// While they are all different, here are some things that they all share
// - All have removeMe set to true by default
// - All have one clock in their clocks vector

DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, int newPriority) : sf::Sprite() {
    setPriority(newPriority);
    setEnemyStatus(false);
    numberOfTextureSets = 1;
    currentFrame = 0;
    textureOffset = 0;
    removeMe = true;
    clocks.push_back(sf::Clock());

    context = newContext;
    name = newName;
}


int DrawableWithPriority::getCurrentSoundIndex(void) {
    return currentSoundIndex;
}
void DrawableWithPriority::playSound(int index) {
  soundplayer.setBuffer(*(sounds[index]));
  currentSoundIndex = index;
  soundplayer.play();
}

int DrawableWithPriority::addNewSound(std::string filename) {
    sf::SoundBuffer * sound = new sf::SoundBuffer;
    bool loaded = sound->loadFromFile(filename);
    if(loaded) {
        int location = sounds.size();
        sounds.push_back(sound);
        return location;
    } else {
        return -1;
    }
}


// delete all the sprite textures (cuz they're pointers)
DrawableWithPriority::~DrawableWithPriority() {
    for(int i = 0; i < spriteTextures.size(); i++) {
        delete spriteTextures[i];
    }
    for(int i = 0; i < sounds.size(); i++) {
        delete sounds[i];
    }
    std::cout << getName() << " successfully removed\n";
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
    bool loaded = spriteTextures[location]->loadFromFile("imgs/apple.png");
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
    textureOffset = 0;
    numberOfTextureSets = 1;
    currentFrame = 0;
    removeMe = true;
    clocks.push_back(sf::Clock());
    setEnemyStatus(false);
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


// Just a default implementations for update
Message DrawableWithPriority::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    return Message();
}

// Just a default implementation for react
Message DrawableWithPriority::react(sf::Event e) {

    // Some example code to demonstrate the functionality of this function ;)
    if(e.type == sf::Event::KeyPressed) {
        if(e.key.code == sf::Keyboard::L && getPosition().x < 1280) {
            setPosition(getPosition().x + 10, getPosition().y);

        }
		if (e.key.code == sf::Keyboard::S && getPosition().x > 0) {
			setPosition(getPosition().x, getPosition().y + 10);

		}
    }
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

// updates the context of the sprite. this is useful when you have a sprite
// that stays relevant and on screen between contexts.
void DrawableWithPriority::setContext(std::string newContext) {
    context = newContext;
}

// returns the name of the sprite. Name your sprite well!
std::string DrawableWithPriority::getName(void) {
    return name;
}

// This constructor is useful when you just want to set a base texture for your sprite
DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int newPriority) {
    name = newName;
    setEnemyStatus(false);
    currentFrame = 0;
    textureOffset = 0;
    numberOfTextureSets = 1;
    clocks.push_back(sf::Clock());
    removeMe = true;
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

bool DrawableWithPriority::isAnEnemy(void) {
    return isEnemy;
}

void DrawableWithPriority::setEnemyStatus(bool newEnemyStatus) {
    isEnemy = newEnemyStatus;
}
// returns the current context of the sprite. This ought to match the current context
// that the game is in.
std::string DrawableWithPriority::getContext() {
    return context;
}

// getCurrentTextureIndex just returns the index of the current texture in the spriteTextures vector
int DrawableWithPriority::getCurrentTextureIndex(void) {
    return currentTextureIndex;
}



/* setCurrentTexture is a nifty function. Basically, it takes a texture that's already
 * been loaded and makes it the current texture of the sprite, which means that
 * it sets the active texture for the sprite. You do this by passing in an index in the
 * spriteTextures vector. The indexes in the spriteTextures vector correspond to the order
 * in which textures are loaded, so the first texture that is loaded gets an index of zero,
 * the second gets an index of one, and so on. The part about setCurrentTexture that makes it nifty
 * is the part where it will "loop" the index for you. So if you pass in an index that is outside
 * the bounds of the spriteTextures vector, it will wrap the index around (indexes higher than the
 * highest index will be wrapped around the zero, indexes less than zero will get wrapped around
 * to the highest valid index). This allows you to add a series of frames for an animation and just
 * increment the index that you pass in by one every time you want to advance the frame. You don't
 * have to worry about going outside the bounds of the spriteTextures vector because this function
 * takes care of that for you.
 */

void DrawableWithPriority::setCurrentTexture(int index) {
    if(spriteTextures.size() - 1 > 0) {
        index = index % ((int)spriteTextures.size());
    }
    setTexture(*(spriteTextures[index]));
    currentTextureIndex = index;

}



void DrawableWithPriority::receiveMessage(Message msg) {
    // This should be overloaded by subclasses
}


DrawableWithPriority::DrawableWithPriority(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int newPriority) {
    name = newName;
    currentFrame = 0;
    numberOfTextureSets = 1;
    context = newContext;
    textureOffset = 0;
    setEnemyStatus(false);
    removeMe = true;
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
