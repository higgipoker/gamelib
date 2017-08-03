cmake_minimum_required (VERSION 2.6)

# ----------------------------------------------------------------------------------------------------
# compiler flags
add_definitions(-std=c++11)

# ----------------------------------------------------------------------------------------------------
# project name
project (gamelib)

# ----------------------------------------------------------------------------------------------------
# cmake environment varables
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ----------------------------------------------------------------------------------------------------
# include dirs
include_directories(${PROJECT_SOURCE_DIR}/src)

# ----------------------------------------------------------------------------------------------------
# project build
#add_library(gamelib STATIC
add_library(gamelib SHARED

src/gamelib.h
#graphics
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

src/camera/camera.cpp

src/input/input.cpp
src/input/keyboard.cpp

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
install (TARGETS gamelib DESTINATION lib)

#gamelib header
install(FILES
src/gamelib.h
DESTINATION include/gamelib)

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
DESTINATION include/gamelib/graphics)

#install camera header files
install(FILES
src/camera/camera.h
DESTINATION include/gamelib/camera)

#install input header files
install(FILES
src/input/input.h
src/input/keyboard.h
DESTINATION include/gamelib/input)

#install state machine header files
install(FILES
src/statemachine/state_machine.h
src/statemachine/state.h
DESTINATION include/gamelib/statemachine)

#install math header files
install(FILES
src/math/constants.h
src/math/vector3.h
src/math/shapes.h
DESTINATION include/gamelib/math)

#install physical header files
install(FILES
src/physics/physical.h
src/physics/collision_detector.h
DESTINATION include/gamelib/physics)

#install game header files
install(FILES
src/game/game.h
src/game/game_entity.h
DESTINATION include/gamelib/game)

#install console header files
install(FILES
src/console/console.h
DESTINATION include/gamelib/console)

#install utils header files
install(FILES
src/utils/timer.h
src/utils/converter.h
src/utils/log.h
src/utils/grid.h
DESTINATION include/gamelib/utils)

#install files header files
install(FILES
src/files/file.h
DESTINATION include/gamelib/files)
