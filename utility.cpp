#include "utility.h"
#include <iostream>
#include <string>
#include<vector>
#include <stdexcept>
#include <cctype>
#include "board.h"


std::pair<int, int> convertToCoordinates(const std::string& coordinate) {
    if (coordinate.size() == 2) {
        char row = coordinate[0];
        char col = coordinate[1];
        int x = row - 'A';
        int y = col - '1';

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            return { x, y };
        }
    }
    else if (coordinate.size() == 3) { // Handles inputs like A10
        char row = coordinate[0];
        int x = row - 'A';
        int y = 9; // Last column for 10

        if (x >= 0 && x < 10) {
            return { x, y };
        }
    }
}



std::pair<int, int> getAttackInput() {
    while (true) {
        try {
            // Input for the row
            std::string rowInput;
            std::cout << "Enter the row (A-J): ";
            std::cin >> rowInput;

            if (rowInput.size() != 1 || !isalpha(rowInput[0])) {
                throw std::invalid_argument("Row must be a single letter (A-J).");
            }

            // Convert to uppercase and validate range
            char rowChar = toupper(rowInput[0]);
            if (rowChar < 'A' || rowChar > 'J') {
                throw std::invalid_argument("Row must be between A and J.");
            }
            int row = rowChar - 'A';

            // Input for the column
            std::string colInput;
            std::cout << "Enter the column (1-10): ";
            std::cin >> colInput;

            // Ensure column is a number
            for (char c : colInput) {
                if (!isdigit(c)) {
                    throw std::invalid_argument("Column must be a number (1-10).");
                }
            }

            // Convert and validate range
            int col = std::stoi(colInput) - 1; // Convert to zero-based index
            if (col < 0 || col >= 10) {
                throw std::out_of_range("Column must be between 1 and 10.");
            }

            return { row, col };
        }
        catch (std::exception& e) {
            std::cout << "Invalid input: " << e.what() << ". Please try again.\n";
        }
    }
}






