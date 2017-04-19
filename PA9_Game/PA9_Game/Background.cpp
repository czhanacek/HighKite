#include "Background.h"



Background::Background(std::string newName, std::string filename, int x, int y, int iPosX, int iPosY, int priority) : DrawableWithPriority(newName, filename, x, y, iPosX, iPosY, priority) {
    std::cout << "I'm running!" << std::endl;
}

void Background::slideUpFirstTime(std::string newBackgroundFile) {


}

void Background::update(sf::Time t) {

	if (getName() == "Cloud1Background" || getName() == "Cloud2Background")
	{
		if (getPosition().y >= 720)
			setPosition(0, getPosition().y - 1420);
		else
			setPosition(0, getPosition().y + 5);
	}
	if (getName() == "BackgroundGrass")
		setPosition(0, getPosition().y + 5);
}

Background::~Background() {

}
