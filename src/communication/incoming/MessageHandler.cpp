/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "communication/headers/Incoming.h"
#include "communication/incoming/MessageHandler.h"

// Login
#include "communication/incoming/login/AuthenticateMessageEvent.h"
#include "communication/incoming/login/UniqueIDMessageEvent.h"
#include "communication/incoming/login/VersionCheckMessageEvent.h"

// User
#include "communication/incoming/user/UserDataMessageEvent.h"

// Misc
#include "communication/incoming/misc/LatencyTestMessageEvent.h"
#include "communication/incoming/misc/EventLogMessageEvent.h"

// Navigator
#include "communication/incoming/navigator/SearchNewNavigatorEvent.h"
#include "communication/incoming/navigator/NewNavigatorMessageEvent.h"

// Room
#include "communication/incoming/room/LeaveRoomMessageEvent.h"
#include "communication/incoming/room/RoomInfoMessageEvent.h"
#include "communication/incoming/room/EnterRoomMessageEvent.h"
#include "communication/incoming/room/HeightMapMessageEvent.h"
#include "communication/incoming/room/WalkMessageEvent.h"

// Messenger
#include "communication/incoming/messenger/MessengerInitMessageEvent.h"
#include "communication/incoming/messenger/MessengerSearchMessageEvent.h"
#include "communication/incoming/messenger/MessengerRequestMessageEvent.h"
#include "communication/incoming/messenger/MessengerAcceptMessageEvent.h"

/*
    MessageHandler constructor

    Loads all incoming message handlers into a map for easier access
*/
MessageHandler::MessageHandler() :
    messages(new std::map<int, MessageEvent*>()) {

    // Login
    this->createEvent(Incoming::VersionCheckMessageEvent, new VersionCheckMessageEvent());
    this->createEvent(Incoming::UniqueIDMessageEvent, new UniqueIDMessageEvent());
    this->createEvent(Incoming::AuthenticateMessageEvent, new AuthenticateMessageEvent());

    // User
    this->createEvent(Incoming::UserDataMessageEvent, new UserDataMessageEvent());

    // Misc
    this->createEvent(Incoming::LatencyTestMessageEvent, new LatencyTestMessageEvent());
    this->createEvent(Incoming::EventLogMessageEvent, new EventLogMessageEvent());
    
    // Navigator
    this->createEvent(Incoming::SearchNewNavigatorEvent, new SearchNewNavigatorEvent());
    this->createEvent(Incoming::NewNavigatorMessageEvent, new NewNavigatorMessageEvent());
    this->createEvent(Incoming::LeaveRoomMessageEvent, new LeaveRoomMessageEvent());

    // Room
    this->createEvent(Incoming::RoomInfoMessageEvent, new RoomInfoMessageEvent());
    this->createEvent(Incoming::EnterRoomMessageEvent, new EnterRoomMessageEvent());
    this->createEvent(Incoming::HeightMapMessageEvent, new HeightMapMessageEvent());
    this->createEvent(Incoming::UserWalkMessageEvent, new WalkMessageEvent());

    // Messenger
    this->createEvent(Incoming::MessengerSearchMessageEvent, new MessengerSearchMessageEvent());
    this->createEvent(Incoming::MessengerInitMessageEvent, new MessengerInitMessageEvent());
    this->createEvent(Incoming::MessengerRequestMessageEvent, new MessengerRequestMessageEvent());
    this->createEvent(Incoming::MessengerAcceptMessageEvent, new MessengerAcceptMessageEvent());
    
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

    for (auto pair : *this->messages) delete pair.second;

    delete messages;
}
