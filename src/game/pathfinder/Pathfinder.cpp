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
        printf ("testing\n");
        while (nodes != nullptr) {
            positions.push_back(Position(nodes->getPosition().getX(), nodes->getPosition().getY()));
            //nodes_remove.push_back(nodes); // add to delete
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

    int map_size_x = model->getMapSizeX() + 20;
    int map_size_y = model->getMapSizeY() + 20;

    PathfinderNode **map = new PathfinderNode*[map_size_x * map_size_y];

    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {
            map[(x * map_size_y) + y] = nullptr;
        }
    }

    PathfinderNode *node = nullptr;
    Position tmp(0, 0);
    int cost;
    int diff;

    PathfinderNode *current = new PathfinderNode(start);
    PathfinderNode *finish = new PathfinderNode(end);
    current->setCost(0);

    map[(start.getX() * map_size_y) + start.getY()] = current;

    if (map[(start.getX() * map_size_y) + start.getY()] == nullptr) {
        printf("null!!\n");
    }

    open_list.push_back(current);

    while (open_list.size() > 0) {

        current = open_list.front();
        open_list.pop_front();
        current->setInClose(true);

        for (int i = 0; i < 8; i++) {

            Position temp_point = getPoints()[i];
            Position tmp = current->getPosition().addPoint(temp_point);

            bool is_final_move = (tmp.getX() == end.getX()) && (tmp.getY() == tmp.getY());

            if (model->getSquares()[(current->getPosition().getX() * map_size_y) + current->getPosition().getX()] == 0) {

                try {
                    if (map[(tmp.getX() * map_size_y) + tmp.getY()] == nullptr) {
                        node = new PathfinderNode(tmp);
                        //printf("testing %s \n", node->getPosition().toString().c_str());
                        map[(tmp.getX() * map_size_y) + tmp.getY()] = node;
                    }
                    else {
                        node = map[(tmp.getX() * map_size_y) + tmp.getY()];
                    }
                }
                catch (std::exception &e) {
                    continue;
                }

                if (node->inClose() == false) {
                    diff = 0;

                   // printf("testing\n");

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

                        node->setInOpen(true);
                        open_list.push_back(node);

                    }
                }
            }
        }
    }

    return nullptr;
}
