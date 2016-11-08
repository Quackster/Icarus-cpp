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
#include "MessageHandler.h"

// Login
#include "login/AuthenticateMessageEvent.h"
#include "login/UniqueIDMessageEvent.h"
#include "login/VersionCheckMessageEvent.h"

// User
#include "user/InfoRetrieveMessageEvent.h"
#include "user/CurrencyBalanceMessageEvent.h"

// Misc
#include "misc/LatencyTestMessageEvent.h"
#include "misc/EventLogMessageEvent.h"

// Navigator
#include "navigator/SearchNewNavigatorEvent.h"
#include "navigator/NewNavigatorMessageEvent.h"
#include "navigator/CreateRoomMessageEvent.h"

// Room
#include "room/LeaveRoomMessageEvent.h"
#include "room/RoomInfoMessageEvent.h"
#include "room/EnterRoomMessageEvent.h"
#include "room/HeightMapMessageEvent.h"
#include "room/WalkMessageEvent.h"
#include "room/RoomEditInfoMessageEvent.h"
#include "room/DeleteRoomMessageEvent.h"
#include "room/SaveRoomMessageEvent.h"
#include "room/user/ChatMessageEvent.h"
#include "room/user/ShoutMessageEvent.h"
#include "room/user/TypingStatusMessageEvent.h"
#include "room/user/ShowSignMessageEvent.h"
#include "room/user/DanceMessageEvent.h"

// Doorbell
#include "room/doorbell/AnswerDoorbellMessageEvent.h"
#include "room/doorbell/EnterDoorbellMessageEvent.h"

// Messenger
#include "messenger/MessengerInitMessageEvent.h"
#include "messenger/MessengerSearchMessageEvent.h"
#include "messenger/MessengerRequestMessageEvent.h"
#include "messenger/MessengerAcceptMessageEvent.h"
#include "messenger/MessengerDeclineMessageEvent.h"
#include "messenger/MessengerDeleteFriendMessageEvent.h"
#include "messenger/MessengerTalkMessageEvent.h"
#include "messenger/FollowFriendMessageEvent.h"
#include "messenger/MessengerInviteMessageEvent.h"

/*
    MessageHandler constructor

    Loads all incoming message handlers into a map for easier access
*/
MessageHandler::MessageHandler() {

    // Login
   this->messages[Incoming::VersionCheckMessageEvent] = new VersionCheckMessageEvent();
   this->messages[Incoming::UniqueIDMessageEvent] = new UniqueIDMessageEvent();
   this->messages[Incoming::AuthenticateMessageEvent] = new AuthenticateMessageEvent();

    // User
   this->messages[Incoming::InfoRetrieveMessageEvent] = new InfoRetrieveMessageEvent();
   this->messages[Incoming::CurrencyBalanceMessageEvent] = new CurrencyBalanceMessageEvent();

    // Misc
   this->messages[Incoming::LatencyTestMessageEvent] = new LatencyTestMessageEvent();
   this->messages[Incoming::EventLogMessageEvent] = new EventLogMessageEvent();
    
    // Navigator
   this->messages[Incoming::SearchNewNavigatorEvent] = new SearchNewNavigatorEvent();
   this->messages[Incoming::NewNavigatorMessageEvent] = new NewNavigatorMessageEvent();
   this->messages[Incoming::LeaveRoomMessageEvent] = new LeaveRoomMessageEvent();
   this->messages[Incoming::CreateRoomMessageEvent] = new CreateRoomMessageEvent();

    // Room
   this->messages[Incoming::RoomInfoMessageEvent] = new RoomInfoMessageEvent();
   this->messages[Incoming::EnterRoomMessageEvent] = new EnterRoomMessageEvent();
   this->messages[Incoming::HeightMapMessageEvent] = new HeightMapMessageEvent();
   this->messages[Incoming::UserWalkMessageEvent] = new WalkMessageEvent();
   this->messages[Incoming::RoomEditInfoMessageEvent] = new RoomEditInfoMessageEvent();
   this->messages[Incoming::DeleteRoomMessageEvent] = new DeleteRoomMessageEvent();
   this->messages[Incoming::SaveRoomMessageEvent] = new SaveRoomMessageEvent();
   this->messages[Incoming::ChatMessageEvent] = new ChatMessageEvent();
   this->messages[Incoming::ShoutMessageEvent] = new ShoutMessageEvent();
   this->messages[Incoming::StartTypingMessageEvent] = new TypingStatusMessageEvent();
   this->messages[Incoming::StopTypingMessageEvent] = new TypingStatusMessageEvent();
   this->messages[Incoming::ShowSignMessageEvent] = new ShowSignMessageEvent();
   this->messages[Incoming::DanceMessageEvent] = new DanceMessageEvent();

    // Doorbell
   this->messages[Incoming::AnswerDoorbellMessageEvent] = new AnswerDoorbellMessageEvent();
   this->messages[Incoming::EnterDoorbellMessageEvent] = new EnterDoorbellMessageEvent();

    // Messenger
   this->messages[Incoming::MessengerSearchMessageEvent] = new MessengerSearchMessageEvent();
   this->messages[Incoming::MessengerInitMessageEvent] = new MessengerInitMessageEvent();
   this->messages[Incoming::MessengerRequestMessageEvent] = new MessengerRequestMessageEvent();
   this->messages[Incoming::MessengerAcceptMessageEvent] = new MessengerAcceptMessageEvent();
   this->messages[Incoming::MessengerDeclineMessageEvent] = new MessengerDeclineMessageEvent();
   this->messages[Incoming::MessengerDeleteFriendMessageEvent] = new MessengerDeleteFriendMessageEvent();
   this->messages[Incoming::FollowFriendMessageEvent] = new FollowFriendMessageEvent();
   this->messages[Incoming::MessengerTalkMessageEvent] = new MessengerTalkMessageEvent();
   this->messages[Incoming::MessengerInviteMessageEvent] = new MessengerInviteMessageEvent();
}

/*
    Gets message event by header, if not found then it will return NULL

    @param message header
    @return none
*/
MessageEvent *MessageHandler::getMessageEvent(int header) {

    if (this->messages.count(header)) {
        return this->messages.find(header)->second;
    }

    return nullptr;
}

/*
    Invokes a message handler with the requested header, if the header doesn't exist
    the method silently fails

    @param message header
    @param message request ptr
    @return none
*/
void MessageHandler::invoke(int header, Request &request, Player *player) {
    
    if (this->messages.count(header)) {

        if (header != Incoming::VersionCheckMessageEvent &&
            header != Incoming::UniqueIDMessageEvent &&
            header != Incoming::AuthenticateMessageEvent) {

            if (!player->authenticated()) {
                printf("Player tried to send packet while not logged in, scripting maybe?\n");
                return;
            }
        }

        this->messages.find(header)->second->handle(player, request);

        if (Icarus::getLogConfiguration()->getBool("log.message.handled")) {
            std::cout << " [MessageHandler] Handled message " << header << " for event (" << typeid(*this->messages.find(header)->second).name() << ") " << std::endl;
        }
    } else {
        
        if (Icarus::getLogConfiguration()->getBool("log.message.unhandled")) {
            std::cout << " [MessageHandler] Unhandled message " << header << std::endl;
        }
    }
}
/* 
    MessageHandler deconstructor

    Deletes all message event ptr's and clears the map, then finally deletes the map
*/
MessageHandler::~MessageHandler() { 
    for (auto pair : this->messages) delete pair.second;
}
