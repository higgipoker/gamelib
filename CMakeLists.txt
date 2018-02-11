cmake_minimum_required (VERSION 2.6)

# ----------------------------------------------------------------------------------------------------
# compiler flags
add_definitions(-std=c++11)

# ----------------------------------------------------------------------------------------------------
# project name
project (gamelib)

# ----------------------------------------------------------------------------------------------------
# cmake environment varables
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)


# ----------------------------------------------------------------------------------------------------
# include dirs
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(/usr/local/include)

# ----------------------------------------------------------------------------------------------------
# library dirs
link_directories(/usr/local/lib)

# ----------------------------------------------------------------------------------------------------
# project build
#add_library(gamelib STATIC
add_library(gamelib SHARED
src/gamelib.h
src/graphics/events.h
src/graphics/window.cpp
src/graphics/renderable.cpp
src/graphics/sprite.cpp
src/graphics/tileset.cpp
src/graphics/animation.cpp
src/graphics/text.cpp
src/graphics/primitives.cpp
src/graphics/color.cpp
src/graphics/palette.cpp
src/graphics/gfx_tools.cpp
src/camera/camera.cpp
src/input/input.cpp
src/input/keyboard.cpp
src/input/mouse.cpp
src/statemachine/state_machine.cpp
src/statemachine/state.cpp
src/math/constants.h
src/math/vector3.h
src/math/shapes.cpp
src/physics/physical.cpp
src/physics/collision_detector.cpp
src/game/game.cpp
src/game/game_entity.cpp
src/console/console.cpp
src/utils/timer.cpp
src/utils/converter.cpp
src/utils/log.cpp
src/utils/grid.cpp
src/files/file.cpp
)
# ----------------------------------------------------------------------------------------------------



# ----------------------------------------------------------------------------------------------------
# install
install (TARGETS gamelib DESTINATION /usr/local/lib)

#gamelib header
install(FILES
src/gamelib.h
DESTINATION /usr/local/include/gamelib)

#install graphics header files
install(FILES
src/graphics/window.h
src/graphics/events.h
src/graphics/renderable.h
src/graphics/sprite.h
src/graphics/tileset.h
src/graphics/animation.h
src/graphics/text.h
src/graphics/primitives.h
src/graphics/color.h
src/graphics/palette.h
DESTINATION /usr/local/include/gamelib/graphics)

#install camera header files
install(FILES
src/camera/camera.h
DESTINATION /usr/local/include/gamelib/camera)

#install input header files
install(FILES
src/input/input.h
src/input/keyboard.h
src/input/keycodes.h
src/input/mouse.h
DESTINATION /usr/local/include/gamelib/input)

#install state machine header files
install(FILES
src/statemachine/state_machine.h
src/statemachine/state.h
DESTINATION /usr/local/include/gamelib/statemachine)

#install math header files
install(FILES
src/math/constants.h
src/math/vector3.h
src/math/shapes.h
DESTINATION /usr/local/include/gamelib/math)

#install physical header files
install(FILES
src/physics/physical.h
src/physics/collision_detector.h
DESTINATION /usr/local/include/gamelib/physics)

#install game header files
install(FILES
src/game/game.h
src/game/game_entity.h
DESTINATION /usr/local/include/gamelib/game)

#install console header files
install(FILES
src/console/console.h
DESTINATION /usr/local/include/gamelib/console)

#install utils header files
install(FILES
src/utils/timer.h
src/utils/converter.h
src/utils/log.h
src/utils/grid.h
DESTINATION /usr/local/include/gamelib/utils)

#install files header files
install(FILES
src/files/file.h
DESTINATION /usr/local/include/gamelib/files)

#install gamelib header files
install(FILES
src/gamelib.h
DESTINATION /usr/local/include/gamelib)

# --------------------------------------------------
# link libs
# --------------------------------------------------

