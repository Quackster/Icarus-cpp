#include "stdafx.h"

#include <deque>

#include "game/pathfinder/Pathfinder.h"


Pathfinder::~Pathfinder()
{
}

std::vector<Position> Pathfinder::makePath(Position start, Position end, Room *room) {

    std::vector<Position> positions;
    std::vector<PathfinderNode*> nodes_remove;

    try {
        // PATHFINDERNODE NEEDS TO BE POINTER TO DECLARE ITSELF INSIDE IT'S OWN CLASS

        PathfinderNode *nodes = makePathReversed(start, end, room);

        if (nodes != nullptr) {
            while (nodes != nullptr) {
                positions.push_back(Position(nodes->getPosition().getX(), nodes->getPosition().getY()));
                //nodes_remove.push_back(nodes); // add to delete
                nodes = nodes->getNextNode();
            }
        }

        for (auto node : nodes_remove) {
            delete node;
        }

    }
    catch (std::exception &e) {
        std::cout << "pathfinder error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "pathfinder error: " << std::endl;
    }

    return positions;
}

PathfinderNode *Pathfinder::makePathReversed(Position start, Position end, Room *room) {

    RoomModel *model = room->getData()->getModel();

    std::deque<PathfinderNode*> open_list;

    int map_size_x = model->getMapSizeX();
    int map_size_y = model->getMapSizeY();

    std::cout << "size x " << map_size_x << ", " << map_size_y << std::endl;
 
    std::map<int, std::map<int, PathfinderNode*>> map;

    for (int y = -1; y < map_size_y; y++) {
        for (int x = -1; x < map_size_x; x++) {
            map[x][y] = nullptr;
        }
    }

    PathfinderNode *node = nullptr;
    Position tmp(0, 0);
    int cost = 0;
    int diff = 0;

    PathfinderNode *current = new PathfinderNode(start);
    PathfinderNode *finish = new PathfinderNode(end);
    current->setCost(0);

    map[start.getX()][start.getY()] = current;

    open_list.push_back(current);

    while (open_list.size() > 0) {

        current = open_list.front();
        open_list.pop_front();
        current->setInClose(true);

        for (int i = 0; i < 8; i++) {

            Position temp_point = getPoints()[i];
            Position tmp = current->getPosition().addPoint(temp_point);

            bool is_final_move = (tmp.getX() == end.getX()) && (tmp.getY() == tmp.getY());

            if (map[tmp.getX()].find(tmp.getY()) != map[tmp.getX()].end() && isValidStep(room, Position(current->getPosition().getX(), current->getPosition().getY()), tmp, is_final_move)) {

                if (map[tmp.getX()][tmp.getY()] == nullptr) {
                    node = new PathfinderNode(tmp);
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

bool Pathfinder::isValidStep(Room *room, Position current, Position tmp, bool is_final_move) {

    try {


        /* if (map.find(tmp.getX()) == map.end()) {
             continue;
         }

         if (map[tmp.getX()].find(tmp.getY()) == map[tmp.getX()].end()) {
             continue;
         }*/

        return room->getData()->getModel()->getSquares()[current.getX()][current.getX()] == 0;

    }
    catch (std::exception &e) {
        return false;
    }


}
