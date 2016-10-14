/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

class EntityDetails
{

public:

    ~EntityDetails() { }

    virtual int &getId() = 0;
    virtual std::string const &getUsername() const = 0;
    virtual std::string const &getMotto() const = 0;
    virtual std::string const &getFigure() const = 0;
    virtual int &getRank() = 0;
    virtual int &getCredits() = 0;
};