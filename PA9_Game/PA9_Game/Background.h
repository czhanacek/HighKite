#pragma once
#include "DrawableWithPriority.h"
class Background : public DrawableWithPriority
{
public:
	Background(std::string newName, std::string filename, int x, int y);
	~Background();
	void slideUpFirstTime(std::string newBackgroundFile);
};

