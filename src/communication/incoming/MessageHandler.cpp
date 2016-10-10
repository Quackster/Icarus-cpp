#include "stdafx.h"

#include "communication/headers/Incoming.h"
#include "communication/incoming/MessageHandler.h"

// Login
#include "communication/incoming/login/AuthenticateMessageEvent.h"
#include "communication/incoming/login/UniqueIDMessageEvent.h"
#include "communication/incoming/login/VersionCheckMessageEvent.h"

// User
#include "communication/incoming/user/UserDataMessageEvent.h"

// Navigator
#include "communication/incoming/navigator/SearchNewNavigatorEvent.h"

// Room
#include "communication/incoming/room/RoomInfoMessageEvent.h"
#include "communication/incoming/room/EnterRoomMessageEvent.h"
#include "communication/incoming/room/HeightMapMessageEvent.h"

/*
    MessageHandler constructor

    Loads all incoming message handlers into a map for easier access
*/
MessageHandler::MessageHandler() :
    messages(new std::map<int, MessageEvent*>())
{
    
    // Login
    this->createEvent(Incoming::VersionCheckMessageEvent, new VersionCheckMessageEvent());
    this->createEvent(Incoming::UniqueIDMessageEvent, new UniqueIDMessageEvent());
    this->createEvent(Incoming::AuthenticateMessageEvent, new AuthenticateMessageEvent());

    // User
    this->createEvent(Incoming::NewNavigatorMessageEvent, new UserDataMessageEvent());
    
    // Navigator
    this->createEvent(Incoming::SearchNewNavigatorEvent, new SearchNewNavigatorEvent());

    // Room
    this->createEvent(Incoming::RoomInfoMessageEvent, new RoomInfoMessageEvent());
    this->createEvent(Incoming::EnterRoomMessageEvent, new EnterRoomMessageEvent());
    this->createEvent(Incoming::HeightMapMessageEvent, new HeightMapMessageEvent());
}

/*
    Gets message event by header, if not found then it will return NULL

    @param message header
    @return none
*/
MessageEvent *MessageHandler::getMessageEvent(int header) {

    if (this->messages->count(header)) {
        return this->messages->find(header)->second;
    }

    return nullptr;
}

/*
    Inserts a message handler into the map only if the header doesn't already exist

    @param message header
    @param message event ptr
    @return none
*/
void MessageHandler::createEvent(int header, MessageEvent *event) {

    if (!this->messages->count(header)) {
        std::cout << " [MessageHandler] Event registered: " << header << " for event (" << typeid(*event).name() << ") " << std::endl;
        this->messages->insert(std::make_pair(header, event));
    }
}

/*
    Invokes a message handler with the requested header, if the header doesn't exist
    the method silently fails

    @param message header
    @param message request ptr
    @return none
*/
void MessageHandler::invoke(int header, Request &request, Player *player) {

    if (this->messages->count(header)) {
        this->messages->find(header)->second->handle(player, request);
        std::cout << " [MessageHandler] Handled message " << header << " for event (" << typeid(*this->messages->find(header)->second).name() << ") " << std::endl;
    } else {
        std::cout << " [MessageHandler] Unhandled message " << header << std::endl;
    }


}
/* 
    MessageHandler deconstructor

    Deletes all message event ptr's and clears the map, then finally deletes the map
*/
MessageHandler::~MessageHandler() { 

    for (auto pair : *this->messages) {
        delete pair.second; // Delete message event pointer
    }

    // Empty out nullptr values
    this->messages->clear();

    // Delete messages map
    delete messages;
}
