#pragma once

#include <string>

#include "camera/camera.h"

#include "game/game.h"
#include "game/game_entity.h"

#include "graphics/animation.h"
#include "graphics/events.h"
#include "graphics/primitives.h"
#include "graphics/renderable.h"
#include "graphics/sprite.h"
#include "graphics/text.h"
#include "graphics/tileset.h"
#include "graphics/window.h"

#include "input/input.h"
#include "input/keyboard.h"

#include "math/constants.h"
#include "math/shapes.h"
#include "math/vector3.h"

#include "physics/collision_detector.h"
#include "physics/physical.h"

#include "statemachine/state.h"
#include "statemachine/state_machine.h"

namespace GameLib {
static const std::string &gamelib_version = "0.0.0";
}
