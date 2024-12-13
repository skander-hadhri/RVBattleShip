#include "game.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <utility>

// Constructor
Game::Game(const std::string& player1Name, const std::string& player2Name)
    : player1(player1Name), player2(player2Name) {
    currentPlayer = &player1;
    opponent = &player2;
}

// Main game loop
void Game::start() {
    std::cout << "Welcome to Battleship!\n";

    // Placement Phase
    std::cout << player1.getName() << ", place your ships:\n";
    placeShips(player1);

    std::cout << player2.getName() << ", place your ships:\n";
    placeShips(player2);

    // Attack Phase
    while (true) {
        std::cout <<currentPlayer->getName() << ", it's your turn to attack!\n";
        (currentPlayer->getBoard()).showStatus();
        /*opponent->getBoard().displayBoard(false); */// Hide opponent's ships

        attack(*currentPlayer, *opponent);

        if (checkVictory(*opponent)) {
            std::cout << currentPlayer->getName() << " wins the game!\n";
            break;
        }

        // Switch turns
        std::swap(currentPlayer, opponent);
    }
}

// Place ships for a player
void Game::placeShips(Player& player) {
    std::vector<std::string> shipTypes = { "battleship", "cruiser", "destroyer","submarine","submarine", "fishing boat" };
    for (const std::string& type : shipTypes) {
        Ship ship(type);
        player.getBoard().setPosition(ship);
    }
}

// Attack logic
void Game::attack(Player& attacker, Player& defender) {
    while (true) { // Keep prompting until a valid attack is made
        // Display both the attack board and the player's own board side-by-side
        
        std::cout << "Your Hit Board (Hit the opponent):             Your Own Board:\n";
        attacker.getBoard().displayBoardsSideBySide(defender.getBoard()); // Only display once

        // Input attack coordinates
        std::pair<int, int> attackCoordinates = getAttackInput();
        int x = attackCoordinates.first;
        int y = attackCoordinates.second;

        // Check if the cell was already attacked
        char cell = defender.getBoard().Grid[x][y];
        if (cell == 'X' || cell == 'O') {
            std::cout << "This cell was already attacked. Try another.\n";
            continue; // Stay in the loop for new input
        }

        // Process the attack
        if (defender.getBoard().markHit(x, y)) {
            std::cout << "It's a hit!\n";

            // Check for victory
            if (defender.getBoard().areAllShipsDestroyed()) {
                std::cout << "All ships of " << defender.getName() << " are destroyed!\n";
            }
        }
        else {
            std::cout << "It's a miss!\n";
        }
        

        break; // Exit the loop after a valid hit or miss
    }
}







// Check victory condition
bool Game::checkVictory(Player& player) {
    return player.getBoard().areAllShipsDestroyed();
}
