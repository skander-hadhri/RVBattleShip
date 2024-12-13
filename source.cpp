#include "Board.h"
#include "Ship.h"
#include "Player.h"
#include "game.h"
#include <iostream>
using namespace std;

int main() {
    // Create a Game object with two players
    Game battleship("Player 1", "Player 2");

    // Start the game
    battleship.start();

    return 0;
}
