
#include "Background.h"

#ifndef GAMEWRAPPER_H
#define GAMEWRAPPER_H


class GameWrapper
{
    public:
        GameWrapper();
        ~GameWrapper();
        DrawableWithPriority getNext(void);
        void registerAnimatableSprite(DrawableWithPriority * newSprite);
        void registerReactableSprite(DrawableWithPriority * newSprite);
        void runApp(void);
        void sortAnimatorsByPriority(void);
        void makeMainMenuBackground(void);

    protected:
    private:
        std::vector<DrawableWithPriority *> animates; // vector of sprites that update their animation at least once
        std::vector<DrawableWithPriority *> reacts; // vector of sprites that react to events at least once
        // Since both of these vectors store pointers, one sprite can be in both animates and reacts


        sf::RenderWindow * window;

};

#endif // GAMEWRAPPER_H
