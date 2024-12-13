#include "Board.h"
#include "Utility.h"
#include <iostream>
using namespace std;
#include<string>
#define NULL

#include <iostream>
#include <vector>
#include <iomanip>


Board::Board() : Grid(10, std::vector<char>(10, '.')) {}

bool Board::isEmpty(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size && Grid[x][y] == '.';
}

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
                        // Invalid alignment, find and remove the newly added position
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


bool Board::markHit(int x, int y) {
    char& cell = Grid[x][y];

    // Check if the cell was already attacked
    if (cell == 'X' || cell == 'O') {
        std::cout << "This cell was already attacked. Try another.\n";
        return false; // Indicate no new action occurred
    }

    // Check if the cell contains a ship
    if (cell == 'S') {
        cell = 'X'; // Mark as a hit
        for (Ship& ship : ShipList) {
            if (ship.checkHit(x, y)) {
                return true; // Hit successful
            }
        }
    }
    else {
        cell = 'O'; // Mark as a miss
    }

    return false; // Miss
}


bool Board::areAllShipsDestroyed() const {
    for (const Ship& ship : ShipList) {
        if (!ship.isSSunk()) {
            return false; // A ship is still afloat
        }
    }
    return true; // All ships are destroyed
}
;


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

    // Print the bottom border
    std::cout << "   +" << std::string(size * 3, '-') << "+\n";
}
void displayBoardsSideBySide(const Board& attackBoard, const Board& ownBoard) {
    const int size = attackBoard.size; // Assuming the board is a square grid (10x10)

    // Print column headers for both boards
    std::cout << "    ";
    for (int col = 1; col <= size; ++col) {
        std::cout << (col < 10 ? " " : "") << col << " ";
    }
    std::cout << "         ";
    for (int col = 1; col <= size; ++col) {
        std::cout << (col < 10 ? " " : "") << col << " ";
    }
    std::cout << "\n   +" << std::string(size * 3, '-') << "+     +" << std::string(size * 3, '-') << "+\n";

    // Print each row for both boards side-by-side
    for (int row = 0; row < size; ++row) {
        // Attack board row
        std::cout << " " << static_cast<char>('A' + row) << " |";
        for (int col = 0; col < size; ++col) {
            char cell = attackBoard.Grid[row][col];
            if (cell == 'S') {
                cell = '.'; // Hide ships on the attack board
            }
            std::cout << " " << cell << " ";
        }
        std::cout << "|     "; // Spacer between boards

        // Own board row
        std::cout << static_cast<char>('A' + row) << " |";
        for (int col = 0; col < size; ++col) {
            char cell = ownBoard.Grid[row][col];
            std::cout << " " << cell << " ";
        }
        std::cout << "|\n";
    }

    // Print bottom borders for both boards
    std::cout << "   +" << std::string(size * 3, '-') << "+     +" << std::string(size * 3, '-') << "+\n";
}
//void displayBoardPlayerStatus({
void Board::showStatus() {
    cout << "These are all your current ship statistics : \n";
    // Find the maximum length of ship names for dynamic column width
    size_t maxShipNameLength = 0;
    for (const Ship& ship : ShipList) {
        maxShipNameLength = std::max(maxShipNameLength, ship.type.length());
    }

    // Define column widths
    size_t shipColWidth = std::max(maxShipNameLength, static_cast<size_t>(10)); // Minimum width of 10
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
            if (ship.size == 5) {
                for (int i = 0; i < 5; i++) {
                    int x = (ship.Position[i]).first;
                    int y = (ship.Position)[i].second;
                    Grid[x][y] = 'X';
                }
                std::cout << "| " << std::setw(shipColWidth) << std::left << ship.type
                    << " | " << std::setw(hitScoreColWidth) << "Out!"
                    << " | " << std::setw(hitsColWidth) << "-"
                    << " | " << std::setw(cellsRemainingColWidth) << "-" << " |\n";
            }
            else {
                std::cout << "| " << std::setw(shipColWidth) << std::left << ship.type
                    << " | " << std::setw(hitScoreColWidth) << "Out!"
                    << " | " << std::setw(hitsColWidth) << "-"
                    << " | " << std::setw(cellsRemainingColWidth) << "-" << " |\n";

            }


            
        }
    }

    // Print the table footer
    std::cout << std::string(shipColWidth + hitScoreColWidth + hitsColWidth + cellsRemainingColWidth + 13, '-') << "\n";
}







