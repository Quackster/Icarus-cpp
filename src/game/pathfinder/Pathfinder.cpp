#include "stdafx.h"

#include <deque>

#include "game/pathfinder/Pathfinder.h"


Pathfinder::~Pathfinder()
{
}

std::vector<Position> Pathfinder::makePath(Position start, Position end, Room *room) {

    std::vector<Position> positions;

    std::shared_ptr<PathfinderNode> nodes = makePathReversed(start, end, room);

    if (nodes != nullptr) {
        while (nodes != nullptr) {
            positions.push_back(nodes->getPosition());
            nodes = nodes->getNextNode();
        }
    }

    return positions;
}

std::shared_ptr<PathfinderNode> Pathfinder::makePathReversed(Position start, Position end, Room *room) {

    std::deque<std::shared_ptr<PathfinderNode>> open_list;

    RoomModel *model = room->getData()->getModel();

    int map_size_x = model->getMapSizeX();
    int map_size_y = model->getMapSizeY();
    std::map<int, std::map<int, std::shared_ptr<PathfinderNode>>> map;

    /*for (int x = 0; x < map_size_x; x++) {
        for (int y = 0; y < map_size_y; y++) {
            map[x][y] = std::shared_ptr<nullptr>();
        }
        std::cout << std::endl;
    }*/

    std::shared_ptr<PathfinderNode> node = std::make_shared<PathfinderNode>();

    Position tmp(0, 0);
    int cost = 0;
    int diff = 0;

    std::shared_ptr<PathfinderNode> current = std::make_shared<PathfinderNode>(start);
    std::shared_ptr<PathfinderNode> finish = std::make_shared<PathfinderNode>(end);
    current->setCost(0);

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
                        if (node->getPosition().sameAs(finish->getPosition())) {
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

        int map_size_x = room->getData()->getModel()->getMapSizeX();
        int map_size_y = room->getData()->getModel()->getMapSizeY();

        if (current.getX() > map_size_x && current.getY() > map_size_y) {
            return false;
        }

        if (tmp.getX() > map_size_x && tmp.getY() > map_size_y) {
            return false;
        }

        int tile = room->getData()->getModel()->getSquares()[tmp.getX() * map_size_y + tmp.getY()];

        return tile == 1 ? false : true;

    }
    catch (std::exception &e) {
        return false;
    }


}