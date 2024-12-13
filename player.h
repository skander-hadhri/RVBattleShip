#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"

class Player {
public :
    std::string name;
    Board board;


    Player(std::string playerName);
    Board& getBoard();
    std::string getName();
};

#endif // PLAYER_H

