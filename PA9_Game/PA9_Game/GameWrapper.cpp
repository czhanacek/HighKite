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
            if(event.type == sf::Event::MouseButtonPressed) {
                checkForClicks();
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                checkForUnclicks();
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
        messageBlaster(); // Sends events to all the reactables
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
	if (msg.getSender() == "playGame" && msg.getContent() == "unclicked") {

		// Switch to diffcc erent if statement once the Play Game button is created.
		removeSpritesBelongingToContext("mainmenu");
		startGame();
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


void GameWrapper::removeSpritesBelongingToContext(std::string theContext)
{

     for(int i = 0; i < animates.size(); i++) {
        if(animates[i]->getContext() == theContext) {
            std::cout << "Erased " << animates[i]->getName() << "from animates\n";
            animates.erase(animates.begin() + i);
            i = 0;
        }
    }
    for(int x = 0; x < reacts.size(); x++) {
        if(reacts[x]->getContext() == theContext) {
            std::cout << "Erased " << reacts[x]->getName() << "from reacts\n";
            reacts.erase(reacts.begin() + x);
            x = 0;
        }
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

        if(mouse.x >= reacts[i]->getPosition().x && mouse.x <= reacts[i]->getPosition().x + (reacts[i]->getSizeX())
                && mouse.y >= reacts[i]->getPosition().y && mouse.y <= reacts[i]->getPosition().y + (reacts[i]->getSizeY())) {
            std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().x  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeX()))  << ")\n";
             std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().y  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeY()))  << ")\n";

            addMessageToQueue(reacts[i]->click());
        }
    }
}

void GameWrapper::checkForUnclicks(void)
{
    sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    for(int i = 0; i < reacts.size(); i++) {
        std::cout << "(" << mouse.x << ", " << mouse.y << ")\n";

        if(mouse.x >= reacts[i]->getPosition().x && mouse.x <= reacts[i]->getPosition().x + (reacts[i]->getSizeX())
                && mouse.y >= reacts[i]->getPosition().y && mouse.y <= reacts[i]->getPosition().y + (reacts[i]->getSizeY())) {
            std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().x  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeX()))  << ")\n";
             std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().y  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeY()))  << ")\n";

            addMessageToQueue(reacts[i]->unclick());
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

	DrawableWithPriority * mmBackground = new Background("Background", "mainmenu", "imgs/clouds.png", window->getSize().x,
		window->getSize().y, 0, 0, 0);
	DrawableWithPriority * mmGrass = new Background("GrassBackground", "mainmenu", "imgs/grass2.png", window->getSize().x,
		window->getSize().y, 0, 0, 1);
    Button * instructions = new Button("showInstructions", "mainmenu", "imgs/button-instructions.gif", "imgs/button-instructions-pressed.gif", 500, 575);
    Button * play = new Button("playGame", "mainmenu", "imgs/button-play.gif", "imgs/button-play-pressed.gif", 500, 450);
    sortAnimatorsByPriority();
	registerAnimatableSprite(mmBackground);
	registerAnimatableSprite(mmGrass);
    registerAnimatableSprite(instructions);
    registerReactableSprite(instructions);
    registerAnimatableSprite(play);
    registerReactableSprite(play);
}

void GameWrapper::startGame(void) {

	DrawableWithPriority * cloud1Background = new Background("Cloud1Background", "game", "imgs/clouds.png", window->getSize().x,
		window->getSize().y, 0, 0, 2);
	DrawableWithPriority * cloud2Background = new Background("Cloud2Background", "game", "imgs/clouds.png", window->getSize().x,
		window->getSize().y, 0, -720, 2);
	DrawableWithPriority * moveGrass = new Background("BackgroundGrass", "game", "imgs/grass2.png", window->getSize().x,
		window->getSize().y, 0, 0, 3);
	registerAnimatableSprite(cloud1Background);
	registerAnimatableSprite(cloud2Background);
	registerAnimatableSprite(moveGrass);

}
