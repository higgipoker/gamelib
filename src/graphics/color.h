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
    Color (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

    // ----------------------------------------------------
    // () operator
    // ----------------------------------------------------
    void operator() (unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    /// components
    unsigned char r, g, b, a;
};

} // GameLib
