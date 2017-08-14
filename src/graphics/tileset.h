#pragma once

#include "../camera/camera.h"
#include "window.h"
#include "sprite.h"

namespace GameLib {

class Tileset : public Sprite{
public:
	/**
	 * @brief constructor
	 */
	explicit Tileset(const std::string& filename, Camera &c);

	/**
	 * @brief render to window
	 */
	virtual void Render(GameLib::Window &window) override;


protected:
	/// tile world dimensions
	unsigned int floor_width, floor_height;

	/// number tiles to fill world
	unsigned int tiles_wide, tiles_high;

	/// tile dimensions
	unsigned int tile_width, tile_height;

	/// tileset needs a camera for rendering
	Camera &camera;
};

}// GameLib
