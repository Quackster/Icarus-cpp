#include "stdafx.h"

#include <deque>

#include "game/pathfinder/Pathfinder.h"


Pathfinder::~Pathfinder()
{
}

std::vector<Position> Pathfinder::makePath(Position start, Position end, Room *room) {

    std::vector<Position> positions;
    std::vector<PathfinderNode*> nodes_remove;

    // PATHFINDERNODE NEEDS TO BE POINTER TO DECLARE ITSELF INSIDE IT'S OWN CLASS

    PathfinderNode *nodes = makePathReversed(start, end, room);

    if (nodes != nullptr) {
        while (nodes != nullptr) {
            positions.push_back(Position(nodes->getPosition().getX(), nodes->getPosition().getY()));
            nodes_remove.push_back(nodes); // add to delete
            nodes = nodes->getNextNode();
        }
    }

    for (auto node : nodes_remove) {
        delete node;
    }

    return positions;
}

PathfinderNode *Pathfinder::makePathReversed(Position start, Position end, Room *room) {

    RoomModel *model = room->getData()->getModel();

    std::deque<PathfinderNode*> open_list;
    PathfinderNode **map = new PathfinderNode*[model->getMapSizeX() * model->getMapSizeY()];

    for (int y = 0; y < model->getMapSizeY(); y++) {
        for (int x = 0; x < model->getMapSizeX(); x++) {
            map[(x * model->getMapSizeY()) + y] = nullptr;
        }
    }

    PathfinderNode *node = nullptr;
    Position tmp(0, 0);
    int cost;
    int diff;

    PathfinderNode *current = new PathfinderNode(start);
    PathfinderNode *finish = new PathfinderNode(end);
    current->setCost(0);

    map[(start.getX() * model->getMapSizeY()) + start.getY()] = current;

    open_list.push_back(current);

    while (open_list.size() > 0) {

        current = open_list.front();
        open_list.pop_front();
        current->seInClose(true);

        for (int i = 0; i < 8; i++) {

            Position temp_point = getPoints()[i];
            Position tmp = current->getPosition().addPoint(temp_point);

            bool is_final_move = (tmp.getX() == end.getX()) && (tmp.getY() == tmp.getY());

            if (model->getSquares()[(current->getPosition().getX() * model->getMapSizeY()) + current->getPosition().getX()] == 0) {

                if (map[(tmp.getX() * model->getMapSizeY()) + tmp.getX()] == nullptr) {
                    node = new PathfinderNode(tmp);
                    map[(tmp.getX() * model->getMapSizeY()) + tmp.getX()] = node;
                }
                else {
                    node = map[(tmp.getX() * model->getMapSizeY()) + tmp.getX()];
                }

                if (node->inClose() == false) {
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

                    if (node->inOpen() == false) {
                        if (node->getPosition().getX() == finish->getPosition().getX() && node->getPosition().getY() == finish->getPosition().getY()) {
                            node->setNextNode(current);
                            return node;
                        }

                        node->seInOpen(true);
                        open_list.push_back(node);

                    }
                }
            }
        }
    }

    return nullptr;
}
