#include "renderable.h"

#include "gfx_tools.h"
#include "primitives.h"
#include "sprite.h"
#include "window.h"
#include <iostream>

namespace GameLib {

static std::map<std::string, TrackableTexture> texture_list;

// ------------------------------------------------------------
// constructor
// ------------------------------------------------------------
Renderable::Renderable() {}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Renderable::Renderable(const std::string &filename) : texture_filename(filename) {

    // if the same texture source exists, don't create a duplicate
    auto it = texture_list.find(filename);
    if (it != texture_list.end()) {
        texture = (*it).second.tex;
        (*it).second.ref_counter++;

    } else {

        // create new texture
        texture = new sf::Texture();
        if (!texture->loadFromFile(filename)) {
            std::cout << "Could not load image file: " << filename << std::endl;
        } else {
            texture_list.insert(std::make_pair(filename, TrackableTexture(texture)));
        }
    }

    // set renderable texture for future use
    sprite.setTexture(*texture);

    // dimensions tracking
    geometry.w = texture->getSize().x;
    geometry.h = texture->getSize().y;
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Renderable::Renderable(const GameLib::Renderable &other) : z_order(0), texture(nullptr), texture_filename(other.texture_filename) {
    paletted_texture = nullptr;
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Renderable::~Renderable() {

    // search for this texture in the list
    auto it = texture_list.find(texture_filename);

    if (it != texture_list.end()) {

        // decrement reference counter
        (*it).second.ref_counter -= 1;

        // if reference counter had become zero, delete the texture and remove
        // from list
        if ((*it).second.ref_counter == 0) {

            // free memory
            delete (*it).second.tex;

            // remove pointer from list
            texture_list.erase(it);
        }
    }

    if (paletted_texture) {
        delete paletted_texture;
    }
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Renderable::Render(GameLib::Window &window) {

    if (visible) {
        window.Draw(*this);
    }
}

// ------------------------------------------------------------
// SetPosition
// ------------------------------------------------------------
void Renderable::SetPosition(float x, float y) {
    geometry.x = x;
    geometry.y = y;
    sprite.setPosition(sf::Vector2f(x, y));
}

// ------------------------------------------------------------
// SwapColors
// ------------------------------------------------------------
void Renderable::SwapColors(std::vector<std::pair<Color, Color>> palette) {

    if (paletted_texture) {
        delete paletted_texture;
    }

    paletted_texture = new sf::Texture();
    sf::Image img = texture->copyToImage();

    for (auto colour : palette) {
        replace_color(img, colour);
    }

    paletted_texture->loadFromImage(img);
    sprite.setTexture(*paletted_texture);
}
} // GameLib
