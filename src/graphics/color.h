#include <SFML/Graphics/Color.hpp>
#pragma once

namespace GameLib {

class Color {
  public:
    /**
     * @brief constructor
     */
    Color();

    /**
     * @brief constructor
     * @param red red
     * @param green green
     * @param blue blue
     * @param alpha alpha
     */
    Color(unsigned char red, unsigned char green, unsigned char blue,
          unsigned char alpha = 255);

    // ----------------------------------------------------
    // () operator
    // ----------------------------------------------------
    void operator()(unsigned char _r, unsigned char _g, unsigned char _b,
                    unsigned char _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    /**
     * @brief ToSFMLColor
     * @return
     */
    sf::Color ToSFMLColor() {
        sf::Color c;
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = a;

        return c;
    }

    /// components
    unsigned char r, g, b, a;
};

} // GameLib
