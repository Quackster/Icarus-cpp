/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

class Item;
class Room;
class BaseInteractor
{

public:
    virtual void onInteract(Room *room, Item *item) = 0;
    virtual ~BaseInteractor() {}
};