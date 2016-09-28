#pragma once
#include <winsock.h>
#include "Response.h"

using namespace std;

class NetworkConnection 
{

public:
    NetworkConnection(int connectionID, SOCKET socket);
    ~NetworkConnection();
    void handle_data(char* data, int length);
    void write_data(Response request);
    void sendPolicy();
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
