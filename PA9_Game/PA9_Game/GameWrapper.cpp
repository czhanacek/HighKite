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
    gamestart = sf::Clock();
    gamestarted = false;
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

            else if(event.type == sf::Event::KeyPressed && getCurrentContext() == "game"){
                Message msg = Message("gamewrapper", "");

                if(!lCurrentlyPressed && event.key.code == sf::Keyboard::L){
                    msg.setContent("L pressed");
                    addMessageToQueue(msg);
                    std::cout << "L pressed" << std::endl;
                    lCurrentlyPressed = true;
                }
                else if(!sCurrentlyPressed && event.key.code == sf::Keyboard::S){
                    msg.setContent("S pressed");
                    addMessageToQueue(msg);
                    std::cout << "S pressed" << std::endl;
                    sCurrentlyPressed = true;
                }
            }
            else if(event.type == sf::Event::KeyReleased){
                Message msg = Message("gamewrapper", "");

                if(lCurrentlyPressed && event.key.code == sf::Keyboard::L){
                    if(sCurrentlyPressed){
                    msg.setContent("L released but S held");
                    }
                    else {
                    msg.setContent("L released");
                    }

                    addMessageToQueue(msg);
                    std::cout << "L released" << std::endl;
                    lCurrentlyPressed = false;
                }
                else if(sCurrentlyPressed && event.key.code == sf::Keyboard::S){

                    if(lCurrentlyPressed){
                    msg.setContent("S released but L held");
                    }
                    else {
                    msg.setContent("S released");
                    }
                    addMessageToQueue(msg);
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

        if(elapsed2.getElapsedTime().asMilliseconds() >= 2000  && getCurrentContext() == "game" && animates.size() < 16) {
            spawnRandomEnemy();
        }

        if(clk2.getElapsedTime().asSeconds() >= 0.5) {
            clk2.restart();
            cleanUpSpritesFarOffScreen();
        }
        if(gamestart.getElapsedTime().asSeconds() >= 0.5 && gamestarted) {
            gamestarted = false;
            makeMainMenuBackground();

        }
        checkForCollisionsWithKite();
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

void GameWrapper::spawnRandomEnemy(void) {
    int randomNumber = rand() % 5;
    DrawableWithPriority * enemy;
    switch(randomNumber) {
    case 0:
        enemy = new Eagle("Eagle", getCurrentContext());
        break;
    case 1:
        enemy = new Seagull("Seagull", getCurrentContext());
        break;
    case 2:
    case 3:
    case 4:
        enemy = new Bird("Bird", getCurrentContext());
        break;
    }
    registerAnimatableSprite(enemy);
    registerReactableSprite(enemy);
}

void GameWrapper::registerAnimatableSprite(DrawableWithPriority * newSprite) {
    animates.push_back(newSprite);
    sortAnimatorsByPriority();
}

void GameWrapper::registerReactableSprite(DrawableWithPriority * newSprite) {
    reacts.push_back(newSprite);
}

int GameWrapper::getIndexByName(std::string thename) {
    int foundIndex = -1;
    for(int i = 0; i < animates.size(); i++) {
        if(animates[i]->getName() == thename) {
            foundIndex = i;
        }
    }
    return foundIndex;
}


void GameWrapper::checkForCollisionsWithKite(void) {
    int indexOfKite = getIndexByName("Kite");
    if(indexOfKite != -1) {
        //std::cout << "Found kite index\n";
        for(int i = 0; i < animates.size(); i++) {
            if(animates[i]->isAnEnemy()) {
                if(Collision::PixelPerfectTest(*(animates[i]), *(animates[indexOfKite]))) {
                    std::cout << "Kite collided with " << animates[i]->getName() << std::endl;
                    addMessageToQueue(Message(animates[i]->getName(), "collided," + animates[i]->signature));
                    addMessageToQueue(Message(animates[indexOfKite]->getName(), "collided"));
                }
/*                 if(animates[i]->getGlobalBounds().intersects(animates[indexOfKite]->getGlobalBounds())) {
 *
 *
 *                 }
 */
            }
            //std::cout << "(" << mouse.x << ", " << mouse.y << ")\n";

        }

    }
}

GameWrapper::~GameWrapper() {
    for(int i = 0; i < animates.size(); i++) {
        delete animates[i];
    }
}

void GameWrapper::handleGameWrapperMessages(Message msg) {


    if(msg.getSender() == "showInstructions" && msg.getContent() == "unclicked") {
        showInstructions();
    }
    if(msg.getSender() == "instructions" && msg.getContent() == "unclicked") {
        removeSpritesByName("instructions");
    }
    if (msg.getSender() == "playGame" && msg.getContent() == "unclicked") {
        // Switch to different if statement once the Play Game button is created.
        startGame();
    }
    if(msg.getSender() == "quit" && msg.getContent() == "unclicked") {
        exit(0);
    }
    if(msg.getSender() == "Kite" && msg.getContent() == "collided") {
        gamestart.restart();
        gamestarted = true;
    }
}

void GameWrapper::removeSpritesByName(std::string theName) {
    // the same deletion method applies to all places where we remove sprites
    for(int i = 0; i < animates.size(); i++) {
        if(animates[i]->getName() == theName) {
            bool foundMatch = false;
            // Now we have to check if the same sprite exists in reacts so that we can make sure to get rid of it there too
            for(int x = 0; x < reacts.size(); x++) {
                if(animates[i] == reacts[x]) { // yes, the sprite is in both reacts and animates, so delete it from both vectors
                    delete animates[i];
                    foundMatch = true;
                    animates.erase(animates.begin() + i);
                    reacts.erase(reacts.begin() + x);
                    //x = 0;
                    //i = 0;
                }
            }
            if(!foundMatch) {
                // no, it only exists in animates, so just delete it from there
                delete animates[i];
                animates.erase(animates.begin() + i);
                //i = 0;
            }
        }
    }
}


void GameWrapper::showInstructions(void) {
    //setCurrentContext("instructions");
    DrawableWithPriority * instructionsScreen = new Instructions("instructions", getCurrentContext(), window->getSize().x, window->getSize().y);
    registerAnimatableSprite(instructionsScreen);
    registerReactableSprite(instructionsScreen);

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
    // the same deletion method applies to all places where we remove sprites. See removeSpritesByName for details
    int unremovalableException = 0;
//    if(animates.size() > 0) {
//        for(int i = unremovalableException; i < animates.size();) {
//            if(animates[i]->getContext() == theContext && animates[i]->removeMe) {
//                std::cout << "Erased " << animates[i]->getName() << " from animates\n";
//                delete animates[i];
//                animates.erase(animates.begin() + i);
//            }
//            else if(!animates[i]->removeMe) {
//                unremovalableException++;
//                animates[i]->setContext(getCurrentContext());
//                i = unremovalableException;
//            }
//        }
//    }
    for(int i = unremovalableException; i < animates.size();) {
        if(animates[i]->getContext() == theContext && animates[i]->removeMe) {
            bool foundMatch = false;
            for(int x = 0; x < reacts.size(); x++) {
                if(animates[i] == reacts[x]) {
                    foundMatch = true;
                    delete animates[i];
                    animates.erase(animates.begin() + i);
                    reacts.erase(reacts.begin() + x);
                    //x = unremovalableException;
                    i = unremovalableException;
                }
            }
            if(!foundMatch) {
                delete animates[i];
                animates.erase(animates.begin() + i);
                i = unremovalableException;
            }
        }
        else {
            unremovalableException++;
            animates[i]->setContext(getCurrentContext());
            i = unremovalableException;
        }
    }
//    unremovalableException = 0;
//    if(reacts.size() > 0) {
//        for(int x = unremovalableException; x < reacts.size();) {
//            if(reacts[x]->getContext() == theContext && reacts[x]->removeMe) {
//                std::cout << "Erased " << reacts[x]->getName() << " from reacts\n";
//                //delete reacts[x];
//                reacts.erase(reacts.begin() + x);
//            }
//            if(!reacts[x]->removeMe) {
//                unremovalableException++;
//                reacts[x]->setContext(getCurrentContext());
//                x = unremovalableException;
//            }
//        }
//    }
}

// Fantastically roasty forum thread that I found when trying to figure out how clicking on sprites works
// "do you even know geometry? trigonometry?"
// https://en.sfml-dev.org/forums/index.php?topic=5662.0

void GameWrapper::checkForClicks(void) {
    int reactsHighestPriorityIndex = -1;
    sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    for(int i = 0; i < reacts.size(); i++) {
        std::cout << "(" << mouse.x << ", " << mouse.y << ")\n";

        if(mouse.x >= reacts[i]->getPosition().x && mouse.x <= reacts[i]->getPosition().x + (reacts[i]->getSizeX())
                && mouse.y >= reacts[i]->getPosition().y && mouse.y <= reacts[i]->getPosition().y + (reacts[i]->getSizeY())) {
            std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().x  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeX()))  << ")\n";
            std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().y  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeY()))  << ")\n";
            if(reactsHighestPriorityIndex > -1 && reacts[reactsHighestPriorityIndex]->getPriority() < reacts[i]->getPriority()) {
                reactsHighestPriorityIndex = i;
            }
            else if (reactsHighestPriorityIndex == -1) {
                reactsHighestPriorityIndex = i;
            }

        }
    }
    if(reactsHighestPriorityIndex > -1) {
        addMessageToQueue(reacts[reactsHighestPriorityIndex]->click());
    }
}



void GameWrapper::checkForUnclicks(void) {
    int reactsHighestPriorityIndex = -1;
    sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    for(int i = 0; i < reacts.size(); i++) {
        std::cout << "(" << mouse.x << ", " << mouse.y << ")\n";

        if(mouse.x >= reacts[i]->getPosition().x && mouse.x <= reacts[i]->getPosition().x + (reacts[i]->getSizeX())
                && mouse.y >= reacts[i]->getPosition().y && mouse.y <= reacts[i]->getPosition().y + (reacts[i]->getSizeY())) {
            std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().x  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeX()))  << ")\n";
            std::cout << reacts[i]->getName() << "(" << reacts[i]->getPosition().y  << " - " << (reacts[i]->getPosition().x + (reacts[i]->getSizeY()))  << ")\n";
            if(reactsHighestPriorityIndex > -1 && reacts[reactsHighestPriorityIndex]->getPriority() < reacts[i]->getPriority()) {
                reactsHighestPriorityIndex = i;
            }
            else if (reactsHighestPriorityIndex == -1) {
                reactsHighestPriorityIndex = i;
            }

        }
    }
    if(reactsHighestPriorityIndex > -1) {
        std::cout << reacts[reactsHighestPriorityIndex]->getName()  << " got unclicked\n";
        addMessageToQueue(reacts[reactsHighestPriorityIndex]->unclick());
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
        //std::cout << "New message from " << msg.getSender() << ": " << msg.getContent() << std::endl;
        messageQueue.push(msg);
    }
}

std::string GameWrapper::getCurrentContext(void) {
    return currentContext;
}

void GameWrapper::setCurrentContext(std::string newCurrentContext) {

    currentContext = newCurrentContext;
    addMessageToQueue(Message("gamewrapper", "context changed"));
    // everything in reacts is guaranteed to be in reacts
    for(int i = 0; i < animates.size(); i++) {
        animates[i]->setContext(getCurrentContext());
    }
    for(int i = 0; i < reacts.size(); i++) {
        reacts[i]->setContext(getCurrentContext());
    }
}

void GameWrapper::forceRemoveAllSprites(void) {
    for(int i = 0; i < animates.size(); i++) {
        delete animates[i];
    }
//    for(int i = 0; i < reacts.size(); i++) {
//        delete reacts[i];
//    }
    animates.erase(animates.begin(), animates.end());
    reacts.erase(reacts.begin(), reacts.end());
}


void GameWrapper::makeMainMenuBackground(void) {
    std::cout << "Making main menu\n";
    forceRemoveAllSprites();
    //removeSpritesBelongingToContext("game");
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
    KiteObj * menuKite = new KiteObj();
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
    registerAnimatableSprite(menuKite);
    registerReactableSprite(menuKite);

}

void GameWrapper::startGame(void) {
    gamestart.restart();
    gamestarted = false;
    removeSpritesBelongingToContext("mainmenu");

    addMessageToQueue(Message("gamewrapper", "Game started"));

    if(getCurrentContext() == "mainmenu") {
        setCurrentContext("game");

        //DrawableWithPriority * boy = new Boy("Boy", "game", "imgs/boy.gif");
        DrawableWithPriority * cloud1Background = new Background("Cloud1Background", "game", "imgs/clouds.png", window->getSize().x,
                window->getSize().y, 0, 0, 2);

        DrawableWithPriority * cloud2Background = new Background("Cloud2Background", "game", "imgs/clouds.png", window->getSize().x,
                window->getSize().y, 0, -720, 2);
        DrawableWithPriority * moveGrass = new Background("BackgroundGrass", "game", "imgs/grass2.png", window->getSize().x,
                window->getSize().y, 0, 0, 3);

		DrawableWithPriority * sun = new ScoreTracker();
		DrawableWithPriority * scoreOne = new DigitOne();
		DrawableWithPriority * scoreTwo = new DigitTwo();
		DrawableWithPriority * scoreThree = new DigitThree();
		DrawableWithPriority * scoreFour = new DigitFour();
		DrawableWithPriority * scoreFive = new DigitFive();


        registerAnimatableSprite(cloud1Background);
        registerAnimatableSprite(cloud2Background);
        registerAnimatableSprite(moveGrass);
		registerAnimatableSprite(sun);
		registerAnimatableSprite(scoreOne);
		registerReactableSprite(scoreOne);
		registerAnimatableSprite(scoreTwo);
		registerReactableSprite(scoreTwo);
		registerAnimatableSprite(scoreThree);
		registerReactableSprite(scoreThree);
		registerAnimatableSprite(scoreFour);
		registerReactableSprite(scoreFour);
		registerAnimatableSprite(scoreFive);
		registerReactableSprite(scoreFive);
    }

}

void GameWrapper::cleanUpSpritesFarOffScreen(void) {
    // the same deletion method applies to all places where we remove sprites. See removeSpritesByName for details
    for(int i = 0; i < animates.size();) {
        if(animates[i]->getPosition().y > 2000 || animates[i]->getPosition().x > 2100 || animates[i]->getPosition().x < -2100 || animates[i]->getPosition().y < -1400) {
            bool foundMatch = false;
            for(int x = 0; x < reacts.size(); x++) {
                if(animates[i] == reacts[x]) {
                    delete animates[i];
                    foundMatch = true;
                    animates.erase(animates.begin() + i);
                    reacts.erase(reacts.begin() + x);
                }
            }
            if(!foundMatch) {
                delete animates[i];
                animates.erase(animates.begin() + i);

            }
        }
        else {
            i++;
        }
    }
}
