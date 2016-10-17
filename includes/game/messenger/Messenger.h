/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/player/Player.h"
#include "game/messenger/MessengerUser.h"

class Messenger {

private:
    bool initialised;
    Player *player;

    std::vector<MessengerUser*> *friends = nullptr;
    std::vector<MessengerUser*> *requests = nullptr;

public:
    Messenger(std::vector<MessengerUser*> *friends, std::vector<MessengerUser*> *requests);
    ~Messenger();
    MessengerUser *getRequest(int user_id);
    MessengerUser *getFriend(int user_id);
    bool hasRequest(int id);
    bool isFriend(int id);
    void removeFriend(int user_id);
    void sendStatus(bool force_offline);

    /*public boolean hasReqest(int id) {
        return this.getRequest(id) != null;
    }

    public boolean isFriend(int id) {
        return this.getFriend(id) != null;
    }

    public MessengerUser getFriend(int id) {
        try {
            return this.friends.stream().filter(f->f.getDetails().getId() == id).findFirst().get();
        }
        catch (Exception e) {
            return null;
        }
    }

    public MessengerUser getRequest(int id) {
        try {
            return this.requests.stream().filter(r->r.getDetails().getId() == id).findFirst().get();
        }
        catch (Exception e) {
            return null;
        }
    }


    public void removeFriend(int id) {
        MessengerUser user = this.getFriend(id);
        this.friends.remove(user);
    }

    public void sendStatus(boolean forceOffline) {

        Response message = new MessengerUpdateMessageComposer(new MessengerUser(this.session.getDetails().getId()), forceOffline);

        for (MessengerUser friend : this.friends) {

            if (friend.isOnline()) {
                if (friend.getSession().getMessenger().hasInitalised()) {
                    friend.getSession().send(message);
                }
            }
        }
    }

    public void dispose() {

        this.sendStatus(false);

        if (this.friends != null) {
            this.friends.clear();
            this.friends = null;
        }

        if (this.requests != null) {
            this.requests.clear();
            this.requests = null;
        }

        this.session = null;
    }*/
};