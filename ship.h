#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include <algorithm>

class Ship {
public:
    const std::string type;
    int size;
    int hits;
    std::vector<std::pair<int, int>> Position;
    int hitscore;

    Ship(std::string name);
    int getSize();
    int getHits();
    std::vector<std::pair<int, int>> getPosition();
    std::string CellInputA1(int i);
    bool isVertical();
    bool isHorizontal();
    bool isDiagonal();
    void sortPositions();
    void incrementHits();
    bool isSunk() const;
    bool checkHit(int x, int y);
    bool isSSunk() const;

};

;

#endif // SHIP_H
