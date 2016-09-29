#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <stdlib.h>
#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <string>

#include "Response.h"

using namespace std;

class NetworkConnection 
{

public:
    NetworkConnection(int connectionID, SOCKET socket);
    ~NetworkConnection();
    
    void sendPolicy();
    void sendRaw(char* buffer, int len);
    void write_data(Response response);
    void handle_data(char* data, int length);
    
    /*
        Getters and setters
    */
    int getConnectionId() { return connectionID; }
    bool getConnectionState() { return connected; }
    void setConnectionState(bool state) { connected = state; }
    SOCKET getSocket() { return socket; };
    DWORD getThreadId() { return thread_id; }

private:
    int connectionID;
    bool connected;
    SOCKET socket;
    DWORD thread_id;
    void createThread();

};
