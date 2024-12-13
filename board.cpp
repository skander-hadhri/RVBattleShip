#include "Board.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define NULL // Unnecessary, but retained for consistency

/**
 * @brief Constructs a Board object.
 *
 * Initializes a 10x10 game grid with all cells set to '.'.
 */
Board::Board() : Grid(10, std::vector<char>(10, '.')) {}

/**
 * @brief Checks if a specific cell on the board is empty.
 * @param x The row index of the cell.
 * @param y The column index of the cell.
 * @return True if the cell is empty and within bounds, false otherwise.
 */
bool Board::isEmpty(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size && Grid[x][y] == '.';
}

/**
 * @brief Places a ship on the board.
 * @param s The ship to be placed.
 *
 * This function prompts the user to input cell coordinates for the ship's placement.
 * Ensures that the ship's cells are correctly aligned and do not overlap with existing ships.
 * Displays the board after each step of the placement process.
 */
void Board::setPosition(Ship s) {
    std::cout << "We are setting up the coordinates for a " << s.type
        << " (size: " << s.size << ") in the form of (CharacterNumber), e.g., A1:\n";
    displayBoard(true);

    for (size_t i = 0; i < s.size; ++i) {
        while (true) {
            std::string coord = s.CellInputA1(i);
            std::pair<int, int> position;

            try {
                position = convertToCoordinates(coord);
            }
            catch (std::invalid_argument&) {
                std::cout << "Invalid coordinate format. Try again.\n";
                continue;
            }

            int x = position.first;
            int y = position.second;

            if (i == 0) {
                // Place the first cell
                if (isEmpty(x, y)) {
                    s.Position.push_back({ x, y });
                    Grid[x][y] = 'S';
                    break;
                }
                else {
                    std::cout << "Oops! This place is already occupied. Try again.\n";
                }
            }
            else {
                // Tentatively add position to the ship
                if (isEmpty(x, y)) {
                    s.Position.push_back({ x, y });
                    s.sortPositions();

                    // Validate arrangement
                    if (s.isHorizontal() || s.isVertical() || s.isDiagonal()) {
                        Grid[x][y] = 'S'; // Placement is valid
                        break;
                    }
                    else {
                        // Invalid alignment, remove the newly added position
                        auto it = std::find(s.Position.begin(), s.Position.end(), std::make_pair(x, y));
                        if (it != s.Position.end()) {
                            s.Position.erase(it);
                        }
                        std::cout << "Invalid placement. Ensure alignment and adjacency. Try again.\n";
                    }
                }
                else {
                    std::cout << "Oops! This place is already occupied. Try again.\n";
                }
            }
        }

        // Show updated board
        std::cout << "Updated board after placing cell " << i + 1 << ":\n";
        displayBoard(true);
    }

    // Finalize ship placement
    ShipList.push_back(s);

    std::cout << "Final board after placing the " << s.type << ":\n";
    displayBoard(true);
}

/**
 * @brief Marks a hit or miss on the board based on the attack coordinates.
 * @param x The row index of the attack.
 * @param y The column index of the attack.
 * @return True if the attack was a hit, false otherwise.
 */
bool Board::markHit(int x, int y) {
    char& cell = Grid[x][y];

    if (cell == 'X' || cell == 'O') {
        std::cout << "This cell was already attacked. Try another.\n";
        return false; // No new action occurred
    }

    if (cell == 'S') { // Ship cell
        cell = 'X'; // Mark as hit
        for (Ship& ship : ShipList) {
            if (ship.checkHit(x, y)) {
                return true; // Hit successful
            }
        }
    }
    else {
        cell = 'O'; // Mark as miss
    }

    return false; // Miss
}

/**
 * @brief Checks if all ships on the board have been destroyed.
 * @return True if all ships are destroyed, false otherwise.
 */
bool Board::areAllShipsDestroyed()  {
    for (const Ship& ship : ShipList) {
        if (ship.isSSunk() && ship.type == "battleship") {
            for (int k = 0; k < (ship.Position).size(); k++) {
                int x = ship.Position[k].first;
                int y = ship.Position[k].second;
                Grid[x][y]='X';
            }

        }
        if (!ship.isSSunk()) {
            return false; // A ship is still afloat
        }
    }
    return true; // All ships are destroyed
}

/**
 * @brief Displays the current board.
 * @param showShips If true, shows the ships; otherwise, hides them.
 */
void Board::displayBoard(bool showShips) const {
    // Print column numbers with proper spacing
    std::cout << "    ";
    for (int col = 1; col <= size; ++col) {
        std::cout << (col < 10 ? " " : "") << col << " ";
    }
    std::cout << "\n   +" << std::string(size * 3, '-') << "+\n";

    // Print each row with row labels (A-J)
    for (int row = 0; row < size; ++row) {
        std::cout << " " << static_cast<char>('A' + row) << " |";
        for (int col = 0; col < size; ++col) {
            char cell = Grid[row][col];
            if (!showShips && cell == 'S') {
                cell = '.'; // Hide ships unless hit
            }
            std::cout << " " << cell << " ";
        }
        std::cout << "|\n";
    }

    std::cout << "   +" << std::string(size * 3, '-') << "+\n"; // Bottom border
}

/**
 * @brief Displays the current status of all ships on the board.
 *
 * Includes details like type, hits, and remaining cells for each ship.
 */
void Board::showStatus() {
    std::cout << "These are all your current ship statistics:\n";

    // Find the maximum length of ship names for formatting
    size_t maxShipNameLength = 0;
    for (const Ship& ship : ShipList) {
        maxShipNameLength = std::max(maxShipNameLength, ship.type.length());
    }

    // Define column widths
    size_t shipColWidth = std::max(maxShipNameLength, static_cast<size_t>(10));
    size_t hitScoreColWidth = 10;
    size_t hitsColWidth = 6;
    size_t cellsRemainingColWidth = 17;

    // Print the table header
    std::cout << std::string(shipColWidth + hitScoreColWidth + hitsColWidth + cellsRemainingColWidth + 13, '-') << "\n";
    std::cout << "| " << std::setw(shipColWidth) << std::left << "Ship Type"
        << " | " << std::setw(hitScoreColWidth) << "Hit Score"
        << " | " << std::setw(hitsColWidth) << "Hits"
        << " | " << std::setw(cellsRemainingColWidth) << "Cells Remaining" << " |\n";
    std::cout << std::string(shipColWidth + hitScoreColWidth + hitsColWidth + cellsRemainingColWidth + 13, '-') << "\n";

    // Print each ship's status
    for (const Ship& ship : ShipList) {
        if (!ship.isSSunk()) {
            std::cout << "| " << std::setw(shipColWidth) << std::left << ship.type
                << " | " << std::setw(hitScoreColWidth) << std::right << ship.hitscore
                << " | " << std::setw(hitsColWidth) << ship.hits
                << " | " << std::setw(cellsRemainingColWidth) << (ship.hitscore - ship.hits) << " |\n";
        }
        else {
            std::cout << "| " << std::setw(shipColWidth) << std::left << ship.type
                << " | " << std::setw(hitScoreColWidth) << "Out!"
                << " | " << std::setw(hitsColWidth) << "-"
                << " | " << std::setw(cellsRemainingColWidth) << "-" << " |\n";
        }
    }

    // Print the table footer
    std::cout << std::string(shipColWidth + hitScoreColWidth + hitsColWidth + cellsRemainingColWidth + 13, '-') << "\n";
}
