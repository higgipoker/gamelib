#include "color.h"

namespace GameLib {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Color::Color() {
    r = g = b = a = 0;
}

// ------------------------------------------------------------
// construcotr
// ------------------------------------------------------------
Color::Color(int red, int green, int blue, int alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

} // GameLib
