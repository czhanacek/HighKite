#include "Button.h"

Button::Button(std::string unclickedFilename, std::string clickedFilename, int xpos, int ypos) : DrawableWithPriority(unclickedFilename, 0){
    setPosition(xpos, ypos);
    if(clickedFilename != "") {
        addNewTexture(clickedFilename);
    }
}

Button::~Button()
{

}

void Button::click(void) {
    setTexture(*(spriteTextures[1]));
}
void Button::unclick(void) {
    setTexture(*(spriteTextures[0]));
}
