#include "GameWrapper.h"


/* Current message senders and their messages
    - gamewrapper
        - context changed
    - cloud
        - blowing
        - not blowing
    - playGame (it's a button)
        - clicked
        - unclicked
    - quit
        - clicked
        - unclicked
*/

GameWrapper::GameWrapper() {
    srand(time(NULL)); // Seed the random number generator so that we get new stuff every time we start

    // start the music now
    sf::Music music;
    music.openFromFile("sounds/lafemme.ogg");
    music.play();
    sf::Clock clk1 = sf::Clock(), elapsed = sf::Clock(), clk2 = sf::Clock(), elapsed2 = sf::Clock(); // set up three clocks. Right now, we only use
    // elapsed,
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "------- High Kite -------");
    //window->setFramerateLimit(30);
    makeMainMenuBackground();
    int leafInterval = rand() % 2500 + 500;
    bool sCurrentlyPressed = false, lCurrentlyPressed = false;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            // Stuff in here will only execute when there's an event in SFML's event loop
            // Thus, anything not related to an event should go outside of this while loop
            // (but still in the window.isOpen() while loop.

            // In this case, event is the event at the beginning of the event queue (yes it is a queue)

            // In the future I'd like to have an application-specific event queue as well so that we can
            // create and handle our own events or abstract SFML events and then handle those.

            // Yo we got that application-specific queue \0/

            if (event.type == sf::Event::Closed)
                window->close();
            else if(event.type == sf::Event::MouseButtonPressed) {
                checkForClicks();
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                checkForUnclicks();
            }
            else if(event.type == sf::Event::KeyPressed){
                if(!lCurrentlyPressed && event.key.code == sf::Keyboard::L){
                    addMessageToQueue(Message("gamewrapper", "L pressed"));
                    std::cout << "L pressed" << std::endl;

                    lCurrentlyPressed = true;
                }
                else if(!sCurrentlyPressed && event.key.code == sf::Keyboard::S){
                    addMessageToQueue(Message("gamewrapper", "S pressed"));
                    std::cout << "S pressed" << std::endl;
                    sCurrentlyPressed = true;
                }
            }
            else if(event.type == sf::Event::KeyReleased){
                if(lCurrentlyPressed && event.key.code == sf::Keyboard::L){
                    addMessageToQueue(Message("gamewrapper", "L released"));
                    std::cout << "L released" << std::endl;
                    lCurrentlyPressed = false;
                }
                else if(sCurrentlyPressed && event.key.code == sf::Keyboard::S){
                    addMessageToQueue(Message("gamewrapper", "S released"));
                    std::cout << "S released" << std::endl;
                    sCurrentlyPressed = false;
                }
            }

            for(int i = 0; i < reacts.size(); i++) {
                //std::cout << "Reacting to events\n";
                addMessageToQueue(reacts[i]->react(event));
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) {
                exit(0);
            }


        }

        if(elapsed.getElapsedTime().asMilliseconds() >= leafInterval  && getCurrentContext() == "mainmenu") {
            elapsed.restart();
            //leafInterval = rand() % 2000 + 3000;
            Leaf * lef = new Leaf("mainmenu");
            registerAnimatableSprite(lef);
            registerReactableSprite(lef);
        }

        if(elapsed2.getElapsedTime().asMilliseconds() >= 1000  && getCurrentContext() == "game") {
            elapsed2.restart();
            //leafInterval = rand() % 2000 + 3000;
            DrawableWithPriority * enemy = new Eagle("blah", getCurrentContext());
            registerAnimatableSprite(enemy);
            registerReactableSprite(enemy);
        }

        if(clk2.getElapsedTime().asSeconds() >= 0.5) {
            clk2.restart();
            cleanUpSpritesFarOffScreen();
        }

        messageBlaster(); // Sends messages to all the reactables
        window->clear();
        sortAnimatorsByPriority();

        for(int i = 0; i < animates.size(); i++) {
            addMessageToQueue(animates[i]->update(elapsed.getElapsedTime(), clk1.getElapsedTime()));
        }
        for(int i = 0; i < animates.size(); i++) {
            window->draw(*(animates[i]));
        }
        // update textures here

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

    Boy * boy = new Boy("Boy", getCurrentContext(), "imgs/boy.png");
    BoyFriend * boyfriend = new BoyFriend("Friend", getCurrentContext(), "imgs/friend.png");
    Background * mmBackground = new Background("Background", "mainmenu", "imgs/clouds.png", window->getSize().x,
            window->getSize().y, 0, 0, 0);
    Background * mmGrass = new Background("GrassBackground", "mainmenu", "imgs/grass2.png", window->getSize().x,
            window->getSize().y, 0, 0, 1);

    Button * quit = new Button("quit", getCurrentContext(), "imgs/button-quit.png", "imgs/button-quit.png", 600,  100);
    Button * instructions = new Button("showInstructions", getCurrentContext(), "imgs/button-instructions.png", "imgs/button-instructions-pressed.png", 400, 100);
    Button * play = new Button("playGame", getCurrentContext(), "imgs/button-play.png", "imgs/button-play-pressed.png", 200, 100);
    Cloud * windcloud = new Cloud("cloud", getCurrentContext());

    sortAnimatorsByPriority();

    registerAnimatableSprite(windcloud);
    registerAnimatableSprite(mmBackground);
    registerAnimatableSprite(boyfriend);
    registerAnimatableSprite(mmGrass);
    registerAnimatableSprite(boy);
    registerReactableSprite(windcloud);
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
    //DrawableWithPriority * boy = new Boy("Boy", "game", "imgs/boy.gif");
    DrawableWithPriority * cloud1Background = new Background("Cloud1Background", "game", "imgs/clouds.png", window->getSize().x,
            window->getSize().y, 0, 0, 2);

    DrawableWithPriority * cloud2Background = new Background("Cloud2Background", "game", "imgs/clouds.png", window->getSize().x,
            window->getSize().y, 0, -720, 2);
    DrawableWithPriority * moveGrass = new Background("BackgroundGrass", "game", "imgs/grass2.png", window->getSize().x,
            window->getSize().y, 0, 0, 3);
    DrawableWithPriority * kite = new KiteObj();

    registerAnimatableSprite(cloud1Background);
    registerAnimatableSprite(cloud2Background);
    registerAnimatableSprite(moveGrass);
    registerAnimatableSprite(kite);
    registerReactableSprite(kite);

}

void GameWrapper::cleanUpSpritesFarOffScreen(void) {
    for(int i = 0; i < animates.size();) {
        if(animates[i]->getPosition().y > 1400 || animates[i]->getPosition().x > 2100 || animates[i]->getPosition().x < -2100 || animates[i]->getPosition().y < -1400) {
            std::cout << "Erased " << animates[i]->getName() << " from animates because it was too far off screen\n";
            animates.erase(animates.begin() + i);
            i = 0;
        }
        else {
            i++;
        }
    }
    for(int i = 0; i < reacts.size();) {
        if(reacts[i]->getPosition().y > 1400 || reacts[i]->getPosition().x > 2100 || reacts[i]->getPosition().x < -2100 || reacts[i]->getPosition().y < -1400) {
            std::cout << "Erased " << reacts[i]->getName() << " from reacts because it was too far off screen\n";
            reacts.erase(reacts.begin() + i);
            i = 0;
        }
         else {
            i++;
        }
    }
}
