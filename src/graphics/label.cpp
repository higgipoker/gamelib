#include "label.h"

namespace GameLib {

// ------------------------------------------------------------
// Label
// ------------------------------------------------------------
Label::Label(const std::string &fontname, unsigned int fontheight)
    : Text(fontname) {
    text.setCharacterSize(fontheight);
}

// ------------------------------------------------------------
// Label
// ------------------------------------------------------------
Label::Label(const std::string &fontname, unsigned int fontheight,
             const std::string &label)
    : Text(fontname, label) {
    text.setCharacterSize(fontheight);
}

} // namespace GameLib
