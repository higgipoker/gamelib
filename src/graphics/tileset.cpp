#include "tileset.h"
#include <iostream>
namespace GameLib {

Tileset::Tileset(const std::string &filename, Camera &c) : GameLib::Sprite(filename, 1, 1), floor_width(10000), floor_height(10000), camera(c) {

    tiles_wide = 1 + (floor_width / static_cast<unsigned int>(sprite.getTextureRect().width));
    tiles_high = 1 + (floor_height / static_cast<unsigned int>(sprite.getTextureRect().height));

    tile_width = static_cast<unsigned int>(sprite.getTextureRect().width);
    tile_height = static_cast<unsigned int>(sprite.getTextureRect().height);
}

void Tileset::Render(GameLib::Window &window) {
    for (unsigned int i = 0; i <= tiles_wide; i++) {
        for (unsigned int j = 0; j <= tiles_high; j++) {

            // get the absolute position of the tile
            Rectangle tile_rect(i * tile_width, j * tile_height, tile_width, tile_height);

            // find intersection
            if (tile_rect.overlaps(camera.GetViewport())) {
                SetPosition(tile_rect.x, tile_rect.y);
                window.Draw(*this);
            }
        }
    }
}

} // GameLib
