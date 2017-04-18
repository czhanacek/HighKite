#include "GameWrapper.h"

GameWrapper::GameWrapper()
{
    sf::Clock clk = sf::Clock();
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "------- High Kite -------");
    window->setFramerateLimit(25);
    makeMainMenuBackground();


    while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event) || !messageQueue.empty())
		{
            // Stuff in here will only execute when there's an event in SFML's event loop
            // Thus, anything not related to an event should go outside of this while loop
            // (but still in the window.isOpen() while loop.

            // In this case, event is the event at the beginning of the event queue (yes it is a queue)

            // In the future I'd like to have an application-specific event queue as well so that we can
            // create and handle our own events or abstract SFML events and then handle those.

            messageBlaster();

            if (event.type == sf::Event::Closed)
                window->close();
            if(event.type == sf::Event::MouseButtonPressed) {
                checkForClicks();
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                for(int i = 0; i < reacts.size(); i++) {
                    addMessageToQueue(reacts[i]->unclick());
                }
            }
            for(int i = 0; i < reacts.size(); i++) {
                addMessageToQueue(reacts[i]->react(event));
            }

        }
        window->clear();
		sortAnimatorsByPriority();


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

void GameWrapper::handleGameWrapperMessages(Message msg) {
    if(msg.getSender() == "showInstructions" && msg.getContent() == "clicked") {
        exit(0);
    }
}


// Sprites at the end of the list will be rendered last
// Therefore, sprites with a lower number will be rendered first.
void GameWrapper::sortAnimatorsByPriority(void)
{
	int size = animates.size();
	DrawableWithPriority * temp;

	// Bubble sort
	while (size)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			if (animates[i]->getPriority() > animates[i + 1]->getPriority())
			{
				// The implementation of this if statement swaps the current object at current index with the next object in the vector
				temp = animates[i];
				animates[i] = animates[i + 1];
				animates[i + 1] = temp;
			}
		}
		size--;
	}

}

// Fantastically roasty forum thread that I found when trying to figure out how clicking on sprites works
// "do you even know geometry? trigonometry?"
// https://en.sfml-dev.org/forums/index.php?topic=5662.0

void GameWrapper::checkForClicks(void)
{

    sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    for(int i = 0; i < reacts.size(); i++) {
        std::cout << "(" << mouse.x << ", " << mouse.y << ")\n";
        std::cout << reacts[i]->getScale().x;
        if(mouse.x >= reacts[i]->getPosition().x && mouse.x <= reacts[i]->getPosition().x + (reacts[i]->getSizeX())
                && mouse.y >= reacts[i]->getPosition().y && mouse.y <= reacts[i]->getPosition().x + (reacts[i]->getSizeY())) {
            std::cout << "(" << reacts[i]->getPosition().x  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeX()))  << ")\n";

            addMessageToQueue(reacts[i]->click());
        }
    }
}
void GameWrapper::messageBlaster(void) {

    while(!messageQueue.empty()) {
        Message currentMessage = messageQueue.front();

        messageQueue.pop();
        handleGameWrapperMessages(currentMessage); // Handle any messages that might be for the app itself.
        for(int i = 0; i < reacts.size(); i++) {
            reacts[i]->receiveMessage(currentMessage);
        }
    }
}

void GameWrapper::addMessageToQueue(Message msg)
{
    if(!msg.isEmpty()) {
        messageQueue.push(msg);
    }
}


void GameWrapper::makeMainMenuBackground(void) {
    DrawableWithPriority * mmBackground = new Background("Background", "imgs/grassyfield.jpg", window->getSize().x,
        window->getSize().y);
    //DrawableWithPriority apple = DrawableWithPriority("imgs/apple.gif", 100, 100, 2);
    Button * instructions = new Button("showInstructions", "imgs/button.jpg", "imgs/button-pressed.jpg", 500, 500);
	Button * instructions2 = new Button("dork", "imgs/button.jpg", "imgs/button-pressed.jpg", 100, 100);
    //boy->setRotation(100);
    sortAnimatorsByPriority();
    registerAnimatableSprite(mmBackground);
    registerAnimatableSprite(instructions);
	registerAnimatableSprite(instructions2);
    registerReactableSprite(instructions);

}
