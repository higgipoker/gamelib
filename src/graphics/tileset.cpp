#include "tileset.h"
#include <iostream>

#include <GL/glu.h>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

namespace GameLib {

Tileset::Tileset(const std::string &filename, Camera &c)
    : GameLib::Sprite(filename, 1, 1),
      floor_width(10000),
      floor_height(10000),
      camera(c) {
  tiles_wide =
      floor_width / static_cast<unsigned int>(sprite.getTextureRect().width);
  tiles_high =
      floor_height / static_cast<unsigned int>(sprite.getTextureRect().height);

  tile_width = static_cast<unsigned int>(sprite.getTextureRect().width);
  tile_height = static_cast<unsigned int>(sprite.getTextureRect().height);
}

void Tileset::Render(GameLib::Window &window) {
  int drawn_tiles = 0;
  for (unsigned int i = 0; i <= tiles_wide; i++) {
    for (unsigned int j = 0; j <= tiles_high; j++) {
      // get the absolute position of the tile
      sf::IntRect tile_rect(i * tile_width, j * tile_height, tile_width,
                            tile_height);

      // only render if intersects with camera
      if (camera.GetViewInWorld().intersects(tile_rect)) {
        SetPosition(tile_rect.left, tile_rect.top);
        window.Draw(*this);
        ++drawn_tiles;
      }
    }
  }
}

}  // namespace GameLib
