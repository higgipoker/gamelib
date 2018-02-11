#pragma once

#include "color.h"
#include <SFML/Graphics.hpp>
#include <map>

namespace GameLib {

/**
 * @brief replace_color
 * @param img
 * @param colors
 */
void replace_color(sf::Image &img, std::pair<Color, Color> colors);

} // namespace GameLib
