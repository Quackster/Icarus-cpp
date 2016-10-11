#pragma once
#include <string>

class Position
{
public:
    Position();
    Position(int x, int y);
    ~Position();

    Position addPoint(Position point) {
        return Position(x + point.getX(), y + point.getY());
    }

    Position subtractPoint(Position point) {
        return Position(x - point.getX(), y - point.getY());
    }

    int getDistance(Position point) {
        int dx = x - point.x;
        int dy = y - point.y;
        return (dx * dx) + (dy * dy);
    }

    bool sameAs(Position point) {
        return x == point.getX() && y == point.getY();
    }

    bool isNull() {
        return x == -999 && y == -999;
    }

    std::string toString() {
        return std::to_string(x) + ", " + std::to_string(y);
    }

    int getX() { return x; }
    int getY() { return y; }

private:
    int x;
    int y;
};

