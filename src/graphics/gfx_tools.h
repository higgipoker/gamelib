#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "color.h"

namespace GameLib{

    void replace_color(sf::Image &img, std::pair<sf::Color, sf::Color> colors);

}// namespace GameLib
