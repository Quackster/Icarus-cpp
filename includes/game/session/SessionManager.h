#pragma once
#include "Session.h"

#include <iostream>
#include <map>
class SessionManager 
{

public:
    SessionManager();
    ~SessionManager();
    void addSession(Session *session, int connection_id);
    void removeSession(int connection_id);
    bool containsSession(int connection_id);
    Session* getSession(int connection_id);

private:
    std::map<int, Session*> *sessions;

};