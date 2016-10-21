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

#include "game/pathfinder/Pathfinder.h"


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
                positions.push_back(nodes->getPosition());
                nodes = nodes->getNextNode();
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

    int map_size_x = model->getMapSizeX();
    int map_size_y = model->getMapSizeY();
    std::map<int, std::map<int, std::shared_ptr<PathfinderNode>>> map;

    std::shared_ptr<PathfinderNode> node = std::make_shared<PathfinderNode>();
    std::shared_ptr<PathfinderNode> current = std::make_shared<PathfinderNode>(start);
    current->setCost(0);

    Position tmp(0, 0);
    int cost = 0;
    int diff = 0;

    map[start.getX()][start.getY()] = current;

    open_list.push_back(current);

    while (open_list.size() > 0) {

        current = open_list.front();
        open_list.pop_front();
        current->setInClose(true);

        for (Position pos : Pathfinder::getPoints()) {

            tmp = current->getPosition().addPoint(pos);
            bool is_final_move = tmp.sameAs(end);

            if (isValidStep(room, current->getPosition(), tmp, is_final_move)) {

                if (map[tmp.getX()][tmp.getY()] == nullptr) {

                    /*if (!room->getModel()->isValidSquare(tmp.getX(), tmp.getY())) {
                        return nullptr;
                    }*/

                    node = std::make_shared<PathfinderNode>(tmp);
                    map[tmp.getX()][tmp.getY()] = node;
                }
                else {
                    node = map[tmp.getX()][tmp.getY()];
                }

                if (!node->getInClose()) {

                    diff = 0;

                    if (current->getPosition().getX() != node->getPosition().getX()) {
                        diff += 1;
                    }

                    if (current->getPosition().getY() != node->getPosition().getY()) {
                        diff += 1;
                    }

                    cost = current->getCost() + diff + node->getPosition().getDistance(end);

                    if (cost < node->getCost()) {
                        node->setCost(cost);
                        node->setNextNode(current);
                    }

                    if (!node->getInOpen()) {
                        if (node->getPosition().sameAs(end)) {
                            node->setNextNode(current);
                            return node;
                        }

                        node->setInOpen(true);
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
bool Pathfinder::isValidStep(Room *room, Position current, Position tmp, bool is_final_move) {

    try {

        int map_size_x = room->getModel()->getMapSizeX();
        int map_size_y = room->getModel()->getMapSizeY();

        if (tmp.getX() >= map_size_x || tmp.getY() >= map_size_y) {
            return false;
        }

        if (current.getX() >= map_size_x || current.getY() >= map_size_y) {
            return false;
        }

        if (tmp.getX() < 0 || tmp.getY() < 0) {
            return false;
        }

        if (current.getX() < 0|| current.getY() < 0) {
            return false;
        }

        if (!room->getModel()->isValidSquare(tmp.getX(), tmp.getY())) {
            return false;
        }

        return true;

    }
    catch (std::exception &e) {
        return false;
    }

}