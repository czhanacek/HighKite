#pragma once
#include "DrawableWithPriority.h"
class Background : public DrawableWithPriority
{
public:
	Background(std::string newName, std::string newContext, std::string filename, int x, int y, int iPosX, int iPosY, int priority);
	~Background();
	void slideUpFirstTime(std::string newBackgroundFile);

	void update(sf::Time totalElapsed, sf::Time sinceLastUpdate);

};

