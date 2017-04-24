#pragma once

#include "Background.h"
#include "Message.h"
#include "Button.h"
#include "Boy.h"
#include "Leaf.h"
#include "BoyFriend.h"
#include "Cloud.h"
#include "KiteObj.h"
#include "Enemy.h"
#include <string.h>


#include <queue>
class GameWrapper
{
    public:
        GameWrapper();
        ~GameWrapper();
        //DrawableWithPriority getNext(void);
        void registerAnimatableSprite(DrawableWithPriority * newSprite);
        void removeSpritesBelongingToContext(std::string theContext);
        void registerReactableSprite(DrawableWithPriority * newSprite);
        void sortAnimatorsByPriority(void);

        void cleanUpSpritesFarOffScreen(void);
        void handleGameWrapperMessages(Message msg);
        void makeMainMenuBackground(void);
        void checkForClicks(void);
        void checkForUnclicks(void);
        void messageBlaster(void);
        void addMessageToQueue(Message msg);
		void startGame(void);
		std::string getCurrentContext(void);
		void setCurrentContext(std::string newCurrentContext);

    protected:
    private:
        std::vector<DrawableWithPriority *> animates; // vector of sprites that update their animation at least once
        std::vector<DrawableWithPriority *> reacts; // vector of sprites that react to events at least once
        // Since both of these vectors store pointers, one sprite can be in both animates and reacts
        std::queue<Message> messageQueue;
        std::string currentContext;
        sf::RenderWindow * window;

};

