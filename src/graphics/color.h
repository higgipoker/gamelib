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
    Color(int red, int green, int blue, int alpha = 255);

    // ----------------------------------------------------
    // () operator
    // ----------------------------------------------------
    double operator()(int _r, int _g, int _b, int _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    /// components
    int r, g, b, a;
};

} // GameLib
