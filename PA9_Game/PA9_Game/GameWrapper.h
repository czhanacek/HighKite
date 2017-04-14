
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
        void runApp(void);
        void sortSpritesByPriority(void);
        void makeMainMenuBackground(void);
    protected:
    private:
        std::vector<DrawableWithPriority> onscreen;


};

#endif // GAMEWRAPPER_H
