#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Ship.h"
#include "utility.h"
#include "board.h"
#include <iostream>
#include <string>

/**
 * @class Board
 * @brief Represents the game board in the Battleship game.
 *
 * The Board class manages the grid, ship placement, attack handling, and
 * provides functionality to display the game board and track ship statuses.
 */
class Board {
public:
    /**
     * @brief The game grid, represented as a 2D vector of characters.
     *
     * Each cell of the grid can represent the following:
     * - 'S' for ship
     * - '.' for an empty cell
     * - 'X' for a hit
     * - 'O' for a miss
     */
    std::vector<std::vector<char>> Grid;

    /**
     * @brief A list of ships placed on the board.
     */
    std::vector<Ship> ShipList;

    /**
     * @brief The size of the game grid (default: 10x10).
     */
    const int size = 10;

    /**
     * @brief Constructs a new Board object.
     *
     * Initializes an empty game grid and prepares the board for ship placement.
     */
    Board();

    /**
     * @brief Checks if a specific cell on the grid is empty.
     * @param x The row index of the cell.
     * @param y The column index of the cell.
     * @return True if the cell is empty, false otherwise.
     */
    bool isEmpty(int x, int y);

    /**
     * @brief Places a ship on the board.
     * @param s The ship to be placed.
     *
     * The method ensures that the ship's cells are correctly aligned
     * and do not overlap with existing ships.
     */
    void setPosition(Ship s);

    /**
     * @brief Displays the game board.
     * @param showShips If true, shows the ships; otherwise, hides them.
     *
     * Useful for displaying the player's own board or an opponent's attack board.
     */
    void displayBoard(bool showShips) const;

    /**
     * @brief Displays the current status of all ships on the board.
     *
     * This method provides information about which ships are still afloat
     * and which have been destroyed.
     */
    void showStatus();

    /**
     * @brief Marks a hit or miss on the board based on the attack coordinates.
     * @param x The row index of the attack.
     * @param y The column index of the attack.
     * @return True if the attack was a hit, false otherwise.
     */
    bool markHit(int x, int y);

    /**
     * @brief Checks if all ships on the board have been destroyed.
     * @return True if all ships are destroyed, false otherwise.
     */
    bool areAllShipsDestroyed() ;

    /**
     * @brief Displays two boards side-by-side: the attack board and the own board.
     * @param attackBoard The board representing the player's view of their opponent's grid.
     *
     * This method is particularly useful for visualizing both the player's attacks
     * and their own board in a single view.
     */
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
