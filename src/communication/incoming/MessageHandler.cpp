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

#include "room/RoomEditInfoMessageEvent.h"
#include "room/DeleteRoomMessageEvent.h"
#include "room/SaveRoomMessageEvent.h"

#include "room/user/WalkMessageEvent.h"
#include "room/user/ChatMessageEvent.h"
#include "room/user/ShoutMessageEvent.h"
#include "room/user/TypingStatusMessageEvent.h"
#include "room/user/ShowSignMessageEvent.h"
#include "room/user/DanceMessageEvent.h"

// Room Item
#include "room/item/PlaceItemMessageEvent.h"
#include "room/item/ApplyDecorationMessageEvent.h"
#include "room/item/MoveItemMessageEvent.h"
#include "room/item/PickupItemMessageEvent.h"
#include "room/item/InteractItemMessageEvent.h"

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
#include "messenger/MessengerUpdateMessageEvent.h"
#include "messenger/FollowFriendMessageEvent.h"
#include "messenger/MessengerInviteMessageEvent.h"

// Catalogue
#include "catalogue/CatalogueTabMessageEvent.h"
#include "catalogue/CataloguePageMessageEvent.h"
#include "catalogue/PurchaseObjectMessageEvent.h"

// Item
#include "item/InventoryMessageEvent.h"



// Outgoing
#include "communication/outgoing/misc/BroadcastMessageAlertComposer.h"

/*
    MessageHandler constructor

    Loads all incoming message handlers into a map for easier access
*/
MessageHandler::MessageHandler() {

    // Login
   this->createEvent(Incoming::VersionCheckMessageEvent, new VersionCheckMessageEvent());
   this->createEvent(Incoming::UniqueIDMessageEvent, new UniqueIDMessageEvent());
   this->createEvent(Incoming::AuthenticateMessageEvent, new AuthenticateMessageEvent());

    // User
   this->createEvent(Incoming::InfoRetrieveMessageEvent, new InfoRetrieveMessageEvent());
   this->createEvent(Incoming::CurrencyBalanceMessageEvent, new CurrencyBalanceMessageEvent());

    // Misc
   this->createEvent(Incoming::LatencyTestMessageEvent, new LatencyTestMessageEvent());
   this->createEvent(Incoming::EventLogMessageEvent, new EventLogMessageEvent());
    
    // Navigator
   this->createEvent(Incoming::SearchNewNavigatorEvent, new SearchNewNavigatorEvent());
   this->createEvent(Incoming::NewNavigatorMessageEvent, new NewNavigatorMessageEvent());
   this->createEvent(Incoming::LeaveRoomMessageEvent, new LeaveRoomMessageEvent());
   this->createEvent(Incoming::CreateRoomMessageEvent, new CreateRoomMessageEvent());

    // Room
   this->createEvent(Incoming::RoomInfoMessageEvent, new RoomInfoMessageEvent());
   this->createEvent(Incoming::EnterRoomMessageEvent, new EnterRoomMessageEvent());
   this->createEvent(Incoming::HeightMapMessageEvent, new HeightMapMessageEvent());
   this->createEvent(Incoming::UserWalkMessageEvent, new WalkMessageEvent());
   this->createEvent(Incoming::RoomEditInfoMessageEvent, new RoomEditInfoMessageEvent());
   this->createEvent(Incoming::DeleteRoomMessageEvent, new DeleteRoomMessageEvent());
   this->createEvent(Incoming::SaveRoomMessageEvent, new SaveRoomMessageEvent());
   this->createEvent(Incoming::ChatMessageEvent, new ChatMessageEvent());
   this->createEvent(Incoming::ShoutMessageEvent, new ShoutMessageEvent());
   this->createEvent(Incoming::StartTypingMessageEvent, new TypingStatusMessageEvent());
   this->createEvent(Incoming::StopTypingMessageEvent, new TypingStatusMessageEvent());
   this->createEvent(Incoming::ShowSignMessageEvent, new ShowSignMessageEvent());
   this->createEvent(Incoming::DanceMessageEvent, new DanceMessageEvent());

   // Room Items
   this->createEvent(Incoming::ApplyDecorationMessageEvent, new ApplyDecorationMessageEvent());
   this->createEvent(Incoming::PlaceItemMessageEvent, new PlaceItemMessageEvent());
   this->createEvent(Incoming::MoveItemMessageEvent, new MoveItemMessageEvent());
   this->createEvent(Incoming::MoveWallItemMessageEvent, new MoveItemMessageEvent());
   this->createEvent(Incoming::PickupItemMessageEvent, new PickupItemMessageEvent());
   this->createEvent(Incoming::InteractItemMessageEvent, new InteractItemMessageEvent());

    // Doorbell
   this->createEvent(Incoming::AnswerDoorbellMessageEvent, new AnswerDoorbellMessageEvent());
   this->createEvent(Incoming::EnterDoorbellMessageEvent, new EnterDoorbellMessageEvent());

    // Messenger
   this->createEvent(Incoming::MessengerSearchMessageEvent, new MessengerSearchMessageEvent());
   this->createEvent(Incoming::MessengerInitMessageEvent, new MessengerInitMessageEvent());
   this->createEvent(Incoming::MessengerUpdateMessageEvent, new MessengerUpdateMessageEvent());
   this->createEvent(Incoming::MessengerRequestMessageEvent, new MessengerRequestMessageEvent());
   this->createEvent(Incoming::MessengerAcceptMessageEvent, new MessengerAcceptMessageEvent());
   this->createEvent(Incoming::MessengerDeclineMessageEvent, new MessengerDeclineMessageEvent());
   this->createEvent(Incoming::MessengerDeleteFriendMessageEvent, new MessengerDeleteFriendMessageEvent());
   this->createEvent(Incoming::FollowFriendMessageEvent, new FollowFriendMessageEvent());
   this->createEvent(Incoming::MessengerTalkMessageEvent, new MessengerTalkMessageEvent());
   this->createEvent(Incoming::MessengerInviteMessageEvent, new MessengerInviteMessageEvent());
   
   // Catalogue
   this->createEvent(Incoming::CatalogueTabMessageEvent, new CatalogueTabMessageEvent());
   this->createEvent(Incoming::CataloguePageMessageEvent, new CataloguePageMessageEvent());
   this->createEvent(Incoming::PurchaseObjectMessageEvent, new PurchaseObjectMessageEvent());

   // Item
   this->createEvent(Incoming::InventoryMessageEvent, new InventoryMessageEvent());

}

/*
    Inserts a message handler into the map only if the header doesn't already exist
    @param message header
    @param message event ptr
    @return none
*/
void MessageHandler::createEvent(int header, MessageEvent *event) {

    if (!this->messages.count(header)) {
        //cout << " [MessageHandler] Event registered: " << header << " for event (" << typeid(*event).name() << ") " << endl;
        this->messages.insert(std::make_pair(header, event));
    }
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
                player->close();
                return;
            }
        }

        this->messages.find(header)->second->handle(player, request);

        if (Icarus::getLogConfiguration()->getBool("log.message.handled")) {
            cout << " [MessageHandler] Handled message " << header << " for event (" << typeid(*this->messages.find(header)->second).name() << ") " << endl;
        }
    } else {
        
        if (Icarus::getLogConfiguration()->getBool("log.message.unhandled")) {
            cout << " [MessageHandler] Unhandled message " << header << endl;
        }
    }
}

/*
    Add all outgoing events to script for Lua

    @parma plugin ptr
    @return none
*/
void MessageHandler::addObjects(Plugin *plugin) {


}

/* 
    MessageHandler deconstructor

    Deletes all message event ptr's and clears the map, then finally deletes the map
*/
MessageHandler::~MessageHandler() { 
    for (auto pair : this->messages) delete pair.second;
}
