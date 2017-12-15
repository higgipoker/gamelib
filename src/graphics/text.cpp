#include "text.h"
#include <iostream>

namespace GameLib {

Text::Text(const std::string &fontfile) {

    if (!font.loadFromFile(fontfile)) {
        std::cout << "could not load font: " << fontfile << std::endl;
    }

    text.setFont(font);
}

Text::Text(const std::string &fontfile, const std::string &label)
 : text(label, font) {

    if (!font.loadFromFile(fontfile)) {
        std::cout << "could not load font: " << fontfile << std::endl;
    }
}

void GameLib::Text::Render(Window &window) {
    text.setPosition(geometry.x, geometry.y);
    window.Draw(text);
}

const sf::Drawable &Text::get() {
    return text;
}

void Text::SetText(const std::string &label) {
    text.setString(label);
}

void Text::SetColor(const Color &c) {
    text.setOutlineColor(sf::Color(c.r, c.g, c.b, c.a));
}

float Text::GetWidth() {
    return text.getLocalBounds().width;
}

float Text::GetHeight() {
    return text.getLocalBounds().height;
}

Label::Label(const std::string &fontname, int fontheight)
 : Text(fontname) {
    text.setCharacterSize(fontheight);
}

Label::Label(const std::string &fontname, int fontheight, const std::string &label)
 : Text(fontname, label) {
    text.setCharacterSize(fontheight);
}

} // GameLib
