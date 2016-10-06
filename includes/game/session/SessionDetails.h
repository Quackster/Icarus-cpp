#pragma once
#include <string>

class SessionDetails {

private:
    int id;
    std::string username;
    std::string motto;
    std::string figure;
    int rank;
    int credits;
    std::string machine_id;
    bool authenticated;

public:
    SessionDetails(int id, std::string username, std::string motto, std::string figure, int rank, int credits);
    ~SessionDetails();

    int getId() { return id; }
    std::string getUsername() { return username; }
    std::string getMotto() { return motto; }
    std::string getFigure() { return figure; }
    int getRank() { return rank; }
    int getCredits() { return credits; }
    
    std::string getMachineId() { return machine_id; }
    void setMachineId(std::string machine_id) { machine_id = machine_id; }
};