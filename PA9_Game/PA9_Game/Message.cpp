#pragma once
#include "Message.h"

Message::Message() {
    setContent("");
    setSender("");
    emptyMessage = true;
}

Message::Message(std::string newSender, std::string newContent) {
    setSender(newSender);
    setContent(newContent);
    if(getSender() == "" || getContent() == "") {
        emptyMessage = true;
    }
    else {
        emptyMessage = false;
    }

}

bool Message::isEmpty(void) {
    return emptyMessage;
}

Message::Message(std::string newSender) {
    setSender(newSender);
    if(getSender() == "" || getContent() == "") {
        emptyMessage = true;
    }
    else {
        emptyMessage = false;
    }
}

void Message::setSender(std::string newSender) {
    sender = newSender;
    if(getSender() == "" || getContent() == "") {
        emptyMessage = true;
    }
    else {
        emptyMessage = false;
    }
}

void Message::setContent(std::string newContent) {
    content = newContent;
    if(getSender() == "" || getContent() == "") {
        emptyMessage = true;
    }
    else {
        emptyMessage = false;
    }
}

std::string Message::getContent(void) {
    return content;
}

std::string Message::getSender(void) {
    return sender;
}

Message::~Message() {
    // Nothing needed here :)
}
