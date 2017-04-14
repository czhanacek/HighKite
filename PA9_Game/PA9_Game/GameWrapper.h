
#include "DrawableWithPriority.h"

#ifndef GAMEWRAPPER_H
#define GAMEWRAPPER_H


class GameWrapper
{
    public:
        GameWrapper();
        ~GameWrapper();
        DrawableWithPriority getNext(void);
        void registerSprite(DrawableWithPriority newSprite);

        void sortSpritesByPriority(void);
        void makeMainMenuBackground(void);
    protected:
    private:
        std::vector<DrawableWithPriority> onscreen;
         sf::RenderWindow * window;


};

#endif // GAMEWRAPPER_H
