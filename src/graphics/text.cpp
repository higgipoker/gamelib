#include "text.h"
#include <iostream>

namespace GameLib {

// ------------------------------------------------------------
// Text
// ------------------------------------------------------------
Text::Text(const std::string &fontfile) {

    if (!font.loadFromFile(fontfile)) {
        std::cout << "could not load font: " << fontfile << std::endl;
    }

    text.setFont(font);
}

// ------------------------------------------------------------
// Text
// ------------------------------------------------------------
Text::Text(const std::string &fontfile, const std::string &label)
    : text(label, font) {

    if (!font.loadFromFile(fontfile)) {
        std::cout << "could not load font: " << fontfile << std::endl;
    }
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void GameLib::Text::Render(Window &window) {
    text.setPosition(geometry.x, geometry.y);
    window.Draw(text);
}

// ------------------------------------------------------------
// Get
// ------------------------------------------------------------
const sf::Drawable &Text::Get() { return text; }

// ------------------------------------------------------------
// SetText
// ------------------------------------------------------------
void Text::SetText(const std::string &label) { text.setString(label); }

// ------------------------------------------------------------
// GetText
// ------------------------------------------------------------
std::string Text::GetText() { return text.getString(); }

// ------------------------------------------------------------
// SetColor
// ------------------------------------------------------------
void Text::SetColor(const Color &c) {
    text.setOutlineColor(sf::Color(c.r, c.g, c.b, c.a));
}

// ------------------------------------------------------------
// GetSize
// ------------------------------------------------------------
Dimension Text::GetSize() {
    return Dimension(text.getLocalBounds().width, text.getLocalBounds().height);
}

} // GameLib
