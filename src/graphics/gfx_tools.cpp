#include "gfx_tools.h"

#include <iostream>

namespace GameLib {

void replace_color(sf::Image &img, std::pair<sf::Color, sf::Color> colors) {

    sf::Color old_col = colors.first;
    sf::Color new_col = colors.second;

    for(int x = 0; x < img.getSize().x; ++x) {
        for(int y = 0; y < img.getSize().y; ++y) {
            sf::Color color = img.getPixel(x, y);

            if(color == old_col) {
                img.setPixel(x, y, new_col);
            }
        }
    }
}

}// namespace GameLib
