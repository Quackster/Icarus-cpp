#include "stdafx.h"

#include <deque>

#include "game/room/Room.h"
#include "game/room/model/RoomModel.h"
#include "game/pathfinder/Pathfinder.h"

Pathfinder::Pathfinder() :
    room_user(nullptr) { 
    //this->path = std::queue<Position*>();
}


Pathfinder::Pathfinder(RoomUser *room_user) :
    room_user(room_user) { 
    //this->path = std::queue<Position*>();
}

Pathfinder::~Pathfinder()
{
}

std::queue<Position*> Pathfinder::findPath() {

    std::queue<Position*> points;

    bool MadeProgress = true;

    while (MadeProgress)
    {
        Position *NextPoint = new Position(-1, -1);
        Position *LastPoint = nullptr;

        if (points.size() > 0)
        {
            LastPoint = points.back();
        }

        int FromX = 0;
        int FromY = 0;

        if (LastPoint != nullptr)
        {
            FromX = LastPoint->getX();
            FromY = LastPoint->getY();
        }
        else
        {
            FromX = this->room_user->getPosition().getX();
            FromY = this->room_user->getPosition().getY();
        }

        //Position target = this->room_user->getPosition();

        if (FromX == target.getX() && FromY == target.getY())
        {
            break;
        }

        if (FromX > target.getX() && FromY > target.getY())
        {
            NextPoint = new Position(FromX - 1, FromY - 1);
        }
        else if (FromX < target.getX() && FromY < target.getY())
        {
            NextPoint = new Position(FromX + 1, FromY + 1);
        }
        else if (FromX > target.getX() && FromY < target.getY())
        {
            NextPoint = new Position(FromX - 1, FromY + 1);
        }
        else if (FromX < target.getX() && FromY > target.getY())
        {
            NextPoint = new Position(FromX + 1, FromY - 1);
        }
        else if (FromX > target.getX())
        {
            NextPoint = new Position(FromX - 1, FromY);
        }
        else if (FromX < target.getX())
        {
            NextPoint = new Position(FromX + 1, FromY);
        }
        else if (FromY < target.getY())
        {
            NextPoint = new Position(FromX, FromY + 1);
        }
        else if (FromY > target.getY())
        {
            NextPoint = new Position(FromX, FromY - 1);
        }

        MadeProgress = (NextPoint->getX() > -1 && NextPoint->getY() > -1);

        if (LastPoint != nullptr && NextPoint->getX() == LastPoint->getX() && NextPoint->getX() == LastPoint->getX())
        {
            MadeProgress = false;
        }

        /*RoomModel *model = this->room_user->getRoom()->getData()->getModel();

        if (model->getSquares()[NextPoint->getX() * model->getMapSizeY() + NextPoint->getY()] == 1)
        {
            MadeProgress = false;
        }*/


        if (MadeProgress)
        {
            points.push(NextPoint);
        }
    }

    return points;
}

void Pathfinder::moveTo(Position position) {

    this->clear();
    this->target = position;
    this->path = this->findPath();
}

Position Pathfinder::getNextStep() {

    if (this->isCompleted()) {

        return Position();
    }

    Position *next = this->path.front();
    Position next_position(next->getX(), next->getY());

    this->path.pop();
    delete next;

    return next_position;
}