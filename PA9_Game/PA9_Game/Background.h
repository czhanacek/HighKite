#pragma once
#include "DrawableWithPriority.h"
class Background : public DrawableWithPriority
{
public:
	Background(std::string newName, std::string filename, int x, int y, int iPosX, int iPosY, int priority);
	~Background();
	void slideUpFirstTime(std::string newBackgroundFile);
	void Background::update(sf::Time t);
};

