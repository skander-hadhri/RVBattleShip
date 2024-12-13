#include "Player.h"

Player::Player(std::string playerName) : name(playerName) {}

Board& Player::getBoard() {
    return board;
}

std::string Player::getName() {
    return name;
}
