#include "Background.h"



Background::Background(std::string newName, std::string filename, int x, int y) : DrawableWithPriority(newName, filename, x, y, 0) {
    std::cout << "I'm running!" << std::endl;
}

void Background::slideUpFirstTime(std::string newBackgroundFile) {


}

Background::~Background() {

}
