#pragma once
#include <string>

using namespace std;

class SessionDetails {

private:
    int id;
    string username;
    string motto;
    string figure;
    int rank;
    int credits;
    string machine_id;
    bool authenticated;

public:
    SessionDetails();
    ~SessionDetails();
    void fill(int id, string username, string motto, string figure, int rank, int credits);

    int getId() { return id; }
    string getUsername() { return username; }
    string getMotto() { return motto; }
    string getFigure() { return figure; }
    int getRank() { return rank; }
    int getCredits() { return credits; }
    
    string getMachineId() { return machine_id; }
    void setMachineId(string machine_id) { machine_id = machine_id; }
};