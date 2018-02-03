#include "gfx_tools.h"

#include <iostream>

namespace GameLib {

void replace_color (sf::Image &img, std::pair<sf::Color, sf::Color> colors) {
    for (unsigned int x = 0; x < img.getSize().x; ++x) {
        for (unsigned int y = 0; y < img.getSize().y; ++y) {
            if (img.getPixel (x, y) == colors.first) {
                img.setPixel (x, y, colors.second);
            }
        }
    }
}

} // namespace GameLib
