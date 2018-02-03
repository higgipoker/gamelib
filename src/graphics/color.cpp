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
Color::Color (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

} // GameLib
