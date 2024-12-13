#include "Ship.h"
#include <iostream>
using namespace std;
#include <cmath>

Ship::Ship(std::string name) : type(name), hits(0) {
	if (name == "battleship") {
		size = 5; hitscore = 4;
	}
	else if (name == "cruiser") {
		hitscore = 4; size = 4;
	}
    else if (name == "destroyer") {
		hitscore = 3; size = 3;
	}
    else if (name == "submarine") {
		hitscore = 2; size = 2;
	}
    else if (name == "fishing boat") {
		hitscore = 1; size = 1;
	}
}

int Ship::getSize() { return size; }
int Ship::getHits() { return hits; }
std::vector<std::pair<int, int>> Ship::getPosition() { return Position; }


std::string Ship::CellInputA1(int i) {
	std::cout << "Please Enter the Cell " << i + 1
		<< "'s Vertical Coordinates for your " << type << ". You have 10 choices from A to J:\n";

	char x; // Vertical coordinate
	int y;  // Horizontal coordinate
	std::string input; // To validate user input

	// Taking the vertical coordinate (x) correctly
	do {
		std::cin >> input; // Read input as a string
		if (input.length() == 1 && isalpha(input[0])) { // Check for single character
			x = toupper(input[0]); // Convert to uppercase
			if (x >= 'A' && x <= 'J') {
				break; // Valid input
			}
		}
		std::cout << "Invalid input. You must enter a character between A and J.\n";
	} while (true);

	// Taking the horizontal coordinate (y) correctly
	std::cout << "Please Enter the Cell " << i + 1
		<< "'s Horizontal Coordinates. You have 10 choices from 1 to 10:\n";
	do {
		std::cin >> input; // Read input as a string
		try {
			y = std::stoi(input); // Attempt to convert input to integer
			if (y >= 1 && y <= 10) {
				break; // Valid input
			}
		}
		catch (std::invalid_argument&) {
			std::cout << "You Didn't Enter a Number! \n";
		}
		catch (std::out_of_range&) {
			// Handle out-of-range numbers
		}
		std::cout << "Invalid input. Please enter a number between 1 and 10.\n";
	} while (true);

	// Combine the coordinates into a string (optional, if needed)
	std::string coordinates = std::string(1, x) + std::to_string(y);

	// Output the result (optional, for debugging purposes)
	std::cout << "You entered: " << coordinates << " for cell number " << i + 1 << "\n";
	return coordinates;
}




bool Ship::isVertical() {
	if (Position.size() <= 1) return true;
	int col = Position[0].second;
	for (size_t i = 1; i < Position.size(); ++i) {
		if (Position[i].second != col || Position[i].first != Position[i - 1].first + 1) {
			return false;
		}
	}
	return true;
}

bool Ship::isHorizontal() {
	if (Position.size() <= 1) return true;
	int row = Position[0].first;
	for (size_t i = 1; i < Position.size(); ++i) {
		if (Position[i].first != row || Position[i].second != Position[i - 1].second + 1) {
			return false;
		}
	}
	return true;
}
bool Ship::isDiagonal() {
	if (Position.size() <= 1) return true;
	for (size_t i = 1; i < Position.size(); ++i) {
		int dx = Position[i].first - Position[i - 1].first;
		int dy = Position[i].second - Position[i - 1].second;
		if (std::abs(dx) != 1 || std::abs(dy) != 1) {
			return false;
		}
	}
	return true;
}

void Ship::sortPositions() {
	std::sort(Position.begin(), Position.end());
}


void Ship::incrementHits() {
	if (hits < size) {
		hits++;
	}
}

bool Ship::isSunk() const {
	if (hits >= hitscore) {
		cout << "Enemy " << type << " was sunk!!! \n";
		return true;
	}
	else {
		return false;
	}

}
bool Ship::checkHit(int x, int y) {
	for (const auto& pos : Position) {
		if (pos.first == x && pos.second == y) {
			incrementHits(); // Register the hit
			return true;
		}
	}
	return false;
}
bool Ship::isSSunk() const {
	if (hits >= hitscore) {
		
		return true;
	}
	else {
		return false;
	}

}


