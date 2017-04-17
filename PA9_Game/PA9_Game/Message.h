#pragma once

#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <SFML/Window/Keyboard.hpp>
// Just a quick note:
// If a Message object is instantiated with no sender and no content, or the sender or content
// is set to "", the Message object is empty, and the emptyMessage flag is set to true.
// Otherwise, the emptyMessage flag is set to false;
class Message {
    public:
        Message();
        Message(std::string newSender, std::string newContent);
        Message(std::string newSender);
        bool isEmpty(void);
        void setSender(std::string newSender);
        void setContent(std::string newContent);
        std::string getContent(void);
        std::string getSender(void);
        ~Message();
    private:
        bool emptyMessage;
        std::string sender;
        std::string content;
};
