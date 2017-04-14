#include "GameWrapper.h"

GameWrapper::GameWrapper()
{
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "------- High Kite -------");

    makeMainMenuBackground();

    sortSpritesByPriority();

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
        }
        window->clear();


        for(int i = 0; i < onscreen.size(); i++) {
            window->draw(onscreen[i]);
            std::cout << "Priority = " << onscreen[i].getPriority() << std::endl;
        }


        window->display();
    }
}

void GameWrapper::registerSprite(DrawableWithPriority newSprite) {
    onscreen.push_back(newSprite);
    sortSpritesByPriority();
}

GameWrapper::~GameWrapper()
{
    //dtor
}

DrawableWithPriority GameWrapper::getNext()
{
    sortSpritesByPriority();
    DrawableWithPriority temp = onscreen[0];
    onscreen.erase(onscreen.begin());
    return temp;
}
// Sprites at the end of the list will be rendered last
// Therefore, sprites with a lower number will be rendered first.
void GameWrapper::sortSpritesByPriority(void)
{
    std::sort(onscreen.begin(), onscreen.end());

}


void GameWrapper::makeMainMenuBackground(void) {
    registerSprite(DrawableWithPriority(0));
    sortSpritesByPriority();
    sf::Texture background;
    background = sf::Texture();
    background.create(window->getSize().x, window->getSize().y);
    onscreen[0].setTexture(background);
    onscreen[0].setColor(sf::Color(255, 170, 0));

}
