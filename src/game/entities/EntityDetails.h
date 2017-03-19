/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

class Entity;
class EntityDetails
{

public:
    EntityDetails(Entity *entity);
    ~EntityDetails();

    void setCredits(int new_amount);

    Entity *entity;

    int id;
    std::string username;
    std::string motto;
    std::string figure;
    int rank;
    int credits;
    std::string machine_id;
    bool authenticated;
    bool has_logged_in = true;
};