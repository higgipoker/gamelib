#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace GameLib {
namespace Converter {

/**
 * @brief convert an int to a string
 * @param i int to convert
 */
std::string IntToString (int i);

/**
 * @brief convert string to list (split)
 */
std::vector<std::string> Split (std::string str);

} // Converter
} // GameLib
