#include "Background.h"



Background::Background(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int priority) : DrawableWithPriority(newName, newContext, filename, x, y, iPosX, iPosY, priority) {
    std::cout << "I'm running!" << std::endl;
}

void Background::slideUpFirstTime(std::string newBackgroundFile) {


}

void Background::update(sf::Time totalElapsed, sf::Time sinceLastUpdate) {
    int speed = 90;
    if(clocks[0].getElapsedTime().asMilliseconds() >= 30) {
            clocks[0].restart();
        if (getName() == "Cloud1Background" || getName() == "Cloud2Background")
        {

                if (getPosition().y >= 720)
                    setPosition(0, getPosition().y - 1420);
                else
                    setPosition(0, getPosition().y + (speed / 30));
            }

        if (getName() == "BackgroundGrass") {
            setPosition(0, getPosition().y + (speed / 30));
        }
    }
}

Background::~Background() {

}
