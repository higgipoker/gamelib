#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace GameLib {

/**
 * \brief convert an int to a string
 * \param i int to convert
 */
std::string IntToString(int i);

/**
 * \brief convert string to list (split)
 */
std::vector<std::string> split(std::string str);

}// GameLib
