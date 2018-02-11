#include "renderable.h"

#include "gfx_tools.h"
#include "primitives.h"
#include "sprite.h"
#include "window.h"
#include <iostream>

namespace GameLib {

int Renderable::shadow_z = 0;
static std::map<std::string, TrackableTexture> texture_list;

// ------------------------------------------------------------
// constructor
// ------------------------------------------------------------
Renderable::Renderable() : z_order(0), texture_filename("[non-textured-renderable]") {
    texture = nullptr;
    paletted_texture = nullptr;
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Renderable::Renderable(const std::string &filename) : z_order(0), texture(nullptr), texture_filename(filename) {

    paletted_texture = nullptr;

    auto it = texture_list.find(filename);

    if (it != texture_list.end()) {
        texture = (*it).second.tex;
        (*it).second.ref_counter++;

    } else {

        texture = new sf::Texture();

        if (!texture->loadFromFile(filename)) {
            std::cout << "Could not load image file: " << filename << std::endl;

        } else {
            texture_list.insert(std::make_pair(filename, TrackableTexture(texture)));
        }
    }

    // set renderable texture for future use
    sprite.setTexture(*texture);

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

        // if reference counter had become zero, delete the texture and remove from list
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

#ifdef RENDER_DEBUG
        // outline
        Primitives::Rectangle(window, this->GetPosition().x, this->GetPosition().y, this->GetWidth(), this->GetHeight());
#endif
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
// count_renderables
// ------------------------------------------------------------
unsigned int Renderable::count_renderables() {
    unsigned int total = 0;

    for (auto it = texture_list.begin(); it != texture_list.end(); ++it) {
        total += (*it).second.ref_counter;
    }

    return total;
}

// ------------------------------------------------------------
// SwapColors
// ------------------------------------------------------------
void Renderable::SwapColors(std::vector<std::pair<sf::Color, sf::Color>> palette) {

    if (paletted_texture) {
        delete paletted_texture;
    }

    paletted_texture = new sf::Texture();
    sf::Image img = texture->copyToImage();

    for (auto it = palette.begin(); it != palette.end(); ++it) {
        replace_color(img, *it);
    }

    paletted_texture->loadFromImage(img);
    sprite.setTexture(*paletted_texture);
}
} // GameLib
