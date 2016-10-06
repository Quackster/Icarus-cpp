#pragma once
#include "Session.h"

#include <iostream>
#include <map>
class SessionManager 
{

public:
    SessionManager();
    ~SessionManager();
    void addSession(Session *session, int connectionID);
    void removeSession(int connectionID);
    bool containsSession(int connectionID);
    Session* getSession(int connectionID);

private:
    std::map<int, Session*> *sessions;

};