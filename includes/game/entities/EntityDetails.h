#pragma once

class EntityDetails
{

public:

    ~EntityDetails() { }

    virtual int getId() = 0;
    virtual std::string getUsername() = 0;
    virtual std::string getMotto() = 0;
    virtual std::string getFigure() = 0;
    virtual int getRank() = 0;
    virtual int getCredits() = 0;
};