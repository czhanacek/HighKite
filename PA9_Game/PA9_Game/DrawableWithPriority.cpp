#include "DrawableWithPriority.h"


DrawableWithPriority::DrawableWithPriority(int newPriority) : sf::Sprite() {
    setPriority(newPriority);
}

DrawableWithPriority::~DrawableWithPriority() {

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


bool operator< (const DrawableWithPriority &d1, const DrawableWithPriority &d2) {
    if(d1.getPriority() < d2.getPriority()) {
        return true;
    }
    else {
        return false;
    }

}
