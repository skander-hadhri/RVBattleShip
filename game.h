#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <string>

class Game {
private:
    Player player1;          // First player
    Player player2;          // Second player
    Player* currentPlayer;   // Pointer to the current player
    Player* opponent;        // Pointer to the opponent

public:
    Game(const std::string& player1Name, const std::string& player2Name); // Constructor

    void start(); // Main method to run the game

private:
    void placeShips(Player& player);     // Method for ship placement phase
    void attack(Player& attacker, Player& defender); // Method to handle attacks
    bool checkVictory(Player& player);  // Check if a player has lost
};

#endif // GAME_H
