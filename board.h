#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Ship.h"
#include "utility.h"
#include "board.h"
#include <iostream>
#include <string>
#include <vector>

class Board {
public:
    
    std::vector<std::vector<char>> Grid;
    std::vector<Ship> ShipList;
    const int size = 10;


    Board();
    bool isEmpty(int x, int y);
    void setPosition(Ship s);
    void displayBoard(bool showShips) const;
    void showStatus() ;
    bool markHit(int x, int y);
    bool areAllShipsDestroyed() const;
    void displayBoardsSideBySide(const Board& attackBoard) const {
        const int size = attackBoard.Grid.size(); // Use the size of the enemy board's grid

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
                char cell = Grid[row][col];
                std::cout << " " << cell << " ";
            }
            std::cout << "|\n";
        }

        // Print bottom borders for both boards
        std::cout << "   +" << std::string(size * 3, '-') << "+     +" << std::string(size * 3, '-') << "+\n";
    }


};

#endif // BOARD_H
