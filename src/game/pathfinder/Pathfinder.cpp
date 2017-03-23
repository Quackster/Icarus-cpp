/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"

#include <algorithm>

#include "Pathfinder.h"

#include "game/item/Item.h"
#include "game/item/definitions/ItemDefinition.h"

#include "game/room/model/DynamicModel.h"

/*
    Deconstructor for Pathfinder
*/
Pathfinder::~Pathfinder() { }

/*
Creates a valid path when given current coordinates and goal coordinates, the list returned
is actually backwards and needs to be reversed.

@param Position start
@param Position end
@return vector of positions
*/
std::deque<Position> Pathfinder::makePath(Position start, Position end, Room *room) {

    std::deque<Position> positions;

    if (!start.sameAs(end)) {
        
        std::shared_ptr<PathfinderNode> nodes = makePathReversed(start, end, room);

        if (nodes != nullptr) {
            while (nodes != nullptr) {
                positions.push_back(nodes->position);
                nodes = nodes->node;
            }
        }

        std::reverse(positions.begin(), positions.end());

        if (positions.size() > 0) {
            positions.pop_front(); // idk why but it always puts an invalid tile at the front ??? need to fix later
        }
    }

    return positions;
}

/*
Returns a tree of PathfinderNode's which needs to be looped through to get the valid path with
node->getNextNode()

@param Position start
@param Position end
@return vector of positions
*/
std::shared_ptr<PathfinderNode> Pathfinder::makePathReversed(Position start, Position end, Room *room) {

    std::deque<std::shared_ptr<PathfinderNode>> open_list;

    RoomModel *model = room->getModel();

    int map_size_x = model->map_size_x;
    int map_size_y = model->map_size_y;
    std::map<int, std::map<int, std::shared_ptr<PathfinderNode>>> map;

    std::shared_ptr<PathfinderNode> node = std::make_shared<PathfinderNode>();
    std::shared_ptr<PathfinderNode> current = std::make_shared<PathfinderNode>(start);
    current->cost = 0;

    Position tmp(0, 0);
    int cost = 0;
    int diff = 0;

    map[start.x][start.y] = current;

    open_list.push_back(current);

    while (open_list.size() > 0) {

        current = open_list.front();
        open_list.pop_front();
        current->in_close = true;

        for (Position pos : Pathfinder::getPoints()) { // looping through all 8 points

            tmp = current->position.addPoint(pos);
            bool is_final_move = tmp.sameAs(end);

            if (isValidStep(room, current->position, tmp, is_final_move)) {

                if (map[tmp.x][tmp.y] == nullptr) {

                    /*if (!room->getModel()->isValidSquare(tmp.getX(), tmp.getY())) {
                        return nullptr;
                    }*/

                    node = std::make_shared<PathfinderNode>(tmp);
                    map[tmp.x][tmp.y] = node;
                }
                else {
                    node = map[tmp.x][tmp.y];
                }

                if (!node->in_close) {

                    diff = 0;

                    if (current->position.x != node->position.x) {
                        diff += 1;
                    }

                    if (current->position.y != node->position.y) {
                        diff += 1;
                    }

                    cost = current->cost + diff + node->position.getDistance(end);

                    if (cost < node->cost) {
                        node->cost = cost;
                        node->node = current;
                    }

                    if (!node->in_open) {
                        if (node->position.sameAs(end)) {
                            node->node = current;
                            return node;
                        }

                        node->in_open = true;
                        open_list.push_back(node);

                    }
                }
            }
        }
    }

    return nullptr;
}

/*
    Returns whether or not the current tile to check is actually a valid step

    @param Room ptr
    @param Position current position
    @param Postion tmp (the coordinate to check)
    @param if last move
    @return boolean true if valid, false if not.
*/
bool Pathfinder::isValidStep(Room *room, Position current, Position neighbour, bool is_final_move) {


    int map_size_x = room->getModel()->map_size_x;
    int map_size_y = room->getModel()->map_size_y;

    if (neighbour.x >= map_size_x || neighbour.y >= map_size_y) {
        return false;
    }

    if (current.x >= map_size_x || current.y >= map_size_y) {
        return false;
    }

    if (neighbour.x < 0 || neighbour.y < 0) {
        return false;
    }

    if (current.x < 0 || current.y < 0) {
        return false;
    }

    double height1 = room->getDynamicModel()->getStackHeight(current.x, current.y);
    double height2 = room->getDynamicModel()->getStackHeight(neighbour.x, neighbour.y);

    double abs = std::abs(height1 - height2);

    Item *item1 = room->getDynamicModel()->getItemAtPosition(current.x, current.y);
    Item *item2 = room->getDynamicModel()->getItemAtPosition(neighbour.x, neighbour.y);

    if (item1 != nullptr || item2 != nullptr) {

        if (abs >= 1) {
            return false;
        }

        if (abs <= 0.2) {

            if (item2 != nullptr) {
                if (item2->getDefinition()->interaction_type == "gate") {
                    if (item2->extra_data != "1") {
                        return false;
                    }
                }

                return item2->canWalk();
            }

            if (item1 != nullptr) {
                if (item1->getDefinition()->interaction_type == "gate") {
                    if (item1->extra_data != "1") {
                        return false;
                    }
                }

                return item1->canWalk();
            }

            return true;
        }
    }

    return room->getDynamicModel()->isValidTile(current.x, current.y);
}