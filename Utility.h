#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include "board.h"



std::pair<int, int> convertToCoordinates(const std::string& coordinate);
std::pair<int, int> getAttackInput();
#endif // UTILITY_H
