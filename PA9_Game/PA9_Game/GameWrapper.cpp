#include "GameWrapper.h"

GameWrapper::GameWrapper()
{
    sf::Clock clk = sf::Clock();
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "------- High Kite -------");
    window->setFramerateLimit(25);
    makeMainMenuBackground();

    sortAnimatorsByPriority();

    while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
            // Stuff in here will only execute when there's an event in SFML's event loop
            // Thus, anything not related to an event should go outside of this while loop
            // (but still in the window.isOpen() while loop.

            // In this case, event is the event at the beginning of the event queue (yes it is a queue)

            // In the future I'd like to have an application-specific event queue as well so that we can
            // create and handle our own events or abstract SFML events and then handle those.
            if (event.type == sf::Event::Closed)
                window->close();
            for(int i = 0; i < reacts.size(); i++) {
                reacts[i]->react(event);
            }

        }
        window->clear();


        for(int i = 0; i < animates.size(); i++) {
            window->draw(*(animates[i]));
        }
        // update textures here
        for(int i = 0; i < animates.size(); i++) {
            animates[i]->update(clk.getElapsedTime());
        }


        window->display();
    }
}

void GameWrapper::registerAnimatableSprite(DrawableWithPriority * newSprite) {
    animates.push_back(newSprite);
    sortAnimatorsByPriority();
}

void GameWrapper::registerReactableSprite(DrawableWithPriority * newSprite) {
    reacts.push_back(newSprite);
}


GameWrapper::~GameWrapper()
{
    for(int i = 0; i < animates.size(); i++) {
        delete animates[i];
    }
}


// Sprites at the end of the list will be rendered last
// Therefore, sprites with a lower number will be rendered first.
void GameWrapper::sortAnimatorsByPriority(void)
{
    std::sort(animates.begin(), animates.end());

}


void GameWrapper::makeMainMenuBackground(void) {
    DrawableWithPriority * mmBackground = new DrawableWithPriority("imgs/grassyfield.jpg", window->getSize().x,
        window->getSize().y, 0);
    //DrawableWithPriority apple = DrawableWithPriority("imgs/apple.gif", 100, 100, 2);
    DrawableWithPriority * boy = new DrawableWithPriority("imgs/boy.jpg", 100, 150, 1);
    boy->setRotation(100);
    boy->setPosition(500, 500);
    sortAnimatorsByPriority();
    registerAnimatableSprite(mmBackground);
    registerAnimatableSprite(boy);
    registerReactableSprite(boy);

}
