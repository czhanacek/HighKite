#include "Button.h"

Button::Button(std::string newName, std::string unclickedFilename, std::string clickedFilename, int xpos, int ypos) : DrawableWithPriority(newName, unclickedFilename, 5) {
    setPosition(xpos, ypos);

    if(clickedFilename != "") {
        addNewTexture(clickedFilename);
    }
}

Button::~Button()
{

}

void Button::receiveMessage(Message msg) {

}

Message Button::click(void) {
    setTexture(*(spriteTextures[1]));
    return Message(getName(), "clicked");
}
Message Button::unclick(void) {
    setTexture(*(spriteTextures[0]));
    return Message("instructionButton", "unclicked");
}
