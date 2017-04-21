#include "GameWrapper.h"

GameWrapper::GameWrapper() {
    srand(time(NULL));
    sf::Clock clk1 = sf::Clock(), elapsed = sf::Clock();
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "------- High Kite -------");
    //window->setFramerateLimit(100);
    makeMainMenuBackground();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
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
        if(elapsed.getElapsedTime().asSeconds() >= 3 && getCurrentContext() == "mainmenu") {
            elapsed.restart();
            registerAnimatableSprite(new Leaf("mainmenu"));
        }



        window->clear();
        sortAnimatorsByPriority();


        for(int i = 0; i < animates.size(); i++) {
            window->draw(*(animates[i]));
        }
        // update textures here
        for(int i = 0; i < animates.size(); i++) {
            animates[i]->update(elapsed.getElapsedTime(), clk1.restart());
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


GameWrapper::~GameWrapper() {
    for(int i = 0; i < animates.size(); i++) {
        delete animates[i];
    }
}

void GameWrapper::handleGameWrapperMessages(Message msg) {
    if (msg.getSender() == "playGame" && msg.getContent() == "unclicked") {

        // Switch to different if statement once the Play Game button is created.
        currentContext = "game";
        removeSpritesBelongingToContext("mainmenu");

        startGame();
    }
    if(msg.getSender() == "quit" && msg.getContent() == "unclicked") {
        exit(0);
    }
}


// Sprites at the end of the list will be rendered last
// Therefore, sprites with a lower number will be rendered first.
void GameWrapper::sortAnimatorsByPriority(void) {
    int size = animates.size();
    DrawableWithPriority * temp;

    // Bubble sort
    while (size) {
        for (int i = 0; i < size - 1; ++i) {
            if (animates[i]->getPriority() > animates[i + 1]->getPriority()) {
                // The implementation of this if statement swaps the current object at current index with the next object in the vector
                temp = animates[i];
                animates[i] = animates[i + 1];
                animates[i + 1] = temp;
            }
        }
        size--;
    }

}


void GameWrapper::removeSpritesBelongingToContext(std::string theContext) {
    int unremovalableException = 0;
    for(int i = unremovalableException; i < animates.size();) {

        if(animates[i]->getContext() == theContext && animates[i]->removeMe) {
            std::cout << "Erased " << animates[i]->getName() << " from animates\n";
            animates.erase(animates.begin() + i);
        }
        else if(!animates[i]->removeMe) {
            unremovalableException++;
            animates[i]->setContext(getCurrentContext());
            i = unremovalableException;
        }
    }
    unremovalableException = 0;
    for(int x = unremovalableException; x < reacts.size();) {
        if(reacts[x]->getContext() == theContext && reacts[x]->removeMe) {
            std::cout << "Erased " << reacts[x]->getName() << " from reacts\n";
            reacts.erase(reacts.begin() + x);
        }
        if(!reacts[x]->removeMe) {
            unremovalableException++;
            reacts[x]->setContext(getCurrentContext());
            x = unremovalableException;

        }
    }
}





// Fantastically roasty forum thread that I found when trying to figure out how clicking on sprites works
// "do you even know geometry? trigonometry?"
// https://en.sfml-dev.org/forums/index.php?topic=5662.0


void GameWrapper::checkForClicks(void) {

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


void GameWrapper::checkForUnclicks(void) {
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

void GameWrapper::addMessageToQueue(Message msg) {
    if(!msg.isEmpty()) {
        messageQueue.push(msg);
    }
}

std::string GameWrapper::getCurrentContext(void) {
    return currentContext;
}

void GameWrapper::setCurrentContext(std::string newCurrentContext) {
    currentContext = newCurrentContext;
    addMessageToQueue(Message("gamewrapper", "context changed"));
}

void GameWrapper::makeMainMenuBackground(void) {
    setCurrentContext("mainmenu");
    DrawableWithPriority * quit = new Button("quit", getCurrentContext(), "imgs/button-quit.gif", "imgs/button-quit.gif", 700,  535);
    DrawableWithPriority * boy = new Boy("Boy", getCurrentContext(), "imgs/boy.gif");

    DrawableWithPriority * mmBackground = new Background("Background", "mainmenu", "imgs/clouds.png", window->getSize().x,
            window->getSize().y, 0, 0, 0);
    DrawableWithPriority * mmGrass = new Background("GrassBackground", "mainmenu", "imgs/grass2.png", window->getSize().x,
            window->getSize().y, 0, 0, 1);
    Button * instructions = new Button("showInstructions", "mainmenu", "imgs/button-instructions.gif", "imgs/button-instructions-pressed.gif", 500, 535);
    Button * play = new Button("playGame", "mainmenu", "imgs/button-play.gif", "imgs/button-play-pressed.gif", 300, 535);
    sortAnimatorsByPriority();
    registerAnimatableSprite(mmBackground);

    registerAnimatableSprite(mmGrass);
    registerAnimatableSprite(boy);
    registerReactableSprite(boy);
    registerAnimatableSprite(quit);
    registerReactableSprite(quit);
    registerAnimatableSprite(instructions);
    registerReactableSprite(instructions);
    registerAnimatableSprite(play);
    registerReactableSprite(play);
}

void GameWrapper::startGame(void) {
    setCurrentContext("game");
    DrawableWithPriority * boy = new Boy("Boy", "game", "imgs/boy.gif");
    DrawableWithPriority * cloud1Background = new Background("Cloud1Background", "game", "imgs/clouds.png", window->getSize().x,
            window->getSize().y, 0, 0, 2);
    DrawableWithPriority * cloud2Background = new Background("Cloud2Background", "game", "imgs/clouds.png", window->getSize().x,
            window->getSize().y, 0, -720, 2);
    DrawableWithPriority * moveGrass = new Background("BackgroundGrass", "game", "imgs/grass2.png", window->getSize().x,
            window->getSize().y, 0, 0, 3);
    registerAnimatableSprite(cloud1Background);

    registerAnimatableSprite(boy);
    registerAnimatableSprite(cloud2Background);
    registerAnimatableSprite(moveGrass);


}
